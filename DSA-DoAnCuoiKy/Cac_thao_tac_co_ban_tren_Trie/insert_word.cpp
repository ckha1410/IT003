TrieNode* insert_word(TrieNode* root, char* word)
{
    //initialize the currentNode pointer with the root node
    TrieNode* current = root;
    //across the length of the string
    for (int i = 0; word[i] != '\0'; i++)
    {
        //initialize the ind with index of each character in childNode array
        int idx = (int) word[i] - 'a';
        //check if the node exist for the current character in the Trie
        if (current->children[idx] == NULL)
        {
            //if node for character does not exist
            //create that child
            current->children[idx] = makeTrieNode(word[i]);
        }
        else {
            //if the corresponding child exist, do nothing
        }
        //because we have a prefix match, go down a level
        current = current->children[idx];
    }
    //at the end of word, mark this node as the leaf node
    //this implies that there is a string ending at the last currentNode
    current->is_leaf = 1;
    return root;
}
