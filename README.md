# **cub3D**

**cub3D** is a 3D raycasting game engine written in C, inspired by **Wolfenstein 3D**. The project demonstrates the fundamentals of 3D graphics programming using raycasting, with a focus on creating a simple game engine to render a 3D environment.

---

## **Features**

- **Raycasting Engine**: Implements a 3D view of a maze-like environment using raycasting, allowing the player to move around and view the world from a first-person perspective.
- **Player Movement**: Supports player movement with keyboard controls (`W`, `A`, `S`, `D` for forward, left, backward, and right movement).
- **Camera Control**: Allows the user to rotate the camera to change the view, simulating a first-person perspective.
- **Map Parsing**: Parses a custom map file format (`.cub`) to define the layout of the game world, including walls, floor, and ceiling textures.
- **Texture Mapping**: Applies textures to walls, floors, and ceilings to create a more realistic and immersive environment.
- **Collision Detection**: Handles collision detection to prevent the player from walking through walls.
- **Graphics Rendering**: Uses **MiniLibX** to handle the graphics rendering and pixel manipulation for the game.
- **Game Loop**: Implements a game loop that continually updates the player's position, refreshes the screen, and listens for input events.

---
