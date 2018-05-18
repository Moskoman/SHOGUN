#version 400 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in ivec4 BoneIDs;
layout (location = 4) in vec4 pesos;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

const int MAX_BONES = 100;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

uniform mat4 gBones[MAX_BONES];
uniform int animated;

void main(void) {
	mat4 BoneTransform = mat4(1.0);
	
	if(animated == 1){
		BoneTransform = gBones[BoneIDs[0]] * pesos[0];
		BoneTransform += gBones[BoneIDs[1]] * pesos[1];
		BoneTransform += gBones[BoneIDs[2]] * pesos[2];
		BoneTransform += gBones[BoneIDs[3]] * pesos[3];
	}

	vec4 transform = BoneTransform * vec4(aPos, 1.0);

	FragPos = vec3(model * transform);
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    TexCoords = aTexCoords;
    
    gl_Position = projection * view * vec4(FragPos,1.0);


}
