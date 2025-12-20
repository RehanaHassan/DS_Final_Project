#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

class CommitNode
{
public:
    int commitId;
    string message;
    CommitNode* next;
    CommitNode(int id, string msg)
    {
        commitId = id;
        message = msg;
        next = nullptr;
    };
};
class FileNode
{
public:
    string fileName;
    FileNode* next;
    FileNode(string name)
    {
        fileName = name;
        next = nullptr;
    }
};
class TreeNode
{
public:
    string repositoryName;
    TreeNode* parent;
    vector<TreeNode*> children;
    CommitNode* commitsHead;
    FileNode* filesHead;
    TreeNode(string name, TreeNode* par = nullptr)
    {
        repositoryName = name;
        parent = par;
        commitsHead = nullptr;
        filesHead = nullptr;
    }
};
class RepositoryManager
{
private:
    TreeNode* root;
    void deleteTree(TreeNode* node);
    string lastRepositoryName;

public:
    RepositoryManager()
    {
        root = nullptr;
    }
    void createRepository(string name, string parentName);
    TreeNode* findRepository(string name, TreeNode* node);
    void deleteRepository(string name);
    void addCommit(string repositoryName, int commitId, string message);
    void addFile(string repositoryName, string fileName);
    void display();
    void saveToFile(string filename);
    void saveHelper(TreeNode* node, ofstream& file);
    void loadFromFile(string filename);

};


