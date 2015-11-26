//
//  Subgroup.hpp
//  GroupTheory
//
//  Created by Donald Pinckney on 10/18/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#ifndef Subgroup_hpp
#define Subgroup_hpp

#include "Group.h"

template <typename T>
class Subgroup : public Group<T> {
    
private:
    Group<T> *superGroup;
    
public:
    Subgroup(T *s, unsigned int c, Group<T> *sg) : Group<T>(s, c, sg->getOperation()), superGroup(sg) { }
    
    // Assumes that isGroup() and superGroup.isGroup() is already true.
    bool isNormal() const;
    
    // NOTE: THIS ALLOCATES MEMORY! YOU MUST CALL DELETE WHEN DONE.
    static Subgroup<T> **generateSubgroups(Group<T> *G, unsigned long long *subgroupCount);
    static void freeSubgroups(Subgroup<T> **subgroups, unsigned long long subgroupCount);
    
    Set<T> **leftCosets(unsigned int *subgroupCount);
    Set<T> **rightCosets(unsigned int *subgroupCount);

};

#include "Subgroup.cpp"


#endif /* Subgroup_hpp */
