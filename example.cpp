//
//  main.cpp
//  GroupTheory
//
//  Created by Donald Pinckney on 10/16/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#include <iostream>
#include "Group.h"
#include "Subgroup.h"
#include "Permutation.h"
#include "CommonGroups.h"
#include "DihedralIsometry.h"

using namespace::std;

// Example 1: Computing subgroups of Sn
void computeSubgroupsOfSn(int n) {
    cout << "Starting computation of Sn" << endl;
    
    Group<Permutation> *S3 = CommonGroups_Sn(n);
    
    
    unsigned long long numSubgroups = 0;
    Subgroup<Permutation> **subgroups = Subgroup<Permutation>::generateSubgroups(S3, &numSubgroups);
    cout << numSubgroups << " subgroups: " << endl;
    
    vector<Subgroup<Permutation> *> normalSubgroups;
    
    for (int i = 0; i < numSubgroups; i++) {
        Subgroup<Permutation> *subgroup = subgroups[i];
        subgroup->print(cout);
        
        if(subgroup->isNormal()) {
            normalSubgroups.push_back(subgroup);
        }
    }
    
    cout << normalSubgroups.size() << " normal subgroups: " << endl;
    for (auto it = normalSubgroups.begin(); it != normalSubgroups.end(); it++) {
        (*it)->print(cout);
    }
    
    Subgroup<Permutation>::freeSubgroups(subgroups, numSubgroups);
    delete S3;
}


void computeSubgroupsOfDn(int n) {
    cout << "Starting computation of Dn" << endl;
    
    Group<DihedralIsometry> *D3 = CommonGroups_Dn(n);
    
    
    unsigned long long numSubgroups = 0;
    Subgroup<DihedralIsometry> **subgroups = Subgroup<DihedralIsometry>::generateSubgroups(D3, &numSubgroups);
    cout << numSubgroups << " subgroups: " << endl;
    
    vector<Subgroup<DihedralIsometry> *> normalSubgroups;
    
    for (int i = 0; i < numSubgroups; i++) {
        Subgroup<DihedralIsometry> *subgroup = subgroups[i];
        subgroup->print(cout);
        
        if(subgroup->isNormal()) {
            normalSubgroups.push_back(subgroup);
        }
    }
    
    cout << normalSubgroups.size() << " normal subgroups: " << endl;
    for (auto it = normalSubgroups.begin(); it != normalSubgroups.end(); it++) {
        (*it)->print(cout);
    }
    
    
    // Create the subgroup {1, x^5} manually
    DihedralIsometry items[2] = { DihedralIsometry(n, false, 0), DihedralIsometry(n, false, n/2) };
    Subgroup<DihedralIsometry> *mySubgroup = new Subgroup<DihedralIsometry>(items, 2, D3);
    
    if(!mySubgroup->isGroup()) {
        cout << "IS NOT A SUBGROUP!!!" << endl;
    }
    
    
   unsigned int numCosets;
   Set<DihedralIsometry> **leftCosets = mySubgroup->leftCosets(&numCosets);
   cout << numCosets << " left cosets" << endl;
   for (int i = 0; i < numCosets; i++) {
       Set<DihedralIsometry> *coset = leftCosets[i];
       coset->print(cout);
   }
   
   
   Set<DihedralIsometry> **rightCosets = mySubgroup->rightCosets(&numCosets);
   cout << numCosets << " right cosets" << endl;
   for (int i = 0; i < numCosets; i++) {
       Set<DihedralIsometry> *coset = rightCosets[i];
       coset->print(cout);
   }
   
   cout << "Is H normal? " << mySubgroup->isNormal() << endl;
   
   
   Subgroup<DihedralIsometry>::freeSubgroups(subgroups, numSubgroups);
   Set<DihedralIsometry>::freeSets(leftCosets, numCosets);
   Set<DihedralIsometry>::freeSets(rightCosets, numCosets);
    
    delete D3;
    delete mySubgroup;
}


int main(int argc, const char * argv[]) {
    
    computeSubgroupsOfSn(3);
    cout << endl;
    computeSubgroupsOfDn(10);

    
    return 0;
}
