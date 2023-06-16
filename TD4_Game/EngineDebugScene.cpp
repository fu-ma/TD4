#include "EngineDebugScene.h"

#include <Raki_imguiMgr.h>
#include <DirectionalLight.h>

#include <FbxLoader.h>

using namespace Rv3Ease;

EngineDebugScene::EngineDebugScene(ISceneChanger* changer)
{
	UINT testTex = TexManager::LoadTexture("Resources/asp3.png");

	testobject = std::make_shared<Object3d>();
	testobject.reset(NY_Object3DManager::Get()->CreateModel_Box(10.f, 1.f, 1.f, testTex));
	testobject->SetAffineParam(RVector3(5, 5, 5), RVector3(0, 0, 0), RVector3(0, 0, 0));
	testEase.Init(RV3_EASE_TYPE::EASE_CUBIC_INOUT, RVector3(0, 0, 0),
		RVector3(0, 50, 0), 30);

	testsp1.Create(testTex);
	testsp2.Create(testTex);

	testFBX_YesBone = std::make_shared<Object3d>();
	testFBX_YesBone.reset(LoadModel_FBXFile("SpiralPBR"));
	testFBX_YesBone->SetAffineParam(RVector3(20.f, 20.f, 20.f), RVector3(90, 0, 0), RVector3(75.f, 0, -50.f));

	testFBX_NoBone = std::make_shared<Object3d>();
	std::shared_ptr<fbxModel> testModel = std::make_shared<fbxModel>();
	testModel.reset(FbxLoader::GetInstance()->LoadFBXFile("hage_1"));
	testFBX_NoBone.reset(SetModel_FBX(testModel));
	testFBX_NoBone->SetAffineParam(RVector3(0.1f, 0.1f, 0.1f), RVector3(90, 0, 0), RVector3(0, 0, -50.0f));
	testFBX_NoBone->PlayAnimation(ANIMATION_PLAYMODE::ANIM_MODE_ROOP);

	testobj = std::make_shared<Object3d>();
	testobj.reset(SetModel_FBX(testModel));
	testobj->SetAffineParam(RVector3(0.1f, 0.1f, 0.1f), RVector3(90, 0, 0), RVector3(-75.f, 0, -50.f));
	testobj->PlayAnimation(ANIMATION_PLAYMODE::ANIM_MODE_ROOP, 1);

	RVector3 eye(0.f, 0.f, -200.f);
	RVector3 target(0.f, 0.f, 0.f);
	RVector3 up(0.f, 1.f, 0.f);
	NY_Camera::Get()->SetViewStatusEyeTargetUp(eye, target, up);

	//音ロード
	testSE = Audio::LoadSound_wav("Resources/don.wav");
	testBGM = Audio::LoadSound_wav("Resources/kari.wav");

	testNum.CreateAndSetDivisionUVOffsets(10, 10, 1, 64, 64, TexManager::LoadTexture("Resources/Score.png"));

	//無限ループ
	Audio::SetPlayRoopmode(testBGM, 255);

	q1 = quaternion(1, 2, 3, 4);
	q2 = quaternion(2, 3, 4, 1);

	q1 *= q2;

	lightdir = RVector3(0, 0, 1);
}

EngineDebugScene::~EngineDebugScene()
{
}

void EngineDebugScene::Initialize()
{
	testcam.Init(RVector3(0, 0, 0), RVector3(0, 0, 1), RVector3(0, 1, 0));
}

void EngineDebugScene::Finalize()
{
}

void EngineDebugScene::Update()
{
	if (Input::isKeyTrigger(DIK_Q)) { testEase.Play(); }
	else if (Input::isKeyTrigger(DIK_E)) { testEase.Reset(); }

	testobject->SetAffineParamTranslate(testEase.Update());

	if (Input::isKeyTrigger(DIK_O)) { Audio::PlayLoadedSound(testSE, true); }
}

void EngineDebugScene::Draw()
{
	//testobject->DrawObject();
	testobj->DrawObject();

	testFBX_NoBone->DrawObject();
	testFBX_YesBone->DrawObject();

	
}

void EngineDebugScene::Draw2D()
{
	//testsp1.DrawExtendSprite(0, 0, 100, 100, { 1,1,1,0.5 });
	//testsp2.DrawExtendSprite(100, 100, 100, 100, { 1,1,1,1 });

	testNum.DrawSprite(0, 100);

	testNum.DrawNumSpriteZeroFill(0, 0, 32, 32, dval, 10);
	testNum.uvOffsetHandle = 1;

	testNum.Draw();
}

void EngineDebugScene::DrawImgui()
{
	int oldmode = testmode;

	myImgui::StartDrawImGui("fbx control", 150, 700);

	ImGui::SliderFloat("rotX", &rotX, 0.f, 360.f);
	ImGui::SliderFloat("rotY", &rotY, 0.f, 360.f);
	ImGui::SliderFloat("rotZ", &rotZ, 0.f, 360.f);

	ImGui::Text("test cam eye %.2f,%.2f,%.2f", testcam._eyepos.x, testcam._eyepos.y, testcam._eyepos.z);
	ImGui::Text("test cam target %.2f,%.2f,%.2f", testcam._targetVec.x, testcam._targetVec.y, testcam._targetVec.z);
	ImGui::Text("test cam up %.2f,%.2f,%.2f", testcam._upVec.x, testcam._upVec.y, testcam._upVec.z);

	ImGui::Text("test cam up %.2f,%.2f,%.2f,%.2f", q1.x, q1.y, q1.z, q1.w);

	ImGui::Text("lightdir %.2f,%.2f,%.2f", DirectionalLight::GetLightDir().x,
		DirectionalLight::GetLightDir().y, DirectionalLight::GetLightDir().z);

	ImGui::SliderFloat("camrot", &camrot, 0.f, 2.0f);

	ImGui::SliderInt("num", &testNum.uvOffsetHandle, 0, 9);
	ImGui::SliderInt("dValue", &dval, -200000000, 200000000);

	myImgui::EndDrawImGui();

	testcam.Init(RVector3(0, 0, 0), RVector3(0, 0, 1), RVector3(0, 1, 0), camrot);

	myImgui::StartDrawImGui("light ctrl", 150, 300);

	ImGui::SliderFloat("light x", &lightdir.x, -1.f, 1.0f);
	ImGui::SliderFloat("light y", &lightdir.y, -1.f, 1.0f);
	ImGui::SliderFloat("light z", &lightdir.z, -1.f, 1.0f);

	DirectionalLight::SetLightDir(lightdir.x, lightdir.y, lightdir.z);

	myImgui::EndDrawImGui();

	myImgui::StartDrawImGui("Audio Control", 150, 300);

	if (ImGui::Button("PLAY")) {
		Audio::PlayLoadedSound(testBGM);
	}
	if (ImGui::Button("STOP")) {
		Audio::StopLoadedSound(testBGM);
	}
	if (ImGui::Button("PAUSE")) {
		Audio::PauseLoadedSound(testBGM);
	}

	static float masterVolume = 0.5f;
	ImGui::SliderFloat("master volume", &masterVolume, 0.0f, 1.0f);
	Audio::SetMasterVolume(masterVolume);

	myImgui::EndDrawImGui();

	testFBX_NoBone->SetAffineParamRotate(RVector3(rotX, rotY, rotZ));
	testFBX_YesBone->SetAffineParamRotate(RVector3(rotX, rotY, rotZ));
	testobj->SetAffineParamRotate(RVector3(rotX, rotY, rotZ));
	testobject->SetAffineParamRotate(RVector3(rotX, rotY, rotZ));

}
