//
// Created by arthur on 16/11/2023.
//

#include <Concerto/Core/Types.hpp>

#ifdef CONCERTO_ENGINE_ECS_BUILD
    #define CONCERTO_ENGINE_ECS_API CONCERTO_EXPORT
#else
    #define CONCERTO_ENGINE_ECS_API CONCERTO_IMPORT
#endif