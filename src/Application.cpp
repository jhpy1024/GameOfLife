#include "Application.hpp"

#include <iostream>

Application::Application(int width, int height, int numCells, const sf::Time& updateRate)
    : WIDTH(width)
    , HEIGHT(height)
    , NUM_CELLS(numCells)
    , ZOOM_FACTOR(0.9f)
    , HORIZONTAL_VIEW_MOVEMENT(WIDTH / NUM_CELLS)
    , VERTICAL_VIEW_MOVEMENT(HEIGHT / NUM_CELLS)
    , UPDATE_RATE_INCREMENT(sf::milliseconds(10))
    , UPDATE_RATE_DECREMENT(sf::milliseconds(10))
    , m_Window(sf::VideoMode(WIDTH, HEIGHT), "Game Of Life", sf::Style::Close)
    , m_View(sf::FloatRect(0, 0, WIDTH, WIDTH))
    , m_UpdateRate(updateRate)
    , m_Grid(WIDTH, WIDTH, NUM_CELLS) // width == height to ensure cells are square
    , m_InfoBar({ 0.f, WIDTH + (WIDTH / NUM_CELLS) }, { WIDTH, HEIGHT - (WIDTH + WIDTH / NUM_CELLS) })
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

    handleInfoBarInput();
}

void Application::update()
{
    updateInfoBar();

    auto currentTime = m_Clock.getElapsedTime();
    if (currentTime - m_LastUpdateTime < m_UpdateRate)
        return;

    m_Grid.update();

    m_LastUpdateTime = currentTime;
}

void Application::draw()
{
    m_Window.clear(sf::Color::White);

    drawGrid();
    drawInfoBar();

    m_Window.display();
}

void Application::drawGrid()
{
    m_Window.setView(m_View);
    m_Window.draw(m_Grid);
}

void Application::drawInfoBar()
{
    m_Window.setView(m_Window.getDefaultView());
    m_Window.draw(m_InfoBar);
}

void Application::handleMousePress(const sf::Event& event)
{
    m_InfoBar.handleMousePress(event);

    auto mousePos = m_Window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }, m_View);

    auto cellX = mousePos.x / (WIDTH / NUM_CELLS);
    auto cellY = mousePos.y / (WIDTH / NUM_CELLS);

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
        m_View.zoom(ZOOM_FACTOR);
    else if (event.key.code == sf::Keyboard::R)
        m_View = sf::View(sf::FloatRect(0.f, 0.f, WIDTH, WIDTH));
    else if (event.key.code == sf::Keyboard::Left)
        m_View.move(-HORIZONTAL_VIEW_MOVEMENT, 0.f);
    else if (event.key.code == sf::Keyboard::Right)
        m_View.move(HORIZONTAL_VIEW_MOVEMENT, 0.f);
    else if (event.key.code == sf::Keyboard::Up)
        m_View.move(0.f, -VERTICAL_VIEW_MOVEMENT);
    else if (event.key.code == sf::Keyboard::Down)
        m_View.move(0.f, VERTICAL_VIEW_MOVEMENT);
}

void Application::handleInfoBarInput()
{
    if (m_InfoBar.increaseRateClicked())
        m_UpdateRate += UPDATE_RATE_INCREMENT;
    else if (m_InfoBar.decreaseRateClicked() && m_UpdateRate > sf::milliseconds(0))
        m_UpdateRate -= UPDATE_RATE_DECREMENT;
}

void Application::updateInfoBar()
{
    m_InfoBar.setGenerationNumber(m_Grid.getNumGenerations());
    m_InfoBar.setUpdateRate(m_UpdateRate);
}
