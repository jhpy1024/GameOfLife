#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Grid : public sf::Drawable
{
public:
    Grid(int width, int height, int numCells);

    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void toggleState(int x, int y);
    void setCellState(int x, int y, int state);

    void reset();
    void togglePlayState();

    bool isPlaying() const;

    int getNumGenerations() const;

private:
    void drawCells(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawLines(sf::RenderTarget& target, sf::RenderStates states) const;

    void createCellShapes();
    void createLineShapes();

    int getNumLiveNeighbors(int x, int y) const;

private:
    const int WIDTH;
    const int HEIGHT;
    const int NUM_CELLS;

    const sf::Color ALIVE_COLOR;
    const sf::Color DEAD_COLOR;

    std::vector<std::vector<int>> m_Cells;

    std::vector<std::vector<sf::RectangleShape>> m_CellShapes;
    std::vector<sf::RectangleShape> m_LineShapes;

    bool m_IsPlaying;

    int m_NumGenerations;
};

#endif
