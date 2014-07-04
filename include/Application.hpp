#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Grid.hpp"
#include "InfoBar.hpp"

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
    void drawGrid();
    void drawInfoBar();

    void handleMousePress(const sf::Event& event);
    void handleKeyPress(const sf::Event& event);
    void handleInfoBarInput();

    void updateInfoBar();

private:
    const int WIDTH;
    const int HEIGHT;
    const int NUM_CELLS;
    const float ZOOM_FACTOR;
    const int HORIZONTAL_VIEW_MOVEMENT;
    const int VERTICAL_VIEW_MOVEMENT;
    const sf::Time UPDATE_RATE_INCREMENT;
    const sf::Time UPDATE_RATE_DECREMENT;

    sf::RenderWindow m_Window;
    sf::View m_View;

    sf::Clock m_Clock;
    sf::Time m_UpdateRate;
    sf::Time m_LastUpdateTime;

    Grid m_Grid;

    InfoBar m_InfoBar;
};

#endif
