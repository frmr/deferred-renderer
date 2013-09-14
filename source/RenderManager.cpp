#include "RenderManager.h"

#include "IcosphereGenerator.h"

#include <iostream>

using std::cout;
using std::endl;

//this code is from MESA implementation of GLU's gluInvertMatrix(), although it is slightly modified
bool RenderManager::InvertMatrixGL( const float matrixIn[16], float matrixOut[16] ) const
{
    float inv[16];
    float det;
    int i;

    inv[0] = matrixIn[5] * matrixIn[10] * matrixIn[15] - matrixIn[5] * matrixIn[11] * matrixIn[14] - matrixIn[9] * matrixIn[6] * matrixIn[15] + matrixIn[9] * matrixIn[7] * matrixIn[14] + matrixIn[13] * matrixIn[6] * matrixIn[11] - matrixIn[13] * matrixIn[7] * matrixIn[10];
    inv[4] = -matrixIn[4] * matrixIn[10] * matrixIn[15] + matrixIn[4] * matrixIn[11] * matrixIn[14] + matrixIn[8] * matrixIn[6] * matrixIn[15] - matrixIn[8] * matrixIn[7] * matrixIn[14] - matrixIn[12] * matrixIn[6] * matrixIn[11] + matrixIn[12] * matrixIn[7] * matrixIn[10];
    inv[8] = matrixIn[4] * matrixIn[9] * matrixIn[15] - matrixIn[4] * matrixIn[11] * matrixIn[13] - matrixIn[8] * matrixIn[5] * matrixIn[15] + matrixIn[8] * matrixIn[7] * matrixIn[13] + matrixIn[12] * matrixIn[5] * matrixIn[11] - matrixIn[12] * matrixIn[7] * matrixIn[9];
    inv[12] = -matrixIn[4] * matrixIn[9] * matrixIn[14] + matrixIn[4] * matrixIn[10] * matrixIn[13] + matrixIn[8] * matrixIn[5] * matrixIn[14] - matrixIn[8] * matrixIn[6] * matrixIn[13] - matrixIn[12] * matrixIn[5] * matrixIn[10] + matrixIn[12] * matrixIn[6] * matrixIn[9];
    inv[1] = -matrixIn[1] * matrixIn[10] * matrixIn[15] + matrixIn[1] * matrixIn[11] * matrixIn[14] + matrixIn[9] * matrixIn[2] * matrixIn[15] - matrixIn[9] * matrixIn[3] * matrixIn[14] - matrixIn[13] * matrixIn[2] * matrixIn[11] + matrixIn[13] * matrixIn[3] * matrixIn[10];
    inv[5] = matrixIn[0] * matrixIn[10] * matrixIn[15] - matrixIn[0] * matrixIn[11] * matrixIn[14] - matrixIn[8] * matrixIn[2] * matrixIn[15] + matrixIn[8] * matrixIn[3] * matrixIn[14] + matrixIn[12] * matrixIn[2] * matrixIn[11] - matrixIn[12] * matrixIn[3] * matrixIn[10];
    inv[9] = -matrixIn[0] * matrixIn[9] * matrixIn[15] + matrixIn[0] * matrixIn[11] * matrixIn[13] + matrixIn[8] * matrixIn[1] * matrixIn[15] - matrixIn[8] * matrixIn[3] * matrixIn[13] - matrixIn[12] * matrixIn[1] * matrixIn[11] + matrixIn[12] * matrixIn[3] * matrixIn[9];
    inv[13] = matrixIn[0] * matrixIn[9] * matrixIn[14] - matrixIn[0] * matrixIn[10] * matrixIn[13] - matrixIn[8] * matrixIn[1] * matrixIn[14] + matrixIn[8] * matrixIn[2] * matrixIn[13] + matrixIn[12] * matrixIn[1] * matrixIn[10] - matrixIn[12] * matrixIn[2] * matrixIn[9];
    inv[2] = matrixIn[1] * matrixIn[6] * matrixIn[15] - matrixIn[1] * matrixIn[7] * matrixIn[14] - matrixIn[5] * matrixIn[2] * matrixIn[15] + matrixIn[5] * matrixIn[3] * matrixIn[14] + matrixIn[13] * matrixIn[2] * matrixIn[7] - matrixIn[13] * matrixIn[3] * matrixIn[6];
    inv[6] = -matrixIn[0] * matrixIn[6] * matrixIn[15] + matrixIn[0] * matrixIn[7] * matrixIn[14] + matrixIn[4] * matrixIn[2] * matrixIn[15] - matrixIn[4] * matrixIn[3] * matrixIn[14] - matrixIn[12] * matrixIn[2] * matrixIn[7] + matrixIn[12] * matrixIn[3] * matrixIn[6];
    inv[10] = matrixIn[0] * matrixIn[5] * matrixIn[15] - matrixIn[0] * matrixIn[7] * matrixIn[13] - matrixIn[4]  * matrixIn[1] * matrixIn[15] + matrixIn[4] * matrixIn[3] * matrixIn[13] + matrixIn[12] * matrixIn[1] * matrixIn[7] - matrixIn[12] * matrixIn[3] * matrixIn[5];
    inv[14] = -matrixIn[0] * matrixIn[5] * matrixIn[14] + matrixIn[0] * matrixIn[6] * matrixIn[13] + matrixIn[4] * matrixIn[1] * matrixIn[14] - matrixIn[4] * matrixIn[2] * matrixIn[13] - matrixIn[12] * matrixIn[1] * matrixIn[6] + matrixIn[12] * matrixIn[2] * matrixIn[5];
    inv[3] = -matrixIn[1] * matrixIn[6] * matrixIn[11] + matrixIn[1] * matrixIn[7] * matrixIn[10] + matrixIn[5] * matrixIn[2] * matrixIn[11] - matrixIn[5] * matrixIn[3] * matrixIn[10] - matrixIn[9] * matrixIn[2] * matrixIn[7] + matrixIn[9] * matrixIn[3] * matrixIn[6];
    inv[7] = matrixIn[0] * matrixIn[6] * matrixIn[11] - matrixIn[0] * matrixIn[7] * matrixIn[10] - matrixIn[4] * matrixIn[2] * matrixIn[11] + matrixIn[4] * matrixIn[3] * matrixIn[10] + matrixIn[8] * matrixIn[2] * matrixIn[7] - matrixIn[8] * matrixIn[3] * matrixIn[6];
    inv[11] = -matrixIn[0] * matrixIn[5] * matrixIn[11] + matrixIn[0] * matrixIn[7] * matrixIn[9] + matrixIn[4] * matrixIn[1] * matrixIn[11] - matrixIn[4] * matrixIn[3] * matrixIn[9] - matrixIn[8] * matrixIn[1] * matrixIn[7] + matrixIn[8] * matrixIn[3] * matrixIn[5];
    inv[15] = matrixIn[0] * matrixIn[5] * matrixIn[10] - matrixIn[0] * matrixIn[6] * matrixIn[9] - matrixIn[4] * matrixIn[1] * matrixIn[10] + matrixIn[4] * matrixIn[2] * matrixIn[9] + matrixIn[8] * matrixIn[1] * matrixIn[6] - matrixIn[8] * matrixIn[2] * matrixIn[5];

    det = matrixIn[0] * inv[0] + matrixIn[1] * inv[4] + matrixIn[2] * inv[8] + matrixIn[3] * inv[12];

    if ( det < 0.001f && det > -0.001f )
    {
        return false;
    }

    det = 1.0f / det;

    for ( i = 0; i < 16; i++ )
    {
        matrixOut[i] = inv[i] * det;
    }

    return true;
}

//this code is from GLU's MultiplyMatrices4by4OpenGL_FLOAT(), although the parameters have been renamed
void RenderManager::MultiplyMatricesGL( const float matrixInA[16], const float matrixInB[16], float matrixOut[16] ) const
{
    matrixOut[0] = matrixInA[0] * matrixInB[0] + matrixInA[4] * matrixInB[1] + matrixInA[8] * matrixInB[2] + matrixInA[12] * matrixInB[3];
    matrixOut[4] = matrixInA[0] * matrixInB[4] + matrixInA[4] * matrixInB[5] + matrixInA[8] * matrixInB[6] + matrixInA[12] * matrixInB[7];
    matrixOut[8] = matrixInA[0] * matrixInB[8] + matrixInA[4] * matrixInB[9] + matrixInA[8] * matrixInB[10] + matrixInA[12] * matrixInB[11];
    matrixOut[12] = matrixInA[0] * matrixInB[12] + matrixInA[4] * matrixInB[13] + matrixInA[8] * matrixInB[14] + matrixInA[12] * matrixInB[15];
    matrixOut[1] = matrixInA[1] * matrixInB[0] + matrixInA[5] * matrixInB[1] + matrixInA[9] * matrixInB[2] + matrixInA[13] * matrixInB[3];
    matrixOut[5] = matrixInA[1] * matrixInB[4] + matrixInA[5] * matrixInB[5] + matrixInA[9] * matrixInB[6] + matrixInA[13] * matrixInB[7];
    matrixOut[9] = matrixInA[1] * matrixInB[8] + matrixInA[5] * matrixInB[9] + matrixInA[9] * matrixInB[10] + matrixInA[13] * matrixInB[11];
    matrixOut[13] = matrixInA[1] * matrixInB[12] + matrixInA[5] * matrixInB[13] + matrixInA[9] * matrixInB[14] + matrixInA[13] * matrixInB[15];
    matrixOut[2] = matrixInA[2] * matrixInB[0] + matrixInA[6] * matrixInB[1] + matrixInA[10] * matrixInB[2] + matrixInA[14] * matrixInB[3];
    matrixOut[6] = matrixInA[2] * matrixInB[4] + matrixInA[6] * matrixInB[5] + matrixInA[10] * matrixInB[6] + matrixInA[14] * matrixInB[7];
    matrixOut[10] = matrixInA[2] * matrixInB[8] + matrixInA[6] * matrixInB[9] + matrixInA[10] * matrixInB[10] + matrixInA[14] * matrixInB[11];
    matrixOut[14] = matrixInA[2] * matrixInB[12] + matrixInA[6] * matrixInB[13] + matrixInA[10] * matrixInB[14] + matrixInA[14] * matrixInB[15];
    matrixOut[3] = matrixInA[3] * matrixInB[0] + matrixInA[7] * matrixInB[1] + matrixInA[11] * matrixInB[2] + matrixInA[15] * matrixInB[3];
    matrixOut[7] = matrixInA[3] * matrixInB[4] + matrixInA[7] * matrixInB[5] + matrixInA[11] * matrixInB[6] + matrixInA[15] * matrixInB[7];
    matrixOut[11] = matrixInA[3] * matrixInB[8] + matrixInA[7] * matrixInB[9] + matrixInA[11] * matrixInB[10] + matrixInA[15] * matrixInB[11];
    matrixOut[15] = matrixInA[3] * matrixInB[12] + matrixInA[7] * matrixInB[13] + matrixInA[11] * matrixInB[14] + matrixInA[15] * matrixInB[15];
}

void RenderManager::SetToOrthogonalProjection( const EngineConfig &engineCfg ) const
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0.0, (double) engineCfg.GetActiveWidth(), (double) engineCfg.GetActiveHeight(), 0.0, -1.0, 1.0);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void RenderManager::SetToPerspectiveProjection( const EngineConfig &engineCfg ) const
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( (float) engineCfg.GetActiveHeight() / (float) engineCfg.GetActiveWidth() * (float) engineCfg.GetFOV(), (float) engineCfg.GetActiveWidth() / (float) engineCfg.GetActiveHeight(), 0.1f, 500.0f );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void RenderManager::StartRenderToFBO( const EngineConfig &engineCfg ) const
{
    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, m_fbo );
	glPushAttrib( GL_VIEWPORT_BIT );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); //clear the FBO

	glActiveTextureARB( GL_TEXTURE0 );
	glEnable( GL_TEXTURE_2D );

	// Specify what to render and start acquiring
	GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT };
	glDrawBuffers(2, buffers);
}

void RenderManager::StopRenderToFBO() const
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glPopAttrib();
}

void RenderManager::Render( const Simulation &gameSim, const EngineConfig &engineCfg ) const
{
    SetToPerspectiveProjection( engineCfg );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); //clear the screen buffer
    glUseProgramObjectARB( deferredShadingShader.GetProgramHandler() );

    glDepthMask( GL_TRUE ); //enable writing to the depth buffer
    glEnable( GL_DEPTH_TEST );

    StartRenderToFBO( engineCfg );

    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );

    //bind the surface texture and pass it to the shader
    glBindTexture( GL_TEXTURE_2D, m_testTexture );
    glUniform1i( m_testTextureID, 0);

    glPushMatrix();

        gameSim.RenderLit();

        int viewportParams[4];
        float modelViewParams[16];
        float projectionParams[16];
        float perspectiveMatrix[16];

        glGetIntegerv( GL_VIEWPORT, viewportParams );
        glGetFloatv( GL_MODELVIEW_MATRIX, modelViewParams );
        glGetFloatv( GL_PROJECTION_MATRIX, projectionParams );
        MultiplyMatricesGL( projectionParams, modelViewParams, perspectiveMatrix );
        InvertMatrixGL( perspectiveMatrix, perspectiveMatrix );

    glPopMatrix();

    StopRenderToFBO();

    //glDisable( GL_CULL_FACE );

    glDepthMask( GL_FALSE ); //disable writing to the depth buffer
    glDisable( GL_DEPTH_TEST );

    glUseProgramObjectARB( deferredRenderingShader.GetProgramHandler() );

	glActiveTextureARB( GL_TEXTURE0_ARB );
	glBindTexture( GL_TEXTURE_2D, m_normalsTexture );
	glUniform1iARB( m_normalsID, 0 );

	glActiveTextureARB( GL_TEXTURE1_ARB );
	glBindTexture( GL_TEXTURE_2D, m_diffuseTexture );
	glUniform1iARB( m_diffuseID, 1 );

	glActiveTextureARB( GL_TEXTURE2_ARB );
	glBindTexture( GL_TEXTURE_2D, m_depthTexture );
	glUniform1iARB( m_depthID, 2 );

    glUniform4ivARB( m_viewportParamsID, 4, viewportParams );
    glUniformMatrix4fvARB( m_perspectiveMatrixID, 16, false, perspectiveMatrix );

    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f);

    glEnable( GL_STENCIL_TEST );
    glClearStencil( 0 );

    const vector<Light> staticLights = gameSim.GetStaticLights();

    for ( auto lightIt : staticLights )
    {
        SetToPerspectiveProjection( engineCfg );

        glUseProgramObjectARB( 0 );

        glColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE ); //disable writing to the color buffer
        glStencilMask( 0xFF ); //enable writing to the stencil buffer

        glClear( GL_STENCIL_BUFFER_BIT );

        glStencilFunc( GL_NEVER, 1, 0xFF ); // never pass stencil test
        glStencilOp( GL_REPLACE, GL_KEEP, GL_KEEP );  // replace stencil buffer values to ref=1

        glPushMatrix();
            //transform to camera position/rotation
            glRotatef( -gameSim.GetCamera().GetRotation().GetX(), 1.0f, 0.0f, 0.0f );
            glRotatef( -gameSim.GetCamera().GetRotation().GetY(), 0.0f, 1.0f, 0.0f );
            glTranslatef( -gameSim.GetCamera().GetPosition().GetX(), -gameSim.GetCamera().GetPosition().GetY(), -gameSim.GetCamera().GetPosition().GetZ() );

            glPushMatrix();
                //render light at correct location and scale
                glTranslatef( lightIt.GetPosition().GetX(), lightIt.GetPosition().GetY(), lightIt.GetPosition().GetZ() );
                glScalef( lightIt.GetRadius(), lightIt.GetRadius(), lightIt.GetRadius() );
                glDisable( GL_CULL_FACE );
                glCallList( icosphere );
            glPopMatrix();

            //enable depth test (and use depth from the FBO)
            glEnable( GL_CULL_FACE );
            glCullFace( GL_FRONT );
            //increment of depth fail
            lightIt.RenderShadowVolumes();
            glCullFace( GL_BACK );
            //decrement of depth fail
            lightIt.RenderShadowVolumes();

        glPopMatrix();

        glStencilFunc( GL_EQUAL, 1, 0xFF );

        glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE ); //enable writing to the color buffer
        glStencilMask( 0x00 ); //disable writing to the stencil buffer

        SetToOrthogonalProjection( engineCfg );

        glUseProgramObjectARB( deferredRenderingShader.GetProgramHandler() );

        //pass the light's attributes to the shader
        glUniform3fARB( m_lightPositionID, lightIt.GetPosition().GetX(), lightIt.GetPosition().GetY(), lightIt.GetPosition().GetZ() );
        glUniform3fARB( m_lightColorID, lightIt.GetColor().GetX(), lightIt.GetColor().GetY(), lightIt.GetColor().GetZ() );
        glUniform1fARB( m_lightLinearAttenuationID, lightIt.GetLinearAttenuation() );
        glUniform1fARB( m_lightQuadraticAttenuationID, lightIt.GetQuadraticAttenuation() );

        glDisable( GL_CULL_FACE );

        //enable blending so that each new quad adds to whatever's in the render buffer
        glEnable( GL_BLEND );
        glBlendFunc( GL_ONE, GL_ONE );

        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f);
            glVertex2f(0.0f, 0.0f);
            glTexCoord2f(0.0f, 0.0f);
            glVertex2f(0.0f, (float) engineCfg.GetActiveHeight());
            glTexCoord2f(1.0f, 0.0f);
            glVertex2f( (float) engineCfg.GetActiveWidth(), (float) engineCfg.GetActiveHeight() );
            glTexCoord2f(1.0f, 1.0f);
            glVertex2f( (float) engineCfg.GetActiveWidth(), 0.0f );
        glEnd();

        glDisable(GL_BLEND);
    }

    glDisable(GL_STENCIL_TEST );

    // Reset OpenGL state
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTextureARB(GL_TEXTURE2_ARB);
	glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgramObjectARB(0);

    //change to perspective projection
	//enable depth test
	//enable depth mask
	//draw projectiles

    //change to orthogonal projection
	//disable depth test
	//disable depth mask
	//draw HUD
	//draw UI
}

void RenderManager::SetupOpenGL( const EngineConfig &engineCfg ) const
{
    glewInit();
    glViewport( 0, 0, engineCfg.GetActiveWidth(), engineCfg.GetActiveHeight() );
    SetToPerspectiveProjection( engineCfg );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
}

RenderManager::RenderManager( const EngineConfig &engineCfg )
{
    SetupOpenGL( engineCfg );
    deferredShadingShader.Load( "../data/shaders/deferredShading.vert", "../data/shaders/deferredShading.frag" );
    deferredRenderingShader.Load( "../data/shaders/deferredRendering.vert", "../data/shaders/deferredRendering.frag" );

    // Generate the OGL resources for what we need
	glGenFramebuffersEXT(1, &m_fbo);
	glGenRenderbuffersEXT(1, &m_normalsRT);
	glGenRenderbuffersEXT(1, &m_diffuseRT);
	glGenRenderbuffersEXT(1, &m_depthRT );

    // Bind the FBO so that the next operations will be bound to it
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);

	// Bind the normal render target
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_normalsRT);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGB8, engineCfg.GetActiveWidth(), engineCfg.GetActiveHeight());
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, m_normalsRT);

    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_diffuseRT);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGB8, engineCfg.GetActiveWidth(), engineCfg.GetActiveHeight());
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_RENDERBUFFER_EXT, m_diffuseRT);

	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_depthRT);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, engineCfg.GetActiveWidth(), engineCfg.GetActiveHeight());
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
	m_testTextureID = glGetUniformLocationARB(deferredShadingShader.GetProgramHandler(), "surfaceTexture");

	// Get the handles from the shader
	m_normalsID = glGetUniformLocationARB( deferredRenderingShader.GetProgramHandler(), "normalsTexture" );
	m_diffuseID = glGetUniformLocationARB( deferredRenderingShader.GetProgramHandler(), "diffuseTexture" );
	m_depthID = glGetUniformLocationARB( deferredRenderingShader.GetProgramHandler(), "depthTexture" );

	m_viewportParamsID = glGetUniformLocationARB( deferredRenderingShader.GetProgramHandler(), "viewportParams" );
	m_perspectiveMatrixID = glGetUniformLocationARB( deferredRenderingShader.GetProgramHandler(), "perspectiveMatrix" );

	m_lightPositionID = glGetUniformLocationARB( deferredRenderingShader.GetProgramHandler(), "lightPosition" );
	m_lightColorID = glGetUniformLocationARB( deferredRenderingShader.GetProgramHandler(), "lightColor" );
	m_lightLinearAttenuationID = glGetUniformLocationARB( deferredRenderingShader.GetProgramHandler(), "lightLinearAttenuation" );
    m_lightQuadraticAttenuationID = glGetUniformLocationARB( deferredRenderingShader.GetProgramHandler(), "lightQuadraticAttenuation" );



	icosphere = IcosphereGenerator::GenerateIcosphereDisplayList( 1 );
}

RenderManager::~RenderManager()
{
    glDeleteTextures(1, &m_testTexture);
    glDeleteTextures(1, &m_normalsTexture);
    glDeleteTextures(1, &m_diffuseTexture);
    glDeleteTextures(1, &m_depthTexture );
	glDeleteFramebuffersEXT(1, &m_fbo);
	glDeleteRenderbuffersEXT(1, &m_normalsRT);
	glDeleteRenderbuffersEXT(1, &m_diffuseRT);
	glDeleteRenderbuffersEXT(1, &m_depthRT);
}
