#include <iostream>
#include "MyMap.h"

using namespace std;

int main()
{
	MyMap<char *> mp;

	mp.Insert("ƒCƒ“ƒT[ƒg1\n", 0);
	mp.Insert("ƒCƒ“ƒT[ƒg2\n", 1);
	mp.Insert("ƒCƒ“ƒT[ƒg3\n", 2);
	mp.Insert("ƒCƒ“ƒT[ƒg4\n", 3);
	mp.Insert("ƒCƒ“ƒT[ƒg5\n", 4);
	
	cout << mp.Get(0);
	cout << mp.Get(1);
	cout << mp.Get(2);
	cout << mp.Get(3);
	cout << mp.Get(4);

	mp.Delete(0);
	mp.Delete(1);
	mp.Delete(2);
	mp.Delete(3);
	mp.Delete(4);

	mp.Insert("OQO\n", 0);
	mp.Insert("OQO2\n", 1);
	mp.Insert("OQO3\n", 2);
	mp.Insert("OQO4\n", 3);
	mp.Insert("OQO5\n", 4);
	
	cout << mp.Get(0);
	cout << mp.Get(1);
	cout << mp.Get(2);
	cout << mp.Get(3);
	cout << mp.Get(4);

	mp.Delete(0);
	mp.Delete(1);
	mp.Delete(2);
	mp.Delete(3);
	mp.Delete(4);



	return 0;
}