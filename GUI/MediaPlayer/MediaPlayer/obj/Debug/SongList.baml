   M S B A M L   `   `   `  ����  MediaPlayer    MediaPlayer.SongList   5      \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5      R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5      Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5      @d2http://schemas.microsoft.com/expression/blend/2008     5      .��5	   
   � .+�5
   
   &   System.Windows.Controls.DataGrid  -   5        $��lvSongListings��5
          AutoGenerateColumns  .   �� AlternationCount$ 1��6]      RowHeaderWidth$ 0Q�6r   "   VerticalScrollBarVisibility$ Hidden=�6�      AlternatingRowBackground �	#FFFAFFFF   	RowHeight$ 22Q�6�      GridLinesVisibility$
 None=�6�      CanUserResizeRows .  $��0q�6  ��6)   ��    Columns 5      0  *System.Windows.Controls.DataGridTextColumn  5      ,  &System.Windows.Controls.DataGridColumn	   Header$	 Title��6%   
   
IsReadOnly
 . 1  +System.Windows.Controls.DataGridBoundColumn   Binding 65   �� *Title+6O     5      $	 Artist��6%   
 .  65   �� *Artist+6P     5      $	 Album��6%   
 .  64   �� *Album+6N     5      $	 Genre��6%   
 .  64   �� *Genre+6N     5      $	 Plays��6%   
 .  64   �� *Plays+6N     5      $	 ID��6%      
Visibility$ Hidden=�6H      Width5  /System.Windows.Controls.DataGridLengthConverter$ 0 6\      CanUserResize .  
 .  61   �� *ID+6|   4  .System.Windows.Controls.DataGridComboBoxColumn  5      -   5        dgCB��$	 Rating��5   7   $ 50 6o    .  
 .     SelectedItemBinding 6H   �� *Rating+   EditingElementStyle 5      �� 5       �� 
TargetType" ��6    .�5      -   5        5      5      5      5      5      