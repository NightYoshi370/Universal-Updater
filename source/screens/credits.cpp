/*
*   This file is part of Universal-Updater
*   Copyright (C) 2019-2020 Universal-Team
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

#include "credits.hpp"

extern std::unique_ptr<Config> config;
extern bool touching(touchPosition touch, Structs::ButtonPos button);
// Language Page 1.
const std::vector<std::string> Translators = {
	"_mapple²",
	"AlbertCoolGuy",
	"antoine62",
	"Chips",
	"cooolgamer",
	"David Pires",
	"FlameKat53",
	"lemonnade0",
	"LinuxCat",
	"Pavel",
	"Pk11",
	"Roby Spia",
	"SuperSaiyajinStackZ",
	"XDgierman",
	"YoSoy",
	"XxPhoenix1996xX"
};

const std::vector<std::string> Languages = {
	"Русский",
	"Dansk",
	"Français",
	"Português",
	"Français",
	"Português",
	"Bruh",
	"Lietuvių",
	"Français",
	"Русский",
	"日本語",
	"Italiano",
	"Deutsch, English",
	"Polski",
	"Español",
	"Español, Italian, Portuguese"
};

// Universal-Team Page 2.
const std::vector<std::string> UniversalTeam = {
	"DeadPhoenix",
	"FlameKat53",
	"NightScript",
	"Pk11",
	"RocketRobz",
	"SuperSaiyajinStackZ",
	"TotallyNotGuy"
};

// Script Page 3.
const std::vector<std::string> ScriptCreators = {
	"cooolgamer", "DualBladedKirito", "Glazed_Belmont", "Pk11", "SuperSaiyajinStackZ", "The Conceptionist", "YoSoy"
};
const std::vector<std::string> ScriptAmount = {"1", "1", "1", "1", "5", "10", "1 | 2"};

const std::vector<std::string> specialNames = {
	"devkitPro", "NightScript"
};
const std::vector<std::string> specialDescriptions = {
	"For devkitARM, Libctru, Citro2D, Citro3D and the portlibs.",
	"For posting updates on Reddit."
};

void Credits::Draw(void) const {
	std::string title = "Universal-Updater - ";
	title += Lang::get("CREDITS");
	GFX::DrawTop();
	if (creditsPage != 4) {
		Gui::DrawStringCentered(0, config->useBars() ? 0 : 2, 0.7f, config->textColor(), title, 400);
		Gui::DrawStringCentered(0, 30, 0.7f, config->textColor(), Lang::get("DEVELOPED_BY"), 390);
		Gui::DrawStringCentered(0, 60, 0.7f, config->textColor(), Lang::get("MAIN_DEV"), 390);
		GFX::DrawSprite(sprites_stackZ_idx, 5, 85);
		GFX::DrawSprite(sprites_universal_core_idx, 200, 110);
		std::string currentVersion = Lang::get("CURRENT_VERSION");
		currentVersion += V_STRING;
		Gui::DrawString(395-Gui::GetStringWidth(0.70f, currentVersion), 219, 0.70f, config->textColor(), currentVersion, 400);
	} else {
		Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, 190));
		GFX::DrawSprite(sprites_discord_idx, 115, 35);
	}

	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect
	DrawBottom();
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect
}

void Credits::DrawBottom(void) const {
	std::string line1;
	std::string line2;

	GFX::DrawBottom();
	switch (creditsPage) {
		case CreditsPages::Translators:
			Gui::DrawStringCentered(0, -2, 0.7f, config->textColor(), Lang::get("TRANSLATORS"), 320);
			for(int i = 0; i < ENTRIES_PER_SCREEN && i < (int)Translators.size(); i++) {
				Gui::Draw_Rect(0, 40+(i*57), 320, 45, config->unselectedColor());
				line1 = Translators[screenPos + i];
				line2 = Languages[screenPos + i];
				if (screenPos + i == Selection) {
					Gui::drawAnimatedSelector(0, 40+(i*57), 320, 45, .060, TRANSPARENT, config->selectedColor());
				}
				Gui::DrawStringCentered(0, 38+(i*57), 0.7f, config->textColor(), line1, 320);
				Gui::DrawStringCentered(0, 62+(i*57), 0.7f, config->textColor(), line2, 320);
			}
			break;
		case CreditsPages::UniversalTeam:
			Gui::DrawStringCentered(0, -2, 0.7f, config->textColor(), "Universal-Team", 320);
			for(int i = 0; i < ENTRIES_PER_SCREEN && i < (int)UniversalTeam.size(); i++) {
				Gui::Draw_Rect(0, 40+(i*57), 320, 45, config->unselectedColor());
				line1 = UniversalTeam[screenPos + i];
				if (screenPos + i == Selection) {
					Gui::drawAnimatedSelector(0, 40+(i*57), 320, 45, .060, TRANSPARENT, config->selectedColor());
				}
				Gui::DrawStringCentered(0, 50+(i*57), 0.7f, config->textColor(), line1, 320);
			}
			break;
		case CreditsPages::ScriptCreators:
			Gui::DrawStringCentered(0, -2, 0.7f, config->textColor(), Lang::get("SCRIPTCREATORS"), 320);
			for(int i = 0; i < ENTRIES_PER_SCREEN && i < (int)ScriptCreators.size(); i++) {
				Gui::Draw_Rect(0, 40+(i*57), 320, 45, config->unselectedColor());
				line1 = ScriptCreators[screenPos + i];
				line2 = ScriptAmount[screenPos + i];
				if (screenPos + i == Selection) {
					Gui::drawAnimatedSelector(0, 40+(i*57), 320, 45, .060, TRANSPARENT, config->selectedColor());
				}
				Gui::DrawStringCentered(0, 38+(i*57), 0.7f, config->textColor(), line1, 320);
				Gui::DrawStringCentered(0, 62+(i*57), 0.7f, config->textColor(), line2, 320);
			}
			break;
		case CreditsPages::SpecialThanks:
			Gui::DrawStringCentered(0, -2, 0.7f, config->textColor(), "Special Thanks", 320);
			for(int i = 0; i < ENTRIES_PER_SCREEN && i < (int)specialNames.size(); i++) {
				Gui::Draw_Rect(0, 40+(i*57), 320, 45, config->unselectedColor());
				line1 = specialNames[screenPos + i];
				line2 = specialDescriptions[screenPos + i];
				if (screenPos + i == Selection) {
					Gui::drawAnimatedSelector(0, 40+(i*57), 320, 45, .060, TRANSPARENT, config->selectedColor());
				}
				Gui::DrawStringCentered(0, 38+(i*57), 0.7f, config->textColor(), line1, 320);
				Gui::DrawStringCentered(0, 62+(i*57), 0.7f, config->textColor(), line2, 320);
			}
			break;
		default:
			Gui::DrawStringCentered(0, -2, 0.55f, config->textColor(), Lang::get("LINK"), 320);
	}
}


void Credits::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (keyRepeatDelay)	keyRepeatDelay--;
	// KEY_DOWN Logic. (SIZE)
	int maxSize;
	switch (creditsPage) {
		case CreditsPages::Translators:
			maxSize = (int)Translators.size()-1;
			break;
		case CreditsPages::UniversalTeam:
			maxSize = (int)UniversalTeam.size()-1;
			break;
		case CreditsPages::ScriptCreators:
			maxSize = (int)ScriptCreators.size()-1;
			break;
		case CreditsPages::SpecialThanks:
			maxSize = (int)specialNames.size()-1;
			break;
	}

	if ((hHeld & KEY_DOWN && !keyRepeatDelay)) {
		if (Selection < maxSize) {
			Selection++;
		} else {
			Selection = 0;
		}

		keyRepeatDelay = config->keyDelay();
	}

	if ((hHeld & KEY_UP && !keyRepeatDelay)) {
		if (Selection > 0) {
			Selection--;
		} else {
			Selection = maxSize;
		}

		keyRepeatDelay = config->keyDelay();
	}
	
		
	if ((hDown & KEY_L || hDown & KEY_LEFT)) {
		if (creditsPage > 0) {
			Selection = 0;
			creditsPage--;
		}
	}

	if ((hDown & KEY_R || hDown & KEY_RIGHT)) {
		if (creditsPage < 4) {
			Selection = 0;
			creditsPage++;
		}
	}

	if (hDown & KEY_B) {
		Gui::screenBack(config->screenFade());
		return;
	}

	if (Selection < screenPos) {
		screenPos = Selection;
	} else if (Selection > screenPos + ENTRIES_PER_SCREEN - 1) {
		screenPos = Selection - ENTRIES_PER_SCREEN + 1;
	}
}