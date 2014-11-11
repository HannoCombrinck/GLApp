#version 400

in vec2 vTexCoordFrag;
in vec4 vClipSpacePosition;

out vec4 vColour;

uniform float fAmbient;

uniform sampler2D sWorldPos;
uniform sampler2D sDiffuse;
uniform sampler2D sNormal;

void main() 
{
	vec2 vTexCoord = (vClipSpacePosition.xy/vClipSpacePosition.w * 0.5) + 0.5;
	vec3 vWorldPos = texture(sWorldPos, vTexCoord).xyz;	
	vec3 vDiffuse = texture(sDiffuse, vTexCoord).xyz;
	vec3 vNormal = texture(sNormal, vTexCoord).xyz;

    vColour = vec4(vDiffuse * fAmbient, 1.0);
}
