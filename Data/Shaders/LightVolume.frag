#version 400

in vec4 vClipSpacePosition;

out vec4 vColour;

uniform vec3 vLightPosition;
uniform vec3 vLightColour;
uniform float fAttenuationFactor;

uniform sampler2D sWorldPos;
uniform sampler2D sDiffuse;
uniform sampler2D sNormal;

void main() 
{
	vec2 vTexCoord = (vClipSpacePosition.xy/vClipSpacePosition.w * 0.5) + 0.5;
	vec3 vWorldPos = texture(sWorldPos, vTexCoord).xyz;	
	vec3 vDiffuse = texture(sDiffuse, vTexCoord).xyz;
	vec3 vNormal = texture(sNormal, vTexCoord).xyz;

	vec3 vLightVec = vLightPosition - vWorldPos;
	float fLength = length(vLightVec);
	float fAttenuation = 1.0/(fLength*fLength) * fAttenuationFactor;

	vec3 vLightVecNorm = normalize(vLightVec);

    vec3 vLit = max(vec3(0.0), dot(vLightVecNorm, vNormal)) * vDiffuse * vLightColour * fAttenuation;
    vColour = vec4(vLit, 1.0);
}
