#version 400

layout(location=0) in vec3 vPositionVert;
layout(location=1) in vec2 vTexCoordVert;

out vec2 vTexCoordFrag;
out vec4 vClipSpacePosition;

void main() 
{
	vTexCoordFrag = vTexCoordVert;
	vClipSpacePosition = vec4(vPositionVert, 1);
    gl_Position = vec4(vPositionVert, 1);
}
