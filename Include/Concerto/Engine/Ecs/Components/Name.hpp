//
// Created by arthur on 13/01/2023.
//

#ifndef CONCERTO_NAME_HPP
#define CONCERTO_NAME_HPP

#include <string>
#include "Concerto/Engine/Export.hpp"

namespace Concerto
{
	struct CONCERTO_ENGINE_API Name
	{
		Name() = default;
		explicit Name(std::string name) : _name(std::move(name)) {}
		Name(const Name&) = default;
		Name(Name&&) = default;
		Name& operator=(const Name&) = default;
		Name& operator=(Name&&) = default;
		std::string _name;
	};
}
#endif //CONCERTO_NAME_HPP
