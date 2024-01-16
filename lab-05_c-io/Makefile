CFLAGS=-c -Iinclude

all: lab-05_c-io

lab-05_c-io: obj/main.o obj/clist.o obj/point.o
	gcc obj/main.o obj/clist.o obj/point.o -o lab-05_c-io
obj/main.o:	src/main.c include/clist.h include/point.h | obj
	gcc $(CFLAGS) src/main.c -o obj/main.o
obj/clist.o: src/clist.c include/clist.h | obj
	gcc $(CFLAGS) src/clist.c -o obj/clist.o
obj/point.o: src/point.c include/point.h include/clist.h | obj
	gcc $(CFLAGS) src/point.c -o obj/point.o

.PHONY: clean
clean:
	rm -rf obj/*.o
obj:
	mkdir obj
