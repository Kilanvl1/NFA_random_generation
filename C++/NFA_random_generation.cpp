#include <iostream>
#include <sstream> 
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unordered_map>
#include <unordered_set>

//Shift option a to comment code out

int numberOfNFAs; 
const int ALPHABET_SIZE = 27; 

class NFA {
public:
    int numberOfTransitions = 0;
    struct Transition {
        int input;
        int targetState;
    };

    void addTransition(int from, int input, int to) {
        Transition transition = {input, to};
        transitions[from].push_back(transition);
    }

    void addFinalState(int state) {
        finalStates.insert(state);
    }

    void printGraph() {
        std::cout << "Delta: " << numberOfTransitions << "\n"; 
        for (const auto& stateTransitions : transitions) {
            for (const Transition& transition : stateTransitions.second) {
                char toASCII; 
                if(transition.input == 26) {
                    toASCII = '$'; 
                } else {
                    toASCII = static_cast<char>(transition.input + 97); 
                }
                 
                std::cout << stateTransitions.first << " " << toASCII << " " << transition.targetState << std::endl;
            }
        }
        std::cout << "\n";
    }

private:
    std::unordered_map<int, std::vector<Transition> > transitions;
    std::unordered_set<int> finalStates;
};

std::vector<int> createRandomBitStream(int n) {
    std::vector<int> randomBits;

    for (int i = 0; i < n; ++i) {
        int bit = std::rand() % 2; // Generate random bit (0 or 1)
        randomBits.push_back(bit);
    }

    return randomBits; 
}

NFA createRandomNFA(std::vector<int> bitStream, int numberOfStates) {
    NFA nfa; 
    for (int l = 0; l < ALPHABET_SIZE; l++)
    {
        for (int i = 0; i < numberOfStates; i++)
        {
            for (int j = 0; j < numberOfStates; j++)
            {
                if(bitStream.at(l * numberOfStates * numberOfStates + i * numberOfStates + j) == 1) {
                    nfa.addTransition(i,l,j); 
                    nfa.numberOfTransitions++;
                }
            }
        }
    }
    return nfa;
}

int main() {
    std::srand(std::time(nullptr));
    std::cout << "How many random NFA's would you like to generate: ";
    std::cin >> numberOfNFAs; 
    for (int i = 0; i < numberOfNFAs; i++)
    {
        int numberOfStates = std::rand() % 100 + 1;
        std::cout << "Q: " << numberOfStates << "\n"; 
        std::cout << "start: 0\n";
        std::vector<int> randomBitStream = createRandomBitStream(ALPHABET_SIZE * numberOfStates * numberOfStates);
        NFA nfa = createRandomNFA(randomBitStream, numberOfStates);
        nfa.printGraph();
    }
    
    return 0; 
}