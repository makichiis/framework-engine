#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include <glad/gl.h>


/*
const char* shader_src_vertex = R"(#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 vertexColor;

void main() {
    gl_Position = vec4(aPos, 1.0);
    vertexColor = vec4(aPos.xzz * 2.5, 1.0);
}
)";

const char* shader_src_fragment = R"(#version 330 core
out vec4 FragColor;

in vec4 vertexColor;

void main() {
    FragColor = vertexColor;
}
)";*/

#endif
