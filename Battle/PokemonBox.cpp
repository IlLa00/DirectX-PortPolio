#include "framework.h"

PokemonBox::PokemonBox(vector<unique_ptr<Pokemon>> init)
	: m_box(std::move(init)), m_field(m_box[0].get())
{}

int PokemonBox::GetFieldIndex() const {
	for (int i = 0; i < (int)m_box.size(); ++i)
		if (m_box[i].get() == m_field) return i;
	return 0;
}

bool PokemonBox::AllFainted() const {
	for (const auto& p : m_box)
		if (p->GetIsSurvive()) return false;
	return true;
}

bool PokemonBox::SwitchToNext() {
	int cur = GetFieldIndex();
	for (int i = 1; i < (int)m_box.size(); ++i) {
		int next = (cur + i) % (int)m_box.size();
		if (m_box[next]->GetIsSurvive()) {
			m_field = m_box[next].get();
			return true;
		}
	}
	return false;
}
