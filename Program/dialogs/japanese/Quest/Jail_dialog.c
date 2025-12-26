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
			dialog.text = "お前は密輸品の移送と販売を企てたことで拘束された。\n当局への協力とお前の立場を考慮し、牢屋で過ごすのはわずか "+FindRussianDaysString(sti(pchar.questTemp.JailTemp2))+"。それに、お前が密輸で稼いだ金は――"+FindRussianMoneyString(sti(pchar.questTemp.JailTemp1))+" 町の財務庫に持っていかれることになるぜ。楽しんでくれ、船長！";
			link.l1 = "";
			link.l1.go = "Jail_officer_take_1";
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Jail");
			NextDiag.currentnode = "Jail_officer_free";
			break;
		}
		//<-- Сомнительное предложение
			dialog.text = "お前は罪を犯したため拘留され、これから牢屋に入れられることになる\n "+FindRussianDaysString(sti(pchar.questTemp.JailTemp2))+"。それに加えて、あなたには罰金が科せられるぞ "+FindRussianMoneyString(sti(pchar.questTemp.JailTemp1))+"。楽しい時間を過ごしてくれよ、船長！";
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
			dialog.text = "さて、お前の投獄は終わりだ。何か学んだだろうな。もう自由だ。将校のそばの箱から自分の持ち物を取っていけ。 二度と俺の前で捕まるんじゃねえぞ！";
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
