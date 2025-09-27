void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Jail_officer_take":
		//--> Сомнительное предложение
		if (CheckAttribute(pchar, "GenQuest.Contraoffer.Jail"))
		{
			dialog.text = "Ôrizetbe vették, mert csempészárut akart átadni és eladni. Figyelembe véve a hatóságoknak nyújtott segítségét és a helyzetét, csak "+FindRussianDaysString(sti(pchar.questTemp.JailTemp2))+"börtönben fog tölteni. Emellett minden pénzt, amit csempészéssel kerestél -"+FindRussianMoneyString(sti(pchar.questTemp.JailTemp1))+" - elvesznek tôled, és a város kincstárába kerülnek. Jó szórakozást, kapitány!";
			link.l1 = "";
			link.l1.go = "Jail_officer_take_1";
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Jail");
			NextDiag.currentnode = "Jail_officer_free";
			break;
		}
		//<-- Сомнительное предложение
			dialog.text = "Önt bûncselekmény elkövetése miatt vették ôrizetbe, és a börtönben tartják fogva "+FindRussianDaysString(sti(pchar.questTemp.JailTemp2))+". Emellett pénzbírságra is számíthatsz "+FindRussianMoneyString(sti(pchar.questTemp.JailTemp1))+". Jó szórakozást, kapitány úr!";
			link.l1 = "";
			link.l1.go = "Jail_officer_take_1";
			NextDiag.currentnode = "Jail_officer_free";
		break;
		
		case "Jail_officer_take_1":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10);
			DialogExit();
			DoQuestFunctionDelay("InPrison", 10.0);
		break;
		
		case "Jail_officer_free":
			dialog.text = "Nos, a börtönbüntetésednek vége. Remélem, tanultál valamit. Most már szabad vagy. Vedd ki a holmidat a tiszt melletti ládából. És ne hagyd, hogy újra elkapjalak!";
			link.l1 = "";
			link.l1.go = "Jail_officer_free_1";
		break;
		
		case "Jail_officer_free_1":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5);
			DialogExit();
			DoQuestFunctionDelay("GoFromPrison", 5.0);
		break;
	}
} 
