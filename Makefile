include config.mk

all: compile clean

flash:
	particle flash $(DEVICEID)

compile:
	particle compile $(DEVICETYPE) --saveTo $(DEVICETYPE)-out.bin

clean:
	rm -f *-out.bin
