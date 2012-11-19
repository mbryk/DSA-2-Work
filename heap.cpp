/* 
 * File:   heap.cpp
 * Author: Mark Bryk
 * ECE 165
 * HW #2
 * 
 * Created on October 10, 2012, 8:08 AM
 */

#include <iostream>
#include "heap.h"

using namespace std;

heap::heap(int capacity){
    data.resize(capacity+1);
    mapping = new hashTable(capacity*2);
    heap::capacity = capacity;
    filled = 0;
}
  
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

int heap::setKey(const std::string &id, int key){
    bool b = true;
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

int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
    if(filled==0) return 1;
    
    if(pId) *pId = data[1].id;
    if(pKey) *pKey = data[1].key;
    if(ppData) *(static_cast<void **> (ppData)) = data[1].pData;
    mapping->remove(data[1].id);
        
    data[1] = data[filled--];
    
    mapping->setPointer(data[1].id, &data[1]);
    percolateDown(1);

    return 0;
}

int heap::remove(const std::string &id, int *pKey, void *ppData){
    bool b = true;
    node *pn = static_cast<node *> (mapping->getPointer(id, &b));
    if(!b) return 1;
    
    int pos = getPos(pn);
    int oldKey = data[pos].key;
    
    if(pKey) *pKey = oldKey;
    if(ppData) *(static_cast<void **> (ppData)) = data[pos].pData;    
    
    mapping->remove(id);
    
    data[pos] = data[filled];
    mapping->setPointer(data[pos].id, &data[pos]);
    
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

    while((posCur > 1) && (temp.key < data[posCur/2].key)) {
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
