#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class MealyCommentDetector {
private:
    int currentState;

    int getNextStateAndOutput(char input, int& output) {
        // Convert any character that is not '/' or '*' to 'a'
        char symbol = (input == '/' || input == '*') ? input : 'a';
        output = 0; // Default output

        switch (currentState) {
            case 0: // q0
                if (symbol == '/') return 1;
                return 4;
            case 1: // q1
                if (symbol == '*') return 2;
                return 4;
            case 2: // q2
                if (symbol == '*') return 3;
                return 2;
            case 3: // q3
                if (symbol == '/') {
                    output = 1; // Valid comment closed
                    return 4;
                }
                if (symbol == '*') return 3;
                return 2;
            case 4: // q4 (Trap/End)
                return 4;
            default:
                return 4;
        }
    }

public:
    MealyCommentDetector() : currentState(0) {}

    void processString(const string& input) {
        currentState = 0;
        vector<int> outputTape;
        bool accepted = false;

        cout << "Input: " << setw(15) << left << input << " | Output: ";

        for (char ch : input) {
            int output = 0;
            currentState = getNextStateAndOutput(ch, output);
            outputTape.push_back(output);
            cout << output;
        }

        if (!outputTape.empty() && outputTape.back() == 1) {
            accepted = true;
        }

        cout << " | Result: " << (accepted ? "ACCEPTED" : "REJECTED") << endl;
    }
};

int main() {
    MealyCommentDetector machine;

    vector<string> testCases = {
        "/*a*/", "/**/", "/***/", "/*aaa*aaa*/", // Accepted
        "/**", "/*/", "/**a/", "//aaaa", "/*a*/a"  // Rejected
    };

    cout << "=== MEALY MACHINE STRING EVALUATION ===\n";
    for (const string& test : testCases) {
        machine.processString(test);
    }

    return 0;
}