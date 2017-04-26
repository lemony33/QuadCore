#include "RayCast.h"

RayCast::RayCast()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer.ID);

	// Clear Picking Buffer (Should Be totally Black)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glDrawBuffer(GL_COLOR_ATTACHMENT1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// MRT: Render Into Both Layers
	unsigned int drawbuffers[] = { GL_COLOR_ATTACHMENT0 , GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, drawbuffers);
}

RayCast::~RayCast()
{
}
