using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MacroProcIDE_MUI
{
    class asmSyntaxProvider
    {
        static List<string> tags = new List<string>();
        static List<char> specials = new List<char>();
        #region ctor
        static asmSyntaxProvider()
        {
            string[] strs = {
            "mov",
            "movd",
            "movg",
            "inc",
            "dec",
            "cinc",
            "cdec",
            "cxor",
            "cmp",
            "jnz",
            "jmp",
            "rnd"
            };
            tags = new List<string>(strs);

            char[] chrs = {
                '.',
                ')',
                '(',
                '[',
                ']',
                '>',
                '<',
                ':',
                ';',
                '\n',
                '\t'
            };
            specials = new List<char>(chrs);
        }
        #endregion
        public static List<char> GetSpecials
        {
            get { return specials; }
        }
        public static List<string> GetTags
        {
            get { return tags; }
        }
        public static bool IsKnownTag(string tag)
        {
            return tags.Exists(delegate(string s) { return s.ToLower().Equals(tag.ToLower()); });
        }
        public static List<string> GetJSProvider(string tag)
        {
            return tags.FindAll(delegate(string s) { return s.ToLower().StartsWith(tag.ToLower()); });
        }
    }
}
