/**
 * @file ChunkFactory.cpp
 * @brief Clean, human-readable processing pipeline for chunk generation.
 *
 * Implements the centralized orchestration steps to initialize and populate 
 * voxels using a shared 64-bit world seed matrix.
 *
 * @project Gladly Voxel Sandbox
 * @license GPLv3
 */

#include "ChunkFactory.hpp"

/**
 * @brief Constructor that instantiates the underlying procedural modules.
 * @param seed The 64-bit unsigned integer used to synchronize all random generation.
 */
ChunkFactory::ChunkFactory(uint64_t seed) : worldSeed(seed) {
    // Both generators are allocated on the heap using the exact same seed footprint
    terrainGenerator = std::make_unique<WorldGenerator>(worldSeed);
    
    // Configures clouds to spawn starting at Y=100 with a maximum height of 4 voxels
    cloudGenerator = std::make_unique<CloudGenerator>(worldSeed, 100, 4);
}

/**
 * @brief Creates, builds, and returns a fully populated 3D block chunk array.
 * @param chunkX The X coordinate of the chunk column in the world grid.
 * @param chunkZ The Z coordinate of the chunk column in the world grid.
 * @param cloudStyle The algorithm model used to render the atmosphere pass.
 * @param timeOffset Time-step modifier used to offset noise sampling for wind simulation.
 * @return A raw pointer to a sequential BlockID array (Size: CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT).
 */
BlockID* ChunkFactory::createChunk(int chunkX, int chunkZ, CloudStyle cloudStyle, float timeOffset) const {
    // Calculate total buffer constraints (16 * 16 * 128 = 32,768 bytes)
    size_t totalVoxels = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT;
    
    // Allocate raw memory for the chunk payload
    BlockID* chunkBuffer = new BlockID[totalVoxels];

    // PASS 1: Execute the terrain pass to carve stone, dirt, grass, sand, and water
    terrainGenerator->populateChunk(chunkX, chunkZ, chunkBuffer);

    // PASS 2: Execute the cloud pass to overlay custom sky blocks over empty air zones
    cloudGenerator->executeCloudPass(chunkX, chunkZ, chunkBuffer, cloudStyle, timeOffset);

    // Hand back the ready-to-mesh data array. Memory ownership transitions to the caller!
    return chunkBuffer;
}
