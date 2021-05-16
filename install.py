#!/usr/bin/python
"""
Script to automatically install and configure this firmware on a provided Particle
Photon device.

Usage:
    Update all configuration files to use default params and be called <devname>
    in HK, but don't install
        python install.py --name <devname>
    
    Update all configuration files to use default params and be called <devname>
    in HK, and install to device <devid>
        python install.py --name <devname> --devid <devid>

    Explicitly set the relay name <r1name> of a single relay setup, don't install
        python install.py --name <devname> --relay-1-name <r1name>

    Configure all files for a 2 relay setup <r1name>, <r2name>, install
        python install.py --name <devname> --relay-1-name <r1name> \
                --relay-2-name <r2name> --devid <devid>

Slightly more details about parameters can be found in python install.py --help
"""

from os import system
from string import Template

OUTPUT_FILE = "./src/config.h"
PARTICLE_CONFIG_FILE = "./lib/particle-hap/src/HKConfig.h"
TEMPLATE_FILE = "./config-tmpl.h"

def update_config_templates(config: dict) -> None:
    """
    Generate a new src/config.h derived from config-tmpl.h with templated values
    filled out. Expects dictionary with {template-field: value} format
    """
    with open(TEMPLATE_FILE, 'r') as f:
        template_data = f.read()
    template = Template(template_data)
    output = template.safe_substitute(config)
    with open(OUTPUT_FILE, 'w') as f:
        f.write(output)

def set_homekit_logging(enable: bool) -> None:
    # see if debugging is enabled already
    with open(PARTICLE_CONFIG_FILE, 'r') as f:
        particle_config_lines = [l.strip() for l in f.readlines()]
    enabling_lines = []
    for ln, line in enumerate(particle_config_lines):
        if "#define DEBUG_PARTICLE_EVENTS" in line:
            enabling_lines.append(ln)

    if enable:
        if len(enabling_lines) >= 1:
            return
        # add a line before #endif that enables logging
        for ln in range(len(particle_config_lines)):
            if "#endif" in particle_config_lines[-(ln+1)]:
                particle_config_lines.insert(-(ln+1), "#define DEBUG_PARTICLE_EVENTS")
    else:
        if len(enabling_lines) == 0:
            return
        # remove all lines enabling the flag
        particle_config_lines = [line for line_num, line in enumerate(particle_config_lines)
                if line_num not in enabling_lines]

    # write new config
    with open(PARTICLE_CONFIG_FILE, 'w') as f:
        f.write("\n".join(particle_config_lines))
        
def flash(particle_id: str) -> None:
    system(f"particle flash {particle_id}")

if __name__ == "__main__":
    from argparse import ArgumentParser

    parser = ArgumentParser()
    parser.add_argument("--devid", help="Particle device ID (will flash w/ this!)",
            required=False, default=None, dest="particle_id")
    parser.add_argument("--name", help="Device name as it shows up in Home UI",
            required=True, dest="hk_name")
    parser.add_argument("--relay-1-name", help="Name of 1st relay in Home UI",
            required=False, default="relay", dest="hk_relay_1_name")
    parser.add_argument("--relay-2-name", help="Name of 2nd relay in Home UI",
            required=False, default=None, dest="hk_relay_2_name")
    parser.add_argument("--enable-hk-logging", help="Enable Homekit lib logging",
            required=False, default=False, action="store_true", dest="hk_logging")
    parser.parse_args()

    args = parser.parse_args()

    update_config_templates({
        "hk_name":      args.hk_name,
        "n_relays":     "1" if args.hk_relay_2_name == None else "2",
        "relay_names":  ",\n".join(
            [f'"{name}"' for name in [args.hk_relay_1_name, args.hk_relay_2_name] if name != None])
        })
    
    set_homekit_logging(args.hk_logging)

    if args.particle_id != None:
        flash(args.particle_id)
