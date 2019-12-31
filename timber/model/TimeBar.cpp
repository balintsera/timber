//
//  TimeBar.cpp
//  timber
//
//  Created by Séra Bálint on 2019. 12. 31..
//  Copyright © 2019. Séra Bálint. All rights reserved.
//

#include <stdio.h>
#include <SFML/Graphics.hpp>

using namespace sf;

class TimeBar {
public:
    TimeBar() {
        initGraphicObject();
    }
    
    TimeBar(int windWidth) {
        this->windWidth = windWidth;
        initGraphicObject();
    }
    
    TimeBar(int windWidth, float initialTime) {
        this->windWidth = windWidth;
        this->initialTime = initialTime;
        initGraphicObject();
    }
    
    float timeRemaining = 6.0f;
    
    void updateSize() {
        float length = getTimeBarWidthPerSecond() * timeRemaining;
        if (length < 0) {
            return;
        }
        timeBar.setSize(Vector2f(length, timeBarHeight));
    }
    RectangleShape timeBar;

private:
    float initialTime;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    int windWidth = 1600;
    void initGraphicObject() {
        updateSize();
        timeBar.setFillColor(Color::Red);
        timeBar.setPosition(((windWidth/2) - timeBarStartWidth) / 2, 980);
    }
    
    float getTimeBarWidthPerSecond() {
        return timeBarStartWidth / 6;
    }
};
