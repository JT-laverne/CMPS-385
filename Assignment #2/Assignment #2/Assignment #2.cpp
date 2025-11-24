using System;

class Book
{
    private int id;
    private string title;
    private string author;
    private int year;
    private bool available;

    public Book()
    {
        id = 0;
        title = "";
        author = "";
        year = 0;
        available = true;
    }

    public Book(int id, string title, string author, int year)
    {
        this.id = id;
        this.title = title;
        this.author = author;
        this.year = year;
        available = true;
    }

    public int GetID() { return id; }
    public string GetTitle() { return title; }
    public string GetAuthor() { return author; }
    public int GetYear() { return year; }
    public bool IsAvailable() { return available; }

    public void SetTitle(string title) { this.title = title; }
    public void SetAuthor(string author) { this.author = author; }
    public void SetYear(int year) { this.year = year; }

    public void BorrowBook()
    {
        if (available)
            available = false;
    }

    public void ReturnBook()
    {
        if (!available)
            available = true;
    }

    public void Display()
    {
        Console.WriteLine($"ID: {id}");
        Console.WriteLine($"Title: {title}");
        Console.WriteLine($"Author: {author}");
        Console.WriteLine($"Year: {year}");
        Console.WriteLine($"Status: {(available ? "Available" : "Borrowed")}");
    }
}

class Program
{
    static void Main()
    {
        Book[] library = new Book[100];
        int bookCount = 0;

        while (true)
        {
            Console.Clear();
            Console.WriteLine("*************** Welcome to the Library ***************");
            Console.WriteLine("Please choose one of the following operations:");
            Console.WriteLine("1 - Add a new book");
            Console.WriteLine("2 - Borrow a book");
            Console.WriteLine("3 - Return a book");
            Console.WriteLine("4 - Display details of a book (by ID)");
            Console.WriteLine("5 - List all available books");
            Console.WriteLine("0 - Exit");
            Console.Write("Choice: ");

            string choice = Console.ReadLine();
            Console.Clear();

            switch (choice)
            {
             //Add Book
            case "1":
                Console.Write("Enter title: ");
                string title = Console.ReadLine();

                Console.Write("Enter author: ");
                string author = Console.ReadLine();

                Console.Write("Enter year: ");
                int year = int.Parse(Console.ReadLine());

                int newID = new Random().Next(10000, 99999);

                library[bookCount] = new Book(newID, title, author, year);
                bookCount++;

                Console.WriteLine("Book added successfully!");
                Console.WriteLine($"Title: {title}");
                Console.WriteLine($"ID: {newID}");
                Console.WriteLine("Press any key to return to Main Menu!");
                Console.ReadKey();
                break;

            //Borrow Book
            case "2":
                Console.Write("Enter Book ID: ");
                int borrowID = int.Parse(Console.ReadLine());

                Book foundBook = null;
                for (int i = 0; i < bookCount; i++)
                {
                    if (library[i].GetID() == borrowID)
                    {
                        foundBook = library[i];
                        break;
                    }
                }

                if (foundBook == null)
                {
                    Console.WriteLine("Book not found!");
                }
                else if (!foundBook.IsAvailable())
                {
                    Console.WriteLine("This book is already borrowed.");
                }
                else
                {
                    foundBook.BorrowBook();
                    Console.WriteLine($"You have successfully borrowed '{foundBook.GetTitle()}'.");
                }

                Console.WriteLine("Press any key to return to Main Menu!");
                Console.ReadKey();
                break;

            //Return Book
            case "3":
                Console.Write("Enter Book ID: ");
                int returnID = int.Parse(Console.ReadLine());

                Book returnBook = null;
                for (int i = 0; i < bookCount; i++)
                {
                    if (library[i].GetID() == returnID)
                    {
                        returnBook = library[i];
                        break;
                    }
                }

                if (returnBook == null)
                {
                    Console.WriteLine("Book not found!");
                }
                else if (returnBook.IsAvailable())
                {
                    Console.WriteLine("Book was not borrowed.");
                }
                else
                {
                    returnBook.ReturnBook();
                    Console.WriteLine($"You have successfully returned '{returnBook.GetTitle()}'.");
                }

                Console.WriteLine("Press any key to return to Main Menu!");
                Console.ReadKey();
                break;

			//Display Book Details
            case "4":
                Console.Write("Enter Book ID: ");
                int searchID = int.Parse(Console.ReadLine());

                Book detailBook = null;
                for (int i = 0; i < bookCount; i++)
                {
                    if (library[i].GetID() == searchID)
                    {
                        detailBook = library[i];
                        break;
                    }
                }

                if (detailBook == null)
                {
                    Console.WriteLine("Book not found.");
                }
                else
                {
                    detailBook.Display();
                }

                Console.WriteLine("Press any key to return to Main Menu!");
                Console.ReadKey();
                break;

			//List Available Books
            case "5":
                Console.WriteLine("Available Books:");

                bool anyAvailable = false;

                for (int i = 0; i < bookCount; i++)
                {
                    if (library[i].IsAvailable())
                    {
                        Console.WriteLine($"ID: {library[i].GetID()} | Title: {library[i].GetTitle()} | Author: {library[i].GetAuthor()} | Year: {library[i].GetYear()}");
                        anyAvailable = true;
                    }
                }

                if (!anyAvailable)
                    Console.WriteLine("No books available at the moment.");

                Console.WriteLine("Press any key to return to Main Menu!");
                Console.ReadKey();
                break;

			//Exit
            case "0":
                Console.WriteLine("Thank you for using the Library System! Goodbye!");
                return;

            default:
                Console.WriteLine("Invalid choice! Press any key...");
                Console.ReadKey();
                break;
            }
        }
    }
}
