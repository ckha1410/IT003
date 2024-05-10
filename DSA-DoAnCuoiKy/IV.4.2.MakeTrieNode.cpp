TrieNode* makeTrieNode(char data)
{
    TrieNode* newNode = new TrieNode();
    for (int i = 0; i < ALPHABET_SIZE; i++)
        newNode->children[i] = NULL;
    newNode->is_leaf = 0;
    newNode->data = data;
    return newNode;
}
