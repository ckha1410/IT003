//function to make a new trie node
TrieNode* makeTrieNode(char data)
{
    //create a trie node
    TrieNode* newNode = new TrieNode();
    //initialize every index of childNode array with NULL
    for (int i = 0; i < ALPHABET_SIZE; i++)
        newNode->children[i] = NULL;
    newNode->is_leaf = 0;   //initialize the is_leaf with 0
    newNode->data = data;   //initialize the data with character in node
    return newNode;
}
