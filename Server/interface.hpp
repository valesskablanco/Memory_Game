#ifndef interface_h
#define interface_h

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>
#include <array>
#include <unistd.h>
#include <string>
#include <thread>
#include "server.hpp"
#include "../Utils/common.hpp"

using namespace sf;
using namespace std;
class Interface
{
public:
    Interface();
    void run();
    string memoryUsage();
    void drawLabels();
    void runServer();
    Server server;

private:
    RenderWindow *window;
    Font font;
    Text memory_usage;
    Text page_faults;
    Text page_hits;
};

#endif