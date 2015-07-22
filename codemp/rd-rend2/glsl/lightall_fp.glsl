uniform sampler2D u_DiffuseMap;
varying vec4	var_Local1; // parallaxScale, haveSpecular, specularScale, 0
varying vec4	u_Local2; // ExtinctionCoefficient
varying vec4	u_Local3; // RimScalar, MaterialThickness, subSpecPower
varying vec2	var_Dimensions;

#if defined(USE_LIGHTMAP)
uniform sampler2D u_LightMap;
#endif

#if defined(USE_NORMALMAP)
uniform sampler2D u_NormalMap;
#endif

#if defined(USE_DELUXEMAP)
uniform sampler2D u_DeluxeMap;
#endif

#if defined(USE_SPECULARMAP)
uniform sampler2D u_SpecularMap;
#endif

#if defined(USE_SHADOWMAP)
uniform sampler2D u_ShadowMap;
#endif

#if defined(USE_CUBEMAP)
#define textureCubeLod textureLod // UQ1: > ver 140 support
uniform samplerCube u_CubeMap;
#endif

#if defined(USE_NORMALMAP) || defined(USE_DELUXEMAP) || defined(USE_SPECULARMAP) || defined(USE_CUBEMAP)
// y = deluxe, w = cube
uniform vec4      u_EnableTextures;
#endif

#if defined(USE_LIGHT_VECTOR) && !defined(USE_FAST_LIGHT)
uniform vec3      u_DirectedLight;
uniform vec3      u_AmbientLight;
uniform vec4		u_LightOrigin;
#endif

#if defined(USE_PRIMARY_LIGHT) || defined(USE_SHADOWMAP)
uniform vec3  u_PrimaryLightColor;
uniform vec3  u_PrimaryLightAmbient;
#endif

//#if defined(USE_LIGHT) && !defined(USE_FAST_LIGHT)
uniform vec4      u_NormalScale;
uniform vec4      u_SpecularScale;
//#endif

#if defined(USE_LIGHT) && !defined(USE_FAST_LIGHT)
#if defined(USE_CUBEMAP)
uniform vec4      u_CubeMapInfo;
#endif
#endif


varying vec4      var_TexCoords;

varying vec4      var_Color;

varying vec3   var_ViewDir;

#if (defined(USE_LIGHT) && !defined(USE_FAST_LIGHT))
  #if defined(USE_VERT_TANGENT_SPACE)
varying vec4   var_Normal;
varying vec4   var_Tangent;
varying vec4   var_Bitangent;
  #else
varying vec3   var_Normal;
  #endif
#else
  #if defined(USE_VERT_TANGENT_SPACE)
varying vec4   var_Normal;
varying vec4   var_Tangent;
varying vec4   var_Bitangent;
  #else
varying vec3   var_Normal;
  #endif
#endif

varying vec3 var_N;

#if defined(USE_LIGHT) && !defined(USE_FAST_LIGHT)
varying vec4      var_LightDir;
#endif

#if defined(USE_PRIMARY_LIGHT) || defined(USE_SHADOWMAP)
varying vec4      var_PrimaryLightDir;
#endif

varying vec3   var_vertPos;

out vec4 out_Glow;

#define EPSILON 0.00000001

#if defined(USE_PARALLAXMAP) || defined(USE_PARALLAXMAP_NONORMALS)
  #if defined(USE_PARALLAXMAP)
	float SampleDepth(sampler2D normalMap, vec2 t)
	{
		#if defined(SWIZZLE_NORMALMAP)
			return 1.0 - texture2D(normalMap, t).r;
		#else
			return 1.0 - texture2D(normalMap, t).a;
		#endif
	}
  #endif

  #if defined(USE_PARALLAXMAP_NONORMALS)
	float SampleDepth(sampler2D normalMap, vec2 t)
	{
		vec3 color = texture2D(u_DiffuseMap, t).rgb;

#define const_1 ( 16.0 / 255.0)
#define const_2 (255.0 / 219.0)
		vec3 color2 = ((color - const_1) * const_2);
#define const_3 ( 125.0 / 255.0)
#define const_4 (255.0 / 115.0)
		
		color = ((color - const_3) * const_4);

		color = clamp(color * color * (color * 5.0), 0.0, 1.0); // testing

		vec3 orig_color = color + color2;

		orig_color = clamp(orig_color * 2.5, 0.0, 1.0); // testing

		orig_color = clamp(orig_color, 0.0, 1.0);
		float combined_color2 = orig_color.r + orig_color.g + orig_color.b;
		combined_color2 /= 4.0;

		return clamp(1.0 - combined_color2, 0.0, 1.0);
	}
  #endif


float RayIntersectDisplaceMap(vec2 dp, vec2 ds, sampler2D normalMap)
{
  #if !defined(FAST_PARALLAX)
	float MAX_SIZE = var_Local1.x / 3.0;//1.25;//1.5;//1.0;
	if (MAX_SIZE > 1.75) MAX_SIZE = 1.75;
	if (MAX_SIZE < 1.0) MAX_SIZE = 1.0;
	const int linearSearchSteps = 16;
	const int binarySearchSteps = 6;

	// current size of search window
	float size = MAX_SIZE / float(linearSearchSteps);

	// current depth position
	float depth = 0.0;

	// best match found (starts with last position 1.0)
	float bestDepth = MAX_SIZE;

    #if 1
	// search front to back for first point inside object
	for(int i = 0; i < linearSearchSteps - 1; ++i)
	{
		depth += size;
		
		float t = SampleDepth(normalMap, dp + ds * depth) * MAX_SIZE;
		
		//if(bestDepth > 0.996)		// if no depth found yet
		if(bestDepth > MAX_SIZE - (MAX_SIZE / linearSearchSteps))		// if no depth found yet
			if(depth >= t)
				bestDepth = depth;	// store best depth
	}
    #else
	bestDepth = MAX_SIZE;
    #endif

	depth = bestDepth;
	
	// recurse around first point (depth) for closest match
	for(int i = 0; i < binarySearchSteps; ++i)
	{
		size *= 0.5;

		float t = SampleDepth(normalMap, dp + ds * depth) * MAX_SIZE;
		
		if(depth >= t)
		{
			bestDepth = depth;
			depth -= 2.0 * size;
		}

		depth += size;
	}

	return bestDepth * var_Local1.x;
  #else
	float depth = SampleDepth(normalMap, dp) - 1.0;
	return depth * var_Local1.x;
  #endif
}
#endif

vec3 EnvironmentBRDF(float gloss, float NE, vec3 specular)
{
	vec4 t = vec4( 1/0.96, 0.475, (0.0275 - 0.25 * 0.04)/0.96,0.25 ) * gloss;
	t += vec4( 0.0, 0.0, (0.015 - 0.75 * 0.04)/0.96,0.75 );
	float a0 = t.x * min( t.y, exp2( -9.28 * NE ) ) + t.z;
	float a1 = t.w;
	return clamp( a0 + specular * ( a1 - a0 ), 0.0, 1.0 );
}

float CalcGGX(float NH, float gloss)
{
	float a_sq = exp2(gloss * -13.0 + 1.0);
	float d = ((NH * NH) * (a_sq - 1.0) + 1.0);
	return a_sq / (d * d);
}

float CalcFresnel(float EH)
{
	return exp2(-10.0 * EH);
}

float CalcVisibility(float NH, float NL, float NE, float EH, float gloss)
{
	float roughness = exp2(gloss * -6.5);

	float k = roughness + 1.0;
	k *= k * 0.125;

	float k2 = 1.0 - k;
	
	float invGeo1 = NL * k2 + k;
	float invGeo2 = NE * k2 + k;

	return 1.0 / (invGeo1 * invGeo2);
}


vec3 CalcSpecular(vec3 specular, float NH, float NL, float NE, float EH, float gloss, float shininess)
{
	float distrib = CalcGGX(NH, gloss);

	vec3 fSpecular = mix(specular, vec3(1.0), CalcFresnel(EH));

	float vis = CalcVisibility(NH, NL, NE, EH, gloss);

	return fSpecular * (distrib * vis);
}


float CalcLightAttenuation(float point, float normDist)
{
	// zero light at 1.0, approximating q3 style
	// also don't attenuate directional light
	float attenuation = (0.5 * normDist - 1.5) * point + 1.0;

	// clamp attenuation
	#if defined(NO_LIGHT_CLAMP)
	attenuation = max(attenuation, 0.0);
	#else
	attenuation = clamp(attenuation, 0.0, 1.0);
	#endif

	return attenuation;
}

mat3 cotangent_frame( vec3 N, vec3 p, vec2 uv )
{
	// get edge vectors of the pixel triangle
	vec3 dp1 = dFdx( p );
	vec3 dp2 = dFdy( p );
	vec2 duv1 = dFdx( uv );
	vec2 duv2 = dFdy( uv );

	// solve the linear system
	vec3 dp2perp = cross( dp2, N );
	vec3 dp1perp = cross( N, dp1 );
	vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
	vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;

	// construct a scale-invariant frame 
	float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );
	return mat3( T * invmax, B * invmax, N );
}
 
#if defined(USE_LIGHT_VECTOR) && !defined(USE_FAST_LIGHT)
float halfLambert(in vec3 vect1, in vec3 vect2)
{
    float product = dot(vect1,vect2);
    return product * 0.5 + 0.5;
}
 
float blinnPhongSpecular(in vec3 normalVec, in vec3 lightVec, in float specPower)
{
    vec3 halfAngle = normalize(normalVec + lightVec);
    return pow(clamp(0.0,1.0,dot(normalVec,halfAngle)),specPower);
}
 
// Main fake sub-surface scatter lighting function

vec3 ExtinctionCoefficient = u_Local2.xyz;
float RimScalar = u_Local3.x;
float MaterialThickness = u_Local3.y;
float SpecPower = u_Local3.z;

vec4 subScatterFS(vec4 BaseColor, vec4 SpecColor, vec3 lightVec, vec3 LightColor, vec3 eyeVec, vec3 worldNormal, float SpecPower)
{
    float attenuation = 10.0 * (1.0 / distance(u_LightOrigin.xyz,var_vertPos.xyz));
    vec3 eVec = normalize(eyeVec);
    vec3 lVec = normalize(lightVec);
    vec3 wNorm = normalize(worldNormal);
     
    vec4 dotLN = vec4(halfLambert(lVec,wNorm) * attenuation);
    dotLN *= BaseColor;
     
    vec3 indirectLightComponent = vec3(MaterialThickness * max(0.0,dot(-wNorm,lVec)));
    indirectLightComponent += MaterialThickness * halfLambert(-eVec,lVec);
    indirectLightComponent *= attenuation;
    indirectLightComponent.r *= ExtinctionCoefficient.r;
    indirectLightComponent.g *= ExtinctionCoefficient.g;
    indirectLightComponent.b *= ExtinctionCoefficient.b;
     
    vec3 rim = vec3(1.0 - max(0.0,dot(wNorm,eVec)));
    rim *= rim;
    rim *= max(0.0,dot(wNorm,lVec)) * SpecColor.rgb;
     
    vec4 finalCol = dotLN + vec4(indirectLightComponent,1.0);
    finalCol.rgb += (rim * RimScalar * attenuation * finalCol.a);
    finalCol.rgb += vec3(blinnPhongSpecular(wNorm,lVec,SpecPower) * attenuation * SpecColor * finalCol.a * 0.05);
    finalCol.rgb *= LightColor.rgb;
     
    return finalCol;   
}
#endif

void main()
{
	vec3 viewDir, lightColor, ambientColor;
	vec3 L, N, E, H;
	float NL, NH, NE, EH, attenuation;
	vec2 tex_offset = vec2(1.0 / var_Dimensions.x, 1.0 / var_Dimensions.y);

#if defined(USE_LIGHT) && !defined(USE_FAST_LIGHT)
  #if defined(USE_VERT_TANGENT_SPACE)
	//mat3 tangentToWorld = mat3(var_Tangent.xyz, var_Bitangent.xyz, var_Normal.xyz);
	//viewDir = vec3(var_Normal.w, var_Tangent.w, var_Bitangent.w);
	mat3 tangentToWorld = cotangent_frame(var_Normal.xyz, -var_ViewDir, var_TexCoords.xy);
	viewDir = var_ViewDir;
  #else
	mat3 tangentToWorld = cotangent_frame(var_Normal.xyz, -var_ViewDir, var_TexCoords.xy);
	//mat3 tangentToWorld = mat3(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
	viewDir = var_ViewDir;
  #endif

	E = normalize(viewDir);

	L = var_LightDir.xyz;
  #if defined(USE_DELUXEMAP)
	L += (texture2D(u_DeluxeMap, var_TexCoords.zw).xyz - vec3(0.5)) * u_EnableTextures.y;
  #endif
	float sqrLightDist = dot(L, L);
#else
  #if defined(USE_VERT_TANGENT_SPACE)
	mat3 tangentToWorld = mat3(var_Tangent.xyz, var_Bitangent.xyz, var_Normal.xyz);
	viewDir = vec3(var_Normal.w, var_Tangent.w, var_Bitangent.w);
  #else
	mat3 tangentToWorld = cotangent_frame(var_Normal.xyz, -var_ViewDir, var_TexCoords.xy);
	viewDir = var_ViewDir;
  #endif
	E = normalize(viewDir);
#endif

#if defined(USE_LIGHTMAP)
	vec4 lightmapColor = texture2D(u_LightMap, var_TexCoords.zw);
  #if defined(RGBM_LIGHTMAP)
	lightmapColor.rgb *= lightmapColor.a;
  #endif
#endif

	vec2 texCoords = var_TexCoords.xy;

#if defined(USE_PARALLAXMAP) || defined(USE_PARALLAXMAP_NONORMALS)
	vec3 offsetDir = normalize(E * tangentToWorld);

	offsetDir.xy *= tex_offset * -var_Local1.x;//-4.0;//-5.0; // -3.0

  #if defined(USE_NORMALMAP)
	texCoords += offsetDir.xy * RayIntersectDisplaceMap(texCoords, offsetDir.xy, u_NormalMap);
  #else
	texCoords += offsetDir.xy * RayIntersectDisplaceMap(texCoords, offsetDir.xy, u_DiffuseMap);
  #endif
#endif

	vec4 diffuse = texture2D(u_DiffuseMap, texCoords);

#if defined(USE_GAMMA2_TEXTURES)
	diffuse.rgb *= diffuse.rgb;
#endif

#if defined(USE_PARALLAXMAP) || defined(USE_PARALLAXMAP_NONORMALS)
	float fakedepth = SampleDepth(u_DiffuseMap, texCoords);
#else
	float fakedepth = (diffuse.r + diffuse.g + diffuse.b) / 3.0; // meh
#endif

#if defined(USE_LIGHT) && !defined(USE_FAST_LIGHT)
	ambientColor = vec3 (0.0);
	attenuation = 1.0;

  #if defined(USE_LIGHTMAP)
	lightColor	= lightmapColor.rgb * var_Color.rgb;
  #elif defined(USE_LIGHT_VECTOR)
	lightColor	= u_DirectedLight * var_Color.rgb;
	ambientColor = u_AmbientLight * var_Color.rgb;
	attenuation = CalcLightAttenuation(float(var_LightDir.w > 0.0), var_LightDir.w / sqrLightDist);
  #elif defined(USE_LIGHT_VERTEX)
	lightColor	= var_Color.rgb;
  #endif

#if defined(USE_PARALLAXMAP) || defined(USE_PARALLAXMAP_NONORMALS)
  #if defined(USE_NORMALMAP)
	float norm = (fakedepth - 0.5);
	float norm2 = 0.0 - (fakedepth - 0.5);
    #if defined(SWIZZLE_NORMALMAP)
		N.xy = vec2(norm, norm2);
    #else
		N.xy = vec2(norm, norm2);
    #endif
	N.xy *= u_NormalScale.xy;
	N.z = sqrt(clamp((0.25 - N.x * N.x) - N.y * N.y, 0.0, 1.0));
	N = tangentToWorld * N;
  #else
	N = var_Normal.xyz;
  #endif
  N = var_Normal.xyz;
#endif

	N = normalize(N);
	L /= sqrt(sqrLightDist);

  #if defined(USE_SHADOWMAP) 
	vec2 shadowTex = gl_FragCoord.xy * r_FBufScale;
	float shadowValue = texture2D(u_ShadowMap, shadowTex).r;

	// surfaces not facing the light are always shadowed
	shadowValue *= float(dot(var_Normal.xyz, var_PrimaryLightDir.xyz) > 0.0);

    #if defined(SHADOWMAP_MODULATE)
	//vec3 shadowColor = min(u_PrimaryLightAmbient, lightColor);
	vec3 shadowColor = u_PrimaryLightAmbient * lightColor;

      #if 0
	shadowValue = 1.0 + (shadowValue - 1.0) * clamp(dot(L, var_PrimaryLightDir.xyz), 0.0, 1.0);
      #endif
	lightColor = mix(shadowColor, lightColor, shadowValue);
    #endif
  #endif

  #if defined(USE_LIGHTMAP) || defined(USE_LIGHT_VERTEX)
	ambientColor = lightColor;
	float surfNL = clamp(dot(var_Normal.xyz, L), 0.0, 1.0);
	lightColor /= max(surfNL, 0.25);
	ambientColor = clamp(ambientColor - lightColor * surfNL, 0.0, 1.0);
  #endif
  
	vec3 reflectance;

	NL = clamp(dot(N, L), 0.0, 1.0);
	NE = clamp(dot(N, E), 0.0, 1.0);

  #if defined(USE_SPECULARMAP)
	vec4 specular;

	if (var_Local1.g != 0.0)
	{// Real specMap...
		specular = texture2D(u_SpecularMap, texCoords);
		specular.a = ((clamp((1.0 - specular.a), 0.0, 1.0) * 0.5) + 0.5);
		specular.a = clamp((specular.a * 2.0) * specular.a, 0.2, 0.9);
	}
	else
	{// Fake it...
		if (var_Local1.b > 0.0)
		{
			specular = vec4(1.0-fakedepth) * diffuse;
			specular.a = ((clamp((1.0 - fakedepth), 0.0, 1.0) * 0.5) + 0.5);
			specular.a = clamp((specular.a * 2.0) * specular.a, 0.2, 0.9);
		}
		else
		{
			specular = vec4(1.0);
		}
	}

    #if defined(USE_GAMMA2_TEXTURES)
	specular.rgb *= specular.rgb;
    #endif
  #else
	vec4 specular = vec4(1.0);
  #endif

	if (var_Local1.b > 0.0)
	{
		if (length(u_SpecularScale) != 0.0 && length(u_SpecularScale) != 1.0) // Shader Specified...
			specular *= u_SpecularScale;
	#if defined(USE_CUBEMAP)
		else if (var_Local1.b > 0.0)
			specular *= var_Local1.b;// * var_Local1.b;
	#endif
		else // Material Defaults...
			specular *= var_Local1.b;
	}
	else
		specular *= u_SpecularScale;

  #if defined(SPECULAR_IS_METALLIC)
	float metallic = specular.r;

	specular.rgb = (0.96 * metallic) * diffuse.rgb + vec3(0.04);
	diffuse.rgb *= 1.0 - metallic;
  #else
	diffuse.rgb *= vec3(1.0) - specular.rgb;
  #endif

	reflectance = diffuse.rgb;

  #if defined(r_deluxeSpecular) || defined(USE_LIGHT_VECTOR)
	float adjGloss = specular.a;
	float adjShininess = exp2(specular.a * 13.0);

    #if !defined(USE_LIGHT_VECTOR)
	adjGloss *= r_deluxeSpecular;
	adjShininess = exp2(adjGloss * 13.0);
    #endif

	H = normalize(L + E);

	EH = clamp(dot(E, H), 0.0, 1.0);
	NH = clamp(dot(N, H), 0.0, 1.0);

    #if !defined(USE_LIGHT_VECTOR)
	reflectance += CalcSpecular(specular.rgb, NH, NL, NE, EH, adjGloss, adjShininess) * r_deluxeSpecular;
    #else
	reflectance += CalcSpecular(specular.rgb, NH, NL, NE, EH, adjGloss, adjShininess);
    #endif
  #endif

  if (var_Local1.b > 0.0)
	gl_FragColor.rgb  = (((lightColor   * reflectance * (attenuation * NL)) * 2.0) + (lightColor   * (reflectance * specular.a) * (attenuation * NL))) / 3.0;
  else
	gl_FragColor.rgb  = lightColor   * reflectance * (attenuation * NL);

#if 0
	vec3 aSpecular = EnvironmentBRDF(specular.a, NE, specular.rgb);

	float hemiDiffuseUp    = N.z * 0.5 + 0.5;
	float hemiDiffuseDown  = 1.0 - hemiDiffuseUp;
	float hemiSpecularUp   = mix(hemiDiffuseUp, float(N.z >= 0.0), specular.a);
	float hemiSpecularDown = 1.0 - hemiSpecularUp;

	gl_FragColor.rgb += ambientColor * 0.75 * (diffuse.rgb * hemiDiffuseUp   + aSpecular * hemiSpecularUp);
	gl_FragColor.rgb += ambientColor * 0.25 * (diffuse.rgb * hemiDiffuseDown + aSpecular * hemiSpecularDown);
#else
	gl_FragColor.rgb += ambientColor * (diffuse.rgb + specular.rgb);
#endif

  #if defined(USE_CUBEMAP)
	if (var_Local1.b > 0.8) {
		reflectance = EnvironmentBRDF(specular.a, NE, specular.rgb);

		vec3 R = reflect(E, N);

		vec3 parallax = u_CubeMapInfo.xyz + u_CubeMapInfo.w * viewDir;

		vec3 cubeLightColor = textureCubeLod(u_CubeMap, R + parallax, 7.0 - specular.a * 7.0).rgb * u_EnableTextures.w;

		gl_FragColor.rgb += cubeLightColor * reflectance;
	}
  #endif

  #if defined(USE_PRIMARY_LIGHT)
	vec3 L2, H2;
	float NL2, EH2, NH2;

	L2 = var_PrimaryLightDir.xyz;

	// enable when point lights are supported as primary lights
	//sqrLightDist = dot(L2, L2);
	//L2 /= sqrt(sqrLightDist);

	NL2 = clamp(dot(N, L2), 0.0, 1.0);

	H2 = normalize(L2 + E);
	EH2 = clamp(dot(E, H2), 0.0, 1.0);
	NH2 = clamp(dot(N, H2), 0.0, 1.0);

	reflectance  = diffuse.rgb;
	reflectance += CalcSpecular(specular.rgb, NH2, NL2, NE, EH2, specular.a, exp2(specular.a * 13.0));

	lightColor = u_PrimaryLightColor * var_Color.rgb;

	// enable when point lights are supported as primary lights
	//lightColor *= CalcLightAttenuation(float(u_PrimaryLightDir.w > 0.0), u_PrimaryLightDir.w / sqrLightDist);

    #if defined(USE_SHADOWMAP)
	lightColor *= shadowValue;
    #endif

	// enable when point lights are supported as primary lights
	//lightColor *= CalcLightAttenuation(float(u_PrimaryLightDir.w > 0.0), u_PrimaryLightDir.w / sqrLightDist);

	gl_FragColor.rgb += lightColor * reflectance * NL2;
  #endif

  gl_FragColor.a = diffuse.a * var_Color.a;

  #if defined(USE_LIGHT_VECTOR) && !defined(USE_FAST_LIGHT)
  // Let's add some sub-surface scatterring shall we???
  if (MaterialThickness > 0.0)
  {
  #if defined(USE_PRIMARY_LIGHT)
	gl_FragColor += subScatterFS(gl_FragColor, specular, L2, lightColor.xyz, E, N, specular.a);
  #else
	gl_FragColor += subScatterFS(gl_FragColor, specular, L, var_Color.xyz, E, N, specular.a);
  #endif
  }
  #endif
#else
	lightColor = var_Color.rgb;
  #if defined(USE_LIGHTMAP) 
	lightColor *= lightmapColor.rgb;
  #endif

  gl_FragColor = vec4 (diffuse.rgb * lightColor, diffuse.a * var_Color.a);
#endif
	
#if defined(USE_GLOW_BUFFER)
	out_Glow = gl_FragColor;
#else
	out_Glow = vec4(0.0);
#endif
}
