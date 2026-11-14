#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <string>
using namespace std;

class Item {
public:
	// Name - Item (Constructor)
	// Desc - Initializes an item with a name and a healing amount.
	// Preconditions  - None
	// Postconditions - m_name and m_healing contain the supplied values.
	Item(string name = "", int healing = 0);
	// Name - GetName
	// Desc - Returns the name of the item.
	// Preconditions  - None
	// Postconditions - Returns m_name; item is unchanged.
	string GetName() const;
	// Name - GetHealing
	// Desc - Returns the amount of health restored by the item.
	// Preconditions  - None
	// Postconditions - Returns m_healing; item is unchanged.
	int GetHealing() const;
	// Name - operator<<
	// Desc - Outputs the item name
	// Preconditions  - Used with cout
	// Postconditions - Name is output
	friend ostream& operator<<(ostream& out, const Item& item);
private:
	string m_name;
	int m_healing;
};


#endif