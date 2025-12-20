#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "Social.h"
using namespace std;

void Graph::addUser(const string& username)
{
    if (adjacencyList.find(username) != adjacencyList.end())
    {
        cout << "User '" << username << "' already exists." << endl;
        return;
    }
    adjacencyList[username] = {};
    cout << "User '" << username << "' added." << endl;
}

void Graph::follow(const string& follower, const string& followee)
{
    if (adjacencyList.find(follower) == adjacencyList.end() || adjacencyList.find(followee) == adjacencyList.end()) {
        cout << "One or both users do not exist." << endl;
        return;
    }
    adjacencyList[follower].insert(followee);
    cout << follower << " is now following " << followee << "." << endl;
}

void Graph::unfollow(const string& follower, const string& followee)
{
    if (adjacencyList.find(follower) == adjacencyList.end() || adjacencyList.find(followee) == adjacencyList.end())
    {
        cout << "One or both users do not exist." << endl;
        return;
    }
    if (adjacencyList[follower].erase(followee) == 0) {
        cout << follower << " is not following " << followee << "." << endl;
    }
    else {
        cout << follower << " unfollowed " << followee << "." << endl;
    }
}

void Graph::displayFollowers(const string& username)
{
    if (adjacencyList.find(username) == adjacencyList.end()) {
        cout << "User '" << username << "' does not exist." << endl;
        return;
    }
    cout << "Users followed by '" << username << "': ";
    for (const auto& followee : adjacencyList[username]) {
        cout << followee << ", ";
    }
    cout << endl;
}
