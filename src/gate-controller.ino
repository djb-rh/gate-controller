#include "config.h"
#include "homekit.h"
#include "particleInt.h"
#include "relay.h"

#include "HKLog.h"
#include "HKServer.h"
#include "NCD2Relay.h"

SerialLogHandler logHandler(LOG_LEVEL_ALL);

NCD2Relay relayController;
ParticleInterface *particleInt = NULL;
RelayBridge *acc = NULL;
HKServer *hkServer = NULL;

void progress(Progress_t progress) {
    hkLog.info("Homekit progress callback: %d", progress);
}

/* CLOUD FUNCTIONS */
int restart(String extra);

void setup() {
    randomSeed(Time.now());
    
    Serial.begin(115200);
    
    particleInt = new ParticleInterface();
    particleInt->initialize(); // initializes logging as well

    relayController.setAddress(0, 0, 0);
    RelayBoard::initialize(&relayController);

    acc = new RelayBridge();
    hkServer = new HKServer(acc->getDeviceType(), Config::devName, "523-12-643", progress);
    acc->initAccessorySet();
    hkServer->start();

    Particle.function("restart", restart);
}

void loop() {
    bool didAnything = false;
    didAnything |= hkServer->handle();
    didAnything |= acc->handle();
    
    if (didAnything) {
        /* TODO add logging or something, if we care */
    }

    particleInt->handle();
}

int restart(String extra) {
    System.reset();
    return 0;
}
