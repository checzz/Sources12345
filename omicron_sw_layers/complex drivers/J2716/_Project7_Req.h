/*

›Driver API (follow AUTOSAR naming convention) 10 %
  –Driver initialization                                                      [DONE]
  –Data to be transmitted                                                     [DONE]
  –Enable/Disable Notification                                                [DONE]

›Status Structures 10 %
  –Use Dynamic Memory Allocation with the following parameters
    ›Channel                                                                  [DONE]
    ›CRC1
    ›CRC2
    ›…
    ›CRCn
    ›Checksum

›Configuration Parameters 30 %
  –Tick period (3us – 90us, 3us resolution)                                   [DONE]
  –Enable optional pause pulse                                                [DONE]
  –Output pin                                                                 [DONE]
  –Message length (number of nibbles that have to be sent; 1 - 6)             [DONE]
  –Low driven pulse ticks ( > 4)                                              [DONE]
  –Support for [1 – n] SENT channels (use only one hardware timer)            [DONE]
  –Support for notification on each transmitted message                       [DONE]

›File dependencies 10 %
  –Internal Driver Structure                                                  [DONE]
  –Driver Dependencies to other Modules                                       [DONE]

›Interrupt Configuration 10 %
  –PIT interrupts XGATE (tick)                                                [DONE]
  –XGATE interrupts S12 (notification)                                        [DONE]

›Programmable with Omicron Bootloader 10 %
  –Use two buttons mechanism to invalidate application and generate MCU Reset [DONE]

›SENT Protocol Driver Implemented on XGATE 20 % –Include a small application
  –Data consistency between S12 and XGATE                                     [DONE]
*/