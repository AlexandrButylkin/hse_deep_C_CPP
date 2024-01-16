CFLAGS=-c -Iinclude

all: lab-02_cstrings

lab-02_cstrings: obj/str.o obj/test.o obj/test_str.o
	gcc obj/str.o obj/test.o obj/test_str.o -o lab-02_cstrings
obj/str.o: src/str.c include/str.h | obj
	gcc $(CFLAGS) src/str.c -o obj/str.o
obj/test.o: src/test.c include/test_str.h | obj
	gcc $(CFLAGS) src/test.c -o obj/test.o
obj/test_str.o: src/test_str.c include/str.h include/test_str.h | obj
	gcc $(CFLAGS) src/test_str.c -o obj/test_str.o

.PHONY: clean
clean:
	rm -rf obj/*.o
obj:
	mkdir obj
