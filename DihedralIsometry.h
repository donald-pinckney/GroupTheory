//
//  DihedralIsometry.hpp
//  GroupTheory
//
//  Created by Donald Pinckney on 11/16/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#ifndef DihedralIsometry_hpp
#define DihedralIsometry_hpp

#include <stdio.h>
#include <iostream>

int rotationMod(int rotationIndex, int mod);

class DihedralIsometry {
    int n;
    bool reflects;
    int rotationIndex;
    
public:
    DihedralIsometry() : n(0), reflects(false), rotationIndex(0) { }
    DihedralIsometry(int numSides, bool r, int rI) : n(numSides), reflects(r), rotationIndex(rI) { }
    
    DihedralIsometry(const DihedralIsometry &d) : n(d.n), reflects(d.reflects), rotationIndex(d.rotationIndex) { }
    
    
    unsigned int getVertexCount() const { return n; }
//    const unsigned int &operator[](unsigned int i) const { return values[i]; }
    
    
    friend bool operator==(const DihedralIsometry &lhs, const DihedralIsometry &rhs);
    friend bool operator!=(const DihedralIsometry &lhs, const DihedralIsometry &rhs);
    friend std::ostream & operator<<(std::ostream &lhs, const DihedralIsometry &rhs);
    
    // NOTE: THIS ALLOCATES MEMORY! YOU MUST CALL DELETE WHEN DONE.
    static DihedralIsometry *compose(const DihedralIsometry &x, const DihedralIsometry &y);
    
    // NOTE: THIS ALLOCATES MEMORY! YOU MUST CALL DELETE WHEN DONE.
    static DihedralIsometry *generateIsometries(unsigned int n, unsigned int *count);
};


#endif /* DihedralIsometry_hpp */
