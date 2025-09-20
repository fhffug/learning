//
// Created by 26326 on 2025/8/30.
//

#ifndef AICPP_ISAVER_HPP
#define AICPP_ISAVER_HPP

namespace ml::saver {
template<typename T>
class DEEPLEARNING_EXPORT ISaver {
protected:
	std::filesystem::path m_path;

public:
	virtual ~ISaver() = default;

	explicit ISaver(std::filesystem::path path) : m_path(std::move(path)) {
	}

	virtual void save(const T *) const = 0;
};
} // ml

#endif //AICPP_ISAVER_HPP
