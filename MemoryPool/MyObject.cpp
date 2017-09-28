#include "MyObject.h"
using namespace std;

Pool MyObject::pool{ sizeof(MyObject) };

ostream& operator << (ostream& out, const MyObject& stuff) {
	return out << '{' << stuff.id << ',' << stuff.name << '}';
}