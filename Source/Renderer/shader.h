/*******************************************************************
** Copyright (C) 2014-2015 {Joey de Vries} {joey.d.vries@gmail.com}
**
** This code is part of Lucid.
** https://github.com/JoeyDeVries/Lucid
**
** Lucid is free software: you can redistribute it and/or modify it
** under the terms of the CC BY-NC 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
*******************************************************************/
#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

/*
    General purpsoe shader object. Compiles from file, generates
    compile/link-time error messages and hosts several utility 
    functions for easy management.
*/
class Shader
{
public:
    std::string Name; // name of the shader program
    GLuint      ID;   // internal OpenGL ID of the shader program
public:
    Shader() { }

    // sets the current shader program as the active program
    Shader  &Use();
    // compiles the shader from source code from file
    void         Compile(const GLchar *vertexSource, const GLchar *fragmentSource, std::string directory); 
    // pre-processes the source code for custom #pragma directives
	std::string  PreProcess(std::string shaderCode, std::string directory);

    // uniform utility functions
    void         SetFloat   (std::string name, GLfloat value, GLboolean useShader = false);
    void         SetInteger (std::string name, GLint value, GLboolean useShader = false);
    void         SetVector2f(std::string name, GLfloat x, GLfloat y, GLboolean useShader = false);
    void         SetVector2f(std::string name, const glm::vec2 &value, GLboolean useShader = false);
    void         SetVector3f(std::string name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
    void         SetVector3f(std::string name, const glm::vec3 &value, GLboolean useShader = false);
    void         SetVector4f(std::string name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
    void         SetVector4f(std::string name, const glm::vec4 &value, GLboolean useShader = false);
    void         SetMatrix3 (std::string name, const glm::mat3 &matrix, GLboolean useShader = false);
    void         SetMatrix4 (std::string name, const glm::mat4 &matrix, GLboolean useShader = false);
private:
    // checks if compilation or linking failed and if so, prints error logs
    void    checkCompileErrors(GLuint object, std::string type);
};
#endif