# Pathfinding adventure

Just a small personnal project I recently started to experiment and have fun with pathfinding algorithms.

I'm planning on implementing A* and creating a small GUI to better display how it works and interract with it.
First step is implementing BFS and displaying it, then clean the code and prepare for more advanced manipulations and A*.

Here's BFS at work for the first step :

![](bfs2_low_quality.gif)

Going well so far.

## Libraries used

For now I mostly used [SDL2](https://libsdl.org/) which is a low level library used to do many things from rendering to handling sound and game controllers. 
On this project I only used it to render the grid so far.  

I also used [SDL_Image](https://www.libsdl.org/projects/SDL_image/) which allows me to use png image instead of bmp. Think of it as an extension on SDL.
