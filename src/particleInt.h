#ifndef autogate_particleInt_h
#define autogate_particleInt_h

#include "NCD2Relay.h"

class ParticleInterface {
private:
    NCD2Relay *relayController;

    char deviceName[32] = "";
    char pubString[40] = "";

    int trips[6]; /* debugTrips */
    bool tripped[6];

    int handleCommand(String command); /* triggerRelay() */

    void nameHandler(const char *topic, const char *data); /* handler() */
    void pubState(const char *topic, const char *data);
    void triggerRelay(const char *topic, const char *data); /* triggerRelayDos() */

public:
    ParticleInterface(NCD2Relay *relay) {
        this->relayController = relay;
    }

    void initialize();
    void handle(); /* this replaces the logic in the old loop() function */
};

#endif
