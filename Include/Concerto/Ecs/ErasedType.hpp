//
// Created by arthur on 17/10/22.
//

#ifndef CONCERTO_ERASEDTYPE_HPP
#define CONCERTO_ERASEDTYPE_HPP

#include <typeinfo>
#include <utility>

#include <Concerto/Core/Types.hpp>

#include "Concerto/Ecs/Component.hpp"

namespace Concerto
{
	template <typename T>
	class ErasedTypeImpl
	{
	public:
		template<typename... Args>
		explicit ErasedTypeImpl(Args&& ...args) :_data(std::forward<Args>(args)...) { }

		explicit ErasedTypeImpl(T& data) : _data(data) { }

		explicit ErasedTypeImpl(T&& data) :	_data(std::move(data)) { }

		~ErasedTypeImpl() = default;

		ErasedTypeImpl& operator=(const ErasedTypeImpl& other)
		{
			_data = other._data;
			return *this;
		}

		ErasedTypeImpl& operator=(ErasedTypeImpl&& other) noexcept
		{
			_data = std::move(other._data);
			return *this;
		}

		T* operator->()
		{
			return &_data;
		}
	private:
		T _data;
	};

	class ErasedType
	{
	public:
		ErasedType() = delete;
		~ErasedType() = default;

	private:
		explicit ErasedType(ComponentHelper::Id id, std::unique_ptr<void*> data) : _id(id), _data(std::move(data)) {}

	public:
		template<typename T>
		bool Is() const
		{
			return _id == ComponentHelper::GetId<T>();
		}

		template<typename T>
		T As()
		{
			using RawType = std::remove_reference_t<std::remove_pointer_t<T>>;
			if (_id != ComponentHelper::GetId<typename std::remove_const<RawType>::type>())
			{
				CONCERTO_ASSERT_FALSE; // Trying to cast to a wrong type
				throw std::bad_cast();
			}
			auto* erasedType = static_cast<ErasedTypeImpl<RawType>*>(*_data.get());
			RawType* data = erasedType->operator->();
			return static_cast<T>(*data);
		}

		template<typename T, class... Args>
		static inline ErasedType Make(Args&&... args)
		{
			using RawType = std::remove_reference_t<std::remove_pointer_t<T>>;
			auto data = std::make_unique<void*>(new ErasedTypeImpl<T>(std::forward<Args>(args)...));
			return ErasedType(ComponentHelper::GetId<typename std::remove_const<RawType>::type>(), std::move(data));
		}

	private:
		ComponentHelper::Id _id;
		std::unique_ptr<void*> _data;
	};
}
#endif //CONCERTO_ERASEDTYPE_HPP