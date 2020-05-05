
public class Lab5_9 {
    public static void main(String[] args) {
        Commodity com1 = new Commodity(123.4, 10);
        Commodity com2 = new Commodity(14.5, 2);
        
        Shop shop1 = new Shop("    d abc    adef    aaa dad ddd  ddd", com1, com2, 15);
        
        String s1 = "abcd";
        String s2 = "abcd";
        
        
        String str = shop1.Get_Name();
        String res_str = "";        
        
        
        boolean end_of_str = false;
        while (!end_of_str) {
            String word = "";
            int k = str.indexOf(' ');
            while (k == 0) {
                str = str.substring(1);
                k = str.indexOf(' ');
            }
            
            if (k > 0) {
                word = str.substring(0, k);
                str = str.substring(k + 1);
            } else {    //Найдено последнее слово в строке
                end_of_str = true;
                word = str;
            }            
            if (!word.isEmpty() && word.charAt(0) == 'd')
                res_str = res_str.concat(word + " ");
        }
        
        shop1.Set_Name(res_str);
        shop1.Display();
        //System.out.println(res_str);
    }
}
