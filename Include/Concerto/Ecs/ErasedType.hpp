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
	class ErasedType
	{
	public:
		ErasedType() = delete;
		virtual ~ErasedType();

	protected:
		explicit ErasedType(ComponentHelper::Id id, void *data) : _id(id), _ptr(data) {}

	public:
		template<typename T>
		bool Is() const
		{
			return _id == ComponentHelper::GetId<T>();
		}

		template<typename T>
		T As()
		{
			using RawType = std::remove_reference_t<std::remove_pointer_t<T>> ;
			if (_id != ComponentHelper::GetId<typename std::remove_const<RawType>::type>())
			{
				CONCERTO_ASSERT_FALSE; // Trying to cast to a wrong type
				throw std::bad_cast();
			}
			return static_cast<T>(*static_cast<RawType*>(_ptr));
		}

	protected:
		void* _ptr;
		ComponentHelper::Id _id;
	};

	inline ErasedType::~ErasedType() = default;

	template <typename T>
	class ErasedTypeImpl : public ErasedType
	{
	public:
		template<typename... Args>
		explicit ErasedTypeImpl(Args&& ...args) :
			ErasedType(ComponentHelper::GetId<T>(), &_data),
			_data(std::forward<Args>(args)...)
		{
		}

		explicit ErasedTypeImpl(T& data) :
			ErasedType(ComponentHelper::GetId<T>(), &_data),
			_data(data)
		{
		}

		explicit ErasedTypeImpl(T&& data) :
			ErasedType(ComponentHelper::GetId<T>(), &_data),
			_data(std::move(data))
		{
		}

		~ErasedTypeImpl() override = default;

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

	private:
		T _data;
	};

	template<typename T, class... Args>
	inline ErasedType MakeErasedType(Args&&... args)
	{
		return std::move(ErasedTypeImpl<T>(std::forward<Args>(args)...));
	}
}
#endif //CONCERTO_ERASEDTYPE_HPP