#version 150

uniform sampler2D depthTexture;

void main( void )
{
	gl_FragDepth = texture2D( depthTexture, gl_TexCoord[0].st );
}

