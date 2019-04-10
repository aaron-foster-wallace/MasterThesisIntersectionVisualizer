#pragma once

#include <memory>
#include "../Model.h"

namespace ModelFactory {

	using namespace DirectX::SimpleMath;

	class InstancedParticleModel {
	public:
		static std::unique_ptr<Model> Create(UINT instances, ShaderSet* shaderSet) {

			const int numVerts = 1;
			glm::vec3* positions = new glm::vec3[numVerts]{
				glm::vec3(0.f, 0.f, 0.f)
			};

			Model::Data buildData;
			buildData.numVertices = numVerts;
			buildData.positions = positions;

			buildData.numInstances = instances;

			std::unique_ptr<Model> model = std::make_unique<Model>(buildData, shaderSet);

			return model;

		}
	};
}

