#version 400

uniform sampler2D sTexture;
in vec2 vTexCoordFrag;
out vec4 vColour;

void main() 
{
	vec4 vTex = texture(sTexture, vTexCoordFrag);
    vColour = vec4(vTex.xyz, 1.0);
}
