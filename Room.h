/***********************************************************
 ** File:    Room.h
 ** Project: CMSC 202 - Project 5 - Dungeon Explorer
 ** Desc:    Defines the room structure.
 **          Room stores information loaded from the input file.
 ***********************************************************/
#ifndef ROOM_H
#define ROOM_H

#include <string>
using namespace std;

// Name - Room (Structure)
// Desc - Stores the description, item, treasure, and enemy
//        information for one dungeon room.
// Preconditions  - None
// Postconditions - Room fields are available to describe an encounter
struct Room {
	int m_id;              // ID of the room
	string m_name;         // Name of the room
	string m_description;  // Description displayed to the player
	string m_itemName;     // Item available in the room (if any)
	int m_itemHealing;     // Health restored by the room's item
	int m_gold;            // Gold available in the room
	string m_enemyName;    // Enemy present in the room (if any)
	int m_enemyDamage;     // Damage inflicted by the enemy

	// Name - Room (Default Constructor)
	// Desc - Initializes a new room with empty strings and zero values.
	// Preconditions  - None
	// Postconditions - All strings are empty and all integers are zero
	Room() : m_id(0), m_itemHealing(0), m_gold(0), m_enemyDamage(0) {}

	// Name - Room (Overloaded Constructor)
	// Desc - Initializes a Room using information from the input file.
	// Preconditions  - Room information is provided in the correct format
	// Postconditions - All member variables contain the provided values
	// Format: id|name|description|itemName|itemHealing|
	//            gold|enemyName|enemyDamage
	Room(int id, string name, string desc, string item,
		int heal, int gold, string enemy, int damage) :
		m_id(id), m_name(name), m_description(desc),
		m_itemName(item), m_itemHealing(heal), m_gold(gold),
		m_enemyName(enemy), m_enemyDamage(damage) {
	}
};

#endif