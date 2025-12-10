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

#define RESET   "\033[0m" //colors
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"
// initializing error count to 0
using namespace std;
using namespace std::chrono;

int unlock_2 = 0;
int unlock_3 = 0;
const int time_limit = 30;
int error_count;
void press_enter_to_start()
{
    cin.clear();
    string dummy;
    getline(cin, dummy);
}

void stop_function(int a) {
    this_thread::sleep_for(std::chrono::seconds(a)); // function to delay the count down by a second
}
void levels(vector <string> word_bank, int total_number);

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
void levelling_system()
{

    if (error_count == 0) {
        cout << "Accuracy: *****" << endl;
        if (unlock_2 == 1) {
            unlock_3 = 1;                                    // unlocking level 3
        }
        if (unlock_2 == 0) {
            press_enter_to_start();
            cout << "\t------Level 2------\t" << endl;       // move to level 2 if not unlocked
            levels(words_medium, 20);
            cout << endl;
        }
        else if (unlock_3 == 1) {    
            press_enter_to_start();// move to level 3 if level 2 cleared
            cout << "\t------Level 3------\t" << endl;
            levels(words_hard, 30);
            cout << endl;
        }
        unlock_2 = 1;                                       // unlocking level 2
    }
    else if (error_count >= 1 && error_count <= 2) {
        cout << "Accuracy: ****" << endl;
        unlock_2 = 1;                                       // unlocking level 2
        if (unlock_3 == 0) { 
            press_enter_to_start();// move to level 2 if level 3 is locked
            cout << "\t------Level 2------\t" << endl;
            levels(words_medium, 20);
            cout << endl;
        }
    }
    else if (error_count >= 3 && error_count <= 5) {
        cout << "Accuracy: ***" << endl;
        unlock_3 = 0;                                       // lock level 3
        if (unlock_2 == 1) {     
            press_enter_to_start();// move to level 2 if it is unlocked
            cout << "\t------Level 2------\t" << endl;
            levels(words_medium, 20);
            cout << endl;
        }
        else if (unlock_2 == 0) {  
            press_enter_to_start();// move to level 1 if level 2 is locked
            cout << "\t------Level 1------\t" << endl;
            levels(words_easy, 10);
            cout << endl;
        }
    }
    else if (error_count >= 6 && error_count <= 8) {
        cout << "Accuracy: **" << endl;
        unlock_2 = 0;                                       // lock level 2
        unlock_3 = 0; 
        press_enter_to_start();// lock level 3
        cout << "\t------Level 1------\t" << endl;
        levels(words_easy, 10);                              // return the user to level 1   
        cout << endl;
    }
    else if (error_count >= 9) {
        cout << "Accuracy: *" << endl;
        unlock_2 = 0;                                       // lock level 2
        unlock_3 = 0;  
        press_enter_to_start();// lock level 3
        cout << "\t------Level 1------\t" << endl;
        levels(words_easy, 10);                             // return the user to level 1 
        cout << endl;
    }
}
void levels(vector <string> word_bank, int total_number) {
    error_count = 0;
    vector<string> selected_words;                 // vector for our randomized words prompt

    for (int i = 0; i < total_number; i++) {
        int index = rand() % word_bank.size();              // generating random words
        selected_words.push_back(word_bank[index]);         // appending the words to the selected words vector 
    }

    for (const auto& w : selected_words) {
        cout << w << " ";                       //displaying the selected words
    }

    cout << endl;
    cout << "------- Start Typing -------" << endl;
    cout << endl;


    cout << "Press Enter to start ... ";
    press_enter_to_start();       //this line allows the user to press enter to start, actually it just ignores the input from the user at this line and when we press enter the code continues and the next line is excuted
    cout << endl;
    // delaying the countdown
    cout << "3...."; this_thread::sleep_for(chrono::seconds(1));
    cout << "2...."; this_thread::sleep_for(chrono::seconds(1));
    cout << "1...."; this_thread::sleep_for(chrono::seconds(1));
    cout << endl;
    cout << "Start";
    cout << endl;


    auto start = steady_clock::now();       // starting the timer after the count down

    for (int i = 0; i < total_number; i++) {
        string input;           // using a string to get input because vectors dont allow direct input like that of arrays
        cin >> input;
        if (input != selected_words[i]) {
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
    levelling_system();

}



int main() {

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

    //applying a loop because we need to continue the program until the user doesnt close it else just simple fuction calls and devising levels depending on the word banks {
        while (true) {
            if (!unlock_2 && !unlock_3) {
                cout << "\t------Level 1------\t\n";
                levels(words_easy, 10);
            }
            else if (unlock_2 && !unlock_3) {
                cout << "\t------Level 2------\t\n";
                levels(words_medium, 20);
            }
            else if (unlock_3) {
                cout << "\t------Level 3------\t\n";
                levels(words_hard, 30);
                break;
            }
        }
    
   

    cout << "Congrats you have completed the game" << endl;

    return 0;

}
//#include <iostream>
//#include <string>
//#include <cstdlib>
//#include <ctime>
//#include <chrono>
//#include <iomanip>
//#include <thread>
//#include <vector>
//#include <limits>
//#include <atomic>
//// ---------------- COLORS ----------------

//
//
//
//using namespace std;
//using namespace std::chrono;
//
//// ---------------- GLOBAL STATE ----------------
//int unlock_2 = 0;
//int unlock_3 = 0;
//int error_count = 0;
//
//// ---------------- WORD BANKS ----------------
////this is the word bank for the 1st level and is easy as hell
//vector<string> words_easy = {
//    "apple","ball","cat","dog","egg","fish","goat","hat","ice","jam","kite","lion","moon","nest","owl","pen","queen","rat","sun","tree","umbrella","van","wolf","xray","yarn","zebra","book","car","desk","ear","frog","game","hand","ink","jug","key","lamp","milk","net","orange","pig","quill","rope","ship","top","unit","vase","water","yard","zip","ant","bag","cup","door","eye","fan","gum","hill","iron","jar","kid","leaf","map","nose","oil","pan","quiz","ring","sock","tent","use","vote","wind","axe","young","zone","air","bed","coin","dust","elf","fire","gold","home","iceberg","joke","king","lake","man","nut","open","play","quiet","road","sand","time","up","voice","warm","year"
//};
////this is the word bank for the 2nd lvl
//vector <string> words_medium = {
//    "abstract","balance","capture","decisive","elegant","fiction","generate","harmony","improve","justice","kingdom","language","maintain","neutral","observe","pattern","qualify","recover","significant","tension","upgrade","variety","wisdom","youthful","zealous","complex","deliver","enhance","frequent","glimmer","historic","identify","journey","kinetic","logical","migrate","notable","organize","perceive","quantify","reflect","sustain","transform","utilize","vivid","wonder","yield","zone","adventure","barrier","concept","dynamic","emerge","fluent","govern","heritage","illustrate","judgment","keen","liberty","modify","navigate","option","precise","qualitative","relevant","strategy","theory","ultimate","variable","welfare","analysis","boundary","cherish","dominate","emphasis","framework","gratitude","hypothesis","intense","justify","landscape","mechanism","notion","optimal","persuade","radiate","sequence","transition","versatile","withdraw","approximate","conclude","devote","expand","fortify","genuine","interpret","mediate","persist"
//};
////this is the word bank for the third and most difficult level
//vector<string> words_hard = {
//    "aberration","abstruse","acquiesce","adjudicate","alacrity","amorphous","anachronistic","antithesis","apocryphal","arboreal","belligerent","cacophony","circumlocution","clandestine","cognizant","conflagration","conundrum","corporeal","credulous","deleterious","demagogue","denigrate","diaphanous","disparate","ebullient","eclectic","egregious","enervate","ephemeral","equanimity","esoteric","evanescent","exacerbate","fastidious","fortuitous","garrulous","grandiloquent","gregarious","hackneyed","iconoclast","idiosyncratic","impecunious","imperious","incontrovertible","indefatigable","ineffable","inexorable","ingratiate","insidious","inveterate","juxtaposition","lachrymose","laconic","lexicon","lugubrious","magnanimous","malevolent","mendacious","meticulous","moribund","nefarious","nonplussed","obfuscate","obsequious","omnipotent","opprobrium","parsimony","pejorative","perfunctory","peripatetic","perspicacious","phlegmatic","precarious","precipitous","predilection","premonition","prevaricate","proclivity","propensity","protuberant","quintessential","recalcitrant","recondite","recrimination","redolent","sagacious","salient","sanguine","solicitous","tenuous","trenchant","ubiquitous","unfathomable","vicissitude","vindicate","vitriolic","vociferous","zeitgeist","zephyr","zealotry"
//};
//
//// ---------------- UTILS ----------------
//void press_enter_to_start()//the name of the function is enough but let me explain
//{
//    cin.clear();
//    string dummy;//creating a dummy string so that we can press enter to start the lvls
//    getline(cin, dummy);//this make it happens
//}
//
//// forward declaration
//void levels(vector<string>, int);
//
//// ---------------- LEVELING SYSTEM ----------------
//void levelling_system()
//{
//    if (error_count == 0) {
//        cout <<GREEN<< "Accuracy: *****\n";
//        unlock_2 = 1;
//        unlock_3 = 1;
//    }
//    else if (error_count <= 2) {
//        cout <<GREEN<< "Accuracy: ****\n";
//        unlock_2 = 1;
//    }
//    else if (error_count <= 5) {
//        cout << GREEN << "Accuracy: ***\n";
//        unlock_3 = 0;
//    }
//    else {
//        cout << GREEN << "Accuracy: ** or *\n";
//        unlock_2 = 0;
//        unlock_3 = 0;
//    }
//}
//
//// ---------------- WORD COUNT MODE ----------------
//void levels(vector<string> word_bank, int total_number)
//{
//    error_count = 0;
//    vector<string> selected;
//
//    for (int i = 0; i < total_number; i++)
//        selected.push_back(word_bank[rand() % word_bank.size()]);
//
//    for (auto& w : selected) cout <<BOLD<< w << " ";
//    cout << "\nPress Enter to start...";
//    press_enter_to_start();
//
//    cout << "\n3..."; this_thread::sleep_for(seconds(1));
//    cout << "2..."; this_thread::sleep_for(seconds(1));
//    cout << "1...\nStart!\n";
//
//    auto start = steady_clock::now();
//
//    for (int i = 0; i < total_number; i++) {
//        string input;
//        cin >> input;
//        if (input != selected[i])
//            error_count++;
//    }
//
//    auto stop = steady_clock::now();
//    double minutes = duration_cast<milliseconds>(stop - start).count() / 60000.0;
//    double wpm = total_number / minutes;
//
//    cout << fixed << setprecision(2);
//    cout << "WPM: " << wpm << "\n";
//    cout << "Errors: " << error_count << "\n";
//
//    levelling_system();
//}
//
//// ---------------- TIMED MODE ----------------
//void level_timed(vector<string> word_bank, int time_limit)
//{
//    error_count = 0;
//    int words_typed = 0;
//    atomic<bool> running(true);//here  we define it as a bool but more diverse
//

//    cout << "\nType for " << time_limit << " seconds\n";
//    cout << "Press Enter to start...";
//    press_enter_to_start();
//    //create a thread that runs parallel in the main
//    //[&] is used to capture everything by reference
//    thread input_thread([&]() {
//        size_t index = 0;//keeps tracks of the words user should type
//        while (running && index < selected.size()) {//running is a type of bool you can say it is true if there is time and false if there is no time left
//            string input;
//            if (cin >> input) {//This doesnt block the function however if we just cin>> input in loop it might block the input 
//                if (input != selected[index])//checking the input against the corrected words
//                    error_count++;//increasing the error count if the input is not matched by the words in the lib
//                words_typed++;//used to capture the number of words typed as it is a time  function so we need this to calculate WPM
//                index++;
//            }
//        }
//        });
//
//    this_thread::sleep_for(seconds(time_limit));
//    running = false;
//    cin.clear();
//
//    if (input_thread.joinable())//returns true or false depending on the q that is the thread joined or not if true than it prcoeeds
//        input_thread.join();//this tells the thread to wait here until all the threads are complete
//
//    press_enter_to_start();
//
//    double minutes = time_limit / 60.0;
//    double wpm = words_typed / minutes;
//    double accuracy = (words_typed == 0)
//        ? 0
//        : ((words_typed - error_count) * 100.0) / words_typed;
//
//    cout << fixed << setprecision(2);
//    cout << "\nTime's up!\n";
//    cout << "WPM: " << wpm << "\n";
//    cout << "Accuracy: " << accuracy << "%\n";
//    cout << "Errors: " << error_count << "\n";
//
//    levelling_system();
//}
//
//// ---------------- MAIN ----------------
//int main()
//{//it is the same as calling random seeds but instead of just time 0 we use real life time
//    srand(time(nullptr));//this make the wordbank random with the today time
//    //everyday time change so does the sequence of the word_bank
//
//    cout << CYAN<<"Codeflow aims to help its users become accurate and fast typists, but hold your horses becuase speed is nothing without consistency. To be the best typist you can be, it is essential to first focus on your accuracy and then increase your speed from there on. " << endl;
//    cout << CYAN << endl;
//    cout << CYAN << "Codeflow has 3 difficulty levels (Noob, Pro, Hacker)." << endl;
//    cout << CYAN << "By achieving 4 Stars in accuracy in level 1 you can unlock level 2." << endl;
//    cout << CYAN << "By achieving 5 Stars in accuracy in any level you can unlock levels 2 and 3." << endl;
//    cout << CYAN << "Level 3 can only be unlocked by achieveing 5 stars in accuracy." << endl;
//    cout << CYAN << "If your accuracy is reduced in later stages you can be DEPORTED back to level 1 or lock higher difficulty levels." << endl;
//    cout << CYAN << "With that said goodluck!" << endl;
//
//    cout << "Choose mode (Words / Time): ";
//    string choice;
//    cin >> choice;
//    press_enter_to_start();
//
//    if (choice == "Words") {
//        levels(words_easy, 10);
//        if (unlock_2) levels(words_medium, 15);
//        if (unlock_3) levels(words_hard, 20);
//    }
//    else if (choice == "Time") {
//        level_timed(words_easy, 60);
//        if (unlock_2) level_timed(words_medium, 30);
//        if (unlock_3) level_timed(words_hard, 15);
//    }
//    else {
//        cout << CYAN << "Invalid choice\n";
//    }
//
//    cout << CYAN << "Game finished.\n";
//    return 0;
//}
