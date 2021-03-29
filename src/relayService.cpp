#include "relayService.h"

#include "config.h"
#include "relay.h"

#include <Particle.h>

#include "HKConnection.h"
#include "HKLog.h" 

std::string RelayService::getPower(HKConnection *sender) {
    return RelayBoard::getPower(port+1) ? "true" : "false";
}

void RelayService::setPower(bool oldValue, bool newValue, HKConnection *sender) {
    RelayBoard::setPower(port+1, newValue);
}

bool RelayService::handle() {
    if ((lastReportMS + Config::reportDelayMS) < millis()) {
        lastReportMS = millis();
        powerState->notify(NULL);
        return true;
    }
    return false;
}

void RelayService::initService(Accessory *accessory) {
    Service *switchService = new Service(serviceType_switch);
    accessory->addService(switchService);

    stringCharacteristics *switchServiceName = new stringCharacteristics(charType_serviceName, permission_read, 0);
    switchServiceName->characteristics::setValue(Config::relayNames[port]);
    accessory->addCharacteristics(switchService, switchServiceName);

    powerState = new boolCharacteristics(charType_on, permission_read|permission_write|permission_notify);
    powerState->perUserQuery = std::bind(&RelayService::getPower, this, std::placeholders::_1);
    powerState->valueChangeFunctionCall = std::bind(&RelayService::setPower, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    accessory->addCharacteristics(switchService, powerState);
}
