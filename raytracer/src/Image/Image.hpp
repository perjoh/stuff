#pragma once

#include <boost/shared_ptr.hpp>
#include <vector>
#include <limits>

namespace resource {

	class Image {
	public :
		typedef unsigned char channel;
		struct pixel {
			pixel() :
				red( 0 ), green( 0 ), blue( 0 ), alpha( 0 )
			{ }

			pixel ( channel r, channel g, channel b ) :
				red( r ), green( g ), blue( b ), alpha( 0 )
			{ }

			pixel( channel r, channel g, channel b, channel a ) :
				red( r ), green( g ), blue( b ), alpha( a )
			{ }

			void invert()
			{
				const channel i = std::numeric_limits<channel>::max()/2;
				red += i;
				green += i;
				blue += i;
				alpha += i;
			}

			bool operator==(const pixel& rhs) const
			{
				return red == rhs.red && green == rhs.green && blue == rhs.blue && alpha == rhs.alpha;
			}

			channel red;
			channel green;
			channel blue;
			channel alpha;
		};

		struct channel_order
		{
			typedef unsigned char channel_index;

			channel_order() :
				red( 0 ), green( 1 ), blue( 2 ), alpha( 3 )
			{ }

			channel_order( channel_index r, channel_index g, channel_index b, channel_index a ) :
				red( r ), green( g ), blue( b ), alpha( a )
			{
				assert( r < 4 );
				assert( g < 4 );
				assert( b < 4 );
				assert( a < 4 );
		   	}

			/*channel_order( const channel_order& c ) :
				red( c.red ),
				green( c.green ),
				blue( c.blue ),
				alpha( c.alpha )
			{ }*/

			void swap( channel_order& rhs )
			{
				std::swap( red, rhs.red );
				std::swap( green, rhs.green );
				std::swap( blue, rhs.blue );
				std::swap( alpha, rhs.alpha );
			}

			channel_index red;
			channel_index green;
			channel_index blue;
			channel_index alpha;
		};

	public :
		Image();

		//! @param width Width of image.
		//! @param height Height of image.
		//! @param num_chan Number of channels in each pixel.
		//! @param pitch The distance in bytes from the start of one row to the next in 'data'.
		//! @param data Linear image data.
		Image( int width, int height, int num_chan, const channel* const * src, const channel_order& co = channel_order() );
		Image( int width, int height, int num_chan, const channel_order& co = channel_order() );
		virtual ~Image();

	public :
		int get_width() const;
		int get_height() const;
		int get_num_channels() const;

	public :
		void set_pixel( int x, int y, const pixel& p );
		pixel get_pixel( int x, int y ) const;

	public :
		const channel* get_row_ptr( int row ) const;
		channel* get_row_ptr( int row );
		int get_pitch() const;

	private :
		const channel* get_pixel_ptr( int x, int y ) const;
		channel* get_pixel_ptr( int x, int y );

	public :
		const channel_order& get_channel_order() const
		{
			return co_;
		}

	public :
		void swap( Image& rhs );

	private :
		int width_;
		int height_;
		int num_chan_;
		channel_order co_;

		typedef std::vector< channel > Bitmap;
		Bitmap bitmap_;

		void copy_from_bitmap( int width, int height, int num_chan, const channel* const src, int src_pitch );
		void copy_from_scanlines( int width, int height, int num_chan, const channel* const * src );
	};


	template <typename T>
	void swap( T& a, T& b ) {
		a.swap( b );
	}

}
