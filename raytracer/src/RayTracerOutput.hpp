#pragma once
#include <array>
#include <cstring>

namespace raytracer {

	template <unsigned int BlockSize = 8>
	class RgbBlock
	{
		static const unsigned int NumChannels = 3;
		static const unsigned int Pitch = BlockSize * NumChannels;

	public:
		void setPixel(unsigned int x, unsigned int y, const Color& color)
		{
			if (x < BlockSize && y < BlockSize)
			{
				pixels_[x * NumChannels + y*Pitch + 0] = static_cast<unsigned char>(Float(255)*color[0]);
				pixels_[x * NumChannels + y*Pitch + 1] = static_cast<unsigned char>(Float(255)*color[1]);
				pixels_[x * NumChannels + y*Pitch + 2] = static_cast<unsigned char>(Float(255)*color[2]);
			}
		}

		void copyToRgb(unsigned char* dest, unsigned int pitch) const
		{
			const unsigned char* src = &pixels_[0];
			for (size_t i = 0; i < BlockSize; ++i)
			{
				std::memcpy(dest, src, BlockSize * 3);
				dest += pitch;
				src += Pitch;
			}
		}

	private:
		std::array<unsigned char, BlockSize> pixels_;
	};

	class RayTracerOutput
	{
	public:
		virtual ~RayTracerOutput() {}

		virtual void copyBlock(const RgbBlock<8>&, unsigned int x, unsigned int y) = 0;

	private:
	};

}
