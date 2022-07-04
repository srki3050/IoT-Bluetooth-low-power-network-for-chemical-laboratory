Please include your answers to the questions below with your submission, entering into the space below each question
See [Mastering Markdown](https://guides.github.com/features/mastering-markdown/) for github markdown formatting if desired.

*Be sure to take measurements with logging disabled to ensure your logging logic is not impacting current/time measurements.*

*Please include screenshots of the profiler window detailing each current measurement captured.  See the file Instructions to add screenshots in assignment.docx in the ECEN 5823 Student Public Folder.* 

1. What is the average current per period?
   Answer: 4.96 uA
   <br>Screenshot:  
   ![Avg_current_per_period](screenshots/assignment4/avg_current_per_period.jpg)
   ![avg_current_per_period](https://user-images.githubusercontent.com/89665917/134851177-0b97910d-0e67-4ae4-985e-f103e25caf4b.JPG)  

2. What is the average current when the Si7021 is Powered Off?
   Answer: 4.31 uA
   <br>Screenshot:  
   ![Avg_current_LPM_Off](screenshots/assignment4/avg_current_lpm_off.jpg)
   ![avg_current_lpm_off](https://user-images.githubusercontent.com/89665917/134851173-9d274569-7413-4b8d-90a9-a2d58bfd158c.JPG)

3. What is the average current when the Si7021 is Powered On?
   Answer: 41.81 uA
   <br>Screenshot:  
   ![Avg_current_LPM_On](screenshots/assignment4/avg_current_lpm_on.jpg)
   ![Avg_current_LPM_On](https://user-images.githubusercontent.com/89665917/134851176-239efbb1-0332-4343-b65f-a14602d6ef5c.JPG)

4. How long is the Si7021 Powered On for 1 temperature reading?
   Answer: 90ms
   <br>Screenshot:  
   ![duration_lpm_on](screenshots/assignment4/avg_current_lpm_on.jpg)
   ![Avg_current_LPM_On](https://user-images.githubusercontent.com/89665917/134851176-239efbb1-0332-4343-b65f-a14602d6ef5c.JPG)

5. Compute what the total operating time of your design for assignment 4 would be in hours, assuming a 1000mAh battery power supply?
   Answer: 1000mAh/4.31uA = 232000 hrs
   
6. How has the power consumption performance of your design changed since the previous assignment?
   Answer: Considering the average current period, assignment 4 is 149.62 uA/4.96 uA is 30 times power efficient.
	   Considering the average current when power off, assignment 4 is 23.20 uA/4.31 uA is around 6 times power efficient.
	   Considering the average current period when power on, assignment 4 is 4.54 mA/41.81 uA is around 110 times power efficient.
   
7. Describe how you have tested your code to ensure you are sleeping in EM1 mode during I2C transfers.
   Answer: Compared my current consumption with that of Assignment 2 and it is in the similar range i.e. between EM0 and EM2. This helped me verify the fact that my blue gecko 13 module was sleeping in EM1 when necessary.


