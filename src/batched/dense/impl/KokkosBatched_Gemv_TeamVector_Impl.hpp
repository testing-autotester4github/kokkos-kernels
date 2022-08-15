#ifndef __KOKKOSBATCHED_GEMV_TEAMVECTOR_IMPL_HPP__
#define __KOKKOSBATCHED_GEMV_TEAMVECTOR_IMPL_HPP__

/// \author Kyungjoo Kim (kyukim@sandia.gov)

#include "KokkosBatched_Util.hpp"
#include "KokkosBatched_Gemv_TeamVector_Internal.hpp"

namespace KokkosBatched {

///
/// Team Impl
/// =========

///
/// Implemented:
/// NT, T
///
/// Not yet implemented
/// CT

///
/// NT
///

template <typename MemberType>
struct TeamVectorGemv<MemberType, Trans::NoTranspose, Algo::Gemv::Unblocked> {
  template <typename ScalarType, typename AViewType, typename xViewType,
            typename yViewType>
  KOKKOS_INLINE_FUNCTION static int invoke(
      const MemberType &member, const ScalarType alpha, const AViewType &A,
      const xViewType &x, const ScalarType beta, const yViewType &y) {
    static_assert(AViewType::Rank == 3,
                  "Batched TeamVectorGemv requires rank-3 A matrix (use "
                  "KokkosBlas::TeamVectorGemv for regular rank-2 matrix)");
    return TeamVectorGemvInternal<Algo::Gemv::Unblocked>::template invoke<
        MemberType, ScalarType, typename AViewType::array_layout,
        typename AViewType::non_const_value_type>(
        member, A.extent(0), A.extent(1), A.extent(2), alpha, A.data(),
        A.stride_0(), A.stride_1(), A.stride_2(), x.data(), x.stride_0(),
        x.stride_1(), beta, y.data(), y.stride_0(), y.stride_1());
  }
};

template <typename MemberType>
struct TeamVectorGemv<MemberType, Trans::NoTranspose, Algo::Gemv::Blocked> {
  template <typename ScalarType, typename AViewType, typename xViewType,
            typename yViewType>
  KOKKOS_INLINE_FUNCTION static int invoke(
      const MemberType &/*member*/, const ScalarType /*alpha*/, const AViewType &/*A*/,
      const xViewType &/*x*/, const ScalarType /*beta*/, const yViewType &/*y*/) {
    static_assert(AViewType::Rank == 3,
                  "Batched TeamVectorGemv requires rank-3 A matrix (use "
                  "KokkosBlas::TeamVectorGemv for regular rank-2 matrix)");
    Kokkos::abort(
        "KokkosBatched::TeamVectorGemv<Algo::Gemv::Blocked> for rank-3 matrix "
        "is NOT implemented");
  }
};

///
/// T
///

template <typename MemberType>
struct TeamVectorGemv<MemberType, Trans::Transpose, Algo::Gemv::Unblocked> {
  template <typename ScalarType, typename AViewType, typename xViewType,
            typename yViewType>
  KOKKOS_INLINE_FUNCTION static int invoke(
      const MemberType &member, const ScalarType alpha, const AViewType &A,
      const xViewType &x, const ScalarType beta, const yViewType &y) {
    static_assert(AViewType::Rank == 3,
                  "Batched TeamVectorGemv requires rank-3 A matrix (use "
                  "KokkosBlas::TeamVectorGemv for regular rank-2 matrix)");
    return TeamVectorGemvInternal<Algo::Gemv::Unblocked>::template invoke<
        MemberType, ScalarType, typename AViewType::array_layout,
        typename AViewType::non_const_value_type>(
        member, A.extent(0), A.extent(2), A.extent(1), alpha, A.data(),
        A.stride_0(), A.stride_2(), A.stride_1(), x.data(), x.stride_0(),
        x.stride_1(), beta, y.data(), y.stride_0(), y.stride_1());
  }
};

template <typename MemberType>
struct TeamVectorGemv<MemberType, Trans::Transpose, Algo::Gemv::Blocked> {
  template <typename ScalarType, typename AViewType, typename xViewType,
            typename yViewType>
  KOKKOS_INLINE_FUNCTION static int invoke(
      const MemberType &/*member*/, const ScalarType /*alpha*/, const AViewType &/*A*/,
      const xViewType &/*x*/, const ScalarType /*beta*/, const yViewType &/*y*/) {
    static_assert(AViewType::Rank == 3,
                  "Batched TeamVectorGemv requires rank-3 A matrix (use "
                  "KokkosBlas::TeamVectorGemv for regular rank-2 matrix)");
    Kokkos::abort(
        "KokkosBatched::TeamVectorGemv<Algo::Gemv::Blocked> for rank-3 matrix "
        "is NOT implemented");
  }
};

}  // namespace KokkosBatched

#endif
