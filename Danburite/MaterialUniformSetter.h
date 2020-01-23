#pragma once

#include <unordered_map>
#include <unordered_set>
#include "ProgramType.h"
#include "Program.h"
#include "MaterialType.h"
#include "VertexAttributeType.h"
#include "MaterialOptionFlag.h"

namespace Danburite
{
	class MaterialUniformSetter
	{
	private:
		std::unordered_map<ProgramType, ObjectGL::Program *> __programMap;

	public:
		MaterialUniformSetter(const std::unordered_set<ProgramType> &programTypes) noexcept;

		ObjectGL::Program &getProgram(const ProgramType programType) const noexcept;

		void setMaterialType(const MaterialType type) noexcept;
		void setVertexType(const VertexAttributeType type) noexcept;
		void setOptionFlag(const MaterialOptionFlag flag) noexcept;

		template <typename FunctionType, typename ...Args>
		void traverseProgram(const FunctionType function, Args &&...args);

		virtual ~MaterialUniformSetter() = default;
	};

	template <typename FunctionType, typename ...Args>
	void MaterialUniformSetter::traverseProgram(const FunctionType function, Args &&...args)
	{
		for (const auto &[_, pProgram] : __programMap)
			(pProgram->*function)(args...);
	}
}