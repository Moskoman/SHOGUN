#include "ShaderProgram.h"
#include "Debug.h"

string ShaderProgram::ReadFile(string file)
{
	ifstream t(file);
	// Read file into buffer
	stringstream buffer;
	buffer << t.rdbuf();
	// Make a std::string and fill it with the contents of buffer
	string fileContent = buffer.str();
	Debug2("Abriu", file);
	return fileContent;
}

void ShaderProgram::LinkAndValidateProgram()
{
	glLinkProgram(programID);
	glValidateProgram(programID);
}

GLint ShaderProgram::getUniformLocation(string uniformName)
{
	GLint location = glGetUniformLocation(programID, uniformName.data());
	Debug2(uniformName, location);
	return location;
}

void ShaderProgram::loadInt(GLint location, GLint value)
{
	glUniform1i(location, value);
}

void ShaderProgram::loadFloat(GLint location, GLfloat value)
{
	glUniform1f(location, value);
}

void ShaderProgram::loadVector4D(GLint location, glm::vec4 vector)
{
	glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}

void ShaderProgram::loadVector(GLint location, glm::vec3 vector)
{
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void ShaderProgram::load2DVector(GLint location, glm::vec2 vector)
{
	glUniform2f(location, vector.x, vector.y);
}

void ShaderProgram::loadBoolean(GLint location, GLboolean value)
{
	glUniform1f(location, value);
}

void ShaderProgram::loadMatrix(GLint location, glm::mat4 matrix)
{
	glUniformMatrix4fv(location, 1, false, (const float*)glm::value_ptr(matrix));
}

ShaderProgram::ShaderProgram(string vertexFile, string fragmentFile) : vertexFile(vertexFile), fragmentFile(fragmentFile){
	Debug("ShaderProgram Initialized");
	vertexShaderID = LoadShader(vertexFile, GL_VERTEX_SHADER);
	fragmentShaderID = LoadShader(fragmentFile, GL_FRAGMENT_SHADER);
	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);	

}

ShaderProgram::~ShaderProgram()
{
	stop();
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glDeleteProgram(programID);
}


GLuint ShaderProgram::LoadShader(std::string filename, GLenum type)
{
	std::fstream file(filename.c_str(), std::fstream::in | std::fstream::ate | std::fstream::binary);

	if (!file.is_open()) {
		Debug("Could not open file: " << filename);
		exit(-2);
	}

	int filesize = file.tellg();

	file.seekg(0, std::ios::beg);

	GLchar* info;

	info = new GLchar[filesize];

	file.read(info, filesize);

	GLuint shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &info, &filesize);
	glCompileShader(shaderID);

	GLint param;

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &param);

	if (param == GL_FALSE) {
		char ErrorLog[500];
		int size;
		glGetShaderInfoLog(shaderID, 500, &size, ErrorLog);
		Debug("Error compiling file: " << filename << std::endl << ErrorLog );
		exit(-3);
	}

	delete[] info;

	return shaderID;
}


void ShaderProgram::start()
{
	glUseProgram(programID);
}


void ShaderProgram::stop() {
	glUseProgram(0);
}

void ShaderProgram::bindAttribute(GLuint attribute, string variableName)
{
	glBindAttribLocation(programID, attribute, variableName.data());
}

