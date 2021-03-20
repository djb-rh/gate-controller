#ifndef autogate_particleInt_h
#define autogate_particleInt_h

#include <Particle.h>

class ParticleInterface {
private:
    char deviceName[32] = "";
    char pubString[40] = "";

    int trips[6]; /* debugTrips */
    bool tripped[6];

    int handleCommand(String command); /* triggerRelay() */

    void nameHandler(const char *topic, const char *data); /* handler() */
    void pubStateHandler(const char *topic, const char *data);
    void triggerRelay(const char *topic, const char *data); /* triggerRelayDos() */

public:
    void initialize();
    void handle(); /* this replaces the logic in the old loop() function */
};

#endif
