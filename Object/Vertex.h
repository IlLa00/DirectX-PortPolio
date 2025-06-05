#pragma once
struct Vertex

{
	Float3 position;
	Float4 colour;

	Vertex()
	{
		position = Float3(0, 0, 0);
		colour = Float4(0, 0, 0, 1);
	}
	Vertex(float x, float y, float r, float g, float b)
	{
		position = Float3(x, y, 0);
		colour = Float4(r, g, b, 1);
	}
};

struct VertexUV
{
	Float3 position;
	Float2 uv;

	VertexUV()
	{
		position = Float3(0, 0, 0);
		uv = Float2(0, 0);
	}
	VertexUV(float x, float y, float u, float v)
	{
		position = Float3(x, y, 0);
		uv = Float2(u, v);
	}
};

struct VertexPos 
{
	Float3 position;

	VertexPos()
	{
		position = Float3(0, 0, 0);
	}
	VertexPos(float x, float y)
	{
		position = Float3(x, y, 0);
	}
};


static float ratio_pos_x(int pos_x)
{
	float ratio = ((float)pos_x - WIN_CENTER_X) / (float)WIN_CENTER_X;

	return ratio;
}

static float ratio_pos_y(int pos_y)
{
	float ratio = -((float)pos_y - WIN_CENTER_Y) / (float)WIN_CENTER_Y;

	return ratio;
}
