// Tiles.cpp
#include "Tiles.h"

// Constructeur par défaut
Tiles::Tiles()
    : m_tileSize(16, 16), m_margin(1) {
    // Initialisation si nécessaire
}

// Constructeur paramétré
Tiles::Tiles(const std::string& tileset, const sf::Vector2u& tileSize,
           const std::vector<int>& tiles, unsigned int width, unsigned int height,
           unsigned int margin)
    : m_tileSize(tileSize), m_margin(margin) {
    load(tileset, tileSize, tiles, width, height, margin);
}

// Méthode de chargement
bool Tiles::load(const std::string& tileset, const sf::Vector2u& tileSize,
               const std::vector<int>& tiles, unsigned int width, unsigned int height,
               unsigned int margin) {
    m_tileSize = tileSize;
    m_margin = margin;

    if (!m_tileset.loadFromFile(tileset)) {
        std::cerr << "Erreur lors du chargement du tileset: " << tileset << std::endl;
        return false;
    }

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {
            if (i + j * width >= tiles.size()) continue; // Sécurité

            int tileNumber = tiles[i + j * width];

            int tu = tileNumber % (m_tileset.getSize().x / (m_tileSize.x + m_margin));
            int tv = tileNumber / (m_tileset.getSize().x / (m_tileSize.x + m_margin));

            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // Définir la position des sommets du quad
            quad[0].position = sf::Vector2f(i * m_tileSize.x, j * m_tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * m_tileSize.x, j * m_tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * m_tileSize.x, (j + 1) * m_tileSize.y);
            quad[3].position = sf::Vector2f(i * m_tileSize.x, (j + 1) * m_tileSize.y);

            // Calculer les coordonnées de texture avec marge
            float left = m_margin + tu * (m_tileSize.x + m_margin);
            float top = m_margin + tv * (m_tileSize.y + m_margin);

            quad[0].texCoords = sf::Vector2f(left, top);
            quad[1].texCoords = sf::Vector2f(left + m_tileSize.x, top);
            quad[2].texCoords = sf::Vector2f(left + m_tileSize.x, top + m_tileSize.y);
            quad[3].texCoords = sf::Vector2f(left, top + m_tileSize.y);
        }
    }

    return true;
}

// Méthode pour mettre à jour les tuiles visibles
void Tiles::updateTiles(const std::vector<int>& tiles, unsigned int width, unsigned int height) {
    // Vérifier si la taille a changé
    if (width * height * 4 != m_vertices.getVertexCount()) {
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);
    }

    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {
            if (i + j * width >= tiles.size()) continue; // Sécurité

            int tileNumber = tiles[i + j * width];

            int tu = tileNumber % (m_tileset.getSize().x / (m_tileSize.x + m_margin));
            int tv = tileNumber / (m_tileset.getSize().x / (m_tileSize.x + m_margin));

            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // Définir la position des sommets du quad
            quad[0].position = sf::Vector2f(i * m_tileSize.x, j * m_tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * m_tileSize.x, j * m_tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * m_tileSize.x, (j + 1) * m_tileSize.y);
            quad[3].position = sf::Vector2f(i * m_tileSize.x, (j + 1) * m_tileSize.y);

            // Calculer les coordonnées de texture avec marge
            float left = m_margin + tu * (m_tileSize.x + m_margin);
            float top = m_margin + tv * (m_tileSize.y + m_margin);

            quad[0].texCoords = sf::Vector2f(left, top);
            quad[1].texCoords = sf::Vector2f(left + m_tileSize.x, top);
            quad[2].texCoords = sf::Vector2f(left + m_tileSize.x, top + m_tileSize.y);
            quad[3].texCoords = sf::Vector2f(left, top + m_tileSize.y);
        }
    }
}

// Méthode de dessin
void Tiles::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Appliquer la transformation
    states.transform *= getTransform();

    // Appliquer la texture du tileset
    states.texture = &m_tileset;

    // Dessiner le tableau de vertex
    target.draw(m_vertices, states);
}
