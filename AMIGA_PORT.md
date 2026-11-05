LTris for AmigaOS 3.x
=====================

A port of LTris 2 (ltris2 2.0.4, Michael Speck's falling-blocks game from
LGames, https://lgames.sourceforge.net) for AmigaOS 3.2 on a 68040 or
68060 with an FPU and an RTG screen, on OpenGPU's SDL 2.

Source: ltris2-2.0.4.tar.gz,
https://downloads.sourceforge.net/project/lgames/ltris/ltris2-2.0.4.tar.gz
(the LTris page links it as prdownloads.sourceforge.net/lgames/ltris2-2.0.4.tar.gz),
sha256 482150495f9d87bb139d5af1abec7030383c37fdb3e75a45e9bad67ead798eda.
It is the "upstream" commit (tag upstream-2.0.4) of this repository; the
port is on branch team2/ltris-amiga.

Status: builds and links; not yet run on an Amiga.


What you need
-------------

- A 68040 or 68060 with an FPU (not an LC040 or EC040), AmigaOS 3.2, an RTG
  card (or the AmigaChrome lab), and some 40 MB of free memory.
- OpenGPU 0.6 or later: opengpu.library and LIBS:OpenGPU/SDL2.module,
  SDL2_image.module (the PNG and JPEG pictures) and SDL2_mixer.module (the
  WAV effects), installed by OpenUp. SDL_ttf (the fonts) is in the program.
- About 3.5 MB of disk.


How to play
-----------

Double-click LTris in its drawer, or from a Shell:

    cd LTris
    LTris

Keep the drawer as it is (LTris, figures, themes/Standard) anywhere but
the very top of a volume: the game finds its files through the drawer's
full name. The settings (ltris2.conf) and highscores (ltris2.hscr) are
written into the drawer.

The menu: cursor up and down choose, Return, cursor left or right change
or enter, Esc goes back. A game starts from "New Game"; the demo plays
behind the menu until then. In a game Esc brings the menu back (and
pauses), F6 shows the frame rate. The mouse works in the menu too.

Player 1 (the Amiga's defaults; upstream's End key isn't on an Amiga
keyboard):

    cursor left / right   move
    cursor down           soft drop
    cursor up             rotate right
    1                     rotate left
    Space                 hard drop
    Del                   hold

Player 2: A / D move, S soft drop, W / E rotate, Y hard drop, Q hold.
Player 3 (Vs 2xCPU's human, if any): numeric pad 1 / 3 move, 2 soft drop,
5 / 6 rotate, 8 hard drop, 7 hold. All can be changed under Controls.
A game controller works too (SDL's mapping; see the gp_ lines of
ltris2.conf).

Game modes: Normal, Figures (pictures to clear), Vs Human, Vs CPU and
Vs 2xCPU, with "modern" rules (ghost piece, hold, three previews) or the
classic ones.

Graphics, Mode: "Window 640x480" (the default) on the Workbench,
"Screen 640x480" a screen of its own, or a window of 800x600 or 1024x768
(on a big enough Workbench), then "Apply Theme&Mode". The frame limit
(50, 60 or 200 a second) is there too; on a 68040 50 is right.


Building
--------

GFOpenAmigaGCC 16.2.0-open4 or later, the OpenGPU developer kit, and
Python 3 with Pillow on the build machine:

    make -f amiga/Makefile.amigaos -j2 dist \
         STOVE=/path/to/openamigagcc-16.2.0-open4 \
         NDK=/path/to/OpenNDK/Include_H SDL2KIT=/path/to/opengpu-sdk

The defaults are CradleLab's paths. Output: build/amigaos/LTris; 'dist'
makes dist/LTris/ (LTris, figures, themes/Standard/, ReadMe, README-ltris,
COPYING.txt, Licences.txt, with GlowIcons) and dist/LTris.info. The icons
are made from amiga/icons/icons.json (see "about" there).


What was changed
----------------

- amiga/Makefile.amigaos: upstream's source lists (src/ in C++, libgame/
  in C), no NLS; links the kit's libSDL2_ttf.a, libSDL2_image.a,
  libSDL2_mixer.a and libSDL2.a. DATADIR, CONFIGDIR and HISCOREDIR (and
  libgame's SRC_DIR) are all amiga_progdir().
- amiga/amiga_progdir.c, amiga_port.h (given to every file with -include):
  the program's drawer as a full name (GetProgramDir() + NameFromLock()),
  since upstream joins "/themes" etc. onto it and "PROGDIR:/x" would be the
  parent; and vasprintf(), which libnix lacks.
- src/main.cpp: amiga/amiga_screens.c (from amigasevenkingdoms) snapshots
  the screens before the global Renderer starts SDL and, after it has
  quit SDL, closes the empty "SDL" screens SDL2.module 0.6 leaves behind
  a full screen.
- src/sdl.cpp: a full screen is SDL_WINDOW_FULLSCREEN at the window's own
  size, not _FULLSCREEN_DESKTOP; the renderer is asked for target textures
  (the game draws into them: frames, previews, the background), falling
  back to SDL's software renderer if the accelerated one can't. The
  renderer's name is printed. createShadow()'s w*h stack array is on the
  heap.
- src/view.cpp: the window modes are a 640x480 screen and windows of
  640x480, 800x600 and 1024x768 (upstream's are fractions of the desktop).
- src/vconfig.cpp: Amiga defaults: a 640x480 window, 8 mixer channels,
  cursor up rotates right and Space drops (no End key).
- src/theme.cpp, theme.h, vgame.cpp: the ten wallpapers are loaded one at a
  time, when the level changes, instead of all at start.
- amiga/tools/shrink_theme.py (run by 'dist'): the 1920x1080 wallpapers
  and menu picture are made 800x600 (the game stretches them to the
  window anyway; ten at full size were 80 MB of textures). Every PNG is
  stored as RGBA (all of upstream's already are).
- libgame/bowl.h, tetris.c: prototypes for three functions used before
  they are defined (GCC 14 and later refuse implicit declarations).
- src/tools.h: <time.h> for main.cpp's time().

Endianness: the settings and highscores are text files (key=value), the
figures file is text, the pictures and sounds go through SDL_image and
SDL_mixer, and the game's pixel work uses SDL's own formats, so nothing
needed swapping.


Known limits
------------

- Not yet run. To check first: that the opengpu renderer gives target
  textures (the console says "Renderer: ..."; if the game is black or the
  bowls have no frames, try SetEnv SDL_RENDER_DRIVER software), the speed
  of the menu's fade and of the fonts (SDL_ttf renders on the 68k), and
  the sound.
- No translations (NLS off): English only.
- Not in a volume's top drawer (see How to play).
- The window sizes are fixed; the pictures are stretched to 4:3 as
  upstream does in its windows.
