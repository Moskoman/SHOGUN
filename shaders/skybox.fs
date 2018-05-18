#version 400

in vec3 textureCoords;
out vec4 out_Color;

uniform samplerCube cubeMap;
uniform samplerCube cubeMap2;
uniform float blendFactor;

void main(void){
	vec4 texture1 = texture(cubeMap, textureCoords);
vec4 texture2 = texture(cubeMap2, textureCoords);
vec4 finalColour = mix(texture1, texture2, blendFactor);

    out_Color = finalColour;
}