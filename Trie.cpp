#include "Trie.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    delete root; // This triggers the recursive destructors in the nodes
}

string Trie::clean_word(string raw) {
    string cleaned = "";
    for (char c : raw) {
        // Only allow a-z and A-Z. Everything else is banished.
        if (std::isalpha(static_cast<unsigned char>(c))) {
            cleaned += tolower(static_cast<unsigned char>(c));
        }
    }
    return cleaned;
}

bool Trie::is_stop_word(string word) {
    // If the word is too short or empty, treat it as a stop word
    if (word.length() <= 1) return true;

    static const std::unordered_set<string> stop_words = {
        "the", "is", "at", "which", "on", "and", "a", "an", "to", "of", "in", "it", "was", "with", "my"
    };

    return stop_words.find(word) != stop_words.end();
}

void Trie::insert_pair(string current_word, string next_word) {
    TrieNode* curr = root;
    for (char c : current_word) {
        unsigned int index = (unsigned char)c;
        
        // SAFETY CHECK: If the character is out of bounds, skip it or cap it
        if (index >= 128) continue; 

        if (curr->children[index] == nullptr) {
            curr->children[index] = new TrieNode();
        }
        curr = curr->children[index];
    }
    curr->isEndOfWord = true;
    curr->followers[next_word]++;
}

TrieNode* Trie::find_node(string word) {
    TrieNode* curr = root;
    for (char c : word) {
        unsigned int index = (unsigned char)c;
        
        // SAFETY CHECK: 
        if (index >= 128) return nullptr; 

        if (curr->children[index] == nullptr) return nullptr;
        curr = curr->children[index];
    }
    // Return curr only if it's marked as a word end
    return (curr && curr->isEndOfWord) ? curr : nullptr;
}

vector<string> Trie::get_top_suggestions(string word, int k) {
    TrieNode* node = find_node(word);
    if (node == nullptr) {
        return {}; 
    }

    vector<std::pair<string, int>> word_counts;
    for (auto const& pair : node->followers) {
        word_counts.push_back({pair.first, pair.second});
    }

    std::sort(word_counts.begin(), word_counts.end(), 
        [](const std::pair<string, int>& a, const std::pair<string, int>& b) {
            return a.second > b.second;
    });

    vector<string> suggestions;
    for (int i = 0; i < std::min(k, (int)word_counts.size()); i++) {
        suggestions.push_back(word_counts[i].first);
    }
    return suggestions;
}

void Trie::load_file(string filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) return;

    string rawWord;
    string prev = "";

    while (inputFile >> rawWord) {
        string clean = clean_word(rawWord);

        if (clean != "" && !is_stop_word(clean)) {
            if (prev != "") {
                insert_pair(prev, clean);
            }
            prev = clean;
        } else {
            // If the current word is a stop word, we reset prev 
            // so we don't bridge across a forbidden word.
            prev = ""; 
        }
    }
    inputFile.close();
}

void Trie::generate_sentence(string start_word, int length) {
    string current = start_word;
    std::cout << current << " ";
    for(int i = 0; i < length; i++) {
        auto suggestions = get_top_suggestions(current, 1);
        if(suggestions.empty()) break;
        std::cout << suggestions[0] << " ";
        current = suggestions[0];
    }
    std::cout << std::endl;
}