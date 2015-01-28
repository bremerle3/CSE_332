// card.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "card.h"

using namespace std;

suit toSuit(char c){
	suit Suit;
	switch (c)
	{
	case 's':
		Suit = spades;
		break;
	case 'h':
		Suit = hearts;
		break;
	case 'c':
		Suit = clubs;
		break;
	case 'd':
		Suit = diamonds;
		break;
	}
	return Suit;
}

rankVal toRank(int i){
	rankVal rank;
	switch (i)
	{
	case 0:
		rank = ace;
		break;
	case 1:
		rank = two;
		break;
	case 2:
		rank = three;
		break;
	case 3:
		rank = four;
		break;
	case 4:
		rank = five;
		break;
	case 5:
		rank = six;
		break;
	case 6:
		rank = seven;
		break;
	case 7:
		rank = eight;
		break;
	case 8:
		rank = nine;
		break;
	case 9:
		rank = ten;
		break;
	case 10:
		rank = jack;
		break;
	case 11:
		rank = queen;
		break;
	case 12:
		rank = king;
		break;
	}
	return rank;
}

int printCards(const vector<Card> &cards){
	const char* suitNames[] = { "Spades", "Hearts", "Clubs", "Diamonds" };
	const char* rankNames[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	int size = cards.size();
	int i = 0;
	while (i<size){
		cout << rankNames[cards[i].Rank] << " of " << suitNames[cards[i].Suit] << endl;
		i++;
	}
	return 0;
}

int file_parser(vector<Card> &cards, char * file)
{
	ifstream ifs(file);
	if (ifs.is_open()){
		string line;
		string card_def_string;
		while (getline(ifs, line)){
			istringstream iss(line);
			while (iss >> card_def_string){
				//so now we have e.g. 2C or 10h or qs
				int cdf_rank = 0;
				char cdf_suit = 'n';
				if (card_def_string.length() == 2){
					if (isdigit(card_def_string[0])){
						cdf_rank = stoi(card_def_string.substr(0, 1)) - 1;
					}
					else if (tolower(card_def_string[0]) == 'j'){
						cdf_rank = 10;
					}
					else if (tolower(card_def_string[0]) == 'q'){
						cdf_rank = 11;
					}
					else if (tolower(card_def_string[0]) == 'k'){
						cdf_rank = 12;
					}

					cdf_suit = card_def_string[1];
				}
				else if (card_def_string.length() == 3){
					cdf_rank = stoi(card_def_string.substr(0, 2));
					cdf_suit = card_def_string[2];
				}
				//make sure they are real card values
				if ((cdf_rank >= 0) && (cdf_rank < 13) && ((tolower(cdf_suit) == 's') | (tolower(cdf_suit) == 'h') | (tolower(cdf_suit) == 'c') | (tolower(cdf_suit) == 'd'))){
					//map values to the struct enums
					Card tmp;
					tmp.Suit = toSuit(tolower(cdf_suit));
					tmp.Rank = toRank(cdf_rank);
					//const char* suitNames[] = { "Spades", "Hearts", "Clubs", "Diamonds" };
					//const char* rankNames[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
					//cout << rankNames[tmp.Rank] << " of " << suitNames[tmp.Suit] << endl;
					cards.push_back(tmp);
				}
			}
		}
		return 0;
	}


	else
	{
		cout << "Unable to open file" << endl;

		cerr << "failure_to_open_file_error" << endl;

	}
	return 1;

}

int usage_fcn(int error_flag, char * name){
	if (error_flag == 0){
		cout << "This program's name is " << name << endl;
		cout << "To run this program, navigate to the folder where its .exe is located and from the command line input a .txt file name to read" << endl;
		cout << "For a test file, use H:/cse332/Labs/Lab0/Lab0/card_file.txt.";
		cout << " " << endl;
			return 0;
	}
	else{
		return 1;
	}
}


int main(int argc, char* argv[])
{
	usage_fcn(0, argv[0]);
	if (argc > 2 | argc < 2){
		cout << "Please enter one .txt file name on the command line." << endl;
		return usage_fcn(1, argv[0]);
	}

	vector<Card> myCards;

	int success = file_parser(myCards, argv[1]);
	printCards(myCards);
	return 0;
}
