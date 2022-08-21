//
// Created by arthur on 19/08/2022.
//

#ifndef CONCERTO_NAZARAEVENT_HPP
#define CONCERTO_NAZARAEVENT_HPP
namespace Nz
{
	class RenderWindow;
}
namespace Concerto::Ecs::System
{
	class NazaraRenderer;
	class NazaraEvent
	{
	public:
		NazaraEvent(Nz::RenderWindow &renderWindow);
	private:
		friend class NazaraRenderer;
		Nz::RenderWindow &_renderWindow;
	};

} // Concerto

#endif //CONCERTO_NAZARAEVENT_HPP
