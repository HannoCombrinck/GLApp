#version 400

in vec3 vNormalFrag;
in vec3 vTangentFrag;
in vec3 vBitangentFrag;
in vec2 vTexCoord1Frag;
in vec2 vTexCoord2Frag;

out vec4 vColour;

uniform sampler2D sDiffuse;

void main() 
{
	vec4 vDiffuse = texture(sDiffuse, vTexCoord1Frag);
    vColour = vec4(vDiffuse.xyz, 1.0);
}
