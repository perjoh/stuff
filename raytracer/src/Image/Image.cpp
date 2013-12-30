
#include <vector>
#include <algorithm>
#include <boost/shared_array.hpp>
#include "image.hpp"

namespace resource {

	typedef boost::shared_array<Image::channel> chan_array;

	Image::Image() :
		width_(0),
		height_(0),
		num_chan_(0)
	{ }


	Image::Image( int width, int height, int num_chan, const channel*const* src, const channel_order& co ) :
		width_( width ),
		height_( height ),
		num_chan_( num_chan ),
		co_( co )
	{

		assert( width > 0 );
		assert( height > 0 );
		assert( num_chan > 0 );
		assert( src );

		copy_from_scanlines( width, height, num_chan, src );
	}


	Image::Image( int width, int height, int num_chan, const channel_order& co ) :
		width_( width ),
		height_( height ),
		num_chan_( num_chan ),
		co_( co )
	{
		assert( width > 0 );
		assert( height > 0 );
		assert( num_chan > 0 );

		copy_from_bitmap( width, height, num_chan, 0, 0 );
	}


	Image::~Image()
	{
	}

	int Image::get_width() const {
		return width_;
	}

	int Image::get_height() const {
		return height_;
	}

	int Image::get_num_channels() const {
		return num_chan_;
	}

	void Image::set_pixel( int x, int y, const pixel& px )
	{
		channel* p = get_pixel_ptr( x, y );
		p[ co_.red ] = px.red;
		p[ co_.green ] = px.green;
		p[ co_.blue ] = px.blue;

		if ( get_num_channels() == 4 ) {
			p[ co_.alpha ] = px.alpha;
		}
	}


	Image::pixel Image::get_pixel( int x, int y ) const
	{
		const channel* p = get_pixel_ptr( x, y );

		if ( get_num_channels() == 4 ) {
			return pixel( p[ co_.red ], p[ co_.green ], p[ co_.blue ], p[ co_.alpha ] );
		}

		return pixel( p[ co_.red ], p[ co_.green ], p[ co_.blue ] );
	}


	void Image::swap( Image& rhs )
	{
		std::swap( width_, rhs.width_ );
		std::swap( height_, rhs.height_ );
		std::swap( num_chan_, rhs.num_chan_ );
		std::swap( co_, rhs.co_ );
		std::swap( bitmap_, rhs.bitmap_ );
	}

	const Image::channel* Image::get_row_ptr( int row ) const
	{
		assert( !( row < 0 ) );
		assert( row < get_height() );
		return &bitmap_[ row * get_pitch() ];
	}

	Image::channel* Image::get_row_ptr( int row )
	{
		assert( !( row < 0 ) );
		assert( row < get_height() );
		return &bitmap_[ row * get_pitch() ];
	}

	const Image::channel* Image::get_pixel_ptr( int x, int y ) const
	{
		assert( x >= 0 );
		assert( y >= 0 );

		return get_row_ptr( y ) + get_num_channels() * x;
	}

	Image::channel* Image::get_pixel_ptr( int x, int y )
	{
		assert( x >= 0 );
		assert( y >= 0 );

		return get_row_ptr( y ) + get_num_channels() * x;
	}

	int Image::get_pitch() const
	{
		return get_width() * get_num_channels();
	}

	void Image::copy_from_bitmap( int width, int height, int num_chan, const channel* src, int src_pitch )
	{
		using namespace std;

		width_ = width;
		height_ = height;
		num_chan_ = num_chan;

		bitmap_.resize( get_pitch() * get_height() );

		if ( src ) {
			for ( int row = 0; row < height; ++row ) {
                memcpy( get_row_ptr( row ), src, sizeof(channel)*src_pitch );
				//copy( src, src + src_pitch, get_row_ptr( row ) );
				src += src_pitch;
			}
		}
		else {
			std::fill( bitmap_.begin(), bitmap_.end(), 0 );
		}
	}

	void Image::copy_from_scanlines( int width, int height, int num_chan, const channel*const* src )
	{
		using namespace std;

		assert( src );

		width_ = width;
		height_ = height;
		num_chan_ = num_chan;

		bitmap_.resize( get_pitch() * get_height() );

		for ( int row = 0; row < get_height(); ++row ) {
			//copy( src[row], src[row] + get_pitch(), get_row_ptr( row ) );
            memcpy( get_row_ptr( row ), src[row], sizeof(channel)*get_pitch() );
		}
	}

}
