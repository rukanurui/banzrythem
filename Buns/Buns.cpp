#include "Buns.h"

#include"../Collider/CollisionManager.h";

Buns::Buns(Input* Input)
{
    assert(Input);
    this->input = Input;
}

void Buns::BunsInitialize(bool Frag)
{
    if (Frag == true)
    {
        Upflag = Frag;
    }
    
}

void Buns::BunsUpdate()
{

    if (input->TriggerKey(DIK_SPACE))
    {
        upVel.m128_f32[1] = 0.1f;
        downVel.m128_f32[1] = -0.1f;
    }

    if (Upflag == true)
    {
        Velocity = upVel;
    }
    else
    {
        Velocity = downVel;
    }

    MoveVector(Velocity);

    

}

void Buns::OnCollision(const CollisionInfo& info)
{

    float Quely = -1.0f;
    Velocity *= Quely;

    MoveVector(Velocity);

    Update();
}
