/* 
 * File:   hash.cpp
 * Author: mark
 * 
 * Created on September 10, 2012, 12:23 PM
 */
#include "hash.h"
using namespace std;

    hashTable::hashTable(int size) {
        capacity = hashTable::getPrime(200);
        try{
            data.resize(capacity);
        }
        catch (bad_alloc const&) {
            return false;
        }
        for(int i = 0; i< size; i++)
            data[i].isOccupied = false;
    }
    
    int hashTable::insert(const std::string &key, void *pv) {
        if (capacity / filled < 2) rehash();
        int number = hash(key);
        
        while(data[number].isOccupied==true){
            if(data[number].isDeleted==false)
                number++;
                            //if pos>capactiy pos-=capacity
            else //dont forget to check if key==this key
                break;
        }
        data[number].key = key;
        data[number].isOccupied = true;
        data[number].isDeleted = false;
        
        if(++filled) return 1;
    }
    
    bool hashTable::contains(const std::string &key){
        //if(findPos(capacity==...))
        int number = hash(key);
        while(data[number].isOccupied == true){
            if(data[number].key == key) 
                return true;
            else number++;
        }
        return false;
    }
    
    /*void hashTable::*getPointer(const std::string &key, bool *b = NULL){
        
    }
    
    int hashTable::setPointer(const std::string &key, void *pv){

    }*/
    
    bool hashTable::remove(const std::string &key){
        int number = hash(key);
        data[number].isDeleted=true;
        data[number].isOccupied=false;
    }
    
    int hashTable::hash(const std::string &key){
        int hashVal = 0;
        
        for( int i = 0; i< key.length(); i++)
            hashVal = 37*hashVal + key[i];
        hashVal %= capacity;
        
        if(hashVal < 0)
            hashVal += capacity;
        
        return hashVal;
    }
        
    
    int hashTable::findPos(const std::string &key){
        
    }
    
    bool hashTable::rehash(){
        std::vector<hashItem> oldData = data;
        
        int capacity = getPrime(capacity*2);
        try{
            data.resize(newSize);
        }
        catch (bad_alloc const&) {
            return false;
        }
        for(int i = 0; i< capacity; i++)
            data[i].isOccupied = false;
        
        for(int j = 0; j<oldData.size(); j++)
            if((oldData[j].isOccupied == true)&&(oldData[j].isDeleted = false))
                insert(oldData[j].key);
        
        return true;
    }
    
    int hashTable::getPrime(int size){
        return 500;
    }
