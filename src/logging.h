#ifndef autogate_logging_h
#define autogate_logging_h

#include <Particle.h>

namespace ParticleLog {
    void initialize(String name);

    void pubEvent(int port, String event);
    void pubRelayState(int port, bool powered);
}

#endif
