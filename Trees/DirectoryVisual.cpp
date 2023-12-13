#include "DirectoryVisual.h"

DirectoryVisual::DirectoryVisual(const std::string& name, const sf::Vector2f& position) {
    if (!texture.loadFromFile("./folder.png")) {
    }

    sprite.setTexture(texture);
    sprite.setPosition(position);

    if (!font.loadFromFile("./arial.ttf")) {
    }

    text.setFont(font);
    text.setString(name);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(position.x + sprite.getLocalBounds().width + 5, position.y);
}

void DirectoryVisual::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(text);
}
