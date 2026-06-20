#include "Chunk.hpp"

Chunk::Chunk() {
    generateTerrain();
}

void Chunk::generateTerrain() {
    // A simple flat world starter generator
    for (int y = 0; y < CHUNK_HEIGHT; y++) {
        for (int z = 0; z < CHUNK_WIDTH; z++) {
            for (int x = 0; x < CHUNK_WIDTH; x++) {
                int index = getIndex(x, y, z);
                if (y == 5) {
                    blocks[index] = Blocks::grass;
                } else if (y < 5 && y > 2) {
                    blocks[index] = Blocks::dirt;
                } else if (y <= 2) {
                    blocks[index] = Blocks::stone;
                } else {
                    blocks[index] = Blocks::air;
                }
            }
        }
    }
}

bool Chunk::isBlockTransparent(int x, int y, int z) const {
    // If the neighbor is outside this chunk boundaries, assume air for now
    if (x < 0 || x >= CHUNK_WIDTH || y < 0 || y >= CHUNK_HEIGHT || z < 0 || z >= CHUNK_WIDTH) {
        return true;
    }
    BlockID id = blocks[getIndex(x, y, z)];
    return BlockRegistry::getInstance().get(id).isTransparent;
}

void Chunk::generateMesh() {
    meshVertices.clear();

    for (int x = 0; x < CHUNK_WIDTH; x++) {
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_WIDTH; z++) {
                BlockID currentBlock = blocks[getIndex(x, y, z)];
                
                if (currentBlock == Blocks::air) continue;

                float fx = static_cast<float>(x);
                float fy = static_cast<float>(y);
                float fz = static_cast<float>(z);

                // 1. Top Face (Y + 1)
                if (isBlockTransparent(x, y + 1, z)) {
                    meshVertices.push_back({fx,     fy+1.0f, fz,      0.0f, 0.0f});
                    meshVertices.push_back({fx,     fy+1.0f, fz+1.0f, 0.0f, 1.0f});
                    meshVertices.push_back({fx+1.0f, fy+1.0f, fz+1.0f, 1.0f, 1.0f});
                    meshVertices.push_back({fx+1.0f, fy+1.0f, fz,      1.0f, 0.0f});
                }

                // 2. Bottom Face (Y - 1)
                if (isBlockTransparent(x, y - 1, z)) {
                    meshVertices.push_back({fx,     fy,      fz,      0.0f, 0.0f});
                    meshVertices.push_back({fx+1.0f, fy,      fz,      1.0f, 0.0f});
                    meshVertices.push_back({fx+1.0f, fy,      fz+1.0f, 1.0f, 1.0f});
                    meshVertices.push_back({fx,     fy,      fz+1.0f, 0.0f, 1.0f});
                }

                // 3. Front Face (Z + 1)
                if (isBlockTransparent(x, y, z + 1)) {
                    meshVertices.push_back({fx,     fy,      fz+1.0f, 0.0f, 0.0f});
                    meshVertices.push_back({fx+1.0f, fy,      fz+1.0f, 1.0f, 0.0f});
                    meshVertices.push_back({fx+1.0f, fy+1.0f, fz+1.0f, 1.0f, 1.0f});
                    meshVertices.push_back({fx,     fy+1.0f, fz+1.0f, 0.0f, 1.0f});
                }

                // 4. Back Face (Z - 1)
                if (isBlockTransparent(x, y, z - 1)) {
                    meshVertices.push_back({fx+1.0f, fy,      fz,      0.0f, 0.0f});
                    meshVertices.push_back({fx,     fy,      fz,      1.0f, 0.0f});
                    meshVertices.push_back({fx,     fy+1.0f, fz,      1.0f, 1.0f});
                    meshVertices.push_back({fx+1.0f, fy+1.0f, fz,      0.0f, 1.0f});
                }

                // 5. Left Face (X - 1)
                if (isBlockTransparent(x - 1, y, z)) {
                    meshVertices.push_back({fx,     fy,      fz,      0.0f, 0.0f});
                    meshVertices.push_back({fx,     fy,      fz+1.0f, 1.0f, 0.0f});
                    meshVertices.push_back({fx,     fy+1.0f, fz+1.0f, 1.0f, 1.0f});
                    meshVertices.push_back({fx,     fy+1.0f, fz,      0.0f, 1.0f});
                }

                // 6. Right Face (X + 1)
                if (isBlockTransparent(x + 1, y, z)) {
                    meshVertices.push_back({fx+1.0f, fy,      fz+1.0f, 0.0f, 0.0f});
                    meshVertices.push_back({fx+1.0f, fy,      fz,      1.0f, 0.0f});
                    meshVertices.push_back({fx+1.0f, fy+1.0f, fz,      1.0f, 1.0f});
                    meshVertices.push_back({fx+1.0f, fy+1.0f, fz+1.0f, 0.0f, 1.0f});
                }
            }
        }
    }
}
