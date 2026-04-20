#pragma once
#include "../Data/PokemonData.h"

struct IBattleContext
{
    virtual ~IBattleContext() = default;

    virtual void BuildEnemyTeam(vector<unique_ptr<Pokemon>>& out) const = 0;
    virtual UINT GetEnemySkillSlot(int fieldIndex)               const = 0;
    virtual void OnPlayerWin(GameState& state)                   const = 0;
    virtual void OnPlayerLose(GameState& state)                  const = 0;
    virtual void OnEnemyFainted(GameState& state, bool allFainted) const = 0;
    virtual UINT GetEnemyNameSlotOffset()                        const = 0;
    virtual bool IsVsPokemon()                                   const = 0;
};

struct VsPokemonContext final : IBattleContext
{
    void BuildEnemyTeam(vector<unique_ptr<Pokemon>>& out) const override
    {
        for (const auto& d : PokemonData::VS_POKEMON_ENEMY)
            out.push_back(make_unique<Pokemon>(
                Vector2(WIN_CENTER_X + 345, 305), d.sx, d.sy, d.sw, d.sh, d.attack));
    }
    UINT GetEnemySkillSlot(int)              const override { return 1; }
    void OnPlayerWin(GameState& s)           const override { s.clear_vsPokemon = true; }
    void OnPlayerLose(GameState& s)          const override { s.lose_vsPokemon = true; s.clear_vsPokemon = true; }
    void OnEnemyFainted(GameState& s, bool)  const override { s.clear_vsPokemon = true; }
    UINT GetEnemyNameSlotOffset()            const override { return 0; }
    bool IsVsPokemon()                       const override { return true; }
};

struct VsChampionContext final : IBattleContext
{
    void BuildEnemyTeam(vector<unique_ptr<Pokemon>>& out) const override
    {
        for (int i = 0; i < 3; ++i)
        {
            const auto& d = PokemonData::VS_CHAMPION_ENEMY[i];
            float py = (i == 0) ? 305.0f : 285.0f;
            out.push_back(make_unique<Pokemon>(
                Vector2(WIN_CENTER_X + 345, py), d.sx, d.sy, d.sw, d.sh, d.attack));
        }
    }
    UINT GetEnemySkillSlot(int fieldIndex) const override
    {
        static constexpr UINT MAP[] = { 1, 2, 4 };
        return MAP[fieldIndex];
    }
    void OnPlayerWin(GameState&)                     const override {}
    void OnPlayerLose(GameState& s)                  const override { s.lose_vsChampion = true; s.clear_vsChampion = true; }
    void OnEnemyFainted(GameState& s, bool allFainted) const override { if (allFainted) s.clear_vsChampion = true; }
    UINT GetEnemyNameSlotOffset()                    const override { return 1; }
    bool IsVsPokemon()                               const override { return false; }
};
