#include "Chunk.hpp"

Chunk::Chunk() {
    generateTerrain();
}

void Chunk::generateTerrain() {
    // A simple flat world starter generator
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int z = 0; z < CHUNK_SIZE; z++) {
            for (int y = 0; y < CHUNK_SIZE; y++) {
                int index = getIndex(x, y, z);
                if (y == 5) {
                    blocks[index] = GRASS;
                } else if (y < 5 && y > 2) {
                    blocks[index] = DIRT;
                } else if (y <= 2) {
                    blocks[index] = STONE;
                } else {
                    blocks[index] = AIR;
                }
            }
        }
    }
}

bool Chunk::isBlockTransparent(int x, int y, int z) const {
    // If the neighbor is outside this chunk boundaries, assume air for now
    if (x < 0 || x >= CHUNK_SIZE || y < 0 || y >= CHUNK_SIZE || z < 0 || z >= CHUNK_SIZE) {
        return true;
    }
    return blocks[getIndex(x, y, z)] == AIR;
}

void Chunk::generateMesh() {
    meshVertices.clear();

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                BlockType currentBlock = blocks[getIndex(x, y, z)];
                
                if (currentBlock == AIR) continue;

                float fx = static_cast<float>(x);
                float fy = static_cast<float>(y);
                float fz = static_cast<float>(z);

                // CRITICAL MOBILE OPTIMIZATION: Face Culling
                
                // 1. Check Top Face (Y + 1)
                if (isBlockTransparent(x, y + 1, z)) {
                    meshVertices.push_back({fx,     fy+1.0f, fz,      0.0f, 0.0f});
                    meshVertices.push_back({fx+1.0f, fy+1.0f, fz,      1.0f, 0.0f});
                    meshVertices.push_back({fx+1.0f, fy+1.0f, fz+1.0f, 1.0f, 1.0f});
                    meshVertices.push_back({fx,     fy+1.0f, fz+1.0f, 0.0f, 1.0f});
                }

                // 2. Check Bottom Face (Y - 1)
                if (isBlockTransparent(x, y - 1, z)) {
                    meshVertices.push_back({fx,     fy,      fz,      0.0f, 0.0f});
                    meshVertices.push_back({fx,     fy,      fz+1.0f, 0.0f, 1.0f});
                    meshVertices.push_back({fx+1.0f, fy,      fz+1.0f, 1.0f, 1.0f});
                    meshVertices.push_back({fx+1.0f, fy,      fz,      1.0f, 0.0f});
                }

                // 3. Check Front Face (Z + 1)
                if (isBlockTransparent(x, y, z + 1)) {
                    meshVertices.push_back({fx,     fy,      fz+1.0f, 0.0f, 0.0f});
                    meshVertices.push_back({fx+1.0f, fy,      fz+1.0f, 1.0f, 0.0f});
                    meshVertices.push_back({fx+1.0f, fy+1.0f, fz+1.0f, 1.0f, 1.0f});
                    meshVertices.push_back({fx,     fy+1.0f, fz+1.0f, 0.0f, 1.0f});
                }

                // [Repeat similar checks for Back (Z-1), Left (X-1), and Right (X+1) faces]
            }
        }
    }
}
