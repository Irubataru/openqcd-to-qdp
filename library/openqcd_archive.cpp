
/*
 * Created: 06-06-2017
 * Modified: Tue 24 Oct 2017 13:18:15 BST
 * Author: Jonas R. Glesaaen (jonas@glesaaen.com)
 */

#include <openqcd_archive.hpp>
#include <stdexcept>

extern "C" {
#include "archive.h"
}

namespace fastsum {

/* Imports the config stored in "filename" and checks whether the parameters are
 * consistent with the assumptions in of this program.
 * */
void import_openqcd_config(std::string filename)
{
  import_cnfg(const_cast<char*>(filename.c_str()));

  if (!check_bc(0.0) or chs_ubnd(1))
    throw std::runtime_error {"Unexpeced boundary values for OpenQCD config"};
}

} // namespace fastsum 
