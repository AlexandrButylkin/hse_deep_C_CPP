CFLAGS=-c -Iinclude

all: hw-01_bmp

hw-01_bmp: obj/main.o obj/bmp.o obj/stego.o
	gcc obj/main.o obj/bmp.o obj/stego.o -o hw-01_bmp
obj/main.o:	src/main.c include/bmp.h include/stego.h | obj
	gcc $(CFLAGS) src/main.c -o obj/main.o
obj/bmp.o: src/bmp.c include/bmp.h | obj
	gcc $(CFLAGS) src/bmp.c -o obj/bmp.o
obj/stego.o: src/stego.c include/stego.h include/bmp.h | obj
	gcc $(CFLAGS) src/stego.c -o obj/stego.o

.PHONY: clean
clean:
	rm -rf obj/*.o
obj:
	mkdir obj
