#include <string>
#include <iostream>
#include <iomanip>
#include "Media.h"

using namespace std;

// Define the static member variable
int Media::placeNum = 0;  // Definition of the static variable
int Media::movieCount = 0; // Initialize movie count
int Media::songCount = 0;  // Initialize song count
int Media::bookCount = 0;  // Initialize book count

// Default constructor
Media::Media() {
    this->type = ' ';
    this->title = " ";
    this->name = " ";
    this->rating = -1;
    this->genre = " ";
    this->length = -1;
    this->yearReleased = -1;

    num = ++placeNum;  // Increment and assign the placeNum to num
}

// Parameterized constructor
Media::Media(char type, string title, string name, int rating, string genre, int length, int year) {
    this->type = type;
    this->title = title;
    this->name = name;
    this->rating = rating;
    this->genre = genre;
    this->length = length;
    this->yearReleased = year;

    num = ++placeNum;  // Increment and assign the placeNum to num
}

// Print function for output to file
void Media::printMedia(ofstream& outFile) {
    outFile << setw(2) << num << " " << setw(40) << left << title
        << setw(8) << left << yearReleased
        << setw(10) << left << rating
        << setw(10) << left << genre << endl;
}

// Print function for console output
void Media::printMedia() {
    cout << setw(2) << num << " " << setw(40) << left << title
        << setw(8) << left << yearReleased
        << setw(10) << left << rating
        << setw(10) << left << genre << endl;
}

// Static function to print counts of each type of media
void Media::printCounts(ofstream& outFile) {
    outFile << string(50, '*') << endl;
    outFile << "\tYOUR MEDIA LIBRARY\n" << endl;
    outFile << "Total Movies: " << movieCount << endl;
    outFile << "Total Songs: " << songCount << endl;
    outFile << "Total Books: " << bookCount << endl;
    outFile << "Total Items: " << movieCount + songCount + bookCount << endl;
    outFile << endl;
}

Movie::Movie(char type, string title, string name, int rating, string genre, int length, int year, vector<string> stars) {
    this->type = type;
    this->title = title;
    this->name = name;
    this->rating = rating;
    this->genre = genre;
    this->length = length;
    this->yearReleased = year;
    this->stars = stars;

    ++movieCount;
}

void Movie::printMedia(ofstream& outFile) {
    outFile << setw(2) << num << " " << setw(40) << left << title
        << setw(8) << left << yearReleased
        << setw(10) << left << rating
        << setw(30) << left << genre
        << "Stars: ";
    for (int i = 0; i < stars.size(); ++i) {
        outFile << stars[i] << " ";
    }
    outFile << endl;
}

Book::Book(char type, string title, string name, int rating, string genre, int length, int year, int weeks) {
    this->type = type;
    this->title = title;
    this->name = name;
    this->rating = rating;
    this->genre = genre;
    this->length = length;
    this->yearReleased = year;
    this->weeksNYT = weeks;

    ++bookCount;
}

void Book::printMedia(ofstream& outFile) {
    outFile << setw(2) << num << " " << setw(40) << left << title
        << setw(8) << left << yearReleased
        << setw(10) << left << rating
        << setw(30) << left << genre
        << "Weeks NYT: " << weeksNYT << endl;
}

Song::Song(char type, string title, string name, int rating, string genre, int length, int year, bool top40) {
    this->type = type;
    this->title = title;
    this->name = name;
    this->rating = rating;
    this->genre = genre;
    this->length = length;
    this->yearReleased = year;
    this->top40 = top40;

    ++songCount;
}

void Song::printMedia(ofstream& outFile) {
    outFile << setw(2) << num << " " << setw(40) << left << title
        << setw(8) << left << yearReleased
        << setw(10) << left << rating
        << setw(30) << left << genre;
    if (top40) outFile << "Top 40 Hit";
    else outFile << "---";
    outFile << endl;
}