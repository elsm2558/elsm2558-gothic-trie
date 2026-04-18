#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
#include <string>
#include <vector>

using std::string;
using std::vector;

struct TrieNode {
    TrieNode* children[128]; // Supports all ASCII characters
    bool isEndOfWord;
    std::unordered_map<string, int> followers;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 128; i++) {
            children[i] = nullptr;
        }
    }
    
    // Destructor for the node to clean up its children recursively
    ~TrieNode() {
        for (int i = 0; i < 128; i++) {
            if (children[i]) delete children[i];
        }
    }
};

class Trie {
public:
    Trie();
    ~Trie();
    
    void insert_pair(string current_word, string next_word);
    void load_file(string filename);
    void generate_sentence(string start_word, int length);

    TrieNode* find_node(string word);
    
    // Helping functions
    string clean_word(string raw);
    bool is_stop_word(string word);
    
private:
    TrieNode* root;
    vector<string> get_top_suggestions(string word, int k);
};

#endif