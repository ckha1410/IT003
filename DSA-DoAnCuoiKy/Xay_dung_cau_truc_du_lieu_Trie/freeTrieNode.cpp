void freeTrieNode(TrieNode* root)
{
    //free the trie node sequence
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i] != NULL)
            freeTrieNode(root->children[i]);
        else continue;
    }
    free(root);
}
