//
//  Set.hpp
//  GroupTheory
//
//  Created by Donald Pinckney on 11/17/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#ifndef Set_hpp
#define Set_hpp

#include <stdio.h>

template <typename T>
class Set {
    
protected:
    T *set;
    unsigned int setCount;
    bool isCopied;
    
public:
    Set(T *s, unsigned int c) : set(s), setCount(c), isCopied(false) { }
    Set(const Set &g) : setCount(g.setCount), isCopied(true) {
        set = new T[g.setCount];
        memcpy(set, g.set, sizeof(T) * g.setCount);
    }
    Set() {
        if(isCopied) {
            delete [] set;
        }
    }
    
    const T* getSet() const {
        return set;
    }
    
    unsigned int getSetCount() const {
        return setCount;
    }
    
    void print(std::ostream &s) const;
    
    static void freeSets(Set<T> **sets, unsigned int setCount);
    
};

#include "Set.cpp"


#endif /* Set_hpp */
