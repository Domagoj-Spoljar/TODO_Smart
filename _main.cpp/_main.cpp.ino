
#define LED1_PIN D1
#define BUTTON_PIN D2
/*
   LED CLASS DEFINITION
*/
class Led {
  private:
    byte pinLED;
    boolean ledState = LOW;
  public:
    Led(byte pinLED, boolean ledState) {
      this->pinLED = pinLED;
      this->ledState = ledState;
      pinMode(pinLED, OUTPUT);
      digitalWrite(pinLED, ledState);
    }

    void turn_on() {
      digitalWrite(pinLED, LOW);
    }
    void turn_off() {
      digitalWrite(pinLED, HIGH);
    }
};

class Button
{
  private:
    uint8_t _pin;          // arduino pin number connected to button
    uint32_t _dbTime;      // debounce time (ms)
    bool _puEnable;        // internal pullup resistor enabled
    bool _invert;          // if true, interpret logic low as pressed, else interpret logic high as pressed
    bool _state;           // current button state, true=pressed
    bool _lastState;       // previous button state
    bool _changed;         // state changed since last read
    uint32_t _time;        // time of current state (ms from millis)
    uint32_t _lastChange;  // time of last state change (ms)

  public:
    // Button(pin, dbTime, puEnable, invert) instantiates a button object.
    //
    // Required parameter:
    // pin      The Arduino pin the button is connected to
    //
    // Optional parameters:
    // dbTime   Debounce time in milliseconds (default 25ms)
    // puEnable true to enable the AVR internal pullup resistor (default false)
    // invert   true to interpret a low logic level as pressed (default true)
    Button(uint8_t pin, uint32_t dbTime = 25, uint8_t puEnable = false, uint8_t invert = true)
      : _pin(pin), _dbTime(dbTime), _puEnable(puEnable), _invert(invert)
    {
      pinMode(_pin, _puEnable ? INPUT_PULLUP : INPUT);
      _state = digitalRead(_pin);
      if (_invert) _state = !_state;
      _time = millis();
      _lastState = _state;
      _changed = false;
      _lastChange = _time;

    }

    // Returns the current debounced button state, true for pressed,
    // false for released. Call this function frequently to ensure
    // the sketch is responsive to user input.
    bool read()
    {
      uint32_t ms = millis();
      bool pinVal = digitalRead(_pin);
      if (_invert) pinVal = !pinVal;
      if (ms - _lastChange < _dbTime)
      {
        _changed = false;
      }
      else
      {
        _lastState = _state;
        _state = pinVal;
        _changed = (_state != _lastState);
        if (_changed) _lastChange = ms;
      }
      _time = ms;
      return _state;
    }
    // Returns true if the button state was pressed at the last call to read().
    // Does not cause the button to be read.
    bool isPressed()
    {
      return _state;
    }
    // Returns true if the button state was released at the last call to read().
    // Does not cause the button to be read.
    bool isReleased()
    {
      return !_state;
    }
    // Returns true if the button state at the last call to read() was pressed,
    // and this was a change since the previous read.
    bool wasPressed()
    {
      return _state && _changed;
    }
    // Returns true if the button state at the last call to read() was released,
    // and this was a change since the previous read.
    bool wasReleased()
    {
      return !_state && _changed;
    }
    // Returns true if the button state at the last call to read() was pressed,
    // and has been in that state for at least the given number of milliseconds.
    bool pressedFor(uint32_t ms)
    {
      return _state && _time - _lastChange >= ms;
    }
    // Returns true if the button state at the last call to read() was released,
    // and has been in that state for at least the given number of milliseconds.
    bool releasedFor(uint32_t ms)
    {
      return !_state && _time - _lastChange >= ms;
    }
    // Returns the time in milliseconds (from millis) that the button last
    // changed state.
    uint32_t lastChange()
    {
      return _lastChange;
    }

};

/******CLASS VARIABLES DECLARATION*******/

Led led1 = Led(LED1_PIN, LOW);
Button button1 = Button(BUTTON_PIN);

/*****************SETUP*******************/
void setup() {
  
}

/*****************LOOP********************/
void loop() {
  button1.read();
  if (button1.isPressed())
  {
    led1.turn_on();
  }
  else {
    led1.turn_off();
  }
  delay(2);

}
