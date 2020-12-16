#include "config.h"
#include "relayAcc.h"

#include <Particle.h>

#include "HKConnection.h"
#include "HKLog.h"

void RelayAccessory::identify(bool oldValue, bool newValue, HKConnection *sender) {
    Serial.printf("Start identify\n");
}

std::string RelayAccessory::getPower(HKConnection *sender) {
    return relayController->readRelayStatus(relayNumber) ? "true" : "false";
}

void RelayAccessory::setPower(bool oldValue, bool newValue, HKConnection *sender) {
    if (newValue) {
        relayController->turnOnRelay(relayNumber);
    } else {
        relayController->turnOffRelay(relayNumber);
    }
}

void RelayAccessory::initAccessorySet() {
    Accessory *switchAcc = new Accessory();
    
    AccessorySet *accSet = &AccessorySet::getInstance();
    addInfoServiceToAccessory(switchAcc, "Switch", switchManufacturer, "Switch", "1", "1.0.0", 
            std::bind(&RelayAccessory::identify, this,
                std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    accSet->addAccessory(switchAcc);

    Service *switchService = new Service(serviceType_switch);    
    switchAcc->addService(switchService);

    stringCharacteristics *switchServiceName = new stringCharacteristics(charType_serviceName, permission_read, 0);
    switchServiceName->characteristics::setValue(switchName);
    switchAcc->addCharacteristics(switchService, switchServiceName);

    boolCharacteristics *powerState = new boolCharacteristics(charType_on,
            permission_read|permission_write|permission_notify);
    powerState->perUserQuery = std::bind(&RelayAccessory::getPower, this, std::placeholders::_1);
    powerState->valueChangeFunctionCall = std::bind(&RelayAccessory::setPower, this,
            std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    switchAcc->addCharacteristics(switchService, powerState);
}
