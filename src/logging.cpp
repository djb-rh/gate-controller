#include "logging.h"

#include <Particle.h>

namespace ParticleLog {
    namespace {
        String deviceName = "";
    }

    void initialize(String name) {
        deviceName = name;
    }

    void pubEvent(int port, String event) {
        Particle.publish(
                deviceName,
                String::format("%d%s", port, event.c_str()),
                PRIVATE);
    }

    void pubRelayState(int port, bool powered) {
        pubEvent(port, powered ? "ON" : "OFF");
    }
};
