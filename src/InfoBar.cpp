#include "InfoBar.hpp"

#include <iostream>

InfoBar::InfoBar(const sf::Vector2f& position, const sf::Vector2f& size)
{
    std::printf("Size=(%f,%f)\n", size.x, size.y);

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
    m_UpdateRateText.setPosition(position.x + m_GenerationText.getLocalBounds().width * 2.f, position.y);

    m_UpArrowTexture.loadFromFile("res/upArrow.png");

    m_IncUpdateRate.setTexture(m_UpArrowTexture);
    m_DecUpdateRate.setTexture(m_UpArrowTexture);

    m_IncUpdateRate.setPosition(position.x + size.x - m_UpArrowTexture.getSize().x * 2, position.y);
    m_DecUpdateRate.setPosition(position.x + size.x - m_UpArrowTexture.getSize().x, position.y);

    m_DecUpdateRate.setTextureRect(sf::IntRect(0, m_UpArrowTexture.getSize().y, m_UpArrowTexture.getSize().x,
                                               -m_UpArrowTexture.getSize().y));
}

void InfoBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(m_Background);
    target.draw(m_GenerationText);
    target.draw(m_UpdateRateText);
    target.draw(m_IncUpdateRate);
    target.draw(m_DecUpdateRate);
}

void InfoBar::setGenerationNumber(int generation)
{
    m_GenerationText.setString("Generation: " + std::to_string(generation));
}

void InfoBar::setUpdateRate(const sf::Time& rate)
{
    m_UpdateRateText.setString("Update rate: " + std::to_string(rate.asMilliseconds()));
}
