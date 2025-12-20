#include <string>
#include <iostream>
#include <fstream>
#include "Users.h"
#include <unordered_map>
#include <set>
using namespace std;
UserHashTable::UserHashTable(int size)
{
    capacity = size;
    table = new UserNode * [capacity];
    for (int i = 0; i < capacity; ++i)
        table[i] = nullptr;
    loadFromFile();
}

UserHashTable::~UserHashTable()
{
    saveToFile();
    saveUsername();
    for (int i = 0; i < capacity; ++i)
    {
        UserNode* current = table[i];
        while (current != nullptr)
        {
            UserNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] table;
}
int UserHashTable::hashFunction(string key)
{
    int hash = 0;
    for (char c : key)
        hash = (hash * 31 + c) % capacity;
    return hash;
}
void UserHashTable::loadFromFile()
{
    ifstream file("userdata.txt");
    if (file.is_open())
    {
        string username, password;
        while (file >> username >> password)
        {
            registerUser(username, password);
        }
        file.close();
    }
}
void UserHashTable::saveToFile()
{
    ofstream file("userdata.txt");
    if (file.is_open())
    {
        for (int i = 0; i < capacity; ++i)
        {
            UserNode* current = table[i];
            while (current != nullptr)
            {
                file << current->username << " " << current->password << std::endl;
                current = current->next;
            }
        }
        file.close();
    }
}
void UserHashTable::saveUsername()
{
    ofstream file("usernames.txt");
    if (file.is_open())
    {
        for (int i = 0; i < capacity; ++i)
        {
            UserNode* current = table[i];
            while (current != nullptr)
            {
                file << current->username << std::endl;
                current = current->next;
            }
        }
        file.close();
    }
}
bool UserHashTable::registerUser(string username, string password)
{
    int index = hashFunction(username);
    UserNode* newNode = new UserNode(username, password);
    if (table[index] == nullptr)
    {
        table[index] = newNode;
    }
    else
    {
        UserNode* current = table[index];
        while (current->next != nullptr)
        {
            if (current->username == username)
            {
                delete newNode;
                return false;
            }
            current = current->next;
        }
        current->next = newNode;
    }
    return true;
}
bool UserHashTable::loginUser(string username, string password)
{
    int index = hashFunction(username);
    UserNode* current = table[index];
    while (current != nullptr)
    {
        if (current->username == username && current->password == password)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}
