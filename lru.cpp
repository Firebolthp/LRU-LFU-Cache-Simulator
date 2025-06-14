#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

class LRUCache {
    int capacity;
    list<pair<int, int>> cacheList; // key, value
    unordered_map<int, list<pair<int, int>>::iterator> cacheMap;

public:
    LRUCache(int cap) : capacity(cap) {}

    int get(int key) {
        if (cacheMap.find(key) == cacheMap.end()) return -1;
        auto node = cacheMap[key];
        int value = node->second;

        cacheList.erase(node);
        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin();
        return value;
    }

    void put(int key, int value) {
        if (cacheMap.find(key) != cacheMap.end()) {
            cacheList.erase(cacheMap[key]);
        } else if (cacheList.size() == capacity) {
            auto last = cacheList.back();
            cacheMap.erase(last.first);
            cacheList.pop_back();
        }

        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin();
    }

    void display() {
        cout << "Cache (Most → Least Recent): ";
        for (auto &p : cacheList) {
            cout << "[" << p.first << ":" << p.second << "] ";
        }
        cout << endl;
    }
};

int main() {
    int capacity;
    cout << "Enter LRU Cache Capacity: ";
    cin >> capacity;
    LRUCache cache(capacity);

    int choice;
    while (true) {
        cout << "\n----- LRU Cache Menu -----\n";
        cout << "1. Put key-value\n";
        cout << "2. Get value by key\n";
        cout << "3. Display Cache\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int key, value;
            cout << "Enter key and value: ";
            cin >> key >> value;
            cache.put(key, value);
            cout << "Added (" << key << ", " << value << ") to cache.\n";
        } else if (choice == 2) {
            int key;
            cout << "Enter key to get value: ";
            cin >> key;
            int value = cache.get(key);
            if (value == -1)
                cout << "Key not found in cache.\n";
            else
                cout << "Value: " << value << endl;
        } else if (choice == 3) {
            cache.display();
        } else if (choice == 4) {
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}

