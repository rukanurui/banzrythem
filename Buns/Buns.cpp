#include "Buns.h"

void Buns::BunsInitialize()
{
}

void Buns::BunsUpdate()
{

    if (input->TriggerKey(DIK_SPACE))
    {
        upVel.m128_f32[1] = -0.1f;
        downVel.m128_f32[1] = 0.1f;

    }
}

void Buns::Draw()
{
}

void Buns::OnCollision(const CollisionInfo& info)
{
}
