// заместитель Маркуса Тиракса в Ла Веге
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
// ------------------------------------------блок angry-----------------------------------------------

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = NPCStringReactionRepeat("Do you have anything to tell me? No? Then get out of here!","I think I've made myself clear, stop annoying me.","Although I've made myself clear, you keep annoying me!","Right, I am getting tired of this rudeness.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I am leaving already.","Sure"+npchar.name+"...","Sorry, "+npchar.name+"...","Oops...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+", I am glad to see you! What do you want?","What else?"," You again? Don't bother people if you have nothing to do!","I know that you are a decent man. But I am done talking to you.","repeat",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Nothing. Just wanted to see you.","Nothing...","Alright, "+npchar.name+", sorry...","Damn it, it's all my fault...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Thievery?! Are you serious?! You're finished, pal...","Wait, what the hell? Turns out you're a thief! You're finished...");
			link.l1 = LinkRandPhrase("Shit!","Caramba!!","Damn it!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Go away","Get away ")+" from here!","Get out of my home!");
			link.l1 = "Oops...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Don't bother me with your cheap talk. Next time you won't like the result...";
        			link.l1 = "I got it.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = "It's over, no talking.";
			link.l1 = RandPhraseSimple("As you wish...","Fine then...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "I hope that you will show me more respect and stop being rude? Otherwise, I would have to kill you. That would be most unpleasant.";
        			link.l1 = ""+npchar.name+", you can be sure, I will.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Lavega_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ_1":
			dialog.text = "Ah, it's you, de Maure. Well, what a surprise. By the sea devil, your arrival is the most interesting thing to happen in a long time, damn it.";
			link.l1 = "Good to see you too, Vensan. Enjoying ruling the village?";
			link.l1.go = "PZ_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_2":
			dialog.text = "How could I? I'm a captain, a damn good one at that, not some bloody accountant. And I've been waiting for Marcus's messengers to summon me for a new voyage longer than I've waited for Christmas, bloody curses!";
			link.l1 = "Christmas and curses in one sentence, now that's something. Aye, I don't envy you. Though, many would love to be in your current position. But I've come to you on business, Vensan.";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "Business?! Well, spit it out then - have you thought of something? Got a good lead? I'm about to drain the local cellar out of sheer boredom with all these bloody calculations.";
			link.l1 = "Well, it's more that I have a question for you, nothing more.";
			link.l1.go = "PZ_4";
		break;
		
		case "PZ_4":
			dialog.text = "Damn it! Alright, I'm listening, Charles.";
			link.l1 = "Has a woman come to see you? Or perhaps you've seen her in La Vega? She goes by the name Belle Étoile, though that's just an alias, so she might have introduced herself under a different name. What's important is that she... she's yellow-skinned. But not a slave or a laborer - she's a wealthy woman.";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_5":
			dialog.text = "Yellow-skinned, but wealthy? We've never had anyone like that here, not ever! Seems you're still living that interesting life of yours, de Maure! I'm almost jealous.";
			link.l1 = "Is that so... Well, thanks for your time, Vensan. I won't keep you from your accounting any longer, heh-heh.";
			link.l1.go = "Exit";
			
			AddQuestRecord("PZ", "40");
			
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1 = "location";
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1.location = "Hispaniola1";
			pchar.quest.PZ_SetHeavyFrigate.win_condition = "PZ_SetHeavyFrigate";
			DelMapQuestMarkCity("LaVega");
			AddMapQuestMarkCity("PortPax", false);
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", true);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
		break;
	}
}
