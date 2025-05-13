#ifndef FE_SHADER_HPP
#define FE_SHADER_HPP

#include "../asset.hpp"

#include <unordered_map>
#include <variant>
#include <vector>
#include <string>
#include <tuple>

#include <glad/gl.h>

// using GLint = int; // TODO: (CRITICAL) Replace with unified GL header include 
// using GLuint = unsigned int;
// using GLfloat = float;
// using GLsizei = long long int; 
// using GLboolean = bool;

using string_ref_t = const std::string&;

using vec2 = std::tuple<GLfloat, GLfloat>;
using vec3 = std::tuple<GLfloat, GLfloat, GLfloat>;
using vec4 = std::tuple<GLfloat, GLfloat, GLfloat, GLfloat>;

using ivec2 = std::tuple<GLint, GLint>;
using ivec3 = std::tuple<GLint, GLint, GLint>;
using ivec4 = std::tuple<GLint, GLint, GLint, GLint>;

using uivec2 = std::tuple<GLuint, GLuint>;
using uivec3 = std::tuple<GLuint, GLuint, GLuint>;
using uivec4 = std::tuple<GLuint, GLuint, GLuint, GLuint>;

using float_valueptr_t = const GLfloat*;
using int_valueptr_t = const GLint*;
using uint_valueptr_t = const GLuint*;

namespace fe {

struct ShaderHandle {
    GLenum type;
    GLuint id;
};

struct ShaderError {
    std::string message;
};

class ShaderAssembler {
public:
    /**
     * @brief Create and compile a shader from `source`.
     * @return `ShaderHandle` if successfully compiled, or `ShaderError` if compilation could not be
     * completed.
     */
    static std::variant<ShaderHandle, ShaderError> CreateShader(GLenum type, string_ref_t source);

    /**
     * @brief Create shader program and link against all shaders in `shader_units`.
     * @return Program ID on successful linkage, or `ShaderError` if linking could not be completed.
     */
    static std::variant<GLuint, ShaderError> CreateAndLinkProgram(std::vector<ShaderHandle> shader_units);

    /**
     * @brief Returns `true` if the previous shader call resulted in an error. 
     * @note Effective wrapper for `std::holds_alternative<ShaderError>(result)`.
     */
    template <class T>
    static bool IsError(const std::variant<T, ShaderError>& result) {
        return std::holds_alternative<ShaderError>(result);
    }
};

class Shader : public Asset {
protected:
    GLuint program_id_;
    // TODO: https://stackoverflow.com/questions/16141178/is-it-possible-to-map-string-to-int-faster-than-using-hashmap
    std::unordered_map<std::string, GLint> uniform_cache_;
public:
    using Asset::Asset;

    GLuint GetShaderID() const;

    /**
     * TODO: Type validation etc. 
     */
    bool HasUniform(string_ref_t name);

    void SetBool(string_ref_t name, bool value);

    void SetInt(string_ref_t name, GLint value);
    void SetIVec2(string_ref_t name, ivec2 values);
    void SetIVec3(string_ref_t name, ivec3 values);
    void SetIVec4(string_ref_t name, ivec4 values);

    void SetUInt(string_ref_t name, GLuint value);
    void SetUIVec2(string_ref_t name, uivec2 values);
    void SetUIVec3(string_ref_t name, uivec3 values);
    void SetUIVec4(string_ref_t name, uivec4 values);

    void SetFloat(string_ref_t name, GLfloat value);
    void SetVec2(string_ref_t name, vec2 values);
    void SetVec3(string_ref_t name, vec3 values);
    void SetVec4(string_ref_t name, vec4 values);

    void SetInts(string_ref_t name, GLsizei count, int_valueptr_t value);
    void SetIVec2s(string_ref_t name, GLsizei count, int_valueptr_t value);
    void SetIVec3s(string_ref_t name, GLsizei count, int_valueptr_t value);
    void SetIVec4s(string_ref_t name, GLsizei count, int_valueptr_t value);

    void SetUInts(string_ref_t name, GLsizei count, uint_valueptr_t value);
    void SetUIVec2s(string_ref_t name, GLsizei count, uint_valueptr_t value);
    void SetUIVec3s(string_ref_t name, GLsizei count, uint_valueptr_t value);
    void SetUIVec4s(string_ref_t name, GLsizei count, uint_valueptr_t value);

    void SetFloats(string_ref_t name, GLsizei count, float_valueptr_t value);
    void SetVec2s(string_ref_t name, GLsizei count, float_valueptr_t value);
    void SetVec3s(string_ref_t name, GLsizei count, float_valueptr_t value);
    void SetVec4s(string_ref_t name, GLsizei count, float_valueptr_t value);

    void SetMatrix2s(string_ref_t name, GLsizei count, GLboolean transpose, float_valueptr_t value);
    void SetMatrix3s(string_ref_t name, GLsizei count, GLboolean transpose, float_valueptr_t value);
    void SetMatrix4s(string_ref_t name, GLsizei count, GLboolean transpose, float_valueptr_t value);

    void SetMatrix2x3s(string_ref_t name, GLsizei count, GLboolean transpose, float_valueptr_t value);
    void SetMatrix3x2s(string_ref_t name, GLsizei count, GLboolean transpose, float_valueptr_t value);
    void SetMatrix2x4s(string_ref_t name, GLsizei count, GLboolean transpose, float_valueptr_t value);
    void SetMatrix4x2s(string_ref_t name, GLsizei count, GLboolean transpose, float_valueptr_t value);
    void SetMatrix3x4s(string_ref_t name, GLsizei count, GLboolean transpose, float_valueptr_t value);
    void SetMatrix4x3s(string_ref_t name, GLsizei count, GLboolean transpose, float_valueptr_t value);
private:
    GLint get_uniform_location_and_cache_(string_ref_t name);
};

}

#endif 