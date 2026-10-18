#include "fonts.h"

const font_chinese_t chinese_model_16[] =
{
    {
        .name = " ",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "!",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X18,0X18,0X18,0X18,0X18,0X18,0X00,0X18,0X18,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "\"",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X24,0X24,0X24,0X24,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "#",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X34,0X24,0X7E,0XFF,0X24,0X24,0XFF,0X24,0X2C,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "$",
        .model = (const uint8_t[]) {
            0X00,0X00,0X18,0X3C,0X7E,0X58,0X60,0X3C,0X26,0X1A,0X5A,0X3C,0X18,0X00,0X00,0X00,
        }
    },
    {
        .name = "%",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X70,0X53,0XD6,0X74,0X20,0X2E,0X6B,0X4B,0X8E,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "&",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X38,0X6C,0X40,0X20,0X50,0X4A,0X4A,0X44,0X7B,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "'",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X18,0X18,0X18,0X18,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "(",
        .model = (const uint8_t[]) {
            0X00,0X00,0X0C,0X18,0X10,0X30,0X20,0X20,0X20,0X20,0X30,0X10,0X08,0X04,0X00,0X00,
        }
    },
    {
        .name = ")",
        .model = (const uint8_t[]) {
            0X00,0X00,0X30,0X18,0X08,0X0C,0X04,0X04,0X04,0X04,0X0C,0X18,0X10,0X20,0X00,0X00,
        }
    },
    {
        .name = "*",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X18,0X5A,0X3C,0X3C,0X5A,0X18,0X00,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "+",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X18,0X18,0X7E,0X7E,0X18,0X18,0X00,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = ",",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X18,0X18,0X08,0X18,0X60,0X00,
        }
    },
    {
        .name = "-",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X3C,0X7E,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = ".",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X18,0X18,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "/",
        .model = (const uint8_t[]) {
            0X00,0X00,0X02,0X04,0X04,0X0C,0X08,0X18,0X10,0X10,0X30,0X20,0X60,0X40,0X00,0X00,
        }
    },
    {
        .name = "0",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X3C,0X26,0X42,0X4E,0X5A,0X72,0X62,0X66,0X3C,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "1",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X18,0X68,0X48,0X08,0X08,0X08,0X08,0X08,0X7E,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "2",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X3C,0X46,0X02,0X06,0X04,0X08,0X10,0X60,0X7E,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "3",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X38,0X44,0X06,0X04,0X3C,0X06,0X02,0X06,0X7C,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "4",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X04,0X0C,0X14,0X34,0X24,0X64,0X7E,0X04,0X04,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "5",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X3E,0X60,0X60,0X60,0X3C,0X06,0X02,0X06,0X7C,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "6",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X08,0X10,0X20,0X68,0X76,0X42,0X42,0X62,0X3C,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "7",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X7E,0X02,0X04,0X04,0X0C,0X08,0X18,0X10,0X30,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "8",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X3C,0X66,0X42,0X66,0X3C,0X42,0X42,0X42,0X3C,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "9",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X3C,0X66,0X42,0X42,0X66,0X3A,0X04,0X08,0X10,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = ":",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X00,0X18,0X18,0X00,0X00,0X18,0X18,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = ";",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X00,0X18,0X18,0X00,0X00,0X18,0X18,0X08,0X18,0X60,0X00,
        }
    },
    {
        .name = "<",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X06,0X1C,0X70,0X70,0X1C,0X06,0X00,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "=",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X00,0X7E,0X00,0X00,0X7E,0X00,0X00,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = ">",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X60,0X38,0X0E,0X0E,0X38,0X60,0X00,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "?",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X3C,0X26,0X42,0X06,0X08,0X18,0X00,0X18,0X18,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "@",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X7C,0X86,0X22,0X7A,0X4B,0X48,0X48,0X6F,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "A",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X18,0X18,0X18,0X24,0X24,0X24,0X7E,0X42,0X42,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "B",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X7C,0X66,0X42,0X46,0X7C,0X42,0X42,0X46,0X7C,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "C",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X1C,0X22,0X40,0X40,0X40,0X40,0X40,0X20,0X3E,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "D",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X78,0X64,0X42,0X42,0X42,0X42,0X42,0X44,0X7C,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "E",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X3E,0X60,0X60,0X60,0X7E,0X60,0X60,0X60,0X7E,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "F",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X7E,0X60,0X40,0X40,0X7E,0X40,0X40,0X40,0X40,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "G",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X3C,0X66,0X42,0X40,0X4E,0X42,0X42,0X66,0X3C,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "H",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X42,0X42,0X42,0X42,0X7E,0X42,0X42,0X42,0X42,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "I",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X7E,0X18,0X18,0X18,0X18,0X18,0X18,0X18,0X7E,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "J",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X3C,0X06,0X06,0X06,0X06,0X06,0X46,0X44,0X3C,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "K",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X46,0X44,0X48,0X50,0X70,0X78,0X4C,0X44,0X42,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "L",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X3E,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "M",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X66,0X66,0X66,0X5A,0X5A,0X5A,0X42,0X42,0X42,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "N",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X62,0X62,0X52,0X52,0X5A,0X4A,0X4A,0X46,0X46,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "O",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X3C,0X64,0X42,0X42,0X42,0X42,0X42,0X66,0X3C,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "P",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X7C,0X66,0X42,0X42,0X7C,0X40,0X40,0X40,0X40,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "Q",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X3C,0X64,0X42,0X42,0X42,0X42,0X42,0X66,0X3C,0X00,0X0E,0X00,0X00,
        }
    },
    {
        .name = "R",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X7C,0X66,0X42,0X42,0X7C,0X48,0X44,0X46,0X42,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "S",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X3C,0X66,0X40,0X60,0X1C,0X06,0X02,0X62,0X3C,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "T",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X7E,0X18,0X18,0X18,0X18,0X18,0X18,0X18,0X18,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "U",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X42,0X42,0X42,0X42,0X42,0X42,0X42,0X66,0X3C,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "V",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X42,0X42,0X66,0X24,0X24,0X24,0X18,0X18,0X18,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "W",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X42,0XC3,0X5A,0X5A,0X5A,0X5A,0X6A,0X66,0X66,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "X",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X42,0X24,0X24,0X18,0X18,0X18,0X24,0X24,0X42,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "Y",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X42,0X42,0X24,0X24,0X18,0X18,0X18,0X18,0X18,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "Z",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X7E,0X06,0X04,0X08,0X18,0X10,0X20,0X60,0X7E,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "[",
        .model = (const uint8_t[]) {
            0X00,0X00,0X3C,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X3C,0X00,0X00,
        }
    },
    {
        .name = "\\",
        .model = (const uint8_t[]) {
            0X00,0X00,0X40,0X20,0X20,0X30,0X10,0X18,0X08,0X08,0X0C,0X04,0X06,0X02,0X00,0X00,
        }
    },
    {
        .name = "]",
        .model = (const uint8_t[]) {
            0X00,0X00,0X3C,0X04,0X04,0X04,0X04,0X04,0X04,0X04,0X04,0X04,0X04,0X3C,0X00,0X00,
        }
    },
    {
        .name = "^",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X18,0X18,0X24,0X66,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "_",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7E,0X00,0X00,
        }
    },
    {
        .name = "`",
        .model = (const uint8_t[]) {
            0X00,0X00,0X20,0X10,0X0C,0X08,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "a",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X1A,0X26,0X64,0X44,0X46,0X46,0X3A,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "b",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X40,0X40,0X58,0X64,0X62,0X42,0X42,0X66,0X5C,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "c",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X1C,0X36,0X40,0X40,0X40,0X60,0X3E,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "d",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X02,0X02,0X1A,0X26,0X46,0X42,0X42,0X66,0X3A,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "e",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X18,0X24,0X42,0X7E,0X40,0X64,0X3E,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "f",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X0E,0X10,0X10,0X7E,0X10,0X10,0X10,0X10,0X10,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "g",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X1A,0X26,0X46,0X42,0X42,0X66,0X3A,0X02,0X64,0X3C,0X00,
        }
    },
    {
        .name = "h",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X40,0X40,0X58,0X66,0X66,0X42,0X42,0X42,0X42,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "i",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X18,0X00,0X00,0X78,0X08,0X08,0X08,0X08,0X7E,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "j",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X0C,0X00,0X00,0X3C,0X04,0X04,0X04,0X04,0X04,0X04,0X4C,0X38,0X00,
        }
    },
    {
        .name = "k",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X60,0X60,0X62,0X6C,0X78,0X78,0X6C,0X64,0X62,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "l",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X70,0X10,0X10,0X10,0X10,0X10,0X10,0X10,0X0E,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "m",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X76,0X5A,0X5A,0X5A,0X5A,0X5A,0X5A,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "n",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X58,0X66,0X66,0X42,0X42,0X42,0X42,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "o",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X18,0X24,0X42,0X42,0X42,0X66,0X3C,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "p",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X5C,0X76,0X42,0X42,0X42,0X66,0X5C,0X40,0X40,0X00,0X00,
        }
    },
    {
        .name = "q",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X3A,0X6E,0X42,0X42,0X42,0X66,0X3A,0X02,0X02,0X00,0X00,
        }
    },
    {
        .name = "r",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X2C,0X76,0X62,0X60,0X60,0X60,0X60,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "s",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X18,0X66,0X60,0X3C,0X06,0X42,0X3C,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "t",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X10,0X10,0X7E,0X10,0X10,0X10,0X10,0X1E,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "u",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X42,0X42,0X42,0X42,0X42,0X66,0X3A,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "v",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X42,0X42,0X24,0X24,0X3C,0X18,0X18,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "w",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X42,0XC3,0X5A,0X5A,0X5A,0X66,0X66,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "x",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X42,0X24,0X3C,0X18,0X18,0X24,0X66,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "y",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X42,0X62,0X26,0X24,0X3C,0X18,0X18,0X18,0X30,0X60,0X00,
        }
    },
    {
        .name = "z",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X3C,0X46,0X0C,0X18,0X10,0X20,0X7E,0X00,0X00,0X00,0X00,
        }
    },
    {
        .name = "{",
        .model = (const uint8_t[]) {
            0X00,0X00,0X0E,0X10,0X10,0X10,0X18,0X70,0X10,0X18,0X10,0X10,0X18,0X0E,0X00,0X00,
        }
    },
    {
        .name = "|",
        .model = (const uint8_t[]) {
            0X00,0X00,0X18,0X18,0X18,0X18,0X18,0X18,0X18,0X18,0X18,0X18,0X18,0X10,0X00,0X00,
        }
    },
    {
        .name = "}",
        .model = (const uint8_t[]) {
            0X00,0X00,0X70,0X08,0X08,0X08,0X18,0X0E,0X08,0X18,0X08,0X08,0X18,0X70,0X00,0X00,
        }
    },
    {
        .name = "~",
        .model = (const uint8_t[]) {
            0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X72,0X4E,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
        }
    },
    {0}
};

// 纯 ASCII：{ 数组, 汉字数, ASCII首字符码, ASCII数, 汉字宽, 汉字高, ASCII宽, ASCII高 }
const font_def_t font_16 = { chinese_model_16, 0, 0x20, 95, 0, 0, 8, 16 };