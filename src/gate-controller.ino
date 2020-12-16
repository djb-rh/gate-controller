#include "config.h"
#include "particleInt.h"
#include "relayAcc.h"

#include "HKServer.h"
#include "HKLog.h"

SerialLogHandler logHandler(LOG_LEVEL_ALL);

HKServer *hkServer = NULL;

NCD2Relay relayController;

RelayAccessory *acc = new RelayAccessory(&relayController);
ParticleInterface *particleInt = new ParticleInterface(&relayController);

void progress(Progress_t progress) {
    hkLog.info("Homekit progress callback: %d", progress);
}

/* CLOUD FUNCTIONS */
int restart(String extra);

void setup() {
    randomSeed(Time.now());
    
    Serial.begin(115200);

    relayController.setAddress(0, 0, 0);

    hkServer = new HKServer(acc->getDeviceType(), "dev-name", "523-12-643", progress);

    acc->initAccessorySet();
    particleInt->initialize();
    hkServer->start();

    Particle.function("restart", restart);
}

void loop() {
    bool didAnything = false;
    didAnything |= hkServer->handle();
    didAnything |= acc->handle();
    if (didAnything) {
    }

    particleInt->handle();
}

int restart(String extra) {
    System.reset();
    return 0;
}
