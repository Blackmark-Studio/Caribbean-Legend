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
			dialog.text = "Vous avez été détenu pour avoir tenté de transférer et de vendre de la contrebande. Compte tenu de votre aide aux autorités et de votre position, vous ne passerez en prison que "+FindRussianDaysString(int(pchar.questTemp.JailTemp2))+".  D'ailleurs, tout l'argent que tu as gagné en faisant de la contrebande -"+FindRussianMoneyString(int(pchar.questTemp.JailTemp1))+" sera confisqué et mis dans le trésor de la ville. Passez un bon moment, capitaine !";
			link.l1 = "";
			link.l1.go = "Jail_officer_take_1";
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Jail");
			NextDiag.currentnode = "Jail_officer_free";
			break;
		}
		//<-- Сомнительное предложение
			dialog.text = "Vous avez été détenu pour avoir commis un crime, et vous serez retenu dans la prison pour "+FindRussianDaysString(int(pchar.questTemp.JailTemp2))+". De plus, vous serez amendé pour "+FindRussianMoneyString(int(pchar.questTemp.JailTemp1))+" Passez un bon moment, capitaine !";
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
			dialog.text = "Eh bien, votre emprisonnement est terminé. J'espère que vous avez appris quelque chose. Vous êtes libre maintenant. Prenez vos affaires dans le coffre près de l'officier. Et ne me laissez pas vous attraper à nouveau !";
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
