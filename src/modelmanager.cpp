/**
 * @file modelmanager.cpp
 *
 * @brief Manages models - stores them and makes it easier to add them together with a vertex layout.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#include "modelmanager.h"

ModelManager::ModelManager() {
	std::vector<VertexAttribute> posNor;
	posNor.push_back({3, GL_FLOAT});
	posNor.push_back({3, GL_FLOAT});

	std::vector<VertexAttribute> posNorCol;
	posNorCol.push_back({3, GL_FLOAT});
	posNorCol.push_back({3, GL_FLOAT});
	posNorCol.push_back({3, GL_FLOAT});

    layoutPresets[VertexLayoutPreset::PosNor] = posNor;
    layoutPresets[VertexLayoutPreset::PosNorCol] = posNorCol;
}

void ModelManager::add(const std::string& name, const float* vertexData, size_t vertexDataSize, VertexLayoutPreset layout) {
    models[name] = std::make_shared<Model>(vertexData, vertexDataSize, layoutPresets.at(layout));
}

void ModelManager::add(const std::string& name, const float* vertexData, size_t vertexDataSize, const std::vector<VertexAttribute>& layout) {
    models[name] = std::make_shared<Model>(vertexData, vertexDataSize, layout);
}

std::shared_ptr<Model> ModelManager::get(const std::string& name) const {
    return models.at(name);
}