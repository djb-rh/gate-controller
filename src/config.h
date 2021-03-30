#ifndef autogate_config_h
#define autogate_config_h

#define cloudLogging
#define serialLogging
#define minTrips 5

namespace Config {
    /* homekit config */
    static const char *switchManufacturer = "manufacturer";
    static const char *devName = "device name";
    static const unsigned long reportDelayMS = 5000;

    /* relay config */
    static const int nRelays = 2;           /* number of relays being used                      */
    static const char *relayNames[] = {     /* the name of each relay as it appears in homekit  */
        "relay-1",
        "relay-2"
    };

    /* particle config */
}

#endif
