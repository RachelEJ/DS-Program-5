/*
Student Name: Rachel Jordan
Student NetID: rej168
Compiler: Visual Studio
Program Description: Program that manages user ids, home directories, and passwords in the form of a hash table
*/

#pragma once
#include <string>
using std::string;

// User Class
class User
{
public: 
	string userID;
	string homeDirectory;
	string password;
	bool empty;
	bool modified;

	// constructors
	User() : userID(""), homeDirectory(""), password(""), empty(true), modified(false) {}
	User(bool empty) : userID(""), homeDirectory(""), password(""), empty(empty), modified(false) {}
	User(string userID) : userID(userID), homeDirectory(""), password(""), empty(false), modified(true) {}
	User(string userID, string password) : userID(userID), homeDirectory(userID), password(password), empty(false), modified(true) {}
	User(string userID, string homeDirectory, string password) : userID(userID), homeDirectory(homeDirectory), password(password), empty(false), modified(true) {}

};