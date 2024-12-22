#include<cctype>
#include<stdexcept>
#include "Card.h"
using std::string;

Card::Card(string rank, string suit) : rank(rank), suit(suit), timesPlayed(0) {
    //validate rank
    //check if rank empty
    if(rank.empty()){
        throw std::invalid_argument("Invalid Rank");
    }
    //check if rank num
    for(unsigned int i = 0; i < rank.size(); i++){
        if((!isdigit(rank[i])) && (!isalpha(rank[i]))){
            throw std::invalid_argument("Invalid Rank");
        }
    }

    //Validate suit
    //check is suit empty
    if(suit.empty()){
        throw std::invalid_argument("Invalid Rank");
    }
    // check if suit is not alpha
    for(unsigned int i = 0; i < suit.size(); i++){
        if((!isalpha(suit[i])) && (!isdigit(suit[i]))){
            throw std::invalid_argument("Invalid Suit");
        }
    }
}

string Card::getRank(){
    //Rank getter
    return rank;
}

string Card::getSuit(){
    //Suit getter
    return suit;
}

int Card::getTimesPlayed(){
    //counter getter
    return timesPlayed;
}

bool Card::canBePlayed(string currentRank, string currentSuit){
    //Return whether or not the card can legally be played
    //unless rank is 8
    if((rank == currentRank) || (suit == currentSuit) || (rank == "8")){
        return true;
    }
    //return false is card invalid
    else{
        return false;
    }
}

void Card::play(){
    timesPlayed++;
}