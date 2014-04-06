/*
 * utility.h
    Copyright (C) 2014  Timothy Sweet

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UTILITY_H_
#define UTILITY_H_
#include "wifi_localization/WifiData.h"
#include "WifiMapper.h"
#include <vector>

namespace utility {
void merge_wifiData(const wifi_localization::WifiData::_data_type& merge_from, wifi_localization::WifiData::_data_type& merge_into);
float compare_observation(const wifi_localization::WifiData::_data_type& truth,const wifi_localization::WifiData::_data_type& observation);
int find_likelyhood(const std::vector<float>& cdf, float value_to_find);
} //namespace utility

#endif /* UTILITY_H_ */
