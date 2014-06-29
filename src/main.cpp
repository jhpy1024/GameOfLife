#include "Application.hpp"

int main()
{
    Application application(600, 600, 20, sf::seconds(1.f));
    application.run();

    return 0;
}
