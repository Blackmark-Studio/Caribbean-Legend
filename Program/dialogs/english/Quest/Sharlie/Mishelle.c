// Брат Шарля, Мишель де Монпе, он же Дичозо, он же воплощение Кукулькана, он же главный злодей
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.Sharlie == "takeknife")
			{
				dialog.text = "Welcome, Charles the Voyager! I've heard all about how you defeated those pirates on the eastern coast of Martinique. Now I'm absolutely certain I wasn't wrong about you, brother.";
				link.l1 = "Sons of bitches caught me in a trap. But they underestimated us. My navigator, my crew and I came out on top. Although I've got to admit, dear brother, in the beginning... things were looking grim.";
				link.l1.go = "trial";//промежуточная стадия
				break;
			}
			if (pchar.questTemp.Sharlie == "gambitstage")
			{
				bool bFMQM = CheckAttribute(pchar,"questTemp.FMQM") && pchar.questTemp.FMQM != "fail" && pchar.questTemp.FMQM != "end";
				bool bFMQN = CheckAttribute(pchar,"questTemp.FMQN") && pchar.questTemp.FMQN != "fail" && pchar.questTemp.FMQN != "end";
				bool bFMQT = CheckAttribute(pchar,"questTemp.FMQT") && pchar.questTemp.FMQT != "fail" && pchar.questTemp.FMQT != "end";
				bool bFMQP = CheckAttribute(pchar,"questTemp.FMQP") && pchar.questTemp.FMQP != "fail" && pchar.questTemp.FMQP != "end";
				bool bFMQG = CheckAttribute(pchar,"questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && pchar.questTemp.FMQG != "end";
				bool bFMQL = CheckAttribute(pchar,"questTemp.FMQL") && pchar.questTemp.FMQL != "fail" && pchar.questTemp.FMQL != "end";
				if(bFMQM || bFMQN || bFMQT || bFMQP || bFMQG || bFMQL)
				{
					if (sti(pchar.rank) < 12)
					{
						dialog.text = "Greetings, brother! I appreciate your sincere zeal to get me out of here, but you're not ready for the next step just yet. My plan requires an experienced captain. Keep exploring the Caribbean, earn prizes and learn! When you're ready, we'll continue.";
						link.l1 = "Well, whatever you say, brother. You're sitting in here, not me.";
						link.l1.go = "exit";
					} 
					else 
					{
						dialog.text = "Good to see you, brother. Don't forget your commitments to others. As soon as you're free, I'll be waiting for you – I have ideas for our next step!";
						link.l1 = "Understood, brother. I'll take care of my commitments, but I'll be back soon!";
						link.l1.go = "exit";
					}
					break;
				}
				if (sti(pchar.rank) < 12)
				{
					Log_info("Level 12 is required");
					dialog.text = "Charles the Navigator! I've heard about your adventures! You're almost ready for the next stage of my plan. Come back as soon as you have gained some more experience.";
					if (sti(pchar.rank) < 7)
					{
						dialog.text = "Greetings, brother! I appreciate your sincere zeal to get me out of here, but you're not ready for the next step just yet. My plan requires an experienced captain. Keep exploring the Caribbean, earn prizes and learn! When you're ready, we'll continue.";
					} 
					else 
					{
						if (sti(pchar.rank) < 10)
						{
							dialog.text = "Good to see you, brother! I hear you're making progress! But you're not ready for the next step of my plan just yet. Keep doing what you've been doing and come back to me when you're ready.";
						}
					}
					link.l1 = "Well, whatever you say, brother. You're sitting in here, not me.";
					link.l1.go = "exit";
					if(sti(pchar.rank) > 8)
					{
						link.l2 = "I don't think so, brother. Perhaps you've settled into this cage already, but I don't intend to stay here for long – our father can't wait forever. Spit it out.";
						link.l2.go = "gambitA";
					}
					break;
				}
				else
				{
					dialog.text = "Good afternoon, Charles. The sight of you brings joy to my heart: you're definitely changing for the better.";
					link.l1 = "Is that so? And how do you figure that?";
					link.l1.go = "gambit";//переход на Гамбит
					break;
				}
			}
			if (!CheckAttribute(npchar, "quest.givelink_saga") && CheckAttribute(pchar, "questTemp.HWIC.Detector"))//признак, что Гамбит пройден или провален
			{
				dialog.text = "I see. I see that you have news for me, Charles! Well, what's the word? Hopefully nothing grim?";
				link.l1 = "I followed the advice you gave me last time...";
				link.l1.go = "saga";//переход на Сагу
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Fail1") && CheckAttribute(pchar, "questTemp.HWIC.Fail2") && CheckAttribute(pchar, "questTemp.HWIC.Fail3"))//признак, что Гамбит провален по всем трем вариантам
			{
				dialog.text = "Finally, you're here... What's the word, dear brother?";
				link.l1 = "I followed the advice you gave me last time...";
				link.l1.go = "gambit_fale";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "mishelle")//Сага готова к старту
			{
				dialog.text = "Pleased to see you, Charles! Have you seen the Chevalier de Poincy? How did your meeting go?";
				link.l1 = "Yes, dear brother. We've met. And I have two pieces of news for you, good and bad. I'll start with the good one. I've taken care of your debt to de Poincy. The bad news is that he won't release you until I fulfil your promise to sort things out with some heretic...";
				link.l1.go = "saga_5";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && !CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью
			{
				dialog.text = "How did you fare in La Vega, brother?";
				link.l1 = "Nothing to boast about, really. Tyrex is a colourful character, but his way of doing business just isn't for me.";
				link.l1.go = "saga_17e";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью, но дальше 4 квеста
			{
				dialog.text = "How did you fare in La Vega, brother? I've heard rumours, and to be completely honest, I'm not happy about them... Charlie Prince.";
				link.l1 = "I think I know what those rumours were about. But it's all in the past. I'm not working with Tyrex anymore, that job just got too dirty for my taste.";
				link.l1.go = "saga_17f";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete") // пиратская линейка пройдена полностью
			{
				dialog.text = "Well, greetings... Corsair Charlie Prince. Tell me, Charles, how did you fall so low? I can't believe this. My brother, who used to make a squeamish face when I once mentioned plundering a Spanish merchant galleon, is now one of the most wanted and dangerous pirates in this region! Even I, sitting deep in shit, blush every time your infamy reaches my ears. I have cursed the day I sent you to La Vega. What a shame! A French nobleman has joined the pirates and has become the worst of them all in such a short time! What now, brother? Are you looking for a vacancy in the job of pirate baron?";
				link.l1 = "No. I am done with piracy once and for all.";
				link.l1.go = "saga_17g";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			
			dialog.text = "What else, Charles? I think we've discussed everything. Time is money, dear brother - make haste!";
			link.l1 = "Yes, yes, off I go...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
		break;
		
		case "Mishelle_prisoner":
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Maltie_officer"));
			QuestPointerDelLoc("FortFrance_Dungeon", "quest", "quest1");
			SetCurrentTime(13, 30);
			dialog.text = "Charles!.. Pleased to see you, brother! I understand, of course, that it may be hard for you to believe, but I'm happy as hell you're here...";
			link.l1 = "Ha! Look at him! He's happy! So while you were on your high horse with your 'Order', Charles was the embarrassment of the family, a measly artist, living off the money of courtesans, and a court 'knight', huh? But now that you're clapped behind bars by your own comrades, you're 'happy as hell' to see your good-for-nothing brother!";
			link.l1.go = "Mishelle_prisoner_1";			
		break;
		
		case "Mishelle_prisoner_1":
			dialog.text = "Charles, you...";
			link.l1 = "I'm not done yet! Why didn't you report anything about yourself to France?! Have you been deprived of the right to correspond?! Our father has become completely ill from worrying about you! And he asked me to find out at least something about your fate!..";
			link.l1.go = "Mishelle_prisoner_1a";
		break;
		
		case "Mishelle_prisoner_1a":
			dialog.text = "Charles, how could I possibly tell Father what happened to me? What would I write to him? No, brother, as hard as it is, it's better that our father doesn't know anything yet. And it would be pointless to write to you – you're always at different addresses in Paris... How did you find me?..";
			link.l1 = "At your father's request, I went to Malta. There, I received some information from your friend, Chevalier de La Brignais. He wrote to me about your troubles and that you were likely somewhere in Martinique. Then I returned to France and visited your father. And after all that, I came to this hellhole in the sweltering heat, where the mosquitoes quite literally chew you to death...";
			link.l1.go = "Mishelle_prisoner_1b";
		break;
		
		case "Mishelle_prisoner_1b":
			dialog.text = "Did you tell the father about all this?";
			link.l1 = "No. And the Chevalier de La Brignais did not reply to his letters, fearing the unfortunate consequences... Father still knows nothing about your fate. I decided to find you and get to the bottom of this. Just so you know, I came to Martinique not for you, but for our poor father!";
			link.l1.go = "Mishelle_prisoner_2";
		break;
		
		case "Mishelle_prisoner_2":
			dialog.text = "Really? Charles, since when do you care about your family? Let's be honest, brother, everyone in Paris knows who your father is. You may bear the family name de Maure, but you don't want the name de Monper to be dishonoured. Because in that case you wouldn't be able to use your lineage to tell everyone fanciful stories about your heroic deeds, am I right? The doors of the finest houses in Paris would be closed to you, and they wouldn't let you come within a mile of the Louvre. Do you really believe that your courtesans and mistresses, whose husbands you cuckold while they are fighting on the battlefield for our fatherland, will be happy to betray their lords and masters with the brother of a state criminal like myself? I suppose you've come here straight from the bed of some married girl, am I right? Charles, what's wrong with your face? Did I strike a nerve?";
			link.l1 = "You... You!..";
			link.l1.go = "Mishelle_prisoner_3";
		break;
		
		case "Mishelle_prisoner_3":
			dialog.text = "All right, brother. We've exchanged barbs, that's enough. I admit I'm not perfect. But you're no angel either. Charles, this really isn't the time to quarrel. We both share the same goal: to save the honour and dignity of the Monper family... whatever our motives may be. Brother, for once in our lives, let's set aside animosity for peace. Deal?";
			link.l1 = "Let's try it out... But can you explain to me what you're being accused of?";
			link.l1.go = "Mishelle_prisoner_4";
		break;
		
		case "Mishelle_prisoner_4":
			dialog.text = "Officially, it sounds like it's about the expenditure of the Society's money. In reality, it's much deeper.";
			link.l1 = "So, you've embezzled your organisation's money? Well, well...";
			link.l1.go = "Mishelle_prisoner_5";
		break;
		
		case "Mishelle_prisoner_5":
			dialog.text = "I told you those were the official charges. I didn't take a single louis d'or. Here's how it happened... you see, I can't explain everything to you in detail as long as I'm behind bars. I don't have the moral right to divulge the secrets of our Society.";
			link.l1 = "Please, try to explain, dear brother. I have a right to know, don't you think?";
			link.l1.go = "Mishelle_prisoner_6";
		break;
		
		case "Mishelle_prisoner_6":
			dialog.text = "Fine. I received money for a very dangerous and delicate operation that was supposed to shift the political balance in the Caribbean. I was acting under the direct orders of Philippe de Poincy, the governor-general of the French colonies. But the operation failed despite all my efforts.\nDe Poincy flew into a rage when all his long-shot plans fell apart. He personally signed the order for my arrest and made sure it was carried out. He then came here and declared that he would accuse me of embezzlement and treason against the Order if my relatives or I did not return the money spent on the operation.";
			link.l1 = "Here's a fine how-do-you-do. Where is it, this money that, as far as I understand, our family has to pay for your muffs?";
			link.l1.go = "Mishelle_prisoner_7";
		break;
		
		case "Mishelle_prisoner_7":
			dialog.text = "It was spent on preparing the operation. Bribes, organising expeditions, purchasing all sorts of merchandise and equipment. I had rather large expenses. Just as I said - I didn't take a coin.";
			link.l1 = "And what is the sum being demanded?";
			link.l1.go = "Mishelle_prisoner_8";
		break;
		
		case "Mishelle_prisoner_8":
			dialog.text = "One million.";
			link.l1 = "Merde! You're joking, right?!";
			link.l1.go = "Mishelle_prisoner_9";
		break;
		
		case "Mishelle_prisoner_9":
			dialog.text = "Do I look like someone in a joking mood? No, dear brother, this is the bitter truth. We are going to need to deliver de Poincy one million pesos.";
			link.l1 = "But damn it! Our family hasn't got anywhere near that kind of money! We couldn't scrape that much together in twenty years!";
			link.l1.go = "Mishelle_prisoner_10";
		break;
		
		case "Mishelle_prisoner_10":
			dialog.text = "If I weren't behind bars and bound by my obligations to the Society, I could make it in six months to a year, a year and a half at most. Charles, this is the New World. Everything's different here. A motivated, ambitious man can make a fortune for himself here without dedicating his whole life to it as he would in Europe.";
			link.l1 = "A million in half a year?! Are you mad? If you're so sure, then why don't you tell your de Poincy about that? Let him release you. Put your best foot forward...";
			link.l1.go = "Mishelle_prisoner_11";
		break;
		
		case "Mishelle_prisoner_11":
			dialog.text = "Oh, don't talk nonsense, Charles! There's no way Poincy is going to release me from this cell. If it were that easy, I wouldn't ask for your help.";
			link.l1 = "So I'm the one who has to come up with the money for your freedom?!";
			link.l1.go = "Mishelle_prisoner_12";
		break;
		
		case "Mishelle_prisoner_12":
			dialog.text = "Not just my freedom. Or have you forgotten? Shall we return to our conversation about the palaces, balls, and sex with noble whores? Yes, Charles, you're the one who has to do it. If, of course, you would like to keep carrying on with your meretricious life in Paris just as before. You would like that, wouldn't you, brother?";
			link.l1 = "But goddamn it, where the hell am I supposed to get it?! Do you know of any old woods around here where louis d'ors grow instead of leaves?";
			link.l1.go = "Mishelle_prisoner_13";
		break;
		
		case "Mishelle_prisoner_13":
			dialog.text = "The whole New World is a grove of money trees, yet people are too lazy to lift their foolish heads and reach out to the branches. Don't worry, Charles, you'll do just fine. I've known you since our childhood, and I would never have wasted my time persuading our father to send you here if I thought you were foolish or lazy.\nDespite the shortcomings I've mentioned before, you are brave, ambitious, clever, your tongue is sharp enough, and you know how to handle a rapier, which is an extremely important skill to have here...";
			link.l1 = "Thank you very much. Has my dear brother truly deigned to praise me? And here I thought I was nothing but a pitiful artist, a courtier...";
			link.l1.go = "Mishelle_prisoner_14";
		break;
		
		case "Mishelle_prisoner_14":
			dialog.text = "Cut the bullshit. Have we got an agreement or not?";
			link.l1 = "Sorry, brother. It slipped out. I'm just not used to hearing those words from you. It's like a street whore preaching about saving a soul.";
			link.l1.go = "Mishelle_prisoner_15";
		break;
		
		case "Mishelle_prisoner_15":
			dialog.text = "Let's proceed, brother. As I said, you have everything it takes to succeed here. Not only that, you are not alone. I will help you with advice on what to do and how to do it the right way. Listen to me and we'll come through with flying colours. Believe me, you won't find anyone to match my experience. Are you ready to hold off on the trash talking and finally get to the point?";
			link.l1 = "Yes, it looks like I'm staying here for a while... All right. I'm all ears, Michel.";
			link.l1.go = "Mishelle_prisoner_16";
		break;
		
		case "Mishelle_prisoner_16":
			dialog.text = "Yes, brother, you are going to stay here for a while. It's good that you can see that now. So if some courtesan is waiting for your return back in Paris, I suggest you forget about her. But don't feel bad about it, local girls have their own charms.\nThough, they like real men, strong and assertive, even rough. So if you are going to bed a colony girl, don't count on poetry, discussions about paintings or walking under the moon. They won't approve.";
			link.l1 = "All right, brother. Have you been struck by a bolt of windbaggery? Let's get to the point. I'm willing to listen to your advice, but not your foul insinuations.";
			link.l1.go = "Mishelle_prisoner_17";
		break;
		
		case "Mishelle_prisoner_17":
			dialog.text = "Splendid. In order to have any kind of success, you need to own a ship. The Caribbean is an archipelago. You do know that, right? Life is intertwined with the sea. A man with his own ship has an endless horizon of earning potential.";
			link.l1 = "But I'm not a sailor!";
			link.l1.go = "Mishelle_prisoner_18";
		break;
		
		case "Mishelle_prisoner_18":
			dialog.text = "Then, it's time to become one. You've got no other choice anyway. You didn't think of becoming a port office clerk or registering with the garrison, did you? No? Then you'll be a captain.";
			link.l1 = "What a turn of events in my career! And where am I to find myself a ship?";
			link.l1.go = "Mishelle_prisoner_19";
		break;
		
		case "Mishelle_prisoner_19":
			dialog.text = "There's an excellent lugger waiting at our local shipyard. It isn't big, but it's a very comfortable boat, just right for taking your first steps into the world of sailing. This lugger was built especially for me. I put down a deposit of five thousand pesos for the vessel with the help of my friends. Make your way to the shipbuilder and tell him that Michel de Monper sent you. He'll understand what you're there for.";
			link.l1 = "The ship only costs five thousand? That's a bit odd...";
			link.l1.go = "Mishelle_prisoner_20";
		break;
		
		case "Mishelle_prisoner_20":
			dialog.text = "Brother, are you listening to me? Five thousand is just the deposit. The lugger's price is around twenty thousand pesos. So you'll have to earn the rest of the money yourself. Besides that, you'll need money to hire a crew and a navigator.";
			link.l1 = "Great! And how will I get it?";
			link.l1.go = "Mishelle_prisoner_21";
		break;
		
		case "Mishelle_prisoner_21":
			dialog.text = "No big surprise there. Earn it. How else? Money can be found behind every bush here, you just have to know where to look and not fear adversity. Walk around the various establishments here. Talk to the local people. You're sure to find some kind of work. But be careful, there are far more con artists than honest folk. If you're not an honest person, you might try stealing something valuable from the houses.";
			link.l1 = "But we are nobility, right?";
			link.l1.go = "Mishelle_prisoner_22";
		break;
		
		case "Mishelle_prisoner_22":
			dialog.text = "Titles mean nothing here. Work, fight, steal just like everyone else. After you buy a boat, hire a crew. You won't be able to steer the boat yourself at first, so you'll need a navigator. You can discuss all this with the tavern owner, he'll help you. And make sure you don't get lost, of course. When you set out to sea, sail straight to Guadalupe...";
			link.l1 = "What is that? A town?";
			link.l1.go = "Mishelle_prisoner_23";
		break;
		
		case "Mishelle_prisoner_23":
			dialog.text = "It's an island almost two days away from here. Try to acquire a map of the archipelago as soon as you can and learn it like the 'Lord's Prayer', so you won't look like a fool to anyone who can tell the difference between a town and an island. You're going to have to sail around the archipelago a great deal, so prepare ahead of time.";
			link.l1 = "Hm. Fine. So what do I do on this, uh... Guadeloupe?";
			link.l1.go = "Mishelle_prisoner_24";
		break;
		
		case "Mishelle_prisoner_24":
			dialog.text = "Find a man there by the name of 'Fadey'. He has his own house not far from the pier. Tell him you know me and ask him to repay his debt - he lost quite a hand to me in a game of cards. The money you receive will help you get back on your feet. Use it to get things going.";
			link.l1 = "What do you mean, get things going?";
			link.l1.go = "Mishelle_prisoner_25";
		break;
		
		case "Mishelle_prisoner_25":
			dialog.text = "I mean, use this money to earn even more, and so on. By trading, for example. We will return to this conversation later. Now you should see to the ship, sail to Guadeloupe, find that fat Muscovite, and collect the debt from him. Not literally, of course. Fadey is a very respected man on Guadeloupe and a friend of the local governor himself. So there is no point in quarrelling. On the contrary, try to make friends with him. Get back to me as soon as you have the money. Understood, brother?";
			link.l1 = "Got it. Oh, why... What did I do to deserve this punishment...";
			link.l1.go = "Mishelle_prisoner_26";
		break;
		
		case "Mishelle_prisoner_26":
			dialog.text = "Don't grieve, Charles. Accept it as an inevitable evil, or...as a blessing in disguise. Later on, you'll be grateful to fate that your life has taken this turn. You, brother, finally have the chance to prove you're a real man. You might even become a decent human being...";
			link.l1 = "(START TUTORIAL) That rubbish again?";
			link.l1.go = "Mishelle_prisoner_27";
			link.l2 = "(SKIP TUTORIAL) Brother, I don't have time for this. I want to skip the boring part and get going on the high seas immediately. The sooner I have a ship, the sooner you'll be out of this shithole. Or would you prefer to stay here longer?";
			link.l2.go = "Mishelle_prisoner_29"; // Addon 2016-1 Jason пиратская линейка 1
		break;
		
		case "Mishelle_prisoner_27":
			dialog.text = "No, no. Don't take it the wrong way... All right, Charles, don't waste any time. You know what to do. I'll be waiting for you to return from Guadeloupe as captain of your own ship with Fadey's money. Good luck, brother. I'm counting on you.";
			link.l1 = "I'll try not to let you down. All right, Michel. Until next time!";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_28":
			DialogExit();
			pchar.questTemp.Sharlie = "ship";//флаг на старт мини-квестов для сбора денег
			//LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);// таверна закр
			if(!bHardcoreGame) LocatorReloadEnterDisable("Fortfrance_town", "reload7_back", true);// ЦЕРКОВЬ закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", true);// ростовщик закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", true);// бордель закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload91", true);// бордель закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", true);// тюрьма закр
			bDisableFastReload = false;//open быстрый переход
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//запомним дату
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5");
			//Sharlie_CreateGigoloMan();//мини-квесты на бордель и на джунгли
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_PortMan"), "questmarkmain");
			if(CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
				QuestPointerToLoc("Fortfrance_town", "reload", "reload3_back");
			}
			QuestPointerToLoc("Fortfrance_town", "reload", "reload6_back");
			/*pchar.quest.CreateGigoloMan.win_condition.l1 = "Hour";
			pchar.quest.CreateGigoloMan.win_condition.l1.start.hour = 17.00;
			pchar.quest.CreateGigoloMan.win_condition.l1.finish.hour = 18.00;
			pchar.quest.CreateGigoloMan.function = "Sharlie_CreateGigoloMan";*/
			/* pchar.quest.SharlieremoveLocks.win_condition.l1 = "HardHour";
			pchar.quest.SharlieremoveLocks.win_condition.l1.hour = 23;
			pchar.quest.SharlieremoveLocks.win_condition.l2 = "location";
			pchar.quest.SharlieremoveLocks.win_condition.l2.location = "FortFrance_Town";
			pchar.quest.SharlieremoveLocks.function = "Sharlie_removeLocks"; */
			//устанавливаем прерывание на джунгли
			pchar.quest.Jungle_jew.win_condition.l1 = "location";
			pchar.quest.Jungle_jew.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.Jungle_jew.function = "Junglejew_CreateIndians";
			
			ref location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// на гида
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
		break;
		
		case "Mishelle_prisoner_29": // Addon 2016-1 Jason пиратская линейка 1
			dialog.text = "Heh! This 'boring part' might save your life one day... Whatever. There is an easy way to get the money right now.\nGo to the local church and talk to Abbot Benoit. He is an old friend of our father. Tell him about the situation, fall to your knees and beg him to lend you enough coins to buy a ship.";
			link.l1 = "(SKIP TUTORIAL) Much better now! Heading to the abbot.";
			link.l1.go = "Mishelle_prisoner_31";
			link.l2 = "(START TUTORIAL) Do you want me to start by increasing your debts to even higher levels? Do you take me for a fool, brother? I can see you can't help me at all with this. So it's all on me, then.";
			link.l2.go = "Mishelle_prisoner_30";
		break;
		
		case "Mishelle_prisoner_30":
			dialog.text = "Whoa! Looks like I wasn`t wrong about you, brother. I`m looking forward to your return from Guadeloupe as captain of your own ship with Fadey`s money. Godspeed!";
			link.l1 = "See you. Have fun in here.";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_31":
			DialogExit();
			AddLandQuestMark(characterFromId("Benua"), "questmarkmain");
			pchar.questTemp.Sharlie = "ship_fast"; // ускоренный старт
			pchar.questTemp.Sharlie.FastStart = "true";
			LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//запомним дату
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5-1");
			location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// на гида
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
			//DeleteAttribute(pchar, "GenQuest.CannotWait");
			Sharlie_removeLocks("");
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			dialog.text = "Are you trying to say that was scary? Don't tense up, brother. It's absolutely fine. I didn't feel much like a hero in my first sea battle either. Nonsense. In a month or two, such encounters will feel like a common-or-garden event... Have you visited Fadey?";
			link.l1 = "I have... But with this kind of success... Why did I even bother?";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Hm. Why is that?";
			link.l1 = "Because he's on the rocks. He was recently robbed and has money problems of his own. He offered me a dagger from his collection instead. He said it's valuable and that its worth exceeds the amount of the entire debt. So, I took it...";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "Fadey? On the rocks? Money problems? Ha-ha-ha! You've given me a chuckle, dear brother! That goddamn Muscovite saw right through you and recognised you as a novice straight away and... ah, that bugger! Show me the dagger the old man gave you in exchange for his debt.";
			if (CheckCharacterItem(pchar, "knife_01"))
			{
				link.l1 = "Here you go...";
				link.l1.go = "trial_3";
				PlaySound("interface\important_item.wav");
			}
			else
			{
				link.l1 = "I don't have it with me. To the naked eye, it's just a regular dagger. Fadey told me it's enchanted by an Indian shaman and called the Chief's Claw.";
				link.l1.go = "trial_4";
			}
		break;
		
		case "trial_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "Hm. Well, let's see... God will judge that pudgy bear. Scrap like that, Charles, you could buy at any local store. He pulled a fast one on you, taking advantage of your lack of experience... Here you go, take this piece of steel back. Keep it as a souvenir. You can hang it over your bed in your cabin.";
			link.l1 = "Fucker! Oh, who cares... I'll go back to see him in Guadeloupe and give this greasy bastard a shake!";
			link.l1.go = "trial_5";
		break;
		
		case "trial_4":
			dialog.text = "Enchanted by a shaman? Chief's Claw? Yes... all clear. God will judge that pudgy bear. Scrap like that, Charles, you could buy at any local shop. He pulled a fast one on you, taking advantage of your lack of experience... He tried to tell me some kind of fairy tales and I put him right back in his place. So you can hang this claw in your cabin above your bed as a souvenir... If you haven't tossed it in the rubbish bin yet.";
			link.l1 = "Fucker! Oh, who cares... I'll go back to see him in Guadeloupe and give this greasy bastard a shake!";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			dialog.text = "Calm down, dear brother, relax. There's no need for that unless you want to spend a couple of months in a Basse-Terre prison cell. Have you forgotten what I told you? That pompous bear is a friend of Claude François de Lyon, the governor of Guadeloupe. As soon as I leave this place, I'll go and have a talk with him... heart to heart. He's not going anywhere.";
			link.l1 = "All right. You'd better deal with him... Looks like I'll be left without the promised starting funds?";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "Looks like it, Charles. But keep your head up. One who has a ship and a head on his shoulders cannot go wrong in the Caribbean. And you've got both, haven't you?";
			link.l1 = "What are you insinuating? I've messed up with this dagger, so what should I...";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			dialog.text = "Calm down, dear brother! Why are you so jumpy all of a sudden? Keep calm, you'll live longer. I'm not insinuating anything. I didn't even have such thoughts!";
			link.l1 = "Sorry, Michel. It's just that I'm a little... well, try to understand me too!";
			link.l1.go = "trial_8";
		break;
		
		case "trial_8":
			dialog.text = "I understand. And I really want to help you! So listen carefully. You must gain some experience and at least save up a little money before taking on more serious matters. Rushing into adventures without the necessary preparation is pure suicide. I don't want you to get crushed by this place just yet.";
			link.l1 = "Very inspiring. What sort of adventures are you expounding on, Michel? I've lost track of your ramblings for some reason.";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "Brother, let me remind you that I, or to be more precise, we, owe de Poincy a million pesos. Do you really think you can earn that honestly? Sure, you can trade that much, it is possible if fortune favours you, but trading in the Caribbean is hardly a peaceful business either.\nAdventure will find you whether you wish it or not—the question is, will you be ready when the time comes? It is better to strike first. Si vis pacem, para bellum, Charles...";
			link.l1 = "Again with the fancy words? Speak plainly, I beg of you...";
			link.l1.go = "trial_10";
		break;
		
		case "trial_10":
			dialog.text = "It's Latin, dear brother. I said, 'If you want peace, prepare for war.' Take this phrase as a leadership mentality towards action. You can write it down in your logbook and reread it every morning after prayer. There is much you have to learn and a lot left for you to grasp...";
			link.l1 = "All right, that's enough. I've grown tired of your scientific papers. Let's get to the point.";
			link.l1.go = "trial_11";
		break;
		
		case "trial_11":
			dialog.text = "I am being specific, you just don't understand yet. Fine. First, you need to get familiar with the archipelago and get used to your new life as captain of a ship. You will have to work hard to ensure your well-being and a wage for your crew. There are many ways to make coin.\nTaking freights and passengers on board are the simplest. Merchants in stores may give you freight contracts and passengers will approach you on the streets themselves. You should also consider checking harbour offices; having a lugger or any fast ship will allow you to earn good money as a courier.\nHarbour masters will provide you with very profitable freight contracts once you acquire a bigger ship. Talk with people, don't boast about your lineage, be friendly and things will go just fine. Visit colony governors, they often offer well-paid work.\nYou may try trading but in that case you should hire a decent purser. Be careful at sea, avoid Spanish military squadrons and warships. If you meet a lone Spanish trader or an unprotected convoy, you may try to capture them.";
			link.l1 = "What?! Michel, have I lost my hearing? Are you suggesting that I take up the life of a pirate? You, the pride of the Society, a servant of God and the Trinity, propose such a lifestyle to me?";
			link.l1.go = "trial_12";
		break;
		
		case "trial_12":
			dialog.text = "Oh, Charles... I advise you to get rid of your fastidiousness once and for all, it is not appreciated here. And about the Order... don't be naive, brother. Perhaps in Europe the Louvre and the Escorial are at peace of some sort, but here there is war. Any Spanish raider will not hesitate to plunder your ship and hang you and your crew to dry on a yardarm.\nTherefore, nobody will blame you for plundering a trade ship of a hostile nation, I assure you. And with a letter of marque you will even get official support from the authorities...";
			link.l1 = "I am beginning to understand your principles in life. Just as I understand the methods by which you would apparently be able to 'earn' a million in half a year.";
			link.l1.go = "trial_13";
		break;
		
		case "trial_13":
			dialog.text = "And you will have to use these methods, Charles. After all, this is supported by the authorities, openly or behind closed doors. Even if you stick to trading, one day you will be forced to fight pirates or Spanish raiders, because to them you are the booty.\nIt is in your best interests to forget your previous views on life. Trust me, brother, you can do a great many things not only without losing face, but also earning the authorities' favour and the love of the people.";
			link.l1 = "You never cease to surprise me, Michel. Now you're telling me to become a pirate. What's next?";
			link.l1.go = "trial_14";
		break;
		
		case "trial_14":
			dialog.text = "Don't overdramatise this, Charles. It's really simple: hunt or be hunted. That's the whole philosophy. I prefer the former, and I would like you to follow my example. And I am not telling you to become a pirate, but to engage in military action against a hostile nation, and only when there is good reason for it.";
			link.l1 = "A benefit, you mean?";
			link.l1.go = "trial_15";
		break;
		
		// Rebbebion, небольшое изменение диалога
		case "trial_15":
			dialog.text = "See, you do understand, brother. But enough words. Time to test yourself. Come see me only when you feel ready. Earn some decent money, get a better ship, learn the archipelago and upgrade your skills.\nBut be aware, if you spend the next couple of months in taverns and brothels and learn nothing useful in the process... don't even return then. Are we clear, Charles?";
			link.l1 = "Don't worry. I didn't come here for recreation... What comes after that?";
			link.l1.go = "trial_16";
		break;
		
		case "trial_16":
			dialog.text = "Later on I'll tell you what to do after that. I've already put a plan together. You've got a bright future ahead of you, Charles, if you follow my advice and recommendations closely.";
			link.l1 = "I would prefer my modest past to such a bright, grand future...";
			link.l1.go = "trial_17";
		break;
		
		case "trial_17":
			dialog.text = "Trust me, brother, you will laugh at your worthless past and thank fate for saving you from it. Be optimistic and positive. You will love this life. You'll see.\nOh, one more thing: pay our mutual friend Fadey a visit and ask him to get you a job. The bear has good connections, I am sure he will find you something. Don't linger or you might miss an opportunity. And please don't let me down.";
			link.l1 = "Moral teachings again... Lord, when will all this end? All right, Michel... Can I be on my way?";
			link.l1.go = "trial_18";
		break;
		
		case "trial_18":
			dialog.text = "Wait. A few more tactical pieces of advice. If you cross any nation and turn outlaw, visit the local church and talk to Abbot Benoit. Tell him that I have sent you. He has connections within both the Papist and Calvinist societies and has helped me a great deal with such matters more than once. But be aware that it is neither easy nor cheap, so try to avoid making enemies.\nWait, one more thing! We are nobles, but it is foolish to have an aversion to crafting with our own hands, especially here. You can craft a lot of useful items, provided you have the necessary tools and components... Tell me, brother, how do you load any of your pistols?";
			link.l1 = "Hm. As usual, a bullet and a pinch of gunpowder.";
			link.l1.go = "trial_19";
		break;
		
		case "trial_19":
			dialog.text = "Ha! I didn't expect to hear anything different.";
			link.l1 = "Do you know another way, dear brother?";
			link.l1.go = "trial_20";
		break;
		
		case "trial_20":
			dialog.text = "Of course. But there are few who do it, due to ignorance and plain old laziness. By spending a couple of hours of your time, you could make paper cartridges out of gunpowder and bullets. Using them halves the reload time of the gun. Impressed?";
			link.l1 = "Hm. I suppose so. It's interesting.";
			link.l1.go = "trial_21";
		break;
		
		case "trial_21":
			pchar.alchemy.known = 1;
			AddQuestRecordInfo("Recipe", "cartridge");
			SetAlchemyRecipeKnown("cartridge");
			dialog.text = "Take these crafting instructions for paper shells, study them in your spare time, and don't be too lazy to put your new knowledge to use\Hold on, brother. Don't forget to stop by and see our dear governor.";
			link.l1 = "Is there an occasion?";
			link.l1.go = "trial_22";
		break;
		
		// Rebbebion, намёк на "Травлю крысы"
		case "trial_22":
			dialog.text = "It's always good to keep in touch with governors, especially if they have your relatives imprisoned on their islands.";
			link.l1 = "Tell me about him.";
			link.l1.go = "trial_23";
		break;
		
		case "trial_23":
			dialog.text = "Not everyone can hold on to the throne of Martinique. The interests of the Order, the Crown, the pirates... and a nobleman shouldn't forget his own interests. If Parquet weren't so lax and tempted by sin, he might even make Poincy take him seriously.";
			link.l1 = "And what use could I be to him?";
			link.l1.go = "trial_24";
		break;
		
		case "trial_24":
			dialog.text = "Officials always have work for free captains. They pay sparingly, though, and only when it concerns public interests, not personal ones. In any case, there's no better way in the Caribbean to uphold honour and improve national relations than by working for the governors. Seize the moment, especially since Parquet's facing some trouble right now. What kind of trouble?";
			link.l1 = "What kind of trouble?";
			link.l1.go = "trial_25";
		break;
		
		case "trial_25":
			dialog.text = "I'm sorry, brother. The Order's interests are involved. I'll just say that we're not the only ones in need of quick ways to get rich.";
			link.l1 = "You're being cryptic again... Well, I'll drop by when I have time.";
			link.l1.go = "trial_26";
		break;
		
		case "trial_26":
			dialog.text = "Go now. Good luck, brother!";
			link.l1 = "Thank you... See you later, Michel.";
			link.l1.go = "trial_27";
		break;
		
		case "trial_27":
			TakeNItems(pchar, "bullet", 5);
			TakeNItems(pchar, "gunpowder", 5);
			DialogExit();
			NextDiag.TempNode = "First time";
			pchar.questTemp.Sharlie = "trial";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			pchar.questTemp.Trial = "begin"; // старт промежуточной линейки
			SetFunctionTimerCondition("Sharlie_TrialOver", 0, 0, 24, false); // таймер
			AddMapQuestMarkCity("Baster", false);
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddQuestRecord("Sharlie", "19");
			// открываем все острова
			for (i=0; i<MAX_ISLANDS; i++)
			{				
				if (!CheckAttribute(&Islands[i], "hidden")) Island_SetReloadEnableGlobal(Islands[i].id, true);
			}
			DeleteAttribute(pchar, "questTemp.Sharlie.Lock"); //снимаем блокировку
			LocatorReloadEnterDisable("FortFrance_store", "reload2", false); // откроем склад магазина
			sld = characterFromId("Benua");
			sld.quest.help = "true";
			npchar.greeting = "mishelle_3";
			i = FindIsland("Martinique");
			Islands[i].EffectRadius = 5000;
			// Addon-2016 Jason, французские миниквесты (ФМК)
			pchar.quest.Sharlie_FMQ.win_condition.l1 = "Rank";
			pchar.quest.Sharlie_FMQ.win_condition.l1.value = 4;
			pchar.quest.Sharlie_FMQ.win_condition.l1.operation = ">=";
			pchar.quest.Sharlie_FMQ.function = "FMQ_SetConditions";
			// Sinistra - миниквест "Делюк"
			PChar.quest.Del_Alonso.win_condition.l1 = "location";
			PChar.quest.Del_Alonso.win_condition.l1.location = "FortFrance_town";
			PChar.quest.Del_Alonso.win_condition = "Del_Alonso";
			// при достижении уровня даём флаг на квест "Голландский Гамбит"
			pchar.quest.Sharlie_GambitStage_level_9.win_condition.l1 = "Rank";
			pchar.quest.Sharlie_GambitStage_level_9.win_condition.l1.value = 9;
			pchar.quest.Sharlie_GambitStage_level_9.win_condition.l1.operation = ">=";
			pchar.quest.Sharlie_GambitStage_level_9.function = "Sharlie_GambitStage_level_9";
			pchar.quest.Sharlie_GambitStage_level_12.win_condition.l1 = "Rank";
			pchar.quest.Sharlie_GambitStage_level_12.win_condition.l1.value = 12;
			pchar.quest.Sharlie_GambitStage_level_12.win_condition.l1.operation = ">=";
			pchar.quest.Sharlie_GambitStage_level_12.function = "Sharlie_GambitStage_level_12";
			//маркер на контрабандиста по квесту "Деньги на деревьях"
			AddLandQuestMark(characterFromId("FortFrance_Smuggler"), "questmarkmain");
			PChar.quest.MOT_UbratMarku.win_condition.l1 = "MapEnter";
			PChar.quest.MOT_UbratMarku.win_condition = "MOT_UbratMarku";
			// Sinistra - Старт квеста "Травля крысы"
			pchar.questTemp.TK_TravlyaKrys = true;
			AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
			SetTimerCondition("TK_Timer", 0, 0, 30, false);
			//маркер на торговца БасТера по квесту "Бесчестный конкурент"
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
		
		case "gambitA":
			dialog.text = "Have it your way then. I believe in you, brother. When I look at you now, I just know that you are changing for the better.";
			link.l1 = "You don't say. How so?";
			link.l1.go = "gambit";
		break;
		
		case "gambit":
			dialog.text = "I can see it, dear brother. I can see your walk and the expression on your face. Finally, the mask of a conceited young boy, which quite literally drove me insane, has melted away from you. Your new life has clearly benefited you by now.";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "I can't understand, brother, whether your words are praise or insult. But I'll tell you the truth: I am uninterested in what you think of me from over there. I have collected the million necessary to pay off your debt, so you'll soon be walking free. Where can I find de Poincy?";
				link.l1.go = "gambit_1_1";
			}
			else
			{
				link.l1 = "I can't understand, brother, whether your words are praise or insult. But I'll tell you the truth: I am not interested in what you think of me from over there. I have a sea, not a heap, of matters to attend to, and I have no time to stand here and bandy words with you. Do you have anything relevant to say? If not, then I'll be on my way...";
				link.l1.go = "gambit_1";
			}
			DelLandQuestMark(npchar);
			DeleteQuestCondition("Sharlie_GambitStage_level_9");
			DeleteQuestCondition("Sharlie_GambitStage_level_12");
			// уберем маркеры, если ФМК не стали проходить
			DelMapQuestMarkCity("Baster");
			DelMapQuestMarkCity("Fortfrance");
			DelMapQuestMarkCity("Charles");
			DelMapQuestMarkCity("Tortuga");
			DelMapQuestMarkCity("Portpax");
			
			if(CharacterIsAlive("FMQG_pass_1"))
			{
				sld = CharacterFromID("FMQG_pass_1");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQM_carpenter"))
			{
				sld = CharacterFromID("FMQM_carpenter");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQN_seafox_1"))
			{
				sld = CharacterFromID("FMQN_seafox_1");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQT_girl"))
			{
				sld = CharacterFromID("FMQT_girl");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") 
			{
				DeleteAttribute(pchar, "questTemp.FMQP");
				sld = CharacterFromID("PortPax_waitress");
				DelLandQuestMark(sld);
			}
			if(CharacterIsAlive("FMQG_cureer"))
			{
				sld = CharacterFromID("FMQG_cureer");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("Guide_y"))
			{
				sld = CharacterFromID("Guide_y");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
		break;
		
		case "gambit_1_1":
			dialog.text = "You've managed to put together a million? Well done, Charles, simply impeccable! But unfortunately, Philippe de Poincy is no longer at his residence; he has departed on Society business, off on a secret expedition. So you'll have to wait a little before visiting him.";
			link.l1 = "Screw you and your secret dealings! I thought I'd be done with all this and go home, and now...";
			link.l1.go = "gambit_1_2";
		break;
		
		case "gambit_1_2":
			dialog.text = "And now you've opened up the opportunity to make much more money, and not just that. Brother, the fact that you've amassed the amount requested by the old fox is amazing, but I wouldn't be so confident or so calm... De Poincy is quite the slippery eel, and he has shown a great deal of interest in your modest person, and...";
			link.l1 = "And now you're afraid that a million won't be enough for him?! Or is there something you left out last time?";
			link.l1.go = "gambit_1_3";
		break;
		
		case "gambit_1_3":
			dialog.text = "I'm not afraid of anything, but I must warn you that Poincy is not a simple man. While he is away, you have the opportunity to build some stature for yourself, so that you may speak with him as an equal, not as a lord and a servant. Thus, I strongly urge you to follow my plan, which I will explain to you right now.";
			link.l1 = "All right. No use crying over spilt milk. I'll hole up in this hellhole a little longer. De Poincy isn't going to be sailing around forever. Bring me up to speed on your plan.";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_1":
			dialog.text = "Oh! A commendable reply. I'm glad, Charles, that you've become a man. However, do not be so stern toward your brother. Granted, I have something to tell you. I've been looking forward to our meeting again and have already developed a plan for what you'll do next.";
			link.l1 = "Nice. Then fill me in.";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_2":
			dialog.text = "Look. Sure, money plays a big role in the Caribbean, just like everywhere else, but money can't solve everything. A successful man must not only have a heavy purse, but also extensive and varied connections, and not to lowlifes, but to people who matter in this world.\nIt doesn't matter what nationality or estate they are. Connections open doors that cannot be opened with money alone. The combination of 'money plus connections' gives a man the most valuable thing in the world - power.\nYou should consider establishing such connections, and you won't be able to do so by doing freight jobs, trading, minor piracy, or even by gaining favour with governors.";
			link.l1 = "What do you propose?";
			link.l1.go = "gambit_3";
		break;
		
		case "gambit_3":
			dialog.text = "There are not that many powerful organisations in the Caribbean. One of them is the Dutch West India Company. You can join them. Their headquarters are in Willemstad on Curaçao. The Company often hires third-party captains and offers special long-term contracts to the most useful of them.\nIf you are lucky, you may make a decent career there. I heard that they are experiencing serious trouble now – some English privateer has taken up arms against the Company and is constantly sinking their ships. They can't do anything about him; he is a navy officer, making him too tough for them.\nThey say that he is somehow connected to British military intelligence, and they are very serious people. So, perhaps, taking the side of this captain will be even more profitable for you, but the problem is – I don't know his name, I only know that Antigua is his operational base.\nYou may sail there and ask around. I also heard about some strange organisation which also takes part in this English-Dutch conflict, but I don't know which side they are on. All I know is that the trail leads to Barbados, to Bridgetown...";
			link.l1 = "So you suggest that I enlist with the Dutch, or go looking for a shady captain or an even shadier 'organisation'?";
			link.l1.go = "gambit_4";
		break;
		
		case "gambit_4":
			dialog.text = "The choice is yours. In any case, you won't have any other means of quickly getting in with the people who decide the fate of others in the Caribbean and possess significant power. I hope you haven't got it into your head that two or three favours for the governor will get you straight into the Royal Navy.";
			link.l1 = "You know, dear brother. I never really hoped for a military career in the French navy. God forbid I end up like you, stuck in a jail cell for some task I failed to accomplish... All right, I understand. I think I'll find the General Headquarters of the Dutch Company without much trouble, but I haven't the faintest idea how to search for the rest of the parties";
			link.l1.go = "gambit_5";			
		break;
		
		case "gambit_5":
			dialog.text = "As for the English privateer, you can ask around in St. John's, Antigua. Someone will definitely be able to tell you. Tell them you're looking for work with the English fleet. As for 'the third force', you can talk to the people in Bridgetown about that. Someone there surely must be connected to this organisation.";
			link.l1 = "Is their work going to be compensated at least? The Company, this privateer... Or is it all going to be for the sake of 'connections'?";
			link.l1.go = "gambit_6";			
		break;
		
		case "gambit_6":
			dialog.text = "Charles, you surprise me. The Dutch West India Company deals in sums a king would envy. The privateer I told you about has plundered so many Dutch ships that he must already be overflowing with wealth. And the people from the 'organisation' don't just have a lot of money. They have a bloody fortune.   Working for them will always guarantee you a sweet piece of the pie. People like them always play big. And if you're clever, you can always play your own game and make even more.";
			link.l1 = "All right. I'll think it over and decide what my best bet is. Do you have any other instructions?";
			link.l1.go = "gambit_7";
		break;
		
		case "gambit_7":
			dialog.text = "Yes. You should learn how to use navigation tools. Alas, many navigators can orient themselves only by compass and stars and cannot estimate their coordinates. And this is critical.\nSo. Use a boussole to estimate latitude. It is quite a rare tool and you won't find it in stores, but you can craft it yourself using two common items - a compass and an astrolabe. Here, take the instructions.\nEstimating longitude is a bit trickier. You will need a rated chronometer. You can make one from a common ship's chronometer by adjusting it with an hourglass. The problem is that such a tool works efficiently only for a month before it becomes too inaccurate due to errors.\nA chronometer always requires resetting. Hourglasses can be bought in the office of the Dutch West India Company. I also bought chronometers there. Here, take these instructions.";
			link.l1 = "Thank you. I'll get to studying right away.";
			link.l1.go = "gambit_8";
		break;
		
		case "gambit_8":
			AddQuestRecordInfo("Recipe", "bussol");
			SetAlchemyRecipeKnown("bussol");
			AddQuestRecordInfo("Recipe", "clock2");
			SetAlchemyRecipeKnown("clock2");
			dialog.text = "Try to acquire all these tools as soon as possible. All experienced and respected captains navigate by latitude and longitude. You will be considered a novice at seamanship until you know what those numbers mean.\nWell, come back to boast as soon as you find success in the matters we have discussed recently. Godspeed, Charles!";
			link.l1 = "Thank you, dear brother. I feel it will surely come in handy!";
			link.l1.go = "gambit_9";
		break;
		
		case "gambit_9":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			pchar.questTemp.Sharlie = "gambit";//флаг на Голландский Гамбит
			pchar.questTemp.HWIC.CanTake = "true"; //Голландский Гамбит доступен для взятия
			AddQuestRecord("Sharlie", "20");
			npchar.greeting = "mishelle_3";
			AddMapQuestMarkCity("Bridgetown", false);
			AddMapQuestMarkCity("Villemstad", false);
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			// Rebbebion, убираем марки
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
		break;
		
		case "gambit_fale":
			dialog.text = "And what do you have to boast about?";
			link.l1 = "Nothing for now. I've found all three organisations and tried working with them, but like a cigar, it all blew up in smoke literally at the first stage. It's as if fate's rigged against me...";
			link.l1.go = "gambit_fale_1";			
		break;
		
		case "gambit_fale_1":
			dialog.text = "So the rumours are true then... Dear brother, fate is not rigged against you. It's called a dull mind and crooked hands. You've disappointed me. Go back to France, there is nothing more for you to do here.";
			link.l1 = "But how...";
			link.l1.go = "gambit_fale_2";			
		break;
		
		case "gambit_fale_2":
			dialog.text = "It's not your business anymore. I'll deal with it myself. I have other people more capable of helping me fix my problem. I was afraid that confiding in you would keep me here till the end of my days. Anyway. Get out of here, go back to your courtesans.";
			link.l1 = "Fine, go to hell...";
			link.l1.go = "gambit_fale_3";
		break;
		
		case "gambit_fale_3":
			DialogExit();
			NextDiag.CurrentNode = "gambit_fale_4";
			npchar.lifeday = 30;
		break;
		
		case "gambit_fale_4":
			dialog.text = "I've got nothing to discuss with you. Go.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gambit_fale_4";
		break;
		
		case "saga":
			switch(pchar.questTemp.HWIC.Detector)
			{
				case "holl_win": sTemp = "I've entered service with the Dutch West India Company and become a special tasks agent and close friend of the vice administrator of the Company, Lucas Rodenburg. I managed to carry out several serious missions, in particular, I liquidated the actual English privateer. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "holl_fail": sTemp = "I've entered service with the Dutch West India Company, however matters have gone modestly, I've failed an important task, and was compelled to a dishonorable discharge with nothing."; break;
				
				case "eng_win": sTemp = "I've found the actual English privateer, Richard Fleetwood, and carried out several important tasks in the name of the English navy, in particular, I liquidated the pirate 'ghost ship' and did away with Lucas Rodenburg himself, vice administrator of the Company. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "eng_win_half": sTemp = "I've found the actual English privateer, Richard Fleetwood, and carried out several important tasks in the name of the English navy, in particular, I liquidated the pirate 'ghost ship'. Of course, Fleetwood departed to England and my service with him is over, but still..."; break;
				
				case "eng_fail": sTemp = "I've entered service with the English privateer from Antigua, however matters have gone modestly, I've failed an important task, and was compelled to a dishonorable discharge with nothing."; break;
				
				case "self_win": sTemp = "I've discovered the 'secret organization' on Barbados, started rolling some game of my own, and achieved quite a bit: I did away with that English privateer, Richard Fleetwood, put Lucas Rodenburg, the vice administrator of the Company, behind bars, become a close friend of governor Matthias Beck and the company's director Peter Stuyvesant. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "self_fail": sTemp = "I've discovered the 'secret organization' on Barbados, started rolling some game of my own, however it all went down in dust at the moment of truth..."; break;
			}
			dialog.text = "And? Come on, dear brother, don't drag it out. What's the good word? Some rumours have reached me of your ardent industriousness, but I wanted to hear it all from you.";
			link.l1 = sTemp;
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "eng_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "Excellent! Great job, Charles! I didn't doubt you for a moment! You'll go far, dear brother... Keeping yourself busy like that and forging relationships with such important people—well, I didn't expect that. Congratulations!";
			}
			else
			{
				dialog.text = "Don't be upset, Charles. If it didn't work out, there's nothing you can do about it. We'll use other means to achieve the results we need.";
			}
			link.l1 = "What shall we do now, Michel? Is it time to pay a visit to the Chevalier de Poincy? I feel quite prepared for a conversation with him.";
			link.l1.go = "saga_2";	
		break;
		
		case "saga_2":
			dialog.text = "Have you already managed to put together the required sum of one million pesos?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Yes, I currently possess the required sum.";
				link.l1.go = "saga_3_1";
			}
			else
			{
				link.l1 = "No, I don't have that much money yet.";
				link.l1.go = "saga_3_2";
			}
		break;
		
		case "saga_3_1":
			dialog.text = "Excellent! Then I won't be sitting in this casemate much longer... Be on your way to Capsterville, it's on Saint Christopher, and request an audience with de Poincy. He should be at the governor's palace where he resides. Beyond that, just judge based on the situation and remember: Poincy is slick, very slick... I've got a bad feeling that this whole shebang isn't going to go down so easily. Go, brother, and be careful!";
			link.l1 = "I'll keep your precautions in mind, Michel. Don't fret, I wasn't born yesterday either. Off I go to the old fox. See you later!";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_3_2":
			dialog.text = "No point in talking to de Poincy then. He won't even let you in. Gather the money, my brother, you're quite experienced already so it won't be much of a problem. Sail to Capsterville on Saint Christopher as soon as you have it.\nThe Chevalier must be in his governor's palace. Ask for an audience and they will let you in. Then see for yourself and be careful: de Poincy is sly, very sly... Something tells me that this story won't end just like that.";
			link.l1 = "I'll keep your precautions in mind, Michel. Don't fret, I wasn't born yesterday either. As soon as I put the money together, I'll go straight to the old fox. See you later!";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			DialogExit();
			AddMapQuestMarkCity("Charles", false);
			AddLandQuestMark(characterFromId("Puancie"), "questmarkmain");
			npchar.quest.givelink_saga = "true";
			NextDiag.TempNode = "First time";
			pchar.questTemp.Sharlie = "saga";//флаг на Пиратскую Сагу
		break;
		
		case "saga_5":
			dialog.text = "Nom d'une pipe! That's exactly what I was afraid of. Poincy has been hot on your heels for a long time, Charles. That's why he has taken such an interest in you! You've built yourself quite a reputation in the Caribbean and so he has decided to use you to fulfil assignments that went down the pan...";
			link.l1 = "I get the feeling, Michel, that you were well aware and you just didn't want to inform me before. It's all turning out too smoothly... The money first, now your work... That doesn't happen by chance.";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Charles, don't look for a secret message where there isn't one. If only you had given Poincy the money the very first day you arrived... Well, I mean, let's say if you had it. The Chevalier wouldn't have asked you for anything else. But now that he has taken an interest in you and seen how easily you've settled in here and what you've managed to achieve, he has decided to exploit your talents.";
			link.l1 = "Right... because your talents are no longer satisfactory to him, are they? Merde! All right. I see I'm at a dead end here. Who is this heretic? How can I find him?";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "No need to search for him! He never leaves Tortuga and remains under the protection of the bastion he built and the hordes of loyal Huguenots who serve as soldiers in his garrison. Therefore, every soldier is loyal to him. Poincy meant François Levasseur, the governor of Tortuga.\nThe Spanish still can't drag him out of there, and de Poincy seriously believed that I would be able to do so alone, without any support from the navy, only because starting a civil war would be a grave political misstep due to the proximity of the Santo Domingo garrison.\nThe old scoundrel is too concerned about his spotless career and forthcoming pension to risk everything like that. Nevertheless, Levasseur has gone too far and now represents a danger to the crown.\nDe Poincy, who appointed Levasseur to his current position himself, considers this fearsome Huguenot a personal enemy and is eager to replace him with the Maltese Chevalier de Fontenay, my immediate superior under whose command I have arrived here from Malta.";
			link.l1 = "Glorious! First, make a million, then assassinate the governor of Tortuga. What will my next assignment be? Organise a conspiracy in the Escorial? Damn! I'm not surprised you messed that thing up. Taking out the governor isn't like robbing Spanish merchants. I hope you had some kind of plan when you swore to pull the chestnuts out of the fire?";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "To be completely honest, I didn't have any plan, since I was going to leave the service anyway and return to our family mansion if my risky venture succeeded. Personally, I don't give a damn about de Poincy's problems.\nSurely, he would have become much more flexible as soon as he saw the Indian gold... Well, currently he holds all the trump cards against us. I suppose I will stay here as long as Levasseur is the governor of Tortuga.";
			link.l1 = "And why wouldn't the Maltese, led by de Fontenay, with their sights set on the governor's seat, storm Tortuga themselves?";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Imagine that. The Order declares war on Louis. Don't be absurd! Such a scandal is out of the question. Only a private individual can capture Tortuga. A pirate, or a Catholic adventurer like you.\nAfterwards, he can surrender the island to the control of the new governor de Poincy will send. Such an act will look excellent from the point of view of high-level policymakers.";
			link.l1 = "So is there any point in negotiating with pirates?";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "Problem is that Levasseur holds authority over many pirates of the Brethren and beyond. He allows them to hide behind Tortuga's batteries and freely sell what they have plundered, taking a share of the booty.\nHe used to share with de Poincy, but he no longer does. The pirate ships will protect Tortuga and its garrison, which makes storming the fort even more difficult.";
			link.l1 = "Do you think this matter is a lost cause?";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "There is always a solution, little brother. It is just not always visible on the surface. Not all pirates are sympathetic to the Huguenots of Tortuga. I know at least two influential pirates who consider Levasseur a traitor and scum. I am talking about Steven Dodson, also known as the Shark, and the legendary baron of Mosquito Bay, Jan Svenson.\nI don't know where to find the Shark; I've heard rumours that something happened and he had to leave his base at Isla Tesoro. But you can always find Svenson in Blueweld. He is a significant figure there.";
			link.l1 = "Do you suppose that this... Svenson will help me?";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "He will if you help him. Things aren't going too well for him at the moment, and the man could use loyal and talented people. You will need to prove your usefulness to him first before having a serious conversation. You will find a way to do so when you get there. I find it hard to give advice from here.\nI take it that you have decided to go on, Charles, since you keep asking questions?";
			link.l1 = "You see, Michel, I just gave away a heap of my own silver to de Poincy. I amassed it through blood, sweat, and tears! I'm not sure you would have risked even a single louis d'or for me if I were in your shoes.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "Charles...";
			link.l1 = "Don't interrupt me! It would be foolish to return to Father empty-handed. The problem still isn't solved, you're behind bars and under threat of being convicted of betraying the Society. Poincy wouldn't hesitate to tarnish the Monper name if I don't carry out his 'request'. It was written all over his face. So I will be off to Blueweld to find a way to approach Svenson. In the meantime, you think about what else you've 'forgotten' to tell me. For example, this is the first time I've heard from you about some Indian gold that you were supposed to bring to de Poincy.";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "There are things that are better left hidden. You are right, I didn't tell you everything I know. Perhaps, one day I will tell you more, but not before you deal with Levasseur; it would be useless knowledge for now.\nI have no doubt that your touching concern for me is motivated only by your wish to save the honour of our family. By saving me, you are saving yourself first and foremost, and secondly, your chance to visit the finest houses in Paris. Am I wrong?";
			link.l1 = "I'm afraid it is no longer so, brother. You were right. These past months I have spent in the Caribbean have changed every fibre of me and my entire outlook. And I'm sure it's for the better. I don't really need those Parisian parlours anymore and will be able to go on without the name Monper one day. De Maure isn't any worse...";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "...";
			link.l1 = "And now the only thing that truly pains me is the fact that your disgrace will leave a stain on our old father. He doesn't know the real situation or what's actually happening here. Also, as you rightly said, the patrimony must be restored from its dire state. And the million paid for your freedom has considerably depleted my treasury, so it will certainly need replenishing.";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			dialog.text = "You have excellently grasped all of life's lessons, Charles. I am truly happy for you. And I'm glad that you went ahead and accepted de Poincy's request instead of sailing home to France. I hope everything turns out well for you and that you will be able to carry out what I was not able to do myself.";
			link.l1 = "I'm afraid I have no choice. Since my first day in the Caribbean, I've been doing everything alone. See you later, Michel. I think our next meeting will include the order for your release.";
			link.l1.go = "saga_17a";

		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "saga_17a":
            dialog.text = "Wait a minute! Before you go to Jan Svenson, make sure to pay Marcus Tyrex a visit - he is the Keeper of the Code. He rules La Vega on Hispaniola. He has limitless authority among pirates, and the Spanish fear him to death.";
			link.l1 = "Could he help me with our matter?";
			link.l1.go = "saga_17b";
		break;
		
		case "saga_17b":
            dialog.text = "Doubt it. I can't really tell which side he's on; most likely, he stands only for himself. You will need the Shark and Svenson anyway, but at this moment, Tyrex is the most powerful pirate out here. They elected him as the Code Keeper for a reason. You shouldn't ignore such an important figure. It could prove useful to get to know the pirates better before you meet Svenson. You may even make a name for yourself among them...";
			link.l1 = "And yet again, we are back to the pirate talk. No way am I getting away from it, huh? Very well. I will pay him a visit.";
			link.l1.go = "saga_17c";
		break;
		
		case "saga_17c":
            dialog.text = "To be a pirate and to do business with them are two entirely different things, brother. I hope you will see the difference. Go to La Vega and ask Tyrex for a job. If you two don't get along - forget him and come back to me.";
			link.l1 = "Very well, Michel. See you!..";
			link.l1.go = "saga_17d";
		break;
		
		case "saga_17d":
            DialogExit();
			AddQuestRecord("Sharlie", "22");
			npchar.greeting = "mishelle_3";
			pchar.questTemp.Mtraxx = "to_lavega";
			pchar.questTemp.Saga = "pirate_line";
			AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
			AddMapQuestMarkCity("LaVega", false);
		break;
		
		case "saga_17e":
            dialog.text = "At least you tried. You had the opportunity to 'get acquainted' with an infamous pirate baron. Never mind. Go to Jan Svenson, he is in Blueweld. Try to make him your ally, or our dealings with Levasseur will turn into bloodshed.";
			link.l1 = "Fine. I am on my way.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17f":
            dialog.text = "Glad you stopped, brother. I once told you that it's a completely different thing to be a pirate and to do business with them. And you have lost your way. I hope you won't make the same mistake with the Shark and Svenson. Do the job, but keep your distance from them. You are a French nobleman after all, so rise above them. Now go to Jan Svenson, he is in Blueweld. Try to make him your ally, or our dealings with Levasseur will end in bloodshed.";
			link.l1 = "Fine. I am on my way.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17g":
            dialog.text = "I am very glad to hear it, if you are telling the truth. But can I really trust the word of a pirate who burns cities, even if they are Spanish, and murders civilians, including women?";
			// belamour legendary edition -->
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice"))
			{
				if(pchar.questTemp.Mtraxx.Retribution.Choice == "good")
				{
			link.l1 = "Stop... I am truly sorry for what I did during my time with Tyrex. I have seen hell with my own eyes, brother... No, it's over! I am done with piracy and there is no way I am setting foot in La Vega again. I will do whatever it takes to restore my good name.";
			link.l1.go = "saga_17gx";
				}
				if(pchar.questTemp.Mtraxx.Retribution.Choice == "bad")
				{
					link.l1 = "Believe it or not. You're behind bars, not me.";
					link.l1.go = "saga_17gxa";
				}
			}
			else //заглушка
			{
				link.l1 = "Stop it... I truly repent for the abominations I committed while working with Tyrex. I have seen hell with my own eyes, brother! .. No, my pirate days are over! I'm not in La Vega anymore. I will do everything I can to restore my good name.";
				link.l1.go = "saga_17gx";
			}
		break;
		
		case "saga_17gxa":
            dialog.text = "Oh, brother... Don't anger God... I hope this doesn't happen again with Svenson and Shark. Do what you must, but keep your distance and remember what kind of people these are. It is unseemly for a French nobleman to become like them. Rise above it. Now go to Jan Swenson in Blueweld and try to find a way to approach the old corsair. Without him, it will not be possible to resolve the issue with Levasseur with minimal bloodshed.";
			link.l1 = "Fine. I won't delay.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;

		case "saga_17gx":
            dialog.text = "You will have to put great effort into it, brother. Do you remember what I told you once before? That it's a totally different thing - to be a pirate and to do business with them. You... Forget it, I hope you will not make the same mistake with the Shark and Svenson. Do the job but keep your distance from them. You are a French nobleman after all, so be above them. Now go to Jan Svenson, he is in Blueweld. Try to make him your ally or our dealings with Levasseur will turn into bloodshed.";
			link.l1 = "Fine. I am on my way.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;
		
		case "saga_17":
			DialogExit();
			AddQuestRecord("Sharlie", "22_1");
			pchar.questTemp.Saga = "blueveld";
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			npchar.greeting = "mishelle_3";
			if(CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince"))
			{
				DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince");
				SetFunctionTimerCondition("DelCharleePrince", 1, 0, 0, false);
			}
			AddMapQuestMarkCity("SantaCatalina", false);
			AddLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("JS_girl"), "questmarkmain");
		break;
		
		case "Base_fight":
			dialog.text = "Now is not the right time for conversation, brother! The enemy is in our refuge!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Base_fight";
		break;
		
		case "Base_afterfight":
			sTemp = "";
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip()) sTemp = "I see you've become a captain of the navy... I didn't see that coming to be honest. I truly congratulate you!";
			dialog.text = "You're right on time, dear brother! I'm so happy to see you! These damned Castilians have already completely taken over Saint-Pierre. I thought we were done for, for sure! "+sTemp+"";
			link.l1 = "We're not out of the woods yet, the city is clear but the scumbags are holed up at the fort and there's a huge squadron led by a battleship. But I do bring you rather delightful news: Michel, you're free!";
			link.l1.go = "Base_afterfight_1";
		break;
		
		case "Base_afterfight_1":
			dialog.text = "I can't believe my ears! Can it truly be? Freedom?!";
			link.l1 = "Levasseur is dead, Tortuga is now led by your former commander, and the old fox Poincy has dropped all charges against you. From now on, nothing threatens our good name.";
			link.l1.go = "Base_afterfight_2";
		break;
		
		case "Base_afterfight_2":
			dialog.text = "I doubted until the last minute... You have surprised me, Charles, and succeeded where I suffered a distressing fiasco.";
			link.l1 = "Audaces fortuna juvat, brother... As you can see, I know Latin too by now. Where is the key to your cell?";
			link.l1.go = "Base_afterfight_3";
		break;
		
		case "Base_afterfight_3":
			dialog.text = "The key to my casemate should be on the orderly officer's desk. Look for it there. Maybe it's fallen onto the ground and slid somewhere...";
			link.l1 = "I'll go find them and I'll be back!";
			link.l1.go = "Base_afterfight_4";			
		break;
		
		case "Base_afterfight_4":
			DialogExit();
			pchar.questTemp.Sharlie.DefendSP.SeekKey = true;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Base_afterfight_6":
			dialog.text = "At last - freedom! I’ve waited so long for this moment!";
			link.l1 = "You’ve no idea how long I’ve waited for this as well! Michel, can we rally any men to fight back?";
			link.l1.go = "Base_afterfight_7";			
		break;
		
		case "Base_afterfight_7":
			dialog.text = "What have you got in mind, Charles?";
			link.l1 = "The threat posed by the Spanish has not yet vanished. I want to drive them out of the fort and then join forces to attack the squadron from both land and sea! By using the cannons from the bastion, I will be able to engage the battleship!";
			link.l1.go = "Base_afterfight_8";			
		break;
		
		case "Base_afterfight_8":
			dialog.text = "We've got manpower. A large number of knights have left to protect the governor's palace. We'll definitely be able to find someone in the city... I'll gather everyone I can find. See you beyond the city gates!";
			link.l1 = "...";
			link.l1.go = "Base_afterfight_9";			
		break;
		
		case "Base_afterfight_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, ""); // скрытое бессмертие
			LAi_SetHP(npchar, 500, 500);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 30.0);
			pchar.quest.DefendSP_base2.win_condition.l1 = "location";
			pchar.quest.DefendSP_base2.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.DefendSP_base2.function = "DefendSP_CloseTown";
			AddQuestRecord("Sharlie", "36");
		break;
		
		case "Fort_attack":
			dialog.text = "Here it is, brother, our army. All the people I was able to find. Not much in terms of numbers, but we will fight for our Fatherland! We'll knock these bloody intruders clear out of the fort! The element of surprise will help us - they are not expecting our attack. Onward!";
			link.l1 = "Dulce et decorum est pro patria mori! Onward!";
			link.l1.go = "Fort_attack_1";
		break;
		
		case "Fort_attack_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			for (i=1; i<=7; i++)
			{
				sld = CharacterFromID("DefendSP_frafort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", true);
			pchar.quest.DefendSP_fort2.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort2.win_condition.l1.location = "FortFrance_fort";
			pchar.quest.DefendSP_fort2.function = "DefendSP_FortBattle";
			locations[FindLocation("FortFrance_fort")].QuestCapture = true;
		break;
		
		case "Fort_attack_2":
			dialog.text = "It is done, brother! The fort is ours!";
			link.l1 = "It's a pity that it took such a hit in the battle with the Spanish squadron... but it is still quite capable of leading a fight.";
			link.l1.go = "Fort_attack_3";			
		break;
		
		case "Fort_attack_3":
			dialog.text = "I'll play my part. We'll load the cannons and deal the enemy a hefty blow! But only after we see your squadron approaching, or else the man-of-war will quickly blast us to sawdust.";
			link.l1 = "Gather the people, Michel! I'm heading straight back to the shore!";
			link.l1.go = "Fort_attack_4";			
		break;
		
		case "Fort_attack_4":
			dialog.text = "Charles, remember: the most dangerous part of the squadron is the man-of-war! Try to take her out first. We'll also concentrate fire on her with what's left of the fort's battery.";
			link.l1 = "All right, brother. Perhaps I should capture her.";
			link.l1.go = "Fort_attack_5";			
		break;
		
		case "Fort_attack_5":
			dialog.text = "Judging by the circumstances, I'm not the one who should be teaching you. Now we should stop wasting our time!";
			link.l1 = "...";
			link.l1.go = "Fort_attack_6";			
		break;
		
		case "Fort_attack_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Shore38", "boat", false); // выпустить в море
			// закрываем городские заведения
			for (i=3; i<=10; i++)
			{
				LocatorReloadEnterDisable("FortFrance_town", "reload"+i+"_back", true);
			}
			LocatorReloadEnterDisable("FortFrance_town", "reload91", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", true);
			pchar.quest.DefendSP_fort3.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort3.win_condition.l1.location = "shore38";
			pchar.quest.DefendSP_fort3.function = "DefendSP_BeforeSeaBattle";
			pchar.quest.DefendSP_sea1.win_condition.l1 = "location";
			pchar.quest.DefendSP_sea1.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_sea1.function = "DefendSP_SeaBattle";
			AddQuestRecord("Sharlie", "37");
		break;
		
		case "Victory":
			dialog.text = "Gloria victorious! Congratulations on your victory, brother! You were magnificent! The Spanish are utterly destroyed!";
			link.l1 = "I hope that will teach them to think twice before attacking French colonies.";
			link.l1.go = "Victory_1";			
		break;
		
		case "Victory_1":
			dialog.text = "Now tell me, Charles: what is your past life worth... compared to this one?";
			link.l1 = "Don't remind me...";
			link.l1.go = "Victory_2";			
		break;
		
		case "Victory_2":
			dialog.text = "Do you remember what I told you during our first meeting here? 'You will love this life,' that's what! Yes, and a huge thanks to you, brother, for your help. Without you, I'd likely never have managed to escape the confines of that underground base.";
			link.l1 = "Don't mention it, Michel. You are my brother after all, and I was obliged to help you.";
			link.l1.go = "Victory_3";			
		break;
		
		case "Victory_3":
			dialog.text = "Just look at you, brother, I am impressed: so much strength in your eyes, confidence in your movements, stature in your posture... where did that wretched artist and court jester go? Indeed! You have surpassed my boldest expectations; truth be told, I never thought that you would become... this.\nIt even... frightens me a little. Because you will stop at nothing to achieve your goal. You are good, too good...";
			link.l1 = "For some reason, I'm having trouble understanding you once again. Are you unhappy with me again?";
			link.l1.go = "Victory_4";			
		break;
		
		case "Victory_4":
			dialog.text = "No! What are you talking about?... Not at all! I was just channelling my excitement.";
			link.l1 = "All right. So, what will you do next, brother? Will you continue serving the Society? Or will you return to our patrimony? Yes, and I almost forgot: you promised to tell me about one thing.";
			link.l1.go = "Victory_5";			
		break;
		
		case "Victory_5":
			dialog.text = "About what exactly?";
			link.l1 = "About your service for de Poincy. About some Indian gold you were supposed to bring him. About everything that led to your imprisonment. There's a lot you haven't managed to tell me, Michel, leaving me pretty much in the dark. So...";
			link.l1.go = "Victory_6";			
		break;
		
		case "Victory_6":
			dialog.text = "Brother, I remember exactly what I said. I will tell you everything. But not in the middle of a burning city!\nWe both have plenty to do now. You need to settle your squadron, repair it, and get the ships ready again. The governor and I will organise and calm the locals.\nWe will discuss everything tomorrow morning over a glass of good French wine. Trust me, brother, I have a big plan. A truly big one. But not now. Visit Abbot Benoit tomorrow at nine a.m. I will spend the night at his place; he is an old friend of mine.";
			link.l1 = "Alright, Michel. It's settled then. I'll be looking forward to our conversation tomorrow.";
			link.l1.go = "Victory_7";			
		break;
		
		case "Victory_6A":
			dialog.text = "Диалог 28.";
			link.l1 = "Alright, Michel. It's settled then. I'll be looking forward to our conversation tomorrow.";
			link.l1.go = "Victory_7";
		break;
		
		case "Victory_7":
			dialog.text = "No need for goodbyes, Charles!";
			link.l1 = "...";
			link.l1.go = "Victory_8";			
		break;
		
		case "Victory_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "DefendSP_OpenExit", -1);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Sharlie", "39");
			pchar.quest.DefendSP_final.win_condition.l1 = "Timer";
			pchar.quest.DefendSP_final.win_condition.l1.date.hour  = 9;
			pchar.quest.DefendSP_final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.DefendSP_final.function = "DefendSP_finaltalk";
			// раздача экспы
			ChangeCharacterNationReputation(pchar, FRANCE, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 10);
			AddComplexSeaExpToScill(500, 500, 500, 500, 500, 500, 0);
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 1000);
			AddSimpleRumour("All those residing in the French colony owe you, Captain. Defending Saint-Pierre from the vile attack of the Spanish is quite a feat!", FRANCE, 30, 15);
			AddSimpleRumour("It's an honor for me to speak with the brave Captain that has beaten a bunch of Spanish invaders hollow!", FRANCE, 30, 15);
			AddSimpleRumour("The French colonists may sleep in peace, while brave naval officers such as you are at the King's service!", FRANCE, 30, 15);
			AddSimpleRumourCity("We are all forever indebted to you, Captain! You have saved our colony from devastation!", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("You are a brave and astute naval officer. All those residing in Saint-Pierre are praying for you, know that!", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("You are the pride and joy of our nation and the hero of Saint-Pierre. We will never forget that!", "FortFrance", 30, 15, "");
			npchar.greeting = "mishelle_0";
		break;
		
		case "kukulkan":
			PlaySound("Voice\English\sharlie\mishelle-04.wav");
			dialog.text = "So we meet again, "+pchar.name+". Despite my warnings, you still went on searching for me, and your search has brought you far, far away...";
			link.l1 = "Michel?... For some reason I'm not surprised. Has Miguel Dichoso returned to Tayasal for another heap of treasure? Hm-hm-hm. Yes, I have been seeking a meeting with you, dear brother. I was simply dying to look into your shameless eyes. On top of that, your attempt to assassinate me at the graveyard crypt was the icing on the cake. But first, tell me, how should I address you? Michel de Monper or Miguel Dichoso?";
			link.l1.go = "kukulkan_1";			
		break;
		
		case "kukulkan_1":
			dialog.text = "These names are no longer important, "+pchar.name+". It's all in the past, which will very soon disappear even from history itself. Now is the moment of truth, which I've been inching towards for a long quarter of a century since I first made it ashore...";
			link.l1 = "What?!! This... this cannot be!!!";
			link.l1.go = "kukulkan_2";			
		break;
		
		case "kukulkan_2":
			dialog.text = "Yes, "+pchar.name+". I see by your face that you understand who I am, but you can't believe it. I am the one you've aspired to meet these past months. The one with whom the representative of your God, the Inquisitor from Santiago, has blessed you for battle.";
			link.l1 = "Kukulcan?!";
			link.l1.go = "kukulkan_change";			
		break;
		
		case "kukulkan_change":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kukulkan_3":
			dialog.text = "I agree. "+pchar.name+", that it is difficult to believe. Life is more complicated and more surprising than any fairy tale...";
			link.l1 = "I was ready for anything, but... my brother!";
			link.l1.go = "kukulkan_4";			
		break;
		
		case "kukulkan_4":
			dialog.text = "Brother? Only by our father's blood. We have different mothers, "+pchar.name+"Know that my mother was a daughter of Kanek, named Shochikezhal. She was abducted by French privateers under the command of the famous Nicolas Gotier after she foolishly left Tayasal. They decided to enslave her. A man named Serge Benoit was among them. Ashamed of his captain's deed, he left him, took the veil, and now you know him as Abbot Benoit. Henri de Monper, our father, was a navy officer back then. He bought Shochikezhal and took her to France, where she gave birth to me. Around the same time, you were born too, "+pchar.name+". Your mother died in childbirth, and our father declared that his lawful wife had given birth to twins.\nShochikezhal, my mother, became a wet nurse to us both. You were nourished with the milk of an Indian woman of the Itza people, "+pchar.name+"! Later, your grandmother on your mother's side decided to take you in for an education, and you were given your mother's name - de Maure.";
			link.l1 = "How did you find all that out?!";
			link.l1.go = "kukulkan_5";			
		break;
		
		case "kukulkan_5":
			dialog.text = "Wouldn't you think, brother, that I know more than most people? Also, our father has told me a lot and I am aware of much... It's just as they say, by the seat of my pants.";
			link.l1 = "Now it's all clear... And what happened to your mother? Why have I never seen her?";
			link.l1.go = "kukulkan_6";			
		break;
		
		case "kukulkan_6":
			dialog.text = "She died saving my life. A little over a year after my birth, I nearly died from a disease. My mother, the daughter of an Itza priest, conducted a secret Mayan healing ceremony for me. I recovered, but this ceremony was accompanied by some... destructive side effects in the form of thunder, lightning, and a tropical hurricane. Shochikezhal was denounced, accused of sorcery, and burned at the stake by the Inquisition...";
			link.l1 = "And you got better...";
			link.l1.go = "kukulkan_7";			
		break;
		
		case "kukulkan_7":
			dialog.text = "Besides healing me, this ritual granted me other abilities as well, in addition to opening a connection to the world of the gods. And you already know the rest. As you already know, I will bear the light of knowledge and experience of the white race into the past and pass it on to the people of Maya. History will be rewritten and you, whites, will not dominate this world. I will make sure of it.";
			link.l1 = "So your whole life, studying at the best naval academy, serving in the army and in the Order of Malta, was all basically just an accumulation of military experience?";
			link.l1.go = "kukulkan_8";			
		break;
		
		case "kukulkan_8":
			dialog.text = "Exactly. When I realised that I knew enough, I arranged to be assigned to the Caribbean. I talked my way into Chevalier de Poincy establishing a base on Martinique. Next, I had to make my way to Tayasal. It wasn't exactly a simple task for me, as this physical vessel remains mortal and the portals in the Caribbean weren't working properly.";
			link.l1 = "And you became Miguel Dichoso...";
			link.l1.go = "kukulkan_9";			
		break;
		
		case "kukulkan_9":
			dialog.text = "Dear brother, I earned this nickname on the battlefields of Europe. I also met Ramón de Mendoza y Riba there. Do you think that life is made of chances? No, not at all; every chance is an unknown regularity. Much had been done for the sake of my return to Tayasal. I had to live two lives: Michel de Monper and Miguel Dichoso. I also had to make sure people believed them to be different men. I had to turn pirate, just like you, in service to de Poincy in order to gain his trust, favour, and money. I had to murder Blaze Sharp, one of the leaders of the pirates, as a favour for Ramón de Mendoza, in order to get soldiers for the expedition. I had to tempt both de Poincy and de Mendoza with tales of Tayasal's treasures. I received seven hundred and fifty thousand pieces of silver from de Poincy's treasury and sold the Spanish military frigate to the pirate Dodson. And then the expedition happened. I returned to Tayasal only to suffer failure...";
			link.l1 = "I understand... While you were but a five-year-old boy chasing butterflies in our father's patrimony, Kanek the great priest, frightened by Don Alonso de Maldonado's invasion of Tayasal, securely hid the Kukulcan mask which is so vital for travelling into the past... beg your pardon, I meant YOUR mask.";
			link.l1.go = "kukulkan_10";			
		break;
		
		case "kukulkan_10":
			dialog.text = "Yes, Kanek had outsmarted himself there. He performed the most difficult ritual, a ritual even the ancients dared not perform. He hid the mask on the newly formed deserted island and managed to lose the key to Ksocheatem - the so-called Guardian of Truth.\nI had to play it smart. The ritual prevented any ship carrying protected items from Taysal's treasury from leaving the Caribbean, casting such vessels onto the shores of Ksocheatem. I intended to use that. I took enough treasures to appease Mendoza. I also took a special item protected by the ritual.\nA ship with this item aboard would be doomed to be delivered right to Ksocheatem, right to my mask. So I went to sea and let Mendoza know about myself.";
			link.l1 = " So, you left Tayasal on your own?";
			link.l1.go = "kukulkan_11";			
		break;
		
		case "kukulkan_11":
			dialog.text = "You mean without Mendoza's soldiers? Certainly. All the Spaniards were slain here, in Tayasal. The Itzas brought the treasures to the shore themselves, and I told Mendoza that the soldiers had been ambushed by the Miskito people. He believed me, since he was only interested in gold, not in people. I had planned to set up the ship with the treasures under the cannons of the 'Gryffondor', but it all went much better: the baron decided to send the treasures to Spain under my watch. That was the best possible outcome; I only had to wait until the ship crossed the invisible border of the Caribbean. However, it turned out that the captain had different orders. I found out that a special boarding unit was supposed to mutiny as soon as we reached the Atlantic Ocean, killing the crew and all the officers. The captain had orders to return the Indian gold to Mendoza afterwards. Such a fine specimen of the white race, isn't he, brother? I had to risk it; I didn't know when the mutiny was supposed to happen. But it all went according to plan: the storm hit us as soon as the 'Santa Quiteria' reached the eastern side of the island of Trinidad and Tobago. The frigate was swept back into the Caribbean towards Ksocheatem. I then suffered the greatest failure of my life—a wave washed me off the ship, and I found myself at Le Marin Cove on Martinique a couple of days later. Fishermen found me and took me to Le François. But de Poincy's men captured me while I was coming back to life at Cesar Craig's place. The 'Gryffondor' didn't find the 'Santa Quiteria' at the place I had specified. Chevalier de Poincy became furious as soon as he learned that the Indian gold was gone, together with the money taken from the Order's treasury and his own savings. He had me arrested. He couldn't kill me, though—he didn't want to. He wanted gold. Gold! That is the only thing your people want and care about! You will do anything to get it... I was in a terrible position: I had no mask on me, and I was left rotting in a cell without a single coin in my pockets. That was when I summoned you. Yes, yes, dear brother, you were supposed to free me, so I could do what I was born to do. And you did extraordinary work. It seems that the Itza milk you suckled did you some good.";
			link.l1 = "What I'm interested in is what you were counting on when you escaped Saint-Pierre, then? What was your plan?";
			link.l1.go = "kukulkan_12";			
		break;
		
		case "kukulkan_12":
			PlaySound("Voice\English\sharlie\mishelle-05.wav");
			dialog.text = "You were my plan all along, brother. Kukulcan can read people's hearts. The letter I left for you at the Abbot's was meant to make you act. I was right about you. I had been watching your progress ever since you first met the Inquisitor of Santiago. You did everything for me. You crafted the Guardian of Truth. You eliminated the competitors. You found Ksocheatem.\nI was there, following you. Though I didn't expect you to get into Tayasal. You have surpassed all my expectations. And with your help, I will do what I was born to do. The reason I was born in mortal flesh.";
			link.l1 = "There's just one little caveat in your reasoning, dear brother. You don't possess your mask and you are nothing without it. I have it. And I'm not burning with desire to give it to you. I'd sooner blow it to shreds than let it end up in your hands.";
			if (CheckCharacterItem(pchar, "mask_true")) link.l1.go = "kukulkan_13";	
			else link.l1.go = "kukulkan_14";			
		break;
		
		case "kukulkan_13":
			dialog.text = "You can't change what is predetermined by fate. I will not allow you to damage my artefact. I can feel it... It's with you. And you are here, in my temple, within my full power! You will never leave this place. It's time for your final test, dear brother, to see what you are worth in a battle against Kukulcan!";
			link.l1 = "I suppose your mortal body can still bleed!";
			link.l1.go = "kukulkan_fight";		
		break;
		
		case "kukulkan_14":
			dialog.text = "Ha! I feel sorry for you, Charles. This is truly sad. But you deserve a chance to fight a God. Even if it's pointless. I'll tell you later, if you survive the first act.";
			link.l1 = "I suppose your mortal body can still bleed!";
			link.l1.go = "kukulkan_fight";			
		break;
		
		case "kukulkan_fight":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "item", "button04");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "quest", "defend1", "", -1);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "defend2", "", -1);
			DoQuestFunctionDelay("Tieyasal_TempleFightGuard", 3.0);
		break;
		
		case "kukulkan_twice": // развилка финалов - есть настоящая маска или нет
			if (CheckCharacterItem(pchar, "mask_true"))
			{
				dialog.text = "";
				link.l1 = "It seems your powers are leaving you, great Kukulcan... You may be strong, but your body is still mortal!";
				link.l1.go = "kukulkan_win";
			}
			else
			{
				dialog.text = "I think that will be enough entertainment. You are truly a master swordsman and a great fighter, I would even dare to say the greatest warrior of your time, but this battle you have lost. "+pchar.name+"...";
				link.l1 = "We're just...";
				link.l1.go = "kukulkan_fail";
			}
		break;
		
		case "kukulkan_fail":
			DialogExit();
			SetMusic("music_teleport");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "attack_force_1", "Tieyasal_KukulkanKick", 1.0);
			LaunchBlast(npchar);
			PlaySound("Sea Battles\udar_metal_003.wav");
		break;
		
		case "kukulkan_fail_1":
			dialog.text = "Enough, dear brother. You cannot withstand the power of Kukulcan when he is united with his artefact! I have allowed you to live for so long just to see what you have truly been able to achieve.";
			link.l1 = "Fuck... That last blow... But which artifact are you talking about? The mask? It's with me!";
			link.l1.go = "kukulkan_fail_2";
		break;
		
		case "kukulkan_fail_2":
			dialog.text = "Poor, poor Captain "+GetFullName(pchar)+"... You have come this far, survived all dangers, slain many of the strongest enemies only to be defeated in the end!.. The jade mask you found inside the metal box near the wrecks of the 'Santa Quiteria' on Ksocheatem is a fake! It is merely an ancient mask from Taysal's treasury. It is NOT THE MASK OF KUKULCAN!.\nI personally took it from here after my failed expedition; it is guarded by the ancient ritual. This mask was the reason why the storm carried the Santa Quiteria away to Ksocheatem. It also had a second purpose. It was meant to deceive anyone who came there seeking my TRUE artefact.";
			link.l1 = "But... Where was the real mask then?! I searched all over Ksocheatem!..";
			link.l1.go = "kukulkan_fail_3";
		break;
		
		case "kukulkan_fail_3":
			dialog.text = "You haven't, "+pchar.name+". My artefact was lying on the opposite side of the island from the 'Santa Quiteria', in a securely guarded sanctuary. The road there leads through underground caverns. It's complicated to find and not obvious to the unrefined eye of a mortal. There it is! Take a good look at it, one final look...";
			link.l1 = "It can't be!";
			link.l1.go = "kukulkan_fail_4";
		break;
		
		case "kukulkan_fail_4":
			dialog.text = "You survived and won many battles, brother. But you've lost this one, "+pchar.name+"...";
			link.l1 = "And what now?";
			link.l1.go = "kukulkan_fail_5";
		break;
		
		case "kukulkan_fail_5":
			dialog.text = "I will travel directly to the tenth century, seven centuries back. This will be enough for the Maya civilisation to achieve unshakable military and scientific supremacy over the white race.";
			link.l1 = "And what will happen to our world? Will it disappear?";
			link.l1.go = "kukulkan_fail_6";
		break;
		
		case "kukulkan_fail_6":
			dialog.text = "No. It will change. Perhaps there will be a place for you, but you will remember nothing of what happened in this world. Some of those who were born here will never be born there, the opposite is also true. The dead will come back to life and the living will die, one way or another, everyone will be reborn. Suum cuique, to each his own, "+pchar.name+".\nDon't be afraid, little brother. You will never realise what has happened and you will naturally embrace the new reality. Only I, Kukulcan, will keep the memories... But enough! Kanek has already prepared everything for the ritual.\nYou will follow me, "+GetFullName(pchar)+", and you will witness the final moments of this reality's existence which you were so eager to preserve.";
			link.l1 = "...";
			link.l1.go = "kukulkan_fail_7";
		break;
		
		case "kukulkan_fail_7":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Tieyasal_Fail_ReloadTown", 2.0);
		break;
		
		case "kukulkan_fail_8":
			dialog.text = "The gates of time have opened! Rejoice, my children, as you stand so close to greatness! We shall create a new world, a world with no place for the pale invaders!\nFarewell, "+pchar.name+", and be ready to accept your new fate, whatever it may be. Suum cuique!";
			link.l1 = "...";
			link.l1.go = "kukulkan_fail_9";
		break;
		
		case "kukulkan_fail_9":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "kukulkan", "", -1);
			DoQuestCheckDelay("Tieyasal_Fail_TeleportStart", 4.0);
		break;
		
		case "kukulkan_win":
			dialog.text = "This battle is not over yet, mortal. You are clearly exhausted, and I have reinforcements on the way! You will surrender my artefact. Either that, or I shall take it from your corpse – it makes no difference to me...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_PrepareToWinBattle");
		break;
		
		case "kukulkan_win_1":
			dialog.text = "Urakan! I order you to kill this man at once!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_2";
		break;
		
		case "kukulkan_win_2":
			dialog.text = "Urakan! Didn't you hear me? I repeat: I order you and your warriors to capture and kill this man!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_3";
		break;
		
		case "kukulkan_win_3":
			dialog.text = "Urakan! What the hell? Kanek! Repeat my order to your bloody son!!!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_4";
		break;
		
		case "kukulkan_win_4":
			DialogExit();
			sld = characterFromId("Kanek");
			sld.dialog.currentnode = "kanek_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "kukulkan_win_5":
			dialog.text = "You betray your people, Urakan! You have quailed in the face of such momentous transformations! Warriors, I order you to capture and put to death not only this man who calls himself my brother, but Urakan the traitor as well!";
			link.l1 = "Warriors, in the name of Cavil and Hurakan I order you to stand as you are, if you value your life! Not one of you would survive a fight against Cavil! Let the gods themselves decide who among them is the strongest on Earth!";
			link.l1.go = "kukulkan_win_6";
		break;
		
		case "kukulkan_win_6":
			DialogExit();
			LAi_SetActorType(PChar);
			LAi_ActorTurnToCharacter(PChar, characterFromID("Mishelle"));
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.8);
		break;
		
		case "kukulkan_win_7":
			dialog.text = "";
			link.l1 = "This day just keeps getting better and better. You didn't expect things to turn out this way, did you, brother? The gods must decide for themselves who among them is truly the strongest. And everyone will get what they deserve, Michel. Suum cuique! To each his own...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_WinBattleStart");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
