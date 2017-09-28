#include "Pool.h"

#ifdef NDEBUG
#undef NDEBUG
#endif

using namespace std;


Pool::Pool(size_t elemSize, size_t blockSize)
{
	std::cout << "Initializing a pool with element size " << elemSize <<" and block size " << blockSize << endl << endl;
	
	//assert elemsize is at least as large as a char*
	assert(elemSize >= sizeof(char*));

	eSize = elemSize; 
	bSize = blockSize;

	blocks = 0;
	free = 0;
	active = 0;

	pool = nullptr;
	free_list = nullptr;
}


Pool::~Pool()
{
	std::cout << "Deleting " << blocks << " blocks" << std::endl;

	for (size_t i = 0; i < blocks; i++)
	{
		delete[] pool[i];
	}
	delete[] pool;
}

void* Pool::allocate() {
	if (free_list == nullptr)
		init_block();

	// assert that free_list isn't null
	assert(free_list != nullptr);

	char* temp = free_list;
	char** temp2 = reinterpret_cast<char**>(free_list);
	free_list = *temp2;

	active++;
	free--;

	std::cout << "Cell allocated at " << static_cast<void*>(temp) << std::endl;
	return temp;
}

void Pool::deallocate(void* thing) {
	char** temp = reinterpret_cast<char**>(thing);

	// assert that the pointer isn't null
	assert(thing != nullptr);
	// assert that active is at least one
	assert(active > 0);

	*temp = free_list;
	free_list = static_cast<char*>(thing);

	std::cout << "Cell deallocated at " << static_cast<void*>(free_list) << std::endl;

	active--;
	free++;
}

void Pool::profile() {
	std::cout << "Live Cells: " << active << ", Free Cells: " << free << std::endl;
	std::cout << "Free List:" << std::endl;

	char* current = free_list;

	while (current)
	{
		char** temp = reinterpret_cast<char**>(current);
		cout << static_cast<void*>(current) << std::endl;
		current = *temp;
	}
	std::cout << std::endl;
}

void Pool::init_block() {
	char* temp = expand();

	free_list = temp;

	std::cout << "Expanding pool..." << std::endl;
	std::cout << "Linking cells starting at " << static_cast<void*>(free_list) << std::endl;

	char* current = free_list;
	char* target = current + eSize;

	std::cout << static_cast<void*>(current) << std::endl;

	for (size_t i = 0; i < bSize; i++)
	{
		if (i == bSize - 1)
			new (current) char*(nullptr);
		else 
		{
			new (current) char*(target);
			current = target;
			target += eSize;

			std::cout << static_cast<void*>(current) << std::endl;
		}
	}
	free += bSize;
	std::cout << std::endl;
}

char*& Pool::expand() {
	if (blocks == 0)
	{
		pool = new char*[blocks + 1];
		pool[blocks] = new char[bSize * eSize];

		return pool[blocks++];
	}
	else 
	{
		char** temp = new char*[blocks + 1];

		// need to fix third parameter?
		std::memcpy(&temp[0], &pool[0], (sizeof(char*) * blocks));

		delete[] pool;
		pool = temp;

		pool[blocks] = new char[bSize * eSize];

		return pool[blocks++];
	}
}