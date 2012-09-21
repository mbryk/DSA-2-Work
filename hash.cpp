/* 
 * File:   hash.cpp
 * Author: mark
 * 
 * Created on September 10, 2012, 12:23 PM
 */
#include "hash.h"
using namespace std;

    hashTable::hashTable(int size) {
        size = hashTable::getPrime(200);
        data.resize(size);
        for(int i = 0; i< size; i++)
            data[i].isOccupied = false;
        
    }
    
    int hashTable::insert(const std::string &key, void *pv) {
        if (this->capacity / this->filled < 2) rehash();
        int number = hash(key);
        while(data[number].isOccupied==true){
            if(data[number].isDeleted==false)
                number++;
            else
                break;
        }
        data[number].key = key;
        data[number].isOccupied = true;
        data[number].isDeleted = false;
        
        this->filled ++;
    }
    
    bool hashTable::contains(const std::string &key){
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
        hashVal %= this->capacity;
        
        if(hashVal < 0)
            hashVal += this->capacity;
        
        return hashVal;
    }
        
    
    int hashTable::findPos(const std::string &key){
        
    }
    
    bool hashTable::rehash(){
        std::vector<hashItem> oldData = data;
        
        int newSize = getPrime(this->capacity*2);
        data.resize(newSize);
        this->capacity = newSize;
        
        for(int i = 0; i< newSize; i++)
            data[i].isOccupied = false;
        
        for(int j = 0; j<oldData.size(); j++)
            if((oldData[j].isOccupied == true)+(oldData[j].isDeleted = false))
                insert(oldData[j].key);
        
        return true;
    }
    
    int hashTable::getPrime(int size){
        return 500;
    }
