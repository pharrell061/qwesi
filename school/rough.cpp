#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <filesystem>

using namespace std;

struct JournalEntry{
    int id;
    char name [50];
    int age;
    float score;
};

void generateRandomEntry(JournalEntry& entry, int id){
    entry.id = id + 1;

    const char* names[] = {"Alice", "Bob", "Charlie", "David", "Eve"};
    strcpy(entry.name, names[rand() % 5]);
}