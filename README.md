# gate-controller

Particle Photon firmware to control an NCD2Relay compatible relay board through Homekit.

Makes use of:

* [NCD2Relay](https://github.com/ControlEverythingCom/NCD2Relay)
* [Particle-HAP](https://github.com/ljezny/Particle-HAP)

When deployed, this will make your Particle Photon into a Homekit device with a Composite Accessory that can switch the relay board on and off.

## Usage

### via Particle Events

The device can be controlled through Particle Events formatted like below:

```
Change device {name}'s {relay #} relay to be state {state}
    {name}_relay {relay #}{state}

Example:
    test_relay 1ON      turn on device test's 1st relay
    
    test_relay 2OFF     turn off device test's 2nd relay
```

Its state can be found by publishing `getstate` and listening for a response (as an event).

### via Homekit

Using Homekit, you can simply change the state of any registered relays by treating them as switches under a composite accessory. Check `src/config.h` to get their names.

To add your accessory, you can use a code (default: `523-12-643`) that is under src/gate-controller.ino.

## Configuration and Building

Any method here requires installation of [particle-cli](https://github.com/particle-iot/particle-cli) to work.

### Using install script

A more detailed explanation can be found under `install.py` or by running it with the `--help` flag.

```
Configure and install to particle device <particle-id> to be called <homekit-name> and have a single relay called <relay-1>
    python install.py --name homekit-name --relay-1-name relay-1 --devid particle-id

The same configuration as above, but with a 2nd relay called relay-2
    python install.py --name homekit-name --relay-1-name relay-1 --relay-2-name relay-2 --devid particle-id

Configure all source files in the same way as above, but don't install (no --devid)
    python install.py --name homekit-name --relay-1-name relay-1 --relay-2-name relay-2
```

### Manually

1. Edit `src/config.h` to fit your needs. Change `devName` to be something unique for the HK UI, change `nRelays` to be the number of relays controlled, and populate `relayNames[]` with the names of each relay being controlled
2. Edit `lib/particle-hap/src/HKConfig.h` to remove `#define DEBUG_PARTICLE_EVENTS` to reduce the number of events being published by the homekit service (which are purely for debugging)
3. Edit `config.mk` to set `DEVICEID` to the name of your Photon as recognized by the Particle CLI tool
4. Run `make install` to cloud compile and flash the source to your board

