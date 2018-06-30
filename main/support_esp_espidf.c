#include "mjd.h"

#include "driver/ledc.h"

/*
 * Logging
 */
static const char TAG[] = "myapp";

/*
 * GPIO selector (Adafruit HUZZAH32)
 */
#define GPIO_NUM_OUTPUT_SOLO   (GPIO_NUM_14)

/*
 * MAIN
 */
void app_main() {
    ESP_LOGD(TAG, "%s()", __FUNCTION__);

    /*
     * LEDC PWM
     */
    int32_t j;
    int32_t freq;
    int32_t duty;

    freq = 60;
    duty = 255;
    ESP_LOGI(TAG, "=== LEDC: ledc_timer_config(LEDC_TIMER_8_BIT) ledc_channel_config() freq=%i | duty = %i", freq, duty);
    ledc_timer_config_t ledc_timer =
        { .speed_mode = LEDC_HIGH_SPEED_MODE,     // LEDC speed speed_mode, high-speed mode or low-speed mode
                .timer_num = LEDC_TIMER_0,              // The timer source of channel (0 - 3)
                .duty_resolution = LEDC_TIMER_8_BIT,    // range 0..255
                .freq_hz = freq,                        // changes/second
            };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));
    ledc_channel_config_t ledc_channel =
        { .timer_sel = LEDC_TIMER_0, .speed_mode = LEDC_HIGH_SPEED_MODE, .channel = LEDC_CHANNEL_0, .gpio_num =
        GPIO_NUM_OUTPUT_SOLO, .duty = duty };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

    ESP_ERROR_CHECK(ledc_fade_func_install(0));

    // Problem: no fading
    for (j=0; j < 2; ++j) {
        duty = 0;
        ESP_LOGI(TAG,"=== freq=%i | vary duty 0..255 using ledc_set_fade_with_time(5 seconds)", freq);
        ESP_LOGI(TAG,"  Set duty := 0");
        ESP_LOGE(TAG,"  ***PROBLEM ledc_set_fade_with_time() does not fade. It starts at duty 255 instead of duty 0 and so ends right away");
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, duty));
        ESP_ERROR_CHECK(ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0));
        //ESP_LOGI(TAG, "   FIX: wait 1 second after updating duty...");
        //vTaskDelay(RTOS_DELAY_1SEC);
        ESP_ERROR_CHECK(ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 255, 5 * 1000));
        ESP_ERROR_CHECK(ledc_fade_start(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, LEDC_FADE_WAIT_DONE));
    }

    // Fix: add delay 1 second after updating duty
    for (j=0; j < 2; ++j) {
        duty = 0;
        ESP_LOGI(TAG,"=== freq=%i | vary duty 0..255 using ledc_set_fade_with_time(5 seconds)", freq);
        ESP_LOGI(TAG,"  Set duty := 0");
        ESP_LOGI(TAG,"  ***OK when using a delay of 1 second after updating duty...***");
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, duty));
        ESP_ERROR_CHECK(ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0));
        ESP_LOGI(TAG, "   FIX: wait 1 second after updating duty...");
        vTaskDelay(RTOS_DELAY_1SEC);
        ESP_ERROR_CHECK(ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 255, 5 * 1000));
        ESP_ERROR_CHECK(ledc_fade_start(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, LEDC_FADE_WAIT_DONE));
    }

    ledc_fade_func_uninstall();
}
