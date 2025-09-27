// Эдвард Мэнсфилд, глава буканьеров и авторитетный пират, английская линейка
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
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
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================
	switch(Dialog.CurrentNode)
	{
		case "First time":
            NextDiag.TempNode = "First time";
            if (CheckAttribute(npchar, "Sp5LaVegaAttackDone"))
            {
            	if (NPChar.quest.meeting == "0")
				{
					dialog.Text = TimeGreeting()+"! I am "+GetFullName(NPChar)+", the new governor of this pit. It won't be easy to bring the local thugs to order, but they no longer pose a threat to the Spanish colonies.";
					Link.l1 = "I am glad to meet you. I'm Captain "+GetFullName(Pchar)+". Sorry, but I should go.";
					Link.l1.go = "exit";
					NPChar.quest.meeting = "1";
				}
				else
				{
					dialog.Text = TimeGreeting()+". I am busy, really busy, I need to keep the local thugs in check to prevent any threat to the Spanish colonies.";
					Link.l1 = "I won't bother you then.";
					Link.l1.go = "exit";
				}
            }
            else
            {
				dialog.text = NPCStringReactionRepeat("Do you have anything to tell me? No? Then "+GetSexPhrase("Get away from here!","I ask you not to disturb me.")+"","I think I've made myself clear...","Although I've made myself clear, you keep annoying me!","Well, you are beyond compare "+GetSexPhrase("too rude, mon chéri","such discourtesy, girl","such discourtesy, girl")+"...","repeat",30,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("I am leaving.","Yes, "+npchar.name+", I see that.","Sorry, "+npchar.name+"...","Ouch...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}


					if (npchar.city == sti(pchar.HeroParam.Location))
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "Do you have any work for me?";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
							{
								link.l2 = "I picked up the trail, but I need some coins — 30,000 pesos to lure the rat from his hole.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "Here, look at this letter I found on the smuggler's corpse";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "It's done. Norman Vigo and his ship belong to the sea devil.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "Hm... Work, you say? Actually, it's good that you've asked me. I need someone from outside. I want to find out something in the nearest town, but my men are known there. Can't promise you much, but you'll get something.";
			link.l1 = "What's the mission?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "Sorry, but I won't take the risk for a few scraps. Farewell.";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "Then listen, I made a deal to deliver 200 slaves a month ago with the captain of the schooner 'Saintblue'. I intended to sell them to the local plantation owner. The deadline has passed and the client has started to worry, but yesterday I was told that the schooner was seen not far from the island. But! The captain didn't show up. Today, my client demanded that I return his advance and said he was offered slaves from another seller. More expensive, but the whole lot of slaves at once.";
			link.l1 = "And? I have to find 200 slaves in a few days to save you from losing an advance? For a few coins?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "Of course not. Do I look like an idiot? I won't return him the advance anyway. But I need proof that the slaves he was offered are mine. Find those who offered him a new deal and you will get your 10,000 pesos. Deal?";
			link.l1 = "I'm in. Do you have any suspicions about who it could be?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "Not a chance. Look for someone else, only for 10,000? Sorry, but it won't work.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "If I had any ideas, I would never use your services. Those men would be dead already. But I am eager to know how they found out about the 'Saintblue's' cargo and my client. It seems it was quite easy for them. See now?";
			link.l1 = "Yes, someone has betrayed you.";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "Exactly! I am looking for him. Killing my competitors and returning my slaves are not your priorities. I need that rat—actually, his head on a skewer, to be honest. Now do you see why my men shouldn't know anything about your mission? I will suspect everyone until I find out who is selling the information. And I don't really want that...";
			link.l1 = "I see. Then I'll keep a low profile. I am on my way.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "Thirty thousand, you say? That's a large sum... I can only give you 5,000 pesos, that's all I have now. And don't even think about running off with the money, or I'll find you and hang you from the nearest fence! Got it?";
			link.l1 = "Fine, give me five thousand then...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "Take it. I am waiting for the result of your search.";
			link.l1 = "It will be fine.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "Ha! Excellent news! I was sure you'd make it. I've got some intriguing information.";
			link.l1 = "I've done my work and I want my ten thousand.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "Sure, here is your reward. But don't run away, I have one more assignment for you.\nPfaifer is a crewman of Norman Vigo, of the lugger 'Septima'. I am sure that Norman Vigo is the rat, even if he is one of us. He has recently been seen in the waters near the island. Your job is to send this rat to the sea devil. You didn't fail me the first time, so I want to ask you to handle this matter as well. I will pay you 15,000 pesos. Deal?";
			link.l1 = "I am on it! Consider the traitor dead.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "You know, I don't want to take part in it... I don't have time anyway. Sorry, but I'm off.";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "I know, I know. My men were watching the battle and have already reported to me about your flawless victory. Fine, you've done your job well. Here are 15,000 pesos, as I promised. And thank you, you have helped me a great deal.";
			link.l1 = "It's fine, I was glad to help! But I have to go now, I've been here too long and I've got a lot of things to do. Farewell!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;
				
 		case "No_Mansfield_first_time":
			dialog.text = "Greetings, my name is Alistair Good. I was elected head of the buccaneers after Mansfield's death.";
			link.l1 = "Nice to meet you, Alistair.";
			link.l1.go = "exit";
			NextDiag.TempNode = "No_Mansfield";
  		break;
 		case "No_Mansfield":
			dialog.text = "I have no time to talk to you. Visit me later.";
			link.l1 = "I am already leaving.";
			link.l1.go = "exit";
  		break;
		

// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Get","Get")+" out!","Get out of my house!");
			link.l1 = "Oops...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Мэнсфилдом через 30 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Don't bother me, remember that.";
        			link.l1 = "I got it.";
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
            DoReloadCharacterToLocation("LaVega_town","reload","reload6");
		break;
// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
