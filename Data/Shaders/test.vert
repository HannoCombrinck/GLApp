#version 400

layout(location=0) in vec3 vPosition;
layout(location=1) in vec3 vNormal;
layout(location=2) in vec2 vTexCoord;

out vec2 vTexCoordFrag;

void main() 
{
	vTexCoordFrag = vTexCoord;
    gl_Position = vec4(vPosition, 1);
}
