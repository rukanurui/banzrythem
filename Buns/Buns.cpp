#include "Buns.h"
#include "../Physics.h"
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

    SandTime++;

    if (SandTime > 10)
    {
        Sandwich = false;
        perfect = false;
        SandTime = 0;
    }

    if (EndSand == true)
    {
        Sandwich = false;
        perfect = false;
        SandTime = 0;
    }

    //パッドのポインタ
    pad* pad_ = nullptr;
    pad_ = new pad();

    //パッドの更新
    pad_->Update();

    float dx_pad = 0;
    float dz_pad = 0;

  
    downVel.m128_f32[0] = 0;
    downVel.m128_f32[1] = 0;

    upVel.m128_f32[0] = 0;
    upVel.m128_f32[1] = 0;

    if ((pad_->state.Gamepad.sThumbLX != 0 || pad_->state.Gamepad.sThumbLY != 0)&&Upflag==false)
    {
      //  dx_pad = static_cast<FLOAT>(pad_->state.Gamepad.sThumbLX / 32767.0 * (0.1f));
      //  dz_pad = static_cast<FLOAT>(pad_->state.Gamepad.sThumbLY / 32767.0 * (0.1f));

        downVel.m128_f32[0] =  (static_cast<FLOAT>(pad_->state.Gamepad.sThumbLX / 32767.0 * (0.4f)));
        downVel.m128_f32[1] =  (static_cast<FLOAT>(pad_->state.Gamepad.sThumbLY / 32767.0 * (0.4f)));

        Push = true;
    }
    else  if ((pad_->state.Gamepad.sThumbLX == 0 && pad_->state.Gamepad.sThumbLY == 0)&& Upflag == false)
    {
        if (Push == true)
        {
            position = OldPosition;
            Push = false;
        }
        else
        {
            if (pad_->iPad_leftshoulder == 1)
            {
                circle_time -= 1;
            }

            if (pad_->iPad_rightshoulder == 1)
            {
                circle_time += 1;
            }
            /*自機の円動き関数*/
            position.x = sin(circle_time * 0.07) * 2.5f + 0.0f;
            position.y = cos(circle_time * 0.07) * 2.5f + 3.5f;
        }
        OldPosition = position;
    }
    

    if ((pad_->state.Gamepad.sThumbRX != 0 || pad_->state.Gamepad.sThumbRY != 0) && Upflag == true)
    {
        upVel.m128_f32[0] = (static_cast<FLOAT>(pad_->state.Gamepad.sThumbRX / 32767.0 * (0.4f)));
        upVel.m128_f32[1] = (static_cast<FLOAT>(pad_->state.Gamepad.sThumbRY / 32767.0 * (0.4f)));

        Push = true;
    }
    else  if ((pad_->state.Gamepad.sThumbRX == 0 && pad_->state.Gamepad.sThumbRY == 0) && Upflag == true)
    {
        if (Push == true)
        {
            position = OldPosition;
            Push = false;
        }
        else
        {
            if (pad_->iPad_leftshoulder == 1 )
            {
                circle_time -= 1;
            }

            if (pad_->iPad_rightshoulder == 1)
            {
                circle_time += 1;
            }
            /*自機の円動き関数*/
            position.x = sin(9.4+circle_time * 0.07) * 2.5f + 0.0f;
            position.y = cos(9.4+circle_time * 0.07) * 2.5f + 3.5f;
        }
        OldPosition = position;
    }


    if (Upflag == true)
    {
        Velocity = upVel;
    }
    else
    {
        Velocity = downVel;
    }
    XMFLOAT2 Vector;

    Vector.x = position .x+ Velocity.m128_f32[0];
    Vector.y = position. y+ Velocity.m128_f32[1];

    //atanで銃身を向ける方向を算出
    rotation.z = atan2(Vector.x-position.x, Vector.y - position.y) * -60;

    if (Upflag == true)
    {
        rotation.z = rotation.z - 180.0f;
    }

    float error_ = 3.0f;
    if ((position.x >= OldPosition.x + error_ || position.x <= OldPosition.x - error_)
        || (position.y >= OldPosition.y + error_ || position.y <= OldPosition.y - error_))
    {
        Velocity = { 0.0f,0.0f,0.0f };
    }

    SandAttribute = 0;

    
    MoveVector(Velocity);


}

void Buns::OnCollision(const CollisionInfo& info)
{
    float Halfhalf = 90.0f;
    float error = 50.0f;
    float perfect_e = 20.0f;

    if (Upflag == true)
    {

        if (info.collider->color == 2 && info.object->GetCanGetFlag() == true)
        {

            IngredientsRotation = info.object->GetRotation();


            if (rotation.z+180.0f +error>= IngredientsRotation.z && rotation.z + 180.0f -error  <= IngredientsRotation.z)
            {
                SandAttribute = 1;
                Sandwich = true;

                     if (rotation.z + 180.0f + perfect_e >= IngredientsRotation.z && rotation.z + 180.0f - perfect_e <= IngredientsRotation.z)
                {
                    perfect = true;
                }
            }
        }
        else  if (info.collider->color == 4 && info.object->GetCanGetFlag() == true)
        {

            IngredientsRotation = info.object->GetRotation();

            if (rotation.z + 180.0f + error >= IngredientsRotation.z && rotation.z + 180.0f - error <= IngredientsRotation.z)
            {
                SandAttribute = 2;
                Sandwich = true;

                if (rotation.z + 180.0f + perfect_e >= IngredientsRotation.z && rotation.z + 180.0f - perfect_e <= IngredientsRotation.z)
                {
                    perfect = true;
                }
            }
        }
        else if (info.collider->color == 8 && info.object->GetCanGetFlag() == true)
        {

            IngredientsRotation = info.object->GetRotation();

            if (rotation.z + 180.0f + error >= IngredientsRotation.z && rotation.z + 180.0f - error <= IngredientsRotation.z)
            {
                SandAttribute = 3;
                Sandwich = true;

                if (rotation.z + 180.0f + perfect_e >= IngredientsRotation.z && rotation.z + 180.0f - perfect_e <= IngredientsRotation.z)
                {
                    perfect = true;
                }
            }
        }
        else if (info.collider->color == 16 && info.object->GetCanGetFlag() == true)
        {

            IngredientsRotation = info.object->GetRotation();

            if (rotation.z + 180.0f + error >= IngredientsRotation.z && rotation.z + 180.0f - error <= IngredientsRotation.z)
            {
                SandAttribute = 4;
                Sandwich = true;
                if (rotation.z + 180.0f + perfect_e >= IngredientsRotation.z && rotation.z + 180.0f - perfect_e <= IngredientsRotation.z)
                {
                    perfect = true;
                }
            }
        }
        else  if (info.collider->color == 32 && info.object->GetCanGetFlag() == true)
        {

            IngredientsRotation = info.object->GetRotation();

            if (rotation.z + 180.0f + error >= IngredientsRotation.z && rotation.z + 180.0f - error <= IngredientsRotation.z)
            {
                SandAttribute = 5;
                Sandwich = true;
                if (rotation.z + 180.0f + perfect_e >= IngredientsRotation.z && rotation.z + 180.0f - perfect_e <= IngredientsRotation.z)
                {
                    perfect = true;
                }
            }
        }
        else  if (info.collider->color == 64 && info.object->GetCanGetFlag() == true)
        {

            IngredientsRotation = info.object->GetRotation();

            if (rotation.z + 180.0f + error >= IngredientsRotation.z && rotation.z + 180.0f - error <= IngredientsRotation.z)
            {
                SandAttribute = 6;
                Sandwich = true;
                if (rotation.z + 180.0f + perfect_e >= IngredientsRotation.z && rotation.z + 180.0f - perfect_e <= IngredientsRotation.z)
                {
                    perfect = true;
                }
            }
        }
    }
    else if (Upflag == false)
    {
        if (info.collider->color == 2 && info.object->GetCanGetFlag() == true)
        {

            IngredientsRotation = info.object->GetRotation();

            if (rotation.z+error-180>= IngredientsRotation.z && rotation.z-error-180  <= IngredientsRotation.z)
            {
                SandAttribute = 1;
                Sandwich = true;
                if (rotation.z + perfect_e - 180 >= IngredientsRotation.z && rotation.z - perfect_e - 180 <= IngredientsRotation.z)
                {
                    perfect = true;
                }
            }
        }
        else  if (info.collider->color == 4 && info.object->GetCanGetFlag() == true)
        {

            IngredientsRotation = info.object->GetRotation();

            if (rotation.z + error - 180 >= IngredientsRotation.z && rotation.z - error - 180 <= IngredientsRotation.z)
            {
                SandAttribute = 2;
                Sandwich = true;
                if (rotation.z + perfect_e - 180 >= IngredientsRotation.z && rotation.z - perfect_e - 180 <= IngredientsRotation.z)
                {
                    perfect = true;
                }
            }
        }
        else if (info.collider->color == 8 && info.object->GetCanGetFlag() == true)
        {

            IngredientsRotation = info.object->GetRotation();

            if (rotation.z + error - 180 >= IngredientsRotation.z && rotation.z - error - 180 <= IngredientsRotation.z)
            {
                SandAttribute = 3;
                Sandwich = true;
                if (rotation.z + perfect_e - 180 >= IngredientsRotation.z && rotation.z - perfect_e - 180 <= IngredientsRotation.z)
                {
                    perfect = true;
                }
            }
        }
        else if (info.collider->color == 16 && info.object->GetCanGetFlag() == true)
        {

            IngredientsRotation = info.object->GetRotation();

            if (rotation.z + error - 180 >= IngredientsRotation.z && rotation.z - error - 180 <= IngredientsRotation.z)
            {
                SandAttribute = 4;
                Sandwich = true;
                if (rotation.z + perfect_e - 180 >= IngredientsRotation.z && rotation.z - perfect_e - 180 <= IngredientsRotation.z)
                {
                    perfect = true;
                }
            }
        }
        else  if (info.collider->color == 32 && info.object->GetCanGetFlag() == true)
        {

            IngredientsRotation = info.object->GetRotation();

            if (rotation.z + error - 180 >= IngredientsRotation.z && rotation.z - error - 180 <= IngredientsRotation.z)
            {
                SandAttribute = 5;
                Sandwich = true;
                if (rotation.z + perfect_e - 180 >= IngredientsRotation.z && rotation.z - perfect_e - 180 <= IngredientsRotation.z)
                {
                    perfect = true;
                }
            }
        }
        else  if (info.collider->color == 64 && info.object->GetCanGetFlag() == true)
        {

            IngredientsRotation = info.object->GetRotation();

            if (rotation.z + error - 180 >= IngredientsRotation.z && rotation.z - error - 180 <= IngredientsRotation.z)
            {
                SandAttribute = 6;
                Sandwich = true;
                if (rotation.z + perfect_e - 180 >= IngredientsRotation.z && rotation.z - perfect_e - 180 <= IngredientsRotation.z)
                {
                    perfect = true;
                }
            }
        }
    }
   
}

void Buns::BunsCollisionColorSet()
{
    collider->SetColor(COLLISION_COLOR_BUNS);
}
