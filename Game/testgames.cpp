#include"CardGame.h"

int CardGame::totalParticipants=0;
int main()
{
	CardGame *bridge=0;
	CardGame *solitaire=0;
	CardGame *poker=0;
	CardGame *blackjack=0;

	bridge=new CardGame(4);
	blackjack=new CardGame(8);
	solitaire=new CardGame(1);
	delete blackjack;
	delete bridge;

	poker=new CardGame(5);
	delete solitaire;
	delete poker;

	return 0;
}