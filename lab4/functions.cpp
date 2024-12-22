# include "functions.h"
// add any includes

using std::cout, std::cin, std::endl, std::string;

void deobfuscate() { 
   
}

void wordFilter() {
    string word;
    string sentence;
    
    
    cout << "Please enter the sentence: ";
    getline(cin, sentence);
    cout << "Please enter the filter word: ";
    getline(cin, word);
    string replace(word.length(), '#');

    
    while(sentence.find(word) != string::npos)
        {
        sentence.replace(sentence.find(word), word.length(), replace);
        }
    

    cout << "Filtered sentence: " << sentence << endl;
}

void passwordConverter() {
    string password;
    
    cout << "Please enter your text input: ";
    getline(cin, password);
    cout << "input: " << password << endl;

    for (unsigned int i = 0; i < password.size(); i++)
    {
        if(password[i] == 'a' || password[i] == 'A'){
            (password[i] = '@');
            }
        if(password[i] == 'e' || password[i] == 'E'){
            (password.at(i) = '3');
            }
        if(password[i] == 'i' || password[i] == 'I'){
            (password.at(i) = '!');
            }
        if(password[i] == 'o' || password[i] == 'O'){
            (password.at(i) = '0');
            }
        if(password[i] == 'u' || password[i] == 'U'){
            (password.at(i) = '^');
            } 
    }
    string newpassword = "";
    for (int i = password.length() - 1; i >= 0; i--)
    {
        newpassword += password[i];
    }
    

    cout << "output: " << password << newpassword << endl;
}

void wordCalculator() {
    // TODO
}

void palindromeCounter() {
    // TODO
}