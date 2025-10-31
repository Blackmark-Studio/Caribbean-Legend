void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "This is a bug. Let the devs know.";
			link.l1 = "Sure!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Wine_fort":
			dialog.text = "Did you bring the bottle?";
			if (CheckCharacterItem(pchar, "potionwine"))
			{
				link.l1 = "Aye, that I did. I paid 700 pesos for it, so I expect 1,000 pesos from you.";
				link.l1.go = "Wine_fort_1";
			}
			link.l2 = "No, I'm working on it.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort";
		break;
	
		case "Wine_fort_1":
			AddMoneyToCharacter(pchar, 1000);
			RemoveItems(PChar, "potionwine", 1);
			dialog.text = "God be praised, I was getting parched. Thank you kindly, sir! Here, take your thousand and I'll take your bottle, haha! Hey now, since we're already doing fine business here, I have another request for you\nCould you get more wine for me and my friends for our... future use? We just shook down a band of smugglers, so we have coins to spare, hehe...";
			link.l1 = "Sorry, mate, I don't have time to make another booze run for you.";
			link.l1.go = "Wine_fort_exit";
			link.l2 = "Money is always welcome. How many bottles do you need?";
			link.l2.go = "Wine_fort_2";
		break;
	
	case "Wine_fort_exit":
			DelLandQuestMark(npchar);
			WineTraderQMDel();
			dialog.text = "As you wish. Thank you for your help, anyway! Cheers, and to your good health!";
			link.l1 = "Keep up the good work, soldier!";
			link.l1.go = "exit";
			sld = characterFromId(pchar.questTemp.Wine.id);	
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			pchar.questTemp.Wine.fail = "true";
			CloseQuestHeader("Wine");
	break;
	
		case "Wine_fort_2":
			dialog.text = "At 1000 pieces of eight per bottle, we can afford to buy sixty bottles, but no more. But don't bring us less than ten either - that'll just make us thirsty!";
			link.l1 = "Understood, no more than 60 bottles and no fewer than ten. I'll bring your wine.";
			link.l1.go = "Wine_fort_3";
		break;
	
		case "Wine_fort_3":
			dialog.text = "Blessed are the feet that carry glad tidings of good drink! I am counting on you, captain. Ah, I almost forgot! You'll need to get the booze here in less than a week, because my marine company is being rotated out to the fleet in seven days' time and we'll be gone for a couple of months once we leave.";
			link.l1 = "I see. I'll try to be quick.";
			link.l1.go = "exit";
			pchar.questTemp.Wine.bottles = "true";
			npchar.lifeday = 7;
			AddQuestRecord("Wine", "1");
			AddQuestUserData("Wine", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Wine.City+"Gen"));
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.SName);
			SetFunctionTimerCondition("Soldier_wait", 0, 0, 7, false);
			NextDiag.TempNode = "Wine_fort_check";
			SetFunctionLocationCondition("WineTraderQM", pchar.questTemp.Wine.City+"_town", 0);
		break;
	
		case "Wine_fort_check":
			dialog.text = "So, captain, have you brought the wine?";
			if (sti(pchar.items.potionwine) >= 10)
			{
				link.l1 = "Yes, I have.";
				link.l1.go = "Wine_take";
			}
			link.l2 = "No. I am still working on it.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort_check";
		break;
	
		case "Wine_take":
			pchar.questTemp.Wine.Qty = sti(pchar.items.potionwine);
			pchar.questTemp.Wine.Money = sti(pchar.questTemp.Wine.Qty)*1000;
			if (sti(pchar.items.potionwine) > 60)
			{
				dialog.text = "Holy Saint Arnulf, pray for us! That's a lot of wine! Excellent! Regrettably, as I said, we can only afford sixty bottles; unfortunately, we don't have enough money to buy more. Take your pesos and I'll take good care of these sixty bottles. Please keep the rest.";
				link.l1 = "Thank you. Be sure that you and your soldier friends raise a glass to my health!";
				link.l1.go = "Wine_take_1";
				pchar.questTemp.Wine.Money = 60000;
				RemoveItems(PChar, "potionwine", 60);
			}
			else
			{
				dialog.text = "Welcome back. Let's see... You have brought "+sti(pchar.questTemp.Wine.Qty)+" bottles. Nice! I'll take them. The payment is "+FindRussianMoneyString(sti(pchar.questTemp.Wine.Money))".";
				link.l1 = "Thank you. Be sure that you and your soldier friends raise a glass to my health!";
				link.l1.go = "Wine_take_1";
				RemoveItems(PChar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			}
		break;
	
		case "Wine_take_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.Wine.Money));
			dialog.text = "We certainly will, "+GetAddress_Form(NPChar)+"! The drum is sounding the assembly, I have to go now. Goodbye!";
			link.l1 = "Fair winds and following seas, mate!";
			link.l1.go = "Wine_take_2";
		break;
	
		case "Wine_take_2":
			DelLandQuestMark(npchar);
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info ("You handed over the wine");
			pchar.quest.Soldier_wait.over = "yes";//снять прерывание
			DeleteAttribute(pchar, "questTemp.Wine.City");
			sld = characterFromId(pchar.questTemp.Wine.id);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
