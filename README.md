# ESP-HOSTED fork for Tanmatsu

This component is used for connecting to the radio on Tanmatsu.

The goal is to get the changes made to the upstream ESP-HOSTED component integrated with the upstream version of ESP-HOSTED in the future.

Changes compared to the upstream version of ESP-HOSTED:

 - It is not started before app_main() gets called, giving the user more control
 - The SDIO initialization function has been modified to allow graceful failure

For more information check out the [readme of the upstream project](https://github.com/espressif/esp-hosted-mcu) or the [issue](https://github.com/espressif/esp-hosted-mcu/issues/48) we have opened on the upstream repository.
