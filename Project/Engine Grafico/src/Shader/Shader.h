#ifndef SHADER_H
#define SHADER_H

#include "../Utils/Export.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Engine {

	class ENGINE_API Shader {
	public:
		Shader(const char* vertexPath, const char* fragmentPath);

		void Use();
		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;

		unsigned int GetID();

	private:
		unsigned int _id;

		void CheckCompileErrors(unsigned int shader, std::string type);
	};

}
#endif // !SHADER_H