#include "mesh.h"
#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


MeshData::MeshData(Vertex& vertices, int num)
{
	faceCount = num;
	memcpy(this->vertices, &vertices, num * sizeof(Vertex));

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Copy data from VBO to the GPU as static
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * num, &this->vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO);


	//Vertex position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);


	//Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//Texture Coordinate
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);


	//Diffuse
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	//Specular
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(11 * sizeof(float)));
	glEnableVertexAttribArray(4);


	//Reflectivity
	glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(14 * sizeof(float)));
	glEnableVertexAttribArray(5);


	//Brightness of the surface
	glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(15 * sizeof(float)));
	glEnableVertexAttribArray(6);
}

void MeshManager::CreateInstance(glm::vec3* worldPosRef, glm::vec3* rotationRef)
{
	MeshInstance newInstance = MeshInstance{
		worldPosRef,
		rotationRef
	};
}

MeshData::~MeshData()
{
	free(vertices);
}

void SceneManager::RenderScene()
{
	//Draw all non-light source objects
	for (int i = OpaqueMeshes.size() - 1; i >= 0; --i) {
		MeshManager* meshManager = &OpaqueMeshes[i];
		Shader* currentShader = meshManager->ShaderInUse;
		glBindVertexArray(meshManager->Mesh->VAO);
		currentShader->Use();
		for (int j = meshManager->MeshInstances.size() - 1; j >= 0; --j) {
			MeshInstance* instance = meshManager->MeshInstances[j];
			glm::mat4 model = glm::mat4(1.0f);
			glm::vec3 rotation = *instance->rotation;
			glm::vec3 translation = *instance->worldPostion;
            model = glm::translate(model, translation);

			//Rotate X Y Z separately
			model = glm::rotate(model, rotation.x, glm::vec3(1.0, 0.0, 0.0));
			model = glm::rotate(model, rotation.y, glm::vec3(0.0, 1.0, 0.0));
			model = glm::rotate(model, rotation.z, glm::vec3(0.0, 0.0, 1.0));

			currentShader->SetMatrix("model", 1, GL_FALSE, model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
}


