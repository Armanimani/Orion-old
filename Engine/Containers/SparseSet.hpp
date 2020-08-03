#pragma once

#include "Engine/engine.hpp"

#include <vector>

namespace orion
{
	template<typename T>
	class SparseSet
	{
	public:
		using element_type = T;
		using size_type = std::size_t;

		using iterator = typename std::vector<T>::iterator;
		using reverse_iterator = typename std::vector<T>::reverse_iterator;
		using const_iterator = typename std::vector<T>::const_iterator;
		using const_reverse_iterator = typename std::vector<T>::const_reverse_iterator;

		static const std::size_t k_element_size = sizeof(T);

		explicit SparseSet(size_type capacity);

		template<typename... Args>
		void construct(size_type index, Args&&... args) noexcept;

		void emplace(size_type index, element_type&& element) noexcept;

		void erase(size_type index) noexcept;

		void clear();

		[[nodiscard]] size_type capacity() const noexcept;
		[[nodiscard]] size_type size() const noexcept;
		[[nodiscard]] size_type sizeInBytes() const noexcept;

		[[nodiscard]] Bool hasElement(size_type index);

		[[nodiscard]] element_type* getElementPointer(size_type index) noexcept;
		[[nodiscard]] const element_type* getElementPointer(size_type index) const noexcept;

		[[nodiscard]] element_type& getElement(size_type index) noexcept;
		[[nodiscard]] const element_type& getElement(size_type index) const noexcept;

		[[nodiscard]] iterator begin() noexcept;
		[[nodiscard]] iterator end() noexcept;

		[[nodiscard]] const_iterator cbegin() const noexcept;
		[[nodiscard]] const_iterator cend() const noexcept;

		[[nodiscard]] reverse_iterator rbegin() const noexcept;
		[[nodiscard]] reverse_iterator rend() const noexcept;
	private:
		std::vector<element_type> dense {};
		std::vector<element_type*> sparse {};
	};


	template <typename T>
	SparseSet<T>::SparseSet(const size_type capacity)
	{
		dense.reserve(capacity);
		sparse.reserve(capacity);
		sparse.assign(capacity, nullptr);
	}

	template <typename T>
	template <typename ... Args>
	void SparseSet<T>::construct(const size_type index, Args&&... args) noexcept
	{
		assert(size() < capacity());

		erase(index);
		dense.push_back(element_type {std::forward<Args>(args)...});
		sparse[index] = &(dense.back());
	}

	template <typename T>
	void SparseSet<T>::emplace(const size_type index, element_type&& element) noexcept
	{
		assert(size() < capacity());

		erase(index);
		dense.push_back(std::move(element));
		sparse[index] = &(dense.back());
	}

	template <typename T>
	void SparseSet<T>::erase(const size_type index) noexcept
	{
		if (!hasElement(index))
			return;

		const auto item_address = sparse[index];
		const auto back_address = &dense.back();
		std::swap(*item_address, *back_address);

		auto address_to_be_updated = std::find(sparse.begin(), sparse.end(), back_address);
		*address_to_be_updated = item_address;

		sparse[index] = nullptr;
		dense.pop_back();
	}

	template <typename T>
	void SparseSet<T>::clear()
	{
		dense.clear();
		sparse.clear();
	}

	template <typename T>
	typename SparseSet<T>::size_type SparseSet<T>::capacity() const noexcept
	{
		return dense.capacity();
	}

	template <typename T>
	typename SparseSet<T>::size_type SparseSet<T>::size() const noexcept
	{
		return dense.size();
	}

	template <typename T>
	typename SparseSet<T>::size_type SparseSet<T>::sizeInBytes() const noexcept
	{
		return dense.size() * k_element_size;
	}

	template <typename T>
	Bool SparseSet<T>::hasElement(const size_type index)
	{
		return (index < sparse.size() && sparse[index]);
	}

	template <typename T>
	typename SparseSet<T>::element_type* SparseSet<T>::getElementPointer(const size_type index) noexcept
	{
		return sparse[index];
	}

	template <typename T>
	const typename SparseSet<T>::element_type* SparseSet<T>::getElementPointer(const size_type index) const noexcept
	{
		return sparse[index];
	}

	template <typename T>
	typename SparseSet<T>::element_type& SparseSet<T>::getElement(const size_type index) noexcept
	{
		assert(sparse[index]);

		return *sparse[index];
	}

	template <typename T>
	const typename SparseSet<T>::element_type& SparseSet<T>::getElement(const size_type index) const noexcept
	{
		assert(sparse[index]);

		return *sparse[index];
	}

	template <typename T>
	typename SparseSet<T>::iterator SparseSet<T>::begin() noexcept
	{
		return dense.begin();
	}

	template <typename T>
	typename SparseSet<T>::iterator SparseSet<T>::end() noexcept
	{
		return dense.end();
	}

	template <typename T>
	typename SparseSet<T>::const_iterator SparseSet<T>::cbegin() const noexcept
	{
		return dense.cbegin();
	}

	template <typename T>
	typename SparseSet<T>::const_iterator SparseSet<T>::cend() const noexcept
	{
		return dense.cend();
	}

	template <typename T>
	typename SparseSet<T>::reverse_iterator SparseSet<T>::rbegin() const noexcept
	{
		return dense.rbegin();
	}

	template <typename T>
	typename SparseSet<T>::reverse_iterator SparseSet<T>::rend() const noexcept
	{
		return dense.rend();
	}
}
