Please include your answers to the questions below with your submission, entering into the space below each question
See [Mastering Markdown](https://guides.github.com/features/mastering-markdown/) for github markdown formatting if desired.

**Note: All average currents should be taken at a time scale of 200mS/div. See the pop-up menu in the lower-right corner of the Energy Profiler window**

**1. Fill in the below chart based on currents measured in each energy mode, replacing each TBD with measured values.  Use the [Selecting Ranges](https://www.silabs.com/documents/public/user-guides/ug343-multinode-energy-profiler.pdf) feature of the profiler to select the appropriate measurement range.  Your measurements should be accurate to 10%**

Energy Mode | Period average current (uA) | Average Current with LED off (uA) | Average Current with LED On (uA)
------------| ----------------------------|-----------------------------------|-------------------------
EM0         |           4990              |           4960                    |         5450
EM1         |          43.77	          |           9.70                    |         493.2
EM2         |          44.88              |           8.40                    |         495.12
EM3         |          39.37              |           6.53                    |         420.14

**2. Fill in the below chart based on time measured period and LED on time measurements for EM2 and EM3 modes, replacing each TBD with measured values.  Use the [Selecting Ranges](https://www.silabs.com/documents/public/user-guides/ug343-multinode-energy-profiler.pdf) feature of the profiler to select the appropriate measurement range.  When measuring time, measure from peak current to peak current.  Your LED on time measurement should be accurate to 1ms and your period measurement should be accurate to within 10ms**

Energy Mode | Period (s) | LED On Time (ms) |
------------| -----------|-------------------
EM2         |   2.25     |        190
EM3         |   2.25     |        220


**3. ScreenShots**  

***EM0***  
Period average current    
![em0_avg_current_period](https://user-images.githubusercontent.com/89665917/133519518-18b0a086-6f54-457c-bb32-a20cb8864a07.jpg)
Average Current with LED ***off***  
![em0_avg_current_ledoff](https://user-images.githubusercontent.com/89665917/133519242-03edd9f6-cc66-4262-8297-d409010413b0.jpg)
Average Current with LED ***on***  
![em0_avg_current_ledon](https://user-images.githubusercontent.com/89665917/133519491-c463295d-dc0f-46e3-b696-7377ffcd008f.jpg) 

***EM1***  
Period average current    
![em1_avg_current_period](https://user-images.githubusercontent.com/89665917/133519585-b8306f01-f51d-4f0c-9f8f-14bba29a6140.jpg) 
Average Current with LED ***off***  
![em1_avg_current_ledoff](https://user-images.githubusercontent.com/89665917/133519539-731e66c6-f124-48ac-8ab1-7146632dd693.jpg) 
Average Current with LED ***on***  
![em1_avg_current_ledon](https://user-images.githubusercontent.com/89665917/133519564-4ce0119e-8033-453e-93ae-c2f6dcbe78bc.jpg)

***EM2***  
Period average current  
![em2_avg_current_period](https://user-images.githubusercontent.com/89665917/133519666-23af8a28-8586-48e5-98e4-c44f1581d877.JPG) 
Average Current with LED ***off***  
![em2_avg_current_ledoff](https://user-images.githubusercontent.com/89665917/133519612-5fab08a0-9d2a-45c3-8b8d-0e9f3c51ed1f.jpg)  
Average Current with LED ***on***  
![em2_avg_current_ledon](https://user-images.githubusercontent.com/89665917/133519645-c88d4fe9-5253-403b-a725-cb1cb879b87e.JPG)
LED measurement - Period   
![em2_led_period](https://user-images.githubusercontent.com/89665917/133519732-52d56dcb-e89b-4e32-ab87-b7c01533b8a8.JPG)
LED measurement - LED on time   
![em2_led_ledOnTime](https://user-images.githubusercontent.com/89665917/133519690-715d6971-14e3-47af-84af-a4abbb89c094.JPG)

***EM3***  
Period average current    
![em3_avg_current_period](https://user-images.githubusercontent.com/89665917/133519836-51cfdc36-eb53-4430-a2f6-ed69f0419eef.JPG)  
Average Current with LED ***off***  
![em3_avg_current_ledoff](https://user-images.githubusercontent.com/89665917/133519758-dd057098-297f-4dc4-afc1-6975851bdd44.jpg)
Average Current with LED ***on***  
![em3_avg_current_ledon](https://user-images.githubusercontent.com/89665917/133519805-cfe0ae47-a17b-4391-91a1-8f18c7cd2853.JPG) 
LED measurement - Period 
![em3_led_period](https://user-images.githubusercontent.com/89665917/133519882-42419b16-6461-4bdc-a962-45be4cbbde0a.JPG)
LED measurement - LED on time   
![em3_led_ledOnTime](https://user-images.githubusercontent.com/89665917/133519863-43ec8c89-3612-4291-84a1-1c4ba9cd1a22.JPG)

[em0_avg_current_period]: screenshots/em0_avg_current_period.jpg "em0_avg_current_period"
[em0_avg_current_ledoff]: screenshots/em0_avg_current_ledoff.jpg "em0_avg_current_ledoff"
[em0_avg_current_ledon]:  screenshots/em0_avg_current_ledon.jpg "em0_avg_current_ledon"

[em1_avg_current_period]: screenshots/em1_avg_current_period.jpg "em1_avg_current_period"
[em1_avg_current_ledoff]: screenshots/em1_avg_current_ledoff.jpg "em1_avg_current_ledoff"
[em1_avg_current_ledon]: screenshots/em1_avg_current_ledon "em1_avg_current_ledon"

[em2_avg_current_period]: screenshots/em2_avg_current_period "em2_avg_current_period"
[em2_avg_current_ledoff]: screenshots/em2_avg_current_ledoff "em2_avg_current_ledoff"
[em2_avg_current_ledon]: screenshots/em2_avg_current_ledon "em2_avg_current_ledon"
[em2_led_period]: screenshots/em2_led_period "em2_led_period"
[em2_led_ledOnTime]: screenshots/em2_led_ledOnTime "em2_led_ledOnTime"

[em3_avg_current_period]: screenshots/em3_avg_current_period "em3_avg_current_period"
[em3_avg_current_ledoff]: screenshots/em3_avg_current_ledoff "em3_avg_current_ledoff"
[em3_avg_current_ledon]: screenshots/em3_avg_current_ledon "em3_avg_current_ledon"
[em3_led_period]: screenshots/em3_led_period "em3_led_period"
[em3_led_ledOnTime]: screenshots/em3_led_ledOnTime "em3_led_ledOnTime"
