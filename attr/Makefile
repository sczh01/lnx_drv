ifeq ($(KERNELRELEASE),)
#KERNEL_DIR:=/lib/modules/$(shell uname -r)/build/
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
    modules-objs := my_attr.o
    obj-m := my_attr.o
endif

