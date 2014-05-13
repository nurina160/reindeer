/*
 * BoxObject.cpp
 *
 *  Created on: May 2, 2014
 *      Author: MRP
 */

#include "BoxObject.h"
#include <GL/glm/gtc/type_ptr.hpp>

BoxObject::BoxObject() {
	vertices[0] = glm::vec3(-3,  3, -3);
	vertices[1] = glm::vec3( 3,  3, -3);
	vertices[2] = glm::vec3( 3,  3,  3);
	vertices[3] = glm::vec3(-3,  3,  3);
	vertices[4] = glm::vec3(-3, -3, -3);
	vertices[5] = glm::vec3( 3, -3, -3);
	vertices[6] = glm::vec3( 3, -3,  3);
	vertices[7] = glm::vec3(-3, -3,  3);

	normals[0] = glm::vec3( 0,  1,  0);
	normals[1] = glm::vec3( 0, -1,  0);
	normals[2] = glm::vec3( 0,  0, -1);
	normals[3] = glm::vec3( 1,  0,  0);
	normals[4] = glm::vec3( 0,  0,  1);
	normals[5] = glm::vec3(-1,  0,  0);

	short indices[] =
	{
		1, 0, 2,    // side 1
		2, 0, 3,
		5, 4, 6,    // side 2
		6, 4, 7,
		0, 1, 4,    // side 3
		4, 1, 5,
		1, 2, 5,    // side 4
		5, 2, 6,
		2, 3, 6,    // side 5
		6, 3, 7,
		3, 0, 7,    // side 6
		7, 0, 4,
	};
	memcpy(this->indices, indices, sizeof(indices));
}

BoxObject::~BoxObject() {
}

void BoxObject::Draw(Camera& camera) {

	glMatrixMode(GL_PROJECTION);
	glm::mat4 projection = camera.GetProjection();
	glLoadMatrixf(glm::value_ptr(projection));

	glMatrixMode(GL_MODELVIEW);
	glm::mat4 modelview = camera.GetView() * world;
	glLoadMatrixf(glm::value_ptr(modelview));

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 36;) {
		glNormal3fv(glm::value_ptr(normals[i / 6]));
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		glVertex3fv(glm::value_ptr(vertices[indices[i++]]));
		glVertex3fv(glm::value_ptr(vertices[indices[i++]]));
		glVertex3fv(glm::value_ptr(vertices[indices[i++]]));

		glVertex3fv(glm::value_ptr(vertices[indices[i++]]));
		glVertex3fv(glm::value_ptr(vertices[indices[i++]]));
		glVertex3fv(glm::value_ptr(vertices[indices[i++]]));
	}
	glEnd();
}
