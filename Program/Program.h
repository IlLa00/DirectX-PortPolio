#pragma once
class Program
{
private:
	vector<Scene*>Scene_list;
	Scene* Now_scene;
	UINT cursor;

	vector<Sound*>Sound_list;
	Sound* Now_sound;

	MatrixBuffer* view;
	MatrixBuffer* projection;

	ID3D11SamplerState* samplerState;
	ID3D11BlendState* blendState;
	ID3D11RasterizerState* rasterizerState;

	void CreateProjection();
	void CreateSamplerState();
	void CreateBlendState();
	void CreateRasterizerState();

public:
	Program();
	~Program();

	void Update();
	void Render();
	void Create();
	void Delete();
};