/***********************************************************
 ** File:    GameState.h
 ** Project: CMSC 202 - Project 5 - Dungeon Explorer
 ** Desc:    Defines the GameState structure used to record
 **          player progress and support undo operations.
 ***********************************************************/
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include "Item.h"
#include "LList.h"
using namespace std;

const int STARTING_HEALTH = 50;

// Name - GameState (Structure)
// Desc - Stores mutable dungeon information so an earlier state
//        can be copied onto the undo stack and restored later.
// Preconditions  - Item and LList must be defined
// Postconditions - Player progress is represented in one structure
struct GameState {
	int room;                 // Current room index
	int health;               // Player's current health
	int gold;                 // Player's collected gold
	vector<bool> taken;       // Whether original room loot was collected
	vector<bool> defeated;    // Whether each enemy was defeated
	vector<bool> dropWaiting; // Whether dropped loot remains on the ground
	vector<Item> drops;       // Enemy drop associated with each room
	LList<Item> inventory;    // Player inventory (templated linked list)
	// Name - GameState (Constructor)
	// Desc - Initializes the player and creates state entries for
	//        the number of rooms loaded into the dungeon.
	// Preconditions  - numRooms is zero or greater
	// Postconditions - Player starts in room 0 with STARTING_HEALTH,
	//                  no gold, and an empty inventory; all room flags
	//                  are false and drops contains default Items
	GameState(int numRooms = 0)
		: room(0), health(STARTING_HEALTH), gold(0),
		taken(numRooms, false), defeated(numRooms, false),
		dropWaiting(numRooms, false), drops(numRooms) {
	}
};

#endif