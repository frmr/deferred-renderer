#version 150

uniform sampler2D normalsTexture; 
uniform sampler2D diffuseTexture;
uniform sampler2D depthTexture;

uniform ivec4 viewportParams;
uniform mat4 perspectiveMatrix;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightLinearAttenuation;
uniform float lightQuadraticAttenuation;

vec3 unproject( in float winX, in float winY, in float winZ )
{	
	//Transformation of normalized coordinates between -1 and 1
	vec4 inVec;
	inVec.x = ( winX - viewportParams.x ) / viewportParams.z * 2.0 - 1.0;
	inVec.y = ( winY - viewportParams.y ) / viewportParams.w * 2.0 - 1.0;
	inVec.z = 2.0 * winZ - 1.0;
	inVec.w = 1.0;
	
	//Objects coordinates
	inVec = perspectiveMatrix * inVec;
	inVec.w = 1.0 / inVec.w;
	
	return inVec.xyz * inVec.w;
}

void main( void )
{
	float fragDepth = texture2D( depthTexture, gl_TexCoord[0].st );
	
	if ( fragDepth == 1.0f )
	{
		discard;
	}
	else
	{
		vec4 fragNormal = texture2D( normalsTexture, gl_TexCoord[0].st ) * 2.0 - 1.0; //unpack normals into the range -1 to 1
		vec4 fragDiffuse = texture2D( diffuseTexture, gl_TexCoord[0].st );
		
		vec3 fragPosition = unproject( gl_FragCoord.x, gl_FragCoord.y, fragDepth );

		//float lightDot = dot( normalize( fragPosition - lightPosition ), fragNormal.xyz );
		float lightDot = dot( normalize( lightPosition - fragPosition ), fragNormal.xyz );
		
		if ( lightDot <= 0.0 )
		{
			discard;
		}
		else
		{
			float dist = distance( fragPosition.xyz, lightPosition );
			gl_FragColor = vec4( fragDiffuse.rgb * lightDot * lightColor / ( dist * lightLinearAttenuation + dist * dist * lightQuadraticAttenuation ), 0.0f );
			//gl_FragColor = vec4( fragDiffuse.rgb * lightColor / ( dist * lightLinearAttenuation + dist * dist * lightQuadraticAttenuation ), 0.0f );
			//gl_FragColor = vec4( lightDot, 0.0, 0.0, 0.0 );
			//gl_FragColor = vec4( fragNormal.xyz, 0.0 );
			//gl_FragColor = vec4( fragDiffuse.rgb, 0.0 );
			//gl_FragColor = vec4( lightDot, 0.0, 0.0, 0.0 );
		}
	}
}