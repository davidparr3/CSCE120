#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include "Game.h"
using std::string, std::vector, std::cout, std::endl;

Game::Game(): players({}), suits({}), ranks({}), 
    deck({}), drawPile({}), discardPile({}) {}

void Game::loadDeckFromFile(string filename){
    //initialize suits, ranks, deck, and drawPile from the given file
    string suitLine, rankLine;
    //open file
    std::ifstream inFS(filename);
    if(!inFS.is_open()){
        throw std::runtime_error("");
    }
    
    //read suits
    if(!getline(inFS, suitLine)){
        throw std::runtime_error("");
    }
    std::stringstream suitsStream(suitLine);
    string suit;
    while(getline(suitsStream, suit, ' ')){
        suits.push_back(suit);
    }
    
    //read ranks
    if(!getline(inFS, rankLine)){
        throw std::runtime_error("");
    }
    std::stringstream ranksStream(rankLine);
    string rank;
    while(getline(ranksStream, rank, ' ')){
        ranks.push_back(rank);
    }

    //create deck
    vector<Card*> origDrawPile; 
    bool end = false;
    while(!end){
            //reset vals
            string newRank = "";
            string newSuit = "";
            string cardLine = "";
            //read card
            if(!getline(inFS, cardLine)){
                end = true;
                break;
            }
            std::stringstream cardStream(cardLine);
            if(!(cardStream >> newRank) || !(cardStream >> newSuit) || (!cardStream.eof())){
                throw std::runtime_error("");
            }

            //Validate suit and rank
            bool validSuit = false;
            bool validRank = false;
            for(size_t i = 0; i < suits.size(); i++){
                if(suits[i] == newSuit){
                    validSuit = true;
                }
            }
            for(size_t i = 0; i < ranks.size(); i++){
                if(ranks[i] == newRank){
                    validRank = true;
                }
            }
            if(!validRank || !validSuit){
                throw std::runtime_error("");
            }
            //create card
            try{
            Card* newCard = new Card(newRank, newSuit);
            deck.push_back(newCard);
            origDrawPile.push_back(newCard);
            }catch (std::invalid_argument&){
                throw std::runtime_error("");
            }
    }
    //reverse order for drawPile
    for(int i = origDrawPile.size() - 1; i >= 0; i--){
        drawPile.push_back(origDrawPile[i]);
    }

    //Validate card count
    if(!inFS.eof()){
        throw std::runtime_error("");
    }
    inFS.close();
}

void Game::addPlayer(bool isAI){
    //add a new player to the game
        Player* newPlayer = new Player(isAI);
        players.push_back(newPlayer);
    }

void Game::drawCard(Player* p){
    //Move the top card of the draw pile to Player p's hand
    //If the draw pile is empty, flip the discard pile to create a new one
    if(drawPile.empty()){
        //not enough cards
        if(discardPile.size() == 1){
            throw std::runtime_error("");
        }
        //normal opp
        else{
            cout << "Draw pile, empty, flipping the discard pile." << endl;
            Card * topcard = discardPile.back();
            discardPile.pop_back();
            for(int i = discardPile.size() - 1; i >= 0; i--){
                drawPile.push_back(discardPile[i]);
                discardPile.pop_back();
            }
            discardPile.push_back(topcard);
        }
    }

    
    //draw opperations
    p -> addToHand(drawPile.back()); //add to hand
    drawPile.pop_back(); //remove from pile
}

//deals numCards cards to each player
Card* Game::deal(int numCards){
    //Flip the top card of the draw pile to be the initial discard
    //then deal numCards many cards to each player
    
    //start discard pile
    discardPile.push_back(drawPile.back());
    drawPile.pop_back();
    //deal
    int dealt = 0;
    while(dealt < numCards){
        for(size_t i = 0; i < players.size(); i++){
            drawCard(players[i]);
        }
        dealt++; //increment dealt
    }
    return discardPile.back();
}

string Game::mostPlayedSuit(){
    //Return the suit which has been played the most times
    //if there is a tie, choose any of the tied suits
    //create vector to store times
    vector<int> times(suits.size(), 0);
    int timesPlayed;
    
    //
    for(size_t i = 0; i < deck.size(); i++){
        for(size_t j = 0; j < suits.size(); j++){
            if((deck[i] -> getSuit()) == suits[j]){
               timesPlayed = deck[i] -> getTimesPlayed();
               times[j] += timesPlayed;
            }
        }
    }
    //check for greatest val
    int highVal = times[0];
    string mostPlayed = suits[0];
    for(size_t i = 0; i < times.size(); i++){
        if(highVal < times[i]){
            highVal = times[i];
            mostPlayed = suits[i];
        }
    }
    return mostPlayed;
}

int Game::runGame(){
    //Run the game and return the number of the winning player    
    bool gameOver = false;
    int winner;
    string currentSuit = discardPile.back() -> getSuit();
    string currentRank = discardPile.back() -> getRank();
    while(!gameOver){
        for(size_t i = 0; i < players.size(); i++){
            cout << "Player " << i << "'s turn!" << endl;
            Card* playedCard = players[i] -> playCard(suits, currentRank, currentSuit);
            //card drawing
            if(playedCard == nullptr){
                bool canDraw = true;
                try{
                    drawCard(players[i]);
                }catch(std::runtime_error&){
                    canDraw = false;
                    winner = -1;
                }
                if(canDraw){
                    cout << "Player " << i << " draws a card." << endl;
                }
                else{
                    cout << "Player " << i << " cannot draw a card." << endl;
                    return winner;
                }
                continue;
            }
            //played Card
            string playedRank = playedCard -> getRank();
            string playedSuit = playedCard -> getSuit();
            if(playedRank == "8"){
                cout << "Player " << i << " plays " << playedRank << " " << playedSuit << " and changes the suit to " << currentSuit << "." << endl;
            }
            else{
                cout << "Player " << i << " plays " << playedRank << " " << playedSuit << "." << endl;
            }

            discardPile.push_back(playedCard);

            //detect winner
            if(players[i] -> getHandSize() == 0){
                gameOver = true;
                winner = i;
                break;
            }
            
        }

    }
    return winner;
}

//Destructor--Deallocates all the dynamic memory we allocated
Game::~Game(){
    for (unsigned int i = 0; i < deck.size(); i++){
        delete deck.at(i);
    }
    for (unsigned int i = 0; i < players.size(); i++) {
        delete players.at(i);
    }
}