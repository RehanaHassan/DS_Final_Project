#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;
class Graph
{
private:
    unordered_map<string, unordered_set<string>> adjacencyList;

public:
    void addUser(const string& username);
    void follow(const string& follower, const string& followee);
    void unfollow(const string& follower, const string& followee);
    void displayFollowers(const string& username);
};
