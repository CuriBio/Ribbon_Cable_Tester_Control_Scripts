#include <ADC.h>

int res = 16; // (bits) adc resolution
float baseline;

ADC *adc = new ADC();



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  
  adc->adc0->setAveraging(8); // set number of averages
  adc->adc0->setResolution(res); // set bits of resolution
  adc->adc0->setSamplingSpeed(ADC_SAMPLING_SPEED::LOW_SPEED);
  adc->adc0->setConversionSpeed(ADC_CONVERSION_SPEED::LOW_SPEED);

  delay(2000);

  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);  

  float result;
  uint16_t vout[512];
  int samples = 512;
  
  for (int x = 0; x < samples; x++) {
    vout[x] = adc->analogRead(A0, ADC_0);
  }

  for (int i = 0; i < samples; i++) {
    baseline += (float) vout[i] / (float) samples;
  }

  digitalWrite(13, LOW); 

}

void loop() {

  float result;
  uint16_t vout[512];
  int samples = 512;
  
  for (int x = 0; x < samples; x++) {
    vout[x] = adc->analogRead(A0, ADC_0);
  }




  for (int i = 0; i < samples; i++) {
    result += (float) vout[i] / (float) samples;
  }

      Serial.println(result);

      delay(100);




  if (result > baseline + 150) {
    digitalWrite(17, LOW); // Fail Short
    digitalWrite(16, LOW);
    digitalWrite(15, HIGH); 
  } else if (result < baseline - 150) {
    digitalWrite(17, LOW);
    digitalWrite(16, HIGH); // Fail Open
    digitalWrite(15, LOW); 
  } else {
    digitalWrite(17, HIGH); 
    digitalWrite(16, LOW); 
    digitalWrite(15, LOW); // Pass
  }

      // put your main code here, to run repeatedly:

}
