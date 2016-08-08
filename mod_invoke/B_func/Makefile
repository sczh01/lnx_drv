obj-m := B_func.o

KBUILD_EXTRA_SYMBOLS += /sdd1/opt/drv/mod_invoke/A_func/Module.symvers
export KBUILD_EXTRA_SYMBOLS

KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	rm -f *.o *.ko *.mod.c *.order *.symvers
