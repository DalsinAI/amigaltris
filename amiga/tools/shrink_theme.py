#!/usr/bin/env python3
"""Make LTris's theme drawer for the Amiga: shrink_theme.py SRC DST.

The wallpapers (JPEG) and the menu picture (PNG) are 1920x1080; the game
stretches them to its window (at most 1024x768 here), so they are made
800x600, a quarter of the memory each as textures and far less to decode.
Every PNG is stored as 8-bit RGBA: SDL2_image.module 0.6 can damage the
heap decoding RGB PNGs without alpha. Everything else is copied as it is.
The AmiCradle Team. GPL 2 or later, like LTris.
"""
import os
import shutil
import sys

from PIL import Image

SIZE = (800, 600)
SHRINK = {"menu.png"}


def main(src, dst):
    os.makedirs(dst, exist_ok=True)
    for name in sorted(os.listdir(src)):
        s = os.path.join(src, name)
        d = os.path.join(dst, name)
        if not os.path.isfile(s) or name.startswith("Makefile"):
            continue
        low = name.lower()
        if low.startswith("wallpaper") and low.endswith(".jpg"):
            with Image.open(s) as im:
                im = im.convert("RGB").resize(SIZE, Image.LANCZOS)
                im.save(d, "JPEG", quality=88, optimize=True)
        elif low.endswith(".png"):
            with Image.open(s) as im:
                im = im.convert("RGBA")
                if name in SHRINK:
                    im = im.resize(SIZE, Image.LANCZOS)
                im.save(d, "PNG", optimize=True)
        else:
            shutil.copyfile(s, d)
        print(name, os.path.getsize(d))


if __name__ == "__main__":
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    main(sys.argv[1], sys.argv[2])
