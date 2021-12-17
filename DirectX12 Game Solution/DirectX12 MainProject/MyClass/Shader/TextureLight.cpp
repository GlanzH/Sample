#include "Base/pch.h"
#include "Base/dxtk.h"

#include "TextureLight.h"

void TextureLight::Init()
{
    m_rootSignature.Init(D3D12_FILTER_MIN_MAG_MIP_LINEAR,
        D3D12_TEXTURE_ADDRESS_MODE_WRAP,
        D3D12_TEXTURE_ADDRESS_MODE_WRAP,
        D3D12_TEXTURE_ADDRESS_MODE_WRAP);
    m_vs.LoadVS(L"Shader/test.fx","VS");
    m_ps.LoadPS(L"Shader/test.fx","PS");

    InitPipeLineState(m_pipelineState, m_rootSignature, m_vs, m_ps);

    SimpleMath::Vector3 vertices[] = {
        { -0.5f, -0.5f, 0.0f },
        { 0.0f, 0.5f, 0.0f },
        { 0.5f, -0.5f, 0.0f }
    };

    m_vBuff.Init(sizeof(vertices), sizeof(vertices[0]));
    m_vBuff.Copy(vertices);

    int indices[] = {
        0,1,2
    };
    m_iBuff.Init(sizeof(indices), 4);
    m_iBuff.Copy(indices);
}

void TextureLight::Render()
{
    DXTK->CommandList->SetGraphicsRootSignature(m_rootSignature.Get());
    DXTK->CommandList->SetPipelineState(m_pipelineState.Get().Get());
    DXTK->CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    DXTK->CommandList->IASetVertexBuffers(0,1,&m_vBuff.GetView());
    DXTK->CommandList->IASetIndexBuffer(&m_iBuff.GetView());
    DXTK->CommandList->DrawIndexedInstanced(3, 1, 0, 0, 0);
}

void TextureLight::InitPipeLineState(PipelineState& pipelineState, RootSignature& rs, DX12Shader& vs, DX12Shader& ps)
{
    // 頂点レイアウトを定義する
    D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
    };

    // パイプラインステートを作成
    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = { 0 };
    psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
    psoDesc.pRootSignature = rs.Get();
    psoDesc.VS = CD3DX12_SHADER_BYTECODE(vs.Get());
    psoDesc.PS = CD3DX12_SHADER_BYTECODE(ps.Get());
    psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
    psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    psoDesc.DepthStencilState.DepthEnable = FALSE;
    psoDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
    psoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
    psoDesc.DepthStencilState.StencilEnable = FALSE;
    psoDesc.SampleMask = UINT_MAX;
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
    psoDesc.SampleDesc.Count = 1;
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    pipelineState.Init(psoDesc);
}
