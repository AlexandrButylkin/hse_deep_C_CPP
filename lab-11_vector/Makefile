lab-11_vector: obj/main.o
	g++ obj/main.o -o lab-11_vector
obj/main.o:	src/main.cpp include/my_vector.h | obj
	gcc -O2 -Wall -Werror -std=c++11 -Iinclude -c src/main.cpp -o obj/main.o

.PHONY: clean
clean:
	rm -rf obj/*.o
obj:
	mkdir obj
