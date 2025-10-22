#pragma once

namespace EchoDrift::Core {

/**
 * @enum GameState
 * @brief Defines the main high-level states of the game.
 */
enum class GameState {
    RUNNING,
    GAME_OVER,
    PAUSED
};

// Simple enum for movement direction
enum class Direction {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

} // namespace EchoDrift::Core