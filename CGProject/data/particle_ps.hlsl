////////////////////////////////////////////////////////////////////////////////
// Filename: particle_ps.hlsl
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////
Texture2D shaderTexture;
SamplerState SampleType;


//////////////
// TYPEDEFS //
//////////////
struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
	float4 color : COLOR;
};


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 ParticlePixelShader(PixelInputType input) : SV_TARGET
{
	float4 textureColor;
	float4 finalColor;


    // 이 텍스처 좌표 위치에서 샘플러를 사용하여 텍스처에서 픽셀 색상을 샘플링합니다.
    textureColor = shaderTexture.Sample(SampleType, input.tex);

	// 텍스처 색상과 입자 색상을 결합하여 최종 색상 결과를 얻습니다.
    finalColor = textureColor * input.color;

	// If the color is black on the texture then treat this pixel as transparent.
	if (finalColor.r == 0.0f && finalColor.g == 0.0f && finalColor.b == 0.0f)
	{
		finalColor.a = 0.0f;
	}
	else if (finalColor.r >= 0.0f && finalColor.g >= 0.0f && finalColor.b == 0.0f)	// light
	{
		finalColor.a = finalColor.r * 1.5f;
		if (finalColor.a > 1.0f) finalColor.a = 1.0f;
	}
	else if (finalColor.r == 1.0f && finalColor.g == 0.0f && finalColor.b == 0.0f)	// blood center
	{
		finalColor.a = 1.0f;
	}
	else if (finalColor.r < 1.0f)	// blood outline
	{
		finalColor.a = finalColor.r * 1.5f;
		if (finalColor.a > 1.0f) finalColor.a = 1.0f;
	}

	// If the color is other than black on the texture then this is a pixel in the font so draw it using the font pixel color.
	else
	{
		//color.rgb = pixelColor.rgb;
		finalColor.a = 1.0f;
	}

    return finalColor;
}