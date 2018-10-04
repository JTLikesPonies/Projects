#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int bool;
#define true 1
#define false 0

struct Card {
    int suit;
    int rank;
    int num;
    bool dealt;};



int search(struct Card deck[], int n, int cardNum) {
    for(int i = 0; i < n; i++) {
        if(deck[i].num == cardNum) return i;
    }}



int calcHandVal(struct Card hole[], struct Card community[]) {
    int handVal = 0;

    return handVal; }



int calcHandType(struct Card hole[], struct Card community[], int sizeOfComm) {
    int handType = 0;
    struct Card hand[sizeOfComm+2];
    //int n = sizeof(community);
    int i;

    hand[0] = hole[0];
    hand[1] = hole[1];

    for(i = 2; i < sizeOfComm+2; i++) hand[i] = community[i-2];
    //for(j = 0; j < 5; j++) printf("Card in hand: %d/%d\n", hand[j].rank, hand[j].suit);
    for(i = 0; i < sizeOfComm+1; i++) {
        if(hand[i].suit != hand[i+1].suit) {
            if(hand[i].rank != hand[i+1].rank) {
            }
            else {
            }}
        else {
            } ;}

    return handType; }



struct Card drawCard(struct Card deck[]) {
    struct Card drawnCard;

    int newCard = rand() % 52;

    drawnCard = deck[newCard];

    if(drawnCard.dealt != 0) drawCard(deck);
    else {
        drawnCard.dealt = 1;
        deck[newCard].dealt = 1;
        return drawnCard; }}



int main() {
    struct Card deck[52];
    struct Card hole[2];
    struct Card community[5];
    int suit, rank;
    int i = 0;
    time_t t;
    srand((unsigned) time(&t));
    int n = sizeof(deck)/sizeof(deck[0]);
    long handVal;
    int handType;
    int commSize;


    // create the deck
    for(suit = 0; suit < 4; suit++) {
        for(rank = 0; rank < 13; rank++) {
            deck[i].num = i;
            deck[i].suit = suit;
            deck[i].rank = rank;
            deck[i].dealt = 0;

            i++; }}
    /*printf("Size of deck: %d\n", n);
    printf("Card %d is %d %d and %d\n",deck[51].num,deck[51].suit,deck[51].rank,deck[51].dealt);*/

    /* Deals player's hand */
    hole[0] = drawCard(deck);
    hole[1] = drawCard(deck);
    printf("\nYour current hand: %d/%d : %d/%d\n", hole[0].rank, hole[0].suit,
      hole[1].rank, hole[1].suit);

    /* Deal the Flop */
    community[0] = drawCard(deck);
    community[1] = drawCard(deck);
    community[2] = drawCard(deck);\
    printf("\nThe Flop: %d/%d : %d/%d : %d/%d\n", community[0].rank, community[0].suit,
      community[1].rank, community[1].suit, community[2].rank, community[2].suit);
    commSize = 3;

    handType = calcHandType(hole, community, commSize);

    /* Deal the Turn */
    //community[3] = drawCard(deck);
    //printf("\nThe Turn: %d\n", community[3].num);

    /* Deal the River */
    //community[4] = drawCard(deck);
    //printf("\nThe River: %d\n", community[4].num);

    return 0;}
