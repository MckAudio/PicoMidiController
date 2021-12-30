#include "pico/stdlib.h"
#include "pico-ssd1306/ssd1306.h"
#include "pico-ssd1306/textRenderer/TextRenderer.h"
#include "pico-ssd1306/shapeRenderer/ShapeRenderer.h"
#include "hardware/i2c.h"
#include "stdio.h"
#include "math.h"

int get_encoder_dir(int DT_PIN, int CLK_PIN)
{
    static bool turning = false;
    static bool clkWise = false;
    bool dt = gpio_get(DT_PIN);
    bool clk = gpio_get(CLK_PIN);
    int ret = 0;

    if (turning)
    {
        if (dt && clk)
        {
            if (clkWise)
            {
                ret = 1;
            }
            else
            {
                ret = -1;
            }
            turning = false;
        }
    }
    else
    {
        turning = dt != clk;
        clkWise = dt && clk == false;
    }
    return ret;
}

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

    // Set up encoder
    const uint DT_PIN = 14;
    const uint CLK_PIN = 15;
    const uint SW_PIN = 16;
    gpio_init(DT_PIN);
    gpio_set_dir(DT_PIN, GPIO_IN);
    gpio_init(CLK_PIN);
    gpio_set_dir(CLK_PIN, GPIO_IN);
    gpio_init(SW_PIN);
    gpio_set_dir(SW_PIN, GPIO_IN);

    // Set up stdio
    stdio_init_all();
    int counter = 64;
    int oldCounter = 64;
    int minCounter = 0;
    int maxCounter = 127;
    int dir = 0;
    bool sw = true;
    bool switching = false;

    sleep_ms(250);

    //Create a new display object
    pico_ssd1306::SSD1306 display = pico_ssd1306::SSD1306(i2c0, 0x3C, pico_ssd1306::Size::W128xH64);

    display.clear();
    char text[4];
    while (1)
    {
        dir = get_encoder_dir(DT_PIN, CLK_PIN);
        sw = gpio_get(SW_PIN);
        counter = fmax(minCounter, fmin(maxCounter, counter + dir));

        if (sw)
        {
            switching = true;
        }
        else if (switching)
        {
            switching = false;
            counter = counter == minCounter ? maxCounter : minCounter;
        }
        if (counter != oldCounter)
        {
            display.clear();
            // Draw Control Frame
            drawRect(&display, 1, 1, 41, 17);
            fillRect(&display, 2, 2, counter * 40 / 128, 16);
            sprintf(text, "%3d", counter);
            drawText(&display, font_12x16, text, 42, 1, pico_ssd1306::WriteMode::ADD);
            display.sendBuffer();
            oldCounter = counter;
        }

        sleep_ms(1);
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