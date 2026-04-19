Gothic Markov Chain Generator (Trie Implementation)

Project Data Structure

This project implements a Trie (Prefix Tree) to manage and analyze word relationships from classic Gothic literature.

Explanation of the Data Structure

A Trie is a specialized tree-based data structure used to store an associative array where the keys are strings.

- Character Paths: Unlike a Hash Table, which stores a whole word in one "bucket," a Trie stores words character-by-character. Each node in the Trie represents a single character.

- The "Map" Logic: By following the path from the root to a leaf, the program "spells out" the word. This makes searching for words extremely efficient (O(L) where L is the length of the word).

- Markov Chain Integration: In this specific implementation, each "End of Word" node contains a std::unordered_map (the Followers). This map tracks which words appear immediately after the current word in the source text and how frequently they occur. This allows the program to predict and generate text in the style of the input authors.

How to Run the Project

To run this project on a Linux/Jupyter terminal, follow these steps:

Compile the program:
Use the g++ compiler to build the executable from the source files:

Bash

g++ -std=c++11 main.cpp Trie.cpp -o elsm2558

Execute the program:

Bash

./elsm2558

Output:
The program will load the text files (frankenstein.txt, carmilla.txt, and jekyll_and_hyde.txt), verify that the Trie is populated, and generate a sample sentence based on a "seed" word (e.g., "monster").

Note: The sentence generator uses a Greedy First-Order Markov Chain. It lacks long-term context because each prediction is based solely on the current node in the Trie. While this accurately reflects the statistical probability of word pairs in the source text, it doesn't account for overarching sentence structure or grammar, leading to 'pseudo-Gothic' nonsense.
