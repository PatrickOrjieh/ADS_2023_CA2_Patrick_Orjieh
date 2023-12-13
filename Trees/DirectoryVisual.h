#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Tree.h"
#include "Folder.h"
class DirectoryVisual {
public:
    DirectoryVisual(Tree<Folder*>* tree, const sf::Vector2f& position);

    void draw(sf::RenderWindow& window);

private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Text text;
    sf::Font font;
};