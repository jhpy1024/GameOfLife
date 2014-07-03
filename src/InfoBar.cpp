#include "InfoBar.hpp"

#include <iostream>

InfoBar::InfoBar(const sf::Vector2f& position, const sf::Vector2f& size)
    : SIZE(size)
    , m_IncreaseRateClicked(false)
    , m_DecreaseRateClicked(false)
{
    setPosition(position);

    createBackground();
    createText();
    createSprites();
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

void InfoBar::handleMousePress(const sf::Event& event)
{
    sf::FloatRect mouseRect(event.mouseButton.x, event.mouseButton.y, 1.f, 1.f);

    if (event.mouseButton.button == sf::Mouse::Left)
    {
        if (mouseRect.intersects(m_IncUpdateRate.getGlobalBounds()))
            m_IncreaseRateClicked = true;
        else if (mouseRect.intersects(m_DecUpdateRate.getGlobalBounds()))
            m_DecreaseRateClicked = true;
    }
}

void InfoBar::setGenerationNumber(int generation)
{
    m_GenerationText.setString("Generation: " + std::to_string(generation));
}

void InfoBar::setUpdateRate(const sf::Time& rate)
{
    m_UpdateRateText.setString("Update rate: " + std::to_string(rate.asMilliseconds()) + "ms");
}

bool InfoBar::increaseRateClicked()
{
    if (m_IncreaseRateClicked)
    {
        // Click has been handled so set to false
        m_IncreaseRateClicked = false;
        return true;
    }

    return false;
}

bool InfoBar::decreaseRateClicked()
{
    if (m_DecreaseRateClicked)
    {
        // Click has been handled so set to false
        m_DecreaseRateClicked = false;
        return true;
    }

    return false;
}

void InfoBar::createBackground()
{
    m_Background.setSize(SIZE);
    m_Background.setFillColor(sf::Color(32, 32, 32));
    m_Background.setPosition(getPosition());
}

void InfoBar::createText()
{
    m_Font.loadFromFile("res/Ubuntu-M.ttf");

    sf::Text baseText;
    baseText.setFont(m_Font);
    baseText.setCharacterSize(16);
    baseText.setColor(sf::Color::White);

    m_GenerationText = baseText;
    m_UpdateRateText = baseText;

    // Should probably be constants
    setGenerationNumber(0);
    setUpdateRate(sf::milliseconds(10));

    m_GenerationText.setPosition(getPosition());
    m_UpdateRateText.setPosition(getPosition().x + m_GenerationText.getLocalBounds().width * 2.f, getPosition().y);
}

void InfoBar::createSprites()
{
    m_UpArrowTexture.loadFromFile("res/upArrow.png");

    m_IncUpdateRate.setTexture(m_UpArrowTexture);
    m_DecUpdateRate.setTexture(m_UpArrowTexture);

    m_IncUpdateRate.setPosition(getPosition().x + SIZE.x - m_UpArrowTexture.getSize().x * 2, getPosition().y);
    m_DecUpdateRate.setPosition(getPosition().x + SIZE.x - m_UpArrowTexture.getSize().x, getPosition().y);

    m_DecUpdateRate.setTextureRect(sf::IntRect(0, m_UpArrowTexture.getSize().y, m_UpArrowTexture.getSize().x,
                                               -m_UpArrowTexture.getSize().y));
}
