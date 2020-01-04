//
//  GameObject.cpp
//  timber
//
//  Created by Séra Bálint on 2019. 12. 30..
//  Copyright © 2019. Séra Bálint. All rights reserved.
//

#include "GameObject.hpp"

#include <iostream>

#include <SFML/Graphics.hpp>

#include "../ResourcePath.hpp"


using namespace std;
using namespace sf;
RandBounds::RandBounds() : min(100), max(100) {
}

void MovingSprite::setXDirection(bool left) {
    xDirection = left ? -1 : 1;
}

int MovingSprite::getXDirection() {
    return xDirection;
}
 


    
GameObject::GameObject(string path, float x, float y, bool left) {
    path = path;
    if (!texture.loadFromFile(graphicsPath + path)) {
        throw EXIT_FILE_NOT_FOUND_ERROR;
    }
    
    addSprite(x, y, left);
}
    
void GameObject::addSprite(float x, float y, bool left) {
    MovingSprite sp;
    sp.setXDirection(left);
    sp.setTexture(texture);
    sp.setPosition(x, y);
    sprites.push_back(sp);
}
    
void GameObject::rePositionAt(int num, float x, float y) {
    if (num >= sprites.size()) {
        return;
    }
    //cout << "reposition" << x << " " << y << "\n";
    sprites[num].setPosition(x, y);
}
    
void GameObject::animateAt(int num, Time dt, RandBounds hBounds, RandBounds sBounds, float xPos, int xMax) {
    if (!sprites[num].active) {
        srand((int)time(0));
        sprites[num].speed = sprites[num].getXDirection() * ((rand() % sBounds.min) + sBounds.max);
        srand((int)time(0) * 10);
        float height = (rand() % hBounds.min) + hBounds.max;
        rePositionAt(num, xPos, height);
        //cout << "new rand pos: " << sprites[0].getPosition().x << " " << height << "\n";

        sprites[num].active = true;
    } else {
        // move the bee
        float x =  sprites[num].getPosition().x + (sprites[num].speed * dt.asSeconds());
        float y = sprites[num].getPosition().y;
        rePositionAt(num, x, y);
        //cout << "new pos: " << x << " " << y << "\n";
        // if it reached the left-hand edge
        bool reachedTheEdge = xMax < 0 ? (sprites[num].getPosition().x < xMax) : (sprites[num].getPosition().x > xMax);
        if (reachedTheEdge) {
            //cout << "new pos less then -100: " << x << " " << y << "\n";
            sprites[num].active = false;
        }
    }
}
    
void GameObject::draw(RenderWindow &win) {
    for (auto d = sprites.begin(); d != sprites.end(); ++d) {
        win.draw(*d);
    }
}

