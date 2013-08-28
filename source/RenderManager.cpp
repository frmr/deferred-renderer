#include "RenderManager.h"

#include <iostream>

using std::cout;
using std::endl;

void RenderManager::StartRenderToFBO( const EngineConfig &engineCfg ) const
{
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);
	glPushAttrib(GL_VIEWPORT_BIT);
	glViewport( 0, 0, engineCfg.GetActiveWidth(), engineCfg.GetActiveHeight() );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glActiveTextureARB(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);

	// Specify what to render and start acquiring
	GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT };
	glDrawBuffers(2, buffers);
}

void RenderManager::StopRenderToFBO() const
{
    // Stop acquiring and unbind the FBO
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glPopAttrib();
}

void RenderManager::Render( const Simulation &gameSim, const EngineConfig &engineCfg ) const
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( (float) engineCfg.GetActiveHeight() / (float) engineCfg.GetActiveWidth() * (float) engineCfg.GetFOV(), (float) engineCfg.GetActiveWidth() / (float) engineCfg.GetActiveHeight(), 1.0f, 1000.0f );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgramObjectARB( deferredShadingShader.GetProgramHandler() );

    glEnable( GL_DEPTH_TEST );

    StartRenderToFBO( engineCfg );

    //bind the surface texture and pass it to the shader
    glBindTexture( GL_TEXTURE_2D, m_testTexture );
    glUniform1i ( m_testTextureID, 0);

    gameSim.RenderLit();

    StopRenderToFBO();

    glUseProgramObjectARB( 0 );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0.0, (float) engineCfg.GetActiveWidth(), (float) engineCfg.GetActiveHeight(), 0.0, 0.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);

    glBindTexture(GL_TEXTURE_2D, m_diffuseTexture);
    //glBindTexture(GL_TEXTURE_2D, m_normalsTexture);
    //glBindTexture(GL_TEXTURE_2D, m_depthTexture);

    glPushMatrix();
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(0.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f((float) engineCfg.GetActiveWidth(), 0.0f );
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f((float) engineCfg.GetActiveWidth(), (float) engineCfg.GetActiveHeight());
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(0.0f, (float) engineCfg.GetActiveHeight());
    glEnd();
    glPopMatrix();
}

void RenderManager::SetupOpenGL( const EngineConfig &engineCfg ) const
{
    glewInit();

    glViewport( 0, 0, engineCfg.GetActiveWidth(), engineCfg.GetActiveHeight() );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( (float) engineCfg.GetActiveHeight() / (float) engineCfg.GetActiveWidth() * (float) engineCfg.GetFOV(), (float) engineCfg.GetActiveWidth() / (float) engineCfg.GetActiveHeight(), 1.0f, 1000.0f );

    glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

RenderManager::RenderManager( const EngineConfig &engineCfg )
{
    SetupOpenGL( engineCfg );
    deferredShadingShader.Load( "../data/shaders/deferredShading.vert", "../data/shaders/deferredShading.frag" );
    //deferredRenderingShader.loadFromFile( "data/shaders/deferredRendering.vert", "data/shaders/deferredRendering.frag" );

    // Generate the OGL resources for what we need
	glGenFramebuffersEXT(1, &m_fbo);
	glGenRenderbuffersEXT(1, &m_normalsRT);
	glGenRenderbuffersEXT(1, &m_diffuseRT);
	glGenRenderbuffersEXT(1, &m_depthRT );

    // Bind the FBO so that the next operations will be bound to it
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);

	// Bind the normal render target
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_normalsRT);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGB8, engineCfg.GetActiveWidth(), engineCfg.GetActiveHeight() );
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, m_normalsRT);

    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_diffuseRT);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGB8, engineCfg.GetActiveWidth(), engineCfg.GetActiveHeight());
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_RENDERBUFFER_EXT, m_diffuseRT);

	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_depthRT);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, engineCfg.GetActiveWidth(), engineCfg.GetActiveHeight() );
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_depthRT);

	// Generate and bind the OGL texture for normals
	glGenTextures(1, &m_normalsTexture);
	glBindTexture(GL_TEXTURE_2D, m_normalsTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, engineCfg.GetActiveWidth(), engineCfg.GetActiveHeight(), 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Attach the texture to the FBO
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_normalsTexture, 0);

    // Generate and bind the OGL texture for diffuse
	glGenTextures(1, &m_diffuseTexture);
	glBindTexture(GL_TEXTURE_2D, m_diffuseTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, engineCfg.GetActiveWidth(), engineCfg.GetActiveHeight(), 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Attach the texture to the FBO
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_TEXTURE_2D, m_diffuseTexture, 0);

    // Generate and bind the OGL texture for depth
	glGenTextures(1, &m_depthTexture);
	glBindTexture(GL_TEXTURE_2D, m_depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, engineCfg.GetActiveWidth(), engineCfg.GetActiveHeight(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Attach the texture to the FBO
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, m_depthTexture, 0);

    //check that FBO is complete
    if ( glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) != GL_FRAMEBUFFER_COMPLETE_EXT )
    {
        //print error
    }

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    glDisable(GL_LIGHTING);

    //load the surface texture from file
    sf::Image img_data;
    img_data.loadFromFile("../data/textures/test.png");

	glGenTextures(1, &m_testTexture);
	glBindTexture(GL_TEXTURE_2D, m_testTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_data.getSize().x, img_data.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //get the memory location of the surface texture in the shader
	m_testTextureID = glGetUniformLocationARB(deferredShadingShader.GetProgramHandler(), "tDiffuse");
}

RenderManager::~RenderManager()
{
    glDeleteTextures(1, &m_normalsTexture);
    glDeleteTextures(1, &m_diffuseTexture);
    glDeleteTextures(1, &m_depthTexture );
	glDeleteFramebuffersEXT(1, &m_fbo);
	glDeleteRenderbuffersEXT(1, &m_normalsRT);
	glDeleteRenderbuffersEXT(1, &m_diffuseRT);
	glDeleteRenderbuffersEXT(1, &m_depthRT);
}
