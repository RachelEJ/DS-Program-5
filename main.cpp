/*
Student Name: Rachel Jordan
Student NetID: rej168
Compiler: Visual Studio
Program Description: Program that manages user ids, home directories, and passwords in the form of a hash table
*/

#include <iostream>
#include <ostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <string>
#include "hash.h"
#include "user.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::istream;
using std::ifstream;
using std::ofstream;
using std::stringstream;

// Read PWD File Function
void readFile(istream& is, bool isFile, Hash& userList, int primes[])
{
	string line;
	string index;
	string user;
	string home;
	string pass;

	// parses the info in the file
	while (true)
	{
		if (isFile && is.eof()) return;
		getline(is, line);
		stringstream ss(line);
		if (getline(ss, user, ' '))
		{
			if (getline(ss, home, ' '))
			{
				if (getline(ss, pass))
				{
					// creates a user with the info and adds it to the hash table
					User temp(user, home, pass);
					userList.insertUser(temp, primes);
				}
			}
		}
	}
}

// Save Password File Function
void savePwd(Hash &userList, ofstream &of, string fileName)
{
	// creates file with the name entered
	of.open(fileName);
	if (of.is_open())
	{
		// calls the print function
		cout << "File successfully saved" << endl << endl;
		userList.print(of);
	}
	// in case it doesn't open correctly
	else
	{
		cout << "Failed to open the file" << endl << endl;
	}
	of.close();
}

// The huge parsing function
void readLines(istream& is, Hash &userList, bool isFile)
{
	string line;
	string cmd;
	string arg1;
	string arg2;
	// a list of 12 primes that could potentially be the hash table's size
	int primes[] = { 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 102877 };

	while (true)
	{
		if (isFile && is.eof()) return;
		if (isFile == false)
		{
			cout << ">> ";
		}
		getline(is, line);
		stringstream ss(line);
		getline(ss, cmd, ' ');
		if (cmd == "exit") return;

		// Load Command
		if (cmd == "load")
		{
			ifstream inFile;
			if (!getline(ss, arg1, ' '))
			{
				cout << "You must enter a file to open. Please try again" << endl << endl;
			}
			else
			{
				// if no keyword "pwd" then opens a command file
				if (!getline(ss, arg2))
				{
					cout << "Attempting to open file..." << endl << endl;
					inFile.open(arg1);
					if (inFile.is_open())
					{
						readLines(inFile, userList, true);
					}
					else
					{
						cout << "Failed to open the file" << endl << endl;
					}
					inFile.close();
				}

				// if a "pwd" keyword then opens a pwd file
				else
				{
					if (arg1 == "pwd")
					{
						cout << "Attempting to open file..." << endl << endl;
						inFile.open(arg2);
						if (inFile.is_open())
						{
							ifstream file;
							readFile(inFile, true, userList, primes);
							cout << "Successfully loaded the table" << endl << endl;
						}
						else
						{
							cout << "Failed to load the table" << endl << endl;
						}
						inFile.close();
					}
					else
					{
						cout << "You must use the keyword \"pwd\" to use this command" << endl << endl;
					}
				}
			}
		}

		// Save Command
		if (cmd == "save")
		{
			// makes sure the user's inputs are valid
			if (!getline(ss, arg1, ' '))
			{
				cout << "You must enter the keyword \"pwd\" to use this command. Please try again" << endl << endl;
			}
			else if (arg1 != "pwd")
			{
				cout << "You must enter the keyword \"pwd\" to use this command. Please try again" << endl << endl;
			}
			else
			{
				if (!getline(ss, arg2))
				{
					cout << "You must enter a file name to save to. Please try again" << endl << endl;
				}
				else
				{
					// if everything works out, it calls the Save Password File Function
					ofstream of;
					savePwd(userList, of, arg2);
				}
				
			}
		}

		// New User Function
		if (cmd == "new")
		{
			// checking for correct input
			if (!getline(ss, arg1, ' '))
			{
				cout << "You must enter a user name to use this command. Please try again" << endl << endl;
			}
			else
			{
				if (!getline(ss, arg2))
				{
					cout << "You must enter a password to use this command. Please try again" << endl << endl;
				}
				else
				{
					// takes input for arg1 and makes the directory into with it
					string homeDirectory = "/users/" + arg1;
					User temp(arg1, homeDirectory, arg2);

					// inserts the new user info into the table
					if (userList.insertUser(temp, primes) == 0)
					{
						cout << "Unable to add that user. Please try again" << endl << endl;
					}
					else
					{
						cout << "User added successfully" << endl << endl;
					}
				}
			}
		}

		// Remove User Command
		if (cmd == "remove")
		{
			// checks input
			if (!getline(ss, arg1))
			{
				cout << "You must enter a user to remove. Please try again" << endl << endl;
			}
			else
			{
				// removes the user based on the string inputted
				if (userList.removeUser(arg1) == 0)
				{
					cout << "Unable to remove that user. Please try again" << endl << endl;
				}
				else
				{
					cout << "User removed successfully" << endl << endl;
				}
			}
		}

		// Clear Table Command
		if (cmd == "clear")
		{
			// calls clear
			userList.clear();
			cout << "The table has been cleared!" << endl << endl;
		}

		// Display Command
		if (cmd == "display")
		{
			// displays the whole thing
			if (!getline(ss, arg1))
			{
				userList.displayWhole();
			}

			// displays only the specified user
			else
			{
				userList.displayUser(arg1);
			}
		}

		// Verify UserID and Password Command
		if (cmd == "verify")
		{
			// checking input again
			if (!getline(ss, arg1, ' '))
			{
				cout << "You must enter a user name to verify. Please try again" << endl << endl;
			}
			else
			{
				if (!getline(ss, arg2))
				{
					cout << "You must enter a password to verify. Please try again" << endl << endl;
				}
				else
				{
					// calls the Verify UserID/Password Function
					if (userList.verify(arg1, arg2) == 0)
					{
						cout << "Validation has failed" << endl << endl;
					}
					else
					{
						cout << "User successfully validated" << endl << endl;
					}
				}
			}
		}

		// Change Home Directory Command
		if (cmd == "home")
		{
			// did you know we're checking input again?
			if (!getline(ss, arg1, ' '))
			{
				cout << "You must enter a user. Please try again" << endl << endl;
			}
			else
			{
				if (!getline(ss, arg2))
				{
					cout << "You must enter a home directory. Please try again" << endl << endl;
				}
				else
				{
					// calls the Change Home Directory Function
					if (userList.home(arg1, arg2) == 0)
					{
						cout << "Failed to change the home directory. Please try again" << endl << endl;
					}
					else
					{
						cout << "Successfully changed the home directory" << endl << endl;
					}
				}
			}
		}

		// Change Password Command
		if (cmd == "passwd")
		{
			// checking input yet again
			if (!getline(ss, arg1, ' '))
			{
				cout << "You must enter a user. Please try again" << endl << endl;
			}
			else
			{
				if (!getline(ss, arg2))
				{
					cout << "You must enter a password. Please try again" << endl << endl;
				}
				else
				{
					// calls the Change Password Function
					if (userList.passwd(arg1, arg2) == 0)
					{
						cout << "Failed to change the password. Please try again" << endl << endl;
					}
					else
					{
						cout << "Successfully changed the password" << endl << endl;
					}
				}
			}
		}
	}
}

// the very empty main function
int main()
{
	
	Hash userList;
	readLines(cin, userList, false);

	return 0;
}