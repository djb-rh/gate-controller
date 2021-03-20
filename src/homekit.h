#ifndef autogate_homekit_h
#define autogate_homekit_h

#include "config.h"
#include "relayService.h"

#include "HAPAccessoryDescriptor.h"
#include "HAPCompositeAccessory.h"
#include "HAPHomekitBridgeAccessory.h"
#include "HKAccessory.h"

class RelayBridge : public HAPHomekitBridgeAccessory {
private:
    HAPCompositeAccessory *relayAcc = new HAPCompositeAccessory();

public:
    RelayBridge() {
        for (int i=0; i<Config::nRelays; i++) {
            relayAcc->descriptors.push_back(new RelayService(i));
        }

        this->descriptors.push_back(relayAcc);
    }
};

#endif
