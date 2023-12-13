#include "DirectoryVisual.h"

DirectoryVisual::DirectoryVisual(Tree<Folder*>* tree, const sf::Vector2f& position){
    if (!texture.loadFromFile("./folder.png")) {
    }

    sprite.setTexture(texture);
    sprite.setPosition(position);

    if (!font.loadFromFile("./arial.ttf")) {
    }   

    text.setFont(font);
    text.setString(tree->data->getName());
    text.setCharacterSize(24);

    text.setFillColor(sf::Color::Black);
    text.setPosition(position.x + sprite.getLocalBounds().width, position.y);
}

void DirectoryVisual::draw(sf::RenderWindow& window) {
    window.clear(sf::Color::White);
    sprite.setScale(0.5f, 0.5f);
    window.draw(sprite);
    window.draw(text);
}

