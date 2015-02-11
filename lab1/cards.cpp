// card.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "card.h"
#include <algorithm>
#include <numeric>

using namespace std;
const int success_flag = 1;

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
	const char* suitNames[] = { "Clubs", "Hearts", "Diamonds", "Spades" };
	const char* rankNames[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	int size = cards.size();
	int i = 0;
	while (i<size){
		cout << rankNames[cards[i].Rank] << " of " << suitNames[cards[i].Suit] << endl;
		i++;
	}
	return 0;
}

//int printCards(const vector<Card> &cards){
//
//for (int i = 0; i < (int)myCards.size(); i++){
//	const char* suitNames[] = { "Clubs", "Hearts", "Diamonds", "Spades" };
//	const char* rankNames[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
//
//	cout << rankNames[myCards[i].Rank] << suitNames[myCards[i].Suit] << endl;

void card_reader(string line, vector<Card> &cards){
	istringstream iss(line);
	string card_def_string;
	vector<Card> one_hand;
	int card_count = 0;
	while (iss >> card_def_string){
		//so now we have e.g. card_def_string = 2C or 10h or qs
		if (card_def_string == "//"){
			if (card_count == 5){
				for (int i = 0; i < (int)one_hand.size(); i++){
					cards.push_back(one_hand[i]);
				}
				/*const char* suitNames[] = { "Clubs", "Hearts", "Diamonds", "Spades" };
				const char* rankNames[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };

				cout << "One Hand: ";
				for (int i = 0; i < (int)one_hand.size(); i++){
					cout << rankNames[one_hand[i].Rank] << suitNames[one_hand[i].Suit] << " ";
				}
				cout << endl;*/
			}
			else{
				cout << "Warning: Hand with more or less than five cards detected!" << endl;
			}
			break;
		}

		int cdf_rank = 0;
		char cdf_suit = 'n';
		if (card_def_string.length() == 2){
			if (isdigit(card_def_string[0])){
				cdf_rank = stoi(card_def_string.substr(0, 1)) - 1;
				//cdf_rank = stoi(card_def_string[0]) - 1;
			}
			else if (tolower(card_def_string[0]) == 'a'){
				cdf_rank = 0;
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
			cdf_rank = stoi(card_def_string.substr(0, 2)) - 1;
			cdf_suit = card_def_string[2];
		}
		else{
			cout << "Warning: Invalid Card Detected! This hand will be thrown away!" << endl;
			break;
		}
		//make sure they are real card values
		if ((cdf_rank >= 0) && (cdf_rank < 13) && ((tolower(cdf_suit) == 's') | (tolower(cdf_suit) == 'h') | (tolower(cdf_suit) == 'c') | (tolower(cdf_suit) == 'd'))){
			//map values to the struct enums
			Card tmp;
			tmp.Suit = toSuit(tolower(cdf_suit));
			tmp.Rank = toRank(cdf_rank);
			one_hand.push_back(tmp);
		}
		card_count++;
	}
};

int file_parser(vector<Card> &cards, char * file)
{
	ifstream ifs(file);
	if (ifs.is_open()){
		string line;
		while (getline(ifs, line)){ //after this line we have e.g. line = 2C 3C 4C 5C 6C 7C 8C 9C 10C JC QC KC AC
			card_reader(line, cards);
		}

		const char* suitNames[] = { "Clubs", "Hearts", "Diamonds", "Spades" };
		const char* rankNames[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };

		return 0;
	}
	else
	{
		cout << "Unable to open file" << endl;
		cerr << "failure_to_open_file_error" << endl;
	}
	return 1;
}

void hand_detector(const vector<Card> &cards){
	const int numRanks = 13;
	const int numSuits = 4;
	const int handSize = 5;
	int rankTally[numRanks] = { 0 };
	int suitTally[numSuits] = { 0 };
	int maxRank = -1;

	for (int i = 0; i < (int)cards.size(); i++){
		rankTally[cards[i].Rank]++;
		suitTally[cards[i].Suit]++;
		//Find the max rank in case of high card
		if ((cards[i].Rank > maxRank) && cards[i].Rank != 0){
			maxRank = cards[i].Rank;
		}
		if (cards[i].Rank == 0) //Aces are high
			maxRank = cards[i].Rank;
	}

	const int num_pos_hands = 9;
	int detected_hand[num_pos_hands] = { 0 };
	const int onePair = 1;
	const int twoPair = 2;
	const int threeKind = 3;
	const int straight = 4;
	const int flush = 5;
	const int fullHouse = 6;
	const int fourKind = 7;
	const int straightFlush = 8;

	size_t rankTallySize = sizeof(rankTally) / sizeof(int);
	int *rankTallyEnd = rankTally + rankTallySize;

	size_t suitTallySize = sizeof(suitTally) / sizeof(int);
	int *suitTallyEnd = suitTally + suitTallySize;
	
	//Detect flush
	int *suitResult = std::find(suitTally, suitTallyEnd, 5);
	if (suitResult != suitTallyEnd){
		detected_hand[flush] += 1;
	}
	
	//Detect fourKind
	int * fourKindResult = std::find(rankTally, rankTallyEnd, 4);
	if (fourKindResult != rankTallyEnd){
		detected_hand[fourKind] += 1;
	}
		
	//Detect threeKind
	int *threeKindResult = std::find(rankTally, rankTallyEnd, 3);
	if (threeKindResult != rankTallyEnd){
		detected_hand[threeKind] += 1;
	}

	//Find pairs, and build vector to detect straights
	vector<int> straight_detect;
	for (int i = 0; i < (int) rankTallySize; i++){
		if (rankTally[i] == 2){
			detected_hand[onePair]++;
		}
		if (rankTally[i] != 0){
			straight_detect.push_back(i);
		}
	}

	//Decide if we have one or two pairs
	if (detected_hand[onePair] == 2){
		detected_hand[twoPair]++;
	}
	else if (detected_hand[onePair] == 1){
	}

	const int wrapAroundSum = 42;
	//Determine if we have a straigh, aces count high and low
	int contiguous = 0;
	if (straight_detect.size() == 5){
		for (int i = 0; i < (int) straight_detect.size() - 1; i++){
			if (straight_detect[i] == straight_detect[i + 1] - 1){
				contiguous++;
			}
		}
		if ((contiguous == 4) || (std::accumulate(straight_detect.begin(), straight_detect.end(), 0) == wrapAroundSum)) {
			detected_hand[straight]++;
		}
	}

	//In case of high card, get the rank and suit of the highest card
	const char* suitNames[] = { "Clubs", "Hearts", "Diamonds", "Spades" };
	const char* rankNames[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };


	//Logic on dected_hand array to determine the hand
	if (detected_hand[straight] && detected_hand[flush])
		cout << "Straight Flush!" << endl;
	else if (detected_hand[fourKind])
		cout << "Four of a Kind!" << endl;
	else if (detected_hand[onePair] && detected_hand[threeKind])
		cout << "Full House!" << endl;
	else if (detected_hand[flush])
		cout << "Flush!" << endl;
	else if (detected_hand[straight])
		cout << "Straight!" << endl;
	else if (detected_hand[threeKind])
		cout << "Three of a Kind!" << endl;
	else if (detected_hand[twoPair])
		cout << "Two Pair!" << endl;
	else if (detected_hand[onePair])
		cout << "One Pair!" << endl;
	else
		cout << "High Card: " << rankNames[maxRank] << " High!" << endl;
}

	int usage_fcn(int error_flag, char * name, const char * usage_text){
		if (error_flag == 0){
			cout << "This program's name is " << name << endl;
			cout << usage_text << endl;
			return ~success_flag;
		}
		else{
			return success_flag;
		}
}

