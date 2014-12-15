#pragma once
#include "BasicTypes.hpp"
#include <array>
#include <cstring>

namespace raytracer {

	template <unsigned int Count, unsigned int ChannelOffset>
	struct CopyRow {
		static void exec(unsigned char* dest, const unsigned char* src) {
			dest[0 + ChannelOffset] = src[0];
			dest[1 + ChannelOffset] = src[1];
			dest[2 + ChannelOffset] = src[2];
			dest[(3 + ChannelOffset)%4] = 255;
			CopyRow<Count - 1, ChannelOffset>::execRgba(dest + 4, src + 3);
		}

	};

	template<unsigned int ChannelOffset>
	struct CopyRow<0, ChannelOffset> {
		static void exec(unsigned char*, const unsigned char*) { 
		}
	};
		 

	template <unsigned int BlockSize = 8>
	class RgbBlock {
		static const unsigned int NumChannels = 3;
		static const unsigned int Pitch = BlockSize * NumChannels;

	public :
		RgbBlock( const Point2d<unsigned int>& screenPosition )
			: pos_(screenPosition.x*BlockSize, screenPosition.y*BlockSize) {} 

	public :
		const Point2d<unsigned int>& getPosition() const { return pos_; }

	public:
		void setPixel(unsigned int x, unsigned int y, const Color& color) {

			if (x < BlockSize && y < BlockSize) {

				pixels_[x * NumChannels + y*Pitch + 0] = static_cast<unsigned char>(Float(255)*color[0]);
				pixels_[x * NumChannels + y*Pitch + 1] = static_cast<unsigned char>(Float(255)*color[1]);
				pixels_[x * NumChannels + y*Pitch + 2] = static_cast<unsigned char>(Float(255)*color[2]);
			}
		}

		void copyToRgb(unsigned char* dest, unsigned int pitch) const {

			const unsigned char* src = &pixels_[0];
			for (size_t i = 0; i < BlockSize; ++i) {

				std::memcpy(dest, src, BlockSize * 3);
				dest += pitch;
				src += Pitch;
			}
		}

		void copyToRgba(unsigned char* dest, unsigned int pitch) const {

			const unsigned char* src = &pixels_[0];
			for (size_t i = 0; i < BlockSize; ++i) {

				CopyRow<BlockSize, 0>::exec(dest, src);
				dest += pitch;
				src += Pitch;
			}

		}

	private:
		std::array<unsigned char, BlockSize> pixels_;
		Point2d<unsigned int> pos_;
	};

	class RayTracerOutput {
	public:
		virtual ~RayTracerOutput() {}

		void submitBlock(const RgbBlock<8>& block) {
		}

		virtual bool getBlock(RgbBlock<8>&) = 0;

	private:
	};

}
