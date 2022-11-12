#include "temp_settings.h" // <-- PIN setup etc here 

#include <RTClib.h> // RTCLib by Adafruit
#include <dhtnew.h> // DHTNEW by Rob Tilaart

#include "temp_sdlog.h" // using: SD by Arduino
#include "logtime.h" // using: RTCLib by Adafruit

#include "TimeHM.h"
#include "TimeConversion.h"

//////////////////////////////////////////////////////////////////////////
// LOOP STATES
//
enum LoopState {
  initializing,
  idle,
  check_measure,
  measuring,
  fatalerror
};

//////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLES

sdlog::LogTime logtime;

DHTNEW temp_sensor(temp_log::pin::_TEMP_SENSOR);

min_time::TimeHM measuring_time{00,00}; // will be overwritten by current time + 1 minute in setup
min_time::TimeHM measuring_cycle{00,01}; //h,m

float current_temperature{-1.f};
float current_humidity{-1.f};

LoopState state{LoopState::initializing};
LoopState last_loop_state{LoopState::initializing};
char loop_state_map[]{"     "};

bool status_led{false};

//////////////////////////////////////////////////////////////////////////
// FUNCTIONS IN THIS FILE

void setup();
bool setup_clock();
bool setup_sd();

void loop();
bool check_measure_time();
void fill_loop_state_map();
bool check_measure_time();
void set_next_measure_time();
void set_onboard_led(bool state);

/// @fn setup
/// @brief setup routine before running loop function
/// @see loop
void setup()
{
  Serial.begin(9600);
  delay(500);

  // setup onboard LED
  pinMode(temp_log::pin::_LED_ONBOARD, OUTPUT);

  // fill serial log state acronym lookup table
  fill_loop_state_map();

  // Setup Clock and SD Card Interface on SD Shield
  if(!setup_clock())
  {
    Serial.println(F("E: Fatal!"));
    state = LoopState::fatalerror;
    return;
  }
  logtime.set_prefix('t');

  if(!setup_sd())
  {
    Serial.println(F("E: Fatal!"));
    state = LoopState::fatalerror;
    return;
  }

  // give the system some time to set up...
  delay(500);

  // set up temperature sensor
  temp_sensor.setType(11);
  temp_sensor.setTempOffset(temp_log::_OFFSET_TEMPERATURE);
  temp_sensor.setHumOffset(temp_log::_OFFSET_HUMIDITY);

  DateTime now{logtime.now()};

  // set up measuring time in one minute
  measuring_time.set_overflow(true);
  measuring_time.set_hours(now.hour());
  measuring_time.set_minutes(now.minute());
  measuring_time = measuring_time + min_time::TimeHM{00,01};

  if(temp_log::_SERIAL_LOGGING)
  {
    Serial.println(min_time::to_string(min_time::TimeHM{now.hour(), now.minute()}));
    Serial.println("next: " + min_time::to_string(measuring_time));
  }

  measuring_cycle.set_overflow(true);

  state = LoopState::check_measure;
  return;
}

///
/// Helper functions
///

/// @brief setup clock on SD shield
bool setup_clock()
{
  // Detect and Start Real Time Clock (RTC)
  if(logtime.begin()){
    Serial.println(F("i: Clock OK"));
  }
  else{
    Serial.println(F("E: Clock fail"));
    return false;
  }

  // Initialize time if RTC is not running
  if(!logtime.isrunning())
    logtime.adjust(DateTime(F(__DATE__), F(__TIME__)));

  return true;
}
/// @brief setup SD interface
bool setup_sd()
{
  // SD Logger initialisieren
  if(!temp_log::init_sd_logging(temp_log::pin::_SD))
    return false;
  
  // Append "System boot" to file named as current month
  temp_log::log_boot(logtime);
  return true;
}

/// @brief helper function to fill loop_state_map arrays with acronyms for terminal debugging
void fill_loop_state_map()
{
  loop_state_map[LoopState::initializing]   = '#';
  loop_state_map[LoopState::idle]           = '~';
  loop_state_map[LoopState::check_measure]  = 'c';
  loop_state_map[LoopState::measuring]      = 'm';
  loop_state_map[LoopState::fatalerror]     = '!';
}

/// @brief checks if set measuring_time matches current time (by minute)
/// @return true = measuring_time is current time, false = measuring_time is not the current time
bool check_measure_time()
{
  // objects to compare with each other
  DateTime now{logtime.now()};
    
  if((now.hour() == measuring_time.get_hours()) && (now.minute() == measuring_time.get_minutes()))
    return true;

  return false;
}

/// @brief calculates measuring_time: adds measuring_cycle to current time
void set_next_measure_time()
{
  DateTime now{logtime.now()};
  measuring_time = min_time::TimeHM(now.hour(), now.minute()) + measuring_cycle;
  return;
}

/// @brief switches the onboard led to given state
/// @param state true = on, false = off
void set_onboard_led(bool state)
{
  status_led = state;
  digitalWrite(temp_log::pin::_LED_ONBOARD, status_led);
  return;
}


///
/// @fn loop
/// @brief executes the main loop
void loop() {

  delay(10);
  
  switch(state)
  {
    case LoopState::initializing:
    {
      break;
    }

    case LoopState::idle:
    {
      delay(5000);
      state = LoopState::check_measure;

      break;
    }

    case LoopState::check_measure:
    {
      state = LoopState::idle;

      if(check_measure_time())
        state = LoopState::measuring;

      if(temp_log::_SERIAL_LOGGING)
      {
        DateTime now{logtime.now()};
        Serial.println(min_time::to_string(min_time::TimeHM{now.hour(), now.minute()}));
        Serial.println("next: " + min_time::to_string(measuring_time));
      }

      break;
    }

    case LoopState::measuring:
    {
      temp_sensor.read();
      current_temperature = temp_sensor.getTemperature();
      current_humidity = temp_sensor.getHumidity();

      if(temp_log::_SD_LOGGING)
      {
        // log data to SD Card
        temp_log::log_temperature(logtime, current_temperature);
        temp_log::log_humidity(logtime, current_humidity);
      }

      if(temp_log::_SERIAL_LOGGING)
      {
        Serial.println("T: " + (String)current_temperature + "°C | H: " + (String)current_humidity);
      }

      // set next measuring time
      set_next_measure_time();

      if(temp_log::_SERIAL_LOGGING)
      {
        Serial.println("next: " + min_time::to_string(measuring_time));
      }

      state = LoopState::idle;

      break;
    }

    case LoopState::fatalerror:
    {
      delay(600);
      set_onboard_led(!status_led);
      state = LoopState::fatalerror;

      break;
    }
  }

  // If loop state changes, log it!
  if(state != last_loop_state)
  {
    if(temp_log::_SERIAL_LOGGING)
    {
      Serial.println(loop_state_map[state]);        
    }

    last_loop_state = state;
  }
}
