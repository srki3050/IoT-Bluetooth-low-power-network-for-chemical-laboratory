Please include your answers to the questions below with your submission, entering into the space below each question
See [Mastering Markdown](https://guides.github.com/features/mastering-markdown/) for github markdown formatting if desired.

**1. How much current does the system draw (instantaneous measurement) when a single LED is on with the GPIO pin set to StrongAlternateStrong?**
   Answer:  **5.36mA** of current is drawn by the system when a single LED (**LED 0**) is on with the GPIO pin set to StrongAlternateStrong.


**2. How much current does the system draw (instantaneous measurement) when a single LED is on with the GPIO pin set to WeakAlternateWeak?**
   Answer: **5.34mA** of current is drawn by the system when a single LED (**LED 0**) is on with the GPIO pin set to WeakAlternateWeak.


**3. Is there a meaningful difference in current between the answers for question 1 and 2? Please explain your answer, 
referencing the [Mainboard Schematic](https://www.silabs.com/documents/public/schematic-files/WSTK-Main-BRD4001A-A01-schematic.pdf) and [AEM Accuracy](https://www.silabs.com/documents/login/user-guides/ug279-brd4104a-user-guide.pdf) section of the user's guide where appropriate. Extra credit is avilable for this question and depends on your answer.**
   Answer: 
1. Since AEM is accurate upto 0.1 mA for values above 250 uA [link to reference,](https://www.silabs.com/documents/public/user-guides/ug279-brd4104a-user-guide.pdf) there is a considerable difference between recorded values.
2. The setting of Drive Strength as Strong and Weak applies to the whole port but not the pins specifically unless the pin has been configured seperately with *gpioModePushPull* as true. [Reference link: ](https://siliconlabs.force.com/community/s/article/relationship-between-gpio-drive-strength-and-pin-configurations?language=en_US)
3. Hence, I am not able to see a meaningful difference between both the values as input current will be same.
4. If *gpioModePushPull* is true, 
a. for Question 1, **5.41mA** current is drawn.
b. for Question 2, **5.33mA** current is drawn. 

**4. With the WeakAlternateWeak drive strength setting, what is the average current for 1 complete on-off cycle for 1 LED with an on-off duty cycle of 50% (approximately 1 sec on, 1 sec off)?**
   Answer: With the WeakAlternateWeak drive strength setting, Average current of **5.02mA** is drawn for 1 complete on-off cycle for 1 LED with an on-off duty cycle of 50%.	


**5. With the WeakAlternateWeak drive strength setting, what is the average current for 1 complete on-off cycle for 2 LEDs (both on at the time same and both off at the same time) with an on-off duty cycle of 50% (approximately 1 sec on, 1 sec off)?**
   Answer: With the WeakAlternateWeak drive strength setting, Average current of **5.19mA** is drawn for 1 complete on-off cycle for 2 LEDs (both on at the time same and both off at the same time) with an on-off duty cycle of 50%.


