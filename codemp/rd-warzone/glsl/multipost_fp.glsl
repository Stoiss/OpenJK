uniform sampler2D u_DiffuseMap;

uniform vec4	u_ViewInfo; // zfar / znear, zfar
uniform vec2	u_Dimensions;
uniform vec4	u_Local0; // num_passes, 0, 0, 0


varying vec2	var_TexCoords;

#define SHARPEN_ENABLED
//#define HDR_ENABLED
//#define SSAO_ENABLED
//#define LF_ENABLED

vec2 resolution = u_Dimensions;
vec2 vTexCoords = var_TexCoords;

vec2 TEX_OFFSET = vec2(1.0 / float(u_Dimensions.x), 1.0 / float(u_Dimensions.y));

vec2 KERNEL[8] = vec2[](
	vec2(TEX_OFFSET.x, TEX_OFFSET.y),
	vec2(0.0, TEX_OFFSET.y),
	vec2(-TEX_OFFSET.x, TEX_OFFSET.y),
	vec2(-TEX_OFFSET.x, 0.0),
	vec2(-TEX_OFFSET.x, -TEX_OFFSET.y),
	vec2(0.0, -TEX_OFFSET.y),
	vec2(TEX_OFFSET.x, -TEX_OFFSET.y),
	vec2(TEX_OFFSET.x, 0.0));

//==============================================================================
vec3 grayScale(in vec3 col)
{
	float grey = (col.r + col.g + col.b) * 0.333333333; // aka: / 3.0
	return vec3(grey);
}

//==============================================================================
vec3 saturation(in vec3 col, in float factor)
{
	const vec3 lumCoeff = vec3(0.2125, 0.7154, 0.0721);

	vec3 intensity = vec3(dot(col, lumCoeff));
	return mix(intensity, col, factor);
}

//==============================================================================
vec3 gammaCorrection(in float gamma, in vec3 col)
{
	return pow(col, vec3(1.0 / gamma));
}

//==============================================================================
vec3 gammaCorrectionRgb(in vec3 gamma, in vec3 col)
{
	return pow(col, 1.0 / gamma);
}

//==============================================================================
vec3 sharpen(in sampler2D tex, in vec2 texCoords)
{
	const float sharpenFactor = 0.25;

	vec3 col = texture(tex, texCoords).rgb;

	vec3 col2 = texture(tex, texCoords + KERNEL[0]).rgb;
	for(int i = 1; i < 8; i++)
	{
		col2 += texture(tex, texCoords + KERNEL[i]).rgb;
	}

	return col * (8.0 * sharpenFactor + 1.0) - sharpenFactor * col2;
}

//==============================================================================
vec3 erosion(in sampler2D tex, in vec2 texCoords)
{
    vec3 minValue = texture(tex, texCoords).rgb;

    for (int i = 0; i < 8; i++)
    {
        vec3 tmpCol = textureLod(tex, texCoords + KERNEL[i], 0.0).rgb;
        minValue = min(tmpCol, minValue);
    }

    return minValue;
}


//==============================================================================
void main(void)
{
	vec3 fColor;

#if defined(SHARPEN_ENABLED)
	fColor = sharpen(u_DiffuseMap, vTexCoords);
#else
	fColor = texture(u_DiffuseMap, vTexCoords).rgb;
#endif
	//fColor = erosion(u_DiffuseMap, vTexCoords);

#if defined(HDR_ENABLED)
	vec3 hdr = texture(ppsHdrFai, vTexCoords).rgb;
	fColor += hdr;
#endif

#if defined(SSAO_ENABLED)
	float ssao = texture(ppsSsaoFai, vTexCoords).r;
	fColor *= ssao;
#endif

#if defined(LF_ENABLED)
	vec3 lf = texture(ppsLfFai, vTexCoords).rgb;
	fColor += lf;
#endif

	//fColor = BlendHardLight(vec3(0.7, 0.72, 0.4), fColor);
	fColor = gammaCorrectionRgb(vec3(0.9, 0.92, 0.75), fColor);

	gl_FragColor = vec4(fColor, 1.0);
}
