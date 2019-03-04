// Nigel Lipps
// match permutations

#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
#include <string>

#include <sstream>
#include <cassert>
#include <algorithm>
#include <csignal>

using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in

long int sizeDict(string dict[]){
    cout << dict->size() << endl;
    return dict->size();
}
int dictionaryReader(istream &dictfile, string dict[]){
/*
 Places each string in dictfile into the array dict. Returns the number of
 words read into dict. This number should not be larger than MAXDICTWORDS since
 that is the size of the array.
 */
    if (dictfile.peek() == EOF || sizeDict(dict) >= MAXDICTWORDS)
        return 0;
//add an if else statement as a condition for handling maximum?
    dictfile >> dict[0];
    return dictionaryReader(dictfile, dict+1) + 1;
};

void pLoop(string& arr, int low, int high, int pivot, int& i){
    
    if (low < high){
        // If current element is smaller than or
        // equal to pivot
        if (arr[low] <= pivot){
            i++;

            char ch = arr[low];
            arr[low] = arr[i];
            arr[i] = ch;
        }
        
        pLoop(arr, low+1, high, pivot, i);
    }
    return;
}

int partition (string& arr, int low, int high){
    int pivot = arr[high];    //taking the last element as pivot
    int i = (low - 1);
    
    pLoop(arr, low, high, pivot, i);

    char ch = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = ch;
    
    return (i + 1);
}

void quickSort(string& arr, int low, int high){
    if (low < high){
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void loop(string word, const string dict[], int size, string results[], string sortedInput, int& x){
    if (size > 0){
        if (word.length() == dict[size].length()){
            string temp = dict[size];
            quickSort(temp, 0, (int)temp.length() - 1);
            
//add to this if statement a condition for over maximum array?
//if max is hit, exit the loop?
            if (sortedInput == temp)
                results[x++] = dict[size];
        }
        loop(word, dict, size - 1, results, sortedInput, x);
    }
    
    return;
}

int recurCombos(string word, const string dict[], int size, string results[]){
    
    string sortedInput = word;
    quickSort(sortedInput, 0, (int)sortedInput.length() - 1);
    
    int x = 0;
    
    loop(word, dict, size - 1, results, sortedInput, x);

    return x;
};

void recursiveDisp(const string results[], int size){ //done
/*
 Displays size number of strings from results. The results can be printed in
 any order.
 */
    if (size == 0)
        return;
    cout << results[0] << endl;
    recursiveDisp(results + 1, size-1);
};

//int main() {
//    string results[MAXRESULTS];
//    string dict[MAXDICTWORDS];
//    ifstream dictfile; // file containing the list of words
//    int nwords;        // number of words read from dictionary
//    string word;
//    dictfile.open("/Users/nigellipps/Desktop/CS2/NLipps-CS2-140-A5realDeal/NLipps-CS2-140-A5realDeal/wordss.txt");
//    if (!dictfile) {
//        cout << "File not found!" << endl;
//        return (1);
//    }
//    nwords = dictionaryReader(dictfile, dict);
//    cout << "Please enter a string for an anagram: ";
//    cin >> word;
//    int numMatches = recurCombos(word, dict, nwords, results);
//    if (!numMatches)
//        cout << "No matches found" << endl;
//    else
//        recursiveDisp(results, numMatches);
//return 0;
//}
void testone(int n)
{
    string dictionary[MAXDICTWORDS];
    string results[MAXRESULTS];
    
    switch (n)
    {
        default: {
            cout << "Bad argument" << endl;
        } break; case  1: {
            istringstream iss("dog\ncat\nrat\neel\ntar\nart\nlee\nact\ngod");
            int numResults = dictionaryReader(iss, dictionary);
            sort(dictionary, dictionary + numResults);
            assert(numResults == 9 && dictionary[0] == "act" && dictionary[1] == "art");
        } break; case  2: {
            // File is empty, Checks that file is empty and dictionaryReader returns 0.
            istringstream iss("");
            int numResults = dictionaryReader(iss, dictionary);
            assert(numResults == 0 && dictionary[0] == "");
        } break; case  3: {
            // Dictionary has been read properly
            istringstream iss("dog\ncat\nrat\neel\ntar\nart\nlee\nact\ngod");
            int numResults = dictionaryReader(iss, dictionary);
            sort(dictionary, dictionary + numResults);
            assert(numResults == 9 && dictionary[0] == "act" && dictionary[numResults - 1] == "tar");
        } break; case  4: {
            // Input file is larger than the dictionary size
            istringstream iss("dog\ncat\nrat\neel\ntar\nart\nlee\nact\ngod\ntoo\nmany\nwords");
            int numResults = dictionaryReader(iss, dictionary);
            sort(dictionary, dictionary + numResults);
            assert(numResults == 10 && dictionary[MAXDICTWORDS - 1] == "too");
        } break; case  5: {
            // If a certain word with repeated letter is shown in results more than once - still accept.
            string dictionary[] = { "one", "oone", "ne", "e", "too" };
            int numResults = recurCombos("oto", dictionary, 5, results);
            assert((numResults == 1 || numResults == 2) && results[0] == "too");
        } break; case  6: {
            // Doesn't check numResults nor duplicates.
            string dictionary[] = { "one", "oone", "ne", "e", "too" };
            recurCombos("oto", dictionary, 5, results);
            assert(results[0] == "too");
        } break; case  7: {
            // If word wasn't found, numResults = 0 and results array is empty.
            string dictionary[] = { "one", "oone", "ne", "e" };
            int numResults = recurCombos("look", dictionary, 4, results);
            assert(numResults == 0 && results[0] == "" && results[1] == "");
        } break; case  8: {
            // No fraction of a permutation is being searched in dictionary
            string dictionary[] = { "one", "oone", "non", "oon" };
            int numResults = recurCombos("on", dictionary, 4, results);
            assert(numResults == 0 && results[0] == "" && results[1] == "");
        } break; case  9: {
            // No fraction of a permutation is being searched in dictionary
            string dictionary[] = { "one", "oone", "ne", "e", "neoo", "oneo" };
            int numResults = recurCombos("neo", dictionary, 6, results);
            assert(numResults == 1 && results[0] == "one" && results[1] == "");
        } break; case  10: {
            // Checking that no error occurs if more than MAXRESULTS are found.
            string dictionary[] = { "true",  "treu", "teru", "teur", "ture",
                "tuer", "rtue", "rteu", "retu","reut", "ruet", "rute", "utre",
                "uter", "uetr", "uert", "urte", "uret", "etru", "etur", "ertu",
                "erut", "eurt", "eutr" };
            // All 24 permutations
            int numResults = recurCombos("true", dictionary, 24, results);
            assert(numResults == MAXRESULTS);
        } break; case  11: {
            // Checking one word was found, no duplicates.
            string dictionary[] = { "ppp" };
            int numResults = recurCombos("ppp", dictionary, 1, results);
            assert(numResults == 1 && results[0] == "ppp" && results[1] == "");
        } break; case  12: {
            string dictionary[] = { "run", "dodge", "break", "urn", "defeat" };
            int numResults = recurCombos("nru", dictionary, 5, results);
            sort(results, results + numResults);
            assert(numResults == 2 && results[0] == "run" && results[1] == "urn");
        } break; case  13: {
            streambuf* oldCoutStreamBuf = cout.rdbuf();
            ostringstream strCout;
            cout.rdbuf(strCout.rdbuf());
            string results[] = { "cat", "act" };
            recursiveDisp(results, 2);
            cout.rdbuf(oldCoutStreamBuf);
            string temp = strCout.str();
            bool match1 = temp.find("act") != string::npos;
            bool match2 = temp.find("cat") != string::npos;
            assert(match1 && match2);
        } break; case  14: {
            istringstream iss("tier\nrite\nbate\ntire\nttir");
            int numWords = dictionaryReader(iss, dictionary);
            sort(dictionary, dictionary + numWords);
            assert(numWords == 5 && dictionary[0] == "bate");
            int numResults = recurCombos("tier", dictionary, numWords, results);
            assert(numResults == 3 && (results[2] == "tire" || results[2] == "tier" || results[2] == "rite"));
        } break; case  15: {
            string example[] = { "kool", "moe", "dee" };
            int numResults = recurCombos("look", example, 3, results);
            assert(numResults == 1 && results[0] == "kool");
        } break;
    }
}

int main()
{
    cout << "Enter test number: ";
    int n;
    cin >> n;
    testone(n);
    cout << "Passed" << endl;
    
}

/*
 4. Check that dictionaryReader handles an input file larger than the dictionary array properly
 
 9. Check that recurCombos for the word "neo" returns "one" for the results and no other fractional results
  CHECK NUM RESULTS
 10. Check that recurCombos handles a word that returns more permutations than the maximum the results array can handle
 
 11. Check that one word was found with no duplicates
 ?
 12. Check that recurCombos for the word "nru" returns both "run" and "urn", as well as number of results equal to 2
 CHECK NUM RESULTS
 15. Verify the recurCombos function works on an example results array properly
 ?
 */
