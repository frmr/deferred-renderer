#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "GL/glew.h"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "frmr_Vec3f.h"
#include "Simulation.h"
#include "frmr_Shader.h"

class RenderManager
{
private:
    frmr::Vec3f     ambientLightColor;
    frmr::Shader    deferredShadingShader;
    //sf::Shader      deferredRenderingShader;
    //displaylist of icosphere with radius of 1 (for lights)

    GLuint          m_testTexture;
    GLuint          m_testTextureID;

    GLuint			m_fbo; // The FBO ID

	GLuint			m_normalsRT; // The normals render target
	GLuint	        m_normalsTexture; // The OpenGL texture for the normals render target
	GLuint          m_diffuseRT;
	GLuint          m_diffuseTexture;
	GLuint          m_depthRT;
	GLuint          m_depthTexture;

	GLuint			m_normalsID; // Normals texture handle for the shader
	GLuint          m_diffuseID;
	GLuint          m_depthID;

private:
    void StartRenderToFBO() const;
    void StopRenderToFBO() const;

public:
    void Render( const Simulation &gameSim ) const;
    void SetupOpenGL() const;

public:
    RenderManager();
    ~RenderManager();
};

#endif // RENDER_MANAGER_H
