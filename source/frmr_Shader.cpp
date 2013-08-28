#include <fstream>
#include <iostream>

#include "frmr_Shader.h"

string frmr::Shader::LoadShaderSourceFromFile( const string &filename )
{
    string content;
    std::ifstream fileStream( filename.c_str(), std::ios::in );

    if( !fileStream.is_open() )
    {
        std::cout << "frmr::Shader::LoadShaderFromFile() - Could not load shader." << std::endl;
        return "";
    }
    else
    {
        string line = "";
        while( !fileStream.eof() )
        {
            std::getline( fileStream, line );
            content.append( line + "\n" );
        }

        fileStream.close();
        return content;
    }
}

void frmr::Shader::Load( const string &vertexShaderFilename, const string &fragmentShaderFilename )
{
    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );

    GLint compiled = 0;

    //load vertex shader
    string vertexShaderSourceString = LoadShaderSourceFromFile( vertexShaderFilename );
    const char* vertexShaderSourceChar = vertexShaderSourceString.c_str();

    vertexShader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
    glShaderSourceARB( vertexShader, 1, &vertexShaderSourceChar, NULL );
    glCompileShaderARB( vertexShader );
    glGetObjectParameterivARB( vertexShader, GL_OBJECT_COMPILE_STATUS_ARB, &compiled );

    if( compiled  == 0 )
    {
        //throw error
    }

    //load fragment shader
    string fragmentShaderSourceString = LoadShaderSourceFromFile( fragmentShaderFilename );
    const char* fragmentShaderSourceChar = fragmentShaderSourceString.c_str();

    fragmentShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
    glShaderSourceARB( fragmentShader, 1, &fragmentShaderSourceChar, NULL );
    glCompileShaderARB( fragmentShader );
    glGetObjectParameterivARB( fragmentShader, GL_OBJECT_COMPILE_STATUS_ARB, &compiled );

    if( compiled  == 0 )
    {
        //throw error
    }


    //bind vertex and fragment shaders together
    programHandler = glCreateProgramObjectARB();
    glAttachObjectARB( programHandler, vertexShader );
    glAttachObjectARB( programHandler, fragmentShader );
    glLinkProgramARB( programHandler );
}

GLhandleARB frmr::Shader::GetProgramHandler() const
{
    return programHandler;
}

frmr::Shader::Shader()
{

}

frmr::Shader::~Shader()
{
    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );
}
