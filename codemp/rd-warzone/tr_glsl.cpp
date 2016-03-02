/*
===========================================================================
Copyright (C) 2006-2009 Robert Beckebans <trebor_7@users.sourceforge.net>

This file is part of XreaL source code.

XreaL source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

XreaL source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with XreaL source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/
// tr_glsl.c
#include "tr_local.h"

void GLSL_BindNullProgram(void);

extern const char *fallbackShader_bokeh_vp;
extern const char *fallbackShader_bokeh_fp;
extern const char *fallbackShader_calclevels4x_vp;
extern const char *fallbackShader_calclevels4x_fp;
extern const char *fallbackShader_depthblur_vp;
extern const char *fallbackShader_depthblur_fp;
extern const char *fallbackShader_down4x_vp;
extern const char *fallbackShader_down4x_fp;
extern const char *fallbackShader_fogpass_vp;
extern const char *fallbackShader_fogpass_fp;
extern const char *fallbackShader_generic_vp;
extern const char *fallbackShader_generic_fp;
extern const char *fallbackShader_lightall_vp;
extern const char *fallbackShader_lightall_fp;
extern const char *fallbackShader_pshadow_vp;
extern const char *fallbackShader_pshadow_fp;
extern const char *fallbackShader_shadowfill_vp;
extern const char *fallbackShader_shadowfill_fp;
extern const char *fallbackShader_shadowmask_vp;
extern const char *fallbackShader_shadowmask_fp;
extern const char *fallbackShader_ssao_vp;
extern const char *fallbackShader_ssao_fp;
extern const char *fallbackShader_texturecolor_vp;
extern const char *fallbackShader_texturecolor_fp;
extern const char *fallbackShader_tonemap_vp;
extern const char *fallbackShader_tonemap_fp;
extern const char *fallbackShader_gaussian_blur_vp;
extern const char *fallbackShader_gaussian_blur_fp;
extern const char *fallbackShader_dglow_downsample_vp;
extern const char *fallbackShader_dglow_downsample_fp;
extern const char *fallbackShader_dglow_upsample_vp;
extern const char *fallbackShader_dglow_upsample_fp;

// UQ1: Added...
extern const char *fallbackShader_generateNormalMap_vp;
extern const char *fallbackShader_generateNormalMap_fp;
extern const char *fallbackShader_truehdr_vp;
extern const char *fallbackShader_truehdr_fp;
extern const char *fallbackShader_magicdetail_vp;
extern const char *fallbackShader_magicdetail_fp;
extern const char *fallbackShader_volumelight_vp;
extern const char *fallbackShader_volumelight_fp;
extern const char *fallbackShader_volumelightCombine_vp;
extern const char *fallbackShader_volumelightCombine_fp;
extern const char *fallbackShader_fakeDepth_vp;
extern const char *fallbackShader_fakeDepth_fp;
extern const char *fallbackShader_fakeDepthSteepParallax_vp;
extern const char *fallbackShader_fakeDepthSteepParallax_fp;
extern const char *fallbackShader_anaglyph_vp;
extern const char *fallbackShader_anaglyph_fp;
extern const char *fallbackShader_uniquesky_fp;
extern const char *fallbackShader_uniquesky_vp;
extern const char *fallbackShader_waterPost_fp;
extern const char *fallbackShader_waterPost_vp;
extern const char *fallbackShader_uniquewater_fp;
extern const char *fallbackShader_uniquewater_vp;
extern const char *fallbackShader_grass_fp;
extern const char *fallbackShader_grass_vp;
extern const char *fallbackShader_grass2_fp;
extern const char *fallbackShader_grass2_vp;
extern const char *fallbackShader_grass2_gs;
extern const char *fallbackShader_grass3_fp;
extern const char *fallbackShader_grass3_vp;
extern const char *fallbackShader_grass3_gs;
extern const char *fallbackShader_hbao_vp;
extern const char *fallbackShader_hbao_fp;
extern const char *fallbackShader_sss_vp;
extern const char *fallbackShader_sss_fp;
extern const char *fallbackShader_sss2_vp;
extern const char *fallbackShader_sss2_fp;
extern const char *fallbackShader_rbm_vp;
extern const char *fallbackShader_rbm_fp;
extern const char *fallbackShader_hbaoCombine_vp;
extern const char *fallbackShader_hbaoCombine_fp;
extern const char *fallbackShader_esharpening_vp;
extern const char *fallbackShader_esharpening_fp;
extern const char *fallbackShader_esharpening2_vp;
extern const char *fallbackShader_esharpening2_fp;
extern const char *fallbackShader_textureclean_vp;
extern const char *fallbackShader_textureclean_fp;
extern const char *fallbackShader_depthOfField_vp;
extern const char *fallbackShader_depthOfField_fp;
extern const char *fallbackShader_depthOfField2_vp;
extern const char *fallbackShader_depthOfField2_fp;
extern const char *fallbackShader_bloom_blur_vp;
extern const char *fallbackShader_bloom_blur_fp;
extern const char *fallbackShader_bloom_combine_vp;
extern const char *fallbackShader_bloom_combine_fp;
extern const char *fallbackShader_anamorphic_blur_vp;
extern const char *fallbackShader_anamorphic_blur_fp;
extern const char *fallbackShader_anamorphic_combine_vp;
extern const char *fallbackShader_anamorphic_combine_fp;
extern const char *fallbackShader_ssgi_vp;
extern const char *fallbackShader_ssgi1_fp;
extern const char *fallbackShader_ssgi2_fp;
extern const char *fallbackShader_ssgi3_fp;
extern const char *fallbackShader_ssgi4_fp;
extern const char *fallbackShader_ssgi_blur_vp;
extern const char *fallbackShader_ssgi_blur_fp;
extern const char *fallbackShader_darkexpand_vp;
extern const char *fallbackShader_darkexpand_fp;
extern const char *fallbackShader_lensflare_vp;
extern const char *fallbackShader_lensflare_fp;
extern const char *fallbackShader_multipost_vp;
extern const char *fallbackShader_multipost_fp;
extern const char *fallbackShader_vibrancy_vp;
extern const char *fallbackShader_vibrancy_fp;
extern const char *fallbackShader_underwater_vp;
extern const char *fallbackShader_underwater_fp;
extern const char *fallbackShader_fxaa_vp;
extern const char *fallbackShader_fxaa_fp;
extern const char *fallbackShader_fastBlur_vp;
extern const char *fallbackShader_fastBlur_fp;
extern const char *fallbackShader_distanceBlur_vp;
extern const char *fallbackShader_distanceBlur_fp;

extern const char *fallbackShader_testshader_vp;
extern const char *fallbackShader_testshader_fp;

//#define TEST_GEOM_SHADER

#ifdef TEST_GEOM_SHADER
const char fallbackShader_basic_gs[] = 
"layout(triangles) in;\n"
"layout (triangle_strip, max_vertices=6) out;\n"
"\n"
"uniform mat4			u_ModelViewProjectionMatrix;\n"\
"#define projModelViewMatrix u_ModelViewProjectionMatrix\n"
"\n"
"in GroundData {\n"
"  vec2 TexCoords;\n"
"  vec3 Normal;\n"
"} ground[3];\n"
"\n"
"out Grass {\n"
"  vec3 LightColor;\n"
"  vec2 GrassTexCoords, ColorMulti;\n"
"  vec3 Normal;\n"
"} grass;\n"
"\n"
"void main()\n"
"{\n"
"  for(int i = 0; i < gl_in.length(); i++)\n"
"  {\n"
"     // copy attributes\n"
"    gl_Position = projModelViewMatrix * gl_in[i].gl_Position;\n"
"    grass.Normal = normalize(/*normalMatrix **/ ground[i].Normal);\n"
"    grass.GrassTexCoords = ground[i].TexCoords;\n"
" \n"
"    // done with the vertex\n"
"    EmitVertex();\n"
"  }\n"
"  EndPrimitive();\n"
"}\n";
#endif //TEST_GEOM_SHADER


//#define SHADER_BASIC
#define SHADER_ONE
////#define SHADER_TWO
//#define SHADER_THREE

#ifdef SHADER_BASIC
const char fallbackShader_genericTessControl_cp[] = 
"layout(vertices = 3) out;\n"\
"float tessLevelOuter = 7;\n"\
"float tessLevelInner = 7;\n"\
"// attributes of the input CPs\n"\
"in vec2				TexCoord_CS_in[];\n"\
"in vec3				Normal_CS_in[];\n"\
"\n"\
"// attributes of the output CPs\n"\
"out vec2				TexCoord_ES_in[3];\n"\
"out vec3				Normal_ES_in[3];\n"\
"void main()\n"\
"{\n"\
"    TexCoord_ES_in[gl_InvocationID] = TexCoord_CS_in[gl_InvocationID];\n"\
"    Normal_ES_in[gl_InvocationID] = Normal_CS_in[gl_InvocationID];\n"\
"	gl_TessLevelOuter[0] = tessLevelOuter;\n"\
"	gl_TessLevelOuter[1] = tessLevelOuter;\n"\
"	gl_TessLevelOuter[2] = tessLevelOuter;\n"\
"	gl_TessLevelInner[0] = tessLevelInner;\n"\
"	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;\n"\
"}\n";

const char fallbackShader_genericTessControl_ep[] = 
"layout(triangles, equal_spacing, ccw) in;\n"\
"in vec2					TexCoord_ES_in[];\n"\
"in vec3					Normal_ES_in[];\n"\
"\n"\
"out vec2					TexCoord_FS_in;\n"\
"out vec3					Normal_FS_in;\n"\
"\n"\
"vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)\n"\
"{\n"\
"   	return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;\n"\
"}\n"\
"\n"\
"vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)\n"\
"{\n"\
"   	return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;\n"\
"}\n"\
"void main()\n"\
"{\n"\
"   	TexCoord_FS_in = interpolate2D(TexCoord_ES_in[0], TexCoord_ES_in[1], TexCoord_ES_in[2]);\n"\
"   	Normal_FS_in = interpolate3D(Normal_ES_in[0], Normal_ES_in[1], Normal_ES_in[2]);\n"\
"   	Normal_FS_in = normalize(Normal_FS_in);\n"\
"	gl_Position = vec4(gl_in[0].gl_Position.x * gl_TessCoord.x, gl_in[1].gl_Position.y * gl_TessCoord.y, gl_in[2].gl_Position.z * gl_TessCoord.z, 1.0);\n"\
"}\n";
#endif

#ifdef SHADER_ONE
const char fallbackShader_genericTessControl_cp[] = 
"// define the number of CPs in the output patch\n"\
"#extension GL_ARB_tessellation_shader : enable\n"\
"\n"\
"layout (vertices = 1) out;\n"\
"\n"\
"uniform vec4 u_Local10;\n"\
"\n"\
"#define gTessellationLevel u_Local10.r\n"\
"\n"\
"// attributes of the input CPs\n"\
"in vec2 TexCoord_CS_in[];\n"\
"in vec4 Normal_CS_in[];\n"\
"\n"\
"struct OutputPatch\n"\
"{\n"\
"    vec4 WorldPos_B030;\n"\
"    vec4 WorldPos_B021;\n"\
"    vec4 WorldPos_B012;\n"\
"    vec4 WorldPos_B003;\n"\
"    vec4 WorldPos_B102;\n"\
"    vec4 WorldPos_B201;\n"\
"    vec4 WorldPos_B300;\n"\
"    vec4 WorldPos_B210;\n"\
"    vec4 WorldPos_B120;\n"\
"    vec4 WorldPos_B111;\n"\
"    vec4 Normal[3];\n"\
"    vec2 TexCoord[3];\n"\
"};\n"\
"\n"\
"// attributes of the output CPs\n"\
"out patch OutputPatch oPatch;\n"\
"\n"\
"vec4 ProjectToPlane(vec4 Point, vec4 PlanePoint, vec4 PlaneNormal)\n"\
"{\n"\
"    vec3 v = Point.xyz - PlanePoint.xyz;  //Pj - Pi ?\n"\
"    float Len = dot(v, PlaneNormal.xyz); //(Pj - Pi) dot Ni ?\n"\
"    vec3 d = Len * PlaneNormal.xyz;\n"\
"\n"\
"    return vec4(Point.xyz - d.xyz, Point.w); //Only project XYZ and then tack the W back on.\n"\
"}\n"\
"\n"\
"void CalcPositions()\n"\
"{\n"\
"    // The original vertices stay the same\n"\
"    oPatch.WorldPos_B030 = gl_in[0].gl_Position.xyzw;\n"\
"    oPatch.WorldPos_B003 = gl_in[1].gl_Position.xyzw;\n"\
"    oPatch.WorldPos_B300 = gl_in[2].gl_Position.xyzw;\n"\
"\n"\
"    // Edges are names according to the opposing vertex\n"\
"    vec4 EdgeB300 = oPatch.WorldPos_B003.xyzw - oPatch.WorldPos_B030.xyzw;\n"\
"    vec4 EdgeB030 = oPatch.WorldPos_B300.xyzw - oPatch.WorldPos_B003.xyzw;\n"\
"    vec4 EdgeB003 = oPatch.WorldPos_B030.xyzw - oPatch.WorldPos_B300.xyzw;\n"\
"\n"\
"    // Generate two midpoints on each edge\n"\
"\n"\
"    oPatch.WorldPos_B021 = oPatch.WorldPos_B030.xyzw + EdgeB300 / 3.0;\n"\
"    oPatch.WorldPos_B012 = oPatch.WorldPos_B030.xyzw + EdgeB300 * 2.0 / 3.0;\n"\
"    oPatch.WorldPos_B102 = oPatch.WorldPos_B003.xyzw + EdgeB030 / 3.0;\n"\
"    oPatch.WorldPos_B201 = oPatch.WorldPos_B003.xyzw + EdgeB030 * 2.0 / 3.0;\n"\
"    oPatch.WorldPos_B210 = oPatch.WorldPos_B300.xyzw + EdgeB003 / 3.0;\n"\
"    oPatch.WorldPos_B120 = oPatch.WorldPos_B300.xyzw + EdgeB003 * 2.0 / 3.0;\n"\
"\n"\
"    //oPatch.Normal[0] = normalize(oPatch.Normal[0]); // Let's ensure this is happening because\n"\
"    //oPatch.Normal[1] = normalize(oPatch.Normal[1]); // normally the vertex shader should have enforced this already.\n"\
"    //oPatch.Normal[2] = normalize(oPatch.Normal[2]);\n"\
"\n"\
"    oPatch.WorldPos_B021 = ProjectToPlane(oPatch.WorldPos_B021, oPatch.WorldPos_B030, oPatch.Normal[0]);\n"\
"    oPatch.WorldPos_B012 = ProjectToPlane(oPatch.WorldPos_B012, oPatch.WorldPos_B003, oPatch.Normal[1]);\n"\
"    oPatch.WorldPos_B102 = ProjectToPlane(oPatch.WorldPos_B102, oPatch.WorldPos_B003, oPatch.Normal[1]);\n"\
"    oPatch.WorldPos_B201 = ProjectToPlane(oPatch.WorldPos_B201, oPatch.WorldPos_B300, oPatch.Normal[2]);\n"\
"    oPatch.WorldPos_B210 = ProjectToPlane(oPatch.WorldPos_B210, oPatch.WorldPos_B300, oPatch.Normal[2]);\n"\
"    oPatch.WorldPos_B120 = ProjectToPlane(oPatch.WorldPos_B120, oPatch.WorldPos_B030, oPatch.Normal[0]);\n"\
"\n"\
"\n"\
"    vec4 Center = (oPatch.WorldPos_B003 + oPatch.WorldPos_B030 + oPatch.WorldPos_B300) / 3.0; // V\n"\
"\n"\
"    oPatch.WorldPos_B111 = (oPatch.WorldPos_B021 + oPatch.WorldPos_B012 + oPatch.WorldPos_B102 +\n"\
"                            oPatch.WorldPos_B201 + oPatch.WorldPos_B210 + oPatch.WorldPos_B120) / 6.0; // E\n"\
"\n"\
"    oPatch.WorldPos_B111 += (oPatch.WorldPos_B111 - Center) / 2.0;   //E + 1/2 (E - V)\n"\
"\n"\
"    //oPatch.WorldPos_B111 = gl_in[0].gl_Position.xyzw;\n"\
"}\n"\
"\n"\
"void main()\n"\
"{\n"\
"	// Set the control points of the output patch\n"\
"   for (int i = 0 ; i < 3 ; i++)\n"\
"	{\n"\
"       oPatch.Normal[i] = Normal_CS_in[i];\n"\
"		oPatch.TexCoord[i] = TexCoord_CS_in[i];\n"\
"    }\n"\
"\n"\
"    CalcPositions();\n"\
"\n"\
"    // Calculate the tessellation levels\n"\
"    gl_TessLevelOuter[0] = gTessellationLevel;\n"\
"    gl_TessLevelOuter[1] = gTessellationLevel;\n"\
"    gl_TessLevelOuter[2] = gTessellationLevel;\n"\
"    gl_TessLevelInner[0] = gTessellationLevel;\n"\
"}\n";

const char fallbackShader_genericTessControl_ep[] = 
"#extension GL_ARB_tessellation_shader : enable\n"\
"\n"\
"layout(triangles, equal_spacing, ccw) in;\n"\
"\n"\
"uniform mat4				u_ModelViewProjectionMatrix;\n"\
"uniform mat4				u_ModelMatrix;\n"\
"\n"\
"#define gVP				u_ModelViewProjectionMatrix\n"\
"\n"\
"//mat4 gVP = mat4(\n"\
"//    1,0,0,0,   //-1 mirrors across vertical!\n"\
"//    0,1,0,0,   //-1 mirrors top to bottom!\n"\
"//    0,0,1,0,   //?? No noticable affect.\n"\
"//    0,0,0,1);  //-1 probably mirrors front to back, as it draws nothing.\n"\
"\n"\
"struct OutputPatch\n"\
"{\n"\
"    vec4 WorldPos_B030;\n"\
"    vec4 WorldPos_B021;\n"\
"    vec4 WorldPos_B012;\n"\
"    vec4 WorldPos_B003;\n"\
"    vec4 WorldPos_B102;\n"\
"    vec4 WorldPos_B201;\n"\
"    vec4 WorldPos_B300;\n"\
"    vec4 WorldPos_B210;\n"\
"    vec4 WorldPos_B120;\n"\
"    vec4 WorldPos_B111;\n"\
"    vec4 Normal[3];\n"\
"    vec2 TexCoord[3];\n"\
"};\n"\
"\n"\
"in patch OutputPatch oPatch;\n"\
"\n"\
"out vec4 WorldPos_FS_in;\n"\
"out vec2 TexCoord_FS_in;\n"\
"out vec4 Normal_FS_in;\n"\
"\n"\
"vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)\n"\
"{\n"\
"   	return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;\n"\
"}\n"\
"\n"\
"vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)\n"\
"{\n"\
"   	return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;\n"\
"}\n"\
"\n"\
"vec4 interpolate4D(vec4 v0, vec4 v1, vec4 v2)\n"\
"{\n"\
"      return vec4(gl_TessCoord.x) * v0 + vec4(gl_TessCoord.y) * v1 + vec4(gl_TessCoord.z) * v2;\n"\
"}\n"\
"\n"\
"void main()\n"\
"{\n"\
"    // Interpolate the attributes of the output vertex using the barycentric coordinates\n"\
"    TexCoord_FS_in = interpolate2D(oPatch.TexCoord[0], oPatch.TexCoord[1], oPatch.TexCoord[2]);\n"\
"	 Normal_FS_in  = interpolate4D(oPatch.Normal[0], oPatch.Normal[1], oPatch.Normal[2]);\n"\
"\n"\
"    float u = gl_TessCoord.x;\n"\
"    float v = gl_TessCoord.y;\n"\
"    float w = gl_TessCoord.z;\n"\
"\n"\
"    float uPow3 = pow(u, 3);\n"\
"    float vPow3 = pow(v, 3);\n"\
"    float wPow3 = pow(w, 3);\n"\
"    float uPow2 = pow(u, 2);\n"\
"    float vPow2 = pow(v, 2);\n"\
"    float wPow2 = pow(w, 2);\n"\
"\n"\
"    WorldPos_FS_in = oPatch.WorldPos_B300 * wPow3 +\n"\
"                    oPatch.WorldPos_B030 * uPow3 +\n"\
"                    oPatch.WorldPos_B003 * vPow3 +\n"\
"                    oPatch.WorldPos_B210 * 3.0 * wPow2 * u +\n"\
"                    oPatch.WorldPos_B120 * 3.0 * w * uPow2 +\n"\
"                    oPatch.WorldPos_B201 * 3.0 * wPow2 * v +\n"\
"                    oPatch.WorldPos_B021 * 3.0 * uPow2 * v +\n"\
"                    oPatch.WorldPos_B102 * 3.0 * w * vPow2 +\n"\
"                    oPatch.WorldPos_B012 * 3.0 * u * vPow2 +\n"\
"                    oPatch.WorldPos_B111 * 6.0 * w * u * v;\n"\
"\n"\
"    gl_Position = gVP * WorldPos_FS_in;\n"\
"}\n";
#endif

#ifdef SHADER_TWO
const char fallbackShader_genericTessControl_cp[] = 
"// PN patch data\n"\
"struct PnPatch\n"\
"{\n"\
" float b210;\n"\
" float b120;\n"\
" float b021;\n"\
" float b012;\n"\
" float b102;\n"\
" float b201;\n"\
" float b111;\n"\
" float n110;\n"\
" float n011;\n"\
" float n101;\n"\
"};\n"\
"\n"\
"// tessellation levels\n"\
"float gTessellationLevel = 3.0;\n"\
"\n"\
"layout(vertices=3) out;\n"\
"\n"\
"layout(location = 0)   in vec3 Normal_CS_in[];\n"\
"layout(location = 1)   in vec2 TexCoord_CS_in[];\n"\
"\n"\
"layout(location = 0) out vec3 iNormal[3];\n"\
"layout(location = 3) out vec2 iTexCoord[3];\n"\
"layout(location = 6) out PnPatch iPnPatch[3];\n"\
"\n"\
"float wij(int i, int j)\n"\
"{\n"\
" return dot(gl_in[j].gl_Position.xyz - gl_in[i].gl_Position.xyz, Normal_CS_in[i]);\n"\
"}\n"\
"\n"\
"float vij(int i, int j)\n"\
"{\n"\
" vec3 Pj_minus_Pi = gl_in[j].gl_Position.xyz\n"\
"                  - gl_in[i].gl_Position.xyz;\n"\
" vec3 Ni_plus_Nj  = Normal_CS_in[i]+Normal_CS_in[j];\n"\
" return 2.0*dot(Pj_minus_Pi, Ni_plus_Nj)/dot(Pj_minus_Pi, Pj_minus_Pi);\n"\
"}\n"\
"\n"\
"void main()\n"\
"{\n"\
" // get data\n"\
" gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;\n"\
" iNormal[gl_InvocationID]            = Normal_CS_in[gl_InvocationID];\n"\
" iTexCoord[gl_InvocationID]          = TexCoord_CS_in[gl_InvocationID];\n"\
"\n"\
" // set base \n"\
" float P0 = gl_in[0].gl_Position[gl_InvocationID];\n"\
" float P1 = gl_in[1].gl_Position[gl_InvocationID];\n"\
" float P2 = gl_in[2].gl_Position[gl_InvocationID];\n"\
" float N0 = Normal_CS_in[0][gl_InvocationID];\n"\
" float N1 = Normal_CS_in[1][gl_InvocationID];\n"\
" float N2 = Normal_CS_in[2][gl_InvocationID];\n"\
"\n"\
" // compute control points\n"\
" iPnPatch[gl_InvocationID].b210 = (2.0*P0 + P1 - wij(0,1)*N0)/3.0;\n"\
" iPnPatch[gl_InvocationID].b120 = (2.0*P1 + P0 - wij(1,0)*N1)/3.0;\n"\
" iPnPatch[gl_InvocationID].b021 = (2.0*P1 + P2 - wij(1,2)*N1)/3.0;\n"\
" iPnPatch[gl_InvocationID].b012 = (2.0*P2 + P1 - wij(2,1)*N2)/3.0;\n"\
" iPnPatch[gl_InvocationID].b102 = (2.0*P2 + P0 - wij(2,0)*N2)/3.0;\n"\
" iPnPatch[gl_InvocationID].b201 = (2.0*P0 + P2 - wij(0,2)*N0)/3.0;\n"\
" float E = ( iPnPatch[gl_InvocationID].b210\n"\
"           + iPnPatch[gl_InvocationID].b120\n"\
"           + iPnPatch[gl_InvocationID].b021\n"\
"           + iPnPatch[gl_InvocationID].b012\n"\
"           + iPnPatch[gl_InvocationID].b102\n"\
"           + iPnPatch[gl_InvocationID].b201 ) / 6.0;\n"\
" float V = (P0 + P1 + P2)/3.0;\n"\
" iPnPatch[gl_InvocationID].b111 = E + (E - V)*0.5;\n"\
" iPnPatch[gl_InvocationID].n110 = N0+N1-vij(0,1)*(P1-P0);\n"\
" iPnPatch[gl_InvocationID].n011 = N1+N2-vij(1,2)*(P2-P1);\n"\
" iPnPatch[gl_InvocationID].n101 = N2+N0-vij(2,0)*(P0-P2);\n"\
"\n"\
" // set tess levels\n"\
" gl_TessLevelOuter[gl_InvocationID] = gTessellationLevel;\n"\
" gl_TessLevelInner[0] = gTessellationLevel;\n"\
"}\n";

const char fallbackShader_genericTessControl_ep[] = 
"// PN patch data\n"\
"struct PnPatch\n"\
"{\n"\
" float b210;\n"\
" float b120;\n"\
" float b021;\n"\
" float b012;\n"\
" float b102;\n"\
" float b201;\n"\
" float b111;\n"\
" float n110;\n"\
" float n011;\n"\
" float n101;\n"\
"};\n"\
"\n"\
"uniform mat4 u_ModelViewProjectionMatrix; // mvp\n"\
"//uniform float uTessAlpha;          // controls the deformation\n"\
"float uTessAlpha = 0.5;          // controls the deformation\n"\
"\n"\
"layout(triangles, fractional_odd_spacing, ccw) in;\n"\
"\n"\
"uniform vec3			u_ViewOrigin;\n"\
"\n"\
"layout(location = 0) in vec3 iNormal[];\n"\
"layout(location = 3) in vec2 iTexCoord[];\n"\
"layout(location = 4) in PnPatch iPnPatch[];\n"\
"\n"\
"layout(location = 0) out vec3 Normal_FS_in;\n"\
"layout(location = 1) out vec2 TexCoord_FS_in;\n"\
"layout(location = 2) out vec3 WorldPos_FS_in;\n"\
"layout(location = 3) out vec3 ViewDir_FS_in;\n"\
"\n"\
"#define b300    gl_in[0].gl_Position.xyz\n"\
"#define b030    gl_in[1].gl_Position.xyz\n"\
"#define b003    gl_in[2].gl_Position.xyz\n"\
"#define n200    iNormal[0]\n"\
"#define n020    iNormal[1]\n"\
"#define n002    iNormal[2]\n"\
"#define uvw     gl_TessCoord\n"\
"\n"\
"void main()\n"\
"{\n"\
" vec3 uvwSquared = uvw*uvw;\n"\
" vec3 uvwCubed   = uvwSquared*uvw;\n"\
"\n"\
" // extract control points\n"\
" vec3 b210 = vec3(iPnPatch[0].b210, iPnPatch[1].b210, iPnPatch[2].b210);\n"\
" vec3 b120 = vec3(iPnPatch[0].b120, iPnPatch[1].b120, iPnPatch[2].b120);\n"\
" vec3 b021 = vec3(iPnPatch[0].b021, iPnPatch[1].b021, iPnPatch[2].b021);\n"\
" vec3 b012 = vec3(iPnPatch[0].b012, iPnPatch[1].b012, iPnPatch[2].b012);\n"\
" vec3 b102 = vec3(iPnPatch[0].b102, iPnPatch[1].b102, iPnPatch[2].b102);\n"\
" vec3 b201 = vec3(iPnPatch[0].b201, iPnPatch[1].b201, iPnPatch[2].b201);\n"\
" vec3 b111 = vec3(iPnPatch[0].b111, iPnPatch[1].b111, iPnPatch[2].b111);\n"\
"\n"\
" // extract control normals\n"\
" vec3 n110 = normalize(vec3(iPnPatch[0].n110,\n"\
"                            iPnPatch[1].n110,\n"\
"                            iPnPatch[2].n110));\n"\
" vec3 n011 = normalize(vec3(iPnPatch[0].n011,\n"\
"                            iPnPatch[1].n011,\n"\
"                            iPnPatch[2].n011));\n"\
" vec3 n101 = normalize(vec3(iPnPatch[0].n101,\n"\
"                            iPnPatch[1].n101,\n"\
"                            iPnPatch[2].n101));\n"\
"\n"\
" // compute texcoords\n"\
" TexCoord_FS_in  = gl_TessCoord[2]*iTexCoord[0]\n"\
"            + gl_TessCoord[0]*iTexCoord[1]\n"\
"            + gl_TessCoord[1]*iTexCoord[2];\n"\
"\n"\
" // normal\n"\
" vec3 barNormal = gl_TessCoord[2]*iNormal[0]\n"\
"                + gl_TessCoord[0]*iNormal[1]\n"\
"                + gl_TessCoord[1]*iNormal[2];\n"\
" vec3 pnNormal  = n200*uvwSquared[2]\n"\
"                + n020*uvwSquared[0]\n"\
"                + n002*uvwSquared[1]\n"\
"                + n110*uvw[2]*uvw[0]\n"\
"                + n011*uvw[0]*uvw[1]\n"\
"                + n101*uvw[2]*uvw[1];\n"\
" Normal_FS_in = uTessAlpha*pnNormal + (1.0-uTessAlpha)*barNormal;\n"\
"\n"\
" // compute interpolated pos\n"\
" vec3 barPos = gl_TessCoord[2]*b300\n"\
"             + gl_TessCoord[0]*b030\n"\
"             + gl_TessCoord[1]*b003;\n"\
"\n"\
" // save some computations\n"\
" uvwSquared *= 3.0;\n"\
"\n"\
" // compute PN position\n"\
" vec3 pnPos  = b300*uvwCubed[2]\n"\
"             + b030*uvwCubed[0]\n"\
"             + b003*uvwCubed[1]\n"\
"             + b210*uvwSquared[2]*uvw[0]\n"\
"             + b120*uvwSquared[0]*uvw[2]\n"\
"             + b201*uvwSquared[2]*uvw[1]\n"\
"             + b021*uvwSquared[0]*uvw[1]\n"\
"             + b102*uvwSquared[1]*uvw[2]\n"\
"             + b012*uvwSquared[1]*uvw[0]\n"\
"             + b111*6.0*uvw[0]*uvw[1]*uvw[2];\n"\
"\n"\
" // final position and normal\n"\
" vec3 finalPos = (1.0-uTessAlpha)*barPos + uTessAlpha*pnPos;\n"\
" gl_Position   = u_ModelViewProjectionMatrix * vec4(finalPos,1.0);\n"\
" WorldPos_FS_in = finalPos.xyz;\n"\
" ViewDir_FS_in = u_ViewOrigin - finalPos;\n"\
"}\n";
#endif

#ifdef SHADER_THREE
const char fallbackShader_genericTessControl_cp[] = 
"// Phong tess patch data\n"\
"struct PhongPatch\n"\
"{\n"\
" float termIJ;\n"\
" float termJK;\n"\
" float termIK;\n"\
"};\n"\
"\n"\
"float uTessLevels = 5.0;\n"\
"\n"\
"layout(vertices=3) out;\n"\
"\n"\
"layout(location = 0)   in vec3 Normal_CS_in[];\n"\
"layout(location = 1)   in vec2 TexCoord_CS_in[];\n"\
"\n"\
"layout(location=0) out vec3 oNormal[3];\n"\
"layout(location=3) out vec2 oTexCoord[3];\n"\
"layout(location=6) out PhongPatch oPhongPatch[3];\n"\
"\n"\
"#define Pi  gl_in[0].gl_Position.xyz\n"\
"#define Pj  gl_in[1].gl_Position.xyz\n"\
"#define Pk  gl_in[2].gl_Position.xyz\n"\
"\n"\
"float PIi(int i, vec3 q)\n"\
"{\n"\
" vec3 q_minus_p = q - gl_in[i].gl_Position.xyz;\n"\
" return q[gl_InvocationID] - dot(q_minus_p, Normal_CS_in[i])\n"\
"                           * Normal_CS_in[i][gl_InvocationID];\n"\
"}\n"\
"\n"\
"void main()\n"\
"{\n"\
" // get data\n"\
" gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;\n"\
" oNormal[gl_InvocationID]   = Normal_CS_in[gl_InvocationID];\n"\
" oTexCoord[gl_InvocationID] = TexCoord_CS_in[gl_InvocationID];\n"\
"\n"\
" // compute patch data\n"\
" oPhongPatch[gl_InvocationID].termIJ = PIi(0,Pj) + PIi(1,Pi);\n"\
" oPhongPatch[gl_InvocationID].termJK = PIi(1,Pk) + PIi(2,Pj);\n"\
" oPhongPatch[gl_InvocationID].termIK = PIi(2,Pi) + PIi(0,Pk);\n"\
"\n"\
" // tesselate\n"\
" gl_TessLevelOuter[gl_InvocationID] = uTessLevels;\n"\
" gl_TessLevelInner[0] = uTessLevels;\n"\
"}\n";

const char fallbackShader_genericTessControl_ep[] = 
"// Phong tess patch data\n"\
"struct PhongPatch\n"\
"{\n"\
" float termIJ;\n"\
" float termJK;\n"\
" float termIK;\n"\
"};\n"\
"\n"\
"float uTessAlpha = 0.5;\n"\
"uniform mat4  u_ModelViewProjectionMatrix;\n"\
"\n"\
"layout(triangles, fractional_odd_spacing, ccw) in;\n"\
"\n"\
"layout(location=0) in vec3 iNormal[];\n"\
"layout(location=3) in vec2 iTexCoord[];\n"\
"layout(location=6) in PhongPatch iPhongPatch[];\n"\
"\n"\
"out vec3 Normal_FS_in;\n"\
"out vec2 TexCoord_FS_in;\n"\
"out vec3 WorldPos_FS_in;\n"\
"\n"\
"#define Pi  gl_in[0].gl_Position.xyz\n"\
"#define Pj  gl_in[1].gl_Position.xyz\n"\
"#define Pk  gl_in[2].gl_Position.xyz\n"\
"#define tc1 gl_TessCoord\n"\
"\n"\
"void main()\n"\
"{\n"\
" // precompute squared tesscoords\n"\
" vec3 tc2 = tc1*tc1;\n"\
"\n"\
" // compute texcoord and normal\n"\
" TexCoord_FS_in = gl_TessCoord[0]*iTexCoord[0]\n"\
"           + gl_TessCoord[1]*iTexCoord[1]\n"\
"           + gl_TessCoord[2]*iTexCoord[2];\n"\
" Normal_FS_in   = gl_TessCoord[0]*iNormal[0]\n"\
"           + gl_TessCoord[1]*iNormal[1]\n"\
"           + gl_TessCoord[2]*iNormal[2];\n"\
"\n"\
" // interpolated position\n"\
" vec3 barPos = gl_TessCoord[0]*Pi\n"\
"             + gl_TessCoord[1]*Pj\n"\
"             + gl_TessCoord[2]*Pk;\n"\
"\n"\
" // build terms\n"\
" vec3 termIJ = vec3(iPhongPatch[0].termIJ,\n"\
"                    iPhongPatch[1].termIJ,\n"\
"                    iPhongPatch[2].termIJ);\n"\
" vec3 termJK = vec3(iPhongPatch[0].termJK,\n"\
"                    iPhongPatch[1].termJK,\n"\
"                    iPhongPatch[2].termJK);\n"\
" vec3 termIK = vec3(iPhongPatch[0].termIK,\n"\
"                    iPhongPatch[1].termIK,\n"\
"                    iPhongPatch[2].termIK);\n"\
"\n"\
" // phong tesselated pos\n"\
" vec3 phongPos   = tc2[0]*Pi\n"\
"                 + tc2[1]*Pj\n"\
"                 + tc2[2]*Pk\n"\
"                 + tc1[0]*tc1[1]*termIJ\n"\
"                 + tc1[1]*tc1[2]*termJK\n"\
"                 + tc1[2]*tc1[0]*termIK;\n"\
"\n"\
" // final position\n"\
" vec3 finalPos = (1.0-uTessAlpha)*barPos + uTessAlpha*phongPos;\n"\
" gl_Position   = u_ModelViewProjectionMatrix * vec4(finalPos,1.0);\n"\
" WorldPos_FS_in = gl_Position.xyz;\n"\
"}\n";
#endif


typedef struct uniformInfo_s
{
	char *name;
	int type;
	int size;
}
uniformInfo_t;

// These must be in the same order as in uniform_t in tr_local.h.
static uniformInfo_t uniformsInfo[] =
{
	{ "u_DiffuseMap",  GLSL_INT, 1 },
	{ "u_LightMap",    GLSL_INT, 1 },
	{ "u_NormalMap",   GLSL_INT, 1 },
	{ "u_DeluxeMap",   GLSL_INT, 1 },
	{ "u_SpecularMap", GLSL_INT, 1 },

	{ "u_TextureMap", GLSL_INT, 1 },
	{ "u_LevelsMap",  GLSL_INT, 1 },
	{ "u_CubeMap",    GLSL_INT, 1 },
	{ "u_OverlayMap",    GLSL_INT, 1 },
	{ "u_SteepMap",  GLSL_INT, 1 },

	{ "u_ScreenImageMap", GLSL_INT, 1 },
	{ "u_ScreenDepthMap", GLSL_INT, 1 },

	{ "u_ShadowMap",  GLSL_INT, 1 },
	{ "u_ShadowMap2", GLSL_INT, 1 },
	{ "u_ShadowMap3", GLSL_INT, 1 },

	{ "u_ShadowMvp",  GLSL_MAT16, 1 },
	{ "u_ShadowMvp2", GLSL_MAT16, 1 },
	{ "u_ShadowMvp3", GLSL_MAT16, 1 },

	{ "u_EnableTextures", GLSL_VEC4, 1 },
	{ "u_DiffuseTexMatrix",  GLSL_VEC4, 1 },
	{ "u_DiffuseTexOffTurb", GLSL_VEC4, 1 },

	{ "u_TCGen0",        GLSL_INT, 1 },
	{ "u_TCGen0Vector0", GLSL_VEC3, 1 },
	{ "u_TCGen0Vector1", GLSL_VEC3, 1 },

	{ "u_DeformGen",    GLSL_INT, 1 },
	{ "u_DeformParams", GLSL_FLOAT5, 1 },

	{ "u_ColorGen",  GLSL_INT, 1 },
	{ "u_AlphaGen",  GLSL_INT, 1 },
	{ "u_Color",     GLSL_VEC4, 1 },
	{ "u_BaseColor", GLSL_VEC4, 1 },
	{ "u_VertColor", GLSL_VEC4, 1 },

	{ "u_DlightInfo",    GLSL_VEC4, 1 },
	{ "u_LightForward",  GLSL_VEC3, 1 },
	{ "u_LightUp",       GLSL_VEC3, 1 },
	{ "u_LightRight",    GLSL_VEC3, 1 },
	{ "u_LightOrigin",   GLSL_VEC4, 1 },
	{ "u_LightColor",   GLSL_VEC4, 1 },
	
	{ "u_ModelLightDir", GLSL_VEC3, 1 },
	{ "u_LightRadius",   GLSL_FLOAT, 1 },
	{ "u_AmbientLight",  GLSL_VEC3, 1 },
	{ "u_DirectedLight", GLSL_VEC3, 1 },

	{ "u_PortalRange", GLSL_FLOAT, 1 },

	{ "u_FogDistance",  GLSL_VEC4, 1 },
	{ "u_FogDepth",     GLSL_VEC4, 1 },
	{ "u_FogEyeT",      GLSL_FLOAT, 1 },
	{ "u_FogColorMask", GLSL_VEC4, 1 },

	{ "u_ModelMatrix",               GLSL_MAT16, 1 },
	{ "u_ViewProjectionMatrix",      GLSL_MAT16, 1 },
	{ "u_ModelViewProjectionMatrix", GLSL_MAT16, 1 },
	{ "u_invProjectionMatrix", GLSL_MAT16, 1 },
	{ "u_invEyeProjectionMatrix", GLSL_MAT16, 1 },
	{ "u_ProjectionMatrix",               GLSL_MAT16, 1 },
	{ "u_ModelViewMatrix",               GLSL_MAT16, 1 },
	{ "u_ViewMatrix",               GLSL_MAT16, 1 },

	{ "u_Time",          GLSL_FLOAT, 1 },
	{ "u_VertexLerp" ,   GLSL_FLOAT, 1 },
	{ "u_NormalScale",   GLSL_VEC4, 1 },
	{ "u_SpecularScale", GLSL_VEC4, 1 },

	{ "u_ViewInfo",				GLSL_VEC4, 1 },
	{ "u_ViewOrigin",			GLSL_VEC3, 1 },
	{ "u_LocalViewOrigin",		GLSL_VEC3, 1 },
	{ "u_ViewForward",			GLSL_VEC3, 1 },
	{ "u_ViewLeft",				GLSL_VEC3, 1 },
	{ "u_ViewUp",				GLSL_VEC3, 1 },

	{ "u_InvTexRes",           GLSL_VEC2, 1 },
	{ "u_AutoExposureMinMax",  GLSL_VEC2, 1 },
	{ "u_ToneMinAvgMaxLinear", GLSL_VEC3, 1 },

	{ "u_PrimaryLightOrigin",  GLSL_VEC4, 1  },
	{ "u_PrimaryLightColor",   GLSL_VEC3, 1  },
	{ "u_PrimaryLightAmbient", GLSL_VEC3, 1  },
	{ "u_PrimaryLightRadius",  GLSL_FLOAT, 1 },

	{ "u_CubeMapInfo", GLSL_VEC4, 1 },
	{ "u_CubeMapStrength", GLSL_FLOAT, 1 },

	{ "u_BoneMatrices",			GLSL_MAT16, 20 },

	// UQ1: Added...
	{ "u_Dimensions",           GLSL_VEC2, 1 },
	{ "u_HeightMap",			GLSL_INT, 1 },
	{ "u_Local0",				GLSL_VEC4, 1  },
	{ "u_Local1",				GLSL_VEC4, 1  },
	{ "u_Local2",				GLSL_VEC4, 1  },
	{ "u_Local3",				GLSL_VEC4, 1  },
	{ "u_Local4",				GLSL_VEC4, 1  },
	{ "u_Local5",				GLSL_VEC4, 1  },
	{ "u_Local6",				GLSL_VEC4, 1  },
	{ "u_Local7",				GLSL_VEC4, 1  },
	{ "u_Local8",				GLSL_VEC4, 1  },
	{ "u_Local9",				GLSL_VEC4, 1  },
	{ "u_Local10",				GLSL_VEC4, 1  },

	{ "u_lightCount",			GLSL_INT, 1 },
	{ "u_lightPositions",		GLSL_VEC2, 16  },
};

static void GLSL_PrintProgramInfoLog(GLuint object, qboolean developerOnly)
{
	char           *msg;
	static char     msgPart[1024];
	int             maxLength = 0;
	int             i;
	int             printLevel = developerOnly ? PRINT_DEVELOPER : PRINT_ALL;

	qglGetProgramiv(object, GL_INFO_LOG_LENGTH, &maxLength);

	if (maxLength <= 0)
	{
		ri->Printf(printLevel, "No compile log.\n");
		return;
	}

	ri->Printf(printLevel, "compile log:\n");

	if (maxLength < 1023)
	{
		qglGetProgramInfoLog(object, maxLength, &maxLength, msgPart);

		msgPart[maxLength + 1] = '\0';

		ri->Printf(printLevel, "%s\n", msgPart);
	}
	else
	{
		msg = (char *)Z_Malloc(maxLength, TAG_SHADERTEXT);

		qglGetProgramInfoLog(object, maxLength, &maxLength, msg);

		for(i = 0; i < maxLength; i += 1024)
		{
			Q_strncpyz(msgPart, msg + i, sizeof(msgPart));

			ri->Printf(printLevel, "%s\n", msgPart);
		}

		Z_Free(msg);
	}
}

static void GLSL_PrintShaderInfoLog(GLuint object, qboolean developerOnly)
{
	char           *msg;
	static char     msgPart[1024];
	int             maxLength = 0;
	int             i;
	int             printLevel = developerOnly ? PRINT_DEVELOPER : PRINT_ALL;

	qglGetShaderiv(object, GL_INFO_LOG_LENGTH, &maxLength);

	if (maxLength <= 0)
	{
		ri->Printf(printLevel, "No compile log.\n");
		return;
	}

	ri->Printf(printLevel, "compile log:\n");

	if (maxLength < 1023)
	{
		qglGetShaderInfoLog(object, maxLength, &maxLength, msgPart);

		msgPart[maxLength + 1] = '\0';

		ri->Printf(printLevel, "%s\n", msgPart);
	}
	else
	{
		msg = (char *)Z_Malloc(maxLength, TAG_SHADERTEXT);

		qglGetShaderInfoLog(object, maxLength, &maxLength, msg);

		for(i = 0; i < maxLength; i += 1024)
		{
			Q_strncpyz(msgPart, msg + i, sizeof(msgPart));

			ri->Printf(printLevel, "%s\n", msgPart);
		}

		Z_Free(msg);
	}
}

static void GLSL_PrintShaderSource(GLuint shader)
{
	char           *msg;
	static char     msgPart[1024];
	int             maxLength = 0;
	int             i;

	qglGetShaderiv(shader, GL_SHADER_SOURCE_LENGTH, &maxLength);

	msg = (char *)Z_Malloc(maxLength, TAG_SHADERTEXT);

	qglGetShaderSource(shader, maxLength, &maxLength, msg);

	for(i = 0; i < maxLength; i += 1024)
	{
		Q_strncpyz(msgPart, msg + i, sizeof(msgPart));
		ri->Printf(PRINT_ALL, "%s\n", msgPart);
	}

	Z_Free(msg);
}

char		GLSL_MAX_VERSION[24] = {0};

char *GLSL_GetHighestSupportedVersion( void )
{
	if (GLSL_MAX_VERSION[0] == '#') return GLSL_MAX_VERSION;

	if (r_tesselation->integer)
	{
		if (glRefConfig.glslMajorVersion >= 5)
			sprintf(GLSL_MAX_VERSION, "#version 500 core\n");
		else if (glRefConfig.glslMajorVersion >= 4 && glRefConfig.glslMinorVersion >= 20)
			sprintf(GLSL_MAX_VERSION, "#version 420 core\n");
		else if (glRefConfig.glslMajorVersion >= 4 && glRefConfig.glslMinorVersion >= 10)
			sprintf(GLSL_MAX_VERSION, "#version 410 core\n");
		else
			sprintf(GLSL_MAX_VERSION, "#version 400 core\n");
	}
	else
	{
		// UQ1: Use the highest level of GL that is supported... Check once and record for all future glsl loading...
		/*if (glRefConfig.glslMajorVersion >= 5)
		sprintf(GLSL_MAX_VERSION, "#version 500 core\n");
		else if (glRefConfig.glslMajorVersion >= 4 && glRefConfig.glslMinorVersion >= 20)
		sprintf(GLSL_MAX_VERSION, "#version 420 core\n");
		else if (glRefConfig.glslMajorVersion >= 4 && glRefConfig.glslMinorVersion >= 10)
		sprintf(GLSL_MAX_VERSION, "#version 410 core\n");
		else if (glRefConfig.glslMajorVersion >= 4)
		sprintf(GLSL_MAX_VERSION, "#version 400 core\n");
		else*/ if (glRefConfig.glslMajorVersion >= 3 && glRefConfig.glslMinorVersion >= 30)
			sprintf(GLSL_MAX_VERSION, "#version 330\n");
		else if (glRefConfig.glslMajorVersion >= 3 && glRefConfig.glslMinorVersion >= 20)
			sprintf(GLSL_MAX_VERSION, "#version 320\n");
		else if (glRefConfig.glslMajorVersion >= 3 && glRefConfig.glslMinorVersion >= 10)
			sprintf(GLSL_MAX_VERSION, "#version 310\n");
		else if (glRefConfig.glslMajorVersion >= 3)
			sprintf(GLSL_MAX_VERSION, "#version 300\n");
		else if (glRefConfig.glslMajorVersion >= 2 && glRefConfig.glslMinorVersion >= 20)
			sprintf(GLSL_MAX_VERSION, "#version 220\n");
		else if (glRefConfig.glslMajorVersion >= 2 && glRefConfig.glslMinorVersion >= 10)
			sprintf(GLSL_MAX_VERSION, "#version 210\n");
		else if (glRefConfig.glslMajorVersion >= 2)
			sprintf(GLSL_MAX_VERSION, "#version 200\n");
		else //if (glRefConfig.glslMinorVersion >= 50)
			sprintf(GLSL_MAX_VERSION, "#version 150\n");
		/*else if (glRefConfig.glslMinorVersion >= 40)
		sprintf(GLSL_MAX_VERSION, "#version 140\n");
		else if (glRefConfig.glslMinorVersion >= 30)
		sprintf(GLSL_MAX_VERSION, "#version 130\n");*/
	}

	ri->Printf(PRINT_WARNING, "GLSL shader version set to highest available version: %s", GLSL_MAX_VERSION);

	return GLSL_MAX_VERSION;
}

static void GLSL_GetShaderHeader( GLenum shaderType, const GLcharARB *extra, char *dest, int size, char *forceVersion )
{
	float fbufWidthScale, fbufHeightScale;

	dest[0] = '\0';

	if (forceVersion)
		sprintf(dest, "#version %s\n", forceVersion);
	else
		//Q_strcat(dest, size, "#version 150 core\n");
		sprintf(dest, GLSL_GetHighestSupportedVersion());
	
	if(shaderType == GL_VERTEX_SHADER)
	{
		Q_strcat(dest, size, "#define attribute in\n");
		Q_strcat(dest, size, "#define varying out\n");
	}
	else if(shaderType == GL_TESS_CONTROL_SHADER)
	{
		if (extra)
		{
			Q_strcat(dest, size, extra);
		}

		// OK we added a lot of stuff but if we do something bad in the GLSL shaders then we want the proper line
		// so we have to reset the line counting
		Q_strcat(dest, size, "#line 0\n");
		return;
	}
	else if(shaderType == GL_TESS_EVALUATION_SHADER)
	{
		if (extra)
		{
			Q_strcat(dest, size, extra);
		}

		// OK we added a lot of stuff but if we do something bad in the GLSL shaders then we want the proper line
		// so we have to reset the line counting
		Q_strcat(dest, size, "#line 0\n");
		return;
	}
	else if(shaderType == GL_GEOMETRY_SHADER)
	{
		if (extra)
		{
			Q_strcat(dest, size, extra);
		}

		// OK we added a lot of stuff but if we do something bad in the GLSL shaders then we want the proper line
		// so we have to reset the line counting
		Q_strcat(dest, size, "#line 0\n");
		return;
	}
	else
	{
		Q_strcat(dest, size, "#define varying in\n");

		Q_strcat(dest, size, "out vec4 out_Color;\n");
		Q_strcat(dest, size, "#define gl_FragColor out_Color\n");
	}

	Q_strcat(dest, size, "#ifndef M_PI\n#define M_PI 3.14159265358979323846\n#endif\n");

	Q_strcat(dest, size,
					 va("#ifndef deformGen_t\n"
						"#define deformGen_t\n"
						"#define DGEN_WAVE_SIN %i\n"
						"#define DGEN_WAVE_SQUARE %i\n"
						"#define DGEN_WAVE_TRIANGLE %i\n"
						"#define DGEN_WAVE_SAWTOOTH %i\n"
						"#define DGEN_WAVE_INVERSE_SAWTOOTH %i\n"
						"#define DGEN_BULGE %i\n"
						"#define DGEN_MOVE %i\n"
						"#endif\n",
						DGEN_WAVE_SIN,
						DGEN_WAVE_SQUARE,
						DGEN_WAVE_TRIANGLE,
						DGEN_WAVE_SAWTOOTH,
						DGEN_WAVE_INVERSE_SAWTOOTH,
						DGEN_BULGE,
						DGEN_MOVE));

	Q_strcat(dest, size,
					 va("#ifndef tcGen_t\n"
						"#define tcGen_t\n"
						"#define TCGEN_LIGHTMAP %i\n"
						"#define TCGEN_LIGHTMAP1 %i\n"
						"#define TCGEN_LIGHTMAP2 %i\n"
						"#define TCGEN_LIGHTMAP3 %i\n"
						"#define TCGEN_TEXTURE %i\n"
						"#define TCGEN_ENVIRONMENT_MAPPED %i\n"
						"#define TCGEN_FOG %i\n"
						"#define TCGEN_VECTOR %i\n"
						"#endif\n",
						TCGEN_LIGHTMAP,
						TCGEN_LIGHTMAP1,
						TCGEN_LIGHTMAP2,
						TCGEN_LIGHTMAP3,
						TCGEN_TEXTURE,
						TCGEN_ENVIRONMENT_MAPPED,
						TCGEN_FOG,
						TCGEN_VECTOR));

	Q_strcat(dest, size,
					 va("#ifndef colorGen_t\n"
						"#define colorGen_t\n"
						"#define CGEN_LIGHTING_DIFFUSE %i\n"
						"#endif\n",
						CGEN_LIGHTING_DIFFUSE));

	Q_strcat(dest, size,
							 va("#ifndef alphaGen_t\n"
								"#define alphaGen_t\n"
								"#define AGEN_LIGHTING_SPECULAR %i\n"
								"#define AGEN_PORTAL %i\n"
								"#endif\n",
								AGEN_LIGHTING_SPECULAR,
								AGEN_PORTAL));

	Q_strcat(dest, size,
							 va("#ifndef texenv_t\n"
								"#define texenv_t\n"
								"#define TEXENV_MODULATE %i\n"
								"#define TEXENV_ADD %i\n"
								"#define TEXENV_REPLACE %i\n"
								"#endif\n",
								GL_MODULATE,
								GL_ADD,
								GL_REPLACE));

	fbufWidthScale = 1.0f / ((float)glConfig.vidWidth * r_superSampleMultiplier->value);
	fbufHeightScale = 1.0f / ((float)glConfig.vidHeight * r_superSampleMultiplier->value);
	Q_strcat(dest, size,
			 va("#ifndef r_FBufScale\n#define r_FBufScale vec2(%f, %f)\n#endif\n", fbufWidthScale, fbufHeightScale));

	if (extra)
	{
		Q_strcat(dest, size, extra);
	}

	// OK we added a lot of stuff but if we do something bad in the GLSL shaders then we want the proper line
	// so we have to reset the line counting
	Q_strcat(dest, size, "#line 0\n");
}

static int GLSL_EnqueueCompileGPUShader(GLuint program, GLuint *prevShader, const GLchar *buffer, int size, GLenum shaderType)
{
	GLuint     shader;

	shader = qglCreateShader(shaderType);

	qglShaderSource(shader, 1, &buffer, &size);

	// compile shader
	qglCompileShader(shader);

	*prevShader = shader;

	return 1;
}

static int GLSL_LoadGPUShaderText(const char *name, const char *fallback,
	GLenum shaderType, char *dest, int destSize)
{
	char            filename[MAX_QPATH];
	GLcharARB      *buffer = NULL;
	const GLcharARB *shaderText = NULL;
	int             size;
	int             result;

	if(shaderType == GL_VERTEX_SHADER)
	{
		Com_sprintf(filename, sizeof(filename), "glsl/%s_vp.glsl", name);
	}
	else if(shaderType == GL_TESS_CONTROL_SHADER)
	{
		Com_sprintf(filename, sizeof(filename), "glsl/%s_cp.glsl", name);
	}
	else if(shaderType == GL_TESS_EVALUATION_SHADER)
	{
		Com_sprintf(filename, sizeof(filename), "glsl/%s_ep.glsl", name);
	}
	else if(shaderType == GL_GEOMETRY_SHADER)
	{
		Com_sprintf(filename, sizeof(filename), "glsl/%s_gs.glsl", name);
	}
	else
	{
		Com_sprintf(filename, sizeof(filename), "glsl/%s_fp.glsl", name);
	}

	ri->Printf(PRINT_DEVELOPER, "...loading '%s'\n", filename);
	size = ri->FS_ReadFile(filename, (void **)&buffer);
	if(!buffer)
	{
		if (fallback)
		{
			ri->Printf(PRINT_DEVELOPER, "couldn't load, using fallback\n");
			shaderText = fallback;
			size = strlen(shaderText);
		}
		else
		{
			ri->Printf(PRINT_DEVELOPER, "couldn't load!\n");
			return 0;
		}
	}
	else
	{
		shaderText = buffer;
	}

	if (size > destSize)
	{
		result = 0;
	}
	else
	{
		Q_strncpyz(dest, shaderText, size + 1);
		result = 1;
	}

	if (buffer)
	{
		ri->FS_FreeFile(buffer);
	}
	
	return result;
}

static void GLSL_LinkProgram(GLuint program)
{
	GLint           linked;

	qglLinkProgram(program);

	qglGetProgramiv(program, GL_LINK_STATUS, &linked);
	if(!linked)
	{
		GLSL_PrintProgramInfoLog(program, qfalse);
		ri->Printf(PRINT_ALL, "\n");
		ri->Error(ERR_DROP, "shaders failed to link");
	}
}

static void GLSL_ValidateProgram(GLuint program)
{
	GLint           validated;

	qglValidateProgram(program);

	qglGetProgramiv(program, GL_VALIDATE_STATUS, &validated);
	if(!validated)
	{
		GLSL_PrintProgramInfoLog(program, qfalse);
		ri->Printf(PRINT_ALL, "\n");
		ri->Error(ERR_DROP, "shaders failed to validate");
	}
}

static void GLSL_ShowProgramUniforms(GLuint program)
{
	int             i, count, size;
	GLenum			type;
	char            uniformName[1000];

	// install the executables in the program object as part of current state.
	qglUseProgram(program);

	// check for GL Errors

	// query the number of active uniforms
	qglGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);

	// Loop over each of the active uniforms, and set their value
	for(i = 0; i < count; i++)
	{
		qglGetActiveUniform(program, i, sizeof(uniformName), NULL, &size, &type, uniformName);

		ri->Printf(PRINT_DEVELOPER, "active uniform: '%s'\n", uniformName);
	}

	qglUseProgram(0);
}

static int GLSL_BeginLoadGPUShader2(shaderProgram_t * program, const char *name, int attribs, const char *vpCode, const char *fpCode, const char *cpCode, const char *epCode, const char *gsCode)
{
	size_t nameBufSize = strlen (name) + 1;

	ri->Printf(PRINT_DEVELOPER, "------- GPU shader -------\n");

	program->name = (char *)Z_Malloc (nameBufSize, TAG_GENERAL);
	Q_strncpyz(program->name, name, nameBufSize);

	program->program = qglCreateProgram();
	program->attribs = attribs;

	program->tesselation = qfalse;
	program->tessControlShader = NULL;
	program->tessEvaluationShader = NULL;

	program->geometry = qfalse;
	program->geometryShader = NULL;

	if (!(GLSL_EnqueueCompileGPUShader(program->program, &program->vertexShader, vpCode, strlen(vpCode), GL_VERTEX_SHADER)))
	{
		ri->Printf(PRINT_ALL, "GLSL_BeginLoadGPUShader2: Unable to load \"%s\" as GL_VERTEX_SHADER\n", name);
		qglDeleteProgram(program->program);
		return 0;
	}

	if (cpCode)
	{
		if (!(GLSL_EnqueueCompileGPUShader(program->program, &program->tessControlShader, cpCode, strlen(cpCode), GL_TESS_CONTROL_SHADER)))
		{
			ri->Printf(PRINT_ALL, "GLSL_BeginLoadGPUShader2: Unable to load \"%s\" as GL_TESS_CONTROL_SHADER\n", name);
			program->tessControlShader = 0;
			qglDeleteProgram(program->program);
			return 0;
		}
		else
		{
			//ri->Printf(PRINT_ALL, "GLSL_BeginLoadGPUShader2: Load \"%s\" as GL_TESS_CONTROL_SHADER\n", name);
			program->tesselation = qtrue;
		}
	}
	else
	{
		program->tessControlShader = 0;
	}

	if (epCode)
	{
		if (!(GLSL_EnqueueCompileGPUShader(program->program, &program->tessEvaluationShader, epCode, strlen(epCode), GL_TESS_EVALUATION_SHADER)))
		{
			ri->Printf(PRINT_ALL, "GLSL_BeginLoadGPUShader2: Unable to load \"%s\" as GL_TESS_EVALUATION_SHADER\n", name);
			program->tessEvaluationShader = 0;
			qglDeleteProgram(program->program);
			return 0;
		}
		else
		{
			//ri->Printf(PRINT_ALL, "GLSL_BeginLoadGPUShader2: Load \"%s\" as GL_TESS_EVALUATION_SHADER\n", name);
			program->tesselation = qtrue;
		}
	}
	else
	{
		program->tessEvaluationShader = 0;
	}

	if (gsCode)
	{
		if (!(GLSL_EnqueueCompileGPUShader(program->program, &program->geometryShader, gsCode, strlen(gsCode), GL_GEOMETRY_SHADER)))
		{
			ri->Printf(PRINT_ALL, "GLSL_BeginLoadGPUShader2: Unable to load \"%s\" as GL_GEOMETRY_SHADER\n", name);
			program->geometryShader = 0;
			qglDeleteProgram(program->program);
			return 0;
		}
		else
		{
			//ri->Printf(PRINT_ALL, "GLSL_BeginLoadGPUShader2: Load \"%s\" as GL_GEOMETRY_SHADER\n", name);
			program->geometry = qtrue;
		}
	}
	else
	{
		program->geometryShader = 0;
	}

	if(fpCode)
	{
		if(!(GLSL_EnqueueCompileGPUShader(program->program, &program->fragmentShader, fpCode, strlen(fpCode), GL_FRAGMENT_SHADER)))
		{
			ri->Printf(PRINT_ALL, "GLSL_BeginLoadGPUShader2: Unable to load \"%s\" as GL_FRAGMENT_SHADER\n", name);
			qglDeleteProgram(program->program);
			return 0;
		}
	}
	
	return 1;
}

static bool GLSL_IsGPUShaderCompiled (GLuint shader)
{
	GLint compiled;

	qglGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if(!compiled)
	{
		GLSL_PrintShaderSource(shader);
		GLSL_PrintShaderInfoLog(shader, qfalse);
		ri->Error(ERR_DROP, "Couldn't compile shader");
		return qfalse;
	}

	return qtrue;
}

static bool GLSL_EndLoadGPUShader (shaderProgram_t *program)
{
	uint32_t attribs = program->attribs;

	//ri->Printf(PRINT_WARNING, "Compiling glsl: %s.\n", program->name);

	if (!GLSL_IsGPUShaderCompiled (program->vertexShader))
	{
		return false;
	}

	if (program->tessControlShader && !GLSL_IsGPUShaderCompiled (program->tessControlShader))
	{
		program->tessControlShader = 0;
		return false;
	}

	if (program->tessEvaluationShader && !GLSL_IsGPUShaderCompiled (program->tessEvaluationShader))
	{
		program->tessEvaluationShader = 0;
		return false;
	}

	if (program->geometryShader && !GLSL_IsGPUShaderCompiled (program->geometryShader))
	{
		program->geometryShader = 0;
		return false;
	}

	if (!GLSL_IsGPUShaderCompiled (program->fragmentShader))
	{
		return false;
	}

	qglAttachShader(program->program, program->vertexShader);
	qglAttachShader(program->program, program->fragmentShader);

	if (program->tessControlShader)
		qglAttachShader(program->program, program->tessControlShader);
	if (program->tessEvaluationShader)
		qglAttachShader(program->program, program->tessEvaluationShader);
	
	if (program->geometryShader)
		qglAttachShader(program->program, program->geometryShader);

	qglBindFragDataLocation (program->program, 0, "out_Color");
	qglBindFragDataLocation (program->program, 1, "out_Glow");
	qglBindFragDataLocation (program->program, 2, "out_DetailedNormal");
	qglBindFragDataLocation (program->program, 3, "out_FoliageMap");
	//qglBindFragDataLocation (program->program, 3, "out_Normal");

	if(attribs & ATTR_POSITION)
		qglBindAttribLocation(program->program, ATTR_INDEX_POSITION, "attr_Position");

	if(attribs & ATTR_TEXCOORD0)
		qglBindAttribLocation(program->program, ATTR_INDEX_TEXCOORD0, "attr_TexCoord0");

	if(attribs & ATTR_TEXCOORD1)
		qglBindAttribLocation(program->program, ATTR_INDEX_TEXCOORD1, "attr_TexCoord1");

	if(attribs & ATTR_TANGENT)
		qglBindAttribLocation(program->program, ATTR_INDEX_TANGENT, "attr_Tangent");

	if(attribs & ATTR_NORMAL)
		qglBindAttribLocation(program->program, ATTR_INDEX_NORMAL, "attr_Normal");

	if(attribs & ATTR_COLOR)
		qglBindAttribLocation(program->program, ATTR_INDEX_COLOR, "attr_Color");

	if(attribs & ATTR_PAINTCOLOR)
		qglBindAttribLocation(program->program, ATTR_INDEX_PAINTCOLOR, "attr_PaintColor");

	if(attribs & ATTR_LIGHTDIRECTION)
		qglBindAttribLocation(program->program, ATTR_INDEX_LIGHTDIRECTION, "attr_LightDirection");

	if(attribs & ATTR_POSITION2)
		qglBindAttribLocation(program->program, ATTR_INDEX_POSITION2, "attr_Position2");

	if(attribs & ATTR_NORMAL2)
		qglBindAttribLocation(program->program, ATTR_INDEX_NORMAL2, "attr_Normal2");

	if(attribs & ATTR_TANGENT2)
		qglBindAttribLocation(program->program, ATTR_INDEX_TANGENT2, "attr_Tangent2");

	if(attribs & ATTR_BONE_INDEXES)
		qglBindAttribLocation(program->program, ATTR_INDEX_BONE_INDEXES, "attr_BoneIndexes");

	if(attribs & ATTR_BONE_WEIGHTS)
		qglBindAttribLocation(program->program, ATTR_INDEX_BONE_WEIGHTS, "attr_BoneWeights");

	GLSL_LinkProgram(program->program);

	// Won't be needing these anymore...
	qglDetachShader (program->program, program->vertexShader);
	qglDetachShader (program->program, program->fragmentShader);

	if (program->tessControlShader)
		qglDetachShader(program->program, program->tessControlShader);
	if (program->tessEvaluationShader)
		qglDetachShader(program->program, program->tessEvaluationShader);
	
	if (program->geometryShader)
		qglDetachShader(program->program, program->geometryShader);

	qglDeleteShader (program->vertexShader);
	qglDeleteShader (program->fragmentShader);

	if (program->tessControlShader)
		qglDeleteShader(program->tessControlShader);
	if (program->tessEvaluationShader)
		qglDeleteShader(program->tessEvaluationShader);

	if (program->geometryShader)
		qglDeleteShader(program->geometryShader);

	program->vertexShader = program->fragmentShader = program->tessControlShader = program->tessEvaluationShader = program->geometryShader = 0;

	return true;
}

static int GLSL_BeginLoadGPUShader(shaderProgram_t * program, const char *name,
	int attribs, qboolean fragmentShader, qboolean tesselation, qboolean geometry, const GLcharARB *extra, qboolean addHeader,
	char *forceVersion, const char *fallback_vp, const char *fallback_fp, const char *fallback_cp, const char *fallback_ep, const char *fallback_gs)
{
	char vpCode[32768];
	char fpCode[32768];
	char cpCode[32768];
	char epCode[32768];
	char gsCode[32768];
	char *postHeader;
	int size;

	//ri->Printf(PRINT_WARNING, "Begin GLSL load for %s.\n", name);

	size = sizeof(vpCode);
	if (addHeader)
	{
		GLSL_GetShaderHeader(GL_VERTEX_SHADER, extra, vpCode, size, forceVersion);
		postHeader = &vpCode[strlen(vpCode)];
		size -= strlen(vpCode);
	}
	else
	{
		postHeader = &vpCode[0];
	}

	if (!GLSL_LoadGPUShaderText(name, fallback_vp, GL_VERTEX_SHADER, postHeader, size))
	{
		return 0;
	}

	if (tesselation && fallback_cp && fallback_cp[0])
	{
		size = sizeof(cpCode);
		if (addHeader)
		{
			GLSL_GetShaderHeader(GL_TESS_CONTROL_SHADER, extra, cpCode, size, forceVersion);
			postHeader = &cpCode[strlen(cpCode)];
			size -= strlen(cpCode);
		}
		else
		{
			postHeader = &cpCode[0];
		}

		//ri->Printf(PRINT_WARNING, "Begin GLSL load GL_TESS_CONTROL_SHADER for %s.\n", name);

		if (!GLSL_LoadGPUShaderText(name, fallback_cp, GL_TESS_CONTROL_SHADER, postHeader, size))
		{
			return 0;
		}
	}

	if (tesselation && fallback_ep && fallback_ep[0])
	{
		size = sizeof(epCode);
		if (addHeader)
		{
			GLSL_GetShaderHeader(GL_TESS_EVALUATION_SHADER, extra, epCode, size, forceVersion);
			postHeader = &epCode[strlen(epCode)];
			size -= strlen(epCode);
		}
		else
		{
			postHeader = &epCode[0];
		}

		//ri->Printf(PRINT_WARNING, "Begin GLSL load GL_TESS_EVALUATION_SHADER for %s.\n", name);

		if (!GLSL_LoadGPUShaderText(name, fallback_ep, GL_GEOMETRY_SHADER, postHeader, size))
		{
			return 0;
		}
	}

	if (geometry && fallback_gs && fallback_gs[0])
	{
		size = sizeof(gsCode);
		if (addHeader)
		{
			GLSL_GetShaderHeader(GL_GEOMETRY_SHADER, extra, gsCode, size, forceVersion);
			postHeader = &gsCode[strlen(gsCode)];
			size -= strlen(gsCode);
		}
		else
		{
			postHeader = &gsCode[0];
		}

		//ri->Printf(PRINT_WARNING, "Begin GLSL load GL_GEOMETRY_SHADER for %s.\n", name);

		if (!GLSL_LoadGPUShaderText(name, fallback_gs, GL_GEOMETRY_SHADER, postHeader, size))
		{
			return 0;
		}
	}

	if (fragmentShader)
	{
		size = sizeof(fpCode);
		if (addHeader)
		{
			GLSL_GetShaderHeader(GL_FRAGMENT_SHADER, extra, fpCode, size, forceVersion);
			postHeader = &fpCode[strlen(fpCode)];
			size -= strlen(fpCode);
		}
		else
		{
			postHeader = &fpCode[0];
		}

		if (!GLSL_LoadGPUShaderText(name, fallback_fp, GL_FRAGMENT_SHADER, postHeader, size))
		{
			return 0;
		}
	}

	if (tesselation && cpCode && cpCode[0] && epCode && epCode[0])
	{
		return GLSL_BeginLoadGPUShader2(program, name, attribs, vpCode, fragmentShader ? fpCode : NULL, cpCode, epCode, NULL);
	}
	else if (geometry && gsCode && gsCode[0])
	{
		return GLSL_BeginLoadGPUShader2(program, name, attribs, vpCode, fragmentShader ? fpCode : NULL, NULL, NULL, gsCode);
	}
	else
	{
		return GLSL_BeginLoadGPUShader2(program, name, attribs, vpCode, fragmentShader ? fpCode : NULL, NULL, NULL, NULL);
	}
}

void GLSL_InitUniforms(shaderProgram_t *program)
{
	int i, size;

	GLint *uniforms;
	
	program->uniforms = (GLint *)Z_Malloc (UNIFORM_COUNT * sizeof (*program->uniforms), TAG_GENERAL);
	program->uniformBufferOffsets = (short *)Z_Malloc (UNIFORM_COUNT * sizeof (*program->uniformBufferOffsets), TAG_GENERAL);

	uniforms = program->uniforms;

	size = 0;
	for (i = 0; i < UNIFORM_COUNT; i++)
	{
		uniforms[i] = qglGetUniformLocation(program->program, uniformsInfo[i].name);

		if (uniforms[i] == -1)
			continue;
		 
		program->uniformBufferOffsets[i] = size;

		switch(uniformsInfo[i].type)
		{
			case GLSL_INT:
				size += sizeof(GLint) * uniformsInfo[i].size;
				break;
			case GLSL_FLOAT:
				size += sizeof(GLfloat) * uniformsInfo[i].size;
				break;
			case GLSL_FLOAT5:
				size += sizeof(float) * 5 * uniformsInfo[i].size;
				break;
			case GLSL_VEC2:
				size += sizeof(float) * 2 * uniformsInfo[i].size;
				break;
			case GLSL_VEC3:
				size += sizeof(float) * 3 * uniformsInfo[i].size;
				break;
			case GLSL_VEC4:
				size += sizeof(float) * 4 * uniformsInfo[i].size;
				break;
			case GLSL_MAT16:
				size += sizeof(float) * 16 * uniformsInfo[i].size;
				break;
			default:
				break;
		}
	}

	program->uniformBuffer = (char *)Z_Malloc(size, TAG_SHADERTEXT, qtrue);
}

void GLSL_FinishGPUShader(shaderProgram_t *program)
{
	GLSL_ValidateProgram(program->program);
	GLSL_ShowProgramUniforms(program->program);
	GL_CheckErrors();
}

void GLSL_SetUniformInt(shaderProgram_t *program, int uniformNum, GLint value)
{
	GLint *uniforms = program->uniforms;
	GLint *compare = (GLint *)(program->uniformBuffer + program->uniformBufferOffsets[uniformNum]);

	if (uniforms[uniformNum] == -1)
		return;

	if (uniformsInfo[uniformNum].type != GLSL_INT)
	{
		ri->Printf( PRINT_WARNING, "GLSL_SetUniformInt: wrong type for uniform %i in program %s\n", uniformNum, program->name);
		return;
	}

	if (value == *compare)
	{
		return;
	}

	*compare = value;

	qglUniform1i(uniforms[uniformNum], value);
}

void GLSL_SetUniformFloat(shaderProgram_t *program, int uniformNum, GLfloat value)
{
	GLint *uniforms = program->uniforms;
	GLfloat *compare = (GLfloat *)(program->uniformBuffer + program->uniformBufferOffsets[uniformNum]);

	if (uniforms[uniformNum] == -1)
		return;

	if (uniformsInfo[uniformNum].type != GLSL_FLOAT)
	{
		ri->Printf( PRINT_WARNING, "GLSL_SetUniformFloat: wrong type for uniform %i in program %s\n", uniformNum, program->name);
		return;
	}

	if (value == *compare)
	{
		return;
	}

	*compare = value;
	
	qglUniform1f(uniforms[uniformNum], value);
}

void GLSL_SetUniformVec2(shaderProgram_t *program, int uniformNum, const vec2_t v)
{
	GLint *uniforms = program->uniforms;
	float *compare = (float *)(program->uniformBuffer + program->uniformBufferOffsets[uniformNum]);

	if (uniforms[uniformNum] == -1)
		return;

	if (uniformsInfo[uniformNum].type != GLSL_VEC2)
	{
		ri->Printf( PRINT_WARNING, "GLSL_SetUniformVec2: wrong type for uniform %i in program %s\n", uniformNum, program->name);
		return;
	}

	if (v[0] == compare[0] && v[1] == compare[1])
	{
		return;
	}

	compare[0] = v[0];
	compare[1] = v[1];

	qglUniform2f(uniforms[uniformNum], v[0], v[1]);
}

void GLSL_SetUniformVec2x16(shaderProgram_t *program, int uniformNum, const vec2_t *elements, int numElements)
{
	GLint *uniforms = program->uniforms;
	float *compare;

	if (uniforms[uniformNum] == -1)
		return;

	if (uniformsInfo[uniformNum].type != GLSL_VEC2)
	{
		ri->Printf( PRINT_WARNING, "GLSL_SetUniformVec2x16: wrong type for uniform %i in program %s\n", uniformNum, program->name);
		return;
	}

	if (uniformsInfo[uniformNum].size < numElements)
		return;

	compare = (float *)(program->uniformBuffer + program->uniformBufferOffsets[uniformNum]);
	if (memcmp (elements, compare, sizeof (vec2_t) * numElements) == 0)
	{
		return;
	}

	Com_Memcpy (compare, elements, sizeof (vec2_t) * numElements);

	qglUniform2fv(uniforms[uniformNum], numElements, (const GLfloat *)elements);
}

void GLSL_SetUniformVec3(shaderProgram_t *program, int uniformNum, const vec3_t v)
{
	GLint *uniforms = program->uniforms;
	float *compare = (float *)(program->uniformBuffer + program->uniformBufferOffsets[uniformNum]);

	if (uniforms[uniformNum] == -1)
		return;

	if (uniformsInfo[uniformNum].type != GLSL_VEC3)
	{
		ri->Printf( PRINT_WARNING, "GLSL_SetUniformVec3: wrong type for uniform %i in program %s\n", uniformNum, program->name);
		return;
	}

	if (VectorCompare(v, compare))
	{
		return;
	}

	VectorCopy(v, compare);

	qglUniform3f(uniforms[uniformNum], v[0], v[1], v[2]);
}

void GLSL_SetUniformVec4(shaderProgram_t *program, int uniformNum, const vec4_t v)
{
	GLint *uniforms = program->uniforms;
	float *compare = (float *)(program->uniformBuffer + program->uniformBufferOffsets[uniformNum]);

	if (uniforms[uniformNum] == -1)
		return;

	if (uniformsInfo[uniformNum].type != GLSL_VEC4)
	{
		ri->Printf( PRINT_WARNING, "GLSL_SetUniformVec4: wrong type for uniform %i in program %s\n", uniformNum, program->name);
		return;
	}

	if (VectorCompare4(v, compare))
	{
		return;
	}

	VectorCopy4(v, compare);

	qglUniform4f(uniforms[uniformNum], v[0], v[1], v[2], v[3]);
}

void GLSL_SetUniformFloat5(shaderProgram_t *program, int uniformNum, const vec5_t v)
{
	GLint *uniforms = program->uniforms;
	float *compare = (float *)(program->uniformBuffer + program->uniformBufferOffsets[uniformNum]);

	if (uniforms[uniformNum] == -1)
		return;

	if (uniformsInfo[uniformNum].type != GLSL_FLOAT5)
	{
		ri->Printf( PRINT_WARNING, "GLSL_SetUniformFloat5: wrong type for uniform %i in program %s\n", uniformNum, program->name);
		return;
	}

	if (VectorCompare5(v, compare))
	{
		return;
	}

	VectorCopy5(v, compare);

	qglUniform1fv(uniforms[uniformNum], 5, v);
}

void GLSL_SetUniformMatrix16(shaderProgram_t *program, int uniformNum, const float *matrix, int numElements)
{
	GLint *uniforms = program->uniforms;
	float *compare;

	if (uniforms[uniformNum] == -1)
		return;

	if (uniformsInfo[uniformNum].type != GLSL_MAT16)
	{
		ri->Printf( PRINT_WARNING, "GLSL_SetUniformMatrix16: wrong type for uniform %i in program %s\n", uniformNum, program->name);
		return;
	}

	if (uniformsInfo[uniformNum].size < numElements)
		return;

	compare = (float *)(program->uniformBuffer + program->uniformBufferOffsets[uniformNum]);
	if (memcmp (matrix, compare, sizeof (float) * 16 * numElements) == 0)
	{
		return;
	}

	Com_Memcpy (compare, matrix, sizeof (float) * 16 * numElements);

	qglUniformMatrix4fv(uniforms[uniformNum], numElements, GL_FALSE, matrix);
}

void GLSL_DeleteGPUShader(shaderProgram_t *program)
{
	if(program->program)
	{
		qglDeleteProgram(program->program);

		Z_Free (program->name);
		Z_Free (program->uniformBuffer);
		Z_Free (program->uniformBufferOffsets);
		Z_Free (program->uniforms);

		Com_Memset(program, 0, sizeof(*program));
	}
}

static bool GLSL_IsValidPermutationForGeneric (int shaderCaps)
{
	if ((shaderCaps & (GENERICDEF_USE_VERTEX_ANIMATION | GENERICDEF_USE_SKELETAL_ANIMATION)) == (GENERICDEF_USE_VERTEX_ANIMATION | GENERICDEF_USE_SKELETAL_ANIMATION))
	{
		return false;
	}

	return true;
}

static bool GLSL_IsValidPermutationForFog (int shaderCaps)
{
	if ((shaderCaps & (FOGDEF_USE_VERTEX_ANIMATION | FOGDEF_USE_SKELETAL_ANIMATION)) == (FOGDEF_USE_VERTEX_ANIMATION | FOGDEF_USE_SKELETAL_ANIMATION))
	{
		return false;
	}

	return true;
}

static bool GLSL_IsValidPermutationForLight (int lightType, int shaderCaps)
{
	if ((shaderCaps & LIGHTDEF_USE_PARALLAXMAP) && !r_parallaxMapping->integer)
		return false;

	if (!lightType && (shaderCaps & LIGHTDEF_USE_PARALLAXMAP))
		return false;

	if (!lightType && (shaderCaps & LIGHTDEF_USE_SHADOWMAP))
		return false;

	/*
	if (r_tesselation->integer < 1 && (shaderCaps & LIGHTDEF_USE_TESSELLATION))
		return qfalse;
	*/

	return true;
}

int GLSL_BeginLoadGPUShaders(void)
{
	int startTime;
	int i;
	char extradefines[1024];
	int attribs;

	ri->Printf(PRINT_ALL, "------- GLSL_InitGPUShaders -------\n");

	R_IssuePendingRenderCommands();

	startTime = ri->Milliseconds();

	for (i = 0; i < GENERICDEF_COUNT; i++)
	{
		if (!GLSL_IsValidPermutationForGeneric (i))
		{
			continue;
		}

		attribs = ATTR_POSITION | ATTR_TEXCOORD0 | ATTR_NORMAL | ATTR_COLOR | ATTR_LIGHTDIRECTION;;
		extradefines[0] = '\0';

		if (i & GENERICDEF_USE_DEFORM_VERTEXES)
			Q_strcat(extradefines, 1024, "#define USE_DEFORM_VERTEXES\n");

		if (i & GENERICDEF_USE_TCGEN_AND_TCMOD)
		{
			Q_strcat(extradefines, 1024, "#define USE_TCGEN\n");
			Q_strcat(extradefines, 1024, "#define USE_TCMOD\n");
		}

		if (i & GENERICDEF_USE_VERTEX_ANIMATION)
		{
			Q_strcat(extradefines, 1024, "#define USE_VERTEX_ANIMATION\n");
			attribs |= ATTR_POSITION2 | ATTR_NORMAL2;
		}

		if (i & GENERICDEF_USE_SKELETAL_ANIMATION)
		{
			Q_strcat(extradefines, 1024, "#define USE_SKELETAL_ANIMATION\n");
			attribs |= ATTR_BONE_INDEXES | ATTR_BONE_WEIGHTS;
		}

		if (i & GENERICDEF_USE_FOG)
			Q_strcat(extradefines, 1024, "#define USE_FOG\n");

		if (i & GENERICDEF_USE_RGBAGEN)
			Q_strcat(extradefines, 1024, "#define USE_RGBAGEN\n");

		if (i & GENERICDEF_USE_GLOW_BUFFER)
			Q_strcat(extradefines, 1024, "#define USE_GLOW_BUFFER\n");

		
		if (!GLSL_BeginLoadGPUShader(&tr.genericShader[i], "generic", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_generic_vp, fallbackShader_generic_fp, NULL, NULL, NULL))
		{
			ri->Error(ERR_FATAL, "Could not load generic shader!");
		}
	}

	//ri->Error(ERR_DROP, "Oh noes!\n");


	attribs = ATTR_POSITION | ATTR_TEXCOORD0;

	if (!GLSL_BeginLoadGPUShader(&tr.textureColorShader, "texturecolor", attribs, qtrue, qfalse, qfalse, NULL, qfalse, NULL, fallbackShader_texturecolor_vp, fallbackShader_texturecolor_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load texturecolor shader!");
	}

	for (i = 0; i < FOGDEF_COUNT; i++)
	{
		if (!GLSL_IsValidPermutationForFog (i))
		{
			continue;
		}

		attribs = ATTR_POSITION | ATTR_POSITION2 | ATTR_NORMAL | ATTR_NORMAL2 | ATTR_TEXCOORD0;
		extradefines[0] = '\0';

		if (i & FOGDEF_USE_DEFORM_VERTEXES)
			Q_strcat(extradefines, 1024, "#define USE_DEFORM_VERTEXES\n");

		if (i & FOGDEF_USE_VERTEX_ANIMATION)
			Q_strcat(extradefines, 1024, "#define USE_VERTEX_ANIMATION\n");

		if (i & FOGDEF_USE_SKELETAL_ANIMATION)
			Q_strcat(extradefines, 1024, "#define USE_SKELETAL_ANIMATION\n");

		if (!GLSL_BeginLoadGPUShader(&tr.fogShader[i], "fogpass", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_fogpass_vp, fallbackShader_fogpass_fp, NULL, NULL, NULL))
		{
			ri->Error(ERR_FATAL, "Could not load fogpass shader!");
		}
	}

	for (i = 0; i < LIGHTDEF_COUNT; i++)
	{
		int lightType = i & LIGHTDEF_LIGHTTYPE_MASK;
		qboolean fastLight = (qboolean)!(r_normalMapping->integer || r_specularMapping->integer);

		// skip impossible combos
		if (!GLSL_IsValidPermutationForLight (lightType, i))
		{
			continue;
		}

		attribs = ATTR_POSITION | ATTR_TEXCOORD0 | ATTR_COLOR | ATTR_NORMAL | ATTR_TANGENT | ATTR_TEXCOORD1 | ATTR_LIGHTDIRECTION;

		extradefines[0] = '\0';

		if (r_deluxeSpecular->value > 0.000001f)
			Q_strcat(extradefines, 1024, va("#define r_deluxeSpecular %f\n", r_deluxeSpecular->value));

		if (r_specularIsMetallic->value)
			Q_strcat(extradefines, 1024, "#define SPECULAR_IS_METALLIC\n");

		if (r_dlightMode->integer >= 2)
			Q_strcat(extradefines, 1024, "#define USE_SHADOWMAP\n");

		if (r_hdr->integer && !glRefConfig.floatLightmap)
			Q_strcat(extradefines, 1024, "#define RGBM_LIGHTMAP\n");

		Q_strcat(extradefines, 1024, "#define USE_PRIMARY_LIGHT_SPECULAR\n");
		
		if (!lightType)
		{// UQ1: Meh! Force it!
			
			if (!(i & LIGHTDEF_ENTITY|LIGHTDEF_USE_TCGEN_AND_TCMOD))
			{
				Q_strcat(extradefines, 1024, "#define USE_LIGHT\n");
				Q_strcat(extradefines, 1024, "#define USE_LIGHT_VERTEX\n");
			}

			Q_strcat(extradefines, 1024, "#define USE_NORMALMAP\n");
		}

		if (lightType)
		{
			Q_strcat(extradefines, 1024, "#define USE_LIGHT\n");

			if (fastLight)
				Q_strcat(extradefines, 1024, "#define USE_FAST_LIGHT\n");

			switch (lightType)
			{
				case LIGHTDEF_USE_LIGHTMAP:
					Q_strcat(extradefines, 1024, "#define USE_LIGHTMAP\n");
					if (r_deluxeMapping->integer && !fastLight)
						Q_strcat(extradefines, 1024, "#define USE_DELUXEMAP\n");
					break;
				case LIGHTDEF_USE_LIGHT_VECTOR:
					Q_strcat(extradefines, 1024, "#define USE_LIGHT_VECTOR\n");
					break;
				case LIGHTDEF_USE_LIGHT_VERTEX:
					Q_strcat(extradefines, 1024, "#define USE_LIGHT_VERTEX\n");
					break;
				default:
					break;
			}

			if (r_normalMapping->integer)
			{
				Q_strcat(extradefines, 1024, "#define USE_NORMALMAP\n");

				if (r_normalMapping->integer == 2)
					Q_strcat(extradefines, 1024, "#define USE_OREN_NAYAR\n");

				if (r_normalMapping->integer == 3)
					Q_strcat(extradefines, 1024, "#define USE_TRIACE_OREN_NAYAR\n");

				Q_strcat(extradefines, 1024, "#define USE_PARALLAXMAP\n");

				if (r_parallaxMapping->integer && r_parallaxMapping->integer < 2) // Fast parallax mapping...
					Q_strcat(extradefines, 1024, "#define FAST_PARALLAX\n");
			}
			else if (r_parallaxMapping->integer) // Parallax without normal maps...
			{
				Q_strcat(extradefines, 1024, "#define USE_NORMALMAP\n");

				Q_strcat(extradefines, 1024, "#define USE_PARALLAXMAP\n");

				if (r_parallaxMapping->integer && r_parallaxMapping->integer < 2) // Fast parallax mapping...
					Q_strcat(extradefines, 1024, "#define FAST_PARALLAX\n");
			}

			if (r_specularMapping->integer)
			{
				Q_strcat(extradefines, 1024, "#define USE_SPECULARMAP\n");
			}

			if (r_cubeMapping->integer && (i & LIGHTDEF_USE_CUBEMAP))
			{
				Q_strcat(extradefines, 1024, "#define USE_CUBEMAP\n");
			}
		}

		//if (i & LIGHTDEF_USE_OVERLAY)
		{
			Q_strcat(extradefines, 1024, "#define USE_OVERLAY\n");
		}

		/*if (i & LIGHTDEF_USE_STEEPMAP)
		{
			Q_strcat(extradefines, 1024, "#define USE_STEEPMAP\n");
		}

		if (i & LIGHTDEF_USE_SWAY)
		{
			Q_strcat(extradefines, 1024, "#define USE_SWAY\n");
		}*/

		if (i & LIGHTDEF_USE_SHADOWMAP)
		{
			Q_strcat(extradefines, 1024, "#define USE_SHADOWMAP\n");

			if (r_sunlightMode->integer == 1)
				Q_strcat(extradefines, 1024, "#define SHADOWMAP_MODULATE\n");
			else if (r_sunlightMode->integer >= 2)
				Q_strcat(extradefines, 1024, "#define USE_PRIMARY_LIGHT\n");
		}

		if (i & LIGHTDEF_USE_TCGEN_AND_TCMOD)
		{
			Q_strcat(extradefines, 1024, "#define USE_TCGEN\n");
			Q_strcat(extradefines, 1024, "#define USE_TCMOD\n");
		}

		if (i & LIGHTDEF_ENTITY)
		{
			if (i & LIGHTDEF_USE_VERTEX_ANIMATION)
			{
				Q_strcat(extradefines, 1024, "#define USE_VERTEX_ANIMATION\n");
			}
			else if (i & LIGHTDEF_USE_SKELETAL_ANIMATION)
			{
				Q_strcat(extradefines, 1024, "#define USE_SKELETAL_ANIMATION\n");
				attribs |= ATTR_BONE_INDEXES | ATTR_BONE_WEIGHTS;
			}

			Q_strcat(extradefines, 1024, "#define USE_MODELMATRIX\n");
			attribs |= ATTR_POSITION2 | ATTR_NORMAL2;

			if (r_normalMapping->integer)
			{
				attribs |= ATTR_TANGENT2;
			}
		}

		if (i & LIGHTDEF_USE_GLOW_BUFFER)
			Q_strcat(extradefines, 1024, "#define USE_GLOW_BUFFER\n");

		/*
		if (i & LIGHTDEF_USE_FASTPASS)
		{
			Q_strcat(extradefines, 1024, "#define USE_FASTPASS\n");
		}
		*/

		if (r_tesselation->integer)
		{
			Q_strcat(extradefines, 1024, "#define USE_TESSELLATION\n");

			if (!GLSL_BeginLoadGPUShader(&tr.lightallShader[i], "lightall", attribs, qtrue, qtrue, qfalse, extradefines, qtrue, NULL, fallbackShader_lightall_vp, fallbackShader_lightall_fp, fallbackShader_genericTessControl_cp, fallbackShader_genericTessControl_ep, NULL))
			{
				ri->Error(ERR_FATAL, "Could not load lightall shader!");
			}
		}
		else
		{
			if (!GLSL_BeginLoadGPUShader(&tr.lightallShader[i], "lightall", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_lightall_vp, fallbackShader_lightall_fp, NULL, NULL, NULL))
			{
				ri->Error(ERR_FATAL, "Could not load lightall shader!");
			}
		}
	}

	if (r_foliage->integer)
	{
		attribs = ATTR_POSITION | ATTR_TEXCOORD0 | ATTR_COLOR | ATTR_NORMAL | ATTR_TANGENT | ATTR_TEXCOORD1 | ATTR_LIGHTDIRECTION;

		extradefines[0] = '\0';

		//Q_strcat(extradefines, 1024, "#define USE_PRIMARY_LIGHT_SPECULAR\n");

		if (r_foliage->integer >= 2)
		{
			if (!GLSL_BeginLoadGPUShader(&tr.grass2Shader, "grass3", attribs, qtrue, qfalse, qtrue, extradefines, qtrue, "330", fallbackShader_grass3_vp, fallbackShader_grass3_fp, NULL, NULL, fallbackShader_grass3_gs))
			{
				ri->Error(ERR_FATAL, "Could not load grass3 shader!");
			}
		}
		else 
		{
			if (!GLSL_BeginLoadGPUShader(&tr.grass2Shader, "grass2", attribs, qtrue, qfalse, qtrue, extradefines, qtrue, "400 compatibility", fallbackShader_grass2_vp, fallbackShader_grass2_fp, NULL, NULL, fallbackShader_grass2_gs))
			{
				ri->Error(ERR_FATAL, "Could not load grass2 shader!");
			}
		}
	}

	
	attribs = ATTR_POSITION | ATTR_POSITION2 | ATTR_NORMAL | ATTR_NORMAL2 | ATTR_TEXCOORD0;

	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.shadowmapShader, "shadowfill", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_shadowfill_vp, fallbackShader_shadowfill_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load shadowfill shader!");
	}

	attribs = ATTR_POSITION | ATTR_NORMAL;
	extradefines[0] = '\0';

	Q_strcat(extradefines, 1024, "#define USE_PCF\n#define USE_DISCARD\n");

	if (!GLSL_BeginLoadGPUShader(&tr.pshadowShader, "pshadow", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_pshadow_vp, fallbackShader_pshadow_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load pshadow shader!");
	}


	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.down4xShader, "down4x", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_down4x_vp, fallbackShader_down4x_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load down4x shader!");
	}


	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.bokehShader, "bokeh", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_bokeh_vp, fallbackShader_bokeh_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load bokeh shader!");
	}


	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.tonemapShader, "tonemap", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_tonemap_vp, fallbackShader_tonemap_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load tonemap shader!");
	}


	for (i = 0; i < 2; i++)
	{
		attribs = ATTR_POSITION | ATTR_TEXCOORD0;
		extradefines[0] = '\0';

		if (!i)
			Q_strcat(extradefines, 1024, "#define FIRST_PASS\n");

		if (!GLSL_BeginLoadGPUShader(&tr.calclevels4xShader[i], "calclevels4x", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_calclevels4x_vp, fallbackShader_calclevels4x_fp, NULL, NULL, NULL))
		{
			ri->Error(ERR_FATAL, "Could not load calclevels4x shader!");
		}		
	}


	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (r_shadowFilter->integer >= 1)
		Q_strcat(extradefines, 1024, "#define USE_SHADOW_FILTER\n");

	if (r_shadowFilter->integer >= 2)
		Q_strcat(extradefines, 1024, "#define USE_SHADOW_FILTER2\n");

	Q_strcat(extradefines, 1024, "#define USE_SHADOW_CASCADE\n");

	Q_strcat(extradefines, 1024, va("#define r_shadowMapSize %d\n", r_shadowMapSize->integer));
	Q_strcat(extradefines, 1024, va("#define r_shadowCascadeZFar %f\n", r_shadowCascadeZFar->value));


	if (!GLSL_BeginLoadGPUShader(&tr.shadowmaskShader, "shadowmask", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_shadowmask_vp, fallbackShader_shadowmask_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load shadowmask shader!");
	}


	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.ssaoShader, "ssao", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_ssao_vp, fallbackShader_ssao_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load ssao shader!");
	}


	for (i = 0; i < 2; i++)
	{
		attribs = ATTR_POSITION | ATTR_TEXCOORD0;
		extradefines[0] = '\0';

		if (i & 1)
			Q_strcat(extradefines, 1024, "#define USE_VERTICAL_BLUR\n");
		else
			Q_strcat(extradefines, 1024, "#define USE_HORIZONTAL_BLUR\n");


		if (!GLSL_BeginLoadGPUShader(&tr.depthBlurShader[i], "depthBlur", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_depthblur_vp, fallbackShader_depthblur_fp, NULL, NULL, NULL))
		{
			ri->Error(ERR_FATAL, "Could not load depthBlur shader!");
		}
	}

#if 0
	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_InitGPUShader(&tr.testcubeShader, "testcube", attribs, qtrue, qfalse, extradefines, qtrue, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load testcube shader!");
	}

	GLSL_InitUniforms(&tr.testcubeShader);

	qglUseProgram(tr.testcubeShader.program);
	GLSL_SetUniformInt(&tr.testcubeShader, UNIFORM_TEXTUREMAP, TB_COLORMAP);
	qglUseProgram(0);

	GLSL_FinishGPUShader(&tr.testcubeShader);

	numEtcShaders++;
#endif

	attribs = 0;
	extradefines[0] = '\0';
	Q_strcat (extradefines, sizeof (extradefines), "#define BLUR_X");

	if (!GLSL_BeginLoadGPUShader(&tr.gaussianBlurShader[0], "gaussian_blur", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_gaussian_blur_vp, fallbackShader_gaussian_blur_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load gaussian_blur (X-direction) shader!");
	}

	attribs = 0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.gaussianBlurShader[1], "gaussian_blur", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_gaussian_blur_vp, fallbackShader_gaussian_blur_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load gaussian_blur (Y-direction) shader!");
	}

	attribs = 0;
	extradefines[0] = '\0';
	if (!GLSL_BeginLoadGPUShader(&tr.dglowDownsample, "dglow_downsample", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_dglow_downsample_vp, fallbackShader_dglow_downsample_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load dynamic glow downsample shader!");
	}

	attribs = 0;
	extradefines[0] = '\0';
	if (!GLSL_BeginLoadGPUShader(&tr.dglowUpsample, "dglow_upsample", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_dglow_upsample_vp, fallbackShader_dglow_upsample_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load dynamic glow upsample shader!");
	}

	//
	// UQ1: Added...
	//

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.darkexpandShader, "darkexpand", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_darkexpand_vp, fallbackShader_darkexpand_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load darkexpand shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.multipostShader, "multipost", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_multipost_vp, fallbackShader_multipost_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load multipost shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	Q_strcat(extradefines, 1024, "#define DUAL_PASS\n");

	if (!GLSL_BeginLoadGPUShader(&tr.volumeLightShader[0], "volumelight", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_volumelight_vp, fallbackShader_volumelight_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load volumelight shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	Q_strcat(extradefines, 1024, "#define DUAL_PASS\n");
	Q_strcat(extradefines, 1024, "#define MQ_VOLUMETRIC\n");

	if (!GLSL_BeginLoadGPUShader(&tr.volumeLightShader[1], "volumelight", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_volumelight_vp, fallbackShader_volumelight_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load volumelight shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	Q_strcat(extradefines, 1024, "#define DUAL_PASS\n");
	Q_strcat(extradefines, 1024, "#define HQ_VOLUMETRIC\n");

	if (!GLSL_BeginLoadGPUShader(&tr.volumeLightShader[2], "volumelight", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_volumelight_vp, fallbackShader_volumelight_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load volumelight shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.volumeLightCombineShader, "volumelightCombine", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_volumelightCombine_vp, fallbackShader_volumelightCombine_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load volumelightCombine shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.bloomBlurShader, "bloom_blur", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_bloom_blur_vp, fallbackShader_bloom_blur_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load bloom_blur shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.bloomCombineShader, "bloom_combine", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_bloom_combine_vp, fallbackShader_bloom_combine_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load bloom_combine shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.lensflareShader, "lensflare", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_lensflare_vp, fallbackShader_lensflare_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load lensflare shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.anamorphicBlurShader, "anamorphic_blur", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_anamorphic_blur_vp, fallbackShader_anamorphic_blur_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load anamorphic_blur shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.anamorphicCombineShader, "anamorphic_combine", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_anamorphic_combine_vp, fallbackShader_anamorphic_combine_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load anamorphic_combine shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.hdrShader, "hdr", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_truehdr_vp, fallbackShader_truehdr_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load hdr shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.magicdetailShader, "magicdetail", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_magicdetail_vp, fallbackShader_magicdetail_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load magicdetail shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.waterPostShader, "waterPost", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_waterPost_vp, fallbackShader_waterPost_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load waterPost shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	Q_strcat(extradefines, 1024, "#define FAST_SSGI\n");

	if (!GLSL_BeginLoadGPUShader(&tr.ssgi1Shader, "ssgi1", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_ssgi_vp, fallbackShader_ssgi1_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load ssgi1 shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	Q_strcat(extradefines, 1024, "#define FAST_SSGI\n");

	if (!GLSL_BeginLoadGPUShader(&tr.ssgi2Shader, "ssgi2", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_ssgi_vp, fallbackShader_ssgi2_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load ssgi2 shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	Q_strcat(extradefines, 1024, "#define FAST_SSGI\n");

	if (!GLSL_BeginLoadGPUShader(&tr.ssgi3Shader, "ssgi3", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_ssgi_vp, fallbackShader_ssgi3_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load ssgi3 shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	Q_strcat(extradefines, 1024, "#define FAST_SSGI\n");

	if (!GLSL_BeginLoadGPUShader(&tr.ssgi4Shader, "ssgi4", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_ssgi_vp, fallbackShader_ssgi4_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load ssgi4 shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.ssgi5Shader, "ssgi5", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_ssgi_vp, fallbackShader_ssgi2_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load ssgi5 shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.ssgi6Shader, "ssgi6", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_ssgi_vp, fallbackShader_ssgi3_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load ssgi6 shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.ssgi7Shader, "ssgi7", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_ssgi_vp, fallbackShader_ssgi4_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load ssgi7 shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.ssgiBlurShader, "ssgi_blur", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_ssgi_blur_vp, fallbackShader_ssgi_blur_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load ssgi_blur shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.fastBlurShader, "fastBlur", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_fastBlur_vp, fallbackShader_fastBlur_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load fastBlur shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.distanceBlurShader, "distanceBlur", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_distanceBlur_vp, fallbackShader_distanceBlur_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load distanceBlur shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.testshaderShader, "testshader", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_testshader_vp, fallbackShader_testshader_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load testshader shader!");
	}

#if 0
	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.dofShader, "depthOfField", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_depthOfField_vp, fallbackShader_depthOfField_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load depthOfField shader!");
	}
#else
	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	Q_strcat(extradefines, 1024, "#define FAST_DOF\n");

	if (!GLSL_BeginLoadGPUShader(&tr.dofShader, "depthOfField2", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_depthOfField2_vp, fallbackShader_depthOfField2_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load depthOfField shader!");
	}
#endif

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.dof2Shader, "depthOfField2", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_depthOfField2_vp, fallbackShader_depthOfField2_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load depthOfField2 shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.vibrancyShader, "vibrancy", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_vibrancy_vp, fallbackShader_vibrancy_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load vibrancy shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.texturecleanShader, "textureclean", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_textureclean_vp, fallbackShader_textureclean_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load textureclean shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.esharpeningShader, "esharpening", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_esharpening_vp, fallbackShader_esharpening_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load esharpening shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.esharpening2Shader, "esharpening2", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_esharpening2_vp, fallbackShader_esharpening2_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load esharpening2 shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.fxaaShader, "fxaa", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_fxaa_vp, fallbackShader_fxaa_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load fxaa shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.generateNormalMapShader, "generateNormalMap", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, "130", fallbackShader_generateNormalMap_vp, fallbackShader_generateNormalMap_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load generateNormalMap shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.underwaterShader, "underwater", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_underwater_vp, fallbackShader_underwater_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load underwater shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.fakedepthShader, "fakedepth", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_fakeDepth_vp, fallbackShader_fakeDepth_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load fake depth shader!");
	}


	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.fakedepthSteepParallaxShader, "fakedepthSteepParallax", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_fakeDepthSteepParallax_vp, fallbackShader_fakeDepthSteepParallax_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load fake depth steep parallax shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.anaglyphShader, "anaglyph", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_anaglyph_vp, fallbackShader_anaglyph_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load anaglyph shader!");
	}

	
	attribs = ATTR_POSITION | ATTR_TEXCOORD0 | ATTR_NORMAL | ATTR_COLOR;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.uniqueskyShader, "uniquesky", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, "130", fallbackShader_uniquesky_vp, fallbackShader_uniquesky_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load uniquesky shader!");
	}




	
	attribs = ATTR_POSITION | ATTR_TEXCOORD0 | ATTR_COLOR | ATTR_NORMAL | ATTR_TANGENT;
	extradefines[0] = '\0';

	if (r_deluxeSpecular->value > 0.000001f)
		Q_strcat(extradefines, 1024, va("#define r_deluxeSpecular %f\n", r_deluxeSpecular->value));

	if (r_specularIsMetallic->value)
		Q_strcat(extradefines, 1024, "#define SPECULAR_IS_METALLIC\n");

	if (r_dlightMode->integer >= 2)
		Q_strcat(extradefines, 1024, "#define USE_SHADOWMAP\n");

	if (1)
		Q_strcat(extradefines, 1024, "#define SWIZZLE_NORMALMAP\n");

	if (r_hdr->integer && !glRefConfig.floatLightmap)
		Q_strcat(extradefines, 1024, "#define RGBM_LIGHTMAP\n");

	Q_strcat(extradefines, 1024, "#define USE_LIGHT\n");

	Q_strcat(extradefines, 1024, "#define USE_LIGHTMAP\n");

	if (r_deluxeMapping->integer)
		Q_strcat(extradefines, 1024, "#define USE_DELUXEMAP\n");

	attribs |= ATTR_TEXCOORD1 | ATTR_LIGHTDIRECTION;

	if (r_normalMapping->integer)
	{
		Q_strcat(extradefines, 1024, "#define USE_NORMALMAP\n");

		if (r_normalMapping->integer == 2)
			Q_strcat(extradefines, 1024, "#define USE_OREN_NAYAR\n");

		if (r_normalMapping->integer == 3)
			Q_strcat(extradefines, 1024, "#define USE_TRIACE_OREN_NAYAR\n");

		Q_strcat(extradefines, 1024, "#define USE_PARALLAXMAP_NONORMALS\n");
	}

	if (r_specularMapping->integer)
	{
		Q_strcat(extradefines, 1024, "#define USE_SPECULARMAP\n");
	}

	if (r_cubeMapping->integer)
		Q_strcat(extradefines, 1024, "#define USE_CUBEMAP\n");

	Q_strcat(extradefines, 1024, "#define USE_SHADOWMAP\n");

	if (r_sunlightMode->integer == 1)
		Q_strcat(extradefines, 1024, "#define SHADOWMAP_MODULATE\n");
	else if (r_sunlightMode->integer >= 2)
		Q_strcat(extradefines, 1024, "#define USE_PRIMARY_LIGHT\n");

	//if (i & LIGHTDEF_USE_TCGEN_AND_TCMOD)
	{
		Q_strcat(extradefines, 1024, "#define USE_TCGEN\n");
		Q_strcat(extradefines, 1024, "#define USE_TCMOD\n");
	}

	//if (i & LIGHTDEF_ENTITY)
	{
		//if (i & LIGHTDEF_USE_VERTEX_ANIMATION)
		{
			Q_strcat(extradefines, 1024, "#define USE_VERTEX_ANIMATION\n");
		}
		/*else if (i & LIGHTDEF_USE_SKELETAL_ANIMATION)
		{
			Q_strcat(extradefines, 1024, "#define USE_SKELETAL_ANIMATION\n");
			attribs |= ATTR_BONE_INDEXES | ATTR_BONE_WEIGHTS;
		}*/

		Q_strcat(extradefines, 1024, "#define USE_MODELMATRIX\n");
		attribs |= ATTR_POSITION2 | ATTR_NORMAL2;

		if (r_normalMapping->integer)
		{
			attribs |= ATTR_TANGENT2;
		}
	}

	//if (i & LIGHTDEF_USE_GLOW_BUFFER)
		Q_strcat(extradefines, 1024, "#define USE_GLOW_BUFFER\n");

	if (!GLSL_BeginLoadGPUShader(&tr.waterShader, "uniquewater", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_uniquewater_vp, fallbackShader_uniquewater_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load water shader!");
	}




	attribs = ATTR_POSITION | ATTR_TEXCOORD0 | ATTR_COLOR | ATTR_NORMAL;
	extradefines[0] = '\0';

	if (r_deluxeSpecular->value > 0.000001f)
		Q_strcat(extradefines, 1024, va("#define r_deluxeSpecular %f\n", r_deluxeSpecular->value));

	if (r_specularIsMetallic->value)
		Q_strcat(extradefines, 1024, "#define SPECULAR_IS_METALLIC\n");

	if (r_dlightMode->integer >= 2)
		Q_strcat(extradefines, 1024, "#define USE_SHADOWMAP\n");

	if (1)
		Q_strcat(extradefines, 1024, "#define SWIZZLE_NORMALMAP\n");

	if (r_hdr->integer && !glRefConfig.floatLightmap)
		Q_strcat(extradefines, 1024, "#define RGBM_LIGHTMAP\n");

	Q_strcat(extradefines, 1024, "#define USE_LIGHT\n");

	Q_strcat(extradefines, 1024, "#define USE_LIGHTMAP\n");

	if (r_deluxeMapping->integer)
		Q_strcat(extradefines, 1024, "#define USE_DELUXEMAP\n");

	attribs |= ATTR_TEXCOORD1 | ATTR_LIGHTDIRECTION | ATTR_TANGENT;

	if (r_normalMapping->integer)
	{
		Q_strcat(extradefines, 1024, "#define USE_NORMALMAP\n");

		if (r_normalMapping->integer == 2)
			Q_strcat(extradefines, 1024, "#define USE_OREN_NAYAR\n");

		if (r_normalMapping->integer == 3)
			Q_strcat(extradefines, 1024, "#define USE_TRIACE_OREN_NAYAR\n");

		Q_strcat(extradefines, 1024, "#define USE_PARALLAXMAP_NONORMALS\n");
	}

	if (r_specularMapping->integer)
	{
		Q_strcat(extradefines, 1024, "#define USE_SPECULARMAP\n");
	}

	if (r_cubeMapping->integer)
		Q_strcat(extradefines, 1024, "#define USE_CUBEMAP\n");

	Q_strcat(extradefines, 1024, "#define USE_SHADOWMAP\n");

	if (r_sunlightMode->integer == 1)
		Q_strcat(extradefines, 1024, "#define SHADOWMAP_MODULATE\n");
	else if (r_sunlightMode->integer >= 2)
		Q_strcat(extradefines, 1024, "#define USE_PRIMARY_LIGHT\n");

	//if (i & LIGHTDEF_USE_TCGEN_AND_TCMOD)
	{
		Q_strcat(extradefines, 1024, "#define USE_TCGEN\n");
		Q_strcat(extradefines, 1024, "#define USE_TCMOD\n");
	}

	//if (i & LIGHTDEF_ENTITY)
	{
		//if (i & LIGHTDEF_USE_VERTEX_ANIMATION)
		{
			Q_strcat(extradefines, 1024, "#define USE_VERTEX_ANIMATION\n");
		}
		/*else if (i & LIGHTDEF_USE_SKELETAL_ANIMATION)
		{
			Q_strcat(extradefines, 1024, "#define USE_SKELETAL_ANIMATION\n");
			attribs |= ATTR_BONE_INDEXES | ATTR_BONE_WEIGHTS;
		}*/

		Q_strcat(extradefines, 1024, "#define USE_MODELMATRIX\n");
		attribs |= ATTR_POSITION2 | ATTR_NORMAL2;

		if (r_normalMapping->integer)
		{
			attribs |= ATTR_TANGENT2;
		}
	}

	//if (i & LIGHTDEF_USE_GLOW_BUFFER)
		Q_strcat(extradefines, 1024, "#define USE_GLOW_BUFFER\n");

	if (!GLSL_BeginLoadGPUShader(&tr.grassShader, "grass", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_grass_vp, fallbackShader_grass_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load grass shader!");
	}




	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.sssShader, "sss", attribs, qtrue, qfalse, qfalse, extradefines, qfalse, NULL, fallbackShader_sss_vp, fallbackShader_sss_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load sss shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.sss2Shader, "sss2", attribs, qtrue, qfalse, qfalse, extradefines, qfalse, NULL, fallbackShader_sss2_vp, fallbackShader_sss2_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load sss2 shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.rbmShader, "rbm", attribs, qtrue, qfalse, qfalse, extradefines, qfalse, NULL, fallbackShader_rbm_vp, fallbackShader_rbm_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load rbm shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	Q_strcat(extradefines, 1024, "#define FAST_HBAO\n");

	if (!GLSL_BeginLoadGPUShader(&tr.hbaoShader, "hbao", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_hbao_vp, fallbackShader_hbao_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load hbao shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.hbao2Shader, "hbao2", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_hbao_vp, fallbackShader_hbao_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load hbao2 shader!");
	}

	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_BeginLoadGPUShader(&tr.hbaoCombineShader, "hbaoCombine", attribs, qtrue, qfalse, qfalse, extradefines, qtrue, NULL, fallbackShader_hbaoCombine_vp, fallbackShader_hbaoCombine_fp, NULL, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load hbaoCombine shader!");
	}

	//
	// UQ1: End Added...
	//

	//ri->Error(ERR_DROP, "Oh noes!\n");
	return startTime;
}

void GLSL_EndLoadGPUShaders ( int startTime )
{
	int i;
	int numGenShaders = 0, numLightShaders = 0, numEtcShaders = 0;

	for (i = 0; i < GENERICDEF_COUNT; i++)
	{
		if (!GLSL_IsValidPermutationForGeneric (i))
		{
			continue;
		}

		if (!GLSL_EndLoadGPUShader(&tr.genericShader[i]))
		{
			ri->Error(ERR_FATAL, "Could not load fogpass shader!");
		}

		GLSL_InitUniforms(&tr.genericShader[i]);

		qglUseProgram(tr.genericShader[i].program);
		GLSL_SetUniformInt(&tr.genericShader[i], UNIFORM_DIFFUSEMAP, TB_DIFFUSEMAP);
		GLSL_SetUniformInt(&tr.genericShader[i], UNIFORM_LIGHTMAP,   TB_LIGHTMAP);
		qglUseProgram(0);

#if defined(_DEBUG)
		GLSL_FinishGPUShader(&tr.genericShader[i]);
#endif

		numGenShaders++;
	}

	if (!GLSL_EndLoadGPUShader (&tr.textureColorShader))
	{
		ri->Error(ERR_FATAL, "Could not load texturecolor shader!");
	}
	
	GLSL_InitUniforms(&tr.textureColorShader);

	qglUseProgram(tr.textureColorShader.program);
	GLSL_SetUniformInt(&tr.textureColorShader, UNIFORM_TEXTUREMAP, TB_DIFFUSEMAP);
	qglUseProgram(0);

	GLSL_FinishGPUShader(&tr.textureColorShader);

	numEtcShaders++;

	for (i = 0; i < FOGDEF_COUNT; i++)
	{
		if (!GLSL_IsValidPermutationForFog (i))
		{
			continue;
		}

		if (!GLSL_EndLoadGPUShader(&tr.fogShader[i]))
		{
			ri->Error(ERR_FATAL, "Could not load fogpass shader!");
		}
		
		GLSL_InitUniforms(&tr.fogShader[i]);
#if defined(_DEBUG)
		GLSL_FinishGPUShader(&tr.fogShader[i]);
#endif
		
		numEtcShaders++;
	}


	for (i = 0; i < LIGHTDEF_COUNT; i++)
	{
		int lightType = i & LIGHTDEF_LIGHTTYPE_MASK;
		qboolean fastLight = (qboolean)!(r_normalMapping->integer || r_specularMapping->integer);

		// skip impossible combos
		if (!GLSL_IsValidPermutationForLight (lightType, i))
		{
			continue;
		}

		if (!GLSL_EndLoadGPUShader(&tr.lightallShader[i]))
		{
			ri->Error(ERR_FATAL, "Could not load lightall shader!");
		}
		
		GLSL_InitUniforms(&tr.lightallShader[i]);

		qglUseProgram(tr.lightallShader[i].program);
		GLSL_SetUniformInt(&tr.lightallShader[i], UNIFORM_DIFFUSEMAP,  TB_DIFFUSEMAP);
		GLSL_SetUniformInt(&tr.lightallShader[i], UNIFORM_LIGHTMAP,    TB_LIGHTMAP);
		GLSL_SetUniformInt(&tr.lightallShader[i], UNIFORM_NORMALMAP,   TB_NORMALMAP);
		GLSL_SetUniformInt(&tr.lightallShader[i], UNIFORM_DELUXEMAP,   TB_DELUXEMAP);
		GLSL_SetUniformInt(&tr.lightallShader[i], UNIFORM_SPECULARMAP, TB_SPECULARMAP);
		GLSL_SetUniformInt(&tr.lightallShader[i], UNIFORM_SHADOWMAP,   TB_SHADOWMAP);
		GLSL_SetUniformInt(&tr.lightallShader[i], UNIFORM_CUBEMAP,     TB_CUBEMAP);
		//GLSL_SetUniformInt(&tr.lightallShader[i], UNIFORM_SUBSURFACEMAP, TB_SUBSURFACEMAP);
		GLSL_SetUniformInt(&tr.lightallShader[i], UNIFORM_OVERLAYMAP, TB_OVERLAYMAP);
		GLSL_SetUniformInt(&tr.lightallShader[i], UNIFORM_STEEPMAP, TB_STEEPMAP);
		qglUseProgram(0);

#if defined(_DEBUG)
		GLSL_FinishGPUShader(&tr.lightallShader[i]);
#endif
		
		numLightShaders++;
	}

	
	if (r_foliage->integer)
	{
		if (!GLSL_EndLoadGPUShader(&tr.grass2Shader))
		{
			ri->Error(ERR_FATAL, "Could not load grass2 shader!");
		}
		
		GLSL_InitUniforms(&tr.grass2Shader);

		qglUseProgram(tr.grass2Shader.program);
		GLSL_SetUniformInt(&tr.grass2Shader, UNIFORM_DIFFUSEMAP,  TB_DIFFUSEMAP);
		GLSL_SetUniformInt(&tr.grass2Shader, UNIFORM_LIGHTMAP,    TB_LIGHTMAP);
		GLSL_SetUniformInt(&tr.grass2Shader, UNIFORM_NORMALMAP,   TB_NORMALMAP);
		GLSL_SetUniformInt(&tr.grass2Shader, UNIFORM_DELUXEMAP,   TB_DELUXEMAP);
		GLSL_SetUniformInt(&tr.grass2Shader, UNIFORM_SPECULARMAP, TB_SPECULARMAP);
		GLSL_SetUniformInt(&tr.grass2Shader, UNIFORM_SHADOWMAP,   TB_SHADOWMAP);
		GLSL_SetUniformInt(&tr.grass2Shader, UNIFORM_CUBEMAP,     TB_CUBEMAP);
		//GLSL_SetUniformInt(&tr.grass2Shader, UNIFORM_SUBSURFACEMAP, TB_SUBSURFACEMAP);
		GLSL_SetUniformInt(&tr.grass2Shader, UNIFORM_OVERLAYMAP, TB_OVERLAYMAP);
		GLSL_SetUniformInt(&tr.grass2Shader, UNIFORM_STEEPMAP, TB_STEEPMAP);
		qglUseProgram(0);

#if defined(_DEBUG)
		GLSL_FinishGPUShader(&tr.grass2Shader);
#endif
		
		numEtcShaders++;
	}

	
	if (!GLSL_EndLoadGPUShader(&tr.shadowmapShader))
	{
		ri->Error(ERR_FATAL, "Could not load shadowfill shader!");
	}
	
	GLSL_InitUniforms(&tr.shadowmapShader);
#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.shadowmapShader);
#endif

	numEtcShaders++;

	if (!GLSL_EndLoadGPUShader(&tr.pshadowShader))
	{
		ri->Error(ERR_FATAL, "Could not load pshadow shader!");
	}
	
	GLSL_InitUniforms(&tr.pshadowShader);

	qglUseProgram(tr.pshadowShader.program);
	GLSL_SetUniformInt(&tr.pshadowShader, UNIFORM_SHADOWMAP, TB_DIFFUSEMAP);
	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.pshadowShader);
#endif
	
	numEtcShaders++;

	if (!GLSL_EndLoadGPUShader(&tr.down4xShader))
	{
		ri->Error(ERR_FATAL, "Could not load down4x shader!");
	}
	
	GLSL_InitUniforms(&tr.down4xShader);

	qglUseProgram(tr.down4xShader.program);
	GLSL_SetUniformInt(&tr.down4xShader, UNIFORM_TEXTUREMAP, TB_DIFFUSEMAP);
	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.down4xShader);
#endif
	
	numEtcShaders++;

	if (!GLSL_EndLoadGPUShader(&tr.bokehShader))
	{
		ri->Error(ERR_FATAL, "Could not load bokeh shader!");
	}
	
	GLSL_InitUniforms(&tr.bokehShader);

	qglUseProgram(tr.bokehShader.program);
	GLSL_SetUniformInt(&tr.bokehShader, UNIFORM_TEXTUREMAP, TB_DIFFUSEMAP);
	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.bokehShader);
#endif
	
	numEtcShaders++;

	if (!GLSL_EndLoadGPUShader(&tr.tonemapShader))
	{
		ri->Error(ERR_FATAL, "Could not load tonemap shader!");
	}
	
	GLSL_InitUniforms(&tr.tonemapShader);

	qglUseProgram(tr.tonemapShader.program);
	GLSL_SetUniformInt(&tr.tonemapShader, UNIFORM_TEXTUREMAP, TB_COLORMAP);
	GLSL_SetUniformInt(&tr.tonemapShader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);
	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.tonemapShader);
#endif
	
	numEtcShaders++;

	for (i = 0; i < 2; i++)
	{
		if (!GLSL_EndLoadGPUShader(&tr.calclevels4xShader[i]))
		{
			ri->Error(ERR_FATAL, "Could not load calclevels4x shader!");
		}
		
		GLSL_InitUniforms(&tr.calclevels4xShader[i]);

		qglUseProgram(tr.calclevels4xShader[i].program);
		GLSL_SetUniformInt(&tr.calclevels4xShader[i], UNIFORM_TEXTUREMAP, TB_DIFFUSEMAP);
		qglUseProgram(0);

#if defined(_DEBUG)
		GLSL_FinishGPUShader(&tr.calclevels4xShader[i]);
#endif
		
		numEtcShaders++;		
	}

	if (!GLSL_EndLoadGPUShader(&tr.shadowmaskShader))
	{
		ri->Error(ERR_FATAL, "Could not load shadowmask shader!");
	}
	
	GLSL_InitUniforms(&tr.shadowmaskShader);

	qglUseProgram(tr.shadowmaskShader.program);
	GLSL_SetUniformInt(&tr.shadowmaskShader, UNIFORM_SCREENDEPTHMAP, TB_COLORMAP);
	GLSL_SetUniformInt(&tr.shadowmaskShader, UNIFORM_SHADOWMAP,  TB_SHADOWMAP);
	GLSL_SetUniformInt(&tr.shadowmaskShader, UNIFORM_SHADOWMAP2, TB_SHADOWMAP2);
	GLSL_SetUniformInt(&tr.shadowmaskShader, UNIFORM_SHADOWMAP3, TB_SHADOWMAP3);
	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.shadowmaskShader);
#endif
	
	numEtcShaders++;

	if (!GLSL_EndLoadGPUShader(&tr.ssaoShader))
	{
		ri->Error(ERR_FATAL, "Could not load ssao shader!");
	}

	GLSL_InitUniforms(&tr.ssaoShader);

	qglUseProgram(tr.ssaoShader.program);
	GLSL_SetUniformInt(&tr.ssaoShader, UNIFORM_SCREENDEPTHMAP, TB_COLORMAP);
	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.ssaoShader);
#endif

	numEtcShaders++;

	for (i = 0; i < 2; i++)
	{
		if (!GLSL_EndLoadGPUShader(&tr.depthBlurShader[i]))
		{
			ri->Error(ERR_FATAL, "Could not load depthBlur shader!");
		}

		GLSL_InitUniforms(&tr.depthBlurShader[i]);

		qglUseProgram(tr.depthBlurShader[i].program);
		GLSL_SetUniformInt(&tr.depthBlurShader[i], UNIFORM_SCREENIMAGEMAP, TB_COLORMAP);
		GLSL_SetUniformInt(&tr.depthBlurShader[i], UNIFORM_SCREENDEPTHMAP, TB_LIGHTMAP);
		qglUseProgram(0);

#if defined(_DEBUG)
		GLSL_FinishGPUShader(&tr.depthBlurShader[i]);
#endif

		numEtcShaders++;
	}

	for (i = 0; i < 2; i++)
	{
		if (!GLSL_EndLoadGPUShader(&tr.gaussianBlurShader[i]))
		{
			ri->Error(ERR_FATAL, "Could not load gaussian blur shader!");
		}

		GLSL_InitUniforms(&tr.gaussianBlurShader[i]);

#if defined(_DEBUG)
		GLSL_FinishGPUShader(&tr.gaussianBlurShader[i]);
#endif

		numEtcShaders++;
	}

	if (!GLSL_EndLoadGPUShader(&tr.dglowDownsample))
	{
		ri->Error(ERR_FATAL, "Could not load dynamic glow downsample shader!");
	}

	GLSL_InitUniforms(&tr.dglowDownsample);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.dglowDownsample);
#endif

	numEtcShaders++;

	if (!GLSL_EndLoadGPUShader(&tr.dglowUpsample))
	{
		ri->Error(ERR_FATAL, "Could not load dynamic glow upsample shader!");
	}

	GLSL_InitUniforms(&tr.dglowUpsample);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.dglowUpsample);
#endif

	numEtcShaders++;

#if 0
	attribs = ATTR_POSITION | ATTR_TEXCOORD0;
	extradefines[0] = '\0';

	if (!GLSL_InitGPUShader(&tr.testcubeShader, "testcube", attribs, qtrue, extradefines, qtrue, NULL, NULL))
	{
		ri->Error(ERR_FATAL, "Could not load testcube shader!");
	}

	GLSL_InitUniforms(&tr.testcubeShader);

	qglUseProgram(tr.testcubeShader.program);
	GLSL_SetUniformInt(&tr.testcubeShader, UNIFORM_TEXTUREMAP, TB_COLORMAP);
	qglUseProgram(0);

	GLSL_FinishGPUShader(&tr.testcubeShader);

	numEtcShaders++;
#endif



	//
	// UQ1: Added...
	//

	if (!GLSL_EndLoadGPUShader(&tr.darkexpandShader))
	{
		ri->Error(ERR_FATAL, "Could not load darkexpand shader!");
	}
	
	GLSL_InitUniforms(&tr.darkexpandShader);

	qglUseProgram(tr.darkexpandShader.program);

	GLSL_SetUniformInt(&tr.darkexpandShader, UNIFORM_TEXTUREMAP, TB_COLORMAP);
	GLSL_SetUniformInt(&tr.darkexpandShader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);

	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.darkexpandShader, UNIFORM_VIEWINFO, viewInfo);
	}

	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.darkexpandShader, UNIFORM_DIMENSIONS, screensize);

		//ri->Printf(PRINT_WARNING, "Sent dimensions %f %f.\n", screensize[0], screensize[1]);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.darkexpandShader);
#endif
	
	numEtcShaders++;



	if (!GLSL_EndLoadGPUShader(&tr.multipostShader))
	{
		ri->Error(ERR_FATAL, "Could not load multipost shader!");
	}
	
	GLSL_InitUniforms(&tr.multipostShader);
	qglUseProgram(tr.multipostShader.program);
	GLSL_SetUniformInt(&tr.multipostShader, UNIFORM_DIFFUSEMAP, TB_DIFFUSEMAP);
	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.multipostShader);
#endif
	
	numEtcShaders++;

	for (int i = 0; i < 3; i++)
	{
	if (!GLSL_EndLoadGPUShader(&tr.volumeLightShader[i]))
	{
		ri->Error(ERR_FATAL, "Could not load volumelight shader!");
	}
	
	GLSL_InitUniforms(&tr.volumeLightShader[i]);
	qglUseProgram(tr.volumeLightShader[i].program);
	GLSL_SetUniformInt(&tr.volumeLightShader[i], UNIFORM_DIFFUSEMAP, TB_DIFFUSEMAP);
	GLSL_SetUniformInt(&tr.volumeLightShader[i], UNIFORM_SCREENDEPTHMAP, TB_LIGHTMAP);
	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.volumeLightShader[i]);
#endif
	
	numEtcShaders++;
	}

	if (!GLSL_EndLoadGPUShader(&tr.volumeLightCombineShader))
	{
		ri->Error(ERR_FATAL, "Could not load volumelightCombine shader!");
	}
	
	GLSL_InitUniforms(&tr.volumeLightCombineShader);
	qglUseProgram(tr.volumeLightCombineShader.program);
	GLSL_SetUniformInt(&tr.volumeLightCombineShader, UNIFORM_DIFFUSEMAP, TB_DIFFUSEMAP);
	GLSL_SetUniformInt(&tr.volumeLightCombineShader, UNIFORM_NORMALMAP, TB_NORMALMAP);
	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.volumeLightCombineShader);
#endif
	
	numEtcShaders++;



	if (!GLSL_EndLoadGPUShader(&tr.bloomBlurShader))
	{
		ri->Error(ERR_FATAL, "Could not load bloom_blur shader!");
	}
	
	GLSL_InitUniforms(&tr.bloomBlurShader);
	qglUseProgram(tr.bloomBlurShader.program);
	GLSL_SetUniformInt(&tr.bloomBlurShader, UNIFORM_DIFFUSEMAP, TB_DIFFUSEMAP);
	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.bloomBlurShader);
#endif
	
	numEtcShaders++;

	if (!GLSL_EndLoadGPUShader(&tr.bloomCombineShader))
	{
		ri->Error(ERR_FATAL, "Could not load bloom_combine shader!");
	}
	
	GLSL_InitUniforms(&tr.bloomCombineShader);
	qglUseProgram(tr.bloomCombineShader.program);
	GLSL_SetUniformInt(&tr.bloomCombineShader, UNIFORM_DIFFUSEMAP, TB_DIFFUSEMAP);
	GLSL_SetUniformInt(&tr.bloomCombineShader, UNIFORM_NORMALMAP,  TB_NORMALMAP);
	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.bloomCombineShader);
#endif
	
	numEtcShaders++;


	if (!GLSL_EndLoadGPUShader(&tr.lensflareShader))
	{
		ri->Error(ERR_FATAL, "Could not load lensflare shader!");
	}
	
	GLSL_InitUniforms(&tr.lensflareShader);
	qglUseProgram(tr.lensflareShader.program);
	GLSL_SetUniformInt(&tr.lensflareShader, UNIFORM_DIFFUSEMAP, TB_DIFFUSEMAP);
	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.lensflareShader);
#endif
	
	numEtcShaders++;



	if (!GLSL_EndLoadGPUShader(&tr.anamorphicBlurShader))
	{
		ri->Error(ERR_FATAL, "Could not load anamorphic_blur shader!");
	}
	
	GLSL_InitUniforms(&tr.anamorphicBlurShader);
	qglUseProgram(tr.anamorphicBlurShader.program);
	GLSL_SetUniformInt(&tr.anamorphicBlurShader, UNIFORM_DIFFUSEMAP, TB_DIFFUSEMAP);
	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.anamorphicBlurShader);
#endif
	
	numEtcShaders++;

	if (!GLSL_EndLoadGPUShader(&tr.anamorphicCombineShader))
	{
		ri->Error(ERR_FATAL, "Could not load anamorphic_combine shader!");
	}
	
	GLSL_InitUniforms(&tr.anamorphicCombineShader);
	qglUseProgram(tr.anamorphicCombineShader.program);
	GLSL_SetUniformInt(&tr.anamorphicCombineShader, UNIFORM_DIFFUSEMAP, TB_DIFFUSEMAP);
	GLSL_SetUniformInt(&tr.anamorphicCombineShader, UNIFORM_NORMALMAP,  TB_NORMALMAP);
	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.anamorphicCombineShader);
#endif
	
	numEtcShaders++;


	if (!GLSL_EndLoadGPUShader(&tr.ssgi1Shader))
	{
		ri->Error(ERR_FATAL, "Could not load ssgi1 shader!");
	}
	
	GLSL_InitUniforms(&tr.ssgi1Shader);

	qglUseProgram(tr.ssgi1Shader.program);

	GLSL_SetUniformInt(&tr.ssgi1Shader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);
	
	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.ssgi1Shader, UNIFORM_DIMENSIONS, screensize);
	}

	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.ssgi1Shader, UNIFORM_VIEWINFO, viewInfo);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.ssgi1Shader);
#endif
	
	numEtcShaders++;

	if (!GLSL_EndLoadGPUShader(&tr.ssgi2Shader))
	{
		ri->Error(ERR_FATAL, "Could not load ssgi2 shader!");
	}
	
	GLSL_InitUniforms(&tr.ssgi2Shader);

	qglUseProgram(tr.ssgi2Shader.program);

	GLSL_SetUniformInt(&tr.ssgi2Shader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);
	
	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.ssgi2Shader, UNIFORM_DIMENSIONS, screensize);
	}

	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.ssgi2Shader, UNIFORM_VIEWINFO, viewInfo);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.ssgi2Shader);
#endif
	
	numEtcShaders++;

	if (!GLSL_EndLoadGPUShader(&tr.ssgi3Shader))
	{
		ri->Error(ERR_FATAL, "Could not load ssgi3 shader!");
	}
	
	GLSL_InitUniforms(&tr.ssgi3Shader);

	qglUseProgram(tr.ssgi3Shader.program);

	GLSL_SetUniformInt(&tr.ssgi3Shader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);
	
	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.ssgi3Shader, UNIFORM_DIMENSIONS, screensize);
	}

	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.ssgi3Shader, UNIFORM_VIEWINFO, viewInfo);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.ssgi3Shader);
#endif
	
	numEtcShaders++;

	if (!GLSL_EndLoadGPUShader(&tr.ssgi4Shader))
	{
		ri->Error(ERR_FATAL, "Could not load ssgi4 shader!");
	}
	
	GLSL_InitUniforms(&tr.ssgi4Shader);

	qglUseProgram(tr.ssgi4Shader.program);

	GLSL_SetUniformInt(&tr.ssgi4Shader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);
	
	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.ssgi4Shader, UNIFORM_DIMENSIONS, screensize);
	}

	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.ssgi4Shader, UNIFORM_VIEWINFO, viewInfo);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.ssgi4Shader);
#endif
	
	numEtcShaders++;

	if (!GLSL_EndLoadGPUShader(&tr.ssgi5Shader))
	{
		ri->Error(ERR_FATAL, "Could not load ssgi4 shader!");
	}
	
	GLSL_InitUniforms(&tr.ssgi5Shader);

	qglUseProgram(tr.ssgi5Shader.program);

	GLSL_SetUniformInt(&tr.ssgi5Shader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);
	
	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.ssgi5Shader, UNIFORM_DIMENSIONS, screensize);
	}

	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.ssgi5Shader, UNIFORM_VIEWINFO, viewInfo);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.ssgi5Shader);
#endif
	
	numEtcShaders++;

	if (!GLSL_EndLoadGPUShader(&tr.ssgi6Shader))
	{
		ri->Error(ERR_FATAL, "Could not load ssgi4 shader!");
	}
	
	GLSL_InitUniforms(&tr.ssgi6Shader);

	qglUseProgram(tr.ssgi6Shader.program);

	GLSL_SetUniformInt(&tr.ssgi6Shader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);
	
	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.ssgi6Shader, UNIFORM_DIMENSIONS, screensize);
	}

	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.ssgi6Shader, UNIFORM_VIEWINFO, viewInfo);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.ssgi6Shader);
#endif
	
	numEtcShaders++;

	if (!GLSL_EndLoadGPUShader(&tr.ssgi7Shader))
	{
		ri->Error(ERR_FATAL, "Could not load ssgi4 shader!");
	}
	
	GLSL_InitUniforms(&tr.ssgi7Shader);

	qglUseProgram(tr.ssgi7Shader.program);

	GLSL_SetUniformInt(&tr.ssgi7Shader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);
	
	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.ssgi7Shader, UNIFORM_DIMENSIONS, screensize);
	}

	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.ssgi7Shader, UNIFORM_VIEWINFO, viewInfo);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.ssgi7Shader);
#endif
	
	numEtcShaders++;

	if (!GLSL_EndLoadGPUShader(&tr.ssgiBlurShader))
	{
		ri->Error(ERR_FATAL, "Could not load ssgi_blur shader!");
	}
	
	GLSL_InitUniforms(&tr.ssgiBlurShader);
	qglUseProgram(tr.ssgiBlurShader.program);
	GLSL_SetUniformInt(&tr.ssgiBlurShader, UNIFORM_DIFFUSEMAP, TB_DIFFUSEMAP);
	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.ssgiBlurShader);
#endif
	
	numEtcShaders++;


	if (!GLSL_EndLoadGPUShader(&tr.hdrShader))
	{
		ri->Error(ERR_FATAL, "Could not load hdr shader!");
	}
	
	GLSL_InitUniforms(&tr.hdrShader);

	qglUseProgram(tr.hdrShader.program);

	GLSL_SetUniformInt(&tr.hdrShader, UNIFORM_TEXTUREMAP, TB_COLORMAP);
	GLSL_SetUniformInt(&tr.hdrShader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);
	
	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.hdrShader, UNIFORM_VIEWINFO, viewInfo);
	}

	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.hdrShader, UNIFORM_DIMENSIONS, screensize);

		//ri->Printf(PRINT_WARNING, "Sent dimensions %f %f.\n", screensize[0], screensize[1]);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.hdrShader);
#endif
	
	numEtcShaders++;


	if (!GLSL_EndLoadGPUShader(&tr.magicdetailShader))
	{
		ri->Error(ERR_FATAL, "Could not load magicdetail shader!");
	}
	
	GLSL_InitUniforms(&tr.magicdetailShader);

	qglUseProgram(tr.magicdetailShader.program);

	GLSL_SetUniformInt(&tr.magicdetailShader, UNIFORM_TEXTUREMAP, TB_COLORMAP);
	GLSL_SetUniformInt(&tr.magicdetailShader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);
	
	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.magicdetailShader, UNIFORM_VIEWINFO, viewInfo);
	}

	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.magicdetailShader, UNIFORM_DIMENSIONS, screensize);

		//ri->Printf(PRINT_WARNING, "Sent dimensions %f %f.\n", screensize[0], screensize[1]);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.magicdetailShader);
#endif
	
	numEtcShaders++;



	if (!GLSL_EndLoadGPUShader(&tr.waterPostShader))
	{
		ri->Error(ERR_FATAL, "Could not load waterPost shader!");
	}
	
	GLSL_InitUniforms(&tr.waterPostShader);

	qglUseProgram(tr.waterPostShader.program);

	GLSL_SetUniformInt(&tr.waterPostShader, UNIFORM_DIFFUSEMAP, TB_DIFFUSEMAP);
	GLSL_SetUniformInt(&tr.waterPostShader, UNIFORM_SCREENDEPTHMAP, TB_LIGHTMAP);
	GLSL_SetUniformInt(&tr.waterPostShader, UNIFORM_NORMALMAP, TB_NORMALMAP);
	
	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.waterPostShader, UNIFORM_VIEWINFO, viewInfo);
	}

	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.waterPostShader, UNIFORM_DIMENSIONS, screensize);

		//ri->Printf(PRINT_WARNING, "Sent dimensions %f %f.\n", screensize[0], screensize[1]);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.waterPostShader);
#endif
	
	numEtcShaders++;


	if (!GLSL_EndLoadGPUShader(&tr.dofShader))
	{
		ri->Error(ERR_FATAL, "Could not load depthOfField shader!");
	}
	
	GLSL_InitUniforms(&tr.dofShader);

	qglUseProgram(tr.dofShader.program);

	GLSL_SetUniformInt(&tr.dofShader, UNIFORM_TEXTUREMAP, TB_COLORMAP);
	GLSL_SetUniformInt(&tr.dofShader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);
	
	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.dofShader, UNIFORM_VIEWINFO, viewInfo);
	}

	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.dofShader, UNIFORM_DIMENSIONS, screensize);

		//ri->Printf(PRINT_WARNING, "Sent dimensions %f %f.\n", screensize[0], screensize[1]);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.dofShader);
#endif
	
	numEtcShaders++;

	if (!GLSL_EndLoadGPUShader(&tr.dof2Shader))
	{
		ri->Error(ERR_FATAL, "Could not load depthOfField2 shader!");
	}
	
	GLSL_InitUniforms(&tr.dof2Shader);

	qglUseProgram(tr.dof2Shader.program);

	GLSL_SetUniformInt(&tr.dof2Shader, UNIFORM_TEXTUREMAP, TB_COLORMAP);
	GLSL_SetUniformInt(&tr.dof2Shader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);
	
	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.dof2Shader, UNIFORM_VIEWINFO, viewInfo);
	}

	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.dof2Shader, UNIFORM_DIMENSIONS, screensize);

		//ri->Printf(PRINT_WARNING, "Sent dimensions %f %f.\n", screensize[0], screensize[1]);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.dof2Shader);
#endif
	
	numEtcShaders++;

	if (!GLSL_EndLoadGPUShader(&tr.vibrancyShader))
	{
		ri->Error(ERR_FATAL, "Could not load vibrancy shader!");
	}
	
	GLSL_InitUniforms(&tr.vibrancyShader);

	qglUseProgram(tr.vibrancyShader.program);

	GLSL_SetUniformInt(&tr.vibrancyShader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);
	
	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.vibrancyShader, UNIFORM_DIMENSIONS, screensize);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.vibrancyShader);
#endif
	
	numEtcShaders++;

	if (!GLSL_EndLoadGPUShader(&tr.testshaderShader))
	{
		ri->Error(ERR_FATAL, "Could not load testshader shader!");
	}
	
	GLSL_InitUniforms(&tr.testshaderShader);

	qglUseProgram(tr.testshaderShader.program);

	GLSL_SetUniformInt(&tr.testshaderShader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);
	
	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.testshaderShader, UNIFORM_DIMENSIONS, screensize);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.testshaderShader);
#endif
	
	numEtcShaders++;


	if (!GLSL_EndLoadGPUShader(&tr.fastBlurShader))
	{
		ri->Error(ERR_FATAL, "Could not load fastBlur shader!");
	}
	
	GLSL_InitUniforms(&tr.fastBlurShader);

	qglUseProgram(tr.fastBlurShader.program);

	GLSL_SetUniformInt(&tr.fastBlurShader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);
	
	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.fastBlurShader, UNIFORM_DIMENSIONS, screensize);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.fastBlurShader);
#endif
	
	numEtcShaders++;


	if (!GLSL_EndLoadGPUShader(&tr.distanceBlurShader))
	{
		ri->Error(ERR_FATAL, "Could not load distanceBlur shader!");
	}
	
	GLSL_InitUniforms(&tr.distanceBlurShader);

	qglUseProgram(tr.distanceBlurShader.program);

	GLSL_SetUniformInt(&tr.distanceBlurShader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);
	
	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.distanceBlurShader, UNIFORM_DIMENSIONS, screensize);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.distanceBlurShader);
#endif
	
	numEtcShaders++;


	//esharpeningShader
	if (!GLSL_EndLoadGPUShader(&tr.esharpeningShader))
	{
		ri->Error(ERR_FATAL, "Could not load esharpening shader!");
	}
	
	GLSL_InitUniforms(&tr.esharpeningShader);

	qglUseProgram(tr.esharpeningShader.program);

	GLSL_SetUniformInt(&tr.esharpeningShader, UNIFORM_TEXTUREMAP, TB_COLORMAP);
	GLSL_SetUniformInt(&tr.esharpeningShader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);
	
	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.esharpeningShader, UNIFORM_VIEWINFO, viewInfo);
	}

	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.esharpeningShader, UNIFORM_DIMENSIONS, screensize);

		//ri->Printf(PRINT_WARNING, "Sent dimensions %f %f.\n", screensize[0], screensize[1]);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.esharpeningShader);
#endif
	
	numEtcShaders++;


	//esharpeningShader
	if (!GLSL_EndLoadGPUShader(&tr.esharpening2Shader))
	{
		ri->Error(ERR_FATAL, "Could not load esharpening2 shader!");
	}
	
	GLSL_InitUniforms(&tr.esharpening2Shader);

	qglUseProgram(tr.esharpening2Shader.program);

	GLSL_SetUniformInt(&tr.esharpening2Shader, UNIFORM_TEXTUREMAP, TB_COLORMAP);
	GLSL_SetUniformInt(&tr.esharpening2Shader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);
	
	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.esharpening2Shader, UNIFORM_VIEWINFO, viewInfo);
	}

	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.esharpening2Shader, UNIFORM_DIMENSIONS, screensize);

		//ri->Printf(PRINT_WARNING, "Sent dimensions %f %f.\n", screensize[0], screensize[1]);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.esharpening2Shader);
#endif
	
	numEtcShaders++;


	//fxaaShader
	if (!GLSL_EndLoadGPUShader(&tr.fxaaShader))
	{
		ri->Error(ERR_FATAL, "Could not load fxaa shader!");
	}
	
	GLSL_InitUniforms(&tr.fxaaShader);

	qglUseProgram(tr.fxaaShader.program);

	GLSL_SetUniformInt(&tr.fxaaShader, UNIFORM_TEXTUREMAP, TB_COLORMAP);
	GLSL_SetUniformInt(&tr.fxaaShader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);
	
	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.fxaaShader, UNIFORM_VIEWINFO, viewInfo);
	}

	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.fxaaShader, UNIFORM_DIMENSIONS, screensize);

		//ri->Printf(PRINT_WARNING, "Sent dimensions %f %f.\n", screensize[0], screensize[1]);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.fxaaShader);
#endif
	
	numEtcShaders++;

	//generateNormalMap
	if (!GLSL_EndLoadGPUShader(&tr.generateNormalMapShader))
	{
		ri->Error(ERR_FATAL, "Could not load generateNormalMap shader!");
	}
	
	GLSL_InitUniforms(&tr.generateNormalMapShader);

	qglUseProgram(tr.generateNormalMapShader.program);

	GLSL_SetUniformInt(&tr.generateNormalMapShader, UNIFORM_TEXTUREMAP, TB_COLORMAP);
	GLSL_SetUniformInt(&tr.generateNormalMapShader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);
	
	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.generateNormalMapShader, UNIFORM_VIEWINFO, viewInfo);
	}

	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.generateNormalMapShader, UNIFORM_DIMENSIONS, screensize);

		//ri->Printf(PRINT_WARNING, "Sent dimensions %f %f.\n", screensize[0], screensize[1]);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.generateNormalMapShader);
#endif
	
	numEtcShaders++;

	//underwaterShader
	if (!GLSL_EndLoadGPUShader(&tr.underwaterShader))
	{
		ri->Error(ERR_FATAL, "Could not load underwater shader!");
	}
	
	GLSL_InitUniforms(&tr.underwaterShader);

	qglUseProgram(tr.underwaterShader.program);

	GLSL_SetUniformInt(&tr.underwaterShader, UNIFORM_TEXTUREMAP, TB_COLORMAP);
	
	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.underwaterShader, UNIFORM_VIEWINFO, viewInfo);
	}

	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.underwaterShader, UNIFORM_DIMENSIONS, screensize);

		//ri->Printf(PRINT_WARNING, "Sent dimensions %f %f.\n", screensize[0], screensize[1]);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.underwaterShader);
#endif
	
	numEtcShaders++;


	if (!GLSL_EndLoadGPUShader(&tr.texturecleanShader))
	{
		ri->Error(ERR_FATAL, "Could not load textureclean shader!");
	}
	
	GLSL_InitUniforms(&tr.texturecleanShader);

	qglUseProgram(tr.texturecleanShader.program);

	GLSL_SetUniformInt(&tr.texturecleanShader, UNIFORM_TEXTUREMAP, TB_COLORMAP);
	GLSL_SetUniformInt(&tr.texturecleanShader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);
	
	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.texturecleanShader, UNIFORM_VIEWINFO, viewInfo);
	}

	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.texturecleanShader, UNIFORM_DIMENSIONS, screensize);

		//ri->Printf(PRINT_WARNING, "Sent dimensions %f %f.\n", screensize[0], screensize[1]);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.texturecleanShader);
#endif
	
	numEtcShaders++;



	if (!GLSL_EndLoadGPUShader(&tr.fakedepthShader))
	{
		ri->Error(ERR_FATAL, "Could not load fake depth shader!");
	}
	
	GLSL_InitUniforms(&tr.fakedepthShader);

	qglUseProgram(tr.fakedepthShader.program);

	GLSL_SetUniformInt(&tr.fakedepthShader, UNIFORM_TEXTUREMAP, TB_COLORMAP);
	GLSL_SetUniformInt(&tr.fakedepthShader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);

	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.fakedepthShader, UNIFORM_VIEWINFO, viewInfo);
	}

	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.fakedepthShader, UNIFORM_DIMENSIONS, screensize);

		//ri->Printf(PRINT_WARNING, "Sent dimensions %f %f.\n", screensize[0], screensize[1]);
	}

	{
		vec4_t local0;
		VectorSet4(local0, r_depthScale->value, r_depthParallax->value, 0.0, 0.0);
		GLSL_SetUniformVec4(&tr.fakedepthShader, UNIFORM_LOCAL0, local0);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.fakedepthShader);
#endif
	
	numEtcShaders++;

	
	if (!GLSL_EndLoadGPUShader(&tr.fakedepthSteepParallaxShader))
	{
		ri->Error(ERR_FATAL, "Could not load fake depth steep parallax shader!");
	}
	
	GLSL_InitUniforms(&tr.fakedepthSteepParallaxShader);

	qglUseProgram(tr.fakedepthSteepParallaxShader.program);

	GLSL_SetUniformInt(&tr.fakedepthSteepParallaxShader, UNIFORM_TEXTUREMAP, TB_COLORMAP);
	GLSL_SetUniformInt(&tr.fakedepthSteepParallaxShader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);

	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.fakedepthSteepParallaxShader, UNIFORM_VIEWINFO, viewInfo);
	}

	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.fakedepthSteepParallaxShader, UNIFORM_DIMENSIONS, screensize);

		//ri->Printf(PRINT_WARNING, "Sent dimensions %f %f.\n", screensize[0], screensize[1]);
	}

	{
		vec4_t local0;
		VectorSet4(local0, r_depthScale->value, r_depthParallax->value, 0.0, 0.0);
		GLSL_SetUniformVec4(&tr.fakedepthSteepParallaxShader, UNIFORM_LOCAL0, local0);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.fakedepthSteepParallaxShader);
#endif
	
	numEtcShaders++;



	if (!GLSL_EndLoadGPUShader(&tr.anaglyphShader))
	{
		ri->Error(ERR_FATAL, "Could not load anaglyph shader!");
	}
	
	GLSL_InitUniforms(&tr.anaglyphShader);

	qglUseProgram(tr.anaglyphShader.program);

	GLSL_SetUniformInt(&tr.anaglyphShader, UNIFORM_TEXTUREMAP, TB_COLORMAP);
	GLSL_SetUniformInt(&tr.anaglyphShader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);

	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.anaglyphShader, UNIFORM_VIEWINFO, viewInfo);
	}

	{
		vec2_t screensize;
		screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
		screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

		GLSL_SetUniformVec2(&tr.anaglyphShader, UNIFORM_DIMENSIONS, screensize);

		//ri->Printf(PRINT_WARNING, "Sent dimensions %f %f.\n", screensize[0], screensize[1]);
	}

	{
		vec4_t local0;
		VectorSet4(local0, r_trueAnaglyphSeparation->value, r_trueAnaglyphRed->value, r_trueAnaglyphGreen->value, r_trueAnaglyphBlue->value);
		GLSL_SetUniformVec4(&tr.anaglyphShader, UNIFORM_LOCAL0, local0);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.anaglyphShader);
#endif
	
	numEtcShaders++;


	
	if (!GLSL_EndLoadGPUShader(&tr.uniqueskyShader))
	{
		ri->Error(ERR_FATAL, "Could not load uniqueskyShader shader!");
	}
	
	GLSL_InitUniforms(&tr.uniqueskyShader);

	qglUseProgram(tr.uniqueskyShader.program);

	GLSL_SetUniformInt(&tr.uniqueskyShader, UNIFORM_TEXTUREMAP, TB_COLORMAP);
	GLSL_SetUniformInt(&tr.uniqueskyShader, UNIFORM_LEVELSMAP,  TB_LEVELSMAP);

	{
		vec4_t viewInfo;

		float zmax = backEnd.viewParms.zFar;
		float zmin = r_znear->value;

		VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
		//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

		GLSL_SetUniformVec4(&tr.uniqueskyShader, UNIFORM_VIEWINFO, viewInfo);
	}

	qglUseProgram(0);

#if defined(_DEBUG)
	GLSL_FinishGPUShader(&tr.uniqueskyShader);
#endif
	
	numEtcShaders++;
	
	
		
		if (!GLSL_EndLoadGPUShader(&tr.waterShader))
		{
			ri->Error(ERR_FATAL, "Could not load water shader!");
		}
		
		GLSL_InitUniforms(&tr.waterShader);

		qglUseProgram(tr.waterShader.program);

		GLSL_SetUniformInt(&tr.waterShader, UNIFORM_DIFFUSEMAP,  TB_DIFFUSEMAP);
		GLSL_SetUniformInt(&tr.waterShader, UNIFORM_LIGHTMAP,    TB_LIGHTMAP);
		GLSL_SetUniformInt(&tr.waterShader, UNIFORM_NORMALMAP,   TB_NORMALMAP);
		GLSL_SetUniformInt(&tr.waterShader, UNIFORM_DELUXEMAP,   TB_DELUXEMAP);
		GLSL_SetUniformInt(&tr.waterShader, UNIFORM_SPECULARMAP, TB_SPECULARMAP);
		GLSL_SetUniformInt(&tr.waterShader, UNIFORM_SHADOWMAP,   TB_SHADOWMAP);
		GLSL_SetUniformInt(&tr.waterShader, UNIFORM_CUBEMAP,     TB_CUBEMAP);
		//GLSL_SetUniformInt(&tr.waterShader, UNIFORM_SUBSURFACEMAP, TB_SUBSURFACEMAP);

		{
			vec4_t viewInfo;

			float zmax = backEnd.viewParms.zFar;
			float zmin = r_znear->value;

			VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
			//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

			GLSL_SetUniformVec4(&tr.waterShader, UNIFORM_VIEWINFO, viewInfo);
		}

		{
			vec2_t screensize;
			screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
			screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

			GLSL_SetUniformVec2(&tr.waterShader, UNIFORM_DIMENSIONS, screensize);

			//ri->Printf(PRINT_WARNING, "Sent dimensions %f %f.\n", screensize[0], screensize[1]);
		}

		qglUseProgram(0);

#if defined(_DEBUG)
		GLSL_FinishGPUShader(&tr.waterShader);
#endif
		
		numEtcShaders++;





		
		
		if (!GLSL_EndLoadGPUShader(&tr.grassShader))
		{
			ri->Error(ERR_FATAL, "Could not load grass shader!");
		}
		
		GLSL_InitUniforms(&tr.grassShader);

		qglUseProgram(tr.grassShader.program);

		GLSL_SetUniformInt(&tr.grassShader, UNIFORM_DIFFUSEMAP,  TB_DIFFUSEMAP);
		GLSL_SetUniformInt(&tr.grassShader, UNIFORM_LIGHTMAP,    TB_LIGHTMAP);
		GLSL_SetUniformInt(&tr.grassShader, UNIFORM_NORMALMAP,   TB_NORMALMAP);
		GLSL_SetUniformInt(&tr.grassShader, UNIFORM_DELUXEMAP,   TB_DELUXEMAP);
		GLSL_SetUniformInt(&tr.grassShader, UNIFORM_SPECULARMAP, TB_SPECULARMAP);
		GLSL_SetUniformInt(&tr.grassShader, UNIFORM_SHADOWMAP,   TB_SHADOWMAP);
		GLSL_SetUniformInt(&tr.grassShader, UNIFORM_CUBEMAP,     TB_CUBEMAP);
		//GLSL_SetUniformInt(&tr.grassShader, UNIFORM_SUBSURFACEMAP, TB_SUBSURFACEMAP);

		{
			vec4_t viewInfo;

			float zmax = backEnd.viewParms.zFar;
			float zmin = r_znear->value;

			VectorSet4(viewInfo, zmax / zmin, zmax, 0.0, 0.0);
			//VectorSet4(viewInfo, zmin, zmax, 0.0, 0.0);

			GLSL_SetUniformVec4(&tr.grassShader, UNIFORM_VIEWINFO, viewInfo);
		}

		{
			vec2_t screensize;
			screensize[0] = glConfig.vidWidth * r_superSampleMultiplier->value;
			screensize[1] = glConfig.vidHeight * r_superSampleMultiplier->value;

			GLSL_SetUniformVec2(&tr.grassShader, UNIFORM_DIMENSIONS, screensize);

			//ri->Printf(PRINT_WARNING, "Sent dimensions %f %f.\n", screensize[0], screensize[1]);
		}

		qglUseProgram(0);

#if defined(_DEBUG)
		GLSL_FinishGPUShader(&tr.grassShader);
#endif
		
		numEtcShaders++;





		if (!GLSL_EndLoadGPUShader(&tr.sssShader))
		{
			ri->Error(ERR_FATAL, "Could not load sss shader!");
		}

		GLSL_InitUniforms(&tr.sssShader);

		qglUseProgram(tr.sssShader.program);
		GLSL_SetUniformInt(&tr.sssShader, UNIFORM_DIFFUSEMAP, TB_DIFFUSEMAP);
		GLSL_SetUniformInt(&tr.sssShader, UNIFORM_SCREENDEPTHMAP, TB_LIGHTMAP);
		GLSL_SetUniformInt(&tr.sssShader, UNIFORM_NORMALMAP, TB_NORMALMAP);
		GLSL_SetUniformInt(&tr.sssShader, UNIFORM_SPECULARMAP, TB_SPECULARMAP);
		qglUseProgram(0);

#if defined(_DEBUG)
		GLSL_FinishGPUShader(&tr.sssShader);
#endif

		numEtcShaders++;




		if (!GLSL_EndLoadGPUShader(&tr.sss2Shader))
		{
			ri->Error(ERR_FATAL, "Could not load sss2 shader!");
		}

		GLSL_InitUniforms(&tr.sss2Shader);

		qglUseProgram(tr.sss2Shader.program);
		GLSL_SetUniformInt(&tr.sss2Shader, UNIFORM_DIFFUSEMAP, TB_DIFFUSEMAP);
		GLSL_SetUniformInt(&tr.sss2Shader, UNIFORM_SCREENDEPTHMAP, TB_LIGHTMAP);
		GLSL_SetUniformInt(&tr.sss2Shader, UNIFORM_NORMALMAP, TB_NORMALMAP);
		qglUseProgram(0);

#if defined(_DEBUG)
		GLSL_FinishGPUShader(&tr.sss2Shader);
#endif

		numEtcShaders++;





		if (!GLSL_EndLoadGPUShader(&tr.rbmShader))
		{
			ri->Error(ERR_FATAL, "Could not load rbm shader!");
		}

		GLSL_InitUniforms(&tr.rbmShader);

		qglUseProgram(tr.rbmShader.program);
		GLSL_SetUniformInt(&tr.rbmShader, UNIFORM_SCREENDEPTHMAP, TB_LIGHTMAP);
		GLSL_SetUniformInt(&tr.rbmShader, UNIFORM_NORMALMAP, TB_NORMALMAP);
		GLSL_SetUniformInt(&tr.rbmShader, UNIFORM_DIFFUSEMAP, TB_DIFFUSEMAP);
		qglUseProgram(0);

#if defined(_DEBUG)
		GLSL_FinishGPUShader(&tr.rbmShader);
#endif

		numEtcShaders++;


		if (!GLSL_EndLoadGPUShader(&tr.hbaoShader))
		{
			ri->Error(ERR_FATAL, "Could not load hbao shader!");
		}

		GLSL_InitUniforms(&tr.hbaoShader);

		qglUseProgram(tr.hbaoShader.program);
		GLSL_SetUniformInt(&tr.hbaoShader, UNIFORM_SCREENDEPTHMAP, TB_LIGHTMAP);
		GLSL_SetUniformInt(&tr.hbaoShader, UNIFORM_DIFFUSEMAP, TB_DIFFUSEMAP);
		GLSL_SetUniformInt(&tr.hbaoShader, UNIFORM_NORMALMAP, TB_NORMALMAP);
		qglUseProgram(0);

#if defined(_DEBUG)
		GLSL_FinishGPUShader(&tr.hbaoShader);
#endif

		numEtcShaders++;

		if (!GLSL_EndLoadGPUShader(&tr.hbao2Shader))
		{
			ri->Error(ERR_FATAL, "Could not load hbao2 shader!");
		}

		GLSL_InitUniforms(&tr.hbao2Shader);

		qglUseProgram(tr.hbao2Shader.program);
		GLSL_SetUniformInt(&tr.hbao2Shader, UNIFORM_SCREENDEPTHMAP, TB_LIGHTMAP);
		GLSL_SetUniformInt(&tr.hbao2Shader, UNIFORM_DIFFUSEMAP, TB_DIFFUSEMAP);
		GLSL_SetUniformInt(&tr.hbao2Shader, UNIFORM_NORMALMAP, TB_NORMALMAP);
		qglUseProgram(0);

#if defined(_DEBUG)
		GLSL_FinishGPUShader(&tr.hbao2Shader);
#endif

		numEtcShaders++;

		if (!GLSL_EndLoadGPUShader(&tr.hbaoCombineShader))
		{
			ri->Error(ERR_FATAL, "Could not load hbaoCombine shader!");
		}

		GLSL_InitUniforms(&tr.hbaoCombineShader);

		qglUseProgram(tr.hbaoCombineShader.program);
		GLSL_SetUniformInt(&tr.hbaoCombineShader, UNIFORM_DIFFUSEMAP, TB_DIFFUSEMAP);
		GLSL_SetUniformInt(&tr.hbaoCombineShader, UNIFORM_NORMALMAP, TB_NORMALMAP);
		qglUseProgram(0);

#if defined(_DEBUG)
		GLSL_FinishGPUShader(&tr.hbaoCombineShader);
#endif

		numEtcShaders++;

	//
	// UQ1: End Added...
	//



	ri->Printf(PRINT_ALL, "loaded %i GLSL shaders (%i gen %i light %i etc) in %5.2f seconds\n", 
		numGenShaders + numLightShaders + numEtcShaders, numGenShaders, numLightShaders, 
		numEtcShaders, (ri->Milliseconds() - startTime) / 1000.0);
}

void GLSL_ShutdownGPUShaders(void)
{
	int i;

	ri->Printf(PRINT_ALL, "------- GLSL_ShutdownGPUShaders -------\n");

	qglDisableVertexAttribArray(ATTR_INDEX_TEXCOORD0);
	qglDisableVertexAttribArray(ATTR_INDEX_TEXCOORD1);
	qglDisableVertexAttribArray(ATTR_INDEX_POSITION);
	qglDisableVertexAttribArray(ATTR_INDEX_POSITION2);
	qglDisableVertexAttribArray(ATTR_INDEX_NORMAL);
	qglDisableVertexAttribArray(ATTR_INDEX_TANGENT);
	qglDisableVertexAttribArray(ATTR_INDEX_NORMAL2);
	qglDisableVertexAttribArray(ATTR_INDEX_TANGENT2);
	qglDisableVertexAttribArray(ATTR_INDEX_COLOR);
	qglDisableVertexAttribArray(ATTR_INDEX_LIGHTDIRECTION);
	qglDisableVertexAttribArray(ATTR_INDEX_BONE_INDEXES);
	qglDisableVertexAttribArray(ATTR_INDEX_BONE_WEIGHTS);
	GLSL_BindNullProgram();

	for ( i = 0; i < GENERICDEF_COUNT; i++)
		GLSL_DeleteGPUShader(&tr.genericShader[i]);

	GLSL_DeleteGPUShader(&tr.textureColorShader);

	for ( i = 0; i < FOGDEF_COUNT; i++)
		GLSL_DeleteGPUShader(&tr.fogShader[i]);

	for ( i = 0; i < LIGHTDEF_COUNT; i++)
		GLSL_DeleteGPUShader(&tr.lightallShader[i]);

	GLSL_DeleteGPUShader(&tr.shadowmapShader);
	GLSL_DeleteGPUShader(&tr.pshadowShader);
	GLSL_DeleteGPUShader(&tr.down4xShader);
	GLSL_DeleteGPUShader(&tr.bokehShader);
	GLSL_DeleteGPUShader(&tr.tonemapShader);

	for ( i = 0; i < 2; i++)
		GLSL_DeleteGPUShader(&tr.calclevels4xShader[i]);

	GLSL_DeleteGPUShader(&tr.shadowmaskShader);
	GLSL_DeleteGPUShader(&tr.ssaoShader);

	for ( i = 0; i < 2; i++)
		GLSL_DeleteGPUShader(&tr.depthBlurShader[i]);



	// UQ1: Added...
	GLSL_DeleteGPUShader(&tr.darkexpandShader);
	GLSL_DeleteGPUShader(&tr.hdrShader);
	GLSL_DeleteGPUShader(&tr.magicdetailShader);
	GLSL_DeleteGPUShader(&tr.esharpeningShader);
	GLSL_DeleteGPUShader(&tr.esharpening2Shader);
	GLSL_DeleteGPUShader(&tr.fakedepthShader);
	GLSL_DeleteGPUShader(&tr.fakedepthSteepParallaxShader);
	GLSL_DeleteGPUShader(&tr.anaglyphShader);
	GLSL_DeleteGPUShader(&tr.waterShader);
	GLSL_DeleteGPUShader(&tr.waterPostShader);
	GLSL_DeleteGPUShader(&tr.grassShader);
	if (r_foliage->integer)	GLSL_DeleteGPUShader(&tr.grass2Shader);
	GLSL_DeleteGPUShader(&tr.sssShader);
	GLSL_DeleteGPUShader(&tr.sss2Shader);
	GLSL_DeleteGPUShader(&tr.rbmShader);
	GLSL_DeleteGPUShader(&tr.hbaoShader);
	GLSL_DeleteGPUShader(&tr.hbao2Shader);
	GLSL_DeleteGPUShader(&tr.hbaoCombineShader);
	GLSL_DeleteGPUShader(&tr.bloomBlurShader);
	GLSL_DeleteGPUShader(&tr.bloomCombineShader);
	GLSL_DeleteGPUShader(&tr.lensflareShader);
	GLSL_DeleteGPUShader(&tr.multipostShader);
	GLSL_DeleteGPUShader(&tr.anamorphicBlurShader);
	GLSL_DeleteGPUShader(&tr.anamorphicCombineShader);
	GLSL_DeleteGPUShader(&tr.dofShader);
	GLSL_DeleteGPUShader(&tr.dof2Shader);
	GLSL_DeleteGPUShader(&tr.fxaaShader);
	GLSL_DeleteGPUShader(&tr.underwaterShader);
	GLSL_DeleteGPUShader(&tr.texturecleanShader);
	GLSL_DeleteGPUShader(&tr.ssgi1Shader);
	GLSL_DeleteGPUShader(&tr.ssgi2Shader);
	GLSL_DeleteGPUShader(&tr.ssgi3Shader);
	GLSL_DeleteGPUShader(&tr.ssgi4Shader);
	GLSL_DeleteGPUShader(&tr.ssgi5Shader);
	GLSL_DeleteGPUShader(&tr.ssgi6Shader);
	GLSL_DeleteGPUShader(&tr.ssgi7Shader);
	GLSL_DeleteGPUShader(&tr.volumeLightShader[0]);
	GLSL_DeleteGPUShader(&tr.volumeLightShader[1]);
	GLSL_DeleteGPUShader(&tr.volumeLightShader[2]);
	GLSL_DeleteGPUShader(&tr.volumeLightCombineShader);
	GLSL_DeleteGPUShader(&tr.vibrancyShader);
	GLSL_DeleteGPUShader(&tr.fastBlurShader);
	GLSL_DeleteGPUShader(&tr.distanceBlurShader);
	GLSL_DeleteGPUShader(&tr.testshaderShader);
	GLSL_DeleteGPUShader(&tr.uniqueskyShader);
	GLSL_DeleteGPUShader(&tr.generateNormalMapShader);


	glState.currentProgram = 0;
	qglUseProgram(0);
}


void GLSL_BindProgram(shaderProgram_t * program)
{
	if(!program)
	{
		GLSL_BindNullProgram();
		return;
	}

	if(r_logFile->integer)
	{
		// don't just call LogComment, or we will get a call to va() every frame!
		GLimp_LogComment(va("--- GL_BindProgram( %s ) ---\n", program->name));
	}

	if(glState.currentProgram != program)
	{
		qglUseProgram(program->program);
		glState.currentProgram = program;
		backEnd.pc.c_glslShaderBinds++;
	}
}


void GLSL_BindNullProgram(void)
{
	if(r_logFile->integer)
	{
		GLimp_LogComment("--- GL_BindNullProgram ---\n");
	}

	if(glState.currentProgram)
	{
		qglUseProgram(0);
		glState.currentProgram = NULL;
	}
}


void GLSL_VertexAttribsState(uint32_t stateBits)
{
	uint32_t		diff;

	GLSL_VertexAttribPointers(stateBits);

	diff = stateBits ^ glState.vertexAttribsState;
	if(!diff)
	{
		return;
	}

	if(diff & ATTR_POSITION)
	{
		if(stateBits & ATTR_POSITION)
		{
			GLimp_LogComment("qglEnableVertexAttribArray( ATTR_INDEX_POSITION )\n");
			qglEnableVertexAttribArray(ATTR_INDEX_POSITION);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArray( ATTR_INDEX_POSITION )\n");
			qglDisableVertexAttribArray(ATTR_INDEX_POSITION);
		}
	}

	if(diff & ATTR_TEXCOORD0)
	{
		if(stateBits & ATTR_TEXCOORD0)
		{
			GLimp_LogComment("qglEnableVertexAttribArray( ATTR_INDEX_TEXCOORD )\n");
			qglEnableVertexAttribArray(ATTR_INDEX_TEXCOORD0);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArray( ATTR_INDEX_TEXCOORD )\n");
			qglDisableVertexAttribArray(ATTR_INDEX_TEXCOORD0);
		}
	}

	if(diff & ATTR_TEXCOORD1)
	{
		if(stateBits & ATTR_TEXCOORD1)
		{
			GLimp_LogComment("qglEnableVertexAttribArray( ATTR_INDEX_LIGHTCOORD )\n");
			qglEnableVertexAttribArray(ATTR_INDEX_TEXCOORD1);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArray( ATTR_INDEX_LIGHTCOORD )\n");
			qglDisableVertexAttribArray(ATTR_INDEX_TEXCOORD1);
		}
	}

	if(diff & ATTR_NORMAL)
	{
		if(stateBits & ATTR_NORMAL)
		{
			GLimp_LogComment("qglEnableVertexAttribArray( ATTR_INDEX_NORMAL )\n");
			qglEnableVertexAttribArray(ATTR_INDEX_NORMAL);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArray( ATTR_INDEX_NORMAL )\n");
			qglDisableVertexAttribArray(ATTR_INDEX_NORMAL);
		}
	}

	if(diff & ATTR_TANGENT)
	{
		if(stateBits & ATTR_TANGENT)
		{
			GLimp_LogComment("qglEnableVertexAttribArray( ATTR_INDEX_TANGENT )\n");
			qglEnableVertexAttribArray(ATTR_INDEX_TANGENT);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArray( ATTR_INDEX_TANGENT )\n");
			qglDisableVertexAttribArray(ATTR_INDEX_TANGENT);
		}
	}

	if(diff & ATTR_COLOR)
	{
		if(stateBits & ATTR_COLOR)
		{
			GLimp_LogComment("qglEnableVertexAttribArray( ATTR_INDEX_COLOR )\n");
			qglEnableVertexAttribArray(ATTR_INDEX_COLOR);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArray( ATTR_INDEX_COLOR )\n");
			qglDisableVertexAttribArray(ATTR_INDEX_COLOR);
		}
	}

	if(diff & ATTR_LIGHTDIRECTION)
	{
		if(stateBits & ATTR_LIGHTDIRECTION)
		{
			GLimp_LogComment("qglEnableVertexAttribArray( ATTR_INDEX_LIGHTDIRECTION )\n");
			qglEnableVertexAttribArray(ATTR_INDEX_LIGHTDIRECTION);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArray( ATTR_INDEX_LIGHTDIRECTION )\n");
			qglDisableVertexAttribArray(ATTR_INDEX_LIGHTDIRECTION);
		}
	}

	if(diff & ATTR_POSITION2)
	{
		if(stateBits & ATTR_POSITION2)
		{
			GLimp_LogComment("qglEnableVertexAttribArray( ATTR_INDEX_POSITION2 )\n");
			qglEnableVertexAttribArray(ATTR_INDEX_POSITION2);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArray( ATTR_INDEX_POSITION2 )\n");
			qglDisableVertexAttribArray(ATTR_INDEX_POSITION2);
		}
	}

	if(diff & ATTR_NORMAL2)
	{
		if(stateBits & ATTR_NORMAL2)
		{
			GLimp_LogComment("qglEnableVertexAttribArray( ATTR_INDEX_NORMAL2 )\n");
			qglEnableVertexAttribArray(ATTR_INDEX_NORMAL2);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArray( ATTR_INDEX_NORMAL2 )\n");
			qglDisableVertexAttribArray(ATTR_INDEX_NORMAL2);
		}
	}

	if(diff & ATTR_TANGENT2)
	{
		if(stateBits & ATTR_TANGENT2)
		{
			GLimp_LogComment("qglEnableVertexAttribArray( ATTR_INDEX_TANGENT2 )\n");
			qglEnableVertexAttribArray(ATTR_INDEX_TANGENT2);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArray( ATTR_INDEX_TANGENT2 )\n");
			qglDisableVertexAttribArray(ATTR_INDEX_TANGENT2);
		}
	}

	if(diff & ATTR_BONE_INDEXES)
	{
		if(stateBits & ATTR_BONE_INDEXES)
		{
			GLimp_LogComment("qglEnableVertexAttribArray( ATTR_INDEX_BONE_INDEXES )\n");
			qglEnableVertexAttribArray(ATTR_INDEX_BONE_INDEXES);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArray( ATTR_INDEX_BONE_INDEXES )\n");
			qglDisableVertexAttribArray(ATTR_INDEX_BONE_INDEXES);
		}
	}

	if(diff & ATTR_BONE_WEIGHTS)
	{
		if(stateBits & ATTR_BONE_WEIGHTS)
		{
			GLimp_LogComment("qglEnableVertexAttribArray( ATTR_INDEX_BONE_WEIGHTS )\n");
			qglEnableVertexAttribArray(ATTR_INDEX_BONE_WEIGHTS);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArray( ATTR_INDEX_BONE_WEIGHTS )\n");
			qglDisableVertexAttribArray(ATTR_INDEX_BONE_WEIGHTS);
		}
	}

	glState.vertexAttribsState = stateBits;
}

void GLSL_UpdateTexCoordVertexAttribPointers ( uint32_t attribBits )
{
	VBO_t *vbo = glState.currentVBO;

	if ( attribBits & ATTR_TEXCOORD0 )
	{
		GLimp_LogComment("qglVertexAttribPointer( ATTR_INDEX_TEXCOORD )\n");

		qglVertexAttribPointer(ATTR_INDEX_TEXCOORD0, 2, GL_FLOAT, 0, vbo->stride_st, BUFFER_OFFSET(vbo->ofs_st + sizeof (vec2_t) * glState.vertexAttribsTexCoordOffset[0]));
	}

	if ( attribBits & ATTR_TEXCOORD1 )
	{
		GLimp_LogComment("qglVertexAttribPointer( ATTR_INDEX_LIGHTCOORD )\n");

		qglVertexAttribPointer(ATTR_INDEX_TEXCOORD1, 2, GL_FLOAT, 0, vbo->stride_st, BUFFER_OFFSET(vbo->ofs_st + sizeof (vec2_t) * glState.vertexAttribsTexCoordOffset[1]));
	}
}

void GLSL_VertexAttribPointers(uint32_t attribBits)
{
	qboolean animated;
	int newFrame, oldFrame;
	VBO_t *vbo = glState.currentVBO;
	
	if(!vbo)
	{
		ri->Error(ERR_FATAL, "GL_VertexAttribPointers: no VBO bound");
		return;
	}

	// don't just call LogComment, or we will get a call to va() every frame!
	if (r_logFile->integer)
	{
		GLimp_LogComment("--- GL_VertexAttribPointers() ---\n");
	}

	// position/normal/tangent are always set in case of animation
	oldFrame = glState.vertexAttribsOldFrame;
	newFrame = glState.vertexAttribsNewFrame;
	animated = glState.vertexAnimation;
	
	if((attribBits & ATTR_POSITION) && (!(glState.vertexAttribPointersSet & ATTR_POSITION) || animated))
	{
		GLimp_LogComment("qglVertexAttribPointer( ATTR_INDEX_POSITION )\n");

		qglVertexAttribPointer(ATTR_INDEX_POSITION, 3, GL_FLOAT, 0, vbo->stride_xyz, BUFFER_OFFSET(vbo->ofs_xyz + newFrame * vbo->size_xyz));
		glState.vertexAttribPointersSet |= ATTR_POSITION;
	}

	if((attribBits & ATTR_TEXCOORD0) && !(glState.vertexAttribPointersSet & ATTR_TEXCOORD0))
	{
		GLimp_LogComment("qglVertexAttribPointer( ATTR_INDEX_TEXCOORD )\n");

		qglVertexAttribPointer(ATTR_INDEX_TEXCOORD0, 2, GL_FLOAT, 0, vbo->stride_st, BUFFER_OFFSET(vbo->ofs_st + sizeof (vec2_t) * glState.vertexAttribsTexCoordOffset[0]));
		glState.vertexAttribPointersSet |= ATTR_TEXCOORD0;
	}

	if((attribBits & ATTR_TEXCOORD1) && !(glState.vertexAttribPointersSet & ATTR_TEXCOORD1))
	{
		GLimp_LogComment("qglVertexAttribPointer( ATTR_INDEX_LIGHTCOORD )\n");

		qglVertexAttribPointer(ATTR_INDEX_TEXCOORD1, 2, GL_FLOAT, 0, vbo->stride_st, BUFFER_OFFSET(vbo->ofs_st + sizeof (vec2_t) * glState.vertexAttribsTexCoordOffset[1]));
		glState.vertexAttribPointersSet |= ATTR_TEXCOORD1;
	}

	if((attribBits & ATTR_NORMAL) && (!(glState.vertexAttribPointersSet & ATTR_NORMAL) || animated))
	{
		GLimp_LogComment("qglVertexAttribPointer( ATTR_INDEX_NORMAL )\n");

		qglVertexAttribPointer(ATTR_INDEX_NORMAL, 4, GL_UNSIGNED_INT_2_10_10_10_REV, GL_TRUE, vbo->stride_normal, BUFFER_OFFSET(vbo->ofs_normal + newFrame * vbo->size_normal));
		glState.vertexAttribPointersSet |= ATTR_NORMAL;
	}

	if((attribBits & ATTR_TANGENT) && (!(glState.vertexAttribPointersSet & ATTR_TANGENT) || animated))
	{
		GLimp_LogComment("qglVertexAttribPointer( ATTR_INDEX_TANGENT )\n");

		qglVertexAttribPointer(ATTR_INDEX_TANGENT, 4, GL_UNSIGNED_INT_2_10_10_10_REV, GL_TRUE, vbo->stride_tangent, BUFFER_OFFSET(vbo->ofs_tangent + newFrame * vbo->size_normal)); // FIXME
		glState.vertexAttribPointersSet |= ATTR_TANGENT;
	}

	if((attribBits & ATTR_COLOR) && !(glState.vertexAttribPointersSet & ATTR_COLOR))
	{
		GLimp_LogComment("qglVertexAttribPointer( ATTR_INDEX_COLOR )\n");

		qglVertexAttribPointer(ATTR_INDEX_COLOR, 4, GL_FLOAT, 0, vbo->stride_vertexcolor, BUFFER_OFFSET(vbo->ofs_vertexcolor));
		glState.vertexAttribPointersSet |= ATTR_COLOR;
	}

	if((attribBits & ATTR_LIGHTDIRECTION) && !(glState.vertexAttribPointersSet & ATTR_LIGHTDIRECTION))
	{
		GLimp_LogComment("qglVertexAttribPointer( ATTR_INDEX_LIGHTDIRECTION )\n");

		qglVertexAttribPointer(ATTR_INDEX_LIGHTDIRECTION, 4, GL_UNSIGNED_INT_2_10_10_10_REV, GL_TRUE, vbo->stride_lightdir, BUFFER_OFFSET(vbo->ofs_lightdir));
		glState.vertexAttribPointersSet |= ATTR_LIGHTDIRECTION;
	}

	if((attribBits & ATTR_POSITION2) && (!(glState.vertexAttribPointersSet & ATTR_POSITION2) || animated))
	{
		GLimp_LogComment("qglVertexAttribPointer( ATTR_INDEX_POSITION2 )\n");

		qglVertexAttribPointer(ATTR_INDEX_POSITION2, 3, GL_FLOAT, 0, vbo->stride_xyz, BUFFER_OFFSET(vbo->ofs_xyz + oldFrame * vbo->size_xyz));
		glState.vertexAttribPointersSet |= ATTR_POSITION2;
	}

	if((attribBits & ATTR_NORMAL2) && (!(glState.vertexAttribPointersSet & ATTR_NORMAL2) || animated))
	{
		GLimp_LogComment("qglVertexAttribPointer( ATTR_INDEX_NORMAL2 )\n");

		qglVertexAttribPointer(ATTR_INDEX_NORMAL2, 4, GL_UNSIGNED_INT_2_10_10_10_REV, GL_TRUE, vbo->stride_normal, BUFFER_OFFSET(vbo->ofs_normal + oldFrame * vbo->size_normal));
		glState.vertexAttribPointersSet |= ATTR_NORMAL2;
	}

	if((attribBits & ATTR_TANGENT2) && (!(glState.vertexAttribPointersSet & ATTR_TANGENT2) || animated))
	{
		GLimp_LogComment("qglVertexAttribPointer( ATTR_INDEX_TANGENT2 )\n");

		qglVertexAttribPointer(ATTR_INDEX_TANGENT2, 4, GL_UNSIGNED_INT_2_10_10_10_REV, GL_TRUE, vbo->stride_tangent, BUFFER_OFFSET(vbo->ofs_tangent + oldFrame * vbo->size_normal)); // FIXME
		glState.vertexAttribPointersSet |= ATTR_TANGENT2;
	}

	if((attribBits & ATTR_BONE_INDEXES) && !(glState.vertexAttribPointersSet & ATTR_BONE_INDEXES))
	{
		GLimp_LogComment("qglVertexAttribPointer( ATTR_INDEX_BONE_INDEXES )\n");

		qglVertexAttribPointer(ATTR_INDEX_BONE_INDEXES, 4, GL_FLOAT, 0, vbo->stride_boneindexes, BUFFER_OFFSET(vbo->ofs_boneindexes));
		glState.vertexAttribPointersSet |= ATTR_BONE_INDEXES;
	}

	if((attribBits & ATTR_BONE_WEIGHTS) && !(glState.vertexAttribPointersSet & ATTR_BONE_WEIGHTS))
	{
		GLimp_LogComment("qglVertexAttribPointer( ATTR_INDEX_BONE_WEIGHTS )\n");

		qglVertexAttribPointer(ATTR_INDEX_BONE_WEIGHTS, 4, GL_FLOAT, 0, vbo->stride_boneweights, BUFFER_OFFSET(vbo->ofs_boneweights));
		glState.vertexAttribPointersSet |= ATTR_BONE_WEIGHTS;
	}

}


shaderProgram_t *GLSL_GetGenericShaderProgram(int stage)
{
	shaderStage_t *pStage = tess.xstages[stage];
	int shaderAttribs = 0;

	if (tess.fogNum && pStage->adjustColorsForFog)
	{
		shaderAttribs |= GENERICDEF_USE_FOG;
	}

	switch (pStage->rgbGen)
	{
		case CGEN_LIGHTING_DIFFUSE:
			shaderAttribs |= GENERICDEF_USE_RGBAGEN;
			break;
		default:
			break;
	}

	switch (pStage->alphaGen)
	{
		case AGEN_LIGHTING_SPECULAR:
		case AGEN_PORTAL:
			shaderAttribs |= GENERICDEF_USE_RGBAGEN;
			break;
		default:
			break;
	}

	if (pStage->bundle[0].tcGen != TCGEN_TEXTURE)
	{
		shaderAttribs |= GENERICDEF_USE_TCGEN_AND_TCMOD;
	}

	if (tess.shader->numDeforms && !ShaderRequiresCPUDeforms(tess.shader))
	{
		shaderAttribs |= GENERICDEF_USE_DEFORM_VERTEXES;
	}

	if (glState.vertexAnimation)
	{
		shaderAttribs |= GENERICDEF_USE_VERTEX_ANIMATION;
	}

	if (glState.skeletalAnimation)
	{
		shaderAttribs |= GENERICDEF_USE_SKELETAL_ANIMATION;
	}

	if (pStage->bundle[0].numTexMods)
	{
		shaderAttribs |= GENERICDEF_USE_TCGEN_AND_TCMOD;
	}

	if (pStage->glow)
	{
		shaderAttribs |= GENERICDEF_USE_GLOW_BUFFER;
	}

	return &tr.genericShader[shaderAttribs];
}
