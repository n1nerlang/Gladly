#include "WorldGenerator.hpp"

void WorldGenerator::populateChunk(int chunkX, int chunkZ, BlockID* chunkBuffer) {
    for (int x = 0; x < CHUNK_WIDTH; x++) {
        for (int z = 0; z < CHUNK_WIDTH; z++) {
            for (int y = 0; y < CHUNK_HEIGHT; y++) {
                int index = x + (z * CHUNK_WIDTH) + (y * CHUNK_WIDTH * CHUNK_WIDTH);
                if (y == 5) {
                    chunkBuffer[index] = Blocks::grass;
                } else if (y < 5 && y > 2) {
                    chunkBuffer[index] = Blocks::dirt;
                } else if (y <= 2) {
                    chunkBuffer[index] = Blocks::stone;
                } else {
                    chunkBuffer[index] = Blocks::air;
                }
            }
        }
    }
}
