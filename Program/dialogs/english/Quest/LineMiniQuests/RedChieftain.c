void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "This is a bug. Let the devs know.";
			link.l1 = "I will!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "RedChieftain":
			dialog.text = "How, paleface. I see that you are captain of big canoe. I am Kanauri. I am chief of Cayman - mighty Arawak tribe. I want to talk with you.";
			link.l1 = "I am listening, chief. What troubles have brought you to me?";
			link.l1.go = "RedChieftain_0";
			link.l2 = "What do you want from me, you foul red-skinned ape? Go back to your jungles and don't bother me with your requests.";
			link.l2.go = "RedChieftain_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
		break;
		
		case "RedChieftain_exit":
			dialog.text = "Gu-u! Wasn't white captain taught to be polite? I made offer. You earn heap lot wampum but now I go. Farewell, paleface.";
			link.l1 = "Go on, get lost...";
			link.l1.go = "RedChieftain_exit_1";
		break;
		
		case "RedChieftain_exit_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.RedChieftain");
			chrDisableReloadToLocation = false;
			ChangeIndianRelation(-3.0);
		break;
		
		case "RedChieftain_0":
			dialog.text = "White brother, insightful like owl, cunning like serpent. Trouble coming to Indian. Big-big canoe of white men came to my village. They took many Cayman, my people, put them on their canoe and took them out to Mother of All Waters...";
			link.l1 = "Wait... are you saying that your people were enslaved by white men from a ship?";
			if (sti(pchar.Basenation) == SPAIN) link.l1.go = "RedChieftain_2";
			else link.l1.go = "RedChieftain_1";
		break;
		
		case "RedChieftain_1":
			dialog.text = "You speak true, white brother. I know those palefaces are no friends to you. These cruel white men of the Spanish tribe. They take my people. But I find them. The Spanish make Indians work from dawn to dusk, dive deep in the Mother of Waters, find shells filled with the tears of the gods.";
			link.l1 = "Pearl diving... That is a brutal job.";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Spa = "true";
			pchar.questTemp.RedChieftain.AttackNation = SPAIN;
		break;
		
		case "RedChieftain_2":
			dialog.text = "You speak true, white brother. I know those people are not friends to you. They are of the English tribe. They take my people. But I find them. The English make Indians work from dawn to dusk, dive deep in the Mother of Waters, find shells filled with the tears of gods.";
			link.l1 = "Pearl diving... This is tough work.";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Eng = "true";
			pchar.questTemp.RedChieftain.AttackNation = ENGLAND;
		break;
		
		case "RedChieftain_3":
			dialog.text = "Indians grow sick and die from slavery. White men have no pity for Indians. The lash and pistol are the law of the white man for the Indian. I am old. I have no men left to fight. The Cayman Arawaks are a peaceful people, we invented the peace pipe. I ask you, white brother, to unsheathe your lash and pistol against the evil whites, save the Arawak Indians.";
			link.l1 = "Are you asking me to declare war? You have to understand, chief, my resources are limited.";
			link.l1.go = "RedChieftain_4";
		break;
		
		case "RedChieftain_4":
			dialog.text = "No go on warpath. Free Indian. My people. We give you all the tears of the gods we have in canoes. Kill evil white man, help Indian, get tears of the gods, sell them for much wampum. Heap of wampum";
			link.l1 = "Ah, I see now. No, Canauri, I can't help you. I can't do it now - my ship is in need of repair, and I have no supplies left...";
			link.l1.go = "RedChieftain_wait";
			link.l2 = "In that case, it would be my pleasure. Let's discuss the details. Where are your people? You said that you'd already found them...";
			link.l2.go = "RedChieftain_5";
		break;
		
		case "RedChieftain_wait":
			dialog.text = "Gu-u! I can wait, white brother... I will be in this port one more moon, looking for a protector of my people. You find me here when you are ready.";
			link.l1 = "...";
			link.l1.go = "RedChieftain_wait_1";
		break;
		
		case "RedChieftain_wait_1":
			DialogExit();
			//LAi_ActorGoToLocator(npchar, "quest", "quest1", "RedChieftainStay", -1);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			SetFunctionTimerCondition("RedChieftainDelete", 0, 0, 30, false);
			
			sld = CharacterFromID("RedChieftain");
            //LAi_SetStayType(sld);
			sld.dialog.currentnode = "RedChieftain_wait_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity, false);
		break;
		
		case "RedChieftain_wait_2":
			dialog.text = "You are back, white brother? Will you help me punish evil men and save the Indian?";
			link.l1 = "Ready as I'll ever be.";
			link.l1.go = "RedChieftain_wait_4";
			link.l2 = "I still need to get prepared.";
			link.l2.go = "RedChieftain_wait_3";
		break;
		
		case "RedChieftain_wait_3":
			dialog.text = "I will be here, white brother.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.Tempnode = "RedChieftain_wait_2";
		break;
		
		case "RedChieftain_wait_4":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
			dialog.text = "I am very glad that you agreed, white brother!";
			link.l1 = "Let's talk about the details, Canauri. Where are your people? You said you'd already found them...";
			link.l1.go = "RedChieftain_5";
			pchar.quest.RedChieftainDelete.over = "yes"; //снять таймер
		break;
		
		case "RedChieftain_5":
			if (CheckAttribute(pchar, "questTemp.RedChieftain.Spa"))
			{
				AddMapQuestMarkShore("Shore19", true);
				pchar.questTemp.RedChieftain.Island = "Cumana";
				pchar.questTemp.RedChieftain.Shore = "Shore19";
				pchar.questTemp.RedChieftain.Add1 = "Spanish";
				pchar.questTemp.RedChieftain.Add2 = "Carupano Cove, not far from Cumana";
				dialog.text = "They are camped at Carupano Cove near the Spanish camp called Cumana. Every day they sail out to sea in boats, diving into the water, deep, deep...";
				link.l1 = "I see. And the Spanish are watching over them while they dive?";
				link.l1.go = "RedChieftain_6";
			}
			else
			{
				AddMapQuestMarkShore("Shore54", true);
				pchar.questTemp.RedChieftain.Island = "SantaCatalina";
				pchar.questTemp.RedChieftain.Shore = "Shore54";
				pchar.questTemp.RedChieftain.Add1 = "English";
				pchar.questTemp.RedChieftain.Add2 = "Cape Perlas, not far from Blueweld";
				dialog.text = "They make camp at Cape Perlas near the English camp called Blueweld. Every day they sail out to sea in boats, diving deep, deep...";
				link.l1 = "I see. And, of course, the English are watching over them?";
				link.l1.go = "RedChieftain_6";
			}
		break;
		
		case "RedChieftain_6":
			dialog.text = "Yes, two big canoes of palefaces with firesticks and big knives. Camp on shore also guarded - Indian cannot escape.";
			link.l1 = "What kind of ships? Can you describe them? How big are they? What kind of sails?";
			link.l1.go = "RedChieftain_7";
		break;
		
		case "RedChieftain_7":
			dialog.text = "This canoe is big, but Canauri has seen bigger. The front sail is very, very tilted, making three sides like this. (He draws three lateen sails and a trapezoidal sail in the dirt) The top is narrow, the bottom is wide.";
			link.l1 = "Sounds and looks like a schooner...";
			link.l1.go = "RedChieftain_8";
		break;
		
		case "RedChieftain_8":
			dialog.text = "Canauri does not know that word. Paleface must be very careful if they see another canoe - they land the Indian and wait until the other canoe sails away.";
			link.l1 = "Cautious sons of bitches... how can I get close to them?";
			link.l1.go = "RedChieftain_9";
		break;
		
		case "RedChieftain_9":
			dialog.text = "If paleface brother takes small canoe then he can sneak near the shore. I show way. But bring only one small canoe or paleface dog see and drive Indian from boat into jungle...";
			link.l1 = "Got it. I'll need a lugger or a sloop for this operation. Great. A sloop against two schooners... God... and here I thought this was going to be easy!";
			link.l1.go = "RedChieftain_10";
		break;
		
		case "RedChieftain_10":
			dialog.text = "Shall we go, white brother? We have less than a moon.";
			link.l1 = "Yes. Get on my ship, chief. Let's not waste time!";
			link.l1.go = "RedChieftain_11";
		break;
		
		case "RedChieftain_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.Red_Chieftain_2.win_condition.l1 = "location";
			pchar.quest.Red_Chieftain_2.win_condition.l1.location = pchar.questTemp.RedChieftain.Island;
			pchar.quest.Red_Chieftain_2.function = "RedChieftain_CreateShooner";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("RedChieftainOver", 0, 0, 30, false);
			AddQuestRecord("RedChieftain", "1");
			AddQuestUserData("RedChieftain", "sText1", pchar.questTemp.RedChieftain.Add1);
			AddQuestUserData("RedChieftain", "sText2", pchar.questTemp.RedChieftain.Add2);
		break;
		
		case "RedChieftain_pearl":
			dialog.text = "Thank you, white brother! You have saved the Cayman Arawak tribe! We owe you a great debt. The path is free of paleface dogs and Indians can run free in the jungles. We give you all the tears of the gods left on the boats.";
			link.l1 = "Well, let's see what you've got...";
			link.l1.go = "RedChieftain_pearl_1";
		break;
		
		case "RedChieftain_pearl_1":
			DialogExit();
			pchar.questTemp.RedChieftain.Ind = 1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_pearl_give":
			int iSmallPearl = rand(200)+rand(250)+rand(200)+250;
			int iBigPearl = rand(100)+rand(100)+rand(50)+150;
			TakeNItems(pchar, "jewelry52", iBigPearl);
			TakeNItems(pchar, "jewelry53", iSmallPearl);
			PlaySound("interface\important_item.wav");
			Log_SetStringToLog("The Chief has given you "+iSmallPearl+" small and "+iBigPearl+" big pearls.");
			dialog.text = LinkRandPhrase("I am glad that the tears of the gods are yours, brother of the Arawak!","Indian, thank you, brave paleface!","Take our catch, white brother!");
			link.l1 = LinkRandPhrase("Glad to help you!","Thanks, red-skinned brother!","Great!");
			link.l1.go = "exit";
			pchar.questTemp.RedChieftain.Ind = sti(pchar.questTemp.RedChieftain.Ind)+1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_final":
			chrDisableReloadToLocation = false;//открыть локацию
		// belamour legendary edition -->
			if(sti(pchar.questTemp.RedChieftain.Tartane) > 5)
			{
				dialog.text = "Canauri thanks you again, paleface brother! You rescued all the canoes with the Indians! For Canauri, it is very important to save every canoe because you also saved the grandson of Canauri, whom the evil palefaces took into slavery. As a child, my grandson loved to swim very much, and Canauri gave him this charmed amulet so that he would not drown. Now the grandson no longer wants to swim and has given the amulet to me so that I can give it to you, paleface brother. I hope that the tears of the gods and this gift will be a sufficient reward for the life of an Arawak. And now we say goodbye - it's time for us to return to our native village.";
				link.l1 = "Good luck, Cunauri! I'm glad your grandson survived! I pray this evil never befalls you again!";
				link.l1.go = "RedChieftain_final_1Obereg";
			}
			else
			{
				dialog.text = "Canauri thanks you again, pale-faced brother! I hope that the tears of the gods will be enough reward for the lives of the Indians. Now goodbye, we go to our native village.";
				link.l1 = "Good luck, Cunauri! Never fall into slavery again!";
				link.l1.go = "RedChieftain_final_1";
			}
			if(SandBoxMode)
			{
				//if(CheckAttribute(pchar,"questTemp.SanBoxTarget"))
				//{
					//if(makeint(pchar.questTemp.SanBoxTarget) == 2 ||  makeint(pchar.questTemp.SanBoxTarget) == 5)
					//{
						pchar.questTemp.SanBoxTarget.RedChieftain = true;
						ChangeCharacterComplexReputation(pchar, "fame", 25);
					//}
				//}
			}
		break;
		
		case "RedChieftain_final_1Obereg":
			DialogExit();
			RemovePassenger(Pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			int n1 = pchar.questTemp.RedChieftain.Tartane;
			for (i=1; i <=n1; i++)
			{
				sld = characterFromId("RC_Indian_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			TakeNItems(pchar, "talisman10", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received Seeker's obereg");
			locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; //энкаутеры открыть
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddQuestRecord("RedChieftain", "9");
			CloseQuestHeader("RedChieftain");
			DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;
		// <-- legendary edition
		
		case "RedChieftain_final_1":
			DialogExit();
			RemovePassenger(Pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			int n = pchar.questTemp.RedChieftain.Tartane;
			for (i=1; i <=n; i++)
			{
				sld = characterFromId("RC_Indian_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; //энкаутеры открыть
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddQuestRecord("RedChieftain", "8");
			CloseQuestHeader("RedChieftain");
			DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
