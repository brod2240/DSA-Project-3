#include <fstream>
#include <sstream>
#include <chrono>
#include <queue>
#include <limits>
#include "AdjacencyList.h"

// Adjacency list implementation
void printMenu();
constexpr wchar_t * const texts[] = { // Need this for special characters
  L"Ñá", //Spanish
  L"forêt intérêt", //French
  L"Gesäß", //German
  L"取消波蘇日奇諾", //Chinese
  L"日本人のビット", //Japanese
  L"немного русский", //Russian
  L"ένα κομμάτι της ελληνικής", // Greek
  L"ਯੂਨਾਨੀ ਦੀ ਇੱਕ ਬਿੱਟ", // Punjabi 
  L"کمی از ایران ", // Persian 
  L"కానీ ఈ ఏమి నరకం ఉంది?", //Telugu 
  L"Но какво, по дяволите, е това?" //Bulgarian
};

int main()  
{ 
    //locale::global(locale(""));
    //wcout.imbue(locale());
    string line;
    bool programRunning = true;
    int option = -1;
    int numOfFiles = 18;
    AdjacencyList list;

    auto start = chrono::steady_clock::now();
    for(int i = 0;i < numOfFiles;i++) // File input for csv
    {
        ifstream inFile("CSV/file" + to_string(i) + ".csv");
        string tokens[3];
        if(inFile.is_open())
        {
            getline(inFile,line);
            int i = 0;
            // Break each line into the form of from, to, weight tokens to enter into graph
            while(getline(inFile,line))
            {
                istringstream stream(line);
                for(int j = 0; j < 3; j++)
                    getline(stream,tokens[j],',');
                string from = tokens[0];
                string to = tokens[1];
                double weight = stod(tokens[2]);
                list.insert(from,to,weight);           
            }
        }
    } 
    //list.printTest("POPULAR");
    cout << right << setw(35) << "WELCOME TO OUR PROJECT" << endl << endl;
    // Menu implementation for user
    while(programRunning)
    {    
        string name;
        printMenu();
        cin >> option;

        // Option to search related artist, search most popular related artists, search most niche related artists.
        switch(option)
        {
            case 0:
            programRunning = false;
            cout << "THANK YOU FOR USING OUR PROGRAM" << endl;
            break;
            case 1:
            list.search();
            break;
            case 2:
            list.mostPop();
            break;
            case 3:
            list.mostNiche();
            break;     
            default:
            cout << left << setw(20) << "INVALID INPUT, TRY AGAIN" << endl;
            break;
        }

        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    auto end = chrono::steady_clock::now();

    cout << "Elapsed time in seconds: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " milliseconds" <<endl;
    return 0;
} 
void printMenu() 
{
    cout << endl << right << setw(25) << "RELATED ARTIST GRAPH" << endl << endl;
    cout << left << setw(20) << "SELECT AN OPTION:" << endl << endl;
    cout << left << setw(20) << "1: SEARCH AN ARTIST" << endl;
    cout << left << setw(20) << "2: TOP TEN MOST POPULAR RELATED ARTISTS" << endl;
    cout << left << setw(20) << "3: TOP TEN MOST NICHE RELATED ARTISTS" << endl;
    cout << left << setw(20) << "0: EXIT" << endl;
}