#pragma once
#include "ConstantBuffers.h"
#include "Quad.h"

class PixelCBuf : public Bindable
{
public:
	PixelCBuf(Graphics& gfx, const Quad& parent);
	void Bind(Graphics& gfx) noexcept override;
private:
	static std::unique_ptr<PixelConstantBuffer<DirectX::XMVECTOR>> pPcbuf;
	const Quad& parent;
};