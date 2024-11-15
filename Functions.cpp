#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "Functions.h"
#include "Media.h"

using namespace std;

bool isDigits(const string& s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

int readMediaList(istream& inFile, ostream& err, vector<Media*>& mediaLib) {
    string line = "";
    vector<string> tokens;
    string token;

    // Temporary class variables
    char type;
    string title;
    string name;
    int rating;
    string genre;
    int length;
    int yearReleased;

    while (getline(inFile, line)) { // Get new line from in file
        if (line.empty()) continue; // Skip empty lines early

        try {
            tokens.clear(); // Clear tokens each iteration
            stringstream ss(line);

            // Load tokens vector with field values from file
            while (getline(ss, token, ',')) tokens.push_back(token);

            // Remove trailing empty tokens from excessive commas
            while (!tokens.empty() && tokens.back().empty()) {
                tokens.pop_back();
            }

            // Validate integer field values
            if (tokens.size() < 7) throw invalid_argument("Insufficient field data:");
            if (!isDigits(tokens[3]) || stoi(tokens[3]) < 0 || stoi(tokens[3]) > 10) throw invalid_argument("Invalid rating value:");
            if (!isDigits(tokens[5]) || stoi(tokens[5]) < 0) throw invalid_argument("Invalid length value:");
            if (!isDigits(tokens[6]) || stoi(tokens[6]) < 1920 || stoi(tokens[6]) > 2024) throw invalid_argument("Invalid year value:");
            if (tokens[0] != "M" && tokens[0] != "B" && tokens[0] != "S") throw invalid_argument("Invalid media type:");

            // Assign class values
            type = tokens[0][0];
            title = tokens[1];
            name = tokens[2];
            rating = stoi(tokens[3]);
            genre = tokens[4];
            length = stoi(tokens[5]);
            yearReleased = stoi(tokens[6]);

            // Create class instance
            if (tokens[0] == "M") {
                vector<string> stars;
                for (int i = 7; i < tokens.size(); ++i) {
                    if (tokens[i] != "") {
                        stars.push_back(tokens[i]);
                    }
                }
                Movie* media = new Movie(type, title, name, rating, genre, length, yearReleased, stars);
                mediaLib.push_back(media);
            }
            else if (tokens[0] == "B") {
                if (!isDigits(tokens[7])) throw invalid_argument("Invalid weeksNYT value: ");
                int weeksNYT = stoi(tokens[7]);
                Book* media = new Book(type, title, name, rating, genre, length, yearReleased, weeksNYT);
                mediaLib.push_back(media);
            }
            else if (tokens[0] == "S") {
                bool top40 = false;
                if (tokens[7] != "1" && tokens[7] != "0") throw invalid_argument("Invalid top40 value: ");
                if (tokens[7] == "1") top40 = true;
                Song* media = new Song(type, title, name, rating, genre, length, yearReleased, top40);
                mediaLib.push_back(media);
            }

        }
        catch (invalid_argument& e) {
            err << setw(30) << left << e.what() << line << endl;
        }
        catch (...) {
            err << setw(30) << left << "UNKNOWN ERROR OCCURRED: " << line << endl;
            inFile.clear();
        }
    }

    return 0;
}


void printAllMedia(ofstream& outFile, vector<Media*> mediaLib) {

    outFile << string(50, '*') << endl;
    outFile << "\tYOUR MEDIA LIST\n" << endl;
    outFile << "#  " << setw(40) << left << "TITLE"
        << setw(8) << left << "YEAR"
        << setw(10) << left << "RATING"
        << setw(30) << left << "GENRE"
        << "OTHER FIELDS" << endl;

    for (auto media : mediaLib) media->printMedia(outFile);
    outFile << endl;
}

void printAllMedia(ofstream& outFile, vector<Media*> mediaLib, int ratingVal) {

    bool ratingExists = false;

    outFile << string(50, '*') << endl;
    outFile << "\tYOUR MEDIA LIST FOR RATING >=" << ratingVal << "\n" << endl;
    outFile << "#  " << setw(40) << left << "TITLE"
        << setw(8) << left << "YEAR"
        << setw(10) << left << "RATING"
        << setw(30) << left << "GENRE"
        << "OTHER FIELDS" << endl;

    for (auto media : mediaLib) {
        if (media->getRating() >= ratingVal) {
            media->printMedia(outFile);
            ratingExists = true;
        }
    }
    if (!ratingExists) outFile << "NO MEDIA EXISTS WITH REQUESTED RATING" << endl;
    outFile << endl;
}

void printAllMedia(ofstream& outFile, vector<Media*> mediaLib, string genre) {

    bool genreExists = false;

    outFile << string(50, '*') << endl;
    outFile << "\tYOUR MEDIA LIST FOR GENRE " << genre << "\n" << endl;
    outFile << "#  " << setw(40) << left << "TITLE"
        << setw(8) << left << "YEAR"
        << setw(10) << left << "RATING"
        << setw(30) << left << "GENRE"
        << "OTHER FIELDS" << endl;

    for (auto media : mediaLib) {
        if (media->getGenre() == genre) {
            media->printMedia(outFile);
            genreExists = true;
        }
    }
    if (!genreExists) outFile << "NO MEDIA EXISTS WITH REQUESTED GENRE" << endl;
    outFile << endl;
}


void printMovies(ofstream& outFile, vector<Media*> mediaLib) {
    
    outFile << string(50, '*') << endl; 
    outFile << "\tYOUR MOVIE LIST\n" << endl;
    outFile << "#  " << setw(40) << left << "TITLE"
        << setw(8) << left << "YEAR"
        << setw(10) << left << "RATING"
        << setw(30) << left << "GENRE"
        << "OTHER FIELDS" << endl;

    for (auto media : mediaLib) {
        if (media->getType() == 'M') {
            media->printMedia(outFile);
        }
    }
    outFile << endl; 
}

void printMovies(ofstream& outFile, vector<Media*> mediaLib, int ratingVal) {

    bool ratingExists = false;

    outFile << string(50, '*') << endl;
    outFile << "\tYOUR MOVIE LIST FOR RATING >=" << ratingVal << "\n" << endl;
    outFile << "#  " << setw(40) << left << "TITLE"
        << setw(8) << left << "YEAR"
        << setw(10) << left << "RATING"
        << setw(30) << left << "GENRE"
        << "OTHER FIELDS" << endl;

    for (auto media : mediaLib) {
        if (media->getType() == 'M') {
            if (media->getRating() >= ratingVal) {
                media->printMedia(outFile);
                ratingExists = true;
            }
        }
    }
    if (!ratingExists) outFile << "NO MOVIES EXIST WITH REQUESTED RATING" << endl;
    outFile << endl;
}

void printMovies(ofstream& outFile, vector<Media*> mediaLib, string genre) {

    bool genreExists = false;

    outFile << string(50, '*') << endl;
    outFile << "\tYOUR MOVIE LIST FOR GENRE " << genre << "\n" << endl;
    outFile << "#  " << setw(40) << left << "TITLE"
        << setw(8) << left << "YEAR"
        << setw(10) << left << "RATING"
        << setw(30) << left << "GENRE"
        << "OTHER FIELDS" << endl;

    for (auto media : mediaLib) {
        if (media->getType() == 'M') {
            if (media->getGenre() == genre) {
                media->printMedia(outFile);
                genreExists = true;
            }
        }
    }
    if (!genreExists) outFile << "NO MOVIES EXIST WITH REQUESTED GENRE" << endl;
    outFile << endl;
}


void printBooks(ofstream& outFile, vector<Media*> mediaLib) {

    outFile << string(50, '*') << endl;
    outFile << "\tYOUR BOOK LIST\n" << endl;
    outFile << "#  " << setw(40) << left << "TITLE"
        << setw(8) << left << "YEAR"
        << setw(10) << left << "RATING"
        << setw(30) << left << "GENRE"
        << "OTHER FIELDS" << endl;

    for (auto media : mediaLib) {
        if (media->getType() == 'B') {
            media->printMedia(outFile);
        }
    }
    outFile << endl;
}

void printBooks(ofstream& outFile, vector<Media*> mediaLib, int ratingVal) {

    bool ratingExists = false;

    outFile << string(50, '*') << endl;
    outFile << "\tYOUR BOOK LIST FOR RATING >=" << ratingVal << "\n" << endl;
    outFile << "#  " << setw(40) << left << "TITLE"
        << setw(8) << left << "YEAR"
        << setw(10) << left << "RATING"
        << setw(30) << left << "GENRE"
        << "OTHER FIELDS" << endl;

    for (auto media : mediaLib) {
        if (media->getType() == 'B') {
            if (media->getRating() >= ratingVal) {
                media->printMedia(outFile);
                ratingExists = true;
            }
        }
    }
    if (!ratingExists) outFile << "NO BOOKS EXIST WITH REQUESTED RATING" << endl;
    outFile << endl;
}

void printBooks(ofstream& outFile, vector<Media*> mediaLib, string genre) {

    bool genreExists = false;

    outFile << string(50, '*') << endl;
    outFile << "\tYOUR BOOK LIST FOR GENRE " << genre << "\n" << endl;
    outFile << "#  " << setw(40) << left << "TITLE"
        << setw(8) << left << "YEAR"
        << setw(10) << left << "RATING"
        << setw(30) << left << "GENRE"
        << "OTHER FIELDS" << endl;

    for (auto media : mediaLib) {
        if (media->getType() == 'B') {
            if (media->getGenre() == genre) {
                media->printMedia(outFile);
                genreExists = true;
            }
        }
    }
    if (!genreExists) outFile << "NO BOOKS EXIST WITH REQUESTED GENRE" << endl;
    outFile << endl;
}


void printSongs(ofstream& outFile, vector<Media*> mediaLib) {

    outFile << string(50, '*') << endl;
    outFile << "\tYOUR SONG LIST\n" << endl;
    outFile << "#  " << setw(40) << left << "TITLE"
        << setw(8) << left << "YEAR"
        << setw(10) << left << "RATING"
        << setw(30) << left << "GENRE"
        << "OTHER FIELDS" << endl;

    for (auto media : mediaLib) {
        if (media->getType() == 'S') {
            media->printMedia(outFile);
        }
    }
    outFile << endl;
}

void printSongs(ofstream& outFile, vector<Media*> mediaLib, int ratingVal) {

    bool ratingExists = false;

    outFile << string(50, '*') << endl;
    outFile << "\tYOUR SONG LIST FOR RATING >=" << ratingVal << "\n" << endl;
    outFile << "#  " << setw(40) << left << "TITLE"
        << setw(8) << left << "YEAR"
        << setw(10) << left << "RATING"
        << setw(30) << left << "GENRE"
        << "OTHER FIELDS" << endl;

    for (auto media : mediaLib) {
        if (media->getType() == 'S') {
            if (media->getRating() >= ratingVal) {
                media->printMedia(outFile);
                ratingExists = true;
            }
        }
    }
    if (!ratingExists) outFile << "NO SONGS EXIST WITH REQUESTED RATING" << endl;
    outFile << endl;
}

void printSongs(ofstream& outFile, vector<Media*> mediaLib, string genre) {

    bool genreExists = false;

    outFile << string(50, '*') << endl;
    outFile << "\tYOUR SONG LIST FOR GENRE " << genre << "\n" << endl;
    outFile << "#  " << setw(40) << left << "TITLE"
        << setw(8) << left << "YEAR"
        << setw(10) << left << "RATING"
        << setw(30) << left << "GENRE"
        << "OTHER FIELDS" << endl;

    for (auto media : mediaLib) {
        if (media->getType() == 'S') {
            if (media->getGenre() == genre) {
                media->printMedia(outFile);
                genreExists = true;
            }
        }
    }
    if (!genreExists) outFile << "NO SONGS EXIST WITH REQUESTED GENRE" << endl;
    outFile << endl;
}


void printTotals(ofstream& outFile) {
    Media::printCounts(outFile);
}

// Function to create a new media object
void createMedia(char mediaType, const vector<string>& commandTokens, vector<Media*>& myLib, ofstream& outErr, ofstream& outFile) {
    // Validate the number of tokens for expected input
    if (commandTokens.size() < 9) throw invalid_argument("Insufficient data for item: "); // Ensure at least 8 tokens for all fields

    // Extract fields
    string title = commandTokens[2];
    string name = commandTokens[3];
    string ratingStr = commandTokens[4];
    string genre = commandTokens[5];
    string lengthStr = commandTokens[6];
    string yearStr = commandTokens[7];

    // Validate media type
    if (mediaType != 'M' && mediaType != 'B' && mediaType != 'S') throw invalid_argument("Invalid media type: ");

    // Validate rating, length, and year fields
    if (!isDigits(ratingStr) || !isDigits(lengthStr) || !isDigits(yearStr)) throw invalid_argument("Invalid values: ");

    // Convert strings to integers
    int rating = stoi(ratingStr);
    int length = stoi(lengthStr);
    int year = stoi(yearStr);

    // Additional validations
    if (rating <= 0 || rating > 10) throw invalid_argument("Invalid rating value: ");

    if (length <= 0) throw invalid_argument("Invalid length value: ");

    if (year < 1920 || year > 2024) throw invalid_argument("Invalid year value: ");

    // Create class instance
    if (commandTokens[1] == "M") {
        char type = 'M';
        vector<string> stars;
        for (int i = 8; i < commandTokens.size(); ++i) {
            if (commandTokens[i] != "") {
                stars.push_back(commandTokens[i]);
            }
        }
        Movie* media = new Movie(type, title, name, rating, genre, length, year, stars);
        myLib.push_back(media);
    }
    else if (commandTokens[1] == "B") {
        char type = 'B';
        if (!isDigits(commandTokens[8])) throw invalid_argument("Invalid weeksNYT value: ");
        int weeksNYT = stoi(commandTokens[8]);
        Book* media = new Book(type, title, name, rating, genre, length, year, weeksNYT);
        myLib.push_back(media);
    }
    else if (commandTokens[1] == "S") {
        char type = 'S';
        bool top40 = false;
        if (commandTokens[8] != "1" && commandTokens[8] != "0") throw invalid_argument("Invalid top40 value: ");
        if (commandTokens[8] == "1") top40 = true;
        Song* media = new Song(type, title, name, rating, genre, length, year, top40);
        myLib.push_back(media);
    }

    outFile << '\n' << title << " was added to your media list.\n" << endl;
}

// Helper function to join tokens into a single string for error messages
string joinTokens(const vector<string>& tokens) {
    stringstream ss;
    for (const auto& token : tokens) {
        ss << token << " ";
    }
    return ss.str();
}

void castLookup(string title, vector<Media*> myLib, ofstream& outFile) {
    outFile << string(50, '*') << endl;
    outFile << "THE STARS OF THE MOVIE " << title << " ARE:" << '\n' << endl;
    bool found = false;
    for (auto media : myLib) {
        if (media->getType() == 'M' && media->getTitle() == title) {
            vector<string> stars = static_cast<Movie*>(media)->getStars();
            for (int i = 0; i < stars.size(); ++i) {
                outFile << stars[i] << endl;
            }
            found = true;
        }
    }
    if (!found) outFile << "NO MOVIES FOUND MATCHING REQUESTED TITLE" << endl;
    outFile << "\n\n" << endl;
}

void actorLookup(string name, vector<Media*> myLib, ofstream& outFile) {
    outFile << string(50, '*') << endl;
    outFile << name << " APPEARS IN THE FOLLOWING MOVIE(S):" << '\n' << endl;
    bool found = false;
    for (auto media : myLib) {
        if (media->getType() == 'M') {
            vector<string> stars = static_cast<Movie*>(media)->getStars();
            for (int i = 0; i < stars.size(); ++i) {
                if (stars[i] == name) {
                    outFile << media->getTitle() << endl;
                    found = true;
                }
            }
        }
    }
    if (!found) outFile << "NO MOVIES FOUND MATCHING REQUESTED ACTOR" << endl;
    outFile << "\n\n" << endl;
}

void nameLookup(string name, vector<Media*> myLib, ofstream& outFile) {
    outFile << string(50, '*') << endl;
    outFile << "YOUR LIST CONTAINING " << name << '\n' << endl;
    outFile << "#  " << setw(40) << left << "TITLE"
        << setw(8) << left << "YEAR"
        << setw(10) << left << "RATING"
        << setw(30) << left << "GENRE"
        << "OTHER FIELDS" << endl;
    bool found = false;
    for (auto media : myLib) {
        if (media->getName() == name) {
            media->printMedia(outFile);
            found = true;
        }
    }
    if (!found) outFile << "NO MEDIA FOUND MATCHING REQUESTED CREATOR" << endl;
    outFile << "\n\n" << endl;
}