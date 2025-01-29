#pragma once

class Frame
{
private:
	vector<VertexUV> vertices; 
	vector<UINT> indices; 

	VertexBuffer* VB;
	IndexBuffer* IB;
	
	Texture* texture;

	Vector2 frame_size;

public:
	Frame(wstring file, Vector2 startUV = Vector2(0, 0), Vector2 endUV = Vector2(1, 1));
	Frame(wstring file, float x, float y, float w, float h);
	~Frame();

	void Render();

	Vector2 Size() { return texture->GetSize(); }
	Vector2 GetFrameSize() { return frame_size; }
	Vector2 GetFrameOrigSize() { return frame_size * texture->GetSize(); }

};