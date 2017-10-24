
/*
 * Created: 24-10-2017
 * Modified: Tue 24 Oct 2017 14:29:17 BST
 * Author: Jonas R. Glesaaen (jonas@glesaaen.com)
 */

#ifndef QDP_ARCHIVE_HPP
#define QDP_ARCHIVE_HPP

#include "qdp_utilities.hpp"

namespace fastsum {

void write_qdp_gauge_field(QDP_Gauge_Field &gauge_field, std::string filename);

} // namespace fastsum 


#endif /* QDP_ARCHIVE_HPP */
