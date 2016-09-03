#include <vector>
#include <iostream>

struct Test {
	int x;
	int y; 
};

int main() {

	Test josh[5];
	for (int i = 0; i < 5; i++ ){
		Test a = {1+i,1+i};
		josh[i] = a;
	}

	for ( Test i : josh ){
		std::cout << i.x << std::endl;
	}
	
}
