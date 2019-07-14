//============================================================================
// Name        : DISTRICTS.cpp
// Author      : Samuel Copping
// Version     :
// Copyright   : 
// Description : A procedurally generated base building game.
//============================================================================

#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
	cout << "Welcome to DISTRICTS." << endl << endl;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << "# ";
		}

		cout << endl;
	}

	cout << endl << "Here's a starting map, sort of." << endl;

	return 0;
}
