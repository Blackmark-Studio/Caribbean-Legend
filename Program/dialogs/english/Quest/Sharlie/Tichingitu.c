// Тичингиту - индеец-офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "What do you want?";
			link.l1 = "Nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "What do you want, pale-face? Tichingitu has nothing to say to you.";
			link.l1 = "Your name is Tichingitu? Hm. Listen, warrior, I haven't come here to stare at you. I've come here to ask you a question: Why did you intrude into that fat man's house?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "";
			link.l1 = "Not saying anything? Not wise. You'll be hanged for theft and everything else you've done. Tell me why you committed such an act and maybe I'll be able to help you.";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "Tichingitu came to the town of pale faces by many, many roads, across great waters, from vast forests and swamps. Tichingitu was tired and wanted to eat. Tichingitu was dying of hunger. No one wanted to help Tichingitu. They yelled, 'Go away, red-skinned dog.' The pub owner kicked the Indian out like a mangy dog. Tichingitu wanted to eat.";
			link.l1 = "God damn it, but why did you come to this settlement from... your forest?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "Tichingitu was kicked out of the native tribe. Tichingitu got into a fight with the tribe's shaman, the shaman told the chief, the shaman cursed Tichingitu, Tichingitu left the tribe, far, far away from native land. Tichingitu has no home, no weapon, nothing at all.";
			link.l1 = "That's what I call misfortune. Why did you fight with your own people?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "The shaman of the tribe is an evil man. He said an evil spirit had settled in my wife's body. My wife had to die. But my wife was just ill, no spirit had settled in her. Tichingitu tried to treat my wife, but the shaman killed her. Tichingitu stood up to the shaman, then everyone turned against Tichingitu, so Tichingitu left.";
			link.l1 = "You tried to save your wife? Is that why you were kicked out of the village?";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Yes, pale face. Tichingitu has no choice. Either steal or die of hunger...";
			link.l1 = "Well, I say... A noose for a few measly coins stolen by a starving man... Tichingitu, I'll try to help you. I know Fadey, that burly man whose house you snuck into. Maybe I'll be able to do something... I'll go talk to the commandant.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
			AddDialogExitQuestFunction("Tichingitu_DlgExit_1");
		break;
		
		case "Tichingitu_wait":
			dialog.text = "Tichingitu wait. Indian not afraid of death. Shaman cursed Tichingitu, Tichingitu must die.";
			link.l1 = "Not all is lost yet. I'll try to help...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			dialog.text = "Tichingitu waits. Indian not afraid of death. Shaman cursed Tichingitu, Tichingitu must die.";
			link.l1 = "No need to be pessimistic. Your imprisonment has come to an end. I've helped set you free.";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			dialog.text = "Pale-face joke? Tichingitu free?";
			link.l1 = "No, I'm not joking. They're about to open your cell and let you out. Follow me, I'll lead you out of jail.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tichingitu_DlgExit_2");
		break;
		
		case "Tichingitu_9":
			dialog.text = "";
			link.l1 = "There you are, free again. Go on, Tichingitu, make sure not to steal anything else and don't get into any more trouble! You'd better find an Indian village and live with your own kind, I don't think they'd be against accepting you.";
			link.l1.go = "Tichingitu_10";
		break;
		
		case "Tichingitu_10":
			dialog.text = "Tichingitu not go. Master saved Tichingitu's life. Tichingitu stay. Tichingitu's life belongs to master.";
			link.l1 = "Huh? What are you talking about? What master, what life? Don't you understand what I'm saying? You're free! Go!";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "Indian has debt, white master. Tichingitu serves you with faith and truth. Tichingitu knows how to fight. Tichingitu will die in battle for master. He stays.";
			link.l1 = "Oh Lord! Damn it... What kind of master am I to you, Tichingitu? I helped you, not to turn you into a slave.";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "Tichingitu not slave. Tichingitu free Indian. Tichingitu want serve you. Tichingitu know how to fight, any dog dies before coming close to master. Tichingitu know how to clean and load musket. Tichingitu can shoot musket.";
			link.l1 = "Although... You know, Tichingitu, that's not a bad idea. I need loyal people and you don't seem to be a bad man. Also, you know how to shoot a musket. And what are you going to do alone anyway? You'll end up stealing something else and next time you'll definitely be hanged... All right, you can stay. But remember: life isn't going to be calm with me.";
			link.l1.go = "Tichingitu_13";
			link.l2 = "All right, enough. Go in peace, red-skinned brother. May your gods watch over you!";
			link.l2.go = "Tichingitu_exit";
		break;
		
		case "Tichingitu_exit":
			DialogExit();
			AddDialogExitQuestFunction("Tichingitu_DlgExit_3");
		break;
		
		case "Tichingitu_13":
			dialog.text = "Tichingitu is not afraid of anything, white master. Tichingitu is glad to serve you. Tichingitu is faithful to his last breath.";
			link.l1 = "All right. Welcome to the crew, Tichingitu!";
			link.l1.go = "Tichingitu_hire";
		break;
		
		case "Tichingitu_hire":
			DialogExit();
			AddDialogExitQuestFunction("Tichingitu_Hire");
		break;
		
	//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Tichingitu_officer":
			dialog.text = "Tichingitu listens to you, Captain "+pchar.name+"!";
			// Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = ""+npchar.name+" sees confusion in Captain "+pchar.name+"'s eyes.";
				Link.l1 = "You always see right through me, my friend. You see, I must return home — to Europe. I've made a hard decision — to sail on someone else's ship, as a passenger.";
				Link.l1.go = "SharlieEpilog_Tichingitu_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Tichingitu, I'm about to depart for an old Indian village called Tayasal. I won't lie to you, it's an extremely dangerous journey and very unusual: through a teleportation idol. You... Will you join me?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Tichingitu, give me a full report on the ship.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "I want you to purchase certain goods every time we dock.";
				Link.l12.go = "QMASTER_2";
			}

			Link.l1 = "Listen to my orders!";
            Link.l1.go = "stay_follow";
			link.l2 = "Nothing at the moment. At ease!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Ship report? Tichingitu has no report, master. Only weapon and clothes. Tichingitu took no report from anywhere.";
			Link.l1 = "Fine, whatever.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Master, Tichingitu never sets foot in a colony without you. When Tichingitu enters a shop - everyone thinks Tichingitu is a thief again. Then, prison.";
			link.l1 = "Yeah, you are probably right. Not that prison thing again. Besides, nobody will ever believe you are a purser.";
			link.l1.go = "exit";
		break;
		
		case "stay_follow":
            dialog.Text = "What orders do you have?";
            Link.l1 = "Hold up here!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Follow me and don't lag behind!";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "You need to change the type of ammunition for your firearm.";
					Link.l3.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Change the type of ammunition for your musket.";
					Link.l4.go = "SetMusketBullets";
				}
					Link.l5 = "Change your primary weapon for combat.";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "I want you to keep your distance from the target.";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Choose ammunition type:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "Select ammunition type:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "At the beginning of the fight you will use:";
			Link.l1 = "Blade";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Musket";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Change of plan!";
            Link.l1 = "At ease.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Change of plan!";
            Link.l1 = "At ease.";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "How far, Captain? Tell Tichingitu how many yards, but no more than twenty.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Captain, forgive Tichingitu, but I do not understand you.";
				link.l1 = "Sorry, my mistake...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Tichingitu stands idle, does not move. Is that what you want, Captain?";
				link.l1 = "Yes, precisely so.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Tichingitu cannot stay more than twenty yards from the target. Then he misses.";
				link.l1 = "Fine, keep your distance at twenty yards.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Tichingitu understands everything. Tichingitu will take the position you say.";
			link.l1 = "Good.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Tichingitu's life, for a long time, has become the life of my Captain. Indian does not forget what Captain did for Tichingitu. Tichingitu will follow him wherever Captain says, no questions, no hesitation.";
			link.l1 = "Thank you, my friend!";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "When will we depart?";
			link.l1 = "A little later. For now, we will have to prepare for the journey.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "21");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "We pay the white man a hundred doubloons, leave, and finish our job freely.";
			link.l1 = "And what if we get caught again?";
			link.l1.go = "tonzag_jailed_1";
			locCameraFromToPos(-16.78, 1.88, -1.70, true, -5.00, -6.10, -20.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "We pay a thousand doubloons.";
			link.l1 = "Cynical, but very perceptive.";
			link.l1.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Guadeloupe is worse.";
			link.l1 = "How so?";
			link.l1.go = "tonzag_jailed_3";
		break;
		
		case "tonzag_jailed_3":
			dialog.text = "There, they want to hang Tichingitu alone. Here, they want to hang more than one. Not so bad.";
			link.l1 = "Now that's just plain cynical!";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "Point-blank shot. Captain, the old man is strong, we can save him if we act quickly.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
			AddDialogExitQuestFunction("Tonzag_JailFear");
		break;
		
		case "tonzag_dead":
			dialog.text = "The white man shows no mercy. Many of mine, Captain. So many. But yours, even more.";
			link.l1 = "Are they your tribe?";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "Some... some of mine.";
			link.l1 = "Hang in there, friend.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
	// Тичингиту говорит о том, что нужно спасти Делюка
		case "Del_Deluck":
			dialog.text = "Another 40 doubloons?";
			link.l1 = "Huh? Are you asking if I'll pay for Deluc's release from prison again?";
			link.l1.go = "Del_Deluck_1";
		break;
		
		case "Del_Deluck_1":
			dialog.text = "Yes.";
			link.l1 = "I'm not sure myself... What do you think?";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "We should bail him out.";
			link.l1 = "That's honourable. Never leave your own behind, eh?";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "Or leave him. Leave the weak to a jaguar in the jungle.";
			link.l1 = "Who?";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			dialog.text = "The big cat.";
			link.l1 = "Tichingitu, I am having trouble understanding you. Just tell me: what should I do in this situation?";
			link.l1.go = "Del_Deluck_5";
		break;
		
		case "Del_Deluck_5":
			dialog.text = "Use your own head.";
			link.l1 = "Very helpful!";
			link.l1.go = "Del_Deluck_6";
		break;
		
		case "Del_Deluck_6":
			DialogExit();
			AddQuestRecord("FolkeDeluc", "2");
			ReturnOfficer_Tichingitu();
		break;
		
		// Эпилог
		case "SharlieEpilog_Tichingitu_1":
			dialog.text = "Captain "+pchar.name+" not take "+npchar.name+" with him?";
			link.l1 = "You're my friend, "+npchar.name+", and of course I invite you to come with me on this journey. But you must understand — people in the Old World aren’t used to seeing natives. They’ll point at you and assume you’re my slave, and treat you as such.";
			link.l1.go = "SharlieEpilog_Tichingitu_2";
		break;

		case "SharlieEpilog_Tichingitu_2":
			dialog.text = ""+npchar.name+" does not care. "+npchar.name+" knows pale-faces despise natives, and will follow Captain "+pchar.name+" as promised — until his last breath.";
			link.l1 = "Not everyone despises natives. But most are wary — it’s how they defend their faith against the unfamiliar. Either way, I won’t let anyone humiliate you or treat you like a slave. I’m sure no one from your tribe has ever seen Europe — not even that damned shaman in his wildest dreams could imagine it.";
			link.l1.go = "SharlieEpilog_Tichingitu_3";
		break;

		case "SharlieEpilog_Tichingitu_3":
			dialog.text = "Maskoke Indian is not sailor. They never reach Europe. I hear: big canoe takes two full moons to get there.";
			link.l1 = "Yes, "+npchar.name+", and that’s if the wind is favorable. It’s not an easy journey. We set sail in two weeks... and I’m glad you’re coming with us. I plan to hold a small celebration at the tavern before we leave. I know you don’t like fire-water, but I’ll be happy if you join us.";
			link.l1.go = "SharlieEpilog_Tichingitu_4";
		break;
		
		case "SharlieEpilog_Tichingitu_4":
			dialog.text = ""+npchar.name+" will come. But maybe better — celebration boarding?";
			link.l1 = "Ha-ha. Not this time, my friend — not the occasion. I’ll let you know when we begin. Now I must go — duty calls.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_officer";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			pchar.questTemp.SharlieEpilog_Tichingitu = true;
			pchar.questTemp.SharlieEpilog_Friends = sti(pchar.questTemp.SharlieEpilog_Friends) + 1;
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
