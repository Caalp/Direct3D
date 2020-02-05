#include "TransformBufferVar.hlsl"

struct VertexIn
{
    float3 PosL : Position;
    float3 NormalL : Normal;
    float2 texCoordinate : TexCoord;
};

struct VertexOut
{
   
    float3 PosW : Pos;
    float3 NormalW : n;
    float3 eyePos : EyePosition;
    float2 txCoord : TexCoord;
    float4 PosH : SV_POSITION;
};
VertexOut main(VertexIn vin)
{
    VertexOut vout;
    vout.PosW = mul(float4(vin.PosL, 1.0f), model);
    vout.NormalW = mul(vin.NormalL, (float3x3) model);
    vout.PosH = mul(float4(vin.PosL, 1.0f), worldViewProj);
    vout.txCoord = vin.texCoordinate;
    //vout.EyePos = mul(float4(EyePos, 1.0f), model);
    vout.eyePos = eyePos;
  
    return vout;
}