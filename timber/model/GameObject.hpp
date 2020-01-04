//
//  GameObject.cpp
//  timber
//
//  Created by Séra Bálint on 2019. 12. 30..
//  Copyright © 2019. Séra Bálint. All rights reserved.
//
#ifndef GAMEOBJECT_hpp
#define GAMEOBJECT_hpp

const int EXIT_FILE_NOT_FOUND_ERROR = 1;

#include <iostream>

#include <SFML/Graphics.hpp>

#include "../ResourcePath.hpp"


using namespace std;
using namespace sf;

struct RandBounds {
    RandBounds();
    RandBounds(int min, int max);
    int min;
    int max;
};

class MovingSprite : public Sprite {
public:
    bool active = false;
    double speed = 0.0f;
    void setXDirection(bool left);
    int getXDirection();
    
private:
    int xDirection = -1;
};

class GameObject {
private:
    string graphicsPath = resourcePath() + "graphics/";
    string path;
    Texture texture;
public:
    bool active;
    double speed;
    vector<MovingSprite> sprites;
    
    GameObject(string path, float x = 0, float y = 0, bool left = true);
    
    void addSprite(float x = 0, float y = 0, bool left = true);
    
    void rePositionAt(int num = 0, float x = 0, float y = 0);
    
    void animateAt(int num = 0, Time dt = seconds(0.0), RandBounds hBounds = RandBounds(), RandBounds sBounds = RandBounds(), float xPos = 1000, int xMax = -100);
    
    void draw(RenderWindow &win);
};

#endif /* GAMEOBJECT_hpp */
