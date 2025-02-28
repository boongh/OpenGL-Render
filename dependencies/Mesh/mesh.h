#pragma once
#include <vector>
#include <glm.hpp>
#include "shader.h"


#pragma pack(push, 12)
struct Material {
	glm::vec3 diffuse;
	glm::vec3 specular;
	float reflectivity;
	float shineBrightness;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct Vertex {
	float relativePosition[3];
	float normal[3];
	float textureCoordinate[2];
	Material material;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct MeshData {
private:
	int faceCount;
	Vertex* vertices;

public:

	/// <summary>
	/// Constructs a mesh from vertices and a material
	/// </summary>
	/// <param name="vertices"></param>
	/// <param name="material"></param>

	MeshData(Vertex& vertices, int num);

	~MeshData();
	unsigned int VAO, VBO;
};
#pragma pack(pop)


struct MeshInstance {


	//World position of the object center reference so it can be changed outside
	glm::vec3* worldPostion;

	//Rotation using fixed 3d axis coordinate reference so it can be change outside
	glm::vec3* rotation;
};



class MeshManager {

public:
	MeshData* Mesh;
	Shader* ShaderInUse;
	
	MeshManager();
	~MeshManager();

	void CreateInstance(glm::vec3* worldPos, glm::vec3* cubePositions);
	/// <summary>
	/// Number of unique meshes, as in, meshes with the same 
	/// </summary>
	std::vector<MeshInstance*> MeshInstances;

};


class SceneManager {
	//Basically skybox;
	glm::vec3 ambient;
	std::vector<MeshManager> OpaqueMeshes;
	std::vector<MeshManager> LightSources;

	enum ObjectType
	{
		Opaque,
		LightSource
	};

public :
	void RenderScene();
	void AddMeshManager(MeshManager* MManagerIn, ObjectType type);
};