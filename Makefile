obj-m := gpio-sysfs.o
HOST_KERN_DIR = /lib/modules/$(shell uname -r)/build/

host:
	make -C $(HOST_KERN_DIR) M=$(PWD) modules 
clean:
	make -C $(HOST_KERN_DIR) M=$(PWD) clean 
help:
	make -C $(HOST_KERN_DIR) M=$(PWD) help 
