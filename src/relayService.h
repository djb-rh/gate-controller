#ifndef autogate_relayService_h
#define autogate_relayService_h

#include "particleInt.h"
#include "relayAcc.h"

#include "NCD2Relay.h"
#include "HKServer.h"

class RelayService {
private:
    RelayAccessory *acc;
    ParticleInterface *particleInt;
    HKServer *hkServer;

    int relayId;
public:
    RelayService(NCD2Relay *relayController, ParticleInterface *particleInt, int relayId);

    void init();
    bool handle();
};

#endif
