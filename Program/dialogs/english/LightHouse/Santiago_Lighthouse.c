// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want?","What would you like to know?"),"What is it you need, "+GetAddress_Form(NPChar)+"?","That's the third time you've tried to ask me...","I've had enough of you, get lost!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Sorry, I've changed my mind.","It's nothing, my apologies."),"I forgot, my apologies...","Third time's the charm, eh? Excuse me...","Sorry, sorry! I'll see myself out then...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak")
			{
				link.l1 = "Greetings. The inquisitor of Santiago, Padre Vincento, has mentioned you in his letter. He said you might help me.";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak_next")
			{
				link.l1 = "Any news from Padre Vincento? "+npchar.name+"?";
                link.l1.go = "guardoftruth_5";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && CheckCharacterItem(pchar, "jewelry33") && CheckCharacterItem(pchar, "jewelry34") && CheckCharacterItem(pchar, "jewelry35"))
			{
				link.l1 = "I need to see Padre Vincento. I have found the items he is interested in.";
                link.l1.go = "guardoftruth_7";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "inquisition")
			{
				link.l1 = "So, "+npchar.name+", what has Padre Vincento told you?";
                link.l1.go = "guardoftruth_11";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Sure, Señor. You must be a man of high renown if Padre Vincento himself does business with you.";
			link.l1 = "Splendid. You are our runner then. Now listen, this man is of great interest to Padre Vincento. He is under your responsibility now, you have to transfer him to Santiago or find someone who will.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "...";
			link.l1 = "You are responsible for the prisoner on behalf of the Inquisitor. I wouldn't advise you to remove his shackles, Gaius Marchais is a strong man. Give this letter to Padre Vincento and tell him that I await an answer from him in two days' time. This should be enough, I hope.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			Log_Info("You part with the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "Understood, Señor. I'll do the best I can. It's not the first time I'm helping the holy father.";
			link.l1 = "That's not all. The captain of the carraca, San Gregorio, Carlos Guevara must have been here. He brought vanilla for me. Has he given you my letter?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Yes, your cargo is fine and waiting for you, Señor.";
			link.l1 = "Good, I'll have it hauled onto my ship then. I'll be here for two days waiting for Padre Vincento's answer. This is not goodbye for now, "+npchar.name+"!";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			LocatorReloadEnterDisable("mayak9", "boat", false);
			ref sld = characterFromId("GOT_Marshe");
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakNextStage", 0, 0, 2, false);
			SetCharacterGoods(pchar, GOOD_CINNAMON, GetCargoGoods(pchar, GOOD_CINNAMON) + sti(pchar.questTemp.Guardoftruth.VanilleQty));
			AddQuestRecord("Guardoftruth", "21");
		break;
		
		case "guardoftruth_5":
			dialog.text = "Yes, Señor. Here is a letter from Padre Vincento. He is very pleased with you, the rest you'll learn from the letter.";
			link.l1 = "Splendid. Until then, "+npchar.name+". And for now - farewell.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_exit";
			GiveItem2Character(pchar, "specialletter");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_next";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Very well. Give them to me and I will take them to the Holy Father.";
			link.l1 = "No way, chap! It wasn't easy to get those and I won't hand them over just like that. I will only give them to Padre Vincento personally.";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "But señor! How can I know that you are not swindling me?";
			link.l1 = "Take a look: the censer, the chalice, and the cross with the lazurite... "+npchar.name+", who do you think I am? Do you really think I'm foolish enough to go to the Inquisition without them?";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Forgive me, señor... Come tomorrow and I'll tell Padre Vincento about your arrival.";
			link.l1 = "Good. See you tomorrow.";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakLastStage", 0, 0, 1, false);
		break;
		
		case "guardoftruth_11":
			dialog.text = "His Grace will receive you, Señor. Don't delay your visit. Here is the document, show it to the guards and they will let you in. But raise a Spanish flag first or the soldiers will likely arrest you.";
			link.l1 = "Got it. Spanish then. Thanks, pal! I'm on my way!";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper");
			pchar.questTemp.Guardoftruth = "santiago";
			AddQuestRecord("Guardoftruth", "34");
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 400);//скрытность
			GuardOT_SetPadreVincento();
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
