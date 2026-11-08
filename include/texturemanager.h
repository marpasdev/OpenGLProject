
/**
 * @file texturemanager.h
 *
 * @brief Declaration of the TextureManager class.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <unordered_map>
#include <string>
#include <memory>
#include "texture.h"

class TextureManager {
    std::unordered_map<std::string, std::shared_ptr<Texture>> textures;

public:

    void add(const std::string& name, const std::string& path);

    std::shared_ptr<Texture> get(const std::string& name) const;

};

#endif // TEXTUREMANAGER_H