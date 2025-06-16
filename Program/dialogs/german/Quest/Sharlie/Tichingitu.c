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
			dialog.text = "Was willst du?";
			link.l1 = "Nichts.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "Was willst du, bleichgesicht? Tichingitu hat dir nichts zu sagen.";
			link.l1 = "Dein Name ist Tichingitu? Hm. Hör zu, Krieger, ich bin nicht hierher gekommen, um dich anzustarren. Ich bin hier, um dir eine Frage zu stellen: Warum bist du in das Haus dieses fetten Mannes eingedrungen?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "";
			link.l1 = "Du sagst nichts? Nicht klug. Du wirst für Diebstahl und all das andere, was du getan hast, gehängt werden. Sag mir, warum du so eine Tat begangen hast und vielleicht kann ich dir helfen.";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "Tichingitu kommt zur Stadt der blassen Gesichter durch viele viele Wege, durch großes Wasser, aus großen Wäldern und Sümpfen. Tichingitu ist müde und will essen. Tichingitu stirbt vor Hunger. Niemand will Tichingitu helfen. Sie schreien, 'Geh weg, rothäutiger Hund'. Der Wirt wirft den Indianer wie einen räudigen Hund raus. Tichingitu will essen.";
			link.l1 = "Verdammt noch mal, aber warum bist du von... deinem Wald in diese Siedlung gekommen?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "Tichingitu wurde aus dem Stamm verstoßen. Tichingitu geriet in einen Streit mit dem Stammesschamanen, der Schamane erzählte es dem Häuptling, der Schamane verfluchte Tichingitu, Tichingitu verließ den Stamm, weit, weit weg von der Heimat. Tichingitu hat kein Zuhause, keine Waffe, gar nichts.";
			link.l1 = "Das nenne ich ein Unglück. Warum hast du mit deinen eigenen Leuten gekämpft?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Schamane des Stammes böser Mann. Er sagt, böser Geist habe sich in Körper der Frau niedergelassen. Frau muss sterben. Meine Frau nur krank, kein Geist niedergelassen. Tichingitu behandelt Frau, Schamane tötet Frau. Tichingitu stellt sich gegen Schamanen, alle stellen sich gegen Tichingitu, Tichingitu verlässt.";
			link.l1 = "Du hast versucht, deine Frau zu retten? Deswegen wurdest du aus dem Dorf vertrieben?";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Ja, bleiches Gesicht. Tichingitu keine Wahl. Entweder stehlen oder vor Hunger sterben...";
			link.l1 = "Nun, ich sage... Eine Schlinge für ein paar mickrige Münzen, gestohlen von einem hungernden Mann... Tichingitu, ich werde versuchen, dir zu helfen. Ich kenne Fadey, diesen kräftigen Mann, in dessen Haus du eingedrungen bist. Vielleicht kann ich etwas tun... Ich werde mit dem Kommandanten sprechen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
			pchar.questTemp.Sharlie.Tichingitu = "commandante";
			AddLandQuestMark(characterFromId("BasterJailOff"), "questmarkmain");
			AddQuestRecord("Tichingitu", "2");
		break;
		
		case "Tichingitu_wait":
			dialog.text = "Tichingitu wartet. Indianer hat keine Angst vor dem Tod. Schamane verflucht Tichingitu, Tichingitu muss sterben.";
			link.l1 = "Noch ist nicht alles verloren. Ich werde versuchen zu helfen...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			dialog.text = "Tichingitu warte. Indianer hat keine Angst vor dem Tod. Schamane verflucht Tichingitu, Tichingitu muss sterben.";
			link.l1 = "Es gibt keinen Grund, pessimistisch zu sein. Deine Gefangenschaft ist zu Ende. Ich habe geholfen, dich zu befreien.";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			dialog.text = "Bleichgesicht-Witz? Tichingitu frei?";
			link.l1 = "Nein, ich mache keine Witze. Sie sind dabei, deine Zelle zu öffnen und dich rauszulassen. Folge mir, ich führe dich aus dem Gefängnis heraus.";
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
			link.l1 = "Da bist du also, wieder frei. Geh weiter, Tichingitu, stell sicher, dass du nichts anderes stiehlst und gerate nicht in weitere Schwierigkeiten! Du solltest besser ein indisches Dorf finden und mit deinesgleichen leben, ich glaube nicht, dass sie etwas dagegen hätten, dich aufzunehmen.";
			link.l1.go = "Tichingitu_10";
		break;
		
		case "Tichingitu_10":
			dialog.text = "Tichingitu geht nicht. Meister rettet Tichingitus Leben. Tichingitu bleibt. Tichingitus Leben gehört dem Meister.";
			link.l1 = "Hä? Wovon redest du? Welcher Meister, welches Leben? Verstehst du nicht, was ich sage? Du bist frei! Geh!";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "Indianer haben Schulden, weißer Herr. Tichingitu dient dir treu und wahr. Tichingitu weiß, wie man kämpft. Tichingitu stirbt im Kampf für den Herrn. Er bleibt.";
			link.l1 = "Oh Herr! Verdammt... Was für ein Meister bin ich für dich, Tichingitu? Ich habe dir geholfen, damit du nicht zu einem Sklaven wirst.";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "Tichingitu kein Sklave. Tichingitu freier Indianer. Tichingitu will dir dienen. Tichingitu weiß, wie man kämpft, jeder Hund stirbt, bevor er sich dem Herrn nähert. Tichingitu weiß, wie man ein Musket reinigt und lädt. Tichingitu kann mit Musket schießen.";
			link.l1 = "Obwohl... Weißt du, Tichingitu, das ist keine schlechte Idee. Ich brauche loyale Leute und du scheinst kein schlechter Mensch zu sein. Außerdem weißt du, wie man ein Musket schießt. Und was wirst du alleine sowieso machen? Du wirst am Ende etwas anderes stehlen und nächstes Mal wirst du definitiv gehängt... In Ordnung, du kannst bleiben. Aber denk daran: das Leben wird mit mir nicht ruhig sein.";
			link.l1.go = "Tichingitu_13";
			link.l2 = "In Ordnung, genug. Geh in Frieden, rothäutiger Bruder. Mögen deine Götter über dich wachen!";
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
			dialog.text = "Tichingitu vor nichts Angst haben, weißer Herr. Tichingitu freut sich, Ihnen zu dienen. Tichingitu treu bis zum letzten Atemzug.";
			link.l1 = "In Ordnung. Willkommen in der Crew, Tichingitu!";
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
			dialog.text = "Tichingitu hört Ihnen zu, Kapitän "+pchar.name+"!";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Tichingitu, ich stehe kurz vor der Abreise zu einem alten Indianerdorf namens Tayasal. Ich werde dir nicht lügen, es ist eine äußerst gefährliche Reise und sehr ungewöhnlich: durch eine Teleportationsidol. Du... Wirst du mich begleiten?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Tichingitu, gib mir einen vollständigen Schiffsbericht.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Ich möchte, dass du bestimmte Waren kaufst, jedes Mal wenn wir angelegt haben.";
				Link.l12.go = "QMASTER_2";
			}

			Link.l1 = "Hört auf meinen Befehl!";
            Link.l1.go = "stay_follow";
			link.l2 = "Im Moment nichts. Seid bereit!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Schiffsbericht? Tichingitu hat keinen Bericht, Meister. Nur Waffe und Kleidung. Tichingitu hat nirgendwo einen Bericht entnommen.";
			Link.l1 = "Gut, was auch immer.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Herr, Tichingitu hat nie einen Fuß in eine Kolonie ohne dich gesetzt. Wenn Tichingitu ein Geschäft betritt - alle denken wieder, Tichingitu ist ein Dieb. Dann, Gefängnis.";
			link.l1 = "Ja, du hast wahrscheinlich recht. Nicht schon wieder dieser Gefängniskram. Außerdem wird dir niemand glauben, dass du ein Zahlmeister bist.";
			link.l1.go = "exit";
		break;
		
		case "stay_follow":
            dialog.Text = "Welche Befehle hast du?";
            Link.l1 = "Halt hier an!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Folge mir und bleib nicht zurück!";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Sie müssen die Art der Munition für Ihre Feuerwaffe ändern.";
					Link.l3.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Ändere die Art der Munition für dein Musket.";
					Link.l4.go = "SetMusketBullets";
				}
					Link.l5 = "Ändere deine Prioritätswaffe für den Kampf.";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "Ich möchte, dass Sie Abstand vom Ziel halten.";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Wähle Munitionsart:";
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
			Dialog.Text = "Wählen Sie den Munitionstyp:";
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
			Dialog.Text = "Zu Beginn des Kampfes wirst du verwenden:";
			Link.l1 = "Klinge";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Muskete";
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
            dialog.Text = "Planänderung!";
            Link.l1 = "Ruhig.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Planänderung!";
            Link.l1 = "Ruhig.";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "Wie weit, Kapitän? Sag Tichingitu wie viele Yards, aber nicht mehr als zwanzig.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Kapitän, verzeihen Sie Tichingitu, aber ich verstehe Sie nicht.";
				link.l1 = "Entschuldigung, mein Fehler...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Tichingitu stand still, bewegte sich nicht. Das ist es, was Sie wollen, Kapitän?";
				link.l1 = "Ja, genau so.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Tichingitu kann nicht mehr als zwanzig Meter vom Ziel entfernt bleiben. Dann verfehlt er.";
				link.l1 = "Gut, halte deinen Abstand auf zwanzig Yards.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Tichingitu versteht alles. Tichingitu nimmt Position, die du sagst.";
			link.l1 = "Gut.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Tichingitus Leben wurde lange Zeit das Leben meines Kapitäns. Der Indianer vergisst nicht, was der Kapitän für Tichingitu getan hat. Tichingitu folgt ihm, wohin der Kapitän sagt, ohne Fragen, ohne Zögern.";
			link.l1 = "Danke, mein Freund!";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Wann werden wir abfahren?";
			link.l1 = "Etwas später. Für jetzt müssen wir uns auf die Reise vorbereiten.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "21");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Wir zahlen dem Weißen hundert Dublonen, gehen und erledigen unsere Arbeit frei.";
			link.l1 = "Und was ist, wenn wir wieder erwischt werden?";
			link.l1.go = "tonzag_jailed_1";
			locCameraFromToPos(-16.78, 1.88, -1.70, true, -5.00, -6.10, -20.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Wir zahlen tausend Dublonen.";
			link.l1 = "Zynisch, aber sehr scharfsinnig.";
			link.l1.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Guadeloupe ist schlimmer.";
			link.l1 = "Wie so?";
			link.l1.go = "tonzag_jailed_3";
		break;
		
		case "tonzag_jailed_3":
			dialog.text = "Dort wollen sie Tichingitu alleine hängen. Hier wollen sie mehr als einen aufhängen. Nicht so schlecht.";
			link.l1 = "Das ist einfach nur zynisch!";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "Direkter Schuss. Kapitän, der alte Mann ist stark, wir können ihn retten, wenn wir schnell handeln.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
			AddDialogExitQuestFunction("Tonzag_JailFear");
		break;
		
		case "tonzag_dead":
			dialog.text = "Der weiße Mann kennt keine Gnade. Viele von den meinen, Kapitän. So viele. Aber noch mehr von den Ihren.";
			link.l1 = "Sind sie dein Stamm?";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "Einige... einige meiner.";
			link.l1 = "Halte durch, Freund.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
	// Тичингиту говорит о том, что нужно спасти Делюка
		case "Del_Deluck":
			dialog.text = "Noch hundert Dublonen?";
			link.l1 = "Hä? Fragst du, ob ich für Delucs Freilassung aus dem Gefängnis nochmal zahlen werde?";
			link.l1.go = "Del_Deluck_1";
		break;
		
		case "Del_Deluck_1":
			dialog.text = "Ja.";
			link.l1 = "Ich bin mir selbst nicht sicher... Was denkst du?";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "Wir sollten ihn auslösen.";
			link.l1 = "Das ist ehrenhaft. Lasse niemals deine eigenen zurück, oder?";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "Oder lass ihn. Überlasse den Schwachen einem Jaguar im Dschungel.";
			link.l1 = "Wer?";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			dialog.text = "Der große Kater.";
			link.l1 = "Tichingitu, ich habe Schwierigkeiten, dich zu verstehen. Sag mir einfach: Was sollte ich in dieser Situation tun?";
			link.l1.go = "Del_Deluck_5";
		break;
		
		case "Del_Deluck_5":
			dialog.text = "Benutze deinen eigenen Kopf.";
			link.l1 = "Sehr hilfreich!";
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
