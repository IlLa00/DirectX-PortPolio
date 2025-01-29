#include "framework.h"

unordered_map<wstring, Texture*> Texture::texture_data;

Texture::Texture(ID3D11ShaderResourceView* srv, ScratchImage& image)
	: srv(srv), image(move(image))
{
}

Texture::~Texture()
{
	srv->Release();
}

Texture* Texture::Add(wstring file)
{
	if (texture_data.count(file) > 0)
		return texture_data[file];

	ScratchImage img;
	ID3D11ShaderResourceView* srv;

	LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, img);

	CreateShaderResourceView(DEVICE, img.GetImages(), img.GetImageCount(), img.GetMetadata(), &srv);

	Texture* t = new Texture(srv, img);

	texture_data[file] = t;

	return t;
}

void Texture::Delete()
{
	for (auto t : texture_data)
	{
		delete t.second;
	}
}

Vector2 Texture::GetSize()
{
	return Vector2(image.GetMetadata().width, image.GetMetadata().height);
}

void Texture::Set(UINT slot)
{
	DVC->PSSetShaderResources(slot, 1, &srv);
}
