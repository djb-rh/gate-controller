#ifndef autogate_relayAcc_h
#define autogate_relayAcc_h

#include "HKAccessory.h"
#include "HAPAccessoryDescriptor.h"

#include "NCD2Relay.h"

#include "particleInt.h"

class RelayAccessory : public HAPAccessoryDescriptor {
private:
    NCD2Relay *relayController;
    ParticleInterface *particleInt;

    int REPORT_PERIOD = 2000;
    int lastMs = 0;

    void identify(bool oldValue, bool newValue, HKConnection *sender);

    std::string getPower(HKConnection *sender);
    void setPower(bool oldValue, bool newValue, HKConnection *sender);

public:
    RelayAccessory(NCD2Relay *relay, ParticleInterface *particleInt) {
        this->relayController = relay;
        this->particleInt = particleInt;
    }

    virtual void initAccessorySet();
    virtual bool handle() { return false; }

    virtual int getDeviceType() { return deviceType_switch; }
};

#endif
