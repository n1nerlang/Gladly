#include <iostream>
#include "Chunk.hpp"
#include "ChunkFactory.hpp"

int main() {
    std::cout << "Starting Gladly Engine Test..." << std::endl;

    ChunkFactory factory(12345ULL);
    BlockID* blocks = factory.createChunk(0, 0, CloudStyle::FLUFFY);

    if (blocks) {
        std::cout << "Chunk created successfully via factory." << std::endl;
        delete[] blocks;
    } else {
        std::cerr << "Failed to create chunk via factory." << std::endl;
        return 1;
    }

    Chunk chunk;
    // generateTerrain() is called in the constructor, but let's be explicit if needed
    // or ensure it's properly initialized.
    chunk.generateMesh();
    std::cout << "Mesh generated for a default chunk. Vertex count: " << chunk.getMesh().size() << std::endl;

    if (chunk.getMesh().size() == 0) {
        std::cerr << "Error: Generated mesh is empty!" << std::endl;
        return 1;
    }

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
