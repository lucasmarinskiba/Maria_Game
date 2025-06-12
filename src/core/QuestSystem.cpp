#include "QuestSystem.h"

void QuestSystem::AddQuest(const std::string& title, const std::string& desc, std::function<bool()> checker) {
    activeQuests.push_back({title, desc, false, checker});
}

void QuestSystem::Update() {
    for (auto& quest : activeQuests) {
        if (!quest.completed && quest.checkCompletion()) {
            quest.completed = true;
            // Aquí puedes mostrar un mensaje al jugador
        }
    }
}
