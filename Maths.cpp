#include "Maths.h"
#include "Game.h"


glm::mat4 Maths::createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, float scale)
{
	glm::mat4 matrix(1);
	matrix = glm::translate(matrix, translation);
	matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));
	return matrix;
}

glm::mat4 Maths::createTransformationMatrix(glm::vec2 translation, glm::vec2 scale)
{
	glm::mat4 matrix(1);
	matrix = glm::translate(matrix, glm::vec3(translation,0));
	matrix = glm::scale(matrix, glm::vec3(scale, 1));
	return matrix;
}

glm::mat4 Maths::createViewMatrix(Camera camera)
{
	glm::mat4 viewMatrix(1);
	
	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.pitch), glm::vec3(1,0,0));
	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.yaw), glm::vec3(0, 1, 0));

	glm::vec3 cameraPos = camera.position;
	glm::vec3 negPos = -camera.position;
	// now get the view matrix by taking the camera inverse
	viewMatrix = glm::translate(viewMatrix, negPos);
	
	return viewMatrix;
}


glm::mat4 Maths::Mat4FromAiMat4(aiMatrix4x4 mat)
{
	glm::mat4 ret;

	ret[0][0] = mat.a1;
	ret[0][1] = mat.a2;
	ret[0][2] = mat.a3;
	ret[0][3] = mat.a4;
	ret[1][0] = mat.b1;
	ret[1][1] = mat.b2;
	ret[1][2] = mat.b3;
	ret[1][3] = mat.b4;
	ret[2][0] = mat.c1;
	ret[2][1] = mat.c2;
	ret[2][2] = mat.c3;
	ret[2][3] = mat.c4;
	ret[3][0] = mat.d1;
	ret[3][1] = mat.d2;
	ret[3][2] = mat.d3;
	ret[3][3] = mat.d4;

	return ret;
}

aiMatrix4x4 Maths::aiMat4FromMat4(glm::mat4 mat)
{
	return aiMatrix4x4(mat[0][0], mat[0][1], mat[0][2], mat[0][3],
		mat[1][0], mat[1][1], mat[1][2], mat[1][3],
		mat[2][0], mat[2][1], mat[2][2], mat[2][3],
		mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
}

glm::vec3 Maths::Vec3FromAiVec3(aiVector3D vec)
{
	return glm::vec3(vec.x, vec.y, vec.z);
}

glm::quat Maths::QuatFromAiQuat(aiQuaternion quaternion)
{
	return glm::quat(quaternion.w, quaternion.x, quaternion.y, quaternion.z);
}

glm::mat4 Maths::createProjectionMatrix(float FOV, float NEAR_PLANE, float FAR_PLANE)
{
	return glm::perspective<float>(glm::radians(FOV), (float)Game::GetInstance()->WIDTH/ (float)Game::GetInstance()->HEIGHT, NEAR_PLANE, FAR_PLANE);
}


