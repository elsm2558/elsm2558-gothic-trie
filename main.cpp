#include "Trie.h"
#include <iostream>

int main() {
    // 1. Create the Trie (No size needed!)
    Trie myGothicLib; 

    std::cout << "Loading Gothic Library..." << std::endl;
    myGothicLib.load_file("frankenstein.txt");
    myGothicLib.load_file("carmilla.txt");
    myGothicLib.load_file("jekyll_and_hyde.txt");

    // 2. Verify the words were stored correctly
    // In a Trie, "finding" a word means the path of nodes exists
    if (myGothicLib.find_node("frankenstein") != nullptr) {
        std::cout << "Trie Verification: 'frankenstein' successfully stored in nodes!" << std::endl;
    } else {
        std::cout << "Trie Verification Failed: The word was not found." << std::endl;
    }

    // 3. Test the Sentence Generator
    std::string startWord = "monster";
    int sentenceLength = 15;

    std::cout << "\n--- Generated Gothic Sentence ---" << std::endl;
    myGothicLib.generate_sentence(startWord, sentenceLength);
    std::cout << "\n---------------------------------" << std::endl;

    // 4. Test a "Dead End" word
    // This will likely return nothing because "the" is a stop_word and not in the Trie
    std::cout << "\nTesting stop-word check ('the'):" << std::endl;
    myGothicLib.generate_sentence("the", 5);
    std::cout << std::endl;

    return 0;
}