using FirstFloor.ModernUI.Windows.Controls;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using Microsoft.Win32;
using MacroProcIDE_MUI;

namespace ModernUIApp1
{

    public partial class MainWindow : ModernWindow
    {
        public MainWindow()
        {
            InitializeComponent();
           // cmbFontFamily.ItemsSource = Fonts.SystemFontFamilies.OrderBy(f => f.Source);
          //  cmbFontSize.ItemsSource = new List<double>() { 8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72 };
        }
        


        private void rtbEditor_SelectionChanged(object sender, RoutedEventArgs e)
        {
            object temp = rtbEditor.Selection.GetPropertyValue(Inline.FontWeightProperty);
    /*        btnBold.IsChecked = (temp != DependencyProperty.UnsetValue) && (temp.Equals(FontWeights.Bold));
            temp = rtbEditor.Selection.GetPropertyValue(Inline.FontStyleProperty);
            btnItalic.IsChecked = (temp != DependencyProperty.UnsetValue) && (temp.Equals(FontStyles.Italic));
            temp = rtbEditor.Selection.GetPropertyValue(Inline.TextDecorationsProperty);
            btnUnderline.IsChecked = (temp != DependencyProperty.UnsetValue) && (temp.Equals(TextDecorations.Underline));

            temp = rtbEditor.Selection.GetPropertyValue(Inline.FontFamilyProperty);
            cmbFontFamily.SelectedItem = temp;
            temp = rtbEditor.Selection.GetPropertyValue(Inline.FontSizeProperty);
            cmbFontSize.Text = temp.ToString();*/
        }
        
        private void Open_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "Rich Text Format (*.rtf)|*.rtf|All files (*.*)|*.*";
            if (dlg.ShowDialog() == true)
            {
                FileStream fileStream = new FileStream(dlg.FileName, FileMode.Open);
                TextRange range = new TextRange(rtbEditor.Document.ContentStart, rtbEditor.Document.ContentEnd);
                range.Load(fileStream, DataFormats.Rtf);
            }
        }

        private void Save_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.Filter = "Rich Text Format (*.rtf)|*.rtf|All files (*.*)|*.*";
            if (dlg.ShowDialog() == true)
            {
                FileStream fileStream = new FileStream(dlg.FileName, FileMode.Create);
                TextRange range = new TextRange(rtbEditor.Document.ContentStart, rtbEditor.Document.ContentEnd);
                range.Save(fileStream, DataFormats.Rtf);
            }
        }
        /*
        private void cmbFontFamily_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (cmbFontFamily.SelectedItem != null)
                rtbEditor.Selection.ApplyPropertyValue(Inline.FontFamilyProperty, cmbFontFamily.SelectedItem);
        }

        private void cmbFontSize_TextChanged(object sender, TextChangedEventArgs e)
        {
            rtbEditor.Selection.ApplyPropertyValue(Inline.FontSizeProperty, cmbFontSize.Text);
        }
        */
        private void TextChangedEventHandler(object sender, TextChangedEventArgs e)
        {
            if (rtbEditor.Document == null)
                return;

            TextRange documentRange = new TextRange(rtbEditor.Document.ContentStart, rtbEditor.Document.ContentEnd);
            documentRange.ClearAllProperties();

            TextPointer navigator = rtbEditor.Document.ContentStart;
            while (navigator.CompareTo(rtbEditor.Document.ContentEnd) < 0)
            {
                TextPointerContext context = navigator.GetPointerContext(LogicalDirection.Backward);
                if (context == TextPointerContext.ElementStart && navigator.Parent is Run)
                {
                    CheckWordsInRun((Run)navigator.Parent);

                }
                navigator = navigator.GetNextContextPosition(LogicalDirection.Forward);
            }

            Format();
            FormatNumbers();
        }
        new struct Tag
        {
            public TextPointer StartPosition;
            public TextPointer EndPosition;
            public string Word;
            
        }
        List<Tag> m_tags = new List<Tag>();
        List<Tag> m_numbers = new List<Tag>();

        void FormatNumbers()
        {

            rtbEditor.TextChanged -= this.TextChangedEventHandler;

            for (int i = 0; i < m_numbers.Count; i++)
            {
                TextRange range = new TextRange(m_numbers[i].StartPosition, m_numbers[i].EndPosition);
                range.ApplyPropertyValue(TextElement.ForegroundProperty, new SolidColorBrush(Color.FromRgb(86, 156, 0)));
                //range.ApplyPropertyValue(TextElement.FontWeightProperty, FontWeights.Bold);
            }
            m_numbers.Clear();

            rtbEditor.TextChanged += this.TextChangedEventHandler;
        }


        void Format()
        {
            rtbEditor.TextChanged -= this.TextChangedEventHandler;

            for(int i=0;i<m_tags.Count;i++)
            {
                TextRange range = new TextRange(m_tags[i].StartPosition, m_tags[i].EndPosition);
                range.ApplyPropertyValue(TextElement.ForegroundProperty, new SolidColorBrush(Color.FromRgb(86,156,214)));
                //range.ApplyPropertyValue(TextElement.FontWeightProperty, FontWeights.Bold);
            }
            m_tags.Clear();

            rtbEditor.TextChanged += this.TextChangedEventHandler;
        }

        void CheckWordsInRun(Run run)
        {
            string text = run.Text;

            int sIndex = 0;
            int eIndex = 0;
            for (int i = 0; i < text.Length; i++)
            {
                if(Char.IsDigit(text[i]))
                {
                    eIndex = i - 1;
                    string word = text.Substring(sIndex, eIndex - sIndex + 1);
                    Tag t = new Tag();
                    t.StartPosition = run.ContentStart.GetPositionAtOffset(i, LogicalDirection.Forward);
                    t.EndPosition = run.ContentStart.GetPositionAtOffset(i+1, LogicalDirection.Backward);
                    t.Word = word;
                    m_numbers.Add(t);
                }

                if (Char.IsWhiteSpace(text[i]) | asmSyntaxProvider.GetSpecials.Contains(text[i]))
                {
                    if (i > 0 && !(Char.IsWhiteSpace(text[i - 1]) | asmSyntaxProvider.GetSpecials.Contains(text[i - 1])))
                    {
                        eIndex = i - 1;
                        string word = text.Substring(sIndex, eIndex - sIndex + 1);

                        if (asmSyntaxProvider.IsKnownTag(word))
                        {
                            Tag t = new Tag();
                            t.StartPosition = run.ContentStart.GetPositionAtOffset(sIndex, LogicalDirection.Forward);
                            t.EndPosition = run.ContentStart.GetPositionAtOffset(eIndex + 1, LogicalDirection.Backward);
                            t.Word = word;
                            m_tags.Add(t);
                        }
                    }
                    sIndex = i + 1;
                }
            }

            string lastWord = text.Substring(sIndex, text.Length - sIndex);
            if (asmSyntaxProvider.IsKnownTag(lastWord))
            {
                Tag t = new Tag();
                t.StartPosition = run.ContentStart.GetPositionAtOffset(sIndex, LogicalDirection.Forward);
                t.EndPosition = run.ContentStart.GetPositionAtOffset(eIndex + 1, LogicalDirection.Backward);
                t.Word = lastWord;
                m_tags.Add(t);
            }
        }
    }
}
