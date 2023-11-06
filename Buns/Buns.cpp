#include "Buns.h"

#include"../Collider/CollisionManager.h";

Buns::Buns(Input* Input)
{
    assert(Input);
    this->input = Input;
}

void Buns::BunsInitialize(bool Frag)
{
    //OldPosition = position;
    if (Frag == true)
    {
        Upflag = Frag;
    }
    
}

void Buns::BunsUpdate()
{

    if (input->TriggerKey(DIK_SPACE)&&Push==false)
    {
        Push = true;
    }

    if (Push == true)
    {
        upVel.m128_f32[1] = 0.1f;
        downVel.m128_f32[1] = -0.1f;

        if (Upflag == true)
        {
            Velocity = upVel;
        }
        else
        {
            Velocity = downVel;
        }
    }
    else
    {
       // OldPosition = position;
    }

    if (Reverse == true)
    {
         float Quely = -1.0f;
         Velocity *= Quely;

         if (position.x == OldPosition.x && position.y == OldPosition.y)
         {
             Velocity.m128_f32[1] = 0.0f;
             Reverse = false;
         }
    }

    MoveVector(Velocity);
}

void Buns::OnCollision(const CollisionInfo& info)
{
   // position = OldPosition;

    Reverse = true;

   // float Quely = -1.0f;
   // Velocity *= Quely;

   // MoveVector(Velocity);

    //Update();
}
