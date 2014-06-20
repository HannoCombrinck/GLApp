#version 400

layout(location=0) in vec3 vPosition;
//layout(location=1) in vec3 vNormal;
//layout(location=2) in vec2 vTexCoord;

//layout(binding=0) uniform sampler2D sTestTexture;

void main() {
    gl_Position = vec4(vPosition, 1);
}