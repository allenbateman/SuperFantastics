#include "../headers/Resources.h"

Resources::Resources()
{
}

uint32 Resources::getResourcePosition(ResourceType rt, const char * file)
{
	size_t size = m_Resources[rt].size();
	size_t i;

	uint32 resourceId = -1;

	for (i = 0; i < size; i++) {
		if (m_Resources[rt][i]->filePath == file) {
			resourceId = static_cast<uint32>(i);
			break;
		}
	}

	return i;
}

Resources::~Resources()
{
	/*for (int i = 0; i < RT_LAST; i++) {
		size_t rsize = mResources[i].size();

		for (size_t j = 0; j < rsize; j++) {
			delete mResources[i][j]->resource;
			delete mResources[i][j];
		}
	}*/
}