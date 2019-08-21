EESchema Schematic File Version 4
LIBS:NODO-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "jeu. 02 avril 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 1100 1025 0    60   ~ 0
Shield for Arduino Nano
Wire Notes Line
	1075 1100 2275 1100
Wire Notes Line
	2275 1100 2275 925 
Wire Notes Line
	3800 3300 1050 3300
Wire Notes Line
	1050 900  3800 900 
Wire Notes Line
	3800 900  3800 3300
Wire Notes Line
	1050 900  1050 3300
$Comp
L Connector_Generic:Conn_01x03 J1
U 1 1 5BAC22B4
P 7550 3950
F 0 "J1" H 7629 3992 50  0000 L CNN
F 1 "Temp Suelo" H 7629 3901 50  0000 L CNN
F 2 "componentes_nodo:connectorx3" H 7550 3950 50  0001 C CNN
F 3 "~" H 7550 3950 50  0001 C CNN
	1    7550 3950
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 5BAC2446
P 7600 4850
F 0 "J2" H 7679 4892 50  0000 L CNN
F 1 "DHT22" H 7679 4801 50  0000 L CNN
F 2 "componentes_nodo:connectorx3" H 7600 4850 50  0001 C CNN
F 3 "~" H 7600 4850 50  0001 C CNN
	1    7600 4850
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 5BAC4A11
P 8050 6000
F 0 "J3" H 8129 5992 50  0000 L CNN
F 1 "C 3.3V" H 8129 5901 50  0000 L CNN
F 2 "componentes_nodo:connectorx2" H 8050 6000 50  0001 C CNN
F 3 "~" H 8050 6000 50  0001 C CNN
	1    8050 6000
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J5
U 1 1 5BAC4ACB
P 9850 5900
F 0 "J5" H 9930 5892 50  0000 L CNN
F 1 "C 5V" H 9930 5801 50  0000 L CNN
F 2 "componentes_nodo:connectorx2" H 9850 5900 50  0001 C CNN
F 3 "~" H 9850 5900 50  0001 C CNN
	1    9850 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 5900 9650 5750
Wire Wire Line
	9650 6000 9650 6150
Text Label 9650 5750 0    50   ~ 10
5V
Text Label 9650 6150 0    50   ~ 10
GND
Wire Notes Line
	9250 5650 9250 6450
Wire Notes Line
	9250 6450 10600 6450
Wire Notes Line
	10600 6450 10600 5650
Wire Notes Line
	10600 5650 9250 5650
Text Notes 9600 5650 0    50   ~ 10
CONECTOR DE 5v
Wire Wire Line
	7850 6000 7850 5850
Wire Wire Line
	7850 6100 7850 6250
Text Label 7850 5850 0    50   ~ 10
3.3V
Text Label 7850 6250 0    50   ~ 10
GND
Wire Notes Line
	7450 6300 7450 5700
Wire Notes Line
	7450 5700 8700 5700
Wire Notes Line
	8700 5700 8700 6300
Wire Notes Line
	8700 6300 7450 6300
Text Notes 7700 5700 0    50   ~ 10
CONECTOR DE 3.3V\n
Wire Notes Line
	6800 5100 8300 5100
Wire Notes Line
	8300 5100 8300 4500
Wire Notes Line
	8300 4500 6800 4500
Wire Notes Line
	6800 4500 6800 5100
Text Notes 7250 4400 0    50   ~ 10
CONECTOR DHT22
Wire Notes Line
	10800 5200 9000 5200
Text Notes 9550 4600 0    50   ~ 10
Humedad Suelo\n
Wire Notes Line
	6550 4200 8500 4200
Wire Notes Line
	8500 4200 8500 3550
Wire Notes Line
	8500 3550 6550 3550
Wire Notes Line
	6550 3550 6550 4200
Text Notes 7300 3500 0    50   ~ 10
TEMPERATURA SUELO\n
$Comp
L lcd_1602:lcd_1602 U1
U 1 1 5BACA58C
P 4050 4700
F 0 "U1" H 2878 5190 50  0000 L CNN
F 1 "lcd_1602" H 2878 5099 50  0000 L CNN
F 2 "componentes_nodo:lcd_1602" H 4050 4700 50  0001 C CNN
F 3 "" H 4050 4700 50  0001 C CNN
	1    4050 4700
	1    0    0    -1  
$EndComp
$Comp
L A6_GPRS:A6_GSM U2
U 1 1 5BAD86BE
P 5200 4250
F 0 "U2" H 5225 5025 50  0000 C CNN
F 1 "A6_GSM" H 5225 4934 50  0000 C CNN
F 2 "componentes_nodo:A6_GSM" H 5200 4250 50  0001 C CNN
F 3 "" H 5200 4250 50  0001 C CNN
	1    5200 4250
	1    0    0    -1  
$EndComp
Wire Notes Line
	4400 3450 6000 3450
Wire Notes Line
	6000 3450 6000 4950
Text Notes 5000 3450 0    50   ~ 0
MODULO GSM\n
Wire Wire Line
	4700 4400 4400 4400
Wire Wire Line
	4700 4500 4400 4500
Text Label 4400 4400 0    50   ~ 0
RX
Text Label 4400 4500 0    50   ~ 0
TX
Wire Wire Line
	4550 3700 4650 3700
Wire Wire Line
	4550 3800 4700 3800
NoConn ~ 5750 4700
$Comp
L Device:CP C1
U 1 1 5BADFD98
P 4050 3800
F 0 "C1" H 4168 3846 50  0000 L CNN
F 1 "CP" H 4168 3755 50  0000 L CNN
F 2 "componentes_nodo:Capacitor_GSM" H 4088 3650 50  0001 C CNN
F 3 "~" H 4050 3800 50  0001 C CNN
	1    4050 3800
	1    0    0    -1  
$EndComp
Wire Notes Line
	4300 4000 3800 4000
Wire Notes Line
	3800 4000 3800 3550
$Comp
L Device:R_POT_TRIM RContraste1
U 1 1 5BAE333C
P 1150 6250
F 0 "RContraste1" V 1036 6250 50  0000 C CNN
F 1 "10K" V 945 6250 50  0000 C CNN
F 2 "componentes_nodo:potenciometro_presicion" H 1150 6250 50  0001 C CNN
F 3 "~" H 1150 6250 50  0001 C CNN
	1    1150 6250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1150 4650 1150 4900
Text Label 1150 4900 1    50   ~ 0
POT-
Text Label 750  6250 0    50   ~ 0
POT-
Wire Wire Line
	1350 4650 1350 4900
Text Label 1350 4900 1    50   ~ 0
POT_M
Text Label 1150 6100 0    50   ~ 0
POT_M
Text Label 1300 6250 0    50   ~ 0
POT+
Wire Wire Line
	1250 4650 1250 4900
Text Label 1250 4900 1    50   ~ 0
POT+
Wire Wire Line
	750  6250 1000 6250
$Comp
L power:GND #PWR05
U 1 1 5BB015E7
P 750 6450
F 0 "#PWR05" H 750 6200 50  0001 C CNN
F 1 "GND" H 755 6277 50  0000 C CNN
F 2 "" H 750 6450 50  0001 C CNN
F 3 "" H 750 6450 50  0001 C CNN
	1    750  6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	750  6250 750  6450
Text Label 750  6400 0    50   ~ 0
GND
Text Label 1750 5900 0    50   ~ 0
5V
Wire Wire Line
	2550 4650 2550 4900
Wire Wire Line
	2650 4650 2650 4900
Text Label 2650 4900 1    50   ~ 0
GND
$Comp
L Device:R Rbrillo1
U 1 1 5BB07A64
P 2750 6200
F 0 "Rbrillo1" H 2820 6246 50  0000 L CNN
F 1 "R" H 2820 6155 50  0000 L CNN
F 2 "componentes_nodo:Resistencia" V 2680 6200 50  0001 C CNN
F 3 "~" H 2750 6200 50  0001 C CNN
	1    2750 6200
	1    0    0    -1  
$EndComp
Text Label 2750 5950 0    50   ~ 0
R_LIGHT
Text Label 2750 6450 0    50   ~ 0
5V
Text Label 2550 4900 1    50   ~ 0
R_LIGHT
Wire Wire Line
	2750 6350 2750 6450
Wire Wire Line
	2750 6050 2750 5950
Wire Wire Line
	2450 4650 2450 5050
Wire Wire Line
	2350 4650 2350 5100
Wire Wire Line
	2350 5100 3000 5100
Wire Wire Line
	2250 4650 2250 5150
Wire Wire Line
	2250 5150 3100 5150
Wire Wire Line
	2150 4650 2150 5200
Wire Wire Line
	2150 5200 3200 5200
Text Label 2900 5050 0    50   ~ 0
D7
Text Label 3000 5100 0    50   ~ 0
D6
Text Label 3100 5150 0    50   ~ 0
D5
Text Label 3200 5200 0    50   ~ 0
D4
Wire Wire Line
	2450 5050 2900 5050
Wire Notes Line
	700  3600 3400 3600
Wire Notes Line
	3400 3600 3400 6800
Wire Notes Line
	3400 6800 600  6800
Wire Notes Line
	600  6800 600  3600
Wire Notes Line
	600  3600 650  3600
Text Label 4200 6200 0    50   ~ 0
D11(MOSI)
Wire Wire Line
	4200 6200 4550 6200
Wire Wire Line
	4200 6300 4550 6300
Text Label 4200 6300 0    50   ~ 0
D12(MISO)
Wire Wire Line
	4550 6400 4250 6400
Text Label 4250 6400 0    50   ~ 0
13(SCK)
Text Label 5400 5850 0    50   ~ 0
3.3V
Wire Wire Line
	5400 5850 5050 5850
Wire Wire Line
	5050 5850 5050 5900
Text Label 5150 7200 0    50   ~ 0
GND
Wire Wire Line
	4550 6500 4200 6500
Wire Wire Line
	4550 6700 4200 6700
Text Label 4200 6500 0    50   ~ 0
D10
Text Label 4200 6700 0    50   ~ 0
D9
Text Notes 7100 6750 0    79   ~ 16
ESQUEMA CIRCUITO NODO DE CAMPO - TESIS MATEO-JULIAN 2018
NoConn ~ 4550 6800
Wire Notes Line
	3500 7250 6350 7250
Wire Notes Line
	3550 5750 6400 5750
Wire Notes Line
	6400 5750 6400 7200
Wire Notes Line
	3550 5750 3550 7200
Text Label 7500 4600 0    59   ~ 0
5V
Wire Wire Line
	7400 4950 7400 5100
Text Label 7400 5100 0    59   ~ 0
GND
$Comp
L Device:R R1
U 1 1 5BB53B33
P 6900 4750
F 0 "R1" H 6970 4796 50  0000 L CNN
F 1 "10K" H 6970 4705 50  0000 L CNN
F 2 "componentes_nodo:Resistencia" V 6830 4750 50  0001 C CNN
F 3 "~" H 6900 4750 50  0001 C CNN
	1    6900 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 4600 7400 4600
Wire Wire Line
	7400 4600 7400 4750
Wire Wire Line
	6900 4900 7200 4900
Wire Wire Line
	7400 4900 7400 4850
Connection ~ 7400 4600
Wire Wire Line
	7400 4600 7500 4600
Connection ~ 7200 4900
Wire Wire Line
	7200 4900 7400 4900
Wire Wire Line
	7200 4900 7200 5050
Wire Wire Line
	7200 5050 7050 5050
Text Label 7050 5050 0    59   ~ 0
D2
Wire Wire Line
	7350 4050 7350 4200
Wire Wire Line
	7350 3850 7350 3750
Text Label 7350 3700 0    59   ~ 0
5V
Text Label 7350 4200 0    59   ~ 0
GND
Wire Wire Line
	7350 3950 7250 3950
$Comp
L Device:R R2
U 1 1 5BB6D02F
P 7000 3900
F 0 "R2" H 7070 3946 50  0000 L CNN
F 1 "10K" H 7070 3855 50  0000 L CNN
F 2 "componentes_nodo:Resistencia" V 6930 3900 50  0001 C CNN
F 3 "~" H 7000 3900 50  0001 C CNN
	1    7000 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 3750 7350 3750
Connection ~ 7350 3750
Wire Wire Line
	7350 3750 7350 3700
Wire Wire Line
	7000 4050 7150 4050
Wire Wire Line
	7250 4050 7250 3950
Wire Wire Line
	7150 4050 7150 4150
Wire Wire Line
	7150 4150 6900 4150
Connection ~ 7150 4050
Wire Wire Line
	7150 4050 7250 4050
Text Label 6900 4150 0    59   ~ 0
D8
NoConn ~ 2050 4650
NoConn ~ 1950 4650
NoConn ~ 1850 4650
NoConn ~ 1750 4650
Wire Wire Line
	1750 6250 1750 5900
Wire Wire Line
	1300 6250 1750 6250
Wire Wire Line
	5050 7100 5150 7150
Wire Wire Line
	5150 7150 5150 7200
$Comp
L A6_GPRS:NRF24L01_Breakout U3
U 1 1 5BAC0CF5
P 5050 6500
F 0 "U3" H 5528 6478 50  0000 L CNN
F 1 "NRF24L01_Breakout" H 5528 6387 50  0000 L CNN
F 2 "componentes_nodo:modulo_rf" H 5200 7100 50  0001 L CIN
F 3 "http://www.nordicsemi.com/eng/content/download/2730/34105/file/nRF24L01_Product_Specification_v2_0.pdf" H 5050 6400 50  0001 C CNN
	1    5050 6500
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J4
U 1 1 5BB2C4BD
P 9850 4800
F 0 "J4" H 9929 4792 50  0000 L CNN
F 1 "Sensor_HumedadS" H 9929 4701 50  0000 L CNN
F 2 "componentes_nodo:connectorx2" H 9850 4800 50  0001 C CNN
F 3 "~" H 9850 4800 50  0001 C CNN
	1    9850 4800
	1    0    0    -1  
$EndComp
$Comp
L Timer:LM555 U4
U 1 1 5BB2C6F3
P 7850 1250
F 0 "U4" H 8150 1750 50  0000 C CNN
F 1 "LM555" H 8150 1650 50  0000 C CNN
F 2 "componentes_nodo:LM555" H 7850 1250 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm555.pdf" H 7850 1250 50  0001 C CNN
	1    7850 1250
	1    0    0    -1  
$EndComp
Text Label 7850 1850 0    50   ~ 0
GND
Text Label 7850 650  0    50   ~ 0
5V
Wire Wire Line
	8350 1050 8500 1050
Text Label 8500 1050 0    50   ~ 0
S_Hum
$Comp
L Device:R R3
U 1 1 5BB3AB64
P 9000 950
F 0 "R3" H 9070 996 50  0000 L CNN
F 1 "1K" H 9070 905 50  0000 L CNN
F 2 "componentes_nodo:Resistencia" V 8930 950 50  0001 C CNN
F 3 "~" H 9000 950 50  0001 C CNN
	1    9000 950 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5BB3AC33
P 6900 2050
F 0 "#PWR01" H 6900 1800 50  0001 C CNN
F 1 "GND" H 6905 1877 50  0000 C CNN
F 2 "" H 6900 2050 50  0001 C CNN
F 3 "" H 6900 2050 50  0001 C CNN
	1    6900 2050
	1    0    0    -1  
$EndComp
Text Label 6900 2000 0    50   ~ 0
GND
$Comp
L Device:CP C3
U 1 1 5BB4117E
P 6900 1450
F 0 "C3" H 7018 1496 50  0000 L CNN
F 1 "CP" H 7018 1405 50  0000 L CNN
F 2 "componentes_nodo:capacitor" H 6938 1300 50  0001 C CNN
F 3 "~" H 6900 1450 50  0001 C CNN
	1    6900 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 5BB411F7
P 6450 1700
F 0 "C2" H 6568 1746 50  0000 L CNN
F 1 "0.1" H 6568 1655 50  0000 L CNN
F 2 "componentes_nodo:capacitor" H 6488 1550 50  0001 C CNN
F 3 "~" H 6450 1700 50  0001 C CNN
	1    6450 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 1300 6900 1250
Wire Wire Line
	6900 1250 7350 1250
Wire Wire Line
	6900 1600 6900 1900
Wire Wire Line
	6900 1900 7850 1900
Wire Wire Line
	7850 1650 7850 1900
Connection ~ 6900 1900
Wire Wire Line
	6900 1900 6900 2050
Wire Wire Line
	7350 1050 7200 1050
Wire Wire Line
	8350 1450 8350 2100
Wire Wire Line
	8350 2100 7200 2100
Wire Wire Line
	7200 2100 7200 1050
Connection ~ 7200 1050
Wire Wire Line
	6450 1050 7200 1050
Wire Wire Line
	6450 1050 6450 1550
Wire Wire Line
	6900 1900 6450 1900
Wire Wire Line
	6450 1900 6450 1850
Wire Wire Line
	7850 650  7850 700 
Wire Wire Line
	7850 700  9000 700 
Wire Wire Line
	9000 700  9000 800 
Connection ~ 7850 700 
Wire Wire Line
	7850 700  7850 850 
Wire Wire Line
	8350 1250 9000 1250
Wire Wire Line
	9000 1250 9000 1100
Wire Wire Line
	9000 1250 9000 1550
Connection ~ 9000 1250
Text Label 9000 1550 0    50   ~ 0
+_SHUM
$Comp
L Relay:G5Q-1 K1
U 1 1 5BB89596
P 10325 1250
F 0 "K1" H 10755 1296 50  0000 L CNN
F 1 "G5Q-1" H 10755 1205 50  0000 L CNN
F 2 "componentes_nodo:rele" H 10775 1200 50  0001 L CNN
F 3 "https://www.omron.com/ecb/products/pdf/en-g5q.pdf" H 10975 1100 50  0001 L CNN
	1    10325 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	10625 950  10625 850 
Wire Wire Line
	9650 4900 9650 5100
Wire Wire Line
	9650 4800 9650 4700
Text Label 9650 5100 0    50   ~ 0
S_HUM-
Text Label 9650 4700 0    50   ~ 0
S_HUM+
Wire Notes Line
	9000 4600 10800 4600
Wire Notes Line
	10800 4600 10800 5200
Wire Notes Line
	9000 4600 9000 5200
Text Label 10525 1725 0    50   ~ 0
+_SHUM
Text Label 10625 850  0    50   ~ 0
S_HUM+
Wire Wire Line
	6450 1050 6000 1050
Wire Wire Line
	6000 1050 6000 1200
Connection ~ 6450 1050
Text Label 6000 1200 0    50   ~ 0
S_HUM-
Wire Notes Line
	11150 550  5200 550 
Wire Wire Line
	4050 3650 4550 3650
Wire Wire Line
	4550 3650 4550 3700
Wire Wire Line
	4050 3950 4550 3950
Wire Wire Line
	4550 3950 4550 3800
Wire Wire Line
	4050 3950 3900 3950
Connection ~ 4050 3950
Wire Wire Line
	4050 3650 3900 3650
Connection ~ 4050 3650
Text Label 3900 3650 0    50   ~ 0
5V
Text Label 3900 3950 0    50   ~ 0
GND
Wire Notes Line
	4400 3550 4400 3450
Wire Notes Line
	3800 3550 4400 3550
Wire Notes Line
	4300 4000 4300 4950
Wire Notes Line
	4300 4950 6000 4950
Wire Wire Line
	7350 1450 7350 1650
Text Label 7350 1650 0    50   ~ 0
5V
NoConn ~ 10425 950 
$Comp
L Transistor_BJT:BC337 47K1
U 1 1 5BC01797
P 10025 1925
F 0 "47K1" H 10216 1971 50  0000 L CNN
F 1 "BC337" H 10216 1880 50  0000 L CNN
F 2 "componentes_nodo:Transisitor_BC337" H 10225 1850 50  0001 L CIN
F 3 "http://www.nxp.com/documents/data_sheet/BC817_BC817W_BC337.pdf" H 10025 1925 50  0001 L CNN
	1    10025 1925
	1    0    0    -1  
$EndComp
$Comp
L Device:R 3,3K1
U 1 1 5BC134C0
P 9575 1925
F 0 "3,3K1" V 9368 1925 50  0000 C CNN
F 1 "R1" V 9459 1925 50  0000 C CNN
F 2 "componentes_nodo:Resistencia" V 9505 1925 50  0001 C CNN
F 3 "~" H 9575 1925 50  0001 C CNN
	1    9575 1925
	0    1    1    0   
$EndComp
$Comp
L Device:R 47K2
U 1 1 5BC135C1
P 9775 2125
F 0 "47K2" H 9705 2079 50  0000 R CNN
F 1 "R2" H 9705 2170 50  0000 R CNN
F 2 "componentes_nodo:Resistencia" V 9705 2125 50  0001 C CNN
F 3 "~" H 9775 2125 50  0001 C CNN
	1    9775 2125
	-1   0    0    1   
$EndComp
Wire Wire Line
	9725 1925 9775 1925
Wire Wire Line
	9775 1975 9775 1925
Connection ~ 9775 1925
Wire Wire Line
	9775 1925 9825 1925
Text Label 9275 1925 2    50   ~ 0
D3
Wire Wire Line
	9275 1925 9425 1925
$Comp
L power:GND #PWR0102
U 1 1 5BC2E3D6
P 10125 2425
F 0 "#PWR0102" H 10125 2175 50  0001 C CNN
F 1 "GND" H 10130 2252 50  0000 C CNN
F 2 "" H 10125 2425 50  0001 C CNN
F 3 "" H 10125 2425 50  0001 C CNN
	1    10125 2425
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 4650 1550 4950
Text Label 1550 4950 1    50   ~ 0
GND
Wire Notes Line
	3300 5400 3300 5675
Wire Notes Line
	3300 5675 1425 5675
Wire Notes Line
	1425 5675 1425 5400
Wire Notes Line
	1425 5400 3300 5400
Text Notes 1525 5550 0    50   ~ 0
RS ----> A1
Wire Wire Line
	10525 1550 10525 1725
Wire Wire Line
	10125 2125 10125 2375
Wire Wire Line
	9775 2275 9775 2375
Wire Wire Line
	9775 2375 10125 2375
Connection ~ 10125 2375
Wire Wire Line
	10125 2375 10125 2425
Wire Wire Line
	10125 1550 10125 1650
Text Label 10125 700  0    50   ~ 0
5V
Wire Wire Line
	10125 700  10125 825 
$Comp
L Device:D D1
U 1 1 5BC9F633
P 9725 1250
F 0 "D1" V 9679 1329 50  0000 L CNN
F 1 "1N4007" H 9575 1150 50  0000 L CNN
F 2 "componentes_nodo:Resistencia" H 9725 1250 50  0001 C CNN
F 3 "~" H 9725 1250 50  0001 C CNN
	1    9725 1250
	0    1    1    0   
$EndComp
Wire Wire Line
	9725 1100 9725 825 
Wire Wire Line
	9725 825  10125 825 
Connection ~ 10125 825 
Wire Wire Line
	10125 825  10125 950 
Wire Wire Line
	9725 1400 9725 1650
Wire Wire Line
	9725 1650 10125 1650
Connection ~ 10125 1650
Wire Wire Line
	10125 1650 10125 1725
Wire Notes Line
	11150 2775 5200 2775
Wire Notes Line
	5200 600  5200 2775
Wire Notes Line
	11150 550  11150 2775
Text Notes 1525 5650 0    50   ~ 0
E -----> A0
Text Notes 7700 2900 0    59   ~ 12
Circuito de Sensor de Humedad
Wire Wire Line
	1650 4650 1650 5300
Wire Wire Line
	1650 5300 3650 5300
Wire Wire Line
	3700 5350 1450 5350
Wire Wire Line
	1450 5350 1450 4650
Text Notes 4550 5700 0    50   ~ 10
MODULO nRF24l01
$Comp
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 5BF3E78B
P 2300 2200
F 0 "A1" H 2300 1114 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 2300 1023 50  0000 C CNN
F 2 "componentes_nodo:Arduino_nano" H 2450 1250 50  0001 L CNN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 2300 1200 50  0001 C CNN
	1    2300 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 1600 1800 1600
Wire Wire Line
	1800 1700 1600 1700
Text Label 1600 1600 0    50   ~ 0
TX
Text Label 1600 1700 0    50   ~ 0
RX
Wire Wire Line
	1800 2300 1400 2300
Wire Wire Line
	1800 2200 1400 2200
Wire Wire Line
	1800 2100 1400 2100
Wire Wire Line
	1800 2000 1400 2000
Text Label 1400 2000 0    50   ~ 0
D4
Text Label 1400 2100 0    50   ~ 0
D5
Text Label 1400 2200 0    50   ~ 0
D6
Text Label 1400 2300 0    50   ~ 0
D7
Wire Wire Line
	2400 3200 3200 3200
Text Label 3200 3200 0    50   ~ 0
GND
Wire Wire Line
	2500 1200 2500 1150
Wire Wire Line
	2500 1150 2650 1150
Text Label 2650 1150 0    50   ~ 0
5V
Wire Wire Line
	2400 1200 2400 1050
Wire Wire Line
	2400 1050 2900 1050
Text Label 2900 1050 0    50   ~ 0
3.3V
Wire Wire Line
	3700 2300 2800 2300
Wire Wire Line
	3700 2300 3700 5350
Wire Wire Line
	3650 2200 2800 2200
Wire Wire Line
	3650 2200 3650 5300
Wire Wire Line
	1800 2400 1400 2400
Text Label 1400 2400 0    50   ~ 0
D8
Wire Wire Line
	1800 1800 1400 1800
Text Label 1400 1800 0    50   ~ 0
D2
Wire Wire Line
	1800 1900 1400 1900
Text Label 1400 1900 0    50   ~ 0
D3
Wire Wire Line
	2800 2400 3000 2400
Text Label 3000 2400 0    50   ~ 0
S_Hum
Wire Wire Line
	1800 2700 1400 2700
Wire Wire Line
	1800 2800 1400 2800
Wire Wire Line
	1800 2900 1400 2900
Text Label 1400 2700 0    50   ~ 0
D11(MOSI)
Text Label 1400 2800 0    50   ~ 0
D12(MISO)
Text Label 1400 2900 0    50   ~ 0
13(SCK)
Wire Wire Line
	1800 2600 1400 2600
Wire Wire Line
	1800 2500 1400 2500
Text Label 1400 2600 0    50   ~ 0
D10
Text Label 1400 2500 0    50   ~ 0
D9
NoConn ~ 2800 1700
NoConn ~ 2800 1600
NoConn ~ 2800 2000
Wire Wire Line
	2800 2500 3000 2500
Text Label 3000 2500 0    50   ~ 0
PWR
Wire Wire Line
	4650 3700 4650 3550
Wire Wire Line
	4650 3550 5900 3550
Wire Wire Line
	5900 3550 5900 4800
Wire Wire Line
	5900 4800 5750 4800
Connection ~ 4650 3700
Wire Wire Line
	4650 3700 4700 3700
Wire Wire Line
	2300 3200 2400 3200
Connection ~ 2400 3200
Text Notes 750  3750 0    50   ~ 0
Utilizar en el conector de LCD tira de Pines macho "Doblados"
$EndSCHEMATC
