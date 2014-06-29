#include "Grid.hpp"

Grid::Grid(int width, int height, int numCells)
    : WIDTH(width)
    , HEIGHT(height)
    , NUM_CELLS(numCells)
    , m_Cells(NUM_CELLS, std::vector<int>(NUM_CELLS, 0))
    , m_CellShapes(NUM_CELLS, std::vector<sf::RectangleShape>(NUM_CELLS))
{
    createCellShapes();
    createLineShapes();
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    drawCells(target, states);
    drawLines(target, states);
}

void Grid::drawCells(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (int x = 0; x < NUM_CELLS; ++x)
    {
        for (int y = 0; y < NUM_CELLS; ++y)
        {
            target.draw(m_CellShapes[x][y]);
        }
    }
}

void Grid::drawLines(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& line : m_LineShapes)
    {
        target.draw(line);
    }
}

void Grid::createCellShapes()
{
    for (int x = 0; x < NUM_CELLS; ++x)
    {
        for (int y = 0; y < NUM_CELLS; ++y)
        {
            auto width = WIDTH / NUM_CELLS;
            auto height = HEIGHT / NUM_CELLS;

            m_CellShapes[x][y].setSize({ width, height });
            m_CellShapes[x][y].setPosition(x * width, y * height);
            m_CellShapes[x][y].setFillColor(sf::Color::White);
        }
    }
}

void Grid::createLineShapes()
{
    sf::RectangleShape line;
    line.setFillColor(sf::Color(128, 128, 128));

    for (int i = 1; i < NUM_CELLS; ++i)
    {
        // Vertical
        line.setPosition(i * (WIDTH / NUM_CELLS), 0);
        line.setSize({ 1.f, HEIGHT });
        m_LineShapes.push_back(line);

        // Horizontal
        line.setPosition(0, i * (HEIGHT / NUM_CELLS));
        line.setSize({ WIDTH, 1.f });
        m_LineShapes.push_back(line);
    }
}
