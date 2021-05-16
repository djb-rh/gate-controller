include config.mk

all: compile clean

install: flash

flash:
	particle flash $(DEVICEID)

compile:
	particle compile $(DEVICETYPE) --saveTo $(DEVICETYPE)-out.bin

clean:
	rm -f *-out.bin
