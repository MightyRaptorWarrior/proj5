#include "Dungeon.h"

Dungeon::Dungeon() {}

void Dungeon::ShowStatus() const {
    cout << "\nRoom " << m_state.room << " / " << m_rooms.size() - 1
        << "  Health: " << m_state.health << "  Gold: " << m_state.gold
        << "  Undos available: " << m_history.Size() << '\n';
    cout << "Inventory (" << m_state.inventory.Size() << "):\n";
    if (m_state.inventory.IsEmpty())
        cout << "  (empty)\n";
    else
        m_state.inventory.Display();
}

void Dungeon::DescribeRoom() const {
    int r = m_state.room;
    const Room& room = m_rooms[r];
    cout << "\n[" << r << ": " << room.m_name << "]\n"
        << room.m_description << '\n';
    if (!room.m_enemyName.empty() && !m_state.defeated[r])
        cout << "An enemy blocks the room: " << room.m_enemyName << ".\n";
    if (!m_state.taken[r] && !room.m_itemName.empty())
        cout << "On the ground: " << room.m_itemName << ".\n";
    if (!m_state.taken[r] && room.m_gold > 0)
        cout << "You see " << room.m_gold << " gold.\n";
    if (m_state.dropWaiting[r])
        cout << "Enemy loot: " << m_state.drops[r] << ".\n";
}

Item Dungeon::RollLoot() const {
    const Item loot[4] = { Item("Healing Potion", 30),
  Item("Small Potion", 15), Item("Silver Charm"),
  Item("Ancient Coin") };
    return loot[rand() % 4];
}

void Dungeon::Start() {
    cout << "=== UMBC Dungeon Explorer ===\n";
    DescribeRoom();
    int choice = 0;
    while (choice != 8) {
        cout << "\n1. Status / Inventory\n2. Inspect Room\n3. Move\n"
            << "4. Take Item / Treasure\n5. Use Potion\n6. Fight\n"
            << "7. Undo Last Action\n8. Quit\nChoice: ";
        if (!(cin >> choice)) {
            return;
        }
        while (choice < 1 || choice > 8) {
            cout << "Enter a number from 1 through 8: ";
            if (!(cin >> choice)) {
                return;
            }
        }
        switch (choice) {
        case 1:
            ShowStatus();
            break;
        case 2:
            DescribeRoom();
            break;
        case 3:
            Move();
            break;
        case 4:
            TakeItem();
            break;
        case 5:
            UsePotion();
            break;
        case 6:
            Fight();
            break;
        case 7:
            Undo();
            break;
        case 8:
            cout << "Thanks for playing!\n";
            break;
        default:
            cout << "Choose a number from 1 through 8." << endl;
        }
    }
}

