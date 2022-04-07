# Instructions to run the code
- Make sure the files `libarayManagementSystem.cpp`, `user.csv` and `books.csv` are in the same directory.
The `.csv` files may/may not be empty but make sure there is one.
- To run the code, make sure you are in the same directory as the files on the terminal and give the command :
```
g++ libraryManagementSystem.cpp -o libraryManagementSystem
.\libraryMangementSystem
```

- You can see the login details of various people in the `user.csv` files to login to the system. Details in `user.csv` file are stored in the format: `Name,userid,password,usertype,fine`.
Where `usertype=1` for Student, `usertype=2` for Professor and `usertype=3` for Librarian. (There is no `fine` field in the end for the Librarian).
- Alternately, you can start from scratch by entering a default librarian login detail: `username=defaultLibrarian` and `password=1234` and then proceed to add users and books of your choice from there.
- Enter the index from the menu displayed on the terminal to perform the various operations.
- To login as another user, logout from the current user and run the code again to login again.
- Data entered in a single run is written to the `.csv` files(saved), so the data is not lost when we logout. It is read back again when run the program.