#ifndef UTF_TOOLS_H
#define UTF_TOOLS_H

namespace simplexpress
{
    class char_sets
    {
        public:
            // Latin alphabet.
            static bool alpha(char);
            // Lower Latin alphabet.
            static bool alpha_lower(char);
            // Upper Latin alphabet.
            static bool alpha_upper(char);
            // Digits
            static bool digit(char);
            // Latin, Latin-Ext-A/B, Greek and Coptic, Latin-1 Supplement, IPA Extensions
            static bool alpha_ext(char);
            // (Used for pronunciations)
        protected:
        private:
    };
}

#endif // UTF_TOOLS_H
