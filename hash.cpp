/*
Student Name: Rachel Jordan
Student NetID: rej168
Compiler: Visual Studio
Program Description: Program that manages user ids, home directories, and passwords in the form of a hash table
*/

#include <iostream>
#include <ostream>
#include <iomanip>
#include <sstream>
#include <istream>
#include <fstream>
#include <string>
#include "hash.h"

using std::cin;
using std::cout;
using std::endl;
using std::left;
using std::setw;
using std::right;
using std::setfill;
using std::string;
using std::ostream;
using std::istream;
using std::ifstream;
using std::ofstream;
using std::stringstream;

// default constructor
Hash::Hash()
{
	hashTable = new User[23];
	size = 23;
	elements = 0;
}

// constructor with specific size
Hash::Hash(int length)
{
	hashTable = new User[length];
	size = length;
	elements = 0;
}

// destructor
Hash::~Hash()
{
	delete[] hashTable;
}

// getter for size
int Hash::getSize()
{
	return size;
}

// reallocate function except renamed resize because "resize" is shorter
// Here I would like to say that I based a lot of my code on the Zybooks section on hash tables. It isn't exactly like the Zybooks, but it is heavily inspired
void Hash::resize(int primes[])
{
	int bucket = 0;
	int oldSize = size;
	User* old = hashTable;

	// checks array of primes and picks the next highest for size
	for (int i = 0; i < 12; i++)
	{
		if (primes[i] > size)
		{
			size = primes[i];
			break;
		}
	}

	// sets hash table's new size
	hashTable = new User[size];
	elements = 0;

	// adds everything back into the new hash table
	while (bucket < oldSize)
	{
		if (old[bucket].empty == false)
		{
			insertUser(old[bucket], primes);
		}
		bucket++;
	}

	// deletes the old array
	delete[] old;
}

// takes a string and converts it into an integer based on ascii value
int Hash::convert(string user)
{
	int asciiVal = 0;
	// loops through each character and adds it
	for (int i = 0; i < user.size(); i++)
	{
		int val = user[i];
		asciiVal += val;
	}
	return asciiVal;
}

// Insert User Function
// Here I would like to say that I based a lot of my code on the Zybooks section on hash tables. It isn't exactly like the Zybooks, but it is heavily inspired
bool Hash::insertUser(User key, int primes[])
{
	// makes sure number of elements is less than half of size
	if (elements >= (size / 2))
	{
		resize(primes);
	}

	int i = 0;
	int bucketsProbed = 0;

	// figures out which bucket
	int bucket = convert(key.userID) % size;
	while (bucketsProbed < size)
	{
		// looks for an empty spot to insert user into
		if (hashTable[bucket].empty == true)
		{
			hashTable[bucket] = key;
			elements++;
			return true;
		}

		// checks if user already exists
		if (hashTable[bucket].userID == key.userID)
		{
			return false;
		}
		i++;
		bucket = (convert(key.userID) +  i * i) % size;
		bucketsProbed++;
	}
	return false;
}

// Remove User Function
// Here I would like to say that I based a lot of my code on the Zybooks section on hash tables. It isn't exactly like the Zybooks, but it is heavily inspired
bool Hash::removeUser(string key)
{
	int i = 0;
	int bucketsProbed = 0;

	// converts string to ascii integer
	int bucket = convert(key) % size;

	// searches hash table for correct bucket
	while ((hashTable[bucket].empty == false || hashTable[bucket].modified == true) && (bucketsProbed < size))
	{
		if ((hashTable[bucket].empty == false) && (hashTable[bucket].userID == key))
		{
			// sets all info to defaults
			hashTable[bucket].userID = "";
			hashTable[bucket].homeDirectory = "";
			hashTable[bucket].password = "";
			hashTable[bucket].empty = true;
			hashTable[bucket].modified = true;
			elements--;
			return true;
		}
		i++;
		bucket = (convert(key) + i * i) % size;
		bucketsProbed++;
	}
	return false;
}

// Display User Function
bool Hash::displayUser(string key)
{
	int i = 0;
	int bucketsProbed = 0;

	int bucket = convert(key) % size;

	// searches through hash table for correct bucket
	while ((hashTable[bucket].empty == false || hashTable[bucket].modified == true) && (bucketsProbed < size))
	{
		if ((hashTable[bucket].empty == false) && (hashTable[bucket].userID == key))
		{
			const char separator = ' ';
			const int index = 5;
			const int user = 15;
			const int homedir = 25;
			const int pwd = 4;

			// prints out table headers
			cout << "That user was found" << endl;
			cout << left << setw(index) << setfill(separator) << "Mod";
			cout << left << setw(user) << setfill(separator) << "User";
			cout << left << setw(homedir) << setfill(separator) << "Home Dir";
			cout << left << setw(pwd) << setfill(separator) << "Pwd";
			cout << endl;

			// prints out user info
			cout << left << setw(index) << setfill(separator) << bucket;
			cout << left << setw(user) << setfill(separator) << hashTable[bucket].userID;
			cout << left << setw(homedir) << setfill(separator) << hashTable[bucket].homeDirectory;
			if (hashTable[bucket].empty == false)
			{
				cout << left << setw(pwd) << setfill(separator) << "*****";
			}
			cout << endl << endl;
			return true;
		}
		i++;
		bucket = (convert(key) + i * i) % size;
		bucketsProbed++;
	}
	cout << "That user could not be found" << endl << endl;
	return false;
}

// Display Whole Table Function
void Hash::displayWhole()
{
	const char separator = ' ';
	const int index = 5;
	const int user = 15;
	const int homedir = 25;
	const int pwd = 6;

	// prints out table headers
	cout << "Displaying the user table..." << endl;
	cout << right << setw(index) << setfill(separator) << "Mod";
	cout << right << setw(user) << setfill(separator) << "User";
	cout << right << setw(homedir) << setfill(separator) << "Home Dir";
	cout << right << setw(pwd) << setfill(separator) << "Pwd";
	cout << endl;

	// prints out table info
	for (int i = 0; i < size; i++)
	{
		cout << right << setw(index) << setfill(separator) << i;
		if (hashTable[i].empty == false)
		{
			cout << right << setw(user) << setfill(separator) << hashTable[i].userID;
			cout << right << setw(homedir) << setfill(separator) << hashTable[i].homeDirectory;
			cout << right << setw(pwd) << setfill(separator) << "*";
		}
		if (hashTable[i].empty == true && hashTable[i].modified == true)
		{
			cout << right << setw(5) << setfill(separator) << "M";
		}
		cout << endl;
	}
	cout << endl;
}

// Clear Hash Table Function
void Hash::clear()
{
	// goes through hash table and sets all stuff back to default
	for (int i = 0; i < size; i++)
	{
		hashTable[i].userID = "";
		hashTable[i].homeDirectory = "";
		hashTable[i].password = "";
		hashTable[i].empty = true;
		hashTable[i].modified = false;
	}
	elements = 0;
	size = 23;
}

// Verify UserID and Password Function
bool Hash::verify(string vUser, string vPwd)
{
	int i = 0;
	int bucketsProbed = 0;

	int bucket = convert(vUser) % size;

	// searches through hash table for correct bucket
	while ((hashTable[bucket].empty == false || hashTable[bucket].modified == true) && (bucketsProbed < size))
	{
		if ((hashTable[bucket].empty == false) && (hashTable[bucket].userID == vUser))
		{
			// checks UserID and Password
			if (hashTable[bucket].password == vPwd)
			{
				return true;
			}
		}

		// increments stuff
		i++;
		bucket = (convert(vUser) + i * i) % size;
		bucketsProbed++;
	}
	return false;
}

// Change Home Directory Function
bool Hash::home(string hUser, string hHome)
{
	int i = 0;
	int bucketsProbed = 0;

	int bucket = convert(hUser) % size;

	// searches through hash table for correct bucket
	while ((hashTable[bucket].empty == false || hashTable[bucket].modified == true) && (bucketsProbed < size))
	{
		if ((hashTable[bucket].empty == false) && (hashTable[bucket].userID == hUser))
		{
			// changes actual home directory
			hashTable[bucket].homeDirectory = hHome;
			return true;
		}
		i++;
		bucket = (convert(hUser) + i * i) % size;
		bucketsProbed++;
	}
	return false;
}

// Change Password Function
bool Hash::passwd(string pUser, string pPwd)
{
	int i = 0;
	int bucketsProbed = 0;

	int bucket = convert(pUser) % size;

	// searches through hash table for correct bucket
	while ((hashTable[bucket].empty == false || hashTable[bucket].modified == true) && (bucketsProbed < size))
	{
		if ((hashTable[bucket].empty == false) && (hashTable[bucket].userID == pUser))
		{
			// changes the actual password
			hashTable[bucket].password = pPwd;
			return true;
		}
		i++;
		bucket = (convert(pUser) + i * i) % size;
		bucketsProbed++;
	}
	return false;
}

// outputs the contents of the hash table for the save function
void Hash::print(ostream &os)
{
	for (int i = 0; i < size; i++)
	{
		if (hashTable[i].empty != true)
		{
			os << hashTable[i].userID << " " << hashTable[i].homeDirectory << " " << hashTable[i].password << endl;
		}
	}
}