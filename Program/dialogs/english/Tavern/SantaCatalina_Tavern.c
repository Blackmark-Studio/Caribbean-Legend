// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			if(startHeroType == 4)
			{
				dialog.text = NPCStringReactionRepeat("Of course, Helen. What is it?","Ah, finally remembered what you wanted?","Are you sure you are all right? You're starting to worry me. Maybe you should see a physician? ","Alright, Helen. Get some sleep, get some fresh air – in short, take a break. Then come back. Mhm?","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("No, nothing really.","No, no, sorry to trouble you.","You're probably right...","Yes, you're probably right. That's the best thing to do.",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?","How can I help you, "+GetAddress_Form(NPChar)+"?"),"You tried to ask me a question not long ago, "+GetAddress_Form(NPChar)+"...","Over the course of this whole day, this is the third time you've brought up that question...","More questions, I presume?","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...","I've got nothing to talk about at the moment."),"Umph, where has my memory gone...","Yes, it really is the third time...","No, what questions?...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				link.l1 = "Listen, "+npchar.name+", who is Jan Svenson, and how can I find him?";
                link.l1.go = "Svenson";
			}	
			//<-- Бремя гасконца
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Listen, has an alchemist arrived in this town, a physician? He's Italian, about thirty years old, his name is Gino Gvineili. Have you heard anything about him?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "Svenson":
			dialog.text = "This is the first time I've met a man who doesn't know who the Forest Devil is. That nickname was given to him by the Spanish, and they offered a whole bag of gold for the head of that privateer from Providence Island, way back fifteen years ago! Yes, the years fly by... People have already begun to forget about our Jan. Maybe it truly is time for him to have a rest.";
			link.l1 = "I've only just arrived here and I don't know much...";
			link.l1.go = "Svenson_1";			
		break;
		
		case "Svenson_1":
			dialog.text = "If you're interested in the past, I can sell you a history book. Many would pay a fortune for it, but I...";
			link.l2 = "Don't give me the runaround! I asked you a question. I'll repeat: where does Jan Svenson live? I have a serious matter to discuss with him.";
			link.l2.go = "Svenson_2";
		break;
		
		case "Svenson_2":
			dialog.text = "He lives in a mansion across from the residence of our mayor, next to the fountain. But at the moment he's going through some hard times and I wouldn't recommend bothering him unless it's of the utmost importance.";
			link.l1 = "Why's that?";
			link.l1.go = "Svenson_3";			
		break;
		
		case "Svenson_3":
			dialog.text = "His favourite girl Helen, also known as Rumba, the daughter of his late old friend Shawn McArthur, has disappeared. Rest in peace, old man... Jan treats the young devil as his own daughter, since he has no children of his own. But the girl has vanished along with her schooner 'Rainbow' and the whole crew\nI feel bad for the girl. A rare beauty, clever too. Hot and feisty as fire, that's why they called her Rumba! Her father taught her everything he knew, she inherited the ship and every single crewman stayed by her side. Even the oldest sea wolves recognised her as a captain...";
			link.l1 = "A lady pirate? What could have happened to her?";
			link.l1.go = "Svenson_4";			
		break;
		
		case "Svenson_4":
			dialog.text = "Who knows... A week is not that long, but MacArthur's widow is certain that something has happened to her daughter, and she managed to convince Svenson of it. He called out his men and began searching himself, but so far with no result. 'Rainbow' and her crew just vanished\nI can tell you where to find Gladys for a thousand pieces of eight.";
			if (sti(pchar.money) >= 1000)
			{
				link.l1 = "Your knowledge is quite costly, but you've piqued my interest. Here's your money. Where do I find her?";
				link.l1.go = "Svenson_5";
			}
			else
			{
				link.l1 = "Don't. I'll handle it myself if I need to. Bye, thanks for the story!";
				link.l1.go = "Svenson_6";
			}		
		break;
		
		case "Svenson_5":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Her home is next to the pier, to the left of the mooring. But she's probably not there. She spends all day hanging around the fort's walls, watching out for her beloved daughter. She must've cried her eyes out already.";
			link.l1 = "Thanks for the story! Goodbye, mate!";
			link.l1.go = "Svenson_6";			
		break;
		
		case "Svenson_6"://устанавливаем Глэдис на форт
			DialogExit();
			ref sld = characterFromId("Gladis");
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl_8";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("JS_girl"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("No, I haven't. We have herbalists and physicians, but none with a name like that.","This is the first time I've heard such a strange name. No, we've never had a visit from the man you speak of.","We don't even have any alchemists here at all. We've got physicians, but none with a strange name like that.");
			link.l1 = "I see. That's a pity. I'll keep searching!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
