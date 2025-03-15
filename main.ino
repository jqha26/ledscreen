#include <LiquidCrystal.h>
#include <IRremote.h>

// LCD Configuration
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// IR Configuration
const int RECV_PIN = 10;
IRrecv irrecv(RECV_PIN);
decode_results results;

// Language system
int current_language = -1; // 0=English, 1=Mandarin, 2=Spanish

// Phrase database [button][language]
const char* phrases[6][3] = {
  {"Thank you", "谢谢", "Gracias"},        // Button 4
  {"Hello", "你好", "Hola"},               // Button 5
  {"Goodbye", "再见", "Adiós"},            // Button 6
  {"Yes", "是", "Sí"},                    // Button 7
  {"No", "不", "No"},                     // Button 8
  {"Please", "请", "Por favor"}           // Button 9
};

void setup() {
  // LCD setup
  lcd.begin(16, 2);
  lcd.print("Select Language:");
  
  // IR setup
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop() {
  if (irrecv.decode(&results)) {
    handleInput(results.value);
    irrecv.resume();
  }
}

void handleInput(unsigned long value) {
  // Clear second line for new messages
  lcd.setCursor(0, 1);
  lcd.print("                "); // Clear line
  
  switch(value) {
    // Language Selection
    case 0xFFA25D: // Button 1 (replace with your actual IR code)
      current_language = 0;
      lcd.setCursor(0, 0);
      lcd.print("English         ");
      break;
      
    case 0xFF629D: // Button 2 (replace with your actual IR code)
      current_language = 1;
      lcd.setCursor(0, 0);
      lcd.print("Mandarin Chinese");
      break;
      
    case 0xFFE21D: // Button 3 (replace with your actual IR code)
      current_language = 2;
      lcd.setCursor(0, 0);
      lcd.print("Spanish         ");
      break;

    // Phrase Buttons 4-9
    case 0xFF22DD: // Button 4 (replace with your actual IR code)
      showPhrase(0);
      break;
      
    case 0xFF02FD: // Button 5 (replace with your actual IR code)
      showPhrase(1);
      break;
      
    case 0xFFC23D: // Button 6 (replace with your actual IR code)
      showPhrase(2);
      break;
      
    case 0xFFE01F: // Button 7 (replace with your actual IR code)
      showPhrase(3);
      break;
      
    case 0xFFA857: // Button 8 (replace with your actual IR code)
      showPhrase(4);
      break;
      
    case 0xFF906F: // Button 9 (replace with your actual IR code)
      showPhrase(5);
      break;

    default:
      lcd.setCursor(0, 1);
      lcd.print("Invalid button!");
  }
}

void showPhrase(int buttonIndex) {
  if (current_language == -1) {
    lcd.setCursor(0, 1);
    lcd.print("Select language!");
    return;
  }
  
  lcd.setCursor(0, 1);
  lcd.print(phrases[buttonIndex][current_language]);
}

