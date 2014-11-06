#version 400

in vec3 vNormalFrag;
in vec3 vTangentFrag;
in vec3 vBitangentFrag;
in vec2 vTexCoord1Frag;
in vec2 vTexCoord2Frag;
in vec3 vWorldPosFrag;

layout (location = 0) out vec4 vWorldPosOut; 
layout (location = 1) out vec4 vDiffuseOut; 
layout (location = 2) out vec4 vNormalOut; 
layout (location = 3) out vec4 vOutExtra; 

uniform sampler2D sDiffuse;

void main() 
{
	vec4 vDiffuse = texture(sDiffuse, vTexCoord1Frag);
	vWorldPosOut = vec4(vWorldPosFrag.xyz, 0.0);
    vDiffuseOut = vec4(vDiffuse.xyz, 0.0);
    vNormalOut = vec4(vNormalFrag.xyz, 0.0);
    vOutExtra = vec4(0.0, 0.0, 0.0, 0.0);
}
