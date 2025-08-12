# https://www.pete01507.com/arduino-code-for-esp32-to-fade-in-and-out-the-on-board-led-with-pwm/

const int ledPin = 2;//On-Board LED
int dc = 0;//read-write
const int freq = 4000;//Freq in Hz
const int ledChannel = 0;//There are 16 channels 0-15
const int resolution = 8;//8,10,12,15 Bit Resolution 8-bit=255 10-bit=1024

void setup()
{
  // send the PWM configuration
  ledcSetup(ledChannel, freq, resolution);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);
}
void loop()
{
  // increase the LED brightness
  for(int i = 0; i <= 255; i++)
  {
    dc=i;
    LED();
  }

  // decrease the LED brightness
  for(int i = 255; i >= 0; i--)
  {
    dc=i;
    LED();
  }
}

void LED()
{
  ledcWrite(ledChannel, dc);
  delay(10);
}