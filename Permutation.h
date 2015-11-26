//
//  Permutation.hpp
//  GroupTheory
//
//  Created by Donald Pinckney on 10/16/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#ifndef Permutation_hpp
#define Permutation_hpp

#include <stdlib.h>
#include <algorithm>
#include <iostream>


unsigned int factorial(unsigned int n);

class Permutation {
    unsigned int *values;
    unsigned int count;

public:
    Permutation() : values(NULL), count(0) { }
    Permutation(unsigned int *vals, unsigned int c) : values(vals), count(c) { }
    
    Permutation(const Permutation &p) : count(p.count) {
        values = new unsigned int[p.count];
        memcpy(values, p.values, sizeof(unsigned int) * p.count);
    }
    
    ~Permutation() {
        delete [] values;
    }
    
    unsigned int getCount() const { return count; }
    const unsigned int &operator[](unsigned int i) const { return values[i]; }
    unsigned int &operator[](unsigned int i) { return values[i]; }
    
    
    friend bool operator==(const Permutation &lhs, const Permutation &rhs);
    friend bool operator!=(const Permutation &lhs, const Permutation &rhs);
    friend std::ostream & operator<<(std::ostream &lhs, const Permutation &rhs);
    
    // NOTE: THIS ALLOCATES MEMORY! YOU MUST CALL DELETE WHEN DONE.
    static Permutation *compose(const Permutation &x, const Permutation &y);
    
    // NOTE: THIS ALLOCATES MEMORY! YOU MUST CALL DELETE WHEN DONE.
    static Permutation *generatePermutations(unsigned int n, unsigned int *count);
};




#endif /* Permutation_hpp */
