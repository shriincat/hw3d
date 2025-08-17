cbuffer CBuf
{
	float res;
	float r;
	float centerX;
	float centerY;
};

float4 main( float4 pos : SV_Position ) : SV_Target
{
	return float4(pos.x, pos.y, 0, 1);
}