//
//  Subgroup.cpp
//  GroupTheory
//
//  Created by Donald Pinckney on 10/18/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#include <vector>
#include <math.h>
#include <strings.h>

using namespace std;

void incrementMask(char *mask, unsigned int maskSize, unsigned int *maskSetCount) {
    mask[0]++;
    
    unsigned int setCount = 0;
    
    for (unsigned int i = 0; i < maskSize - 1; i++) {
        if(mask[i] == 2) {
            mask[i] = 0;
            mask[i + 1]++;
        } else if(mask[i] == 1) {
            setCount++;
        }
    }
    
    if(mask[maskSize - 1] == 2) {
        mask[maskSize - 1] = 0;
        setCount = 0;
    } else if(mask[maskSize - 1] == 1){
        setCount++;
    }
    
    *maskSetCount = setCount;
}

template <typename T>
bool Subgroup<T>::isNormal() const {
    const T *superIdentity = superGroup->identity();
    
    const T *superSet = superGroup->getSet();
    unsigned int superCount = superGroup->getSetCount();
    
    for (unsigned int i = 0; i < superCount; i++) {
        const T &g = superSet[i];
        const T *gInv = superGroup->inverse(g, *superIdentity);
        
        for (unsigned int j = 0; j < this->setCount; j++) {
            const T &h = this->set[j];
            
            const T *rhs = this->operation(h, *gInv);
            const T *res = this->operation(g, *rhs);
            
            bool found = false;
            for (unsigned int k = 0; k < this->setCount; k++) {
                if(this->set[k] == *res) {
                    found = true;
                    break;
                }
            }
            
            if(found == false) {
                return false;
            }
        }
    }
    
    return true;
}


// NOTE: THIS ALLOCATES MEMORY! YOU MUST CALL DELETE WHEN DONE.
template <typename T>
Subgroup<T> **Subgroup<T>::generateSubgroups(Group<T> *G, unsigned long long *subgroupCount) {
    vector<Subgroup<T> *> *subgroups = new vector<Subgroup<T> *>();
    
    unsigned int setCount = G->getSetCount();
    const T *set = G->getSet();
    
    char *mask = new char[setCount];
    bzero(mask, sizeof(char) * setCount);
    unsigned int maskSetCount = 0;
    
    unsigned long long numPossibleSubgroups = 1ul << (unsigned long long)setCount;
    
    for (unsigned long long i = 0; i < numPossibleSubgroups; i++) {
        T *newSet = new T[maskSetCount];
        
        int insertIndex = 0;
        for (unsigned int j = 0; j < setCount; j++) {
            if(mask[j]) {
                newSet[insertIndex] = set[j];
                insertIndex++;
            }
        }
        
        Subgroup<T> *possibleSubgroup = new Subgroup<T>(newSet, maskSetCount, G);
        
        if(possibleSubgroup->isGroup()) {
            subgroups->push_back(possibleSubgroup);
        } else {
            delete possibleSubgroup;
        }
        
        incrementMask(mask, setCount, &maskSetCount);
    }
    
    delete [] mask;
    
    
    *subgroupCount = (unsigned long long)(subgroups->size());
    return subgroups->data();
}

template <typename T>
void Subgroup<T>::freeSubgroups(Subgroup<T> **subgroups, unsigned long long subgroupCount) {
    for (unsigned long long i = 0; i < subgroupCount; i++) {
        delete subgroups[i];
    }
    delete [] subgroups;
}


// NOTE: THIS ALLOCATES MEMORY! YOU MUST CALL DELETE WHEN DONE.
template <typename T>
Set<T> **Subgroup<T>::leftCosets(unsigned int *cosetCount) {

    unsigned int myCount = this->getSetCount();
    unsigned int groupCount = this->superGroup->getSetCount();
    if (groupCount % myCount != 0) {
        *cosetCount = 0;
        return NULL;
    }
    
    unsigned int numCosets = groupCount / myCount;
    *cosetCount = numCosets;
    T ***cosets = new T**[numCosets];
    memset(cosets, 0, sizeof(T*) * numCosets);
    
    int cosetIndex = 0;
    
    const T *superSet = superGroup->getSet();
    for (unsigned int i = 0; i < groupCount; i++) {
        const T &a = superSet[i];
        T **newSet = new T*[myCount];
        
        for (unsigned int j = 0; j < myCount; j++) {
            newSet[j] = this->operation(a, this->set[j]);
        }
        
        
        // Check if newSet is already contained in cosets
        T *compareTo = newSet[0];
        bool isUnique = true;
        for (unsigned int j = 0; j < numCosets; j++) {
            T **coset = cosets[j];
            if(coset == NULL) {
                break;
            }
            
            
            bool foundMatch = false;
            for (unsigned int k = 0; k < myCount; k++) {
                if(*(coset[k]) == *compareTo) {
                    foundMatch = true;
                    break;
                }
            }
            if(foundMatch) {
                isUnique = false;
                break;
            }
        }
        
        if(!isUnique) {
            for (unsigned int j = 0; j < myCount; j++) {
                delete newSet[j];
            }
            delete [] newSet;
            continue;
        }
        
        cosets[cosetIndex] = newSet;
        cosetIndex++;
    }
    
    
    Set<T> **cosetsFinal = new Set<T>*[numCosets];
    for (unsigned int i = 0; i < numCosets; i++) {
        T **coset = cosets[i];
        T *tempCoset = new T[myCount];
        for (unsigned int j = 0; j < myCount; j++) {
            tempCoset[j] = *(coset[j]);
            delete coset[j];
        }
        delete [] coset;
        
        Set<T> *cosetFinal = new Set<T>(tempCoset, myCount);
        cosetsFinal[i] = cosetFinal;
    }
    
    delete [] cosets;
    
    
    return cosetsFinal;
}


template <typename T>
Set<T> **Subgroup<T>::rightCosets(unsigned int *cosetCount) {
    
    unsigned int myCount = this->getSetCount();
    unsigned int groupCount = this->superGroup->getSetCount();
    if (groupCount % myCount != 0) {
        *cosetCount = 0;
        return NULL;
    }
    
    unsigned int numCosets = groupCount / myCount;
    *cosetCount = numCosets;
    T ***cosets = new T**[numCosets];
    memset(cosets, 0, sizeof(T*) * numCosets);
    
    int cosetIndex = 0;
    
    const T *superSet = superGroup->getSet();
    for (unsigned int i = 0; i < groupCount; i++) {
        const T &a = superSet[i];
        T **newSet = new T*[myCount];
        
        for (unsigned int j = 0; j < myCount; j++) {
            newSet[j] = this->operation(this->set[j], a);
        }
        
        
        // Check if newSet is already contained in cosets
        T *compareTo = newSet[0];
        bool isUnique = true;
        for (unsigned int j = 0; j < numCosets; j++) {
            T **coset = cosets[j];
            if(coset == NULL) {
                break;
            }
            
            
            bool foundMatch = false;
            for (unsigned int k = 0; k < myCount; k++) {
                if(*(coset[k]) == *compareTo) {
                    foundMatch = true;
                    break;
                }
            }
            if(foundMatch) {
                isUnique = false;
                break;
            }
        }
        
        if(!isUnique) {
            for (unsigned int j = 0; j < myCount; j++) {
                delete newSet[j];
            }
            delete [] newSet;
            continue;
        }
        
        cosets[cosetIndex] = newSet;
        cosetIndex++;
    }
    
    
    Set<T> **cosetsFinal = new Set<T>*[numCosets];
    for (unsigned int i = 0; i < numCosets; i++) {
        T **coset = cosets[i];
        T *tempCoset = new T[myCount];
        for (unsigned int j = 0; j < myCount; j++) {
            tempCoset[j] = *(coset[j]);
            delete coset[j];
        }
        delete [] coset;
        
        Set<T> *cosetFinal = new Set<T>(tempCoset, myCount);
        cosetsFinal[i] = cosetFinal;
    }
    
    delete [] cosets;
    
    
    return cosetsFinal;
}
