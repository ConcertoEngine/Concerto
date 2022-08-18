//
// Created by arthu on 01/08/2022.
//

#ifndef CONCERTO_ASYSTEM_HPP
#define CONCERTO_ASYSTEM_HPP
#include "ISystem.hpp"
#include "Config.hpp"
namespace Concerto::Ecs::System
{
	class ASystem : public ISystem
	{
	public:
		ASystem(const Config::Object &data) : _data(data) {}
	private:
		const Config::Object &_data;
	};
}
#endif //CONCERTO_ASYSTEM_HPP
