#include<iostream>
#include<sstream>
#include "Player.h"
using std::vector, std::string, std::size_t, std::cout, std::cin, std::endl;

Player::Player(bool isAI) : isAI(isAI), hand()  {
    
}

void Player::addToHand(Card* c){
    //Add the card c to the player's hand
    //add c to end of hand vector
    hand.push_back(c);
}

size_t Player::getHandSize(){
    //Hand size getter
    //initalize handsize
    size_t handSize = hand.size();
    return handSize;
}

std::string Player::getHandString(){
    //Hand getter
    string handString;
    //convert hand vector to usable string
    for(size_t i = 0; i < hand.size(); i++){
        //
        handString = handString + hand[i]->getRank() + " " + hand[i]->getSuit() + ", ";
    }
    //remove , if string not empty
    if(!handString.empty()){
        handString.resize(handString.size() - 2);
    }
    return handString;
}

Card* Player::playCard(vector<string> const& suits, string& currentRank, string& currentSuit){
    //Choose a card to play and return the chosen card
    string temp_rank, temp_suit, newsuit;
    bool input = false;
    bool in_hand = false;
    bool wild = false;
    

    //For AI
    if(isAI){
        for(size_t i = 0; i < hand.size(); i++){
            temp_rank = hand[i]->getRank();
            temp_suit = hand[i]->getSuit();
            if(hand[i]->canBePlayed(currentRank,currentSuit)){
                currentRank = temp_rank;
                currentSuit = temp_suit;
                hand[i]->play();
                //remove card from deck
                Card* card = hand[i];
                hand.erase(hand.begin() + i);
                return card;
            }
        }
        //ai draws if no valid move
        return nullptr;
    }

    //For human
    cout << "Your hand contains: " << getHandString() << endl;
    cout << "The next card played must be a " << currentRank << " or " << currentSuit << endl;
    cout << "What would you like to play? (enter \"draw card\" to draw a card)" << endl;
    while(input == false){
        in_hand = false; //reset in_hand
        cin >> temp_rank >> temp_suit;
        //check if nothing returned
        if((temp_rank == "draw") || (temp_rank == "Draw")){
            input = true;
            return nullptr;
        }
        //if card not empty
        for(size_t i = 0; i < hand.size(); i++){
            if((temp_rank == hand[i]->getRank()) && (temp_suit == hand[i]->getSuit())){
                in_hand = true; // player has the card
                //deternmine is card can be played
                if(hand[i]->canBePlayed(currentRank,currentSuit)){
                    input = true;
                    //for 8
                    if(temp_rank == "8"){
                        cout << "What suit would you like to declare?" << endl;
                        while(!wild){
                            cin >> newsuit;
                            for(size_t i = 0; i < suits.size(); i++){
                                if(newsuit == suits[i]){
                                    wild = true;
                                    temp_suit = newsuit;
                                    break;
                                }
                            }
                            if(!wild){
                                cout << "That's not a suit in this deck. Try again." << endl;
                            }
                        }
                    }
                    //normal card
                    currentRank = temp_rank;
                    currentSuit = temp_suit;
                    hand[i]->play();
                    //remove card from deck
                    Card* card = hand[i];
                    hand.erase(hand.begin() + i);
                    return card;
                }
                //card cannot be played
                cout << "You can't play that card. Try again." << endl;
            }  
        }
        //if card not in hand
        if(!in_hand){
            cout << "That's not a card you have. Try again." << endl;
        }
    }
    return nullptr;
}