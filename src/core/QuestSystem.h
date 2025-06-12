#pragma once
#include <vector>
#include <string>
#include <functional>

struct Quest {
    std::string title;
    std::string description;
    bool completed = false;
    std::function<bool()> checkCompletion;
};

class QuestSystem {
public:
    std::vector<Quest> activeQuests;
    void AddQuest(const std::string& title, const std::string& desc, std::function<bool()> checker);
    void Update();
};
