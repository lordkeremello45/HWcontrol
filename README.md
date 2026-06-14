# HWControl

An experimental, kernel-level hardware control utility inspired by MSI Afterburner. This project serves as a technical proof-of-concept to evaluate how effectively AI can assist in developing complex system software and drivers.

## About This Project
This project is an experimental, kernel-level hardware control utility designed to test the capabilities of AI in developing low-level system software. The core logic and structure of this application were generated and refined with the assistance of an AI, exploring the potential of artificial intelligence in architectural design and system-level programming.

## Features
* **Kernel-Mode Operations:** High-performance hardware interaction.
* **System Monitoring:** Real-time data retrieval capabilities.
* **AI-Assisted Architecture:** Built to explore AI's role in system-level development.

## Requirements
* Windows 10/11 (x64)
* Visual Studio 2022
* Windows Driver Kit (WDK)

## Disclaimer
**Warning:** This is a kernel-level project. Improper use or modification may cause system instability or crashes. Use only in isolated environments (e.g., virtual machines) for testing purposes.

## License
This project is licensed under the GNU V3.0 License. See the [LICENSE](LICENSE) file for details.
## Build Instructions
1. Open the project in Visual Studio (with WDK installed).
2. Configure the project as a "Kernel Mode Driver (KMDF)".
3. Build the solution to generate `HWControl.sys`.
4. Use the provided Python interface in `src/app/` to interact with the driver.
