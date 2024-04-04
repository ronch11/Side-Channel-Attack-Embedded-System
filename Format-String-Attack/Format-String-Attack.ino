#define LENGTH 100


char buff[LENGTH];
char format[LENGTH];


void PrintWellcomeMessage();
void inputFormat();
void PrintResult(char* format);


char pass[] = "Fundmentals_Of_Software_Security";


void setup()
{
    Serial.begin(9600);
}


void loop()
{
    PrintWellcomeMessage();
    delay(1000);

    inputFormat();
    delay(1000);
    
    PrintResult();

    delay(1000);
}


void PrintWellcomeMessage()
{
    String welcomeMessage = "Welcome to format string CTF. Try to read the password from the stack";
    Serial.println(welcomeMessage);
    Serial.println("Enter the length of format string you want write");

    delay(1000);
}


void inputFormat()
{
    while (Serial.available() == 0) {}

    int len = Serial.parseInt();
    
    delay(10000);
    Serial.println("Enter your format string:");
    delay(1000);

    while (Serial.available() == 0) {}

    for (int i = 0; i < len; i++)
    {
        format[i] = Serial.read();
    }
}


void PrintResult()#define LENGTH 100


char buff[LENGTH];
char format[LENGTH];


void PrintWellcomeMessage();
void inputFormat();
void PrintResult(char* format);


char pass[] = "Fundmentals_Of_Software_Security";


void setup()
{
    Serial.begin(9600);
}


void loop()
{
    PrintWellcomeMessage();
    delay(1000);

    inputFormat();
    delay(1000);
    
    PrintResult();

    delay(1000);
}


void PrintWellcomeMessage()
{
    String welcomeMessage = "Welcome to format string CTF. Try to read the password from the stack";
    Serial.println(welcomeMessage);
    Serial.println("Enter the length of format string you want write");

    delay(1000);
}


void inputFormat()
{
    while (Serial.available() == 0) {}

    int len = Serial.parseInt();
    
    delay(10000);
    Serial.println("Enter your format string:");
    delay(1000);

    while (Serial.available() == 0) {}

    for (int i = 0; i < len; i++)
    {
        format[i] = Serial.read();
    }
}


void PrintResult()
{
    buff[strcspn(buff, "\n")] = '\0';
    sprintf(buff, PSTR(format));

    if (strncmp(pass, buff, sizeof(pass)))
    {
        Serial.print(buff);
        Serial.println(" does not have access");
    }

    else 
    {
        Serial.println("Good job!");
    }
}
{
    buff[strcspn(buff, "\n")] = '\0';
    sprintf(buff, PSTR(format));

    if (strncmp(pass, buff, sizeof(pass)))
    {
        Serial.print(buff);
        Serial.println(" does not have access");
    }

    else 
    {
        Serial.println("Good job!");
    }
}
