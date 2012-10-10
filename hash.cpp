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
            data.at(i).isOccupied = false;
    }
    
    int hashTable::insert(const std::string &key, void *pv) {
        if(filled>0 &&(capacity/filled)<2)
            if(!rehash()) return 2;
        
        int number = hash(key);
        
        while(data.at(number).isOccupied==true){
            if(data.at(number).isDeleted==false){
                if(data.at(number).key == key) 
                    return 1;
                number++;
                
                if(number>capacity)
                    number-=capacity;
            }
            else 
                break;
        }
        data.at(number).key = key;
        data.at(number).isOccupied = true;
        data.at(number).isDeleted = false;
        
        if(++filled) return 0;
    }
    
    bool hashTable::contains(const std::string &key){
        int number = hash(key);
        while(data.at(number).isOccupied == true){
            if((data.at(number).key == key) && (data.at(number).isDeleted==false)) 
                return true;
            else number++;
        }
        return false;
    }
    
    void *hashTable::getPointer(const std::string &key, bool *b){
        int pos = findPos(key);
        return data.at(pos).pv;
    }
    
    int hashTable::setPointer(const std::string &key, void *pv){
        return 0;
    }
    
    
    bool hashTable::remove(const std::string &key){
        int number = hash(key);
        if(data.at(number).isDeleted=true)
            return true;
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
        return 0;
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
            data.at(i).isOccupied = false;
        
        for(int j = 0; j<oldData.size(); j++) {
            if((oldData.at(j).isOccupied == true)&&(oldData.at(j).isDeleted == false))
                insert(oldData.at(j).key);
        }
        return true;
    }
    
    int hashTable::getPrime(int size){
        int primes[] = {19997,40009,80021,160049,320101,640219,1301221,2783999};
        for(int i=0; i < sizeof(primes); i++) {
            if(size<primes[i]) return primes[i];
        }
        return 0;
    }
