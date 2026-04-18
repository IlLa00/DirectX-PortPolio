#include "framework.h"
#include "Data/SkillAnimConfig.h"

Skill::Skill()
{
	for (const auto& cfg : SkillData::ALL_SKILLS)
	{
		wstring file = cfg.texture_file;
		Texture::Add(file);
		vector<Frame*> frames;
		for (const auto& fr : cfg.frames)
			frames.push_back(new Frame(file, fr.x, fr.y, fr.w, fr.h));
		skill.push_back(new Clip(frames, Clip::CLIP_TYPE::END, cfg.fps));
	}

	for (auto& a : is_active)
		a = false;

	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();
}

Skill::~Skill()
{
	for (auto s : skill)
		delete s;
	skill.clear();
	delete CB;
}

void Skill::Update(UINT slot)
{
	is_active[slot] = true;
	const auto& cfg = SkillData::ALL_SKILLS[slot];
	this->pos     = cfg.world_pos;
	this->scale.x = skill[slot]->GetFrameSize().x * cfg.sx_factor;
	this->scale.y = skill[slot]->GetFrameSize().y * cfg.sy_factor;
	WorldUpdate();
	skill[slot]->Update();
}

void Skill::Render()
{
	VS->Set();
	PS->Set();
	WB->SetVS(0);
	CB->SetPS(0);
	for (int i = 0; i < 6; ++i)
		if (is_active[i])
			skill[i]->Render();
}
