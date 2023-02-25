//
// Created by arthur on 18/05/22.
//

#ifndef CONCERTO_ENTITY_HPP
#define CONCERTO_ENTITY_HPP

#include <cstddef>
#include <exception>
#include <any>
#include <unordered_map>
#include <bitset>
#include <stdexcept>
#include "Component.hpp"

namespace Concerto::Ecs::Entity
{
	using Id = std::size_t;
}

#endif //CONCERTO_ENTITY_HPP