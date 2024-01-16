CFLAGS=-c -Iinclude

all: lab-06_int-vector

lab-06_int-vector: obj/main.o obj/my_vector.o
	g++ obj/main.o obj/my_vector.o -o lab-06_int-vector
obj/main.o:	src/main.cpp include/my_vector.hpp | obj
	g++ $(CFLAGS) src/main.cpp -o obj/main.o
obj/my_vector.o: src/my_vector.cpp include/my_vector.hpp | obj
	g++ $(CFLAGS) src/my_vector.cpp -o obj/my_vector.o

.PHONY: clean
clean:
	rm -rf obj/*.o
obj:
	mkdir obj