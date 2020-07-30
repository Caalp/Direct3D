#include "Technique.h"
#include "Drawable.h"

#include "RenderGraph.h"

Technique::Technique(std::string techName, bool status) : techniqueName(techName), isActive(status)
{
}

Technique::Technique(std::string techName, size_t techChannel, bool status): techniqueName(techName), techniqueChannel(techChannel), isActive(status)
{

}

void Technique::Link(RenderGraph& rg)
{
	
		for (auto& s : steps)
		{
			s.Link(rg);
		}
	

}

void Technique::Submit(Drawable& d, size_t channel)
{
	for (auto& s : steps)
	{
		if (isActive && ((techniqueChannel & channel) != 0))
		{
			s.Submit(d);
		}
	}
}

void Technique::AddStep(Step& step)
{
	//assert(this->step == nullptr);
	steps.push_back(step);
}
