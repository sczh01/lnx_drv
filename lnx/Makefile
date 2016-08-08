ifeq ($(KERNELRELEASE),)
KERNEL_DIR:=/usr/src/linux-headers-$(shell uname -r)
PWD:=$(shell pwd)
modules:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules
modules_install:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules_install
clean:
	rm -rf  .*.cmd *.ko  *.o modules.order  Module.symvers *mod.c
.PHONY: modules modules_install clean
else
    modules-objs := ker_ex.o
    obj-m := ker_ex.o
endif

