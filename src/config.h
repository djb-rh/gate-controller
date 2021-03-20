#ifndef autogate_config_h
#define autogate_config_h

#define cloudLogging
#define serialLogging
#define minTrips 5

namespace Config {
    /* homekit config */
    static const char *switchManufacturer = "manufacturer";
    static const char *switchName = "test switch";
    static const char *devName = "dev-name";

    /* relay config */
    /* if a relay is being used, it'll show up under the name as a homekit accessory */
    /* TODO there's probably a better way to configure this. also not in use yet */
    static const int nRelays = 1;           /* number of relays being used                  */
    /* static const int relaysUsing = 0b01;    /1* bitmask of relays to activate:               *1/ */
                                            /* i.e. both relays = 0b11, relay 1 = 0b01, etc */
    static const char *relayNames[] = {     /* the name of each relay for homekit           */
        "relay-1",
        "relay-2"                           /* note that we're only using one relay so this */
                                            /* ends up being ignored                        */
    };

    static const int relayNumber = 1;

    /* particle config */
}

#endif
