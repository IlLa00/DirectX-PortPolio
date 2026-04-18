#pragma once
#include <vector>

// Requires framework.h to be pre-included (for Vector2 and WIN_CENTER_X)

struct FrameRegion { float x, y, w, h; };

struct SkillAnimConfig {
	const wchar_t*           texture_file;
	std::vector<FrameRegion> frames;
	float                    fps;
	Vector2                  world_pos;
	float                    sx_factor;
	float                    sy_factor;
};

namespace SkillData {
	inline const SkillAnimConfig ALL_SKILLS[] = {
		// 0: Hydro-Pump (Budew)
		{
			L"Texture/Attack/Hydro-Pump.png",
			{
				{  78,  83,  43,  58 }, {  78, 212,  81,  76 }, {  78, 287, 178, 139 },
				{  78, 432, 178, 139 }, {  72, 576, 184, 139 }, {  78, 720, 179, 139 },
				{  75, 864, 181, 143 }, { 331,   0, 181, 141 }, { 336, 143, 176, 143 },
				{ 341, 287, 171, 144 }, { 340, 432, 172, 132 }, { 353, 576, 159, 120 },
				{ 402, 720, 110, 122 }, { 425, 866,  87, 115 }
			},
			1.0f / 3.0f,
			Vector2(WIN_CENTER_X, 420.0f), 3.5f, 1.5f
		},
		// 1: Crunch (Starly / Infernape)
		{
			L"Texture/Attack/Crunch.png",
			{
				{   0,  44, 104, 116 }, { 120,  38, 104, 131 }, { 266,  33, 104, 148 },
				{ 390,  21, 104, 171 }, { 525,  29, 104, 157 }, { 672,  42, 104, 136 },
				{ 817,  57, 104, 111 }, {   0, 260, 104,  78 }
			},
			1.0f / 3.0f,
			Vector2(WIN_CENTER_X / 2.0f, 430.0f), 1.5f, 1.5f
		},
		// 2: Wood-Hammer (Electivire)
		{
			L"Texture/Attack/Wood-Hammer.png",
			{
				{ 107, 488,  83,  56 }, { 103, 123,  73,  45 }, {  61,   0, 122, 115 },
				{  47, 182, 148,  58 }, {   0, 346, 195,  75 }
			},
			1.0f / 3.0f,
			Vector2(WIN_CENTER_X / 2.0f - 25.0f, 440.0f), 3.0f, 3.0f
		},
		// 3: Surf-Regular (Torterra)
		{
			L"Texture/Attack/Surf-Regular.png",
			{
				{ 202, 513, 227,  40 }, { 218, 445, 208,  50 }, { 237, 376, 188,  64 },
				{ 272, 301, 159,  70 }, { 289, 214, 145,  80 }, { 304, 111, 130,  90 },
				{ 330,   0, 106, 100 }
			},
			1.0f / 3.0f,
			Vector2(WIN_CENTER_X, 420.0f), 2.5f, 2.5f
		},
		// 4: Dragon-Claw (Arcanine)
		{
			L"Texture/Attack/Dragon-Claw.png",
			{
				{  11, 110,  20,  54 }, {  11, 175,  28,  62 }, {  10, 250,  35,  73 },
				{  12, 334,  41,  87 }, {  15, 434, 103,  87 }, {  17, 536, 104,  87 },
				{  17, 631, 104,  87 }, {  17, 725, 104,  87 }
			},
			1.0f / 3.0f,
			Vector2(WIN_CENTER_X / 2.0f - 25.0f, 440.0f), 3.0f, 3.0f
		},
		// 5: Scary-Face (Roserade)
		{
			L"Texture/Attack/Scary-Face-Reg.png",
			{
				{   0,  23,  34,  19 }, { 120,  10,  68,  40 }, {   5,  71,  78,  46 },
				{ 103,  71,  73,  55 }, {  90, 137,  98,  74 }, {  42,  20, 106,  80 }
			},
			1.0f / 3.0f,
			Vector2(WIN_CENTER_X + 345.0f, 305.0f), 3.0f, 3.0f
		}
	};
}
