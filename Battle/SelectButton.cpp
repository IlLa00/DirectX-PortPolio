#include "framework.h"

SelectButton::SelectButton()
{
	wstring file = L"Texture/StatusBox.png";
	vector<TextFrame*> font_box;

	button_list.push_back(new RectCollider(Vector2(380, 165)));
	button_list.push_back(new RectCollider(Vector2(380, 165)));
	button_list.push_back(new RectCollider(Vector2(380, 165)));

	for (auto b : button_list)
		b->is_active = true;

	font_box.push_back(new TextFrame(file, 295, 31, 6, 10)); // A
	font_box.push_back(new TextFrame(file, 645, 52, 5, 8)); // t
	font_box.push_back(new TextFrame(file, 645, 52, 5, 8)); // t
	font_box.push_back(new TextFrame(file, 501, 34, 6, 7)); // a
	font_box.push_back(new TextFrame(file, 501, 50, 6, 10)); // k
	text_list.push_back(font_box);
	font_box.clear();

	font_box.push_back(new TextFrame(file, 327, 50, 6, 10)); // M
	font_box.push_back(new TextFrame(file, 565, 34, 6, 7)); // e
	font_box.push_back(new TextFrame(file, 549, 31, 6, 10)); // d
	font_box.push_back(new TextFrame(file, 630, 32, 2, 9)); // i
	font_box.push_back(new TextFrame(file, 645, 52, 5, 8)); // t
	font_box.push_back(new TextFrame(file, 501, 34, 6, 7)); // a
	font_box.push_back(new TextFrame(file, 645, 52, 5, 8)); // t
	font_box.push_back(new TextFrame(file, 630, 32, 2, 9)); // i
	font_box.push_back(new TextFrame(file, 565, 53, 6, 7)); // o
	font_box.push_back(new TextFrame(file, 549, 53, 6, 7)); // n
	text_list.push_back(font_box);
	font_box.clear();

	font_box.push_back(new TextFrame(file, 327, 31, 6, 10)); // C
	font_box.push_back(new TextFrame(file, 613, 31, 6, 10)); // h
	font_box.push_back(new TextFrame(file, 501, 34, 6, 7)); // a
	font_box.push_back(new TextFrame(file, 549, 53, 6, 7)); // n
	font_box.push_back(new TextFrame(file, 597, 34, 6, 9)); // g
	font_box.push_back(new TextFrame(file, 565, 34, 6, 7)); // e
	text_list.push_back(font_box);
	font_box.clear();

	image = new TextBox();

	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();
}

SelectButton::~SelectButton()
{
	for (auto b: button_list)
		delete b;
	button_list.clear();

	for (int i = 0; i < text_list.size(); i++)
	{
		for (int j = 0; j < text_list[i].size(); j++)
			delete text_list[i][j];
	}
	text_list.clear();

	delete image;
	delete CB;
}

void SelectButton::Update()
{
	button_list[0]->pos = Vector2(213.3, 625); // 공격 버튼
	button_list[1]->pos = Vector2(639.9, 625); // 회복 버튼
	button_list[2]->pos = Vector2(1066.5, 625); // 교체 버튼

	for (auto b : button_list)
		b->WorldUpdate();

	for (int i = 0; i < text_list[0].size(); i++)
	{
		text_list[0][i]->pos = Vector2(160 + 20 * i, 625);
		text_list[0][i]->scale = text_list[0][i]->GetFrameSize() * 2.5f;
		text_list[0][i]->WorldUpdate();
	}
	for (int i = 0; i < text_list[1].size(); i++)
	{
		text_list[1][i]->pos = Vector2(535 + 20 * i, 625);
		text_list[1][i]->scale = text_list[1][i]->GetFrameSize() * 2.5f;
		text_list[1][i]->WorldUpdate();
	}
	for (int i = 0; i < text_list[2].size(); i++)
	{
		text_list[2][i]->pos = Vector2(960 + 20 * i, 625);
		text_list[2][i]->scale = text_list[2][i]->GetFrameSize() * 2.5f;
		text_list[2][i]->WorldUpdate();
	}
	
	image->Update();

	WorldUpdate();
}

void SelectButton::Render()
{
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	image->Render();

	if (is_active)
	{
		for (auto b : button_list)
			b->Render();

		for (auto t : text_list[0])
			t->Render();
		for (auto t : text_list[1])
			t->Render();
		for (auto t : text_list[2])
			t->Render();
	}
	
}