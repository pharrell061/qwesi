// ============ HEADER FILES ============
// Standard input/output library for console operations (cin, cout, cerr)
#include <iostream>

// File stream library for reading/writing files (ifstream, ofstream)
#include <fstream>

// Standard string library (for string class if needed)
#include <string>

// C standard library for random number generation (rand, srand)
#include <cstdlib>

// Time library for seeding random numbers with current time
#include <ctime>

// Input/output manipulator library for formatting output (setw, fixed, setprecision)
#include <iomanip>

// Filesystem library for getting file size and file operations
#include <filesystem>

// This allows us to use cout, cin, string, etc. without writing std::
using namespace std;

// ============ STRUCTURE DEFINITION ============
// struct is a template for organizing related data together
// All variables inside belong to one "object" or "record"
struct JournalEntry {
    // Integer that uniquely identifies each journal entry (entry number)
    int id;
    
    // Character array of size 50 for storing a person's name
    // char[50] means 50 individual characters
    char name[50];
    
    // Integer for storing the person's age in years
    int age;
    
    // Float (decimal number) for storing a score or grade
    float score;
    // Each JournalEntry will take up space in memory:
    // int (4 bytes) + char[50] (50 bytes) + int (4 bytes) + float (4 bytes) = 62 bytes total
};

// ============ FUNCTION TO GENERATE RANDOM DATA ============
// This function takes a reference to a JournalEntry (& means we modify the original, not a copy)
// and an integer 'id' which will be used to populate the entry
void generateRandomEntry(JournalEntry& entry, int id) {
    // Set the id field: add 1 so IDs start from 1 instead of 0
    entry.id = id + 1;
    
    // Array of predefined names to choose from (10 names)
    const char* names[] = { "Alice", "Bob", "Charlie", "Diana", "Eve", 
                           "Frank", "Grace", "Henry", "Ivy", "Jack" };
    
    // strcpy_s copies a string safely to the char array
    // names[id % 10] uses modulo (%) to cycle through the names array
    // For example: id=0 -> names[0], id=10 -> names[0], id=11 -> names[1]
    strcpy_s(entry.name, sizeof(entry.name), names[id % 10]);
    
    // Generate random age between 18 and 60
    // rand() gives random number, % 43 gives 0-42, +18 gives 18-60
    entry.age = 18 + rand() % 43;
    
    // Generate random score between 0 and 100
    // rand() % 10000 gives 0-9999, divide by 100.0f to get decimal (0-99.99)
    entry.score = (float)(rand() % 10000) / 100.0f;
}

// ============ FUNCTION TO WRITE ENTRIES TO BINARY FILE ============
// This function takes the filename as a parameter
void writeToFile(const string& filename) {
    // Create an output file stream (ofstream) in binary mode
    // ios::binary means write as raw bytes, not text
    ofstream file(filename, ios::binary);
    
    // Check if the file was successfully opened
    if (!file.is_open()) {
        // Print error message to error output stream
        cerr << "Error: Cannot open file for writing!" << endl;
        // Exit function early if file didn't open
        return;
    }
    
    // Tell user what the program is doing
    cout << "Writing 10 entries to binary file..." << endl;
    
    // Loop 10 times to create 10 entries
    for (int i = 0; i < 10; i++) {
        // Create a new JournalEntry on the stack for this iteration
        JournalEntry entry;
        
        // Call function to fill 'entry' with random data
        generateRandomEntry(entry, i);
        
        // Write the struct to file as binary data
        // reinterpret_cast<char*>(&entry) converts the struct address to a char pointer
        // This allows us to write the raw bytes of the struct
        // sizeof(JournalEntry) tells write() how many bytes to write (62 bytes)
        file.write(reinterpret_cast<char*>(&entry), sizeof(JournalEntry));
    }
    
    // Close the file to flush all data to disk and free resources
    file.close();
    
    // Confirm successful write to user
    cout << "Successfully written 10 entries!" << endl;
}

// ============ FUNCTION TO READ AND DISPLAY ENTRIES FROM BINARY FILE ============
// This function reads all entries from the binary file and prints them nicely
void readFromFile(const string& filename) {
    // Create an input file stream (ifstream) in binary mode to read the file
    // ios::binary means read as raw bytes, not text
    ifstream file(filename, ios::binary);
    
    // Check if file opened successfully
    if (!file.is_open()) {
        cerr << "Error: Cannot open file for reading!" << endl;
        return;
    }
    
    // Print header for the table
    cout << "\n========== JOURNAL ENTRIES ==========" << endl;
    
    // Print column headers with formatting
    // setw(5) means allocate 5 character spaces for next output
    cout << setw(5) << "ID" << setw(15) << "Name" << setw(8) << "Age" 
         << setw(10) << "Score" << endl;
    cout << "=====================================" << endl;
    
    // Create a temporary entry to hold data read from file
    JournalEntry entry;
    
    // Counter to track how many entries we read
    int count = 0;
    
    // Loop to read entries from file
    // file.read() reads exactly sizeof(JournalEntry) bytes from file into &entry
    // The condition checks if read was successful (true if read succeeded, false at EOF)
    // reinterpret_cast<char*>(&entry) converts struct address to char pointer for read()
    while (file.read(reinterpret_cast<char*>(&entry), sizeof(JournalEntry))) {
        // Print the entry data with formatting to align columns
        cout << setw(5) << entry.id                    // Print ID in 5-char space
             << setw(15) << entry.name                 // Print name in 15-char space
             << setw(8) << entry.age                   // Print age in 8-char space
             << setw(9) << fixed << setprecision(2)    // fixed means always use decimal format
                         << entry.score << endl;        // Print score with 2 decimal places
        
        // Increment counter for each entry read
        count++;
    }
    
    // Print footer
    cout << "=====================================" << endl;
    
    // Show total number of entries that were read
    cout << "Total entries read: " << count << endl;
    
    // Close the file to free system resources
    file.close();
}

// ============ FUNCTION TO DISPLAY FILE SIZE ============
// This function gets and prints the size of the binary file in bytes
void displayFileSize(const string& filename) {
    // try-catch block helps handle errors gracefully
    // try runs the code, catch catches any exceptions (errors)
    try {
        // filesystem::file_size() returns the file size in bytes
        // uintmax_t is an unsigned integer type for storing large numbers
        uintmax_t size = filesystem::file_size(filename);
        
        // Print the file size to the console
        cout << "\nFile size: " << size << " bytes" << endl;
    } 
    // catch exception if file doesn't exist or can't be accessed
    catch (const exception& e) {
        // Print error message from the exception
        cerr << "Error getting file size: " << e.what() << endl;
    }
}

// ============ MAIN FUNCTION - ENTRY POINT OF PROGRAM ============
// This is where the program starts executing
int main() {
    // Seed the random number generator with current time
    // This ensures different random numbers each time program runs
    // Static cast converts time(0) to unsigned int type that srand() expects
    srand(static_cast<unsigned>(time(0)));
    
    // Create a string variable to store the filename we'll use
    string filename = "journal.bin";
    
    // Print program title to console
    cout << "=== BINARY JOURNAL PROGRAM ===" << endl;
    
    // Call function to write 10 random entries to the binary file
    writeToFile(filename);
    
    // Call function to read all entries back from file and display them
    readFromFile(filename);
    
    // Call function to show how many bytes the binary file takes up
    displayFileSize(filename);
    
    // Print completion message
    cout << "\nProgram completed successfully!" << endl;
    
    // Return 0 to indicate successful program execution
    // (non-zero would indicate an error occurred)
    return 0;
}
