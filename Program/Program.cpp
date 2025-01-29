#include "framework.h"
#include "Program.h"

Program::Program()
{
	Create();

	Scene_list.push_back(new StartScene());
	Scene_list.push_back(new CharactorSelectScene());
	Scene_list.push_back(new TownScene());
	Scene_list.push_back(new vsPokemonScene());
	Scene_list.push_back(new vsChampionScene());

	Now_scene = Scene_list[0];

	Sound::Init();

	Sound_list.push_back(new Sound("BGM/Pokemon Diamond - Intro - Nintendo DS.mp3", true));
	Sound_list.push_back(new Sound("BGM/Data_sound_bgm_Introduction.wav", true));
	Sound_list.push_back(new Sound("BGM/Data_sound_bgm_Lake.wav", true));
	Sound_list.push_back(new Sound("BGM/206496544D7DC35D18.mp3", true));
	Sound_list.push_back(new Sound("BGM/17159E4D4D7DC6202B.mp3", true));
	
	Now_sound = Sound_list[0];
	Now_sound->Play();

	cursor = 0;
}


void Program::Update()
{
	Control::Get()->Update();
	Timer::Get()->Update();

	if (Now_scene == Scene_list[0] && KEY_CON->Down(VK_SPACE)) // 게임 시작화면 -> 캐릭터 선택화면
	{
		Now_scene = Scene_list[1];

		Now_sound->Stop();
		Now_sound = Sound_list[1];
		Now_sound->Play();
	}

	if (Now_scene == Scene_list[1] && mouse_click_pos.x > 260.0f && mouse_click_pos.x < 410 && mouse_click_pos.y < 535 && mouse_click_pos.y > 185)
	// 캐릭터 선택화면 -> 마을 (남자선택)
	{
		gender = true;
		Now_scene = Scene_list[2];

		Now_sound->Stop();
		Now_sound = Sound_list[2];
		Now_sound->Play();
	}
	if (Now_scene == Scene_list[1] && mouse_click_pos.x > 865.0f && mouse_click_pos.x < 1015 && mouse_click_pos.y < 535 && mouse_click_pos.y > 185)
	// 캐릭터 선택화면 -> 마을 (여자선택)
	{
		gender = false;
		Now_scene = Scene_list[2];

		Now_sound->Stop();
		Now_sound = Sound_list[2];
		Now_sound->Play();
	}

	if (Now_scene == Scene_list[2] && is_vsPokemon) // 마을 -> 포켓몬과 전투
	{
		Now_scene = Scene_list[3];

		Now_sound->Stop();
		Now_sound = Sound_list[3];
		Now_sound->Play();
	}
	if (Now_scene == Scene_list[3] && clear_vsPokemon) // 포켓몬과 전투를 끝내면 마을로 복귀
	{
		Now_scene = Scene_list[2];

		Now_sound->Stop();
		Now_sound = Sound_list[2];
		Now_sound->Play();
	}

	if (Now_scene == Scene_list[2] && is_vsChampion) // 마을 -> 챔피언과 전투
	{
		Now_scene = Scene_list[4];

		Now_sound->Stop();
		Now_sound = Sound_list[4];
		Now_sound->Play();
	}
	if (Now_scene == Scene_list[4] && clear_vsChampion) // 챔피언과 전투를 끝내면 마을로 복귀
	{
		Now_scene = Scene_list[2];

		Now_sound->Stop();
		Now_sound = Sound_list[2];
		Now_sound->Play();
	}

	// 밑에는 빠른 작업을 위한 코드
	
	if (KEY_CON->Down('R')) 
	{
		cursor++;
		Now_scene = Scene_list[cursor];
	}

	Now_scene->Update();
	Now_sound->Update();
}

void Program::CreateSamplerState()
{
	D3D11_SAMPLER_DESC desc = {};
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	desc.MinLOD = 0;
	desc.MaxLOD = D3D11_FLOAT32_MAX;

	DEVICE->CreateSamplerState(&desc, &samplerState);

	DVC->PSSetSamplers(0, 1, &samplerState);
}

void Program::CreateBlendState()
{
	D3D11_BLEND_DESC desc = {};
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	DEVICE->CreateBlendState(&desc, &blendState);

	float blendFactor[] = { 0, 0, 0, 0 };
	DVC->OMSetBlendState(blendState, blendFactor, 0xffffffff);
}

void Program::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC desc = {};
	desc.CullMode = D3D11_CULL_NONE;
	desc.FillMode = D3D11_FILL_SOLID;

	DEVICE->CreateRasterizerState(&desc, &rasterizerState);

	DVC->RSSetState(rasterizerState);
}

Program::~Program()
{
	delete view;
	delete projection;

	for (auto s : Scene_list)
		delete s;
	for (auto s : Sound_list)
		delete s;

	Scene_list.clear();
	Sound_list.clear();

	delete Now_scene;
	delete Now_sound;
	
	Sound::Release();
}

void Program::Render()
{
	Device::Get()->Clear();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	ImGui::Text(fps.c_str());
	ImGui::Text("Total Run Time : %f", Timer::Get()->GetRunTime());
	ImGui::Text("Gender : %s (True : Boy, False : Girl)", gender ? "true" : "false");
	//ImGui::Text("is Pokemon : %s", is_vsPokemon ? "true" : "false");
	//ImGui::Text("Clear Pokemon : %s", clear_vsPokemon ? "true" : "false");

	Now_scene->Render();
	Now_scene->PostRender();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	
	Device::Get()->Present();
}

void Program::Create()
{
	Device::Get();
	Control::Get();
	Timer::Get();

	CreateProjection();
	CreateSamplerState();
	CreateBlendState();
	CreateRasterizerState();

	ImGui::CreateContext(); 
	ImGui::StyleColorsDark(); 
	ImGui_ImplDX11_Init(DEVICE, DVC);
	ImGui_ImplWin32_Init(hWnd);
}

void Program::CreateProjection()
{
	view = new MatrixBuffer();
	projection = new MatrixBuffer();

	Matrix orthographic = XMMatrixOrthographicOffCenterLH
	(
		0.0f, (float)WIN_WIDTH,
		(float)WIN_HEIGHT, 0.0f, 
		-1.0f, 1.0f
	);

	projection->Set(orthographic); 
	view->SetVS(1);
	projection->SetVS(2);
}

void Program::Delete()
{
	Device::Delete();
	Control::Delete();
	Timer::Delete();
}
