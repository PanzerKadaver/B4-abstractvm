#ifndef ABSTRACTVM_TRAIT_HPP_
# define ABSTRACTVM_TRAIT_HPP_

namespace TRAIT
{
	template <typename T>
	struct is_float
	{
		static const bool value = false;
	};

	template <>
	struct is_float<float>
	{
		static const bool value = true;
	};

	template <typename T>
	struct is_double
	{
		static const bool value = false;
	};

	template <>
	struct is_double<double>
	{
		static const bool value = true;
	};
}

#endif // !ABSTRACTVM_TRAIT_HPP_
