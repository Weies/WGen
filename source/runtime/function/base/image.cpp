#include"image.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stbi/stb_image.h"
#include"stbi/stb_image_resize.h"

void Image::load(const string& filepath, bool flip)
{
	stbi_set_flip_vertically_on_load(flip);
	if (mData)free(), mData = 0;
	mData = stbi_load(filepath.c_str(), &w, &h, &mNumChannels, 0);
	if (!mData)excep(WERROR_FILE_LOAD, "Wrong when load image,file not found: " + filepath);
}