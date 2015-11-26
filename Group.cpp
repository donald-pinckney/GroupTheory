//
//  Group.cpp
//  GroupTheory
//
//  Created by Donald Pinckney on 10/16/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//


template <typename T>
bool Group<T>::closed() {
    for(int i = 0; i < this->setCount; i++) {
        const T &x = this->set[i];
        for(int j = 0; j < this->setCount; j++) {
            const T &y = this->set[j];
            T *result = operation(x, y);
            
            bool found = false;
            for (int k = 0; k < this->setCount; k++) {
                if(this->set[k] == *result) {
                    found = true;
                    break;
                }
            }
            
            delete result;
            
            if(found == false) {
                return false;
            }
        }
    }
    
    return true;
}


 
template <typename T>
const T* Group<T>::identity() {
    for (int i = 0; i < this->setCount; i++) {
        T &e = this->set[i];
        bool foundIdentity = true;
        
        for (int j = 0; j < this->setCount; j++) {
            T &x = this->set[j];
            T *res1 = operation(e, x);
            T *res2 = operation(x, e);
            
            if(x != *res1 || x != *res2) {
                
                delete res1;
                delete res2;
                
                foundIdentity = false;
                break;
            }
            
            delete res1;
            delete res2;
        }
        
        if (foundIdentity) {
            return &e;
        }
    }
    
    return NULL;
}

template <typename T>
const T* Group<T>::inverse(const T &a, const T& e) {
    for (int i = 0; i < this->setCount; i++) {
        T &aInv = this->set[i];
        T *res1 = operation(a, aInv);
        T *res2 = operation(aInv, a);
        
        if(*res1 == e && *res2 == e) {
            
            delete res1;
            delete res2;
            
            return &aInv;
        }
        
        delete res1;
        delete res2;
    }
    
    return NULL;
}

template <typename T>
bool Group<T>::closedUnderInverse() {
    const T* e = identity();
    
    if(e == NULL) {
        return false;
    }
    
    for (int i = 0; i < this->setCount; i++) {
        T *x = this->set + i;
        if (inverse(*x, *e) == NULL) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool Group<T>::isGroup() {
    return this->setCount > 0 && closed() && closedUnderInverse();
}

