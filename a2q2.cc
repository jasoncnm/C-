#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[]) {
    int Votes = 0;
    if (argc >= 2)
    {
        string Arg = argv[1];
        istringstream ss{Arg};
        ss >> Votes;
    }
    bool IsCandidate = true;
    string Input;
    int CandidateNumber = 0;
    int Voters = 0;
    int ValidBallots = 0;
    int SpoiltBallots = 0;
    int Integer;
    string Candidate;
    string Score;
    while (getline(cin, Input))
    {
        istringstream I{Input};
        if (I >> Integer)
        {
            if (argc < 2)
            {
                Votes = CandidateNumber;
            }
            IsCandidate = false;
            int Sum = Integer;
            int Count =  1;
            Voters++;
            while (I >> Integer)
            {
                Sum += Integer;
                Count++;
            }
            if (Count == CandidateNumber && Sum <= Votes)
            {
                ValidBallots++;
                Score += Input + "\n";
            }
            else 
            {
                SpoiltBallots++;
            }
        }
        else if (IsCandidate)
        {
            Candidate += Input + "\n";
            CandidateNumber++;
        }
        else 
        {
            Voters++;
            SpoiltBallots++;
        }
    }

    int x;
    istringstream S{Score};
    int Array[CandidateNumber] = {0};
    int Counter = 0;
    while (S >> x)
    {
        if (Counter >= CandidateNumber)
        {
            Counter = 0;
        }
        Array[Counter] += x;
        Counter++;
    }

    cout << "Number of voters: " << Voters << endl;
    cout << "Number of valid ballots: " << ValidBallots << endl;
    cout << "Number of spoilt ballots: " << SpoiltBallots << endl;
    cout << endl;
    cout << setw(15) << left << "Candidate" << setw(3) << right << "Score" << endl;
    cout << endl;
    if (Voters >= 0)
    {
        istringstream C{Candidate};
        string OutputString;
        Counter = 0;
        while(getline(C,OutputString))
        {
            if (Counter >= CandidateNumber)
            {
                break;
            } 
            cout << setw(15) << left << OutputString << setw(3) << right << Array[Counter] << endl;
            Counter++;
        }
    }
    return 0;
}