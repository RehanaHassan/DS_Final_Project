#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
using namespace std;
class UserNode
{
public:
    string username;
    string password;
    UserNode* next;

    UserNode(string uname, string pword)
    {
        username = uname;
        password = pword;
    }
};

class UserHashTable
{
private:
    UserNode** table;
    int capacity;
    int hashFunction(string key);
    void saveToFile();
    void saveUsername();

public:
    UserHashTable(int size);
    ~UserHashTable();
    bool registerUser(string username, string password);
    bool loginUser(string username, string password);
    void loadFromFile();
};
