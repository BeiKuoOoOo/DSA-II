#include "heap.h"

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;
// useHeap - The constructor allocates space for the nodes of the useHeap
// and the mapping (hash table) based on the specified capacity
//
heap::heap(int capacity){

    data.resize(capacity + 1);
    mapping = hashTable(capacity + 1);
    heap::capacity = capacity;
    filled = 0;
};

//
// insert - Inserts a new node into the binary useHeap
//
// Inserts a node with the specified id string, key,
// and optionally a pointer.  They key is used to
// determine the final position of the new node.
//
// Returns:
//   0 on success
//   1 if the useHeap is already filled to capacity
//   2 if a node with the given id already exists (but the useHeap
//     is not filled to capacity)
//
int heap::insert(const std::string &id, int key, void *pv){
    if ((mapping.contains(id)) && filled < capacity) {
        return 2;
    } else if (filled == capacity){
        return 1;
    }
    filled++;
    data[filled].id = id;
    data[filled].key = key;
    data[filled].pData = pv;
    mapping.insert(id, &data[filled]);
    percolateUp(filled);
    return 0;
};

//
// setKey - set the key of the specified node to the specified value
//
// I have decided that the class should provide this member function
// instead of two separate increaseKey and decreaseKey functions.
//
// Returns:
//   0 on success
//   1 if a node with the given id does not exist
int heap::setKey(const std::string &id, int key){
    int pos, oldk;
    if (!mapping.contains(id)){
        return 1;
    }
    node *ptr = static_cast<node *>(mapping.getPointer(id));
    oldk = ptr->key;
    ptr->key = key;
    pos = int(ptr - &data[0]);
    if (key > oldk) {
        percolateDown(pos);
    }else if (key < oldk) {
        percolateUp(pos);
    }
    return 0;
}


//
// deleteMin - return the data associated with the smallest key
//             and delete that node from the binary useHeap
//
// If pId is supplied (i.e., it is not nullptr), write to that address
// the id of the node being deleted. If pKey is supplied, write to
// that address the key of the node being deleted. If ppData is
// supplied, write to that address the associated void pointer.
//
// Returns:
//   0 on success
//   1 if the useHeap is empty
//
int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
    if (filled == 0){
        return 1;
    }
    if (pId != nullptr){
        *pId = data[1].id;
    }
    if (pKey != nullptr){
        *pKey = data[1].key;
    }
    if (ppData != nullptr){
        *(static_cast<void**>(ppData)) = data[1].pData;
    }
    mapping.remove(data[1].id);
    data[1] = data[filled];
    filled--;
    percolateDown(1);
    return 0;
};

//
// remove - delete the node with the specified id from the binary useHeap
//
// If pKey is supplied, write to that address the key of the node
// being deleted. If ppData is supplied, write to that address the
// associated void pointer.
//
// Returns:
//   0 on success
//   1 if a node with the given id does not exist
//
int heap::remove(const std::string &id, int *pKey, void *ppData)
{
    bool b;
    if (!mapping.contains(id)) {
        return 1;
    }
    node *pn = static_cast<node *> (mapping.getPointer(id, &b));
    int pos = getPos(pn);
    if (pKey != nullptr){
        *pKey = data[pos].key;
    }
    if (ppData != nullptr){
        *(static_cast<void**>(ppData)) = data[pos].pData;
    }
    setKey(id, data[1].key-1);
    deleteMin();
    return 0;
}


void heap::percolateUp (int posCur){
    node temp = data[posCur];
    for (; posCur > 1 && temp.key < data[posCur>>1].key; posCur = posCur>>1){
        data[posCur] = data[posCur>>1];
        mapping.setPointer(data[posCur].id, &data[posCur]);
    }
    data[posCur] = temp;
    mapping.setPointer(data[posCur].id, &data[posCur]);
};

void heap::percolateDown (int posCur){
    int child, left, right;
    node temp = data[posCur];
    while ((posCur<<1) <= filled){
        left = posCur<<1;
        right = left + 1;
        if (right <= filled){
            if(data[right].key < data[left].key){
                child = right;
            } else{
                child = left;
            }
        } else{
            child = left;
        }
        if (data[child].key <temp.key) {
            data[posCur] = data[child];
            mapping.setPointer(data[posCur].id, &data[posCur]);
            posCur = child;
        } else{
            break;
        }
    }
    data[posCur] = temp;
    mapping.setPointer(data[posCur].id, &data[posCur]);
};

//get position in heap
int heap::getPos(node *pn)
{
    int pos = pn - &data[0];
    return pos;
}