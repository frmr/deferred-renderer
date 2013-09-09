#version 150

uniform sampler2D tNormals; 
uniform sampler2D tDiffuse;
uniform sampler2D tDepth;

uniform ivec4 viewportParams;
uniform mat4 perspectiveMatrix;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightAttenuation;

vec3 unproject( in float winx, in float winy, in float winz)
{	
	//Transformation of normalized coordinates between -1 and 1
	vec4 inVec;
	inVec.x = ( winx - viewportParams.x ) / viewportParams.z * 2.0 - 1.0;
	inVec.y = ( winy - viewportParams.y ) / viewportParams.w * 2.0 - 1.0;
	inVec.z = 2.0 * winz - 1.0;
	inVec.w = 1.0;
	
	//Objects coordinates
	inVec = perspectiveMatrix * inVec;
	inVec.w = 1.0 / inVec.w;
	
	return inVec.xyz * inVec.w;
}

void main( void )
{
	float depth = texture2D( tDepth, gl_TexCoord[0].xy );
	
	if ( depth == 1.0f )
	{
		discard;
	}
	
	vec4 normal = texture2D( tNormals, gl_TexCoord[0].xy ) * 2.0 - 1.0; //unpack normals into the range -1 to 1
	vec4 texColor = texture2D( tDiffuse, gl_TexCoord[0].xy );
	
	vec3 fragPosition = unproject( gl_FragCoord.x, gl_FragCoord.y, depth );

	if ( dot( normalize( lightPosition - fragPosition ), normal.xyz ) >= 0.0 )
	{
		discard;
	}
	
	gl_FragColor = vec4( texColor.xyz * lightColor / ( distance( fragPosition.xyz, lightPosition ) * lightAttenuation ), 0.0f );
}

