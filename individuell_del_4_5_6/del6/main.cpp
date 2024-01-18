#include <iostream>
#include <fstream>
#include <unordered_map>
#include <list>
#include <iterator>
#include <cstdlib>
#include <ctime>

struct HockeyPlayer {
    int id;
    std::string name;
    int jersey;
    std::string teamName;
};

class LRUCache {
private:
    std::list<HockeyPlayer> cacheList;
    std::unordered_map<int, std::list<HockeyPlayer>::iterator> cacheMap;
    const int capacity;


    void readFromFile() {
        std::ifstream file("hockey_players.txt", std::ios::in | std::ios::trunc);
        if (file.is_open()) {
            cacheList.clear();
            cacheMap.clear();

            int id, jersey;
            std::string name, teamName;
            while (file >> id >> name >> jersey >> teamName) {
                HockeyPlayer player = {id, name, jersey, teamName};
                addToCache(player);
            }
            file.close();
        } 
        else {
            std::cerr <<"Generating players.\n";
            
            file.close();

            std::ofstream clearFile("hockey_players.txt", std::ofstream::out | std::ofstream::trunc);
            clearFile.close();
            generateRandomData();
            saveToFile();
        }
    }


    void saveToFile() const {
        std::ofstream file("hockey_players.txt");
        if (file.is_open()) {
            for (const auto& player : cacheList) {
                file <<"ID: " <<player.id <<" Player: " <<player.name <<" Jerseynumber: " <<player.jersey <<" Team: " <<player.teamName <<"\n";
            }
            file.close();
        } 
        else {
            std::cerr <<"Unable to open file for writing.\n";
        }
    }

    void generateRandomData() {
        std::srand(std::time(0));

        for (int i = 0; i < capacity; ++i) {
            int playerId = i + 1;
            int jersey = std::rand() % 100 + 1;
            std::string playerName = "Player" + std::to_string(playerId);
            std::string teamName = "Team" + std::to_string((i % 2) + 1);

            HockeyPlayer player = {playerId, playerName, jersey, teamName};
            addToCache(player);
        }
    }


    void addToCache(const HockeyPlayer& player) {
        if (cacheList.size() == static_cast<std::list<HockeyPlayer>::size_type>(capacity)) {
            int lastId = cacheList.back().id;
            cacheList.pop_back();
            cacheMap.erase(lastId);
        }
        cacheList.push_front(player);
        cacheMap[player.id] = cacheList.begin();
    }

public:
    LRUCache(int cap) : capacity(cap) {
        readFromFile();
    }

    ~LRUCache() {
        saveToFile();
    }

    HockeyPlayer* GetPlayer(int id) {
        auto it = cacheMap.find(id);
        if (it != cacheMap.end()) {
            HockeyPlayer player = *it->second;
            cacheList.erase(it->second);
            cacheList.push_front(player);
            cacheMap[id] = cacheList.begin();
            saveToFile();
            return &(*cacheMap[id]);
        } 
        else {
            readFromFile();
            it = cacheMap.find(id);
            if (it != cacheMap.end()) {
                return &(*cacheMap[id]);
            } else {
                return nullptr;
            }
        }
    }
};

int main() {
    LRUCache cache(100000);
    while (true) {
        std::cout <<"Enter player ID to search (enter -1 to exit): ";
        int playerIdToGet;
        std::cin>> playerIdToGet;

        if (playerIdToGet == -1) {
            break;  
        }

    HockeyPlayer* player = cache.GetPlayer(playerIdToGet);

    if (player != nullptr) {
        std::cout <<"Player found: " <<player->name <<" (ID: " << player->id <<", Team: " <<player->teamName <<")\n";
    } 
    else {
        std::cout <<"Player not found.\n";
    }

    }
    return 0;
}