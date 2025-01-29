#pragma once

class MatrixBuffer : public ConstBuffer
{
private:
	struct Data
	{
		Matrix matrix;
	} data;

public:
	MatrixBuffer() : ConstBuffer(&data, sizeof(data))
	{
		data.matrix = XMMatrixIdentity();
	}

	void Set(Matrix value)
	{
		data.matrix = XMMatrixTranspose(value);
	}

};

class ColourBuffer : public ConstBuffer
{
public:
	struct Data
	{
		Float4 colour;
	} data;

	ColourBuffer() : ConstBuffer(&data, sizeof(data))
	{
		data.colour = Float4(1.0f, 1.0f, 1.0f, 1.0f);
	}
};