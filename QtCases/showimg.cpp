#include "showimg.h"

ShowImage::ShowImage()
{
}

ShowImage::~ShowImage()
{
}

unsigned char* pixels = NULL;
png_uint_32 width, height;
int color_type;

//获取每一行所用的字节数，需要凑足4的倍数  
int getRowBytes(int width) {
    //刚好是4的倍数  
    if ((width * 3) % 4 == 0) {
        return width * 3;
    }
    else {
        return ((width * 3) / 4 + 1) * 4;
    }
}

int ShowImage::setPixels(const char* filename)
{
    png_structp png_ptr;
    png_infop info_ptr;
    int bit_depth;
    FILE *fp;

    qDebug() << "lpng16(" << PNG_LIBPNG_VER_STRING << "), zlib(" << ZLIB_VERSION << ")";

    if ((fp = fopen(filename, "rb")) == NULL) {
        return EXIT_FAILURE;
    }
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL)
    {
        fclose(fp);
        return EXIT_FAILURE;
    }
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL)
    {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        return EXIT_FAILURE;
    }
    if (setjmp(png_jmpbuf(png_ptr))) {
        /* Free all of the memory associated with the png_ptr and info_ptr */
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        /* If we get here, we had a problem reading the file */
        return EXIT_FAILURE;
    }
    /* Set up the input control if you are using standard C streams */
    png_init_io(png_ptr, fp);
    //读取PNG文件  
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);
    //获取PNG图片相关信息  
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
        NULL, NULL, NULL);
    qDebug() << "[" << width << "*" << height << "]";
    width = width / 2 + 520;
    height = height / 2 + 234;
    //获得所有PNG数据  
    png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);
    //计算pixel大小  
    unsigned int size = 0;
    if (color_type == PNG_COLOR_TYPE_RGB) {
        size = getRowBytes(width) * height;
    }
    else if (color_type == PNG_COLOR_TYPE_RGBA) {
        size = width * height * 4;
    }
    else {
        return EXIT_FAILURE;
    }
    //申请堆空间  
    pixels = (unsigned char*)malloc(size);
    int i;
    for (i = 0; i < height; i++) {
        //拷贝每行的数据到pixel，  
        //opengl原点在下方，拷贝时要倒置一下  
        if (color_type == PNG_COLOR_TYPE_RGB) {
            memcpy(pixels + getRowBytes(width) * i, row_pointers[height - i - 1], width * 3);
        }
        else if (color_type == PNG_COLOR_TYPE_RGBA) {
            memcpy(pixels + i * width * 4, row_pointers[height - i - 1], width * 4);
        }
    }
    png_destroy_read_struct(&png_ptr, &info_ptr, 0);
    fclose(fp);
    return EXIT_SUCCESS;
}

GLuint ShowImage::CreateTextureFromPng(const char* filename)
{
    unsigned char header[8];     //8  
    int k;   //循环计数  
    GLuint textureID; //贴图名字  
    int width, height; //记录图片到宽和高  
    png_byte color_type; //图片到类型（会用在是否是开启来通道）  
    png_byte bit_depth; //字节深度  

    png_structp png_ptr; //图片  
    png_infop info_ptr; //图片的信息  
    int number_of_passes; //隔行扫描  
    png_bytep * row_pointers;//图片的数据内容  
    int row, col, pos;  //改变png像素排列的问题。  
    GLubyte *rgba;

    FILE *fp = fopen(filename, "rb");//以只读形式打开文件名为file_name的文件  
    if (NULL == fp)//做出相应可能的错误处理  
    {
        printf("error: %s\n", strerror(errno));//关闭打开的文件！给出默认贴图  
        return 0;//应该调用一个生成默认贴图返回ID的函数  
    }
    //读取文件头判断是否是PNG格式图片.不是则做出相应处理  
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8))
    {
        fclose(fp);
        return 0; //每个错误处理都是一样的！  
    }

    //根据libpng的libpng-manual.txt的说明使用文档 接下来必须初始化png_structp 和 png_infop  
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL); //后三个是绑定错误以及警告的函数这里设置为空  
    if (!png_ptr)//做出相应到初始化失败的处理  
    {
        fclose(fp);
        return 0;
    }
    //根据初始化的png_ptr初始化png_infop  
    info_ptr = png_create_info_struct(png_ptr);

    if (!info_ptr)
    {
        //初始化失败以后销毁png_structp  
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        fclose(fp);
        return 0;
    }

    //按照libpng给到的说明稳定步骤错误处理
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        //释放占用的内存！然后关闭文件返回一个贴图ID
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        fclose(fp);
        return 0;
    }
    //通过i/o定制函数png_init_io打开文件 
    png_init_io(png_ptr, fp);
    //告诉libpng文件从第几个开始missing  
    png_set_sig_bytes(png_ptr, 8);
    //简单的操作读取实际图片信息
    png_read_info(png_ptr, info_ptr);
    //获得图片到信息 width height 颜色类型  字节深度  
    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
    //如果图片带有alpha通道调用  
    // if (color_type == PNG_COLOR_TYPE_RGB_ALPHA)  
    // png_set_swap_alpha(png_ptr);  
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    //隔行扫描图片 
    number_of_passes = png_set_interlace_handling(png_ptr);
    //将读取到的信息更新到info_ptr  
    png_read_update_info(png_ptr, info_ptr);
    //读文件  
    if (setjmp(png_jmpbuf(png_ptr))) {
        fclose(fp);
        return 0;
    }
    rgba = (GLubyte*)malloc(width * height * 4);
    //使用动态数组  设置长度  
    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);

    for (k = 0; k < height; k++)
        row_pointers[k] = NULL;

    //通过扫描流里面的每一行将得到的数据赋值给动态数组         
    for (k = 0; k < height; k++)
        //row_pointers[k] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));  
        row_pointers[k] = (png_bytep)png_malloc(png_ptr, png_get_rowbytes(png_ptr,
            info_ptr));
    //由于PNG的像素是由 左-右-从顶到底 而贴图需要的像素都是 左-右-从底到顶 的所以需要把像素内容进行一个从新排列 读图片  
    png_read_image(png_ptr, row_pointers);

    pos = (width * height * 4) - (4 * width);
    for (row = 0; row < height; row++)
    {
        for (col = 0; col < (4 * width); col += 4)
        {
            rgba[pos++] = row_pointers[row][col];        // red  
            rgba[pos++] = row_pointers[row][col + 1];    // green  
            rgba[pos++] = row_pointers[row][col + 2];    // blue  
            rgba[pos++] = row_pointers[row][col + 3];    // alpha  
        }
        pos = (pos - (width * 4) * 2);
    }

    //开启纹理贴图特效  
    glEnable(GL_TEXTURE_2D);
    //创建纹理   
    glGenTextures(1, &textureID);
    //绑定纹理  
    glBindTexture(GL_TEXTURE_2D, textureID); //将纹理绑定到名字  
                                             //设置贴图和纹理的混合效果 默认只用纹理  
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    //设置纹理所用到图片数据  
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba);

    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    free(row_pointers);
    fclose(fp);
    return textureID;
}

void ShowImage::loadGLTextures(const char* filename)
{
    if (filename == NULL)
        return;
#ifdef QT_GUI_LIB
    QImage tex, buf;
    if (!buf.load(filename))
    {
        qWarning("Could not read image file, using single-color instead.");
        QImage dummy(128, 128, QImage::Format_RGB32);
#ifdef QCOLOR_H
        dummy.fill(QColor("darkCyan").rgb());
#endif
        buf = dummy;
    }
#ifdef QGL_H
    tex = QGLWidget::convertToGLFormat(buf);
#endif
    glGenTextures(3, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0,
        GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0,
        GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
#endif
}

void ShowImage::Show(const char* filename)
{
    if (filename == NULL)
        return;
    glEnable(GL_TEXTURE_2D);
    if (NULL == texture[0])
        texture[0] = CreateTextureFromPng(filename);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

//显示图片  
void ShowImage::Show() {
    glDisable(GL_DEPTH_TEST);
    //图片是否有透明度  
    if (color_type == PNG_COLOR_TYPE_RGB) {
        glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    }
    else if (color_type == PNG_COLOR_TYPE_RGBA) {
        glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    }
    glFlush();
    glEnable(GL_DEPTH_TEST);
}
