struct TrieNode
{
    char data;        //storing for printing purposes only
    TrieNode* children[ALPHABET_SIZE];
    bool is_leaf;    //a flag to check if it's a leaf node
};
