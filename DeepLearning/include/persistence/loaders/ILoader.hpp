//
// Created by 26326 on 2025/8/30.
//

#ifndef AICPP_LOADER_HPP
#define AICPP_LOADER_HPP

namespace ml::loader {
template<class T>
class DEEPLEARNING_EXPORT ILoader {
public:
	explicit ILoader(std::filesystem::path path) : path(std::move(path)) {
	}

	virtual ~ILoader() = default;

protected:
	std::filesystem::path path;

public:
	virtual T * load() = 0;

	virtual std::shared_ptr<T> load_shared() = 0;

	virtual std::unique_ptr<T> load_unique() = 0;
};
} // ml

#endif //AICPP_LOADER_HPP
