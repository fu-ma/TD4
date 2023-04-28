#include "AfroHead.h"

#include <Raki_Input.h>

AfroHead::AfroHead()
{
	headOffset = RVector3(0, 10.f, 0);
	hearOffset = RVector3(0, 20.0f, 0);
}

AfroHead::~AfroHead()
{
}

void AfroHead::Init()
{
	afroheadTex = TexManager::LoadTexture("Resources/blackParticleTex.png");

	headObject = std::make_shared<Object3d>();
	afroObject = std::make_shared<Object3d>();

	headObject.reset(NY_Object3DManager::Get()->CreateModel_Box(5.f, 1.f, 1.f, afroheadTex));
	afroObject.reset(NY_Object3DManager::Get()->CreateModel_Box(10.f, 1.f, 1.f, afroheadTex));

	scale = RVector3(1, 1, 1);
	rot = RVector3(0, 0, 0);
	pos.zero();
	headObject->SetAffineParam(scale, rot, pos);
	afroObject->SetAffineParam(scale, rot, pos);
}

void AfroHead::Update()
{
	// �����L�������ꂽ��
	if (isactive) {
		//���͂��󂯕t����

	}


	//�I�u�W�F�N�g�`��ʒu��ݒ�
	headObject->SetAffineParamTranslate(pos + headOffset);
	afroObject->SetAffineParamTranslate(pos + hearOffset);
}

void AfroHead::Draw()
{
	//�I�u�W�F�N�g�`��
	headObject->DrawObject();
	afroObject->DrawObject();
}

void AfroHead::Finalize()
{



}