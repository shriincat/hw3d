cbuffer CBuf
{
	float res;
	float radius;
	float centerX;
	float centerY;
};

float4 main(float4 pos : SV_Position) : SV_Target
{
	float halfRes = res * 0.5f;
	double2 c =
	{
		((((double) pos.x - halfRes)) / halfRes) * radius + centerX,
		-(((double) pos.y - halfRes) / halfRes) * radius + centerY};
	double2 z = { 0.0, 0.0 };

	int i;
	int max = 120;
	for (i = 0; i < max; i++)
	{
		double x = (z.x * z.x - z.y * z.y);
		double y = (z.x * z.y + z.y * z.x);
		z.x = x;
		z.y = y;
		z += c;
		if (z.x * z.x + z.y * z.y > 2 * 2)
		{
			break;
		}
	}
	if (i == max)
	{
		return float4(0, 0, 0, 1);
	}
	else
	{
		float3 colors[12] =
		{
			{ 1, 0, 0 },
			{ 1, 0.5f, 0 },
			{ 1, 1, 0 },
			{ 0.5f, 1, 0 },
			{ 0, 1, 0 },
			{ 0, 1, 0.5f },
			{ 0, 1, 1 },
			{ 1, 0.5f, 1 },
			{ 1, 0, 1 },
			{ 0.5f, 0, 1 },
			{ 1, 0, 1 },
			{ 1, 0, 0.5f },
		};
		float idx = (((float) i / max) * 12);
		int idx1 = floor(idx);
		int idx2 = (idx1 + 1) % 12;
		float3 c1 = colors[idx1];
		float3 c2 = colors[idx2];
		float t = idx - idx1;
		float r = lerp(c1.r, c2.r, t);
		float g = lerp(c1.g, c2.g, t);
		float b = lerp(c1.b, c2.b, t);
		return float4(r, g, b, 1);
	}
}