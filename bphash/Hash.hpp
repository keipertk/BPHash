/*! \file
 * \brief Hash value definition and utilities (header)
 */

#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace bphash {

/*! \brief Stores the value of a hash
 *
 * While you can use this like a normal std::vector,
 * consider using the other utilities in this file
 * (such as truncate_hash and hash_to_string)
 */
typedef std::vector<uint8_t> HashValue;


/*! \brief Truncate the hash to a given number of bytes
 *
 * If the desired size is larger than the size of the size of
 * the given hash, the new hash is padded with zeroes.
 *
 * \param [in] hash The hash to truncate
 * \param [in] nbytes Desired size of the new hash (in bytes)
 * \return A new, truncated hash
 */
HashValue truncate_hash(const HashValue & hash, size_t nbytes);


/*! \brief Convert the hash to a given numerical type
 *
 * If the type is larger than the size of the stored hash, it is padded
 * with zeros. Otherwise, the hash it is truncated.
 *
 * \tparam The type to convert to. Must be an arithmetic type.
 *
 * \param [in] hash The hash to convert
 * \return The hash converted to an arithmetic type
 */
template<typename T>
T convert_hash(const HashValue & hash)
{
    static_assert(std::is_arithmetic<T>::value,
                  "Type to convert to must be an arithmetic type");

    const size_t wantedbytes = sizeof(T);
    HashValue tmphash = truncate_hash(hash, wantedbytes); // will pad with zero

    T ret = static_cast<T>(0);

    // i = number of bytes, so i*8 is the
    //     number of bits to shift
    for(size_t i = 0; i < wantedbytes; i++)
        ret |= static_cast<T>(tmphash[i]) << (i*8);

    return ret;
}


/*! \brief Return a string representation of a hash
 *
 * The string representation is the usual hex representation,
 * with lower case letters. The length of the string
 * should be 2*number_of_bits/8 characters.
 *
 * \param [in] hash The hash to convert
 * \return A string representing the hash
 */
std::string hash_to_string(const HashValue & hash);


} // close namespace bphash

