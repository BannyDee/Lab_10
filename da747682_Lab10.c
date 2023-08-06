#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    int count;
    struct Trie *children[26];
};
// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie* temp = pTrie;
    for(int i = 0;word[i] != '\0';i++){
        int j = word[i] - 'a';
        if(temp->children[j] == NULL){
            temp->children[j] = createTrie();
        }
        temp = temp->children[j];
    }
    temp->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie* temp = pTrie;
    for(int i = 0; word[i] != '\0'; i++){
        int j = word[i] - 'a';
        if(temp->children[j] == NULL){
            return 0;
        }
        temp = temp->children[j];
    }
    return temp->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if(pTrie != NULL){
        for(int i = 0; i < 26;i++){
            if(pTrie->children[i] != NULL){
                deallocateTrie(pTrie->children[i]);
            }
        }
        free(pTrie);
    }
}

// Initializes a trie structure
struct Trie* createTrie()
{
     struct Trie* pNode = (struct Trie*)malloc(sizeof(struct Trie));
    for(int i = 0; i < 26;i++){
        pNode->children[i] = NULL;
    }
    pNode->count = 0;
    return pNode;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* fp = fopen(filename,"r");
    if(fp == NULL){
        printf("Unable to open the file!\n");
        exit(1);
    }
    int num;
    fscanf(fp, "%d",&num);
    for(int i = 0;i < num;i++){
        pInWords[i] = (char*)malloc(256 * sizeof(char));
        fscanf(fp,"%s",pInWords[i]);
    }
    fclose(fp);
    return num;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[][256] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL){
		printf("There is an error in this program\n");
    }
    for(int i = 0; i< numWords; i++){
        free(inWords[i]);
    }
    return 0;
}