# Intelligent Lamp

Intelligent Lamp is an Arduino-based lighting system that detects ambient light and automatically adjusts the brightness of an LED.

The project was created for students and office workers who spend long periods studying or working. Fixed lighting may become too bright or uncomfortable when a light is first turned on, when daylight changes, or when the surrounding environment becomes darker. Intelligent Lamp responds automatically to these changes, reduces the need for manual adjustment, and helps maintain stable and comfortable lighting conditions.

When the system starts, it spends approximately five seconds observing the surrounding light level and establishing an initial calibration range. The photoresistor connected to analog pin A0 continuously measures ambient light, while an exponential moving-average filter reduces sudden fluctuations in the sensor readings. The filtered value is converted into a PWM output for the LED on pin 9. A deadband and gradual brightness adjustment are used to reduce flickering and prevent abrupt changes in light intensity.

## Operating Flow

```mermaid
flowchart TD
    A[Power on] --> B[Observe ambient light for approximately five seconds]
    B --> C[Establish the initial calibration range]
    C --> D[Photoresistor reads ambient light on A0]
    D --> E[Exponential moving-average filter smooths the reading]
    E --> F[Controller applies calibration and deadband]
    F --> G[Convert the filtered light level into a PWM target]
    G --> H[Gradually adjust LED brightness on pin 9]
    H --> D
```

The system was developed using Arduino IDE and Arduino C/C++. It combines photoresistor sensing, electronic circuit assembly, PWM brightness control, exponential moving-average filtering, automatic light calibration, gradual brightness adjustment, and serial-monitor debugging.

The hardware prototype, ambient-light detection, and automatic LED brightness control have been completed and tested. Future improvements will focus on refining the brightness-control algorithm, improving the circuit layout, and designing a complete lamp enclosure.

## Project Media

<img src="media/intelligent-lamp-prototype.jpg" alt="Intelligent Lamp prototype" width="520">

### Demonstration

<video src="https://github.com/user-attachments/assets/f6c083d1-6b1c-4d24-aff2-504683a06791" controls width="620"></video>
