#include "ChunkFactory.hpp"

ChunkFactory::ChunkFactory(int seed) : worldSeed(seed) {
    // Automatically construct internal generators sharing the same seed matrix
    terrainGenerator = std::make_unique<WorldGenerator>(worldSeed);
    
    // Configures clouds to rest at a base height of 100 with a 4-voxel maximum thickness
    cloudGenerator = std::make_unique<CloudGenerator>(worldSeed, 100, 4);
}

BlockID* ChunkFactory::createChunk(int chunkX, int chunkZ, CloudStyle cloudStyle, float timeOffset) const {
    // 1. Calculate safe structural buffer size (16 * 16 * 128 = 32,768 bytes)
    size_t totalVoxels = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT;
    
    // 2. Allocate clean memory block on the heap
    BlockID* chunkBuffer = new BlockID[totalVoxels];

    // 3. STEP ONE: Run automated terrain pass (Stone, Dirt, Grass, Sand, Water)
    terrainGenerator->populateChunk(chunkX, chunkZ, chunkBuffer);

    // 4. STEP TWO: Run automated environment pass (Injects your custom cloud blocks)
    cloudGenerator->executeCloudPass(chunkX, chunkZ, chunkBuffer, cloudStyle, timeOffset);

    // 5. Hand back the ready-to-use chunk block payload
    return chunkBuffer;
}
