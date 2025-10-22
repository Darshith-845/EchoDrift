#pragma once

#include <iostream>

namespace EchoDrift::Entities {

/**
 * @struct Vec2
 * @brief Simple struct to represent 2D coordinates (grid position).
 */
struct Vec2 {
    int x;
    int y;
    // Constructor for easy initialization
    Vec2(int x_ = 0, int y_ = 0) : x(x_), y(y_) {} 
};


/**
 * @class Entity
 * @brief Abstract Base Class for all dynamic game objects.
 * Enforces a common interface using Pure Virtual Functions.
 */

constexpr float MOVE_INTERVAL = 0.2f;

class Entity {
private:
    // --- Encapsulated Data ---
    // The current position of the entity on the grid.
    Vec2 m_position;

protected:
    // Protected allows derived classes (Echo, Ghost) to access the position directly,
    // but keeps it private from outside systems (GameManager).
    void setPosition(const Vec2& pos) { m_position = pos; }

    // NEW: Timer to control when the entity moves
    float m_moveTimer = 0.0f;

public:
    // --- Public Interface ---
    Entity(int startX, int startY) : m_position(startX, startY) {}
    
    // CRUCIAL FOR POLYMORPHISM: Allows derived class destructors to be called
    // when deleted via an Entity* pointer.
    virtual ~Entity() = default; 

    // --- Pure Virtual Methods (Abstraction) ---
    // Derived classes MUST implement these methods.
    
    /**
     * @brief Logic update function.
     * @param dt Delta time since last frame.
     */

    /**
     * @brief Rendering function.
     */
    virtual void Render() = 0; 
    
    // Accessor (Getter)
    Vec2 getPosition() const { return m_position; }

    // Make Update take delta time (dt) for the timer
    virtual void Update(float dt) = 0;
};

} // namespace EchoDrift::Entities 