//
//  GameObject.cpp
//  timber
//
//  Created by Séra Bálint on 2019. 12. 30..
//  Copyright © 2019. Séra Bálint. All rights reserved.
//
const int EXIT_FILE_NOT_FOUND_ERROR = 1;

#include <iostream>

#include <SFML/Graphics.hpp>

#include "../ResourcePath.hpp"


using namespace std;
using namespace sf;

struct RandBounds {
    RandBounds(): min(100), max(100) {}
    RandBounds(int min, int max) {
        min = min;
        max = max;
    }
    int min;
    int max;
};

class MovingSprite : public Sprite {
public:
    bool active = false;
    double speed = 0.0f;
    void setXDirection(bool left) {
        xDirection = left ? -1 : 1;
    };
    int getXDirection() {
        return xDirection;
    };
    
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
    
    GameObject(string path, float x = 0, float y = 0, bool left = true) {
        path = path;
        if (!texture.loadFromFile(graphicsPath + path)) {
            throw EXIT_FILE_NOT_FOUND_ERROR;
        }
        
        addSprite(x, y, left);
    }
    
    void addSprite(float x = 0, float y = 0, bool left = true) {
        MovingSprite sp;
        sp.setXDirection(left);
        sp.setTexture(texture);
        sp.setPosition(x, y);
        sprites.push_back(sp);
    }
    
    void rePositionAt(int num = 0, float x = 0, float y = 0) {
        if (num >= sprites.size()) {
            return;
        }
        //cout << "reposition" << x << " " << y << "\n";
        sprites[num].setPosition(x, y);
    }
    
    void animateAt(int num = 0, Time dt = seconds(0.0), RandBounds hBounds = RandBounds(), RandBounds sBounds = RandBounds(), float xPos = 1000, int xMax = -100) {
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
    
    void draw(RenderWindow &win) {
        for (auto d = sprites.begin(); d != sprites.end(); ++d) {
            win.draw(*d);
        }
    }
};
