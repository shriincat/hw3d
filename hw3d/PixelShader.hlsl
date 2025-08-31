cbuffer CBuf
{
	float res;
	float radius;
	float centerX;
	float centerY;
};

float3 distance_from_sphere(float3 p, float3 c, float r)
{
	return length(p - c) - r;
}

float map_the_world(float3 p)
{
	float displacement = sin(5.0 * p.x) * sin(5.0 * p.y) * sin(5.0 * p.z) * 0.25;
	float sphere_0 = distance_from_sphere(p, float3(0.0, 0.0, 0.0), 1.0);

	return sphere_0 + displacement;
}

float3 calculate_normal(float3 p)
{
	const float3 small_step = float3(0.001, 0.0, 0.0);

	float gradient_x = map_the_world(p + small_step.xyy) - map_the_world(p - small_step.xyy);
	float gradient_y = map_the_world(p + small_step.yxy) - map_the_world(p - small_step.yxy);
	float gradient_z = map_the_world(p + small_step.yyx) - map_the_world(p - small_step.yyx);

	float3 normal = float3(gradient_x, gradient_y, gradient_z);

	return normalize(normal);
}


float3 ray_march(float3 ro, float3 rd)
{
	float total_distance_traveled = 0.0;
	const int NUMBER_OF_STEPS = 32;
	const float MINIMUM_HIT_DISTANCE = 0.001;
	const float MAXIMUM_TRACE_DISTANCE = 1000.0;

	for (int i = 0; i < NUMBER_OF_STEPS; ++i)
	{
		float3 current_position = ro + total_distance_traveled * rd;

		float distance_to_closest = map_the_world(current_position);

		if (distance_to_closest < MINIMUM_HIT_DISTANCE)
		{
			float3 normal = calculate_normal(current_position);
			float3 light_position = float3(2.0, 5.0, 3.0);
			float3 direction_to_light = normalize(current_position - light_position);

			float diffuse_intensity = max(0.0, dot(normal, direction_to_light));

			return float3(1.0, 0.0, 0.0) * diffuse_intensity;
		}

		if (total_distance_traveled > MAXIMUM_TRACE_DISTANCE)
		{
			break;
		}
		total_distance_traveled += distance_to_closest;
	}
	return float3(0.0, 0.0, 0.0);
}

float4 main(float4 pos : SV_Position) : SV_Target
{
	float halfRes = res * 0.5f;
	float2 uv = float2((pos.x - halfRes) / halfRes, (pos.y - halfRes) / halfRes);

	float3 camera_position = float3(0.0, 0.0, -5);
	float3 ro = camera_position;
	float3 rd = float3(uv, 1.0);

	float3 shaded_color = ray_march(ro, rd);

	return float4(shaded_color, 1.0);
}