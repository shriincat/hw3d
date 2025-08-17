#include "PixelCBuf.h"

PixelCBuf::PixelCBuf(Graphics& gfx, const Quad& parent)
	:
	parent(parent)
{
	if (!pPcbuf)
	{
		pPcbuf = std::make_unique<PixelConstantBuffer<DirectX::XMVECTOR>>(gfx, parent.GetTransformXM());
	}
}

void PixelCBuf::Bind(Graphics& gfx) noexcept
{
	pPcbuf->Update(gfx, parent.GetTransformXM());
	pPcbuf->Bind(gfx);
}

std::unique_ptr<PixelConstantBuffer<DirectX::XMVECTOR>> PixelCBuf::pPcbuf;