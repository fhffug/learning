//
// Created by 26326 on 25-8-28.
//

#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <nlohmann/json.hpp>

namespace ml::config {
class DEEPLEARNING_EXPORT IConfig {
public:
	virtual ~IConfig() = default;

	// 提供通用的序列化和反序列化接口
	virtual void to_json(nlohmann::json & json) const = 0;

	virtual void from_json(const nlohmann::json & json) = 0;

	virtual void to_json(nlohmann::ordered_json & json) const = 0;

	virtual void from_json(const nlohmann::ordered_json & json) = 0;
};

template<typename T>
concept IConfigConcept = requires(T t, nlohmann::json j) {
	requires std::derived_from<T, IConfig>;
	{ t.to_json(j) } -> std::same_as<void>;
	{ t.from_json(j) } -> std::same_as<void>;
};

// 实现通用的 to_json 和 from_json 函数模板
template<IConfigConcept T>
void to_json(nlohmann::json & json, const T & config) {
	config.to_json(json);
}

template<IConfigConcept T>
void from_json(const nlohmann::json & json, T & config) {
	config.from_json(json);
}

// 实现通用的 to_json 和 from_json 函数模板
template<IConfigConcept T>
void to_json(nlohmann::ordered_json & json, const T & config) {
	config.to_json(json);
}

template<IConfigConcept T>
void from_json(const nlohmann::ordered_json & json, T & config) {
	config.from_json(json);
}
}

#endif //CONFIG_HPP
