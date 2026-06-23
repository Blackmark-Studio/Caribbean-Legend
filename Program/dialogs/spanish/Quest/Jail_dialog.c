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
			dialog.text = "Fuiste detenido por intentar transferir y vender un contrabando. Considerando tu ayuda a las autoridades y tu posición, pasarás en prisión solo "+FindRussianDaysString(int(pchar.questTemp.JailTemp2))+". Además, todo el dinero que has ganado con el contrabando -"+FindRussianMoneyString(int(pchar.questTemp.JailTemp1))+" será confiscado y puesto en el tesoro de la ciudad. ¡Que lo pases bien, capitán!";
			link.l1 = "";
			link.l1.go = "Jail_officer_take_1";
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Jail");
			NextDiag.currentnode = "Jail_officer_free";
			break;
		}
		//<-- Сомнительное предложение
			dialog.text = "Eras detenido por cometer un crimen, y serás retenido en la prisión por "+FindRussianDaysString(int(pchar.questTemp.JailTemp2))+" Además se le multará por "+FindRussianMoneyString(int(pchar.questTemp.JailTemp1))+"¡Que lo pase bien, capitán!";
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
			dialog.text = "Bueno, tu encarcelamiento ha terminado. Espero que hayas aprendido algo. Ahora eres libre. Toma tus pertenencias del cofre cerca del oficial. ¡Y no dejes que te atrape de nuevo!";
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
