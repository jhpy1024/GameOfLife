#include "Application.hpp"

#include <iostream>

Application::Application(int width, int height, int numCells, const sf::Time& updateRate)
    : WIDTH(width)
    , HEIGHT(height)
    , NUM_CELLS(numCells)
    , UPDATE_RATE(updateRate)
    , m_Window(sf::VideoMode(WIDTH, HEIGHT), "Game Of Life", sf::Style::Close)
    , m_View(sf::FloatRect(0, 0, WIDTH, HEIGHT))
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
            case sf::Event::KeyPressed:
                handleKeyPress(event);
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

    m_Grid.update();
    m_LastUpdateTime = currentTime;
}

void Application::draw()
{
    m_Window.clear(sf::Color::White);
    m_Window.setView(m_View);
    m_Window.draw(m_Grid);
    m_Window.display();
}

void Application::handleMousePress(const sf::Event& event)
{
    auto mousePos = m_Window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
    auto cellX = mousePos.x / (WIDTH / NUM_CELLS);
    auto cellY = mousePos.y / (HEIGHT / NUM_CELLS);

    if (event.mouseButton.button == sf::Mouse::Left && !m_Grid.isPlaying())
    {
        m_Grid.toggleState(cellX, cellY);
    }
}

void Application::handleKeyPress(const sf::Event& event)
{
    if (event.key.code == sf::Keyboard::Space)
        m_Grid.togglePlayState();
    else if (event.key.code == sf::Keyboard::Escape)
        m_Grid.reset();
    else if (event.key.code == sf::Keyboard::I)
        m_View.zoom(0.9f);
    else if (event.key.code == sf::Keyboard::R)
        m_View = m_Window.getDefaultView();
    else if (event.key.code == sf::Keyboard::Left)
        m_View.move(-(WIDTH / NUM_CELLS), 0.f);
    else if (event.key.code == sf::Keyboard::Right)
        m_View.move(WIDTH / NUM_CELLS, 0.f);
    else if (event.key.code == sf::Keyboard::Up)
        m_View.move(0.f, -(HEIGHT / NUM_CELLS));
    else if (event.key.code == sf::Keyboard::Down)
        m_View.move(0.f, HEIGHT / NUM_CELLS);
}
