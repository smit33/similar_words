# similar_words
Using a hashtable, a spell checker is checks the word in dictionary and suggests similar word if the entered word is wrong


A Hashtable is a data structure that maps a key to its respective value. If we know the ket, it is very easy to search some value in the table. This uses a hash function to compute the indexes for a key.
Based on hashtable index, we can store the values at appropriate location. If two different hash keys map to the same index, it is called a collision. We use another data structure (buckets) to resolve this.
The whole benefit of using hash table is due to it’s very fast access time

Functions:
createHashTable(int size);
hashKey(char *string);
insert(hashTable *phashTable, char *str);
search(hashTable *phashTable, char *str);
extraCharacter(hashTable *phashTable, char *str);
main();
