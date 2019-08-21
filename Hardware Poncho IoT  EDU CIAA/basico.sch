EESchema Schematic File Version 4
LIBS:basico-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Poncho Básico (Editar y colocar el nombre final)"
Date "2016-08-07"
Rev "1.0"
Comp "Proyecto CIAA - COMPUTADORA INDUSTRIAL ABIERTA ARGENTINA"
Comment1 "https://github.com/ciaa/Ponchos/tree/master/Basico/doc"
Comment2 "Autores y Licencia del modelo (Diego Brengi - UNLaM)"
Comment3 "Autor del poncho (COMPLETAR NOMBRE Y APELLIDO). Ver directorio \"doc\""
Comment4 ""
$EndDescr
$Comp
L basico-rescue:OSHWA #G102
U 1 1 560A0A28
P 10800 6050
F 0 "#G102" H 10770 6450 60  0001 C CNN
F 1 "OSHWA" H 10800 6353 60  0001 C CNN
F 2 "Poncho_Esqueleto:Logo_OSHWA" H 10800 6050 60  0001 C CNN
F 3 "" H 10800 6050 60  0000 C CNN
	1    10800 6050
	1    0    0    -1  
$EndComp
$Comp
L basico-rescue:Logo_Poncho #G101
U 1 1 560CFFC0
P 10150 6000
F 0 "#G101" H 10100 5600 60  0001 C CNN
F 1 "Logo_Poncho" H 10350 5600 60  0001 C CNN
F 2 "Poncho_Esqueleto:Logo_Poncho" H 10150 6000 60  0001 C CNN
F 3 "" H 10150 6000 60  0001 C CNN
	1    10150 6000
	1    0    0    -1  
$EndComp
$Comp
L basico-rescue:+3.3V #PWR01
U 1 1 560EB699
P 1050 1075
F 0 "#PWR01" H 1050 1035 30  0001 C CNN
F 1 "+3.3V" H 1050 1185 30  0000 C CNN
F 2 "" H 1050 1075 60  0000 C CNN
F 3 "" H 1050 1075 60  0000 C CNN
	1    1050 1075
	1    0    0    -1  
$EndComp
$Comp
L basico-rescue:+5V #PWR02
U 1 1 560EB7BE
P 3150 1025
F 0 "#PWR02" H 3150 1115 20  0001 C CNN
F 1 "+5V" H 3150 1175 30  0000 C CNN
F 2 "" H 3150 1025 60  0000 C CNN
F 3 "" H 3150 1025 60  0000 C CNN
	1    3150 1025
	1    0    0    -1  
$EndComp
$Comp
L basico-rescue:Conn_Poncho2P_2x_20x2 XA101
U 1 1 57A7A0F8
P 1800 1525
F 0 "XA101" H 2100 1925 60  0000 C CNN
F 1 "Conn_Poncho2P_2x_20x2" H 2150 -175 60  0000 C CNN
F 2 "footprint:Conn_Poncho_SinBorde" H 1800 1525 60  0001 C CNN
F 3 "" H 1800 1525 60  0000 C CNN
F 4 "Harwin" H 1800 1525 60  0001 C CNN "Manf"
F 5 "M50-3502042" H 1800 1525 60  0001 C CNN "Manf#"
F 6 "952-1387-ND" H 1800 1525 60  0001 C CNN "Digikey#"
	1    1800 1525
	1    0    0    -1  
$EndComp
$Comp
L basico-rescue:Conn_Poncho2P_2x_20x2 XA101
U 2 1 57A7A13C
P 1925 5425
F 0 "XA101" H 2225 5825 60  0000 C CNN
F 1 "Conn_Poncho2P_2x_20x2" H 2275 3725 60  0000 C CNN
F 2 "footprint:Conn_Poncho_SinBorde" H 1925 5425 60  0001 C CNN
F 3 "" H 1925 5425 60  0000 C CNN
F 4 "Harwin" H 1925 5425 60  0001 C CNN "Manf"
F 5 "M50-3502042" H 1925 5425 60  0001 C CNN "Manf#"
F 6 "952-1387-ND" H 1925 5425 60  0001 C CNN "Digikey#"
	2    1925 5425
	1    0    0    -1  
$EndComp
$Comp
L basico-rescue:GND #PWR06
U 1 1 57A7A207
P 2950 3325
F 0 "#PWR06" H 2950 3325 30  0001 C CNN
F 1 "GND" H 2950 3255 30  0001 C CNN
F 2 "" H 2950 3325 60  0000 C CNN
F 3 "" H 2950 3325 60  0000 C CNN
	1    2950 3325
	1    0    0    -1  
$EndComp
$Comp
L basico-rescue:+3.3VP #PWR07
U 1 1 57A7A9F3
P 1325 4975
F 0 "#PWR07" H 1475 4925 50  0001 C CNN
F 1 "+3.3VP" H 1325 5075 50  0000 C CNN
F 2 "" H 1325 4975 50  0000 C CNN
F 3 "" H 1325 4975 50  0000 C CNN
	1    1325 4975
	1    0    0    -1  
$EndComp
Wire Wire Line
	1675 5125 1325 5125
Wire Wire Line
	1325 5125 1325 4975
Wire Wire Line
	2875 5125 3325 5125
Wire Wire Line
	1050 1225 1050 1075
Wire Wire Line
	2750 1225 3150 1225
Wire Wire Line
	3150 1225 3150 1025
Wire Wire Line
	1050 1225 1550 1225
$Comp
L HC05:HC05 U3
U 1 1 5B9F6D5C
P 6225 3125
F 0 "U3" H 6250 3450 50  0000 C CNN
F 1 "HC05" H 6250 3359 50  0000 C CNN
F 2 "footprint:HC05" H 6175 2775 50  0001 C CNN
F 3 "" H 6175 2775 50  0001 C CNN
	1    6225 3125
	1    0    0    -1  
$EndComp
$Comp
L SD_CARD_CIAA:SD_card_CIAA U4
U 1 1 5BA4F0E3
P 10775 3525
F 0 "U4" V 10990 3547 50  0000 R CNN
F 1 "SD_card_CIAA" V 11575 4175 50  0000 R CNN
F 2 "footprint:SD_card_CIAA" H 10775 3525 50  0001 C CNN
F 3 "" H 10775 3525 50  0001 C CNN
	1    10775 3525
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10675 3925 10675 4250
$Comp
L basico-rescue:+3.3VP #PWR0103
U 1 1 5BAA6098
P 8950 2725
F 0 "#PWR0103" H 9100 2675 50  0001 C CNN
F 1 "+3.3VP" H 9125 2775 50  0000 C CNN
F 2 "" H 8950 2725 50  0000 C CNN
F 3 "" H 8950 2725 50  0000 C CNN
	1    8950 2725
	1    0    0    -1  
$EndComp
$Comp
L basico-rescue:+3.3V #PWR0107
U 1 1 5BB203A4
P 6875 4100
F 0 "#PWR0107" H 6875 4060 30  0001 C CNN
F 1 "+3.3V" H 6975 4175 30  0000 C CNN
F 2 "" H 6875 4100 60  0000 C CNN
F 3 "" H 6875 4100 60  0000 C CNN
	1    6875 4100
	1    0    0    -1  
$EndComp
$Comp
L basico-rescue:GND #PWR0108
U 1 1 5BB318FE
P 5915 5300
F 0 "#PWR0108" H 5915 5300 30  0001 C CNN
F 1 "GND" H 5915 5230 30  0001 C CNN
F 2 "" H 5915 5300 60  0000 C CNN
F 3 "" H 5915 5300 60  0000 C CNN
	1    5915 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5915 5300 5915 5100
Wire Wire Line
	5915 5100 6025 5100
$Comp
L A6_GPRS:A6_GSM U5
U 1 1 5BB600DD
P 6350 1625
F 0 "U5" H 6425 1075 50  0000 C CNN
F 1 "A6_GSM" H 6375 2309 50  0000 C CNN
F 2 "footprint:A6_gsm" H 6350 1625 50  0001 C CNN
F 3 "" H 6350 1625 50  0001 C CNN
	1    6350 1625
	1    0    0    -1  
$EndComp
$Comp
L basico-rescue:GND #PWR0110
U 1 1 5BB6BAA7
P 7250 2300
F 0 "#PWR0110" H 7250 2300 30  0001 C CNN
F 1 "GND" H 7250 2230 30  0001 C CNN
F 2 "" H 7250 2300 60  0000 C CNN
F 3 "" H 7250 2300 60  0000 C CNN
	1    7250 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 2075 7250 2300
$Comp
L Device:CP C1
U 1 1 5BA447EF
P 5350 1175
F 0 "C1" H 5468 1221 50  0000 L CNN
F 1 "CP" H 5468 1130 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P5.00mm" H 5388 1025 50  0001 C CNN
F 3 "~" H 5350 1175 50  0001 C CNN
	1    5350 1175
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 1075 5450 1025
Wire Wire Line
	5450 1025 5350 1025
$Comp
L basico-rescue:GND #PWR0109
U 1 1 5BA53C51
P 5350 1400
F 0 "#PWR0109" H 5350 1400 30  0001 C CNN
F 1 "GND" H 5350 1330 30  0001 C CNN
F 2 "" H 5350 1400 60  0000 C CNN
F 3 "" H 5350 1400 60  0000 C CNN
	1    5350 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 1325 5350 1400
Wire Wire Line
	5350 1325 5700 1325
Wire Wire Line
	5700 1325 5700 1175
Wire Wire Line
	5700 1175 5850 1175
Connection ~ 5350 1325
$Comp
L basico-rescue:+5V #PWR0111
U 1 1 5BA6B5D8
P 5350 1025
F 0 "#PWR0111" H 5350 1115 20  0001 C CNN
F 1 "+5V" H 5350 1175 30  0000 C CNN
F 2 "" H 5350 1025 60  0000 C CNN
F 3 "" H 5350 1025 60  0000 C CNN
	1    5350 1025
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 1075 5850 1075
$Comp
L basico-rescue:+5V #PWR0101
U 1 1 5BAB275C
P 3325 4850
F 0 "#PWR0101" H 3325 4940 20  0001 C CNN
F 1 "+5V" H 3325 5000 30  0000 C CNN
F 2 "" H 3325 4850 60  0000 C CNN
F 3 "" H 3325 4850 60  0000 C CNN
	1    3325 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3325 4850 3325 5125
$Comp
L basico-rescue:+5V #PWR0102
U 1 1 5BAC0A05
P 10175 4125
F 0 "#PWR0102" H 10175 4215 20  0001 C CNN
F 1 "+5V" H 10175 4275 30  0000 C CNN
F 2 "" H 10175 4125 60  0000 C CNN
F 3 "" H 10175 4125 60  0000 C CNN
	1    10175 4125
	-1   0    0    1   
$EndComp
$Comp
L basico-rescue:GND #PWR015
U 1 1 57A7ADB5
P 10275 4125
F 0 "#PWR015" H 10275 4125 30  0001 C CNN
F 1 "GND" H 10275 4055 30  0001 C CNN
F 2 "" H 10275 4125 60  0000 C CNN
F 3 "" H 10275 4125 60  0000 C CNN
	1    10275 4125
	1    0    0    -1  
$EndComp
$Comp
L basico-rescue:+5V #PWR0106
U 1 1 5BAF9980
P 5850 2975
F 0 "#PWR0106" H 5850 3065 20  0001 C CNN
F 1 "+5V" H 5850 3125 30  0000 C CNN
F 2 "" H 5850 2975 60  0000 C CNN
F 3 "" H 5850 2975 60  0000 C CNN
	1    5850 2975
	1    0    0    -1  
$EndComp
$Comp
L RF:NRF24L01_Breakout U1
U 1 1 5B9DB070
P 8950 3375
F 0 "U1" H 9150 2975 50  0000 L CNN
F 1 "NRF24L01_Breakout" V 9375 3000 50  0000 L CNN
F 2 "RF_Module:nRF24L01_Breakout" H 9100 3975 50  0001 L CIN
F 3 "http://www.nordicsemi.com/eng/content/download/2730/34105/file/nRF24L01_Product_Specification_v2_0.pdf" H 8950 3275 50  0001 C CNN
	1    8950 3375
	1    0    0    -1  
$EndComp
$Comp
L basico-rescue:GND #PWR0115
U 1 1 5BB489C6
P 5850 3325
F 0 "#PWR0115" H 5850 3325 30  0001 C CNN
F 1 "GND" H 5850 3255 30  0001 C CNN
F 2 "" H 5850 3325 60  0000 C CNN
F 3 "" H 5850 3325 60  0000 C CNN
	1    5850 3325
	1    0    0    -1  
$EndComp
Text Label 2875 6125 0    50   ~ 0
D7
Text Label 2875 6225 0    50   ~ 0
RS
Text Label 2875 6325 0    50   ~ 0
D6
Text Label 2875 6425 0    50   ~ 0
D5
Text Label 2875 6525 0    50   ~ 0
D4
Text Label 1575 6225 2    50   ~ 0
E
Wire Wire Line
	6875 4250 6825 4250
Wire Wire Line
	6825 4750 6875 4750
Wire Wire Line
	6875 4750 6875 4250
$Comp
L lcd_1602:lcd_1602 U6
U 1 1 5BB04F44
P 11825 1650
F 0 "U6" H 10653 2140 50  0000 L CNN
F 1 "lcd_1602" H 8925 2450 50  0000 L CNN
F 2 "" H 11825 1650 50  0001 C CNN
F 3 "" H 11825 1650 50  0001 C CNN
	1    11825 1650
	1    0    0    -1  
$EndComp
Text Label 10225 1900 3    50   ~ 0
D7
Text Label 10125 1900 3    50   ~ 0
D6
Text Label 10025 1900 3    50   ~ 0
D5
Text Label 9925 1900 3    50   ~ 0
D4
Text Label 9425 1900 3    50   ~ 0
E
Text Label 9225 1900 3    50   ~ 0
RS
Wire Wire Line
	9225 1600 9225 1900
Wire Wire Line
	9425 1600 9425 1900
Wire Wire Line
	10225 1600 10225 1900
Wire Wire Line
	10125 1600 10125 1900
Wire Wire Line
	10025 1600 10025 1900
Wire Wire Line
	9925 1600 9925 1900
Wire Wire Line
	9525 1600 9525 1700
Wire Wire Line
	9525 1700 9625 1700
Wire Wire Line
	9825 1700 9825 1600
Wire Wire Line
	9725 1600 9725 1700
Connection ~ 9725 1700
Wire Wire Line
	9725 1700 9825 1700
Wire Wire Line
	9625 1600 9625 1700
Connection ~ 9625 1700
Wire Wire Line
	9625 1700 9725 1700
Wire Wire Line
	10425 1600 10425 1700
Wire Wire Line
	10425 1700 9825 1700
Connection ~ 9825 1700
$Comp
L Device:R_POT_US RV1
U 1 1 5BB506DA
P 8400 1725
F 0 "RV1" H 8332 1771 50  0000 R CNN
F 1 "R_POT_US" H 8332 1680 50  0000 R CNN
F 2 "" H 8400 1725 50  0001 C CNN
F 3 "~" H 8400 1725 50  0001 C CNN
	1    8400 1725
	1    0    0    -1  
$EndComp
$Comp
L basico-rescue:+5V #PWR0104
U 1 1 5BB507D5
P 8400 1525
F 0 "#PWR0104" H 8400 1615 20  0001 C CNN
F 1 "+5V" H 8400 1675 30  0000 C CNN
F 2 "" H 8400 1525 60  0000 C CNN
F 3 "" H 8400 1525 60  0000 C CNN
	1    8400 1525
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 1525 8400 1575
$Comp
L basico-rescue:GND #PWR0105
U 1 1 5BB60B01
P 8400 1975
F 0 "#PWR0105" H 8400 1975 30  0001 C CNN
F 1 "GND" H 8400 1905 30  0001 C CNN
F 2 "" H 8400 1975 60  0000 C CNN
F 3 "" H 8400 1975 60  0000 C CNN
	1    8400 1975
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 1875 8400 1975
Wire Wire Line
	9325 1600 9325 1700
Wire Wire Line
	9325 1700 9525 1700
Connection ~ 9525 1700
Wire Wire Line
	8550 1725 9125 1725
Wire Wire Line
	9125 1725 9125 1600
$Comp
L basico-rescue:GND #PWR0112
U 1 1 5BB1510E
P 9025 1850
F 0 "#PWR0112" H 9025 1850 30  0001 C CNN
F 1 "GND" H 9025 1780 30  0001 C CNN
F 2 "" H 9025 1850 60  0000 C CNN
F 3 "" H 9025 1850 60  0000 C CNN
	1    9025 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9025 1850 9025 1600
$Comp
L basico-rescue:+5V #PWR0113
U 1 1 5BB25F93
P 10325 1825
F 0 "#PWR0113" H 10325 1915 20  0001 C CNN
F 1 "+5V" H 10325 1975 30  0000 C CNN
F 2 "" H 10325 1825 60  0000 C CNN
F 3 "" H 10325 1825 60  0000 C CNN
	1    10325 1825
	-1   0    0    1   
$EndComp
Wire Wire Line
	8925 1850 8925 1600
Wire Notes Line
	11050 600  11050 2225
Wire Notes Line
	7925 2225 7925 600 
Wire Notes Line
	7925 600  11050 600 
Wire Notes Line
	7925 2225 11050 2225
Text Label 10675 4250 3    50   ~ 0
SCK
Text Label 10575 4250 3    50   ~ 0
MOSI
Text Label 10475 4250 3    50   ~ 0
MISO
Text Label 10375 4250 3    50   ~ 0
CS
Wire Wire Line
	10375 3925 10375 4250
Wire Wire Line
	10475 3925 10475 4250
Wire Wire Line
	10575 3925 10575 4250
Wire Wire Line
	10275 3925 10275 4125
Wire Wire Line
	10175 4125 10175 3925
Text Label 8200 3075 0    50   ~ 0
MOSI
Wire Wire Line
	8200 3075 8450 3075
Text Label 8200 3175 0    50   ~ 0
MISO
Wire Wire Line
	8200 3175 8450 3175
Text Label 8200 3275 0    50   ~ 0
SCK
Text Label 8200 3375 0    50   ~ 0
CSN
Text Label 8200 3575 0    50   ~ 0
CE
Text Label 8200 3675 0    50   ~ 0
IRQ
Wire Wire Line
	8200 3275 8450 3275
Wire Wire Line
	8200 3375 8450 3375
Wire Wire Line
	8200 3575 8450 3575
Wire Wire Line
	8200 3675 8450 3675
Wire Wire Line
	8950 2725 8950 2775
$Comp
L basico-rescue:GND #PWR0114
U 1 1 5BB18C55
P 8950 4000
F 0 "#PWR0114" H 8950 4000 30  0001 C CNN
F 1 "GND" H 8950 3930 30  0001 C CNN
F 2 "" H 8950 4000 60  0000 C CNN
F 3 "" H 8950 4000 60  0000 C CNN
	1    8950 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 4000 8950 3975
Wire Notes Line
	11050 2350 7925 2350
Text Label 2975 5925 0    50   ~ 0
MISO
Text Label 2975 6025 0    50   ~ 0
SCK
Wire Wire Line
	2975 6025 2875 6025
Wire Wire Line
	2975 5925 2875 5925
Text Label 1600 6125 2    50   ~ 0
MOSI
Wire Wire Line
	1600 6125 1675 6125
Text Label 2975 6725 0    50   ~ 0
CS
Wire Wire Line
	2975 6725 2875 6725
Text Label 2975 6825 0    50   ~ 0
IRQ
Text Label 2975 6925 0    50   ~ 0
CE
Wire Wire Line
	2975 6925 2875 6925
Text Label 1550 6525 2    50   ~ 0
CSN
Wire Wire Line
	1550 6525 1675 6525
Text Label 3000 6625 0    50   ~ 0
UART0_TX
Wire Wire Line
	3000 6625 2875 6625
Text Label 1550 6625 2    50   ~ 0
UART0_RX
Wire Wire Line
	1550 6625 1675 6625
Text Label 3000 7025 0    50   ~ 0
PWR_A6
Wire Wire Line
	2875 7025 3000 7025
Connection ~ 5350 1025
Text Label 5725 1775 2    50   ~ 0
UART0_RX
Wire Wire Line
	5725 1775 5850 1775
Text Label 5725 1875 2    50   ~ 0
UART0_TX
Wire Wire Line
	5725 1875 5850 1875
Text Label 6950 2175 0    50   ~ 0
PWR_A6
Wire Wire Line
	6950 2175 6900 2175
Wire Wire Line
	6900 2075 7250 2075
Wire Notes Line
	5100 2425 7650 2425
Text Notes 7250 750  0    63   Italic 13
UART0
Text Label 1600 5525 2    50   ~ 0
UART2_TX
Wire Wire Line
	1600 5525 1675 5525
Text Label 2975 5525 0    50   ~ 0
UART2_RX
Wire Wire Line
	2975 5525 2875 5525
Text Label 6625 3025 0    50   ~ 0
UART2_RX
Text Label 6625 3125 0    50   ~ 0
UART2_TX
Wire Wire Line
	5850 3325 5850 3225
Wire Wire Line
	5850 3225 5925 3225
Wire Wire Line
	5850 2975 5850 3125
Wire Wire Line
	5850 3125 5925 3125
Wire Notes Line
	5100 2550 7650 2550
Wire Notes Line
	7650 2550 7650 3575
Wire Notes Line
	7650 3575 5100 3575
Wire Notes Line
	5100 3575 5100 2525
Wire Notes Line
	5100 2525 5125 2525
Text Notes 7275 2675 0    63   Italic 13
UART2
Text Label 1500 2325 2    50   ~ 0
UART3_RX
Text Label 1500 2425 2    50   ~ 0
UART3_TX
Wire Wire Line
	1500 2425 1550 2425
Wire Notes Line
	5100 3725 7650 3725
Wire Notes Line
	7650 3725 7650 5475
Wire Notes Line
	7650 5475 5100 5475
Wire Notes Line
	5100 5475 5100 3725
Text Label 6875 5100 0    50   ~ 0
UART3_RX
Text Label 5975 4250 2    50   ~ 0
UART3_TX
Wire Wire Line
	5975 4250 6025 4250
Wire Wire Line
	6825 5100 6875 5100
$Comp
L ESP8266_CIAA:ESP8266_CIAA U2
U 1 1 5BC2EA41
P 6375 4700
F 0 "U2" H 6450 4300 50  0000 C CNN
F 1 "ESP8266_CIAA" H 6425 5324 50  0000 C CNN
F 2 "" V 6775 4650 50  0001 C CNN
F 3 "" V 6775 4650 50  0001 C CNN
	1    6375 4700
	1    0    0    -1  
$EndComp
Text Notes 7575 3875 2    63   Italic 13
UART3
Wire Wire Line
	2750 3125 2950 3125
Wire Wire Line
	2950 3125 2950 3325
$Comp
L basico-rescue:GND #PWR0116
U 1 1 5BC43C0E
P 3150 1600
F 0 "#PWR0116" H 3150 1600 30  0001 C CNN
F 1 "GND" H 3150 1530 30  0001 C CNN
F 2 "" H 3150 1600 60  0000 C CNN
F 3 "" H 3150 1600 60  0000 C CNN
	1    3150 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 1325 3150 1325
Wire Wire Line
	3150 1325 3150 1600
$Comp
L basico-rescue:GND #PWR0117
U 1 1 5BC4D60A
P 1350 5250
F 0 "#PWR0117" H 1350 5250 30  0001 C CNN
F 1 "GND" H 1350 5180 30  0001 C CNN
F 2 "" H 1350 5250 60  0000 C CNN
F 3 "" H 1350 5250 60  0000 C CNN
	1    1350 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1675 5225 1350 5225
Wire Wire Line
	1350 5225 1350 5250
Wire Wire Line
	1575 6225 1675 6225
Text Notes 6275 3875 2    71   Italic 14
WI-FI
Wire Notes Line
	7125 3725 7125 3925
Wire Notes Line
	5100 3925 7650 3925
Wire Notes Line
	7650 2700 5100 2700
Wire Notes Line
	7175 2550 7175 2700
Text Notes 6525 2675 2    71   Italic 14
BLUETOOTH
Wire Notes Line
	7650 775  5100 775 
Wire Notes Line
	5100 625  7650 625 
Wire Notes Line
	7650 625  7650 2425
Wire Notes Line
	5100 625  5100 2425
Wire Notes Line
	7175 775  7175 625 
Wire Wire Line
	6875 4250 6875 4100
Connection ~ 6875 4250
Text Notes 6325 750  2    71   Italic 14
GPRS
Wire Notes Line
	7925 2525 11050 2525
Wire Notes Line
	11050 2350 11050 4500
Wire Notes Line
	9575 2350 9575 4500
Wire Notes Line
	7925 2350 7925 4500
Wire Notes Line
	7925 4500 11050 4500
Text Notes 10400 2475 2    71   Italic 14
SD_CARD
Text Notes 10975 2500 2    71   Italic 14
SPI
Text Notes 8625 2475 2    71   Italic 14
RF
Text Notes 9475 2500 2    71   Italic 14
SPI
Wire Notes Line
	10700 2525 10700 2350
Wire Notes Line
	9200 2525 9200 2350
Wire Wire Line
	6575 3025 6625 3025
Wire Wire Line
	6575 3125 6625 3125
Wire Wire Line
	1500 2325 1550 2325
Wire Wire Line
	10325 1825 10325 1600
$Comp
L basico-rescue:+5V #PWR0118
U 1 1 5BCA28C9
P 8925 1850
F 0 "#PWR0118" H 8925 1940 20  0001 C CNN
F 1 "+5V" H 8925 2000 30  0000 C CNN
F 2 "" H 8925 1850 60  0000 C CNN
F 3 "" H 8925 1850 60  0000 C CNN
	1    8925 1850
	-1   0    0    1   
$EndComp
$Comp
L basico-rescue:GND #PWR0119
U 1 1 5BCA5316
P 10425 1850
F 0 "#PWR0119" H 10425 1850 30  0001 C CNN
F 1 "GND" H 10425 1780 30  0001 C CNN
F 2 "" H 10425 1850 60  0000 C CNN
F 3 "" H 10425 1850 60  0000 C CNN
	1    10425 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	10425 1850 10425 1700
Connection ~ 10425 1700
Wire Wire Line
	2875 6825 2975 6825
$EndSCHEMATC
