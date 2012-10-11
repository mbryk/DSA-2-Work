/* 
 * File:   heap.cpp
 * Author: mark
 * 
 * Created on October 10, 2012, 8:08 AM
 */

#include "heap.h"
#include "hash.h"
using namespace std;

heap::heap(int capacity){
    data.resize(capacity+1);
    mapping = new hashTable(capacity*2);
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
    if(filled ==capacity) return 1;
    if(mapping.contains(id)) return 2;

    int posCur = ++filled;
    data[posCur].id = id;
    data[posCur].key = key;
    data[posCur].pData = pv;
    
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
    int oldKey = pn.key;
    pn.key = key;
    int pos = getPos(pn);
    
    if(key>oldKey)
        percolateUp(pos);
    else if(key<oldKey)
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
    if(filled==1) return 0;
    
    if(pId) pId = data[1].id;
    if(pKey) pKey = data[1].key;
    if(ppData) *(static_cast<void **> (ppData)) = data[1].pData;
    
    data[1].id = data[filled].id;
    data[1].key = data[filled].key;
    data[1].pData = data[filled].pData;
    
    mapping->setPointer(data[1].id, &data[1]);
    percolateDown(1);
    
    filled--;
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
    
    if(pKey) pKey = oldKey;
    if(ppData) *(static_cast<void **> (ppData)) = data[pos].pData;    
    
    data[pos].id = data[filled].id;
    data[pos].key = data[filled].key;
    data[pos].pData = data[filled].pData;
    
    if(data[filled].key < oldKey)
        percolateUp();
    else if(data[filled].key > oldKey)
        percolateDown();
    filled--;
    return 0;
}

void heap::percolateUp(int posCur){
    int tempId = data[posCur].id;
    int tempKey = data[posCur].key;
    int tempPointer = data[posCur].pData;
    while((posCur > 1) && (data[posCur].key < data[posCur/2].key)) {
        data[posCur].id = data[posCur/2].id;
        data[posCur].key = data[posCur/2].key;
        data[posCur].pData = data[posCur/2].pData;
        
        mapping->setPointer(data[posCur].id, &data[posCur]);
        posCur /= 2;
    }
    data[posCur].id = tempId;
    data[posCur].key = tempKey;
    data[posCur].pData = tempPointer;
    
    mapping->setPointer(data[posCur].id, &data[posCur]);
}

void heap::percolateDown(int posCur){
    int tempId = data[posCur].id;
    int tempKey = data[posCur].key;
    int tempPointer = data[posCur].pData;
    while((posCur > 1) && (data[posCur].key < data[posCur/2].key)) {
        data[posCur].id = data[posCur/2].id;
        data[posCur].key = data[posCur/2].key;
        data[posCur].pData = data[posCur/2].pData;
        
        mapping->setPointer(data[posCur].id, &data[posCur]);
        posCur /= 2;
    }
    data[posCur].id = tempId;
    data[posCur].key = tempKey;
    data[posCur].pData = tempPointer;
    
    mapping->setPointer(data[posCur].id, &data[posCur]);    
}

int heap::getPos(node *pn){
    int pos = pn - &data[0];
    return pos;
}



