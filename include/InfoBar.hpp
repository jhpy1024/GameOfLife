#ifndef INFO_BAR_HPP
#define INFO_BAR_HPP

#include <SFML/Graphics.hpp>

class InfoBar : public sf::Drawable, public sf::Transformable
{
public:
    InfoBar(const sf::Vector2f& position, const sf::Vector2f& size);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void handleMousePress(const sf::Event& event);

    void setGenerationNumber(int generation);
    void setUpdateRate(const sf::Time& rate);

    bool increaseRateClicked();
    bool decreaseRateClicked();

private:
    sf::Font m_Font;

    sf::Text m_GenerationText;
    sf::Text m_UpdateRateText;

    sf::RectangleShape m_Background;

    sf::Texture m_UpArrowTexture;
    sf::Sprite m_IncUpdateRate;
    sf::Sprite m_DecUpdateRate;

    bool m_IncreaseRateClicked;
    bool m_DecreaseRateClicked;
};

#endif
