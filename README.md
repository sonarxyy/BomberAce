[![Static Badge](https://img.shields.io/badge/Ng%C3%B4n_ng%E1%BB%AF-Ti%E1%BA%BFng_Vi%E1%BB%87t-blue)](https://github.com/sonarxyy/ShapeDominance/blob/main/README-vi.md)


# Shape Dominance
Small Game Project Written in C++ using [SDL2](https://wiki.libsdl.org/SDL2/FrontPage).


# Game Manager Class Components
- Audio Manager: Manage audio of the game.
  - Reused loaded BGM, SFX.
  - Load BGM, SFX.
  - Play BGM, SFX.
  - Halt BGM.
  - Pause, resume BGM.
  - Set BGM, SFX volume.
- Constants: Define constants for the game.
- Engine: Manage core functionalities of the game.
  - Initialize core functions of the game.
  - Handle Events.
  - Update.
  - Render.
  - Clean.
- Game Object: Manage game objects of the game.
  - Update Object.
  - Render Object.
- Game State Manager: Manage the states of the game.
  - Set current state of the game.
  - Get current state of the game.
- Level Manager: Manage the loading levels of the game.
  - Load level from text file.
- Text Manager: Manage text rendering of the game.
  - Reused loaded font.
  - Create Texture from text.
  - Unload font.
  - Unload texture created from font.
- Texture Manager: Manage texture of the game.
  - Reused loaded texture.
  - Load Texture.
  - Unload Texture.
- Tile Manager: Manage tile map of the game.
  - Load texture for each tile type.
  - Render tile map of the game.
  - Check collision with any objects (player, enemy, explosion).
  - Check if designated position is a wall.
  - Destroy breakable tile.
  - Get tile type at designated position.


# Indispensible class of the game.
- Bomb: Kaboom!
  - Load texture of the bomb.
  - Update status of the bomb.
  - Render the bomb.
  - Get the explosion radius of the bomb.
- Enemy: Cats.
  - Update status of enemy.
  - Place bomb at random position (prioritize breakable tile).
  - Try to escape from explosion.
  - Render to the screen.
- Explosion: The breakthrough.
  - Load texture of explosion.
  - Update status of explosion.
  - Render explosion to the screen.
  - Check if explosion is ended.
- Fade transition: For smootha experience.
  - Fade in, fade out transition for the game.
- HUD: Head-up display
  - Update and render basic information of player's status.
- In Game: When playing game
  - Handle input from user.
  - Update information while playing.
  - Render changes to the screen.
- Main menu: A pool of selections.
  - Create a list of options.
  - Handle input from user.
  - Update change based on input (can be from mouse, keyboard, mousewheel).
  - Render change to the screen.
- Options menu: Main menu but in a different context.
- Player: A cat.
  - Handle input from user.
  - Update animation (idle, walk, facing direction).
  - Render animation to the screen.
  - Get player position
  - Place bomb at designated position.
  - Can take damage.
  - Game over when healh point deducted to 0.
- Power-ups:


# Build and Installation
1. Clone my repository. 
```
git clone https://github.com/sonarxyy/ShapeDominance.git
```
2. Settings the environment and build.
> [!IMPORTANT]
> First of all, you need to ensure that C/C++ compiler is included in your environment variable.  

> [!NOTE]
> From second time, you just need to run build.bat to build the game.

Inside cloned directory, run install.bat. After installation is done, run build.bat.  
3. Open the game.  
4. Enjoy.


# References
[Lazy Foo](https://lazyfoo.net/tutorials/SDL/)

[Let's Make Games](https://www.youtube.com/playlist?list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx)

[Game Programming Pattern](https://gameprogrammingpatterns.com/contents.html)

[CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)


# Credits
|                               Author                              |              Assets             |
|:-----------------------------------------------------------------:|:-------------------------------:|
|  [Gemini Imagen3](https://deepmind.google/technologies/imagen-3/) |            Main Menu            |
|                   [bigjpg](https://bigjpg.com/)                   |          Upscale Image          |
|           [Netherzapdos](https://netherzapdos.itch.io/)           | Player's sprite, enemy's sprite |
|                 [Kenney](https://kenney.nl/assets)                |               SFX               |
|      [Caz Creates Games](https://caz-creates-games.itch.io/)      |            Bomb's VFX           |
|            [JAR Incorporated](https://jarinc.itch.io/)            |         Heart's textures        |
|               [CodeManu](https://codemanu.itch.io/)               |       Explosion's textures      |
| [Raymond Larabie](https://www.dafont.com/profile.php?user=137418) |           Xirod's font          |