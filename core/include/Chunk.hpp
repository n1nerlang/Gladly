#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <vector>
#include <cstdint>
#include "Block.hpp"

// 16x16x128 dimensions are standard for the engine
const int CHUNK_WIDTH = 16;
const int CHUNK_HEIGHT = 128;
const int CHUNK_VOLUME = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT;

struct Vertex {
    float x, y, z;
    float u, v; // Texture coordinates
};

class Chunk {
private:
    BlockID blocks[CHUNK_VOLUME];
    std::vector<Vertex> meshVertices;

    // Helper to convert 3D coordinates to flat 1D array index
    inline int getIndex(int x, int y, int z) const {
        return x + (z * CHUNK_WIDTH) + (y * CHUNK_WIDTH * CHUNK_WIDTH);
    }

public:
    Chunk();
    void generateTerrain();
    void generateMesh();
    bool isBlockTransparent(int x, int y, int z) const;
    
    const std::vector<Vertex>& getMesh() const { return meshVertices; }
};

#endif
