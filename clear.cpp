#include "pico/stdlib.h"
#include "pico-ssd1306/ssd1306.h"
#include "hardware/i2c.h"

int main()
{
    const uint8_t SDA_PIN = PICO_DEFAULT_I2C_SDA_PIN;
    const uint8_t SCL_PIN = PICO_DEFAULT_I2C_SCL_PIN;
    i2c_init(i2c0, 1000 * 1000); //Use i2c port with baud rate of 1Mhz
    //Set pins for I2C operation
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    //Create a new display object
    pico_ssd1306::SSD1306 display = pico_ssd1306::SSD1306(i2c0, 0x3C, pico_ssd1306::Size::W128xH64);

    display.clear();
    display.sendBuffer();
    /*while (1)
    {
        for (int y = 0; y < 64; y += 2)
        {
            for (int x = 0; x < 128; x += 2)
            {
                display.setPixel(x, y, pico_ssd1306::WriteMode::INVERT);
                display.sendBuffer(); //Send buffer to device and show on screen
            }
        }
    }*/
}