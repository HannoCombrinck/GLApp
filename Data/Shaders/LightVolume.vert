#version 400

layout(location=0) in vec3 vPositionVert;
layout(location=1) in vec3 vNormalVert;
layout(location=2) in vec3 vTangentVert;
layout(location=3) in vec3 vBitangentVert;
layout(location=4) in vec2 vTexCoord1Vert;
layout(location=5) in vec2 vTexCoord2Vert;

out vec4 vClipSpacePosition;

uniform float fLightSize;

uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mWorld;

void main() 
{
	//vec4 v = mProjection * mView * mWorld * vec4(vPositionVert * fLightSize, 1);
	vec4 v = mProjection * mView * mWorld * vec4(vPositionVert * 15.0, 1);
	vClipSpacePosition = v;
    gl_Position = v;
}
