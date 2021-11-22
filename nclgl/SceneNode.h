#pragma once
#include "../nclgl/Matrix4.h"
#include "../nclgl/Vector3.h"
#include "../nclgl/Vector4.h"
#include "../nclgl/Mesh.h"
#include "../nclgl/Shader.h"
#include "../nclgl/MeshMaterial.h"
#include <vector>

class SceneNode
{
public:
	SceneNode(Mesh* m = NULL, Vector4 colour = Vector4(1, 1, 1, 1));
	~SceneNode(void);

	void SetTransform(const Matrix4& matrix) { transform = matrix; }
	const Matrix4& GetTransform() const { return transform; }
	Matrix4 GetWorldTransform() const { return worldTransform; }

	Vector4 GetColour() const { return colour; }
	void SetColour(Vector4 c) { colour = c; }

	Vector3 GetModelScale() const { return modelScale; }
	void SetModelScale(Vector3 s) { modelScale = s; }

	Mesh* GetMesh() const { return mesh; }
	void SetMesh(Mesh* m) { mesh = m; }

	MeshMaterial* GetMeshMaterial() const { return material; }
	void SetMeshMaterial(MeshMaterial* m) { material = m; }


	Shader* GetShader() const { return shader; }
	void SetShader(Shader* s) { shader = s; }

	float GetBoundingRadius() const { return boundingRadius; }
	void SetBoundingRadius(float f) { boundingRadius = f; }
	
	float GetCameraDistance() const { return distanceFromCamera; }
	void SetCameraDistance(float f) { distanceFromCamera = f; }
	
	void SetTexture(GLuint tex) { texture = tex; }
	GLuint GetTexture() const { return texture; }

	void AddTexture(GLuint tex) { matTextures.emplace_back(tex); }
	vector<GLuint> GetMaterialTextures() { return matTextures; }
	
	static bool CompareByCameraDistance(SceneNode * a, SceneNode * b) {
		return (a->distanceFromCamera < b->distanceFromCamera) ? true : false;
	}

	void AddChild(SceneNode* s);
	void RemoveChild(int index);
	virtual void Update(float dt);
	virtual void Draw(const OGLRenderer& r);


	std::vector < SceneNode* >::const_iterator GetChildIteratorStart() {
		return children.begin();
	}

	std::vector < SceneNode* >::const_iterator GetChildIteratorEnd() {
		return children.end();
	}
protected:
	SceneNode* parent;
	Mesh* mesh;
	Shader* shader;
	Matrix4 worldTransform;
	Matrix4 transform;
	Vector3 modelScale;
	Vector4 colour;
	std::vector <SceneNode*> children;
	float distanceFromCamera;
	float boundingRadius;
	GLuint texture;
	vector <GLuint> matTextures;
	MeshMaterial* material;

};

