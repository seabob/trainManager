PROJECT: trainManager

GITHUB REPOSITORY
	git clone https://github.com/seabob/trainManager.git

BUILD AND RUN
    CMAKE(Linux) version:3.5
        mkdir build
        cd build
        cmake ..
	make
	sudo make install
	trainManager ../testfile.txt

TEST
    MEMCHECK
	valgrind --tool=memcheck ./trainsManager ../testfile.txt

DESCRIBE
    BASIC DATA STRUCTURE:
	Rewrite kernel-list data structure.
	Rewrite vector/stack data structure based on kernel-list.
	Use recursion to processe input graph.
	Compiled by cmake, and memchecked by valgrind.
