public class ArrayDS {

    private int[] main_array;
    private int capacity = 0;
    private int pointer = -1;
    private int number_of_elements = 0;
    public ArrayDS() {
        capacity = 5;
        main_array = new int[capacity];
        Console.WriteLine("\nSuccessfully initialized main_array[] to capacity [" + capacity + "].");
        PrintDS();
    }

    public ArrayDS(int capacity) {
        this.capacity = capacity;
        main_array = new int[capacity];
        Console.WriteLine("\nSuccessfully initialized main_array[] to capacity [" + capacity + "].");
        PrintDS();
    }

    private bool IsDefault() {
        bool flag = true;
        for (int i = 0; i < main_array.Length; i++) {
            if (main_array[i] == 0) {
                flag = true;
            } else {
                flag = false;
            }
        }
        return flag;
    }

    private bool IsEmpty() {
        if (main_array == null) {
            return true;
        } else {
            return false;
        }
    }

    public void PrintDS() {
        if (IsEmpty()) {
            Console.WriteLine("main_array[]: []");
        } else {
            Console.Write("main_array[]: [");
            main_array.ToList().ForEach(i => Console.Write(" " + i.ToString()));
            Console.Write(" ]\n");
        }
        Console.WriteLine("\tpointer: " + pointer);
        Console.WriteLine("\tnumber of elements: " + number_of_elements);
    }

    public void InsertFirst(int data) {
        Console.WriteLine("\nInsertFirst(" + data + ") called...");
        if (pointer == -1) {
            pointer++;
            main_array[0] = data;
        } else {
            pointer++;
            for (int i = pointer; i > 0; i--) {
                main_array[i] = main_array[i - 1];   
            }
            main_array[0] = data;
        }
        number_of_elements++;
        PrintDS();
    }
}