const int EXIT_SUCCESS=0;
const int WINDOW_WIDTH=1280;
const int WINDOW_HEIGHT=960;

#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


int main(int, char const**)
{
  
    VideoMode vm(WINDOW_WIDTH, WINDOW_HEIGHT);
    RenderWindow(vm, "Timber!!", Style::Fullscreen);
    
    return EXIT_SUCCESS;
}

// helper function to print out supported video resolutions
void OutVideoModes() {
    vector<VideoMode> modes = VideoMode::getFullscreenModes();
    for (auto i = modes.begin(); i != modes.end(); ++i) {
        cout << "Mode " << i->width << "-" << i->height << "-" << i->bitsPerPixel << " is valid" << endl;
    }
}
