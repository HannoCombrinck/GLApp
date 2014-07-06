#version 400

layout(location=0) in vec3 vPosition;
layout(location=1) in vec2 vTexCoord;

uniform vec2 vUVScale;
uniform vec2 vUVOffset;
uniform vec2 vPosScale;
uniform vec2 vPosOffset;

out vec2 vTexCoordFrag;

void main() 
{
	vTexCoordFrag = vec2(vTexCoord.x*vUVScale.x + vUVOffset.x, vTexCoord.y*vUVScale.y + vUVOffset.y);
	vec2 vPosNormalized = vec2(vPosition.x*vPosScale.x + vPosOffset.x, vPosition.y*vPosScale.y + vPosOffset.y);
    gl_Position = vec4(vPosNormalized.x*2.0 - 1.0, vPosNormalized.y*2.0 - 1.0, 0, 1);
}
