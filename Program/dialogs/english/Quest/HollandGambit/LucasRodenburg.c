// Лукас Роденбург - вице-директор ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl"))
			{
				dialog.text = "Speak up boy, but be quick. I'm a busy man .";
				link.l1 = "I heard that you are hiring captains.";
				link.l1.go = "Holl_start";	
			break;
			}
			dialog.text = "Do you have any business for me?";
			link.l1 = "No, sorry. I'm leaving.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Second_time":
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "BaltazarEsc")
			{
				dialog.text = "You were supposed to be halfway to Sint Maarten by now, kapitein.";
				link.l1 = "I am preparing to set sail, mynheer.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "BaltazarCom")
			{
				dialog.text = "Ah, kapitein, there you are! I didn't see you coming, I have just finished reading Ridderbrock's letter. You made quite the impression. He calls you the 'guardian of merchants and scourge of pirates. God's gift to the Company!' What say you about that?";
				link.l1 = "I'd prefer to stay just an ordinary captain. An ordinary yet rich captain.";
				link.l1.go = "SantiagoTrip";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				dialog.text = "Why are you still here and not en route to Cuba?!";
				link.l1 = "Yes, yes, I am on my way, mynheer.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripFinal")
			{
				sld = characterFromId("Santiago_usurer");
				dialog.text = "Ah, kapitein! I admit that I was starting to worry. How was it?";
				link.l1 = "It was not without trouble, but I'll tell you about that later. Business first. Senor " + GetFullName(sld) + " told me to say you the following: 'this man has to die'. Then Geraldi will consider the incident settled. Also, he said that this decision is the will of their family.";
				link.l1.go = "SantiagoTrip_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripComplete")
			{
				dialog.text = "Glad to see you, kapitein! It's good you came to see me.";
				link.l1 = "Good day, mynheer. I take it that you have another Company job for me?";
				link.l1.go = "JacobBerg";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobTakeShip")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
				{
					dialog.text = "I have told you to moor your ship. Are you too stupid or ignorant to follow direct orders?";
					link.l1 = "Neither, mynheer. I am on my way.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "So, you have moored your ship. Now I will lend you my xebec. Are you ready to get this mission started immediately? My ship is well equipped and ready to sail so there is nothing left to worry about for you.";
					link.l1 = "Yes, sure. I am ready, Mynheer Rodenburg.";
					link.l1.go = "JacobBerg_6";
					DelLandQuestMark(npchar);
				}
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobLongway")
			{
				dialog.text = "Why are you still here? Go see Longway at once.";
				link.l1 = "Sorry, I'm on my way.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MirageTake")//а вот теперь начинается дурдом с перебором кораблей
			{
				int iMir = 0;
				int iMef = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG) iMef = 1;
				}
				}//установили признак наличия кораблей в эскадре.
				RemoveItems(PChar, "JacobJournal", 1);//удалим журнал ван Берга
				pchar.quest.MirageConvoyOver.over = "yes"; //снять таймер
				if (iMir == 1 && iMef == 0)//потеряли Мейфенг
				{
					dialog.text = "Kapitein... I am already aware about your voyage.";
					link.l1 = "Oh, really? So you must know that...";
					link.l1.go = "Jacob_lostMef";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 1)//потеряли Мираж
				{
					dialog.text = "Kapitein... I am already aware about your voyage.";
					link.l1 = "Is that so? So you must know that...";
					link.l1.go = "Jacob_lostMir";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 0)//а это вообще плохо
				{
					dialog.text = "Kapitein... I am already aware about your voyage.";
					link.l1 = "Is that so? So you must know that...";
					link.l1.go = "Jacob_failFull";
					DelLandQuestMark(npchar);
					break;
				}
					dialog.text = "Here you are, Kapitein... I already know everything about your trip.";
					link.l1 = "Is that so? So you must know that...";
			link.l1.go = "Jacob_complete";
			DelLandQuestMark(npchar);
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Get to Antigua. Now.";
				link.l1 = "Sorry, I'm on my way.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink" || pchar.questTemp.HWIC.Holl == "FleetwoodCapture")
			{//опять начинаем проверять корабли
				iMir = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					}
				}//установили признак наличия Миража в эскадре.
				pchar.quest.ToAntiguaOver.over = "yes"; //снять таймер
				if (iMir == 0)//потеряли Мираж
				{
					dialog.text = "I was informed of your arrival, kapitein. I also know that you have lost my Mirage in battle.";
					link.l1 = "You are well informed, Mynheer Rodenburg. Despite all of my efforts we weren't able to save her.";
					link.l1.go = "Fleetwood_fail";
					DelLandQuestMark(npchar);
				}
				else
				{
					dialog.text = "I was informed of your arrival, kapitein. I see that the Mirage is safely docked. This is good.";
					link.l1 = "It was all by your instructions, mynheer. You ordered me to kill Fleetwood and he is dead. You ordered me to bring the Mirage back to the local port and she is here.";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
				}
				pchar.quest.Meifeng_fail.over = "yes";
				Group_DeleteGroup("Meifeng_Empty");
				sld = characterFromId("MeifengCap");
				sld.lifeday = 0;//зачистим Мейфенг без китайца
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "Abby_prepare")
			{
				dialog.text = "Ah, here you are. Good to see you. I have another mission for you, just as promised.";
				link.l1 = "I am listening, mynheer.";
				link.l1.go = "Abby";
				DelLandQuestMark(npchar);
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "Ah, I am glad to see you, my boy. You were late in coming and I had started to worry. Were you able to get anything from Abigail?";
				link.l1 = "Not only that, I have solved your other problems as well. I have found the island and the Shneur's lost fortune. Solomon is happy and Abigail will say yes to your proposal. Congratulations, mynheer!";
				link.l1.go = "Abby_2";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "NotFindAbbyIsland")
			{
				dialog.text = "Ah, I am glad to see you, my friend. Were you able to get anything from Abigail?";
				link.l1 = "Yes. I had a talk with Abigail and her father. There is a problem, mynheer: her father's lost fortune. Abigail feels unworthy of you, she fears of people's gossip and whispers if her as a dowryless girl would marry a gentleman such as yourself. I hope that you understand.";
				link.l1.go = "Abby_6";
				DelLandQuestMark(npchar);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "Ah, my friend! I trust that you have brought good news?";
				link.l1 = "Your plan was successful. Abigail will say yes. Congratulations, mynheer.";
				link.l1.go = "Abby_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokStart")
			{
				dialog.text = "I have been awaiting you. My boy, you are in great danger.";
				link.l1 = "What do you mean?";
				link.l1.go = "Merdok";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokDie")
			{
				dialog.text = "My agents at the dock told me that you had arrived. Is Johan van Merden dead?";
				link.l1 = "Yes. He and his accomplice are gone. It was a tough fight, but I saw it through.";
				link.l1.go = "Merdok_4";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "We have nothing further to discuss, kapitein.";
			link.l1 = "Understood, I'm leaving.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "What is it? Time is money.";
		link.l1 = "Sorry, I'm leaving.";
		link.l1.go = "exit";
		break;
		
//------------------------------------------------1 задание--------------------------------------------
		case "Holl_start":
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
			DelLandQuestMark(characterFromId("Knippel"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Perhaps. Who are you? Speak quickly, time is money.";
			link.l1 = "I am captain " + pchar.name + ", my ship and  can be useful to you.";
			link.l1.go = "Holl_start_0";			
		break;
		
		case "Holl_start_0":
			dialog.text = "Hm, an unknown alloy to be assayed in the crucible.";
			link.l1 = "That is why I am here, mynheer.";
			link.l1.go = "Holl_start_1";			
		break;
		
		case "Holl_start_1":
			pchar.questTemp.HWIC.Holl.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Very well, we will see the color of your mettle. Alright Kapetein whatever your name is, do you know Balthazar Ridderbrock? No? How fortunate. Such greedy, grumpy, hot-tempered idiots such as he are rare sights.\nBut it seems that such outstanding qualities were not enough for the man, so he was smart enough to offend a filibuster by the name of " + GetName( NAMETYPE_ORIG, pchar.questTemp.HWIC.Holl.PirateName, NAME_NOM) + " in the local tavern and called the guard on him the very moment the offended party touched a sword...";
			link.l1 = "...and they had the pirate hung with the first free rope?";
			link.l1.go = "Holl_start_2";			
		break;
		
		case "Holl_start_2":
			dialog.text = "It is not that simple. " + GetName( NAMETYPE_ORIG, pchar.questTemp.HWIC.Holl.PirateName, NAME_NOM) + " is not a common pirate, but a Dutch privateer, a veteran of the last two wars with the Brits. The local taxpayers are quite fond of him. I can't say the same about Ridderbrock.";
			link.l1 = "So our privateer is still alive?";
			link.l1.go = "Holl_start_3";			
		break;
		
		case "Holl_start_3":
			dialog.text = "Yes, but he is really angry. That is why Ridderbrock is scared shitless.";
			link.l1 = "I suppose, that my good fortune is about to end. When do I meet Mynheer Ridderbrock?";
			link.l1.go = "Holl_start_4";			
		break;
		
		case "Holl_start_4":
			dialog.text = "Imminently. The good people of Philipsburg are awaiting a shipment of sugar, one which our mutual acquaintance Ridderbrock promised to deliver. I don't consider the man worth the leather of his boots, but alas he works for us, so get ye to the harbor office. Find Ridderbrock there and tell him that I ordered him to set sail immediately.\nYou shall shadow him, and...escort him to Philipsburg in one piece. I don't want " + GetName( NAMETYPE_ORIG, pchar.questTemp.HWIC.Holl.PirateName, NAME_NOM) + " to send the reputation of the Company to the bottom of the Caribbean along with his cargo.";
			link.l1 = "Ugh, an escort mission. What about payment for this...unpleasant assignment?";
			link.l1.go = "Holl_start_5";			
		break;
		
		case "Holl_start_5":
			dialog.text = "Kapitein, do the job first. Balthazar will pay you as soon as he reaches his destination. At Philipsburg! Not Davy Jones' Locker! Afterwards report back to me once the job is done. If you are successful you will be able to count on my further patronage and that of the Company. Dismissed.";
			link.l1 = "See you, mynheer.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Create_Baltazar");
			pchar.questTemp.HWIC.Holl = "BaltazarEsc";
			NextDiag.TempNode = "Second_time";
			pchar.quest.HWIC_ReturnOfficer.over = "yes";//чтобы офицер не доставал
			pchar.questTemp.HWIC.CanTake.Holl = "true";//признак, что голландка уже бралась
		break;
		
//----------------------------------------------задание 1а--------------------------------------------	
		case "SantiagoTrip":
			dialog.text = "Yes, Ridderbrock is a miserly whoreson even for a fellow Dutchman. Whatever, he is no concern of mine any longer. Let's talk about you, Kapitein Whatever Your Name Is. I like your style, so I am going to offer you another job. This time I will pay for it myself.";
			link.l1 = "I am listening, mynheer.";
			link.l1.go = "SantiagoTrip_1";			
			AddSimpleRumourCity("Ah, so you are the brave kapitein who escorted that scoundrel Ridderbrock? We heard all about about it... He paid you only five thousand pesos! He's been boasting about it nonstop at the tavern in Philipsburg drunk as a swine. If I were you captain, I drag him out into the street and thrash him.", "Villemstad", 20, 3, "");//слух по 1 заданию
		break;
		
		case "SantiagoTrip_1":
			dialog.text = "I need a man for a very important matter. You did well with the Ridderbrock case so the Company believes that I can entrust it to you.";
			link.l1 = "I guess that I'm honored. What's the matter?";
			link.l1.go = "SantiagoTrip_2";
		break;
		
		case "SantiagoTrip_2":
			sld = characterFromId("Santiago_usurer");
			dialog.text = "I can not give you exact details, but be aware that this is not my job, this is the Company's, so you have a chance to get into our good graces, Which I assure you are very profitable.\nSail to Santiago in Cuba and deliver this package to Don " + GetFullName(sld) + ". He has a high position in Geraldi's bank and he is also my... our business partner. You are to deliver him this gold which I will give you right now. I trust your honesty, kapitein. Well, if not your honesty than your survival instinct. The Company always finds those who try and steal from us.";
			link.l1 = "Do you doubt me, mynheer?";
			link.l1.go = "SantiagoTrip_3";
		break;
		
		case "SantiagoTrip_3":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) sTemp = " I am also giving you this short-term Company trade license in order to spare you from any diplomatic entanglements with the Spanish. This will allow you to dock at Spanish colonies for some time.";
			else sTemp = "";
			dialog.text = "At the moment, I do not doubt you. Trust me, I wouldn't even talk with you about this matter if I did. Know that we wasted a lot of time lining this job up, so you have only fifteen days to deliver."+sTemp+"\nMy message and package must be delivered in time. This is vital, boy. Hurry, but be careful, this isn't going to be a milk run.";
			link.l1 = "Anything else? Why do you warn me, mynheer Rodenburg?";
			link.l1.go = "SantiagoTrip_4";
		break;
		
		case "SantiagoTrip_4":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) GiveNationLicence(HOLLAND, 20);
			dialog.text = "Let's just say that I have my suspicions. Don't worry, if you do it as fast as you did the last job then you will have a chance to become a valuable agent for delicate matters of the Company.";
			link.l1 = "All I have is to deliver this letter and money to the banker at Santiago in fifteen days? Doesn't sound too difficult on the surface.";
			link.l1.go = "SantiagoTrip_5";
		break;
		
		case "SantiagoTrip_5":
			dialog.text = "Not so fast boy... I take it that you don't really grasp the gravity of this situation. Doing this job will make me very obliged to you. On the other hand, failing it will make me very pissed off. In that case I will then piss on you. Do we understand each other, kapitein " + GetFullName(pchar) + "?";
			link.l1 = "Point taken. You have my word. I will do my best to keep you in good mood.";
			link.l1.go = "SantiagoTrip_6";
		break;
		
		case "SantiagoTrip_6":
			dialog.text = "Very well. Now, take the letter, these chests and remember the terms and conditions. And one more thing: stay out of trouble in Santiago.";
			link.l1 = "Very well.";
			link.l1.go = "SantiagoTrip_7";
		break;
		
		case "SantiagoTrip_7":
			DialogExit();
			GiveItem2Character(pchar, "NPC_Letter");
			ChangeItemDescribe("NPC_Letter", "itmdescr_NPC_Letter4");
			TakeNItems(pchar, "chest", 5); 
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 32, false);
			}
			else SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 16, false); //таймер
			AddQuestRecord("Holl_Gambit", "1-43");
			pchar.questTemp.HWIC.Holl = "SantiagoTripBegin";
			AddMapQuestMarkCity("Santiago", true);
			AddLandQuestMark(characterFromId("Santiago_usurer"), "questmarkmain");
		break;
		
		case "SantiagoTrip_8":
			dialog.text = "'Has to die'... just like that. I didn't expect that coming. Hm. You have done your job well, kapitein. Now give me a debrief.";
			link.l1 = "Nothing special... it was a milk run.";
			link.l1.go = "SantiagoTrip_9";
			link.l2 = "I was stunned and kidnapped by a man in Santiago. He was very interested in your business with Geraldi. I managed to escape but had to kill him first. The only clue he dropped was the name of some man named Gaston I don't have any ideas what was it all about.";
			link.l2.go = "SantiagoTrip_10";
			link.l3 = "I was stunned and kidnapped by a man in Santiago. He was very interested in your business with Geraldi. I managed to escape but had to kill him first. I wasn't able to get to know anything out of him before I sent him to hell.";
			link.l3.go = "SantiagoTrip_11";
		break;
		
		case "SantiagoTrip_9":
			dialog.text = "The Company's gratitude is not limited to mere words. Take your reward, you have earned it.";
			link.l1 = "Working for the Company is quite profitable.";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_10":
			dialog.text = "What! Kidnapping... Wait, though... Gaston! I understand... I guess. Alas my boy, you have been dragged into a sordid affair. We're in uncharted waters, so we'll have to see how it develops. Glad that you made it alive.\nLet's talk about more pleasant things - accept this reward, it's well deserved.";
			link.l1 = "Working for the Company is quite profitable";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_11":
			dialog.text = "Nonsense! Kidnapping you... I have some suspicions though. You'll learn more if you continue working for me. You are lucky and I am glad that you made it.\nLet's talk about more pleasant things - accept this reward, it's well deserved.";
			link.l1 = "Working for the Company is quite profitable";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_12":
			AddMoneyToCharacter(pchar, 25000);
			dialog.text = "Exactly, my boy! You can become a well-compensated agent of the Company if we will continue to work together. Now go, take a rest from your voyage. You have lived up to my expectations. I would be really grateful if you came back in a week, we still have a lot of work to do.";
			link.l1 = "You can count on me, Mynheer Rodenburg.";
			link.l1.go = "SantiagoTrip_13";
		break;
		
		case "SantiagoTrip_13":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "true";
			AddQuestRecord("Holl_Gambit", "1-46");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 80);
			AddSimpleRumourCity("My brother at the Company says that Mynheer Rodenburg is quite pleased by your performance, kapitein. Don't lose your chance, Lucas rarely shows such favor.", "Villemstad", 10, 3, "");
			SetTimerFunction("GollandGambit_2_ZadanieStart", 0, 0, 7);
		break;
		
//-----------------------------------------------2 задание--------------------------------------------
		case "JacobBerg":
			dialog.text = "You are smart, captain. Exactly. Well, let's talk details of the upcoming mission...";
			link.l1 = "I am all ears.";
			link.l1.go = "JacobBerg_1";			
		break;
		
		case "JacobBerg_1":
			dialog.text = "I have a very serious and important mission for you and I expect you to do everything according to my instructions. As you know, the relationship between the United Provinces and England are...not cordial. The Brits are sure that they are the ones who should rule the world. Problem is - not everyone tend to agree with such claim. Anywhere they sail to do business, rest assured that the Dutch West India Company has gotten there first.\nWe Dutch have the largest trade fleet in the world and our military squadrons can defend interests of the Republic's interests both here and abroad. The English envy us for our trading power and they are doing what they can to sabotage the Company's activities. Now, there is a certain English navy captain named Richard Fleetwood. Despite being a commissioned officer of the Commonwealth, he is currently operating as a pirate. He attacks and plunders any ship daring to sail under the Dutch flag in the Caribbean. He explains his actions to be a counter-measures to the 'ghost ship' which sinks English traders. He claims that this 'ghost ship' is a privateer sailing under a Dutch letter of marque.\nHave you heard about the 'ghost ship', kapitein?";
			link.l1 = "You can hear that kind of nonsense in any tavern. Just buy some rum for an old boatswain and you will hear any story you want...";
			link.l1.go = "JacobBerg_2";
		break;
		
		case "JacobBerg_2":
			dialog.text = "This matter is no drunk's fantasy. I have investigated the actions of this 'ghost ship'. I found out that she is a ship of wood and canvas and crewed by ordinary men, a ketch named 'Mirage'. She is under the command of a man named Jacob van Berg who is passing her off as the legendary 'Flying Dutchman'.";
			link.l1 = "Van Berg? That's a Dutch surname. A bonefide 'Flying Dutchman' eh?";
			link.l1.go = "JacobBerg_3";
		break;
		
		case "JacobBerg_3":
			dialog.text = "Correct. Jacob van Berg is a Dutchman, originally from Leiden. But the Republic sentenced him to the gallows a long time ago. He is a criminal on the run, a pirate who acts only on his own interests. Richard Fleetwood is hunting van Berg. This fact we'll use against that insolent Englishman.\nI would prefer not to kill Fleetwood outright, though he deserved it long ago. Death would not be enough for him. I want not only to kill him, but also to destroy his name and honor. That is what I want. That will also teach other the arrogant English swine a lesson.\nLet's talk details.";
			link.l1 = "Mynheer, this is starting to sound like it's something personal...";
			link.l1.go = "JacobBerg_4";
		break;
		
		case "JacobBerg_4":
			dialog.text = "That is none of your concern. You will follow orders, then you get paid. I have found out where Jacob van Berg lurks with his 'Mirage', thanks to my agent. He operates out of a city in the Southern Spainish Main. Go to him and find out where he moored his ghost ship\nThen kill him, find his 'Mirage', take her as a prize, and deliver her back here. You must capture the 'Mirage', don't even think about sinking her.";
			link.l1 = "Sounds simple enough. Where should I look for van Berg?";
			link.l1.go = "JacobBerg_5";
		break;
		
		case "JacobBerg_5":
			dialog.text = "All details will be provided to you by my agent. His name is Longway, a Chinaman. I am providing you my personal ship, the xebec 'Meifeng' for this mission. Longway is her kapitein, but he will take orders from you.\nGo to the local harbor office and moor all your vessels there. Return to me once it's done.";
			link.l1 = "Fine, I will visit the harbor master. I won't make you wait for too long.";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Holl = "JacobTakeShip";
			AddLandQuestMark(characterFromId("Villemstad_portman"), "questmarkmain");
		break;
		
		case "JacobBerg_6":
			dialog.text = "Longway is waiting for you outside. He will show you your new ship and will give you some information regarding van Berg's location. Good luck, kapitein and don't let me down. Remember that you must bring the 'Meifeng' back to me so try not to sink her while taking the 'Mirage'.";
			link.l1 = "On my way!";
			link.l1.go = "JacobBerg_7";	
		break;
		
		case "JacobBerg_7":
			DialogExit();
			pchar.quest.Create_Longway.win_condition.l1 = "location";
			pchar.quest.Create_Longway.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Create_Longway.function = "Create_Longway";
			pchar.questTemp.HWIC.Holl = "JacobLongway";
			AddQuestRecord("Holl_Gambit", "1-7");
			pchar.questTemp.HWIC.TakeQuestShip = "true";//все ПУ недоступны для стоянки до поры, также корабль нельзя продать
			pchar.questTemp.HWIC.HollEquip = "true";//форма солдат
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
		break;
		
		//дурдом продолжается
		case "Jacob_lostMir":
			dialog.text = "You incompetent fool. You have failed your mission to capture the pirate vessel. All my plans are ruined. I am taking away 'Meifeng' from you. Get out, we no longer need you.";
			link.l1 = "I am sorry. Farewell, Mynheer Rodenburg.";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
		break;
		
		case "Jacob_lostMef":
			dialog.text = "You blithering idiot. You have lost the 'Meifeng'. This is unacceptable... I will take the 'Mirage' from you and withhold your payment as compensation for my loss. Get out, we no longer need you.";
			link.l1 = "I am sorry. Farewell, Mynheer Rodenburg.";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MIRAGE;
		break;
		
		case "Jacob_failFull":
			dialog.text = "My God, you are truly a rare specimen. A incompetent bungler AND an idiot. You failed to capture the Mirage and lost the Meifeng along with it. Get out the fuck out of my office!";
			link.l1 = "I'm leaving.";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Longway");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//Лонгвэя из офицеров
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Jacob_complete":
			dialog.text = "Well done. Word of your success has already reached my ears. Van Berg is dead and you captured his ship. Your payment is 50,000 pesos, take it.\nI am retrieving the 'Meifeng' from you. Now it is time for you to take command of the 'Mirage', she will play an important role in the next stage. Are you ready?";
			link.l1 = "Yes, Mynheer Rodenburg.";
			link.l1.go = "Fleetwood";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			AddSimpleRumourCity("They say that you are on special assignment for Mynheer Rodenburg himself. Something about sending those English to the bottom of the sea. It seems that you are a man on the rise, kapitein.", "Villemstad", 15, 3, "");
		break;
		
		case "Jacob_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			sld = characterFromId("Longway");
			sld.lifeday = 0;
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumourCity("They say that you have failed Mynheer Rodenburg himself. Good luck, you'll need it.", "Villemstad", 20, 3, "");
		break;
		
//----------------------------------------------3 задание-------------------------------------------------
		
		case "Fleetwood":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "Now we deal with Fleetwood. You are going to lure him out using the 'ghost ship' Mirage that he has been hunting so enthusiastically. Set a trap close by Dominica, the Mirage will serve as bait.\nFirst, you will let Fleetwood know that the Mirage was seen not far from Dominica. Our brave Englishman will drop everything that he's doing and rush immediately to Dominica in search of his prey. Don't talk to Fleetwood directly or you won't survive the encounter. Find the drugstore in St. John's. The apothecary John Murdock is an old friend of mine.\nTell him that you are acting under my command and he will help you to find local ears to fill with juicy lies about the 'ghost ship' attacking English merchants around Dominica.";
			link.l1 = "I can do that. The goal is to ambush Fleetwood at Dominica, am I right?";
			link.l1.go = "Fleetwood_1";
		break;
		
		case "Fleetwood_1":
			dialog.text = "Exactly. Longway and 'Meifeng' will wait for you near Dominica. The two of you can take the English dog easily. Board his ship and search his cabin. I want his logbook. I'll pay extra for it.\nBut your main priority is to kill that bastard Fleetwood, so if boarding him is impractical - send him to the bottom. Above all you must preserve 'Mirage' at all costs. She has a critical role to play in the next stage of the plan.";
			link.l1 = "Understood.";
			link.l1.go = "Fleetwood_2";
		break;
		
		case "Fleetwood_2":
			dialog.text = "A word of advice, kapitein. Do not drop anchor at St. John's. Land at one of the island's bays and walk to the city through the jungle, otherwise John won't talk with you. If you draw too much attention to yourself, he will pretend he doesn't know you. Also, be careful at the sea - the 'Mirage' is notorious among the English colonies, so avoid their warships and settlements if you don't want to be set upon by a pack of sea wolves. That is all. God be with you.";
			link.l1 = "Aye aye.";
			link.l1.go = "Fleetwood_3";
		break;
		
		case "Fleetwood_3":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toAntigua";
			AddQuestRecord("Holl_Gambit", "1-15");
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			SetFunctionTimerCondition("ToAntiguaOver", 0, 0, 60, false); //таймер 2 месяца
			AddMapQuestMarkShore("Shore1", false);
			AddMapQuestMarkShore("Shore2", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Fleetwood_complete":
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink")//Флитвуд утоп с журналом
			{
				dialog.text = "You have returned, kapitein... Do you have Richard Fleetwood's logbook?";
				link.l1 = "Unfortunately no. I didn't get a chance to board his ship before he scuttled her.";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			if (!CheckCharacterItem(pchar, "FleetwoodJournal"))
			{
				dialog.text = "You have returned, kapitein... Do you have Richard Fleetwood's logbook?";
				link.l1 = "Unfortunately, I didn't. I managed to board the Valkyrie and kill the man in hand-to-hand combat, but I didn't find his journal. One of his men fired the magazine and we only had seconds to escape with our lives.";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			dialog.text = "You have returned, kapitein... Do you have Richard Fleetwood's logbook?";
			link.l1 = "I did. Here it is. I managed to board the Valkyrie, alhough it was a near-run thing. The bastard fired his magazine his ship and blew it sky high. We barely got away with our lives.";
			link.l1.go = "Fleetwood_complete_2";
		break;
		
		case "Fleetwood_complete_1":
			AddMoneyToCharacter(pchar, 100000);
			dialog.text = "That is a damn shame, it would have answered many questions that we have. It is of no matter now. You killed that insolent English dog and that's what matters most. Here is your reward - 100,000 pesos. I am taking the 'Mirage' from you, we are going to return this ship to England.";
			link.l1 = "What the devil?! She is a fine ship, I wanted to keep her!";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_2":
			AddMoneyToCharacter(pchar, 150000);
			RemoveItems(PChar, "FleetwoodJournal", 1);
			dialog.text = "Excellent! You are a very capable man. If all of our captains were like you, the Dutch Republic would be first amongst the greatest maritime nations of history. Here is your reward - 100,000 pesos and 50,000 pesos extra for the logbook. I am taking the 'Mirage' from you, we are going to return this ship to England.";
			link.l1 = "What the devil?! She is a fine ship, I wanted to keep her!";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_3":
			dialog.text = "My boy, you are an excellent soldier, but trust me and my experience in the matters of politics. Remember what I said about Fleetwood? I am going to nail his name and reputation to a millstone and fling it into the depths. And these arrogant nobles from Port Royal will have to swallow and choke.\nWe are going to make Richard Fleetwood the captain of the 'ghost ship' Mirage, a werewolf playing the two nations of England and the Netherlands off each other, plundering, pillaging, and murdering peaceful citizens of both just to make himself rich! What a travesty! I have already prepared evidence and witnesses, but the 'Mirage' will serve as the main event of my perfect play.";
			link.l1 = "Well fuck me then. You're going to sacrifice my excellent ship for your plan!?";
			link.l1.go = "Fleetwood_complete_4";
			AddDialogExitQuestFunction("Lucas_ExangeShip");
		break;
		
		case "Fleetwood_complete_4":
			dialog.text = "Watch your tongue boy, this is war. Sometimes we must sacrifice not only men, but ships and wealthy settlements to achieve our political aims. Every war comes with losses...Speaking of losses, I have bad news for you.\nWhile you gone, Willemstad was attacked by English privateers. The fort managed to chase them off, but not before they got into the harbor with fireships.\nYour ship was caught at anchor and burnt down to the waterline. She's a total loss";
			link.l1 = "Mynheer, you have to be fucking kidding me right now. Damn it all to hell! What will I do now?!";
			link.l1.go = "Fleetwood_complete_5";			
		break;
		
		case "Fleetwood_complete_5":
			dialog.text = "Don't be so upset kapitein, I also have good news. To salve your indignation, I am giving you my Beautiful Wind, the xebec 'Meifeng'. You are free to use the ship in any way you want, within reason. Additionally, meet me tomorrow in the governor's residence, you have been nominated for a state award with the gratitude of the Dutch Republic and West India Company. Don't leave the town until you receive it, kapitein.";
			link.l1 = "That does take the sting out of my losses a bit. I am honored. By the way, mynheer, where has Longway gone?";
			link.l1.go = "Fleetwood_complete_6";
		break;
		
		case "Fleetwood_complete_6":
			dialog.text = "Longway suddenly disappeared right after I ordered him to sail to Dominica. I have suspicions that English agents have set upon him... or perhaps not. I am investigating.";
			link.l1 = "I see. His help at Dominica would've been most welcome. Fleetwood and his 'Valkerie' made a fearsome pair. I hope that Longway is still alive... Tot zeins, mynheer!";
			link.l1.go = "Fleetwood_complete_7";
			pchar.questTemp.HWIC.Holl = "Award";
			AddQuestRecord("Holl_Gambit", "1-24");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", true);
		break;
		
		case "Fleetwood_complete_7":
			DialogExit();
			pchar.quest.Award_FromLucas.win_condition.l1 = "Timer";
			pchar.quest.Award_FromLucas.win_condition.l1.date.hour  = 8.00;
			pchar.quest.Award_FromLucas.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Award_FromLucas.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Award_FromLucas.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Award_FromLucas.win_condition.l2 = "location";
			pchar.quest.Award_FromLucas.win_condition.l2.location = "Villemstad_townhall";
			pchar.quest.Award_FromLucas.function = "AwardFromFromLucas";
			AddSimpleRumour("Tell me captain, was that damned English dog Fleetwood was really responsible for plundering English 'and' Dutch merchants? Really? Such an artful dodger! It is good that you have eliminated this bastard. You are a real hero, captain!", HOLLAND, 10, 3);
		break;
		
		case "Fleetwood_fail":
			dialog.text = "You are not just an ordinary clown, you are the entire circus. We were so close to the final act and you bungled it... I will pay you 30,000 pesos for Fleetwood's elimination. I have no more missions for you and our arrangement is finished. Get out.";
			link.l1 = "As you wish.";
			link.l1.go = "Fleetwood_fail_1";			
		break;
		
		case "Fleetwood_fail_1":
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "I have bad news for you.\nWhile you gone, Willemstad was attacked by English privateers. The fort managed to chase them off, but not before they got into the harbor with fireships.\nYour ship was caught at anchor and burnt down to the waterline. She's a total loss.";
			link.l1 = "I guess I'll just go fuck myself then! Thanks for nothing!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Holl = "end";
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumour("Tell me, captain, is it true that you have sunk this damned English dog Fleetwood? Really? It is good that you have eliminated this bastard. You did well, captain!", HOLLAND, 15, 3);
		break;
		
		case "LucasAward":
			dialog.text = "Kapitein " + GetFullName(pchar) + "! For eliminating Richard Fleetwood, a dangerous state criminal, for exposure of treacherous English conspiracy against the Republic, for bravery and courage, you are awarded with one thousand golden doubloons on behalf of the Dutch Republic!\nYou also are to receive this valuable navigation tool - the dream of any military sailor.";
			link.l1 = "I am happy to serve the Republic!";
			link.l1.go = "LucasAward_1";			
		break;
		
		case "LucasAward_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetActorType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
			sld.dialog.currentnode = "Bek_7";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			GiveItem2Character(pchar, "bussol");
		break;
		
		case "LucasAward_2":
			dialog.text = "Congratulations again, my friend. And please, visit me in a week. We need you for an exceedingly delicate matter.";
			link.l1 = "Understood, Mynheer Rodenburg. I will visit you in a week.";
			link.l1.go = "LucasAward_3";			
		break;
		
		case "LucasAward_3"://наведем порядок
			LAi_SetActorType(pchar);
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-25");
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_ActorGoToLocator(sld, "goto", "goto6", "BekSitDown", -1);
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("LucasGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
			sld = characterFromId("Lucas");
			LAi_ActorGoToLocator(sld, "reload", "reload1", "LucasReturnInCabinet", -1);
			bDisableFastReload = true;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			SetTimerFunction("GollandGambit_4_ZadanieStart", 0, 0, 7);
			AddSimpleRumourCity("They say that you were given a state award by Matias Beck himself! The Republic should be proud to have people like you, kapetein!", "Villemstad", 20, 4, "");
		break;
		
//--------------------------------------------------4 задание----------------------------------------------
		
		case "Abby":
			dialog.text = "Let me tell you a story. It will help you understand how delicate your next task is. A few months ago, a fluyt sailing the English flag en route to Willemstad was attacked by the late Jacob van Berg. He took the ship and scuttled it not far from an island not on any of our maps. Only two of the passengers on the fluyt survived. A Jew named Solomon Shneur and his daughter Abigail. All other passengers perished, including the rest of their family. Our two Jews reached the island by floating on some wreckage\nSolomon even managed to drag a chest filled with the family gold with them. Very thrifty of him. Another character of our story, Richard Fleetwood, was sailing nearby and heard the sounds of fighting. He arrived too late to catch van Berg, and the 'Mirage' fled. Fleetwood decided to check the island for any survivors\nHe saved Solomon and Abigail from certain death on that desert island. Unfortunately for the old Jew, Solomon does not have a sailor's eye. He mistook Richard's 'Valkerie' for Jacob's 'Mirage' and - terrified the pirate was returning to finish the job - stashed his gold somewhere on the island. As a result, he and his daughter arrived here without a penny, dropped off by Fleetwood at Blanca Lagoon, near Willemstad, their original destination.\nSolomon told me this story. The Dutch Republic supports the free practice of religion. As a part of that policy, the Company supports the Jewish community here. Therefore I made sure they have a roof over their heads, and things to eat and wear. I visited their place a lot. Abigail is a... remarkable young woman. Sincere and trusting\nI won't lie to you, captain, I want her and I intend to make her my wife. She loves me in return, but something has come between us.";
			link.l1 = "Her father not too enthused about a goyim son-in-law?";
			link.l1.go = "Abby_0";			
		break;
		
		case "Abby_0":
			dialog.text = "Ha! Old Solomon would be in the seventh heaven if I married Abigail, uncircumcized son-in-law or not. As a matter of fact, he pushes her to accept my proposal. No, no this is something that goes beyond Jew and Gentile. I ask you my boy, to solve this problem for me. Talk to Abigail and find out what is wrong\nYou are a stranger, she might tell you things that she would never tell familiar people because of her charming modesty. Shneur's house is located to the right of the company's office, if you stand with your back to it. I know that you are a smooth talker\nBut remember one thing: Richard Fleetwood was the true captain of the 'ghost ship'... Keep it in mind while talking to Abigail.";
			link.l1 = "Ha! Sure I remember that, Mynheer Rodenburg. Isn't that the officially recognized fact after all? I won't waste time then, I will go pay your beloved a visit immediately.";
			link.l1.go = "Abby_1";			
		break;
		
		case "Abby_1":
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyInHouse";
			AddQuestRecord("Holl_Gambit", "1-26");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "Abby_2":
			dialog.text = "Have you really found the island where Solomon has stashed his gold? This is most excellent! I was starting to think that you are able to do any task... Have you found anything else in the stash?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.ScullnotReturn"))
			{
				link.l1 = "No, nothing else. Only money.";
				link.l1.go = "Abby_3";
			}
			else
			{
				link.l1 = "There was an interesting item - a jade skull. I gave it to Solomon, he said that it was a family heirloom. He also said that you were planning to buy it from him...";
				link.l1.go = "Abby_4";
			}
		break;
		
		case "Abby_3":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "Hm. Fine then. It is quite odd though. Whatever... I owe you, mynheer, and I will never forget it. I have prepared a reward for you - 50,000 pesos and this amulet. It is yours now.";
			link.l1 = "Thank you, Mynheer Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_4":
			pchar.questTemp.HWIC.Holl.LucasItem = "totem_04";
			dialog.text = "Excellent! Yes I am going to buy this artefact from Solomon, he doesn't need it and I have a very generous buyer for it. I have prepared a reward for you - 50,000 pesos and this amulet. It is yours now.";
			link.l1 = "Thank you, Mynheer Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_5":
			dialog.text = "I don't have any job worthy of such a kapitein like you at the moment. But don't leave Curacao for too long, soon I will need your services again.";
			link.l1 = "I got it, mynheer. Goodbye!";
			link.l1.go = "exit";
			GiveItem2Character(pchar, pchar.questTemp.HWIC.Holl.LucasItem);
			AddMoneyToCharacter(pchar, 50000);
			pchar.questTemp.HWIC.Holl = "Merdok_wait";
			AddQuestRecord("Holl_Gambit", "1-34");
			DelMapQuestMarkCity("Villemstad");
			SetTimerFunction("GollandGambit_5_ZadanieStart", 0, 0, 10);
			AddSimpleRumourCity("Have you heard the latest news? Mynheer Rodenburg is going to marry Abigail Shneur, the beautiful daughter of the old crazy Jew Solomon. What can I say, she is a lucky girl. God willing, she'll be baptized a true Christian before the wedding!", "Villemstad", 20, 3, "");
		break;
		
		case "Abby_6":
			dialog.text = "Ha, and that's it? Patently absurd...how much like a woman. Listen to me, my boy, this problem can be easily solved. I know how much money was in Solomon's stash: 200,000 pesos. I am ready to spare this sum for my and Abigail's happiness. I will give you the money and you will leave Curacao for a week or two. Then you will return to Solomon and give him the money. Pretend that you've found the stash. The wolf will be sated and the sheep left untouched. Here, take the required sum";
			link.l1 = "A good and simple plan. Let's do it.";
			link.l1.go = "Abby_7";
		break;
		
		case "Abby_7":
			dialog.text = "Sail out to the open sea and return back to me in ten days. Go do something productive. Look for Manga Rosa, craft some materials, or something.";
			link.l1 = "Whatever you say, Mynheer Rodenburg.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 200000);
			pchar.questTemp.HWIC.Holl = "GiveLucasMoney";
			SaveCurrentQuestDateParam("questTemp.HWIC.Holl.LucasMoney");
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";
			AddQuestRecord("Holl_Gambit", "1-35");
		break;
		
		case "Abby_8":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "Splendid! Once again, you did the job perfectly. I owe you, mynheer, and I will never forget it. I have prepared a reward for you - 50,000 pesos and this amulet. It is yours now.";
			link.l1 = "Thank you, Mynheer Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
//-------------------------------------------5 задание-------------------------------------------------
		case "Merdok":
			dialog.text = "Yes, exactly so. My friend, sometimes it's hard to see who is your friend and who is your enemy. Sometimes you miss the point when your closest associate turns into your nemesis. Our mutual acquaintance from St John's John Murdock - also known as Johan van Merden - is an ex-agent of the Company who has sold himself to the English Navy.\nHis newest mission is to eliminate one of the Company's brightest stars... you.";
			link.l1 = "I am flattered. Glad you told me, otherwise I wouldn't have seen this coming.";
			link.l1.go = "Merdok_1";
		break;
		
		case "Merdok_1":
			dialog.text = "Precisely, kapitein. He is a sly dog. Find the bastard and kill him before he strikes. Sail to Antigua and search for a secret entrance to his drugstore. There is a hatch in front of the church that leads to a secret tunnel. Use it.";
			link.l1 = "I'll take care of it.";
			link.l1.go = "Merdok_2";
		break;
		
		case "Merdok_2":
			dialog.text = "One more thing, kapitein. Once Johan is be dead, search his corpse, the house and the basement. He has an archive - a fat ledger that he used to write down some damning notes during his work for the Company. This information will destroy us all if our enemies find it.\nFind that accursed archive and deliver it to me, I will pay extra for it. Now go. Godspeed, Kapitein " + pchar.name + ", and try to return in one piece. The Republic needs you!";
			link.l1 = "I promise you, mynheer, to return back in one piece. That is most assuredly in my best interest!";
			link.l1.go = "Merdok_3";
		break;
		
		case "Merdok_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "KillMerdok";
			AddQuestRecord("Holl_Gambit", "1-42");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//откроем проход в подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//откроем проход в дом из подземелья
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//аптеку закроем
			pchar.quest.Merdok_inCave.win_condition.l1 = "location";
			pchar.quest.Merdok_inCave.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Merdok_inCave.function = "MerdokInUndergroundCave";
			LAi_LocationDisableOfficersGen("SentJons_TownCave", true);//офицеров в шахту не пускать
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("SentJons", false);
		break;
		
		case "Merdok_4":
			dialog.text = "Excellent, captain! I am glad, I really do. Did you find his archive?";
			if (CheckCharacterItem(pchar, "MerdokArchive"))//архив
			{
				link.l1 = "Yes, here it is. There were no other documents on the chemist's corpse or in his chests.";
				link.l1.go = "Merdok_book";
			}
			link.l2 = "No. I looked for it everywhere but found nothing.";
			link.l2.go = "Merdok_5";
			DeleteAttribute("SentJons_TownCave", "box2");//если не нашли шифр - уже и не найдем
		break;
		
		case "Merdok_5":
			dialog.text = "That's a pity for sure, but I am fine with that. I am sure that Johan didn't have enough time to give it to the English, otherwise we'd already have nooses around our necks... It is likely that he hid it in some secret stash... let it stay there forever! I congratulate you, kapitein, with the successful conclusion of our mission!";
			link.l1 = "Gratitude!";
			link.l1.go = "Merdok_6";
			
			SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false);	// проверку не прошёл, значит нападёт Лига через неделю, после чего начнётся таймер на 30 дней 1 этапа
		break;
		
		case "Merdok_book":
			dialog.text = "Splendid! Now it is safely where it belongs. You have proven that you are the best once again... Give me the book... There is a reward for the archive - this fine musket. It has served me with great distinction and now it's yours!";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.PZ_RodenburgUkradenaStranitsa"))
			{
				link.l1.go = "Merdok_book_2";
			}
			else
			{
				link.l1.go = "Merdok_book_6";
			}
			RemoveItems(PChar, "MerdokArchive", 1);
		break;
		
		case "Merdok_book_2":
			dialog.text = "What's your game, Captain? Several pages are missing - pages that are very important to me. Did you think I wouldn't notice so you could use them against me? Or were you hoping to get more out of it? I'm afraid I have to disappoint you on both counts.";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l1 = "(Trustworthy) I apologize. My only fault was not checking the archive myself beforehand.";
				link.l1.go = "VD_Merdok_book_3";
				SetTimerCondition("PZ_Etap1_Start", 0, 0, 30, false);	// 1 этап стартует через 30 дней
			}
			else
			{
				notification("Perk check failed", "Trustworthy");
				link.l1 = "Would I really tear out the pages and then hand over the archive with a nonchalant look?";
				link.l1.go = "Merdok_book_3";
				SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false);	// проверку не прошёл, значит нападёт Лига через неделю, после чего начнётся таймер на 30 дней 1 этапа
			}
			LAi_Fade("", "");
		break;
		
		case "Merdok_book_3":
			dialog.text = "Greed, stupidity, and impudence sometimes drive people to the most insane acts, Captain.";
			link.l1 = "None of those three motivated me, I assure you.";
			link.l1.go = "Merdok_book_4";
		break;
		
		case "Merdok_book_4":
			dialog.text = "So you're saying van Merden removed those pages and hid them elsewhere?";
			link.l1 = "Exactly. I could go back and search for them-turn the whole drugstore upside down, or even all of St. John's - if you deem it necessary.";
			link.l1.go = "Merdok_book_5";
		break;
		
		case "Merdok_book_5":
			dialog.text = "No need, sir. Most of what's important is here anyway, and without the missing pages, the rest poses no threat to me.";
			link.l1 = "";
			link.l1.go = "Merdok_book_6";
		break;
		
		case "VD_Merdok_book_3":
			dialog.text = "So, it's a lack of care or curiosity rather than dishonesty or secret agenda? Do you think it was already like this when you found it?";
			link.l1 = "Most likely, Mynheer Rodenburg. Perhaps van Merden tore out those pages beforehand. ";
			link.l1.go = "VD_Merdok_book_4";
		break;
		
		case "VD_Merdok_book_4":
			dialog.text = "Perhaps it's for the best. Without those pages, the rest of the archive poses no threat to me - especially in ignorant hands.";
			link.l1 = "";
			if (IsCharacterPerkOn(pchar, "Trustworthy")) link.l1.go = "Merdok_book_6";
			else link.l1 = "Merdok_6";
		break;
		
		case "Merdok_book_6":
			dialog.text = "There is a reward for the archive - this fine musket. It has served me with great distinction and now it's yours!";
			link.l1 = "Bedankt!";
			link.l1.go = "Merdok_6";
			GiveItem2Character(PChar, "mushket2");
		break;
		
		case "Merdok_6":
			dialog.text = "We did well, you and I, kapitein. It is not an overstatement that none of this would have happened without you. You will reach incredible career heights in case you will continue to serve the Republic, perhaps even be ennobled.";
			link.l1 = "I guess this is goodbye, Mynheer Rodenburg.";
			link.l1.go = "Merdok_7";
		break;
		
		case "Merdok_7":
			dialog.text = "It is goodbye, " + pchar.name + ". I have accomplished everything I wanted here, so I departing home to Amsterdam in a week. My new wife Abigail and my father-in-law Solomon will accompany me. Peter Stuyvesant has already found a new Company vice-director, so talk to him if you need something\nFor your service I present you the Meifeng. She is yours now, kapitein, you deserve her.";
			link.l1 = "Thank you, Mynheer Rodenburg. I have gotten quite attached to the Meifeng and already started to consider her as my own.";
			link.l1.go = "Merdok_8";
		break;
		
		case "Merdok_8":
			dialog.text = "And now I have to ask you to leave me, my boy. I have got a lot of things to do before we set sail... Visit me in Amsterdam one day! We will share a drink and remember the good old times...";
			link.l1 = "Aye, mynheer. I hope that you are all happy and prosperous in your new life! Farewell!";
			link.l1.go = "Merdok_9";
			// belamour legendary edition -->
			link.l2 = "Aye, mynheer. I hope that you are all happy and prosperous in your new life!\n(through gritted teeth) ... I hope we don't see each other again, you arrogant prick. Just wait until you discover the joys of being married to a 'demure' Jewish harridan.";
			link.l2.go = "Merdok_9a";
		break;
		
		case "Merdok_9a":
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");//уберем Аби
			sld.lifeday = 0;
			sld = characterFromId("Solomon");//уберем Соломона
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";//прерывание на Лукаса
			pchar.questTemp.HWIC.Detector = "holl_win";
			CheckPortugalHWIC();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddSimpleRumourCity("Mynheer Rodenburg has sailed to Amsterdam with his young wife and father-in-law. Are you the new vice-director?", "Villemstad", 30, 3, "");
			AddSimpleRumour("They say, kapitein, that you are well regarded by the governor-general. Mynheer Rodenburg supposedly appointed you as his successor in the Company, is that so?", HOLLAND, 30, 3);
		break;
		
		case "Merdok_9":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");//уберем Аби
			sld.lifeday = 0;
			sld = characterFromId("Solomon");//уберем Соломона
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";//прерывание на Лукаса
			pchar.questTemp.HWIC.Detector = "holl_win";
			CheckPortugalHWIC();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddSimpleRumourCity("Mynheer Rodenburg has sailed to Amsterdam with his young wife and father-in-law. Are you the new vice-director?", "Villemstad", 30, 3, "");
			AddSimpleRumour("They say, kapitein, that you are well regarded by the governor-general. Mynheer Rodenburg supposedly appointed you as his successor in the Company, is that so?", HOLLAND, 30, 3);
		break;
		
//----------------------------------------------за Англию------------------------------------------------------
		case "Lucas_abordage":
			dialog.text = "God in de Hemel! Fleetwood's dog! You may win this day, but Lucas Rodenburg will sell his life dearly.";
			link.l1 = "I don't think so. You'll hand your life over to me for free, you Dutch miser.";
			link.l1.go = "Lucas_abordage_1";
		break;
		
		case "Lucas_abordage_1":
			PlaySound("Voice\English\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "From the depth of hell I will shit in your mouth! I just set the cargo hold ablaze and the fire will soon spread to the gunpowder magazine! Our ships are grappled in close quarters so there is no hope of escape! You will burn or feed the sharks!";
			link.l1 = "Damn! Fall back men, we must retreat!";
			link.l1.go = "Lucas_abordage_2";
			// belamour legendary edition -->
			link.l2 = "I'm not leaving until your soul leaves your body. Hold still, this will hurt.";
			link.l2.go = "Lucas_abordage_2a";
		break;
		
		case "Lucas_abordage_2a":
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "Lucas_abordage_2":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
//----------------------------------------------против всех--------------------------------------------------
		case "LucasPrisoner":
			dialog.text = "Why are you here, you bastard? Here to mock me? Perhaps you will tell me at last what's your place in this play. It was you who captured the brigantine, correct? Was this your plan from the beginning?";
			link.l1 = "I am here to give you some regards, Lucas Rodenburg. The best regards from John Merdock, who you betrayed. You were my job and I did it. Farewell for now.";
			link.l1.go = "LucasPrisoner_1";
		break;
		
		case "LucasPrisoner_1":
			PlaySound("Voice\English\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "Johan? Haha! So that was the man behind all of this! That old scoundrel! But the game is not over yet. Jacob van Berg is coming for you and you will not escape! You and your ship are forfeit, you pathetic sea beggar!";
			link.l1 = "Spare your voice for the hangman's court, Rodenburg.";
			link.l1.go = "LucasPrisoner_2";
		break;
		
		case "LucasPrisoner_2":
			DialogExit();
			pchar.questTemp.jailCanMove = true; //разрешить пройти мимо стражи
			LAi_SetPlayerType(pchar);
			pchar.quest.Login_Joakim.win_condition.l1 = "location";
			pchar.quest.Login_Joakim.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Login_Joakim.function = "Create_Joakim";
			pchar.questTemp.HWIC.Self = "JoakimMeeting";
			SetFunctionTimerCondition("LucasQuit", 0, 0, 7, false);
		break;
	}
}
