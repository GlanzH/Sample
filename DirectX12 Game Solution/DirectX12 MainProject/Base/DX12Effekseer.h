/**
 * @file DX12Effekseer.h
 * @brief DirectX12でEffekseerを使用するためのクラス
 * @author 星寛文
 * @date 2021/10/08
 */

#pragma once

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

#include <Effekseer.h>
#include <EffekseerRendererDX12.h>

using namespace  DirectX::SimpleMath;
typedef Effekseer::Effect*   EFFECT;
typedef Effekseer::Handle    EFFECTHANDLE;

//------------------------------------------------------------------------------
//	DX12Effekseerクラス定義
//------------------------------------------------------------------------------
namespace DX12Effekseer
{
	class CEffekseer
	{
	public:
		virtual ~CEffekseer();

		static CEffekseer& GetInstance()
		{
			static CEffekseer effekseer;
			return effekseer;
		}

		bool Initialize();
		void Reset();
		void Update(const float deltaTime);
		void Renderer();

		void SetCamera(DX12::CAMERA* camera); /*{ _camera = &camera; }*/
		void SetCameraPosition(DX12::CAMERA* camera);

		EFFECT Create(LPCWSTR fileName, std::string effectName);
		EFFECT Create(LPCWSTR fileName);

		void Play(std::string effectName);
		void Play(std::string effectName, Vector3 pos);
		EFFECTHANDLE Play(EFFECT effect, Vector3 pos);

		EFFECTHANDLE Play2D(EFFECT effect, Vector3 pos);

	//	void PlayOneShot(std::string effectName);

		void PlayOneShot(std::string effectName, Vector3 pos);

		void PlayOneShot2D(std::string effectName, Vector3 pos);

		void Stop(std::string effectName);
		void Stop(EFFECTHANDLE handle);
		void AllStop();

		void Pause(std::string effectName);
		void Pause(EFFECTHANDLE handle);

		void SetPosition(std::string effectName, Vector3 effectPosition);
		void SetPosition(EFFECTHANDLE handle, Vector3 effectPosition);

		void SetPosition2D(std::string effectName, Vector3 effectPosition);
		void SetPosition2D(EFFECTHANDLE handle, Vector3 effectPosition);

		void MoveEffect(std::string effectName, Vector3 position);
		void MoveEffect(EFFECTHANDLE handle, Vector3 position);

		void SetRotation(std::string effectName, Vector3 rotation);
		void SetRotation(EFFECTHANDLE handle, Vector3 rotation);

		void SetScale(std::string effectName, Vector3 scale);
		void SetScale(EFFECTHANDLE handle, Vector3 scale);

		void SetTarget(std::string effectName, Vector3 position);

		float GetSpeed(std::string effectName);
		void SetSpeed(std::string effectName, float speed);

		bool CheckAlive(std::string effectName) { return m_manager->Exists(m_handles[effectName]); }
		bool CheckAlive(EFFECTHANDLE handle) { return m_manager->Exists(handle); }

	private:
		Effekseer::Manager* m_manager;
		EffekseerRenderer::Renderer* m_renderer;
		EffekseerRenderer::SingleFrameMemoryPool* m_sfMemoryPoolEfk;
		EffekseerRenderer::CommandList* m_commandListEfk;

		std::map<std::string, EFFECT> m_effects;
		std::map<std::string, EFFECTHANDLE> m_handles;

		DX12::CAMERA* _camera;
	private:
		CEffekseer();

	};
}

//マクロ
#define DX12Effect DX12Effekseer::CEffekseer::GetInstance()
