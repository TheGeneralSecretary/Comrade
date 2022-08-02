#include "comradepch.h"
#include "Comrade/Scene/SceneSerializer.h"
#include "Comrade/Utils/FileIO.h"
#include "Comrade/Entity/Entity.h"
#include "Comrade/Entity/Components.h"

#include <yaml-cpp/yaml.h>

namespace YAML
{
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& vec)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << vec.x << vec.y << vec.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& vec)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << vec.x << vec.y << vec.z << vec.w << YAML::EndSeq;
		return out;
	}

	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};
}

namespace Comrade
{
	static void SerializeEntity(YAML::Emitter& out, Entity& entity)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Entity" << YAML::Value << (uint32_t)entity.GetID();

		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;
			out << YAML::Key << "TagComponent" << YAML::BeginMap;
			out << YAML::Key << "Tag" << YAML::Value << tag;
			out << YAML::EndMap;
		}

		if (entity.HasComponent<TransformComponent>())
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			out << YAML::Key << "TransformComponent" << YAML::BeginMap;
			out << YAML::Key << "Translation" << YAML::Value << transform.Translation;
			out << YAML::Key << "Rotation" << YAML::Value << transform.Rotation;
			out << YAML::Key << "Scale" << YAML::Value << transform.Scale;
			out << YAML::EndMap;
		}

		if (entity.HasComponent<CameraComponent>())
		{
			auto& camera = entity.GetComponent<CameraComponent>();
			out << YAML::Key << "CameraComponent" << YAML::BeginMap;
			out << YAML::Key << "Primary" << YAML::Value << camera.Primary;
			out << YAML::Key << "Fixed" << YAML::Value << camera.Fixed;
			out << YAML::Key << "Camera" << YAML::BeginMap;
			out << YAML::Key << "ProjectionType" << YAML::Value << (int)camera.Camera.GetProjectionType();
			out << YAML::Key << "OrthographicSize" << YAML::Value << camera.Camera.GetOrthographicSize();
			out << YAML::Key << "OrthographicNear" << YAML::Value << camera.Camera.GetOrthographicNear();
			out << YAML::Key << "OrthographicFar" << YAML::Value << camera.Camera.GetOrthographicFar();
			out << YAML::EndMap;
			out << YAML::EndMap;
		}

		if (entity.HasComponent<SpriteRendererComponent>())
		{
			auto& sprite = entity.GetComponent<SpriteRendererComponent>();
			out << YAML::Key << "SpriteRendererComponent" << YAML::BeginMap;
			out << YAML::Key << "Color" << YAML::Value << sprite.Color;
			out << YAML::EndMap;
		}

		out << YAML::EndMap;
	}

	bool SceneSerializer::Serialize(const MemoryRef<Scene>& scene, const std::string& outpath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << scene->GetName();
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

		scene->GetRegistry().each([&](auto entityID)
			{
				Entity entity{ entityID, scene.get() };
				if (!entity) return;
				SerializeEntity(out, entity);
			});

		out << YAML::EndSeq;
		out << YAML::EndMap;

		FileIO::WriteFileContent(outpath, std::string(out.c_str()));
		return true;
	}

	bool SceneSerializer::Deserialize(const MemoryRef<Scene>& scene, const std::string& inpath)
	{
		YAML::Node data = YAML::Load(std::stringstream(FileIO::ReadFileContent(inpath)));
		if (!data["Scene"]) return false;

		scene->SetName(data["Scene"].as<std::string>());

		auto entities = data["Entities"];
		for (auto& entity : entities)
		{
			uint64_t uuid = entity["Entity"].as<uint64_t>();
			std::string name;

			if(entity["TagComponent"])
				name = entity["TagComponent"]["Tag"].as<std::string>();

			Entity newentity = scene->CreateEntity(name);

			if (entity["TransformComponent"])
			{
				auto& transform = newentity.GetComponent<TransformComponent>();
				transform.Translation = entity["TransformComponent"]["Translation"].as<glm::vec3>();
				transform.Rotation = entity["TransformComponent"]["Rotation"].as<glm::vec3>();
				transform.Scale = entity["TransformComponent"]["Scale"].as<glm::vec3>();
			}

			if (entity["CameraComponent"])
			{
				auto& camera = newentity.AddComponent<CameraComponent>();
				camera.Primary = entity["CameraComponent"]["Primary"].as<bool>();
				camera.Fixed = entity["CameraComponent"]["Fixed"].as<bool>();
				camera.Camera.SetProjectionType((CameraProjectionType)entity["CameraComponent"]["Camera"]["ProjectionType"].as<int>());
				camera.Camera.SetOrthographicSize(entity["CameraComponent"]["Camera"]["OrthographicSize"].as<float>());
				camera.Camera.SetOrthographicNear(entity["CameraComponent"]["Camera"]["OrthographicNear"].as<float>());
				camera.Camera.SetOrthographicFar(entity["CameraComponent"]["Camera"]["OrthographicFar"].as<float>());
			}

			if (entity["SpriteRendererComponent"])
			{
				auto& sprite = newentity.AddComponent<SpriteRendererComponent>();
				sprite.Color = entity["SpriteRendererComponent"]["Color"].as<glm::vec4>();
			}
		}
		return true;
	}
}
