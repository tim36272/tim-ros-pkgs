/*
 * PgmImage.cpp
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
#include "PgmImage.h"
PgmImage::PgmImage(int x,int y) {
	x_size = x;
	y_size = y;
	data = new unsigned char*[y_size];
	for(int i=0;i<y_size;i++) {
		data[i] = new unsigned char[x_size];
		for(int j=0;j<x_size;j++) {
			data[i][j] = 25;
		}
	}
}
void PgmImage::write(const std::string& filename) {

	std::ofstream out;
	out.open(filename.c_str(), std::ios::out | std::ios::binary);

	 if (!out) {
	   std::cout << "Can't open file: " << filename << std::endl;
	 }

	 out << "P5" << std::endl;
	 out << x_size << " " << y_size << std::endl;
	 out << 255 << std::endl;

	 unsigned char* char_image = new unsigned char[x_size*y_size];
	 for(int y=0;y<y_size;y++) {
		 for(int x=0;x<x_size;x++) {
			 char_image[y*x_size+x] = data[y][x];
		 }
	 }
	 out.write( reinterpret_cast<char *>(char_image), (x_size*y_size)*sizeof(unsigned char));

	 if (out.fail()) {
	   std::cout << "Can't write image " << filename << std::endl;
	   exit(0);
	 }
}
