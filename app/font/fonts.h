#ifndef __FONT_H
#define __FONT_H

#include <stdint.h>

//ASCII 字模
//!"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~

typedef struct {
    const uint8_t width;
    uint8_t height;
    const uint16_t *data;
} FontDef;

typedef struct {
    const char *name;       
    const uint8_t *model;
} font_chinese_t;

// 字体描述符：打包一套字体的所有差异信息，供 ST7789_DrawString 使用
typedef struct {
    const font_chinese_t *model;  // 字模数组（汉字在前，ASCII 在后）
    uint8_t cn_count;             // 汉字数量（无汉字则为 0）
    uint8_t ascii_min;            // ASCII 首字符码
    uint8_t ascii_count;          // ASCII 字模数量
    uint8_t cn_w, cn_h;           // 汉字点阵宽高
    uint8_t ascii_w, ascii_h;     // ASCII 点阵宽高
} font_def_t;


extern const font_def_t font_16;
extern const font_def_t font_20;
extern const font_def_t font_24_semibold;
extern const font_def_t font_24_bold;
extern const font_def_t font_32;
extern const font_def_t font_54_semibold;
extern const font_def_t font_54_bold;
extern const font_def_t font_64;
extern const font_def_t font_76;

//Font lib.
extern FontDef Font_7x10;
extern FontDef Font_11x18;
extern FontDef Font_16x26;


extern const font_chinese_t chinese_model_16[];
extern const font_chinese_t chinese_model_20[];
extern const font_chinese_t chinese_model_24_semibold[];
extern const font_chinese_t chinese_model_24_bold[];
extern const font_chinese_t chinese_model_32[];
extern const font_chinese_t chinese_model_54_semibold[];
extern const font_chinese_t chinese_model_54_bold[];
extern const font_chinese_t chinese_model_64[];
extern const font_chinese_t chinese_model_76[];

//16-bit(RGB565) Image lib.
/*******************************************
 *             CAUTION:
 *   If the MCU onchip flash cannot
 *  store such huge image data,please
 *           do not use it.
 * These pics are for test purpose only.
 *******************************************/

/* 128x128 pixel RGB565 image */
extern const uint16_t saber[][128];

/* 160x160 pixel RGB565 image */
extern const unsigned char gImage_error[51200]; 

/* 180x180 pixel RGB565 image */
extern const unsigned char gImage_hua[64800];

/* 180x164 pixel RGB565 image */
extern const unsigned char gImage_wifi[59040];

/* 240x240 pixel RGB565 image 
extern const uint16_t knky[][240];
extern const uint16_t tek[][240];
extern const uint16_t adi1[][240];
*/

/* weather pixel RGB565 image */
extern const unsigned char gImage_icon_wifi[1152];
extern const unsigned char gImage_icon_wenduji[2142];
extern const unsigned char gImage_icon_qing[5832];
extern const unsigned char gImage_icon_yintian[5832];
extern const unsigned char gImage_icon_yueliang[5832];
extern const unsigned char gImage_icon_zhongxue[5832];
extern const unsigned char gImage_icon_duoyun[5832];
extern const unsigned char gImage_icon_leizhenyu[5832];
extern const unsigned char gImage_icon_zhongyu[5832];
extern const unsigned char gImage_icon_na[5832];


#endif
