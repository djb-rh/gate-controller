#ifndef autogate_config_h
#define autogate_config_h

/* configuration things. useful! */
inline bool debugLogging = true;
inline int minTrips = 5;

/* homekit config */
inline const char *switchManufacturer = "manufacturer";
inline const char *switchName = "test switch";

/* relay config */
/* if a relay is being used, it'll show up under the name as a homekit accessory */
/* TODO there's probably a better way to configure this. also not in use yet */
/* inline const int relaysUsing = 0b01;    /1* bitmask of relays;                           *1/ */
/*                                         /1* i.e. both relays = 0b11, relay 1 = 0b01, etc *1/ */
/* inline const char **relayNames = { */
/*     "relay-1", */
/*     "relay-2" */
/* }; */

inline const int relayNumber = 1;

/* particle config */

#endif
