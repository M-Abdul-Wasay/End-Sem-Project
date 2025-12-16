// importing libraries
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <iomanip>
#include<thread>
#include<vector>
#include<limits>
#ifdef _WIN32
#include <windows.h>
#endif

//colors
#define RESET   "\033[0m" 
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"
#define BOLDGREEN  "\033[1;32m"
#define BOLDRED    "\033[1;31m"
#define BOLDYELLOW "\033[1;33m"
#define BOLDBLUE   "\033[1;34m"


using namespace std;
using namespace std::chrono;            // needed for timer functionality


// enables ANSI color and formatting support in the windows console while safely doing nothing on non-windows systems.
void enableANSI() {
#ifdef _WIN32           //calling win32 lib for ui in the console
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

// global variables
int unlock_2 = 0;
int unlock_3 = 0;
const int time_limit = 30;
int error_count;

void wpm(int total_number, double total_time);


// function to output playbook with a transition
void typewriter(const string& text, int delay = 20) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(milliseconds(delay));  //delaying output by some time for smooth transition of the char
    }
}


// function to give color
void color(string input, bool correct) {
    if (correct)
        cout << BOLDGREEN << input << " " << RESET;         // highlight correct user input words in green
    else
        cout << BOLDRED << input << " " << RESET;           // highlight incorrect user input words in red
}


// start the game by pressing the enter key
void press_enter_to_start() {
    cin.clear();
    string dummy;
    getline(cin, dummy);            // take in a dummy value (enter) to start
}


void stop_function(int a) {
    this_thread::sleep_for(std::chrono::seconds(a));   // function to delay the count down by a second
}


void levels(vector <string> word_bank, int total_number);

// Word bank for level 1 (easy)
vector<string> words_easy = {
    "apple","ball","cat","dog","egg","fish","goat","hat","ice","jam","kite","lion","moon","nest","owl","pen","queen","rat","sun","tree","umbrella","van","wolf","xray","yarn","zebra","book","car","desk","ear","frog","game","hand","ink","jug","key","lamp","milk","net","orange","pig","quill","rope","ship","top","unit","vase","water","yard","zip","ant","bag","cup","door","eye","fan","gum","hill","iron","jar","kid","leaf","map","nose","oil","pan","quiz","ring","sock","tent","use","vote","wind","axe","young","zone","air","bed","coin","dust","elf","fire","gold","home","iceberg","joke","king","lake","man","nut","open","play","quiet","road","sand","time","up","voice","warm","year"
};

// Word bank for level 2 (medium)
vector<string> words_medium = {
    "actor","alarm","animal","answer","artist","attack","author","battle","beauty","bottle","camera","castle","chance","charge","choice","circle","cloud","corner","damage","danger","dream","engine","event","family","forest","future","garden","ground","growth","health","island","lesson","letter","market","memory","message","mirror","motion","nature","object","office","parent","people","planet","power","problem","product","project","purpose","reason","record","result","river","school","science","shadow","signal","silver","skill","sound","speech","street","system","teacher","thought","travel","valley","vision","window","winter","writer","yellow","energy","machine","nation","picture","surface","vehicle","weather","weight","victory","freedom","balance","harvest","journey","respect","comfort","pattern","fortune","detail"
};

// Word bank for level 3 (hard)
vector <string> words_hard = {
    "abstract","balance","capture","decisive","elegant","fiction","generate","harmony","improve","justice","kingdom","language","maintain","neutral","observe","pattern","qualify","recover","significant","tension","upgrade","variety","wisdom","youthful","zealous","complex","deliver","enhance","frequent","glimmer","historic","identify","journey","kinetic","logical","migrate","notable","organize","perceive","quantify","reflect","sustain","transform","utilize","vivid","wonder","yield","zone","adventure","barrier","concept","dynamic","emerge","fluent","govern","heritage","illustrate","judgment","keen","liberty","modify","navigate","option","precise","qualitative","relevant","strategy","theory","ultimate","variable","welfare","analysis","boundary","cherish","dominate","emphasis","framework","gratitude","hypothesis","intense","justify","landscape","mechanism","notion","optimal","persuade","radiate","sequence","transition","versatile","withdraw","approximate","conclude","devote","expand","fortify","genuine","interpret","mediate","persist"
};

// using vectors instead of arrays as vectors allow the index to be a variable

void levelling_system(){
    // upgrade or downgrade difficulty level based on errors in user input
    if (error_count == 0) {
        cout << "Accuracy: *****" << endl;
        if (unlock_2 == 1) {
            unlock_3 = 1;                                    // unlocking level 3
        }
        unlock_2 = 1;                                       // unlocking level 2
        if (unlock_2 == 1 && unlock_3 == 0) {
            press_enter_to_start();
            cout <<CYAN<< "\t------Level 2------\t" << endl;       // move to level 2 if not unlocked
            levels(words_medium, 20);
            cout << endl;
        }
        else if (unlock_3 == 1) {
            return;
        }
    }
    else if (error_count >= 1 && error_count <= 2) {
        cout << "Accuracy: ****" << endl;
        unlock_2 = 1;                                       // unlocking level 2
        if (unlock_3 == 0) {
            press_enter_to_start();// move to level 2 if level 3 is locked
            cout << CYAN << "\t------Level 2------\t" << endl;
            levels(words_medium, 20);
            cout << endl;
        }
    }
    else if (error_count >= 3 && error_count <= 5) {
        cout << "Accuracy: ***" << endl;
        unlock_3 = 0;                                       // lock level 3
        if (unlock_2 == 1) {
            press_enter_to_start();// move to level 2 if it is unlocked
            cout << CYAN << "\t------Level 2------\t" << endl;
            levels(words_medium, 20);
            cout << endl;
        }
        else if (unlock_2 == 0) {
            press_enter_to_start();// move to level 1 if level 2 is locked
            cout << CYAN << "\t------Level 1------\t" << endl;
            levels(words_easy, 10);
            cout << endl;
        }
    }
    else if (error_count >= 6 && error_count <= 8) {
        cout << "Accuracy: **" << endl;
        unlock_2 = 0;                                       // lock level 2
        unlock_3 = 0;
        press_enter_to_start();// lock level 3
        cout << CYAN << "\t------Level 1------\t" << endl;
        levels(words_easy, 10);                              // return the user to level 1   
        cout << endl;
    }
    else if (error_count >= 9) {
        cout << "Accuracy: *" << endl;
        unlock_2 = 0;                                       // lock level 2
        unlock_3 = 0;
        press_enter_to_start();// lock level 3
        cout << CYAN << "\t------Level 1------\t" << endl;
        levels(words_easy, 10);                             // return the user to level 1 
        cout << endl;
    }
}


void levels(vector <string> word_bank, int total_number) {
    error_count = 0;                               // initializing error count to 0
    vector<string> selected_words;                 // vector for our randomized words prompt
    cout << YELLOW << "Words:\n" << RESET;
    for (int i = 0; i < total_number; i++) {
        int index = rand() % word_bank.size();              // generating random words
        selected_words.push_back(word_bank[index]);         // appending the words to the selected words vector 
    }

    for (const auto& word : selected_words) {
        cout << word << " ";                       //displaying the selected words
    }

    cout << endl;
    cout << "------- Start Typing -------" << endl;
    cout << endl;

    cout << "Press Enter to start ... ";
    press_enter_to_start();       //this line allows the user to press enter to start
    cout << endl;

    // delaying the countdown
    for (int i = 3; i >= 1; i--) {
        cout << BOLDYELLOW << i << "..." << RESET << "\r" << flush;
        this_thread::sleep_for(seconds(1));         // total 3 seconds countdown (1+1+1=3)
    }
    cout << "Start";
    cout << endl;

    auto start = steady_clock::now();       // starting the timer after the count down
    for (int i = 0; i < total_number; i++) {
        string input;
        cin >> input;           // taking user input of the words
        bool correct_word = (input == selected_words[i]);         // comparing user input word with acutal word for typo
        color(input, correct_word);
        if (!correct_word) error_count++;         // incrementing the error count if user made a typo
    }

    auto stop = steady_clock::now();            // stopping the timer when all the input are taken from the user
    auto time_elapsed = stop - start;           // calculating time taken 
    cout << endl;
    auto total_time = duration_cast<milliseconds>(time_elapsed).count() / 60000.0;    //converting milliseconds to minutes
    
    wpm(total_number, total_time);                           // calculating words per minute

    // call leveling system() to change levels based on results
    levelling_system();
}


// function to calculate user's words per minute (speed)
void wpm(int total_number, double total_time) {
    double word_per_minute = total_number / total_time;         // calculating words per minute
    cout << fixed << setprecision(2);
    cout << CYAN << "Your Typing Speed: " << word_per_minute << " WPM\n";       // output speed in wpm
    cout << "Errors: " << error_count << "\n";                                  // output errors
}


int main() {

    enableANSI();           //enabling ansi for custom ui
    srand(time(0));         // using srand for a randomized prompt on each attempt

    // Intro to user with playbook
    typewriter(BOLDBLUE "\nCodeflow aims to help its users become accurate and fast typists, but hold your horses becuase speed is nothing without consistency. To be the best typist you can be, it is essential to first focus on your accuracy and then increase your speed from there on.\n "
        "\nCodeflow has 3 difficulty levels (Noob, Pro, Hacker).\n"
        "Achieving 4 Stars in accuracy in level 1 you can unlock level 2.\n"
        "By achieving 5 Stars in accuracy in any level you can unlock levels 2 and 3.\n"
        "Level 3 can only be unlocked by achieveing 5 stars in accuracy.\n"
        "Level 3 is the FINAL BOSS STAGE of the game giving you one shot to prove your skills in the final showdown.\n"
        "If your accuracy is reduced in later stages you can be DEPORTED back to level 1 or lock higher difficulty levels.\n"
        "With that said goodluck!\n\n"
        RESET, 15);

    //applying a loop because we need to continue the program until the user doesnt close it else just simple fuction calls and devising levels depending on the word banks
    while (true) {
        if (!unlock_2 && !unlock_3) {
            cout << CYAN << "\t------Level 1------\t\n";
            levels(words_easy, 10);
        }
        else if (unlock_2 && !unlock_3) {
            cout<< CYAN << "\t------Level 2------\t\n";
            levels(words_medium, 20);
        }
        else if (unlock_3) {
            press_enter_to_start();
            cout << CYAN << "\t------Level 3------\t\n";
            levels(words_hard, 30);
            cout << BOLDGREEN << "\nCongratulations you have completed the game!!!\n" << RESET;
            cout << BOLDYELLOW << "Satisfied with your score or would you like to try again?" << RESET;
            break;
        }
    }

    return 0;
}