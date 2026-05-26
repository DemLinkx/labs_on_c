#include <iostream>
#include <vector>
#include "cirlList.hpp"

using List = CircularList<int>;

void clear_input() {
    std::cin.ignore(256, '\n');
}

int main() {
    std::vector<List*> lists;
    int active_idx = -1;
    int choice, val;

    while (true) {
        std::cout << "\n=== MAIN MENU ===\n"
                  << "0. Create new list\n"
                  << "1. Select active list\n"
                  << "2. Delete current list\n"
                  << "3. List all\n"
                  << "--- Operations on active list ---\n"
                  << "4. Insert after current\n"
                  << "5. Insert before current\n"
                  << "6. Remove current\n"
                  << "7. Move next\n"
                  << "8. Move prev\n"
                  << "9. Print current\n"
                  << "10. Size / Is Empty\n"
                  << "11. Copy current -> new list\n"
                  << "12. Exit\n"
                  << "Choice: ";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input.\n";
            clear_input();
            continue;
        }
        clear_input();

        auto check_active = [&]() -> bool {
            if (active_idx < 0 || active_idx >= lists.size() || !lists[active_idx]) {
                std::cout << "Error: No active list selected.\n";
                return false;
            }
            return true;
        };

        switch (choice) {
            case 0: {
                lists.push_back(new List());
                active_idx = lists.size() - 1;
                std::cout << "Created list #" << active_idx << ". It is now active.\n";
                break;
            }
            case 1: {
                std::cout << "--- Available lists ---\n";
                if (lists.empty()) {
                    std::cout << "No lists created.\n";
                } else {
                    for (size_t i = 0; i < lists.size(); ++i) {
                        std::cout << (i == active_idx ? "> " : "  ") 
                                  << "[" << i << "] Size: " << lists[i]->size() << "\n";
                    }
                }
                std::cout << "Select index (0-" << lists.size() - 1 << "): ";
                int idx;
                if (std::cin >> idx && idx >= 0 && idx < lists.size()) {
                    active_idx = idx;
                    std::cout << "Activated list #" << active_idx << ".\n";
                } else {
                    std::cout << "Invalid index.\n";
                    clear_input();
                }
                break;
            }
            case 2: {
                if (!check_active()) break;
                std::cout << "Delete list #" << active_idx << "? (y/n): ";
                char c; std::cin >> c; clear_input();
                if (c == 'y' || c == 'Y') {
                    delete lists[active_idx];
                    lists.erase(lists.begin() + active_idx);
                    if (lists.empty()) active_idx = -1;
                    else if (active_idx >= lists.size()) active_idx = lists.size() - 1;
                    std::cout << "Deleted. Active is now #" << active_idx << ".\n";
                }
                break;
            }
            case 3: {
                std::cout << "--- All Lists ---\n";
                for (size_t i = 0; i < lists.size(); ++i) {
                    std::cout << "List #" << i << (i == active_idx ? " [ACTIVE]" : "") 
                              << " | Size: " << lists[i]->size() << "\n";
                }
                break;
            }
            case 4: {
                if (!check_active()) break;
                std::cout << "Value to insert after: ";
                if (std::cin >> val) { lists[active_idx]->insert_after(val); std::cout << "OK\n"; }
                else clear_input();
                break;
            }
            case 5: {
                if (!check_active()) break;
                std::cout << "Value to insert before: ";
                if (std::cin >> val) { lists[active_idx]->insert_before(val); std::cout << "OK\n"; }
                else clear_input();
                break;
            }
            case 6: {
                if (!check_active()) break;
                lists[active_idx]->remove_current();
                break;
            }
            case 7: {
                if (!check_active()) break;
                lists[active_idx]->move_next();
                std::cout << "Moved next.\n";
                break;
            }
            case 8: {
                if (!check_active()) break;
                lists[active_idx]->move_prev();
                std::cout << "Moved prev.\n";
                break;
            }
            case 9: {
                if (!check_active()) break;
                std::cout << "Content of list #" << active_idx << ":\n";
                lists[active_idx]->print();
                break;
            }
            case 10: {
                if (!check_active()) break;
                std::cout << "Size: " << lists[active_idx]->size() 
                          << " | Empty: " << (lists[active_idx]->empty() ? "Yes" : "No") << "\n";
                break;
            }
            case 11: {
                if (!check_active()) break;
                lists.push_back(new List(*lists[active_idx]));
                active_idx = lists.size() - 1;
                std::cout << "Copied to new list #" << active_idx << ".\n";
                break;
            }
            case 12: {
                for (auto* l : lists) delete l;
                std::cout << "Exiting.\n";
                return 0;
            }
            default:
                std::cout << "Unknown command.\n";
        }
    }
}