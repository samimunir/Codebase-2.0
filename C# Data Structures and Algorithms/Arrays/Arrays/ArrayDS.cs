public class ArrayDS {

    private int[] main_array;
    private int capacity = 0;
    private int pointer = -1;
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

    public void PrintDS() {
        if (main_array == null) {
            Console.WriteLine("main_array[]: []");
            Console.WriteLine("\tpointer: " + pointer);
        } else {
            Console.Write("main_array[]: [");
            main_array.ToList().ForEach(i => Console.Write(" " + i.ToString()));
            Console.Write(" ]\n");
            Console.WriteLine("\tpointer: " + pointer);
        }
    }
}