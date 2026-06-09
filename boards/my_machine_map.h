/*
  my_machine_map.h - driver code for RP2040 ARM processors

  Minimal direct-GPIO pin map for a bare RP2040 (e.g. Raspberry Pi Pico)
  wired straight to step/direction stepper drivers (A4988, DRV8825, TMC step/dir,
  external line drivers, etc.). No shift registers, no I/O expanders, no CNC
  peripherals - intended for quickly bench-testing stepper motion.

  Part of grblHAL

  Copyright (c) 2021-2026 Terje Io

  grblHAL is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  grblHAL is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with grblHAL. If not, see <http://www.gnu.org/licenses/>.
*/

#if TRINAMIC_ENABLE
#error Trinamic plugin not supported!
#endif

#if N_ABC_MOTORS
#error "Axis configuration is not supported! This map is 3-axis (XYZ) only."
#endif

#define BOARD_NAME "MyMachine direct GPIO"

// Step pulse output pins.
// Driven by a single PIO state machine, so the N_AXIS step pins MUST be
// consecutive GPIOs starting at STEP_PINS_BASE: X = base+0, Y = base+1, Z = base+2.
#define STEP_PORT               GPIO_PIO
#define STEP_PINS_BASE          2         // X step = GPIO2, Y step = GPIO3, Z step = GPIO4

// Step direction output pins.
// Plain GPIO outputs. With GPIO_SHIFT5 the direction bits are written as a
// contiguous group starting at GPIO5 (X = GPIO5, Y = GPIO6, Z = GPIO7).
// If you need non-contiguous direction pins, set DIRECTION_OUTMODE to GPIO_MAP.
#define DIRECTION_PORT          GPIO_OUTPUT
#define X_DIRECTION_PIN         5
#define Y_DIRECTION_PIN         6
#define Z_DIRECTION_PIN         7
#define DIRECTION_OUTMODE       GPIO_SHIFT5

// Common stepper driver enable/disable output pin (active for all axes).
#define ENABLE_PORT             GPIO_OUTPUT
#define STEPPERS_ENABLE_PIN     8

// Homing/hard limit switch input pins.
// Defined so the firmware builds and the inputs exist; leave them unconnected
// if you are not using limit switches (disable hard limits / homing in $ settings).
#define X_LIMIT_PIN             9
#define Y_LIMIT_PIN             10
#define Z_LIMIT_PIN             11
#define LIMIT_INMODE            GPIO_MAP

// Default PWM spindle output (only assigned if a driver spindle is enabled).
// Kept so a default PWM spindle has a valid pin; harmless if spindle is unused.
#if DRIVER_SPINDLE_ENABLE
#define SPINDLE_PORT            GPIO_OUTPUT
#endif
#if DRIVER_SPINDLE_ENABLE & SPINDLE_PWM
#define SPINDLE_PWM_PIN         15
#endif
#if DRIVER_SPINDLE_ENABLE & SPINDLE_DIR
#define SPINDLE_DIRECTION_PIN   14
#endif
#if DRIVER_SPINDLE_ENABLE & SPINDLE_ENA
#define SPINDLE_ENABLE_PIN      13
#endif

// Optional control / probe inputs (only assigned if the matching feature is enabled).
#define AUXINPUT0_PIN           18 // Reset/EStop
#define AUXINPUT1_PIN           19 // Feed hold
#define AUXINPUT2_PIN           20 // Cycle start
#define AUXINPUT3_PIN           28 // Probe

#if CONTROL_ENABLE & CONTROL_HALT
#define RESET_PIN               AUXINPUT0_PIN
#endif
#if CONTROL_ENABLE & CONTROL_FEED_HOLD
#define FEED_HOLD_PIN           AUXINPUT1_PIN
#endif
#if CONTROL_ENABLE & CONTROL_CYCLE_START
#define CYCLE_START_PIN         AUXINPUT2_PIN
#endif
#if PROBE_ENABLE
#define PROBE_PIN               AUXINPUT3_PIN
#endif
