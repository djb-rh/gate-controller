# gate-controller

A Particle project named gate-controller

Based on NCD2Relay. Works on a 1 relay board, but steals GP1 for the second relay that doesn’t exist if you do that. You’d have to go back and hack these changes to NCD1Relay if you need all 7 GPIOs and not just 6 from the IO expander.

Publishes {controller name}_1 on/off when the relay state is changed.

Relay state can be changed by the cloud by any device publishing {controller name}_relay_1 with “on” or “off”.

Relay state can also be changed by the Particle app under Functions.

## Configuration and Building

This section is mainly relevant to config options and extra required setup for the Homekit updated version of the repo.

To configure the build process, fill out `config.mk` to have settings that make sense for your project -- the placeholder variables should be self-explanatory.
Then, to configure the actual deployed service (ex: setting the Homekit device name), there are a few more parameters to set in `src/config.h`.

To build the project and make sure that everything compiles properly, run `make all`.
When deploying to your device (specified in `config.mk`), use `make flash`.

There's a solid chance that you also want to disable extra logging done by the Homekit library -- to do this, edit the config file under `lib/Particle-HAP/src/HKConfig.h` (a git submodule) and comment out the `DEBUG_PARTICLE_EVENTS` flag.

Future proofing: there's a PR pending in the Homekit repo to get that flag merged into the actual library, and when it gets there the `lib/` folder will likely be cut in favor of using the upstream Particle library.
In that case, make sure to use `particle library copy Particle-HAP` to download the lib so that you can edit it, and then comment out the requirement in `project.properties`.
