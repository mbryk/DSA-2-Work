/* 
 * File:   hash.cpp
 * Author: mark
 * 
 * Created on September 10, 2012, 12:23 PM
 */

#include "hash.h"
    hashTable(int size = 0) {
        data.resize(size);
    }
    
    int hashTable::insert(const std::string &key, void *pv = NULL) {
        //check size of data. if not enough, call hashTable(200)
        int number;
        number = hash(key);
        data[number]={key, isOccupied=1, isDeleted=0};
        
        
    }
    
    bool contains(const std::string &key){
        number = hash(key);
        data[number]->isOccupied and !Deleted;
        
    }
    
    void *getPointer(const std::string &key, bool *b = NULL){
        
    }
    
    int setPointer(const std::string &key, void *pv){
        
    }
    
    bool remove(const std::string &key){
        
    }
    
private:
    class hashItem {
    
    public:
        std::string key;
        bool isOccupied;
        bool isDeleted;
        void *pv;
    };
    
    int capacity;
    int filled;
    
    std::vector<hashItem> data;
    
    int hash(const std::string &key){
        int number = key[1]+key[2];
        return number;
    }
        
    
    int findPos(const std::string &key);
    
    bool rehash();
    
    static unsigned int getPrime(int size);
};
