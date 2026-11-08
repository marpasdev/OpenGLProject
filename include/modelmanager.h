/**
 * @file modelmanager.h
 *
 * @brief Declaration of the ModelManager class, which manages models - stores them and makes it easier to add them together with a vertex layout.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

#include "model.h"

enum class VertexLayoutPreset {
    PosNor,
    PosNorCol,
    PosNorUV,
    PosNorUVW
};

class ModelManager {
    std::unordered_map<std::string, std::shared_ptr<Model>> models;
    std::unordered_map<VertexLayoutPreset, std::vector<VertexAttribute>> layoutPresets;

public:

    ModelManager();

    void add(const std::string& name, const float* vertexData, size_t vertexDataSize, VertexLayoutPreset layout = VertexLayoutPreset::PosNor);
    
    void add(const std::string& name, const float* vertexData, size_t vertexDataSize, const std::vector<VertexAttribute>& layout);

    void add(const std::string& name, const std::string path, VertexLayoutPreset layout = VertexLayoutPreset::PosNorUV);

    std::shared_ptr<Model> get(const std::string& name) const;
};

#endif // MODELMANAGER_H