#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Media {
protected:
    int num;
    static int placeNum;  // Make placeNum static
    static int movieCount; // Counter for movies
    static int songCount;  // Counter for songs
    static int bookCount;  // Counter for books
    char type;
    string title;
    string name;
    int rating;
    string genre;
    int length;
    int yearReleased;

public:
    // Constructors
    Media();
    Media(char type, string title, string name, int rating, string genre, int length, int year);

    // Setters
    void setType(char c) { type = c; }
    void setTitle(string t) { title = t; }
    void setName(string n) { name = n; }
    void setRating(int r) { rating = r; }
    void setGenre(string g) { genre = g; }
    void setLength(int l) { length = l; }
    void setYearReleased(int yr) { yearReleased = yr; }

    // Getters
    char getType() { return type; }
    string getTitle() { return title; }
    string getName() { return name; }
    int getRating() { return rating; }
    string getGenre() { return genre; }
    int getLength() { return length; }
    int getYearReleased() { return yearReleased; }

    virtual void printMedia(ofstream& outFile) = 0;
    void printMedia();

    // Static function to print counts
    static void printCounts(ofstream& outFile);
};

class Movie : public Media {
private:
    vector<string> stars;

public:
    // Constructor
    Movie(char type, string title, string name, int rating, string genre, int length, int year, vector<string> stars);

    // Accessors and Mutators
    vector<string> getStars() { return stars; }
    void setStars(vector<string> stars) { this->stars = stars; }

    // Print function override
    void printMedia(ofstream& outFile) override;

};

class Book : public Media {
private:
    int weeksNYT;

public:
    // Constructor
    Book(char type, string title, string name, int rating, string genre, int length, int year, int weeksNYT);

    // Accessors and Mutators
    int getWeeks() { return weeksNYT; }
    void setWeeks(int weeks) { weeksNYT = weeks; }

    // Print function override
    void printMedia(ofstream& outFile) override;
};

class Song : public Media {
private:
    bool top40;

public:
    // Constructor
    Song(char type, string title, string name, int rating, string genre, int length, int year, bool top40);

    // Accessors and Mutators
    bool getTop40() { return top40; }
    void setTop40(bool val) { top40 = val; }

    // Print function override
    void printMedia(ofstream& outFile) override;
};