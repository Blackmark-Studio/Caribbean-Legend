// Юрген Шмидт - оружейник
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iRem;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "Listen, mister, why did you start a fight, huh? You have no business in my workshop unless you are our enemy. Get out!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"! I have heard of your deeds. It is good that you have become a friend of Donald and our ally. Narwhals know how to value friendship, I can tell you that for sure.";
					link.l1 = "I hope so. Can I count on your services now?";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "So? What do you want?";
					link.l1 = TimeGreeting()+". My name is "+GetFullName(pchar)+". And I am just walking around, getting to know people. Am I bothering you?";
				link.l1.go = "meeting";
				}
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"! I have heard about your deeds. It is good that you have become Donald's friend and our ally. Narwhals appreciate friendship, I can tell you that for sure.";
					link.l1 = "I hope so. Can I count on your services now?";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"! Want to talk again? I have to disappoint you, I have neither the time nor the desire for that.";
					link.l1 = "Fine, I won't bother you.";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Exactly! You are bothering me, mister. I am Jurgen Schmidt, gunsmith and blacksmith of the Narwhal clan. I provide our people with weapons. But it takes time to make a good blade, key, lock, or to repair the mechanism of a tower musket. It takes a lot of time, patience, and attention. That is why I don't like it when people bother me.";
			link.l1 = "Do you make weapons? Can I order something from you?";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "No. I make weapons only for members of the Narwhal clan. This is my principle and I will keep it. So don't even hope, mister. Join our clan or at least become our ally, and in that case we will have a talk.";
			link.l1 = "Fine. I'm leaving you then. Sorry for troubling you!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "friend":
			dialog.text = "You can. A friend of Narwhal is my friend too, so I am listening to you.";
			link.l1 = "I'd like to order a blade.";
			link.l1.go = "blade";
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l2 = "I've heard that you made a special blade for the late Alan Milrow. I've seen that broadsword; it's a fine weapon. Can I order something like that?";
				link.l2.go = "narval";
			}
			link.l3 = "I have no ideas yet. I'll think about it and then I'll be back!";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "Jurgen":
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Ha, "+GetFullName(pchar)+"! So you haven't drowned? Isn't that something! Are you truly alive?";
				link.l1 = "Don't worry, Jurgen. I'm alive! I wasn't about to drown...";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				NextDiag.TempNode = "Jurgen";
				break;
			}
			dialog.text = "Ah, "+GetFullName(pchar)+"! What do you want?";
			if (CheckAttribute(npchar, "quest.narval_blade") && npchar.quest.narval_blade == "ferrum")
			{
				if (GetCharacterItem(pchar, "jewelry11") >= 3)
				{
					link.l4 = "I have brought your three pieces of special iron as you asked. Take a look, is it what you wanted?";
					link.l4.go = "narval_7";
				}
				if (CheckCharacterItem(pchar, "meteorite"))
				{
					link.l5 = "Take a look, Jurgen. I found an interesting iron ingot at the bottom, but it weighs much more than you asked. Five pounds at least.";
					link.l5.go = "narval_7_1";
				}
			}
			if (!CheckAttribute(npchar, "quest.blade_done"))
			{
				link.l1 = "I'd like to order a blade.";
				if (!CheckAttribute(npchar, "quest.blade_rules")) link.l1.go = "blade";
				else link.l1.go = "blade_4";
			}
			if (CheckAttribute(npchar, "quest.blade_payseek"))
			{
				link.l1 = "I have brought you more doubloons as payment for the blade.";
				link.l1.go = "blade_3";
			}
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive" && npchar.quest.narval_blade == "begin" && pchar.questTemp.LSC != "return") // patch-9
			{
				link.l2 = "I've heard that you made a special blade for the late Alan Milrow. I've seen that broadsword, it's a fine weapon. Can I order something like that?";
				link.l2.go = "narval";
			}
			if (CheckAttribute(npchar, "blade_date") && GetNpcQuestPastDayParam(npchar, "blade_date") >= 20)
			{
				link.l1 = "I am here for my order. It must be finished already, am I right?";
				link.l1.go = "blade_done_2";
			}
			link.l3 = "No, it's nothing, I just wanted to greet you.";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		// --> заказ клинков
		case "blade":
			dialog.text = "Fine. But I have some special requirements for any order, so listen carefully first.";
			link.l1 = "I am all ears.";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "You may order only one blade from me, and only once. I don't make specific weapons; you may name only the type - rapier, saber, or broadsword. Think carefully before you make your choice; the final characteristics and quality of the blade will depend on the materials I have at the moment\nNow. It will take twenty days to craft your order. I accept only doubloons. One thousand coins. Payment upfront.";
			link.l1 = "Really! Expensive...";
			link.l1.go = "blade_2";
		break;
		
		case "blade_2":
			dialog.text = "It is pricey. But I make excellent blades, so the price is fair enough. It's your call anyway, no pressure.";
			link.l1 = "I understand, Jurgen. Yes, I would like to place an order.";
			link.l1.go = "blade_3";
			link.l2 = "Hm. I need some time to think before ordering anything from you. We'll talk about it later!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
			npchar.quest.blade_rules = "true";
			npchar.quest.blade_dublon = 1000;
			AddQuestRecord("LSC", "17");
		break;
		
		case "blade_3":
			dialog.text = "Very well. Give me your doubloons, then.";
			if (PCharDublonsTotal() > 0)
			{
				npchar.quest.blade_pay = PCharDublonsTotal();
				link.l1 = "Here, please. I have "+FindRussianQtyString(sti(npchar.quest.blade_pay))+".";
				link.l1.go = "blade_pay";
			}
			link.l2 = "Hm. Unfortunately, I don't have any with me right now. But I will bring them to you for sure, and we will continue our talk.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "blade_4":
			dialog.text = "So is this your final choice? Are you sure?";
			link.l1 = "Yes, I am.";
			link.l1.go = "blade_3";
		break;
		
		case "blade_pay": // оплата
			if (sti(npchar.quest.blade_dublon) < sti(npchar.quest.blade_pay)) // полная сумма
			{
				npchar.quest.blade_pay = sti(npchar.quest.blade_dublon);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.blade_dublon)-sti(npchar.quest.blade_pay);
			npchar.quest.blade_dublon = iTemp; // запоминаем остаток
			RemoveDublonsFromPCharTotal(sti(npchar.quest.blade_pay));
			Log_Info("You have given "+sti(npchar.quest.blade_pay)+" doubloons");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "Splendid. You have paid me for my work and materials, so I can start now.";
				link.l1 = "May I place an order?";
				link.l1.go = "blade_done";
			}
			else
			{
				dialog.text = "Fine. I accept your doubloons. You have to bring me "+FindRussianQtyString(sti(npchar.quest.blade_dublon))+" more.";
				link.l1 = "I will bring them to you when I have them.";
				link.l1.go = "exit";
				npchar.quest.blade_payseek = "true";
			}
		break;
		
		case "blade_done":
			DeleteAttribute(npchar, "quest.blade_payseek");
			dialog.text = "Sure! Which type do you prefer? Rapiers, sabres, or broadswords?";
			link.l1 = "Rapiers. I like elegant, light weapons.";
			link.l1.go = "rapier";
			link.l2 = "Sabres. In my opinion, they are optimal.";
			link.l2.go = "sabre";
			link.l3 = "Broadswords for sure! Cut and chop!";
			link.l3.go = "palash";
		break;
		
		case "rapier":
			npchar.quest.blade_done = SelectJurgenBladeDone("rapier");
			dialog.text = "As you wish. Come back for your order in twenty days, no sooner.";
			link.l1 = "Thank you! I'll see you in twenty days. Goodbye, Jurgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "sabre":
			npchar.quest.blade_done = SelectJurgenBladeDone("sabre");
			dialog.text = "As you wish. Come back for your order in twenty days, no sooner.";
			link.l1 = "Thank you! I'll see you in twenty days. Goodbye, Jurgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "palash":
			npchar.quest.blade_done = SelectJurgenBladeDone("palash");
			dialog.text = "As you wish. Come back for your order in twenty days, no sooner.";
			link.l1 = "Thank you! I'll see you in twenty days. Goodbye, Jurgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "blade_done_1":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "blade_date");
			NextDiag.CurrentNode = "Jurgen";
			AddQuestRecord("LSC", "18");
		break;
		
		case "blade_done_2":
			dialog.text = "Yes. Your blade is ready. Please, take it and use it. You will understand that it is worth its price as soon as you touch it.";
			link.l1 = "Thanks, Jurgen.";
			link.l1.go = "blade_done_3";
		break;
		
		case "blade_done_3":
			DialogExit();
			NextDiag.CurrentNode = "Jurgen";
			GiveItem2Character(pchar, npchar.quest.blade_done);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "blade_date");
		break;
		
		// заказ палаша Нарвал для Мэри
		case "narval":
			dialog.text = "Alas, my friend, I have to refuse, for two reasons. First, I will make such a broadsword only for a member of the Narwhal clan, and only for someone special. Secondly, I don't have the materials for it.";
			link.l1 = "And what is this special iron you need? I've heard they got it from the bottom...";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "Exactly. There are pieces of this metal scattered all around our shoal. I don't know how they got there. But the iron is unique, it never turns rusty and the blades made from it never grow blunt. So if you manage to get the iron then we might solve the matter. But there is still a problem, you are not Narwhal...";
			link.l1 = "Hm. Does it really matter?";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "Yes. You may consider that my whim, but I will make such a broadsword only for Narwhal.";
			link.l1 = "Well... Fine, I accept that. But I have an idea. Can I order this blade for a member of the Narwhal clan?";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "Hm. I suppose you can, if you bring me the iron. It won't violate my principles... And for whom do you want me to make the broadsword?";
			link.l1 = "For Red Mary. She is from the Narwhal clan and she deserves to own such an excellent weapon.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "Ha! I could have figured that out myself. I am getting too old... Well, I agree. Mary will be truly happy to receive such a gift, I am sure... Bring me the iron and I will make the broadsword. I will take for the blade... ah, whatever, I will make it for free. It will be a present not only from you, but from both of us.";
			link.l1 = "Thanks! How much iron do you need?";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "Those pieces we've been finding at the bottom were all the same - a pound each. I need three pieces like them.";
			link.l1 = "Fine. I will try to find them. And we will talk again.";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			DialogExit();
			npchar.quest.narval_blade = "ferrum";
			NextDiag.CurrentNode = "Jurgen";
			// кладем гигантский кусок метеорита на дно
			sld = ItemsFromID("meteorite");
			sld.shown = true;
			sld.startLocation = "underwater";
			sld.startLocator = "item"+(rand(7)+1);
			Log_TestInfo("Meteorite in the locator " + sld.startLocator);
			pchar.quest.LSC_narval_ferrum.win_condition.l1 = "item";
			pchar.quest.LSC_narval_ferrum.win_condition.l1.item = "meteorite";
			pchar.quest.LSC_narval_ferrum.function = "LSC_NarvalFerrum";
			AddQuestRecord("LSC", "19");
		break;
		
		case "narval_7":
			RemoveItems(pchar, "jewelry11", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "Let me see... Yes, it is! Was it difficult to find such small pieces at the bottom?";
			link.l1 = "Well, what can I say... Mary is worth such trouble, isn't she?";
			link.l1.go = "narval_8";
			pchar.quest.LSC_narval_ferrum.over = "yes"; //снять прерывание
		break;
		
		case "narval_7_1":
			RemoveItems(pchar, "meteorite", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Let me see... Isn't that something! Yes, it is bottom iron, but I have never seen such large pieces before. This one will be enough to make the broadsword. Was it difficult to find?";
			link.l1 = "Well, what can I say... Mary is worth such trouble, isn't she?";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			dialog.text = "I like you more and more, "+pchar.name+"... Very well then. Now it's my turn to work on behalf of our beautiful Amazon. It will take two days to make the broadsword, I'll put aside other orders\nBring Mary to me the day after tomorrow. Don't tell her, it's a surprise. She'll be as happy as a child.";
			link.l1 = "Fine, Jurgen. Deal! See you the day after tomorrow!";
			link.l1.go = "narval_9";
		break;
		
		case "narval_9":
			DialogExit();
			npchar.quest.narval_blade = "work";
			NextDiag.CurrentNode = "narval_10";
			SetFunctionTimerCondition("LSC_NarvalBladeForMary", 0, 0, 2, false); // таймер
			AddQuestRecord("LSC", "21");
		break;
		
		case "narval_10":
			dialog.text = ""+pchar.name+", don't bother me. You want me to finish the broadsword on time, don't you?";
			link.l1 = "Yes, sure. I am leaving.";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_10";
		break;
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("What are you doing there, eh? Thief!","Just look at that! The moment I lost myself in contemplation, you decided to check my chest!","Decided to check my chests? You won't get away with it!");
			link.l1 = "Damn it!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Listen, you'd better put your weapon away. It makes me nervous.","You know, running around with a blade is not tolerated here. Put it away.","Listen, don't act like a medieval knight running around with a sword. Put it away, it doesn't suit you...");
			link.l1 = LinkRandPhrase("Fine.","Fine.","As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Listen, I am a citizen of this city and I'd ask you to lower your blade.","Listen, I am a citizen of this city and I'd ask you to lower your blade.");
				link.l1 = LinkRandPhrase("Fine.","Fine.","As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Be careful, mate, running around with a weapon. You might make me nervous...","I don't like it when men walk in front of me with their weapons drawn. It scares me...");
				link.l1 = RandPhraseSimple("Got it.","I am taking it away.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string SelectJurgenBladeDone(string _sType)
{
	string sBlade;
	switch (_sType)
	{
		case "rapier":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_18"; 
			else sBlade = "q_blade_16";
		break;
		
		case "sabre":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_19"; 
			else sBlade = "q_blade_10";
		break;
		
		case "palash":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_21"; 
			else sBlade = "q_blade_13";
		break;
	}
	return sBlade;
}
