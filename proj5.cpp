#include "Dungeon.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: ./proj5 rooms.txt\n";
        return 1;
    }
    srand(time(nullptr));
    Dungeon dungeon;
    if (!dungeon.LoadRooms(argv[1])) {
        cerr << "Could not load valid rooms from " << argv[1] << ".\n";
        return 1;
    }
    dungeon.Start();
    return 0;
}