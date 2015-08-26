uniform sampler2D u_DiffuseMap;
uniform vec2	u_Dimensions;
uniform vec4	u_Local1; // parallaxScale, haveSpecular, specularScale, materialType
uniform vec4	u_Local2; // ExtinctionCoefficient
uniform vec4	u_Local3; // RimScalar, MaterialThickness, subSpecPower, cubemapScale
uniform vec4	u_Local4; // haveNormalMap, isMetalic, hasRealSubsurfaceMap, useSteepParallax

#define ARGHFUCKTHISSHIT

varying float  var_Time;

#if defined(USE_LIGHTMAP)
uniform sampler2D u_LightMap;
#endif

//#if defined(USE_NORMALMAP)
uniform sampler2D u_NormalMap;
//#endif

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

uniform sampler2D u_SubsurfaceMap;

//#if defined(USE_NORMALMAP) || defined(USE_DELUXEMAP) || defined(USE_SPECULARMAP) || defined(USE_CUBEMAP)
// y = deluxe, w = cube
uniform vec4      u_EnableTextures;
//#endif

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
	{// Provides enhanced parallax depths without stupid distortions... Also provides a nice backup specular map...
		vec3 color = texture2D(u_DiffuseMap, t).rgb;

#define const_1 ( 16.0 / 255.0)
#define const_2 (255.0 / 219.0)
		vec3 color2 = ((color - const_1) * const_2);
#define const_3 ( 125.0 / 255.0)
#define const_4 (255.0 / 115.0)
		color = ((color - const_3) * const_4);

		color = clamp(color * color * (color * 5.0), 0.0, 1.0); // 1st half "color * color" darkens, 2nd half "* color * 5.0" increases the mids...

		vec3 orig_color = color + color2;

		orig_color = clamp(orig_color * 2.5, 0.0, 1.0); // Lightens the new mixed version...

		float combined_color2 = orig_color.r + orig_color.g + orig_color.b;
		combined_color2 /= 4.0; // Darkens the whole thing a litttle...

		// Returns inverse of the height. Result is mostly around 1.0 (so we don't stand on a surface far below us), with deep dark areas (cracks, edges, etc)...
		float height = clamp(1.0 - combined_color2, 0.0, 1.0);
		return height;
	}
  #endif


float RayIntersectDisplaceMap(vec2 dp, vec2 ds, sampler2D normalMap)
{
	if (u_Local1.x == 0.0)
		return 0.0;
	
  #if !defined(FAST_PARALLAX)
	float MAX_SIZE = u_Local1.x / 3.0;//1.25;//1.5;//1.0;
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

	return bestDepth * u_Local1.x;
  #else
	float depth = SampleDepth(normalMap, dp) - 1.0;
	return depth * u_Local1.x;
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

vec4 subScatterFS(vec4 BaseColor, vec4 SpecColor, vec3 lightVec, vec3 LightColor, vec3 eyeVec, vec3 worldNormal, vec2 texCoords)
{
	vec4 subsurface = vec4(ExtinctionCoefficient, MaterialThickness);

	if (u_Local4.z != 0.0)
	{// We have a subsurface image, use it instead...
		subsurface = texture2D(u_SubsurfaceMap, texCoords.xy);
	}
	else if (length(ExtinctionCoefficient) == 0.0)
	{// Default if not specified...
		subsurface.rgb = vec3(BaseColor.rgb);
	}

	if (MaterialThickness == 0.0)
	{// Default if not specified...
		MaterialThickness = 0.8;
	}
	
	if (subsurface.a == 0.0 && MaterialThickness != 0.0)
	{// Backup in case image is missing alpha channel...
		subsurface.a = MaterialThickness;
	}

	subsurface.a = 1.0 - subsurface.a;

	if (RimScalar == 0.0)
	{// Default if not specified...
		RimScalar = 0.5;
	}

	if (SpecPower == 0.0)
	{// Default if not specified...
		SpecPower = 0.3;
	}

	float attenuation = 10.0 * (1.0 / distance(u_LightOrigin.xyz,var_vertPos.xyz));
    vec3 eVec = normalize(eyeVec);
    vec3 lVec = normalize(lightVec);
    vec3 wNorm = normalize(worldNormal);
     
    vec4 dotLN = vec4(halfLambert(lVec,wNorm) * attenuation);
    dotLN *= BaseColor;
     
    vec3 indirectLightComponent = vec3(subsurface.a * max(0.0,dot(-wNorm,lVec)));
    indirectLightComponent += subsurface.a * halfLambert(-eVec,lVec);
    indirectLightComponent *= attenuation;
    indirectLightComponent.r *= subsurface.r;
    indirectLightComponent.g *= subsurface.g;
    indirectLightComponent.b *= subsurface.b;
     
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

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{ 
	vec2 tex_offset = vec2(1.0 / u_Dimensions.x, 1.0 / u_Dimensions.y);
    // number of depth layers
	float height_scale = u_Local1.x;
    const float minLayers = 10;
    const float maxLayers = 20;
    float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));  
    // calculate the size of each layer
    float layerDepth = 1.0 / numLayers;
    // depth of current layer
    float currentLayerDepth = 0.0;
    // the amount to shift the texture coordinates per layer (from vector P)
    vec2 P = viewDir.xy / viewDir.z * height_scale * tex_offset; 
    vec2 deltaTexCoords = P / numLayers;
  
    // get initial values
    vec2  currentTexCoords     = texCoords;
    float currentDepthMapValue = texture2D(u_NormalMap, currentTexCoords).a;
      
    while(currentLayerDepth < currentDepthMapValue)
    {
        // shift texture coordinates along direction of P
        currentTexCoords -= deltaTexCoords;
        // get depthmap value at current texture coordinates
        currentDepthMapValue = texture2D(u_NormalMap, currentTexCoords).a;  
        // get depth of next layer
        currentLayerDepth += layerDepth;  
    }
    
    // -- parallax occlusion mapping interpolation from here on
    // get texture coordinates before collision (reverse operations)
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    // get depth after and before collision for linear interpolation
    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture2D(u_NormalMap, prevTexCoords).a - currentLayerDepth + layerDepth;
 
    // interpolation of texture coordinates
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords;
}

//---------------------------------------------------------
// get pseudo 3d bump background
//---------------------------------------------------------
vec4 BumpyBackground (sampler2D texture, vec2 pos)
{
  #define LINEAR_STEPS 20.0
  #define DISTANCE 0.16
  #define FEATURES 0.5

  vec4 color = vec4(0.0);
  vec2 dir = -(vec2(pos - vec2(0.5, 0.5)) * (DISTANCE / LINEAR_STEPS)) * 0.5;
    
  for (float i = 0.0; i < LINEAR_STEPS; i++) 
  {
    vec4 pixel1 = texture2D(texture, pos - i * dir);
    if (pow(length(pixel1.rgb) / 1.4, 0.20) * (1.0 - FEATURES)
       +pow(length(texture2D(texture, (pos - i * dir) * 2.0).rgb) / 1.4, 0.90) * FEATURES
       > i / LINEAR_STEPS) 
    //color = pixel1 * i / LINEAR_STEPS;
    color += 0.16 * pixel1 * i / LINEAR_STEPS;
  }
  return color;
}

void main()
{
	vec3 viewDir, lightColor, ambientColor;
	vec3 L, N, E, H;
	float NL, NH, NE, EH, attenuation;
	vec2 tex_offset = vec2(1.0 / u_Dimensions.x, 1.0 / u_Dimensions.y);

	/*
	if (u_Local4.r != 0.0)
	{
		//gl_FragColor = vec4(vec3(texture2D(u_NormalMap, var_TexCoords.xy).a), 1.0);
		gl_FragColor = vec4(texture2D(u_NormalMap, var_TexCoords.xy).rgb, 1.0);
		//gl_FragColor = vec4(1.0,0.0,0.0,1.0);
		out_Glow = vec4(0.0);
		return;
	}
	else
	{
		//gl_FragColor = vec4(0.0,1.0,0.0,1.0);
		//gl_FragColor = texture2D(u_NormalMap, var_TexCoords.xy);
		gl_FragColor = vec4(vec3(texture2D(u_NormalMap, var_TexCoords.xy).a), 1.0);
		out_Glow = vec4(0.0);
		return;
	}
	*/
	
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
	vec4 diffuse;
	//vec4 diffuse = texture2D(u_DiffuseMap, texCoords);
	//vec4 diffuse = BumpyBackground(u_DiffuseMap, texCoords);

#if defined(USE_PARALLAXMAP) || defined(USE_PARALLAXMAP_NONORMALS)
	if (u_Local4.a == 0.0)
	{// Normal parallax...
		vec3 offsetDir = normalize(E * tangentToWorld);
		offsetDir.xy *= tex_offset * -u_Local1.x;//-4.0;//-5.0; // -3.0
		texCoords += offsetDir.xy * RayIntersectDisplaceMap(texCoords, offsetDir.xy, u_NormalMap);
		diffuse = texture2D(u_DiffuseMap, texCoords);
	}
	else
	{// Use steep parallax... (below)
		vec3 offsetDir = normalize(E * tangentToWorld);
		texCoords = ParallaxMapping(var_TexCoords.xy, offsetDir);

		//if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
		//	discard;

		diffuse = texture2D(u_DiffuseMap, texCoords);
	}
#else
	diffuse = texture2D(u_DiffuseMap, texCoords);
#endif

#if defined(USE_GAMMA2_TEXTURES)
	diffuse.rgb *= diffuse.rgb;
#endif

	float fakedepth = texture2D(u_NormalMap, texCoords).a;

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
	// WOW - There is something wrong with this. Just makes everything black... Normal maps are correct, but something seems to be wrong here...
    /*if (u_Local4.r != 0.0)
	{// Have a real normal map...
		N.xy = texture2D(u_NormalMap, texCoords).rg - vec2(0.5);
		N.xy *= u_NormalScale.xy;
		N.z = sqrt(clamp((0.25 - N.x * N.x) - N.y * N.y, 0.0, 1.0));
		//N.z = 1.0 - N.z;
		N = tangentToWorld * N;
	}
	else
	{
		N = var_Normal.xyz;
	}*/
	vec3 norm = texture2D(u_NormalMap, texCoords).xzy;
	//N = norm.xyz * 2.0 - 1.0;
	//N = norm.xyz - 0.5;
	N.xy *= u_NormalScale.xy;
	N.z = sqrt(clamp((0.25 - N.x * N.x) - N.y * N.y, 0.0, 1.0));

	N = tangentToWorld * N;
	
#else
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

	gl_FragColor = vec4(0.0);

  #if defined(USE_SPECULARMAP)
	vec4 specular;

	if (u_Local1.g != 0.0)
	{// Real specMap...
		specular = texture2D(u_SpecularMap, texCoords);
		//specular.a = (specular.r + specular.g + specular.b) / 3.0;
		//specular.a = ((clamp((1.0 - specular.a), 0.0, 1.0) * 0.5) + 0.5);
		//specular.a = clamp((specular.a * 2.0) * specular.a, 0.2, 0.9);
	}
	else
	{// Fake it...
		if (u_Local1.b > 0.0)
		{
			specular = vec4(1.0-fakedepth) * diffuse;
			specular.a = ((clamp((1.0 - fakedepth), 0.0, 1.0) * 0.5) + 0.5);
			specular.a = clamp((specular.a * 2.0) * specular.a, 0.2, 0.9);
			//specular.a = 1.0;
			//specular = vec4(1.0);
#define const_1 ( 12.0 / 255.0)
#define const_2 (255.0 / 219.0)
			specular.rgb = ((clamp(specular.rgb - const_1, 0.0, 1.0)) * const_2); // amplify light/dark
		}
		else
		{
			specular = vec4(1.0);
		}
	}

	//specular = vec4(1.0);

    #if defined(USE_GAMMA2_TEXTURES)
	specular.rgb *= specular.rgb;
    #endif
  #else
	vec4 specular = vec4(1.0);
  #endif

	if (u_Local1.b > 0.0)
	{
		if (u_SpecularScale.r + u_SpecularScale.g + u_SpecularScale.b + u_SpecularScale.a != 0.0) // Shader Specified...
			specular *= u_SpecularScale;
		else // Material Defaults...
		{
			specular *= u_Local1.b;
			
			if (u_Local4.b != 0.0 /* METALS */
				&& u_Local1.a != 30.0 /* ARMOR */ 
				&& u_Local1.a != 10.0 /* GLASS */ 
				&& u_Local1.a != 29.0 /* SHATTERGLASS */ 
				&& u_Local1.a != 18.0 /* BPGLASS */ 
				&& u_Local1.a != 31.0 /* COMPUTER */
				&& u_Local1.a != 15.0 /* ICE */
				&& u_Local1.a != 25.0 /* PLASTIC */
				&& u_Local1.a != 12.0 /* MARBLE */)
			{// Only if not metalic... Metals should remain nice and shiny...
				specular.rgb *= u_SpecularScale.rgb;
			}
		}
	}
	else
		specular *= u_SpecularScale;

	//float specularv = pow(clamp(dot(reflect(-L, N), E), 0.0, 1.0), u_Local1.b );
	//specular = specular * specularv;

	if (u_Local4.b != 0.0)
	{// Metalic...
		float metallic = specular.r;

		specular.rgb = (0.96 * metallic) * diffuse.rgb + vec3(0.04);
		diffuse.rgb *= 1.0 - metallic;
	}
	else
	{// Non Metalic...
		diffuse.rgb *= vec3(1.0) - specular.rgb;
	}

	// Reduce brightness of really bright spots (eg: light right above a reflective surface)
	float refMult = (specular.r + specular.g + specular.b + specular.a) / 4.0;
	refMult = 1.0 - refMult;
	refMult = clamp(refMult, 0.25, 0.75);
  
	reflectance = diffuse.rgb;

  #if defined(r_deluxeSpecular) || defined(USE_LIGHT_VECTOR)
	float adjGloss = specular.a * refMult;
	float adjShininess = exp2(specular.a * refMult * 13.0);

    #if !defined(USE_LIGHT_VECTOR)
	adjGloss *= r_deluxeSpecular;
	adjShininess = exp2(adjGloss * 13.0);
    #endif

	H = normalize(L + E);

	EH = clamp(dot(E, H), 0.0, 1.0);
	NH = clamp(dot(N, H), 0.0, 1.0);

    #if !defined(USE_LIGHT_VECTOR)
	reflectance += CalcSpecular(specular.rgb * refMult, NH, NL, NE, EH, adjGloss, adjShininess) * r_deluxeSpecular;
    #else
	reflectance += CalcSpecular(specular.rgb * refMult, NH, NL, NE, EH, adjGloss, adjShininess);
    #endif
  #endif

  if (u_Local1.b > 0.0)
	gl_FragColor.rgb  += (((lightColor   * reflectance * (attenuation * NL)) * 2.0) + (lightColor   * (reflectance * specular.a * refMult) * (attenuation * NL))) / 3.0;
  else
	gl_FragColor.rgb  += lightColor   * reflectance * (attenuation * NL);

#if 0
	vec3 aSpecular = EnvironmentBRDF(specular.a * refMult, NE, specular.rgb * refMult);

	float hemiDiffuseUp    = N.z * 0.5 + 0.5;
	float hemiDiffuseDown  = 1.0 - hemiDiffuseUp;
	float hemiSpecularUp   = mix(hemiDiffuseUp, float(N.z >= 0.0), specular.a * refMult);
	float hemiSpecularDown = 1.0 - hemiSpecularUp;

	gl_FragColor.rgb += ambientColor * 0.75 * (diffuse.rgb * hemiDiffuseUp   + aSpecular * hemiSpecularUp);
	gl_FragColor.rgb += ambientColor * 0.25 * (diffuse.rgb * hemiDiffuseDown + aSpecular * hemiSpecularDown);
#else
	gl_FragColor.rgb += ambientColor * (diffuse.rgb + (specular.rgb * refMult));
#endif

  #if defined(USE_CUBEMAP)
	if (u_Local3.a > 0.0) {
		reflectance = EnvironmentBRDF(specular.a * refMult, NE, specular.rgb * refMult);

		vec3 R = reflect(E, N);

		vec3 parallax = u_CubeMapInfo.xyz + u_CubeMapInfo.w * viewDir;

		vec3 cubeLightColor = textureCubeLod(u_CubeMap, R + parallax, 7.0 - specular.a * 7.0).rgb * u_EnableTextures.w;

		gl_FragColor.rgb += cubeLightColor * reflectance * (u_Local3.a * refMult);
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
	reflectance += CalcSpecular(specular.rgb * refMult, NH2, NL2, NE, EH2, specular.a * refMult, exp2(specular.a * refMult * 13.0));

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
  if (MaterialThickness > 0.0 || u_Local4.z != 0.0 /*|| u_Local1.a == 5 || u_Local1.a == 6 || u_Local1.a == 12 
	|| u_Local1.a == 14 || u_Local1.a == 15 || u_Local1.a == 16 || u_Local1.a == 17 || u_Local1.a == 19 
	|| u_Local1.a == 20 || u_Local1.a == 21 || u_Local1.a == 22*/)
  {
  #if defined(USE_PRIMARY_LIGHT)
	gl_FragColor.rgb += subScatterFS(gl_FragColor, specular * refMult, L2, lightColor.xyz, E, N, texCoords).rgb;
  #else
	gl_FragColor.rgb += subScatterFS(gl_FragColor, specular * refMult, L, var_Color.xyz, E, N, texCoords).rgb;
  #endif
	gl_FragColor = clamp(gl_FragColor, 0.0, 1.0);
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
