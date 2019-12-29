const int EXIT_SUCCESS=0;
const int EXIT_FILE_NOT_FOUND_ERROR = 1;
const int WINDOW_WIDTH=1600;
const int WINDOW_HEIGHT=1200;

#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"

using namespace sf;
using namespace std;



// forward declaration
void OutVideoModes();

class GameObject {
private:
    string graphicsPath = resourcePath() + "graphics/";
    string path;
    int x;
    int y;
    Texture texture;
public:
    vector<Sprite> sprites;
    
    GameObject(string path, int x = 0, int y = 0) {
        path = path;
        if (!texture.loadFromFile(graphicsPath + path)) {
            throw EXIT_FILE_NOT_FOUND_ERROR;
        }
        
        addSprite(x, y);
    }
    
    void addSprite(int x = 0, int y = 0) {
        Sprite sp;
        sp.setTexture(texture);
        sp.setPosition(x, y);
        sprites.push_back(sp);
    }
    
    void rePositionAt(int num = 0, int x = 0, int y = 0) {
        if (num >= sprites.size()) {
            return;
        }
        sprites[num].setPosition(x, y);
    }
};

class Drawings : public vector<Sprite> {
public:
    void draw(RenderWindow &window) {
        for (auto d = this->begin(); d != this->end(); ++d) {
            window.draw(*d);
        }
    }
private:
    RenderWindow window;
};

int main(int, char const**)
{
    // add everything to be drawn to this vector
    //vector<Sprite> drawings;
   
    //OutVideoModes();
    VideoMode vm(WINDOW_WIDTH, WINDOW_HEIGHT);
    RenderWindow window(vm, "Timber!!");
    Drawings drawings;
    
    GameObject bg("background.png");
    drawings.push_back(bg.sprites[0]);
    
    GameObject cloud("cloud.png", 20, 100);
    cloud.addSprite(400, 100);
    cloud.addSprite(800, 100);
    for (auto sp = cloud.sprites.begin(); sp != cloud.sprites.end(); ++sp) {
        drawings.push_back(*sp);
    }
    
    // position to the center horizontally
    GameObject tree("tree.png");
    int x = (WINDOW_WIDTH/2) - ((tree.sprites[0].getLocalBounds().width)/2);
    tree.rePositionAt(0, x);
    drawings.push_back(tree.sprites[0]);
    
    GameObject bee("bee.png", 440, 600);
    bool beeActive = false;
    bool beeSpeed = 0.0f;
    drawings.push_back(bee.sprites[0]);
    

    
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

        
        // clear everything from the last frame
        window.clear();
        
        drawings.draw(window);
        
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


