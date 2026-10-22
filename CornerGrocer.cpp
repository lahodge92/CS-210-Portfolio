
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>
using namespace std;

// This class keeps track of the grocery items and their frequencies.
class GroceryTracker {
private:
    map<string, int> itemCounts;

public:
    // Read the grocery items from the input file.
    bool loadItems(string fileName) {
        ifstream inputFile(fileName);
        string item;

        if (!inputFile.is_open()) {
            cout << "Error: Could not open " << fileName << endl;
            return false;
        }

        while (inputFile >> item) {
            itemCounts[item]++;
        }

        inputFile.close();
        return true;
    }

    // Create a backup file with the item counts.
    bool saveBackup() {
        ofstream outputFile("frequency.dat");

        if (!outputFile.is_open()) {
            cout << "Error: Could not create frequency.dat" << endl;
            return false;
        }

        for (const auto& item : itemCounts) {
            outputFile << item.first << " " << item.second << endl;
        }

        outputFile.close();
        return true;
    }

    // Option 1: Find how many times an item was purchased.
    void searchItem() {
        string item;

        cout << "\nEnter the item you want to search for: ";
        cin >> item;

        auto found = itemCounts.find(item);

        if (found != itemCounts.end()) {
            cout << item << " was purchased "
                << found->second << " times." << endl;
        }
        else {
            cout << item << " was purchased 0 times." << endl;
        }
    }

    // Option 2: Display all items and their frequencies.
    void displayFrequencies() {
        cout << "\nGrocery Item Frequencies\n";
        cout << "------------------------\n";

        for (const auto& item : itemCounts) {
            cout << item.first << " " << item.second << endl;
        }
    }

    // Option 3: Display a histogram using asterisks.
    void displayHistogram() {
        cout << "\nGrocery Item Histogram\n";
        cout << "----------------------\n";

        for (const auto& item : itemCounts) {
            cout << item.first << " ";

            for (int i = 0; i < item.second; i++) {
                cout << "*";
            }

            cout << endl;
        }
    }
};

// Display the menu choices.
void displayMenu() {
    cout << "\n=================================\n";
    cout << "       CORNER GROCER MENU\n";
    cout << "=================================\n";
    cout << "1. Search for an item\n";
    cout << "2. Display all item frequencies\n";
    cout << "3. Display histogram\n";
    cout << "4. Exit program\n";
    cout << "=================================\n";
    cout << "Enter your choice (1-4): ";
}

int main() {
    GroceryTracker tracker;
    int choice = 0;

    // Load the grocery list when the program starts.
    if (!tracker.loadItems("CS210_Project_Three_Input_File.txt")) {
        return 1;
    }

    // Automatically create the backup file.
    if (!tracker.saveBackup()) {
        return 1;
    }

    // Keep showing the menu until the user chooses Exit.
    while (choice != 4) {
        displayMenu();

        if (!(cin >> choice)) {
            cout << "\nInvalid input. Please enter a number from 1 to 4.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            tracker.searchItem();
            break;

        case 2:
            tracker.displayFrequencies();
            break;

        case 3:
            tracker.displayHistogram();
            break;

        case 4:
            cout << "\nThank you for using Corner Grocer. Goodbye!\n";
            break;

        default:
            cout << "\nInvalid choice. Please select 1 through 4.\n";
            break;
        }
    }

    return 0;
}
