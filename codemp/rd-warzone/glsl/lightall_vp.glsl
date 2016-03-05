//precision highp float;

attribute vec2 attr_TexCoord0;

uniform float	u_Time;


#if defined(USE_TESSELLATION)
out vec4 Normal_CS_in;
out vec2 TexCoord_CS_in;
out vec4 WorldPos_CS_in;
#endif

#if defined(USE_LIGHTMAP) || defined(USE_TCGEN)
attribute vec2 attr_TexCoord1;
#endif
attribute vec4 attr_Color;

attribute vec3 attr_Position;
attribute vec3 attr_Normal;
attribute vec4 attr_Tangent;

#if defined(USE_VERTEX_ANIMATION)
attribute vec3 attr_Position2;
attribute vec3 attr_Normal2;
attribute vec4 attr_Tangent2;
#elif defined(USE_SKELETAL_ANIMATION)
attribute vec4 attr_BoneIndexes;
attribute vec4 attr_BoneWeights;
#endif

#if defined(USE_DELUXEMAP)
uniform vec4   u_EnableTextures; // x = normal, y = deluxe, z = specular, w = cube
#endif

uniform vec3   u_ViewOrigin;

#if defined(USE_TCGEN)
uniform int    u_TCGen0;
uniform vec3   u_TCGen0Vector0;
uniform vec3   u_TCGen0Vector1;
uniform vec3   u_LocalViewOrigin;
#endif

#if defined(USE_TCMOD)
uniform vec4   u_DiffuseTexMatrix;
uniform vec4   u_DiffuseTexOffTurb;
#endif

uniform mat4   u_ModelViewProjectionMatrix;
uniform mat4	u_ViewProjectionMatrix;
uniform mat4   u_ModelMatrix;

uniform vec4   u_BaseColor;
uniform vec4   u_VertColor;

#if defined(USE_VERTEX_ANIMATION)
uniform float  u_VertexLerp;
#elif defined(USE_SKELETAL_ANIMATION)
uniform mat4   u_BoneMatrices[20];
#endif

uniform vec4  u_PrimaryLightOrigin;
uniform float u_PrimaryLightRadius;

varying vec2   var_TexCoords;
varying vec2   var_TexCoords2;

varying vec4   var_Color;

varying vec3 var_N;
varying vec4   var_Normal;
varying vec4   var_Tangent;
varying vec4   var_Bitangent;
varying vec3   var_ViewDir;

varying vec4   var_PrimaryLightDir;

varying vec3   var_vertPos;
varying float  var_Time;


#if defined(USE_TCGEN)
vec2 GenTexCoords(int TCGen, vec3 position, vec3 normal, vec3 TCGenVector0, vec3 TCGenVector1)
{
	vec2 tex = attr_TexCoord0.st;

	if (TCGen >= TCGEN_LIGHTMAP && TCGen <= TCGEN_LIGHTMAP3)
	{
		tex = attr_TexCoord1.st;
	}
	else if (TCGen == TCGEN_ENVIRONMENT_MAPPED)
	{
		vec3 viewer = normalize(u_LocalViewOrigin - position);
		vec2 ref = reflect(viewer, normal).yz;
		tex.s = ref.x * -0.5 + 0.5;
		tex.t = ref.y *  0.5 + 0.5;
	}
	else if (TCGen == TCGEN_VECTOR)
	{
		tex = vec2(dot(position, TCGenVector0), dot(position, TCGenVector1));
	}

	return tex;
}
#endif

#if defined(USE_TCMOD)
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
#endif



void main()
{
	vec3 normal = vec3(attr_Normal.xyz);
	vec3 position = vec3(attr_Position.xyz);

#if defined(USE_VERTEX_ANIMATION)
	position  = mix(attr_Position,    attr_Position2,    u_VertexLerp);
	normal    = mix(attr_Normal,      attr_Normal2,      u_VertexLerp);
	vec3 tangent   = mix(attr_Tangent.xyz, attr_Tangent2.xyz, u_VertexLerp);
#elif defined(USE_SKELETAL_ANIMATION)
	vec4 position4 = vec4(0.0);
	vec4 normal4 = vec4(0.0);
	vec4 originalPosition = vec4(attr_Position, 1.0);
	vec4 originalNormal = vec4(attr_Normal - vec3 (0.5), 0.0);
	vec4 tangent4 = vec4(0.0);
	vec4 originalTangent = vec4(attr_Tangent.xyz - vec3(0.5), 0.0);

	for (int i = 0; i < 4; i++)
	{
		int boneIndex = int(attr_BoneIndexes[i]);

		position4 += (u_BoneMatrices[boneIndex] * originalPosition) * attr_BoneWeights[i];
		normal4 += (u_BoneMatrices[boneIndex] * originalNormal) * attr_BoneWeights[i];
		tangent4 += (u_BoneMatrices[boneIndex] * originalTangent) * attr_BoneWeights[i];
	}

	position = position4.xyz;
	normal = normalize (normal4.xyz);
	vec3 tangent = normalize (tangent4.xyz);
#else
	position  = attr_Position;
	normal    = attr_Normal;
	vec3 tangent   = attr_Tangent.xyz;
#endif

#if !defined(USE_SKELETAL_ANIMATION)
	normal  = normal  * 2.0 - vec3(1.0);
	tangent = tangent * 2.0 - vec3(1.0);
#endif

#if defined(USE_TCGEN)
	vec2 texCoords = GenTexCoords(u_TCGen0, position, normal, u_TCGen0Vector0, u_TCGen0Vector1);
#else
	vec2 texCoords = attr_TexCoord0.st;
#endif

#if defined(USE_TCMOD)
	var_TexCoords.xy = ModTexCoords(texCoords, position, u_DiffuseTexMatrix, u_DiffuseTexOffTurb);
#else
	var_TexCoords.xy = texCoords;
#endif

	gl_Position = u_ModelViewProjectionMatrix * vec4(position, 1.0);

	vec3 preMMPos = position.xyz;
	vec3 preMMNorm = normal.xyz;

#if defined(USE_MODELMATRIX)
	position  = (u_ModelMatrix * vec4(position, 1.0)).xyz;
	normal    = (u_ModelMatrix * vec4(normal,   0.0)).xyz;
	tangent   = (u_ModelMatrix * vec4(tangent,  0.0)).xyz;
#endif


	vec3 bitangent = cross(normal, tangent) * (attr_Tangent.w * 2.0 - 1.0);




#if defined(USE_LIGHTMAP)
	var_TexCoords2 = attr_TexCoord1.st;
#endif

	var_Color = u_VertColor * attr_Color + u_BaseColor;

	var_PrimaryLightDir.xyz = u_PrimaryLightOrigin.xyz - (position * u_PrimaryLightOrigin.w);
	var_PrimaryLightDir.w = u_PrimaryLightRadius * u_PrimaryLightRadius;


	vec3 viewDir = u_ViewOrigin - position;
	var_ViewDir = viewDir;

  // store view direction in tangent space to save on varyings
  var_Normal    = vec4(normal,    viewDir.x);
  var_Tangent   = vec4(tangent,   viewDir.y);
  var_Bitangent = vec4(bitangent, viewDir.z);

  var_vertPos = gl_Position.xyz;
  var_Time = u_Time;

#if defined(USE_TESSELLATION)
  TexCoord_CS_in = var_TexCoords.xy;
  Normal_CS_in = vec4(preMMNorm,    viewDir.x);//var_Normal;
  gl_Position = vec4(preMMPos, 1.0);
#endif
}
