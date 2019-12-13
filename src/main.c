#include "ssd1366.h"

void app_main(void)
{
    i2c_master_init();
	ssd1306_init();

    char str[30];
	int s = 0, m = 0, h = 0;
	
	xTaskCreate(&task_ssd1306_display_clear, "ssd1306_display_clear",  2048, NULL, 6, NULL);
	vTaskDelay(100/portTICK_PERIOD_MS);
	while(1)
	{
		sprintf(str, "Time: %d:%d:%d", h, m, ++s);
		if(s == 60)
		{
			s = 0;
			m++;
		}
		if(m == 60)
		{
			m = 0;
			h++;
		}
		if(h == 24)
		{
			h = 0;
		}
		vTaskDelay(1000/portTICK_PERIOD_MS);
		xTaskCreate(&task_ssd1306_display_text, "ssd1306_display_text",  2048,
		(void *)str, 6, NULL);
	}
}