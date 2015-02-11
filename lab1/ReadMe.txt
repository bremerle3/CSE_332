========================================================================
    CONSOLE APPLICATION : lab1 Project Overview
========================================================================

Author: Leo Bremer
Lab1 Solution

/////////////////////////////////////////////////////////////////////////////
Fixes applied to previous submission:

Fixed warning from Lab0 submission: "warning C4554: '|' : check operator 
precedence for possible error; use parentheses to clarify precedence".

Separated source file and main file, as per Lab0 feedback.  Doing so caused a
linker error when I included cards.cpp in lab1.cpp.  I fixed this error by 
including card.h in lab1.cpp instead.

Changed input of usage_fcn in main from hard-coded argv[0] to argv[program_name].

Corrected an off-by-one error in the file_parser that incorrectly interpreted
a card rank of 10 as a Jack (e.g. 10C was interpreted as JC).

Re-ordered rank enum in card.h to put Ace at position zero, to match the 
file_parser's interpretation of an Ace.

/////////////////////////////////////////////////////////////////////////////
Documentation of Errors/Warnings:

	Received the following warning when calling the size() method on a vector of cards:
"h:\cse332\lab1\lab1\cards.cpp(110): warning C4018: '<' : signed/unsigned mismatch"
	I realized that the problem was I was using the size in a comparison to an integer
	loop variable. I added a cast to int to resolve this warning.

	Received the following warning on a later build:
 "h:\cse332\lab1\lab1\cards.cpp(308): warning C4018: '<' : signed/unsigned mismatch"
 "h:\cse332\lab1\lab1\cards.cpp(327): warning C4018: '<' : signed/unsigned mismatch"
	The warning at line 308 occured because I compared a variable of type size_t to a 
	variable of type int.  The warning at line 327 occured because I compared an int to
	the size() of a vector of ints.  Casting to int once again cleared up that error.

/////////////////////////////////////////////////////////////////////////////
Design Decisions:

In implementing the less than operator, I chose to take advantage of the implicit
"this" pointer to only explicitly pass one argument to the member method.

One design choice I made was to assume that the only input hands would be selected from
a stand 52 card deck of playing cards. This assumption means that in detecting hands, I
do not worry about detecting duplicate cards (e.g. multiple ace of spades) since there
should be only one of each card of each suit.  Similarly, if I detect a hand of all
spades, I know that a pair within that hand is impossible.  A more robust program might
detect invalid hands, but that requirement was not outlined in the assignment document, 
so I ignore that possiblity.  

I decided to print the high card in the case of no rank, since that might useful
in a game such as poker.

/////////////////////////////////////////////////////////////////////////////
Testing:

For testing, I used the provided hands.txt file which I moved to my H drive at
H:/cse332/lab1/hands.txt.  This produces the following output on the console:

H:\cse332\lab1\Debug>lab1.exe H:/cse332/lab1/hands.txt
This program's name is lab1.exe
To run this program, navigate to the folder where its .exe is located and from t
he command line input a .txt file name to readFor a test file, use H:/cse332/lab
1/hands.txt
Warning: Hand with more or less than five cards detected!
Warning: Hand with more or less than five cards detected!
High Card: King High!
Full House!
Straight!
Three of a Kind!
Straight Flush!
One Pair!
Four of a Kind!
Flush!
Two Pair!

All cards sorted:
Ace of Clubs
Ace of Hearts
Ace of Diamonds
Ace of Spades
Two of Clubs
Two of Hearts
Two of Spades
Three of Clubs
Three of Hearts
Four of Clubs
Four of Hearts
Four of Diamonds
Four of Spades
Five of Hearts
Five of Diamonds
Five of Spades
Six of Clubs
Six of Diamonds
Six of Spades
Seven of Hearts
Seven of Diamonds
Seven of Spades
Eight of Clubs
Eight of Hearts
Eight of Diamonds
Eight of Spades
Nine of Clubs
Nine of Hearts
Nine of Diamonds
Nine of Spades
Ten of Clubs
Ten of Hearts
Ten of Diamonds
Ten of Spades
Jack of Clubs
Jack of Hearts
Jack of Diamonds
Jack of Spades
Queen of Clubs
Queen of Hearts
Queen of Diamonds
Queen of Spades
King of Hearts
King of Diamonds
King of Spades

First there is some text instructions directing the user on how to use the program.
Then there are several warnings about hand sizes. These warnings occur because the 
sample text file had some improper hands, which the program has thrown out. Next 
the value of each hand is printed out. Finally, all of the sorted cards from all the
valid hands are printed out (cards from invalid hands were discarded).

In the next test, I added some more invalid hands by adding the following lines to 
hands.txt:

asdfsdaf sdafsdaf
  sdfsdf dsf sdf dfs sdffsdfsdfsdf

Here is the console output from that run:

H:\cse332\lab1\Debug>lab1.exe H:/cse332/lab1/hands.txt
This program's name is lab1.exe
To run this program, navigate to the folder where its .exe is located and from t
he command line input a .txt file name to readFor a test file, use H:/cse332/lab
1/hands.txt
Warning: Hand with more or less than five cards detected!
Warning: Hand with more or less than five cards detected!
Warning: Invalid Card Detected! This hand will be thrown away!
Warning: Invalid Card Detected! This hand will be thrown away!
High Card: King High!
Full House!
Straight!
Three of a Kind!
Straight Flush!
One Pair!
Four of a Kind!
Flush!
Two Pair!

All cards sorted:
Ace of Clubs
Ace of Hearts
Ace of Diamonds
Ace of Spades
Two of Clubs
Two of Hearts
Two of Spades
Three of Clubs
Three of Hearts
Four of Clubs
Four of Hearts
Four of Diamonds
Four of Spades
Five of Hearts
Five of Diamonds
Five of Spades
Six of Clubs
Six of Diamonds
Six of Spades
Seven of Hearts
Seven of Diamonds
Seven of Spades
Eight of Clubs
Eight of Hearts
Eight of Diamonds
Eight of Spades
Nine of Clubs
Nine of Hearts
Nine of Diamonds
Nine of Spades
Ten of Clubs
Ten of Hearts
Ten of Diamonds
Ten of Spades
Jack of Clubs
Jack of Hearts
Jack of Diamonds
Jack of Spades
Queen of Clubs
Queen of Hearts
Queen of Diamonds
Queen of Spades
King of Hearts
King of Diamonds
King of Spades

This input yields invalid hand warnings.  The program throws those away as well.
