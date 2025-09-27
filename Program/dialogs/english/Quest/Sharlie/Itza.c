// диалоги Уракана, Канека и прочих индейцев ица
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
			dialog.text = "Is there anything you need?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// ица-горожане
		case "itza_ctz":
			dialog.text = LinkRandPhrase("Another pale face... Great priest happy to carve your heart out...","Pale face knows how to come to Tayasal, but no one leaves the city!","I'm surprised, pale face: you still haven't gone to the spirit land... Walk while you can, soon you will see your ancestors.");
			link.l1 = LinkRandPhrase("Well, well. We'll see...","Don't try to scare me, red-skinned warrior. I've seen worse than that.","Go on, go on. Try frightening the children.");
			link.l1.go = "exit";
			NextDiag.TempNode = "itza_ctz";
		break;
		
		case "itza_ctz_1":
			dialog.text = LinkRandPhrase("Bless me for battle with my foe, great Cavil!","Great Cavil and great Kukulcan honour us with their presence. Even in ancient Maya, this did not happen!","We pass the legend of the great battle between Kukulcan and Cavil to our children!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "itza_ctz_1";
		break;
		
		// Уракан - вождь ица
		case "urakan":
			dialog.text = "You are a great warrior, pale face. We bring your blood to the gods. You die with dignity.";
			link.l1 = "Easy there, red-skinned warrior. I'm not going to allow your Kanek to bring me as a sacrifice to Kukulcan or anyone else for that matter. Your warriors were not able to capture me. Each and every one of them has fallen in battle.";
			link.l1.go = "urakan_1";
		break;
		
		case "urakan_1":
			dialog.text = "Yes, you gracious warrior, pale face. But you cannot withstand hundreds of Tayasal Itza warriors. But, you say interesting word. How you know about great Kanek and Kukulcan?";
			link.l1 = "Well, let me guess... Since you're not Kanek, your name must be Urakan and you're the son of the priest Kanek?";
			link.l1.go = "urakan_2";
		break;
		
		case "urakan_2":
			dialog.text = "Your lips speak the truth, pale face. I am Urakan, and I am surprised.";
			link.l1 = "You're going to be even more surprised when you have a look at this... Look.";
			link.l1.go = "urakan_3";
		break;
		
		case "urakan_3":
			dialog.text = "Oh, gods! If pale face has mask, that means the time has come... You are the one Kukulcan spoke of. He ordered us to bring you to him when you arrived in Tayasal. He knows you have come.";
			link.l1 = "Kukulcan?! He's here in Tayasal?";
			link.l1.go = "urakan_4";
		break;
		
		case "urakan_4":
			dialog.text = "Yes, white warrior. Quetzalcoatl comes to Tayasal. Soon he will leave to bring light to the ancestors, the great city of the Maya.";
			link.l1 = "God damn it! So, he's already here...(lowering voice) Urakan, I know everything. I know that you were the one who sent Ksatl Cha with the Guardian of Truth to search for Ksocheatem and the mask of Kukulcan...";
			link.l1.go = "urakan_5";
		break;
		
		case "urakan_5":
			dialog.text = "";
			link.l1 = "I see surprise in your eyes, but also doubt, great chief Urakan. You're not pleased with Kukulcan, am I right?";
			link.l1.go = "urakan_6";
		break;
		
		case "urakan_6":
			dialog.text = "Every Itza warrior is happy that the great Kukulcan has come, white warrior. You must stand before Kukulcan. He has waited for you many nights. He is a great prophet. He knows everything ahead of time. Go to the Flying Snake, you have no other path. We will not allow you to leave Tayasal.";
			link.l1 = "Don't you understand that as soon as Kukulcan passes through the gates of time, all of you, including yourself, will cease to exist? And the best part is, you will be reborn in another form, in another body... Perhaps as a simple warrior, or even as a cripple or beggar...";
			link.l1.go = "urakan_7";
		break;
		
		case "urakan_7":
			dialog.text = "Go, pale-skinned warrior. You will find Kukulcan in the Great Temple of the Itza warriors. Go straight across the bridge until you see the big pyramid. Enter the lower door of the temple and approach the sanctuary.";
			link.l1 = "All right. I will go to Kukulcan, for I see that we are not to escape this encounter. But I've warned you.";
			link.l1.go = "urakan_8";
		break;
		
		case "urakan_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_warrior_SetStay(npchar, true);
			LAi_warrior_DialogEnable(npchar, true);
			NextDiag.CurrentNode = "urakan_9";
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			AddQuestRecord("Tieyasal", "25");
			pchar.quest.Tieyasal_Templegreat.win_condition.l1 = "location";
			pchar.quest.Tieyasal_Templegreat.win_condition.l1.location = "Temple_great";
			pchar.quest.Tieyasal_Templegreat.function = "Tieyasal_InGreatTemple";
			// экспа за бой
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "urakan_9":
			dialog.text = "Go, white warrior. Kukulcan awaits you.";
			link.l1 = "I'm on my way...";
			link.l1.go = "exit";
			NextDiag.TempNode = "urakan_9";
		break;
		
		case "urakan_10":
			PlaySound("Voice\English\Complete.wav");
			dialog.text = "It has come true! When I saw how you fought Kukulcan, I knew you were Cavil himself. You have come to Tayasal to save the Itza people from death because of my father and Kukulcan. My father, the great priest Kanek, has doomed the Itza people in the name of the long-dead Maya ancestors.\nI am the war chief Urakan, who has protected the Itza people for many years. Not a single pale face has left Tayasal alive. My warriors and I have made sure the Itza people remain protected and alive for many, many years to come. I do not want to sacrifice all my people.";
			link.l1 = "I knew that, Urakan. And I asked you to help me on the bridge.";
			link.l1.go = "urakan_11";
		break;
		
		case "urakan_11":
			dialog.text = "Nothing hides from the eyes of the great Cavil. Forgive Urakan for not understanding who you truly are.";
			link.l1 = "Don't worry about it, chief. I've defeated the mortal embodiment of Kukulcan, but we have another important task ahead - to close the gates to the past. This unnatural hole in time must be sealed. Will you help me?";
			link.l1.go = "urakan_12";
		break;
		
		case "urakan_12":
			dialog.text = "What can Urakan help you with, oh Cavil?";
			link.l1 = "You sent Ksatl Cha with the Guardian of Truth to search for Ksocheatem and the mask of Kukulcan. So, you know that it can be used to close the gates of time. Did your father tell you about that?";
			link.l1.go = "urakan_13";
		break;
		
		case "urakan_13":
			dialog.text = "Father does not speak. I study the writings in the Temple of Knowledge and Wisdom. But much is unclear to Urakan. Maybe Cavil can understand?";
			link.l1 = "What exactly did you find out?";
			link.l1.go = "urakan_14";
		break;
		
		case "urakan_14":
			dialog.text = "I have learned it by heart. The writing proclaims: 'When the sun rises against the rain, and fire stands between them in a triangle, strike Tohil's leg against leg and incinerate the mask of Kukulcan on the altar of time. And seal the Itzamna gates of time until the end of days.'";
			link.l1 = "What.";
			link.l1.go = "urakan_15";
		break;
		
		case "urakan_15":
			dialog.text = "Yes.";
			link.l1 = "Jesus... Show me the gates.";
			link.l1.go = "urakan_16";
		break;
		
		case "urakan_16":
			dialog.text = "They are located in the Kukulcan temple. But the door there is locked. Only my father can lock and unlock it. When he opens the door to the Kukulcan temple, he says: 'The sun comes and goes, water falls and subsides, fire ignites and fades, war and peace interchange, but only heaven is forever. Above time, there is only heaven.'";
			link.l1 = "Interesting... Let's remember that and see what we can do...";
			link.l1.go = "urakan_17";
		break;
		
		case "urakan_17":
			dialog.text = "I stay here, down below, near the altar of time. I have seen every pyramid and building in Taysal from the inside. Find the keys. I stay here.";
			link.l1 = "If I have any important questions, I'll definitely come to you.";
			link.l1.go = "urakan_18";
		break;
		
		case "urakan_18":
			DialogExit();
			NextDiag.CurrentNode = "urakan_adv";
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			pchar.quest.Tieyasal_UrakanTemple.win_condition.l1 = "location";
			pchar.quest.Tieyasal_UrakanTemple.win_condition.l1.location = "Tenochtitlan";
			pchar.quest.Tieyasal_UrakanTemple.function = "Tieyasal_UrakanInTemple";
			AddQuestRecord("Tieyasal", "26");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "quest", "urakan", "", -1);
			// экспа за бой
			AddComplexSelfExpToScill(1000, 1000, 1000, 1000);
			AddCharacterExpToSkill(pchar, "Leadership", 3000);
			AddCharacterExpToSkill(pchar, "Fortune", 1500);
		break;
		
		case "urakan_adv":
			dialog.text = "Can Urakan help the great Cavil with advice or action?";
			if (Tieyasal_CheckTablets() && !CheckAttribute(npchar, "quest.tablets"))
			{
				link.l1 = "Take a look at this tablet I found. Judging by where I found it, it must have had something to do with your father, and it's clearly not an ordinary item...";
				link.l1.go = "tablets";
			}
			if (CheckAttribute(npchar, "quest.treasureentrance"))
			{
				link.l1 = "I found another entrance at the top of the Great Temple, but it's sealed. How can I get inside? Maybe what I'm looking for is in there.";
				link.l1.go = "treasure";
			}
			link.l9 = "Nothing right now, Urakan. I'll manage on my own...";
			link.l9.go = "exit";
			NextDiag.TempNode = "urakan_adv";
		break;
		
		case "tablets":
			dialog.text = "God's stone plate. Father has several different pieces and they are very valuable to him. The ancient Tayasal builders used the plate to activate hidden mechanisms, open and close doors, even perform magic rituals.\nThey work if you put them in the right place - that's what my father does. But I am a warrior just like you, I don't know how to use them properly. Perhaps Cavil knows?";
			link.l1 = "We'll definitely get to the bottom of it...";
			link.l1.go = "exit";
			npchar.quest.tablets = "true";
			NextDiag.TempNode = "urakan_adv";
			AddQuestRecord("Tieyasal", "31");
		break;
		
		case "treasure":
			dialog.text = "This is the door to the treasures of Tayasal. There lie the riches of the Itza Indians. Only my father can open and close the door from inside. No one dares enter the treasure chamber without him. Not even I.";
			link.l1 = "How did your father open the entrance?";
			link.l1.go = "treasure_1";
		break;
		
		case "treasure_1":
			dialog.text = "My father says: 'Any riches have two sides. Only he who knows these two sides may enter the treasures of Tayasal.' What this means - I do not know. Maybe, Cavil can guess?";
			link.l1 = "We'll figure this one out too...";
			link.l1.go = "exit";
			NextDiag.TempNode = "urakan_adv";
			DeleteAttribute(npchar, "quest.treasureentrance");
			AddQuestRecord("Tieyasal", "32");
		break;
		
		case "urakan_19":
			PlaySound("Voice\English\Complete.wav");
			dialog.text = "You did it, oh great Cavil! The people of Itza are now safe. I, Urakan, son of Kanek, assure you I will not bring shame upon the honour you have given me, and I will protect Tayasal from any invasion by dishonourable pale faces in your name.";
			link.l1 = "I can well believe it, chief. Well, we can celebrate now: we've put a stop to Kukulcan's treacherous plans. He'll never be able to bring about a time revolution again.";
			link.l1.go = "urakan_20";
		break;
		
		case "urakan_20":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "Glory to the great Cavil! For me and my generation, it is a great honour to have seen two gods in Tayasal. We write this history for our children. They will know about the battle of the gods in Tayasal! Glory to Cavil! Glory!";
			link.l1 = "I need a drink...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_Win_IndianBead");
		break;
		
		// Канек - жрец ица
		case "kanek":
			dialog.text = "You stand before the Winged Serpent, pale face. The spirit of mighty Kukulcan in human flesh. You are fortunate to be his brother through the father of his embodiment, just as I am fortunate to be the father of his mother, the woman who gave birth to him. It is a great honour. Perhaps this is why you have become a strong warrior and are still alive.\nBut your time will run out, pale face. We will begin a new era, the time of the great Maya. We will establish our own power and never let the pale faces come to our world. Soon. I, Kanek the priest, will go and begin the ritual!";
			link.l1 = "Wonderful...";
			link.l1.go = "kanek_1";
		break;
		
		case "kanek_1":
			DialogExit();
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kanek_2":
			dialog.text = "Urakan, you heard what our lord said. Surrender now!";
			link.l1 = "When great ones battle each other, it's better for us simple mortals to stand aside and watch from a distance, father...";
			link.l1.go = "kanek_3";
		break;
		
		case "kanek_3":
			dialog.text = "What?! Come to your senses, son!";
			link.l1 = "This man is Kukulcan's brother and a great warrior. I see the embodiment of Cavil himself in him! No one but him could withstand a god like THAT. No doddling in a duel of gods, father! And if you bring offerings to Kukulcan, my warriors will give their blood to Cavil!";
			link.l1.go = "kanek_4";
		break;
		
		case "kanek_4":
			dialog.text = "Are you in your right mind, Urakan?";
			link.l1 = "For many years, I, named after Hurakan, have successfully protected our lands in Cavil's name from the invasion of outlanders. Hundreds of them have fallen under our clubs, and none have left Tayasal. But never in my life have I seen a warrior so strong and swift as this pale face. If he is able to defeat Kukulcan, then he is the embodiment of the spirit of Cavil himself!";
			link.l1.go = "kanek_5";
		break;
		
		case "kanek_5":
			DialogExit();
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
