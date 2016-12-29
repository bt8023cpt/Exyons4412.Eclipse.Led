obj-m := led.o

KDIR := /home/uesr/workspace/tiny4412/linux-3.5
PWD := $(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean
