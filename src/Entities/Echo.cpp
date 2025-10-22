#include "Echo.h"
#include "Core/GameManager.h" // Needed to access the Grid and Renderer
#include "Rendering/Renderer.h"
#include <iostream>
#include "Core/Types.h" // Make sure to include this

namespace EchoDrift::Entities {

// Access the global systems via Singleton/Composition (Simplified Accessors needed in GameManager/Renderer)
using EchoDrift::Core::GameManager; 
using EchoDrift::Rendering::Renderer;
using EchoDrift::Game::Grid;

// ------------------------------------------------------------------
// Constructor and Input
// ------------------------------------------------------------------

Echo::Echo(int startX, int startY) : Entity(startX, startY) {
    m_trailHistory.push_back(getPosition());
    // NEW: Initialize the buffer
    m_buffer = std::make_unique<EchoDrift::Rendering::Buffer>();
}

void Echo::handleInput(EchoDrift::Core::Direction d) {
    // ... (Your previous input logic, including the reversal check if implemented) ...
    m_currentDirection = d;
}

// ------------------------------------------------------------------
// Geometry Generation Logic
// ------------------------------------------------------------------

void Echo::generateTrailGeometry(const Grid& grid) {
    std::vector<float> vertices;
    
    // Convert all trail history points to NDC
    for (const auto& gridPos : m_trailHistory) {
        Vec2 screenPos = grid.gridToScreen(gridPos);
        vertices.push_back(screenPos.x); 
        vertices.push_back(screenPos.y); 
    }
    
    // NEW: The Buffer::SetData will now hold the vertices for a GL_LINE_STRIP.
    m_buffer->SetData(vertices); 
}

// ------------------------------------------------------------------
// Core Loop Implementations
// ------------------------------------------------------------------

void Echo::Update(float dt) {
    m_moveTimer += dt;
    
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
    // Get the required system references
    GameManager& gm = GameManager::GetInstance();
    Grid* grid = gm.getGrid();
    if (!grid) return;
    
    // 1. Check if we should even attempt a move (based on direction)
    if (m_currentDirection == Core::Direction::NONE) {
        return; 
    }

    // 2. Calculate next position
    Vec2 newPos = getPosition();
    switch (m_currentDirection) {
        case Core::Direction::UP:    newPos.y += 1; break;
        case Core::Direction::DOWN:  newPos.y -= 1; break;
        case Core::Direction::LEFT:  newPos.x -= 1; break;
        case Core::Direction::RIGHT: newPos.x += 1; break;
        default: break;
    }

    // ===================================
    //  COLLISION CHECK BLOCK
    // ===================================

    // A. Boundary Collision Check
    if (newPos.x < 0 || newPos.x >= grid->getWidth() || 
        newPos.y < 0 || newPos.y >= grid->getHeight()) 
    {
        std::cout << "Collision! Boundary hit. Game Over." << std::endl;
        gm.setState(Core::GameState::GAME_OVER);
        return; 
    }
    
    // B. Self-Collision Check
    // We check against ALL existing trail segments
    for (size_t i = 0; i < m_trailHistory.size(); ++i) {
        const Vec2& trailSegment = m_trailHistory[i];
        
        if (newPos.x == trailSegment.x && newPos.y == trailSegment.y) {
            std::cout << "Collision! Self-trail hit. Game Over." << std::endl;
            gm.setState(Core::GameState::GAME_OVER);
            return;
        }
    }
    
    // ===================================
    //  END COLLISION CHECK BLOCK
    // ===================================

    // 3. Update position and trail ONLY if no collision occurred
    m_trailHistory.push_back(newPos);
    setPosition(newPos);
    
    // 4. Generate and Upload Geometry (as implemented in the previous step)
    generateTrailGeometry(*grid);
}


void Echo::Render() {
    // We need the Renderer and Shader references.
    Renderer& renderer = Renderer::GetInstance(); // If Renderer is a Singleton
    // OR: Renderer& renderer = GameManager::GetInstance().getRenderer();
    
    // Assume a public accessor for the Shader
    const auto& shader = *renderer.getDefaultShader(); 
    
// 1. Draw the Trail
renderer.Draw(
    *m_buffer, 
    shader, 
    0.2f, 0.5f, 0.8f, // Trail color (dim blue)
    GL_LINE_STRIP     
);

// 2. Draw the Echo's Head (as a single point for now, for a bright "dot")
std::vector<float> headVertex;
Vec2 headScreenPos = GameManager::GetInstance().getGrid()->gridToScreen(getPosition());
headVertex.push_back(headScreenPos.x);
headVertex.push_back(headScreenPos.y);

// Temporarily create a buffer for the head. (More optimized to reuse a small buffer or draw a quad).
EchoDrift::Rendering::Buffer headBuffer;
headBuffer.SetData(headVertex);

// Draw the head as a bright point (GL_POINTS)
renderer.Draw(
    headBuffer, 
    shader, 
    0.8f, 1.0f, 1.0f, // Bright cyan/white for the head
    GL_POINTS
);}

} // namespace EchoDrift::Entities