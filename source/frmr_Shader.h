#ifndef FRMR_SHADER_H
#define FRMR_SHADER_H

#include <string>
#include <fstream>
#include <iostream>

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
        string LoadShaderSourceFromFile( const string &filename )
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

    public:
        GLhandleARB GetProgramHandler() const
        {
            return programHandler;
        }

        void Load( const string &vertexShaderFilename, const string &fragmentShaderFilename )
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

    public:
        Shader()
        {
        }

        ~Shader()
        {
            glDeleteShader( vertexShader );
            glDeleteShader( fragmentShader );
        }
    };
}

#endif // FRMR_SHADER_H
