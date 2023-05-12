﻿#include "LightHearHead.h"

LightHairHead::LightHairHead()
{
}

LightHairHead::~LightHairHead()
{
}

void LightHairHead::Init()
{
	lighthairTex = TexManager::LoadTexture("Resources/blackParticleTex.png");

	headObject = std::make_shared<Object3d>();
	hairObject = std::make_shared<Object3d>();

	headObject.reset(NY_Object3DManager::Get()->CreateModel_Box(5.f, 1.f, 1.f, lighthairTex));
	hairObject.reset(NY_Object3DManager::Get()->CreateModel_Box(10.f, 1.f, 1.f, lighthairTex));

	scale = RVector3(1, 1, 1);
	rot = RVector3(0, 0, 0);
	pos.zero();
	headObject->SetAffineParam(scale, rot, pos);
	hairObject->SetAffineParam(scale, rot, pos);
	SlapCount = 0;
	isKramer = false;
	isactive = false;
	ResetFrontEase();
}

void LightHairHead::ResetFrontEase()
{
	FrontStart = pos;
	FrontEnd = { FrontStart.x,FrontStart.y,FrontStart.z - FrontLength };
	isFrontEase = true;
}

void LightHairHead::Update()
{
	//オブジェクト描画位置を設定
	headObject->SetAffineParamTranslate(pos + headOffset);
	hairObject->SetAffineParamTranslate(pos + hairOffset);

	if (isFrontEase)
	{
		if (pos.z <= FrontEnd.z)
		{
			isactive = true;
			isFrontEase = false;
		}
		else
		{
			pos = Rv3Ease::OutQuad(FrontStart, FrontEnd, (float)FrontEaseT);
			FrontEaseT++;
		}
	}

	// 頭が有効化されたら
	if (isactive) 
	{
		if (!isMostFront)
		{
			return;
		}

		//入力を受け付ける
		SlappingMove();

		PullOutHair();
	}
}

void LightHairHead::Draw()
{
	//オブジェクト描画
	headObject->DrawObject();
	if (!isHairDestroy)
	{
		hairObject->DrawObject();
	}
}

void LightHairHead::Finalize()
{
}

void LightHairHead::SlappingMove()
{
	if (!isHairDestroy)
	{
		return;
	}

	//プレイヤーの入力を受け付けたら
	//if(ptr->)
	//{}

	if (isSlap)
	{
		if (isKramer)
		{
			SlapCount++;
			if (SlapCount >= 3)
			{
				isAllMoveFinish = true;
			}
			isSlap = false;
		}
		else
		{
			pos.x -= 0.5f;
			if (pos.x < -3)
			{
				isAllMoveFinish = true;
			}
		}
	}

	if (Input::isXpadButtonPushTrigger(XPAD_BUTTON_A))
	{
		isSlap = true;
	}
}

void LightHairHead::PullOutHair()
{
	if (isHairDestroy)
	{
		return;
	}

	//プレイヤーの入力を受け付けたら
	//if(ptr->)
	//{
	//}

	if (Input::isXpadButtonPushTrigger(XPAD_BUTTON_A))
	{
		isHairDestroy = true;
	}
}
