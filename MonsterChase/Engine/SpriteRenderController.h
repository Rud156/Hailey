#pragma once
#include <vector>

namespace Core
{
	namespace BaseComponents
	{
		class Node;
	}
}

namespace sf
{
	class RenderWindow;
}

namespace Core::Controllers::Rendering
{
	class SpriteRenderController
	{
	private:
		std::vector<BaseComponents::Node*> _nodes;

		static bool CompareRenderOrder(BaseComponents::Node* i_a,
		                               BaseComponents::Node* i_b);
		void SortRenderer();

	public:
		// Constructor/Destructor
		SpriteRenderController();
		~SpriteRenderController();

		void AddNodeRenderer(BaseComponents::Node* i_node);
		void RemoveNodeRender(BaseComponents::Node* i_node);
		void RenderNodes(sf::RenderWindow* i_window);
	};
}
