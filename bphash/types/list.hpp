/*! \file
 *
 * \brief Hashing of std::list
 * \author Benjamin Pritchard (ben@bennyp.org)
 */

#pragma once

#include "bphash/types/ContainerHelper.hpp"
#include <list>

namespace bphash {
namespace detail {

/*! \brief Hashing of std::list */
template<typename T, typename Alloc>
struct ObjectHasher<std::list<T, Alloc>> : public ContainerHasher<std::list<T, Alloc>> { };


} // close namespace detail
} // close namespace bphash

