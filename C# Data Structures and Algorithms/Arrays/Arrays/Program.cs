/*
    Sami Munir
    April 3rd, 2024
    C# Data Structures & Algorithms
    Learning arrays in C#
    - Arrays
        > Program.cs
*/

Console.WriteLine("Arrays in C#!");

/*
    int array for main program.
*/
int[] main_array = new int[6];
int pointer = -1;

for (int i = 0; i < main_array.Length; i++) {
    pointer++;
    main_array[i] = (i + 1);
}

// Console.WriteLine("main_array[]: " + main_array + "\n\tpointer: " + pointer);
Console.Write("main_array[]: [");
main_array.ToList().ForEach(i => Console.Write(" " + i.ToString()));
Console.WriteLine(" ]\n\tpointer: " + pointer);