// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?","How can I help you, "+GetAddress_Form(NPChar)+"?"),"You tried to ask me a question not long ago, "+GetAddress_Form(NPChar)+"...","Throughout this whole day, this is the third time you've brought up this question...","More questions, I presume?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...","I've got nothing to talk about at the moment."),"Umph, where has my memory gone...","Yes, it really is the third time...","No, what questions?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin" && sti(pchar.money) >= 3000)
			{
				link.l1 = "I've heard that consumption is running rampant in your fort. Do you think the epidemic will spread to the town?";
				link.l1.go = "Consumption";
			}
			if (CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.Commandant") && pchar.questTemp.Consumption == "begin")
			{
				link.l1 = "What can you say about the fort's commandant?";
				link.l1.go = "Consumption_8";
			}
			if (!CheckAttribute(npchar, "quest.Consumption_1") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Tell me, does the name 'Juan' mean anything to you?";
				link.l1.go = "Consumption_12";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Listen, in April 1654 a frigate docked at your port under the command of Captain Miguel Dichoso, and he disappeared afterwards. Is there anything you can tell me about it?";
				link.l1.go = "guardoftruth";
			}
			//--> Оковы Азарта
			if (CheckAttribute(pchar, "questTemp.OZ_Tavern_1"))
			{
				link.l2 = "Tell me, "+npchar.name+", who is this Javier Castillo?";
				link.l2.go = "OZ_Tavern_1";
			}
			if (CheckAttribute(pchar, "questTemp.OZ_Tavern_2"))
			{
				link.l2 = "Let’s get back to the conversation about the man who can influence Javier.";
				link.l2.go = "OZ_Tavern_2_1";
			}
			//<-- Оковы Азарта

		break;
		
		//--> Цена чахотки
		case "Consumption":
			dialog.text = "The commandant says there's no danger. Those who get too curious end up locked in the casemates. I'm not one of them, sorry.";
			link.l1 = "Is that so? A tavernkeeper with no desire to listen to rumours - that's something new! Perhaps the clinking of pesos will rekindle your curiosity?";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "Silver is tempting, of course, but my own skin is worth more. Perhaps I could tell you about something else, señor? I'm actually always glad to talk, just start the conversation!";
			link.l1 = "So that's how the issue unfolds... All right, in this purse are three thousand pieces of eight and we will have a nice little chat about the weather, deal?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3000);
			dialog.text = "Oh, you are persistent, señor. Just remember, this conversation never happened. (whispering) I've heard, time and again, for a whole year now, that people have been wasting away in our prisons, dying of consumption. You can blame the authorities, you can blame God, or the Devil, but most of it is put down to ill fortune. This damned disease steals lives so quickly. Sometimes they'll put a perfectly healthy man in there, and in a week or two he's gone. Just like that...";
			link.l1 = "Shiver me timbers... A whole year, you say? And what, nobody's taken it upon themselves to do anything about it?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "Who cares, señor? Who cares about prisoners? The scum of society - or so the great men in silk say. There was a physician who worked in the dungeons. Tried to heal those poor souls. He didn't last long; it seems the illness claimed him too.\nThe commandant doesn't let people in now, and our authorities pay no mind to such matters, especially when they have to pay less for prison rations.";
			link.l1 = "Interesting, but what is it about this disease that frightens you so much that, locked inside secure walls, we are whispering like nuns in the confessional?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "It's hard for me to tell you, but there was one fellow here. He was taken in for smuggling and was locked up for about half a year until his mates bought him out. Well, you know—they weighed out gold for whoever needed it, they paid as much as they were told, and the fellow got out. But ever since then he's been quite mad.";
			link.l1 = "Crazier than a bilge rat?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "I suppose so. He was useless to his mates from then on, spending the whole day in here, drinking himself to death. It seemed like he wanted to erase something from his mind. Every time he got drunk, he told stories about the consumption that takes people in silence\nThose were his exact words. According to him, 'consumption' is the worst thing that can happen to a man.";
			link.l1 = "A drunkard's ramblings. What of it?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			if (CheckAttribute(pchar, "questTemp.Consumption.Commandant"))
			{
				dialog.text = "Nothing, except that he found some liquid courage and started talking more and more, and then just like that, someone slit his throat and tossed him in the gutter... and whoever did it and why is all the same to me.";
				link.l1 = "What can you say about the commandant?";
				link.l1.go = "Consumption_8";
			}
			else
			{
				dialog.text = "Nothing, other than the fact that he got brave and started talking more and more and then just like that somebody slits his throat and tosses him in the gutter... and whoever did it and what for is all the same to me. (raises his voice) Yes, the bays and reefs are really dangerous here, señor. You have to be careful when the storms come crashing in from the Greater Antilles, miss the weather gage and you're gone! Have a nice rest, señor, thanks for stopping by!";
				link.l1 = "Storms... right. Thank you, too.";
				link.l1.go = "Consumption_7";
			}
			pchar.questTemp.Consumption.Contra = "true";
		break;
		
		case "Consumption_7":
			DialogExit();
			npchar.quest.Consumption = "true";
			AddQuestRecord("Consumption", "2");
		break;
		
		case "Consumption_8":
			dialog.text = "What is there to say about him? He's a colonel, he arrived from Europe a couple of years ago after being given this post. Supposedly, he was demoted back in the Old World for some shady dealings. I don't know if that's true, but there were rumours at first. But who doesn't have rumours about them, right?";
			link.l1 = "Dirty deeds, you say... That's interesting. Anything else?";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			dialog.text = "Well, what can I say... The colonel seems like a man who is deeply concerned for his own safety. Sure, these parts aren't safe because of pirates, bandits, Indians and other scum, but Señor Commandant never leaves his house without several bodyguards\nHis mansion is in this city, and he has turned it into a small fortress - his servants are well-armed and keep the windows barred.";
			link.l1 = "But during the day he serves in the prison, doesn't he?";
			link.l1.go = "Consumption_10";
		break;
		
		case "Consumption_10":
			dialog.text = "Yes, but that mansion is basically just waiting there for an ambush or an invasion. Anyway, Señor Commandant apparently doesn't often return there — a true fortress is more his style, he-he.";
			link.l1 = "Thank you, you've been a great help. See you later, "+npchar.name+"!";
			link.l1.go = "Consumption_11";
		break;
		
		case "Consumption_11":
			DialogExit();
			if (CheckAttribute(npchar, "quest.Consumption")) AddQuestRecord("Consumption", "4");
			else AddQuestRecord("Consumption", "5");
			DeleteAttribute(pchar, "questTemp.Consumption.Commandant");
			pchar.questTemp.Consumption = "current";
		break;
		
		case "Consumption_12":
			dialog.text = "Juan? Which one? There are a lot of them here, people usually have last names too... or at least a nickname...";
			link.l1 = "I was just thinking... Maybe his nickname is 'Consumption', have you ever heard that?";
			link.l1.go = "Consumption_13";
		break;
		
		case "Consumption_13":
			dialog.text = "Oh God, are you talking about that again! No, thank God, I haven't heard. I swear! Now, let's change the subject. Please!";
			link.l1 = "Fine, alright, don't have a heart attack...";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan)+1;
			if(sti(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption_1 = "true";
		break;
		//<-- Цена чахотки
		
		//--> Оковы Азарта
		case "OZ_Tavern_1":
			dialog.text = "Javier is a card player, a cheat, and a swindler. Always hanging around the tavern, looking for someone to squeeze a few pesos from.";
			link.l1 = "So, he hasn’t been noticed in other shady dealings? Maybe he has enemies?";
			link.l1.go = "OZ_Tavern_2";
			DeleteAttribute(pchar, "questTemp.OZ_Tavern_1");
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Tavern_2":
			dialog.text = "Well, let’s just say he has far fewer friends than people who dream of wringing his neck. But if you need the name of someone who can truly influence him, that will cost you a thousand pesos. Pay – and I’ll tell you everything.";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "All right, take your money, you old extortionist.";
				link.l1.go = "OZ_Tavern_3";
			}
			else
			{
				link.l1 = "We’ll get back to this conversation later. Right now I don’t have the amount.";
				link.l1.go = "exit";
				pchar.questTemp.OZ_Tavern_2 = true;
				AddLandQuestMark(npchar, "questmarkmain");
			}
		break;
		
		case "OZ_Tavern_2_1":
			dialog.text = "Captain, have you brought the thousand pesos?";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "I have. Take it, you old extortionist.";
				link.l1.go = "OZ_Tavern_3";
			}
			else
			{
				link.l1 = "Damn. I’ll be back soon.";
				link.l1.go = "exit";
			}
		break;
		
		case "OZ_Tavern_3":
			dialog.text = "Now that’s more like it. You see, Javier doesn’t just have gambling debts. Once he decided to dabble in the antique trade, but as you might expect, it didn’t end well for him. At first things even went fairly well, but then he stumbled upon an opportunity to acquire a certain rare item\nHe got so fired up about the idea that he went around to every moneylender looking for funds. Naturally, no one gave him a single coin. Then he found another man just as obsessed with antiques and borrowed one hundred and fifty thousand pesos from him. The rest, I think, you can guess\nHe was swindled, and now that debt hangs around his neck like a stone. He’s paid back mere pennies, and by the look of it, has no intention of paying the rest, even though his creditor has even hired people to intimidate him\nThe man he owes is Felipe Alarcon. His house is across from the bank – you’ll recognize it easily, it’s a magnificent mansion with columns at the entrance.";
			link.l1 = "Thanks!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000);
			DeleteAttribute(pchar, "questTemp.OZ_Tavern_2");
			AddDialogExitQuestFunction("OZ_Felip_1");
			DelLandQuestMark(npchar);
		break;
		//<-- Оковы Азарта
		
		case "guardoftruth":
			dialog.text = "I remember him. He often stopped by my tavern, but didn't talk much. Had a few shots of rum, shared a whisper with some customers, and left. Very gloomy and serious, like everyone on that frigate. Dangerous-looking mercenaries who kept their blades ready\nThere was a rumour that the frigate was full of treasure, but I don't believe such tales. Valuable cargo is never transported on a single ship without a convoy. They spent a day here, then left. To Europe, I heard. That's all I know.";
			link.l1 = "I see. Well, it's something, at least...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "40");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
