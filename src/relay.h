#ifndef autogate_relay_h
#define autogate_relay_h

#include "NCD2Relay.h"

namespace RelayBoard {
    void initialize(NCD2Relay *relayController);

    void setPower(int port, bool powered);
    bool getPower(int port);
    void togglePower(int port);

    void setAllPower(bool powered);
    int getAllPower(); // wraps readAllInputs
}

#endif
