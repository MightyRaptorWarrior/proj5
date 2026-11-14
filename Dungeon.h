#ifndef DUNGEON_H
#define DUNGEON_H
#include "LList.h"
#include "Item.h"
#include "GameState.h"
#include "Room.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;

// CONSTANTS
const char DELIMITER = '|'; // Used to load rooms
const string VAULT_KEY = "Vault Key"; // Name of the key required to enter vault

class Dungeon {
public:
	// Name - Dungeon (Constructor)
	// Desc - Initializes a dungeon with default room and game state values.
	// Preconditions  - None
	// Postconditions - Dungeon object is ready to load room data.
	Dungeon();
	// Name - LoadRooms
	// Desc - Loads all rooms from the specified input file.
	// Preconditions  - filename identifies a standard room file.
	// Postconditions - Returns true after loading and resetting
	//        game state; false on failure.
	bool LoadRooms(const string& filename);
	// Name - Start
	  // Desc - Displays the game menu and processes player actions
  //        until quitting.
  // Preconditions  - Room data has been loaded successfully.
  // Postconditions - Game actions are processed until the player
  //        quits or input ends.
	void Start();
private:
	vector<Room> m_rooms; //Holds all of the rooms in the dungeon
	GameState m_state; // Stores the current state
	LList<GameState> m_history; // stack: most recent state first
	// Name - SaveUndo
	// Desc - Pushes a copy of the current game state onto the undo stack.
	// Preconditions  - Current game state is valid.
	// Postconditions - A snapshot is added to m_history; current
	//        state is unchanged.
	void SaveUndo();
	// Name - ShowStatus
// Desc - Displays player location, health, gold, inventory, and
//        undo count. Indicates if the inventory is empty.
// Preconditions  - None
// Postconditions - Status is printed; game state is unchanged.
	void ShowStatus() const;
	// Name - DescribeRoom
	// Desc - Displays the current room description and available
	//        encounters or items. Indicates if there is an enemy, item,
	//        gold, or enemy loot.
	// Preconditions  - Current room index is valid.
	// Postconditions - Room details are printed; game state is unchanged.
	void DescribeRoom() const;
	// Name - Move
	// Desc - Prompts the player to move forward or backward one room.
	//        Checks to make sure that direction is allowed. If an enemy
	  //        exists in room, can't move. If at vault, checks for key
  // Preconditions  - Room data has been loaded.
  // Postconditions - On a valid move, the prior state is saved and
  //        room index changes.
	void Move();
	// Name - TakeItem
	// Desc - Collects available room treasure or a defeated enemy's
	//        dropped item. Only allows to collect treasure if enemy has
	//        been defeated. Indicates if there is nothing left to collect.
	//        Tries to collect item then gold. If in final room, indicates
	//        victory.
	// Preconditions  - Room data has been loaded.
	// Postconditions - On success, the prior state is saved and
	//        inventory or gold changes.
	void TakeItem();
	// Name - UsePotion
	  // Desc - Consumes the first healing item in the player inventory.
  // Preconditions  - A usable healing item exists and player
  //        health is below maximum. Uses FindPotion to identify potion.
  // Postconditions - On success, prior state is saved, the item is
  //        removed, and health rises.
	void UsePotion();
	// Name - Fight
	// Desc - Resolves a battle with an undefeated enemy in the current room.
	//        Checks to see if the fight would defeat you BEFORE battle.
	//        Indicates if no enemy (or already defeated). 75% percent
	//        chance to drop an item (Calls RollLoot).
	// Preconditions  - An undefeated enemy exists and player has
	//        sufficient health.
	// Postconditions - On success, health decreases, enemy is
	//        defeated, and loot may appear.
	void Fight();
	// Name - Undo
// Desc - Restores the last saved game-state snapshot from the
//        history stack. Indicates if nothing to undo.
// Preconditions  - History contains a previous state.
// Postconditions - Most recent snapshot is removed and becomes
//        the current game state.
	void Undo();
	// Name - FindPotion
	// Desc - Searches inventory for the first item with positive healing.
	// Preconditions  - None
	// Postconditions - Returns its zero-based index or -1;
	//        inventory is unchanged.
	int FindPotion() const;
	// Name - HasKey
	// Desc - Searches inventory for an item named Vault Key.
	// Preconditions  - None
	  // Postconditions - Returns true if the key is present;
  //        inventory is unchanged.
	bool HasKey() const;
	// Name - RollLoot
	// Desc - Randomly selects an item from the enemy loot table.
	//        Can find one of four items Healing Potion (30 heal),
	//        Small Potion (15 heal), Silver Charm, or Ancient Coin
	// Preconditions  - Random number generator has been seeded
	//        by the calling program.
	// Postconditions - Returns a new Item value; dungeon state is unchanged.
	Item RollLoot() const;
};
#endif