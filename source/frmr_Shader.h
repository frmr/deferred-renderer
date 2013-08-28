#ifndef FRMR_SHADER_H
#define FRMR_SHADER_H

#include <string>
#include "GL/glew.h"
using std::string;

namespace frmr
{
    class Shader
    {
    private:
        GLhandleARB vertexShader;
        GLhandleARB fragmentShader;
        GLhandleARB programHandler;

    private:
        string LoadShaderSourceFromFile( const string &filename );

    public:
        void Load( const string &vertexShaderFilename, const string &fragmentShaderFilename );
        GLhandleARB GetProgramHandler() const;

    public:
        Shader();
        ~Shader();
    };
}

#endif // FRMR_SHADER_H
