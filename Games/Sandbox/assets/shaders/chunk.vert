#version 330 core

///////////////////////////////////////////////////////////		
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in uint a_CustomFlags;
///////////////////////////////////////////////////////////
uniform mat4 u_ViewProjection;
uniform mat4 u_Model;
uniform sampler2D u_Texture;
///////////////////////////////////////////////////////////
out vec2 v_TexCoord;
out vec2 v_TileSize;
out vec2 v_TextureUV;
///////////////////////////////////////////////////////////
ivec2 textureAtlasSize = textureSize(u_Texture, 0);
float tileResolution = 32.0f;
float tileWidth = tileResolution / textureAtlasSize.x;
float tileHeight = tileResolution / textureAtlasSize.y;
///////////////////////////////////////////////////////////

vec2 GetTextureUVFromOffset(int x, int y)
{
  vec2 result;

  result.x = x * tileWidth;
  result.y = ((1/tileHeight) - 1 - y) * tileHeight;

  return result;
}

vec2 GetTextureUV(int blockType)
{
  switch (blockType)
  {
	case 1: return GetTextureUVFromOffset(0,0);		// Grass
	case 2: return GetTextureUVFromOffset(1,0);		// Dirt
	case 3: return GetTextureUVFromOffset(4,0);		// Sand
  }

  return vec2(0.0);
}

///////////////////////////////////////////////////////////

void main()
{
	int blockType = int(a_CustomFlags);
	v_TexCoord = a_TexCoord;
	v_TileSize = vec2(tileWidth, tileHeight);
	v_TextureUV = GetTextureUV(blockType);
	gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);	
}