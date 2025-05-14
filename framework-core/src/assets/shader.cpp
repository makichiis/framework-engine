#include <fe/objects/assets/shaders/shader.hpp>
#include <glad/gl.h> // TODO: (CRITICAL) CHANGE
#include <tuple>

namespace fe {

std::variant<ShaderHandle, ShaderError> ShaderAssembler::CreateShader(GLenum type, string_ref_t source) {
    GLuint id = glCreateShader(type);

    const char* dataptr = source.data();
    glShaderSource(id, 1, &dataptr, nullptr);
    glCompileShader(id);

    int success = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (!success) {
        int message_length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &message_length);

        std::string error_message(static_cast<size_t>(1 + message_length), '\0');
        glGetShaderInfoLog(id, message_length, nullptr, error_message.data());

        std::cout << "uh oh\n";

        return ShaderError{ error_message };
    }

    return ShaderHandle{ type, id };
}

// TODO: Shader caching ? long-term consideration
std::variant<GLuint, ShaderError> ShaderAssembler::CreateAndLinkProgram(std::vector<ShaderHandle> shader_units) {
    GLuint program_id = glCreateProgram();
    glUseProgram(program_id);

    assert(shader_units.size() >= 2);

    for (auto&& shader : shader_units)
        glAttachShader(program_id, shader.id);

    glLinkProgram(program_id);

    int success = 0;
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);

    if (!success) {
        int message_length;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &message_length);

        std::string error_message(static_cast<size_t>(1 + message_length), '\0');
        glGetProgramInfoLog(program_id, message_length, nullptr, error_message.data());

        return ShaderError{ error_message };
    }

    for (auto&& shader : shader_units)
        glDeleteShader(shader.id);

    return program_id;
}

GLuint Shader::GetShaderID() const {
    return program_id_;
}

GLint Shader::get_uniform_location_and_cache_(string_ref_t name) {
    auto loc = uniform_cache_.find(name);
    glUseProgram(GetShaderID());

    if (loc == uniform_cache_.end()) {
        GLint res = glGetUniformLocation(program_id_, name.c_str());
        uniform_cache_.insert_or_assign(name, res);
        return res;
    }

    return loc->second;
}

bool Shader::HasUniform(string_ref_t name) {
    GLint loc = glGetUniformLocation(program_id_, name.c_str());
    if (loc) {
        uniform_cache_.insert_or_assign(name, loc);
    }

    return loc != -1; 
}

void Shader::SetBool(string_ref_t name, bool value) {
    glUniform1i(get_uniform_location_and_cache_(name), value ? GL_TRUE : GL_FALSE);
}

void Shader::SetInt(string_ref_t name, GLint value) {
    glUniform1i(get_uniform_location_and_cache_(name), value);
}

void Shader::SetIVec2(string_ref_t name, ivec2 values) {
    glUniform2i(get_uniform_location_and_cache_(name), std::get<0>(values), std::get<1>(values));
}

void Shader::SetIVec3(string_ref_t name, ivec3 values) {
    glUniform3i(get_uniform_location_and_cache_(name), std::get<0>(values), std::get<1>(values), std::get<2>(values));
}

void Shader::SetIVec4(string_ref_t name, ivec4 values) {
    glUniform4i(get_uniform_location_and_cache_(name), std::get<0>(values), std::get<1>(values), std::get<2>(values), std::get<3>(values));
}

void Shader::SetUInt(string_ref_t name, GLuint value) {
    glUniform1ui(get_uniform_location_and_cache_(name), value);
}

void Shader::SetUIVec2(string_ref_t name, uivec2 values) {
    glUniform2ui(get_uniform_location_and_cache_(name), std::get<0>(values), std::get<1>(values));
}

void Shader::SetUIVec3(string_ref_t name, uivec3 values) {
    glUniform3ui(get_uniform_location_and_cache_(name), std::get<0>(values), std::get<1>(values), std::get<2>(values));
}

void Shader::SetUIVec4(string_ref_t name, uivec4 values) {
    glUniform4ui(get_uniform_location_and_cache_(name), std::get<0>(values), std::get<1>(values), std::get<2>(values), std::get<3>(values));
}

void Shader::SetFloat(string_ref_t name, GLfloat value) {
    glUniform1f(get_uniform_location_and_cache_(name), value);
}

void Shader::SetVec2(string_ref_t name, vec2 values) {
    glUniform2f(get_uniform_location_and_cache_(name), std::get<0>(values), std::get<1>(values));
}

void Shader::SetVec3(string_ref_t name, vec3 values) {
    glUniform3f(get_uniform_location_and_cache_(name), std::get<0>(values), std::get<1>(values), std::get<2>(values));
}

void Shader::SetVec4(string_ref_t name, vec4 values) {
    glUniform4f(get_uniform_location_and_cache_(name), std::get<0>(values), std::get<1>(values), std::get<2>(values), std::get<3>(values));
}

void Shader::SetInts(string_ref_t name, GLsizei count, int_valueptr_t value) {
    glUniform1iv(get_uniform_location_and_cache_(name), count, value);
}

void Shader::SetIVec2s(string_ref_t name, GLsizei count, int_valueptr_t value) {
    glUniform2iv(get_uniform_location_and_cache_(name), count, value);
}

void Shader::SetIVec3s(string_ref_t name, GLsizei count, int_valueptr_t value) {
    glUniform3iv(get_uniform_location_and_cache_(name), count, value);
}

void Shader::SetIVec4s(string_ref_t name, GLsizei count, int_valueptr_t value) {
    glUniform4iv(get_uniform_location_and_cache_(name), count, value);
}

void Shader::SetUInts(string_ref_t name, GLsizei count, uint_valueptr_t value) {
    glUniform1uiv(get_uniform_location_and_cache_(name), count, value);
}

void Shader::SetUIVec2s(string_ref_t name, GLsizei count, uint_valueptr_t value) {
    glUniform2uiv(get_uniform_location_and_cache_(name), count, value);
}

void Shader::SetUIVec3s(string_ref_t name, GLsizei count, uint_valueptr_t value) {
    glUniform3uiv(get_uniform_location_and_cache_(name), count, value);
}

void Shader::SetUIVec4s(string_ref_t name, GLsizei count, uint_valueptr_t value) {
    glUniform4uiv(get_uniform_location_and_cache_(name), count, value);
}

void Shader::SetFloats(string_ref_t name, GLsizei count, float_valueptr_t value) {
    glUniform1fv(get_uniform_location_and_cache_(name), count, value);
}

void Shader::SetVec2s(string_ref_t name, GLsizei count, float_valueptr_t value) {
    glUniform2fv(get_uniform_location_and_cache_(name), count, value);
}

void Shader::SetVec3s(string_ref_t name, GLsizei count, float_valueptr_t value) {
    glUniform3fv(get_uniform_location_and_cache_(name), count, value);
}

void Shader::SetVec4s(string_ref_t name, GLsizei count, float_valueptr_t value) {
    glUniform4fv(get_uniform_location_and_cache_(name), count, value);
}

void Shader::SetMatrix2s(string_ref_t name, GLsizei count, GLboolean transpose, float_valueptr_t value) {
    glUniformMatrix2fv(get_uniform_location_and_cache_(name), count, transpose, value);
}

void Shader::SetMatrix3s(string_ref_t name, GLsizei count, GLboolean transpose, float_valueptr_t value) {
    glUniformMatrix3fv(get_uniform_location_and_cache_(name), count, transpose, value);
}

void Shader::SetMatrix4s(string_ref_t name, GLsizei count, GLboolean transpose, float_valueptr_t value) {
    glUniformMatrix4fv(get_uniform_location_and_cache_(name), count, transpose, value);
}

void Shader::SetMatrix2x3s(string_ref_t name, GLsizei count, GLboolean transpose, float_valueptr_t value) {
    glUniformMatrix2x3fv(get_uniform_location_and_cache_(name), count, transpose, value);
}

void Shader::SetMatrix3x2s(string_ref_t name, GLsizei count, GLboolean transpose, float_valueptr_t value) {
    glUniformMatrix3x2fv(get_uniform_location_and_cache_(name), count, transpose, value);
}

void Shader::SetMatrix2x4s(string_ref_t name, GLsizei count, GLboolean transpose, float_valueptr_t value) {
    glUniformMatrix2x4fv(get_uniform_location_and_cache_(name), count, transpose, value);
}

void Shader::SetMatrix4x2s(string_ref_t name, GLsizei count, GLboolean transpose, float_valueptr_t value) {
    glUniformMatrix4x2fv(get_uniform_location_and_cache_(name), count, transpose, value);
}

void Shader::SetMatrix3x4s(string_ref_t name, GLsizei count, GLboolean transpose, float_valueptr_t value) {
    glUniformMatrix3x4fv(get_uniform_location_and_cache_(name), count, transpose, value);
}

void Shader::SetMatrix4x3s(string_ref_t name, GLsizei count, GLboolean transpose, float_valueptr_t value) {
    glUniformMatrix4x3fv(get_uniform_location_and_cache_(name), count, transpose, value);
}

} // namespace fe
