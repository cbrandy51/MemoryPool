#ifndef POOL
#define POOL

#include <cstddef>
#include <cassert>
#include <new>
#include <list>
#include <iostream>

class Pool
{
	// Data Members
	char* free_list;
	char** pool;
	size_t blocks;
	size_t eSize;
	size_t bSize;
	size_t free;
	size_t active;
public:
	// Purpose: Parameterized constructor for the memory pool
	// Parameters: Two size_t constants
	// Returns: None
	// -----------------------------------------------------------------
	Pool(size_t elemSize, size_t blockSize = 5);

	// Purpose: Default destructor for the memory pool
	// Parameters: None
	// Returns: None
	// -----------------------------------------------------------------
	~Pool();

	// Deleting the copy constructor and assignment operator
	Pool(const Pool&) = delete;
	Pool& operator= (const Pool&) = delete;

	// Purpose: Returns the first memory location pointed to by the free list
	// Parameters: None
	// Returns: Void pointer
	// -------------------------------------------------------------------------
	void* allocate();
	
	// Purpose: Frees up the passed in memory location and adds it to the free list
	// Parameters: Void pointer
	// Returns: None
	// -------------------------------------------------------------------------------
	void deallocate(void*);

	// Purpose: Prints out all necessary things about the memory pool
	// Parameters: None
	// Returns: None
	// -----------------------------------------------------------------
	void profile();

	// Purpose: Links all the blocks together forming a list of free cells
	// Parameters: None
	// Returns: None
	// ---------------------------------------------------------------------
	void Pool::init_block();

	// Purpose: Dynamically expands the memory pool to hold an increasing number of blocks
	// Parameters: None
	// Returns: Reference to a char pointer
	// ---------------------------------------------------------------------------------------
	char*& Pool::expand();
};

#endif