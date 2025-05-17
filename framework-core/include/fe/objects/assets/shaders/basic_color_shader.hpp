#ifndef FE_BASIC_COLOR_SHADER_HPP
#define FE_BASIC_COLOR_SHADER_HPP

#include "shader.hpp"

#include <glm/vec4.hpp>

namespace fe {

class BasicColorShader : public Shader {
public:
    using Shader::Shader;

    void OnInit() override;
private:
    GLuint build_program_();
};

}

#endif 