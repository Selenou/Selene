#pragma once

namespace Selene
{
	enum class DataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t GetDataTypeSize(DataType type)
	{
		switch (type)
		{
			case DataType::Float:   return 4;
			case DataType::Float2:	return 4 * 2;
			case DataType::Float3:  return 4 * 3;
			case DataType::Float4:  return 4 * 4;
			case DataType::Mat3:    return 4 * 3 * 3;
			case DataType::Mat4:    return 4 * 4 * 4;
			case DataType::Int:     return 4;
			case DataType::Int2:    return 4 * 2;
			case DataType::Int3:    return 4 * 3;
			case DataType::Int4:    return 4 * 4;
			case DataType::Bool:    return 1;
			default:				SLN_ENGINE_ASSERT(false, "Unknown DataType!");
		}
		return 0;
	}

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	struct VertexBufferElement
	{
		std::string Name;
		DataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		VertexBufferElement(const std::string& name, DataType type, bool normalized = false)
			: Name(name), Type(type), Size(GetDataTypeSize(type)), Offset(0), Normalized(normalized)
		{}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case DataType::Float:	return 1;
				case DataType::Float2:  return 2;
				case DataType::Float3:  return 3;
				case DataType::Float4:  return 4;
				case DataType::Mat3:    return 3 * 3;
				case DataType::Mat4:    return 4 * 4;
				case DataType::Int:     return 1;
				case DataType::Int2:    return 2;
				case DataType::Int3:    return 3;
				case DataType::Int4:    return 4;
				case DataType::Bool:    return 1;
				default:				SLN_ENGINE_ASSERT(false, "Unknown DataType!");
			}

			return 0;
		}
	};

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout(const std::initializer_list<VertexBufferElement>& elements);
		uint32_t GetStride() const { return m_Stride; }
	public:
		std::vector<VertexBufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<VertexBufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<VertexBufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<VertexBufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void ComputeLayoutStride();
		void ComputeElementsOffset();
	private:
		std::vector<VertexBufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;
	public:
		static std::shared_ptr<VertexBuffer> Create(void* data, uint32_t size);
		virtual uint32_t GetID() = 0;
		void SetLayout(VertexBufferLayout& layout) { m_Layout = &layout; }
		VertexBufferLayout* GetLayout() { return m_Layout; }
	protected:
		VertexBufferLayout* m_Layout;
	};

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;
	public:
		static std::shared_ptr<IndexBuffer> Create(void* data, uint32_t size);
		virtual uint32_t GetCount() const = 0;
		virtual uint32_t GetID() = 0;
	};
}