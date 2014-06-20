#version 400

uniform sampler2D sTestTexture;
in vec2 vTexCoordFrag;
out vec4 vColour;

void main() 
{
	vec4 vTex = texture(sTestTexture, vTexCoordFrag);
    vColour = vec4(vTex.xyz + vec3(0.5,0.5,0.5), 1.0);
}
