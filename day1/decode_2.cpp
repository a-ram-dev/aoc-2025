#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//global declarations
int count;

int decode(string direction, int change){
	//setup bounds of our dial (0 & 99)
	int hBound = 99;
	int lBound = 0;

	//setup return
	int target = 0;

	//spin the dial up to our change
	for (int i = 0; i < change; i++) {

		//check direction of change (L - down, R - up)
		if (direction == "L"){
			if (count == lBound){
				count = 99;
			}
			else{
				count--;
			}
		}else{
			if (count == hBound) {
				count = 0;
			}
			else{
				count++;
			}
		
		}
			
		//check if count is 0, increase target
		if (count == lBound) {
			target++;
		}
	}


	return target;

}



int main(int argc, char* argv[]) {
	//check arg count
	if (argc != 2){
		cout <<"Usage: decode <input file>\n";
		return 0;
	}

	//declarations
	count = 50; //starting our dial at 50 per specifications
	string input = argv[1];
	string currLine;
	int zCount = 0;

	ifstream fileIn(input);

	//read input
	while (getline(fileIn, currLine)) {

		//create substrings
		string s1 = currLine.substr(0,1);
		string s2 = currLine.substr(1);

		int change = stoi(s2);


		//call count function
		zCount += decode(s1, change);
	}

	cout << zCount << "\n";
	
	//cleanup
	fileIn.close();
	return 0;

}
