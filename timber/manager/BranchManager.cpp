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
        go.sprites[i].setOrigin(220, 20);
    }
}

void BranchManager::update() {
    int i = 0;
    for (auto d = go.sprites.begin(); d != go.sprites.end(); ++d) {
        float height = i * 150;
        if (Positions[i] == side::LEFT) {
            // Move to the left side
            d->setPosition(610, height);
            // Flip the sprite round the other way
            d->setRotation(180);
        } else if (Positions[i] == side::RIGHT) {
            // Move the sprite to the right
            d->setPosition(1330, height);
            // set the rotation
            d->setRotation(0);
        } else {
            // hide the branch
            d->setPosition(3000, height);
        }
        i++;
    }
}

