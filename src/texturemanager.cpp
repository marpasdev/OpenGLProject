/**
 * @file texturemanager.cpp
 *
 * @brief 
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#include "texturemanager.h"

void TextureManager::add(const std::string& name, const std::string& path) {
    textures[name] = std::make_shared<Texture>("assets/textures/" + path);
}

std::shared_ptr<Texture> TextureManager::get(const std::string& name) const {
    return textures.at(name);
}