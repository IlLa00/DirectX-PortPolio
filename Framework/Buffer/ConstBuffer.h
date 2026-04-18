#pragma once

class ConstBuffer
{
private:
	ID3D11Buffer* buffer = nullptr;

	void* data;

	UINT data_size;

public:
	ConstBuffer(void* data, UINT data_size);
	~ConstBuffer();

	void SetVS(UINT slot);
	void SetPS(UINT slot);
};