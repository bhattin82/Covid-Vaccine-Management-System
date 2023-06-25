# Covid-Vaccine-Management-System

In this project, I made a COVID vaccine management system. I created files that store the personal information (hypothetical data) of individuals (Name, Age, Gender, Phone Number, Id Number, Vaccine status). The data from the files is stored into a linked list where each node represents the data of a person. The system requires a login to access the information, and it provides three attempts. When the attempts limit is exceeded, the user has to wait for some time before another login attempt. If successful, the user is provided with some options. The user enters their preferred choice through a command line interface, and the relevant linked list operation is performed. The following are the operations: 1. Current Database, 2. Add Record, 3. Update Record, 4. Search Record, 5. Prioritize individuals, 6. Delete Record, 7. Logout.

For example, let us say the user's name is Mr Z. He selects option 4 (search record). He is further asked if he wants to search by name, gender or vaccine status. Mr Z. wants to search by the vaccination received (Pfizer or Johnson and Johnson). In this case, Mr Z. is interested to know the names of the individuals that got the Pfizer vaccine, and he writes the vaccine name in the command line interface. Mr Z should get the output in the following format:

|Name | Age | Gender  | Phone Number |  ID Number |  Vaccination |
|:---:|:---:|:-------:|:------------:|:----------:|:----------------:|
| A   | XX  |   M     |  XXXXXXXXXX  | XXXXXXXXXX |     Pfizer       |
| B   | XX  |   M     |  XXXXXXXXXX  | XXXXXXXXXX |     Pfizer       |
| C   | XX  |   F     |  XXXXXXXXXX  | XXXXXXXXXX |     Pfizer       |
| D   | XX  |   M     |  XXXXXXXXXX  | XXXXXXXXXX |     Pfizer       |


Notice that the vaccination column is for all those who received Pfizer. This output is just for the explanation. X can be any integer between 0 and 9 inclusive. 

Let us consider another example. Now, Mr Z. wants to inquire about the individuals that are not vaccinated yet, and he wants the system to generate a list of all individuals with their priority level in receiving the vaccine. This is done by taking into consideration the age of those individuals. A sorting algorithm (bubble sort) is used. Mr Z. selects option 5 (Prioritize Individuals). He should get the output in the following format:

|Name| Age | Gender| Phone Number |  ID Number  |Vaccination |
|:--:|:-------:|:-----:|:------------:|:-----------:|:--------------:|
| M  |   94    |  M    |  XXXXXXXXXX  |  XXXXXXXXXX |    None        |
| J  |   77    |  M    |  XXXXXXXXXX  |  XXXXXXXXXX |    None        |
| K  |   68    |  F    |  XXXXXXXXXX  |  XXXXXXXXXX |    None        |
| C  |   57    |  M    |  XXXXXXXXXX  |  XXXXXXXXXX |    None        |
| R  |   51    |  F    |  XXXXXXXXXX  |  XXXXXXXXXX |    None        |
| T  |   40    |  F    |  XXXXXXXXXX  |  XXXXXXXXXX |    None        |
| N  |   33    |  M    |  XXXXXXXXXX  |  XXXXXXXXXX |    None        |


Notice that the vaccination column is for all those who did not receive any vaccine yet. Also, it can be observed that the oldest person has the highest priority and likewise. Again, this output is just for the explanation. X can be any integer between 0 and 9 inclusive. 

**Why I chose bubble sort?**

Since my file size was extremely small (Lines <= 20), I preferred using bubble sort. Also, it is simple and easy to implement. However, if my file size was extremely big (Lines>=5000), then bubble sort was amongst the worst sorting algorithms to implement on an unsorted list. In that case, it has a worst case time complexity of O(n^2). However, if the list is already sorted, bubble sort has a best case time complexity of Ω(n). If I had an extremely large file, I would have either used merge sort, heap sort or quick sort. If I had to pick one, I would have implemented heap sort. I say so because quick sort does not perform well when the list is already sorted. Quick sort has a worst case time complexity of O(n^2). Merge sort performs fairly well in both cases. It has a worst, average, best case time complexity of O(nlog(n)), θ(nlog(n)) and Ω(nlog(n)) respectively. Heap sort has the same time complexity, but it has a better space complexity than merge sort. Merge sort has a space complexity of O(n) while heap sort has a space complexity of O(1).


All the changes done by the user are updated in the relevant file.

This program is compiled with the following commands:
1) gcc vaccine.c -o vaccine
2) ./vaccine community_vaccine.txt priority.txt

This program performs memory management. It does not leak any memory. This can be tested with the following command: 
valgrind --leak-check=yes ./vaccine community_vaccine.txt priority.txt

Lastly, this project was worked on a secure shell (ssh). I used vim on my terminal. 
