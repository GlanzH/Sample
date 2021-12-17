#pragma once

#include "../DX12SetUp/DX12SetUp.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class TextureLight {
public:
	void Init();
	void Render();

private:
	void InitPipeLineState(PipelineState& pipelineState,
		RootSignature& rs, DX12Shader& vs, DX12Shader& ps);

	RootSignature m_rootSignature;
	DX12Shader m_vs, m_ps;
	PipelineState m_pipelineState;
	VertexBuffer m_vBuff;
	IndexBuffer m_iBuff;

};