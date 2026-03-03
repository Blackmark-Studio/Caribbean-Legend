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
			dialog.text = "밀수품을 옮기고 판매하려다 붙잡혔소. 당국에 협조한 점과 그대의 신분을 고려하여, 감옥에서 보내게 될 시간은 단지 "+FindRussianDaysString(sti(pchar.questTemp.JailTemp2))+". 게다가, 밀수로 번 돈 전부 -"+FindRussianMoneyString(sti(pchar.questTemp.JailTemp1))+" 도시 금고로 옮겨질 거요. 즐거운 시간 보내시오, 선장!";
			link.l1 = "";
			link.l1.go = "Jail_officer_take_1";
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Jail");
			NextDiag.currentnode = "Jail_officer_free";
			break;
		}
		//<-- Сомнительное предложение
			dialog.text = "범죄를 저질러 구금되었으니, 감옥에 수감될 것이다\n "+FindRussianDaysString(sti(pchar.questTemp.JailTemp2))+". 게다가, 너는 ~로 인해 벌금을 물게 될 거야 "+FindRussianMoneyString(sti(pchar.questTemp.JailTemp1))+". 즐거운 시간 보내시오, 선장!";
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
			dialog.text = "자, 이제 감옥살이는 끝났어. 뭔가 배웠길 바란다. 이제 자유다. 장교 근처에 있는 상자에서 네 물건을 챙겨라. 그리고 다시는 내 눈에 띄지 마!";
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
