# DESIGN DOCUMENT

This is a preliminary design document for the PER|FORMER eurorack sequencer. Planned features are marked with [ ] while implemented features are marked with [x].

# Hardware

The hardware design files (KiCad) are available on https://github.com/westlicht/eurorack-sequencer-hardware. The hardware platform is based on the following components:

- STM32F405RGT6 (168 MHz, 1MB Flash, 192KB Ram)
- JTAG interface
- Serial interface
- 256x64 OLED display with 4bpp
- MicroSD card slot
- USB host port with support for USB-MIDI controllers
- MIDI input/output
- Clock/Reset input/output
- 4 CV Inputs (12bit internal ADC)
- 8 Gate Outputs
- 8 CV Outputs (TI DAC8568 16bit DAC)
- Encoder with push button
- Button/Led matrix (bi-color leds)

# Features

- 8 track sequencer (8 CV/gate output pairs)
- 16 patterns per project
- 64 steps per sequence
- various sequence modes:
  - note sequence
  - function sequence
  - chord sequence
- snapshot system
- master/slave clock sync (analog, MIDI, USB-MIDI)

# User Interface

The user interface is based on the following inputs/outputs:

- 264x64 display
- 1 push encoder
- 32 buttons with bi-color leds
- 5 soft buttons

## Global Controls

Global buttons are `PLAY`, `CLOCK`, `<`, `>`, `SNAPSHOT`, `FILL`, `GLOBAL`, `SHIFT`

### Clock Control

- [x] press `PLAY` to resume/stop the sequencer
- [x] press `SHIFT` + `PLAY` to reset and restart the sequencer
- [x] hold `CLOCK` and turn `ENCODER` to set the tempo (press/hold and turn `ENCODER` to adjust in smaller steps, hold `SHIFT` and turn `ENCODER` to adjust in larger steps)
- [x] hold `CLOCK` and tap `PLAY` multiple times to set tempo by tapping
- [ ] hold `CLOCK` and hold `<` or `>` to nudge playhead (temporary decrease/increase tempo)
- [x] press `SHIFT` + `CLOCK` to open the _clock setup_ page

### Snapshot Control

Snapshots are used to modify patterns in a non-destructive manner. This is useful in a live performance situation to quickly create variations of the active pattern without loosing the original state. It can also help to develop new ideas from a given pattern and store the results in a new pattern.

- [ ] press `SNAPSHOT` + `>` to copy the _pattern state_ to a new _snapshot_ on top of the _snapshot queue_ and activate it
- [ ] press `SNAPSHOT` + `<` to discard the _snapshot queue_ and revert to the _pattern state_
- [ ] press `SNAPSHOT` + `STEP[1-8]` to activate a _snapshot_ in the _snapshot queue_
- [ ] press `SHIFT` + `SNAPSHOT` to commit the current _snapshot_ to the _pattern state_ and discard the _snapshot queue_

### Fill Control

TBD

### Global Control

- press `GLOBAL` to enable/disable global mode
- press `SHIFT` + `CONTROL` to open _global setup_ page

## Mode/Track Control

Mode/track buttons are `MODE/TRACK[1-8]`.

### Track Selection

- [x] press `TRACK[1-8]` to select track

### Mode Selection

- [x] press `SHIFT` + `MODE1` to show _track setup_ page
    - configure track mode (trigger, note, chord, function, etc.)
    - configure track outputs (gate, cv, midi)
- [x] press `SHIFT` + `MODE2` to show _sequence_ page
- [x] press `SHIFT` + `MODE3` to show _sequence parameter_ page  (first step, last step, division, shuffle, direction etc)
- [ ] press `SHIFT` + `MODE4` to show _sequence modifier_ page (transpose, shift, etc.)
- [x] press `SHIFT` + `MODE6` to show _project_ page
- [x] press `SHIFT` + `MODE7` to show _pattern_ page
- [x] press `SHIFT` + `MODE8` to show _performer_ page



## Track Setup Page (`MODE1`)

**Note** Changing track setup deletes the current snapshots.

## Sequence Page (`MODE2`)

### Note Sequencer

- [x] press `F1` to switch between _gate_ and _gate variation_ mode
- [x] press `F2` to switch between _length_ and _length variation_ mode
- [x] press `F3` to switch between _note_ and _note variation_ mode

- [x] in _gate_ mode, press `STEP[1-16]` to toggle the _gate_
- [x] in _gate variation_ mode, hold `STEP[1-16]` or `SHIFT` to select steps and turn the `ENCODER` to adjust the _gate probability_
- [x] in _length_ mode, hold `STEP[1-16]` or `SHIFT` to select steps and turn the `ENCODER` to adjust the _length_
- [x] in _length variation_ mode, hold `STEP[1-16]` or `SHIFT` to select steps and turn the `ENCODER` to adjust the _length variation range_, press/hold and turn the `ENCODER` to adjust the _length variation probability_
- [x] in _note_ mode, hold `STEP[1-16]` or `SHIFT` to select steps and turn the `ENCODER` to adjust the _note_, press/hold and turn the `ENCODER` to adjust the _note_ in octaves
- [ ] in _note variation_ mode, hold `STEP[1-16]` or `SHIFT` to select steps and turn the `ENCODER` to adjust the _note variation range_, press/hold and turn the `ENCODER` to adjust the _note variation probability_

- ratcheting
- trigger conditions

- press `<` / `>` to move to previous/next page in sequence
- press `SHIFT` + `<` / `>` to move to first/last page in sequence

- **IDEA**: use `SHIFT` to select all notes, but if a `STEP[1-16]` is pressed while `SHIFT` is hold, enter mode where selected steps can be toggled on the step buttons without holding shift

### Control Sequencer

- [ ] press `F1` to edit shapes
- [ ] press `SHIFT` + `F1` to edit shape variations
- [ ] press `F2` to edit amplitudes
- [ ] press `F3` to edit offsets


## Sequence Parameter Page (`MODE3`)

- **IDEA**: use `SHIFT` + `STEP[1-16]` as shortcuts to sequence parameters

## Sequence Modifier Page (`MODE4`)


## Project Page (`MODE6`)

- [ ] press `F1` to load project from SD card
- [ ] press `F2` to save project to SD card

## Pattern Page (`MODE7`)

- [ ] press `STEP[1-16]` to switch _pattern_ immediately
- [ ] press `SHIFT` + `STEP[1-16]` to schedule switch of _pattern_ on next _global measure_
- [ ] press `F5` to cancel scheduled switch

## Performer Page (`MODE8`)

### Buttons

- [ ] press `F1` to mute all
- [ ] press `SHIFT` + `F1` to schedule mute all for next _global measure_
- [ ] press `F2` to unmute all
- [ ] press `SHIFT` + `F2` to schedule unmute all for next _global measure_
- [ ] press `F5` to cancel all scheduled actions
- [ ] press `STEP[1-8]` to mute/unmute track
- [ ] press `SHIFT` + `STEP[1-8]` to schedule mute/unmute track for next _global measure_
- [ ] press `STEP[9-16]` to solo/unsolo track
- [ ] press `SHIFT` + `STEP[9-16]` to schedule solo/unsolo track for  next _global measure_

**IDEA**: would be nice to add some way to trigger fills on this page as well (track keys)!

### LEDs

TBD


## Generators

### Euclidean Gates

### Arpeggiator

### LFO


## Step Variations

Variations are defined by a _range_ and a _probability_. The _range_ defines the interval of random values to choose from while the _probability_ defines the probability of choosing a value from the defined _range_. The _range_ is selected by turning the `ENCODER`, the probability is selected by pressing/holding and then turning the `ENCODER`.

## Additional Features

- clear project/sequence/steps
- copy/paste
- song mode
- calibration
- let users configure track/mode key behavior with shift

## Data Model

- `root`
  - `project`
    - `bpm` : Master tempo
    - `swing` : Master swing amount
    - `clockSetup`
      - `mode` : `Auto` | `Master` | `Slave`
      - `clockInputPPQN` : Parts Per Quarter Note
      - `clockInputMode` : `Reset` | `Start/Stop`
      - `clockOutputPPQN` : Parts Per Quarter Note
      - `clockOutputPulse` : Pulse Width (ms)
      - `clockOutputMode` : `Reset` | `Start/Stop`
      - `midiRx` : Receive MIDI Clock (`on` | `off`)
      - `midiTx` : Transmit MIDI Clock (`on` | `off`)
      - `usbRx` : Receive USB MIDI Clock (`on` | `off`)
      - `usbTx` : Transmit USB MIDI Clock (`on` | `off`)
    - `track[1-8]`
      - `mode` : `Note` | `Function`
    - `pattern[1-16]`
      - `sequence[1-8]`
        - `playMode` : `Forward` | `Backward` | `PingPong` | `Pendulum` | `Random`
        - `firstStep`
        - `lastStep`
        - `divider`
        - `stepData`
  - `settings`

### Note Step Data

- `stepData`
    - `step[1-16]`
        - `gate` `1b`
        - `gateProbability` `4b`
        - `length` `1B`
        - `lengthVariation` `1B`
            - `range` `4b`
            - `probability` `4b`
        - `repeats`
        - `repeatsVariation`
            - `range`
            - `probability`
        - `note` `1B`
        - `noteVariation` `1B`
            - `range` `4b`
            - `probability` `4b`

### Function Step Data

- `stepData`
    - `step[1-16]`
        - `function`

- Note Step Data (if given track is in `Note` mode)
    - asd
- Function Step Data (if given track is in `Function` mode)
    - asd