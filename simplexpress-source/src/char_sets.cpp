#include "simplexpress/char_sets.hpp"

const int char_sets::arr_greek_lower[GREEK_LOWER_CNT] =
    {0x0371, 0x0373, 0x0377, 0x037B, 0x037C, 0x037D,
     0x0390, 0x03AC, 0x03AD, 0x03AE, 0x03AF, 0x03B0,
     0x03B1, 0x03B2, 0x03B3, 0x03B4, 0x03B5, 0x03B6,
     0x03B7, 0x03B8, 0x03B9, 0x03BA, 0x03BB, 0x03BC,
     0x03BD, 0x03BE, 0x03BF, 0x03C0, 0x03C1, 0x03C2,
     0x03C3, 0x03C4, 0x03C5, 0x03C6, 0x03C7, 0x03C8,
     0x03C9, 0x03CA, 0x03CB, 0x03CC, 0x03CD, 0x03CE,
     0x03D9, 0x03DB, 0x03DD, 0x03DF, 0x03E1, 0x03E3,
     0x03E5, 0x03E7, 0x03E9, 0x03EB, 0x03ED, 0x03EF};

const int char_sets::arr_greek_upper[GREEK_UPPER_CNT] =
    {0x0370, 0x0372, 0x0376, 0x037F, 0x0386, 0x0388,
     0x0389, 0x038A, 0x038C, 0x038E, 0x038F, 0x0391,
     0x0392, 0x0393, 0x0394, 0x0395, 0x0396, 0x0397,
     0x0398, 0x0399, 0x039A, 0x039B, 0x039C, 0x039D,
     0x039E, 0x039F, 0x03A0, 0x03A1, 0x03A2, 0x03A3,
     0x03A4, 0x03A5, 0x03A6, 0x03A7, 0x03A8, 0x03A9,
     0x03AA, 0x03AB, 0x03CF, 0x03D8, 0x03DA, 0x03DC,
     0x03DE, 0x03E0, 0x03E2, 0x03E4, 0x03E6, 0x03E8,
     0x03EA, 0x03EC, 0x03EE, 0x03F7, 0x03F9, 0x03FA,
     0x03FD, 0x03FE, 0x03FF};

const int char_sets::arr_ipa_various[IPA_VARIOUS_CNT] =
    {0x0020, 0x0028, 0x0029, 0x002F, 0x003C, 0x003D,
     0x005F, 0x007B, 0x007C, 0x007D, 0x00E6, 0x00F0,
     0x00F8, 0x0127, 0x014B, 0x0153, 0x01C0, 0x01C1,
     0x01C2, 0x01C3, 0x0221, 0x0234, 0x0235, 0x0236,
     0x03B2, 0x03B8, 0x03C7, 0x0593, 0x0594, 0x0595,
     0x0599, 0x0600};

const int char_sets::arr_latin_ext_lower[LATIN_EXT_LOWER_CNT] =
    {0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7,
     0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF,
     0x00F0, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00F8,
     0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x00FE, 0x00FF, 0x0101,
     0x0103, 0x0105, 0x0107, 0x0109, 0x010B, 0x010D, 0x010F, 0x0111,
     0x0113, 0x0115, 0x0117, 0x0119, 0x011B, 0x011D, 0x011F, 0x0121,
     0x0123, 0x0125, 0x0127, 0x0129, 0x012B, 0x012D, 0x012F, 0x0131,
     0x0133, 0x0135, 0x0137, 0x0138, 0x013A, 0x013C, 0x013E, 0x0140,
     0x0142, 0x0144, 0x0146, 0x0148, 0x0149, 0x014B, 0x014D, 0x014F,
     0x0151, 0x0153, 0x0155, 0x0157, 0x0159, 0x015B, 0x015D, 0x015F,
     0x0161, 0x0163, 0x0165, 0x0167, 0x0169, 0x016B, 0x016D, 0x016F,
     0x0171, 0x0173, 0x0175, 0x0177, 0x017A, 0x017C, 0x017E, 0x017F,
     0x0180, 0x0183, 0x0185, 0x0188, 0x018C, 0x018D, 0x0192, 0x0195,
     0x0199, 0x019A, 0x019B, 0x019E, 0x01A1, 0x01A3, 0x01A5, 0x01A8,
     0x01AB, 0x01AD, 0x01B0, 0x01B4, 0x01B6, 0x01B9, 0x01BA, 0x01BD,
     0x01C6, 0x01C9, 0x01CC, 0x01CE, 0x01D0, 0x01D2, 0x01D4, 0x01D6,
     0x01D8, 0x01DA, 0x01DC, 0x01DD, 0x01DF, 0x01E1, 0x01E3, 0x01E5,
     0x01E7, 0x01E9, 0x01EB, 0x01ED, 0x01EF, 0x01F3, 0x01F5, 0x01F7,
     0x01F9, 0x01FB, 0x01FD, 0x01FF, 0x0201, 0x0203, 0x0205, 0x0207,
     0x0209, 0x020B, 0x020D, 0x020F, 0x0211, 0x0213, 0x0215, 0x0217,
     0x0219, 0x021B, 0x021D, 0x021F, 0x0221, 0x0223, 0x0225, 0x0227,
     0x0229, 0x022B, 0x022D, 0x022F, 0x0231, 0x0233, 0x0234, 0x0235,
     0x0236, 0x0237, 0x0238, 0x0239, 0x023C, 0x023F, 0x0240, 0x0242,
     0x0247, 0x0249, 0x024B, 0x024D, 0x024F};

const int char_sets::arr_whitespace[WHITESPACE_CNT] =
    {0x0009, 0x0020, 0x00A0, 0x1680, 0x2000, 0x2001, 0x2002, 0x2003,
     0x2004, 0x2005, 0x2006, 0x2007, 0x2008, 0x2009, 0x200A, 0x202F,
     0x205F, 0x3000, 0x180E, 0x200B, 0x200C, 0x200D, 0x2060, 0xFEFF
    };

const int char_sets::arr_whitespace_brk[WHITESPACE_BRK_CNT] =
    {0x000A, 0x000B, 0x000C, 0x000D, 0x0085, 0x2028, 0x2029
    };

/*0x2800 is the BRAILLE PATTERN BLANK, included for completeness.
The Unicode standard does say, however, that this does not act
as a space.*/
const int char_sets::arr_whitespace_symb[WHITESPACE_SYMB_CNT] =
    {0x00B7, 0x237D, 0x2420, 0x2422, 0x2423, 0x2800
    };

//NOTE: The wide character 0x1D4B3 is not supported in practice.
const int char_sets::arr_special_duodecimal[SPECIAL_DUODECIMAL_CNT] =
    {0x0041, 0x0042, 0x0045, 0x0054, 0x0058, 0x2130, 0x218A, 0x218B, 0x1D4B3
    };

bool char_sets::alpha(onechar ch)
{
    return latin(ch);
}

int char_sets::char_bin_search(const int arr[], const int n, int value)
{
    int first = 0,
        last = n - 1,
        position = -1;
    bool found = false;
    while(!found && first <= last)
    {
        int middle = (first + last) / 2;
        if(arr[middle] == value)
        {
            found = true;
            position = middle;
        }
        else if(arr[middle] > value)
        {
            last = middle - 1;
        }
        else
        {
            first = middle + 1;
        }
    }
    return position;
}

bool char_sets::digit(onechar ch, int radix)
{
    //If the radix is 1-10...
    if(radix > 1 && radix <= 10)
    {
        /*Allow the digits from 0 to 9 (less the difference between
        10 and radix).*/
        return ch >= u8"\u0030" && ch <= (u8"\u0039"-(10-radix));
    }
    else if(radix == 12)
    {
        //Allow all 0-9 digits.
        if(ch >= u8"\u0030" && ch <= u8"\u0039")
        {
            return true;
        }
        else
        {
            /*Duodecimal can use A, B, E, T, X, or any of four Unicode characters
            beyond digits. Perform binary search on this array of Unicode
            character code points.*/
            char upper_ch = toupper(*ch.c_str());
            return char_bin_search(arr_special_duodecimal,
                SPECIAL_DUODECIMAL_CNT, upper_ch) > -1;
        }
    }
    else if(radix > 10 && radix <= 35)
    {
        //Allow all 0-9 digits.
        if(ch >= u8"\u0030" && ch <= u8"\u0039")
        {
            return true;
        }
        else
        {
            //If no match, check for a letter.
            //Convert character to uppercase...
            //FIXME: Not Unicode compatible
            ch = toupper(*ch.c_str());
            /*Allow for Latin letters sequentially for all unassigned numbers.
            That is, use A- some letter. That end letter is Z minus an offset
            calculated from 26 minus the difference between radix and 10.*/
            return ch >= u8"\u0041" && ch <= (u8"\u005A" - (26-(radix-10)));
        }
    }
    else
    {
        //TODO: Throw an error.
        std::cerr << "Invalid radix " << radix << "! Must be 1-35."
                  << std::endl;
    }
    return false;
}

bool char_sets::greek(onechar ch)
{
    return ch >= u8"\u0370" && ch <= u8"\u03FF";
}

bool char_sets::greek_lower(onechar ch)
{
    bool r = false;
    // FIXME: T1278
    if(greek(ch))
    {
        r = char_bin_search(arr_greek_lower, GREEK_LOWER_CNT, *ch.c_str()) > -1;
    }
    return r;
}

bool char_sets::greek_upper(onechar ch)
{
    bool r = false;
    // FIXME: T1278
    if(greek(ch))
    {
        r = char_bin_search(arr_greek_upper, GREEK_UPPER_CNT, *ch.c_str()) > -1;
    }
    return r;
}

bool char_sets::latin(onechar ch)
{
    //We will simply leverage latin_lower() and latin_upper() for this.
    return latin_lower(ch) || latin_upper(ch);
}

bool char_sets::latin_ext(onechar ch, bool includeStd)
{
    return (ch >= u8"\u00C0" && ch <= u8"\u024F") || (includeStd && latin(ch));
}

bool char_sets::latin_ext_letter(onechar ch, bool includeStd)
{
    // FIXME: Temporarily ignore unused parameter.
    (void)includeStd;
    //If in latin_ext range and not one of the two non-letter characters...
    return latin_ext(ch) && ch != u8"\u00D7" && ch != u8"\u00F7";
}

bool char_sets::latin_ext_lower(onechar ch, bool includeStd)
{
    bool r = latin_lower(ch) && includeStd;
    /*If that first test fails, make sure the character is ext_latin...*/
    if(!r && latin_ext_letter(ch, false))
    {
        //Binary search the lowercase Latin extended letters.
        r = char_bin_search(arr_latin_ext_lower, LATIN_EXT_LOWER_CNT, *ch.c_str()) > -1;
    }
    return r;
}

bool char_sets::latin_ext_upper(onechar ch, bool includeStd)
{
    //First, see if it is a standard Latin uppercase letter.
    bool r = latin_upper(ch) && includeStd;
    /*If that first test fails, make sure the character is ext_latin...*/
    if(!r && latin_ext_letter(ch, false))
    {
        //It is now safe to assume, if it isn't lower, it is upper!
        r = latin_ext_lower(ch) == false;
    }
    return r;
}

bool char_sets::latin_lower(onechar ch)
{
    return ch >= u8"\u0061" && ch <= u8"\u007A";
}

bool char_sets::latin_upper(onechar ch)
{
    return ch >= u8"\u0041" && ch <= u8"\u005A";
}

bool char_sets::ipa(onechar ch)
{
    bool r = false;
    //Check for lowercase Latin letter (u8"\u0061"-u8"\u007A").
    if (latin_lower(ch))
    {
        r = true;
    }
    /*Check for IPA Extensions block (u8"\u0250"-u8"\u02AF"),
    Spacing Modifier Letters block (u8"\u02B0"-u8"\u02FF"),
    or Combining Diacritical Marks block (u8"\u0300"-u8"\u036F").*/
    else if (ch >= u8"\u0250" && ch <= u8"\u0300")
    {
        r = true;
    }
    /*Check for Phonetic Extensions block (u8"\u1D00"-u8"\u1D7F"),
    or Phonetic Extensions Supplement block (u8"\u1D80"-u8"\u1DBF")*/
    else if (ch >= u8"\u0D00" && ch <= u8"\u0DBF")
    {
        r = true;
    }
    //Check for Superscripts and Subscripts block (u8"\u2070"-u8"\u209F")
    else if (ch >= u8"\u2070" && ch <= u8"\u209F")
    {
        r = true;
    }
    //Check for Modifier Tone Letters block (u8"\uA700"-u8"\uA71F")
    else if (ch >= u8"\uA700" && ch <= u8"\uA71F")
    {
        r = true;
    }
    //Check if it is one of the other various characters in IPA.
    // FIXME: T1278
    else if (char_bin_search(arr_ipa_various, IPA_VARIOUS_CNT, *ch.c_str()) > -1)
    {
        r = true;
    }
    return r;
}

bool char_sets::whitespace(onechar ch, bool includeVisible)
{
    //If we match the standard space, save algorithm time and return true.
    if(ch == ' ')
    {
        return true;
    }
    //If the character is other non-breaking whitespace...
    if (char_bin_search(arr_whitespace, WHITESPACE_CNT, *ch.c_str()) > -1)
    {
        return true;
    }
    //If the character is other breaking whitespace...
    if (char_bin_search(arr_whitespace_brk, WHITESPACE_BRK_CNT, *ch.c_str()) > -1)
    {
        return true;
    }
    //Otherwise, if we've flagged to include visible...
    else if(includeVisible)
    {
        //Return if the character is a visible whitespace symbol.
        return char_bin_search(arr_whitespace_symb, WHITESPACE_SYMB_CNT, *ch.c_str()) > -1;
    }
    //If we get this far, return false.
    return false;
}