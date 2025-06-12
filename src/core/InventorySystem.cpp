#include "InventorySystem.h"
#include <iostream>

void InventorySystem::AddItem(const std::string& name, const std::string& description) {
    for (auto& item : items) {
        if (item.name == name) {
            item.quantity++;
            return;
        }
    }
    items.push_back({name, description, 1});
}

void InventorySystem::UseItem(int index) {
    if (index >= 0 && index < items.size() && items[index].quantity > 0) {
        std::cout << "Usaste: " << items[index].name << std::endl;
        items[index].quantity--;
        if (items[index].quantity == 0) items.erase(items.begin() + index);
    }
}
