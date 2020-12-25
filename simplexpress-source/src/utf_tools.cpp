// FIXME: T1278
//#include "simplexpress/utf_tools.hpp"
//
// int utf_utils::ch_to_int(onechar ch)
//{
//    //48 [0] - 57 [9]
//    // FIXME: line 138 again, but may be okay?
//    int i = static_cast<int>(*ch.c_str()) - 48;
//    if(i < 0 || i > 9)
//    {
//        throw std::out_of_range("The character could not be converted.");
//    }
//    return i;
//}
//
// int utf_utils::str_to_int(onestring str, bool failsafe)
//{
//    //If we start with 0x, it's hex.
//    if(str[0] == '0' && str[1] == 'x')
//    {
//        return utf_utils::str_to_hex(str, failsafe);
//    }
//    //Otherwise, proceed with interpreting in binary.
//    //Initialize our return integer.
//    int r = 0,
//    //The integerized character.
//        ci = 0,
//    //The incrementer.
//        i = 0;
//    const int AL = str.length() - 1;
//    /*ALGORITHM:
//    let ci = the integerized character
//         i = the index of the character
//        al = the length, minus 1 so the algorithm works
//       str = the initial string
//         r = the final return integer
//    for each i in str:
//        r += [10^(al-i)] * ci
//    EXAMPLE:
//    string: 957
//    al = [length] - 1 = 3 - 1 = 2
//    ci=9, i=0
//    [10^(2-0)] * 9 = [10^2] * 9 = 100 * 9 = 900
//    r = 0 + 900
//    ci=5, i=1
//    [10^(2-1)] * 5 = [10^1] * 5 = 10 * 5 = 50
//    r = 900 + 50 = 950
//    ci=7, i=2
//    [10^(2-2)] * 7 = [10^2] * 7 = 1 * 7 = 7
//    r = 950 + 7 = 957
//    */
//    //If we hit a negative sign at i=0...
//    if(str[0] == '-')
//    {
//        //Skip i=0 and invert r's sign later.
//        i = 1;
//    }
//    for(int ii = i; ii <= AL; ii++)
//    {
//        try
//        {
//            ci = ch_to_int(str[ii]);
//        }
//        catch(const std::out_of_range& oor)
//        {
//            if(failsafe)
//            {
//                return -1;
//            }
//            else
//            {
//                throw std::out_of_range("The string cannot be converted.");
//            }
//        }
//        r += pow(10, (AL-i)) * ci;
//        i = ii;
//    }
//    //If we found a negative sign at i=0 earlier...
//    if(str[0] == '-')
//    {
//        //Make r negative.
//        r *= -1;
//    }
//    return r;
//}