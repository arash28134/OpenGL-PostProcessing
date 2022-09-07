#pragma once

#include <GL/glew.h>

#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>

class PostProcessing_Shader
{
private:
	GLuint shader;

	void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	void compileShaders(const char* vShaderCode, const char* fShaderCode);
public:
	PostProcessing_Shader();

    // Read a shader file (e.g. vertex shader)
	static std::string ReadShader(std::string fileName);

	// Create a shader program using vertex and fragment shaders
	void CreateProgram(std::string vShader, std::string fShader);

	// Using a shader program
	void UseShader() { glUseProgram(this->shader); }

	GLuint GetProgram() { return this->shader; }

	~PostProcessing_Shader();
};

class PostProcessing
{
private:
    int width, height;

    unsigned int FBO;
    unsigned int framebufferTexture;

    PostProcessing_Shader* framebuffer_shader;

    GLuint uniformScreenResolution;

    static const float rectangleVerts[];

    unsigned int rectVAO;
public:
    PostProcessing();

    void Initialize(int _width, int _height, const char* vShader_Path, const char* fShader_Path);

    void StartProcessing();
    void EndProcessing();

    ~PostProcessing();
};