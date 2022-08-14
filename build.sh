# mkdir build && cd build && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 .. && make

g++ -g main.cpp -o a.out ./build/libleveldb.a -lpthread -lsnappy -I ./include
