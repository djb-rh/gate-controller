#include "particleInt.h"

#include "config.h"
#include "logging.h"
#include "relay.h"

#include <Particle.h>

int ParticleInterface::handleCommand(String command) {
    if (command.equalsIgnoreCase("turnonallrelays")) {
        RelayBoard::setAllPower(true);
        return 1;
    }
    if (command.equalsIgnoreCase("turnoffallrelays")) {
        RelayBoard::setAllPower(false);
        return 1;
    }
    
    /* relay specific commands */
    int relayNumber = command.substring(0, 1).toInt();
    String relayCommand = command.substring(1);

#ifdef serialLogging
    Serial.print("relayNumber: ");
    Serial.println(relayNumber);
    Serial.print("relayCommand: ");
    Serial.println(relayCommand);
#endif
    
    if (relayCommand.equalsIgnoreCase("on")) {
#ifdef serialLogging
        Serial.println("Turning on relay");
#endif
        RelayBoard::setPower(relayNumber, true);
        return 1;
    }

    if (relayCommand.equalsIgnoreCase("off")) {
#ifdef serialLogging
        Serial.println("Turning off relay");
#endif
        RelayBoard::setPower(relayNumber, false);
        return 1;
    }
    
    if (relayCommand.equalsIgnoreCase("toggle")) {
#ifdef serialLogging
        Serial.println("Toggling relay");
#endif
        RelayBoard::togglePower(relayNumber);
        return 1;
    }
    
    if (relayCommand.equalsIgnoreCase("momentary")) {
#ifdef serialLogging
        Serial.println("Momentarily toggling relay");
#endif
        RelayBoard::togglePower(relayNumber);
        delay(300);
        RelayBoard::togglePower(relayNumber);
        return 1;
    }
    return 0;
}

void ParticleInterface::nameHandler(const char *topic, const char *data) {
    strncpy(deviceName, data, sizeof(deviceName)-1);
}

void ParticleInterface::pubStateHandler(const char *topic, const char *data) {
    ParticleLog::pubRelayState(
            Config::relayNumber,
            RelayBoard::getPower(Config::relayNumber));
}

void ParticleInterface::triggerRelay(const char *topic, const char *data) {
#ifdef serialLogging
    Serial.println(data);
#endif
    this->handleCommand(data);
}

void ParticleInterface::initialize() {
    /* get device name */
    Particle.subscribe("particle/device/name", &ParticleInterface::nameHandler, this);
    Particle.publish("particle/device/name");

    for (uint32_t ms = millis(); millis() - ms < 3000 && !(std::strcmp(deviceName, "")); Particle.process());
    
    ParticleLog::initialize(String(deviceName));
#ifdef serialLogging
    Serial.println(deviceName);
#endif

    Particle.function("controlRelay", &ParticleInterface::handleCommand, this);
    Particle.subscribe(
            String::format("%s_relay_1", deviceName),
            &ParticleInterface::triggerRelay, this);
    Particle.subscribe("getstate", &ParticleInterface::pubStateHandler, this);

    ParticleLog::pubRelayState(
            Config::relayNumber,
            RelayBoard::getPower(Config::relayNumber));
}

void ParticleInterface::handle() {
    int status = RelayBoard::getAllPower();
    for (int i=0; i<6; i++) {
        if (status & (1<<i)) {
            trips[i]++;
            if (trips[i] >= minTrips && !tripped[i]) {
                tripped[i] = true;

                String eventName = "Input_";
                eventName += (i+1);
                Particle.publish(eventName, "ON");

#ifdef serialLogging
                Serial.print("eventName: ");
                Serial.println(eventName);
                Serial.print("eventContents: ");
                Serial.println("ON");
#endif
            }
        } else {
            trips[i] = 0;
            if (tripped[i]) {
                tripped[i] = false;

                String eventName = "Input_";
                eventName += (i+1);
                Particle.publish(eventName, "OFF");

#ifdef serialLogging
                Serial.print("eventName: ");
                Serial.println(eventName);
                Serial.print("eventContents: ");
                Serial.println("OFF");
#endif
            }
        }
    }
}
