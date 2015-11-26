//
//  CommonGroups.cpp
//  GroupTheory
//
//  Created by Donald Pinckney on 10/18/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#include "CommonGroups.h"

// NOTE: THIS ALLOCATES MEMORY! YOU MUST CALL DELETE WHEN DONE.
Group<Permutation> *CommonGroups_Sn(int n) {
    unsigned int count = 0;
    Permutation *perms = Permutation::generatePermutations(n, &count);
    
    Group<Permutation> *G = new Group<Permutation>(perms, count, Permutation::compose);
    
    return G;
}

// NOTE: THIS ALLOCATES MEMORY! YOU MUST CALL DELETE WHEN DONE.
Group<DihedralIsometry> *CommonGroups_Dn(int n) {
    unsigned int count = 0;
    DihedralIsometry *iso = DihedralIsometry::generateIsometries(n, &count);
    
    Group<DihedralIsometry> *G = new Group<DihedralIsometry>(iso, count, DihedralIsometry::compose);
    
    return G;
}