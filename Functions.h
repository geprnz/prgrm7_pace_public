#pragma once
#include <vector>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>

#include "Media.h"
using namespace std;

bool isDigits(const string& str1);
int  readMediaList(istream &i, ostream &o, vector<Media*> &m);

void printAllMedia(ofstream& outFile, vector<Media*> mediaLib);
void printAllMedia(ofstream& outFile, vector<Media*> mediaLib, int ratingVal);
void printAllMedia(ofstream& outFile, vector<Media*> mediaLib, string genre);

void printMovies(ofstream& outFile, vector<Media*> mediaLib);
void printMovies(ofstream& outFile, vector<Media*> mediaLib, int ratingVal);
void printMovies(ofstream& outFile, vector<Media*> mediaLib, string genre);

void printBooks(ofstream& outFile, vector<Media*> mediaLib);
void printBooks(ofstream& outFile, vector<Media*> mediaLib, int ratingVal);
void printBooks(ofstream& outFile, vector<Media*> mediaLib, string genre);

void printSongs(ofstream& outFile, vector<Media*> mediaLib);
void printSongs(ofstream& outFile, vector<Media*> mediaLib, int ratingVal);
void printSongs(ofstream& outFile, vector<Media*> mediaLib, string genre);

void printTotals(ofstream& outFile);

void createMedia(char mediaType, const vector<string>& commandTokens, vector<Media*>& myLib, ofstream& outErr, ofstream& outFile);
string joinTokens(const vector<string>& tokens);

void castLookup(string title, vector<Media*> myLib, ofstream& outFile);
void actorLookup(string name, vector<Media*> myLib, ofstream& outFile);
void nameLookup(string name, vector<Media*> myLib, ofstream& outFile);