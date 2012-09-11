/* 
 * File:   hash.h
 * Author: mark
 *
 * Created on September 10, 2012, 12:23 PM
 */

#ifndef HASH_H
#define	HASH_H

#include <vector>
#include <string>

class hashTable {
    
public:
    hashTable(int size = 0);
    
    int insert(const std::string &key, void *pv = NULL);
    
    bool contains(const std::string &key);
    
    void *getPointer(const std::string &key, bool *b = NULL);
    
    int setPointer(const std::string &key, void *pv);
    
    bool remove(const std::string &key);
    
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
    
    int hash(const std::string &key);
    
    int findPos(const std::string &key);
    
    bool rehash();
    
    static unsigned int getPrime(int size);
};

#endif	/* HASH_H */

