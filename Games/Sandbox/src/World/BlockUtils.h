#pragma once

namespace Sandbox
{
	enum class BlockType
	{
		Air = 0,
		Grass,
		Dirt,
		Sand,
		Gravel,
		Snow
	};

	enum Direction
	{
		Front = 0,
		Back,
		Left,
		Right,
		Top,
		Bottom,
		None
	};

	struct Block
	{
		BlockType BlockType;
	};

	struct BlockFaces 
	{ 
		static inline constexpr std::array<float, 30> FrontFaceVertices =
		{
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f
		};

		static inline constexpr std::array<float, 30> BackFaceVertices =
		{
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f
		};

		static inline constexpr std::array<float, 30> LeftFaceVertices =
		{

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f
		};

		static inline constexpr std::array<float, 30> RightFaceVertices =
		{
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f
		};

		static inline constexpr std::array<float, 30> TopFaceVertices =
		{
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f
		};

		static inline constexpr std::array<float, 30> BottomFaceVertices =
		{
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f
		};
	
		static inline constexpr std::array<float, 30> Faces[6] =
		{
			FrontFaceVertices,
			BackFaceVertices,
			LeftFaceVertices,
			RightFaceVertices,
			TopFaceVertices,
			BottomFaceVertices
		};
	};	
};