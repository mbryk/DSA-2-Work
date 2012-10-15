/* 
 * File:   heap.cpp
 * Author: mark
 * 
 * Created on October 10, 2012, 8:08 AM
 */

#include "heap.h"
#include "hash.h"
#include <iostream>
using namespace std;

heap::heap(int capacity){
    data.resize(capacity+1);
    mapping = new hashTable(capacity*2);
    heap::capacity = capacity;
    filled = 0;
}
  
  //
  // insert - Inserts a new node into the binary heap
  //
  // Inserts a node with the specified id string, key,
  // and optionally a pointer.  They key is used to
  // determine the final position of the new node.
  //
  // Returns:
  //   0 on success
  //   1 if the heap is already filled to capacity
  //   2 if a node with the given id already exists (but the heap
  //     is not filled to capacity)
  //
int heap::insert(const std::string &id, int key, void *pv){
    if(filled == capacity) return 1;
    if(mapping->contains(id)) return 2;

    int posCur = ++filled;
    data[posCur].id = id;
    data[posCur].key = key;
    data[posCur].pData = pv;
    
    mapping->insert(data[posCur].id, &data[posCur]);
    
    percolateUp(posCur);    
    
    return 0;
}

  //
  // setKey - set the key of the specified node to the specified value
  //
  // I have decided that the class should provide this member function
  // instead of two separate increaseKey and decreaseKey functions.
  //
  // Returns:
  //   0 on success
  //   1 if a node with the given id does not exist
  //
int heap::setKey(const std::string &id, int key){
    bool b = 1;
    node *pn = static_cast<node *> (mapping->getPointer(id, &b));
    if(!b)
        return 1;
    int pos = getPos(pn);
    int oldKey = data[pos].key;
    data[pos].key = key;

    if(key<oldKey)
        percolateUp(pos);
    else if(key>oldKey)
        percolateDown(pos);
    return 0;
}
  //
  // deleteMin - return the data associated with the smallest key
  //             and delete that node from the binary heap
  //
  // If pId is supplied (i.e., it is not NULL), write to that address
  // the id of the node being deleted. If pKey is supplied, write to
  // that address the key of the node being deleted. If ppData is
  // supplied, write to that address the associated void pointer.
  //
  // Returns:
  //   0 on success
  //   1 if the heap is empty
  //
int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
    if(filled==0) return 1;
    
    if(pId) *pId = data[1].id;
    if(pKey) *pKey = data[1].key;
    if(ppData) *(static_cast<void **> (ppData)) = data[1].pData;
    
    data[1] = data[filled--];
    
    mapping->setPointer(data[1].id, &data[1]);
    percolateDown(1);
    
    return 0;
}

  //
  // remove - delete the node with the specified id from the binary heap
  //
  // If pKey is supplied, write to that address the key of the node
  // being deleted. If ppData is supplied, write to that address the
  // associated void pointer.
  //
  // Returns:
  //   0 on success
  //   1 if a node with the given id does not exist
  //
int heap::remove(const std::string &id, int *pKey, void *ppData){
    bool b = 1;
    node *pn = static_cast<node *> (mapping->getPointer(id, &b));
    if(!b) return 1;
    
    int pos = getPos(pn);
    int oldKey = data[pos].key;
    
    if(pKey) *pKey = oldKey;
    if(ppData) *(static_cast<void **> (ppData)) = data[pos].pData;    
    
    mapping->remove(id);
    
    data[pos] = data[filled];
    
    if(data[filled].key < oldKey)
        percolateUp(pos);
    else if(data[filled].key > oldKey)
        percolateDown(pos);
    filled--;
    return 0;
}

void heap::percolateUp(int posCur){
    bool changed = false;
    node temp = data[posCur];

    while((posCur > 1) && (data[posCur].key < data[posCur/2].key)) {
        data[posCur] = data[posCur/2];
        
        mapping->setPointer(data[posCur].id, &data[posCur]);
        posCur /= 2;
        changed = true;
    }
    if(changed) {
        data[posCur] = temp;
        mapping->setPointer(data[posCur].id, &data[posCur]);
    }
}

void heap::percolateDown(int posCur){
    node temp = data[posCur];
    int child;
    
    for(; posCur * 2 <= filled; posCur = child) {
        child = posCur *2;
        if( child != filled && data[child + 1].key < data[child].key)
            child++;
        if( data[child].key < temp.key) {
            data[posCur] = data[child];  
            mapping->setPointer(data[posCur].id, &data[posCur]);
        } else
            break;
    }
    
    data[posCur] = temp;
    
    mapping->setPointer(data[posCur].id, &data[posCur]);    
}

int heap::getPos(node *pn){
    int pos = pn - &data[0];
    return pos;
}



