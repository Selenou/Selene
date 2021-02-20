#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec2 a_Normal;
layout(location = 3) in uint a_CustomFlags;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;
uniform sampler2D u_Texture;

out vec3 v_TexCoord;
out float v_LightFactor;

float computeLightFactor()
{
	float result;

	if(a_Normal.y > 0) // top face
		result = 1.0f;
	else if(a_Normal.y < 0) // bottom face
		result = 0.4f;
	else if(a_Normal.x < 0) // left face
		result = 0.55f;
	else if(a_Normal.x > 0) // right face
		result = 0.85f;
	else // front & back face
		result = 0.7f;

	return result;
}

void main()
{
	int blockType = int(a_CustomFlags);
	v_TexCoord = vec3(a_TexCoord, blockType-1);
	v_LightFactor = computeLightFactor();
	gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);	
}