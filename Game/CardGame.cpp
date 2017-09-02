#include "CardGame.h"
#include<iostream>
using namespace std;

CardGame::CardGame(int p)
{
	players=p;
	totalParticipants+=p;
	cout<<p<<" players have started a new game. The total no. of participants is: "<<totalParticipants<<endl;
}

CardGame::~CardGame(void)
{
	totalParticipants-=players;
	cout<<players<<" players have finished the game. Now there are "<<totalParticipants<<" in total."<<endl;
}