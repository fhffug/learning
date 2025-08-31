//
// Created by 26326 on 2025/8/30.
//

#ifndef AICPP_ISAVER_HPP
#define AICPP_ISAVER_HPP

namespace ml {
template<typename T>
class DEEPLEARNING_EXPORT ISaver {
public:
	virtual ~ISaver() = default;

	explicit ISaver(std::filesystem::path path) : path(std::move(path)) {
	}

protected:
	std::filesystem::path path;

public:
	virtual void save(const T &) const = 0;

	virtual void save(const std::shared_ptr<T> &) const = 0;

	virtual void save(const std::unique_ptr<T> &) const = 0;

	virtual void save(const T *) const = 0;
};
} // ml

#endif //AICPP_ISAVER_HPP
