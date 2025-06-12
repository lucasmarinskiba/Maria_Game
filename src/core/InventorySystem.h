#pragma once
#include <vector>
#include <string>

struct Item {
    std::string name;
    std::string description;
    int quantity = 1;
};

class InventorySystem {
public:
    std::vector<Item> items;

    void AddItem(const std::string& name, const std::string& description);
    void UseItem(int index);
};
