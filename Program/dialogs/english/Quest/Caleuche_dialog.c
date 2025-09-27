void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "That is definitely a bug. Can you please inform Jason about when and how that happened.";
			link.l1 = "Will do.";
			link.l1.go = "exit";
		break;
		
		// шаман карибов Туттуатхапак
		case "Tuttuat":
			dialog.text = "Why have you come to my hut, white man? Tuttuathapak does not consider you his dear guest.";
			if (GetCharacterFreeItem(pchar, "mushket1") || GetCharacterFreeItem(pchar, "mushket2") || GetCharacterFreeItem(pchar, "mushket7"))
			{
				link.l1 = "Hail to you, great shaman Tuttuathapak. I have come to seek your help and advice. Please accept this musket as a token of my goodwill.";
				link.l1.go = "Tuttuat_1";
			}
			else
			{
				link.l1 = "Hail to you, great shaman Tuttuathapak. I have come to seek your help and advice.";
				link.l1.go = "Tuttuat_exit";
			}
		break;
		
		case "Tuttuat_exit":
			dialog.text = "Tuttuathapak will not help white man. White men are bad men. They kill and conquer Indians, make Indians slaves. Tuttuathapak gives white man no advice. You leave now.";
			link.l1 = "Hmm...";
			link.l1.go = "Tuttuat_exit_1";
		break;
		
		case "Tuttuat_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat";
		break;
		
		case "Tuttuat_1":
			if (GetCharacterFreeItem(pchar, "mushket1")) 
			{
				sTemp = "mushket1";
			}
			else 
			{
				if(GetCharacterFreeItem(pchar, "mushket2"))
				{
					sTemp = "mushket2";
				}
				else
				{
					sTemp = "mushket7";
				}
			}
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You have given: "+XI_ConvertString(sTemp)+"");
			dialog.text = "You know what to give to Tuttuathapak, white man. Tuttuathapak accepts your gift. He will speak. What advice do you seek from me?";
			link.l1 = "I heard that you came from a distant place in the South. I have an Indian amulet, and a knowledgeable man told me that you might know how it can be used.";
			link.l1.go = "Tuttuat_2";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_2":
			dialog.text = "Show the amulet.";
			link.l1 = "Here you go, great shaman.";
			link.l1.go = "Tuttuat_3";
		break;
		
		case "Tuttuat_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(looking at the amulet)... Your friend speaks the truth, white man. This amulet belonged to my people, the great Indians, Chavin was their name. A cursed, blasphemous, pale-faced cur defiled the shrine and brought it here. Tuttuathapak punished that hound.";
			link.l1 = "You deprived him of his mind, I take it?";
			link.l1.go = "Tuttuat_4";
		break;
		
		case "Tuttuat_4":
			dialog.text = "White man surprises Tuttuathapak with his knowledge. Yes, I devoured the mind of that scurvy cur. He and his filthy men got their due.";
			link.l1 = "I see... Tell me, shaman, what is this amulet used for? Perhaps it can protect one in battle or ward off evil magic?";
			link.l1.go = "Tuttuat_5";
		break;
		
		case "Tuttuat_5":
			dialog.text = "This amulet is of no use to you, white captain. You cannot use its power. Only the great shamans of our tribe know how to awaken it.";
			link.l1 = "Hmm... So, it turns out I made such a long journey in vain. But perhaps you can awaken the power of this amulet, great shaman? Surely we could come to an agreement...";
			link.l1.go = "Tuttuat_6";
		break;
		
		case "Tuttuat_6":
			dialog.text = "Even if I awaken the amulet, you will not hold its power for long. But I offer you a deal, white man.";
			link.l1 = "What kind of deal?";
			link.l1.go = "Tuttuat_7";
		break;
		
		case "Tuttuat_7":
			dialog.text = "Three amulets like this were taken from our shrine. They have different powers, but if they are brought together, they become very, very powerful. Find all three amulets and bring them to me, and I will reward you. I will give you power you can hold forever.";
			link.l1 = "I don't quite understand... What kind of power are you talking about?";
			link.l1.go = "Tuttuat_8";
		break;
		
		case "Tuttuat_8":
			dialog.text = "You will know everything in due time. Find and bring me all three amulets. They are in the Caribbean. Seek them out and find them. You will recognise them easily – they look alike. Go, white man. Tuttuathapak waits and asks the spirits to help you.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_9";
		break;
		
		case "Tuttuat_9":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "ghostship"; 
			AddQuestRecord("Caleuche", "3");
			pchar.quest.Caleuche_ghostship.win_condition.l1 = "location";
			pchar.quest.Caleuche_ghostship.win_condition.l1.location = "Dominica";
			pchar.quest.Caleuche_ghostship.function = "Caleuche_PrepareGhostship";
		break;
		
		case "Tuttuat_10":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "Go, white man. Find two more amulets.";
				link.l1 = "I have already found them, great shaman. Here, take a look.";
				link.l1.go = "Tuttuat_33";
			}
			else
			{
				dialog.text = "Go, white man. Find the other two amulets.";
				link.l1 = "...";
				link.l1.go = "Tuttuat_10_1";
			}
		break;
		
		case "Tuttuat_10_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
		break;
		
		case "Tuttuat_11":
			dialog.text = "You here again, white man? You look like you met a fierce jaguar in the jungle.";
			link.l1 = "Worse, great shaman. As I stepped into the sea, a massive storm appeared out of nowhere and I was attacked by a ship manned by the undead! Their captain was utterly invincible. First he took the amulet from me and nearly killed me - I barely survived. And then they almost sank my ship, only a handful of my crew survived.";
			link.l1.go = "Tuttuat_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Tuttuat_12":
			dialog.text = "Bad news, white man. The Caleuche is going in for the kill again.";
			link.l1 = "The Caleuche? That undead captain called his ship the Flying Heart. So, you knew about the ghost ship and you didn't warn me? If I had known that this sailing nightmare was hunting for the amulet, I'd never...";
			link.l1.go = "Tuttuat_13";
		break;
		
		case "Tuttuat_13":
			dialog.text = "Tuttuathapak sees the white captain is upset. The white captain must calm down.";
			link.l1 = "Calm down?! Are you insane? How can I even survive against such a thing!";
			link.l1.go = "Tuttuat_14";
		break;
		
		case "Tuttuat_14":
			dialog.text = "Yes. Calm down and don't shout. Tell me – do you still want to receive great power from me, which will stay with you forever?";
			link.l1 = "Well, of course I do. But I don't have the amulet anymore.";
			link.l1.go = "Tuttuat_15";
		break;
		
		case "Tuttuat_15":
			dialog.text = "I'll teach you how to take the amulet from the captain of the Caleuche. It won't be easy. But if you do it, you'll take his ship as your prize, find valuable treasure, win glory among your people, and receive a reward from me.";
			link.l1 = "Goddamn it! I'd gladly destroy that shrivelled monster! But how can I defeat him, if he cannot be harmed by either sword or bullet?!";
			link.l1.go = "Tuttuat_16";
		break;
		
		case "Tuttuat_16":
			dialog.text = "You ready to listen to me, white captain?";
			link.l1 = "Yes, I am, great shaman.";
			link.l1.go = "Tuttuat_17";
		break;
		
		case "Tuttuat_17":
			dialog.text = "When my father was a young warrior, white men came to my land on a ship called the Flying Heart. They went to the mountains. Legend says a shrine of our ancestors is hidden there. Shrine of the jaguar warriors. The white men found the shrine and gold and defiled an ancient sacred thing. They took away the great treasure of the Chavins - the jade skull of Yum Cimil, god of death and patron of the jaguar men.\nThe white men returned to their ship. They decided to come back for more gold, but as one of their men stepped onto dry land, he died in horrible pain. Yum Cimil cursed the captain and his crew. They became immortal, but they could never set foot on land again. They sailed for many, many winters, half a century by your calendar. That's how the Caleuche emerged.\nTheir bodies withered, their flesh rotted, but they still lived. If you hack an arm or leg off, it grows back. If you slice them in two, they become whole again. If their ship goes down, they repair it underwater, and it sails again.";
			link.l1 = "Just great...";
			link.l1.go = "Tuttuat_18";
		break;
		
		case "Tuttuat_18":
			dialog.text = " The Caleuche terrorises sailors. It attacks without reason and spells certain doom. It is not a frequent guest in the Caribbean. It prefers sailing along the shores of my motherland. Methinks he wants to remove the curse. But he will never lift it.";
			link.l1 = "Why? What must be done to lift the curse?";
			link.l1.go = "Tuttuat_19";
		break;
		
		case "Tuttuat_19":
			dialog.text = "Jade skull. It must be returned to the shrine of Yum Cimil, temple of the jaguar warriors. There are several temples. Elders of my tribe say there is one on a small island in the Caribbean. That's why the Caleuche sailed there. Once the skull is at the temple, the spell of Yum Cimil breaks, and they become mortal and can no longer heal their wounds.";
			link.l1 = "Ha! More likely, they aren't going to return the skull! Why would they, if they're immortal and invincible? And besides, they simply cannot bring it back if they aren't allowed to set foot on land, right?";
			link.l1.go = "Tuttuat_20";
		break;
		
		case "Tuttuat_20":
			dialog.text = "They don't have the skull. The captain threw it away in my ancestors' land, when he returned from the shrine of the jaguar men. Jade is not gold, the white man did not need it, he could not take the beautiful green gem from the skull's eyes. And so he threw it away. One sailor picked it up, and he was not touched by the curse\nWhen the sailor saw what the Caleuche crew had become, he fled. He came to our village. My father saw that sailor and the skull of Yum Cimil. And then the white man went north along the coast and took the skull with him.";
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul"))
				{
					link.l1 = "A jade skull with green stones in the eye sockets? I had it in my hands, can you imagine? I gave it to Solomon myself. But he left for Europe with his daughter, and it seems he took the skull with him.";
				}
				else
				{
					link.l1 = "A jade skull with green gems in the eye sockets? Bloody hell... I... I held it in my own hands! And I sold it to some Portuguese... Merriman, or something like that... Yes, that's what he called it - the skull of Yum Cimil! He wanted it desperately! He paid half a million pesos for it!";
				}
				link.l1.go = "Tuttuat_21_1";
			}
			else
			{
				link.l1 = "A jade skull with green gems in the eye sockets? So that's what I need to find? But that sailor could have perished in the selva fifty years ago, and the skull might be lost forever!";
				link.l1.go = "Tuttuat_21_2";
			}
		break;
		
		case "Tuttuat_21_1":
			dialog.text = "I know the skull is in the Caribbean. The Caleuche is here not by chance. For the last six moons, it has often been seen at the island. In former times, it was not there for many winters. The captain of the Caleuche can sense the artifact of the jaguar men. That's how he found you and your ship.";
			link.l1 = "So, do I understand correctly that I have to find this skull again? And then what am I supposed to do with it?";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_21_2":
			dialog.text = "Skull must be here, in the Caribbean. Caleuche is here not by chance. For the last six moons it has often been seen at the island. Before that, it was not there for many winters. The captain of the Caleuche can sense the artifact of the jaguar men. That's how he found you and your ship.";
			link.l1 = "So, do I understand correctly that I have to find this skull again? And then what am I supposed to do with it?";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_22":
			dialog.text = "First, you must find the two amulets we spoke of. Without them, you cannot do anything. The amulets give you the power to stand against the jaguar men and any enemy you encounter.";
			link.l1 = "Stand against jaguar men? What are you talking about?";
			link.l1.go = "Tuttuat_23";
		break;
		
		case "Tuttuat_23":
			dialog.text = "The temple where you must bring the jade skull is on a deserted island in the Caribbean. It is guarded by jaguar men. They were all dead, but now they live again. Without the amulet, you will not pass them. In life, the jaguar men were fierce warriors, and in death they have become almost invincible. They are given strength by Yum Cimil himself.";
			link.l1 = "Undead? Again? Lucky me...";
			link.l1.go = "Tuttuat_24";
		break;
		
		case "Tuttuat_24":
			dialog.text = "Why so surprised, white captain? Yum Cimil is the god of death, the jade skull gives power over the dead and the living. Caribbean. It is guarded by jaguar men. Without the amulet you cannot pass them. With the amulet you can enter the temple and survive, leave the skull there, then find the Caleuche, defeat her captain and take back the amulet he took from you.";
			link.l1 = "And why does the captain of the Caleuche need these amulets?";
			link.l1.go = "Tuttuat_25";
		break;
		
		case "Tuttuat_25":
			dialog.text = "Methinks he wants to go to the temple of the jaguar men, and he thinks the amulet will help him. But I could be wrong. Still, the Caleuche is always lured by artefacts from my land. She sailed near the island where the temple of the jaguar men is, and she sailed along the shores of my motherland.";
			link.l1 = "And where is that island?";
			link.l1.go = "Tuttuat_26";
		break;
		
		case "Tuttuat_26":
			dialog.text = "First you find the skull of Yum Cimil and the amulets. Then we talk about the island.";
			link.l1 = "Fine. Can you give me a hint where to look for the jade skull?";
			link.l1.go = "Tuttuat_27";
		break;
		
		case "Tuttuat_27":
			dialog.text = "I know not. But it's here, in the Caribbean. And amulets, too. Ask. Seek. Find.";
			link.l1 = "Heh... Alright, I'll try.";
			link.l1.go = "Tuttuat_28";
		break;
		
		case "Tuttuat_28":
			dialog.text = "And you be careful, white captain. The Caleuche senses Chavin's items. When you have the amulet, she will seek you. If she finds you, flee, and quickly. If she catches you, you're a dead man.";
			link.l1 = "This cursed ship is insanely fast! It's about twice as fast as any ship I've ever seen. But I noticed that it struggles when sailing into the wind.";
			link.l1.go = "Tuttuat_29";
		break;
		
		case "Tuttuat_29":
			dialog.text = "The Caleuche is cursed - that's why she's so fast. Hard to escape. You must have a ship which can outrun the Caleuche. Or you end up dead. When you find the amulet, bring it to me. Do not keep the amulet on the ship.";
			link.l1 = "I've already got it. Thank you for your tale, great shaman. It's time for me to go now.";
			link.l1.go = "Tuttuat_31";
		break;
		
		case "Tuttuat_31":
			dialog.text = "I am asking the spirits to help you and save you from the Caleuche.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_32";
		break;
		
		case "Tuttuat_32":
			DialogExit();
			LocatorReloadEnterDisable("Shore27", "boat", false);
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "mayak"; 
			AddQuestRecord("Caleuche", "6");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Amuletmaster") && pchar.questTemp.Caleuche.Amuletmaster == "Santiago_Lightman") {AddLandQuestMark(characterFromId("Santiago_Lightman"), "questmarkmain");}
			if (CheckAttribute(pchar, "questTemp.Caleuche.Amuletmaster") && pchar.questTemp.Caleuche.Amuletmaster == "BasTer_Lightman") {AddLandQuestMark(characterFromId("BasTer_Lightman"), "questmarkmain");}
		break;
		
		case "Tuttuat_33":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given the amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "(looking) Yes, that's the one. The second Chavin amulet. You're good. You still need to find another amulet.";
			link.l1 = "I remember that, shaman. Soon you shall have it.";
			link.l1.go = "Tuttuat_34";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_34":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
			AddQuestRecord("Caleuche", "22");
			if (!Caleuche_CheckAmulet())
			{
				if (GetCharacterIndex("Map_Caleuche") != -1)
				{
					sld = characterFromId("Map_Caleuche");
					sld.lifeday = 0;
					Map_ReleaseQuestEncounter("Map_Caleuche");
				}
			}
		break;
		
		case "Tuttuat_35":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "Go, white man. Find one more amulet.";
				link.l1 = "I already have it, great shaman. Here, take a look.";
				link.l1.go = "Tuttuat_36";
			}
			else
			{
				dialog.text = "Go, white man. Find one more amulet.";
				link.l1 = "...";
				link.l1.go = "Tuttuat_35_1";
			}
		break;
		
		case "Tuttuat_35_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
		break;
		
		case "Tuttuat_36":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given the amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "(looking) Yes, that's the one. The third Chavins amulet. You're good. You found all the amulets to pass the dead jaguar warriors, servants of Yum Cimil.";
			link.l1 = "Now, as I understand it, I will need the jade skull?";
			link.l1.go = "Tuttuat_37";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_37":
			dialog.text = "You speak the truth. The jade skull of Yum Cimil. You must take it to Chavin's temple. Then the Caleuche will lose its power for good.";
			link.l1 = "Tuttuathapak, please, tell me, where should I look? Any thoughts?";
			link.l1.go = "Tuttuat_38";
		break;
		
		case "Tuttuat_38":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "No. You think where you last saw jade skull. Whom you gave it to. Start searching there.";
				link.l1 = "Alright, great shaman. I'll do everything I can.";
				link.l1.go = "Tuttuat_39";
			}
			else
			{
				dialog.text = "A white warlock interested in the skull of Yum Cimil. He seeks it. He even came to our village. I heard the warlock lives in a house on a Dutch island. Seek the warlock on the Dutch island, and you may learn something.";
				link.l1 = "Alright, great shaman. I'll do everything I can.";
				link.l1.go = "Tuttuat_39";
			}
		break;
		
		case "Tuttuat_39":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
			AddQuestRecord("Caleuche", "23");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul")) sTemp = "I'll start with Curacao, where I handed it over to Solomon. Maybe I'll find some clue - to find out what happened to the skull.";
				else sTemp = "I'll start with visiting Curacao - there I've sold the jade skull to Joachim Merriman.";
			}
			else sTemp = "Tuttuathapak told me, that a 'white warlock' showed interest in the jade skull, and adviced seeking for him on Dutch islands. Who might that be?";
			AddQuestUserData("Caleuche", "sText", sTemp);
			if (GetCharacterIndex("Map_Caleuche") != -1)
			{
				sld = characterFromId("Map_Caleuche");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter("Map_Caleuche");
			}
			pchar.questTemp.Caleuche = "skul";
			pchar.quest.Caleuche_villemstad.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstad.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Caleuche_villemstad.function = "Caleuche_CreateMonk";
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Tuttuat_40":
			dialog.text = "Go, white man. Find the jade skull of Yum Cimil.";
			if (pchar.questTemp.Caleuche == "island")
			{
				link.l1 = "I have it here, great shaman, take a look.";
				link.l1.go = "Tuttuat_45";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Tuttuat_40_1";
			}
		break;
		
		case "Tuttuat_40_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_41":
			dialog.text = "Go, white man. Find the jade skull of Yum Cimil.";
			link.l1 = "I am afraid I will not be able to do it. I have found the warlock, but at the last moment he slipped away with the skull. I have absolutely no idea where he could be now.";
			link.l1.go = "Tuttuat_42";
		break;
		
		case "Tuttuat_42":
			dialog.text = "This is very bad, white man. Now you will not pass the temple and will not defeat the Caleuche. I give you no gift. Now you leave.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_43";
		break;
		
		case "Tuttuat_43":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_44";
		break;
		
		case "Tuttuat_44":
			dialog.text = "You leave now, white man.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_44_1";
		break;
		
		case "Tuttuat_44_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_45":
			dialog.text = "(looking) Yes, that's the one. Very beautiful. And very frightening.";
			link.l1 = "Sure... But what's more interesting – I crossed the entire Caribbean Sea from Cuba to Dominica, and the Caleuche never tried to attack me when I had this skull; I didn't even see it. Yet when I was carrying amulets to you, it constantly hunted me down – as soon as I set sail, it found me within a few hours.";
			link.l1.go = "Tuttuat_46a";
			DelLandQuestMark(npchar);
		break;
		
		case "Tuttuat_46a":
			dialog.text = "Methinks the Caleuche is afraid of the skull, or it cannot sense it. I have no other explanation. Perhaps Yum Cimil made the jade skull very dangerous to the Caleuche - in addition to the curse. Perhaps that's why the captain wanted so much to take the three amulets of my people. To gain wisdom on how to control the spell of Yum Cimil.";
			link.l1 = "So, as long as I have the jade skull on board my ship, I need have no fear of the Caleuche's attacks?";
			link.l1.go = "Tuttuat_46b";
		break;
		
		case "Tuttuat_46b":
			dialog.text = "Exactly, pale-faced one. You see it for yourself.";
			link.l1 = "Very good! So, I can take command of a large ship, hire a decent crew and prepare a nice welcome for that walking dead man, when the spell is lifted from him, without fear that he'd intercept me earlier...";
			link.l1.go = "Tuttuat_46c";
		break;
		
		case "Tuttuat_46c":
			dialog.text = "";
			link.l1 = "...about that spell, by the way - where should I take the jade skull?";
			link.l1.go = "Tuttuat_46";
		break;
		
		case "Tuttuat_46":
			dialog.text = "You must take it to Chavin's temple and finish your journey. I want to tell you a story. You ready to listen, white man?";
			link.l1 = "My ears are always open to your wisdom, Tuttuathapak.";
			link.l1.go = "Tuttuat_47";
		break;
		
		case "Tuttuat_47":
			dialog.text = "As the legends of my ancestors say, long ago, when pale-faced men had not yet come to our land, the great chieftain of the Chavins built a very, very large canoe and sent it with a party of warriors to the land of many islands. The son of the great chieftain led them, and among them was one of the high shamans. In the land of many islands, they found a deserted place and founded a settlement, building a great temple for Yum Cimil, which only our great ancestors could have built\nMessengers returned with good news, but no one ever saw the chieftain’s son, nor the shaman, nor the warriors again. Legend has it that they stayed there to live, but the wisest of shamans spoke to the spirits and said that no people lived there anymore, and that Yum Cimil ruled this land\nThe land of many islands is the Caribbean, white man. The temple of Yum Cimil is on an island where no white men nor Indians live. Only the servants of Yum Cimil, the Chavinavi, still guard the temple corridors.";
			link.l1 = "And where is this island?";
			link.l1.go = "Tuttuat_48";
		break;
		
		case "Tuttuat_48":
			dialog.text = "From the tale I understand that it is a small island, lying from the island with this village in the direction the pale faces call 'north', in the midst of three islands, and on the fourth side there is the great water — the ocean.";
			link.l1 = "Hmm... To the north of Dominica, within a triangle of islands, right at the edge of the ocean? Damn, that’s quite a stretch of sea! How am I supposed to find a tiny island there that no one has ever heard of?";
			link.l1.go = "Tuttuat_49";
		break;
		
		case "Tuttuat_49":
			dialog.text = "I cannot say for certain. But I know yet another story. You could have heard it from your brothers. About twenty winters ago, a white man found that island. With a woman and an old man, he entered the temple of Yum Cimil and took away a powerful artifact - the Orb of the Rising Sun. At the shores of the island, the pale-faced captain was attacked by the Caleuche\nThe pale-faced man was clever. He blinded the captain and crew of the Caleuche with the rising sun. The curse of the Caleuche weakened, and the captain sank it, but the Orb of the Rising Sun dissolved. If you find that pale-faced man, he will tell you where the island is.";
			if (CheckAttribute(pchar, "questTemp.NatanStory")) link.l1 = "Ha! I think I know that 'pale-faced man'... The stories sound too similar. So, the Caleuche was sunk?";
			else link.l1 = "Hmm... So, the Caleuche has been sunk?";
			link.l1.go = "Tuttuat_50";
		break;
		
		case "Tuttuat_50":
			dialog.text = "Yes, but the curse protects them from death. They fixed it and continued on their eternal journey.";
			link.l1 = "Alright, got it. But what should I do in the temple? Where should I put the skull? How can I defeat the jaguar warriors guarding it? If they are Chavinavi like those summoned by that warlock Merriman, it would be foolish to go there alone – each of them is as strong as ten soldiers.";
			link.l1.go = "Tuttuat_51";
		break;
		
		case "Tuttuat_51":
			dialog.text = "They are not. Chavinavi summoned by the white warlock with the skull are weak. Much weaker than those summoned by Yum Cimil himself. You can never harm them, and they kill you with a single touch of their weapon.";
			link.l1 = "Hold on - and how did that 'pale-faced man' manage to enter the temple and steal the artifact?";
			link.l1.go = "Tuttuat_52";
		break;
		
		case "Tuttuat_52":
			dialog.text = "Before that first pale-faced man entered the temple, it was guarded by the spirits of dead ancestors. The pale-faced man was a strong warrior and he defeated them. When he stole the orb of the rising sun, Yum Cimil was furious. He sent fire and brimstone upon the pale-faced man and almost destroyed the temple, but he escaped with the artefact. Now Yum Cimil has summoned invincible jaguar warriors to guard the temple.";
			link.l1 = "Glorious! And how am I supposed to sneak in, then?";
			link.l1.go = "Tuttuat_53";
		break;
		
		case "Tuttuat_53":
			dialog.text = "I help you, white man. I give you two Chavin amulets you bring me. I will speak to the ancestor spirits and empower the amulet. When you have one with you, you can fight jaguar warriors like common soldiers; you will be like one of them, though very strong. The amulet will protect you and give your weapon the power to harm the Chavinavi of the temple.";
			link.l1 = "Are you sure the amulets will help?";
			link.l1.go = "Tuttuat_54";
		break;
		
		case "Tuttuat_54":
			dialog.text = "I know. I speak to the ancestors. I am a great shaman. You trust me. You take two amulets. One protects. The other empowers your weapon. You must use one amulet. Which one - you choose. If you do not wear an amulet, you will perish to the jaguar warriors\nAnd remember, at midnight Yum Cimil brings back to life all the warriors you kill. You must figure out the timing so you do not fight them twice, or do so; the spirits tell me that you could.";
			link.l1 = "I see.";
			link.l1.go = "Tuttuat_55";
		break;
		
		case "Tuttuat_55":
			dialog.text = "You take the amulets. Here they are. Remember, their power has limits. It wanes in one moon. Remember I said, you cannot hold their power? Only the great shaman of our tribe can wield it.";
			link.l1 = "I remember. So, do I only have one moon? One month?";
			link.l1.go = "Tuttuat_56";
		break;
		
		case "Tuttuat_56":
			dialog.text = "Yes. When you come to the temple of Yum Cimil, you must find the shrine and a great statue of the Condor in it. This is the most important part of the temple. Here you place the jade skull of Yum Cimil, and the curse will be lifted from the Caleuche. When he attacks you again, you will defeat him like an ordinary man. Then you bring me the amulet he took from you.";
			link.l1 = "Condor? What is it?";
			link.l1.go = "Tuttuat_57";
		break;
		
		case "Tuttuat_57":
			dialog.text = "Condor is a great bird which lives in the mountains of my homeland. In memory of home, my ancestors built a statue of the Condor near the shrine.";
			link.l1 = "Fine, I'll search for it...";
			link.l1.go = "Tuttuat_58";
		break;
		
		case "Tuttuat_58":
			dialog.text = "You be careful. Many dangers lurk in the temple besides jaguar warriors.";
			link.l1 = "What dangers?";
			link.l1.go = "Tuttuat_59";
		break;
		
		case "Tuttuat_59":
			dialog.text = "I don't know for sure. See for yourself. It could be a trap, or just confusion. Entering the shrine is hard. The entrance is sealed, and you must find a way to open it. My ancestors were not only great warriors and shamans, but great builders too. To open it, you need to think.";
			link.l1 = "Heh! Sounds frightening, but let them all come! I will not waste time. I am setting sail at once!";
			link.l1.go = "Tuttuat_60";
		break;
		
		case "Tuttuat_60":
			dialog.text = "Go, white warrior. I shall summon spirits to help you against the jaguar warriors and the Caleuche. Remember, if you use amulets I can help, if not, you will perish";
			link.l1 = "Thank you, great shaman... I will see it done.";
			link.l1.go = "Tuttuat_61";
		break;
		
		case "Tuttuat_61":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
			npchar.greeting = "Tuttuat_3";
			Log_Info("You have received two amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "kaleuche_amulet2");
			GiveItem2Character(pchar, "kaleuche_amulet3");
			// преобразуем амулеты
			ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_sword");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_shield");
			sld = ItemsFromID("kaleuche_amulet2");
			sld.picIndex = 13;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			sld = ItemsFromID("kaleuche_amulet3");
			sld.picIndex = 14;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			SetFunctionTimerCondition("Caleuche_TuttuatAmuletOver", 0, 0, 30, false); // таймер
			// делаем доступным Хаэль Роа
			n = FindIsland("KhaelRoa");
			Islands[n].visible = true;
			Island_SetReloadEnableGlobal(Islands[n].id, true);
			Islands[n].reload.l1.radius = 150.0;
			Islands[n].reload.l2.label = "Shore64_1";
			Islands[n].reload.l2.name = "reload_2";
			Islands[n].reload.l2.go = "";
			Islands[n].reload.l2.emerge = "";
			Islands[n].reload.l2.radius = 0.0;
			Islands[n].reload.l2.pic = 0;
			Islands[n].reload.l2.tex = "t1";
			pchar.questTemp.Caleuche = "khaelroa";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1 = "location";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1.location = "KhaelRoa_port";
			pchar.quest.Caleuche_khaelroa_arrive.function = "Caleuche_KhaelRoaArrive";
			AddQuestRecord("Caleuche", "34");
			if (CheckAttribute(pchar, "questTemp.NatanStory")) 
			{
				pchar.questTemp.Caleuche.NatanInfo = "true";
				AddQuestUserData("Caleuche", "sText", "But I have a clue: it seems that white captain, who had visited the temple of the Chavins, is none other than my good friend Nathaniel Hawk. I remember him saying that he had a map of that island in Maroon Town. Guess I will pay Nathan a visit.");
			}
			else AddQuestUserData("Caleuche", "sText", "That's a huge area in the sea, but I have no choice. I'll have to scour it entirely. Shaman said North of Dominica, and not too far so I could steadily move North, it might very well be a bit to the East or West. He also mentioned some Captain that destroyed the undead ship maybe I will be lucky and I might find him one day, alas, he said that I have only one month to hold this power or whatever it is, oh well it is what it is, let the search begin!");
		break;
		
		case "Tuttuat_62":
			if (pchar.questTemp.Caleuche == "regard" && CheckCharacterItem(pchar, "kaleuche_amulet1") && CheckCharacterItem(pchar, "kaleuche_amulet2") && CheckCharacterItem(pchar, "kaleuche_amulet3")) 
			{
				dialog.text = "I speak with spirits. You were on the island, in the temple of Yum Cimil. Did you find the Caleuche and the amulet?";
				link.l1 = "You're right, great shaman. I have found the island, entered the temple, and left the jade skull inside.";
				link.l1.go = "Tuttuat_63";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Go, white warrior.";
				if (CheckAttribute(pchar, "questTemp.Caleuche.AmuletOver"))
				{
					link.l1 = "Tuttuathapak, you see... I didn't take the skull to the temple in time, and your amulets lost their power.";
					link.l1.go = "Tuttuat_82";
				}
				else
				{
					link.l1 = "...";
					link.l1.go = "Tuttuat_62_1";
				}
			}
		break;
		
		case "Tuttuat_62_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
		break;
		
		case "Tuttuat_63":
			npchar.greeting = "Tuttuat_2";
			pchar.quest.Caleuche_TuttuatAmuletOver.over = "yes"; //снять таймер
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet2")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet3")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			dialog.text = "You lifted the curse from the Caleuche. Did she find you afterwards?";
			link.l1 = "Yes. We met right on the island. I engaged her in combat and emerged victorious. Now I have all three amulets. Here, take them.";
			link.l1.go = "Tuttuat_64";
		break;
		
		case "Tuttuat_64":
			RemoveItems(pchar, "kaleuche_amulet1", 1);
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given three Chavin amulets");
			PlaySound("interface\important_item.wav");
			dialog.text = "You are a fast and strong warrior, palefaced one. Tuttuathapak does not like white men, but I respect a brave and skilful warrior. You did very well. You have rid the seas of the Caleuche. You have brought me three amulets. I will reward you.";
			link.l1 = "You promised something about 'power that I would be able to hold forever'?";
			link.l1.go = "Tuttuat_65";
		break;
		
		case "Tuttuat_65":
			dialog.text = "You speak true. I'll give you that power. None in the Caribbean knows the secret of the plant I know. Listen to me, pale-faced one! In my home, there is a medicinal plant. We call it Manga Rosa. Have you heard of that plant?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa.Tell"))
			{
				link.l1 = "Yes. I held it in my hands. The gypsies show great interest in it. And one of them, the healer Amelia, can even...";
				link.l1.go = "Tuttuat_66";
			}
			else
			{
				link.l1 = "No idea...";
				link.l1.go = "Tuttuat_66_1";
			}
		break;
		
		case "Tuttuat_66":
			dialog.text = "I have heard of the herbalist Amelia. She knows a little, but not much. She does not know the secret of Manga Rosa. Only a great shaman from my homeland, from where Manga Rosa was brought here, can use its full power.";
			link.l1 = "What power?";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_66_1":
			dialog.text = "This herb grows in my homeland, but it can be found in the Caribbean, too. It's a tall, light-green plant, with leaves like a palm with spread fingers, and a pleasant smell. You will recognise it instantly and not confuse it with anything. I know the secrets of this plant. I can extract power from it.";
			link.l1 = "I understand, but what kind of power?";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_67":
			dialog.text = "I can make potions of Manga Rosa. Very strong potions. None but me in the Caribbean can make those. My potions make a man forever stronger, faster, smarter, keener-eyed, handsomer and luckier. I will brew three such potions for you.";
			link.l1 = "Very interesting!";
			link.l1.go = "Tuttuat_68";
		break;
		
		case "Tuttuat_68":
			dialog.text = "You are a great warrior, so first you need a potion to make you sturdier and one to make you quicker. And you will choose the third potion after I make the first two. But you must bring me Manga Rosa to make them – I have none.";
			link.l1 = "Where should I look for Manga Rosa?";
			link.l1.go = "Tuttuat_69";
		break;
		
		case "Tuttuat_69":
			dialog.text = "Manga Rosa is a rare herb in the Caribbean. It grows where people do not walk much. Foolish people pick it, dry it and smoke it. Very foolish people. DO NOT SMOKE IT! It is a waste of its power... Seek out jungles and coves, secret places where foolish people do not tread. Look carefully. For each potion I need five stems of Manga Rosa.";
			link.l1 = "Alright, great shaman. I'll come back to you once I have enough Manga Rosa.";
			link.l1.go = "Tuttuat_70";
		break;
		
		case "Tuttuat_70":
			dialog.text = "Go, white warrior. Bring me Manga Rosa. You will not regret it. My potions are the best. I will tell the spirits to help you in your search.";
			link.l1 = "Thank you! See you, shaman!";
			link.l1.go = "Tuttuat_71";
		break;
		
		case "Tuttuat_71":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			pchar.questTemp.Caleuche = "mangarosa";
			pchar.questTemp.Caleuche.Mangarosa = 0;
			AddQuestRecord("Caleuche", "41");
		break;
		
		case "Tuttuat_72":
			dialog.text = "Did you bring five stems of Manga Rosa for the potion?";
			if (GetCharacterItem(pchar, "cannabis7") >= 5)
			{
				link.l1 = "Yes. Here are five plants you need.";
				link.l1.go = "Tuttuat_73";
			}
			link.l2 = "Not yet, great shaman. My search continues...";
			link.l2.go = "Tuttuat_72_1";
		break;
		
		case "Tuttuat_72_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
		break;
		
		case "Tuttuat_73":
			RemoveItems(pchar, "cannabis7", 5);
			switch (sti(pchar.questTemp.Caleuche.Mangarosa))
			{
				case 0:
					dialog.text = "Very good. Come tomorrow, once the sun goes down. I will brew you potions that will increase your reaction and dexterity.";
					link.l1 = "Alright, shaman. I'll come tomorrow evening.";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 1;
				break;
				
				case 1:
					dialog.text = "Very good. Come tomorrow, once the sun goes down. I will brew you potions that will increase your endurance.";
					link.l1 = "Alright, shaman. I'll come tomorrow evening.";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 2;
				break;
				
				case 2:
					dialog.text = "Very good. Which potion do you choose? Potion of strength, keen vision, intelligence, beauty or luck?";
					link.l1 = "Potion of strength.";
					link.l1.go = "Tuttuat_77_1";
					link.l2 = "Potion of keen vision.";
					link.l2.go = "Tuttuat_77_2";
					link.l3 = "Potion of intelligence.";
					link.l3.go = "Tuttuat_77_3";
					link.l4 = "Potion of beauty.";
					link.l4.go = "Tuttuat_77_4";
					link.l5 = "Potion of luck.";
					link.l5.go = "Tuttuat_77_5";
				break;
			}
		break;
		
		case "Tuttuat_74":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1 = "Timer";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.hour  = 19.0;
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.function = "Caleuche_MangarosaPotion";
		break;
		
		case "Tuttuat_75":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Potion"))
			{
				sTemp = "";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1) sTemp = "  It make your movements faster, and you better fight with fine light weapons.";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2) sTemp = "  It make you more hardy in long journeys, and you better fight with sharp sabers.";
				dialog.text = "Potion's ready, pale-faced warrior. Take it."+sTemp+"";
				link.l1 = "Thank you, great shaman.";
				link.l1.go = "Tuttuat_76";
			}
			else
			{
				dialog.text = "It's not ready yet, white man. Come back later. Do not disturb me.";
				link.l1 = "Fine...";
				link.l1.go = "Tuttuat_75_1";
			}
		break;
		
		case "Tuttuat_75_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
		break;
		
		case "Tuttuat_76":
			if (sti(pchar.questTemp.Caleuche.Mangarosa) > 2)
			{
				dialog.text = "I've brewed all the potions I promised for you. You'll become stronger. Are you happy?";
				link.l1 = "Yes, great shaman. That was indeed a worthy reward.";
				link.l1.go = "Tuttuat_78";
			}
			else
			{
				dialog.text = "You find five more stems of Manga Rosa, bring them to me. I'll make you another potion.";
				link.l1 = "I will bring you more of them. See you!";
				link.l1.go = "Tuttuat_77";
			}
		break;
		
		case "Tuttuat_77":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1)
			{
				ChangeItemDescribe("kaleuche_amulet1", "itmdescr_kaleuche_amulet1_potion");
				sld = ItemsFromID("kaleuche_amulet1");
				sld.name = "itmname_kaleuche_amulet1_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
				GiveItem2Character(pchar, "kaleuche_amulet1");
			}
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2)
			{
				ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_potion");
				sld = ItemsFromID("kaleuche_amulet2");
				sld.name = "itmname_kaleuche_amulet2_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
				GiveItem2Character(pchar, "kaleuche_amulet2");
			}
		break;
		
		case "Tuttuat_77_1":
			dialog.text = "Come tomorrow, as usual. I'll brew you a potion to make you stronger, and you'll fight better with a big axe.";
			link.l1 = "Fine.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 31;
		break;
		
		case "Tuttuat_77_2":
			dialog.text = "Come tomorrow, as usual. I'll brew you a potion to make your eyes keen so you'll see every target, and you'll strike better with fiery weapons that roar.";
			link.l1 = "Fine.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 32;
		break;
		
		case "Tuttuat_77_3":
			dialog.text = "Come tomorrow, as usual. I'll brew you a potion to make you smarter, and you'd better hide from your enemies.";
			link.l1 = "Fine.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 33;
		break;
		
		case "Tuttuat_77_4":
			dialog.text = "Come tomorrow, as usual. I'll brew you a potion to make you handsomer, and you'll be better at persuading people.";
			link.l1 = "Fine.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 34;
		break;
		
		case "Tuttuat_77_5":
			dialog.text = "Come tomorrow, as usual. I will brew you a potion to make you luckier, and you will have good fortune.";
			link.l1 = "Fine.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 35;
		break;
		
		case "Tuttuat_78":
			dialog.text = "I am glad that you like my art, the art of a great shaman.";
			link.l1 = "Say, Tuttuathapak, what did you need these three amulets for? Just curious...";
			link.l1.go = "Tuttuat_79";
		break;
		
		case "Tuttuat_79":
			dialog.text = "You can already feel the power of these two amulets. The spirits will help me empower them, and all three amulets together will grant the great shamanic wisdom and enlightenment of my ancestors, the great Chavins.";
			link.l1 = "I see. Alright, thank you once again for your excellent potions. You truly are a great shaman. It is time for me to go now. Farewell, Tuttuathapak, I hope I shall see you again.";
			link.l1.go = "Tuttuat_80";
		break;
		
		case "Tuttuat_80":
			dialog.text = "Farewell, white warrior. You need seek me no longer. I go into seclusion, to grasp the wisdom of my ancestors. May the spirits aid you on your journeys!";
			link.l1 = "Well then... hah... may the spirits guide your path as well, great shaman. Farewell...";
			link.l1.go = "Tuttuat_81";
		break;
		
		case "Tuttuat_81":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			GiveItem2Character(pchar, "kaleuche_amulet3");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_potion");
			sld = ItemsFromID("kaleuche_amulet3");
			sld.name = "itmname_kaleuche_amulet3_potion";
			sld.groupID = SPECIAL_ITEM_TYPE;
			sld.picIndex = 15;
			sld.picTexture = "ITEMS_35";
			sld.price = 0;
			sld.Weight = 1.0;
			sld.reaction = sti(pchar.questTemp.Caleuche.Mangarosa);
			sld.ItemType = "SUPPORT";
			i = sti(sld.reaction);
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet"+i+"_potion");
			AddQuestRecord("Caleuche", "42");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			DeleteAttribute(pchar, "questTemp.Caleuche.Mangarosa");
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
		break;
		
		case "Tuttuat_82":
			Log_Info("You have given amulets");
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			dialog.text = "You make me sad, pale-face. I performed a ritual with the spirits to give power to these amulets, and you wasted it. I am sad. You go now. Tuttuathapak has nothing more to say to you.";
			link.l1 = "I'm sorry, I was just really unlucky... Oh well. Farewell, shaman.";
			link.l1.go = "Tuttuat_83";
		break;
		
		case "Tuttuat_83":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Caleuche", "43");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			sld = ItemsFromID("SkullAztec");
			sld.price = 10000;
		break;

		// капитан Калеуче
		case "CaleucheCap":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_01.wav");
			dialog.text = "It's all in vain, sailor. You will not best me. And all my men lying on the deck will gather their bones and rise again before dawn. We cannot be killed, for death has abandoned us forever.";
			link.l1 = "Goddammit! Are you dead or alive? More likely still alive – the dead usually lie quietly and don't swing swords. But who are you, and why did you attack my ship?";
			link.l1.go = "CaleucheCap_1";
		break;
		
		case "CaleucheCap_1":
			dialog.text = "I am Balthazar de Cordes of the Flying Heart. Pitiful cowards, who know nothing about me, call me Van der Decken, captain of the Flying Dutchman. But it doesn't matter. What matters is that you have an amulet on you, which I'll take now. I need it! I feel it! The great amulet of the Chavins, one of the three, will finally be mine! Kneel before me, mortal! And I might make your death painless!";
			link.l1 = "Go to hell, corpse!";
			link.l1.go = "CaleucheCap_2";
		break;
		
		case "CaleucheCap_2":
			DialogExit();
			npchar.MultiFighter = 4.0;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(pchar, 10, true, "Caleuche_GhostshipGetOut");
		break;
		
		case "CaleucheCap_3":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_02.wav");
			dialog.text = "I can't believe it! It's been so long since I last saw my own blood or felt any pain... HOW?!";
			link.l1 = "This time you have lost, Balthazar de Cordes. I know your story. The jade skull has been returned to the temple of the Chavins, and the curse of Yum Cimil no longer hangs over you or your crewmen. You will no longer bring your sailors back to life.";
			link.l1.go = "CaleucheCap_4";
		break;
		
		case "CaleucheCap_4":
			dialog.text = "Oh, so you must consider yourself a redeemer, perhaps? No! Balthazar de Cordes will sell dearly whatever little life he has left!";
			link.l1 = "The last journey of the Flying Heart ends here, at Khael Roa. And you will not raise your ship from the seabed, as you did twenty-five years ago.";
			link.l1.go = "CaleucheCap_5";
		break;
		
		case "CaleucheCap_5":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_03.wav");
			dialog.text = "Hawk! Twenty-five years have passed, and I still remember it as if it were only yesterday. The radiance of that orb which blinded us and split my ship in half. That was the first and the last defeat of the Flying Heart and Balthazar de Cordes... So let us cross swords one last time, captain! Death in battle is light and welcome!";
			link.l1 = "...";
			link.l1.go = "CaleucheCap_6";
		break;
		
		case "CaleucheCap_6":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Caleuche_ChangeShip");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Caleuche_Alonso_1":
			dialog.text = "The tub's been cleared of filth, Cap. This time the dead stayed down. But the vessel itself... damned if I know how it's still afloat.";
			link.l1 = "The curse was holding her together, Alonso. But that's done with now.";
			link.l1.go = "Caleuche_Alonso_2";
		break;
		
		case "Caleuche_Alonso_2":
			dialog.text = "What are your orders? Shall we set her ablaze - and be done with it?";
			link.l1 = "I will think on it. Even falling apart, 'Flying Heart' nearly turned our ship into a sieve.";
			link.l1.go = "Caleuche_Alonso_3";
		break;

		case "Caleuche_Alonso_3":
			dialog.text = "Firepower is one thing this wreck has in spades, thrice damn her... What I came to say is this - we have a sailor in the crew, Jacques...";
			link.l1 = "Jacques Trudeau? I remember him. He joined us recently, right?";
			link.l1.go = "Caleuche_Alonso_4";
		break;

		case "Caleuche_Alonso_4":
			dialog.text = "Aye, Cap. The thing is, that rascal has an excellent nose for valuables - an excellent one. As soon as the undead went still, he leapt to one of the bunks, crawled under it - and pulled out a chest. And in the chest - five thousand doubloons!";
			link.l1 = "Five thousand? Hm... Looks like Balthazar de Cordes and his crew really hoped to rid themselves of the curse. They stuffed their pockets with gold, dreaming of an easy life... when it would all be over.";
			link.l1.go = "Caleuche_Alonso_5";
		break;
		
		case "Caleuche_Alonso_5":
			dialog.text = "Our crew would not mind living like that either, Cap... If you share with the lads, they will never forget it. But if you do not - they will remember.";
			link.l1 = "You are right, Alonso. We should indulge the crew a little - they have earned it. Hand out half to them, and Jacques - relieve him of watches for a week. Instead of grog I allow rum to be poured today. But keep your guard up - you know the sea does not forgive mistakes.";
			link.l1.go = "Caleuche_Alonso_6";
			link.l2 = "Hm... Maybe you are right, Alonso. The crew could stand to blow off some steam. Give them a quarter of the take. And make sure those sots do not start the feast before we drop anchor in some port.";
			link.l2.go = "Caleuche_Alonso_7";
			link.l3 = "So that those idlers scatter to taverns and brothels in the very first port? I am not going to spend a month gathering them one by one. Their wages I pay are enough. And bring the doubloons here. So that no one gets the idea to keep them.";
			link.l3.go = "Caleuche_Alonso_8";
		break;
		
		case "Caleuche_Alonso_6":
			dialog.text = "It will be done, Cap. And do not worry, the lads will never let you down.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_AlonsoAfterWinOnShip_2");
		break;
		
		case "Caleuche_Alonso_7":
			dialog.text = "Aye, Cap. I know how to keep those devils in check - you can count on me.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_AlonsoAfterWinOnShip_3");
		break;
		
		case "Caleuche_Alonso_8":
			dialog.text = "As you order, Cap. The crew, of course, hoped for more... but you are the captain here, it is for you to decide.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_AlonsoAfterWinOnShip_4");
		break;
		
		// --> // наш матрос на берегу
		case "on_coast":
			dialog.text = "Finally, you've woken up, captain... How do you feel?";
			link.l1 = "Goddamn it, what happened? My head is splitting apart from pain...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "When we entered the captain's cabin, you were lying on the floor, still not making a single movement. The men picked you up and dragged you to our ship – and just in time, since the dead men lying on the deck began to rise again\nMost Holy Virgin and all the Saints! We quickly cut the lines and tried to sail away, but a salvo from their ship quickly turned our old tub into splinters and we lost control of her. Then they hoisted their sails and were gone in the blink of an eye\nOur ship ran aground, and everyone who managed to survive reached the shore in a boat. Many good men died today... if only we had stayed aboard... But we were sure that the storm would finish the ship for good.";
			link.l1 = "Not your fault, gentlemen. It was the right call. Thank you, I'll remember that.";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "We dragged you into the boat and then brought you ashore. You were almost dead...";
			link.l1 = "I owe you my life. How long was I lying here, unconscious?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "For an entire day. We washed and dressed your wounds, gave you medicine and poured some rum into you. You should get well soon.";
			link.l1 = "I surely won't die this time. Although I don't feel very well...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "That's for sure... Was it the Flying Dutchman, Cap? Why did they attack us? And why didn't they fire at us before boarding, but almost sank our ship with just one volley afterwards?";
			link.l1 = "Their captain needed the amulet, about which I had spoken to Tuttuathapak, an Indian shaman. That's why they didn't sink us immediately, but as soon as their leader took the amulet, they quickly disposed of us... What a nightmare! A ship manned by the dead! Impossible to believe...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Yes, now it was our turn to encounter the Flying Dutchman. When I get the chance, I'll go to church, light a candle for my miraculous deliverance, and pray to our Lord...";
			link.l1 = "Me too... I suppose. But first I'll go back to that village. I need to tell Tuttuathapak everything about it. That accursed ship attacked us because of the amulet! I'm sure that red-skinned devil had some idea why in hell those living dead might have needed it.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Alright. But be careful, Cap, your wounds have barely healed. At least take someone with you, just in case.";
			link.l1 = "I will be careful, I promise. Thank you for not abandoning me!";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "What are you talking about, Cap! We'd go to the ends of the earth for you and fight thousands of undead! It's a damn shame we lost so much, but this story will live on in legend.";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		
		// Фергус Хупер
		case "fergus":
			dialog.text = "Hey! I haven't collected enough snake skins to sell to you yet, so piss off!";
			link.l1 = "Hmm... Are you Fergus Hooper?";
			link.l1.go = "fergus_1";
			DelLandQuestMark(npchar);
		break;
		
		case "fergus_1":
			dialog.text = "No, my name is Tuttuathapak, and I will curse you if you don't get lost at once. So you'd better hurry, or you will...";
			link.l1 = "...lose my mind, burn my own ship, and my sailors will kill me and take all my belongings. Right?";
			link.l1.go = "fergus_2";
		break;
		
		case "fergus_2":
			sld = characterFromId(pchar.questTemp.Caleuche.Amuletmaster);
			dialog.text = "Arrgh... What the hell, who are you!? How did you...";
			link.l1 = "We have a mutual friend, Fergus. He's a lighthouse keeper, and his name is "+GetFullName(sld)+". He told me about you and sent me to find you. By the way, I happen to know Shaman Tuttuathapak personally, so your joke didn't work, sorry. Listen, I'm not looking for trouble. I want to buy something from you, and it's not snake skins.";
			link.l1.go = "fergus_3";
		break;
		
		case "fergus_3":
			dialog.text = "Oh, so you know my old friend! How is he? Has he died of boredom in his lighthouse yet? Please, sit, sailor, have a drink with me!";
			link.l1 = "I am sorry, Fergus, I really don't have much time. Listen, I need that Indian amulet, one of those your late captain took from the Main with Tuttuathapak. I will pay a good price for it, and you will be rid of a dangerous trinket.";
			link.l1.go = "fergus_4";
		break;
		
		case "fergus_4":
			dialog.text = "And what's so dangerous about it? I haven't seen any harm from it so far. It's just a useless stone";
			link.l1 = "That's because you're no longer sailing the seas. I used to have a similar amulet until recently. A ghost ship is hunting these things.";
			link.l1.go = "fergus_5";
		break;
		
		case "fergus_5":
			dialog.text = "Are you kidding, mate? Perhaps knowing Tuttuathapak has taken its toll on you? Be careful, Cap, that red-skinned devil will devour your mind...";
			link.l1 = "Believe me or not, but I am telling the truth. I wouldn't believe it myself if I hadn't seen it with my own eyes. I can swear on the Book, or you can ask those who were with me. I barely survived after that encounter with the Caleuche.";
			link.l1.go = "fergus_6";
		break;
		
		case "fergus_6":
			dialog.text = "The Caleuche?";
			link.l1 = "Well, most call it the Flying Dutchman, but its true name is Flying Heart. Whatever. Just sell me that amulet. It's of no use to you anyway, I know.";
			link.l1.go = "fergus_7";
		break;
		
		case "fergus_7":
			dialog.text = "That's right. This is just a useless trinket, although quite a beautiful one. Listen, I would have sold it to you without further ado, but you see - I don't have it anymore. It was stolen from my hut along with other things, while I was hunting out in the jungle. That happened rather recently, about a month ago. Sorry, but there's nothing I can help you with.";
			link.l1 = "And who stole it?";
			link.l1.go = "fergus_8";
		break;
		
		case "fergus_8":
			dialog.text = "Are you seriously thinking that I'd be sitting here if I knew who cleaned out my home? There's a gang of thieves and brigands operating outside Belize, and they have informers in town. Well, at least that's what the commandant thinks. I am certain it was them.";
			link.l1 = "The commandant knows about the bandits and still does nothing?";
			link.l1.go = "fergus_9";
		break;
		
		case "fergus_9":
			dialog.text = "Whether he is doing something or not, I don't know. The only thing I know for certain is that my belongings are gone, and your precious amulet with them. Try to seek out these bandits – perhaps you'll find it in their pockets. It's unlikely they managed to sell it – merchants have no use for such things.";
			link.l1 = "Alright, I'll go and see the commandant. Good luck, Fergus!";
			link.l1.go = "fergus_10";
		break;
		
		case "fergus_10":
			DialogExit();
			AddQuestRecord("Caleuche", "9");
			pchar.questTemp.Caleuche.Bandos = "start"; 
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
		break;
		
		// бандит в городе
		case "Beliz_townbandos":
			dialog.text = "Hey! What do you want? I wasn't expecting any guests. Get lost!";
			link.l1 = "Why so rude, friend? I just wanted to ask...";
			link.l1.go = "Beliz_townbandos_1";
		break;
		
		case "Beliz_townbandos_1":
			dialog.text = "Haven't you heard? Get the fuck out, or I'll kick you out the door!";
			link.l1 = "Hmm... Well, perhaps you're the person I am looking for after all. You seem way too nervous, mate...";
			link.l1.go = "Beliz_townbandos_2";
		break;
		
		case "Beliz_townbandos_2":
			dialog.text = "Think you're too clever, aren't you? Once again: either you get lost right now, or I’ll call the guards and they'll throw you behind bars!";
			link.l1 = "Throw me behind bars? How very interesting. You know, now I am almost certain that I have found whom I was looking for. Alright, I agree. Let's call the guards, and then we'll walk to the commandant's office together, like a happy family. I've just been there, so I remember the way... Guards! GUARDS!";
			link.l1.go = "Beliz_townbandos_3";
		break;
		
		case "Beliz_townbandos_3":
			dialog.text = "Screw you! I'll run you through!";
			link.l1 = "Oh ho-ho! Well, you may try!";
			link.l1.go = "Beliz_townbandos_4";
		break;
		
		case "Beliz_townbandos_4":
			DialogExit();
			DeleteAttribute(npchar, "CityType");
			DeleteAttribute(npchar, "city"); // чтобы не было НЗГ
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_BelizTownbandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.Caleuche_letter.win_condition.l1 = "item";
			pchar.quest.Caleuche_letter.win_condition.l1.item = "kaleuche_letter";
			pchar.quest.Caleuche_letter.function = "Caleuche_FindLetter";
		break;
		
		// главарь лесных бандосов
		case "Beliz_forestbandos":
			dialog.text = "Hey, traveller! Welcome, welcome... Supper, lodging - everything for your money. So, get ready to turn your pockets inside out!";
			link.l1 = "Not so fast, my good man. I have business with you.";
			link.l1.go = "Beliz_forestbandos_1";
		break;
		
		case "Beliz_forestbandos_1":
			dialog.text = "Business? Ha-ha! Your only business is to hand over all your silver and gold!";
			link.l1 = "Shut up already. I brought you the letter from Belize you've been waiting for. The messenger couldn't get past the guards and entrusted the affair to me.";
			link.l1.go = "Beliz_forestbandos_2";
		break;
		
		case "Beliz_forestbandos_2":
			dialog.text = "Show me!";
			link.l1 = "Here...";
			link.l1.go = "Beliz_forestbandos_3";
		break;
		
		case "Beliz_forestbandos_3":
			Log_Info("You have given a note");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "kaleuche_letter", 1);
			dialog.text = "(reading) Hm... That is certainly strange... How did you get involved?";
			link.l1 = "I told you already, they seized your man, so I took his job. He promised money and a warm welcome from you...";
			link.l1.go = "Beliz_forestbandos_4";
		break;
		
		case "Beliz_forestbandos_4":
			dialog.text = "A warm welcome? Alright, pal. We'll warm you up, feed you, give you money and all that stuff - but you, you too, will have to prove us that you're not a guards' hound. We've got a score to settle now\nA merchant has recently arrived to a nearby cove; apparently, he wants to sneak into the city with his wares past the customs office. But we will still exact the duty from him. We are lawful folk after all! You'll come with us. Do you know which end of the sword goes where?";
			link.l1 = "And will I get a share of this duty?";
			link.l1.go = "Beliz_forestbandos_5";
		break;
		
		case "Beliz_forestbandos_5":
			dialog.text = "Sure you will! If you're brave in battle and if you stay alive. But don't expect a cakewalk, the merchant is not alone, he has an escort, and a very large escort. Well, time to go - our prey is close. Boys! Prepare your weapons, we're heading out!";
			link.l1 = "...";
			link.l1.go = "Beliz_forestbandos_6";
		break;
		
		case "Beliz_forestbandos_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LocatorReloadEnterDisable(pchar.location, "reload2_back", true);
			LocatorReloadEnterDisable(pchar.location, "reload3_back", true);
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("Beliz_forestbandos_"+i);	
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "TMP_FRIEND");
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "Beliz_ExitTown", "goto", "goto"+(rand(1)+1), "", 10.0);
			}
			DoQuestCheckDelay("OpenTheDoors", 12.0);
			pchar.quest.Caleuche_bandosrobb.win_condition.l1 = "location";
			pchar.quest.Caleuche_bandosrobb.win_condition.l1.location = "Beliz_ExitTown";
			pchar.quest.Caleuche_bandosrobb.function = "Caleuche_JungleBandosRobbery";
		break;
		
		case "Beliz_forestbandos_7":
			dialog.text = "I see you're no coward. Well done! You've earned your share. How would you like it? Cash? Merchandise? They carried a lot of alcohol, it's sure to fetch a good price.";
			link.l1 = "Cash.";
			link.l1.go = "Beliz_forestbandos_8_1";
			link.l2 = "Merchandise.";
			link.l2.go = "Beliz_forestbandos_8_2";
		break;
		
		case "Beliz_forestbandos_8_1":
			Log_Info("You have received 100 doubloons");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Here you go! And this purse is for delivering the letter.";
			link.l1 = "Thanks! Now that's just how I like it!";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_8_2":
			Log_Info("You have received 30 bottles of rum");
			Log_Info("You have received 12 bottles of wine");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "potionrum", 30);
			TakeNItems(pchar, "potionwine", 12);
			dialog.text = "Here you go! Just don't drink yourself to death, ha-ha-ha! And this purse is for delivering the letter.";
			link.l1 = "Thanks! Now that's just how I like it!";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_9":
			Log_Info("You have received a purse");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "purse2", 1);
			dialog.text = "You seem like a decent fellow to me. How about another job? It's about that letter you had delivered to me.";
			link.l1 = "Sure.";
			link.l1.go = "Beliz_forestbandos_10";
		break;
		
		case "Beliz_forestbandos_10":
			dialog.text = "Then come to the cave. There are two of them. Go into the jungle to the place where we last met, then take the left path. We gather in three days at the entrance to the cave, from midnight to one. Got it? If you behave yourself, we'll accept you into our gang. But keep in mind – if you blab anything in town, you're finished. I have a long reach.";
			link.l1 = "Stop scaring me already. I got it. I'll be quiet as a fish. Wait for me in three days, I'll be there. I love easy money!";
			link.l1.go = "Beliz_forestbandos_11";
		break;
		
		case "Beliz_forestbandos_11":
			dialog.text = "Alright, pal. Now get lost before the guards come here. We're leaving as well.";
			link.l1 = "See you around, mate...";
			link.l1.go = "Beliz_forestbandos_12";
		break;
		
		case "Beliz_forestbandos_12":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload2_back", false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload3_back", false);
			LocatorReloadEnterDisable("Beliz_CaveEntrance_2", "reload1_back", true); // закрываем пещеру
			SetFunctionTimerCondition("Caleuche_CaveOpen", 0, 0, 1, false); // таймер
			SetFunctionTimerCondition("Caleuche_BelizbandosClear", 0, 0, 4, false); // таймер
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			for (i=1; i<=6; i++)
			{
				if (GetCharacterIndex("Beliz_forestbandos_"+i) != -1)
				{
					sld = characterFromId("Beliz_forestbandos_"+i);	
					LAi_SetActorType(sld);
					LAi_group_MoveCharacter(sld, "TMP_FRIEND");
					LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "OpenTheDoors", 20.0);
				}
			}
			AddQuestRecord("Caleuche", "13");
			// костер
			ref location = &Locations[FindLocation("Beliz_Jungle_01")];
			DeleteAttribute(location, "fire");
			sld = ItemsFromID("fire");
			sld.shown = false;
			// пакуем схрон в пещере
			pchar.GenQuestBox.Beliz_Cave_2 = true;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.kaleuche_amulet2 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.suit4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse1 = 7; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse2 = 3; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potion2 = 10;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potionrum = 55;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.indian_3 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.obereg_4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.berserker_potion = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry2 = 15;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry3 = 33;
			// меняем флаг
			pchar.questTemp.Caleuche.Bandos = "know";
			SaveCurrentQuestDateParam("questTemp.Caleuche.belizbandos");
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
		break;
		
		// спалили бандосы в пещере
		case "Beliz_cavebandos":
			dialog.text = "What! I take it you decided to claim some of our property? You will not get away with it, you filthy worm!";
			link.l1 = "Who did you just call a worm, you scum?!";
			link.l1.go = "Beliz_cavebandos_1";
		break;
		
		case "Beliz_cavebandos_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Beliz_cavebandos_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Beliz_cavebandos_3", "citiz_23", "man", "man", 30, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 30, 70, 70, "blade_10", "pistol1", "bullet", 150);
				ChangeCharacterAddressGroup(sld, pchar.location, "monsters", "monster16");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_CaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// капитан гарпии
		case "reginald":
			dialog.text = "Hello, colleague! What brings you here?";
			link.l1 = TimeGreeting()+", mynheer Jackson. I am glad to have finally found you.";
			link.l1.go = "reginald_1";
			DelLandQuestMark(npchar);
		break;
		
		case "reginald_1":
			dialog.text = "'Mynheer Jackson', ha-ha! Well, to be honest, soon I'll be calling myself that too. I'm working for this damned Company without a break... but they pay well, very well!.. So, what brings you here, mate?";
			link.l1 = "Our mutual acquaintance, the lighthouse keeper, told me you had an ancient Indian amulet. I suppose you've never found any use for it, and I need it quite badly. I'd like to buy it from you.";
			link.l1.go = "reginald_2";
		break;
		
		case "reginald_2":
			dialog.text = "Oh, you mean that fancy trinket I asked that retired bosun about? Yes, friend, you're right, it never actually came in handy, it just looks pretty.";
			link.l1 = "How much do you want for it?";
			link.l1.go = "reginald_3";
		break;
		
		case "reginald_3":
			dialog.text = "You see, there's a slight problem... Let me explain. I don't have it with me at the moment. Since I never found any use for it, I left it in my chest on the shore, among my other belongings.";
			link.l1 = "Oh, that explains why you are still... well, never mind. Let's just head to that chest of yours, and I'll buy the amulet from you. As simple as that. Where do you keep it?";
			link.l1.go = "reginald_4";
		break;
		
		case "reginald_4":
			dialog.text = "It's not exactly that simple. My chest is on Barbados, in the lighthouse tower, and it's safely locked so that no one can take advantage of it in my absence. And I'm truly sorry, but I cannot go with you to Barbados. According to my contract with the Dutch, I must sail between Philipsburg and Port Royal and adhere strictly to the schedule. And Barbados is nowhere near that route.";
			link.l1 = "And what can we do? I really, truly need that amulet!";
			link.l1.go = "reginald_5";
		break;
		
		case "reginald_5":
			dialog.text = "Hmm... Well, there is one option. I give you the key to my chest, and you sail to Barbados on your own. But you will have to compensate me for everything that's in it, and then you can have them. I am sorry for the distrust - but you must understand. I've never seen you before.";
			link.l1 = "How much?";
			link.l1.go = "reginald_6";
		break;
		
		case "reginald_6":
			dialog.text = "Five hundred gold coins. No less.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "You've got it! Here's your gold.";
				link.l1.go = "reginald_10";
			}
			link.l2 = "Hmm... I don't have that many doubloons with me.";
			link.l2.go = "reginald_7";
		break;
		
		case "reginald_7":
			dialog.text = "Then come and see me again once you've raised the money. If you found me once, you'll find me again. I shall be sailing between St. Martin and Jamaica for quite some time now.";
			link.l1 = "Alright, deal.";
			link.l1.go = "reginald_8";
		break;
		
		case "reginald_8":
			DialogExit();
			NextDiag.CurrentNode = "reginald_9";
			npchar.DeckDialogNode = "reginald_9";
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "reginald_9":
			dialog.text = "You again, friend? Do you have 500 coins?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Yes. Here's your gold.";
				link.l1.go = "reginald_10";
			}
			link.l2 = "Not yet, but I am working on it.";
			link.l2.go = "reginald_8";
		break;
		
		case "reginald_10":
			RemoveDublonsFromPCharTotal(500);
			DelLandQuestMark(npchar);
			
			dialog.text = "Great! And here is your key. I have but one request: after you take everything that's in it, please leave the key in the lock. I would hate to commission a new lock and key for it.";
			link.l1 = "Alright.";
			link.l1.go = "reginald_11";
		break;
		
		case "reginald_11":
			dialog.text = "Then good luck to you, friend! Bon voyage!";
			link.l1 = "And the same to you... Bon voyage, mynheer Jackson!";
			link.l1.go = "reginald_12";
		break;
		
		case "reginald_12":
			DialogExit();
			AddDialogExitQuestFunction("Caleuche_SpawnItemsInTheChest");
			AddQuestRecord("Caleuche", "20");
		break;
		
		case "Caleuche_Reginald_21":
			dialog.text = "What the devil do you want from us? This is a vessel of the Dutch West India Company, and stunts like this don't go unpunished. They'll hunt you down to the ends of the earth – you and your rabble.";
			link.l1 = "I couldn't care less about the Dutch or their trading company. I'm after an old Indian amulet, and I know you've got it – or had it.";
			link.l1.go = "Caleuche_Reginald_22";
		break;

		case "Caleuche_Reginald_22":
			dialog.text = "You're insane! Attacking a ship over a trinket?";
			link.l1 = "Shut up and hand it over, and maybe you'll live.";
			link.l1.go = "Caleuche_Reginald_23";
		break;

		case "Caleuche_Reginald_23":
			dialog.text = "Damn you... I don’t carry it with me. It’s on Barbados.";
			link.l1 = "Then your leaky tub goes to the bottom right now, and you get to keep the rats company in my hold. We'll have plenty of time on the way for you to tell me exactly where to find it. And trust me – I’ve got some boys on board who can make even the thickest skull spill its secrets... no pleasantries needed.";
			link.l1.go = "Caleuche_Reginald_24";
		break;

		case "Caleuche_Reginald_24":
			dialog.text = "There’s no need for that. It’s in a chest at the lighthouse. Locked. Here’s the key.";
			link.l1 = "Smart choice, mate. Pity more of your kind don't have the brains to do the same... would save me a lot of blood on my hands.";
			link.l1.go = "Caleuche_Reginald_24_1";
			link.l2 = "You chose wisely. But you see... I can’t let you live. You’d run straight to those Dutch merchants, and I’d rather not attract their attention.";
			link.l2.go = "Caleuche_Reginald_24_2";
		break;
		
		case "Caleuche_Reginald_24_1":
			dialog.text = "That chest holds everything I’ve earned serving the Dutch over the years...";
			link.l1 = "Then let’s call it a deal: the chest is mine, and you keep your precious hide. Fair enough...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_EndFightWithReginald");
		break;
		
		case "Caleuche_Reginald_24_2":
			dialog.text = "Argh...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_KillToReginald");
		break;
		
		// монах в Виллемстаде
		case "monk_caleuche":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("villemstad");
			npchar.lifeday = 1;
			dialog.text = "Hello, Captain "+GetFullName(pchar)+" Glad to welcome you to Willemstad.";
			link.l1 = "Hello, Father. I don't remember you. Do we know each other?";
			link.l1.go = "monk_caleuche_1";
		break;
		
		case "monk_caleuche_1":
			dialog.text = "I made inquiries about you once your ship had moored. And I think I can ask you for assistance.";
			link.l1 = "Very interesting. And why me?";
			link.l1.go = "monk_caleuche_2";
		break;
		
		case "monk_caleuche_2":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "Because you've done a great deal for the Republic of Free Provinces. You're in good standing with the Company and are friends with the governor. I have already appealed to several authorities and was rebuffed, but I do hope that a noble person such as yourself would not turn down a humble request from a servant of our Lord.";
			}
			else
			{
				dialog.text = "Because you are not in the service of our governor. You're not working for the Company and you have no dealings with our military - otherwise you would most likely just brush me aside like an annoying fly, since I have already appealed to several authorities and was rebuffed.";
			}
			link.l1 = "Fine, then. What's the nature of your request?";
			link.l1.go = "monk_caleuche_3";
		break;
		
		case "monk_caleuche_3":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "There is a house at the back of the bank. A lady who lived there was renting a room in it to a very suspicious type, not a local, and not the Dutchman. And so our father superior, Father "+sld.name+", had recognised him\nIt was Joachim Merriman, a Portuguese man, accused by the Inquisition of witchcraft and dealings with unholy powers. He hid himself from the Inquisition in the New World. You know, Spaniards often accuse those out of favour of heresy and witchcraft in order to burn them at the stake, but... In this case they were right. Merriman is a warlock\nSo, he'd been living in Willemstad for some time, and then he disappeared as suddenly as he had appeared. And after some time, a woman, the one who rented the room to him, was never seen leaving that house. Never! And she was never seen anywhere ever since\nAnd at night, citizens can occasionally see red-blue lights flashing in the windows of the second floor and hear strange sounds, almost like some unholy screams. Father "+sld.name+" appealed to the commandant. He sent a patrol of four soldiers; they searched the house, but found nothing: neither the landlady herself, nor anyone else, nor anything suspicious at all\nBut these strange things keep happening. The landlady has never shown up, and this hellish light can still be seen there at night. Besides, two beggars have recently gone missing as well. I heard them talking at the parvis – they knew there were no owners in the house, so they decided to lodge there. No one has seen them since.";
			link.l1 = "I take it, you want me to go into that house and check what really happened?";
			link.l1.go = "monk_caleuche_4";
		break;
		
		case "monk_caleuche_4":
			dialog.text = "Exactly, noble sir. Please help the Holy Church. The commandant says that we're imagining things, since his patrol never found anything. The government thinks the same. Commoners simply don't care, because they don't see it as a clear threat to them.";
			link.l1 = "Hmm... And do I need to go there at night?";
			link.l1.go = "monk_caleuche_5";
		break;
		
		case "monk_caleuche_5":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Yes, mynheer. It's quiet there during the day, that's why the soldiers didn't find anything. I think the commandant is afraid for his men; I would be too. But please, I beg of you. Father "+sld.name+" will thank you and reward you for your service. Once you've been to that den during the night, please tell him what you find there. I assure you, our misgivings are well-founded.";
			link.l1 = "Alright. I'll think about it.";
			link.l1.go = "monk_caleuche_6";
		break;
		
		case "monk_caleuche_6":
			dialog.text = "Thank you, captain. I hope you won't turn down my humble request. Please, do it in the name of our Lord, our faith, and all that is holy. Go with my blessing.";
			link.l1 = "...";
			link.l1.go = "monk_caleuche_7";
		break;
		
		case "monk_caleuche_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "none", "", "", "", -1);
			AddQuestRecord("Caleuche", "24");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul")) sTemp = "visit the house of Joaquim Merriman, where, according to him, strange things happen at night. Remembering that special gleam in Merriman's eyes when he looked at the jade skull, I feel a little creepy. It seems that the old Jew could not resist the sum of half a million pesos. Whatever the case, I don`t feel like going to Merriman former abode at night.";
				else sTemp = "visit the house of my old acquaintance Joachim Merriman, where, allegedly, strange things are happening at nights. I still remember that glitter in Merriman's eyes, when he was looking at the skull, and honestly I feel frightened. I am not really fond of the idea to visit his former abode in the night, who knows what kind of devils lurk there.";
			}
			else sTemp = "visit the house at the back of the bank, where some Joachim Merriman had been renting a room. Apparently it is that warlock, of which Tuttuathapak was talking about. According to the monk, strange things are happening in this house in the night. I really feel uncomfortable about visiting the warlock's former home, who knows what kind of devils lurk there.";
			AddQuestUserData("Caleuche", "sText", sTemp);
			i = Findlocation("Villemstad_town");
			DeleteAttribute(&locations[i], "reload.l14.close_for_night");
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1.location = "Villemstad_houseSp1_room";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2 = "Hour";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.start.hour = 1.00;
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.finish.hour = 3.00;
			pchar.quest.Caleuche_villemstadhouse.function = "Caleuche_CreateJoakimSkel";
		break;
		
		// охотник у пещеры
		case "cavehunter":
			dialog.text = "Hold on, mate. You'd better not go there if you value your life.";
			link.l1 = "And what's the deal?";
			link.l1.go = "cavehunter_1";
		break;
		
		case "cavehunter_1":
			dialog.text = "Trust me, you don't want to know. But Death itself is around the corner, and I can swear on the Book that you won't come back alive, there are things beyond your imagination.";
			link.l1 = "Well, if you say so, I will not tempt fate. Thanks for the warning.";
			link.l1.go = "cavehunter_2";
		break;
		
		case "cavehunter_2":
			dialog.text = "You're welcome. Stay clear of that path.";
			link.l1 = "...";
			link.l1.go = "cavehunter_3";
		break;
		
		case "cavehunter_3":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_4":
			dialog.text = "Stay clear of that path, mate.";
			link.l1 = "Yeah, I remember...";
			link.l1.go = "cavehunter_4_1";
		break;
		
		case "cavehunter_4_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_5":
			sld = characterFromId("Havana_Priest");
			dialog.text = "Are you sure you want to go there?";
			link.l1 = "Absolutely. "+sld.name+", father superior of the church in Havana, sent me here. I must determine what is happening here, and take appropriate measures.";
			link.l1.go = "cavehunter_6";
			DelLandQuestMark(npchar);
		break;
		
		case "cavehunter_6":
			dialog.text = "What's happening here? I'm afraid you'll be trembling with fear once you see what's happening here with your own eyes.";
			link.l1 = "You mean the walking dead?";
			link.l1.go = "cavehunter_7";
		break;
		
		case "cavehunter_7":
			dialog.text = "Yes. And you had better believe my words.";
			link.l1 = "And I do believe you. I have already encountered that unholy thing in Willemstad and destroyed it. And I will now go in there and destroy all the filth that lurks in this cave.";
			link.l1.go = "cavehunter_8";
		break;
		
		case "cavehunter_8":
			int icpy = GetOfficersQuantity(pchar);
			switch (icpy)
			{
				case 0:
					dialog.text = "Are you going to go there alone? You're a dead man, mate. You have no idea just how many of those things are there. Well, go if you must, and I'll go to the church to light a candle for the peace of your soul.";
					link.l1 = "Don't be too quick to bury me. I've seen worse.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 1:
					dialog.text = "Just the two of you? I'm afraid you won't get far. You have no idea just how many of those things are out there. It's suicide.";
					link.l1 = "You just don't know us well, friend. Step aside, and we shall cleanse this unholy den.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 2:
					dialog.text = "Just the three of you? You must be seasoned fighters if you dare to do it. But I am still afraid that you will not manage. You have no idea just how many of those things are inside that grotto.";
					link.l1 = "You just don't know us well, friend. Step aside, and we shall cleanse this unholy den.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 3:
					dialog.text = "You lot are no cowards, I see. But you really have no idea how many of those things there are. In such an affair, every man counts. Damn it, I'll come with you and I'll shoot that filth with my musket!";
					link.l1 = "You're a brave soul, friend. I will not turn down your help. Let's go!";
					link.l1.go = "cavehunter_9";
				break;
			}
		break;
		
		case "cavehunter_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
		break;
		
		case "cavehunter_9":
			DialogExit();
			npchar.quest.caleuche = true;
			npchar.dialog.currentnode = "cavehunter_10";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			// закрываем локаторы выхода
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload1_back", true);
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload3_back", true);
		break;
		
		case "cavehunter_10":
			dialog.text = "Let's go! Death to the filthy undead!";
			link.l1 = "...";
			link.l1.go = "cavehunter_10_1";
		break;
		
		case "cavehunter_10_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_10";
		break;
		
		case "cavehunter_11":
			dialog.text = "Now that was quite a massacre! Who would have thought that so many dead were hiding in this place! Well, at least we can rest now... Please tell that father superior of yours about this, the one who sent you here. I do hope that the Inquisition will get to the bottom of this after your report. Dealing with the undead is their business, after all, I am just a simple hunter.";
			link.l1 = "I'll definitely tell him. Thank you for the help, mate. You're a rare kind, not many would dare to fight death itself! Good luck!";
			link.l1.go = "cavehunter_exit";
		break;
		
		// солдат в крипте при провале
		case "cryptguard":
			dialog.text = "Stand where you are! This place is off-limits!";
			link.l1 = "Ehh... And what's in there?";
			link.l1.go = "cryptguard_1";
		break;
		
		case "cryptguard_1":
			dialog.text = "A dangerous warlock was found there. Only the holy fathers and the soldiers accompanying them may enter.";
			link.l1 = "I see. Was the warlock arrested?";
			link.l1.go = "cryptguard_2";
		break;
		
		case "cryptguard_2":
			dialog.text = "I am not authorised to answer such questions, señor. It is time for you to leave.";
			link.l1 = "Alright, I got it. Good luck!";
			link.l1.go = "cryptguard_3";
		break;
		
		case "cryptguard_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Caleuche", "31");
			CloseQuestHeader("Caleuche");
			pchar.questTemp.Caleuche = "end";
		break;
		
		// чавинави-вождь
		case "Chavinavi":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_01.wav");
			dialog.text = "Hold still, human! You are in the very heart of the temple, and you have gone too far to turn back now.";
			link.l1 = "Who are you?!";
			link.l1.go = "Chavinavi_1";
		break;
		
		case "Chavinavi_1":
			dialog.text = "I am the chieftain of the Chavinavi, the keeper and guardian of this sacred place. You're not the first to enter this temple, but only two men and one woman have entered and left alive before you. That is the only reason I condescend to speak with you now. Why have you come here, pale-face?";
			link.l1 = "I have brought an ancient relic here, the jade skull. Fifty years ago, it was taken from an Indian temple deep in the mainland. I was going to find the shrine and return the relic to your god.";
			link.l1.go = "Chavinavi_2";
		break;
		
		case "Chavinavi_2":
			dialog.text = "It is strange to hear such words from one of your kind. I don't believe you. You pale-faced ones are always coming to take something, but never to give anything back.";
			link.l1 = "I do not lie. By returning the skull, I will lift the curse laid upon the captain of the ghost ship terrorising the Caribbean Sea, which will make him mortal again, and I will rid the world of him for good.";
			link.l1.go = "Chavinavi_3";
		break;
		
		case "Chavinavi_3":
			dialog.text = "How do you know that our God will lift that curse, pale-face? Does our God speak to you?";
			link.l1 = "No. I came here on the advice of a great shaman by the name of Tuttuathapak. As he said, the skull is the key to the curse, and this is the only temple in the Caribbean. And you know what - I think that he truly can converse with the spirits of the past. Perhaps even with you, chieftain of the jaguar warriors.";
			link.l1.go = "Chavinavi_4";
		break;
		
		case "Chavinavi_4":
			dialog.text = "Your words surprise me, pale-face, but I still cannot trust you completely. Yet, if you came to this temple to return our relic, surely our shaman must have told you about this place, its creation, its history, and its denizens\nIf so, you will easily answer all my questions. Then I will admit that you have been sincere with me, allow you to pass and, moreover, reward you.";
			link.l1 = "Then ask!";
			link.l1.go = "question1";
		break;
		
		case "question1":
			dialog.text = "I am the chieftain of the Chavinavi, and the jaguar warriors. Thousand years ago I was human; now I am carrying out my sacred duty in these chambers. Which god commands me?";
			link.l1 = "Mictlantecuhtli.";
			link.l1.go = "question1_l";
			link.l2 = "Kukulcan.";
			link.l2.go = "question1_l";
			link.l3 = "Yum Cimil.";
			link.l3.go = "question1_r";
			link.l4 = "Inti.";
			link.l4.go = "question1_l";
			link.l5 = "Kauil.";
			link.l5.go = "question1_l";
		break;
		
		case "question1_r":
			dialog.text = "Before your pale-faced people came, this entire land, from the great snows in the north to the great plains in the south, belonged to us, brothers of one family...";
			link.l1 = "";
			link.l1.go = "question2";
		break;
		
		case "question1_l":
			dialog.text = "Before your pale-faced people came, this entire land, from the great snows in the north to the great plains in the south, belonged to us, brothers of one family...";
			link.l1 = "";
			link.l1.go = "question2";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question2":
			dialog.text = "What Indian tribe built this temple?";
			link.l1 = "Inca.";
			link.l1.go = "question2_l";
			link.l2 = "Chavins.";
			link.l2.go = "question2_r";
			link.l3 = "Maya.";
			link.l3.go = "question2_l";
			link.l4 = "Aztec.";
			link.l4.go = "question2_l";
			link.l5 = "Arawak.";
			link.l5.go = "question2_l";
		break;
		
		case "question2_r":
			dialog.text = "Our people advanced, gaining wisdom, and subdued new forests, plains, and islands. The people who built this temple came from the woodlands across the Great Water...";
			link.l1 = "";
			link.l1.go = "question3";
		break;
		
		case "question2_l":
			dialog.text = "Our people advanced, gaining wisdom, and subdued new forests, plains and islands. The people who built this temple came from the woodlands across the Great Water...";
			link.l1 = "";
			link.l1.go = "question3";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question3":
			dialog.text = "Who led the party of those glorious people?";
			link.l1 = "Great chieftain.";
			link.l1.go = "question3_l";
			link.l2 = "Great priest.";
			link.l2.go = "question3_l";
			link.l3 = "Son of the great chieftain.";
			link.l3.go = "question3_r";
			link.l4 = "Son of the great priest.";
			link.l4.go = "question3_l";
			link.l5 = "The party had no leader.";
			link.l5.go = "question3_l";
		break;
		
		case "question3_r":
			dialog.text = "The Indians, valiant warriors and travellers, always loved and revered their homeland, even after settling in a new place. As a token of their love for their home, they built a statue in the temple in the form of a bird, the symbol of their home. It is behind me...";
			link.l1 = "";
			link.l1.go = "question4";
		break;
		
		case "question3_l":
			dialog.text = "The Indians, valiant warriors and travellers, always loved and revered their homeland, even after settling in a new place. As a token of their love for their home, they built a statue in the temple in the form of a bird, the symbol of their home. It is behind me...";
			link.l1 = "";
			link.l1.go = "question4";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question4":
			dialog.text = "What is the name of this bird?";
			link.l1 = "Albatross.";
			link.l1.go = "question4_l";
			link.l2 = "Eagle.";
			link.l2.go = "question4_l";
			link.l3 = "Vulture.";
			link.l3.go = "question4_l";
			link.l4 = "Roc.";
			link.l4.go = "question4_l";
			link.l5 = "Condor.";
			link.l5.go = "question4_r";
		break;
		
		case "question4_r":
			dialog.text = "Years of prosperity have come and gone, fading like the flame of a lamp, and life has abandoned the island. Only the temple remains here as a reminder of the great power of the ancient Indians. The last shaman left a sacred solar orb on a pedestal, which granted strength to the courageous and punished the wicked. It was taken by the man who was here before you.";
			link.l1 = "";
			link.l1.go = "question5";
		break;
		
		case "question4_l":
			dialog.text = "Years of prosperity have come and gone, fading like the flame of a lamp, and life has abandoned the island. Only the temple remains here as a reminder of the great power of the ancient Indians. The last shaman left a sacred solar orb on a pedestal, which granted strength to the brave and punished the wicked. It was taken by the man who was here before you.";
			link.l1 = "";
			link.l1.go = "question5";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question5":
			dialog.text = "What was the name of that sacred orb?";
			link.l1 = "Orb of the shining sun.";
			link.l1.go = "question5_l";
			link.l2 = "Orb of the sunrays.";
			link.l2.go = "question5_l";
			link.l3 = "Orb of the midday sun.";
			link.l3.go = "question5_l";
			link.l4 = "Orb of the rising sun.";
			link.l4.go = "question5_r";
			link.l5 = "Orb of the setting sun.";
			link.l5.go = "question5_l";
		break;
		
		case "question5_r":
			if (CheckAttribute(pchar, "questTemp.Caleuche.QuestionFail"))
			{
				PlaySound("Voice\English\LE\Chavinavi\Chavinavi_02.wav");
				dialog.text = "Wrong answers indicate that you lied to me, white man! You have come with evil intentions! You managed to sneak past the guardians of the temple and the shrine, you figured out how the mechanism of the door works - but you still won't escape a mortal combat with me. Prepare to die, pale face!";
				link.l1 = "Well, if you insist - let's see how great a warrior you are...";
				link.l1.go = "chavinavi_fight";
			}
			else
			{
				dialog.text = "Your knowledge of my people and my temple does you credit, pale-face. Now I believe you. Go and fulfil that which you came here for. Place the holy relic on the pedestal in front of the condor, where the orb of the rising sun once resided\nThen return to me. Your worship of Yum Cimil and your decision to voluntarily return that which was stolen by your brothers must be rewarded.";
				link.l1 = "Thank you for your trust, great chieftain.";
				link.l1.go = "chavinavi_exit";
			}
		break;
		
		case "question5_l":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_02.wav");
			dialog.text = "Wrong answers indicate that you lied to me, white man! You have come with evil intentions! You managed to sneak past the guardians of the temple and the shrine, you figured out how the mechanism of the door works - but you still won't escape a mortal combat with me. Prepare to die, pale face!";
			link.l1 = "Well, if you insist - let's see how great a warrior you are...";
			link.l1.go = "chavinavi_fight";
		break;
		
		case "chavinavi_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_TopChavinaviDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "chavinavi_exit":
			DialogExit();
			sld = ItemsFromID("SkullAztec");
			sld.shown = "0";
			sld.useLocation = "KhaelRoa_Treasure_Alcove";
			sld.useLocator = "button01";
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "Chavinavi_5":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_03.wav");
			dialog.text = "You have done as you promised, paleface. I am glad that you were not a liar like most of your brothers. I will keep my word as well. Here, take this gift from me – the symbol of the jaguar warriors' might. Yum Cimil himself has imbued this pelt with a measure of his strength.";
			link.l1 = "Shiver me timbers! It is so beautiful!";
			link.l1.go = "Chavinavi_6";
		break;
		
		case "Chavinavi_6":
			GiveItem2Character(pchar, "KhaelRoa_item");
			Log_Info("You have received jaguar's pelt");
			PlaySound("interface\important_item.wav");
			dialog.text = "This is no ordinary pelt. Once you wear it, you will gain the strength of the jaguar warrior. The power of your weapon, which breathes fire and spits lead, will increase tenfold, and you will be able to litter the battlefield with the corpses of your enemies\nBut no mortal can bear the power that Yum Cimil has placed within this pelt. Once you unleash it, it will remain with you only until the next midnight, and then it will fade. Take care of it, pale-face, and do not waste its power on a petty skirmish.";
			link.l1 = "Thank you! I will only use it when I am completely overwhelmed by enemies.";
			link.l1.go = "Chavinavi_7";
		break;
		
		case "Chavinavi_7":
			dialog.text = "Now go. And warn your brothers against encroaching on the serenity of these sacred chambers. The jaguar warriors show no mercy to the pale-faces and will give them no quarter.";
			link.l1 = "Farewell, chieftain.";
			link.l1.go = "Chavinavi_8";
		break;
		
		case "Chavinavi_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_CharacterDisableDialog(sld);
			}
			AddQuestRecord("Caleuche", "38");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeIndianRelation(10.0);
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
