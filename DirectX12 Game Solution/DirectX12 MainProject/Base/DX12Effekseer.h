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

typedef DirectX::SimpleMath::Vector3 Vector3;
typedef Effekseer::Effect* EFFECT;
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

		void SetCamera(DX12::CAMERA camera);

		Effekseer::Effect* Create(LPCWSTR fileName,std::string name);
		void Play(std::string effectName);
		void PlayOneShot(std::string effectName);
		void Stop(std::string handleName);
		void Pause(std::string handleName);

		void SetPosition(std::string handleName,Vector3 effectPosition);
		void MoveEffect(std::string handleName, Vector3 position);
		void SetRotation(std::string handleName, Vector3 rotation);
		void SetScale(std::string handleName, Vector3 scale);

		void SetTarget(std::string handleName, Vector3 position);

		float GetSpeed(std::string handleName);
		void SetSpeed(std::string handleName,float speed);


	private:
		Effekseer::Manager*			m_manager;
		EffekseerRenderer::Renderer*	m_renderer;
		EffekseerRenderer::SingleFrameMemoryPool* m_sfMemoryPoolEfk;
		EffekseerRenderer::CommandList*			m_commandListEfk;

		std::map<std::string,EFFECT> m_effects;
		std::map<std::string,EFFECTHANDLE> m_handles;

	private:
		CEffekseer();

	};
}

//マクロ
#define DX12Effect DX12Effekseer::CEffekseer::GetInstance()
