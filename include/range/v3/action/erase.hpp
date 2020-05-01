/// \file
// Range v3 library
//
//  Copyright Eric Niebler 2013-present
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//

#ifndef RANGES_V3_ACTION_ERASE_HPP
#define RANGES_V3_ACTION_ERASE_HPP

#include <utility>

#include <range/v3/range_fwd.hpp>

#include <range/v3/action/insert.hpp>
#include <range/v3/utility/static_const.hpp>

#include <range/v3/detail/disable_warnings.hpp>

namespace ranges
{
    /// \cond
    namespace adl_erase_detail
    {
        CPP_template(typename Cont, typename I, typename S)( //
            requires lvalue_container_like<Cont> && forward_iterator<I>  && //
                sentinel_for<S, I>) //
        auto erase(Cont && cont, I first, S last)                            //
            -> decltype(unwrap_reference(cont).erase(first, last))
        {
            return unwrap_reference(cont).erase(first, last);
        }

        struct erase_fn
        {
            CPP_template(typename Rng, typename I, typename S)( //
                requires range<Rng> && forward_iterator<I> && sentinel_for<S, I>) //
            auto operator()(Rng && rng, I first, S last) const
                -> decltype(erase((Rng &&) rng, first, last))
            {
                return erase(static_cast<Rng &&>(rng), first, last);
            }
        };
    } // namespace adl_erase_detail
    /// \endcond

    /// \ingroup group-actions
    RANGES_INLINE_VARIABLE(adl_erase_detail::erase_fn, erase)

    namespace actions
    {
        using ranges::erase;
    }

    /// \addtogroup group-range
    /// @{
    // clang-format off
    template<typename Rng, typename I, typename S>
    CPP_concept_fragment(erasable_range_,
        requires(Rng && rng, I first, S last)
        (
            ranges::erase((Rng &&) rng, first, last)
        )
    );
    template<typename Rng, typename I, typename S>
    CPP_concept_bool erasable_range =
        range<Rng> && CPP_fragment(ranges::erasable_range_, Rng, I, S);
    // clang-format on
    /// @}
} // namespace ranges

#include <range/v3/detail/reenable_warnings.hpp>

#endif
