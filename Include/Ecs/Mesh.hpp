//
// Created by arthur on 01/08/2022.
//

#ifndef CONCERTO_MESH_HPP
#define CONCERTO_MESH_HPP
#include <string>

namespace Concerto::Ecs
{
	struct Mesh
	{
		std::string modelPath;
		std::string texturePath;
	};
}
#endif //CONCERTO_MESH_HPP
