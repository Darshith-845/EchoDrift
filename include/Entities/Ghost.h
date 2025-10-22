#pragma once

#include "Entity.h"
#include "Rendering/Buffer.h" 
#include "Game/Grid.h"       
#include <vector>
#include <memory>

namespace EchoDrift::Entities {

/**
 * @class Ghost
 * @brief An AI-controlled enemy that leaves a deadly trail.
 * Inherits movement and rendering interface from Entity.
 */
class Ghost : public Entity {
private:
    // The Ghost's trail history (its own deadly line)
    std::vector<Vec2> m_trailHistory;
    
    // The Ghost's geometry buffer (Composition)
    std::unique_ptr<EchoDrift::Rendering::Buffer> m_buffer;

    // Helper to generate trail vertices for the Renderer
    void generateTrailGeometry(const EchoDrift::Game::Grid& grid);

    // Simple AI helper function
    EchoDrift::Core::Direction decideMove(const EchoDrift::Game::Grid& grid);

public:
    // Constructor uses the base Entity constructor
    Ghost(int startX, int startY); 

    // --- Polymorphic Overrides ---
    void Update(float dt) override;
    void Render() override;
};

} // namespace EchoDrift::Entities

