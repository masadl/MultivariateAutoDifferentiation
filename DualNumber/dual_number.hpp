#include <stdio.h>
#include <cmath>
#include <array>
#include <algorithm>

template <size_t DIM>
class DualNumber
{
public:
	DualNumber(const double f = 0.0) {
		fval_ = f;
		std::fill(fprime_.begin(), fprime_.end(), 0.0);
	}

	DualNumber(const double f, const size_t varIdx) {
		fval_ = f;
		std::fill(fprime_.begin(), fprime_.end(), 0.0);
		fprime_[varIdx] = 1.0;
	}

	template <size_t DIM>
	DualNumber<DIM>& operator-() {
		for (std::size_t i = 0; i < DIM; ++i) {
			this->fprime_[i] = -this->fprime_[i];
		}
		this->fval_ = -this->fval_;
		return *this;
	}

	template <size_t DIM>
	DualNumber<DIM>& operator+=(const DualNumber<DIM>& rhs) {
		for (std::size_t i = 0; i < DIM; ++i) {
			this->fprime_[i] += rhs.fprime_[i];
		}
		this->fval_ += rhs.fval_;
		return *this;
	}

	template <size_t DIM>
	DualNumber<DIM>& operator-=(const DualNumber<DIM>& rhs) {
		for (std::size_t i = 0; i < DIM; ++i) {
			this->fprime_[i] -= rhs.fprime_[i];
		}
		this->fval_ -= rhs.fval_;
		return *this;
	}

	template <size_t DIM>
	DualNumber<DIM>& operator*=(const DualNumber<DIM>& rhs) {
		for (std::size_t i = 0; i < DIM; ++i) {
			this->fprime_[i] = 
				this->fprime_[i] * rhs.fval_ + this->fval_ * rhs.fprime_[i];
		}
		this->fval_ *= rhs.fval_;
		return *this;
	}

	template <size_t DIM>
	DualNumber<DIM> operator/(const DualNumber<DIM> &rhs) {
		DualNumber<DIM> ret;
		for (size_t i = 0; i < DIM; ++i) {
			this->fprime_[i] =
				(this->fprime_[i] * rhs.fval_ - this->fval_ * rhs.fprime_[i])
				/ (rhs.fval_ * rhs.fval_);
		}
		this->fval_ /= rhs.fval_;
		return ret;
	}

	DualNumber<DIM> operator+(const DualNumber<DIM> &rhs) const {
		return DualNumber<DIM>(*this) += rhs;
	}

	DualNumber<DIM> operator-(const DualNumber<DIM> &rhs) const {
		return DualNumber<DIM>(*this) -= rhs;
	}

	DualNumber<DIM> operator*(const DualNumber<DIM> &rhs) const {
		return DualNumber<DIM>(*this) *= rhs;
	}

	DualNumber<DIM> operator/(const DualNumber<DIM> &rhs) const {
		return DualNumber<DIM>(*this) /= rhs;
	}

	double getFval() {
		return fval_;
	}

	std::array<double, DIM> getFprime() {
		return fprime_;
	}

private:
	double fval_;
	std::array<double, DIM> fprime_;
};	