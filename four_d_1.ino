// Arduino pins connected to the 74HC595
int latch = 9;   // Arduino pin 9  -> 74HC595 STCP (chip pin 12): copies data to the outputs
int clock = 10;  // Arduino pin 10 -> 74HC595 SHCP (chip pin 11): shift clock
int data = 8;    // Arduino pin 8  -> 74HC595 DS (chip pin 14): serial data in

// Segment patterns. Each number is one byte, and each bit turns on one segment:
//   bit 0 = a, bit 1 = b, bit 2 = c, bit 3 = d,
//   bit 4 = e, bit 5 = f, bit 6 = g, bit 7 = decimal point
// Example: 0x3f = 00111111 lights a, b, c, d, e, f, which draws a "0"
// Index 0-9 = digits, 10-15 = letters A-F, index 16 = display off

// Refer to the picture on the project page to see how calling an index
// on the table leads to it being displayed on the 4 digit display
unsigned char table[] =
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,
 0x39,0x5e,0x79,0x71,0x00};

void setup() {
  // All three control pins send signals out to the chip
  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);
}

// Shows one character from the table on the display
void Display(unsigned char num)
{
  digitalWrite(latch, LOW);                      // start sending: outputs hold their old value
  shiftOut(data, clock, MSBFIRST, table[num]);   // send the 8 bits of the pattern, one at a time
  digitalWrite(latch, HIGH);                     // done: the new pattern appears on the segments
}

void loop() {
  // Count down from 9 to 0
  for (int i = 9; i >= 0; i--)
  {
    Display(i);
    delay(1200); // This is the delay timer in between each number, delay(1200) causes 
                 //each number to be displayed for roughly a second before going onto the next
  }
}