#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <utility>
#include <cstdint>
#include <sstream>
using namespace std;

// Using total to check solution
int total;


uint64_t sumVect(vector<uint64_t> copies) {
	uint64_t total = 0;

	while (!copies.empty()) {
		uint64_t x = copies.back();

		total += x;

		copies.pop_back();
	}
	return total;
}


vector<uint64_t>  checkIds(vector<string> ids) {
	//build vector to return
	vector<uint64_t> temp;
	//temp ints for id ranges
	uint64_t x1;
	uint64_t x2;
	

	//iterate over vector
	while (!ids.empty()) {
		string tmp = ids.back();
		stringstream strm(tmp);
		char delim = '-';
		string id;

		//create temp vector to store id tokens
		vector<uint64_t> tmpVect;

		while (getline(strm, id, delim)) {
			//cout << "Token: " << id << endl;
			uint64_t val = stoul(id);

			tmpVect.push_back(val);
		
		}
		//cout << "Finished Processing line" << endl;

		//once finshed with the line, begin parsing
		x2 = tmpVect.back();
		tmpVect.pop_back();
		x1 = tmpVect.back();

		for (uint64_t i = x1; i <= x2; i++) {
			string str = to_string(i);
			//cout << "value we're checking -> " << str << endl;

			if (str.length() % 2 != 0) {
				continue;
			} else {
				string s1 = str.substr(0,(str.length()/2));
				string s2 = str.substr(str.length()/2);
			
				if (s1 == s2) {
					temp.push_back(i);
					total += 1;
				}
			}
		}
		


		ids.pop_back();
	}
	

	return temp;
}




int main (int argc, char* argv[]) {
	if (argc !=2) {
		cout << "Usage: idCopy <input>\n";
		return 0;
	}

	//vector declarations
	vector<string> idLine;
	//vector<pair<uint64_t, uint64_t>> idRange;
	vector<uint64_t> invalidIds;


	//file input
	string input = argv[1];
	string currLine;
	ifstream fileIn(input);

	//read input, place into vector
	while (getline(fileIn, currLine)) {
		//using strtok func to break line into id ranges
		string tmp = currLine;
		char* line = tmp.data();
		char* strSeg;
		
		strSeg = strtok(line, ",");

		//insert idranges in string vect
		while (strSeg != NULL) {
			string val = strSeg;
			//cout << "inserting value -> " << val << "\n";
			idLine.push_back(val);
			strSeg = strtok(NULL, ",");
		}
	}




	//go over id ranges to find dupes
	invalidIds = checkIds(idLine);

	
	//add ids!
	uint64_t idSum = sumVect(invalidIds);


	//print out total invalid sum
	cout << "Total: " << idSum << "\n";
	//cout << total << "\n";



	/* TESTING PRINTS 

	//test pring for invalid IDs
	for (int id : invalidIds) {
		cout << id << "\n";
	}

	
	//test print pair vector
	for (pair<int,int> pairs : idRange) {
		cout << pairs.first << " | " << pairs.second << "\n";
	}*/

}


	 /*
		Debugging for a bit and I think I've found my error, will keep this code in for posterity.

		Somehow when char* line grabs its element, its corrupting the string data on certain values only
		IE: value 3737324037 turns into a huge value instead -> 18446744073151908357 which is basically 
		uint64 MAX. I'm unsure why this is happening within the loop. 

		It worked fine with the sample data, but we're getting the wrong input value somehow.

		Redoing
		-> entering my id check function with the string vector
		-> we'll need to figure out a way to safely type convert each line
		-> compare values



	//take string vector and add range values into int pair vect
	while (!idLine.empty()) {
		string tmp = idLine.back();
		char* line = tmp.data();
		
		cout << "temp char array data -> " << line << "\n";

		//use strtok again
		char* strSeg = strtok(line, "-");

		
		//theory - what if we turn it back into a string
		//string s1(strSeg);

		uint64_t x1 = atoi(strSeg);

		strSeg = strtok(NULL, "-");
		uint64_t x2 = atoi(strSeg);


		//insert values into our pair
		idRange.push_back({x1, x2});

		cout << "Values are: " << x1 << " | " << x2 << "\n";
		
		//need to popback before looping
		idLine.pop_back();


}*/


/* moving original check ID func here to recreate (used vector<pair<uint64,uint64>>)


	//while loop into for loop to check id validity
	while (!ids.empty()) {
		//cout << "Checking -> " << ids.back().first << "-" << ids.back().second << "\n";

		//pull values, for loop
		uint64_t start = ids.back().first;
		uint64_t end = ids.back().second;

		//iterate over values
		for (uint64_t i = start; i <= end; i++) {
			//convert value to str
			string tmp = to_string(i);

			//if length of i is odd, omit, even we check values
			if (tmp.length() % 2 != 0) {
				continue;
			}
			else {
				//create two substrings then compare
				string s1 = tmp.substr(0,(tmp.length()/2));
				string s2 = tmp.substr(tmp.length()/2);

				//cout << "comparing: " << s1 << " | " << s2 << "\n";

				//if the strings match, add the id num to our return
				if (s1 == s2) {
					//cout << "Inalid id: " << i << "\n";
					temp.push_back(i);
					total += 1;
				}
			}
		

		}

		//before looping pop the element
		ids.pop_back();
		
	}
*/

