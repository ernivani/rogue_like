// Tiles.h
#ifndef TILES_H
#define TILES_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class Tiles : public sf::Drawable, public sf::Transformable {
public:
    Tiles();
    Tiles(const std::string& tileset, const sf::Vector2u& tileSize,
          const std::vector<int>& tiles, unsigned int width, unsigned int height,
          unsigned int margin = 1);
    
    bool load(const std::string& tileset, const sf::Vector2u& tileSize,
              const std::vector<int>& tiles, unsigned int width, unsigned int height,
              unsigned int margin = 1);
    
    // Méthode pour mettre à jour les tuiles visibles
    void updateTiles(const std::vector<int>& tiles, unsigned int width, unsigned int height);
    
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    sf::Vector2u m_tileSize;
    unsigned int m_margin;
};

#endif // TILES_H
