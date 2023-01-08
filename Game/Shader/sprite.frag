#version 330 core

uniform sampler2D image;
uniform sampler2D normals;
uniform vec3 spriteColor;

//attributes from vertex shader
in vec2 TexCoords;
out vec4 color;

//values used for shading algorithm...
uniform vec2 Resolution;      //resolution of screen

#define MAX_LIGHTS 10
uniform int uLightCount;
uniform vec3 uLightsPos[MAX_LIGHTS];
uniform vec4 uLightColor[MAX_LIGHTS];      //light RGBA -- alpha is intensity

uniform vec4 AmbientColor;    //ambient RGBA -- alpha is intensity 
uniform vec3 Falloff;         //attenuation coefficients

void main()
{
	vec3 Sum = vec3(0.0);

	for(int i=0; i < uLightCount; ++i)
	{
		vec3 NormalMap = vec3(1);//texture2D(normals, TexCoords).rgb;
		vec3 LightPos = uLightsPos[i];
		
		//The delta position of light
		vec3 LightDir = vec3(LightPos.xy - (gl_FragCoord.xy / Resolution.xy), LightPos.z);

		//Correct for aspect ratio
		LightDir.x *= Resolution.x / Resolution.y;

		//Determine distance (used for attenuation) BEFORE we normalize our LightDir
		float D = length(LightDir);

		//normalize our vectors
		vec3 N = normalize(NormalMap * 2.0 - 1.0);

		vec4 LightColor = uLightColor[i];
		//Pre-multiply light color with intensity
		//Then perform "N dot L" to determine our diffuse term
		vec3 Diffuse = (LightColor.rgb * LightColor.a) * max(dot(N, vec3(1)), 0.0);

		//pre-multiply ambient color with intensity
		vec3 Ambient = AmbientColor.rgb * AmbientColor.a;

		//calculate attenuation
		float Attenuation = 1.0 / ( Falloff.x + (Falloff.y*D) + (Falloff.z*D*D) );

		//the calculation which brings it all together
		vec3 Intensity = Ambient + Diffuse * Attenuation;

		vec4 DiffuseColor = vec4(spriteColor, 1.0);
		vec3 FinalColor = DiffuseColor.rgb * Intensity;
		Sum += FinalColor;
	}

	color = texture(image, TexCoords) * vec4(Sum, 1);
}  