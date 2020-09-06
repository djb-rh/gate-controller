/*
 * Project gate-controller
 * Description: control the gate!
 * Author: Donnie Barnes <djb@donniebarnes.com>
 * Date: May 6, 2020
 */

// This #include statement was automatically added by the Particle IDE.
#include <NCD2Relay.h>

NCD2Relay relayController;

SYSTEM_MODE(AUTOMATIC);

int triggerRelay(String command);

bool tripped[6];

int debugTrips[6];

int minTrips = 5;

String eventName;

char dev_name[32] = "";
char pubString[40] = "";
char restarted_msg[11] = "_restarted";
bool publishName = false;

void handler(const char *topic, const char *data){
    strncpy(dev_name, data, sizeof(dev_name)-1);
    publishName = true;
}

void pubState(const char *topic, const char *data){
	char pub[40] = "";
	strcat(pub, pubString);
	strcat(pub, "_1");
	if (relayController.readRelayStatus(1)) Particle.publish(pub, "ON", PRIVATE);
	else Particle.publish(pub, "OFF", PRIVATE);
}

/* This function is called once at start up ----------------------------------*/
void setup()
{
	Particle.function("controlRelay", triggerRelay);
	Particle.subscribe("particle/device/name", handler);
    Particle.publish("particle/device/name");
    // allow for up to 3 sec and maximum time to attend to cloud tasks
    for (uint32_t ms = millis(); millis() - ms < 3000 && !publishName; Particle.process());
	Serial.begin(115200);
	relayController.setAddress(0,0,0);
	Serial.println(dev_name);
	strcat(pubString, dev_name);
	strcat(dev_name, "_relay_1");
	Particle.subscribe(dev_name, triggerRelayDos, MY_DEVICES);

	// listen for monitors to ask for state and if they do, report it (this report is the same
	// as what gets reported when the gate state is changed)
	Particle.subscribe("getstate", pubState, MY_DEVICES);
	// publish state on boot up, too
	pubState(NULL, NULL);
	
	// register calendar functions
	Particle.function("getOpen", getOpen);
	Particle.function("getAlive", vitalCheck);
	Particle.function("open", openGate);
	Particle.function("close", closeGate);
}

/* This function loops forever --------------------------------------------*/
void loop()
{
	int status = relayController.readAllInputs();
	int a = 0;
	for(int i = 1; i < 33; i*=2){
		if(status & i){
			debugTrips[a]++;
			if(debugTrips[a] >= minTrips){
				if(!tripped[a]){
					tripped[a] = true;
					//set input trip event to true
					eventName = "Input_";
					eventName+=(a+1);
					Particle.publish(eventName, "ON");
					Serial.print("eventName: ");
					Serial.println(eventName);
					Serial.print("eventContents: ");
					Serial.println("ON");
				}
			}
		}else{
			debugTrips[a] = 0;
			if(tripped[a]){
				tripped[a] = false;
				//set input trip event to false
				eventName = "Input_";
				eventName+=(a+1);
				Particle.publish(eventName, "OFF");
				Serial.print("eventName: ");
				Serial.println(eventName);
				Serial.print("eventContents: ");
				Serial.println("OFF");
			}
		}
		a++;
	}
}

int triggerRelayDos(const char *event, const char *data){
    Serial.println(data);
    triggerRelay(data);
}

int triggerRelay(String command){
	if(command.equalsIgnoreCase("turnonallrelays")){
		relayController.turnOnAllRelays();
		return 1;
	}
	if(command.equalsIgnoreCase("turnoffallrelays")){
		relayController.turnOffAllRelays();
		return 1;
	}
	if(command.startsWith("setBankStatus:")){
		int status = command.substring(14).toInt();
		if(status < 0 || status > 255){
			return 0;
		}
		Serial.print("Setting bank status to: ");
		Serial.println(status);
		relayController.setBankStatus(status);
		Serial.println("done");
		return 1;
	}
	//Relay Specific Command
	eventName = pubString;
	eventName+="_";
	int relayNumber = command.substring(0,1).toInt();
	Serial.print("relayNumber: ");
	Serial.println(relayNumber);
	String relayCommand = command.substring(1);
	Serial.print("relayCommand:");
	Serial.print(relayCommand);
	Serial.println(".");
	if(relayCommand.equalsIgnoreCase("on")){
		Serial.println("Turning on relay");
		relayController.turnOnRelay(relayNumber);
		eventName+=(relayNumber);
		Particle.publish(eventName, "ON", PRIVATE);
		Serial.println("returning");
		return 1;
	}
	if(relayCommand.equalsIgnoreCase("off")){
		relayController.turnOffRelay(relayNumber);
		eventName+=(relayNumber);
		Particle.publish(eventName, "OFF", PRIVATE);

		return 1;
	}
	if(relayCommand.equalsIgnoreCase("toggle")){
		relayController.toggleRelay(relayNumber);
		return 1;
	}
	if(relayCommand.equalsIgnoreCase("momentary")){
		relayController.turnOnRelay(relayNumber);
		delay(300);
		relayController.turnOffRelay(relayNumber);
		return 1;
	}
	return 0;
}

int vitalCheck(String extra) {
	// basically a ping the calendar server uses
	return 1;
}

int getOpen(String extra) {
	// check current state, return status for calendar controller
	// 1 if open, 2 otherwise
	// TODO ensure that a high relay means an open gate
	return (relayController.readRelayStatus(1)) ? 1 : 2;
}

int openGate(String extra) {
	return triggerRelay("1on");
}

int closeGate(String extra) {
	return triggerRelay("1off");
}
