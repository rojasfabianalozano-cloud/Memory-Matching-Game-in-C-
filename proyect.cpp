#include<iostream>
#include<string>//text
#include<iomanip>//setw
#include<fstream>//add files
#include<cstdlib>//rand,srand
#include<ctime>//time
#include<thread>//sleep_for(wait time)
#include<chrono>//chrono sec(wait time)
using namespace std;


const int MAX_FILE = 50;
const int MAX_SIZE = 8;

//board display
void displayBoard(string board[][MAX_SIZE], bool revealed[][MAX_SIZE], int size){
    cout << "\n    ";
    for(int c = 0; c < size; c++){
        cout << setw(12) << c;
    }
     cout << endl;

     for(int r = 0; r < size; r++){
        cout << setw(3) << r;
        for(int c = 0; c < size; c++){
            if(revealed[r][c]){
                cout << setw(12) << board[r][c];
            } else {
                cout << setw(12) << "*";
            }
        }
        cout << endl;
    }
 }


int main(){

    string words[MAX_FILE];
    ifstream fin1, fin2, fin3;
    fin1.open("Week10FabianaRojas50WordsArt3.txt");
    fin2.open("Week10FabianaRojas50WordsMath1.txt");
    fin3.open("Week10FabianaRojas50WordsUniverse2.txt");

    if(!fin1 || !fin2 || !fin3){
        cout<<"Error opening file."<<endl;
        return 1;
    }

    //intro
    std:: cout<<"welcome to the Memory Matching Game"<< std::endl;
    cout<<"by Fabiana Rojas 12/08/2025"<< endl;
    cout<<"This is a game where you will have to match pairs of cards."<<endl;

    //menu
    int option;
    cout<<"Please select an option(1,2,3)"<<endl;
    cout<<"1. Art\n2. Math\n3. Universe\n"<<endl;
    cin>>option;
 
    //options
     if(option == 1) {
        cout << "ART FILE SELECTED:" << endl;
        for(int i = 0; i < MAX_FILE; i++){
            if(!(fin1 >> words[i])){
                cout << "Error reading Art file." << endl;
                return 1;
            }
        }
    }
    else if(option == 2) {
        cout << "MATH FILE SELECTED:" << endl;
        for(int i = 0; i < MAX_FILE; i++){
            if(!(fin2 >> words[i])){
                cout << "Error reading Math file." << endl;
                return 1;
            }
        }
    }
    else if(option == 3) {
        cout << "UNIVERSE FILE SELECTED:" << endl;
        for(int i = 0; i < MAX_FILE; i++){
            if(!(fin3 >> words[i])){
                cout << "Error reading Universe file." << endl;
                return 1;
            }
        }
    }
    else {
        cout << "Invalid option." << endl;
        return 0;
    }

    //size
    int size;
    cout<<"Please select the size of the board(4,6,8)"<<endl;
    cin>>size;
    if(size != 4 && size != 6 && size != 8){
        cout<<"Invalid size."<<endl;
        return 0;
    }

    //waiting time
    int waitTime;
     cout << "\nSelect the wait time (in seconds) after a wrong match (2,4,6): ";
    cin >> waitTime;
    if(waitTime != 2 && waitTime != 4 && waitTime != 6){
        cout << "Invalid wait time." << endl;
        return 0;
    }

    //cards
     int numCards = size * size;
    int numPairs = numCards / 2;

    string cards[64];               // máximo 8x8 = 64
    for(int i = 0; i < numPairs; i++){
        cards[2 * i]     = words[i];
        cards[2 * i + 1] = words[i];
    }

    //shuffle cards
    srand(static_cast<unsigned int>(time(0)));
    for(int i = 0; i < numCards; i++){
        int r = rand() % numCards;
        swap(cards[i], cards[r]);
    }

    // reveal cards
        string boardArr[MAX_SIZE][MAX_SIZE];
        bool revealed[MAX_SIZE][MAX_SIZE];

        int k = 0;
        for(int r = 0; r < size; r++){
            for(int c = 0; c < size; c++){
               boardArr[r][c] = cards[k++];
               revealed[r][c] = false;
        }
    }

    //game loop
    int matchedPairs = 0;
    int moves=0;
    while(matchedPairs < numPairs){
        displayBoard(boardArr, revealed, size);

        int r1, c1, r2, c2;
        cout << "Enter the coordinates of the first card a row ";
        cin >> r1;
        cout << " and column: ";
        cin >> c1;
        cout << "Enter the coordinates of the second card row  ";
        cin >> r2;
        cout << " and column: ";
        cin >> c2;
        if(r1 < 0 || r1 >= size || c1 < 0 || c1 >= size ||
           r2 < 0 || r2 >= size || c2 < 0 || c2 >= size ||
           (r1 == r2 && c1 == c2) || revealed[r1][c1] || revealed[r2][c2]){
            cout << "Invalid coordinates. Try again." << endl;
            
            continue;
        }
        moves++;

    //temporal reveral
        revealed[r1][c1] = true;
        revealed[r2][c2] = true;
        displayBoard(boardArr, revealed, size);

        if(boardArr[r1][c1] == boardArr[r2][c2]){
            cout << "It's a match!" << endl;
            matchedPairs++;
        } else {
            cout << "Not a match. Cards will be hidden in " << waitTime << " seconds." << endl;
            this_thread::sleep_for(chrono::seconds(waitTime));
            revealed[r1][c1] = false;
            revealed[r2][c2] = false;
        }
    }
    cout << "Congratulations! You've matched all pairs in: " << moves<< " moves!"<< endl;
    system("pause");
    return 0;   
}
        

 
