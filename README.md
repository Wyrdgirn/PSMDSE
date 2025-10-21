# PSMDSE
> Pokémon Super Mystery Dungeon Save Editor for Nintendo 3DS.

PSMDSE is a Save Editor for Pokémon Super Mystery Dungeon for the Nintendo 3DS!

## Build on Windows

1) Install MSYS2
2) Open an MSYS2 shell (not a Mingw shell!) and change to a folder of your choice (empty is better)
3) Install the [devkitPro](https://devkitpro.org/wiki/devkitPro_pacman).
4) Install GIT, the 3ds-dev package, clone this repo and enter the dir. Installing Git is optional if you already have it installed on your system and it is in your PATH.
```bash
pacman -S git
pacman -S 3ds-dev
git clone https://github.com/Wyrdgirn/PSMDSE.git
cd PSMDSE
```
5) Clone the Universal-Core. I've created a fork in `https://github.com/Wyrdgirn/Universal-Core` in case the devs update it and make it incompatible (again) with this project.
```bash
git clone https://github.com/Universal-Team/Universal-Core.git
```
6) Download the [bannertool](https://github.com/diasurgical/bannertool/releases) and [makerom](https://github.com/3DSGuy/Project_CTR/releases) tools and put the .exe files in the root folder of this project.
7) Just do a `make` to build the project... use `-j` for faster compilation.
```bash
make -j4
```

### Compilation problems
If you see error `make: *** No rule to make target 'romfs/gfx', needed by 'all'.  Stop.` when compiling, run the following commands and try compiling again
```bash
mkdir romfs
mkdir romfs/gfx
```
Ignore `fatal: No names found, cannot describe anything.` errors, they do not affect compilation for now.

## Official repository
> https://github.com/Universal-Team/PSMDSE
