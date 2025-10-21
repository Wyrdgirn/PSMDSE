/*
*   This file is part of PSMDSE
*   Copyright (C) 2020 DeadPhoenix8091, Epicpkmn11, Flame, RocketRobz, StackZ, TotallyNotGuy
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#include "common.hpp"
#include "init.hpp"
#include "structs.hpp"
#include "titleSelection.hpp"

#include <3ds.h>
#include <dirent.h>

// The classic Fade Effect! ;P
// Wyrdgirn: Both renamed to avoid "multiple definition" error.
// they are already defined here: Universal-Core/gui.cpp line 42 & 43
int initFadealpha = 255;
bool initFadein = true;

// If true -> Exit PSMDSE.
bool exiting = false;

touchPosition touch;

u32 DARKER_COLOR, LIGHT_COLOR, LIGHTER_COLOR, SELECTED_COLOR, UNSELECTED_COLOR; // Color Types.

// Include all spritesheet's.
C2D_SpriteSheet sprites;

// If button Position pressed -> Do something.
bool touching(touchPosition touch, Structs::ButtonPos button) {
	if (touch.px >= button.x && touch.px <= (button.x + button.w) && touch.py >= button.y && touch.py <= (button.y + button.h))
		return true;
	else
		return false;
}

Result Init::Initialize() {
	gfxInitDefault();
	romfsInit();
	amInit();
	Gui::init();
    Gui::loadSheet("romfs:/gfx/sprites.t3x", sprites);
	cfguInit();
	// make folders if they don't exist
	mkdir("sdmc:/3ds", 0777);	// For DSP dump
	mkdir("sdmc:/3ds/PSMDSE", 0777); // main Path.
	osSetSpeedupEnable(true);	// Enable speed-up for New 3DS users.

	DARKER_COLOR = DARKER_BLUE;
	LIGHT_COLOR = LIGHT_BLUE;
	LIGHTER_COLOR = LIGHTER_BLUE;
	SELECTED_COLOR = SELECTED_BLUE;
	UNSELECTED_COLOR = UNSELECTED_BLUE;

    Gui::setScreen(std::make_unique<TitleSelection>());

    return 0;
}

Result Init::MainLoop() {
    // Initialize everything.
    Initialize();

	// Loop as long as the status is not exiting.
	while (aptMainLoop() && !exiting)
	{
		hidScanInput();
		u32 hHeld = hidKeysHeld();
		u32 hDown = hidKeysDown();
	#ifdef UC_KEY_REPEAT
        u32 hDownRepeat = hidKeysDownRepeat();
    #endif
		hidTouchRead(&touch);
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(Top, BLACK);
		C2D_TargetClear(Bottom, BLACK);
		Gui::clearTextBufs();
        
        // Wyrdgirn: Renamed from Gui::mainLoop. see Universal-Core/gui.hpp
	#ifdef UC_KEY_REPEAT
		Gui::ScreenLogic(hDown, hDownRepeat, hHeld, touch);
    #else
		Gui::ScreenLogic(hDown, hHeld, touch);
    #endif
    
		C3D_FrameEnd(0);

		if (initFadein == true) {
			initFadealpha -= 3;
			if (initFadealpha < 0) {
				initFadealpha = 0;
				initFadein = false;
			}
		}
	}
    // Exit all services and exit the app.
    Exit();
    return 0;
}

Result Init::Exit() {
	// Exit every process.
	cfguExit();
	amExit();
	Gui::exit();
	Gui::unloadSheet(sprites);
	gfxExit();
	romfsExit();
	return 0;
}
