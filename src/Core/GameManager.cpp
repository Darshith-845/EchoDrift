#include "Core/GameManager.h"
#include "Core/InputManager.h" // Needed for GetInstance() and SubscribeToDirection
#include "Game/Grid.h"         // Needed for Grid definition and GRID_SIZE constant
#include "Entities/Ghost.h"    // Needed for std::make_unique<Ghost>
#include <iostream>            // For basic logging
#include <utility>             // For std::move
#include <iterator>            // <-- FIX: Added for range-based for loops (begin/end)

namespace EchoDrift::Core {

using EchoDrift::Game::Grid;
using EchoDrift::Entities::Echo;
using EchoDrift::Entities::Ghost;
using EchoDrift::Game::GRID_SIZE;

/**
 * @brief Initializes game components and entities.
 * @param window The main GLFW window pointer.
 */
void GameManager::Init(GLFWwindow* window) {
    m_window = window;
    std::cout << "GameManager initializing..." << std::endl;

    // Initialize Renderer (Mock implementation)
    m_renderer.Init(m_window);

    // Initialize Grid
    m_grid = std::make_unique<Grid>();

    // Initialize Player Echo
    m_playerEcho = std::make_unique<Echo>(m_grid.get(), GRID_SIZE / 2, GRID_SIZE / 2);

    // Initialize Ghosts
    // FIX START: Corrected syntax for Ghost instantiation
    m_ghosts.push_back(std::make_unique<Ghost>(
        m_grid.get(), // <-- FIX: Added the missing Grid pointer argument
        GRID_SIZE / 4, 
        GRID_SIZE / 4
    )); // <-- FIX: Closed the parenthesis for std::make_unique/Ghost constructor

    // Subscribe player input handler to directional changes
    // Assuming InputManager::SubscribeToDirection expects a DirectionCallback
    InputManager::GetInstance().SubscribeToDirection([this](Direction d) {
        if (m_currentState == GameState::RUNNING) {
            m_playerEcho->handleInput(d);
        }
    });

    std::cout << "GameManager initialized successfully." << std::endl;
}

/**
 * @brief Updates the game state every frame.
 * @param deltaTime Time elapsed since the last frame.
 */
void GameManager::Update(float deltaTime) {
    if (m_currentState != GameState::RUNNING) {
        return;
    }
    
    // Update InputManager state (e.g., check for key presses)
    InputManager::GetInstance().Update();

    // Update Player Echo
    m_playerEcho->Update(deltaTime);

    // Update Ghosts
    // FIX START: std::begin/std::end is now available thanks to <iterator>
    for (const auto& ghost : m_ghosts) {
        ghost->Update(deltaTime);
    }
    // FIX END

    // TODO: Check for collisions and update state if necessary
    // Example: checkCollision(m_playerEcho.get(), m_ghosts);
}

/**
 * @brief Renders the game components to the screen.
 */
void GameManager::Render() {
    m_renderer.Clear();

    // Render Grid/Background (Mock)
    m_renderer.DrawSquare(0, 0);

    // Render Player Echo
    m_playerEcho->Render(m_renderer);

    // Render Ghosts
    // FIX START: std::begin/std::end is now available thanks to <iterator>
    for (const auto& ghost : m_ghosts) {
        ghost->Render(m_renderer);
    }
    // FIX END

    m_renderer.SwapBuffers(m_window);
}

} // namespace EchoDrift::Core
