//
//  Set.cpp
//  GroupTheory
//
//  Created by Donald Pinckney on 11/17/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#include <iostream>

template <typename T>
void Set<T>::print(std::ostream &s) const {
    s << '{';
    for (int i = 0; i < setCount; i++) {
        s << set[i];
        if (i != setCount - 1) {
            s << ", ";
        }
    }
    s << '}' << std::endl;
}

template <typename T>
void Set<T>::freeSets(Set<T> **sets, unsigned int setCount) {
    for (int i = 0; i < setCount; i++) {
        delete sets[i];
    }
    delete [] sets;
}