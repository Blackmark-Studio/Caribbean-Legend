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
			dialog.text = "Sei stato arrestato per aver tentato di trafficare e vendere merce di contrabbando. Considerando l'aiuto dato alle autorità e la tua posizione, passerai in prigione solo "+FindRussianDaysString(sti(pchar.questTemp.JailTemp2))+". Inoltre, tutto il denaro che hai guadagnato col contrabbando -"+FindRussianMoneyString(sti(pchar.questTemp.JailTemp1))+" verrà confiscato e messo nel tesoro della città. Divertiti pure, capitano!";
			link.l1 = "";
			link.l1.go = "Jail_officer_take_1";
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Jail");
			NextDiag.currentnode = "Jail_officer_free";
			break;
		}
		//<-- Сомнительное предложение
			dialog.text = "Sei stato arrestato per aver commesso un crimine, e verrai rinchiuso nella prigione per "+FindRussianDaysString(sti(pchar.questTemp.JailTemp2))+". Inoltre verrai multato per "+FindRussianMoneyString(sti(pchar.questTemp.JailTemp1))+"   Passa un buon tempo, capitano!";
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
			dialog.text = "Ebbene, la tua prigionia è finita. Spero tu abbia imparato qualcosa. Ora sei libero. Riprendi i tuoi averi dal baule vicino all’ufficiale. E non farti più beccare da me, canaglia!";
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
