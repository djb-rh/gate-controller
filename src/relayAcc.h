#ifndef autogate_relayAcc_h
#define autogate_relayAcc_h

#include "HKAccessory.h"
#include "HAPAccessoryDescriptor.h"

#include "NCD2Relay.h"

class RelayAccessory : public HAPAccessoryDescriptor {
private:
    /* configuration things. useful! */
    const bool debugLogging = true;
    const int minTrips = 5;

    /* homekit config */
    const char *switchManufacturer = "manufacturer";
    const char *switchName = "test switch";

    /* relay config */
    const int relayNumber = 1;

    /* particle config */
    
    NCD2Relay *relayController;

    int REPORT_PERIOD = 2000;
    int lastMs = 0;

    void identify(bool oldValue, bool newValue, HKConnection *sender);

    std::string getPower(HKConnection *sender);
    void setPower(bool oldValue, bool newValue, HKConnection *sender);

public:
    RelayAccessory(NCD2Relay *relay) {
        this->relayController = relay;
    }

    virtual void initAccessorySet();
    virtual bool handle() { return false; }

    virtual int getDeviceType() { return deviceType_switch; }
};

#endif
