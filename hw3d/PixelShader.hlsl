cbuffer CBuf
{
	float res;
	float radius;
	float centerX;
	float centerY;
};

float4 main(float4 pos : SV_Position) : SV_Target
{
	return float4(sin(pos.x), cos(pos.y), 1, 1);
}