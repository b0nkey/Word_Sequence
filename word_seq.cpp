#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
// For some reason, these two are needed on Windows machines but not on Mac
// #include <time.h>
// #include <math.h>
using namespace std;

// ~~~~~~ WORDSEQ CLASS ~~~~~~
class WordSeq{
private:
    unordered_map<string,int> sequences;
    vector<pair<string, int>> printVec;
    int seqStart, seqEnd;

public:
    WordSeq(int, int, string); // default constructor
    void populate(string);
    void printResults();
};


struct sortCond{ // Sort condition. Couldnt find a cleaner solution.
    bool operator()(const pair<string,int> &left, const pair<string,int> &right){
        return left.second > right.second; 
    }
};

WordSeq::WordSeq(int start, int end, string fileName){
    clock_t c_start = clock();

    seqStart = start;
    seqEnd = end;
    populate("dictionary.txt");
    printResults();


    clock_t c_end = clock();
    double elapsed = double(c_end - c_start)/CLOCKS_PER_SEC;
    cout << "CPU time: " << elapsed << endl;
}

void WordSeq::populate(string fileName){
    ifstream f(fileName);
    if(!f){
        cout<<"Error opening output file"<<endl;
        exit(0);
    }

    while(!f.eof()){
        string s;
        f >> s;

        // Adds every possible sequence within range to the seq map
        for(int left=0; left<s.length()-1; left++){
            for(int right=left+seqStart; right<=s.length(); right++){
                int r = right-left;
                string sub = s.substr(left, r);
                sequences[sub]++; // will add one to sub.second if it exists
            }
        }
    }
}

void WordSeq::printResults(){
    for(int i=seqStart; i<=seqEnd; i++){ // For range of sequences
        for(auto &e:sequences) // For each sub string in sequences map
            if(e.first.length() == i)  printVec.push_back(e);
        sort(printVec.begin(), printVec.end(), sortCond());

        cout << "\nFound " << printVec.size() << " sub-sequences of length " << i << endl;

        for(int j=9; j>=0; j--)
            cout << printVec[j].first << " - " << printVec[j].second << endl;
        printVec.clear();
    }
}



// ~~~~~~ MAIN FUNCTION ~~~~~~
int main(){
    WordSeq w(2,5, "dictionary.txt");
    return 0;
}