#version 400

in vec3 vNormalFrag;
in vec3 vTangentFrag;
in vec3 vBitangentFrag;
in vec2 vTexCoord1Frag;
in vec2 vTexCoord2Frag;

out vec4 vColour;

uniform vec3 vInputColour;

void main() 
{
    vColour = vec4(vNormalFrag.xyz, 1.0);
}
