#ifndef autogate_relayService_h
#define autogate_relayService_h

#include "HAPAccessoryDescriptor.h"
#include "HAPServiceDescriptor.h"
#include "HKAccessory.h"

class RelayService : public HAPServiceDescriptor {
private:
    int port;
    unsigned long lastReportMS;

    boolCharacteristics *powerState;

    std::string getPower(HKConnection *sender);
    void setPower(bool oldValue, bool newValue, HKConnection *sender);

public:
    RelayService(int port) { this->port = port; }

    virtual void initService(Accessory *accessory);
    virtual bool handle();
};

#endif
