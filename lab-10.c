#include <stdlib.h>
#include <stdio.h>
#include <string.h>



struct trienode {
    int count;
    struct trienode* children[26];
};

void insert(struct trienode** ppTrie, char* word) {
    struct trienode* temp = *ppTrie;
    int len = strlen(word);
    for(int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if(temp->children[index] == NULL) {
            temp->children[index] = (struct trienode*) malloc(sizeof(struct trienode));
            temp->children[index]->count = 0;
            for(int j = 0; j < 26; j++) {
                temp->children[index]->children[j] = NULL;
            }
        }
        temp = temp->children[index];
    }
    temp->count++;
}

int numberOfOccurances(struct trienode* pTrie, char* word) {
    struct trienode* temp = pTrie;
    int len = strlen(word);
    for(int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if(temp->children[index] == NULL) {
            return 0;
        }
        temp = temp->children[index];
    }
    return temp != NULL ? temp->count : 0;
}

struct trienode* deallocateTrie(struct trienode* pTrie) {
    if(pTrie == NULL) {
        return NULL;
    }

    for(int i = 0; i < 26; i++) {
        deallocateTrie(pTrie->children[i]);
    }

    free(pTrie);
    return NULL;
}

struct trienode* createnode(char word[]) {
    struct trienode* trie = (struct trienode*) malloc(sizeof(struct trienode));
    trie->count = 0;
    for(int i = 0; i < 26; i++) {
        trie->children[i] = NULL;
    }
    return trie;
}

int main(void)
{
//read the number of the words in the dictionary
// parse line by line, and insert each word to the trie data structure

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    int numWords = sizeof(pWords)/sizeof(pWords[0]);

    struct trienode* trie = createnode("");

    for (int i = 0; i < numWords; i++)
    {
        insert(&trie, pWords[i]);
    }

    for (int i=0;i<numWords;i++)
    {
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
    }

    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
    
    return 0;    
}