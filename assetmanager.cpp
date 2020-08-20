#include <iostream>
#include <assert.h>
#include "assetmanager.h"
#include "SFML/Graphics/Texture.hpp"

AssetManager * AssetManager::m_assetManagerInstance = nullptr;

AssetManager::AssetManager()
{
    assert(m_assetManagerInstance == nullptr);
    m_assetManagerInstance = this;
}

// -------------------------------------------------------
// Loads texture if it is not in the map yet and return it
// -------------------------------------------------------
sf::Texture &AssetManager::getTexture(std::string fileName)
{
    if (!m_assetManagerInstance->loadedTextures.empty()) { // if we already have some textures in map

        auto& textures = m_assetManagerInstance->loadedTextures;    // just for convenient

        auto pairInfo = textures.find(fileName);                    // try to find whether this texture is in the map

        if (pairInfo != textures.end()) {                           // if found
            return pairInfo->second;                                // then return the texture
        }
    }

    sf::Texture tempTexture;
    if (tempTexture.loadFromFile(fileName)) {                                                       // if loaded succesfully
        auto inserted = m_assetManagerInstance->loadedTextures.insert({fileName, tempTexture});     // try to insert
        return inserted.first->second;
    } else {                                                                                        // if loading failed
        // by default the message will be outed. Do some custom work.
    }
}
