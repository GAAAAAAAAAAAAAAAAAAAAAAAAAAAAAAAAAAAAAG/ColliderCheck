//-----------------------------------------------------------------------------
// File: CGameObject.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Mesh.h"

CMesh::CMesh(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
}

CMesh::~CMesh()
{
	if (m_pxmf3Positions) delete[] m_pxmf3Positions;

	if (m_pnIndices) delete[] m_pnIndices;

	if (m_pnSubSetIndices) delete[] m_pnSubSetIndices;
	if (m_pnSubSetStartIndices) delete[] m_pnSubSetStartIndices;
	for (UINT i = 0; i < m_nSubsets; i++) if (m_ppnSubSetIndices[i]) delete[] m_ppnSubSetIndices[i];
	if (m_ppnSubSetIndices) delete[] m_ppnSubSetIndices;

	if (m_pd3dVertexBufferViews) delete[] m_pd3dVertexBufferViews;

	if (m_pd3dPositionBuffer) m_pd3dPositionBuffer->Release();

	for (UINT i = 0; i < m_nSubsets; i++) if (m_ppd3dSubSetIndexBuffers[i]) m_ppd3dSubSetIndexBuffers[i]->Release();
	if (m_ppd3dSubSetIndexBuffers) delete[] m_ppd3dSubSetIndexBuffers;

	if (m_pd3dIndexBufferViews) delete[] m_pd3dIndexBufferViews;
}

void CMesh::ReleaseUploadBuffers()
{
	if (m_pd3dPositionUploadBuffer) m_pd3dPositionUploadBuffer->Release();
	m_pd3dPositionUploadBuffer = NULL;

	if (m_ppd3dSubSetIndexUploadBuffers)
	{
		for (UINT i = 0; i < m_nSubsets; i++) if (m_ppd3dSubSetIndexUploadBuffers[i]) m_ppd3dSubSetIndexUploadBuffers[i]->Release();
		delete[] m_ppd3dSubSetIndexUploadBuffers;
	}
	m_ppd3dSubSetIndexUploadBuffers = NULL;
};

void CMesh::OnPreRender(ID3D12GraphicsCommandList *pd3dCommandList)
{
	pd3dCommandList->IASetPrimitiveTopology(m_d3dPrimitiveTopology);
	pd3dCommandList->IASetVertexBuffers(m_nSlot, m_nVertexBufferViews, m_pd3dVertexBufferViews);
}

void CMesh::Render(ID3D12GraphicsCommandList *pd3dCommandList)
{
}


bool CMesh::CheckMeshCollision(CMesh* pOtherMesh, const XMFLOAT4X4& worldMatrix1, const XMFLOAT4X4& worldMatrix2)
{
	if (pOtherMesh == nullptr)
		return false;


	// 기존의 메쉬 데이터를 이용하여 충돌 검사 수행
	if (!m_pnIndices || !pOtherMesh->m_pnIndices) return false;

	for (UINT i = 0; i < m_nIndices; i += 3)
	{
		XMFLOAT3 v0 = Vector3::TransformCoord(m_pxmf3Positions[m_pnIndices[i]], worldMatrix1);
		XMFLOAT3 v1 = Vector3::TransformCoord(m_pxmf3Positions[m_pnIndices[i + 1]], worldMatrix1);
		XMFLOAT3 v2 = Vector3::TransformCoord(m_pxmf3Positions[m_pnIndices[i + 2]], worldMatrix1);

		for (UINT j = 0; j < pOtherMesh->m_nIndices; j += 3)
		{
			XMFLOAT3 u0 = Vector3::TransformCoord(pOtherMesh->m_pxmf3Positions[pOtherMesh->m_pnIndices[j]], worldMatrix2);
			XMFLOAT3 u1 = Vector3::TransformCoord(pOtherMesh->m_pxmf3Positions[pOtherMesh->m_pnIndices[j + 1]], worldMatrix2);
			XMFLOAT3 u2 = Vector3::TransformCoord(pOtherMesh->m_pxmf3Positions[pOtherMesh->m_pnIndices[j + 2]], worldMatrix2);

			if (TriangleIntersectsTriangle(v0, v1, v2, u0, u1, u2))
			{
				return true;
			}
		}
	}
	return false;
}


bool CMesh::TriangleIntersectsTriangle(const XMFLOAT3& v0, const XMFLOAT3& v1, const XMFLOAT3& v2,
	const XMFLOAT3& u0, const XMFLOAT3& u1, const XMFLOAT3& u2)
{
	// 삼각형의 평면 법선 벡터 계산
	XMFLOAT3 edge1 = Vector3::Subtract(v1, v0);
	XMFLOAT3 edge2 = Vector3::Subtract(v2, v0);
	XMFLOAT3 normalV = Vector3::CrossProduct(edge1, edge2);

	XMFLOAT3 edgeU1 = Vector3::Subtract(u1, u0);
	XMFLOAT3 edgeU2 = Vector3::Subtract(u2, u0);
	XMFLOAT3 normalU = Vector3::CrossProduct(edgeU1, edgeU2);

	// 🔹 삼각형이 동일한 평면에 존재하는지 확인 (SAT 검사)
	float d0 = Vector3::DotProduct(normalV, Vector3::Subtract(u0, v0));
	float d1 = Vector3::DotProduct(normalV, Vector3::Subtract(u1, v0));
	float d2 = Vector3::DotProduct(normalV, Vector3::Subtract(u2, v0));

	if ((d0 > 0.0f && d1 > 0.0f && d2 > 0.0f) || (d0 < 0.0f && d1 < 0.0f && d2 < 0.0f))
		return false; // 삼각형이 동일 평면에 존재하지 않음

	float d3 = Vector3::DotProduct(normalU, Vector3::Subtract(v0, u0));
	float d4 = Vector3::DotProduct(normalU, Vector3::Subtract(v1, u0));
	float d5 = Vector3::DotProduct(normalU, Vector3::Subtract(v2, u0));

	if ((d3 > 0.0f && d4 > 0.0f && d5 > 0.0f) || (d3 < 0.0f && d4 < 0.0f && d5 < 0.0f))
		return false; // 삼각형이 동일 평면에 존재하지 않음

	// 🔹 삼각형 모서리를 기준으로 분리 축 검사 (SAT)
	XMFLOAT3 axes[] = {
		Vector3::CrossProduct(edge1, edgeU1), Vector3::CrossProduct(edge1, edgeU2),
		Vector3::CrossProduct(edge2, edgeU1), Vector3::CrossProduct(edge2, edgeU2),
		Vector3::CrossProduct(normalV, normalU)
	};

	for (int i = 0; i < 5; i++)
	{
		if (!Vector3::OverlapOnAxis(v0, v1, v2, u0, u1, u2, axes[i]))
		{
			return false;
		}
	}
	
	return true; // 두 삼각형이 충돌함
}

bool CMesh::CheckOBBMeshCollision(const BoundingOrientedBox& playerOBB, CMesh* pOtherMesh, const XMFLOAT4X4& worldMatrix1, const XMFLOAT4X4& worldMatrix2)
{
	if (!m_pnIndices) return false; // 메쉬 데이터가 없는 경우

	//BoundingOrientedBox transformedOBB;
	//playerOBB.Transform(transformedOBB, XMLoadFloat4x4(&worldMatrix1)); // OBB를 월드 공간으로 변환

	for (UINT i = 0; i < pOtherMesh->m_nIndices; i += 3)
	{
		XMVECTOR v0 = XMVector3TransformCoord(XMLoadFloat3(&pOtherMesh->m_pxmf3Positions[pOtherMesh->m_pnIndices[i]]), XMLoadFloat4x4(&worldMatrix2));
		XMVECTOR v1 = XMVector3TransformCoord(XMLoadFloat3(&pOtherMesh->m_pxmf3Positions[pOtherMesh->m_pnIndices[i + 1]]), XMLoadFloat4x4(&worldMatrix2));
		XMVECTOR v2 = XMVector3TransformCoord(XMLoadFloat3(&pOtherMesh->m_pxmf3Positions[pOtherMesh->m_pnIndices[i + 2]]), XMLoadFloat4x4(&worldMatrix2));

		if (playerOBB.Intersects(v0, v1, v2))
		{
			return true;
		}
	}
	return false; // 충돌 없음
}

bool CMesh::TriangleIntersectsOBB(const XMFLOAT3& v0, const XMFLOAT3& v1, const XMFLOAT3& v2, const BoundingOrientedBox& obb)
{
	// 삼각형의 AABB 생성 (빠른 필터링)
	XMFLOAT3 minV = Vector3::Min(Vector3::Min(v0, v1), v2);
	XMFLOAT3 maxV = Vector3::Max(Vector3::Max(v0, v1), v2);

	BoundingBox triAABB;
	BoundingBox::CreateFromPoints(triAABB, XMLoadFloat3(&minV), XMLoadFloat3(&maxV));

	// OBB와 삼각형의 AABB 간 충돌 검사
	if (!obb.Intersects(triAABB)) return false;

	// 🎯 OBB의 회전 행렬 변환 (쿼터니언 → 회전 행렬)
	XMMATRIX rotMatrix = XMMatrixRotationQuaternion(XMLoadFloat4(&obb.Orientation));

	// 🎯 OBB의 축 벡터를 변환 후 저장
	XMFLOAT3 obbAxes[3];
	XMStoreFloat3(&obbAxes[0], rotMatrix.r[0]); // X축
	XMStoreFloat3(&obbAxes[1], rotMatrix.r[1]); // Y축
	XMStoreFloat3(&obbAxes[2], rotMatrix.r[2]); // Z축

	// 🎯 삼각형 법선 벡터
	XMFLOAT3 triNormal = Vector3::CrossProduct(Vector3::Subtract(v1, v0), Vector3::Subtract(v2, v0));

	XMFLOAT3 axes[] = {
		obbAxes[0], obbAxes[1], obbAxes[2], triNormal
	};

	// 🎯 SAT(Separating Axis Theorem) 충돌 검사
	for (int i = 0; i < 4; i++)
	{
		if (!Vector3::OverlapOnAxis(v0, v1, v2, obb, axes[i]))
		{
			return false; // 충돌 없음
		}
	}

	return true; // 충돌 발생
}


/////////////////////////////////////////////////////////////////////////////////////////
//
CMeshFromFile::CMeshFromFile(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, char* pstrFileName) : CMesh(pd3dDevice, pd3dCommandList)
{
	if (pstrFileName) LoadMeshFromFile(pd3dDevice, pd3dCommandList, pstrFileName);
}

CMeshFromFile::~CMeshFromFile()
{
	if (m_pxmf3Normals) delete[] m_pxmf3Normals;
	if (m_pd3dNormalBuffer) m_pd3dNormalBuffer->Release();
}

void CMeshFromFile::ReleaseUploadBuffers()
{
	CMesh::ReleaseUploadBuffers();

	if (m_pd3dNormalUploadBuffer) m_pd3dNormalUploadBuffer->Release();
	m_pd3dNormalUploadBuffer = NULL;
};

void CMeshFromFile::Render(ID3D12GraphicsCommandList* pd3dCommandList, UINT nSubset)
{
	if (m_nSubsets > 0)
	{
		pd3dCommandList->IASetIndexBuffer(&m_pd3dIndexBufferViews[nSubset]);
		pd3dCommandList->DrawIndexedInstanced(m_pnSubSetIndices[nSubset], 1, 0, 0, 0);
	}
	else
	{
		pd3dCommandList->DrawInstanced(m_nVertices, 1, m_nOffset, 0);
	}
}

void CMeshFromFile::LoadMeshFromFile(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, char* pstrFileName)
{
	FILE* pFile = NULL;
	::fopen_s(&pFile, pstrFileName, "rb");
	::rewind(pFile);

	char pstrToken[256] = { '\0' };

	BYTE nStrLength = 0;
	UINT nReads = 0;

	while (1)
	{
		::ReadUnityBinaryString(pFile, pstrToken, &nStrLength);

		if (!strcmp(pstrToken, "<BoundingBox>:"))
		{
			nReads = (UINT)::fread(&m_xmBoundingBox.Center, sizeof(float), 3, pFile);
			nReads = (UINT)::fread(&m_xmBoundingBox.Extents, sizeof(float), 3, pFile);
			m_xmBoundingBox.Orientation = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
		}
		else if (!strcmp(pstrToken, "<Positions>:"))
		{
			nReads = (UINT)::fread(&m_nVertices, sizeof(int), 1, pFile);
			m_pxmf3Positions = new XMFLOAT3[m_nVertices];
			nReads = (UINT)::fread(m_pxmf3Positions, sizeof(float), 3 * m_nVertices, pFile);
		}
		else if (!strcmp(pstrToken, "<Normals>:"))
		{
			nReads = (UINT)::fread(&m_nVertices, sizeof(int), 1, pFile);
			m_pxmf3Normals = new XMFLOAT3[m_nVertices];
			nReads = (UINT)::fread(m_pxmf3Normals, sizeof(float), 3 * m_nVertices, pFile);
		}
		else if (!strcmp(pstrToken, "<Indices>:"))
		{
			nReads = (UINT)::fread(&m_nIndices, sizeof(int), 1, pFile);
			m_pnIndices = new UINT[m_nIndices];
			nReads = (UINT)::fread(m_pnIndices, sizeof(UINT), m_nIndices, pFile);
		}
		else if (!strcmp(pstrToken, "<SubMeshes>:"))
		{
			nReads = (UINT)::fread(&m_nSubsets, sizeof(int), 1, pFile);

			m_pnSubSetIndices = new UINT[m_nSubsets];
			m_pnSubSetStartIndices = new UINT[m_nSubsets];
			m_ppnSubSetIndices = new UINT * [m_nSubsets];

			for (UINT i = 0; i < m_nSubsets; i++)
			{
				nReads = (UINT)::fread(&m_pnSubSetStartIndices[i], sizeof(UINT), 1, pFile);
				nReads = (UINT)::fread(&m_pnSubSetIndices[i], sizeof(UINT), 1, pFile);
				nReads = (UINT)::fread(&m_nIndices, sizeof(int), 1, pFile);
				m_ppnSubSetIndices[i] = new UINT[m_pnSubSetIndices[i]];
				nReads = (UINT)::fread(m_ppnSubSetIndices[i], sizeof(UINT), m_pnSubSetIndices[i], pFile);
			}

			break;
		}
		//else if (!strcmp(pstrToken, "<MeshCollider>:") || !strcmp(pstrToken, "<Convex>:") ||
		//	!strcmp(pstrToken, "<ColliderVertices>:") || !strcmp(pstrToken, "<ColliderIndices>:"))
		//{
		//	nReads = (UINT)::fread(&m_nMeshColliders, sizeof(int), 1, pFile);

		//	// 🔹 기존 할당된 메모리 해제 (중복 할당 방지)
		//	if (m_pnMeshColliders)
		//	{
		//		delete[] m_pnMeshColliders;
		//		m_pnMeshColliders = NULL;
		//	}

		//	// 🔹 유효한 데이터가 있을 경우에만 메모리 할당
		//	if (m_nMeshColliders > 0)
		//	{
		//		m_pnMeshColliders = new UINT[m_nMeshColliders]; // ✅ 크기 수정
		//		nReads = (UINT)::fread(m_pnMeshColliders, sizeof(UINT), m_nMeshColliders, pFile);
		//	}
		//}
	}

	::fclose(pFile);

	m_pd3dPositionBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, m_pxmf3Positions, sizeof(XMFLOAT3) * m_nVertices, D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dPositionUploadBuffer);
	m_pd3dNormalBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, m_pxmf3Normals, sizeof(XMFLOAT3) * m_nVertices, D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dNormalUploadBuffer);

	m_nVertexBufferViews = 2;
	m_pd3dVertexBufferViews = new D3D12_VERTEX_BUFFER_VIEW[m_nVertexBufferViews];

	m_pd3dVertexBufferViews[0].BufferLocation = m_pd3dPositionBuffer->GetGPUVirtualAddress();
	m_pd3dVertexBufferViews[0].StrideInBytes = sizeof(XMFLOAT3);
	m_pd3dVertexBufferViews[0].SizeInBytes = sizeof(XMFLOAT3) * m_nVertices;

	m_pd3dVertexBufferViews[1].BufferLocation = m_pd3dNormalBuffer->GetGPUVirtualAddress();
	m_pd3dVertexBufferViews[1].StrideInBytes = sizeof(XMFLOAT3);
	m_pd3dVertexBufferViews[1].SizeInBytes = sizeof(XMFLOAT3) * m_nVertices;

	m_ppd3dSubSetIndexBuffers = new ID3D12Resource * [m_nSubsets];
	m_ppd3dSubSetIndexUploadBuffers = new ID3D12Resource * [m_nSubsets];
	m_pd3dIndexBufferViews = new D3D12_INDEX_BUFFER_VIEW[m_nSubsets];

	for (UINT i = 0; i < m_nSubsets; i++)
	{
		m_ppd3dSubSetIndexBuffers[i] = ::CreateBufferResource(pd3dDevice, pd3dCommandList, m_ppnSubSetIndices[i], sizeof(UINT) * m_pnSubSetIndices[i], D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_INDEX_BUFFER, &m_ppd3dSubSetIndexUploadBuffers[i]);

		m_pd3dIndexBufferViews[i].BufferLocation = m_ppd3dSubSetIndexBuffers[i]->GetGPUVirtualAddress();
		m_pd3dIndexBufferViews[i].Format = DXGI_FORMAT_R32_UINT;
		m_pd3dIndexBufferViews[i].SizeInBytes = sizeof(UINT) * m_pnSubSetIndices[i];
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
CBoundingBoxMesh::CBoundingBoxMesh(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList) : CMesh(pd3dDevice, pd3dCommandList)
{
	m_nVertices = 12 * 2;
	m_nStride = sizeof(XMFLOAT3);
	m_nOffset = 0;
	m_nSlot = 0;
	m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_LINELIST;

	m_pd3dPositionBuffer = CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, m_nStride * m_nVertices, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);
	m_pd3dPositionBuffer->Map(0, NULL, (void**)&m_pcbMappedPositions);

	m_nVertexBufferViews = 1;
	m_pd3dVertexBufferViews = new D3D12_VERTEX_BUFFER_VIEW[m_nVertexBufferViews];

	m_pd3dVertexBufferViews[0].BufferLocation = m_pd3dPositionBuffer->GetGPUVirtualAddress();
	m_pd3dVertexBufferViews[0].StrideInBytes = sizeof(XMFLOAT3);
	m_pd3dVertexBufferViews[0].SizeInBytes = sizeof(XMFLOAT3) * m_nVertices;
}

CBoundingBoxMesh::~CBoundingBoxMesh()
{
	if (m_pd3dPositionBuffer) m_pd3dPositionBuffer->Unmap(0, NULL);
}

void CBoundingBoxMesh::UpdateVertexPosition(BoundingOrientedBox* pxmBoundingBox)
{
	XMFLOAT3 xmf3Corners[8];
	pxmBoundingBox->GetCorners(xmf3Corners);

	int i = 0;

	m_pcbMappedPositions[i++] = xmf3Corners[0];
	m_pcbMappedPositions[i++] = xmf3Corners[1];

	m_pcbMappedPositions[i++] = xmf3Corners[1];
	m_pcbMappedPositions[i++] = xmf3Corners[2];

	m_pcbMappedPositions[i++] = xmf3Corners[2];
	m_pcbMappedPositions[i++] = xmf3Corners[3];

	m_pcbMappedPositions[i++] = xmf3Corners[3];
	m_pcbMappedPositions[i++] = xmf3Corners[0];

	m_pcbMappedPositions[i++] = xmf3Corners[4];
	m_pcbMappedPositions[i++] = xmf3Corners[5];

	m_pcbMappedPositions[i++] = xmf3Corners[5];
	m_pcbMappedPositions[i++] = xmf3Corners[6];

	m_pcbMappedPositions[i++] = xmf3Corners[6];
	m_pcbMappedPositions[i++] = xmf3Corners[7];

	m_pcbMappedPositions[i++] = xmf3Corners[7];
	m_pcbMappedPositions[i++] = xmf3Corners[4];

	m_pcbMappedPositions[i++] = xmf3Corners[0];
	m_pcbMappedPositions[i++] = xmf3Corners[4];

	m_pcbMappedPositions[i++] = xmf3Corners[1];
	m_pcbMappedPositions[i++] = xmf3Corners[5];

	m_pcbMappedPositions[i++] = xmf3Corners[2];
	m_pcbMappedPositions[i++] = xmf3Corners[6];

	m_pcbMappedPositions[i++] = xmf3Corners[3];
	m_pcbMappedPositions[i++] = xmf3Corners[7];

	XMFLOAT4 boxColor = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f); // RGBA (빨간색)
}

void CBoundingBoxMesh::Render(ID3D12GraphicsCommandList* pd3dCommandList)
{
	OnPreRender(pd3dCommandList);

	//pd3dCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	//pd3dCommandList->IASetVertexBuffers(0, 1, &m_pd3dVertexBufferViews[0]);
	//pd3dCommandList->DrawInstanced(24, 1, 0, 0); // 🎯 12개의 선을 24개의 정점으로 표현
	pd3dCommandList->DrawInstanced(m_nVertices, 1, m_nOffset, 0);
}
