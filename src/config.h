#ifndef autogate_config_h
#define autogate_config_h

/* configuration things. useful! */
static bool debugLogging = true;
static int minTrips = 5;

/* homekit config */
/* static const char *switchManufacturer = "manufacturer"; */
/* static const char *switchName = "test switch"; */

/* relay config */
/* if a relay is being used, it'll show up under the name as a homekit accessory */
/* TODO there's probably a better way to configure this. also not in use yet */
static const int nRelays = 1;           /* number of relays being used                  */
static const int relaysUsing = 0b01;    /* bitmask of relays to activate:               */
                                        /* i.e. both relays = 0b11, relay 1 = 0b01, etc */
/* static const char *relayNames[] = {     /1* the name of each relay for homekit           *1/ */
/*     "relay-1", */
/*     "relay-2"                           /1* note that we're only using one relay so this *1/ */
/*                                         /1* ends up being ignored                        *1/ */
/* }; */

static const int relayNumber = 1;

/* particle config */

#endif
