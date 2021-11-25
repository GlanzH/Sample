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

		Effekseer::Effect* Create(LPCWSTR fileName);
		Effekseer::Handle Play(EFFECT effectName);
		void Stop(EFFECTHANDLE handleName);
		void Pause(EFFECTHANDLE handleName);

		void SetPosition(EFFECTHANDLE handleName,Vector3 effectPosition);
		void MoveEffect(EFFECTHANDLE handleName, Vector3 position);
		void SetRotation(EFFECTHANDLE handleName, Vector3 rotation);
		void SetScale(EFFECTHANDLE handleName, Vector3 scale);

		void SetTarget(EFFECTHANDLE handleName, Vector3 position);

		float GetSpeed(EFFECTHANDLE handleName);
		void SetSpeed(EFFECTHANDLE handleName,float speed);


	private:
		Effekseer::Manager*			m_manager;
		EffekseerRenderer::Renderer*	m_renderer;
		EffekseerRenderer::SingleFrameMemoryPool* m_sfMemoryPoolEfk;
		EffekseerRenderer::CommandList*			m_commandListEfk;

	private:
		CEffekseer();

	};
}

//マクロ
#define DX12Effect DX12Effekseer::CEffekseer::GetInstance()
