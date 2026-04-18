#include "framework.h"
#include "Program.h"

Program::Program()
{
	Create();

	scene_list.push_back(make_unique<StartScene>(g_state));
	scene_list.push_back(make_unique<CharactorSelectScene>(g_state));
	scene_list.push_back(make_unique<TownScene>(g_state));
	scene_list.push_back(make_unique<vsPokemonScene>(g_state));
	scene_list.push_back(make_unique<vsChampionScene>(g_state));

	Now_scene = scene_list[0].get();

	Sound::Init();

	sound_list.push_back(make_unique<Sound>("BGM/Pokemon Diamond - Intro - Nintendo DS.mp3", true));
	sound_list.push_back(make_unique<Sound>("BGM/Data_sound_bgm_Introduction.wav", true));
	sound_list.push_back(make_unique<Sound>("BGM/Data_sound_bgm_Lake.wav", true));
	sound_list.push_back(make_unique<Sound>("BGM/206496544D7DC35D18.mp3", true));
	sound_list.push_back(make_unique<Sound>("BGM/17159E4D4D7DC6202B.mp3", true));

	Now_sound = sound_list[0].get();
	Now_sound->Play();

}


void Program::Update()
{
	Control::Get()->Update();
	Timer::Get()->Update();

	SceneID next = Now_scene->GetNextScene();
	if (next != SceneID::None)
		TransitionTo(next);

	Now_scene->Update();
	Now_sound->Update();
}

void Program::TransitionTo(SceneID id)
{
	Now_scene->OnExit();
	Now_scene = scene_list[(int)id].get();
	Now_sound->Stop();
	static const int BGM_MAP[] = { 0, 1, 2, 3, 4 };
	Now_sound = sound_list[BGM_MAP[(int)id]].get();
	Now_sound->Play();
	Now_scene->OnEnter();
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
	ImGui::Text("Gender : %s (True : Boy, False : Girl)", g_state.gender ? "true" : "false");
	//ImGui::Text("is Pokemon : %s", g_state.is_vsPokemon ? "true" : "false");
	//ImGui::Text("Clear Pokemon : %s", g_state.clear_vsPokemon ? "true" : "false");

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
	view = make_unique<MatrixBuffer>();
	projection = make_unique<MatrixBuffer>();

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
