#pragma once
#include "../Framework/Math/Vector2.h"

struct GameState
{
    bool    gender           = false;
    bool    is_vsPokemon     = false;
    bool    is_vsChampion    = false;
    bool    clear_vsPokemon  = false;
    bool    clear_vsChampion = false;
    bool    lose_vsPokemon   = false;
    bool    lose_vsChampion  = false;

    Vector2 mouse_pos;
    Vector2 mouse_click_pos;

    void ResetBattleResult()
    {
        clear_vsPokemon  = false;
        clear_vsChampion = false;
        lose_vsPokemon   = false;
        lose_vsChampion  = false;
    }

    void ResetMouseClick() { mouse_click_pos = Vector2(0.0f, 0.0f); }
};
