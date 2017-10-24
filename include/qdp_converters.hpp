
/*
 * Created: 05-06-2017
 * Modified: Tue 24 Oct 2017 14:37:16 BST
 * Author: Jonas R. Glesaaen (jonas@glesaaen.com)
 */

#ifndef QDP_CONVERTERS_HPP
#define QDP_CONVERTERS_HPP

#include <qdp.h>
#include <types.hpp>
#include <openqcd_utilities.hpp>

namespace fastsum {

void copy(su3_dble const& from, QDP::ColorMatrixD &to);
void copy(OpenQCD_Gauge_Field const& from, QDP_Gauge_Field &to);

} // namespace fastsum 

#endif /* QDP_CONVERTERS_HPP */
