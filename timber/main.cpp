const int EXIT_SUCCESS=0;
const int WINDOW_WIDTH=1600;
const int WINDOW_HEIGHT=1200;

#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"

#include "model/GameObject.cpp"

using namespace sf;
using namespace std;



// forward declaration
void OutVideoModes();

int main(int, char const**)
{
    //OutVideoModes();
    VideoMode vm(WINDOW_WIDTH, WINDOW_HEIGHT);
    RenderWindow window(vm, "Timber!!");
    
    GameObject bg("background.png");

    GameObject cloud("cloud.png", 0, 0, false);
    cloud.addSprite(0, 250, false);
    cloud.addSprite(0, 500, false);
    
    
    // position to the center horizontally
    GameObject tree("tree.png");
    int x = (WINDOW_WIDTH/2) - ((tree.sprites[0].getLocalBounds().width)/2);
    tree.rePositionAt(0, x);
    
    GameObject bee("bee.png", 1000, 800, true);
    
    Clock clock;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        Time dt = clock.restart();
        RandBounds hBounds;
        hBounds.min = 200;
        hBounds.max = 200;
        RandBounds sBounds;
        sBounds.min = 500;
        sBounds.max = 500;
        bee.animateAt(0, dt, hBounds, sBounds, 1920);
        
        hBounds.max = 0;
        sBounds.min = 150;
        sBounds.max = 0;
        cloud.animateAt(0, dt, hBounds, sBounds, -200, 1920);
        
        sBounds.min = 80;
        cloud.animateAt(1, dt, hBounds, sBounds, 200, 1920);
        
        hBounds.min = 300;
        hBounds.max = 40;
        sBounds.min = 110;
        sBounds.max = 10;
        cloud.animateAt(2, dt, hBounds, sBounds, -200, 1920);
        
        // clear everything from the last frame
        window.clear();
        
        bg.draw(window);
        cloud.draw(window);
        tree.draw(window);
        bee.draw(window);
        
        window.display();
        
    }
    return EXIT_SUCCESS;
}

// helper function to print out supported video resolutions
void OutVideoModes() {
    vector<VideoMode> modes = VideoMode::getFullscreenModes();
    for (auto i = modes.begin(); i != modes.end(); ++i) {
        cout << "Mode " << i->width << "-" << i->height << "-" << i->bitsPerPixel << " is valid" << endl;
    }
}


