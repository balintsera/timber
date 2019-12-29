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

class MovingSprite : public Sprite {
public:
    bool active = false;
    double speed = 0.0f;
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
    
    GameObject(string path, float x = 0, float y = 0) {
        path = path;
        if (!texture.loadFromFile(graphicsPath + path)) {
            throw EXIT_FILE_NOT_FOUND_ERROR;
        }
        
        addSprite(x, y);
    }
    
    void addSprite(float x = 0, float y = 0) {
        MovingSprite sp;
        sp.setTexture(texture);
        sp.setPosition(x, y);
        sprites.push_back(sp);
    }
    
    void rePositionAt(int num = 0, float x = 0, float y = 0) {
        if (num >= sprites.size()) {
            return;
        }
        cout << "reposition" << x << " " << y << "\n";
        sprites[num].setPosition(x, y);
    }
    
    void draw(RenderWindow &win) {
        for (auto d = sprites.begin(); d != sprites.end(); ++d) {
            win.draw(*d);
        }
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
    
    GameObject cloud("cloud.png");
    cloud.addSprite(0, 250);
    cloud.addSprite(0, 500);
    for (auto sp = cloud.sprites.begin(); sp != cloud.sprites.end(); ++sp) {
        drawings.push_back(*sp);
    }
    
    // position to the center horizontally
    GameObject tree("tree.png");
    int x = (WINDOW_WIDTH/2) - ((tree.sprites[0].getLocalBounds().width)/2);
    tree.rePositionAt(0, x);
    drawings.push_back(tree.sprites[0]);
    
    GameObject bee("bee.png", 1000, 800);
    drawings.push_back(bee.sprites[0]);
    
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
        if (!bee.sprites[0].active) {
            srand((int)time(0));
            bee.sprites[0].speed = (rand() % 200) + 200;
            srand((int)time(0) * 10);
            float height = (rand() % 500) + 500;
            bee.rePositionAt(0, bee.sprites[0].getPosition().x, height);
            bee.sprites[0].active = true;
        } else {
            // move the bee
            float x =  bee.sprites[0].getPosition().x - (bee.sprites[0].speed * dt.asSeconds());
            float y = bee.sprites[0].getPosition().y;
            bee.rePositionAt(0, x, y);
            cout << "new pos: " << x << " " << y << "\n";
            // if it reached the left-hand edge
            if (bee.sprites[0].getPosition().x < -100) {
                 bee.sprites[0].active = false;
            }
           
        }
        
        
        // clear everything from the last frame
        window.clear();
        
        bg.draw(window);
        tree.draw(window);
        cloud.draw(window);
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


