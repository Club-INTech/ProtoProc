   M S B A M L   `   `   `  ����   MacroProcIDE_MUI    ModernUIApp1.MainWindow   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     Z VFirstFloor.ModernUI, Version=1.0.6.0, Culture=neutral, PublicKeyToken=2d21ec3cd074c59a0mui&http://firstfloorsoftware.com/ModernUI  :d2http://schemas.microsoft.com/expression/blend/2008  Dmc;http://schemas.openxmlformats.org/markup-compatibility/2006  -     � Title$  MacroProcesseur Editor�� � 	Resources    ComboBoxStyleModern �� 
TargetType �� Property  	InputText �� Value  InputBackground  InputBorder �� 
TargetType �Name J� SnapsToDevicePixels � ColumnDefinitions	 �Name
 � AllowsTransparency �� RelativeSource �� MaxDropDownHeight �� ElementName �� CornerRadius ��Name  WindowBorderActive  PopupBackground ��Name �� ClearTypeHint ��Name ��Name-  'System.Windows.Input.KeyboardNavigation   DirectionalNavigation d� 	IsChecked �� Mode F�Name  DownArrowGeometry J� IsHitTestVisible �� SelectionBoxItemTemplate �� SelectionBoxItem# �� SelectionBoxItemStringFormat �� ContentStringFormat �� Triggers P� Property P� Value  �� 
TargetName  InputTextDisabled  InputBackgroundHover 	 InputBorderHover 

 Accent! P� 
SourceName" �� Triggers# ��Name$ �� 
IsReadOnly  RichTextBoxStyleMetro% �� Padding��%#  &	        &	 �    �� " ��.���  � ��# �  ��  � ��# �  ��  � ��# �  ��  � ��$ 1q���  � ��$
 Auto=���  � ��$
 Auto=���  � ��$ 7,3,8,3q���  � �� . ��  �@��PanningMode$
 Both=���  �@��IsFlicksEnabled .  ��  �@�FocusVisualStyle Z� ��  � �� �� " ��.R�� $ MainGrid�� .  �� $��* ��� #��� r�$��0 �.+�� $	 
PART_Popup��
 . $��2��$��1q�#��� .�$��Bottom=����� *IsDropDownOpen+ �� *TemplatedParent+.��� #��z $��4q����� *ActualWidth+$ MainGrid��.+��� ���	#0F000000$��1q����	#0C000000$	 2.5��$��-1q��� ���	#0C000000$��1q����	#0A000000$
 2.75��$��-2q��� $ DropDownBorder��#���  $��1q�#���  $��0,-1,0,0q�._��� $ DropDownScrollViewer��.��� $ Enabled=�.+��� $
��Left=�$��0��$	��Top=�$��0��.+��� $ 
OpaqueRect������ *
Background+$ DropDownBorder������ *ActualHeight+$ DropDownBorder������ *ActualWidth+$ DropDownBorder���� $ ItemsPresenter��$ 	Contained=�# z d� #��z��#��z��#��z��$��2��$��0,0,0,10q� �� *IsDropDownOpen+$ TwoWay=� �� *TemplatedParent+F� $ Arrow��$��2��#���  #��z��$��Right=� .  $��3,1,8,0q�$��Center=��� #��z #��z # z #��z�� .  #��z��# z #��z�� P�  �@��HasItems .  . ��� $  DropDownBorder�� � ��$ 95��P�  � {� .  . ��� # �   � ��P�  �@J�IsMouseOver . . ��� # �   � ���� # � 	  � ��P�  �@J�	IsFocused . . ��� # � 
  � ��P�  �@��
IsGrouping . . ���  � �� .  P� $! DropDownScrollViewer�� � �� .  . ��� $  
OpaqueRect�� �� *VerticalOffset+$ DropDownScrollViewer�� �@��Top�� $  
OpaqueRect�� �� *HorizontalOffset+$ DropDownScrollViewer�� �@��Left" P�  �@��
IsEditable . . ���  � �� .  ��  � ��$ 3q���  � �� �� " ��.R�� $ MainGrid�� .  �� $��* ��� #��� r�$��0 �.+�� $	 
PART_Popup��
 . $��2��$��1q�#��� .�$��Bottom=����� *IsDropDownOpen+ �� *TemplatedParent+.��� #��z $��4q����� *ActualWidth+$ MainGrid��.+��� ���	#0F000000$��1q����	#0C000000$	 2.5��$��-1q��� ���	#0C000000$��1q����	#0A000000$
 2.75��$��-2q��� $ DropDownBorder��#���  $��1q�#���  $��0,-1,0,0q�._��� $ DropDownScrollViewer��.��� $ Enabled=�.+��� $
��Left=�$��0��$	��Top=�$��0��.+��� $ 
OpaqueRect������ *
Background+$ DropDownBorder������ *ActualHeight+$ DropDownBorder������ *ActualWidth+$ DropDownBorder���� $ ItemsPresenter��$ 	Contained=�# z d� #��z��#��z��#��z��$��2��$��0,0,0,10q� �� *IsDropDownOpen+$ TwoWay=� �� *TemplatedParent+F� $ Arrow��$��2��#���  #��z��$��Right=� .  $��3,1,8,0q�$��Center=��� $# PART_EditableTextBox��#��z��#��z��$��2,0,0,1q�#��z��$ �� *
IsReadOnly+ �� *TemplatedParent+.������ " ��.���  �@�OverridesDefaultStyle . ��  �@J�	AllowDrop . ��  � ��$ 0����  � ��$ 0����  �@�FocusVisualStyle Z� ��  �@��PanningMode$ VerticalFirst=���  �@��IsFlicksEnabled .  ��  � �� �� " ��.R��� $ PART_ContentHost��
������ |�.  $��Hidden=�$��Hidden=�.�� P�  �@��HasItems .  . ��� $  DropDownBorder�� � ��$ 95��P�  � {� .  . ��� # �   � ��P�  �@J�IsMouseOver . . ��� # �   � ���� # � 	  � ��P�  �@J�	IsFocused . . ��� # � 
  � ��P�  �@��
IsGrouping . . ���  � �� .  P� $! DropDownScrollViewer�� � �� .  . ��� $  
OpaqueRect�� �� *VerticalOffset+$ DropDownScrollViewer�� �@��Top�� $  
OpaqueRect�� �� *HorizontalOffset+$ DropDownScrollViewer�� �@��Left�� " ��.���  � ��# �  ��  � ��# �  ��  � ��# �  ��  � ��$ 1q���  � ��$ 2,1,1,1q���  �@J�	AllowDrop . ��  �@�FocusVisualStyle Z� ��  �@��PanningMode$ VerticalFirst=���  �@��IsFlicksEnabled .  ��  �@��SelectionBrush# � 
 ��  �@=�ErrorTemplate �� ��  � �� �� " ��.R��� $ Bd��#��z��#��z��#��z��#% z�� . ._��� $ PART_ContentHost��$ Enabled=�# z  P�  � {� .  . ��� # �   � ��P�  �@��
IsReadOnly . . ��� # �   � ��P�  �@J�	IsFocused . . ��� $  Bd��# � 
  � ������ & �� ResourceKey$& BlankWindow��' J� CommandBindings' )  #System.Windows.Input.CommandBinding  -   (   Command$( ApplicationCommands.Open��  -   $( ApplicationCommands.Save��.��]� .+�c� $	��Top=�  ToolBarStyleMetro#���  .@��� $��ApplicationCommands.Open��.���� $��Open_6529.png��$��16��$��16���� $��ApplicationCommands.Save��.���� $��Save_6530.png��$��16��$��16���� .��� .+��� -   ) ��Name$) lineNumbers����. * �� AcceptsReturn* . #���  $��70��$
��Left=� ��%3   'J�       �� " J�.���  �@��Margin$ 0q��� -   $) 	rtbEditor����. $��Visible=�* . + �� 
AcceptsTab+ . #���  $��70,0,0,0q� ��%3   'J�       �� " J�.���  �@��Margin$ 0q�