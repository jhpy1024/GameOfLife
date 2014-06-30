#include "Application.hpp"

int main()
{
    Application application(600, 600, 50, sf::seconds(0.2f));
    application.run();

    return 0;
}
