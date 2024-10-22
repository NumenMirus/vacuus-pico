
// Define SPI pins
#define SD_SPI spi0
#define SD_MISO 16
#define SD_MOSI 19
#define SD_SCK 18
#define SD_CS 17
#define SD_BAUDRATE 12500 * 1000 // 1 MHz
#define SD_DETECT 29

bool test_sd_card();