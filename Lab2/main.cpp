#include <iostream>
#include <cstdlib>
#include <Magick++.h>
#include <memory>
#include <random>

const size_t width = 100;
const size_t height = 100;
const size_t pixelDepth = 3;


//void setPixel(size_t _x, size_t _y, unsigned char _r,
//              unsigned char _g, unsigned char _b,
//              std::unique_ptr<unsigned char []> &_image)
//{
//    auto offset = (_y*width)*3+(_x*3);
//    _image[offset]=_r;
//    _image[offset+1]=_g;
//    _image[offset+2]=_b;
//}


int main()
{

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> colour(0,255);

    std::unique_ptr<unsigned char []> image
            =std::make_unique<unsigned char[]>(width*height*pixelDepth);

    auto setPixel=[&image](size_t _x, size_t _y, unsigned char _r,
            unsigned char _g, unsigned char _b)
    {
        auto offset = (_y*width)*3+(_x*3);
        image[offset]=_r;
        image[offset+1]=_g;
        image[offset+2]=_b;
    };
    for(size_t i = 0; i<width*height*pixelDepth; ++i)
        image[i] = 500;

    char fileName[20];
    for(size_t frame =0; frame<100;++frame)
    {

        for(size_t y=0; y<height; ++y)
            for(size_t x=0; x<width; ++x)
                setPixel(x, y, colour(gen), colour(gen), colour(gen));
        sprintf(fileName,"image.%03d.bmp", frame);
        Magick::Image output(width,height,"RGB",Magick::CharPixel,image.get());
        output.depth(16);
        std::cerr<<"Writing file "<<fileName<<'\n';
        output.write(fileName);
    }

    return EXIT_SUCCESS;
}
