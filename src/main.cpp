#include "Application.hpp"

int main()
{
    Application application(600, 650, 50, sf::milliseconds(10));
    application.run();

    return 0;
}
