#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Grid : public sf::Drawable
{
public:
    Grid(int width, int height, int numCells);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    void drawCells(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawLines(sf::RenderTarget& target, sf::RenderStates states) const;

    void createCellShapes();
    void createLineShapes();

private:
    const int WIDTH;
    const int HEIGHT;
    const int NUM_CELLS;

    std::vector<std::vector<int>> m_Cells;

    std::vector<std::vector<sf::RectangleShape>> m_CellShapes;
    std::vector<sf::RectangleShape> m_LineShapes;
};

#endif
