#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

using namespace std;

enum suit { clubs, hearts, diamonds, spades };
enum rankVal {ace, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king };

struct Card
{
	suit Suit;
	rankVal Rank;
	
	//Remember that this member function takes implicit *this pointer as first argument.
	bool operator< (const Card& other_card) const
	{
		if (Rank != other_card.Rank){
			return (Rank < other_card.Rank);
		}
		else {
			return (Suit < other_card.Suit);
		}
	}
};

int file_parser(vector<Card> &, char *);
suit toSuit(char);
rankVal toRank(int);
int printCards(const vector<Card> &);
int usage_fcn(int, char *, const char *);
void card_reader(string, vector<Card> &);
void hand_detector(const vector<Card> &);



#endif /*CARD_H*/ 