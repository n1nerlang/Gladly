#ifndef CLOUD_GENERATOR_HPP
#define CLOUD_GENERATOR_HPP

#include <cstdint>
#include "Block.hpp"
#include "Chunk.hpp"

enum class CloudStyle {
    FLUFFY,
    STREAKY,
    OVERCAST
};

class CloudGenerator {
private:
    uint64_t seed;
    int startY;
    int maxHeight;

public:
    CloudGenerator(uint64_t seed, int startY, int maxHeight)
        : seed(seed), startY(startY), maxHeight(maxHeight) {}

    void executeCloudPass(int chunkX, int chunkZ, BlockID* chunkBuffer, CloudStyle style, float timeOffset);
};

#endif
