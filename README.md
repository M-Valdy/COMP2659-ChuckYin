# Checkpoint III: Main Game Loop & Double Buffering
# Project Overview (Due March 16<sup>th</sup>)
> This checkpoint marks the transition from a static renderer to a dynamic, playable game. You will implement the high-level input module, the main game loop, all 1-player game logic and double-buffering to ensure smooth, flicker-free animation.

## Input Module Design
The project follows a strict three-level input architecture to ensure hardware independence:

1. Main Game Module: Orchestrates the game but contains no direct system calls for input.

2. Input Module (input.h/input.c): A middle-layer library that wraps O/S-specific code.

3. TOS System Calls: The underlying low-level routines (e.g., Cconis, Cnecin).

## Requirements

[ ] has_input(): Returns true if there is pending input.

[ ] get_input(): Returns the next character to be processed.

[ ] Decoupling: The library must be game-independent and reusable.

2. Main Game Module & Loop
The main game module (e.g., pong.c) must contain the main() function and follow a specific algorithmic structure.

The Game Loop Algorithm 
``` 
initialize model
render model (first frame)
set quit = false

repeat until quit
    if input is pending
        process async event  <-- update model change requests
    if clock has ticked
        process sync events  <-- update model data
        process cond events  <-- update model data
        render model (next frame)
```

### Critical Logic Rules

1. Async Events: Pressing a key (e.g., Up Arrow) only sets a "request" field in the model; it does not move the item.

2. Sync Events: Movement and data updates occur only on a clock tick.

> Rendering: Must be triggered by clock ticks, never by user input events.

### Timing and Privileged Mode
> The Atari ST maintains a 70 Hz clock at memory location 0x462.

> Accessing the Timer: Because this memory address is protected, you must use the Super() system call to enter privileged mode before reading it.

> Best Practice: Switch to privileged mode, read the value, and exit immediately to avoid system instability.

## Double Buffered Graphics
To eliminate flickering and tearing caused by rendering while the hardware scans the buffer, double buffering is required.

## Implementation Details

1. Buffer Allocation: Allocate a 32,000-byte buffer.

2. Alignment: The buffer must be 256-byte aligned for hardware compatibility.

3. No Stack Allocation: Do not allocate the buffer as a local variable, as it will cause stack smashing.

4. Page Flipping: Use the Setscreen system call to update the video base register.

5. Vertical Blank Sync: You must wait for the next vertical blank after calling Setscreen before rendering the next frame.

6. Cleanup: You must restore the original frame buffer address upon quitting to prevent a system crash.

### Coding Standards
1. Function Length: No function should exceed approximately 25–30 lines.

2. Documentation: Every function must have a header block specifying its purpose, parameters, and return values .

3. File Headers: Every source file must include a summary, ID header, and names of all team members.

## Deliverables
### input.h and input.c.

[ ] Main game module (e.g., pong.c).

[ ] Test driver programs for the input module.

[ ] A Makefile that generates a game-specific executable (e.g., pong.tos).