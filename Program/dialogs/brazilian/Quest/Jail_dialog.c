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
			dialog.text = "Você foi detido por tentar transferir e vender contrabando. Considerando sua colaboração com as autoridades e sua posição, você passará na prisão apenas "+FindRussianDaysString(sti(pchar.questTemp.JailTemp2))+". Além disso, todo o dinheiro que você ganhou contrabandeando -"+FindRussianMoneyString(sti(pchar.questTemp.JailTemp1))+" será levado e colocado no tesouro da cidade. Aproveite, capitão!";
			link.l1 = "";
			link.l1.go = "Jail_officer_take_1";
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Jail");
			NextDiag.currentnode = "Jail_officer_free";
			break;
		}
		//<-- Сомнительное предложение
			dialog.text = "Você foi detido por cometer um crime, e ficará preso por "+FindRussianDaysString(sti(pchar.questTemp.JailTemp2))+". Além disso, você será multado por "+FindRussianMoneyString(sti(pchar.questTemp.JailTemp1))+". Tenha um bom momento, capitão!";
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
			dialog.text = "Bem, sua prisão acabou. Espero que tenha aprendido alguma coisa. Agora você está livre. Pegue seus pertences no baú perto do oficial. E não me faça te pegar de novo!";
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
