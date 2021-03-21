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
                String::format("%s_%d", deviceName.c_str(), port),
                event,
                PRIVATE);
        Serial.println(String::format("%s_%d", deviceName.c_str(), port));
    }

    void pubRelayState(int port, bool powered) {
        pubEvent(port, powered ? "ON" : "OFF");
    }
};
