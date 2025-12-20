#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>
#include <windows.h>
#include "Repository.h"
#include "Users.h"
#include "Social.h"
using namespace std;


int main()
{
    system("color 70");

    cout << R"(
 <>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>
 ||    _______   _____    _____    _   _    _   _    ______   ||      
 ||   /  ____|  |_   _|  |_   _|  | | | |  | | | |  |  _   |  ||     
 ||  |  |  __     | |      | |    | |_| |  | | | |  | |_) /   ||    
 ||  |  | |_ |    | |      | |    |  _  |  | | | |  |  _  \   ||  
 ||  |  |__| |   _| |_     | |    | | | |  | |_| |  | |_)  |  ||    
 ||   \______|  |_____|    |_|    |_| |_|   \___/   |_____/   || 
  =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=                                                         
)" << endl;

    UserHashTable userTable(10);
    userTable.loadFromFile();
    cout << "||||||||||| Welcome to GITHUB |||||||||||" << endl;
    cout << "\n1- Registeration " << endl;
    cout << "2-Login" << endl;
    cout << "0- Exit" << endl;
    int c;
    cout << ">>- Enter your choice: ";
    cin >> c;
    string name;
    string password;
    if (c == 1)
    {
        cout << "Enter your name: ";
        cin >> name;
        cout << "Enter your password: ";
        cin >> password;
        userTable.registerUser(name, password);
    }
    else if (c == 2)
    {
        cout << "Enter your name: ";
        cin >> name;
        cout << "Enter your password: ";
        cin >> password;
        if (userTable.loginUser(name, password))
        {
            cout << ">>>>>|||| Welcome ||||<<<<<" << endl;
            cout << "1- Repositories Management" << endl;
            cout << "2- Social Connections" << endl;
            cout << ">>- Enter your choice: ";
            cin >> c;
            if (c == 1)
            {
                RepositoryManager manager;

                int choice;
                do {
                    cout << "--------------------------------------------------" << endl;
                    cout << "|=<>=<>=<> Repository Management System <>=<>=<>=|" << endl;
                    cout << "--------------------------------------------------" << endl;
                    cout << "1- Create Repository" << endl;
                    cout << "2- Add Commit" << endl;
                    cout << "3- Add File" << endl;
                    cout << "4- Delete Repository" << endl;
                    cout << "5- Display Repositories" << endl;
                    cout << "6- Save Repositories to File" << endl;
                    cout << "7- Load Repositories from File" << endl;
                    cout << "8- Exit" << endl;
                    cout << ">>- Enter your choice: ";
                    cin >> choice;

                    string name, parentName, message, fileName, filename;
                    int commitId;
                    switch (choice) {
                    case 1:
                        int num;
                        cout << "Enter repository name: ";
                        cin >> name;
                        cout << "Is there any Parent Repository? " << endl;
                        cout << "1- Yes" << endl;
                        cout << "2- No" << endl;
                        cout << ">>- Enter your choice: ";
                        cin >> num;
                        if (num == 1)
                        {
                            cout << "Enter parent repository name: ";
                            cin >> parentName;
                        }
                        else if (num == 2)
                        {
                            cout << "Repository is created!" << endl;
                        }
                        manager.createRepository(name, parentName);
                        break;
                    case 2:
                        cout << "Enter repository name: ";
                        cin >> name;
                        cout << "Enter commit ID: ";
                        cin >> commitId;
                        cout << "Enter commit message: ";
                        cin.ignore();
                        getline(cin, message);
                        manager.addCommit(name, commitId, message);
                        break;
                    case 3:
                        cout << "Enter repository name: ";
                        cin >> name;
                        cout << "Enter file name: ";
                        cin >> fileName;
                        manager.addFile(name, fileName);
                        break;
                    case 4:
                        cout << "Enter repository name to delete: ";
                        cin >> name;
                        manager.deleteRepository(name);
                        break;
                    case 5:
                        cout << "|| = < >= < >= <> Display Repositories <>=<>=<>= ||" << endl;
                        manager.display();
                        cout << "=================================" << endl;
                        break;
                    case 6:
                        cout << "Enter filename to save: ";
                        cin >> filename;
                        manager.saveToFile(filename);
                        break;
                    case 7:
                        cout << "Enter filename to load: ";
                        cin >> filename;
                        manager.loadFromFile(filename);
                        break;
                    case 8:
                        cout << "___________________________________" << endl;
                        cout << "|||||||||| GOOD BYE :) ||||||||||||" << endl;
                        cout << "-----------------------------------" << endl;
                        break;
                    default:
                        cout << "Invalid choice! Please enter a number from 1 to 8." << endl;
                    }
                } while (choice != 8);


            }
            else if (c==2)
            {
                Graph socialNetwork;

                while (true)
                {
                    cout << "_______________________________________________" << endl;
                    cout << "|=<>=<>=<> Social Network Management  <>=<>=<>=|" << endl;
                    cout << "-----------------------------------------------" << endl;
                    cout << "1- Add User" << endl;
                    cout << "2- Follow User" << endl;
                    cout << "3- Unfollow User" << endl;
                    cout << "4- Display Followed Users" << endl;
                    cout << "5- Exit" << endl;
                    cout << ">>- Enter your choice: ";

                    int choice;
                    cin >> choice;

                    string username, follower, followee;

                    switch (choice) {
                    case 1:
                        cout << "Enter username: ";
                        cin >> username;
                        socialNetwork.addUser(username);
                        break;
                    case 2:
                        cout << "Enter follower username: ";
                        cin >> follower;
                        cout << "Enter followee username: ";
                        cin >> followee;
                        socialNetwork.follow(follower, followee);
                        break;
                    case 3:
                        cout << "Enter follower username: ";
                        cin >> follower;
                        cout << "Enter followee username: ";
                        cin >> followee;
                        socialNetwork.unfollow(follower, followee);
                        break;
                    case 4:
                        cout << "Enter username: ";
                        cin >> username;
                        socialNetwork.displayFollowers(username);
                        cout << "=================================" << endl;
                        break;
                    case 5:
                        cout << "___________________________________" << endl;
                        cout << "|||||||||| GOOD BYE :) ||||||||||||" << endl;
                        cout << "-----------------------------------" << endl;
                        return 0;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                    }
                }
            }
        }
        else if (c == 2)
        {
            cout << "Error: Invalid username and password!" << endl;
        }
    }
    else if (c == 0)
    {
        cout << "___________________________________" << endl;
        cout << "|||||||||| GOOD BYE :) ||||||||||||" << endl;
        cout << "-----------------------------------" << endl;
        return 0;
    }
    else
    {
        cout << "Invalid Choice!!!" << endl;
    }


    return 0;
}
