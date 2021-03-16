#include "relayService.h"

#include "config.h"
#include "particleInt.h"
#include "relayAcc.h"

#include "HKLog.h"

void progress(Progress_t progress) {
    hkLog.info("Homekit progress callback: %d", progress);
}

RelayService::RelayService(NCD2Relay *relayController, int relayId) {
    this->relayId = relayId;
    
    this->acc = new RelayAccessory(relayController, relayId);
    this->particleInt = new ParticleInterface(relayController);

    this->hkServer = new HKServer(
            this->acc->getDeviceType(),
            relayNames[relayId],
            "523-12-643",
            progress);
}

void RelayService::init() {
    this->acc->initAccessorySet();
    this->particleInt->initialize();
    this->hkServer->start();
}

bool RelayService::handle() {
    bool didAnything = false;
    didAnything |= this->acc->handle();
    didAnything |= this->hkServer->handle();
    this->particleInt->handle();
    return didAnything;
}
