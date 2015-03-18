using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MacroProcIDE_MUI
{
    class asmSyntaxProvider
    {
        static List<string> register = new List<string>();
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

            string[] registersStrs = {
            "r0",
            "r1",
            "r2",
            "r3",
            "r4",
            "r5",
            "r6",
            "r7",
            "r8",
            "r9",
            "r10",
            "r11",
            "r12",
            "r13",
            "r14",
            "r15",
            "r16",
            "r17",
            "r18",
            "r19",
            "r20",
            "r21",
            "r22",
            "r23",
            "r24",
            "r25",
            "r26",
            "r27",
            "r28",
            "r29",
            "r30",
            "r31",
            "r32",
            "index0",
            "index1",
            "index2",
            "index3",
            "index4",
            "inj1",
            "inj2",
            "inj3",
            "inj4",
            "acc",
            "[index]",
            "equ"
            };
            register = new List<string>(registersStrs);


            char[] chrs = {
                '.',
                ')',
                '(',
                '>',
                '<',
                ':',
                ';',
                ',',
                '\r',
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
        public static bool IsKnownRegister(string tag)
        {
            return register.Exists(delegate(string s) { return s.ToLower().Equals(tag.ToLower()); });
        }
        
        public static List<string> GetJSProvider(string tag)
        {
            return tags.FindAll(delegate(string s) { return s.ToLower().StartsWith(tag.ToLower()); });
        }
    }
}
