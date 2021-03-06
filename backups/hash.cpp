/* 
 * File:   hash.cpp
 * Author: Mark Bryk
 * ECE 165
 * HW #1
 * 
 * Created on September 10, 2012, 12:23 PM
 */
#include "hash.h"
using namespace std;

    hashTable::hashTable(int size) {
        capacity = getPrime(size);
        filled = 0;
        try{
            data.resize(capacity);
        }
        catch (bad_alloc const&) {
        }
        for(int i = 0; i< size; i++)
            data[i].isOccupied = false;
    }
    
    int hashTable::insert(const std::string &key, void *pv) {
        if(filled>0 &&(capacity/filled)<2)
            if(!rehash()) return 2;

        int number = hash(key);
        
        while(data[number].isOccupied == true){
            if((data[number].key == key) && (data[number].isDeleted==false)) 
                return 1;
            else {
                number++;
                if(number>capacity)
                    number-=capacity;
            }
        }
        
        data[number].key = key;
        data[number].isOccupied = true;
        data[number].isDeleted = false;
        data[number].pv = pv;
        
        if(++filled) return 0;
    }
    
    bool hashTable::contains(const std::string &key){
        int pos = findPos(key);
        if(pos!=-1)
            return true;
        return false;

    }
    
    void* hashTable::getPointer(const std::string &key, bool *b){
        int pos = findPos(key);
        if(pos!=-1){
            if(b) *b = true;
            return data[pos].pv;
        }
            
        if(b) *b = false;
        return NULL;
    }
    
    int hashTable::setPointer(const std::string &key, void *pv){
        int pos = findPos(key);
        if(pos==-1) 
            return 1;
        else
            data[pos].pv = pv;
        return 0;
    }
    
    
    bool hashTable::remove(const std::string &key){
        int number = findPos(key);
        if(number != -1){
            data[number].isDeleted = true;
            return true;
        }
        return false;
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
        int number = hash(key);
        while(data[number].isOccupied == true){
            if((data[number].key == key) && (data[number].isDeleted==false)) 
                return number;
            else {
                number++;
                if(number>capacity)
                    number-=capacity;
            }
        }
        return -1;
    }
    
    bool hashTable::rehash(){
        std::vector<hashItem> oldData = data;
        
        capacity = getPrime(capacity*2);
        try{
            data.resize(capacity);
        }
        catch (bad_alloc const&) {
            return false;
        }
        for(int i = 0; i< capacity; i++)
            data[i].isOccupied = false;
        
        filled = 0;
        
        for(int j = 0; j<oldData.size(); j++) {
            if((oldData[j].isOccupied == true)&&(oldData[j].isDeleted == false)){
                insert(oldData[j].key, oldData[j].pv);
            }
        }
        return true;
    }
    
    int hashTable::getPrime(int size){
        int primes[] = {101,467,947,2063,9901,19997,40009,80021,160049,320101,640219,1301221,2783999,6500003};
        for(int i=0; i < sizeof(primes); i++) {
            if(size<primes[i]) return primes[i];
        }
        return 0;
    }
