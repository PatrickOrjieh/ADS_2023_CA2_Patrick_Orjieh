#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class DirectoryVisual {
public:
    DirectoryVisual(const std::string& name, const sf::Vector2f& position);

    void draw(sf::RenderWindow& window);

private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Text text;
    sf::Font font;
};