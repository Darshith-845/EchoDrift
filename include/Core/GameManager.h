#pragma once

#include "Rendering/GLCommon.h"
#include <memory>         // Needed for std::unique_ptr
#include "Entities/Echo.h"
#include "Rendering/Renderer.h"
#include "Game/Grid.h"
#include "Core/Types.h" 

// Forward Declaration for Ghost (Corrected Namespace!)
// The Ghost class is defined in the Entities namespace,
// so we forward-declare it here before it's used by GameManager.
namespace EchoDrift::Entities {
    class Ghost; 
}

namespace EchoDrift::Core {

/**
 * @class GameManager
 * @brief Implements the Singleton pattern to manage the core game loop, state,
 * and coordination of all game systems (Input, Renderer, Entities).
 */
class GameManager {
private:
    // --- Singleton Implementation ---
    // 1. Private default constructor to prevent direct instantiation.
    GameManager() = default;
    
    // 2. Delete copy constructor and assignment operator. (CRITICAL for Singleton)
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    // --- Game State Members (Composition and Encapsulation) ---
    
    GLFWwindow* m_window = nullptr; // Pointer to the main window.
    
    // Renderer Declaration (Composition)
    EchoDrift::Rendering::Renderer m_renderer; 
    
    // Grid Declaration (Composition using RAII)
    std::unique_ptr<EchoDrift::Game::Grid> m_grid;
    
    // The player's main object
    std::unique_ptr<EchoDrift::Entities::Echo> m_playerEcho; 
    
    // NEW: Game State
    EchoDrift::Core::GameState m_currentState = EchoDrift::Core::GameState::RUNNING;

    // NEW: List of active Ghosts (Now the compiler can find EchoDrift::Entities::Ghost)
    std::vector<std::unique_ptr<EchoDrift::Entities::Ghost>> m_ghosts;

public:
    // --- Singleton Access ---
    static GameManager& GetInstance() {
        // C++11 guarantees thread-safe initialization.
        static GameManager instance; 
        return instance;
    }

    // --- Core Game Methods (Abstraction) ---
    void Init(GLFWwindow* window);
    void Update(float deltaTime);
    void Render();

    // NEW: Setter for game state (used by Echo on collision)
    void setState(EchoDrift::Core::GameState newState) { m_currentState = newState; }
    
    // Getter to check the state
    EchoDrift::Core::GameState getState() const { return m_currentState; }

    // NEW: Accessor for the Echo's trail (needed for Ghost collision)
    EchoDrift::Entities::Echo* getPlayerEcho() const { return m_playerEcho.get(); }
    
    // NEW: Accessor for Renderer (needed for Echo/Ghost render calls)
    EchoDrift::Rendering::Renderer& getRenderer() { return m_renderer; }
};

} // namespace EchoDrift::Core
