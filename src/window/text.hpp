#ifndef FONT_HPP
#define FONT_HPP

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include <string>

class Text {
        sf::Text _text;
        sf::Font _font;

        void loadFont (const std::string &path);

    public:
        Text (const std::string &path);

        void setTextFromFloat (float num);

        sf::Text getText (void) const;

};

#endif  // FONT_HPP
