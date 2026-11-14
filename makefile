CXX = g++
CXXFLAGS = -Wall

proj5: proj5.o Dungeon.o Item.o
    $(CXX) $(CXXFLAGS) proj5.o Dungeon.o Item.o -o proj5

proj5.o: proj5.cpp Dungeon.h GameState.h Room.h Item.h LList.h
    $(CXX) $(CXXFLAGS) -c proj5.cpp

Dungeon.o: Dungeon.cpp Dungeon.h GameState.h Room.h Item.h LList.h
    $(CXX) $(CXXFLAGS) -c Dungeon.cpp

Item.o: Item.h Item.cpp
    $(CXX) $(CXXFLAGS) -c Item.cpp

ltest: LList_test.cpp LList.h
    $(CXX) $(CXXFLAGS) LList_test.cpp -o ltest

run:
    ./proj5 proj5_rooms.txt

test:
    ./ltest

val:
    valgrind ./proj5 proj5_rooms.txt

clean:
    rm -f proj5
    rm -f *~
    rm -f *.o
    rm -f vgcore*
    rm -f *.gch

submit:
    cp Dungeon.h Dungeon.cpp Item.h Item.cpp LList.h GameState.h Room.h proj5.cpp ~/cs202proj/proj5