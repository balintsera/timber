//
//  BranchManager.hpp
//  timber
//
//  Created by Séra Bálint on 2020. 01. 01..
//  Copyright © 2020. Séra Bálint. All rights reserved.
//

#ifndef BranchManager_hpp
#define BranchManager_hpp

#include <stdio.h>
#include "../model/GameObject.hpp"


class BranchManager {
public:
    BranchManager(int branchNum = 6);
    void generate();
    GameObject go;
    int numBranches;
};

#endif /* BranchManager_hpp */
