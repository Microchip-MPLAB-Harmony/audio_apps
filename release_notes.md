![Microchip logo](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_logo.png)
![Harmony logo small](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_mplab_harmony_logo_small.png)

# Microchip MPLAB® Harmony 3 Release Notes

## Harmony 3 Audio Application Examples V3.1.0 (May, 2022)

- **Applications/Projects**

The following table provides the list of the applications/projects :

| Application | Description | MZ EF/C2 | E54 | E70 | V71 |
| --- | --- | --- | --- | --- | --- |
| audio_enc | Audio encoder for WAV files |  |  | x |  |
| audio_player_basic | Audio player for WAV files (without library) |  | x | x |  |
| audio_tone | Sine wave audio tone generator | x | x | x | x |
| audio_linkeddma | Audio tone generator using linked DMA |  |  | x |  |
| microphone_loopback | Microphone loopback demo | x | x | x | x |
| universal_audio_decoders | Audio player for WAV, ADPCM, FLAC and MP3 files | x |  | x |  |
| usb_headset | USB headset demo | x |  |  |  |
| usb_microphone | USB microphone demo |  |  | x |  |
| usb_speaker | USB speaker demo | x |  | x |  |
| usb_speaker_bass_boost | USB speaker, with variable bass boost | x |  | x |  |
| usb_speaker_hi_res | USB speaker, hi-res (96 kHz/24-bit) |  |  | x |  |

where:

| |  Development Kit |
| --- | --- | 
|**MZ EF/C2**| [Curiosity PIC32MZEF Dev Board 2.0](https://www.microchip.com/developmenttools/ProductDetails/PartNO/DM320209) |
|**E54**| [SAM E54 Curiosity Ultra Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/PartNO/DM320210) |
|**E70**| [SAM E70 Xplained Ultra Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/PartNO/DM320113) |
|**V71**| [SAM V71 Xplained Ultra Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/PartNO/ATSAMV71-XULT) |

### TESTED WITH:

#### Software Dependencies

Supports MCC.
Before using MPLAB Harmony Audio Applications, ensure that the following are installed:

- [MPLAB X IDE v6.00](https://www.microchip.com/mplab/mplab-x-ide) or later
- [MPLAB XC32 C/C++ Compiler v4.10](https://www.microchip.com/mplab/compilers) or later
- [Harmony audio application repository, 3.1.0](https://github.com/Microchip-MPLAB-Harmony/audio_apps)

In order to regenerate source code for any of the applications, you will also need the following to be installed:

| Tool | Version | Notes |
| --- | --- | --- |
| MPLAB® Harmony Code Configurator (MCC) plug-in | v5.1.4 | |
| [Harmony 3 Audio](https://github.com/Microchip-MPLAB-Harmony/audio)| v3.6.0 | |
| [Harmony 3 BSP](https://github.com/Microchip-MPLAB-Harmony/bsp)| v3.12.0 | |
| [Harmony 3 CSP](https://github.com/Microchip-MPLAB-Harmony/csp)| v3.12.0 | |
| [Harmony 3 Core](https://github.com/Microchip-MPLAB-Harmony/core)| v3.10.0 | |
| [Harmony 3 Dev_Packs](https://github.com/Microchip-MPLAB-Harmony/dev_packs)| v3.12.0 | |
| [Harmony 3 USB](https://github.com/Microchip-MPLAB-Harmony/usb)| v3.9.0 | only if using USB |
| [Harmony 3 CMSIS-FreeRTOS](https://github.com/ARM-software/CMSIS-FreeRTOS)| v10.3.1 | only if using FreeRTOS |
| [Harmony 3 MP3 Decoder Library](https://github.com/Microchip-MPLAB-Harmony/helix_mp3)| v1.1.0 |only if using MP3 decoder|
| [Harmony 3 FLAC Decoder Library](https://github.com/Microchip-MPLAB-Harmony/xiph_flac)| v1.0.0 |only if using FLAC decoder|

#### Development Kit Support

This release supports applications for the following development kits

| Development Kits |
| --- |
| [Curiosity PIC32MZEF Dev Board 2.0 (DM320209)](https://www.microchip.com/developmenttools/ProductDetails/PartNO/DM320209) |
| [SAM E54 Curiosity Ultra Evaluation Kit (DM320210)](https://www.microchip.com/developmenttools/ProductDetails/PartNO/DM320210) |
| [SAM E70 Xplained Ultra Evaluation Kit (DM320113)](https://www.microchip.com/developmenttools/ProductDetails/PartNO/DM320113) |
| [SAM V71 Xplained Ultra Evaluation Kit (ATSAMV71-XULT)](https://www.microchip.com/developmenttools/ProductDetails/PartNO/ATSAMV71-XULT) |

### KNOWN ISSUES

The current known issues are as follows:

* Code is compliant to MISRA C 2012 Mandatory guidelines, except:
    - USB Speaker Bass Boost app fails Mandatory Rules 17.3 and 17.4, but these appear to be false positives as the same code passes using another tool (Coverity) 
* The ICD4 loads the reset line of the SAM V71 Xplained Ultra board. When running demo projects using the V71, the ICD4 flex cable should be removed after programming to run the application.
* audio_enc demonstration:
    - Audible artifacts may occur as a result of long period MSD writes.
    - Functionality deteriorates as higher sampling rates.
    - Audible artifacts may occur when using FreeRTOS.
    - LED operation doesn't exactly match documentation.
* audio_player_basic demonstration:
    - Playback of files with more than 2 channels is not supported.
    - Only CBR (Constant Bit Rate) encoding is supported.
    - Audible artifacts and/or L/R channel swapping may occur for some configurations.
    - LED operation doesn't exactly match documentation.-  
* audio_tone demonstration:
    - In both E54/WM8904 projects, only 32-bit audio has been tested.
    - Dropouts or ticking sound may occur when switching buffers. 
* audio_tone_linkeddma demonstration:
    - When changing the frequency the first time, the pushbutton must be pressed twice.
* microphone_loopback demonstration:
    - In both E54/WM8904 projects, only 32-bit audio has been tested.
    - Volume is rather low using internal mic on AK4954 codec
* usb_headset demonstrations:
    - Muting from the PC doesn't always work
	- LED operation doesn't exactly match documentation.
* all usb_speaker demonstrations:
    - Audible artifacts may occur 
* USB Speaker E70 I2SC demonstration: 
    - Button press of SW1 to change volume might not work.
* USB Speaker Hi-Res demonstration: 
    - If there is no audio, then the Windows driver of the audio device needs to be uninstalled, and device should be plugged in back (so that the driver gets properly installed)
* In case of build error after a regeneration via MCC, then take the original codes in the release and do a regeneration with MHC first.

### RELEASE CONTENTS

This topic lists the contents of this release and identifies each module.

#### Description

This table lists the contents of this release, including a brief description, and the release type (Alpha, Beta, Production, or Vendor).

| Folder | Description | Release Type |
| --- | --- | --- |
| audio\apps\audio_enc | audio encoder application | Production |
| audio\apps\audio_player_basic | audio_player_basic application | Production |
| audio\apps\audio_tone  | audio tone application | Production |
| audio\apps\audio_tone_linkeddma | audio tone using linked dma application | Production |
| audio\apps\microphone_loopback | microphone loopback application | Production |
| audio\apps\universal_audio_decoders | universal audio decoders application | Production |
| audio\apps\usb_headset | USB headset application | Beta |
| audio\apps\usb_microphone | USB microphone application | Production |
| audio\apps\usb_speaker | USB speaker application | Production |
| audio\apps\usb_speaker_bass_boost | USB speaker bass boost application | Production |
| audio\apps\usb_speaker_hi_res | USB speaker application (hi-res) | Production |






