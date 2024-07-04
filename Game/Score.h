#pragma once
#define SCORE_H

#include <SFML/Graphics.hpp>

class Score {
public:
    Score();
    void addPoints(int points);
    int getPoints() const;
    void draw(sf::RenderWindow& window);

private:
    int points;
    sf::Font font;
    sf::Text text;
};


