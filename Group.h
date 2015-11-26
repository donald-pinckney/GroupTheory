//
//  Group.hpp
//  GroupTheory
//
//  Created by Donald Pinckney on 10/16/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#ifndef Group_hpp
#define Group_hpp

#include <iostream>
#include <stdio.h>

#include "Set.h"


template <typename T>
class Group : public Set<T> {
    
protected:
    // NOTE: THIS ALLOCATES MEMORY! YOU MUST CALL DELETE WHEN DONE.
    typedef T *(*Composition)(const T &x, const T &y);
    Composition operation;
    
public:
    Group(T *s, unsigned int c, Composition op) : Set<T>(s, c), operation(op) { }
    Group(const Group &g) : Set<T>(g), operation(g.operation) { }
    
    
    const Composition getOperation() const {
        return operation;
    }
    
    
    bool isGroup();

    bool closed();
    const T* identity();
    const T* inverse(const T &a, const T& e);
    bool closedUnderInverse();
};

#include "Group.cpp"


#endif /* Group_hpp */



