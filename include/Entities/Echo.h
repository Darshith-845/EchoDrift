#pragma once

#include "Entity.h"
#include "Core/InputManager.h"
#include "Rendering/Buffer.h" // New include for Buffer
#include "Game/Grid.h"        // New include for Grid access
#include <vector>
#include <memory>
#include "Core/Types.h" // <-- CORRECT path

namespace EchoDrift::Entities {

class Echo : public Entity {
private:
    EchoDrift::Core::Direction m_currentDirection = EchoDrift::Core::Direction::NONE;
    std::vector<Vec2> m_trailHistory;
    
    // NEW: The Echo owns its trail geometry buffer. (Composition)
    std::unique_ptr<EchoDrift::Rendering::Buffer> m_buffer;

    // Helper to generate trail vertices and upload to the buffer
    void generateTrailGeometry(const EchoDrift::Game::Grid& grid);

public:
    Echo(int startX, int startY); // Updated constructor
    
    // ... handleInput, Update, Render overrides ...
    void handleInput(EchoDrift::Core::Direction d);
    void Update(float dt) override;
    void Render() override;
    
    // CRITICAL: We need a way to get the Grid from the GameManager for coordinate mapping
    // We will assume a global accessor for the grid for simplicity in this step.
};

} // namespace EchoDrift::Entities