void printTrie(TrieNode* root)
{
    //print the nodes of the trie
    if (root == NULL) return;
    TrieNode* current = root;
    cout << "->" << current->data;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        printTrie(current->children[i]);
}
