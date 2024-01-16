CXX = g++
CXXFLAGS = -O2 -Wall -std=c++14 -Iinclude

hw-02_huffman: obj/main.o obj/test.o obj/archiver.o obj/bitset.o obj/huffmanTree.o
	$(CXX) obj/main.o obj/test.o obj/archiver.o obj/bitset.o obj/huffmanTree.o -o hw-02_huffman

obj/main.o:	src/main.cpp include/Archiver.h include/test.h | obj
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o obj/main.o

obj/test.o: test/test.cpp include/test.h include/TestRunner.h include/Archiver.h | obj
	$(CXX) $(CXXFLAGS) -c test/test.cpp -o obj/test.o

obj/archiver.o: src/Archiver.cpp include/Archiver.h include/Bitset.h include/HuffmanTree.h | obj
	$(CXX) $(CXXFLAGS) -c src/Archiver.cpp -o obj/archiver.o

obj/huffmanTree.o: src/HuffmanTree.cpp include/HuffmanTree.h | obj
	$(CXX) $(CXXFLAGS) -c src/HuffmanTree.cpp -o obj/huffmanTree.o

obj/bitset.o: src/Bitset.cpp include/Bitset.h | obj
	$(CXX) $(CXXFLAGS) -c src/Bitset.cpp -o obj/bitset.o

.PHONY: clean
clean:
	rm -rf obj/*.o
obj:
	mkdir obj

