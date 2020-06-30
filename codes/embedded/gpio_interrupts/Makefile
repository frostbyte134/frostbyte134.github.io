obj-m	:=	dwkang_gpio_driver.o
KDIR	:= /lib/modules/$(shell uname -r)/build
PWD		:=	$(shell pwd)	

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	
clean:
	rm -rf *.ko
	rm -rf *.mod.*
	rm -rf *.cmd
	rm -rf *.o
	rm -rf .tmp_versions
