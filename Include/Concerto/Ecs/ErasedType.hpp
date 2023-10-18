//
// Created by arthur on 17/10/22.
//

#ifndef CONCERTO_ERASEDTYPE_HPP
#define CONCERTO_ERASEDTYPE_HPP

#include <typeinfo>
#include <utility>

#include "Concerto/Ecs/Component.hpp"

namespace Concerto
{
	class ErasedType
	{
	public:
		ErasedType() = delete;

	protected:
		explicit ErasedType(ComponentHelper::Id id, void *data) : _id(id), _data(data) {}
		virtual ~ErasedType() = 0;

	public:
		template<typename T>
		bool Is() const
		{
			return _id == ComponentHelper::GetId<T>();
		}

		template<typename T>
		T As()
		{
			if (_id != ComponentHelper::GetId<T>())
				throw std::bad_cast();
			using RawType = std::remove_reference_t<std::remove_pointer_t<T>> ;
			return static_cast<T>(*static_cast<RawType*>(_data));
		}

	protected:
		void* _data;
		ComponentHelper::Id _id;
	};

	ErasedType::~ErasedType() = default;

	template <typename T>
	class ErasedTypeImpl : public ErasedType
	{
	public:
		template<typename... Args>
		ErasedTypeImpl(Args&& ...args) :
			ErasedType(ComponentHelper::GetId<T>(), &_data),
			_data(std::forward<Args>(args)...)
		{
		}

		ErasedTypeImpl(T& data) :
			ErasedType(ComponentHelper::GetId<T>(), &_data),
			_data(data)
		{
		}

		ErasedTypeImpl(T&& data) :
			ErasedType(ComponentHelper::GetId<T>(), &_data),
			_data(std::move(data))
		{
		}

		~ErasedTypeImpl() {};

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
		return ErasedTypeImpl<T>(std::forward<Args>(args)...);
	}
}
#endif //CONCERTO_ERASEDTYPE_HPP