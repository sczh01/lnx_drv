obj-m := hello-yf.o
hello-yf-objs := hello.o

KID :=/sda1/main/mediatek
PWD := $(shell pwd)
ARCH=arm
SUBARCH=arm
CROSS_COMPILE=arm-linux-androideabi- 
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld

all:
	make -C $(KID) ARCH=$(ARCH) SUBARCH=$(SUBARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=${PWD} modules

clean:
	rm -rf *.o .cmd *.ko *.mod.c .tmp_versions
