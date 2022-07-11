#include "text.hpp"

#include <iostream>


void Text::loadFont (const std::string &path) {
    sf::Font font;
    if (!font.loadFromFile(path)) {
        std::cerr << "Could not load " << path << " from file. File does not exist." << std::endl;
    }
    _font = font;
}

Text::Text (const std::string &path) {
    loadFont(path);
    _text.setFont(_font);
    _text.setCharacterSize(18);
    _text.setFillColor(sf::Color::White);
    _text.setStyle(sf::Text::Regular);

    _text.setPosition(3.0f, 3.0f);
}

void Text::setTextFromFloat (float num) {
    _text.setString(std::to_string(num).substr(0, 6));
}

sf::Text Text::getText (void) const {
    return _text;
}

