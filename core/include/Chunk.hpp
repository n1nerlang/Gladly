#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <vector>
#include <cstdint>

// 16x16x16 dimensions are ideal for mobile cache alignment
const int CHUNK_SIZE = 16;
const int CHUNK_VOLUME = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

enum BlockType : uint8_t {
    AIR = 0,
    DIRT = 1,
    GRASS = 2,
    STONE = 3
};

struct Vertex {
    float x, y, z;
    float u, v; // Texture coordinates
};

class Chunk {
private:
    BlockType blocks[CHUNK_VOLUME];
    std::vector<Vertex> meshVertices;

    // Helper to convert 3D coordinates to flat 1D array index
    inline int getIndex(int x, int y, int z) const {
        return x + (y * CHUNK_SIZE) + (z * CHUNK_SIZE * CHUNK_SIZE);
    }

public:
    Chunk();
    void generateTerrain();
    void generateMesh();
    bool isBlockTransparent(int x, int y, int z) const;
    
    const std::vector<Vertex>& getMesh() const { return meshVertices; }
};

#endif
