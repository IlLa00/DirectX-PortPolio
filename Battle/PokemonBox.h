#pragma once

class PokemonBox {
	vector<unique_ptr<Pokemon>> m_box;
	Pokemon* m_field;

public:
	explicit PokemonBox(vector<unique_ptr<Pokemon>> init);

	Pokemon* GetField()         const { return m_field; }
	Pokemon* GetPokemon(int i)  const { return m_box[i].get(); }
	int      GetSize()          const { return (int)m_box.size(); }
	int      GetFieldIndex()    const;
	bool     AllFainted()       const;
	bool     SwitchToNext();
};
