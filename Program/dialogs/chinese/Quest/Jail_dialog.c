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
		//--> 可疑的提议
		if (CheckAttribute(pchar, "GenQuest.Contraoffer.Jail"))
		{
			dialog.text = "你因试图转运和出售违禁品而被拘留。 鉴于你对当局的帮助和你的身份, 你将只在监狱里待" + FindRussianDaysString(sti(pchar.questTemp.JailTemp2)) + "。 此外, 你通过走私赚的所有钱 - " + FindRussianMoneyString(sti(pchar.questTemp.JailTemp1)) + " 将被没收并归入城镇国库。 祝你过得愉快, 船长! ";
			link.l1 = "";
			link.l1.go = "Jail_officer_take_1";
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Jail");
			NextDiag.currentnode = "Jail_officer_free";
			break;
		}
		//<—— 可疑的提议
			dialog.text = "你因犯罪被拘留, 将在监狱里关押" + FindRussianDaysString(sti(pchar.questTemp.JailTemp2)) + "。 此外, 你将被罚款" + FindRussianMoneyString(sti(pchar.questTemp.JailTemp1)) + "。 祝你愉快, 船长! ";
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
			dialog.text = "好了, 你的监禁期结束了。 我希望你学到了一些东西。 你现在自由了。 从军官附近的箱子里拿走你的物品。 别让我再抓到你! ";
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