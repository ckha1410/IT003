void printTrie(TrieNode* root)
{
    //print the nodes of the trie
    if (root == NULL) return;
    //initialize the currentNode pointer with the root node
    TrieNode* current = root;
    //print the current character in this currentNode
    cout << "->" << current->data;
    //iterate across the length of the children array to print the next character
    for (int i = 0; i < ALPHABET_SIZE; i++)
        printTrie(current->children[i]);
}
