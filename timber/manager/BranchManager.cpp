//
//  BranchManager.cpp
//  timber
//
//  Created by Séra Bálint on 2020. 01. 01..
//  Copyright © 2020. Séra Bálint. All rights reserved.
//

#include "BranchManager.hpp"

#include <SFML/Graphics.hpp>
#include "../model/GameObject.hpp"

BranchManager::BranchManager(int branchNum) : go("branch.png", -2000, -2000) {
    numBranches = branchNum;
    generate();
}

void BranchManager::generate() {
    // the first one is automatically generated
    for (int i = 0; i < numBranches - 1; i++) {
        go.addSprite(-2000, -2000);
        // how to set origin
    }
    
    
}

