#include "Grid.hpp"

#include <map>
#include <iostream>

Grid::Grid(int width, int height, int numCells)
    : WIDTH(width)
    , HEIGHT(height)
    , NUM_CELLS(numCells)
    , ALIVE_COLOR(sf::Color::Black)
    , DEAD_COLOR(sf::Color::White)
    , m_Cells(NUM_CELLS, std::vector<int>(NUM_CELLS, 0))
    , m_CellShapes(NUM_CELLS, std::vector<sf::RectangleShape>(NUM_CELLS))
    , m_IsPlaying(false)
    , m_NumGenerations(0)
{
    createCellShapes();
    createLineShapes();
}

void Grid::update()
{
    if (!m_IsPlaying)
        return;

    std::map<std::pair<int,int>, int> stateChanges;

    for (int x = 0; x < NUM_CELLS; ++x)
    {
        for (int y = 0; y < NUM_CELLS; ++y)
        {
            auto numLiveNeighbors = getNumLiveNeighbors(x, y);

            if (m_Cells[x][y] == 1)
            {
                if ((numLiveNeighbors < 2) || (numLiveNeighbors > 3))
                    stateChanges[std::make_pair(x, y)] = 0;
            }
            else
            {
                if (numLiveNeighbors == 3)
                    stateChanges[std::make_pair(x, y)] = 1;
            }
        }
    }

    for (auto& pair : stateChanges)
    {
        auto x = pair.first.first;
        auto y = pair.first.second;

        setCellState(x, y, pair.second);
    }

    ++m_NumGenerations;
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    drawCells(target, states);
    drawLines(target, states);
}

void Grid::toggleState(int x, int y)
{
    setCellState(x, y, (m_Cells[x][y] == 0 ? 1 : 0));
}

void Grid::setCellState(int x, int y, int state)
{
    m_Cells[x][y] = state;
    m_CellShapes[x][y].setFillColor(state == 0 ? DEAD_COLOR : ALIVE_COLOR);
}

void Grid::reset()
{
    m_Cells = std::vector<std::vector<int>>(NUM_CELLS, std::vector<int>(NUM_CELLS, 0));
    m_CellShapes = std::vector<std::vector<sf::RectangleShape>>(NUM_CELLS, std::vector<sf::RectangleShape>(NUM_CELLS));
    m_IsPlaying = false;
    m_NumGenerations = 0;

    createCellShapes();
}

void Grid::togglePlayState()
{
    m_IsPlaying = !m_IsPlaying;
}

bool Grid::isPlaying() const
{
    return m_IsPlaying;
}

int Grid::getNumGenerations() const
{
    return m_NumGenerations;
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
            m_CellShapes[x][y].setFillColor(DEAD_COLOR);
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

int Grid::getNumLiveNeighbors(int x, int y) const
{
    int numLiveNeighbors = 0;

    // Copy of cells with padding so that we don't have to check
    // if the cell is on one of the edges, just check (x-1,y-1) to (x+1,y+1),
    // not counting (x,y)
    std::vector<std::vector<int>> cells(NUM_CELLS + 2, std::vector<int>(NUM_CELLS + 2, 0));
    for (int i = 0; i < NUM_CELLS; ++i)
    {
        for (int j = 0; j < NUM_CELLS; ++j)
        {
            cells[i+1][j+1] = m_Cells[i][j];
        }
    }

    int offsetX = x + 1;
    int offsetY = y + 1;

    if (cells[offsetX][offsetY-1] == 1) ++numLiveNeighbors;        // North
    if (cells[offsetX+1][offsetY-1] == 1) ++numLiveNeighbors;      // North East
    if (cells[offsetX+1][offsetY] == 1) ++numLiveNeighbors;        // East
    if (cells[offsetX+1][offsetY+1] == 1) ++numLiveNeighbors;      // South East
    if (cells[offsetX][offsetY+1] == 1) ++numLiveNeighbors;        // South
    if (cells[offsetX-1][offsetY+1] == 1) ++numLiveNeighbors;      // South West
    if (cells[offsetX-1][offsetY] == 1) ++numLiveNeighbors;        // West
    if (cells[offsetX-1][offsetY-1] == 1) ++numLiveNeighbors;      // North West

    return numLiveNeighbors;
}
