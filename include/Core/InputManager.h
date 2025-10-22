#pragma once

#include <functional> // For std::function
#include "Core/Types.h" // <-- FIX: Added to define Direction

namespace EchoDrift::Core {

class InputManager {
public:
    // FIX: Using full namespace for Direction in std::function template
    using DirectionCallback = std::function<void(EchoDrift::Core::Direction)>;

    static InputManager& GetInstance();
    
    // --- Public methods ---
    void Update();

    // FIX: DirectionCallback is now declared because Types.h is included
    void SubscribeToDirection(DirectionCallback callback) {
        m_directionListener = std::move(callback);
    }
    
private:
    InputManager() = default;
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    DirectionCallback m_directionListener; // FIX: Type is now valid

    // FIX: Direction type is now valid
    EchoDrift::Core::Direction checkDirectionalKeys() const; 
};

} // namespace EchoDrift::Core
