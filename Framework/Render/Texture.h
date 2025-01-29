#pragma once
class Texture
{
private:
	ScratchImage image;
	ID3D11ShaderResourceView* srv;

	static unordered_map<wstring, Texture*> texture_data;

	Texture(ID3D11ShaderResourceView* srv, ScratchImage& image);
	~Texture();

public:

	static Texture* Add(wstring file);

	static void Delete();
	
	Vector2 GetSize();
	void Set(UINT slot = 0);
};