
void setup() 
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{
    for(int i = 0; i <= 4; i++)
    {
        Serial.print("Hello World  i : ");
        Serial.println(i);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(300);
        digitalWrite(LED_BUILTIN, LOW);
        delay(300);
    }

    Serial.println();
    delay(3000);
}
