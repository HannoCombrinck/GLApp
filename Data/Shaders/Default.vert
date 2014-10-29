#version 400

layout(location=0) in vec3 vPosition;
layout(location=1) in vec3 vNormal;
layout(location=2) in vec3 vTangent;
layout(location=3) in vec3 vBitangent;
layout(location=4) in vec2 vTexCoord1;
layout(location=5) in vec2 vTexCoord2;

out vec3 vNormalFrag;
out vec3 vTangentFrag;
out vec3 vBitangentFrag;
out vec2 vTexCoord1Frag;
out vec2 vTexCoord2Frag;

void main() 
{
	vNormalFrag = vNormal;
	vTangentFrag = vTangent;
	vBitangentFrag = vBitangent;
	vTexCoord1Frag = vTexCoord1;
	vTexCoord2Frag = vTexCoord2;

    gl_Position = vec4(vPosition, 1);
}
