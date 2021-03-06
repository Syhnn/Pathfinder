# Pathfinding adventure

Just a small personnal project I recently started to experiment and have fun with pathfinding algorithms.

I implemented the BFS pathfinding algorithm, and later replaced it with A* - ~~at least a v1 for now~~ - and created a very simple UI to display it while it works.  
\[update\] : I just pushed a fix that gives a slightly higher value to the heuristic than normal, making the algorithm just that more greedy. Now it'll try to "beeline" for the end when it can saving time. Still have to make the path look better but that's a nice change.  
Here it is in a low fps gif :


![](astarv2.gif)

Going well so far. But there are still things to correct.  
I'd like to clean the code a bit (it is quite messy in some places) and also make it so the path look a little better.  
After that if I have enough time I'll probably try it on weighted map to see how it react to actual terrain.


## Libraries used

For now I mostly used [SDL2](https://libsdl.org/) which is a low level library used to do many things from rendering to handling sound and game controllers. 
On this project I only used it to render the grid and handle the mouse inputs.  

I also used [SDL_Image](https://www.libsdl.org/projects/SDL_image/) which allows me to use png image instead of bmp. Think of it as an extension on SDL.
