#include "Application.hpp"

#include <iostream>

Application::Application(int width, int height, int numCells, const sf::Time& updateRate)
    : WIDTH(width)
    , HEIGHT(height)
    , NUM_CELLS(numCells)
    , UPDATE_RATE(updateRate)
    , m_Window(sf::VideoMode(WIDTH, HEIGHT), "Game Of Life", sf::Style::Close)
    , m_Grid(WIDTH, HEIGHT, NUM_CELLS)
{

}

void Application::run()
{
    while (m_Window.isOpen())
    {
        handleInput();
        update();
        draw();
    }
}

void Application::handleInput()
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                m_Window.close();
                break;
            case sf::Event::MouseButtonPressed:
                handleMousePress(event);
                break;
            default:
                break;
        }
    }
}

void Application::update()
{
    auto currentTime = m_Clock.getElapsedTime();
    if (currentTime - m_LastUpdateTime < UPDATE_RATE)
        return;

    // ...update...
    m_LastUpdateTime = currentTime;
}

void Application::draw()
{
    m_Window.clear(sf::Color::White);
    m_Window.draw(m_Grid);
    m_Window.display();
}

void Application::handleMousePress(const sf::Event& event)
{
    int cellX = event.mouseButton.x / (WIDTH / NUM_CELLS);
    int cellY = event.mouseButton.y / (HEIGHT / NUM_CELLS);

    if (event.mouseButton.button == sf::Mouse::Left)
    {
        m_Grid.toggleState(cellX, cellY);
    }
}
