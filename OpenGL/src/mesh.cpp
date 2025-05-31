#include "mesh.h"
#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


MeshData::MeshData(const Vertex* vertices, int num)
{
	verticesCount = num;
	this->vertices = (Vertex*)malloc(num * sizeof(Vertex));
	if (this->vertices == nullptr) {
		throw std::bad_alloc();
	}
	memcpy(this->vertices, vertices, num * sizeof(Vertex));

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Copy data from VBO to the GPU as static
	glBufferData(GL_ARRAY_BUFFER, num * sizeof(Vertex), this->vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO);


	//Vertex position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);


	//Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//Texture Coordinate
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
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

MeshManager::MeshManager(const Vertex* vertices, int num, const Shader& shader) : Mesh(vertices, num)
{
	ShaderInUse = shader;
}

MeshManager::~MeshManager()
{
}

MeshInstance* MeshManager::CreateInstance(glm::vec3 worldPosRef, glm::vec3 rotationRef)
{
	MeshInstance newInstance = MeshInstance{
		worldPosRef,
		rotationRef
	};

	MeshInstances.push_back(newInstance);

	MeshInstance* returnInstance = &MeshInstances[MeshInstances.size() - 1];

	return returnInstance;
}

MeshData::~MeshData()
{
	free(vertices);
}

int MeshData::GetVertexCount()
{
	return verticesCount;
}

void SceneManager::RenderScene()
{
	//Draw all non-light source objects
	for (int i = 0; i < OpaqueMeshes.size(); ++i) {
		MeshManager* meshManager = OpaqueMeshes[i];
		Shader* currentShader = &meshManager->ShaderInUse;
		glBindVertexArray(meshManager->Mesh.VAO);
		currentShader->Use();

		currentShader->SetVec("ambientColor", 1, ambient);
		for (int j = 0; j < meshManager->MeshInstances.size(); ++j) {
			MeshInstance& instance = meshManager->MeshInstances[j];
			glm::mat4 model = glm::mat4(1.0f);
			glm::vec3 rotation = instance.rotation;
			glm::vec3 translation = instance.worldPostion;
            model = glm::translate(model, translation);

			//Rotate X Y Z separately
			model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
			model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
			model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));
			currentShader->SetMatrix("model", 1, GL_FALSE, model);
			glDrawArrays(GL_TRIANGLES, 0, meshManager->Mesh.GetVertexCount());
		}
	}
}

void SceneManager::AddMeshManager(MeshManager* MManagerIn, ObjectType type)
{
	for (MeshManager* m : OpaqueMeshes) {
		if (MManagerIn == m) {
			continue;
		}
		else {
			OpaqueMeshes.push_back(MManagerIn);
		}
	}
}



