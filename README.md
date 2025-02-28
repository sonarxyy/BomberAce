[![Static Badge](https://img.shields.io/badge/Ng%C3%B4n_ng%E1%BB%AF-Ti%E1%BA%BFng_Vi%E1%BB%87t-blue)](https://github.com/sonarxyy/ShapeDominance/blob/main/README-vi.md)


# Shape Dominance
Small Game Project Written in C++ using [SDL2](https://wiki.libsdl.org/SDL2/FrontPage).


# Game Manager Class Components
- Engine: Manage core functionalities of the game.
  - Initialize core functions of the game.
  - Handle Events.
  - Update.
  - Render.
  - Clean.
- Game Object: Manage game objects of the game.
  - Update Object.
  - Render Object.
- Text Manager: Manage text rendering of the game.
  - Reused loaded font.
  - Create Texture from text.
  - Unload font.
  - Unload texture created from font.
- Texture Manager: Manage texture of the game.
  - Reused loaded texture.
  - Load Texture.
  - Unload Texture.
- Audio Manager: Manage audio of the game.
  - Reused loaded BGM, SFX.
  - Load BGM, SFX.
  - Play BGM, SFX.
  - Halt BGM.
  - Pause, resume BGM.
  - Set BGM, SFX volume.
- Constants : Define constants for the game.


# Game Components
- Main Menu.


# Build and Installation
1. Clone my repository. 
```
git clone https://github.com/sonarxyy/ShapeDominance.git
```
2. Install and Build.
> [!IMPORTANT]
> First of all, you need to ensure that C/C++ compiler is included in your environment variable.

   Inside cloned directory, run install.bat as administrator.  
3. Open the game.  
4. Enjoy.


# References
[Lazy Foo](https://lazyfoo.net/tutorials/SDL/)

[Let's Make Games](https://www.youtube.com/playlist?list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx)

[Game Programming Pattern](https://gameprogrammingpatterns.com/contents.html)

[CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)


# Credits
| Author |          Assets         |                                                                 Patreon                                                                |                                                             Itch.io                                                             |
|:------:|:-----------------------:|:--------------------------------------------------------------------------------------------------------------------------------------:|:-------------------------------------------------------------------------------------------------------------------------------:|
|  Kenny | Main UI, Audio, Texture | [![Static Badge](https://img.shields.io/badge/Patreon-white?style=flat&logo=patreon&labelColor=black)](https://www.patreon.com/kenney) | [![Static Badge](https://img.shields.io/badge/Itch.io-white?style=flat&logo=itch.io&labelColor=black)](https://kenney.itch.io/) |
| Lynocs |        Background       |                                                                   N/A                                                                  | [![Static Badge](https://img.shields.io/badge/Itch.io-white?style=flat&logo=itch.io&labelColor=black)](https://lynocs.itch.io/) |