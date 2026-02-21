# CHECKPOINT II *(due February 23 <sup>rd</sup>)*

> Use a **GITPULL** to get the latest assignments and documentation.
> Since we are on C89 version of C, all varibles must be declared at the very top of each function.

## COMP 2659 - Checkpoint 2 Task List

### Checkpoint 2 Summary

- [X] Asset Creation: Make models in monochrome and 640x400; create sprites in 8, 16, and 32-bit bitmaps.
- [ ] Raster Library Testing: Test your raster graphics library (plotting routines).

Note: Animation is not required until Checkpoint 3.

- [X] Data Structures: Write structs for models (e.g., player, walls, NPCs).

- [X] Each must be in its own .h and .c file of the same name.

- [X] Constraint: Avoid decimals/floats; aim for integers only.

- [ ] Events Module: Write functions for asynchronous, synchronous, and condition-based events.

- [X] Validation: Use printf to verify that model implementation and event handling are working.

- [ ] Documentation: Use the testing guide for test modules (available on D2L).

### Raster Graphics Library

These routines can optionally be done in C first, then in Assembly.

- [X] clear_screen

- [X] clear_region

- [X] plot_pixel

- [X] plot_horizontal_line

- [X] plot_vertical_line

- [X] plot_line (generic line between any two points)

- [X] plot_rectangle

- [X] plot_square

- [X] plot_triangle

- [X] plot_bitmap_8

- [X] plot_bitmap_16

- [X] plot_bitmap_32

- [X] plot_character

- [X] plot_string

### Renderer

- [ ] Rendering Library: Develop a library that uses the raster graphics library to render the model's current state to the screen.

**Requirement: Must be able to render at least a single frame.**

- [ ] Object Functions: Each object needs its own render_* function.

- [ ] Master Function: Implement a Master_render function.

### Coding Standards & "Other"

- [X] Function Length: Keep functions between 25-30 lines.

- [X] Formatting: Ensure code is readable and properly indented.

- [X] Header Documentation: Each function must include a header describing:

    Its purpose from the caller's perspective.

    The purpose of each input parameter.

    The purpose of each output parameter and return value.

    Any assumptions, limitations, or known bugs.

- [X] Source File Metadata: In .c files, write the purpose of data structures and functions.

- [X] Authorship: Include team member names and author(s) in the files.

## TASK ASSIGNMENTS

> - ***Gaurik's currently*** working on the raster graphics library in C and Assembly.
> - ***Meagan's currently*** working on adding basic functions for the first level, Asynchronous Events, and Renderer.
> - ***Paolo's currently*** working on Synchronous Events and Event Handling.
