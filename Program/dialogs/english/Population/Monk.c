//Jason общий диалог уличных монахов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iTest;
	string sTemp, sTitle;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	iTest = FindColony(NPChar.City);
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> диалог первой встречи
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(npchar, "quest.donation"))//пожертвования
				{
					dialog.text = "Good day to you, my son. I ask you to show some favor and to donate a few silver coins for the good of the poor, your soul, and Holy Mother Church.";
					link.l1 = "Well father, I suppose that we all have to help one another as Christ and His Church teaches us. Can you tell me about where the money will go?";
					link.l1.go = "donation";
					link.l2 = "Forgive me, father, but I'm as poor as a churchmouse right now.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Monkpassenger") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) < 3)//монах-пассажир
				{
					dialog.text = "Good day to you, my son. I'd like to ask you to do my favor. I will pay of course.";
					link.l1 = "I am listening to you, father. What do you need?";
					link.l1.go = "passenger";
					link.l2 = "I am so sorry, father, but I have to go.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.capellan") && !CheckAttribute(pchar, "questTemp.ShipCapellan"))//корабельный капеллан
				{
					dialog.text = "Greetings, my son. I take it that you are a captain. So I have a proposal for you.";
					link.l1 = "I am listening, father.";
					link.l1.go = "capellan";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = PCharRepPhrase(LinkRandPhrase("Greetings, my son. What troubles you?","Greetings, my son. See the pastor if you want to confess.","Greetings, my son. 'Remember thy Creator in the days of thy youth.'"),LinkRandPhrase("Greetings, my son. What troubles you?","Good day to you, my son, may God bless you!","Good day to you, my son, may God's face shine upon you!"));
				link.l1 = LinkRandPhrase("Same to you, father. How are you doing?","Good day to you, father. How is your parish?","How are you, father?");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("I have a question for you, father.", "I need information.");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10)
				{
					link.l3 = "Father, I've got people on my ship. They are slaves, both Christians and non-baptized pagans. I want you to baptize the pagans and to administer communion to the Christians. Afterwards I will free them all for the glory of God and our Church.";
					link.l3.go = "slaves";
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "Father, I want you to bless my ship and offer mass for my crew. How much would that cost?";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("Pardon, father, but I have to go.","Sorry for troubling you, father.","I need to go back to my ship, father. Farewell!");
				link.l10.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				//--> диалог второй встречи
				dialog.text = LinkRandPhrase("You again, my son? What do you want?","Have anything more to tell me, my son?","It is good to see you again, my son.");
				link.l1 = LinkRandPhrase("Same to you, father. How are you doing?","Good day to you, father. How is your parish?","How are you, father?");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("I have a question for you, father.", "I need information.");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10 && !CheckAttribute(npchar, "quest.slaves"))
					{
						link.l3 = "Father, I've got people on my ship. They are slaves, both Christians and non-baptized pagans. I want you to baptize the pagans and to administer communion to the Christians. Afterwards I will free them all for the glory of God and our Church.";
						link.l3.go = "slaves";
					}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "Father, I want you to bless my ship and offer mass for my crew. How much would that cost?";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("Pardon, father, but I have to go.","Sorry for troubling you, father.","I need to go to my ship, father. Farewell!");
				link.l10.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "check":
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) < 3 && !CheckAttribute(npchar, "quest.monkletter") && !CheckAttribute(pchar, "GenQuest.Monkletter") && !CheckAttribute(npchar, "quest.passenger")) //церковная депеша
			{
				pchar.GenQuest.Monkletter.City = FindFriendCityToMC(false);
				pchar.GenQuest.Monkletter.StartCity = npchar.city;//город квестодателя
				dialog.text = "I have a pressing matter for you, my son. I need to deliver these papers to the pastor of  "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen")+". Are you sailing in that direction? The documents must be delivered in two weeks...";
				link.l1 = "Easy enough, father. Give me those papers and I will deliver them to "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen")+".";
				link.l1.go = "Monkletter";
				link.l2 = "I'd be glad to do it, father, but I am sailing in another direction.";
				link.l2.go = "exit_monkletter";
				npchar.quest.monkletter = "true";
				break;
			}
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) > 5 && sti(pchar.rank < 11) && !CheckAttribute(npchar, "quest.churchbooks") && !CheckAttribute(pchar, "GenQuest.Churchbooks") && !CheckAttribute(npchar, "quest.passenger")) //привезти молитвенники
			{
				pchar.GenQuest.Churchbooks.StartCity = npchar.city;//город квестодателя
				pchar.GenQuest.Churchbooks.Nation = npchar.nation;
				dialog.text = "My son, would you agree to help me in an urgent matter? Our church is running low on Bibles and prayer books which we give to all who need them\nCould you sail to the nearest colony "+NationNameGenitive(sti(npchar.nation))+", to pick up a few Bibles and prayer books from the local church and bring them here? And try to do that in one month, we don't have many left.";
				link.l1 = "I'll help your church with pleasure. Can I get these books from any pastor?";
				link.l1.go = "Churchbooks";
				link.l2 = "I'd be glad to it, father, but I can't do it now.";
				link.l2.go = "exit_churchbooks";
				npchar.quest.churchbooks = "true";
				break;
			}
			
			dialog.text = RandPhraseSimple("It's alright, my son. Thank you for your kind words.", "Our parish is fine, my son. Thank you for your concerns.");
			link.l1 = "I have to go then, father.";
			link.l1.go = "exit";
		break;
		
//-------------------------------------------------пожертвования------------------------------------------------
		case "donation":
			sTemp = DonationType();
			dialog.text = "Sure, my son. "+sTemp+"";
			link.l1 = "What donation would be considered as sufficient?";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			dialog.text = "It all depends on your purse and personal wish, my son. 'God loves a cheerful giver.' We are deeply grateful for any donation.";
			link.l1 = "100 pesos";
			link.l1.go = "donation_rate_1";
			link.l2 = "1000 pesos";
			link.l2.go = "donation_rate_2";
			link.l3 = "5000 pesos";
			link.l3.go = "donation_rate_3";
			link.l4 = "10000 pesos";
			link.l4.go = "donation_rate_4";
		break;
		
		case "donation_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "Thank you for the coins, my son! They will go to a good cause!";
				link.l1 = "You're welcome, holy father.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "'Be not deceived, God is not mocked. For what things a man shall sow, those also shall he reap. For he that soweth in his flesh, of the flesh also shall reap corruption. But he that soweth in the spirit, of the spirit shall reap life everlasting.'";
				link.l1 = "Ha-ha! Save the sermon, I don't do charity. Get lost!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_2":
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "I thank you, my son. This sum will really help our parish mission. Bless you!";
				link.l1 = "Good luck, father!";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCrewMorale(pchar, 2);
			}
			else
			{
				dialog.text = "God's retribution is waiting for you, sirrah! Mocking a servant of Christ's holy church is a blasphemy!";
				link.l1 = "Ha-ha! I don't do charity. Get lost!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_3":
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "I couldn't even imagine that you would be that generous, my son! I will mention you in my next letter to our bishop and we will pray for you every day! I bless you and accept your money gratefully!";
				link.l1 = "Money is nothing unless it is used for God's purpose! Good luck, father!";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCrewMorale(pchar, 3);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			}
			else
			{
				dialog.text = "God's retribution is waiting for you, sirrah! Mocking a servant of Christ's holy church is a blasphemy!";
				link.l1 = "Ha-ha! I don't do charity. Get lost!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_4":
			if (sti(pchar.money) >= 10000)
			{
				AddMoneyToCharacter(pchar, -10000);
				dialog.text = "What...Have I heard you right? Will you really donate ten thousand pesos!? I bless you and accept your money gratefully. I will mention you in my next letter to our bishop and we will pray for you every day! This is a huge help for the Church!";
				link.l1 = "'To whom much is given, much is required,' right? Good luck, holy father.";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 10);
				AddCharacterExpToSkill(pchar, "Leadership", 60);
				AddCrewMorale(pchar, 5);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
				ChangeCrewExp(pchar, "Sailors", 5);
				ChangeCrewExp(pchar, "Cannoners", 5);
				ChangeCrewExp(pchar, "Soldiers", 5);
			}
			else
			{
				dialog.text = "God's retribution is waiting for you, sirrah! Mocking a servant of Christ's holy church is a blasphemy!";
				link.l1 = "Ha-ha! I don't do charity. Get lost!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterHealth(pchar, -5);
			LAi_CharacterDisableDialog(npchar);
		break;
		
//-------------------------------------------отпустить рабов---------------------------------------------------
		case "slaves":
			dialog.text = "Of course, my son. It's our sacred duty to help these poor miserable people. I will do what you ask for.";
			link.l1 = "Thank you, father. I will donate ten pieces of eight for each baptized and administered prisoner.";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves_1":
			AddMoneyToCharacter(pchar, -GetSquadronGoods(pchar, GOOD_SLAVES)*10);
			dialog.text = "While not necessary, I gratefully accept your stole fee. Your money will go towards various missions at our parish. Could you lead me to your ship?";
			link.l1 = "Yes, father. Follow me.";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			npchar.quest.slaves = "true";
			DialogExit();
			SetLaunchFrameFormParam("Two hours later"+ NewStr() +"Slaves were freed", "Monk_RemoveSlaves", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
//<-- отпустить рабов

//----------------------------------------------освятить корабль------------------------------------------------
		case "shipshine":
			//поиск старшего класса
			iTemp = 6;
			for (i=0; i<COMPANION_MAX; i++)
			{
				int iIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iIdx >= 0)
				{
					sld = GetCharacter(iIdx);
					if (GetCharacterShipClass(sld) < iTemp) iTemp = GetCharacterShipClass(sld);
				}
			}
			switch (GetCompanionQuantity(pchar))
			{
				case 1: 
					sTemp = "I have only one ship in my squadron and it's "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = 5000*(6-iTemp);
				break;
				case 2:
					sTemp = "I have two ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(1.8*(5000*(6-iTemp)));
				break;
				case 3:
					sTemp = "I have three ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(2.6*(5000*(6-iTemp)));
				break;
				case 4:
					sTemp = "I have four ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(3.4*(5000*(6-iTemp)));
				break;
				case 5:
					sTemp = "I have five ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(4.2*(5000*(6-iTemp)));
				break;
			}
			dialog.text = "It all depends on the total amount of ships in your squadron and their size.";
			link.l1 = ""+sTemp+"";
			link.l1.go = "shipshine_1";
		break;
		
		case "shipshine_1":
			dialog.text = "It will cost you "+FindRussianMoneyString(sti(pchar.GenQuest.Shipshine.Money))+", my son.";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Shipshine.Money))
			{
				link.l1 = "I can pay you this sum, father. Take the money.";
				link.l1.go = "shipshine_2";
			}
			link.l2 = "Unfortunately, I don't have that much money on me.";
			link.l2.go = "shipshine_exit";
		break;
		
		case "shipshine_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Shipshine.Money));
			dialog.text = "Very well, my son. Let me collect the sacred vessels and we'll go to the port.";
			link.l1 = "Follow me, father.";
			link.l1.go = "shipshine_3";
		break;
		
		case "shipshine_3":
			DialogExit();
			SetLaunchFrameFormParam("Several hours later"+ NewStr() +"The priest has held mass aboard your ship and blessed it", "Monk_Shipshine", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, GetCompanionQuantity(pchar), 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shipshine_exit":
			DialogExit();
			DeleteAttribute(Pchar, "GenQuest.Shipshine");
		break;
//<-- освятить корабль

//------------------------------------------корабельный капеллан-----------------------------------------------
		case "capellan":
			dialog.text = "Hello captain, allow me to introduce myself. I am a priest and have quite some experience as a chaplain aboard warships. I left my last ship because the captain and I had some...moral disagreements. Do you want to take me in your crew?";
			link.l1 = "A priest aboard? Tell me father, what does a ship's chaplain do?";
			link.l1.go = "capellan_1";
			pchar.questTemp.ShipCapellan = "true";
		break;
		
		case "capellan_1":
			dialog.text = "Why, it is quite obvious. I pray to God for you and your crew, hold mass daily, and bless your men and hear confession before battle. God's word grants strength to your crew's hands and spirits. Your crew will have an opportunity to receive communion and a confession on a regular basis. Believe me, a sailor in a state of grace will hold firm through situations where an impious one will quail\nI ask not much for myself: a one-time payment of fifty thousand pesos for my home parish, a simple bunk in a cabin and a board same to your officers have. That would be all.";
			if (sti(pchar.money) >= 50000)
			{
				link.l1 = "Interesting... You are right, a good captain must carry about not only his crew's bodies but their souls as well. Welcome aboard, father!";
				link.l1.go = "capellan_2";
			}
			link.l2 = "No, father. I am sorry but I can't afford your services.";
			link.l2.go = "capellan_exit";
		break;
		
		case "capellan_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "capellan_2":
			AddMoneyToCharacter(pchar, -50000);
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = "Thank you for your trust, my son. You have spent your money wisely. But I warn you, I serve only worthy captains, whether trader or privateer, it is of no matter. But I will never preach aboard a pirate ship!\nSo if you ever raise the devil's Jolly Roger I will immediately leave your vessel at the very first port.";
			link.l1 = "I will consider that, father, and I'll try to not disappoint you. Please head aboard and introduce yourself to the crew!";
			link.l1.go = "capellan_3";
		break;
		
		case "capellan_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "rld", "loc1", "Monk_Capellan", -1);
			pchar.questTemp.ShipCapellan.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.ShipCapellan.Yes = "true";//капеллан в команде
			Achievment_Set("ach_69");
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			npchar.reputation = 60;
		break;
		
		case "capellan_4":
			dialog.text = "Need anything, my son?";
			link.l1 = "No it's nothing, father.";
			link.l1.go = "exit";
			link.l2 = "Padre, I'd like you to leave the ship in the next port. I will not explain myself further.";
			link.l2.go = "capellan_5";
			NextDiag.TempNode = "capellan_4";
		break;
		
		case "capellan_5":
			dialog.text = "Very well, my son. You are in charge here. I will leave your ship in the next settlement.";
			link.l1 = "Thank you for your understanding, father.";
			link.l1.go = "capellan_6";
		break;
		
		case "capellan_6":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			ShipCapellan_Remove();
		break;
		
		case "capellan_7":
			dialog.text = "Fie, captain! I warned you, that I would leave you if you raise the pirate flag! I am leaving your ship at the next port. I will pray for your immediate repentance and return to the fold of Holy Mother Church.";
			link.l1 = "Well damn...";
			link.l1.go = "exit";
			NextDiag.TempNode = "capellan_7";
		break;
//<-- капеллан
	
//--------------------------------------------монах-пассажир---------------------------------------------------
		case "passenger":
			if (hrand(19) < 15) SetPassengerParameter("Monkpassenger", false);
			else SetPassengerParameter("Monkpassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
			{
				dialog.text = "My "+GetSexPhrase("son","daughter")+", I have to get to " + XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+" it is on "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Dat")+", for "+FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty))+". I'll pay you "+FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money))+" for that. What do you say?";
			}
			else
			{
				dialog.text = "My "+GetSexPhrase("son","daughter")+", the Lord moves in mysterious ways, and so I seek a reliable captain. Can you help me get to " + XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+", which is on "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Dat")+"? I understand that it's like trip to fiery Gehenna, since our enemies never sleep. And I understand that you are not Jesus Christ, but I am not an apostle too, and therefore I have some savings. Will " + FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money)) + " be enough for you?";
			}
			link.l1 = "I agree, father.";
			link.l1.go = "passenger_1";
			link.l2 = "I am sorry, father, but I am sailing in a different direction. Can't help you.";
			link.l2.go = "passenger_exit";
			npchar.quest.passenger = true;
		break;
		
		case "passenger_exit":
			dialog.text = "It is God's will for all, my son. I'll wait for another ship. Peace be with you!";
			link.l1 = "Farewell, padre.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Monkpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "God bless you! You will get your payment when we get to our destination.";
			link.l1 = "Head to my ship, father. We are leaving soon.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Monkpassenger.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "monk");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Monkpassenger.City+"Gen") + ", which is on " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Voc")+"."; // belamour gen
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Monkpassenger.win_condition.l1 = "location";
			pchar.quest.Monkpassenger.win_condition.l1.location = pchar.GenQuest.Monkpassenger.City+"_town";
			pchar.quest.Monkpassenger.function = "Monkpassenger_complete";
			SetFunctionTimerCondition("Monkpassenger_Over", 0, 0, sti(pchar.GenQuest.Monkpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Monkpassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Thank you, my "+GetSexPhrase("son","daughter")+". You have fulfilled your promise and it's my turn now. Take your money as I promised.";
			link.l1 = "Thank you. Good luck, father.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Monkpassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Monkpassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Monkpassenger");
		break;
//<-- монах-пассажир
		
//---------------------------------------------церковная депеша-------------------------------------------------
		case "exit_monkletter":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter":
			dialog.text = "Here. Take this package, my son. Remember that you have only two weeks to deliver it. The pastor is waiting for it. Go, and may God be with you!";
			link.l1 = "I won't fail you, father. Farewell.";
			link.l1.go = "Monkletter_1";
		break;
		
		case "Monkletter_1":
			DialogExit();
			GiveItem2Character(pchar, "letter_church");
			ReOpenQuestHeader("Monkletter");
			AddQuestRecord("Monkletter", "1");
			AddQuestUserData("Monkletter", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("Monkletter", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen"));
			AddQuestUserData("Monkletter", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity));
			SetFunctionTimerCondition("Monkletter_Over", 0, 0, 15, false);
			OfficersReaction("good");
		break;
//<-- Церковная депеша
		
//-------------------------------------------доставить молитвенники---------------------------------------------
		case "exit_churchbooks":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;

		case "Churchbooks":
			dialog.text = "Yes. You can get them in any colony "+NationNameGenitive(sti(npchar.nation))+". Bring all the books that you'll find to our pastor in the church. May God bless you!";
			link.l1 = "Thanks! You will receive your books soon.";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			DialogExit();
			ReOpenQuestHeader("Churchbooks");
			AddQuestRecord("Churchbooks", "1");
			AddQuestUserData("Churchbooks", "sNation", NationNameGenitive(sti(pchar.GenQuest.Churchbooks.Nation)));
			AddQuestUserData("Churchbooks", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity));
			SetFunctionTimerCondition("Churchbooks_Over", 0, 0, 30, false);
			pchar.GenQuest.Churchbooks = "go";
			switch (rand(4))
			{
				case 0: pchar.GenQuest.Churchbooks.Item = "amulet_2"; break;
				case 1: pchar.GenQuest.Churchbooks.Item = "amulet_3"; break;
				case 2: pchar.GenQuest.Churchbooks.Item = "amulet_6"; break;
				case 3: pchar.GenQuest.Churchbooks.Item = "amulet_7"; break;
				case 4: pchar.GenQuest.Churchbooks.Item = "amulet_10"; break;
			}
			OfficersReaction("good");
		break;
//<-- доставить молитвенники
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string DonationType()
{
	string sText;
	switch (hrand(9))
	{
		case 0: sText = "I am gathering money for building "+LinkRandPhrase("a chapel","an almshouse","a hospital")+". The local citizens give little in alms so I must ask prosperous men like you." break;
		case 1: sText = "I am gathering donations for our church. Sailors don't usually have much time to visit the house of God, but everyone must do his best in saving his own soul." break;
		case 2: sText = "I am gathering money to buy food and medicines for our poorhouse for the sick, widows, orphans, and infirm. Please donate sir, because there but for the grace of God go all of us." break;
		case 3: sText = "I am gathering money for new sacred vessels, the ones which we brought from Europe are battered with continual use. It's a duty for every Christian to take care of our Church." break;
		case 4: sText = "I am gathering money for our church's renovation, the roof is leaking terribly and the pews have to be repaired too. It's a duty for every Christian to take care of our Church." break;
		case 5: sText = "I am gathering money to pay the good artist who is able to paint the walls of our church and draw scenes from the Bible on them for those of our parish who cannot read. It's a duty for every Christian to take care about his Church." break;
		case 6: sText = "I am gathering money for a new high altar for our church. Our parish is poor and we would like a noble seat for the Blessed Sacrament. I do hope for your help." break;
		case 7: sText = "There are a lot of wounded sailors from pirate raids in our hospital. They need medicines and bandages. Pray help them, for you can really understand sufferings of the common sailors." break;
		case 8: sText = "I am trying to get money for clothes and food for our poorest citizens. The only hope they have is our holy church. Please help them." break;
		case 9: sText = "I am going to go deep in our island for missionary work to bring the light of Christ's Gospel to the lost souls of the pagan Indians. I am gathering funds for this expedition. Please help our good deed!" break;
	}
	return sText;
}
