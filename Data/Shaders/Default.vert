#version 400

layout(location=0) in vec3 vPositionVert;
layout(location=1) in vec3 vNormalVert;
layout(location=2) in vec3 vTangentVert;
layout(location=3) in vec3 vBitangentVert;
layout(location=4) in vec2 vTexCoord1Vert;
layout(location=5) in vec2 vTexCoord2Vert;

out vec3 vNormalFrag;
out vec3 vTangentFrag;
out vec3 vBitangentFrag;
out vec2 vTexCoord1Frag;
out vec2 vTexCoord2Frag;

uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mWorld;

void main() 
{
	vNormalFrag = normalize(mat3(mWorld) * vNormalVert);
	vTangentFrag = normalize(mat3(mWorld) * vTangentVert);
	vBitangentFrag = normalize(mat3(mWorld) * vBitangentVert);
	vTexCoord1Frag = vTexCoord1Vert;
	vTexCoord2Frag = vTexCoord2Vert;
	
    gl_Position = mProjection * mView * mWorld * vec4(vPositionVert, 1);
}
