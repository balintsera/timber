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
#include <SFML/Graphics.hpp>

#include "../model/GameObject.hpp"


class BranchManager {
public:
    GameObject go;
    int numBranches;
    
    BranchManager(int branchNum = 6);
    void generate();
    void update();    
    
private:
    enum class side { LEFT, RIGHT, NONE };
    side Positions[6];
};


#endif /* BranchManager_hpp */
