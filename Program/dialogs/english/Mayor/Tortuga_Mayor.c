// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want? Ask away.","I'm listening, what's the question?"),"This is the second time you've tried to ask...","This is the third time you have tried to ask...","When is this going to end?! I am a busy man, working on colonial matters and you are still bothering me!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind, sorry.","Not now. Wrong place and time."),"True, I have nothing to say right now, sorry.","I'll ask later.","I am sorry, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "huber")
			{
				link.l1 = "Monsieur Governor, I have terrible news for you. I'll be brief: your wife wants to rob you. She tried to persuade me to pick the lock on one of your cabinet chests. I thought you should know about this.";
                link.l1.go = "FMQT";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
			{
				link.l1 = TimeGreeting()+", Monsieur. I am here as ordered by Governor-General Chevalier de Poincy. My task is to deliver a baron by the name of Noel Forget to Tortuga, who has arrived from the mother country with orders to inspect the colonies. His main purpose is to establish a French West Indies Trading Company. Allow me to introduce him to you... He will explain all the details himself.";
                link.l1.go = "patria_tortuga";
			}
		break;
		
		case "FMQT":
			dialog.text = "Wh-a-at? Again? That bitch! She'll regret this, oh I swear! Kampacho will make her scream. Why are you still here? Get the hell out of here!";
			link.l1 = "I thought...";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 25) link.l1.go = "FMQT_2";
			else link.l1.go = "FMQT_1";
		break;
		
		case "FMQT_1":
			Notification_Skill(false, 26, SKILL_LEADERSHIP);
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "Always the same! Here, take this! It's all I have on the table! Now get out!";
			link.l1 = "Thank you, your Excellency. I'll see myself out.";
			link.l1.go = "FMQT_3";
		break;
		
		case "FMQT_2":
			AddMoneyToCharacter(pchar, 1000);
			GiveItem2Character(pchar, "pistol6");
			GiveItem2Character(pchar, "purse1");
			Log_Info("You have received a double barreled pistol and a purse of doubloons");
			dialog.text = "Always the same! Here, take this! It's all I have on the table!.. Though, fine, you don't look like the rest of the morons and losers my island is filled with. Take a bit extra... Now get out!";
			link.l1 = "Thank you, your Excellency. I'll see myself out.";
			link.l1.go = "FMQT_3";
		break;
		
		case "FMQT_3":
			DialogExit();
			pchar.quest.FMQT_late1.over = "yes";
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.questTemp.FMQT = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Tortuga", "7");
			CloseQuestHeader("FMQ_Tortuga");
			FMQT_ClearChest();
		break;
		
		// Jason НСО
		case "patria_tortuga":
			dialog.text = "Fine, Captain Charles de Maure. The baron will be treated accordingly and I will do what I can to help him with his task.";
			link.l1 = "";
			link.l1.go = "patria_tortuga_1";
		break;
		
		case "patria_tortuga_1":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_5";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			npchar.quest.patria = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
