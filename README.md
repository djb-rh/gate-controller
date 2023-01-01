# gate-controller

A Particle project named gate-controller

Based on NCD2Relay. Works on a 1 relay board, but steals GP1 for the second relay that doesn’t exist if you do that. You’d have to go back and hack these changes to NCD1Relay if you need all 7 GPIOs and not just 6 from the IO expander.

Publishes {controller name}_1 on/off when the relay state is changed.

Relay state can be changed by the cloud by any device publishing {controller name}_relay_1 with “1on” or “1off”.

Relay state can be gathered from all gates by publishing "getstate" to particle cloud.

Future commands can be skipped by publishing "skipcommand X" where X is 0-9. For example, if you publish "skipcommand 2" then every gate will skip the next two commands sent to it by particle cloud.

Relay state can also be changed by the Particle app under Functions. (Warning: this does not trigger the firmware to publish any status to particle cloud. It also does NOT count as a "command" as far as skips are concerned.)


## Compiling your project

When you're ready to compile your project, make sure you have the correct Particle device target selected and run `particle compile <platform>` in the CLI or click the Compile button in the Desktop IDE. The following files in your project folder will be sent to the compile service:

- Everything in the `/src` folder, including your `.ino` application file
- The `project.properties` file for your project
- Any libraries stored under `lib/<libraryname>/src`
