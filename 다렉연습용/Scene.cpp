﻿//-----------------------------------------------------------------------------
// File: CScene.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Scene.h"

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::BuildLightsAndMaterials()
{
	m_pLights = new LIGHTS;
	::ZeroMemory(m_pLights, sizeof(LIGHTS));

	m_pLights->m_xmf4GlobalAmbient = XMFLOAT4(0.234f, 0.234f, 0.234f, 1.0f);

	m_pLights->m_pLights[0].m_bEnable = true;
	m_pLights->m_pLights[0].m_nType = POINT_LIGHT;
	m_pLights->m_pLights[0].m_fRange = 100.0f;
	m_pLights->m_pLights[0].m_xmf4Ambient = XMFLOAT4(0.1f, 0.0f, 0.0f, 1.0f);
	m_pLights->m_pLights[0].m_xmf4Diffuse = XMFLOAT4(0.148f, 0.0f, 0.0f, 1.0f);
	m_pLights->m_pLights[0].m_xmf4Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.0f);
	m_pLights->m_pLights[0].m_xmf3Position = XMFLOAT3(130.0f, 30.0f, 30.0f);
	m_pLights->m_pLights[0].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_pLights->m_pLights[0].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.001f, 0.0001f);
	m_pLights->m_pLights[1].m_bEnable = true;
	m_pLights->m_pLights[1].m_nType = SPOT_LIGHT;
	m_pLights->m_pLights[1].m_fRange = 150.0f;
	m_pLights->m_pLights[1].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pLights->m_pLights[1].m_xmf4Diffuse = XMFLOAT4(0.14f, 0.14f, 0.14f, 1.0f);
	m_pLights->m_pLights[1].m_xmf4Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.0f);
	m_pLights->m_pLights[1].m_xmf3Position = XMFLOAT3(-50.0f, 20.0f, -5.0f);
	m_pLights->m_pLights[1].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_pLights->m_pLights[1].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights->m_pLights[1].m_fFalloff = 8.0f;
	m_pLights->m_pLights[1].m_fPhi = (float)cos(XMConvertToRadians(40.0f));
	m_pLights->m_pLights[1].m_fTheta = (float)cos(XMConvertToRadians(20.0f));
	m_pLights->m_pLights[2].m_bEnable = true;
	m_pLights->m_pLights[2].m_nType = DIRECTIONAL_LIGHT;
	m_pLights->m_pLights[2].m_xmf4Ambient = XMFLOAT4(0.053f, 0.053f, 0.053f, 1.0f);
	m_pLights->m_pLights[2].m_xmf4Diffuse = XMFLOAT4(0.0f, 0.17f, 0.17f, 1.0f);
	m_pLights->m_pLights[2].m_xmf4Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	m_pLights->m_pLights[2].m_xmf3Direction = XMFLOAT3(1.0f, 0.0f, 1.0f);
	m_pLights->m_pLights[3].m_bEnable = true;
	m_pLights->m_pLights[3].m_nType = DIRECTIONAL_LIGHT;
	m_pLights->m_pLights[3].m_xmf4Ambient = XMFLOAT4(0.053f, 0.053f, 0.053f, 1.0f);
	m_pLights->m_pLights[3].m_xmf4Diffuse = XMFLOAT4(0.17f, 0.17f, 0.0f, 1.0f);
	m_pLights->m_pLights[3].m_xmf4Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	m_pLights->m_pLights[3].m_xmf3Direction = XMFLOAT3(0.0f, -1.0f, 1.0f);
	m_pLights->m_pLights[4].m_bEnable = true;
	m_pLights->m_pLights[4].m_nType = SPOT_LIGHT;
	m_pLights->m_pLights[4].m_fRange = 30.0f;
	m_pLights->m_pLights[4].m_xmf4Ambient = XMFLOAT4(0.012f, 0.012f, 0.012f, 1.0f);
	m_pLights->m_pLights[4].m_xmf4Diffuse = XMFLOAT4(0.24f, 0.14f, 0.24f, 1.0f);
	m_pLights->m_pLights[4].m_xmf4Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pLights->m_pLights[4].m_xmf3Position = XMFLOAT3(0.0f, 5.0f, -7.0f);
	m_pLights->m_pLights[4].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_pLights->m_pLights[4].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.25f, 0.05f);
	m_pLights->m_pLights[4].m_fFalloff = 1.0f;
	m_pLights->m_pLights[4].m_fPhi = (float)cos(XMConvertToRadians(10.0f));
	m_pLights->m_pLights[4].m_fTheta = (float)cos(XMConvertToRadians(5.0f));
	m_pLights->m_pLights[5].m_bEnable = false;
	m_pLights->m_pLights[6].m_bEnable = false;
	m_pLights->m_pLights[7].m_bEnable = false;

	m_pMaterials = new MATERIALS;
	::ZeroMemory(m_pMaterials, sizeof(MATERIALS));

	m_pMaterials->m_pReflections[1] = { XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f), XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f), XMFLOAT4(0.7f, 0.7f, 0.7f, 5.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[0] = { XMFLOAT4(0.3f, 0.4f, 0.0f, 1.0f), XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 10.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[2] = { XMFLOAT4(0.0f, 0.6f, 1.0f, 1.0f), XMFLOAT4(0.0f, 0.5f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 15.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[3] = { XMFLOAT4(0.5f, 0.0f, 0.6f, 1.0f), XMFLOAT4(0.0f, 0.5f, 0.8f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 20.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[4] = { XMFLOAT4(0.0f, 0.5f, 0.6f, 1.0f), XMFLOAT4(0.5f, 0.0f, 0.8f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 25.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[5] = { XMFLOAT4(0.0f, 0.5f, 0.5f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.8f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 30.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[6] = { XMFLOAT4(0.5f, 0.5f, 0.6f, 1.0f), XMFLOAT4(0.5f, 0.5f, 0.8f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 35.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[7] = { XMFLOAT4(1.0f, 0.5f, 0.6f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.8f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 40.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[8] = { XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f), XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 5.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[9] = { XMFLOAT4(0.0f, 0.5f, 0.0f, 1.0f), XMFLOAT4(0.0f, 0.8f, 0.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 10.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[10] = { XMFLOAT4(0.0f, 0.0f, 0.5f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 15.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[11] = { XMFLOAT4(0.4f, 0.0f, 0.5f, 1.0f), XMFLOAT4(0.0f, 0.3f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 20.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[12] = { XMFLOAT4(0.0f, 0.4f, 0.7f, 1.0f), XMFLOAT4(0.3f, 0.0f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 25.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[13] = { XMFLOAT4(0.0f, 0.3f, 0.3f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 30.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[14] = { XMFLOAT4(0.3f, 0.3f, 0.6f, 1.0f), XMFLOAT4(0.3f, 0.3f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 35.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[15] = { XMFLOAT4(0.7f, 0.5f, 0.7f, 1.0f), XMFLOAT4(0.5f, 0.0f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 40.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
}

void CScene::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);

	m_pBoundingBoxShader = new CBoundingBoxShader();
	m_pBoundingBoxShader->CreateShader(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE);

	BuildLightsAndMaterials();

	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CScene::ReleaseObjects()
{
	if (m_pd3dGraphicsRootSignature) m_pd3dGraphicsRootSignature->Release();

	if (m_ppObjectShaders)
	{
		for (int i = 0; i < m_nObjectShaders; i++)
		{
			m_ppObjectShaders[i]->ReleaseShaderVariables();
			m_ppObjectShaders[i]->ReleaseObjects();
			m_ppObjectShaders[i]->Release();
		}
		delete[] m_ppObjectShaders;
	}

	if (m_pBoundingBoxShader) m_pBoundingBoxShader->Release();

	ReleaseShaderVariables();

	if (m_pLights) delete m_pLights;
	if (m_pMaterials) delete m_pMaterials;
}

void CScene::ReleaseUploadBuffers()
{
	for (int i = 0; i < m_nObjectShaders; i++) m_ppObjectShaders[i]->ReleaseUploadBuffers();
}

ID3D12RootSignature *CScene::CreateGraphicsRootSignature(ID3D12Device *pd3dDevice)
{
	ID3D12RootSignature *pd3dGraphicsRootSignature = NULL;

	D3D12_ROOT_PARAMETER pd3dRootParameters[5];

	pd3dRootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[0].Descriptor.ShaderRegister = 0; //Camera: b0
	pd3dRootParameters[0].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[1].Descriptor.ShaderRegister = 1; //GameObject: b1
	pd3dRootParameters[1].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[2].Descriptor.ShaderRegister = 2; //Materials
	pd3dRootParameters[2].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[3].Descriptor.ShaderRegister = 3; //Lights
	pd3dRootParameters[3].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[4].Constants.Num32BitValues = 12;
	pd3dRootParameters[4].Constants.ShaderRegister = 4; //Constants
	pd3dRootParameters[4].Constants.RegisterSpace = 0;
	pd3dRootParameters[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	D3D12_STATIC_SAMPLER_DESC d3dSamplerDesc;
	::ZeroMemory(&d3dSamplerDesc, sizeof(D3D12_STATIC_SAMPLER_DESC));
	d3dSamplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	d3dSamplerDesc.Filter = D3D12_FILTER_ANISOTROPIC;
	d3dSamplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	d3dSamplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	d3dSamplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	d3dSamplerDesc.MipLODBias = 0;
	d3dSamplerDesc.MaxAnisotropy = 16;
	d3dSamplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	d3dSamplerDesc.MinLOD = 0;
	d3dSamplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
	d3dSamplerDesc.ShaderRegister = 0;
	d3dSamplerDesc.RegisterSpace = 0;
	d3dSamplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	D3D12_ROOT_SIGNATURE_FLAGS d3dRootSignatureFlags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT | D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS | D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS | D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS;
	D3D12_ROOT_SIGNATURE_DESC d3dRootSignatureDesc;
	::ZeroMemory(&d3dRootSignatureDesc, sizeof(D3D12_ROOT_SIGNATURE_DESC));
	d3dRootSignatureDesc.NumParameters = _countof(pd3dRootParameters);
	d3dRootSignatureDesc.pParameters = pd3dRootParameters;
	d3dRootSignatureDesc.NumStaticSamplers = 1;
	d3dRootSignatureDesc.pStaticSamplers = &d3dSamplerDesc;
	d3dRootSignatureDesc.Flags = d3dRootSignatureFlags;

	ID3DBlob *pd3dSignatureBlob = NULL;
	ID3DBlob *pd3dErrorBlob = NULL;
	D3D12SerializeRootSignature(&d3dRootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &pd3dSignatureBlob, &pd3dErrorBlob);
	pd3dDevice->CreateRootSignature(0, pd3dSignatureBlob->GetBufferPointer(), pd3dSignatureBlob->GetBufferSize(), __uuidof(ID3D12RootSignature), (void **)&pd3dGraphicsRootSignature);
	if (pd3dSignatureBlob) pd3dSignatureBlob->Release();
	if (pd3dErrorBlob) pd3dErrorBlob->Release();

	return(pd3dGraphicsRootSignature);
}

void CScene::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(LIGHTS) + 255) & ~255); //256의 배수
	m_pd3dcbLights = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbElementBytes, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbLights->Map(0, NULL, (void **)&m_pcbMappedLights);

	UINT ncbMaterialBytes = ((sizeof(MATERIALS) + 255) & ~255); //256의 배수
	m_pd3dcbMaterials = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbMaterialBytes, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbMaterials->Map(0, NULL, (void **)&m_pcbMappedMaterials);
}

void CScene::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	::memcpy(m_pcbMappedLights, m_pLights, sizeof(LIGHTS));
	::memcpy(m_pcbMappedMaterials, m_pMaterials, sizeof(MATERIALS));
}

void CScene::ReleaseShaderVariables()
{
	if (m_pd3dcbLights)
	{
		m_pd3dcbLights->Unmap(0, NULL);
		m_pd3dcbLights->Release();
	}
	if (m_pd3dcbMaterials)
	{
		m_pd3dcbMaterials->Unmap(0, NULL);
		m_pd3dcbMaterials->Release();
	}
}

bool CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return(false);
}

bool CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return(false);
}

bool CScene::ProcessInput(UCHAR *pKeysBuffer)
{
	return(false);
}

bool CScene::CheckObjectByObjectCollisions(CGameObject* pTargetGameObject)
{
	for (int i = 0; i < m_nObjectShaders; i++)
	{
		for (int j = 0; j < m_ppObjectShaders[i]->m_nObjects; j++)
		{
			CGameObject* pGameObject = m_ppObjectShaders[i]->m_ppObjects[j];
			if (!pGameObject || pGameObject == pTargetGameObject) continue;

			if (m_pPlayer->m_xmBoundingBox.Intersects(pGameObject->m_xmBoundingBox))
			{
				if (nullptr != pGameObject->m_pMesh)
				{
					if (m_pPlayer->m_pMesh->CheckOBBMeshCollision(m_pPlayer->m_xmBoundingBox, pGameObject->m_pMesh, m_pPlayer->m_xmf4x4World, pGameObject->m_xmf4x4World))
					{
						float deltaY = m_pPlayer->GetPosition().y - pGameObject->GetPosition().y;
						if (deltaY > 0.0f && deltaY < 20.0f) // 바닥이라고 판단할 수 있는 높이
						{
							m_pPlayer->SetOnGround(true);
							m_pPlayer->SetVelocityY(0.0f); // y 속도 정지

							return true;
						}
						else
						{
							// 바닥이 아니면 위치 복구 및 속도 제한
							ResolveCollision(m_pPlayer, pGameObject);
							return true;
						}

						//TODO: 여기에 충돌처리 로직 넣어보자
						//ResolveCollision(m_pPlayer, pGameObject);
					}
				}
			}
		}
	}
	m_pPlayer->SetOnGround(false); // 아무 것도 닿지 않으면 공중
	return false;
}

//void CScene::ResolveCollision(CPlayer* player, CGameObject* object)
//{
//	if (!player) return; // 플레이어가 유효하지 않으면 리턴
//
//	// 🎯 플레이어가 충돌한 경우, 이전 위치를 기준으로 복귀
//	player->SetPosition2(player->GetBeforeCollidedPosition());
//
//	if (!object) return; // 충돌 대상이 없으면 더 이상 계산할 필요 없음
//
//	// 🎯 충돌 방향을 계산하여 해당 축 이동 제한
//	XMFLOAT3 direction = Vector3::Subtract(player->GetPosition(), object->GetPosition());
//	direction = Vector3::Normalize(direction);
//
//	XMFLOAT3 newVelocity = player->GetVelocity();
//
//	// X축 충돌 (좌우 이동 제한)
//	if (fabs(direction.x) > fabs(direction.z)) {
//		newVelocity.x = 0.0f;
//	}
//	// Z축 충돌 (앞뒤 이동 제한)
//	else {
//		newVelocity.z = 0.0f;
//	}
//
//	// Y축 충돌 (점프 또는 떨어지는 경우)
//	if (fabs(direction.y) > 0.1f) {
//		newVelocity.y = 0.0f;
//	}
//
//	player->SetVelocity(newVelocity);
//}

void CScene::ResolveCollision(CPlayer* player, CGameObject* object)
{
	if (!player || !object) return;

	// 🎯 이동 벡터
	XMFLOAT3 velocity = player->GetVelocity();

	// 🎯 방향 벡터 (object → player)
	XMFLOAT3 direction = Vector3::Subtract(player->GetPosition(), object->GetPosition());
	direction = Vector3::Normalize(direction);

	// 🎯 충돌 법선 벡터로 가정 (충돌한 면의 반대 방향)
	XMFLOAT3 collisionNormal = direction;

	// 🎯 슬라이딩 벡터 = 속도에서 충돌 법선 방향을 제거한 나머지
	float dot = Vector3::DotProduct(velocity, collisionNormal);
	XMFLOAT3 projection = Vector3::ScalarProduct(collisionNormal, dot);
	XMFLOAT3 slideVector = Vector3::Subtract(velocity, projection);

	// 🎯 새 속도 설정
	player->SetVelocity(slideVector);
}


bool CScene::CheckGroundCollision(CPlayer* pPlayer)
{
	BoundingOrientedBox playerOBB = pPlayer->m_xmBoundingBox;
	playerOBB.Center.y -= 1.0f; // 아래로 살짝 내려서 바닥 감지

	for (int i = 0; i < m_nObjectShaders; i++)
	{
		for (int j = 0; j < m_ppObjectShaders[i]->m_nObjects; j++)
		{
			CGameObject* obj = m_ppObjectShaders[i]->m_ppObjects[j];
			if (obj->m_pMesh && obj != pPlayer)
			{
				if (obj->m_pMesh->CheckOBBMeshCollision(m_pPlayer->m_xmBoundingBox, obj->m_pMesh, m_pPlayer->m_xmf4x4World, obj->m_xmf4x4World))
				{
					return true;
				}
			}
		}
	}
	return false;
}

void CScene::AnimateObjects(float fTimeElapsed)
{
	for (int i = 0; i < m_nObjectShaders; i++)
	{
		m_ppObjectShaders[i]->AnimateObjects(fTimeElapsed);
	}

	if (m_pLights)
	{
		m_pLights->m_pLights[1].m_xmf3Position = m_pPlayer->GetPosition();
		m_pLights->m_pLights[1].m_xmf3Direction = m_pPlayer->GetLookVector();
		m_pLights->m_pLights[4].m_xmf3Position = Vector3::Add(m_pPlayer->GetPosition(), Vector3::Add(Vector3::ScalarProduct(m_pPlayer->GetLookVector(), -15.0f, false), XMFLOAT3(0.0f, 5.0f, 0.0f)));
		m_pLights->m_pLights[4].m_xmf3Direction = m_pPlayer->GetLookVector();
	}
}

void CScene::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);

	pCamera->SetViewportsAndScissorRects(pd3dCommandList);
	pCamera->UpdateShaderVariables(pd3dCommandList);

	UpdateShaderVariables(pd3dCommandList);

	D3D12_GPU_VIRTUAL_ADDRESS d3dcbMaterialsGpuVirtualAddress = m_pd3dcbMaterials->GetGPUVirtualAddress();
	pd3dCommandList->SetGraphicsRootConstantBufferView(2, d3dcbMaterialsGpuVirtualAddress); //Materials

	D3D12_GPU_VIRTUAL_ADDRESS d3dcbLightsGpuVirtualAddress = m_pd3dcbLights->GetGPUVirtualAddress();
	pd3dCommandList->SetGraphicsRootConstantBufferView(3, d3dcbLightsGpuVirtualAddress); //Lights

	for (int i = 0; i < m_nObjectShaders; i++)
	{
		m_ppObjectShaders[i]->Render(pd3dCommandList, pCamera);
	}
}

void CScene::RenderBoundingBox(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	m_pBoundingBoxShader->Render(pd3dCommandList, pCamera);
	for (int i = 0; i < m_nObjectShaders; i++)
	{
		if (m_ppObjectShaders[i]) m_ppObjectShaders[i]->RenderBoundingBox(pd3dCommandList, pCamera);
	}

	m_pPlayer->RenderBoundingBox(pd3dCommandList, pCamera);
}

//////////////////////////////////////////////////////////////////////////////////////////
//
void CCanaleScene::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	CScene::BuildObjects(pd3dDevice, pd3dCommandList);

	m_nObjectShaders = 1;
	m_ppObjectShaders = new CObjectsShader * [m_nObjectShaders];

	CObjectsShader* pObjectShader = new CObjectsShader();
	pObjectShader->CreateShader(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);
	pObjectShader->BuildObjects(pd3dDevice, pd3dCommandList, "Models/Canalescene/Scene.bin");
	m_ppObjectShaders[0] = pObjectShader;
}

//////////////////////////////////////////////////////////////////////////////////////////
//
void CNightScene::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	CScene::BuildObjects(pd3dDevice, pd3dCommandList);

	m_nObjectShaders = 1;
	m_ppObjectShaders = new CObjectsShader * [m_nObjectShaders];

	CObjectsShader* pObjectShader = new CObjectsShader();
	pObjectShader->CreateShader(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);
	pObjectShader->BuildObjects(pd3dDevice, pd3dCommandList, "Models/Canalescene/Scene.bin");
	m_ppObjectShaders[0] = pObjectShader;
}

