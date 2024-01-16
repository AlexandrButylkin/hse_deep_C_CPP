CFLAGS=-c -Iinclude

all: lab-03_mergesort

lab-03_mergesort: obj/mergesort.o obj/main.o
	gcc  obj/mergesort.o obj/main.o -o lab-03_mergesort
obj/mergesort.o: src/mergesort.c include/mergesort.h | obj
	gcc $(CFLAGS) src/mergesort.c -o obj/mergesort.o
obj/main.o: src/main.c include/mergesort.h | obj
	gcc $(CFLAGS) src/main.c -o obj/main.o

.PHONY: clean
clean:
	rm -rf obj/*.o
obj:
	mkdir obj
