#pragma once

class VertexShader
{
private:
	ID3D11VertexShader* VS;
	ID3D11InputLayout* input_layout;
	ID3DBlob* vertex_blob;
	ID3D11ShaderReflection* reflection;

	static unordered_map<wstring, VertexShader*> shader_data;

	void CreateInputLayout();
	void CreateInputLayoutByPos();
	UINT type;

public:
	VertexShader(wstring file_loc, UINT type = 0, 
		DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG);
	~VertexShader();

	static VertexShader* GetInstance(wstring file_loc, UINT type = 0);
	static void Delete();

	void Release();
	ID3D11InputLayout* GetInputLayout() { return input_layout; }
	ID3D11VertexShader* GetVertexShader() { return VS; }

	void Set();
};