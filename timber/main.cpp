const int EXIT_SUCCESS=0;
const int WINDOW_WIDTH=800;
const int WINDOW_HEIGHT=600;

#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"

using namespace sf;
using namespace std;



// forward declaration
void OutVideoModes();

int main(int, char const**)
{
    OutVideoModes();
    VideoMode vm(WINDOW_WIDTH, WINDOW_HEIGHT);
    RenderWindow window(vm, "Timber!!");
    Texture textureBackround;
    if (!textureBackround.loadFromFile(resourcePath() + "cute_image.jpg")) {
        return 1;
    }
    
    // create a sprite
    Sprite spriteBackround;
    spriteBackround.setTexture(textureBackround);
    spriteBackround.setPosition(0, 0);
    
    while (window.isOpen()) {
        // Handle players input
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        
        // update the scene
        // create a texture to hold a graphic on the GPU
        
        // draw the scene
        
        // clear everything from the last frame
        window.clear();
        window.draw(spriteBackround);
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
