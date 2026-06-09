## RP2040 Driver

A grblHAL driver for the Raspberry Pi Pico RP2040 processor on a [Pi Pico or Pi Pico W board](https://www.raspberrypi.org/products/raspberry-pi-pico/).

This driver can be built with the [Web Builder](https://svn.io-engineering.com:8443/?driver=RP2040&board=PicoCNC).

__Important__ download information can be found [here](https://github.com/grblHAL/core/wiki/Compiling-grblHAL).  
The project has been updated to/now uses [SDK version 2.1.1](https://github.com/raspberrypi/pico-sdk/releases).

The default build environment is Visual Studio Code, it is surprisingly easy to set up on Raspberry Pi - see the [Getting started](https://datasheets.raspberrypi.org/pico/getting-started-with-pico.pdf) documentation for how to for this and other platforms.

> [!NOTE]
> The RP2350B_5X board uses a RP2350B processor, to build the firmware with Visual Studio Code choose the _pimoroni_pga2350_ board.
For other boards choose the _pico_, _pico\_w_, _pico2_ or _pico2\_w_ board that matches the processor or Pico board used.  
The board is selected in the lower right corner of the UI.

---

### Fork customization: minimal direct-GPIO stepper test

This fork adds a stripped-down board map for bench-testing steppers on a bare Pico, with **no CNC peripherals and no shift registers / I/O expanders**. STEP, DIR and ENABLE drive RP2040 GPIOs directly.

**What was changed**
- `my_machine.h` — enables `#define BOARD_MY_MACHINE` (which pulls in `boards/my_machine_map.h`); CNC features (probe, safety door, motor fault) left disabled.
- `boards/my_machine_map.h` — rewritten from the shift-register PicoCNC layout to direct GPIO, based on `boards/generic_map.h`:
  - `STEP_PORT GPIO_PIO` instead of `GPIO_SR8` — step pulses come straight off GPIOs via PIO, not a 74HC595.
  - `DIRECTION_PORT GPIO_OUTPUT` / `ENABLE_PORT GPIO_OUTPUT` — plain GPIO outputs, no expander.

**Pin map (3-axis, XYZ)**

| Signal | GPIO |
|---|---|
| X / Y / Z step | 2 / 3 / 4 |
| X / Y / Z dir | 5 / 6 / 7 |
| Steppers enable (shared) | 8 |
| X / Y / Z limits (optional, unconnected) | 9 / 10 / 11 |

**Configuring**
- Step pins are PIO-driven and **must be consecutive**; move them by changing `STEP_PINS_BASE`.
- Direction uses `DIRECTION_OUTMODE GPIO_SHIFT5` (also consecutive). For non-contiguous dir pins set `DIRECTION_OUTMODE GPIO_MAP`.
- STEP/DIR are single-ended only. For differential pairs (e.g. Mesa-style STEP±) feed each GPIO into an external RS-422 line driver (AM26LS31 / SN75174); the driver has no built-in complementary output.

---
2025-12-31
