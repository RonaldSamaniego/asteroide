#include "Score.h"

Score::Score() : points(0) {
    if (!font.loadFromFile("fonts/arial.ttf")) {
        
    }
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);
}

void Score::addPoints(int points) {
    this->points += points;
    text.setString("Score: " + std::to_string(this->points));
}

int Score::getPoints() const {
    return points;
}

void Score::draw(sf::RenderWindow& window) {
    window.draw(text);
}
