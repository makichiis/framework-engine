#include <iostream>

#include <fe/objects/assets/shaders/basic_color_shader.hpp>
#include <fe/runtime_handler.hpp>

static const char* basic_color_shader_src_vertex_ = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec2 aTex;\n"
    "layout (location = 2) in vec3 aNormal;\n"
    ""
    "uniform mat4 projection;\n"
    "uniform mat4 view;\n"
    "uniform mat4 model;\n"
    ""
    "void main()\n"
    "{\n"
    "    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

static const char* basic_color_shader_src_frag_ = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 color;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
    "}\0";

// TODO: (CRITICAL) This is an awful model. Refactor into global shader type factory. 

void fe::BasicColorShader::OnInit() {
    static GLuint program_id = build_program_();
    program_id_ = program_id;
}

GLuint fe::BasicColorShader::build_program_() {
    const char* source_vert = basic_color_shader_src_vertex_;
    const char* source_frag = basic_color_shader_src_frag_;

    auto shader_vertex_result = ShaderAssembler::CreateShader(GL_VERTEX_SHADER, source_vert);
    if (ShaderAssembler::IsError(shader_vertex_result)) {
        std::cerr << "Failed to build Shader BasicColorShader [VERTEX SHADER]: " << std::get<ShaderError>(shader_vertex_result).message << '\n';
        std::abort();
    }

    auto shader_fragment_result = ShaderAssembler::CreateShader(GL_FRAGMENT_SHADER, source_frag);
    if (ShaderAssembler::IsError(shader_fragment_result)) {
        std::cerr << "Failed to build Shader BasicColorShader [FRAGMENT SHADER]: " << std::get<ShaderError>(shader_fragment_result).message << '\n';
        std::abort();
    }

    auto shader_vertex = std::get<ShaderHandle>(shader_vertex_result);
    auto shader_fragment = std::get<ShaderHandle>(shader_fragment_result);

    auto shader_program_result = ShaderAssembler::CreateAndLinkProgram({ shader_vertex, shader_fragment });
    if (ShaderAssembler::IsError(shader_program_result)) {
        std::cerr << "Failed to link Shader BasicColorShader: " << std::get<ShaderError>(shader_program_result).message << '\n';
        std::abort();
    }

    return std::get<GLuint>(shader_program_result);
}
