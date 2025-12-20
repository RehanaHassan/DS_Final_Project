#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>
#include "Users.h"
#include "Social.h"
#include "Repository.h"
using namespace std;

void RepositoryManager::deleteTree(TreeNode* node)
{
    if (node == nullptr)
        return;
    for (TreeNode* child : node->children)
        deleteTree(child);
    delete node;
}
void RepositoryManager::createRepository(string name, string parentName = "")
{

    TreeNode* newNode = new TreeNode(name);
    if (parentName.empty() || root == nullptr)
    {
        root = newNode;
    }
    else {
        TreeNode* parent = findRepository(parentName, root);
        if (parent != nullptr)
        {
            parent->children.push_back(newNode);
            newNode->parent = parent;
        }
        else
        {
            cout << "Parent repository not found!" << endl;
            delete newNode;
        }
    }
}
TreeNode* RepositoryManager::findRepository(string name, TreeNode* node)
{
    if (node == nullptr)
        return nullptr;
    if (node->repositoryName == name)
        return node;
    for (TreeNode* child : node->children)
    {
        TreeNode* found = findRepository(name, child);
        if (found != nullptr)
            return found;
    }
    return nullptr;
}
void  RepositoryManager::deleteRepository(string name)
{
    TreeNode* nodeToDelete = findRepository(name, root);
    if (nodeToDelete != nullptr)
    {
        if (nodeToDelete->parent != nullptr)
        {
            auto it = nodeToDelete->parent->children.begin();
            while (it != nodeToDelete->parent->children.end())
            {
                if (*it == nodeToDelete)
                {
                    it = nodeToDelete->parent->children.erase(it);
                    break;
                }
                else
                {
                    ++it;
                }
            }
        }
        else
        {
            root = nullptr;
        }
        deleteTree(nodeToDelete);
        cout << "Repository '" << name << "' deleted successfully!" << endl;
    }
    else
    {
        cout << "Repository not found!" << endl;
    }
}
void RepositoryManager::addCommit(string repositoryName, int commitId, string message)
{
    TreeNode* node = findRepository(repositoryName, root);
    if (node != nullptr)
    {
        CommitNode* newCommit = new CommitNode(commitId, message);
        newCommit->next = node->commitsHead;
        node->commitsHead = newCommit;
        cout << "Commit added to repository '" << repositoryName << "' successfully!" << endl;
    }
    else {
        cout << "Repository not found!" << endl;
    }
}
void RepositoryManager::addFile(string repositoryName, string fileName)
{
    TreeNode* node = findRepository(repositoryName, root);
    if (node != nullptr) {
        FileNode* newFile = new FileNode(fileName);
        newFile->next = node->filesHead;
        node->filesHead = newFile;
        cout << "File added to repository '" << repositoryName << "' successfully!" << endl;
    }
    else {
        cout << "Repository not found!" << endl;
    }
}
void RepositoryManager::display()
{
    if (root == nullptr) {
        cout << "No repositories found!" << endl;
        return;
    }
    queue <TreeNode*> q;
    q.push(root);
    cout << "\n>>>> Repository Details <<<<" << endl;
    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        cout << " Repository Name: ";
        cout << current->repositoryName << endl;
        cout << "Commits:" << endl;
        CommitNode* commit = current->commitsHead;
        while (commit != nullptr) {
            cout << "  ID: " << commit->commitId << ", Message: " << commit->message << endl;
            commit = commit->next;
        }
        cout << "Files:" << endl;
        FileNode* file = current->filesHead;
        while (file != nullptr) {
            cout << "  " << file->fileName << endl;
            file = file->next;
        }
        for (TreeNode* child : current->children)
            q.push(child);
        cout << endl;
    }
}
void RepositoryManager::saveToFile(string filename)
{
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open file for writing!" << endl;
        return;
    }
    saveHelper(root, file);
    file.close();
    cout << "Repositories saved to file '" << filename << "' successfully!" << endl;
}
void RepositoryManager::saveHelper(TreeNode* node, ofstream& file) {
    if (node == nullptr)
        return;
    file << node->repositoryName << endl;
    CommitNode* commit = node->commitsHead;
    while (commit != nullptr) {
        file << "C:" << commit->commitId << ":" << commit->message << endl;
        commit = commit->next;
    }
    FileNode* fileNode = node->filesHead;
    while (fileNode != nullptr) {
        file << "F:" << fileNode->fileName << endl;
        fileNode = fileNode->next;
    }
    for (TreeNode* child : node->children)
        saveHelper(child, file);
}
void RepositoryManager::loadFromFile(string filename)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open file for reading!" << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            if (line[0] == 'C') {
                stringstream ss(line.substr(2));
                int commitId;
                string message;
                char delimiter;
                ss >> commitId >> delimiter;
                getline(ss, message);
                addCommit(lastRepositoryName, commitId, message);
            }
            else if (line[0] == 'F') {
                addFile(lastRepositoryName, line.substr(2));
            }
            else {
                createRepository(line);
                lastRepositoryName = line;
            }
        }
    }
    file.close();
    cout << "Repositories loaded from file '" << filename << "' successfully!" << endl;
}