// ChangeCommand.h
//////////////////////////////////////////////////////////////////////

#ifndef _SENTAKUSOR_H_
#define _STOPMOTIONCMD_H_
#define PLUGIN_ID 1035503  
#include "c4d.h"
#include "c4d_symbols.h"
#include "lib_activeobjectmanager.h"
#include "customgui_inexclude.h"


class Sentaku : public GeDialog
{
private:
    Int32 _Scnt;
public:	
	Sentaku();
	~Sentaku();

 	virtual Bool CreateLayout(void);
	virtual Bool InitValues(void);
	virtual Bool Command(Int32 id, const BaseContainer &msg);
	virtual Int32 Message(const BaseContainer &msg, BaseContainer &result);
	virtual Bool AskClose();

	Bool EnableGadgets(void);

	Bool Select();
	void SerchiType(BaseDocument* doc, BaseObject* op, Int32 n, BaseList2D* Lop, Bool Bflag,  NBIT nbit, Bool solo , Bool GetIns, Bool Atag, Bool Lastflag, Bool P0flag);
	void TreeUnFold(BaseDocument* doc, BaseObject* tg,  NBIT nbit);
    Bool SetSelectObj();
	Bool Reset();
	void SoloReset(BaseDocument* doc, BaseObject* op);

	void TreeFoldOff(BaseDocument* doc, BaseObject* op,   NBIT nbit);
    void ActionCMD(BaseDocument* doc, BaseObject* op, Bool solo, Bool Lastflag, Bool P0flag, NBIT nbit);



};




class SentakuCMD : public CommandData
{
private:
	Sentaku dlg;
public:
	SentakuCMD();
	~SentakuCMD();

	enum StopMotionCMD_ID { ID = 1035503 };

	virtual Int32 GetState(BaseDocument *doc);
	virtual Bool Execute(BaseDocument *doc);
	virtual Bool RestoreLayout(void *secret);
};

#endif // _CHANGECOMMAND_H_