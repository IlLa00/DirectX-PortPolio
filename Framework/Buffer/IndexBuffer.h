#pragma once
class IndexBuffer
{
private:
	ID3D11Buffer* buffer = nullptr;

public:
	IndexBuffer(void* data, UINT count);
	~IndexBuffer();

	void Set();
};