attribute vec2				attr_TexCoord0;
attribute vec2				attr_TexCoord1;

attribute vec4				attr_Color;

attribute vec3				attr_Position;
attribute vec3				attr_Normal;

attribute vec3				attr_Position2;
attribute vec3				attr_Normal2;
attribute vec4				attr_BoneIndexes;
attribute vec4				attr_BoneWeights;

uniform vec4				u_Settings0; // useTC, useDeform, useRGBA
uniform vec4				u_Settings1; // useVertexAnim, useSkeletalAnim

#define USE_TC				u_Settings0.r
#define USE_DEFORM			u_Settings0.g
#define USE_RGBA			u_Settings0.b
#define USE_TEXTURECLAMP	u_Settings0.a

#define USE_VERTEX_ANIM		u_Settings1.r
#define USE_SKELETAL_ANIM	u_Settings1.g
#define USE_FOG				u_Settings1.b


uniform float				u_Time;

uniform vec3				u_ViewOrigin;

uniform int					u_TCGen0;
uniform vec3				u_TCGen0Vector0;
uniform vec3				u_TCGen0Vector1;
uniform vec3				u_LocalViewOrigin;

uniform int					u_DeformGen;
uniform float				u_DeformParams[5];

uniform vec4				u_DiffuseTexMatrix;
uniform vec4				u_DiffuseTexOffTurb;

uniform mat4				u_ModelViewProjectionMatrix;
uniform mat4				u_ModelMatrix;

//uniform float				u_VertexLerp;
uniform mat4				u_BoneMatrices[20];

uniform vec2				u_textureScale;

uniform int					u_AlphaGen;
uniform vec4				u_BaseColor;
uniform vec4				u_VertColor;

uniform float				u_PortalRange;
uniform vec4				u_PrimaryLightOrigin;

varying vec2				var_TexCoords;
varying vec3				var_Position;
varying vec3				var_Normal;
varying vec4				var_Color;

vec3 DeformPosition(const vec3 pos, const vec3 normal, const vec2 st)
{
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
		func = sign(fract(0.5 - value));
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

vec2 GenTexCoords(int TCGen, vec3 position, vec3 normal, vec3 TCGenVector0, vec3 TCGenVector1)
{
	vec2 tex = attr_TexCoord0;

	switch (TCGen)
	{
		case TCGEN_LIGHTMAP:
		case TCGEN_LIGHTMAP1:
		case TCGEN_LIGHTMAP2:
		case TCGEN_LIGHTMAP3:
			tex = attr_TexCoord1;
		break;

		case TCGEN_ENVIRONMENT_MAPPED:
		{
			vec3 viewer = normalize(u_LocalViewOrigin - position);
			vec2 ref = reflect(viewer, normal).yz;
			tex.s = ref.x * -0.5 + 0.5;
			tex.t = ref.y *  0.5 + 0.5;
		}
		break;

		case TCGEN_VECTOR:
		{
			tex = vec2(dot(position, TCGenVector0), dot(position, TCGenVector1));
		}
		break;
	}

	return tex;
}

vec2 ModTexCoords(vec2 st, vec3 position, vec4 texMatrix, vec4 offTurb)
{
	float amplitude = offTurb.z;
	float phase = offTurb.w * 2.0 * M_PI;
	vec2 st2;
	st2.x = st.x * texMatrix.x + (st.y * texMatrix.z + offTurb.x);
	st2.y = st.x * texMatrix.y + (st.y * texMatrix.w + offTurb.y);

	vec2 offsetPos = vec2(position.x + position.z, position.y);

	vec2 texOffset = sin(offsetPos * (2.0 * M_PI / 1024.0) + vec2(phase));

	return st2 + texOffset * amplitude;
}

vec4 CalcColor(vec3 position, vec3 normal)
{
	vec4 color = u_VertColor * attr_Color + u_BaseColor;
	
	if (USE_RGBA > 0.0)
	{
		if (u_AlphaGen == AGEN_LIGHTING_SPECULAR)
		{
			vec3 viewer = u_LocalViewOrigin - position;
			//vec3 lightDir = normalize(vec3(-960.0, 1980.0, 96.0) - position);
			vec3 lightDir = normalize((u_ModelMatrix * vec4(u_PrimaryLightOrigin.xyz, 1.0)).xyz - position);
			vec3 reflected = -reflect(lightDir, normal);
		
			color.a = clamp(dot(reflected, normalize(viewer)), 0.0, 1.0);
			color.a *= color.a;
			color.a *= color.a;
		}
		else if (u_AlphaGen == AGEN_PORTAL)
		{
			vec3 viewer = u_LocalViewOrigin - position;
			color.a = clamp(length(viewer) / u_PortalRange, 0.0, 1.0);
		}
	}
	
	return color;
}

void main()
{
	vec3 position;
	vec3 normal;

	if (USE_VERTEX_ANIM == 1.0)
	{
		//position  = mix(attr_Position,    attr_Position2,    u_VertexLerp);
		//normal    = mix(attr_Normal,      attr_Normal2,      u_VertexLerp) * 2.0 - 1.0;
		position  = attr_Position;
		normal    = attr_Normal * 2.0 - 1.0;
	}
	else if (USE_SKELETAL_ANIM == 1.0)
	{
		vec4 position4 = vec4(0.0);
		vec4 normal4 = vec4(0.0);
		vec4 originalPosition = vec4(attr_Position, 1.0);
		//vec4 originalNormal = vec4(attr_Normal - vec3(0.5), 0.0);
		vec4 originalNormal = vec4(attr_Normal * 2.0 - 1.0, 0.0);

		for (int i = 0; i < 4; i++)
		{
			int boneIndex = int(attr_BoneIndexes[i]);

			position4 += (u_BoneMatrices[boneIndex] * originalPosition) * attr_BoneWeights[i];
			normal4 += (u_BoneMatrices[boneIndex] * originalNormal) * attr_BoneWeights[i];
		}

		position = position4.xyz;
		normal = normalize(normal4.xyz);
	}
	else
	{
		position  = attr_Position;
		normal    = attr_Normal * 2.0 - 1.0;
	}

	vec2 texCoords = attr_TexCoord0.st;

	if (USE_DEFORM == 1.0)
	{
		position = DeformPosition(position, normal, attr_TexCoord0.st);
	}

	gl_Position = u_ModelViewProjectionMatrix * vec4(position, 1.0);

	//if (USE_VERTEX_ANIM == 1.0 || USE_SKELETAL_ANIM == 1.0)
	{
		position = (u_ModelMatrix * vec4(position, 1.0)).xyz;
		normal = (u_ModelMatrix * vec4(normal, 0.0)).xyz;
	}

	if (USE_TC == 1.0)
	{
		texCoords = GenTexCoords(u_TCGen0, position, normal, u_TCGen0Vector0, u_TCGen0Vector1);
		texCoords = ModTexCoords(texCoords, position, u_DiffuseTexMatrix, u_DiffuseTexOffTurb);
	}

	if (!(u_textureScale.x <= 0.0 && u_textureScale.y <= 0.0) && !(u_textureScale.x == 1.0 && u_textureScale.y == 1.0))
	{
		texCoords *= u_textureScale;
	}

	var_Color = CalcColor(position, normal);
	var_Position = position;
	var_Normal = normal;
	var_TexCoords = texCoords;
}
