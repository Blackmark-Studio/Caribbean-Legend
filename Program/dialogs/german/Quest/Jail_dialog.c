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
			dialog.text = "Sie wurden festgenommen, weil Sie versucht haben, Schmuggelware zu übertragen und zu verkaufen. Unter Berücksichtigung Ihrer Hilfe für die Behörden und Ihrer Position werden Sie nur im Gefängnis verbringen "+FindRussianDaysString(int(pchar.questTemp.JailTemp2))+". Außerdem, all das Geld, das du durch Schmuggel verdient hast -"+FindRussianMoneyString(int(pchar.questTemp.JailTemp1))+" wird weggenommen und in die Stadtkasse gelegt. Viel Spaß, Kapitän!";
			link.l1 = "";
			link.l1.go = "Jail_officer_take_1";
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Jail");
			NextDiag.currentnode = "Jail_officer_free";
			break;
		}
		//<-- Сомнительное предложение
			dialog.text = "Sie wurden wegen Begehung einer Straftat festgenommen und Sie werden im Gefängnis festgehalten für "+FindRussianDaysString(int(pchar.questTemp.JailTemp2))+". Außerdem wirst du bestraft für "+FindRussianMoneyString(int(pchar.questTemp.JailTemp1))+". Hab eine gute Zeit, Kapitän!";
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
			dialog.text = "Nun, deine Gefangenschaft ist vorbei. Ich hoffe, du hast etwas gelernt. Du bist jetzt frei. Nimm deine Habseligkeiten aus der Truhe in der Nähe des Offiziers. Und lass dich nicht wieder erwischen!";
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
