/**
 * 
 * NAME - SMIT SHAH 19BCE259
 * 
 * Program definition -  Create a spell checker application. Use hashing 
 * functionality to check incorrect spelling with correct available 
 * stored spellings. It should suggest to users to correct spellings.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 26                 // Number of elements in table 
#define WORD_SIZE 100           //max size of word

typedef struct LLNode       
{
    char word[100];               
    struct LLNode *next;   
}llnode;

typedef struct HashNode
{
    int total_elements;          
    llnode *rootElement;   
}hashNode;  

typedef struct HashTable
{
    int size;                     
    hashNode *base;           
}hashTable;

// function to create hashTable
hashTable* createHashTable(int size)
{
    int i;

    hashTable *phashTable = (hashTable *)malloc(sizeof(hashTable));

    if (phashTable == NULL)
    {
        printf("memory allocation failed\n");
    }

    phashTable->size = size;

    if (size > 0)
    {
        phashTable->base = (hashNode *)malloc(sizeof(hashNode) * phashTable->size);

        if (phashTable->base == NULL)
        {
            printf("memory allocation failed\n");
        }

        for (i = 0; i < size; i++)
        {
            phashTable->base[i].rootElement = NULL;
        }
    }

    return phashTable;
}

//hashKey generator
int hashKey(char *string)
{
    char ch = string[0];
    if(ch >= 'A' && ch <= 'Z') 
    {
        ch = ch -'A' +'a';      // coverting to lowercase
    }
    int key = ch - 'a';     // gendrating key for hashMap
    return key;
} 

// inserts word in the hash table
void insert(hashTable *phashTable, char *str)
{ 
    bool ispresent;
    int hashindex = hashKey(str);    // generates key for hashIndex

    llnode *pllnode = phashTable->base[hashindex].rootElement;

    if (!pllnode)
    {
        pllnode = (llnode *)malloc(sizeof(llnode));
        if (pllnode == NULL)
        {
            printf("memory allocation failed\n");
        }
        phashTable->base[hashindex].rootElement = pllnode;
        strcpy(pllnode->word, str);
        pllnode->next = NULL;
    }
    else
    {
        while (pllnode->next != NULL)
        {
            pllnode = pllnode->next;
        }

        pllnode->next = (llnode *)malloc(sizeof(llnode));
        if (pllnode->next == NULL)
        {
            printf("memory allocation failed\n");
        }

        pllnode = pllnode->next;
        strcpy(pllnode->word, str);
        pllnode->next = NULL;
        
    }
}

// searches word in the hashTable
bool search(hashTable *phashTable, char *str)
{ 
    int hashindex = hashKey(str);    // generates key for hashIndex

    llnode *pllnode = phashTable->base[hashindex].rootElement;

    while (pllnode != NULL)
    {
        if (!strcmp(pllnode->word, str))
        {
            return true;
        }
        pllnode = pllnode->next;
    }

    return false;
}


// suggest correct spellings of the misspelled word
int extraCharacter(hashTable *phashTable, char *str)
{
    int found = 0;
    int word_length = strlen(str);
    int correct_word_length = word_length - 1;
    char temp[word_length];
    strcpy(temp,str);
    int hashindex = hashKey(str);    // generates key for hashIndex

    char possibleCorrectWords[correct_word_length][word_length];
    for(int i = 1; i < word_length; i++) 
    {
        memmove(&temp[i], &temp[i+1], strlen(temp) - i);
        temp[correct_word_length] = '\0';
        strcpy(possibleCorrectWords[i-1], temp);
        
        strcpy(temp,str);
    }

    llnode *pllnode = phashTable->base[hashindex].rootElement;

    while (pllnode != NULL)
    {
        int temp_length = strlen(pllnode->word);
        if (correct_word_length == temp_length)
        {
            for(int i = 0; i < correct_word_length; i++)
            {
                if(strcmp(possibleCorrectWords[i], pllnode->word) == 0)
                {
                    printf("%s\n", possibleCorrectWords[i]);
                    found = 1;
                }
            }
            
        }
        pllnode = pllnode->next;
    }

    return found;
}

int main()
{
    FILE *file;
    char word[WORD_SIZE];
    char ch;
    bool ispresent;
    int ans;
    hashTable *phashTable = createHashTable(SIZE);

    file = fopen("words.txt", "r");

    do
    {
        ch = fscanf(file, "%s", word);
        insert(phashTable, word);

    } while (ch != EOF);

    do
    {
        printf("Enter a word - ");
        scanf("%s", word);

        ispresent = search(phashTable, word);
        if(ispresent)
        {
            printf("Word is present in dictionary. Spelling is correct\n");
        }
        else
        {
            printf("Entered spelling is incorrect.\nPossible correct words: \n");
            int hasExtraChar = extraCharacter(phashTable, word);
            if(hasExtraChar == 0)
            {
                printf("No possible match found\n");
            }
        }
        
        printf("Do you want to continue? 1/0: ");
        scanf("%d", &ans);
    } while (ans != 0);
    
    fclose(file);
    return 0;
}
