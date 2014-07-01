#include "InfoBar.hpp"

#include <iostream>

InfoBar::InfoBar(const sf::Vector2f& position, const sf::Vector2f& size)
{
    setPosition(position);

    m_Background.setSize(size);
    m_Background.setFillColor(sf::Color(32, 32, 32));
    m_Background.setPosition(position);

    m_Font.loadFromFile("res/Ubuntu-M.ttf");

    sf::Text baseText;
    baseText.setFont(m_Font);
    baseText.setCharacterSize(16);
    baseText.setColor(sf::Color::White);

    m_GenerationText = baseText;
    m_UpdateRateText = baseText;

    setGenerationNumber(42);
    setUpdateRate(sf::seconds(2));

    m_GenerationText.setPosition(position);
    m_UpdateRateText.setPosition(position.x, position.y + m_GenerationText.getLocalBounds().height * 2.f);
}

void InfoBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(m_Background);
    target.draw(m_GenerationText);
    target.draw(m_UpdateRateText);
}

void InfoBar::setGenerationNumber(int generation)
{
    m_GenerationText.setString("Generation: " + std::to_string(generation));
}

void InfoBar::setUpdateRate(const sf::Time& rate)
{
    m_UpdateRateText.setString("Update rate: " + std::to_string(rate.asMilliseconds()));
}
