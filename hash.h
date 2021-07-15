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

#pragma once

class Hash
{
private:
	User* hashTable;
	int size;
	int elements;

public:

	// constructor/destructor
	Hash();
	Hash(int length);
	~Hash();

	// basic management functions
	int getSize();
	void resize(int primes[]);
	void print(ostream& os);

	// converting strings
	int convert(string user);

	// hash table functions
	bool insertUser(User key, int primes[]);
	bool removeUser(string key);
	bool displayUser(string key);
	void displayWhole();
	void clear();
	bool verify(string vUser, string vPwd);
	bool home(string hUser, string hHome);
	bool passwd(string pUser, string pPwd);
};