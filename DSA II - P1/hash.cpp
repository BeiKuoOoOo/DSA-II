//DSA II Program 1, Sophia (Ruxi) Xu

#include "hash.h"
#include <string>
#include <vector>

using namespace std;

//Prime number list for selecting the initial size of hash table
//Prime number found online
int prime[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289,
               24593, 49157, 98317, 196613, 393241, 786433,
               1572869, 3145739, 6291469, 12582917, 25165843,
               50331653, 100663319, 201326611, 402653189,
               805306457, 1610612741};
#define A 54059             // a prime
#define B 76963             // another prime
#define FIRSTH 37           // also prime

//Constructor
//initialize hash table
hashTable::hashTable(int size) {
    capacity = getPrime(size);
    data.resize(capacity);
    filled = 0;
}

// GETPRIME - get prime number at least as large as size of hash table
unsigned int hashTable::getPrime(int size) {
    unsigned int size1 = 0;
    for (int i = 0; i < sizeof(prime); i++) {
        if(prime[i] > size*2){
            size1 = prime[i];
            return size1;
        }
    }
    return 0;
}

//http://www.cse.yorku.ca/~oz/hash.html
//hash function found online
int hashTable::hash(const std::string &key){
    const char *strPtr = key.c_str();
    unsigned int hashIndex = FIRSTH;
    while(*strPtr){
        hashIndex = (hashIndex * A) ^ (strPtr[0] * B);
        strPtr++;
    }
    return hashIndex % capacity;
}

//insert key to the hash table
//0 = success, 1 = already exist, 2 = fail
int hashTable::insert(const std::string &key, void *pv){
    int h = hash(key);
    if(2*filled >= capacity && !rehash()){ //filled, cannot insert
        return 2;
    }
    if(contains(key)){ //already have key
        return 1;
    }
    while (data[h].isOccupied){ //insert
        h++;
        h %= capacity;
        if(data[h].key == key){
            break;
        }
    }
    filled++;
    data[h].isDeleted = false;
    data[h].key = key;
    data[h].isOccupied = true;
    return 0; //success
}

//bool function to find out if key already exist or not
//used in insert function
bool hashTable::contains(const std::string &key){
    if (findPos(key) > 0){ //findPos returns the position (-1 means cannot find)
        return true;
    } else{
        return false;
    }
}

//find item with specific key
//return position if found, -1 = not found
int hashTable::findPos(const std::string &key){
    int pos = hash(key);
    for(int i = 0; i < capacity; i++){
        if(data[pos].key == key){ //found key
            return pos;
        }else if(data[pos].isOccupied){ //data in position
            pos++;
            pos %= capacity;
        }else{
            return -1;
        }
    }
    return -1;
}

//rehash function to get a bigger table
//true if success, fail if mem. alloc. fail
bool hashTable::rehash(){
    vector<hashItem> old = data;
    data.clear();
    capacity = getPrime(capacity);
    data.resize(capacity);
    if(data.size() != capacity){
        return false;
    }
    filled = 0;
    for (int i = 0; i < old.size(); i++){
        if(old[i].isOccupied && !old[i].isDeleted){
            insert(old[i].key, old[i].pv);
        }
    }
    old.clear();
    return true;
}