#pragma once
class Program
{
private:
	vector<unique_ptr<Scene>> scene_list;
	Scene* Now_scene;

	vector<unique_ptr<Sound>> sound_list;
	Sound* Now_sound;

	unique_ptr<MatrixBuffer> view;
	unique_ptr<MatrixBuffer> projection;

	ID3D11SamplerState* samplerState;
	ID3D11BlendState* blendState;
	ID3D11RasterizerState* rasterizerState;

	void CreateProjection();
	void CreateSamplerState();
	void CreateBlendState();
	void CreateRasterizerState();
	void TransitionTo(SceneID id);

public:
	Program();
	~Program();

	void Update();
	void Render();
	void Create();
	void Delete();
};