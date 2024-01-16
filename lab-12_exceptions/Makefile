lab-12_exceptions: obj/main.o obj/matrix.o
	g++ obj/main.o obj/matrix.o -o lab-12_exceptions
obj/main.o:	src/main.cpp include/matrix.h | obj
	g++ -O2 -Wall -Werror -std=c++11 -Iinclude -c src/main.cpp -o obj/main.o
obj/matrix.o:	src/matrix.cpp include/matrix.h | obj
	g++ -O2 -Wall -Werror -std=c++11 -Iinclude -c src/matrix.cpp -o obj/matrix.o

.PHONY: clean
clean:
	rm -rf obj/*.o
obj:
	mkdir obj
