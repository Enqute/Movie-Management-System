#pragma once

#include <string>

struct Date
{
    int Date;
    int Month;
    int Year;
};

enum class MovieType
{
    ACTION = 1, ADVENTURE, COMMEDY, DRAMA,
    FANTANSY, HORROR, MYSTERY, ROMANCE,
    SCIFI, SPORTS, THRILLER, WESTERN
};

enum class Language
{
    AMHARIC = 1, ARABIC, CHINESE, KOREAN, ENGLISH, FRENCH, HINDU, SPANISH
};

struct Movie
{
    int ID;
    std::string Title;
    float Rate;
    float Price;
    float Length;

    MovieType Genre;
    Date ReleasedDate;
    Language Lang;
};

struct Node
{
    Movie Movie;
    Node* Next;
    Node* Prev;
};

void AddFirst(const std::string& filepath);
void AddFirst(Movie movie);
void AddLast(Movie movie);
void InsertAtIndex(int index, Movie movie);
void InsertById(Movie movie, bool before, int ID);
void InsertByTitle(Movie movie, bool before, std::string title);

void RemoveFirst();
void RemoveLast();
void RemoveById(int ID);
void RemoveByTitle(std::string title);
void RemoveByIndex(int index);
void Remove(Movie movie);
void RemoveByLang(std::string lang);
void RemoveByGenre(std::string genre);
void RemoveByDate(std::string date);
void RemoveByMinPrice();
void RemoveByMinRate();
void RemoveByMaxPrice();
void RemoveByMaxRate();

Movie GetById(int ID);
Movie GetByTitle(std::string title);
Movie GetByIndex(int index);
Movie GetByMinPrice();
Movie GetByMinRating();
Movie GetByMaxPrice();
Movie GetByMaxRating();
float GetByAvePrice();
float GetByAveLength();
Movie* GetByLang(std::string lang);
Movie* GetByGenre(std::string genre, int top);
Movie* GetByDate(std::string releasedDate, int top);
Movie* GetByPrice(float price, int top);
Movie* GetByRate(float rate, int top);
Movie* GetByLength(float length, int top);

void SaveStatus(const std::string& filepath);

int CountByRate(float rate);
int CountByPrice(float price);
int CountByLength(float length);
int CountByGenre(std::string genre);
int CountByDate(std::string date);
int CountByLang(std::string language);

int GetSize();

void UpdateId(int oldID, int newID);
void UpdateTitle(int oldID, std::string newTitle);
void UpdatePrice(int oldID, float newPrice);
void UpdateLength(int oldID, float newLength);
void UpdateRate(int oldID, float newRate);
void UpdateGenre(int oldID, std::string newGenre);
void UpdateLang(int oldID, std::string newLang);
void UpdateDate(int oldID, std::string newDate);

void SortById();
void SortByTitle();
void SortByPrice();
void SortByLength();
void SortByRate();
void SortByGenre();
void SortByLang();
void SortByDate();

void TopByTitle(size_t size);
void TopByPrice(size_t size);
void TopByRate(size_t size);
void TopByDate(size_t size);

void DisplayForward();
void DisplayBackward();

inline bool IsEmpty();
int IndexOf(int movieID);
int IndexOf(Movie movie);
bool Contains(int movieID);

void printNode(Node node);
std::string toUpper(const char* string);

Date stringToDate(std::string string);
MovieType stringToGenre(const char* string);
Language stringToLang(const char* string);

std::string dateToString(Date date);
std::string genreToString(MovieType genre);
std::string langToString(Language lang);
