//
//  HUD.cpp
//  timber
//
//  Created by Séra Bálint on 2019. 12. 30..
//  Copyright © 2019. Séra Bálint. All rights reserved.
//

#include "HUD.hpp"

#include <sstream>
#include <iostream>

#include <SFML/Graphics.hpp>
#include "../ResourcePath.hpp"


using namespace sf;
using namespace std;

class HUD {
public:
    int score = 0;
    Text messageText;
    Text scoreText;
    Font font;
    
    HUD() {
        font.loadFromFile(fontsPath + "KOMIKAP_.ttf");
        
        messageText.setString("Press Enter to start");
        styleText(messageText, 75, Color::White);
        
        updateScoreDisplay();
        styleText(scoreText, 100, Color::Red);
        
        positionText();
    }
    
    void draw(RenderWindow &window) {
        window.draw(scoreText);
        window.draw(messageText);
    }
    
    void updateScoreDisplay() {
        stringstream ss;
        ss << "Score = " << score;
        scoreText.setString(ss.str());
    }
    
private:
    const string fontsPath = resourcePath() + "fonts/";
    void positionText() {
        FloatRect textRect = messageText.getLocalBounds();
        messageText.getLocalBounds();
        double yOffset = 70;
        double x = textRect.left + textRect.width / 2.0f;
        double y = (textRect.top + textRect.height / 2.0f) + yOffset;
        messageText.setPosition(x, y);
        scoreText.setPosition(20, 20);
    }
    
    void styleText(Text &text, int size, Color color) {
        text.setFont(font);
        text.setCharacterSize(size);
        text.setFillColor(color);
    }
};
