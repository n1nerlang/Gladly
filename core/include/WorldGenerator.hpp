#ifndef WORLD_GENERATOR_HPP
#define WORLD_GENERATOR_HPP

#include <cstdint>
#include "Block.hpp"
#include "Chunk.hpp"

class WorldGenerator {
private:
    uint64_t seed;

public:
    WorldGenerator(uint64_t seed) : seed(seed) {}
    void populateChunk(int chunkX, int chunkZ, BlockID* chunkBuffer);
};

#endif
