/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) 1989-2004 MAXON Computer GmbH, all rights reserved  //
/////////////////////////////////////////////////////////////

// Starts the plugin registration

#include "c4d.h"
#include <string.h>

// forward declarations
//‚±‚±‚Éplugin“o˜^
//Bool RegisterSoftSel2VMCommand(void);
Bool RegisterSentakuCommand(void);

C4D_CrashHandler old_handler;


void SDKCrashHandler(Char *crashinfo)
{
	//printf("SDK CrashInfo:\n");
	//printf(crashinfo);
	
	// don't forget to call the original handler!!!
	if (old_handler) (*old_handler)(crashinfo);
}

void EnhanceMainMenu(void) 
{
	// do this only if necessary - otherwise the user will end up with dozens of menus!

	BaseContainer *bc = GetMenuResource(String("M_EDITOR"));
	if (!bc) return;

	// search for the most important menu entry. if present, the user has customized the settings
	// -> don't add menu again
	if (SearchMenuResource(bc,String("PLUGIN_CMD_1000472")))
		return; 

	GeData *last = SearchPluginMenuResource();

	BaseContainer sc;
	sc.InsData(MENURESOURCE_SUBTITLE,String("SDK Test"));
	sc.InsData(MENURESOURCE_COMMAND,String("IDM_NEU")); // add C4D's new scene command to menu
	sc.InsData(MENURESOURCE_SEPERATOR,true);
	sc.InsData(MENURESOURCE_COMMAND,String("PLUGIN_CMD_1000472")); // add ActiveObject dialog to menu
	
	if (last)
		bc->InsDataAfter(MENURESOURCE_STRING,sc,last);
	else // user killed plugin menu - add as last overall entry
		bc->InsData(MENURESOURCE_STRING,sc);
}

Bool PluginStart(void)
{

	// example of installing a crashhandler
	old_handler = C4DOS.CrashHandler; // backup the original handler (must be called!)
	C4DOS.CrashHandler = SDKCrashHandler; // insert the own handler


	if (!RegisterSentakuCommand()) return false;
	return true;
}

void PluginEnd(void)
{
	
}

Bool PluginMessage(Int32 id, void *data)
{
	switch (id)
	{
		case C4DPL_INIT_SYS:
			{
				if (!resource.Init()) return false; // don't start plugin without resource

				// important, the serial hook must be registered before PluginStart(), best in C4DPL_INIT_SYS
			
				return true;	
			}

	}
	return false;
}

