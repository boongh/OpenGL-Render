#pragma once
#include <vector>
#include <glm.hpp>
#include "shader.h"


#pragma pack(push, 1)
struct Material {
	glm::vec3 diffuse;
	glm::vec3 specular;
	float reflectivity;
	float shineBrightness;
};
#pragma pack(pop)


#pragma pack(push, 64)
struct alignas(64) Vertex {
	float relativePosition[3];
	float normal[3];
	float textureCoordinate[2];
	Material material;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct MeshData {
private:
	int verticesCount;
	Vertex* vertices;

public:
		
	/// <summary>
	/// Constructs a mesh from vertices and a material
	/// </summary>
	/// <param name="vertices"></param>
	/// <param name="material"></param>

	MeshData(const Vertex* vertices, int num);
	~MeshData();

	int GetVertexCount();

	unsigned int VAO, VBO;
};
#pragma pack(pop)


struct MeshInstance {


	//World position of the object center reference so it can be changed outside
	glm::vec3 worldPostion;

	//Rotation using fixed 3d axis coordinate reference so it can be change outside
	glm::vec3 rotation;
};



class MeshManager {

public:
	MeshData Mesh;
	Shader ShaderInUse = Shader(); // Initialize ShaderInUse
	
	MeshManager(const Vertex* vertices, int num, const Shader& shader);
	~MeshManager();

	MeshInstance* CreateInstance(glm::vec3 worldPos, glm::vec3 rotation);
	/// <summary>
	/// Number of unique meshes, as in, meshes with the same 
	/// </summary>
	std::vector<MeshInstance> MeshInstances;

};


class SceneManager {
	std::vector<MeshManager*> OpaqueMeshes;
	std::vector<MeshManager*> LightSources;

public :
	//Basically skybox;
	glm::vec3 ambient;
	enum ObjectType
	{
		Opaque,
		LightSource
	};

	void RenderScene();
	void AddMeshManager(MeshManager* MManagerIn, ObjectType type);
};