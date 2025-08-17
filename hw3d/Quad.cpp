#include "Quad.h"
#include "BindableBase.h"
#include "GraphicsThrowMacros.h"

Quad::Quad(Graphics& gfx)
{
	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			struct
			{
				float x;
				float y;
			} pos;
		};
		const std::vector<Vertex> vertices =
		{
			{ -1.0f,-1.0f },
			{ 1.0f,-1.0f },
			{ -1.0f,1.0f },
			{ 1.0f,1.0f }
		};
		AddStaticBind(std::make_unique<VertexBuffer>(gfx, vertices));

		auto pvs = std::make_unique<VertexShader>(gfx, L"VertexShader.cso");
		auto pvsbc = pvs->GetBytecode();
		AddStaticBind(std::move(pvs));

		AddStaticBind(std::make_unique<PixelShader>(gfx, L"PixelShader.cso"));

		const std::vector<unsigned short> indices =
		{
			1,0,2, 3,1,2
		};
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, indices));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

		AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		SetIndexFromStatic();
	}

	AddBind(std::make_unique<PixelCBuf>(gfx, *this));
}

void Quad::Update(float dt) noexcept
{
}

void Quad::SetViewCenter(float centerX, float centerY)
{
	this->centerX = centerX;
	this->centerY = centerY;
}

void Quad::SetViewRadius(float radius) 
{
	this->radius = radius;
}

float Quad::GetRadius() const noexcept
{
	return radius;
}

float Quad::GetCenterX() const noexcept
{
	return centerX;
}

float Quad::GetCenterY() const noexcept
{
	return centerY;
}

DirectX::XMVECTOR Quad::GetTransformXM() const noexcept
{
	return DirectX::XMVectorSet(1080, radius, centerX, centerY); // not performing any vertex transformations, but must ovveride virtual function
}