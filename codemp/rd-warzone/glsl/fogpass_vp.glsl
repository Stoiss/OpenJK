attribute vec3  attr_Position;
attribute vec3  attr_Normal;

attribute vec2  attr_TexCoord0;

#if defined(USE_VERTEX_ANIMATION)
attribute vec3  attr_Position2;
attribute vec3  attr_Normal2;
#elif defined(USE_SKELETAL_ANIMATION)
attribute vec4 attr_BoneIndexes;
attribute vec4 attr_BoneWeights;
#endif

uniform vec4    u_FogDistance;
uniform vec4    u_FogDepth;
uniform float   u_FogEyeT;

#if defined(USE_DEFORM_VERTEXES)
uniform int     u_DeformGen;
uniform float   u_DeformParams[7];
#endif

uniform float   u_Time;
uniform mat4    u_ModelViewProjectionMatrix;

#if defined(USE_VERTEX_ANIMATION)
uniform float   u_VertexLerp;
#elif defined(USE_SKELETAL_ANIMATION)
uniform mat4	u_BoneMatrices[20];
#endif

uniform vec4  u_Color;

varying float   var_Scale;

#if defined(USE_DEFORM_VERTEXES)
vec3 DeformPosition(const vec3 pos, const vec3 normal, const vec2 st)
{
	if (u_DeformGen == 0)
	{
		return pos;
	}

	float base =      u_DeformParams[0];
	float amplitude = u_DeformParams[1];
	float phase =     u_DeformParams[2];
	float frequency = u_DeformParams[3];
	float spread =    u_DeformParams[4];

	if (u_DeformGen == DGEN_BULGE)
	{
		phase *= st.x;
	}
	else // if (u_DeformGen <= DGEN_WAVE_INVERSE_SAWTOOTH)
	{
		phase += dot(pos.xyz, vec3(spread));
	}

	float value = phase + (u_Time * frequency);
	float func;

	if (u_DeformGen == DGEN_WAVE_SIN)
	{
		func = sin(value * 2.0 * M_PI);
	}
	else if (u_DeformGen == DGEN_WAVE_SQUARE)
	{
		func = sign(0.5 - fract(value));
	}
	else if (u_DeformGen == DGEN_WAVE_TRIANGLE)
	{
		func = abs(fract(value + 0.75) - 0.5) * 4.0 - 1.0;
	}
	else if (u_DeformGen == DGEN_WAVE_SAWTOOTH)
	{
		func = fract(value);
	}
	else if (u_DeformGen == DGEN_WAVE_INVERSE_SAWTOOTH)
	{
		func = (1.0 - fract(value));
	}
	else // if (u_DeformGen == DGEN_BULGE)
	{
		func = sin(value);
	}

	return pos + normal * (base + func * amplitude);
}
#endif

float CalcFog(vec3 position)
{
	float s = dot(vec4(position, 1.0), u_FogDistance) * 8.0;
	float t = dot(vec4(position, 1.0), u_FogDepth);

	float eyeOutside = float(u_FogEyeT < 0.0);
	float fogged = float(t >= eyeOutside);

	t += 1e-6;
	t *= fogged / (t - u_FogEyeT * eyeOutside);

	return s * t;
}

void main()
{
#if defined(USE_VERTEX_ANIMATION)
	vec3 position = mix(attr_Position, attr_Position2, u_VertexLerp);
	vec3 normal   = mix(attr_Normal,   attr_Normal2,   u_VertexLerp);
	normal = normalize(normal - vec3(0.5));
#elif defined(USE_SKELETAL_ANIMATION)
	vec4 position4 = vec4(0.0);
	vec4 normal4 = vec4(0.0);
	vec4 originalPosition = vec4(attr_Position, 1.0);
	vec4 originalNormal = vec4(attr_Normal - vec3 (0.5), 0.0);

	for (int i = 0; i < 4; i++)
	{
		int boneIndex = int(attr_BoneIndexes[i]);

		position4 += (u_BoneMatrices[boneIndex] * originalPosition) * attr_BoneWeights[i];
		normal4 += (u_BoneMatrices[boneIndex] * originalNormal) * attr_BoneWeights[i];
	}

	vec3 position = position4.xyz;
	vec3 normal = normalize(normal4.xyz);
#else
	vec3 position = attr_Position;
	vec3 normal   = attr_Normal * 2.0 - vec3(1.0);
#endif

#if defined(USE_DEFORM_VERTEXES)
	position = DeformPosition(position, normal, attr_TexCoord0.st);
#endif

	gl_Position = u_ModelViewProjectionMatrix * vec4(position, 1.0);

	var_Scale = CalcFog(position) * u_Color.a * u_Color.a;
}
