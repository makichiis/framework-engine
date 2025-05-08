#ifndef FE_BASIC_COLOR_SHADER_HPP
#define FE_BASIC_COLOR_SHADER_HPP

#include "shader.hpp"

namespace fe {

class BasicColorShader : public Shader {
public:
    using Shader::Shader;

    BasicColorShader();
    BasicColorShader(std::string p_name);
private:
    GLuint build_program_();
};

}

#endif 