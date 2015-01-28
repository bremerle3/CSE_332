#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

using namespace std;

enum suit { clubs, hearts, diamonds, spades };
enum rankVal { two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace };

struct Card
{
	suit Suit;
	rankVal Rank;
};

int file_parser(vector<Card> &, char *);
suit toSuit(char);
rankVal toRank(int);
int printCards(const vector<Card> &);



#endif /*CARD_H*/ 