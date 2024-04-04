// Define the length of the buffer and format arrays
#define LENGTH 100

// Declare the buffer and format arrays
char buff[LENGTH];
char format[LENGTH];

// Function prototypes
void PrintWellcomeMessage();
void inputFormat();
void PrintResult(char* format);

// The password to be checked
char pass[] = "Fundmentals_Of_Software_Security";

// Setup function for the Arduino
void setup() {
    // Begin serial communication at 9600 baud
    Serial.begin(9600);
}

// Main loop function
void loop() {
    // Print the welcome message
    PrintWellcomeMessage();
    delay(1000);

    // Input the format string
    inputFormat();
    delay(1000);
    
    // Print the result of the password check
    PrintResult();

    delay(1000);
}

// Function to print the welcome message
void PrintWellcomeMessage() {
    String welcomeMessage = "Welcome to format string CTF. Try to read the password from the stack";
    Serial.println(welcomeMessage);
    Serial.println("Enter the length of format string you want write");

    delay(1000);
}

// Function to input the format string
void inputFormat() {
    // Wait until there is available data
    while (Serial.available() == 0) {}

    // Parse the length of the format string
    int len = Serial.parseInt();
    
    delay(10000);
    Serial.println("Enter your format string:");
    delay(1000);

    // Wait until there is available data
    while (Serial.available() == 0) {}

    // Read the format string
    for (int i = 0; i < len; i++) {
        format[i] = Serial.read();
    }
}

// Function to print the result of the password check
void PrintResult() {
    // Remove newline characters from the buffer
    buff[strcspn(buff, "\n")] = '\0';
    sprintf(buff, PSTR(format));

    // Check if the password matches
    if (strncmp(pass, buff, sizeof(pass))) {
        Serial.print(buff);
        Serial.println(" does not have access");
    } else {
        Serial.println("Good job!");
    }
}
