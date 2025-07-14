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
			dialog.text = "What you want, pale-face? Tichingitu have nothing to say you.";
			link.l1 = "Your name is Tichingitu? Hm. Listen, warrior, I haven't come here to stare at you. I've come here to ask you a question: Why did you intrude into that fat man's house?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "";
			link.l1 = "Not saying anything? Not smart. You'll be hanged for theft and everything else you've done. Tell me why you committed such an act and maybe I'll be able to help you.";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "Tichingitu come to town of pale faces through many many roads, through big water, from great forests and swamps. Tichingitu tired and wanted eat. Tichingitu die from hunger. No one want help Tichingitu. They yell, 'Go away, red-skinned dog'. Pub owner kick out Indian like mangy dog. Tichingitu want eat.";
			link.l1 = "God-damn it, but why did you come to this settlement from... your forest?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "Tichingitu kicked from native tribe. Tichingitu get into fight with tribe shaman, shaman tell chief, Shaman curse Tichingitu, Tichingitu leave tribe, far far away from native land. Tichingitu no home, no weapon, no nothing.";
			link.l1 = "That's what I call a misfortune. Why did you fight with your own people?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Shaman of tribe evil man. He say evil spirit settle into wife's body. Wife must die. My wife just sick, no spirit settle. Tichingitu treat wife, shaman kill wife. Tichingitu stand out against shaman, everyone stand out against Tichingitu, Tichingitu leave.";
			link.l1 = "You tried to save your wife? That's why you were kicked out of the village?";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Yes, pale face. Tichingitu no choice. Either steal or die of hunger...";
			link.l1 = "Well, I say... A noose for a few measly coins stolen by a starving man... Tichingitu, I'll try to help you. I know Fadey, that husky man whose house you snuck into. Maybe I'll be able to do something... I'll go talk to the commandant.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
			pchar.questTemp.Sharlie.Tichingitu = "commandante";
			AddLandQuestMark(characterFromId("BasterJailOff"), "questmarkmain");
			AddQuestRecord("Tichingitu", "2");
		break;
		
		case "Tichingitu_wait":
			dialog.text = "Tichingitu wait. Indian not afraid of death. Shaman curse Tichingitu, Tichingitu must die.";
			link.l1 = "Not all is lost yet. I'll try to help...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			dialog.text = "Tichingitu wait. Indian not afraid of death. Shaman curse Tichingitu, Tichingitu must die.";
			link.l1 = "No need to be pessimistic. Your imprisonment has come to an end. I've helped to set you free.";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			dialog.text = "Pale-face joke? Tichingitu free?";
			link.l1 = "No, I'm not joking. They are about to open your cell and let you out. Follow me, I'll lead you out of jail.";
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			DialogExit();
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			DoQuestReloadToLocation("BasTer_exittown", "rld", "aloc9", "TichingituFree"); // 170712
			pchar.quest.FreeTichingituOver.over = "yes"; //снять таймер
			if (GetHour() > 17.0)
			{
				WaitDate("", 0, 0, 0, 13, 0);
				RecalculateJumpTable();
				RefreshWeather();
				RefreshLandTime();
			}
			if (GetHour() < 8.0)
			{
				WaitDate("", 0, 0, 0, 7, 0);
				RecalculateJumpTable();
				RefreshWeather();
				RefreshLandTime();
			}
		break;
		
		case "Tichingitu_9":
			dialog.text = "";
			link.l1 = "There you are, free again. Go on, Tichingitu, make sure not to steal anything else and don't get into any more trouble! You'd better find some Indian village and live with your own kind, I don't think they'd be against accepting you.";
			link.l1.go = "Tichingitu_10";
		break;
		
		case "Tichingitu_10":
			dialog.text = "Tichingitu not go. Master save Tichingitu's life. Tichingitu stay. Tichingitu's life belong to master.";
			link.l1 = "Huh? What are you talking about? What master, what life? Don't you understand what I'm saying? You're free! Go!";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "Indian have debt, white master. Tichingitu serve you faith and truth. Tichingitu know how to fight. Tichingitu die in battle for master. He stay.";
			link.l1 = "Oh Lord! Damn it... What kind of a master am I to you, Tichingitu? I helped you not to turn you into a slave.";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "Tichingitu not slave. Tichingitu free Indian. Tichingitu want serve you. Tichingitu know how to fight, any dog die before come close to master. Tichingitu know how to clean and load musket. Tichingitu can shoot musket.";
			link.l1 = "Although... You know, Tichingitu, that's not a bad idea. I need loyal people and you don't seem to be a bad man. Also you know how to shoot a musket. And what are you going to do alone anyway? You'll end up stealing something else and next time you'll definitely be hanged... All right, you can stay. But remember: life isn't going to be calm with me.";
			link.l1.go = "Tichingitu_13";
			link.l2 = "All right, enough. Go in peace, red-skinned brother. May your gods watch over you!";
			link.l2.go = "Tichingitu_exit";
		break;
		
		case "Tichingitu_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			AddQuestRecord("Tichingitu", "5");
			CloseQuestHeader("Tichingitu");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Sharlie.Tichingitu");
			pchar.systeminfo.tutorial.Fighter = true;
		break;
		
		case "Tichingitu_13":
			dialog.text = "Tichingitu not afraid of anything, white master. Tichingitu be glad to serve you. Tichingitu faithful to last breath.";
			link.l1 = "All right. Welcome to the crew, Tichingitu!";
			link.l1.go = "Tichingitu_hire";
		break;
		
		case "Tichingitu_hire":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			LAi_SetImmortal(npchar, false);
			npchar.quest.OfficerPrice = sti(pchar.rank)*20;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.CanTakeMushket = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Tichingitu_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			DeleteAttribute(pchar, "questTemp.Sharlie.Tichingitu");
			pchar.OfficerAttRange = 35.0;
			
			AddQuestRecord("Tichingitu", "4");
			CloseQuestHeader("Tichingitu");
			// Sinistra - Начало квеста "Знакомство с индейцами"
			string sModel = "Miskito_"+(rand(5)+1);
			sld = GetCharacter(NPC_GenerateCharacter("ListKakao", sModel, "man", "man", 1, PIRATE, -1, false, "quest"));
			sld.name = "Cocoa";
			sld.lastname = "Leaf";
			GiveItem2Character(sld, "blade_01");
			EquipCharacterByItem(sld, "blade_01");
			AddItems(sld, "jewelry53", rand(20)+180);
			AddItems(sld, "cannabis1", 3);
			GiveItem2Character(sld, "indian_10");
			GiveItem2Character(sld, "talisman11");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "ZsI_ListKakao";
			ChangeCharacterAddressGroup(sld, "BasTer_ExitTown", "item", "item3");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			//LaunchTutorial("Fighter", 1);
		break;
		
	//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Tichingitu_officer":
			dialog.text = "Tichingitu listen to you, Captain "+pchar.name+"!";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Tichingitu, I'm about to depart to an old Indian village called Tayasal. I won't lie to you, it's an extremely dangerous journey and very unusual: through a teleportation idol. You... Will you join me?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Tichingitu, give me a full ship report.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "I want you to purchase certain goods every time we are docked.";
				Link.l12.go = "QMASTER_2";
			}

			Link.l1 = "Listen to my order!";
            Link.l1.go = "stay_follow";
			link.l2 = "Nothing at the moment. At ease!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Ship report? Tichingitu has no report, master. Only weapon and clothes. Tichingitu took no report from nowhere.";
			Link.l1 = "Fine, whatever.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Master, Tichingitu never set foot in a colony without you. When Tichingitu enters a shop - all think Tichingitu is thief again. Then, prison.";
			link.l1 = "Yeah, you are probably right. Not that prison thing again. Plus, nobody will ever believe you are a purser.";
			link.l1.go = "exit";
		break;
		
		case "stay_follow":
            dialog.Text = "What orders you have?";
            Link.l1 = "Hold up here!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Follow me and don't lag behind!";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "You need to change the type of ammunition for your firing arm.";
					Link.l3.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Change the type of ammo for your musket.";
					Link.l4.go = "SetMusketBullets";
				}
					Link.l5 = "Change your priority weapon for combat.";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "I want you to keep distance from the target.";
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
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
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
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
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
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
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
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
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
			dialog.text = "How far, Captain? Tell Tichingitu how many yards, but not more than twenty.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Captain, forgive Tichingitu but me not understand you.";
				link.l1 = "Sorry, my mistake...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Tichingitu stand idle, no move. That is what you want, Captain?";
				link.l1 = "Yes, precisely so.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Tichingitu cannot stay more than twenty yards from target. Then he miss.";
				link.l1 = "Fine, keep your distance at twenty yards.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Tichingitu understand everything. Tichingitu take position you say.";
			link.l1 = "Good.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Tichingitu's life long time become life of my Captain. Indian not forget what Captain do for Tichingitu. Tichingitu follow him where Captain say, no question, no hesitation.";
			link.l1 = "Thank you, my friend!";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "When will we depart?";
			link.l1 = "A little later. For now we will have to prepare for the journey.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "21");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "We pay the white man a hundred doubloons, leave, and complete our job freely.";
			link.l1 = "And what if we get caught again?";
			link.l1.go = "tonzag_jailed_1";
			locCameraFromToPos(-16.78, 1.88, -1.70, true, -5.00, -6.10, -20.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "We pay a thousand doubloons.";
			link.l1 = "Cynical but very acute.";
			link.l1.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Guadeloupe be worse.";
			link.l1 = "How so?";
			link.l1.go = "tonzag_jailed_3";
		break;
		
		case "tonzag_jailed_3":
			dialog.text = "There, they want to hang Tichingitu alone. Here, they want to hang more than one. Not so bad.";
			link.l1 = "Now that's just plain cynical!";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "Point-blank shot. Captain, the old man is strong, we can save him if act quickly.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
			AddDialogExitQuestFunction("Tonzag_JailFear");
		break;
		
		case "tonzag_dead":
			dialog.text = "The white man know no mercy. Many of mine, Captain. So many. But yours more.";
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
			dialog.text = "More hundred doubloons?";
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
			link.l1 = "That's honorable. Never leave your own behind, eh?";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "Or leave him. Leave weak to a jaguar in the jungle.";
			link.l1 = "Who?";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			dialog.text = "The big cat.";
			link.l1 = "Tichingitu, I am having troubles understanding you. Just tell me: what should I do in this situation?";
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
			Return_TichingituOfficer();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
