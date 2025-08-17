#pragma once
#include "DrawableBase.h"

class Quad : public DrawableBase<Quad>
{
public:
	Quad(Graphics& gfx);
	void Update(float dt) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
private:
	float radius = 2.0f;
	float centerX = 0.0f;
	float centerY = 0.0f;
};