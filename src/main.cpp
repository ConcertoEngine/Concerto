#include <iostream>

#include "ecs/Registry.hpp"
#include <string>

int main(int argc, char** argv)
{
	using namespace Concerto::Ecs;
	Registry r;
	auto entity = r.createEntity();
	auto str = r.emplaceComponent<std::string>(entity, "x");
	std::cout << str << std::endl;
	r.removeComponent<std::string>(entity);
}
