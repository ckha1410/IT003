//define a trie node structure
struct TrieNode
{
    char data; //storing for printing purposes only
    TrieNode* children[ALPHABET_SIZE];  //pointer array for child nodes of each node
    bool is_leaf; //a flag to check if it's a leaf node
                  //that means it is the last character of a word in trie
};
