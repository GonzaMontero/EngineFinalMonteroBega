#ifndef SHADER_H
#define SHADER_H

#include "../Utils/Export.h"

#include <glm.hpp>
#include <matrix_transform.hpp>
#include <type_ptr.hpp>

#include <iostream>

namespace Engine {

	class ENGINE_API Shader {
	private:
		unsigned int _id;
		unsigned int Compile(unsigned int type, std::string& source);
		void CreateAttribPointer(unsigned int shaderAttribIndex, int dataAmmount, int dataSize, int dataPosition);

	public:
		Shader();
		~Shader();
		void Create(const char* vertexPath, const char* fragmentPath);
		void Use();
		void Use(glm::mat4 model);
		void SetVertexAttributes(const char* name, int vertexSize);
		void SetColorAttributes(const char* name, int vertexSize);
		void SetTextureAttributes(const char* name, int vertexSize);
		void SetNormalAttributes(const char* name, int vertexSize);
		unsigned int GetMatrixAttributes(const char* name);
		unsigned int GetID();
	};

}
#endif // !SHADER_H