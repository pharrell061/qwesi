#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <filesystem>

using namespace std;

struct JournalEntry {
    int id;
    char name[50];
    int age;
    float score;
};

void generateRandomEntry(JournalEntry& entry, int id) {
    entry.id = id + 1;
    
    const char* names[] = { "Alice", "Bob", "Charlie", "Diana", "Eve", 
                           "Frank", "Grace", "Henry", "Ivy", "Jack" };
    
    strncpy(entry.name, names[id % 10], sizeof(entry.name) - 1);
    entry.name[sizeof(entry.name) - 1] = '\0';
    
    entry.age = 18 + rand() % 43;
    
    entry.score = (float)(rand() % 10000) / 100.0f;
}

void writeToFile(const string& filename) {
    ofstream file(filename, ios::binary);
    
    if (!file.is_open()) {
        cerr << "Error: Cannot open file for writing!" << endl;
        return;
    }
    
    cout << "Writing 10 entries to binary file..." << endl;
    
    for (int i = 0; i < 10; i++) {
        JournalEntry entry;
        
        generateRandomEntry(entry, i);
        
        file.write(reinterpret_cast<char*>(&entry), sizeof(JournalEntry));
    }
    
    file.close();
    
    cout << "Successfully written 10 entries!" << endl;
}

void readFromFile(const string& filename) {
    ifstream file(filename, ios::binary);
    
    if (!file.is_open()) {
        cerr << "Error: Cannot open file for reading!" << endl;
        return;
    }
    
    cout << "\n========== JOURNAL ENTRIES ==========" << endl;
    
    cout << setw(5) << "ID" << setw(15) << "Name" << setw(8) << "Age" 
         << setw(10) << "Score" << endl;
    cout << "=====================================" << endl;
    
    JournalEntry entry;
    int count = 0;
    
    while (file.read(reinterpret_cast<char*>(&entry), sizeof(JournalEntry))) {
        cout << setw(5) << entry.id 
             << setw(15) << entry.name 
             << setw(8) << entry.age 
             << setw(10) << fixed << setprecision(2) << entry.score << endl;
        
        count++;
    }
    
    cout << "=====================================" << endl;
    
    cout << "Total entries read: " << count << endl;
    
    file.close();
}

void displayFileSize(const string& filename) {
    try {
        uintmax_t size = filesystem::file_size(filename);
        
        cout << "\nFile size: " << size << " bytes" << endl;
    } 
    catch (const exception& e) {
        cerr << "Error getting file size: " << e.what() << endl;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    
    string filename = "journal.bin";
    
    cout << "=== BINARY JOURNAL PROGRAM ===" << endl;
    
    writeToFile(filename);
    
    readFromFile(filename);
    
    displayFileSize(filename);
    
    cout << "\nProgram completed successfully!" << endl;
    
    return 0;
}
