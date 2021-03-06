#pragma once
#include "../nclgl/Matrix4.h"
#include "../nclgl/Vector3.h"
#include "../nclgl/Vector4.h"
#include "../nclgl/Mesh.h"
#include "../nclgl/Shader.h"
#include "../nclgl/MeshMaterial.h"
#include "../nclgl/MeshAnimation.h"
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

	void SetBumpTexture(GLuint tex) { bump = tex; }
	GLuint GetBumpTexture() const { return bump; }

	//void AddTexture(GLuint tex) { matTextures.emplace_back(tex); }
	void SetTextures(vector<GLuint>* texs) { matTextures = texs; }
	vector<GLuint>* GetMaterialTextures() { return matTextures; }

	void SetBumpTextures(vector<GLuint>* texs) { bumpTextures = texs; }
	vector<GLuint>* GetBumpTextures() { return bumpTextures; }

	void SetAnimation(MeshAnimation* anim) { animation = anim; }
	MeshAnimation* GetAnimation() { return animation; }

	bool UsesShadows() { return useShadows; }
	void SetUseShadows(bool val) { useShadows = val; }

	bool IsInstanced() { return isInstanced; }
	void SetIsInstanced(bool val) { isInstanced = val; }

	int GetCurrentFrame() { return currentFrame; }
	
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
	GLuint bump;
	vector<GLuint>* matTextures;
	vector<GLuint>* bumpTextures;
	MeshMaterial* material;
	MeshAnimation* animation;
	int currentFrame;
	float frameTime;
	bool useShadows = false;
	bool isInstanced = false;

};

