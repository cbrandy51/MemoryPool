// File/Project Prolog
// Name: Chase Brandner
#ifndef MY_OBJECT
#define MY_OBJECT

#include <cstddef>
#include <cassert>
#include <iostream>
#include <string>
#include "Pool.h"

class MyObject
{
private:
	// Data Members
	int id;
	std::string name;
	static Pool pool;

	// Purpose: Private parameterized constructor for the MyObject class
	// Parameters: Integer value, String value
	// Returns: None
	// ---------------------------------------------------------------------
	MyObject(int i, const std::string& nm) : name(nm) 
	{
		id = i;
	};
	
	// Purpose: New operator overload that gets a memory location from the memory pool
	// Parameters: Size_t constant
	// Returns: Void pointer
	// -----------------------------------------------------------------------------------
	static void* operator new (std::size_t)
	{
		return pool.allocate();
	};

	// Deleting the copy constructor and assignment operator
	MyObject(const MyObject&) = delete;
	MyObject& operator= (const MyObject&) = delete;
public:
	// Purpose: Basic factory function to create MyObject objects
	// Parameters: Integer value, String value
	// Returns: MyObject pointer
	// -----------------------------------------------------------------
	static MyObject* create(int id, const std::string& name)
	{
		return new MyObject(id, name);
	};

	// Purpose: Static function to the profile of the memory pool
	// Parameters: None
	// Returns: None
	// -----------------------------------------------------------------
	static void profile() {
		pool.profile();
	};

	// Purpose: Delete operator overload to pass a memory location back to the memory pool
	// Parameters: Void pointer
	// Returns: None
	// ----------------------------------------------------------------------------------------
	static void operator delete (void* oldObj) {
		pool.deallocate(oldObj);
	};

	// Purpose: Out file stream operator overload used to printing out MyObject data members
	// Parameters: Ostream object reference, constant MyObject reference
	// Returns: Ostream object reference
	// -----------------------------------------------------------------------------------------
	friend std::ostream& operator << (std::ostream& out, const MyObject& stuff);
};

#endif