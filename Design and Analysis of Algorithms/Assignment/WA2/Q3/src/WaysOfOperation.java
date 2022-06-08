import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;


public class WaysOfOperation {
    public static void main(String[] args) {
        WaysOfOperation test = new WaysOfOperation();
        System.out.println(test.TransToArrayList("8+6+7*5"));
    }
    List<String> lst = new ArrayList<>();

    public List<Integer> TransToArrayList(String str) {
        List<String> list= Stream.iterate(0, n -> ++n).limit(str.length())
                .map(n -> "" + str.charAt(n))
                .collect(Collectors.toList());
        for(int i = 0; i< list.size(); i++) {
            lst.add(list.get(i));
        }
        System.out.println(lst);
        return CalculateWays(0, lst.size()-1);
    }
    public List<Integer> CalculateWays(int left, int right){
        List<Integer> num = new ArrayList<>();
        // transform the char to the integer type
        if(left == right){
            num.add(Integer.parseInt(lst.get(left)));
            return num;
        }
        for(int i = left+1; i<right; i += 2){
            List<Integer> new_left = CalculateWays(left, i-1), new_right = CalculateWays(i+1, right);
            for(int x: new_left)
                for(int y: new_right){
                    if("-".equals(lst.get(i))) num.add(x-y);
                    else if("+".equals(lst.get(i)))
                        num.add(x+y);
                    else if("*".equals(lst.get(i)))
                        num.add(x*y);
                    else
                        System.out.println("Please enter the right operation!");
                }
        }
        return num;
    }
}