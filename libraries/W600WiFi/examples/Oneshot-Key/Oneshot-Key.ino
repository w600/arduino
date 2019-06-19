#include <Arduino.h>
#include <W600WiFi.h>

int start_oneshot()
{
	int i = 0;

	WiFi.oneshotSetMode(ONESHOT_UDP);
	WiFi.oneshotStart();
	printf("oneshot state:%d\n", WiFi.oneshotGetState());
	printf("oneshot Mode:%d\n", WiFi.oneshotGetMode());
	while(i++ < 50)
	{
		delay(1000);
		if(0 == WiFi.oneshotGetState())
			return 0;
	}
	WiFi.oneshotStop();
	printf("oneshot time out, over\n");
}

void w600_arduino_setup()
{
	int val = 1;
	int press_secs = 0;
	while (1)
	{
		press_secs = 0;
		do {
			val = digitalRead(USER_BTN);
			press_secs ++;
			delay(1000);
		} while (val == USER_BTN_PRESS
			&& press_secs < 5);
		if (press_secs >= 5)
		{
			start_oneshot();
		} else {
			Serial.println("Please press USER_BTN for at leaset 5 seconds...");
		}
	}
}

void w600_arduino_loop()
{
	Serial.println("Enter Loop");
	delay(1000);
}

void setup() {
    printf("setup()\n");
    w600_arduino_setup();
}

void loop() {
    w600_arduino_loop();
}