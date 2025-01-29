cbuffer Color : register(b0)
{
	float4 color;
}


struct PixelInput
{
	float4 position : SV_Position;
	float4 uv : UV;
};

SamplerState samp : register(s0);
Texture2D map : register(t0);

float4 PS(PixelInput input) : SV_TARGET
{
	return map.Sample(samp, input.uv) * color;
	
}