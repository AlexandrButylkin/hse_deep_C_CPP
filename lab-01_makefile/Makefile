lab-01_makefile: obj/main.o obj/io.o obj/util.o obj/algorithm.o
	gcc obj/main.o obj/io.o obj/util.o obj/algorithm.o -o lab-01_makefile
obj/main.o:	src/main.c include/algorithm.h include/io.h include/util.h | obj
	gcc -c -Iinclude src/main.c -o obj/main.o
obj/io.o: src/io.c include/io.h | obj
	gcc -c -Iinclude src/io.c -o obj/io.o
obj/util.o: src/util.c include/util.h | obj
	gcc -c -Iinclude src/util.c -o obj/util.o
obj/algorithm.o: src/algorithm.c include/io.h include/util.h include/algorithm.h | obj
	gcc -c -Iinclude src/algorithm.c -o obj/algorithm.o

.PHONY: clean
clean:
	rm -rf obj/*.o
obj:
	mkdir obj
