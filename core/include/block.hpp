/**
 * @file Block.hpp
 * @brief Core block definitions and static property registry for the Gladly engine.
 *
 * Implements the Flyweight Pattern to minimize memory footprint on mobile devices.
 * Features a dynamic texture path resolver using hyphen separation for multi-textured blocks.
 *
 * @project Gladly Voxel Sandbox
 * @license GPLv3
 */

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <cstdint>
#include <string>
#include <unordered_map>
#include <filesystem> 
#include <algorithm>  

using BlockID = uint8_t;

namespace Blocks {
    const std::string TEXTURE_PACK_PATH = "textures/latest/gladlyoriginal";

    const BlockID air    = 0;
    const BlockID dirt   = 1;
    const BlockID grass  = 2;
    const BlockID stone  = 3;
    const BlockID wood   = 4;
    const BlockID leaves = 5;
    const BlockID planks = 6;
    const BlockID sand   = 7;
    const BlockID glass  = 8;
    const BlockID water  = 9;
}

struct TextureFaces {
    uint16_t top;
    uint16_t bottom;
    uint16_t north;
    uint16_t south;
    uint16_t east;
    uint16_t west;
};

struct BlockDefinition {
    BlockID id;
    std::string name; 
    bool isTransparent;
    bool isCollidable;
    TextureFaces textures;
};

class BlockRegistry {
private:
    std::unordered_map<BlockID, BlockDefinition> registry;
    
    BlockRegistry() {
        registerAllBlocks();
    }

    std::string toLower(std::string data) const {
        std::transform(data.begin(), data.end(), data.begin(), [](unsigned char c){ return std::tolower(c); });
        return data;
    }

public:
    static BlockRegistry& getInstance() {
        static BlockRegistry instance;
        return instance;
    }

    BlockRegistry(const BlockRegistry&) = delete;
    void operator=(const BlockRegistry&) = delete;

    void registerBlock(const BlockDefinition& block) {
        registry[block.id] = block;
    }

    const BlockDefinition& get(BlockID id) {
        auto it = registry.find(id);
        if (it != registry.end()) {
            return it->second;
        }
        return registry[Blocks::air];
    }

    /**
     * @brief Resolves the exact file path for a block face using hyphen asset naming rules.
     * @param id The target block ID.
     * @param facing The direction string ("top", "bottom", "north", "south", "east", "west").
     * @return Path string if found, path to "notfound.png", or empty string if all fail.
     */
    std::string resolveFaceTexture(BlockID id, const std::string& facing) const {
        if (id == Blocks::air) return ""; 

        std::string blockName = toLower(get(id).name);
        std::string preferredPath;

        // 1. OVERRIDE: Wood log sides explicitly look for 'woodsides.png'
        if (id == Blocks::wood && facing != "top" && facing != "bottom") {
            preferredPath = Blocks::TEXTURE_PACK_PATH + "/woodsides.png";
        } 
        // 2. OVERRIDE: Sand and Glass look for a single global file (e.g., 'sand.png')
        else if (id == Blocks::sand || id == Blocks::glass) {
            preferredPath = Blocks::TEXTURE_PACK_PATH + "/" + blockName + ".png";
        } 
        // 3. STANDARD FORMAT: Uses hyphen notation (e.g., 'wood-top.png', 'dirt-north.png')
        else {
            preferredPath = Blocks::TEXTURE_PACK_PATH + "/" + blockName + "-" + facing + ".png";
        }

        // Validate file presence on disk
        if (std::filesystem::exists(preferredPath)) {
            return preferredPath;
        }

        // Fallback asset tracker
        std::string fallbackPath = Blocks::TEXTURE_PACK_PATH + "/notfound.png";
        if (std::filesystem::exists(fallbackPath)) {
            return fallbackPath;
        }

        return "";
    }

private:
    void registerAllBlocks() {
        registerBlock({Blocks::air, "Air", true, false, {0, 0, 0, 0, 0, 0}});
        registerBlock({Blocks::dirt, "Dirt", false, true, {2, 2, 2, 2, 2, 2}});
        registerBlock({Blocks::grass, "Grass", false, true, {0, 2, 1, 1, 1, 1}});
        registerBlock({Blocks::stone, "Stone", false, true, {3, 3, 3, 3, 3, 3}});
        registerBlock({Blocks::wood, "Wood", false, true, {5, 5, 6, 6, 6, 6}});
        registerBlock({Blocks::leaves, "Leaves", true, true, {4, 4, 4, 4, 4, 4}});
        registerBlock({Blocks::planks, "Planks", false, true, {7, 7, 7, 7, 7, 7}});
        registerBlock({Blocks::sand, "Sand", false, true, {8, 8, 8, 8, 8, 8}});
        registerBlock({Blocks::glass, "Glass", true, true, {9, 9, 9, 9, 9, 9}});
        registerBlock({Blocks::water, "Water", true, false, {10, 10, 10, 10, 10, 10}});
    }
};

#endif
