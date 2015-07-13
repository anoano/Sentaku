// C4D-DialogResource
DIALOG IDD_DIALOGMAIN
{
  NAME IDS_DIALOG; CENTER_V; SCALE_H; 
  
  GROUP IDC_STATIC
  {
    ALIGN_TOP; ALIGN_LEFT; 
    BORDERSIZE 10, 10, 10, 10; 
    COLUMNS 1;
    SPACE 4, 4;
    
    COMBOBOX IDC_COMBO1
    {
      ALIGN_TOP; ALIGN_LEFT; SIZE 200, 15; 
      CHILDS
      {
        CH1, ST1; 
        CH2, ST2; 
        CH3, ST3; 
        CH4, ST4; 
        CH5, ST5; 
        CH6, ST6; 
        CH7, ST7; 
      }
    }
    GROUP IDC_STATIC
    {
      NAME IDS_STATIC1; SCALE_V; ALIGN_LEFT; 
      BORDERSIZE 0, 10, 0, 5; 
      COLUMNS 1;
      SPACE 4, 4;
      
      LINK IDC_LINK
      {
        ALIGN_TOP; SCALE_H; SIZE 235, 9; 
      }
      GROUP IDC_STATIC
      {
        NAME IDS_STATIC8; ALIGN_TOP; ALIGN_LEFT; 
        BORDERSIZE 14, 0, 0, 0; 
        COLUMNS 1;
        SPACE 4, 4;
        
        CHECKBOX IDC_CHK { NAME IDS_CHECK; ALIGN_TOP; CENTER_H; SIZE 0, 1;  }
        CHECKBOX IDC_CHKINS { NAME IDS_CHECK3; ALIGN_TOP; ALIGN_LEFT;  }
        CHECKBOX IDC_CHKTAB { NAME IDS_CHECK4; ALIGN_TOP; ALIGN_LEFT;  }
		CHECKBOX IDC_CHKLAST { NAME IDS_CHECK5; ALIGN_TOP; ALIGN_LEFT;  }
	    CHECKBOX IDC_CHK0POLY { NAME IDS_CHECK6; ALIGN_TOP; ALIGN_LEFT;  }
      }
    }
    SEPARATOR { SCALE_H; }
    GROUP IDC_STATIC
    {
      NAME IDS_STATIC4; ALIGN_TOP; SCALE_H; 
      BORDERSIZE 0, 5, 0, 5; 
      COLUMNS 2;
      SPACE 4, 4;
      
      STATICTEXT IDC_STATIC { NAME IDS_STATIC3; CENTER_V; CENTER_H; }
      EDITNUMBERARROWS IDC_EDITMANAGER
      { CENTER_V; SCALE_H; SIZE 70, 0; }
    }
    GROUP IDC_STATIC
    {
      NAME IDS_STATIC7; ALIGN_TOP; SCALE_H; 
      BORDERSIZE 0, 5, 0, 5; 
      COLUMNS 2;
      SPACE 4, 4;
      
      CHECKBOX IDC_SOLO { NAME IDS_CHECK2; CENTER_V; CENTER_H;  }
      BUTTON IDC_BTNSRESET { NAME IDS_BUTTON1; ALIGN_TOP; SCALE_H; SIZE 73, 15; }
    }
    SEPARATOR { SCALE_H; }
    GROUP IDC_STATIC
    {
      NAME IDS_STATIC4; ALIGN_TOP; SCALE_H; 
      BORDERSIZE 0, 0, 0, 0; 
      COLUMNS 1;
      SPACE 4, 4;
      
      GROUP IDC_STATIC
      {
        NAME IDS_STATIC6; CENTER_V; SCALE_H; 
        BORDERSIZE 0, 5, 0, 0; 
        COLUMNS 2;
        SPACE 4, 4;
        
        BUTTON IDC_BTNSELECT { NAME IDS_BUTTON; ALIGN_TOP; SCALE_H; SIZE 180, 15; }
      }
      GROUP IDC_STATIC
      {
        NAME IDS_STATIC5; ALIGN_TOP; SCALE_H; 
        BORDERSIZE 0, 4, 0, 0; 
        COLUMNS 1;
        SPACE 4, 4;
        
        BUTTON IDC_BTNSEL { NAME IDS_BTNSEL; ALIGN_TOP; SCALE_H; SIZE 180, 15; }
      }
    }
  }
}