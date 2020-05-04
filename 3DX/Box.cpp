#include "Box.h"
#include "Surface.h"
#include "TextureLoader.h"
#include "MatHelper.h"


Box::Box(Graphics & gfx, float x, float y, float z, bool reflaction, bool isShadowOn) :
	x(x), y(y), z(z),isReflaction(reflaction),isShadow(isShadowOn)
{

	if (!isStaticallyBinded())
	{
		struct Vertex
		{

			DirectX::XMFLOAT3 Pos;
			DirectX::XMFLOAT3 Normal;
			DirectX::XMFLOAT2 texCoord;
			
		};
		
		
		std::vector<Vertex> vertices;
		vertices.resize(24);
		

		constexpr float side = 1.0f / 2.0f;

	
		vertices[0].Pos = { -side,-side,-side };// 0 near side
		vertices[1].Pos = { side,-side,-side };// 1
		vertices[2].Pos = { -side,side,-side };// 2
		vertices[3].Pos = { side,side,-side };// 3
		vertices[4].Pos = { -side,-side,side };// 4 far side
		vertices[5].Pos = { side,-side,side };// 5
		vertices[6].Pos = { -side,side,side };// 6
		vertices[7].Pos = { side,side,side };// 7
		vertices[8].Pos = { -side,-side,-side };// 8 left side
		vertices[9].Pos = { -side,side,-side };// 9
		vertices[10].Pos = { -side,-side,side };// 10
		vertices[11].Pos = { -side,side,side };// 11
		vertices[12].Pos = { side,-side,-side };// 12 right side
		vertices[13].Pos = { side,side,-side };// 13
		vertices[14].Pos = { side,-side,side };// 14
		vertices[15].Pos = { side,side,side };// 15
		vertices[16].Pos = { -side,-side,-side };// 16 bottom side
		vertices[17].Pos = { side,-side,-side };// 17
		vertices[18].Pos = { -side,-side,side };// 18
		vertices[19].Pos = { side,-side,side };// 19
		vertices[20].Pos = { -side,side,-side };// 20 top side
		vertices[21].Pos = { side,side,-side };// 21
		vertices[22].Pos = { -side,side,side };// 22
		vertices[23].Pos = { side,side,side };// 23
		vertices[0].texCoord = { 0.0f,0.0f };
		vertices[1].texCoord = { 1.0f,0.0f };
		vertices[2].texCoord = { 0.0f,1.0f };
		vertices[3].texCoord = { 1.0f,1.0f };
		vertices[4].texCoord = { 0.0f,0.0f };
		vertices[5].texCoord = { 1.0f,0.0f };
		vertices[6].texCoord = { 0.0f,1.0f };
		vertices[7].texCoord = { 1.0f,1.0f };
		vertices[8].texCoord = { 0.0f,0.0f };
		vertices[9].texCoord = { 1.0f,0.0f };
		vertices[10].texCoord = { 0.0f,1.0f };
		vertices[11].texCoord = { 1.0f,1.0f };
		vertices[12].texCoord = { 0.0f,0.0f };
		vertices[13].texCoord = { 1.0f,0.0f };
		vertices[14].texCoord = { 0.0f,1.0f };
		vertices[15].texCoord = { 1.0f,1.0f };
		vertices[16].texCoord = { 0.0f,0.0f };
		vertices[17].texCoord = { 1.0f,0.0f };
		vertices[18].texCoord = { 0.0f,1.0f };
		vertices[19].texCoord = { 1.0f,1.0f };
		vertices[20].texCoord = { 0.0f,0.0f };
		vertices[21].texCoord = { 1.0f,0.0f };
		vertices[22].texCoord = { 0.0f,1.0f };
		vertices[23].texCoord = { 1.0f,1.0f };
		
		

		const int n = 5;
		mInstancedData.resize(n*n*n);

		float width = 200.0f;
		float height = 200.0f;
		float depth = 200.0f;

		float x = -0.5f*width;
		float y = -0.5f*height;
		float z = -0.5f*depth;
		float dx = width / (n - 1);
		float dy = height / (n - 1);
		float dz = depth / (n - 1);
		for (int k = 0; k < n; ++k)
		{
			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < n; ++j)
				{
					// Position instanced along a 3D grid.
					mInstancedData[k*n*n + i * n + j].World = DirectX::XMFLOAT4X4(
						1.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 1.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f,
						x + j * dx, y + i * dy, z + k * dz, 1.0f);

					// Random color.
					mInstancedData[k*n*n + i * n + j].Color.x = MatHelper::randF(0.0f, 1.0f);
					mInstancedData[k*n*n + i * n + j].Color.y = MatHelper::randF(0.0f, 1.0f);
					mInstancedData[k*n*n + i * n + j].Color.z = MatHelper::randF(0.0f, 1.0f);
					mInstancedData[k*n*n + i * n + j].Color.w = 1.0f;
				}
			}
		}

		AddStaticBind(std::make_unique<VertexBuffer>(gfx, vertices, mInstancedData));
		//AddStaticBind(std::make_unique<VertexBuffer>(gfx, vertices));
		//AddStaticBind(std::make_unique<PixelShader>(gfx, L"PhongLightingPS.cso"));
		
			AddStaticBind(std::make_unique<PixelShader>(gfx, L"PhongLightingPS.cso"));
			auto vs = std::make_unique<VertexShader>(gfx, L"TexBlenderVS.cso");
			auto vsBlob = vs->GetVBlob();
			AddStaticBind(std::move(vs));
		
		/*else
		{
			AddStaticBind(std::make_unique<PixelShader>(gfx, L"PhongLightingPS.cso"));
			auto vs = std::make_unique<VertexShader>(gfx, L"TexPhongVS.cso");
			auto vsBlob = vs->GetVBlob();
			AddStaticBind(std::move(vs));
		}*/
		/*auto vs = std::make_unique<VertexShader>(gfx, L"TexPhongVS.cso");
		auto vsBlob = vs->GetVBlob();
		AddStaticBind(std::move(vs));*/
		std::vector<unsigned short> indices =
		{
			
				0,2,1,    2,3,1,
				4,5,7,    4,7,6,
				8,10, 9,  10,11,9,
				12,13,15, 12,15,14,
				16,17,18, 18,17,19,
				20,23,21, 20,22,23

		};
		/*struct PSConst
		{
			
			alignas(16) bool alphaClip;
			
		}psConst;
		psConst.alphaClip = true;*/

		struct MaterialConstantPS
		{

			DirectX::XMFLOAT4 amb;
			DirectX::XMFLOAT4 diff;
			DirectX::XMFLOAT4 spec;

		}matConst;

		matConst.amb = DirectX::XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
		matConst.diff = DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
		matConst.spec = DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 16.0f);

		AddStaticBind(std::make_unique<PSConstBuff<MaterialConstantPS>>(gfx, matConst, 1u));
		
		//AddStaticBind(std::make_unique<PSConstBuff<PSConst>>(gfx, psConst));
		//TextureLoader texLoader("Textures\\WoodCrate01.dds");
		//AddStaticBind(std::make_unique<RasterizerState>(gfx));
	
		AddStaticBind(std::make_unique<IndexBuff>(gfx, indices));
		//AddStaticBind(std::make_unique<BlendState>(gfx,));
		std::vector<D3D11_INPUT_ELEMENT_DESC> ied;
		if (instancingEnabled)
		{
			ied =
			{
				{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
				{ "Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0 },
				{ "texCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,24u,D3D11_INPUT_PER_VERTEX_DATA,0 },
				{ "World",0,DXGI_FORMAT_R32G32B32A32_FLOAT,1,0,D3D11_INPUT_PER_INSTANCE_DATA,1},
				{ "World",1,DXGI_FORMAT_R32G32B32A32_FLOAT,1,16,D3D11_INPUT_PER_INSTANCE_DATA,1},
				{ "World",2,DXGI_FORMAT_R32G32B32A32_FLOAT,1,32,D3D11_INPUT_PER_INSTANCE_DATA,1},
				{ "World",3,DXGI_FORMAT_R32G32B32A32_FLOAT,1,48,D3D11_INPUT_PER_INSTANCE_DATA,1},
				{ "Color",0,DXGI_FORMAT_R32G32B32A32_FLOAT,1,64,D3D11_INPUT_PER_INSTANCE_DATA,1},
			};
		}
		else
		{
			ied =
			{
				{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
				{ "Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0 },
				{ "texCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,24u,D3D11_INPUT_PER_VERTEX_DATA,0 }
			};
		}
		
		AddStaticBind(std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, vsBlob));
		//AddStaticBind(std::make_unique<Texture>(gfx, texLoader));
		AddStaticBind(std::make_unique<SamplerState>(gfx));
	}
	else
	{
		SetIndexBufferFromStatic();
	}
		 
	 AddBind(std::make_unique<TransformationBuffer>(gfx,*this));
}

void Box::Update(float ft)
{
	pitch += ft;
	yaw += ft;
	roll += ft;
	
}

void Box::FrustumCulling(Graphics & gfx)
{
	UpdateVertexBuffer(gfx, mInstancedData);

}

DirectX::XMMATRIX Box::GetTransformation() const
{
	if (!isReflaction && !isShadow)
	{
		return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) * DirectX::XMMatrixTranslation(x, y, z);
	}
	else if (isReflaction && !isShadow)
	{
		DirectX::XMVECTOR mirrorPlane = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		DirectX::XMMATRIX R = DirectX::XMMatrixReflect(mirrorPlane);

		return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) * DirectX::XMMatrixTranslation(x, y, z)*R;
	}
	else if (isShadow)
	{
		DirectX::XMFLOAT3 lightDir = DirectX::XMFLOAT3( -0.57735f, 0.57735f, -0.57735f);
		DirectX::XMVECTOR shadowPlane = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		DirectX::XMVECTOR toLight = DirectX::XMLoadFloat3(&lightDir);
		DirectX::XMMATRIX s = DirectX::XMMatrixShadow(shadowPlane, toLight);
		DirectX::XMMATRIX shadowOffsetY = DirectX::XMMatrixTranslation(0.0f, 0.001f, 0.0f);
		return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) * DirectX::XMMatrixTranslation(x, y, z)* s*shadowOffsetY;

	}
	//return DirectX::XMMatrixIdentity();
}

void Box::ReflactionOn(bool reflationStatus)
{
	isReflaction = reflationStatus;
}

void Box::ShadowOn(bool shadowStatus)
{
	isShadow = shadowStatus;
}

void Box::MoveBox(float fx, float fy, float fz)
{
	x += fx;
	y += fy;
	z += fz;
}

void Box::BindTestShadow(Graphics & gfx, bool refStat)
{
	/*if (refStat)
	{

	}*/
}

