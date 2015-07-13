



#include "SentakuSORC.h"







Sentaku::Sentaku()
{
    GePrint("--------------------------------------------------------");
    GePrint(GeLoadString(ID_TITLE) +" "+ GeLoadString(ID_TITLE_VER));
    GePrint("copyright(c) Since 2015 CoffeeStock All rights reserved.");
    GePrint("--------------------------------------------------------");

}
Sentaku::~Sentaku()
{


}

Bool Sentaku::CreateLayout(void)
{
	if (!GeDialog::CreateLayout())
		return false;
	// first call the parent instance
	Bool res = GeDialog::CreateLayout();

	res = LoadDialogResource(IDD_DIALOGMAIN,NULL,0);
	return res;
}
Bool Sentaku::InitValues(void)
{
	SetInt32(IDC_COMBO1, CH1);
	SetInt32( IDC_EDITMANAGER, 1);

	EnableGadgets();
	return true;
}

Bool Sentaku::EnableGadgets(void)
{
	Int32 a;
	GetInt32(IDC_COMBO1, a);

	if (a == CH7) Enable(IDC_LINK, true);
	else Enable(IDC_LINK, false);

	if (a == CH7)
	{
		BaseDocument* doc = GetActiveDocument();
		if (!doc) return false;
		LinkBoxGui *link = (LinkBoxGui*)FindCustomGui(IDC_LINK, CUSTOMGUI_DESCRIPTION);
		BaseList2D* list = link->GetLink(doc);
		if (list)
		{
			if (list->IsInstanceOf(Oinstance))
			{
				Enable(IDC_CHK, true);
				Enable(IDC_CHKINS, false);
				Enable(IDC_CHKTAB, false);
			}
			else
			{
				Enable(IDC_CHK, false);
				if( list->IsInstanceOf(Obase))
				{
				   Enable(IDC_CHKINS, true);
				   Enable(IDC_CHKTAB, false);
                    if(list->IsInstanceOf(Opolygon))
                    {
                       Enable(IDC_CHK0POLY, true);
                    }

				}
				else if( list->IsInstanceOf(Tbase))
				{
					Enable(IDC_CHKINS, false);
					 Enable(IDC_CHKTAB, true);
                  //  Enable(IDC_CHKLAST, false);
                    Enable(IDC_CHK0POLY, false);
					Enable(IDC_CHKUVW, true);

				}
				else
				{
 					Enable(IDC_CHKINS, false);
					Enable(IDC_CHKTAB, false);
                  //  Enable(IDC_CHKLAST, false);
                    Enable(IDC_CHK0POLY, false);
					Enable(IDC_CHKUVW, false);

				}
				
			}
               Enable(IDC_CHKLAST, true);
		}
		else
		{
			Enable(IDC_CHK, false);
			Enable(IDC_CHKINS, false);
			Enable(IDC_CHKTAB, false);
            Enable(IDC_CHKLAST, false);
            Enable(IDC_CHK0POLY, false);
			Enable(IDC_CHKUVW, false);
		}
	}
	else
	{
		Enable(IDC_CHK, false);
		Enable(IDC_CHKINS, false);
		Enable(IDC_CHKTAB, false);
        Enable(IDC_CHKLAST, false);
        Enable(IDC_CHK0POLY, false);
		Enable(IDC_CHKUVW, false);
	}

	Bool flag;
	GetBool( IDC_SOLO,flag);
	if(flag) Enable(IDC_BTNSRESET, true);
	else Enable(IDC_BTNSRESET, false);



	return true;
}
Bool Sentaku::Command(Int32 id, const BaseContainer &msg)
{
	switch (id)
	{
	case IDC_COMBO1: 
		EnableGadgets();
		break;

	case IDC_BTNSELECT:
		Select();
		break;
	case IDC_LINK: 
		EnableGadgets();
		break;
	case IDC_EDITMANAGER:
		{
			Int32 a;
			GetInt32(IDC_EDITMANAGER,a);
			if( a <= 1) SetInt32(IDC_EDITMANAGER,1);
			if( a >= 4)SetInt32(IDC_EDITMANAGER,4);
		}
		break;
        case IDC_BTNSEL:
            SetSelectObj();
            break;
		case IDC_BTNSRESET:
			Reset();
			break;
		case IDC_SOLO:
			EnableGadgets();
		break;

		default:
break;
	}

	return true;
}

Int32 Sentaku::Message(const BaseContainer &msg, BaseContainer &result)
{


	return GeDialog::Message(msg, result);
}



Bool Sentaku::AskClose()
{
	Reset();
	return false;
}

Bool Sentaku::Select()
{
	StopAllThreads();
	BaseDocument* doc = GetActiveDocument();
	if (!doc) return false;

	BaseObject* op = doc->GetFirstObject();
	if (!op) return false;

	Int32 type;
	GetInt32(IDC_COMBO1, type);

	BaseList2D* list = nullptr;
	Bool flag = false;

	Int32 num;
	GetInt32(IDC_EDITMANAGER, num);
	NBIT nbit = NBIT_OM1_FOLD;
	switch(num)
	{
	case 1:
		nbit=NBIT_OM1_FOLD;
		break;
	case 2:
		 nbit=NBIT_OM2_FOLD;
		 break;
	case 3:
		nbit=NBIT_OM3_FOLD;
		break;
	case 4:
		nbit=NBIT_OM4_FOLD;
		break;
	}
    
    //Solo表示
    Bool solo;
    GetBool(IDC_SOLO, solo);


	Bool GetIns = false;

	Bool Atag=false;
    
    Bool P0flag = false; //ポリゴン０フラグ
    Bool Lastflag = false; //Endのみ選択フラグ
    
    GetBool(IDC_CHKLAST, Lastflag );
    GetBool(IDC_CHK0POLY, P0flag );

	Bool UVW;
	GetBool(IDC_CHKUVW, UVW);
    
	if (type == CH7)
	{

		LinkBoxGui *link = (LinkBoxGui*)FindCustomGui(IDC_LINK, CUSTOMGUI_DESCRIPTION);

		list = link->GetLink(doc);
		if (!list)
		{
			return false;
		}

		GetBool(IDC_CHK, flag);
		GetBool(IDC_CHKINS, GetIns);
		GetBool(IDC_CHKTAB, Atag);

	}
	Reset();
	doc->StartUndo();

	TreeFoldOff(doc, op, nbit );

	op = doc->GetFirstObject();

	SerchiType(doc, op, type, list, flag, nbit, solo, GetIns, Atag, Lastflag, P0flag, UVW);

	if(Atag)
	{
		//ActiveObjectManager_Open();
		ActiveObjectManager_SetMode( ACTIVEOBJECTMODE_TAG, true); 
	}
	doc->EndUndo();
	EventAdd();
	return true;
}

void Sentaku::TreeFoldOff(BaseDocument* doc, BaseObject* op,  NBIT nbit)
{
	
	while(op)
	{
		doc->AddUndo(UNDOTYPE_CHANGE, op);
		if(op->GetNBit(nbit))
		{
		   op->ChangeNBit(nbit, NBITCONTROL_CLEAR);
		}

		TreeFoldOff(doc, op->GetDown(), nbit);
		op = op->GetNext();
	}


}

void  Sentaku::TreeUnFold(BaseDocument* doc, BaseObject* tg, NBIT nbit)
{
	while(tg)
	{

		if(!tg->GetNBit(nbit))
		{
			//doc->AddUndo(UNDOTYPE_CHANGE, tg);
			BaseObject* ntg=tg->GetUp();
			tg->ChangeNBit(nbit, NBITCONTROL_SET);
			tg=ntg;
		}
		else //展開している場合
		{
		   break;
		}
	}
}


Bool Sentaku::SetSelectObj()
{
    BaseDocument* doc=GetActiveDocument();
    if(!doc) return false;
    
    BaseObject* op=BaseObject::Alloc(Oselection);
    if(!op) return false;
    BaseContainer* bc=op->GetDataInstance();
    InExcludeData *list=(InExcludeData*)bc->GetCustomDataType(SELECTIONOBJECT_LIST,CUSTOMDATATYPE_INEXCLUDE_LIST);
    
	BaseObject* fop = doc->GetFirstObject();
	if (!fop) return false;
	


	AutoAlloc<AtomArray> array;
	doc->GetActiveObjects(array, GETACTIVEOBJECTFLAGS_0);
	for (Int32 i = 0; i < array->GetCount(); i++)
	{
		BaseObject* op = (BaseObject*)array->GetIndex(i);
		list->InsertObject(op, i);
	}

    //オブジェクトを記憶
    doc->AddUndo(UNDOTYPE_NEW,op);
    doc->InsertObject(op,nullptr, nullptr );
    
    
    
    
    EventAdd();
    return true;
}

void Sentaku::SerchiType(BaseDocument* doc, BaseObject* op, Int32 n, BaseList2D* Lop, Bool Bflag , NBIT nbit, Bool solo, Bool GetIns, Bool Atag, Bool Lastflag, Bool P0flag, Bool UVW)
{
	
	while (op)
	{
		Bool check=false;
		//doc->AddUndo(UNDOTYPE_CHANGE, op);
	
		if (n == CH1)
		{
			if (op->GetEditorMode() == MODE_ON)
			{
				op->SetBit(BIT_ACTIVE);
				TreeUnFold( doc, op->GetUp(), nbit);
			}
			else
            {
               op->DelBit(BIT_ACTIVE);
                if(solo)
                {
                    op->ChangeNBit(NBIT_OHIDE,NBITCONTROL_SET);
                }
            }
		}
		else if (n == CH2)
		{
			if (op->GetEditorMode() == MODE_OFF)
			{
				op->SetBit(BIT_ACTIVE);
				TreeUnFold( doc, op->GetUp(), nbit);
			}
			else
			{
				op->DelBit(BIT_ACTIVE);
				if (solo)
				{
					op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_SET);
				}
			}
		}
		else if (n == CH3)
		{
			if (op->GetRenderMode() == MODE_ON)
			{
				op->SetBit(BIT_ACTIVE);
				TreeUnFold( doc, op->GetUp(), nbit);
			}
			else
			{
				op->DelBit(BIT_ACTIVE);
				if (solo)
				{
					op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_SET);
				}
			}
		}
		else if (n == CH4)
		{
			if (op->GetRenderMode() == MODE_OFF)
			{
				op->SetBit(BIT_ACTIVE);
				TreeUnFold( doc, op->GetUp(), nbit);
			}
			else
			{
				op->DelBit(BIT_ACTIVE);
				if (solo)
				{
					op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_SET);
				}
			}
		}
		else if (n == CH5)
		{
			if (op->GetInfo()& OBJECT_MODIFIER || op->GetInfo()& OBJECT_GENERATOR || op->GetInfo()& OBJECT_PARTICLEMODIFIER || op->GetInfo()& OBJECT_INPUT)
			{
			
				if (op->GetDeformMode())
				{
					op->SetBit(BIT_ACTIVE);
					TreeUnFold( doc, op->GetUp(), nbit);
				}
				else
				{
					op->DelBit(BIT_ACTIVE);
					if (solo)
					{
						op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_SET);
					}
				}
			}
			else
			{
				op->DelBit(BIT_ACTIVE);
				if (solo)
				{
					op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_SET);
				}
			}
		}
		else if (n == CH6)
		{
			if (op->GetInfo()& OBJECT_MODIFIER || op->GetInfo()& OBJECT_GENERATOR || op->GetInfo()& OBJECT_PARTICLEMODIFIER || op->GetInfo()& OBJECT_INPUT)
			{
				if (!op->GetDeformMode())
				{
					op->SetBit(BIT_ACTIVE);
					TreeUnFold( doc, op->GetUp(), nbit);
				}
				else
				{
					op->DelBit(BIT_ACTIVE);
					if (solo)
					{
						op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_SET);
					}
				}
			}
			else
			{
				op->DelBit(BIT_ACTIVE);
				if (solo)
				{
					op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_SET);
				}
			}
		}
		else if (n == CH7)
		{

			if (Lop->IsInstanceOf(Obase))
			{
				
				if(Lop != op)
				{
					
					if (Lop->IsInstanceOf(Oinstance))  //ターゲットがインスタンスのみ
					{

						if (Bflag)	//レファレンスが同じもののみ
						{
 								//ターゲットインスタンス
							BaseContainer *Abc = Lop->GetDataInstance();
							BaseObject* Alink = Abc->GetObjectLink(INSTANCEOBJECT_LINK, doc); //ターゲットインスタンスソース
							if( op->IsInstanceOf(Oinstance)) //探索対象がインスタンスの場合
							{
								//探索対象	インスタンス
								BaseContainer *Bbc = op->GetDataInstance();
								BaseObject* Blink = Bbc->GetObjectLink(INSTANCEOBJECT_LINK, doc); // 探索インスタンスソース


								if(Alink && Blink)
								{
									if(Alink == Blink)
									{
                                        ActionCMD(doc, op, solo,  Lastflag, P0flag, nbit);
//										op->SetBit(BIT_ACTIVE);
//										TreeUnFold( doc, op->GetUp(), nbit);
										
									}
									else
									{
										op->DelBit(BIT_ACTIVE);
										if (solo)
										{
											op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_SET);
										}
									}
								}

							}
							else if(Alink == op)
							{
//								op->SetBit(BIT_ACTIVE);
//								TreeUnFold( doc, op->GetUp(), nbit);
                                ActionCMD(doc, op, solo,  Lastflag, P0flag, nbit);
								check=true;
							}
							else
							{
								op->DelBit(BIT_ACTIVE);
								if (solo)
								{
									op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_SET);
								}
							}
						}
						else
						{
							//ターゲットと探索対象が同じタイプの場合
							if (Lop->GetType() == op->GetType())
							{
                                ActionCMD(doc, op, solo,  Lastflag,P0flag, nbit);
//								op->SetBit(BIT_ACTIVE);
//								TreeUnFold( doc, op->GetUp(), nbit);
							}
							else
							{
								op->DelBit(BIT_ACTIVE);
								if (solo)
								{
									op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_SET);
								}
							}
						}

					}
					else   //インスタンス以外
					{
                        //GePrint("other");
						 if( GetIns	)
						 {
							 if(op->IsInstanceOf(Oinstance))
							 {
									//ターゲットインスタンス
									BaseContainer *Abc = op->GetDataInstance();
									BaseObject* Alink = Abc->GetObjectLink(INSTANCEOBJECT_LINK, doc); //ターゲットインスタンスソース
									if(Alink && Alink == Lop)
									{
                                        ActionCMD(doc, op, solo,  Lastflag, P0flag, nbit);
// 										op->SetBit(BIT_ACTIVE);
//										TreeUnFold( doc, op->GetUp(), nbit);
									

									}
									else
									{
										op->DelBit(BIT_ACTIVE);
										if (solo)
										{
											op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_SET);
										}

									}


							 }
							 else
							 {
								op->DelBit(BIT_ACTIVE);
								if (solo)
								{
									op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_SET);
								}
							 }

						 }
						 else
						 {
                           //  GePrint("kkkk");
							if (Lop->GetType() == op->GetType())
							{
                                ActionCMD(doc, op, solo,  Lastflag, P0flag, nbit);
//                                if(Lastflag) //Endのみ選択
//                                {
//                                    if(!op->GetDown())
//                                    {
//                                        op->SetBit(BIT_ACTIVE);
//                                        TreeUnFold( doc, op->GetUp(), nbit);
//                                    }
//                                    else{
//                                        op->DelBit(BIT_ACTIVE);
//                                        if (solo)
//                                        {
//                                            op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_SET);
//                                        }
//                                    }
//                                }
//                                else{
//                                    op->SetBit(BIT_ACTIVE);
//                                    TreeUnFold( doc, op->GetUp(), nbit);
//                                }
							}
							else
							{

								if (Bflag && Lop->IsInstanceOf(Oinstance) )	//レファレンスが同じもののみ
								{
									//ターゲットインスタンス
									BaseContainer *Abc = Lop->GetDataInstance();
									BaseObject* Alink = Abc->GetObjectLink(INSTANCEOBJECT_LINK, doc); //ターゲットインスタンスソース
									if( Alink == op)
									{
                                        ActionCMD(doc, op, solo,  Lastflag, P0flag, nbit);
//                                        if(Lastflag) //Endのみ選択
//                                        {
//                                            if(!op->GetDown())
//                                            {
//                                                op->SetBit(BIT_ACTIVE);
//                                                TreeUnFold( doc, op->GetUp(), nbit);
//                                            }
//                                            else{
//                                                op->DelBit(BIT_ACTIVE);
//                                                if (solo)
//                                                {
//                                                    op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_SET);
//                                                }
//                                            }
//                                        }
//                                        else{
//                                            op->SetBit(BIT_ACTIVE);
//                                            TreeUnFold( doc, op->GetUp(), nbit);
//                                        }
									}
									else
									{
										op->DelBit(BIT_ACTIVE);
										if (solo)
										{
											op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_SET);
										}

									}
								}
								else
								{
									op->DelBit(BIT_ACTIVE);
									if (solo)
									{
										op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_SET);
									}
								}
							}
						 }
					}
				}
				else
				{
                    if(!Lastflag && !P0flag )
                    {
                        op->SetBit(BIT_ACTIVE);
                        TreeUnFold( doc, op->GetUp(), nbit);
                        check=true;
                    }
                    else{
                         ActionCMD(doc, op, solo,  Lastflag, P0flag, nbit);
                    }
				}
			}
			else if (Lop->IsInstanceOf(Tbase))
			{
				BaseTag* tag = op->GetFirstTag();
				Bool flag = false;
				while (tag)
				{

					if( UVW)
					{
						if(tag->IsInstanceOf( Ttexture))
						{
							TextureTag* Atag=(TextureTag*)tag;
							GeData d;
							Atag->GetParameter(DescLevel(TEXTURETAG_PROJECTION), d ,DESCFLAGS_GET_0);
							if(d.GetInt32() != TEXTURETAG_PROJECTION_UVW)
							{
							   tag->SetBit(BIT_ACTIVE);
							   op->SetBit(BIT_ACTIVE);
							   flag = true;

							}
							else
							{
								tag->DelBit(BIT_ACTIVE);
							}

						}
 						else
						{
							tag->DelBit(BIT_ACTIVE);
						}

					}
					else
					{
						if(tag->IsInstanceOf( Ttexture) && Lop->IsInstanceOf( Ttexture))
						{
					
							TextureTag* Ztag=(TextureTag*)Lop;
							TextureTag* Xtag=(TextureTag*)tag;
							BaseMaterial* Amat= Ztag->GetMaterial();
							BaseMaterial* Bmat= Xtag->GetMaterial();
							if(Amat == Bmat)
							{
						
								//ActionCMD(doc, op, solo,  Lastflag, P0flag, nbit);
								op->SetBit(BIT_ACTIVE);
								flag = true;

								if(Atag)
								{
									tag->SetBit(BIT_ACTIVE);
								}
								else break;	

							}
							else
							{
								tag->DelBit(BIT_ACTIVE);
							}
						}
						else
						{
							if (Lop->GetType() == tag->GetType())
							{
								op->SetBit(BIT_ACTIVE);
								//op->SetBit(BIT_ACTIVE);
								flag = true;

								if(Atag)
								{
									tag->SetBit(BIT_ACTIVE);
								}
								else break;	
							}
							else
							{
								tag->DelBit(BIT_ACTIVE);
							}
						}
					}
					tag = tag->GetNext();
				}

				if(flag)
				{
					TreeUnFold( doc, op->GetUp(), nbit);
				}
				else
				{
					op->DelBit(BIT_ACTIVE);
					if (solo)
					{
						op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_SET);
					}
				}

			}
			
		}
		if(!check)
		{
			SerchiType(doc, op->GetDown(), n, Lop, Bflag, nbit, solo,  GetIns, Atag, Lastflag, P0flag, UVW);
		}
		op = op->GetNext();
	}
}

Bool Sentaku::Reset()
{
	BaseDocument* doc = GetActiveDocument();
	if (!doc) return false;

	BaseObject* op = doc->GetFirstObject();
	if (!op) return false;

	doc->StartUndo();
	SoloReset(doc, op);
	doc->EndUndo();
	EventAdd();
	return true;
}


void Sentaku::ActionCMD(BaseDocument* doc, BaseObject* op, Bool solo, Bool Lastflag, Bool P0flag, NBIT nbit)
{
    if(Lastflag && P0flag && op->IsInstanceOf(Opolygon)) //Endのみ選択
    {
        PolygonObject* poly = ToPoly(op);
        
        
        Int32 cnt = poly->GetPolygonCount();
        if( cnt == 0 && !op->GetDown())
        {
            op->SetBit(BIT_ACTIVE);
            TreeUnFold( doc, op->GetUp(), nbit);
        }
        else
        {
            op->DelBit(BIT_ACTIVE);
            if (solo)
            {
                op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_SET);
            }
        }
    
    }else if(Lastflag && !P0flag)
    {
        if(!op->GetDown())
        {
            op->SetBit(BIT_ACTIVE);
            TreeUnFold( doc, op->GetUp(), nbit);
        }
        else{
            op->DelBit(BIT_ACTIVE);
            if (solo)
            {
                op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_SET);
            }
        }
    }else if(!Lastflag && P0flag && op->IsInstanceOf(Opolygon) )
    {
        PolygonObject* poly = ToPoly(op);


        Int32 cnt = poly->GetPolygonCount();
        if( cnt == 0)
        {
            op->SetBit(BIT_ACTIVE);
            TreeUnFold( doc, op->GetUp(), nbit);
        }
        else
        {
            op->DelBit(BIT_ACTIVE);
            if (solo)
            {
                op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_SET);
            }
        }
    }
    else{
        op->SetBit(BIT_ACTIVE);
        TreeUnFold( doc, op->GetUp(), nbit);
    }
    
//        if(P0flag && op->IsInstanceOf(Opolygon))
//        {
//            PolygonObject* poly = ToPoly(op);
//            
//        
//            Int32 cnt = poly->GetPolygonCount();
//            if( cnt == 0)
//            {
//                op->SetBit(BIT_ACTIVE);
//                TreeUnFold( doc, op->GetUp(), nbit);
//            }
//            else
//            {
//                op->DelBit(BIT_ACTIVE);
//                if (solo)
//                {
//                    op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_SET);
//                }
//            }
//            
//        }
//        else{
//            if(!op->GetDown())
//            {
//                op->SetBit(BIT_ACTIVE);
//                TreeUnFold( doc, op->GetUp(), nbit);
//            }
//            else{
//                op->DelBit(BIT_ACTIVE);
//                if (solo)
//                {
//                    op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_SET);
//                }
//            }
//        }
//    }
//    else{
//        op->SetBit(BIT_ACTIVE);
//        TreeUnFold( doc, op->GetUp(), nbit);
//    }
    
}
void Sentaku::SoloReset(BaseDocument* doc, BaseObject* op)
{

	while (op)
	{
		doc->AddUndo(UNDOTYPE_CHANGE, op);
		op->ChangeNBit(NBIT_OHIDE, NBITCONTROL_CLEAR);
		SoloReset(doc, op->GetDown());
		op = op->GetNext();
	}

}
///////////////////////////////////////////////////////////////////////////
//コマンド設定
SentakuCMD::SentakuCMD()
{
}

SentakuCMD::~SentakuCMD()
{
}

Int32 SentakuCMD::GetState(BaseDocument *doc)
{
	return CMD_ENABLED;
}

Bool SentakuCMD::Execute(BaseDocument *doc)
{
	return dlg.Open(DLG_TYPE_ASYNC,PLUGIN_ID,-1,-1);//ダイアログオープン
}

Bool SentakuCMD::RestoreLayout(void *secret)
{
	return dlg.RestoreLayout(PLUGIN_ID,0,secret);
}
////////////////////////////////////////////////////////////////////////////////////

Bool  RegisterSentakuCommand()
{
	String name =GeLoadString(ID_TITLE);
//	return RegisterCommandPlugin(PLUGIN_ID, name, 0, AutoBitmap("serial.tif"),String("SerialCode Plugin") , gNew SerialCommand);
		return RegisterCommandPlugin(PLUGIN_ID, name, 0, AutoBitmap("Sentaku.tif"),String(" ") , NewObjClear( SentakuCMD ));
}
