#include "gamewindow.hpp"
#include <ctime>

using namespace cv;

int main()
{
    srand(time(0));
    GameWindow gameWindow;
    gameWindow.run();

    return 0;
}
