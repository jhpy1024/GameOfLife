#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Grid.hpp"

#include <SFML/Graphics.hpp>

class Application
{
public:
    Application(int width, int height, int numCells, const sf::Time& updateRate);

    void run();

    void handleInput();
    void update();
    void draw();

private:
    void handleMousePress(const sf::Event& event);
    void handleKeyPress(const sf::Event& event);

private:
    const int WIDTH;
    const int HEIGHT;
    const int NUM_CELLS;
    const sf::Time UPDATE_RATE;

    sf::RenderWindow m_Window;
    sf::Clock m_Clock;

    sf::Time m_LastUpdateTime;

    Grid m_Grid;
};

#endif
