#include "Food.h"

Food::Food(float windowWidth, float windowHeight, float gridSize)
    : windowWidth(windowWidth), windowHeight(windowHeight), gridSize(gridSize) {
    shape.setRadius(gridSize / 2 - 2.f);
    shape.setFillColor(sf::Color::Red);
    respawn();
}

void Food::update(float deltaTime) {
}

void Food::respawn() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, static_cast<int>(windowWidth / gridSize) - 1);
    std::uniform_int_distribution<> disY(0, static_cast<int>(windowHeight / gridSize) - 1);

    float x = disX(gen) * gridSize;
    float y = disY(gen) * gridSize;
    shape.setPosition(x, y);
}

sf::FloatRect Food::getBounds() const {
    return shape.getGlobalBounds();
}

void Food::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
}
