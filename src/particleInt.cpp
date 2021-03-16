#include "config.h"
#include "particleInt.h"

#include <Particle.h>

int ParticleInterface::handleCommand(String command) {
    if (command.equalsIgnoreCase("turnonallrelays")) {
        relayController->turnOnAllRelays();
        return 1;
    }
    if (command.equalsIgnoreCase("turnoffallrelays")) {
        relayController->turnOffAllRelays();
        return 1;
    }
    if (command.startsWith("setBankStatus:")) {
        int status = command.substring(14).toInt();
        if (status < 0 || status > 255) {
            return 0;
        }
        if (debugLogging) {
            Serial.print("Setting bank status to: ");
            Serial.println(status);
        }
        relayController->setBankStatus(status);
        return 1;
    }
    
    /* relay specific commands */
    int relayNumber = command.substring(0, 1).toInt();
    String relayCommand = command.substring(1);

    String event = pubString;
    event += "_";
    event += (relayNumber);
    
    if (debugLogging) {
        Serial.print("relayNumber: ");
        Serial.println(relayNumber);
        Serial.print("relayCommand: ");
        Serial.println(relayCommand);
    }
    
    if (relayCommand.equalsIgnoreCase("on")) {
        if (debugLogging) {
            Serial.println("Turning on relay");
        }
        relayController->turnOnRelay(relayNumber);
        Particle.publish(event, "ON", PRIVATE);
        return 1;
    }
    if (relayCommand.equalsIgnoreCase("off")) {
        if (debugLogging) {
            Serial.println("Turning off relay");
        }
        relayController->turnOffRelay(relayNumber);
        Particle.publish(event, "OFF", PRIVATE);
        return 1;
    }
    if (relayCommand.equalsIgnoreCase("toggle")) {
        if (debugLogging) {
            Serial.println("Toggling relay");
        }
        relayController->toggleRelay(relayNumber);
        return 1;
    }
    if (relayCommand.equalsIgnoreCase("momentary")) {
        if (debugLogging) {
            Serial.println("Momentarily toggling relay");
        }
        relayController->turnOnRelay(relayNumber);
        delay(300);
        relayController->turnOffRelay(relayNumber);
        return 1;
    }
    return 0;
}

void ParticleInterface::nameHandler(const char *topic, const char *data) {
    strncpy(deviceName, data, sizeof(deviceName)-1);
}

void ParticleInterface::pubState() {
    char pub[40] = "";
    strcat(pub, pubString);
    strcat(pub, "_1");
    Particle.publish(pub, relayController->readRelayStatus(1) ? "ON" : "OFF", PRIVATE);
}

void ParticleInterface::pubStateHandler(const char *topic, const char *data) {
    this->pubState();
}

void ParticleInterface::triggerRelay(const char *topic, const char *data) {
    Serial.println(data);
    this->handleCommand(data);
}

void ParticleInterface::initialize() {
    /* get device name */
    Particle.subscribe("particle/device/name", &ParticleInterface::nameHandler, this);
    Particle.publish("particle/device/name");

    for (uint32_t ms = millis(); millis() - ms < 3000 && !(std::strcmp(deviceName, "")); Particle.process());
    
    Serial.println(deviceName);

    strcat(pubString, deviceName);
    strcat(deviceName, "_relay_1");

    Particle.function("controlRelay", &ParticleInterface::handleCommand, this);
    Particle.subscribe(deviceName, &ParticleInterface::triggerRelay, this);
    Particle.subscribe("getstate", &ParticleInterface::pubStateHandler, this);

    this->pubState();
}

void ParticleInterface::handle() {
    int status = relayController->readAllInputs();
    for (int i=0; i<6; i++) {
        if (status & (1<<i)) {
            trips[i]++;
            if (trips[i] >= minTrips && !tripped[i]) {
                tripped[i] = true;

                String eventName = "Input_";
                eventName += (i+1);
                Particle.publish(eventName, "ON");

                if (debugLogging) {
                    Serial.print("eventName: ");
                    Serial.println(eventName);
                    Serial.print("eventContents: ");
                    Serial.println("ON");
                }
            }
        } else {
            trips[i] = 0;
            if (tripped[i]) {
                tripped[i] = false;

                String eventName = "Input_";
                eventName += (i+1);
                Particle.publish(eventName, "OFF");

                if (debugLogging) {
                    Serial.print("eventName: ");
                    Serial.println(eventName);
                    Serial.print("eventContents: ");
                    Serial.println("OFF");
                }
            }
        }
    }
}
