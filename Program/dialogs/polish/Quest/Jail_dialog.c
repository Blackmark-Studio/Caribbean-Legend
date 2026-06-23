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
			dialog.text = "Zostałeś zatrzymany za próbę przewozu i sprzedaży kontrabandy. Biorąc pod uwagę twoją pomoc dla władz i twoją pozycję, spędzisz w więzieniu tylko "+FindRussianDaysString(int(pchar.questTemp.JailTemp2))+". Poza tym, wszystkie pieniądze, które zarobiłeś na przemycie -"+FindRussianMoneyString(int(pchar.questTemp.JailTemp1))+" zostaną zabrane i umieszczone w miejskim skarbcu. Baw się dobrze, kapitanie!";
			link.l1 = "";
			link.l1.go = "Jail_officer_take_1";
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Jail");
			NextDiag.currentnode = "Jail_officer_free";
			break;
		}
		//<-- Сомнительное предложение
			dialog.text = "Zostałeś zatrzymany za popełnienie przestępstwa i będziesz przetrzymywany w więzieniu przez "+FindRussianDaysString(int(pchar.questTemp.JailTemp2))+" Poza tym zostaniesz ukarany grzywną za "+FindRussianMoneyString(int(pchar.questTemp.JailTemp1))+"Miłego czasu, kapitanie!";
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
			dialog.text = "Cóż, twoje uwięzienie dobiegło końca. Mam nadzieję, że czegoś się nauczyłeś. Jesteś teraz wolny. Weź swoje rzeczy z skrzyni obok oficera. I nie daj mi się znowu złapać!";
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
