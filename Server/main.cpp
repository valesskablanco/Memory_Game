#include "interface.hpp"

int main()
{
    Interface *server_gui = new Interface();
    server_gui->run();
    delete server_gui;
}