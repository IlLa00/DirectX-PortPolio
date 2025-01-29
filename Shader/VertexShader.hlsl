
struct VertexInput
{
	float4 pos : POSITION;
	float4 color : COLOR;
};

struct PixelInput
{
	float4 position : SV_Position;
	float4 color : COLOR;
};

PixelInput VS(VertexInput input)
{
	PixelInput output;
	output.position = input.pos;
	output.color = input.color;
	
	return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
	return input.color;
}
