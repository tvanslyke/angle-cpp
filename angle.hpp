#ifndef TIM_ANGLE_ANGLE_HPP
#define TIM_ANGLE_ANGLE_HPP

#include <cstdint>

namespace tim {

inline namespace angle {

template <class Float>
struct Angle {
private:
	static constexpr const std::uintmax_t digit_count = std::min(
		std::numeric_limits<Float>::digits,
		std::numeric_limits<std::uintmax_t>::digits - 1
	);

	static constexpr const std::uintmax_t maxm
		= static_cast<std::uintmax_t>(1) << digit_count;

	static constexpr const Float float_maxm() {
		return static_cast<Float>(maxm);
	}
	static constexpr const Float tau() {
		constexpr const double tau_v = 6.2831853071795864769252867665590057683943387987502116419498891846;
		return static_cast<Float>(tau_v);
	}

public:
	template <class T, std::enable_if_t<std::is_arithmetic_v<T>, bool> = false>
	static constexpr Angle from_degrees(T degrees_val) {
		if constexpr(std::is_integral_v<T>) {
			if constexpr(std::is_unsigned_v<T>) {
				constexpr auto lim = std::numeric_limits<std::uintmax_t>::max() / 360ull;
				if constexpr(lim < maxm) {
				
				} else {
					
				}
			}
		}
			
		} 
	}

	constexpr Angle() noexcept:
		raw_value_(0ul)
	{
		
	}

	Angle(const Angle&) = default;
	Angle(Angle&&) = default;
	Angle& operator=(const Angle&) = default;
	Angle& operator=(Angle&&) = default;

	constexpr Float radians() const {
		return static_cast<Float>(raw_value_) * (static_cast<Float>(tau()) / max_value());
	}

	constexpr Float degrees() const {
		return static_cast<Float>(raw_value_) * (static_cast<Float>(tau()) / max_value());
	}

	constexpr std::pair<std::uintmax_t, std::uintmax_t> rational() const {
		return std::pair{raw_value_, maxm};
	}

	friend constexpr bool operator<(Angle l, Angle r) noexcept {
		return l.raw_value_ < r.raw_value_;
	}

	friend constexpr bool operator<(Angle l, Angle r)  noexcept { return l.raw_value_ < r.raw_value_; }
	friend constexpr bool operator<=(Angle l, Angle r) noexcept { return l.raw_value_ <= r.raw_value_; }
	friend constexpr bool operator>(Angle l, Angle r)  noexcept { return l.raw_value_ > r.raw_value_; }
	friend constexpr bool operator>=(Angle l, Angle r) noexcept { return l.raw_value_ >= r.raw_value_; }
	friend constexpr bool operator==(Angle l, Angle r) noexcept { return l.raw_value_ == r.raw_value_; }
	friend constexpr bool operator!=(Angle l, Angle r) noexcept { return l.raw_value_ != r.raw_value_; }

	friend constexpr Angle operator+(Angle l, Angle r) noexcept {
		return truncate(l.raw_value_ + r.raw_value_)
	}

	friend constexpr Angle& operator+=(Angle& l, Angle r) noexcept {
		l.raw_value += r.raw_value_;
		return l;
	}

	friend constexpr Angle operator+(Angle a) noexcept {
		return from_raw(a.raw_value_);
	}

	friend constexpr Angle operator-(Angle l, Angle r) noexcept {
		if(r > l) {
			return truncate(maxm - (r.raw_value_ - l.raw_value_);
		}
		return truncate(l.raw_value_ - r.raw_value_)
	}

	friend constexpr Angle& operator-=(Angle& l, Angle r) noexcept {
		return l = (l - r);
	}

	friend constexpr Angle operator-(Angle a) noexcept {
		return truncate(maxm - a.raw_value_);
	}

private:
	static constexpr Angle from_raw(std::uintmax_t v) {
		Angle a;
		assert(v < maxm);
		a.raw_value_ = v;
		return a;
	}

	static constexpr Angle truncate(std::uintmax_t v) {
		Angle a;
		a.raw_value_ = v;
		return a;
	}

	std::uintmax_t raw_value_: digit_count;
};


} /* namespace angle */

} /* namespace tim */


#endif /* TIM_ANGLE_ANGLE_HPP */
