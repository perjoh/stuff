#define _CRT_SECURE_NO_WARNINGS
#include "PngImage.hpp"
#include <png.h>
#include <pnginfo.h>
#include <boost/scoped_array.hpp>
#include <boost/bind.hpp>
#include <exception>

namespace resource {
namespace png {

	void read( Image& img, const char* file_name ) {

		// TODO: Use shared_ptr to execute fclose() etc. when exiting scope.

		// open file

		FILE *fp = fopen(file_name, "rb");
		if (!fp) {
			throw std::exception("Failed to open file.");
		}

		boost::shared_ptr<void> fp_cleanup( static_cast<void*>(0), boost::bind( fclose, fp ) );

		const int PNG_BYTES_TO_CHECK = 4;
		png_byte header[PNG_BYTES_TO_CHECK];

		fread(header, 1, PNG_BYTES_TO_CHECK, fp);
		const bool is_png = !png_sig_cmp(header, 0, PNG_BYTES_TO_CHECK);
		if (!is_png) {
			throw std::exception("File is not a valid PNG file.");
		}

		// setup PNG structs

		png_structp png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, 0, 0, 0);
		if (!png_ptr) {
			throw std::exception("png_create_read_struct failed.");
		}

		png_infop info_ptr = 0;
		png_infop end_info = 0;
		boost::shared_ptr<void> png_cleanup( static_cast<void*>(0), boost::bind( png_destroy_read_struct, &png_ptr, &info_ptr, &end_info ) );

		info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr) {
			throw std::exception("png_create_info_struct failed.");
		}

		end_info = png_create_info_struct(png_ptr);
		if (!end_info) {
			throw std::exception("png_create_info_struct failed.");
		}

		// TODO Remove setjmp
		if (setjmp(png_jmpbuf(png_ptr))) {
			throw std::exception("Failed to read PNG-image.");
		}

		png_init_io(png_ptr, fp);

		png_set_sig_bytes(png_ptr, PNG_BYTES_TO_CHECK);

		png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

		const png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);

		// Assert we are making correct assumptions about PNG lib.
		assert( info_ptr->rowbytes == info_ptr->channels * info_ptr->width );

		Image img_tmp( info_ptr->width, info_ptr->height, info_ptr->channels, row_pointers );
		img.swap( img_tmp );
	}


	void write( Image& img, const char* filename ) {

		if ( !( img.get_width() > 0 && img.get_height() > 0 && img.get_num_channels() > 0 ) ) {
			throw std::exception( "This is not a valid image to write." );
		}

		FILE* fp = fopen( filename, "wb" );
		if ( !fp ) {
			throw std::exception( "Failed to open file." );
		}

		boost::shared_ptr<void> fp_cleanup( static_cast<void*>(0), boost::bind( fclose, fp ) );

		png_structp png_ptr = png_create_write_struct( PNG_LIBPNG_VER_STRING, NULL, NULL, NULL );
		if (!png_ptr) {
		   throw std::exception( "png_create_write_struct failed." );
		}

		png_infop info_ptr = 0;

		boost::shared_ptr<void> png_cleanup( static_cast<void*>(0), boost::bind( png_destroy_write_struct, &png_ptr, &info_ptr ) );

		info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr) {
		   throw std::exception( "png_create_info_struct failed." );
		}

		if ( setjmp(png_jmpbuf(png_ptr)) ) {
		   throw std::exception( "libpng returned an error." );
		}

	   png_init_io(png_ptr, fp);

		// optional: call png_set_filter to control compression

		// fill png_info structure

		typedef boost::scoped_array< Image::channel* > Channel_array;
		Channel_array row_pointers( new Image::channel* [ img.get_height() ] );

		for ( int row = 0; row < img.get_height(); ++row ) {
			row_pointers[ row ] = img.get_row_ptr( row );
		}

		png_set_rows( png_ptr, info_ptr, row_pointers.get() );

		png_set_IHDR(
			png_ptr,
			info_ptr,
		   	img.get_width(),
		   	img.get_height(),
		   	8,
		   	PNG_COLOR_TYPE_RGB,
		   	PNG_INTERLACE_NONE,
		   	PNG_COMPRESSION_TYPE_DEFAULT,
		   	PNG_FILTER_TYPE_DEFAULT );

		png_write_png(
			png_ptr,
		   	info_ptr,
		   	PNG_TRANSFORM_IDENTITY,
		   	NULL );
	}
} }
