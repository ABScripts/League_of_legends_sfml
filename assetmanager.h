#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>

namespace sf {
    class Texture;
}

class AssetManager
{
public:
    AssetManager();
    void operator=(const AssetManager &other) = delete; // deprecate default assignment operator
    AssetManager(const AssetManager &other) = delete;   // deprecate copy constructor

    static sf::Texture & getTexture(std::string fileName);
protected:
    std::map<std::string, sf::Texture> loadedTextures;      // contains all the textures loaded
private:
    static AssetManager *m_assetManagerInstance;
};

#endif // ASSETMANAGER_H
