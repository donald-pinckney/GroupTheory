//
//  Permutation.cpp
//  GroupTheory
//
//  Created by Donald Pinckney on 10/16/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#include "Permutation.h"

unsigned int factorial(unsigned int n) {
    unsigned int product = 1;
    for (unsigned int i = 2; i <= n; i++) {
        product *= i;
    }
    return product;
}

// NOTE: THIS ALLOCATES MEMORY! YOU MUST CALL DELETE WHEN DONE.
Permutation *Permutation::compose(const Permutation &x, const Permutation &y) {
    Permutation *r = new Permutation();
    r->count = x.count;
    r->values = new unsigned int[x.count];
    
    for (unsigned int i = 0; i < x.count; i++) {
        r->values[i] = x.values[y.values[i] - 1];
    }
    return r;
}


bool operator==(const Permutation &lhs, const Permutation &rhs) {
    if(lhs.count != rhs.count) {
        return false;
    }
    
    for (unsigned int i = 0; i < lhs.count; i++) {
        if(lhs.values[i] != rhs.values[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const Permutation &lhs, const Permutation &rhs) {
    return !(lhs == rhs);
}

std::ostream & operator<<(std::ostream &lhs, const Permutation &rhs) {
    lhs << '(';
    for (unsigned int i = 0; i < rhs.count; i++) {
        lhs << rhs.values[i];
        if (i != rhs.count - 1) {
            lhs << ' ';
        }
    }
    lhs << ')';
    
    return lhs;
}

// NOTE: THIS ALLOCATES MEMORY! YOU MUST CALL DELETE WHEN DONE.
Permutation *Permutation::generatePermutations(unsigned int n, unsigned int *count) {
    *count = factorial(n);
    
    Permutation *newPerms = new Permutation[*count];
    
    unsigned int *nums = new unsigned int[n];
    for (unsigned int i = 0; i < n; i++) {
        nums[i] = i + 1;
    }
    
    unsigned int i = 0;
    do {
        newPerms[i].values = new unsigned int[n];
        memcpy(newPerms[i].values, nums, sizeof(unsigned int) * n);
        
        newPerms[i].count = n;
        
        i++;
    } while(std::next_permutation(nums, nums + n));
    
    if(i != *count) {
        printf("ERROR: count != factorial(n).\n");
    }
    
    delete [] nums;
    
    return newPerms;
}