#pragma once

struct PokemonInitData {
	float sx, sy, sw, sh;
	float attack;
};

namespace PokemonData {
	inline constexpr PokemonInitData PLAYER[] = {
		{ 1621.0f,   34.0f, 80.0f, 80.0f, 50.0f },  // Budew
		{ 2107.0f,   34.0f, 80.0f, 80.0f, 60.0f },  // Torterra
		{ 2107.0f, 2569.0f, 80.0f, 80.0f, 80.0f }   // Roserade
	};
	inline constexpr PokemonInitData VS_POKEMON_ENEMY[] = {
		{   23.0f, 250.0f, 35.0f, 39.0f, 50.0f }    // Starly
	};
	inline constexpr PokemonInitData VS_CHAMPION_ENEMY[] = {
		{  244.0f, 1594.0f, 80.0f, 80.0f, 50.0f },  // Infernape
		{  244.0f,  619.0f, 80.0f, 80.0f, 55.0f },  // Electivire
		{ 1459.0f, 1594.0f, 80.0f, 80.0f, 60.0f }   // Arcanine
	};
}
