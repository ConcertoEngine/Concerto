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
		explicit NazaraEvent(Nz::RenderWindow &renderWindow);
		void PollEvents(float deltaTime);
	private:
		friend class NazaraRenderer;
		Nz::RenderWindow &_window;
	};

} // Concerto

#endif //CONCERTO_NAZARAEVENT_HPP
