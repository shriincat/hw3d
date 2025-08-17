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
			0,1,2, 1,3,2
		};
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, indices));

		struct ConstantBuffer
		{
			struct
			{
				float resolution;
				float radius;
				float centerX;
				float centerY;
			} data;
		};
		const ConstantBuffer cb =
		{
			{
				1080,
				radius,
				centerX,
				centerY
			}
		};
		AddStaticBind(std::make_unique<PixelConstantBuffer<ConstantBuffer>>(gfx, cb));

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

	// AddBind(std::make_unique<TransformCbuf>(gfx, *this)); // replace with pixelCbuf
}

void Quad::Update(float dt) noexcept
{
	// copy update code from shadertoy branch's App function here?
}

DirectX::XMMATRIX Quad::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixIdentity(); // not performing any vertex transformations, but must ovveride virtual function
}