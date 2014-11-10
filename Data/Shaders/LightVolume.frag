#version 400

in vec4 vClipSpacePosition;

out vec4 vColour;

uniform vec3 vLightPosition;

uniform sampler2D sWorldPos;
uniform sampler2D sDiffuse;
uniform sampler2D sNormal;

void main() 
{
	vec2 vTexCoord = (vClipSpacePosition.xy/vClipSpacePosition.w * 0.5) + 0.5;
	vec3 vWorldPos = texture(sWorldPos, vTexCoord).xyz;	
	vec3 vDiffuse = texture(sDiffuse, vTexCoord).xyz;
	vec3 vNormal = texture(sNormal, vTexCoord).xyz;

    vColour = vec4(vDiffuse + vec3(0.2, 0.2, 0.2), 1.0);
}
