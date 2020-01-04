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
        //go.sprites[i].setOrigin(220, 20);
    }
}

void BranchManager::update() {
    int i = 0;
    for (auto d = go.sprites.begin(); d != go.sprites.end(); ++d) {
        float height = i * 90;
        if (Positions[i] == side::LEFT) {
            // Move to the left side
            d->setPosition(660, height);
            // Flip the sprite round the other way
            d->setRotation(180);
        } else if (Positions[i] == side::RIGHT) {
            // Move the sprite to the right
            d->setPosition(940, height);
            // set the rotation
            d->setRotation(0);
        } else {
            // hide the branch
            d->setPosition(-3000, height);
        }
        i++;
    }
}

void BranchManager::move() {
    for (int j = numBranches-1; j > 0; j--) {
        Positions[j] = Positions[j-1];
    }
    
    // Spawn a new branch at position 0
    srand((int)time(0));
    int r = (rand() % 5);
    switch(r) {
        case 0:
            Positions[0] = side::LEFT;
            break;
        case 1:
            Positions[0] = side::RIGHT;
        default:
            Positions[0] = side::NONE;
    }
}

