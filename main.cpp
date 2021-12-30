#include "pico/stdlib.h"
#include "pico-ssd1306/ssd1306.h"
#include "pico-ssd1306/textRenderer/TextRenderer.h"
#include "pico-ssd1306/shapeRenderer/ShapeRenderer.h"
#include "hardware/i2c.h"
#include "stdio.h"

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

    sleep_ms(250);

    //Create a new display object
    pico_ssd1306::SSD1306 display = pico_ssd1306::SSD1306(i2c0, 0x3C, pico_ssd1306::Size::W128xH64);

    display.clear();
    char text[4];
    while (1)
    {
        for (int i = 0; i < 128; i++)
        {
            display.clear();
            // Draw Control Frame
            drawRect(&display, 1, 1, 41, 17);
            fillRect(&display, 2, 2, i * 40 / 128, 16);
            sprintf(text, "%3d", i);
            drawText(&display, font_12x16, text, 42, 1, pico_ssd1306::WriteMode::ADD);
            display.sendBuffer();
            sleep_ms(100);
        }
        display.clear();
        display.sendBuffer();
        sleep_ms(1000);
    }
    /*
    while (1)
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