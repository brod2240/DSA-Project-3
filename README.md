# DSA Project 3 - Group 65
# What Does the Program Do?:
The program prompts the user to select an option on what they want to see in terms (niche or popular) of related artists and then enter in the name of the artist in question. The program the returns 20 artists in the category the user chose. This allows the user to be able to see similar artists in a readable display.
# How Did We Acquire the Data
The data was collected using the Spotify API in Python. In Python, given a playlist and the tracks in the playlist, we were able to extract artist information such as related artists, popularity, genres, etc. With this data, we were able to get more artists using related artists and used that information in a CSV. The CSV has three headers, "From Artist", "To Artist", and "Weight". When finding the related artist with a source artist, the source artists will be the "From" and the related artists will be the "To". In order to get the weight, an equation was used to determine how "related" the artist was and how popular they were in relation to each other. The equation used was weight = common genre number + average popularity. This way, there is a disinguisable difference between who is related and who is not and how popular they are (i.e. are they niche or not). It is important to note that most CSV files are separated by genre
# How To Use Program
There is a folder labeled CSV, that should have the CSV files that are to be used in the program. This is because the program can only handle so much data until it is very slow and not user-friendly. The user can then insert what option they want (search by artist, search artist and display popular, search artist and display niche, or exit). The user can then input the artist name and have it display the related artist and the weight associated. If the artist is not in the CSV, the display will show "artist not found". The program will run until the program ends.
# Structure Comparison
In this program, we implemented a graph and used heaps and quicksort in order to collect the data and sort to find the popular and niche related artists. We used the chrono library in order to see what the time difference was. We did not expect much of a time difference as both time complexities were O(logn). 
# Notes
CSV(complete) is a CSV file that includes 100,000 unique artists. There is a file called supplement.csv that is a randomly generated name and weight CSV file that fits the format of the CSVs we created with the Spotify API. This is because, due to Spotify API limitations, there were only so many pulls we can do before we recieved a timeout and we do not know when that timeout will be lifted. 
