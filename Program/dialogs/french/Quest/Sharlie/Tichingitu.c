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
			dialog.text = "Que veux-tu?";
			link.l1 = "Rien.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "Que veux-tu, visage pâle ? Tichingitu n'a rien à te dire.";
			link.l1 = "Ton nom est Tichingitu ? Hm. Écoute, guerrier, je ne suis pas venu ici pour te fixer du regard. Je suis venu ici pour te poser une question : Pourquoi as-tu pénétré dans la maison de cet homme gras ?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "";
			link.l1 = "Tu ne dis rien ? Pas malin. Tu seras pendu pour vol et tout le reste que tu as fait. Dis-moi pourquoi tu as commis un tel acte et peut-être que je pourrai t'aider.";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "Tichingitu vient à la ville des visages pâles par de nombreux chemins, par la grande eau, depuis les vastes forêts et marécages. Tichingitu est fatigué et veut manger. Tichingitu meurt de faim. Personne ne veut aider Tichingitu. Ils crient, 'Va-t'en, chien à peau rouge'. Le propriétaire de la taverne chasse l'Indien comme un chien galeux. Tichingitu veut manger.";
			link.l1 = "Bon sang, mais pourquoi es-tu venu dans cette colonie depuis... ta forêt ?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "Tichingitu chassé de la tribu indigène. Tichingitu s'est battu avec le chaman de la tribu, le chaman a raconté au chef, le chaman a maudit Tichingitu, Tichingitu a quitté la tribu, très très loin de la terre natale. Tichingitu pas de maison, pas d'arme, rien du tout.";
			link.l1 = "C'est ce que j'appelle un malheur. Pourquoi t'es-tu battu avec les tiens ?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "L'homme-médecin de la tribu est un homme mauvais. Il dit qu'un esprit maléfique s'est installé dans le corps de ma femme. Ma femme doit mourir. Ma femme est juste malade, aucun esprit ne s'est installé. Tichingitu soigne ma femme, le chaman tue ma femme. Tichingitu s'oppose au chaman, tout le monde s'oppose à Tichingitu, Tichingitu part.";
			link.l1 = "Vous avez essayé de sauver votre femme ? C'est pour cela que vous avez été chassé du village ?";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Oui, visage pâle. Tichingitu n'a pas de choix. Soit voler, soit mourir de faim...";
			link.l1 = "Eh bien, je dis... Une corde pour quelques piécettes volées par un homme affamé... Tichingitu, je vais essayer de t'aider. Je connais Fadey, cet homme robuste dans la maison duquel tu t'es introduit. Peut-être que je pourrai faire quelque chose... Je vais aller parler au commandant.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
			pchar.questTemp.Sharlie.Tichingitu = "commandante";
			AddLandQuestMark(characterFromId("BasterJailOff"), "questmarkmain");
			AddQuestRecord("Tichingitu", "2");
		break;
		
		case "Tichingitu_wait":
			dialog.text = "Tichingitu attendre. Indien pas peur de la mort. Chaman maudit Tichingitu, Tichingitu doit mourir.";
			link.l1 = "Tout n'est pas encore perdu. Je vais essayer d'aider...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			dialog.text = "Tichingitu attend. Indien n'a pas peur de la mort. Chaman maudit Tichingitu, Tichingitu doit mourir.";
			link.l1 = "Pas besoin d'être pessimiste. Votre emprisonnement est terminé. J'ai aidé à vous libérer.";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			dialog.text = "Blague de visage pâle ? Tichingitu libre ?";
			link.l1 = "Non, je ne plaisante pas. Ils sont sur le point d'ouvrir ta cellule et de te laisser sortir. Suis-moi, je te conduirai hors de la prison.";
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
			link.l1 = "Te voilà libre à nouveau. Continue, Tichingitu, assure-toi de ne rien voler d'autre et de ne plus avoir d'ennuis ! Tu ferais mieux de trouver un village indien et de vivre avec les tiens, je ne pense pas qu'ils s'opposeraient à t'accepter.";
			link.l1.go = "Tichingitu_10";
		break;
		
		case "Tichingitu_10":
			dialog.text = "Tichingitu ne part pas. Maître a sauvé la vie de Tichingitu. Tichingitu reste. La vie de Tichingitu appartient au maître.";
			link.l1 = "Hein ? De quoi parles-tu ? Quel maître, quelle vie ? Ne comprends-tu pas ce que je dis ? Tu es libre ! Va !";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "L'Indien a une dette, maître blanc. Tichingitu vous sert avec foi et vérité. Tichingitu sait se battre. Tichingitu mourra au combat pour le maître. Il reste.";
			link.l1 = "Oh Seigneur ! Bon sang... Quel genre de maître suis-je pour toi, Tichingitu ? Je t'ai aidé, mais pas pour te transformer en esclave.";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "Tichingitu pas esclave. Tichingitu Indien libre. Tichingitu veut servir vous. Tichingitu sait comment se battre, tout chien meurt avant d'approcher maître. Tichingitu sait comment nettoyer et charger mousquet. Tichingitu peut tirer mousquet.";
			link.l1 = "Bien que... Tu sais, Tichingitu, ce n'est pas une mauvaise idée. J'ai besoin de gens loyaux et tu ne sembles pas être un mauvais homme. De plus, tu sais comment tirer au mousquet. Et que vas-tu faire tout seul de toute façon ? Tu finiras par voler autre chose et la prochaine fois tu seras certainement pendu... D'accord, tu peux rester. Mais souviens-toi : la vie ne sera pas calme avec moi.";
			link.l1.go = "Tichingitu_13";
			link.l2 = "D'accord, ça suffit. Va en paix, frère à la peau rouge. Que tes dieux veillent sur toi !";
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
			dialog.text = "Tichingitu n'a peur de rien, maître blanc. Tichingitu sera heureux de vous servir. Tichingitu fidèle jusqu'au dernier souffle.";
			link.l1 = "D'accord. Bienvenue dans l'équipage, Tichingitu !";
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
			dialog.text = "Tichingitu t'écoute, Capitaine "+pchar.name+"!";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Tichingitu, je suis sur le point de partir pour un ancien village indien appelé Tayasal. Je ne te mentirai pas, c'est un voyage extrêmement dangereux et très inhabituel : à travers une idole de téléportation. Toi... Veux-tu te joindre à moi ?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Tichingitu, donne-moi un rapport complet du navire.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Je veux que tu achètes certains produits chaque fois que nous sommes à quai.";
				Link.l12.go = "QMASTER_2";
			}

			Link.l1 = "Ecoutez mon ordre !";
            Link.l1.go = "stay_follow";
			link.l2 = "Rien pour le moment. Repos!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Rapport de navire ? Tichingitu n'a pas de rapport, maître. Seulement des armes et des vêtements. Tichingitu n'a pris aucun rapport de nulle part.";
			Link.l1 = "D'accord, peu importe.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Maître, Tichingitu ne met jamais les pieds dans une colonie sans vous. Quand Tichingitu entre dans une boutique - tous pensent que Tichingitu est encore un voleur. Puis, prison.";
			link.l1 = "Oui, tu as probablement raison. Pas encore cette affaire de prison. De plus, personne ne croira jamais que tu es un intendant.";
			link.l1.go = "exit";
		break;
		
		case "stay_follow":
            dialog.Text = "Quelles sont vos ordres ?";
            Link.l1 = "Attends ici !";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Suis-moi et ne traîne pas derrière !";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Vous devez changer le type de munitions pour votre arme à feu.";
					Link.l3.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Changez le type de munitions pour votre mousquet.";
					Link.l4.go = "SetMusketBullets";
				}
					Link.l5 = "Changez votre arme prioritaire pour le combat.";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "Je veux que tu gardes tes distances avec la cible.";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Choisissez le type de munitions :";
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
			Dialog.Text = "Sélectionnez le type de munitions :";
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
			Dialog.Text = "Au début du combat, vous utiliserez :";
			Link.l1 = "Lame";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Fusil à mèche";
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
            dialog.Text = "Changement de plan !";
            Link.l1 = "Repos.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Changement de plan !";
            Link.l1 = "Repos.";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "À quelle distance, Capitaine ? Dites à Tichingitu combien de yards, mais pas plus de vingt.";
			link.l1 = "Bonjour, monami.";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Capitaine, pardonnez Tichingitu mais moi pas comprendre vous.";
				link.l1 = "Désolé, ma faute...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Tichingitu reste là à ne rien faire, ne bouge pas. C'est ce que tu veux, Capitaine ?";
				link.l1 = "Oui,   précisément ainsi.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Tichingitu ne peut pas rester à plus de vingt yards de la cible. Ensuite, il rate.";
				link.l1 = "D'accord, garde tes distances à vingt yards.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Tichingitu comprend tout. Tichingitu prend la position que tu dis.";
			link.l1 = "Bien.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "La vie de Tichingitu est depuis longtemps devenue celle de mon Capitaine. L'Indien n'oublie pas ce que le Capitaine a fait pour Tichingitu. Tichingitu le suit où le Capitaine dit, sans question, sans hésitation.";
			link.l1 = "Merci, mon ami !";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Quand partirons-nous ?";
			link.l1 = "Un peu plus tard. Pour l'instant, nous devrons nous préparer pour le voyage.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "21");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Nous payons l'homme blanc cent doublons, nous partons, et nous accomplissons notre tâche librement.";
			link.l1 = "Et que ferons-nous si nous nous faisons prendre à nouveau ?";
			link.l1.go = "tonzag_jailed_1";
			locCameraFromToPos(-16.78, 1.88, -1.70, true, -5.00, -6.10, -20.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Nous payons mille doublons.";
			link.l1 = "Cynique mais très perspicace.";
			link.l1.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "La Guadeloupe est pire.";
			link.l1 = "Comment cela?";
			link.l1.go = "tonzag_jailed_3";
		break;
		
		case "tonzag_jailed_3":
			dialog.text = " Là, ils veulent pendre Tichingitu seul. Ici, ils veulent en pendre plus d'un. Pas si mal.";
			link.l1 = "Alors ça, c'est vraiment cynique !";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "À bout portant. Capitaine, le vieil homme est fort, nous pouvons le sauver si nous agissons vite.";
			link.l1 = "... ";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
			AddDialogExitQuestFunction("Tonzag_JailFear");
		break;
		
		case "tonzag_dead":
			dialog.text = "L'homme blanc ne connaît pas la pitié. Beaucoup des miens, Capitaine. Tant de. Mais les tiens encore plus.";
			link.l1 = "Sont-ils ta tribu ?";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "Quelques... quelques-unes des miennes.";
			link.l1 = "Tiens bon, ami.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
	// Тичингиту говорит о том, что нужно спасти Делюка
		case "Del_Deluck":
			dialog.text = "Encore cent doublons ?";
			link.l1 = "Hein ? Vous demandez si je vais encore payer pour la libération de Deluc de prison ?";
			link.l1.go = "Del_Deluck_1";
		break;
		
		case "Del_Deluck_1":
			dialog.text = "Oui.";
			link.l1 = "Je ne suis pas sûr moi-même... Qu'en penses-tu ?";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "Nous devrions le tirer d'affaire.";
			link.l1 = "C'est honorable. Ne jamais laisser les siens derrière, hein ?";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "Ou laisse-le. Abandonne le faible à un jaguar dans la jungle.";
			link.l1 = "Qui ?";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			dialog.text = "Le grand chat.";
			link.l1 = "Tichingitu, j'ai des difficultés à te comprendre. Dis-moi simplement : que devrais-je faire dans cette situation ?";
			link.l1.go = "Del_Deluck_5";
		break;
		
		case "Del_Deluck_5":
			dialog.text = "Utilise ta propre caboche.";
			link.l1 = "Très utile !";
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
