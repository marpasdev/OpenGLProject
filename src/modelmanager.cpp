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

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stdexcept>

ModelManager::ModelManager() {
	std::vector<VertexAttribute> posNor;
	posNor.push_back({3, GL_FLOAT});
	posNor.push_back({3, GL_FLOAT});
    layoutPresets[VertexLayoutPreset::PosNor] = posNor;

	std::vector<VertexAttribute> posNorCol;
	posNorCol.push_back({3, GL_FLOAT});
	posNorCol.push_back({3, GL_FLOAT});
	posNorCol.push_back({3, GL_FLOAT});
    layoutPresets[VertexLayoutPreset::PosNorCol] = posNorCol;

	std::vector<VertexAttribute> posNorUV;
	posNorUV.push_back({3, GL_FLOAT});
	posNorUV.push_back({3, GL_FLOAT});
	posNorUV.push_back({2, GL_FLOAT});
	layoutPresets[VertexLayoutPreset::PosNorUV] = posNorUV;
}

void ModelManager::add(const std::string& name, const float* vertexData, size_t vertexDataSize, VertexLayoutPreset layout) {
    models[name] = std::make_shared<Model>(vertexData, vertexDataSize, layoutPresets.at(layout));
}

void ModelManager::add(const std::string& name, const float* vertexData, size_t vertexDataSize, const std::vector<VertexAttribute>& layout) {
    models[name] = std::make_shared<Model>(vertexData, vertexDataSize, layout);
}

void ModelManager::add(const std::string& name, const std::string path) {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile("assets/models/" + path, 
		aiProcess_Triangulate | aiProcess_GenNormals
		);

	if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode) {
		throw std::runtime_error(importer.GetErrorString());
	}

	std::vector<float> data;

	for (size_t m = 0; m < scene->mNumMeshes; ++m) {
		const aiMesh* mesh = scene->mMeshes[m];
		data.reserve(data.size() + mesh->mNumFaces * 3 * 8);

		for (size_t f = 0; f < mesh->mNumFaces; ++f) {
			const aiFace& face = mesh->mFaces[f];

			for (size_t i = 0; i < 3; ++i) {
				size_t idx = face.mIndices[i];

				const aiVector3D& pos = mesh->mVertices[idx];
				data.insert(data.end(), { pos.x, pos.y, pos.z });

				const aiVector3D& nor = mesh->mNormals[idx];
				data.insert(data.end(), { nor.x, nor.y, nor.z });

				if (mesh->HasTextureCoords(0)) {
					const aiVector3D& uv = mesh->mTextureCoords[0][idx];
					data.insert(data.end(), { uv.x, uv.y });
				} else {
					data.insert(data.end(), { 0.0f, 0.0f });
				}
			}
		}
	}

	add(name, data.data(), data.size() * sizeof(float), VertexLayoutPreset::PosNorUV);
}

std::shared_ptr<Model> ModelManager::get(const std::string& name) const {
    return models.at(name);
}