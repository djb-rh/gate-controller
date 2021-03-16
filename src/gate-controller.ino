#include "config.h"
#include "particleInt.h"
#include "relayAcc.h"
#include "relayService.h"

#include "HKServer.h"
#include "HKLog.h"

SerialLogHandler logHandler(LOG_LEVEL_ALL);

NCD2Relay relayController;

ParticleInterface *particleInt = new ParticleInterface(&relayController);

void progress(Progress_t progress) {
    hkLog.info("Homekit progress callback: %d", progress);
}

RelayService *services[nRelays];

/* CLOUD FUNCTIONS */
int restart(String extra);

void setup() {
    randomSeed(Time.now());
    
    Serial.begin(115200);

    relayController.setAddress(0, 0, 0);

    for (int r=0; r<nRelays; r++) {
        services[r] = new RelayService(&relayController, particleInt, r);
        services[r]->init();
    }

    Particle.function("restart", restart);
}

void loop() {
    bool didAnything = false;
    for (int r=0; r<nRelays; r++) {
        didAnything |= services[r]->handle();
    }
    
    if (didAnything) {
        /* TODO add logging or something, if we care */
    }
}

int restart(String extra) {
    System.reset();
    return 0;
}
