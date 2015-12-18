//
//  DihedralIsometry.cpp
//  GroupTheory
//
//  Created by Donald Pinckney on 11/16/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#include "DihedralIsometry.h"

int rotationMod(int rotationIndex, int mod) {
    int mult = abs(rotationIndex) / mod + 1;
    return (rotationIndex + mult*mod) % mod;
}

// NOTE: THIS ALLOCATES MEMORY! YOU MUST CALL DELETE WHEN DONE.
DihedralIsometry *DihedralIsometry::compose(const DihedralIsometry &x, const DihedralIsometry &y) {
    bool reflects = x.reflects != y.reflects;
    
    int rotationIndex;
    if(x.reflects) {
        rotationIndex = x.rotationIndex - y.rotationIndex;
    } else {
        rotationIndex = x.rotationIndex + y.rotationIndex;
    }
    rotationIndex = rotationMod(rotationIndex, x.n);
    
    DihedralIsometry *iso = new DihedralIsometry(x.n, reflects, rotationIndex);

    return iso;
}

// NOTE: THIS ALLOCATES MEMORY! YOU MUST CALL DELETE WHEN DONE.
DihedralIsometry *DihedralIsometry::generateIsometries(unsigned int n, unsigned int *count) {
    *count = 2*n;
    
    DihedralIsometry *isos = new DihedralIsometry[*count];
    
    for (unsigned int i = 0; i < n; i++) {
        isos[i].n = n;
        isos[i].reflects = false;
        isos[i].rotationIndex = i;
        
        
        isos[i + n].n = n;
        isos[i + n].reflects = true;
        isos[i + n].rotationIndex = i;
    }
    
    return isos;
}

bool operator==(const DihedralIsometry &lhs, const DihedralIsometry &rhs) {
    return lhs.n == rhs.n && lhs.reflects == rhs.reflects && lhs.rotationIndex == rhs.rotationIndex;
}
bool operator!=(const DihedralIsometry &lhs, const DihedralIsometry &rhs) {
    return !(lhs == rhs);
}
std::ostream & operator<<(std::ostream &lhs, const DihedralIsometry &rhs) {
    if(rhs.rotationIndex == 0 && rhs.reflects == false) {
        lhs << "1";
    }
    else if(rhs.rotationIndex != 0) {
        lhs << "x^" << rhs.rotationIndex;
    }
    lhs << (rhs.reflects ? "y" : "");
    
    return lhs;
}
