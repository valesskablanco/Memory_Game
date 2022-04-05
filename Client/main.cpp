#include "client.hpp"
#include "interface.hpp"
#include "button.hpp"

int main()
{
    Interface *GUI = new Interface();
    GUI->run();
    delete GUI;
}
