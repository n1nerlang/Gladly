/**
 * @file ChunkFactory.hpp
 * @brief Automated processing pipeline combining terrain and cloud generation passes.
 *
 * Acts as the centralized factory to build complete chunk data payloads deterministically
 * without manual step-by-step injection in the main gameplay loop.
 *
 * @project Gladly Voxel Sandbox
 * @license GPLv3
 */

#ifndef CHUNK_FACTORY_HPP
#define CHUNK_FACTORY_HPP

#include <cstdint>
#include <memory>
#include "Block.hpp"
#include "WorldGenerator.hpp"
#include "CloudGenerator.hpp"

class ChunkFactory {
private:
    int worldSeed;
    std::unique_ptr<WorldGenerator> terrainGenerator;
    std::unique_ptr<CloudGenerator> cloudGenerator;

public:
    /**
     * @brief Initializes the automated factory with a unified generation seed.
     * @param seed The world seed used to sync landscapes and clouds.
     */
    ChunkFactory(int seed);

    /**
     * @brief Automatically allocates and generates a complete 3D chunk data block.
     * @param chunkX World column X coordinate.
     * @param chunkZ World column Z coordinate.
     * @param cloudStyle Which custom calculation blueprint to use for the sky layer.
     * @param timeOffset Time element to simulate drifting cloud movement.
     * @return Pointer to the fully populated raw BlockID array.
     * @note Memory ownership shifts to the caller. Remember to delete[] the array when unloading chunks!
     */
    BlockID* createChunk(int chunkX, int chunkZ, CloudStyle cloudStyle, float timeOffset = 0.0f) const;
};

#endif
