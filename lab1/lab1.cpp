// lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "card.h"
#include <iostream>
#include <algorithm>


using namespace std;
const int program_name = 0;
const int error_flag = 1;
const int success_flag = 0;

const char *usage_text = 
"To run this program, navigate to the folder where its .exe is located and from the command line input a .txt file name to read"
"For a test file, use H:/cse332/lab1/hands.txt";

int main(int argc, char* argv[])
{
	usage_fcn(success_flag, argv[program_name], usage_text);
	if ((argc > 2) | (argc < 2)){
		cout << "Please enter one .txt file name on the command line." << endl;
		return usage_fcn(error_flag, argv[program_name], usage_text);
	}

	vector<Card> myCards;

	int success = file_parser(myCards, argv[1]);
	vector<Card> Hand;
	for (int i = 0; i < (int)myCards.size() / 5; i++){
		Hand.clear();
		for (int j = i * 5; j < (i * 5) + 5; j++){
			Hand.push_back(myCards[j]);
		}
		hand_detector(Hand);
	}
	std::sort(myCards.begin(), myCards.end());

	cout << endl;
	cout << "All cards sorted: " << endl;

	printCards(myCards);


	return 0;
}


