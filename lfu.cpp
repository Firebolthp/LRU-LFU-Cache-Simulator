#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

class LFUCache {
private:
    struct Node {
        int key, value, freq;
        Node(int k, int v) : key(k), value(v), freq(1) {}
    };

    int capacity, minFreq;
    unordered_map<int, list<Node>> freqMap;
    unordered_map<int, list<Node>::iterator> keyMap; 
    int size;

public:
    LFUCache(int cap) : capacity(cap), minFreq(0), size(0) {}

    int get(int key) {
        if (keyMap.find(key) == keyMap.end()) return -1;

        auto nodeIt = keyMap[key];
        Node node = *nodeIt;
        freqMap[node.freq].erase(nodeIt);
        if (freqMap[node.freq].empty()) {
            freqMap.erase(node.freq);
            if (minFreq == node.freq) minFreq++;
        }

        node.freq++;
        freqMap[node.freq].push_front(node);
        keyMap[key] = freqMap[node.freq].begin();

        return node.value;
    }

    void put(int key, int value) {
        if (capacity == 0) return;

        if (keyMap.find(key) != keyMap.end()) {
            keyMap[key]->value = value;
            get(key);
            return;
        }

        if (size >= capacity) {
            auto &lfuList = freqMap[minFreq];
            Node evictNode = lfuList.back();
            keyMap.erase(evictNode.key);
            lfuList.pop_back();
            if (lfuList.empty()) {
                freqMap.erase(minFreq);
            }
            size--;
        }

        Node newNode(key, value);
        freqMap[1].push_front(newNode);
        keyMap[key] = freqMap[1].begin();
        minFreq = 1;
        size++;
    }

    void display() {
        cout << "Cache (Grouped by Frequency):\n";
        for (auto &entry : freqMap) {
            cout << "Freq " << entry.first << ": ";
            for (auto &node : entry.second) {
                cout << "[" << node.key << ":" << node.value << "] ";
            }
            cout << "\n";
        }
        cout << endl;
    }
};

int main() {
    int capacity;
    cout << "Enter LFU Cache Capacity: ";
    cin >> capacity;
    LFUCache cache(capacity);

    int choice;
    while (true) {
        cout << "\n----- LFU Cache Menu -----\n";
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
