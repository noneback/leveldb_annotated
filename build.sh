mkdir -p build && cd build && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_CXX_STANDARD=11 .. && make -j

# g++ -g main.cpp -o a.out ./build/libleveldb.a -lpthread -lsnappy -I ./include
