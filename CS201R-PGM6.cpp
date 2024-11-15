// CS201R-PGM7.cpp : This file contains the 'main' function. Program execution begins and ends there.
// GUNNER PACE

#include "Functions.h"
#include "Media.h"
 
using namespace std;

int main() {
    // Declare and open the input and output files
    ifstream inList("mediaList.txt");
    ifstream inCommands("mediaCommands.txt");
    ofstream outFile("mediaReport.txt");
    ofstream outErr("mediaError.txt");

    // Check if the files were opened successfully
    if (!inList.good()) {
        cout << "Could not open mediaList.txt" << endl;
        exit(1); // Exit if there's an issue
    }
    if (!inCommands.good()) {
        cout << "Could not open mediaCommands.txt" << endl;
        exit(1); // Exit if there's an issue
    }
    if (!outFile.good()) {
        cout << "Could not open mediaReport.txt" << endl;
        exit(1); // Exit if there's an issue
    }
    if (!outErr.good()) {
        cout << "Could not open mediaError.txt" << endl;
        exit(1); // Exit if there's an issue
    }

    vector<Media*> myLib;

    // Read data into myLib
    readMediaList(inList, outErr, myLib);
    inList.close();

    // Prepare to read the commands
    string commandRecord;
    vector<string> commandTokens;
    char choice;

    while (getline(inCommands, commandRecord)) {
        // Reset stringstream for each command
        stringstream ss(commandRecord);
        commandTokens.clear(); // Clear previous tokens

        // Tokenize the command by commas
        string token;
        while (getline(ss, token, ',')) {
            commandTokens.push_back(token);
        }

        // Ensure there is at least one token before accessing
        if (!commandTokens.empty()) {
            choice = commandTokens[0][0]; // Get the first character for the command choice
            string lookupName;
            string actorName;
            string creatorName;

            // Process command
            switch (choice) {
            case 'A':
                if (commandTokens.size() == 1) {
                    printAllMedia(outFile, myLib); // No rating or genre specified; print all media
                }
                else if (commandTokens.size() > 1) {
                    if (isDigits(commandTokens[1])) {
                        int ratingVal = stoi(commandTokens[1]); // Convert to integer
                        if (ratingVal >= 1 && ratingVal <= 10) {
                            printAllMedia(outFile, myLib, ratingVal); // Print with rating filter
                        }
                        else {
                            outErr << "Unable to process command. The rating " << commandTokens[1] << " is out of range. Please enter a rating between 1 and 10." << endl;
                        }
                    }
                    else {
                        string genre = commandTokens[1];
                        printAllMedia(outFile, myLib, genre); // Print with genre filter
                    }
                }
                break;

            case 'M':
                if (commandTokens.size() == 1) {
                    printMovies(outFile, myLib); // No rating specified; print all movies
                }
                else if (commandTokens.size() > 1) {
                    if (isDigits(commandTokens[1])) {
                        int ratingVal = stoi(commandTokens[1]); // Convert to integer
                        if (ratingVal >= 1 && ratingVal <= 10) {
                            printMovies(outFile, myLib, ratingVal); // Print movies with rating filter
                        }
                        else {
                            outErr << "Unable to process command. The rating " << commandTokens[1] << " is out of range. Please enter a rating between 1 and 10." << endl;
                        }
                    }
                    else {
                        string genre = commandTokens[1];
                        printMovies(outFile, myLib, genre); // Print movies with genre filter
                    }
                }
                break;

            case 'B':
                if (commandTokens.size() == 1) {
                    printBooks(outFile, myLib); // No rating specified; print all books
                }
                else if (commandTokens.size() > 1) {
                    if (isDigits(commandTokens[1])) {
                        int ratingVal = stoi(commandTokens[1]); // Convert to integer
                        if (ratingVal >= 1 && ratingVal <= 10) {
                            printBooks(outFile, myLib, ratingVal); // Print books with rating filter
                        }
                        else {
                            outErr << "Unable to process command. The rating " << commandTokens[1] << " is out of range. Please enter a rating between 1 and 10." << endl;
                        }
                    }
                    else {
                        string genre = commandTokens[1];
                        printBooks(outFile, myLib, genre); // Print books with genre filter
                    }
                }
                break;

            case 'S':
                if (commandTokens.size() == 1) {
                    printSongs(outFile, myLib); // No rating specified; print all songs
                }
                else if (commandTokens.size() > 1) {
                    if (isDigits(commandTokens[1])) {
                        int ratingVal = stoi(commandTokens[1]); // Convert to integer
                        if (ratingVal >= 1 && ratingVal <= 10) {
                            printSongs(outFile, myLib, ratingVal); // Print songs with rating filter
                        }
                        else {
                            outErr << "Unable to process command. The rating " << commandTokens[1] << " is out of range. Please enter a rating between 1 and 10." << endl;
                        }
                    }
                    else {
                        string genre = commandTokens[1];
                        printSongs(outFile, myLib, genre); // Print songs with genre filter
                    }
                }
                break;

            case 'T':
                printTotals(outFile);
                break;

            case 'Q':
                cout << "Thank You for Using Media Everywhere" << endl;
                outErr << "Thank You for Using Media Everywhere" << endl;
                return 0; // Exit the program

            case 'N':
                if (commandTokens.size() >= 2) {
                    char mediaType = commandTokens[1][0]; // Media type (e.g., 'M', 'S', 'B')
                    try {
                        createMedia(mediaType, commandTokens, myLib, outErr, outFile);
                    }
                    catch (invalid_argument& e) {
                        outErr << setw(30) << e.what() << commandRecord << endl;
                    }
                }
                else {
                    cout << "Invalid N command: " << commandRecord << "\n";
                }
                break;

            case 'L':
                lookupName = commandTokens[1];
                castLookup(lookupName, myLib, outFile);
                break;

            case 'F':
                actorName = commandTokens[1];
                actorLookup(actorName, myLib, outFile);
                break;

            case 'K':
                creatorName = commandTokens[1];
                nameLookup(creatorName, myLib, outFile);
                break;

            default:
                outErr << "There is an error in the input command: " << commandRecord << "\n";
                break;
            }

        }
    }

    inCommands.close();
    outFile.close();
    outErr.close();
}
