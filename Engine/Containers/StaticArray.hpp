#pragma once

#include "Engine/engine.hpp"

namespace orion
{
	template<typename ElementType, Size_t Size>
	class StaticArray
	{
	public:
		using element_type = ElementType;

		const Size_t size {Size};

		explicit StaticArray(const ElementType& default_element = ElementType{});		
		
		[[nodiscard]] ElementType& operator[](Size_t index) noexcept;
		[[nodiscard]] ElementType operator[](Size_t index) const noexcept;
	private:
		element_type buffer[Size];
	};


	template <typename ElementType, Size_t Size>
	StaticArray<ElementType, Size>::StaticArray(const ElementType& default_element)
	{
		for (auto& element : buffer)
		{
			element = default_element;
		}
	}

	template <typename ElementType, Size_t Size>
	ElementType& StaticArray<ElementType, Size>::operator[](const Size_t index) noexcept
	{
		ORION_ASSERT(index < size);
		
		return buffer[index];
	}

	template <typename ElementType, Size_t Size>
	ElementType StaticArray<ElementType, Size>::operator[](const Size_t index) const noexcept
	{
		ORION_ASSERT(index < size);
		
		return buffer[index];
	}

	/* Operators */
	template<typename ElementType, Size_t Size>
	Bool operator==(const StaticArray<ElementType, Size>& lhs, const StaticArray<ElementType, Size>& rhs) noexcept
	{
		for (Size_t index = 0; index != Size; ++index)
		{
			if (lhs[index] != rhs[index])
				return false;
		}
		
		return true;
	}
	
	template<typename ElementType, Size_t Size>
	Bool operator!=(const StaticArray<ElementType, Size>& lhs, const StaticArray<ElementType, Size>& rhs) noexcept
	{
		return !(lhs == rhs);
	}
}
