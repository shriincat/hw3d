#pragma once
#include "DrawableBase.h"
#include "DirectXMath.h""

class Quad : public DrawableBase<Quad>
{
public:
	Quad(Graphics& gfx);
	void Update(float dt) noexcept override;
	void SetViewCenter(float centerX, float centerY);
	void SetViewRadius(float radius);
	float GetRadius() const noexcept;
	float GetCenterX() const noexcept;
	float GetCenterY() const noexcept;
	DirectX::XMVECTOR GetTransformXM() const noexcept override;
private:
	float radius;
	float centerX;
	float centerY;
};