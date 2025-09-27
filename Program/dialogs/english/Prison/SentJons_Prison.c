// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Speak, I am listening";
			link.l1 = "I was mistaken. Farewell.";
			link.l1.go = "Exit";
			
			// --> Sinistra Длинные тени старых грехов
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaZalog"))
			{
				link.l1 = "Recently, one of the city's soldiers arrested and detained Charlie Knippel. Is he still here?"; 
				link.l1.go = "DTSG_AntiguaZalog_2";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов
		case "DTSG_AntiguaZalog_2":
			dialog.text = "That's right, but why do you ask?";
			link.l1 = "The thing is, Charlie is one of my officers. I'd like to know what he's accused of. The soldiers who took him didn't tell me anything."; 
			link.l1.go = "DTSG_AntiguaZalog_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaZalog_3":
			dialog.text = "Right. It's not common knowledge. Unfortunately, not even for you. It's a state secret, sir.";
			link.l1 = "So, I take it bail is not an option?"; 
			link.l1.go = "DTSG_AntiguaZalog_4";
		break;
		
		case "DTSG_AntiguaZalog_4":
			dialog.text = "Exactly. I understand it's unpleasant to lose a valuable crewman, but neither you nor I can do anything about it. I'm very sorry, Captain.";
			link.l1 = "No bail, I see. Then how about... compensation? A generous one, I might add. For you and all your men, so no one is left out."; 
			link.l1.go = "DTSG_AntiguaZalog_5";
		break;
		
		case "DTSG_AntiguaZalog_5":
			dialog.text = "A bribe? Bold of you, Captain, but no amount of money will save us from the wrath of those who find out we let Charlie go.";
			link.l1 = "Perhaps... But can I at least speak to him?"; 
			link.l1.go = "DTSG_AntiguaZalog_6";
		break;
		
		case "DTSG_AntiguaZalog_6":
			dialog.text = "Why not? You can't do anything to rescue him or help him escape, so... go ahead. He's in one of the cells.";
			link.l1 = "Ha, and if he tells me what he's accused of and reveals that state secret you're so concerned about, Officer?"; 
			link.l1.go = "DTSG_AntiguaZalog_7";
		break;
		
		case "DTSG_AntiguaZalog_7":
			dialog.text = "I'm not worried about that. You'll understand why. Go, talk to your former officer before I change my mind.";
			link.l1 = "Thank you."; 
			link.l1.go = "DTSG_AntiguaZalog_8";
		break;
		
		case "DTSG_AntiguaZalog_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaZalog");
			pchar.questTemp.jailCanMove = true;
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto9");
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Killer", "sold_eng_10", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Killer";
			LAi_SetStayType(sld);
			sld.talker = 5;
			GiveItem2Character(sld, "blade_14");
			EquipCharacterbyItem(sld, "blade_14");
			GiveItem2Character(sld, "pistol4");
			EquipCharacterbyItem(sld, "pistol4");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "reload", "reload12");
			sld.rank = 30;
			SetSelfSkill(sld, 80, 80, 80, 80, 80);
			LAi_SetHP(sld, 200+MOD_SKILL_ENEMY_RATE*20, 200+MOD_SKILL_ENEMY_RATE*20);
			LAi_SetImmortal(sld, true);
		break;
		
		case "DTSG_AntiguaTrevoga_2":
			dialog.text = "There's no need, Captain. As I said, you would have been thrown into the same cell as that fool Charlie. But first, the Governor appreciated that you didn't resist arrest, and second, he wasn't pleased with the recent visit from the moneylender, whose screams nearly shattered the windows in the palace...";
			link.l1 = "He asked for my arrest?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaTrevoga_3":
			dialog.text = "He didn't ask - he demanded. And His Excellency doesn't like being demanded anything. Therefore, that usurer was shown the door.";
			link.l1 = "Hilarious. Now..."; 
			link.l1.go = "DTSG_AntiguaTrevoga_4";
		break;
		
		case "DTSG_AntiguaTrevoga_4":
			dialog.text = "Now I suggest you do the same, Captain de Maure. And don't ask questions you won't get answers to.";
			link.l1 = "I won't leave here without Charlie Knippel."; 
			link.l1.go = "DTSG_AntiguaTrevoga_H1";
			link.l2 = "Please, sir, let me speak with Charlie Knippel. Or at least find out what..."; 
			link.l2.go = "DTSG_AntiguaTrevoga_Ch1";
		break;
		
		case "DTSG_AntiguaTrevoga_H1":
			dialog.text = "In that case, join him. Not in a cell, but in the afterlife.";
			link.l1 = "So, he's dead..."; 
			link.l1.go = "DTSG_AntiguaTrevoga_H2";
			ChangeCharacterComplexReputation(pchar, "authority", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_H2":
			dialog.text = "You're damn perceptive, Captain. And I hope you realize I won't tell you who did it or why.";
			link.l1 = "Is that so?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_H3";
		break;
		
		case "DTSG_AntiguaTrevoga_H3":
			dialog.text = "Exactly. And now don't test my patience – before I order you thrown in a cell for killing an English soldier.";
			link.l1 = "Considering not many get out of your cells, I wouldn't want to end up there. I won't wish you a good day."; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_Ch1":
			dialog.text = "Charlie Knippel will speak to no one. Except perhaps the Creator...";
			link.l1 = "He's dead?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_Ch2";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_Ch2":
			dialog.text = "The sentence has been carried out. I can't give you any details. And I hope you won't insist - it could end badly for you. Not just with a cell. Am I clear, Captain de Mor?";
			link.l1 = "Perfectly clear. Goodbye."; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaTrevoga");
			AddQuestRecord("DTSG", "10");
			CloseQuestHeader("DTSG");
			ChangeCharacterComplexReputation(pchar, "authority", -10);
			AddCrewMorale(Pchar, -30);
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
