#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Permute the deck of cards, effectively shuffling it.
 * Uses the Fisher-Yates / Durstenfeld shuffle algorithm.
 */
void shuffle(int cards[])
{ 
  for(int i=0; i<52; i++) {
    cards[i]=i;
  }
  //values 0-51 and shuffler
  for(int k= 51; k>0; k--) {
    int j = rand()%(k+1);
   
    int a = cards[k];
    cards[k] = cards[j];
    cards[j] = a;
  } 
}

/**
 *  Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{
  /*int ID example
   * if 31 is given
   * 7-D should be returned */
  int suit1 = id/13;
  
  if(suit1 == 0) {
    cout << type[id%13] << "-" << suit[0] << " "; 
  }
  
  if(suit1 == 1) {
    cout << type[id%13] << "-" << suit[1] << " "; 
  }
  
  if(suit1 == 2) {
    cout << type[id%13] << "-" << suit[2] << " "; 
  }
 
  if(suit1 == 3) {
    cout << type[id%13] << "-" << suit[3] << " "; 
  }
  
}
  

/**
 *  Returns the numeric value of the card.
 *  Return 11 for an ACE.
 */
int cardValue(int id)
{
  return value[id%13];
}

/**
 * Print out each card in the hand separated by a space and
 * then print a newline at the end.
 */
void printHand(int hand[], int numCards)
{
  for(int i= 0; i < numCards; i++){
    printCard(hand[i]);
  }
}

/**
 * Returns the total score of the provided hand.  
 * ACES are be treated as 11s to make the highest possible hand
 *  and reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  int sum = 0;
  
  for(int i=0;i<numCards; i++) {
    sum += cardValue(hand[i]);
  }
    //when ACE and over 21
  for(int i=0;i<numCards; i++) {
    if(sum > 21 && cardValue(hand[i]) == 11) {
    sum -= 10;
    }
  }
  return sum;
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];

  char yesorno = 'y';
  do {
    shuffle(cards);
  
    int pnumCards = 2;
    int dnumCards = 2;
    int deckCards = 4;
    //deckCards needed to count how many cards are taken from deck
    //also used to properly distribute cards between dealer and player
  
    //deal the cards in alternating fashion
    phand[0] = cards[0];
    dhand[0] = cards[1];
    phand[1] = cards[2];
    dhand[1] = cards[3];
  
    cout << "Dealer: ? ";
    printCard(dhand[1]);
    cout << endl;
    
    cout << "Player: ";
    printCard(phand[0]);
    printCard(phand[1]);
    cout << endl;
  
    while(1) { //run a while loop and continously check for when sum is equal or over 21
      if(getBestScore(phand, pnumCards) >= 21){
        break;
      }
    
      else { // hit or stay
      
        char hors;
        cout << "Type 'h' to hit and 's' to stay:" << endl;
        cin >> hors;
    
        if(hors == 'h') { //hit and show cards to player
          phand[pnumCards++] = cards[deckCards++];
          cout << "Player: ";
          printHand(phand, pnumCards);
          cout << endl;
        }
  
        if(hors == 's') { //run dealers hand
          break;
        }
      }
    }
    
    if(getBestScore(phand, pnumCards) < 22) {
      while(getBestScore(dhand, dnumCards) < 17) {
          dhand[dnumCards++] = cards[deckCards++];
        }
        cout << "Dealer: ";
        printHand(dhand, dnumCards);
        cout << endl;
    }
  
    //COMPARISONS
  
    //player> dealer
    if(getBestScore(phand, pnumCards) < 22) {
      if(getBestScore(phand, pnumCards) > getBestScore(dhand, dnumCards)) {
        cout << "Win " << getBestScore(phand, pnumCards) << " " << getBestScore(dhand, dnumCards) << endl;
      }
    }
  
    //player busts
    if(getBestScore(phand, pnumCards) > 21) {
      cout << "Player busts" << endl;
      cout << "Lose " << getBestScore(phand, pnumCards) << " " << getBestScore(dhand, dnumCards) << endl;
    }
    
    //dealer > player
    if(getBestScore(dhand, dnumCards) < 22) {
      if(getBestScore(phand, pnumCards) < getBestScore(dhand, dnumCards)) {
        cout << "Lose " << getBestScore(phand, pnumCards) << " " << getBestScore(dhand, dnumCards) << endl;
      }
    }
 
    //dealer busts
    if(getBestScore(dhand, dnumCards) > 21) {
      cout << "Dealer busts" << endl;
      cout << "Win " << getBestScore(phand, pnumCards) << " " << getBestScore(dhand, dnumCards) << endl;
    }
  
    //tie
    if(getBestScore(dhand, dnumCards) == getBestScore(phand, pnumCards)) {
      cout << "Tie " << getBestScore(phand, pnumCards) << " " << getBestScore(dhand, dnumCards) << endl;
    }
    
    //PLAY AGAIN
    cout << endl;
    cout << "Play again? [y/n]" << endl;
    cin >> yesorno;
  }
  while(yesorno == 'y');
  
  return 0;
}


