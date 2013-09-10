# Thoughts and ramblings on Kf::InputSystem

InputSystem should implement custom event types which hide the underlying tech (e.g. SDL). Binding keys/buttons/mouse movements to application-level events at the engine-level (i.e. in InputSystem) is not necessary. The application should have and register an application-level button-mapper:

    Read input events from underlying tech (e.g. SDL_KeyboardEvent)
                      |
                      v
    Wrap raw event with engine-level event <-- Obscuring underlying technology (e.g. SDL) /
                      |                        Adding value (e.g. duration?/double-press?/etc) here
                      |
                      | (e.g. SDL_KeyboardEvent -> InputSystem::KeyboardEvent) 
                      |
                      |
                      v
    Push engine-level event to listeners/subscribers  <-- Callbacks fire here (gotta be fast!)
                      |
                      v
    Map engine-level event to application-level event <-- Key bidings here, at application level
                      |
                      |
                      | (e.g. InputSystem::KeyboardEvent -> MyGame::JumpEvent)
                      |
                      |
                      v
    Push application-level event to listeners/subscribers <-- Callbacks here