#include "DX12Effekseer.h"

#ifndef _DEBUG
#pragma comment(lib,"Effekseer.lib")
#pragma comment(lib,"LLGI.lib")
#pragma comment(lib,"EffekseerRendererDX12.lib")
#else
#pragma comment(lib,"Effekseerd.lib")
#pragma comment(lib,"LLGId.lib")
#pragma comment(lib,"EffekseerRendererDX12d.lib")
#endif


DX12Effekseer::CEffekseer::CEffekseer() :m_manager(nullptr),
m_renderer(nullptr),m_sfMemoryPoolEfk(nullptr), m_commandListEfk(nullptr)
{

}

DX12Effekseer::CEffekseer::~CEffekseer()
{
	Reset();
}

/**
	@brief	Effekseerの初期設定
	@return　true 成功 失敗 false
*/
bool DX12Effekseer::CEffekseer::Initialize()
{
	//エフェクトレンダラーの生成
	auto format = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_renderer = ::EffekseerRendererDX12::Create(DXTK->Device, DXTK->CommandQueue, 3, &format, 1, DXGI_FORMAT_UNKNOWN, false, 8000);

	//メモリプールの生成
	m_sfMemoryPoolEfk = EffekseerRendererDX12::CreateSingleFrameMemoryPool(m_renderer);

	//コマンドリストの生成
	m_commandListEfk = EffekseerRendererDX12::CreateCommandList(m_renderer, m_sfMemoryPoolEfk);

	//エフェクトのマネージャーの生成
	m_manager = Effekseer::Manager::Create(8000);

	m_manager->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);

	//描画モジュールの設定
	m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
	m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
	m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
	m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
	m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

	// テクスチャ、モデル、カーブ、マテリアルローダーの設定する。
	// ユーザーが独自で拡張できる。現在はファイルから読み込んでいる。
	m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
	m_manager->SetModelLoader(m_renderer->CreateModelLoader());
	m_manager->SetMaterialLoader(m_renderer->CreateMaterialLoader());



	auto g_position = ::Effekseer::Vector3D(10.0f, 5.0f, 20.0f);

	//プロジェクションビュー初期設定
	m_renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovRH
	(90.0f / 180.0f * 3.14, (float)1280 / 720, 1.0f, 500.0f));

	//カメラの初期設定
	m_renderer->SetCameraMatrix(::Effekseer::Matrix44().LookAtRH
	(g_position, Effekseer::Vector3D(0, 0, 0), ::Effekseer::Vector3D(0, 1, 0)));

	if (m_manager == nullptr || m_renderer == nullptr || m_commandListEfk == nullptr)
		return false;

	return true;
}

/**
	@brief	Effekseerの解放
*/
void DX12Effekseer::CEffekseer::Reset()
{
	m_manager->Release();
	m_renderer->Release();
	m_commandListEfk->Release();
}

/**
	@brief	Effekseerの更新
*/
void DX12Effekseer::CEffekseer::Update(const float deltaTime)
{
	m_manager->Update();
	m_renderer->SetTime(deltaTime);
}

/**
	@brief	Effekseerの描画
*/
void DX12Effekseer::CEffekseer::Renderer()
{
	m_sfMemoryPoolEfk->NewFrame();
	EffekseerRendererDX12::BeginCommandList(m_commandListEfk, DXTK->CommandList);
	m_renderer->SetCommandList(m_commandListEfk);
	m_renderer->BeginRendering();
	m_manager->Draw();
	m_renderer->EndRendering();
	m_renderer->SetCommandList(nullptr);
	EffekseerRendererDX12::EndCommandList(m_commandListEfk);
}

void DX12Effekseer::CEffekseer::SetCamera(DX12::CAMERA* camera) 
{
	_camera = camera; 

	int a = 9;
}

/**
	@brief	カメラ設定
	@param	camera DX12のカメラ
*/
void DX12Effekseer::CEffekseer::SetCameraPosition(DX12::CAMERA* camera)
{
	auto view = camera->GetViewMatrix();
	m_renderer->SetCameraMatrix(*(Effekseer::Matrix44*)&view);

	auto proj = camera->GetProjectionMatrix();
	m_renderer->SetProjectionMatrix(*(Effekseer::Matrix44*)&proj);

	_camera = camera;

	int i = 0;
}



/**
	@brief	エフェクトのループ再生
	@param	effectName エフェクト名
*/
void DX12Effekseer::CEffekseer::Play(std::string effectName)
{
	if (m_effects[effectName] == NULL)
		return;

	if (m_handles[effectName] == NULL)
	{
		m_handles[effectName] = m_manager->Play(m_effects[effectName], 0, 0, 0);
	}

	if (!m_manager->Exists(m_handles[effectName]))
	{
		m_handles[effectName] = m_manager->Play(m_effects[effectName], 0, 0, 0);
	}
}

void DX12Effekseer::CEffekseer::Play(std::string effectName, Vector3 pos)
{
	if (m_effects[effectName] == NULL)
		return;

	if (m_handles[effectName] == NULL)
	{
		m_handles[effectName] = m_manager->Play(m_effects[effectName], pos.x, pos.y, pos.z);
	}

	if (!m_manager->Exists(m_handles[effectName]))
	{
		m_handles[effectName] = m_manager->Play(m_effects[effectName], pos.x, pos.y, pos.z);
	}
}

EFFECTHANDLE DX12Effekseer::CEffekseer::Play(EFFECT effect ,Vector3 pos)
{
	EFFECTHANDLE handle = m_manager->Play(effect, pos.x, pos.y, pos.z);

	return handle;
}

EFFECTHANDLE DX12Effekseer::CEffekseer::Play2D(EFFECT effect, Vector3 effectPosition)
{
	auto pos = DXTK->Direct3D9->ScreenToWorldPoint(Vector3(effectPosition.x, effectPosition.y, effectPosition.z), *_camera);

	EFFECTHANDLE handle = m_manager->Play(effect, pos.x, pos.y, pos.z);

	return handle;
}

/**
	@brief	エフェクト一度だけ再生
	@param	effectName エフェクト名
*/
//void DX12Effekseer::CEffekseer::PlayOneShot(std::string effectName)
//{
//	if (m_handles[effectName] == NULL || !m_manager->Exists(m_handles[effectName]))
//	{
//		m_handles[effectName] = m_manager->Play(m_effects[effectName], 0, 0, 0);
//	}
//}

void DX12Effekseer::CEffekseer::PlayOneShot(std::string effectName, Vector3 pos)
{
	if (m_handles[effectName] == NULL || !m_manager->Exists(m_handles[effectName]))
	{
		m_handles[effectName] = m_manager->Play(m_effects[effectName], pos.x, pos.y, pos.z);
	}
}

void DX12Effekseer::CEffekseer::PlayOneShot2D(std::string effectName, Vector3 effectPosition)
{
	auto pos = DXTK->Direct3D9->ScreenToWorldPoint(Vector3(effectPosition.x, effectPosition.y, effectPosition.z), *_camera);

	if (m_handles[effectName] == NULL || !m_manager->Exists(m_handles[effectName]))
	{
		m_handles[effectName] = m_manager->Play(m_effects[effectName], pos.x, pos.y, pos.z);
	}
}

/**
	@brief	エフェクトを停止して最初から再生する
	@param	effectName エフェクト名
*/
void DX12Effekseer::CEffekseer::Stop(std::string effectName)
{
	m_manager->StopEffect(m_handles[effectName]);
}

void DX12Effekseer::CEffekseer::Stop(EFFECTHANDLE handle)
{
	m_manager->StopEffect(handle);
}

void DX12Effekseer::CEffekseer::AllStop()
{
	m_manager->StopAllEffects();
}

/**
	@brief	エフェクトの一時停止　再生
	@param	effectName エフェクト名
*/
void DX12Effekseer::CEffekseer::Pause(std::string effectName)
{
	auto flag = m_manager->GetPaused(m_handles[effectName]);
	m_manager->SetPaused(m_handles[effectName], !flag);
	m_manager->SetShown(m_handles[effectName], flag);
}

void DX12Effekseer::CEffekseer::Pause(EFFECTHANDLE handle)
{
	auto flag = m_manager->GetPaused(handle);
	m_manager->SetPaused(handle, !flag);
	m_manager->SetShown(handle, flag);
}

/**
	@brief	エフェクトのポジション変更
	@param	effectName エフェクト名
	@param	effectPosition	ポジション
*/
void DX12Effekseer::CEffekseer::SetPosition(std::string effectName,Vector3 effectPosition)
{
	Effekseer::Vector3D position = Effekseer::Vector3D(effectPosition.x, effectPosition.y, effectPosition.z);
	m_manager->SetLocation(m_handles[effectName], position);

}

void DX12Effekseer::CEffekseer::SetPosition(EFFECTHANDLE handle, Vector3 effectPosition)
{
	Effekseer::Vector3D position = Effekseer::Vector3D(effectPosition.x, effectPosition.y, effectPosition.z);
	m_manager->SetLocation(handle, position);
}

void DX12Effekseer::CEffekseer::SetPosition2D(std::string effectName, Vector3 effectPosition)
{
	auto pos = DXTK->Direct3D9->ScreenToWorldPoint(Vector3(effectPosition.x, effectPosition.y, effectPosition.z), *_camera);

	Effekseer::Vector3D position = Effekseer::Vector3D(pos.x, pos.y, pos.z);
	m_manager->SetLocation(m_handles[effectName], position);
}

void DX12Effekseer::CEffekseer::SetPosition2D(EFFECTHANDLE handle, Vector3 effectPosition)
{
	auto pos = DXTK->Direct3D9->ScreenToWorldPoint(Vector3(effectPosition.x, effectPosition.y, effectPosition.z), *_camera);

	Effekseer::Vector3D position = Effekseer::Vector3D(pos.x, pos.y, pos.z);

	m_manager->SetLocation(handle, position);
}

/**
	@brief	エフェクトを移動させる
	@param	effectName エフェクト名
	@param	position	ポジション
*/
void DX12Effekseer::CEffekseer::MoveEffect(std::string effectName, Vector3 position)
{
	Effekseer::Vector3D pos = Effekseer::Vector3D(position.x, position.y, position.z);
	m_manager->AddLocation(m_handles[effectName], pos);
}

void DX12Effekseer::CEffekseer::MoveEffect(EFFECTHANDLE handle, Vector3 position)
{
	Effekseer::Vector3D pos = Effekseer::Vector3D(position.x, position.y, position.z);
	m_manager->AddLocation(handle, pos);
}

/**
	@brief	エフェクトを回転させる
	@param	effectName エフェクト名
	@param	rotation	ローテーション
*/
void DX12Effekseer::CEffekseer::SetRotation(std::string effectName, Vector3 rotation)
{
	m_manager->SetRotation(m_handles[effectName], rotation.x, rotation.y, rotation.z);
}

void DX12Effekseer::CEffekseer::SetRotation(EFFECTHANDLE handle, Vector3 rotation)
{
	m_manager->SetRotation(handle, rotation.x, rotation.y, rotation.z);
}

/**
	@brief	エフェクトのスケール変更
	@param	effectName エフェクト名
	@param	scale		拡大率
*/
void DX12Effekseer::CEffekseer::SetScale(std::string effectName, Vector3 scale)
{
	m_manager->SetScale(m_handles[effectName], scale.x, scale.y, scale.z);
}

void DX12Effekseer::CEffekseer::SetScale(EFFECTHANDLE handle, Vector3 scale)
{
	m_manager->SetScale(handle, scale.x, scale.y, scale.z);
}

/**
	@brief	エフェクトを特定の位置まで動かす
	@param	effectName エフェクト名
	@param	position	ポジション
*/
void DX12Effekseer::CEffekseer::SetTarget(std::string effectName, Vector3 position)
{
	Effekseer::Vector3D pos = Effekseer::Vector3D(position.x, position.y, position.z);
	m_manager->SetTargetLocation(m_handles[effectName], pos);
}

/**
	@brief	エフェクトの再生速度を取得する
	@param	effectName エフェクト名
	@return 再生速度
*/
float DX12Effekseer::CEffekseer::GetSpeed(std::string effectName)
{
	return m_manager->GetSpeed(m_handles[effectName]);
}

/**
	@brief	エフェクトの再生速度を変更する
	@param	effectName エフェクト名
	@param	float		再生速度
*/
void DX12Effekseer::CEffekseer::SetSpeed(std::string effectName, float speed)
{
	m_manager->SetSpeed(m_handles[effectName], speed);
}

/**
	@brief	エフェクトを生成する
	@param	fileName	ファイル名
	@return	エフェクト
*/
EFFECT DX12Effekseer::CEffekseer::Create(LPCWSTR fileName, std::string effectName)
{
	EFFECT effect = Effekseer::Effect::Create(m_manager, (const EFK_CHAR*)fileName, 1.0f);
	m_effects[effectName] = effect;

	return effect;
}

EFFECT DX12Effekseer::CEffekseer::Create(LPCWSTR fileName)
{
	EFFECT effect = Effekseer::Effect::Create(m_manager, (const EFK_CHAR*)fileName, 1.0f);
	return effect;
}
