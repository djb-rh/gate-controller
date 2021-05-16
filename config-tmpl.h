#ifndef autogate_config_h
#define autogate_config_h

#define cloudLogging
#define serialLogging
#define minTrips 5

namespace Config {
    /* homekit config */
    static const char *switchManufacturer = "djb-rh/gate-controller";
    static const char *devName = "$hk_name";
    static const unsigned long reportDelayMS = 5000;

    /* relay config */
    static const int nRelays = $n_relays;   /* number of relays being used                      */
    static const char *relayNames[] = {     /* the name of each relay as it appears in homekit  */
        $relay_names
    };

    /* particle config */
}

#endif
