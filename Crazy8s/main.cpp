#include<iostream>
#include<fstream>
#include<string>
#include "Card.h"
#include "Player.h"
#include "Game.h"
using std::string, std::cout, std::endl, std::cin;

bool loadDeck(Game& g){
    string filename;
    std::cout << "Choose a file to load the deck from:" << std::endl;
    std::cin >> filename;
    try{
        g.loadDeckFromFile(filename);
    }
    catch(std::runtime_error const&){
        std::cout << "The file was invalid. Aborting." << std::endl;
        return false;
    }
    return true;
}

int getPlayerCount(){
    std::cout << "Enter number of players:" << std::endl;
    int numPlayers;
    while(true){
        if((!(std::cin >> numPlayers)) || numPlayers <= 0){
            if(std::cin.fail()){
                //Clear the fail flag
                std::cin.clear();
                //Remove the non-integer data from the stream
                string garbage;
                std::cin >> garbage;
            }
            std::cout << "Please enter a positive number" << std::endl;
        }
        else{
            //break out of the loop once we've read a valid number
            break;
        }
    }
    return numPlayers;
}

void setupPlayers(Game& g, int numPlayers){
    //Determine whether each player is a human or an AI
    //and add them to the game
    for(int i = 0; i < numPlayers; i++){
        char AIChar;
        bool input = false;
        cout << "Is player " << i << " an AI? (y/n)" << endl;
        while(!input){
            cin >> AIChar;
            cin.ignore();
            if((AIChar == 'Y') || (AIChar == 'y')){
                input = true;
                g.addPlayer(true);
            }
            else if((AIChar == 'N') || (AIChar == 'n')){
                input = true;
                g.addPlayer(false);
            }
            else{
                cout << "Please enter y or n" << endl;
            }
        }
    }
    
  
    
}

void setupGame(Game& g){
    //Determine how many cards to deal, deal the cards, and
    //print the initial discard
    bool input = false;
    string start = "";
    cout << "How many cards should each player start with?" << endl;
    while(!input){
        //reset vals
        string start = "";
        bool isNum = true;

        cin >> start;
        //start is num
        for(size_t i = 0; i < start.length(); i++){
            if(!isdigit(start[i])){
                isNum = false;
            }
        }
        if(!isNum){
            cout << "Please enter a positive number" << endl;
        }
        else{
            //start not valid num
            int startNum = stoi(start);
            if(startNum < 1){
                cout << "Please enter a positive number" << endl;
            }
            //normal opp
            else{
                input = true;
                Card* topcard = g.deal(startNum);
                string disSuit = topcard -> getSuit();
                string disRank = topcard -> getRank();
                cout << "The initial discard is " << disRank << " " << disSuit << endl;
            }
        }
    }   
}

int main(){
    Game g;
    if(!loadDeck(g)){
        return 1;
    }
    int numPlayers = getPlayerCount();
    setupPlayers(g,numPlayers);
    setupGame(g);
    int winner = g.runGame();
    if(winner != -1){
        std::cout << "Player " << winner << " wins!" << std::endl;
    }
    else{
        std::cout << "The game is a draw!" << std::endl;
    }
    std::cout << "The most played suit was " << g.mostPlayedSuit() << std::endl;
    return 0;
}