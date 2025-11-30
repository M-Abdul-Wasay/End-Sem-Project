#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <iomanip>
#include<thread>
#include<vector>

using namespace std;
using namespace std::chrono;

int unlock_2 = 0;
int unlock_3 = 0;

void stop_fucntion(int a){
    this_thread::sleep_for(std::chrono::seconds(a)); // function to delay the count down by a second
}

// Word bank for level 1 (easy)
vector<string> words_easy = {
    "apple","ball","cat","dog","egg","fish","goat","hat","ice","jam","kite","lion","moon","nest","owl","pen","queen","rat","sun","tree","umbrella","van","wolf","xray","yarn","zebra","book","car","desk","ear","frog","game","hand","ink","jug","key","lamp","milk","net","orange","pig","quill","rope","ship","top","unit","vase","water","yard","zip","ant","bag","cup","door","eye","fan","gum","hill","iron","jar","kid","leaf","map","nose","oil","pan","quiz","ring","sock","tent","use","vote","wind","axe","young","zone","air","bed","coin","dust","elf","fire","gold","home","iceberg","joke","king","lake","man","nut","open","play","quiet","road","sand","time","up","voice","warm","year"
};

// Word bank for level 2 (medium)
vector <string> words_medium = {
    "abstract","balance","capture","decisive","elegant","fiction","generate","harmony","improve","justice","kingdom","language","maintain","neutral","observe","pattern","qualify","recover","significant","tension","upgrade","variety","wisdom","youthful","zealous","complex","deliver","enhance","frequent","glimmer","historic","identify","journey","kinetic","logical","migrate","notable","organize","perceive","quantify","reflect","sustain","transform","utilize","vivid","wonder","yield","zone","adventure","barrier","concept","dynamic","emerge","fluent","govern","heritage","illustrate","judgment","keen","liberty","modify","navigate","option","precise","qualitative","relevant","strategy","theory","ultimate","variable","welfare","analysis","boundary","cherish","dominate","emphasis","framework","gratitude","hypothesis","intense","justify","landscape","mechanism","notion","optimal","persuade","radiate","sequence","transition","versatile","withdraw","approximate","conclude","devote","expand","fortify","genuine","interpret","mediate","persist"
};

// Word bank for level 3 (hard)
vector<string> words_hard = {
    "aberration","abstruse","acquiesce","adjudicate","alacrity","amorphous","anachronistic","antithesis","apocryphal","arboreal","belligerent","cacophony","circumlocution","clandestine","cognizant","conflagration","conundrum","corporeal","credulous","deleterious","demagogue","denigrate","diaphanous","disparate","ebullient","eclectic","egregious","enervate","ephemeral","equanimity","esoteric","evanescent","exacerbate","fastidious","fortuitous","garrulous","grandiloquent","gregarious","hackneyed","iconoclast","idiosyncratic","impecunious","imperious","incontrovertible","indefatigable","ineffable","inexorable","ingratiate","insidious","inveterate","juxtaposition","lachrymose","laconic","lexicon","lugubrious","magnanimous","malevolent","mendacious","meticulous","moribund","nefarious","nonplussed","obfuscate","obsequious","omnipotent","opprobrium","parsimony","pejorative","perfunctory","peripatetic","perspicacious","phlegmatic","precarious","precipitous","predilection","premonition","prevaricate","proclivity","propensity","protuberant","quintessential","recalcitrant","recondite","recrimination","redolent","sagacious","salient","sanguine","solicitous","tenuous","trenchant","ubiquitous","unfathomable","vicissitude","vindicate","vitriolic","vociferous","zeitgeist","zephyr","zealotry"
};
// using vectors instead of arrays as vectors allow the index to be a variable

void levels(vector <string> word_bank, int total_number){
    int error_count = 0;                           // initializing error count to 0
    vector<string> selected_words;                 // vector for our randomized words prompt

    for (int i = 0; i < total_number; i++){
        int index = rand() % word_bank.size();              // generating random words
        selected_words.push_back(word_bank[index]);         // appending the words to the selected words vector 
    }

    for (const auto& w : selected_words){
        cout << w << " ";                       //displaying the selected words
    }

    cout << endl;
    cout << "------- Start Typing -------" << endl;
    cout << endl;


    cout << "Press Enter to start ... ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');        //this line allows the user to press enter to start, actually it just ignores the input from the user at this line and when we press enter the code continues and the next line is excuted
    cout << endl;
    // delaying the countdown
    cout << "1...."; this_thread::sleep_for(chrono::seconds(1));
    cout << "2...."; this_thread::sleep_for(chrono::seconds(1));
    cout << "3...."; this_thread::sleep_for(chrono::seconds(1));
    cout << endl;

    auto start = steady_clock::now();       // starting the timer after the count down
    for (int i = 0; i < total_number; i++){
        string input;           // using a string to get input because vectors dont allow direct input like that of arrays
        cin >> input;
        if (input != selected_words[i]){
            error_count++;                  // incrementing error count for each spelling mistake
        }
    }
    
    auto stop = steady_clock::now();            // stopping the timer when all the input are taken from the user
    auto time_elapsed = stop - start;           // calculating time taken 
    cout << endl;
    auto total_time = duration_cast<milliseconds>(time_elapsed).count() / 60000.0;          //converting milliseconds to minutes

    double word_per_minute = (total_number / total_time);                           // calculating words per minute
    cout << fixed << setprecision(2);       // setting result to 2 decimal places
    cout << "Your Typing speed is " << word_per_minute << " WPM" << endl;           // words per min output
    cout << "The amount of error in your typing are : " << error_count << endl;     // accuracy errors output

    // Leveling system
    if (error_count == 0) {
        cout << "Accuracy: *****" << endl;
        if (unlock_2 == 1) {
            unlock_3 = 1;                                    // unlocking level 3
        }
        if (unlock_2 == 0) {
            cout << "\t------Level 2------\t" << endl;       // move to level 2 if not unlocked
            levels(words_medium, 20);
            cout << endl;
        }
        else if (unlock_3 == 1) {                             // move to level 3 if level 2 cleared
            cout << "\t------Level 3------\t" << endl;
            levels(words_hard, 30);
            cout << endl;
        }
        unlock_2 = 1;                                       // unlocking level 2
    }
    else if (error_count >= 1 && error_count <= 2) {
        cout << "Accuracy: ****" << endl;
        unlock_2 = 1;                                       // unlocking level 2
        if (unlock_3 == 0) {                                 // move to level 2 if level 3 is locked
            cout << "\t------Level 2------\t" << endl;
            levels(words_medium, 20);
            cout << endl;
        }
    }
    else if (error_count >= 3 && error_count <= 5) {
        cout << "Accuracy: ***" << endl;
        unlock_3 = 0;                                       // lock level 3
        if (unlock_2 == 1) {                                 // move to level 2 if it is unlocked
            cout << "\t------Level 2------\t" << endl;
            levels(words_medium, 20);
            cout << endl;
        }
        else if (unlock_2 == 0){                          // move to level 1 if level 2 is locked
            cout << "\t------Level 1------\t" << endl;
            levels(words_easy, 10);
            cout << endl;
        }
    }
    else if (error_count >= 6 && error_count <= 8) {
        cout << "Accuracy: **" << endl;
        unlock_2 = 0;                                       // lock level 2
        unlock_3 = 0;                                       // lock level 3
        cout << "\t------Level 1------\t" << endl;
        levels(words_easy, 10);                              // return the user to level 1   
        cout << endl;
    }
    else if (error_count >= 9) {
        cout << "Accuracy: *" << endl;
        unlock_2 = 0;                                       // lock level 2
        unlock_3 = 0;                                       // lock level 3
        cout << "\t------Level 1------\t" << endl;
        levels(words_easy, 10);                             // return the user to level 1 
        cout << endl;
    }
}



int main(){

    // using srand for a randomized prompt on each attempt
    srand(time(0));

    // Intro to user with playbook
    cout << "Codeflow aims to help its users become accurate and fast typists, but hold your horses becuase speed is nothing without consistency. To be the best typist you can be, it is essential to first focus on your accuracy and then increase your speed from there on. " << endl;
    cout << endl;
    cout << "Codeflow has 3 difficulty levels (Noob, Pro, Hacker)." << endl;
    cout << "By achieving 4 Stars in accuracy in level 1 you can unlock level 2." << endl;
    cout << "By achieving 5 Stars in accuracy in any level you can unlock levels 2 and 3." << endl;
    cout << "Level 3 can only be unlocked by achieveing 5 stars in accuracy." << endl;
    cout << "If your accuracy is reduced in later stages you can be DEPORTED back to level 1 or lock higher difficulty levels." << endl;
    cout << "With that said goodluck!" << endl;

    cout << "\t------Level 1------\t" << endl;
    
    //applying a loop because we need to continue the program until the user doesnt close it else just simple fuction calls and devising levels depending on the word banks
    while (true){
        if (unlock_2 == 0){             // checking if level 2 is locked
            levels(words_easy, 10);
        }
        else if (unlock_2 == 1 && unlock_3 == 0){       // checking if level 2 in unlocked and level 3 is locked
            levels(words_medium, 20);
        }
        else if (unlock_3 == 1){                        // checking if level 3 is unlocked
            levels(words_hard, 30);
        }
    }

    return 0;
}