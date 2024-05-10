TrieNode* insert(TrieNode* root, char* word)
{
    TrieNode* current = root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int idx = (int) word[i] - 'a';
        if (current->children[idx] == NULL)
        {
            //if the conrresponding child doesn't exist
            //create that child
            current->children[idx] = makeTrieNode(word[i]);
        }
        else {
            //if the conrresponding child exist, do nothing
        }
        //because we have a prefix match, go down a level
        current = current->children[idx];
    }
    //at the end of word, mark this node as the leaf node
    current->is_leaf = 1;
    return root;
}
