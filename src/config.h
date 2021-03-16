#ifndef autogate_config_h
#define autogate_config_h

/* configuration things. useful! */
static bool debugLogging = true;
static int minTrips = 5;

/* homekit config */
static const char *switchManufacturer = "manufacturer";
static const char *switchName = "test switch";

/* relay config */
/* if a relay is being used, it'll show up under the name as a homekit accessory */
/* TODO there's probably a better way to configure this. also not in use yet */
/* static const int relaysUsing = 0b01;    /1* bitmask of relays;                           *1/ */
/*                                         /1* i.e. both relays = 0b11, relay 1 = 0b01, etc *1/ */
/* static const char **relayNames = { */
/*     "relay-1", */
/*     "relay-2" */
/* }; */

static const int relayNumber = 1;

/* particle config */

#endif
