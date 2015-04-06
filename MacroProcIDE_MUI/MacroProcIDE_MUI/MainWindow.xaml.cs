﻿using FirstFloor.ModernUI.Windows.Controls;
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
using System.Diagnostics;
using System.ComponentModel;

namespace ModernUIApp1
{

    public partial class MainWindow : ModernWindow
    {
        WaitingWindow mWaitingWindow;
        public MainWindow()
        {
            mswatch = new Stopwatch();
            mswatch.Start();
            InitializeComponent();
            mWaitingWindow = new WaitingWindow();
            mWaitingWindow.Hide();
           // cmbFontFamily.ItemsSource = Fonts.SystemFontFamilies.OrderBy(f => f.Source);
          //  cmbFontSize.ItemsSource = new List<double>() { 8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72 };
        }

        private void CancelEventHandler(object sender, CancelEventArgs e)
        {
            mWaitingWindow.Close();
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
            dlg.Filter = "Abwabwa File (*.asm)|*.asm|All files (*.*)|*.*";
            if (dlg.ShowDialog() == true)
            {

                mWaitingWindow.Show();
                FileStream fileStream = new FileStream(dlg.FileName, FileMode.Open);
                TextRange range = new TextRange(rtbEditor.Document.ContentStart, rtbEditor.Document.ContentEnd);
                range.Load(fileStream, DataFormats.Text);

                mWaitingWindow.Hide();
            }
        }

        private void Save_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.Filter = "Abwabwa File (*.asm)|*.asm|All files (*.*)|*.*";
            if (dlg.ShowDialog() == true)
            {
                FileStream fileStream = new FileStream(dlg.FileName, FileMode.Create);
                TextRange range = new TextRange(rtbEditor.Document.ContentStart, rtbEditor.Document.ContentEnd);
                range.Save(fileStream, DataFormats.Text);
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
        Stopwatch mswatch;
        private void TextChangedEventHandler(object sender, TextChangedEventArgs e)
        {
            if (rtbEditor.Document == null)
                return;

            printLineNumbers();

            foreach (TextChange C in e.Changes)
            {
                TextPointer P = rtbEditor.Document.ContentStart.GetPositionAtOffset(C.Offset);
                if (P.Paragraph != null) P.Paragraph.Tag = null; //It needs reformatting
            }

            if (rtbEditor.Document.Blocks.Count > 0)
            {
                Block B = rtbEditor.Document.Blocks.FirstBlock;
                while (B != null)
                {
                    if (B is Paragraph)
                    {
                        Paragraph P = B as Paragraph;
                        if (P.Tag == null)
                        {
                            TextRange documentRange = new TextRange(P.ContentStart, P.ContentEnd);
                            documentRange.ClearAllProperties();

                            TextPointer navigator = P.ContentStart;
                            while (navigator.CompareTo(P.ContentEnd) < 0)
                            {
                                TextPointerContext context = navigator.GetPointerContext(LogicalDirection.Backward);
                                if (context == TextPointerContext.ElementStart && navigator.Parent is Run)
                                {
                                    CheckWordsInRun((Run)navigator.Parent);

                                }
                                navigator = navigator.GetNextContextPosition(LogicalDirection.Forward);
                            }

                            P.Tag = true; //It has been highlighted
                        }
                     }
                    else 
                        throw new Exception("Unknown block type " + B.ToString());
                    B = B.NextBlock;
                }
            }







/*
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
            */
            Format();
        }
        new struct Tag
        {
            public TextPointer StartPosition;
            public TextPointer EndPosition;
            public string Word;
            
        }
        List<Tag> m_tags = new List<Tag>();
        List<Tag> m_numbers = new List<Tag>();
        List<Tag> m_rgisters = new List<Tag>();
        List<Tag> m_comments = new List<Tag>();
        List<Tag> m_label = new List<Tag>();
        

        void Format(Paragraph P = null)
        {
            rtbEditor.TextChanged -= this.TextChangedEventHandler;




            for (int i = 0; i < m_numbers.Count; i++)
            {
                TextRange range = new TextRange(m_numbers[i].StartPosition, m_numbers[i].EndPosition);
                range.ApplyPropertyValue(TextElement.ForegroundProperty, new SolidColorBrush(Color.FromRgb(86, 156, 0)));
                //range.ApplyPropertyValue(TextElement.FontWeightProperty, FontWeights.Bold);
            }
            m_numbers.Clear();


            for (int i = 0; i < m_label.Count; i++)
            {
                TextRange range = new TextRange(m_label[i].StartPosition, m_label[i].EndPosition);
                range.ApplyPropertyValue(TextElement.ForegroundProperty, new SolidColorBrush(Color.FromRgb(185, 16, 30)));
                //range.ApplyPropertyValue(TextElement.FontWeightProperty, FontWeights.Bold);
            }
            m_label.Clear();

            for (int i = 0; i < m_comments.Count; i++)
            {
                TextRange range = new TextRange(m_comments[i].StartPosition, m_comments[i].EndPosition);
                range.ApplyPropertyValue(TextElement.ForegroundProperty, new SolidColorBrush(Color.FromRgb(145, 145, 105)));
                //range.ApplyPropertyValue(TextElement.FontWeightProperty, FontWeights.Bold);
            }
            m_comments.Clear();

            for(int i=0;i<m_tags.Count;i++)
            {
                TextRange range = new TextRange(m_tags[i].StartPosition, m_tags[i].EndPosition);
                range.ApplyPropertyValue(TextElement.ForegroundProperty, new SolidColorBrush(Color.FromRgb(86,156,214)));
                //range.ApplyPropertyValue(TextElement.FontWeightProperty, FontWeights.Bold);
            }
            m_tags.Clear();


            for (int i = 0; i < m_rgisters.Count; i++)
            {
                TextRange range = new TextRange(m_rgisters[i].StartPosition, m_rgisters[i].EndPosition);
                range.ApplyPropertyValue(TextElement.ForegroundProperty, new SolidColorBrush(Color.FromRgb(255, 156, 0)));
                //range.ApplyPropertyValue(TextElement.FontWeightProperty, FontWeights.Bold);
            }
            m_rgisters.Clear();




            rtbEditor.TextChanged += this.TextChangedEventHandler;
        }

        void CheckWordsInRun(Run run)
        {
            string text = run.Text;

            // pointeur de texte sur le début du dernier mot avant le pointeur i
            int startIndex = 0;
            
            // ittère sur toute la ligne
            for (int i = 0; i < text.Length; i++)
            {
                // si commentaire
                if ((i > 0 && text[i] == '/' && text[i - 1] == '/') | text[i] == ';')
                {
                    Tag t = new Tag();
                    t.StartPosition = run.ContentStart.GetPositionAtOffset(i-1, LogicalDirection.Forward);
                    t.EndPosition = run.ContentEnd;
                    t.Word = text;
                    m_comments.Add(t);
                    break;
                }

                // si label
                if (i > 0 && text[i] == ':')
                {
                    Tag t = new Tag();
                    t.StartPosition = run.ContentStart;
                    t.EndPosition = run.ContentEnd.GetPositionAtOffset(i, LogicalDirection.Forward);
                    t.Word = text;
                    m_label.Add(t);
                    continue;
                }

                // si mot clef
                if (!(Char.IsWhiteSpace(text[i]) | asmSyntaxProvider.GetSpecials.Contains(text[i])))
                {
                    string word = text.Substring(startIndex, i - startIndex + 1);

                    if (asmSyntaxProvider.IsKnownTag(word))
                    {
                        Tag t = new Tag();
                        t.StartPosition = run.ContentStart.GetPositionAtOffset(startIndex, LogicalDirection.Forward);
                        t.EndPosition = run.ContentStart.GetPositionAtOffset(startIndex + word.Length, LogicalDirection.Backward);
                        t.Word = word;
                        m_tags.Add(t);
                    }
                    else if (asmSyntaxProvider.IsKnownRegister(word))
                    {
                        Tag t = new Tag();
                        t.StartPosition = run.ContentStart.GetPositionAtOffset(startIndex, LogicalDirection.Forward);
                        t.EndPosition = run.ContentStart.GetPositionAtOffset(startIndex + word.Length + 1, LogicalDirection.Backward);
                        t.Word = word;
                        m_rgisters.Add(t);
                    }
                }

                // met a jour le pointeur de debut de mot si on change de mot
                if (Char.IsWhiteSpace(text[i]) | asmSyntaxProvider.GetSpecials.Contains(text[i]))
                    startIndex = i + 1;


                // si chiffres
                 if (Char.IsDigit(text[i]))
                {
                    string word = text.Substring(startIndex, i - startIndex);
                    Tag t = new Tag();
                    t.StartPosition = run.ContentStart.GetPositionAtOffset(i, LogicalDirection.Forward);
                    t.EndPosition = run.ContentStart.GetPositionAtOffset(i + 1, LogicalDirection.Backward);
                    t.Word = word;
                    m_numbers.Add(t);
                }
            }

        }

        int lastLineCount;
        private void printLineNumbers()
        {
            int linecount = rtbEditor.Document.Blocks.Count;
            if (linecount == lastLineCount)
                return;
            if (linecount > lastLineCount)
            {

                StringBuilder sb = new StringBuilder();
                for (int i = lastLineCount+1; i < linecount + 1; i++)
                {
                    sb.Append(Convert.ToString(i));
                    sb.Append("\n");
                }
                lineNumbers.AppendText(sb.ToString());
            }
            else
            {
                lineNumbers.Document.Blocks.Clear();

                StringBuilder sb = new StringBuilder();
                for (int i = 1; i < linecount + 1; i++)
                {
                    sb.Append(Convert.ToString(i));
                    sb.Append("\n");
                }
                sb.Append("\n");
                lineNumbers.AppendText(sb.ToString());
            }

            TextRange range = new TextRange(lineNumbers.Document.ContentStart, lineNumbers.Document.ContentEnd);
            range.ApplyPropertyValue(TextElement.ForegroundProperty, new SolidColorBrush(Color.FromRgb(135, 135, 230)));
            lastLineCount = linecount;
        }
        private void assemble(object sender, RoutedEventArgs e)
        {

        }
    }

}
