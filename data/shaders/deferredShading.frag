varying vec3 normals;
uniform sampler2D	tDiffuse;

void main( void )
{
	gl_FragData[0] = vec4(normals.xyz,0);
	if (texture2D(tDiffuse,gl_TexCoord[0].st).a < 0.1)
	{
		//gl_FragData[1] = vec4(1.0f, 0.0f, 0.0f, 0.0f);
		discard;
	}
	else
	{
		gl_FragData[1] = vec4(texture2D(tDiffuse,gl_TexCoord[0].st).rgb, 0);
	}
}
