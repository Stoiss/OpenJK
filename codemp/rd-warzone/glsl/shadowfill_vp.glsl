attribute vec3  attr_Position;
attribute vec3  attr_Normal;
attribute vec4  attr_TexCoord0;

//#if defined(USE_VERTEX_ANIMATION)
attribute vec3  attr_Position2;
attribute vec3  attr_Normal2;
//#endif

//#if defined(USE_DEFORM_VERTEXES)
uniform int     u_DeformGen;
uniform float    u_DeformParams[7];
//#endif

uniform float   u_Time;
uniform mat4    u_ModelViewProjectionMatrix;

uniform mat4   u_ModelMatrix;

//#if defined(USE_VERTEX_ANIMATION)
uniform float   u_VertexLerp;
//#endif

//varying vec3    var_Position;

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

	if (u_DeformGen == DGEN_PROJECTION_SHADOW)
	{
		vec3 ground = vec3(
			u_DeformParams[0],
			u_DeformParams[1],
			u_DeformParams[2]);
		float groundDist = u_DeformParams[3];
		vec3 lightDir = vec3(
			u_DeformParams[4],
			u_DeformParams[5],
			u_DeformParams[6]);

		float d = dot(lightDir, ground);

		lightDir = lightDir * max(0.5 - d, 0.0) + ground;
		d = 1.0 / dot(lightDir, ground);

		vec3 lightPos = lightDir * d;

		return pos - lightPos * dot(pos, ground) + groundDist;
	}
	else if (u_DeformGen == DGEN_WAVE_SIN)
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

void main()
{
	vec3 position  = mix(attr_Position, attr_Position2, u_VertexLerp);
	vec3 normal    = mix(attr_Normal,   attr_Normal2,   u_VertexLerp) * 2.0 - 1.0;
	//normal = normalize(normal - vec3(0.5));

	position = DeformPosition(position, normal, attr_TexCoord0.st);

	gl_Position = u_ModelViewProjectionMatrix * vec4(position, 1.0);
	
	//var_Position  = (u_ModelMatrix * vec4(position, 1.0)).xyz;
}
