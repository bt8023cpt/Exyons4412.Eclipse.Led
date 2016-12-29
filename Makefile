all:
	make -C ./application all
	make -C ./modules all
	
clean:
	make -C ./application clean
	make -C ./modules clean