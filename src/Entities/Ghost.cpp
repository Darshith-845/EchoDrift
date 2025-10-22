#include "Ghost.h"
#include "Core/GameManager.h"
#include "Rendering/Renderer.h"
#include <iostream>
#include <random> // For simple random AI

namespace EchoDrift::Entities {

using EchoDrift::Core::GameManager;
using EchoDrift::Rendering::Renderer;
using EchoDrift::Game::Grid;

// Global random number generator (for simple AI)
static std::mt19937 rng(std::random_device{}());
static std::uniform_int_distribution<int> directionDist(1, 4); // Maps to UP/DOWN/LEFT/RIGHT

// ------------------------------------------------------------------
// Constructor
// ------------------------------------------------------------------

Ghost::Ghost(int startX, int startY) : Entity(startX, startY) {
    m_trailHistory.push_back(getPosition());
    m_buffer = std::make_unique<EchoDrift::Rendering::Buffer>();
}

// ------------------------------------------------------------------
// AI and Trail Generation
// ------------------------------------------------------------------

EchoDrift::Core::Direction Ghost::decideMove(const Grid& grid) {
    // Simple AI: Just pick a random direction
    int randomInt = directionDist(rng);
    return static_cast<EchoDrift::Core::Direction>(randomInt);
}

void Ghost::generateTrailGeometry(const Grid& grid) {
    std::vector<float> vertices;
    
    // Draw trail as points (same as Echo for simplicity)
    for (const auto& gridPos : m_trailHistory) {
        Vec2 screenPos = grid.gridToScreen(gridPos);
        vertices.push_back(screenPos.x); 
        vertices.push_back(screenPos.y); 
    }
    
    m_buffer->SetData(vertices); 
}

// ------------------------------------------------------------------
// Core Loop Implementations
// ------------------------------------------------------------------

void Ghost::Update(float dt) {
    m_moveTimer += dt;
    GameManager& gm = GameManager::GetInstance();
    Grid* grid = gm.getGrid();
    if (!grid || gm.getState() != Core::GameState::RUNNING) return;

    if (m_moveTimer >= MOVE_INTERVAL) {
    
    // --- ALL EXISTING MOVEMENT, COLLISION, AND POSITION UPDATE LOGIC GOES HERE ---
    
    // Example: 
    // Vec2 newPos = getPosition();
    // // ... calculate newPos ...
    // // ... collision checks ...
    // setPosition(newPos);
    
    // --- END OF LOGIC ---
    
    // 3. Reset the timer
    m_moveTimer = 0.0f; // Reset to 0 or subtract MOVE_INTERVAL for precision
    
    }
    // 1. Ghost decides where to move (Simple random AI)
    EchoDrift::Core::Direction decidedDir = decideMove(*grid);
    Vec2 newPos = getPosition();
    
    switch (decidedDir) {
        case Core::Direction::UP:    newPos.y += 1; break;
        case CoreDrift::Core::Direction::DOWN:  newPos.y -= 1; break;
        case CoreDrift::Core::Direction::LEFT:  newPos.x -= 1; break;
        case CoreDrift::Core::Direction::RIGHT: newPos.x += 1; break;
        default: break;
    }

    // 2. Boundary Check (Ghost can move off screen for a bit, but we'll limit it for now)
    // Note: A simpler rule for Ghost is just to bounce off walls, but we'll stick to a basic check.
    if (newPos.x < 0 || newPos.x >= grid->getWidth() || 
        newPos.y < 0 || newPos.y >= grid->getHeight()) 
    {
        // Ignore this move if it's out of bounds and try again next frame
        return; 
    }

    // 3. Collision with Player Trail (The Game Rule!)
    const auto& playerTrail = gm.getPlayerEcho()->getTrailHistory(); // Assume a public accessor is added
    for (const auto& trailSegment : playerTrail) {
        if (newPos.x == trailSegment.x && newPos.y == trailSegment.y) {
            std::cout << "GHOST HIT ECHO TRAIL! Ghost neutralized." << std::endl;
            // The Ghost is neutralized/destroyed. 
            // In a real game, this means marking the Ghost for deletion.
            return; 
        }
    }
    
    // 4. Commit the move
    m_trailHistory.push_back(newPos);
    setPosition(newPos);
    
    // 5. Generate Geometry
    generateTrailGeometry(*grid);
}

void Ghost::Render() {
    GameManager& gm = GameManager::GetInstance();
    Renderer& renderer = gm.getRenderer(); // Assume a public accessor exists
    
    if (gm.getState() != Core::GameState::RUNNING) return;

    // Draw the Ghost's trail and head. Use a distinct color (e.g., magenta).
    renderer.Draw(
        *m_buffer, 
        shader, 
        0.2f, 0.5f, 0.8f, // Trail color
        GL_LINE_STRIP     // NEW: Specify how to draw the vertices
    );
}

} // namespace EchoDrift::Entities