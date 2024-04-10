/*
    Sami Munir
    April 3rd, 2024
    C# Data Structures & Algorithms
    Learning arrays in C#
    - Arrays
        > Program.cs
*/

public class Program {
    public static void Main() {
        Console.WriteLine("Array Data Structure C#");

        ArrayDS main_array = new ArrayDS();

        /*
            Testing function InsertFirst()
        */
        main_array.InsertFirst(2);
        main_array.InsertFirst(7);
        main_array.InsertFirst(0);
        main_array.InsertFirst(156);

        // main_array.RemoveFirst();
        // main_array.RemoveFirst();
        // main_array.RemoveFirst();
    }
}