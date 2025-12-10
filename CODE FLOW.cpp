#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <thread>
#include <vector>
#include <limits>
#include <atomic>
// ---------------- COLORS ----------------
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"



using namespace std;
using namespace std::chrono;

// ---------------- GLOBAL STATE ----------------
int unlock_2 = 0;
int unlock_3 = 0;
int error_count = 0;

// ---------------- WORD BANKS ----------------
//this is the word bank for the 1st level and is easy as hell
vector<string> words_easy = {
    "apple","ball","cat","dog","egg","fish","goat","hat","ice","jam","kite","lion","moon","nest","owl","pen","queen","rat","sun","tree","umbrella","van","wolf","xray","yarn","zebra","book","car","desk","ear","frog","game","hand","ink","jug","key","lamp","milk","net","orange","pig","quill","rope","ship","top","unit","vase","water","yard","zip","ant","bag","cup","door","eye","fan","gum","hill","iron","jar","kid","leaf","map","nose","oil","pan","quiz","ring","sock","tent","use","vote","wind","axe","young","zone","air","bed","coin","dust","elf","fire","gold","home","iceberg","joke","king","lake","man","nut","open","play","quiet","road","sand","time","up","voice","warm","year"
};
//this is the word bank for the 2nd lvl
vector <string> words_medium = {
    "abstract","balance","capture","decisive","elegant","fiction","generate","harmony","improve","justice","kingdom","language","maintain","neutral","observe","pattern","qualify","recover","significant","tension","upgrade","variety","wisdom","youthful","zealous","complex","deliver","enhance","frequent","glimmer","historic","identify","journey","kinetic","logical","migrate","notable","organize","perceive","quantify","reflect","sustain","transform","utilize","vivid","wonder","yield","zone","adventure","barrier","concept","dynamic","emerge","fluent","govern","heritage","illustrate","judgment","keen","liberty","modify","navigate","option","precise","qualitative","relevant","strategy","theory","ultimate","variable","welfare","analysis","boundary","cherish","dominate","emphasis","framework","gratitude","hypothesis","intense","justify","landscape","mechanism","notion","optimal","persuade","radiate","sequence","transition","versatile","withdraw","approximate","conclude","devote","expand","fortify","genuine","interpret","mediate","persist"
};
//this is the word bank for the third and most difficult level
vector<string> words_hard = {
    "aberration","abstruse","acquiesce","adjudicate","alacrity","amorphous","anachronistic","antithesis","apocryphal","arboreal","belligerent","cacophony","circumlocution","clandestine","cognizant","conflagration","conundrum","corporeal","credulous","deleterious","demagogue","denigrate","diaphanous","disparate","ebullient","eclectic","egregious","enervate","ephemeral","equanimity","esoteric","evanescent","exacerbate","fastidious","fortuitous","garrulous","grandiloquent","gregarious","hackneyed","iconoclast","idiosyncratic","impecunious","imperious","incontrovertible","indefatigable","ineffable","inexorable","ingratiate","insidious","inveterate","juxtaposition","lachrymose","laconic","lexicon","lugubrious","magnanimous","malevolent","mendacious","meticulous","moribund","nefarious","nonplussed","obfuscate","obsequious","omnipotent","opprobrium","parsimony","pejorative","perfunctory","peripatetic","perspicacious","phlegmatic","precarious","precipitous","predilection","premonition","prevaricate","proclivity","propensity","protuberant","quintessential","recalcitrant","recondite","recrimination","redolent","sagacious","salient","sanguine","solicitous","tenuous","trenchant","ubiquitous","unfathomable","vicissitude","vindicate","vitriolic","vociferous","zeitgeist","zephyr","zealotry"
};

// ---------------- UTILS ----------------
void press_enter_to_start()//the name of the function is enough but let me explain
{
    cin.clear();
    string dummy;//creating a dummy string so that we can press enter to start the lvls
    getline(cin, dummy);//this make it happens
}

// forward declaration
void levels(vector<string>, int);

// ---------------- LEVELING SYSTEM ----------------
void levelling_system()
{
    if (error_count == 0) {
        cout <<GREEN<< "Accuracy: *****\n";
        unlock_2 = 1;
        unlock_3 = 1;
    }
    else if (error_count <= 2) {
        cout <<GREEN<< "Accuracy: ****\n";
        unlock_2 = 1;
    }
    else if (error_count <= 5) {
        cout << GREEN << "Accuracy: ***\n";
        unlock_3 = 0;
    }
    else {
        cout << GREEN << "Accuracy: ** or *\n";
        unlock_2 = 0;
        unlock_3 = 0;
    }
}

// ---------------- WORD COUNT MODE ----------------
void levels(vector<string> word_bank, int total_number)
{
    error_count = 0;
    vector<string> selected;

    for (int i = 0; i < total_number; i++)
        selected.push_back(word_bank[rand() % word_bank.size()]);

    for (auto& w : selected) cout <<BOLD<< w << " ";
    cout << "\nPress Enter to start...";
    press_enter_to_start();

    cout << "\n3..."; this_thread::sleep_for(seconds(1));
    cout << "2..."; this_thread::sleep_for(seconds(1));
    cout << "1...\nStart!\n";

    auto start = steady_clock::now();

    for (int i = 0; i < total_number; i++) {
        string input;
        cin >> input;
        if (input != selected[i])
            error_count++;
    }

    auto stop = steady_clock::now();
    double minutes = duration_cast<milliseconds>(stop - start).count() / 60000.0;
    double wpm = total_number / minutes;

    cout << fixed << setprecision(2);
    cout << "WPM: " << wpm << "\n";
    cout << "Errors: " << error_count << "\n";

    levelling_system();
}

// ---------------- TIMED MODE ----------------
void level_timed(vector<string> word_bank, int time_limit)
{
    error_count = 0;
    int words_typed = 0;
    atomic<bool> running(true);//here  we define it as a bool but more diverse

    vector<string> selected;
    for (int i = 0; i < 200; i++)
        selected.push_back(word_bank[rand() % word_bank.size()]);

    for (auto& w : selected) cout << BOLD << w << " ";
    cout << "\nType for " << time_limit << " seconds\n";
    cout << "Press Enter to start...";
    press_enter_to_start();
    //create a thread that runs parallel in the main
    //[&] is used to capture everything by reference
    thread input_thread([&]() {
        size_t index = 0;//keeps tracks of the words user should type
        while (running && index < selected.size()) {//running is a type of bool you can say it is true if there is time and false if there is no time left
            string input;
            if (cin >> input) {//This doesnt block the function however if we just cin>> input in loop it might block the input 
                if (input != selected[index])//checking the input against the corrected words
                    error_count++;//increasing the error count if the input is not matched by the words in the lib
                words_typed++;//used to capture the number of words typed as it is a time  function so we need this to calculate WPM
                index++;
            }
        }
        });

    this_thread::sleep_for(seconds(time_limit));
    running = false;
    cin.clear();

    if (input_thread.joinable())//returns true or false depending on the q that is the thread joined or not if true than it prcoeeds
        input_thread.join();//this tells the thread to wait here until all the threads are complete

    press_enter_to_start();

    double minutes = time_limit / 60.0;
    double wpm = words_typed / minutes;
    double accuracy = (words_typed == 0)
        ? 0
        : ((words_typed - error_count) * 100.0) / words_typed;

    cout << fixed << setprecision(2);
    cout << "\nTime's up!\n";
    cout << "WPM: " << wpm << "\n";
    cout << "Accuracy: " << accuracy << "%\n";
    cout << "Errors: " << error_count << "\n";

    levelling_system();
}

// ---------------- MAIN ----------------
int main()
{//it is the same as calling random seeds but instead of just time 0 we use real life time
    srand(time(nullptr));//this make the wordbank random with the today time
    //everyday time change so does the sequence of the word_bank

    cout << CYAN<<"Codeflow aims to help its users become accurate and fast typists, but hold your horses becuase speed is nothing without consistency. To be the best typist you can be, it is essential to first focus on your accuracy and then increase your speed from there on. " << endl;
    cout << CYAN << endl;
    cout << CYAN << "Codeflow has 3 difficulty levels (Noob, Pro, Hacker)." << endl;
    cout << CYAN << "By achieving 4 Stars in accuracy in level 1 you can unlock level 2." << endl;
    cout << CYAN << "By achieving 5 Stars in accuracy in any level you can unlock levels 2 and 3." << endl;
    cout << CYAN << "Level 3 can only be unlocked by achieveing 5 stars in accuracy." << endl;
    cout << CYAN << "If your accuracy is reduced in later stages you can be DEPORTED back to level 1 or lock higher difficulty levels." << endl;
    cout << CYAN << "With that said goodluck!" << endl;

    cout << "Choose mode (Words / Time): ";
    string choice;
    cin >> choice;
    press_enter_to_start();

    if (choice == "Words") {
        levels(words_easy, 10);
        if (unlock_2) levels(words_medium, 15);
        if (unlock_3) levels(words_hard, 20);
    }
    else if (choice == "Time") {
        level_timed(words_easy, 60);
        if (unlock_2) level_timed(words_medium, 30);
        if (unlock_3) level_timed(words_hard, 15);
    }
    else {
        cout << CYAN << "Invalid choice\n";
    }

    cout << CYAN << "Game finished.\n";
    return 0;
}
