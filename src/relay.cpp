#include "relay.h"

#include "config.h"
#include "logging.h"

#include "NCD2Relay.h"

namespace RelayBoard {
    namespace {
        NCD2Relay *board;
    }

    void initialize(NCD2Relay *relayController) {
        board = relayController;
    }

    bool getPower(int port) {
        return board->readRelayStatus(port);
    }
    
    void setPower(int port, bool powered) {
        if (getPower(port) == powered) {
            return;
        }

        if (powered) {
            board->turnOnRelay(port);
        } else {
            board->turnOffRelay(port);
        }

        ParticleLog::pubRelayState(port, powered);
    }

    void togglePower(int port) {
        setPower(port, !getPower(port));
    }

    void setAllPower(bool powered) {
        for (int i=0; i<Config::nRelays; i++) {
            setPower(i, powered);
        }
    }

    int getAllPower() {
        return board->readAllInputs();
    }
};
