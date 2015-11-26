//
//  CommonGroups.hpp
//  GroupTheory
//
//  Created by Donald Pinckney on 10/18/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#ifndef CommonGroups_hpp
#define CommonGroups_hpp

#include <stdio.h>
#include "Group.h"
#include "Permutation.h"
#include "DihedralIsometry.h"

// NOTE: THIS ALLOCATES MEMORY! YOU MUST CALL DELETE WHEN DONE.
Group<Permutation> *CommonGroups_Sn(int n);
Group<DihedralIsometry> *CommonGroups_Dn(int n);




#endif /* CommonGroups_hpp */
