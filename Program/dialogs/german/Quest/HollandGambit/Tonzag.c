// Эркюль Тонзаг, он же Плешивый Гастон
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
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MainBegin")
			{
				dialog.text = "Nun, hallo, "+pchar.name+". Schön dich am Leben zu sehen.";
				link.l1 = "Gaston! Bist du das?";
				link.l1.go = "SJ_talk";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetTonzag")
			{
				dialog.text = "Grüße, "+pchar.name+". Ich weiß bereits über Ihre Geschäfte Bescheid - John hat mir alles erzählt. Ich weiß nicht einmal, was ich sagen soll. Ich bewundere Sie!";
				link.l1 = "Ich freue mich, solch ein Lob von Ihnen zu hören, Hercule!";
				link.l1.go = "SJ_talk_11";
				break;
			}
			dialog.text = "Guten Nachmittag. Haben Sie Geschäfte für mich?";
			link.l1 = "Nein. Mein Fehler. Es tut mir leid. Tschüss. .";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "SJ_talk":
			dialog.text = "Du kanntest mich unter diesem Namen. Aber mein echter Name ist Hercule. Hercule Tonzag.";
			link.l1 = "Heiliger Herr! Ich bin auch froh, dich zu sehen... Ich habe dich im Eifer des Gefechts nicht erkannt. Du warst gerade rechtzeitig mit deiner Hilfe da.";
			link.l1.go = "SJ_talk_1";
		break;
		
		case "SJ_talk_1":
			dialog.text = "Unmittelbar nach deiner Abreise erhielt ich die Nachricht, dass Fleetwood seine Bemühungen verstärkt hat, sein Haus zu schützen. Ich habe vorgeschlagen, dass dahinter eine Falle stecken könnte. Ich bin sofort mit meinem Schiff 'Dämmerung' nach Antigua aufgebrochen - und wie du jetzt siehst, aus gutem Grund.";
			link.l1 = "Wahr. Ich habe es gerade noch geschafft, mit den Wachen im Haus fertig zu werden, aber ich war zu erschöpft, um auf der Straße weiter zu kämpfen...";
			link.l1.go = "SJ_talk_2";
		break;
		
		case "SJ_talk_2":
			dialog.text = "Nach diesem Kampf hatte Fleetwood einen holländischen Spion auf die Fahndungsliste gesetzt. Sie dachten, du wärst ein holländischer Spion. Er ist ihnen in unversöhnlicher Feindschaft verbunden. Das Schlimmste war, dass ein Soldat im Haus überlebte und sich an dein Gesicht erinnerte. Aber, wie auch immer, das ist jetzt kein Problem mehr. Ich habe beendet, was du angefangen hast. Dieser Soldat wird niemanden mehr erkennen können, und niemand wird ihn erkennen...";
			link.l1 = "Hast du ihn getötet? Ich verstehe...";
			link.l1.go = "SJ_talk_3";
		break;
		
		case "SJ_talk_3":
			dialog.text = "Ja. Während du bewusstlos in Johns Haus lagst, habe ich Fleetwood verletzt, aber der Mistkerl hat es geschafft zu überleben. Ich habe ihn blind geschlagen - Pfeffer in seine Augen geworfen und dann zugeschlagen, bevor er eine Chance hatte, sein Schwert zu ziehen. Aber der Abschaum trug einen Harnisch unter seiner Uniform - es rettete sein Leben. Schlau. Jetzt liegt er zu Hause im Bett mit erhöhter Sicherheit. Es ist sehr bedauerlich, dass er überlebt hat.";
			link.l1 = "Also, war Ihre Hauptaufgabe auf Antigua die Beseitigung von Fleetwood?";
			link.l1.go = "SJ_talk_4";
		break;
		
		case "SJ_talk_4":
			dialog.text = "Allgemein, ja. Jetzt scheint es jedoch unmöglich - das Haus ist immer verschlossen, es sind rund um die Uhr ein halbes Dutzend ausgewählte Wächter im Dienst, und sie lassen nur seinen Vertrauten ihn sehen - einen alten Kanonier Charlie, Spitzname der Knippel.";
			link.l1 = "Das ist schon etwas...";
			link.l1.go = "SJ_talk_5";
		break;
		
		case "SJ_talk_5":
			dialog.text = "Warte mal... Willst du dich in diese Angelegenheit einmischen?";
			link.l1 = "Warum nicht? Brauchst du keine Hilfe? Du hast mich gerettet, und ich will helfen. Außerdem, ich brauche immer noch Geld.";
			link.l1.go = "SJ_talk_6";
			// belamour legendary edition -->
			link.l2 = "Warum nicht? Ihr seid ernsthafte Leute. Und ernsthafte Leute zahlen großzügig. Ich suche nur einen Job.";
			link.l2.go = "SJ_talk_6a";
		break;
		
		case "SJ_talk_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			dialog.text = "Glauben Sie mir, Freund, das werden Sie nicht schaffen. Sie sind ein feiner Kerl, ein echtes Talent, und das Logbuch, das Sie geholt haben, half mir, einen Anschlag auf Fleetwoods Leben zu planen, Sie haben die Wachen gut zerschnitten - aber Sie werden niemals in der Lage sein, jetzt zu Fleetwood zu kommen. Selbst ich habe nicht die geringste Ahnung, wie man das macht.";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "Ich werde darüber nachdenken. Ich habe noch Zeit. Es ist schade, dass mein Schiff verhaftet wurde und ich keine Besatzung habe.";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "Ich werde darüber nachdenken. Ich habe Zeit und ein Schiff.";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_6":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			dialog.text = "Glaub mir, Freund, das wirst du nicht schaffen. Du bist ein feiner Kerl, ein echtes Talent, und das Logbuch, das du geholt hast, hat mir geholfen, einen Anschlag auf Fleetwoods Leben zu planen - du hast die Wachen gut geschnitten - aber du wirst niemals in der Lage sein, jetzt zu Fleetwood zu gelangen. Selbst ich habe nicht die geringste Ahnung, wie man das macht.";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "Ich werde darüber nachdenken. Ich habe noch Zeit. Schade, dass mein Schiff festgenommen wurde und ich keine Crew habe.";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "Ich werde darüber nachdenken. Ich habe Zeit und ein Schiff.";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_7":
			dialog.text = "Machen Sie sich darüber keine Sorgen. Als Ihr alter Trog festgenommen wurde, habe ich alle Ihre Offiziere und einige der Seemänner an Bord meiner 'Dämmerung' genommen. Sie wissen, dass Sie lebendig sind und sich bereit erklärt haben, in Dienst zu bleiben. Und als Belohnung für das Journal überlasse ich Ihnen mein Schiff 'Dämmerung'.";
			link.l1 = "Danke! Das werde ich mir merken!";
			link.l1.go = "SJ_talk_9";
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 46)
			{
				pchar.Ship.Type = GenerateShipHand(pchar, SHIP_CAREERLUGGER, 12, 580, 30, 800, 20000, 16.5, 65.5, 1.6);
			}
			else
			{
				pchar.Ship.Type = GenerateShipHand(pchar, SHIP_SCHOONER, 16, 1900, 50, 1350, 25000, 13.5, 55.0, 1.10);
			}
			pchar.Ship.name = "Twilight";
			SetBaseShipData(pchar);
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 46) pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
			else pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
			SetCrewQuantityFull(pchar);
			pchar.Ship.Crew.Morale = 80;
			pchar.Ship.Crew.Exp.Sailors = 90;
			pchar.Ship.Crew.Exp.Cannoners = 70;
			pchar.Ship.Crew.Exp.Soldiers = 70;
			SetCharacterGoods(pchar, GOOD_BALLS, 100);
			SetCharacterGoods(pchar, GOOD_GRAPES, 100);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 100);
			SetCharacterGoods(pchar, GOOD_BOMBS, 100);
			SetCharacterGoods(pchar, GOOD_FOOD, 100);
			SetCharacterGoods(pchar, GOOD_POWDER, 300);
			SetCharacterGoods(pchar, GOOD_WEAPON, 60);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 60);
		break;
		
		case "SJ_talk_8":
			AddMoneyToCharacter(pchar, 15000);
			dialog.text = "Ja, ich möchte Ihnen für das Journal zahlen. 15000 Pesos - mehr habe ich im Moment leider nicht. Wir werden es in einem Tag begleichen. ";
			link.l1 = "Keine Notwendigkeit. Das ist genug. Wenn du nicht rechtzeitig angekommen wärst, hätte ich sowieso kein Geld gebraucht.";
			link.l1.go = "SJ_talk_9";
		break;
		
		case "SJ_talk_9":
			dialog.text = "In Ordnung, "+pchar.name+", Ich muss gehen. Ich gehe noch nicht zurück nach Bridgetown. Wenn du mich jemals brauchst - frag John. Viel Glück!";
			link.l1 = "Viel Glück, Hercule!";
			link.l1.go = "SJ_talk_10";
		break;
		
		case "SJ_talk_10":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-13");
			pchar.questTemp.HWIC.Self = "HuntFleetwood";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "SJ_talk_11":
			dialog.text = "Ich möchte Ihnen diese Rüstung für die Beseitigung von Fleetwood präsentieren. Sie wird Sie in zukünftigen Schlachten schützen. Lassen Sie uns jetzt zu John gehen. Er möchte mit Ihnen sprechen und Ihnen... eine interessante Angelegenheit anbieten.";
			link.l1 = "Danke für das Geschenk. Gut, lass uns gehen...";
			link.l1.go = "SJ_talk_12";
		break;
		
		case "SJ_talk_12":
			DialogExit();
			GiveItem2Character(pchar, "cirass7");//дать вещь
			sld = characterFromId("Merdok");
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetOwnerType(sld);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddQuestRecord("Holl_Gambit", "3-35");
		break;
		
		case "Tonzag_hired":
			dialog.text = "Ich möchte auch mit Ihnen sprechen, Kapitän. Ich wollte Ihnen mein Handwerk beibringen, aber jetzt sehe ich, dass ich es bin, der von Ihnen lernen sollte. Stellen Sie mich als Offizier auf Ihrem Schiff ein - Sie werden es nicht bereuen.";
			link.l1 = "Mit Vergnügen, Hercule! Willkommen an Bord!";
			link.l1.go = "Tonzag_hired_1";
			link.l2 = "Hercule, ich kann mir nicht vorstellen, dein Vorgesetzter zu sein. Vielen Dank für dein Angebot, aber ich kann dich einfach nicht als meinen Untergebenen sehen.";
			link.l2.go = "Tonzag_exit";
		break;
		
		case "Tonzag_hired_1"://Тонзага - в офицеры
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			npchar.greeting = "tonzag_hire";
			NextDiag.CurrentNode = "tonzag_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			LAi_SetImmortal(npchar, false);
			SetCharacterPerk(npchar, "ShipEscape");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
		break;
		
		case "Tonzag_exit":
			dialog.text = "Wie du wünschst, "+pchar.name+". Auf Wiedersehen. Vielleicht treffen wir uns wieder. Es war mir ein Vergnügen, mit Ihnen zu arbeiten.";
			link.l1 = "Viel Glück, Freund!";
			link.l1.go = "Tonzag_exit_1";
		break;
		
		case "Tonzag_exit_1":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DialogExit();
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "tonzag_officer":
			dialog.text = "Ich höre Ihnen zu, Kapitän. Was haben Sie zu sagen?";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Hercule, ich gehe zur alten indischen Stadt Tayasal und, was noch ungewöhnlicher ist, mein Weg führt durch eine Teleportationsstatue. Willst du dich mir anschließen?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Hercule, gib mir einen vollständigen Schiffsbericht.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Ich möchte, dass du bestimmte Waren kaufst, jedes Mal wenn wir angedockt sind.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Ich bin auf Ihren Befehl angekommen, Kapitän.";
				Link.l2 = "Ich muss Ihnen mehrere Befehle erteilen.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "tonzag_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Hör auf meinen Befehl!";
            Link.l1.go = "stay_follow";
			link.l2 = "Im Moment nichts. Machen Sie sich locker!";
			link.l2.go = "exit";
			NextDiag.TempNode = "tonzag_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Kapitän, es tut mir leid, aber ich beschäftige mich nicht mit Zahlen und Berechnungen. Fragen Sie van Merden - er hat ein Händchen für solche Dinge, allerdings bezweifle ich, dass er daran interessiert wäre, sein Nest zu verlassen.";
			Link.l1 = "Du hast recht, Hercule. Meh, ich muss mir einen Zahlmeister suchen...";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Kapitän, als ich ein Wirt auf Barbados war, habe ich nur Rum und Vorräte gekauft. Und mit Vorräten meine ich ordentliche Lebensmittel, nicht einige Cracker und Corned Beef. Entschuldigung, aber das ist nicht mein Bereich.";
			link.l1 = "Vielleicht sollten wir mein Schiff in eine Taverne verwandeln... Nur ein Scherz, Hercule. Was auch immer, ich mache es selbst.";
			link.l1.go = "exit";
		break;
		
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Ich höre Ihnen zu.";
			Link.l1 = "Es geht ums Entern.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Es geht um dein Schiff.";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "Bisher nichts.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "Also, was ist dein Wunsch.";
			Link.l1 = "Entern Sie keine feindlichen Schiffe. Kümmern Sie sich um sich selbst und die Crew.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Ich möchte, dass du feindliche Schiffe betrittst.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "Also, was ist dein Wunsch.";
			Link.l1 = "Ich möchte, dass Sie Ihr Schiff nach dem Entern nicht gegen ein anderes austauschen. Es ist zu wertvoll.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Wenn du feindliche Schiffe entertest, kannst du sie für dich selbst beanspruchen, falls sie zufällig anständig sind.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Jawohl.";
			Link.l1 = "Ruhig.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "Es wird erledigt sein.";
			Link.l1 = "Ruhig.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "Jawohl.";
			Link.l1 = "Es wird erledigt sein.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "Es wird erledigt sein.";
			Link.l1 = "Ruhig.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========////////////////////////////////////////
		
		case "stay_follow":
            dialog.Text = "Welche sind Ihre Befehle? ?";
            Link.l1 = "Bleib hier!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Folge mir und bleibe nicht zurück!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Ändere die Art deiner Munition.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Wahl des Munitionstyps:";
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
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Jawohl!";
            Link.l1 = "Ruhig.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Jawohl!";
            Link.l1 = "Ruhig.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Du bist ein glücklicher Hurensohn, Kapitän. Ich bin froh, dass ich mich dir angeschlossen habe, als ich, du und John zusammen gearbeitet haben. Möge ein Hai mich verschlingen, wenn ich dich nicht bei diesem Unternehmen unterstütze!";
			link.l1 = "Danke dir, Hercule! Ich bin froh, dass ich mit dir Recht hatte.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Also, wann brechen wir auf?";
			link.l1 = "Etwas später. Jetzt sollten wir uns auf die Reise vorbereiten.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "23");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "So ziemlich nichts, Käpt'n. Wenn das mit unserem Geschäft zu tun hätte, hätten sie uns schon auf dem Foltertisch.\nDa sie uns nicht sofort zum Verhör genommen haben, scheint die Angelegenheit offenbar nicht dringend zu sein.\nEntweder eine Falle oder Erpressung.\nSie werden uns hier ein paar Tage ohne Erklärungen marinieren. Und dann kommen sie mit einem Angebot, das wir annehmen werden.";
			link.l1 = "Persönliche Erfahrung?";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "Nun, gibt es eine Möglichkeit, sie dazu zu bringen, jetzt sofort mit einem solchen Angebot zu kommen?";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-14.82, 0.92, 2.74, true, -60.00, -5.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Natürlich. Gruoh wurde einmal von den Verwandten eines toten Mannes bezahlt, um ihn vor den Abschiedsküssen des Henkers von Trinidad zu bewahren.\nSie zahlte dem Kommandanten für das Recht, durch die Zellen zu gehen. Übliche Praxis - viele zahlen die Soldaten für die Gelegenheit, die Menschen zu quälen, die sich nicht wehren können, ohne Zeugen.\nDer Mann starb leise und ohne Leiden. Saubere und anständige Arbeit.";
			link.l1 = "Gruoh? Wer ist das?";
			link.l1.go = "tonzag_jailed_1_1";
		break;
		
		case "tonzag_jailed_1_1":
			dialog.text = "Entschuldigung, Kapitän. Falscher Ort und falsche Zeit.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Wir können es versuchen. Warten wir auf die Fütterungszeit, und ich werde ein paar Worte mit dem Wachposten wechseln. Siehst du, sie haben immer noch nicht gelernt, richtig zu suchen. Eh...";
			link.l1 = "Was ist los?";
			link.l1.go = "tonzag_jailed_2_1";
		break;
		
		case "tonzag_jailed_2_1":
			dialog.text = "Seltsames Gefühl, Käpt'n. Ich würde es sogar als Vorahnung bezeichnen. Entschuldigen Sie, wir sprechen später.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "tonzag_killed_hunters":
			dialog.text = "Habe ich etwas verpasst, Kapitän?";
			link.l1 = "Oh, nichts Besonderes, nur ein weiterer Tag auf See. Schau mal, du alter Teufel! Du hast hier ganz schön Chaos angerichtet.";
			link.l1.go = "tonzag_killed_hunters_1";
		break;
		
		case "tonzag_killed_hunters_1":
			dialog.text = "Blut wäscht sich mit kaltem Wasser ab, Kapitän. Wir müssen reden.";
			link.l1 = "Du denkst? Es würde nicht schaden, diesen Tag erstmal zu überleben.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_Victory");
		break;
		
		case "tonzag_after_victory_helena":
			dialog.text = "Es freut mich auch, dich zu sehen, Rumba. Kapitän, ich werde Sie nicht stören, wir werden später sprechen.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog1");
		break;
		
		case "tonzag_after_victory_mary":
			dialog.text = "Hallo, Rotschopf. Kapitän, ich werde nicht stören, wir sprechen später.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog1");
		break;
		
		case "tonzag_after_victory_alonso":
			dialog.text = "Kapitän, ich werde Sie nicht stören, wir werden später sprechen.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_drink":
			dialog.text = "Bereit, mir zuzuhören, Kapitän?";
			link.l1 = "Es ist höchste Zeit, dass wir reden, Hercule. Mir ist gerade klar geworden, dass ich fast nichts über dich weiß.";
			link.l1.go = "tonzag_drink_1";
		break;
		
		case "tonzag_drink_1":
			dialog.text = "Also ist es Zeit, sich kennenzulernen. Lassen wir die frühen Jahre aus, wenn nur, weil es nichts zu besprechen gibt - ein siegreicher Soldat, ein besiegter Soldat, ein Deserteur, ein Marodeur... Du weißt, wie es läuft.";
			link.l1 = "Ich tue es eigentlich nicht, aber bisher klingt das ziemlich gewöhnlich.";
			link.l1.go = "tonzag_drink_2";
		break;
		
		case "tonzag_drink_2":
			dialog.text = "Karrieremöglichkeiten nach einem solchen militärischen Weg waren für mich - einen Banditen, einen gehängten Mann oder einen Wachmann, der der Niederländischen Westindien-Kompanie würdig ist, gering. Wie Sie verstehen, habe ich letzteres gewählt.";
			link.l1 = "Hast du auch von dort desertiert?";
			link.l1.go = "tonzag_drink_3";
		break;
		
		case "tonzag_drink_3":
			dialog.text = "Ganz im Gegenteil, ich habe dort Karriere gemacht. Ich erhielt ein Angebot, dem Kampfflügel der Geheimdienstabteilung der Gesellschaft beizutreten, wo ich meine zukünftige Frau traf.";
			link.l1 = "Also, bisher ist die Geschichte ziemlich friedlich... vor allem, wenn man nicht zu viel über die Methoden der Holländer nachdenkt.";
			link.l1.go = "tonzag_drink_4";
		break;
		
		case "tonzag_drink_4":
			dialog.text = "Sie werden kein großes Geld verdienen, wenn Sie ehrlich sind, und Sie können auf verschiedene Weisen mit der Konkurrenz kämpfen. Ja, wir haben mit besonderen Methoden gearbeitet...";
			link.l1 = "Ich vermute, ich weiß, was du meinst...";
			link.l1.go = "tonzag_drink_5";
		break;
		
		case "tonzag_drink_5":
			dialog.text = "Ja, es könnte alles sein: von Piraterie bis zum Anzünden von Lagerhäusern mit Waren. Am Ende wurde das Schema aufgedeckt, und wir wurden aufgelöst... auf dem Papier natürlich. So wurde die Liga geboren, bekannt und kontrolliert nur von den ausgewählten Führern der höheren Ebenen der Kompanie. Für einen karibischen Gesetzlosen, der etwas wert ist, gab es nur zwei Optionen: Piraterie oder die Liga. Und die Liga zahlte normalerweise besser\nIm Großen und Ganzen arbeitete die Liga immer noch für die Holländer, konnte aber auch Nebenaufträge übernehmen...";
			link.l1 = "Die Dinge fangen an, sich zu klären...";
			link.l1.go = "tonzag_drink_6";
		break;
		
		case "tonzag_drink_6":
			dialog.text = "Die Liga steckte hinter dieser Farce auf Tortuga. Und dann diese Landungspartei...";
			link.l1 = "Ich dachte mir so viel. Aber warum?";
			link.l1.go = "tonzag_drink_7";
		break;
		
		case "tonzag_drink_7":
			dialog.text = "Weil niemand die Liga lebend verlässt, und man nicht ungeschoren davonkommt mit den Dingen, die wir dort getan haben, Kapitän. Ich wollte in den Ruhestand gehen, also habe ich es trotzdem versucht. Wie du sehen kannst, nicht sehr erfolgreich.";
			link.l1 = "Sagen Sie also, dass Ihre ehemaligen Kollegen enorme finanzielle Aufwendungen getätigt, fast hundert Menschen weggeworfen, einen Brandstifter verbrannt und ihr Kriegsschiff riskiert haben, nur um... Sie wegen Desertion zu töten?";
			link.l1.go = "tonzag_drink_8";
		break;
		
		case "tonzag_drink_8":
			dialog.text = "Ich war mehr als nur ein Laufbursche in der Liga, Kapitän. Ich weiß zu viel darüber. Ich kann nicht einfach gehen gelassen werden, und sie müssen dies klarstellen, damit niemand sonst an das Verlassen des Geschäfts denkt... Sie haben schon einmal versucht, mich zu erreichen... vor ziemlich langer Zeit... Sie haben meine Frau getötet und mich entstellt, obwohl es sie teuer zu stehen gekommen ist. Es gibt kein glückliches Ende zu dieser Geschichte, Kapitän. Geben Sie einfach den Befehl, und ich werde das Schiff verlassen und mich alleine mit ihnen auseinandersetzen, zum letzten Mal.";
			link.l1 = "Rede keinen Unsinn, Hercule... Und welche Rolle spielte Lucas Rodenburg in all dem? Er muss in diese Angelegenheiten verwickelt gewesen sein! Deine, oder besser gesagt seine, 'Organisation', die Liga...";
			link.l1.go = "tonzag_drink_9";
		break;
		
		case "tonzag_drink_9":
			dialog.text = "Verschiedene Agenturen, Kapitän. Zugegeben, sie gehorchten oft derselben Person und arbeiteten eng zusammen. Aber Rodenburgs Spezialagenten führten punktgenaue, effektive Schläge aus, während die Liga Massenoperationen durchführte. Und was ist jetzt aus der Liga geworden? Die Organisation gibt es nicht mehr, wie du siehst: Ich bin hier bei dir, John Murdock ist weg, Longway ist abgehauen, Van Berg liegt auf dem Meeresgrund, Rodenburg wurde hingerichtet... Trotzdem schuldete ich diesem verstorbenen Schurken etwas. Er bemerkte mich in der Liga, und als ich versuchte sie zu verlassen, zog er mich aus einigen ernsten Schwierigkeiten heraus und machte mich zu seinem Stellvertreter. Natürlich mochten es die anderen nicht, aber niemand wagte es, ihm zu widersprechen... Und dann entschied er sich unter den bekannten Umständen, sich von Murdock und mir zu trennen, aber du griffst ein und nahmst mich in deinen Dienst. Und so dachte ich, 'Hier ist meine zweite Chance, mit der Vergangenheit abzuschließen...' Du hast Rodenburg ausgespielt, die Liga verlor ihren Schutzpatron, es gab keine Gefahr mehr... Aber natürlich lag ich falsch... Alter Narr... Aber genug davon, Kapitän. Lassen Sie uns überlegen, was wir als nächstes tun sollen, wenn Sie wirklich nicht vorhaben, mich im ersten Hafen gehen zu lassen.";
			link.l1 = "Ich nicht. Ich nehme an, du hast einen Plan?";
			link.l1.go = "tonzag_drink_10";
		break;
		
		case "tonzag_drink_10":
			dialog.text = "Nichts Besonderes, eigentlich. Wir werden sie nie alle auslöschen, aber wir können ihnen solche großen Verluste zufügen, dass es sich für sie nicht lohnt, weiter hinter mir...uns herzujagen.";
			link.l1 = "Und wie machen wir das? Haben sie ein Lager?";
			link.l1.go = "tonzag_drink_11";
		break;
		
		case "tonzag_drink_11":
			dialog.text = "Ein großes Fort? Kaum. Es wäre zu auffällig und gefährlich für die Liga. Und mit Verlusten meine ich nicht menschliche Verluste - sie kümmern sich nicht um Menschen, aber sie werden es nicht genießen, Gold zu verlieren. Das Geld von der Firma kommt nicht mehr zu ihnen, richtig? Ich bezweifle, dass die Liga einen neuen Gönner gefunden hat, also müssen sie das Gold woanders herausquetschen.";
			link.l1 = "Und welcher Ort wäre das?";
			link.l1.go = "tonzag_drink_12";
		break;
		
		case "tonzag_drink_12":
			dialog.text = "Ich weiß nicht, Kapitän.";
			link.l1 = "Hercule, aber du hast gerade gesagt, dass du gerade deshalb verfolgt wirst, weil du zu viel weißt!";
			link.l1.go = "tonzag_drink_13";
		break;
		
		case "tonzag_drink_13":
			dialog.text = "Lass mich nachdenken... Vielleicht agiert die Liga gerade gegen die Spanier. Sie sind die Hauptkandidaten für eine ordentliche Aufmischung. Apropos, Rodenburg war immer auf guten Fuß mit den kastilischen Fettsäcken. Manchmal hat er die Liga-Jungs für verschiedene Jobs in ihre Richtung gelenkt und ihnen stets verboten, ihnen Schaden zuzufügen, was übrigens den Jungs nicht sehr gefiel...";
			link.l1 = "Gute Bedingungen, sagst du? Und was ist mit diesem einen Hidalgo und seinem Finger, den du mich zu deiner Taverne hast schleppen lassen?";
			link.l1.go = "tonzag_drink_14";
		break;
		
		case "tonzag_drink_14":
			dialog.text = "Das war ein Sonderfall, eine Nebenbestellung. Wenn du dich schuldig fühlst, Kapitän, kannst du beruhigt sein - dieser Don hat bekommen, was er verdient hat... Aber ich spreche von etwas anderem: Nachdem ihr Arbeitgeber verschwunden war, könnten die Agenten der Liga einfach ihren Gelüsten nachgeben und versuchen, ein solides Stück vom spanischen Kuchen zu greifen. Dank der Zusammenarbeit mit den Spaniern unter Rodenburg wissen sie, wo und was zu nehmen ist.";
			link.l1 = "Hm... du könntest recht haben. Aber soweit ich weiß, bricht niemand wirklich in spanische Banken ein, gegen die Spanier auf See zu operieren - das liegt an der Dame Glück... Vielleicht sollten wir nach einem spanischen Unternehmen suchen? Eine Fabrik?";
			link.l1.go = "tonzag_drink_15";
		break;
		
		case "tonzag_drink_15":
			dialog.text = "Vernünftige Annahme, Kapitän... Haben wir noch andere Anhaltspunkte?";
			link.l1 = "Hm... das Schiff, das uns heute angegriffen hat, ist Richtung Süden gezogen...";
			link.l1.go = "tonzag_drink_16";
		break;
		
		case "tonzag_drink_16":
			dialog.text = "Es ist unwahrscheinlich, dass sein Kapitän uns noch einmal belästigen wird, aber er muss die anderen warnen, dass die Dinge nicht nach Plan verlaufen sind, und vielleicht das Personal an einen anderen Ort transportieren. Noch etwas?";
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.KnowMain")) {
				link.l1 = "Ja, ich hatte ein freundliches Gespräch mit dem Kommandanten des Gefängnisses von Tortuga... Er erwähnte etwas über das Festland.";
				link.l1.go = "tonzag_drink_know";
			} else {
				link.l1 = "Nein, nichts anderes.";
				link.l1.go = "tonzag_drink_notknow";
			}
		break;
		
		case "tonzag_drink_know":
			dialog.text = "Ausgezeichnet, Kapitän! Süden, Festland, Spanier - das bedeutet, wir werden sie schnell finden. Setzen wir die Segel? Und danke, dass Sie meiner Geschichte zugehört haben.";
			link.l1 = "Ja, wir hatten ein ziemlich herzliches Gespräch... Lass uns in See stechen!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_drink_notknow":
			dialog.text = "Nicht viel, worauf man sich stützen kann. Aber für Leute wie uns ist das genug. Sollen wir nach Süden gehen? Auf der Suche nach einem spanischen Handelsunternehmen? Und danke, dass du meiner Geschichte zugehört hast.";
			link.l1 = "Ja, wir hatten wirklich eine Herz-zu-Herz-Unterhaltung... Lassen wir die Segel setzen!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_dead":
			dialog.text = "Schau, Kapitän. So arbeiten sie.";
			link.l1 = "Und Sie haben auch so gearbeitet?";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "Lass uns gehen, schauen wir mal, was drinnen ist.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_AfterDead");
		break;
		
		case "tonzag_afterminefight":
			dialog.text = "Eine schmutzige Angelegenheit, Kapitän. Wir haben dieses Versteck ausgeräumt, aber es ist sicherlich nicht das letzte...";
			link.l1 = "Was ist mit der Mine, Hercule?! All die Menschen draußen?! Wurden sie auch 'geräumt'! Und was meinte dieser Schurke?";
			link.l1.go = "tonzag_afterminefight_1";
		break;
		
		case "tonzag_afterminefight_1":
			dialog.text = "Let's discuss this later, Captain. Their commander survived; we need to interrogate him.";
			link.l1 = "Und was ist, wenn er nichts weiß?";
			link.l1.go = "tonzag_afterminefight_2";
		break;
		
		case "tonzag_afterminefight_2":
			dialog.text = "He knows something. Think about it - they were waiting for us, carried out all the gold, and eliminated witnesses. That means they had a plan. I want to take a look around here, and later I'll bring the scoundrel to the ship myself. You should also keep an eye out; perhaps they were too hasty and missed something.";
			link.l1 = "Gut, aber wenn wir zurück zum Schiff kommen, gibt es ein ernstes Gespräch zu führen!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			locations[FindLocation("LosTeques_town")].locators_radius.reload.gate_back = 1.0;
			DeleteAttribute(&locations[FindLocation("LosTeques_town")], "locators_radius.reload.reload1_back");
			AddDialogExitQuestFunction("Tonzag_PrepareJournal");
		break;
		
		case "tonzag_in_hold":
			dialog.text = "Gute Nachrichten, Kapitän.";
			link.l1 = "Ich sehe nichts Gutes in unserer Situation, Hercule. Lass uns gehen, wir müssen unter vier Augen sprechen.";
			link.l1.go = "tonzag_in_hold_1";
		break;
		
		case "tonzag_in_hold_1":
			dialog.text = "Also, so ist es, huh? Aye, Kapitän.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_EnterAlonso");
		break;
		
		case "tonzag_drink_again":
			dialog.text = "Ich sehe, dass wir eine ernsthafte Unterhaltung führen werden, Kapitän.";
			link.l1 = "Ja, und ich werde derjenige sein, der das Gespräch führt. Zuerst einmal, glaubst du nicht, dass hier ein gewisser Trend entsteht? Leichenhaufen folgen uns, wohin wir auch gehen! Zuerst nimmst du eine Ladung Traubenschuss in den Bauch, und am nächsten Tag sterben über hundert Menschen, gute und nicht so gute, in... Ich kann es nicht einmal eine Seeschlacht nennen! Eine Siedlung wurde vor ein paar Tagen ausgelöscht, und heute haben wir zum wachsenden Haufen beigetragen, indem wir eine Gruppe von Menschen in den Minen abgeschlachtet haben.";
			link.l1.go = "tonzag_drink_again_1_1";
		break;
		
		case "tonzag_drink_again_1_1":
			dialog.text = "";
			link.l1 = "Natürlich mache ich mir Sorgen, dass der Haufen morgen zu einem Berg wird, aber was mich wirklich erschreckt, ist, dass all dieses Blut wegen einer Person vergossen wird. Und diese Person hat eine bedeutende Position in meiner Mannschaft!";
			link.l1.go = "tonzag_drink_again_1";
		break;
		
		case "tonzag_drink_again_1":
			dialog.text = "";
			link.l1 = "Zweitens, du hast mich belogen, Hercule. Kein Deserteur ist die Mühe wert, die deine ehemaligen Kollegen in deine Eliminierung stecken. Was hat unser Gefangener in den Minen geschrien? Verräter? Porto Bello? Gruoh? Du hast etwas getan, Hercule, und diesmal will ich die Wahrheit.";
			link.l1.go = "tonzag_drink_again_2";
		break;
		
		case "tonzag_drink_again_2":
			dialog.text = "Truth? The truth is, Captain, that I did desert, along with my wife Gruoh. Madame Tonzag didn't want to leave the League; she loved that life, but she loved me even more. We were supposed to take care of a Spanish hidalgo, but he made a better offer. It was our chance, and we both agreed to go into his service. Of course, the League thought we perished on a mission and sent a second group to Porto Bello to finish the job and seek revenge.";
			link.l1 = "Und du hast sie alle getötet?";
			link.l1.go = "tonzag_drink_again_3";
		break;
		
		case "tonzag_drink_again_3":
			dialog.text = "Zuerst haben sie Gruoh getötet und mich entstellt. Der Hidalgo wollte nichts mehr mit mir zu tun haben und warf mich raus. Das ist, als Rodenburg mich gefunden hat...";
			link.l1 = "Und wie soll ich dir jetzt vertrauen? Du hast die Armee verlassen, die Liga verlassen und deine eigenen Partner getötet! Wirst du mich auch verraten, wenn der richtige Moment kommt?";
			link.l1.go = "tonzag_drink_again_4";
		break;
		
		case "tonzag_drink_again_4":
			dialog.text = "Ja, ich bin desertiert, habe den Vertrag gebrochen, habe ein paar Dutzend Mitglieder der Liga getötet. Aber ich habe meine Lektion gelernt, Kapitän. Und außerdem kann ein toter Mann niemanden verraten, und ich bin schon lange tot, seit Porto Bello. Und vielleicht ist das der Grund, warum es jetzt so schwer ist, mich zu töten.";
			link.l1 = "Das reicht für heute. Ich habe das Gefühl, du erzählst mir immer noch nicht alles.";
			link.l1.go = "tonzag_drink_again_5";
		break;
		
		case "tonzag_drink_again_5":
			dialog.text = "Ich werde mich selbst um den Gefangenen kümmern, oder möchtest du mitmachen?";
			link.l1 = "Lass uns gehen. Ich werde ihn selbst verhören.";
			link.l1.go = "tonzag_drink_again_hold";
			link.l2 = "Nein, solche Angelegenheiten sind nichts für mich. Wir sehen uns in einer halben Stunde in meiner Kabine!";
			link.l2.go = "tonzag_drink_again_cabin";
		break;
		
		case "tonzag_drink_again_hold":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToHold");
		break;
		
		case "tonzag_drink_again_cabin":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToCabin");
		break;
		
		case "tonzag_hold":
			dialog.text = "Wer ist jetzt der Boss? Arno?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog1");
		break;
		
		case "tonzag_hold_1":
			dialog.text = "Dieser Abschaum ist an die Macht gekommen? Es hat nicht lange gedauert, bis du dich zu einer gewöhnlichen Bande von Banditen herabgesunken bist...";
			link.l1 = "Wer ist Austin?";
			link.l1.go = "tonzag_hold_2";
		break;
		
		case "tonzag_hold_2":
			dialog.text = "Austins Bande war berühmt dafür, freie Kapitäne in die Wildnis zu locken, sie aufzuschneiden und ihre Leichen vollständig von Geld oder Krimskrams zu befreien. Gutes Geschäft, und es mangelt nicht an Abenteuersuchenden, also hat niemand etwas dagegen. Aber sie stießen auf ein Problem mit einem Kapitän, und so musste er seine Mannschaft unter den Schutz der Kompanie stellen. Wir hielten ihn an der Leine und ließen ihn nur los, wenn wir Probleme auf schnelle und einfache Weise lösen mussten.";
			link.l1 = "Ich bezweifle, dass ich mit einer solchen Person verhandeln kann.";
			link.l1.go = "tonzag_hold_3";
		break;
		
		case "tonzag_hold_3":
			dialog.text = "Das ist sicher. Wenn er und seine Leute jetzt die Dinge regeln, wird die Liga bald nur noch eine weitere Bande sein.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog3");
		break;
		
		case "tonzag_after_hold":
			dialog.text = "Eine interessante Unterhaltung, die wir hatten.";
			link.l1 = "Ich würde gerne wissen, wie viel davon wahr ist... Was ist mit dem Massaker in Porto Bello? Wenn er nicht gelogen hat, bedeutet das, dass Sie das letzte Mal, als wir sprachen, erneut ein paar wichtige Fakten aus Ihrer illustren Biographie ausgelassen haben.";
			link.l1.go = "tonzag_after_hold_1";
		break;
		
		case "tonzag_after_hold_1":
			dialog.text = "Es war heiß in Porto Bello, Kapitän. Ich kämpfte um mein Leben, um das Leben des Arbeitgebers, um das Leben meiner Frau. Ich hatte keine Zeit, die Getöteten zu zählen und jeden Bauern zu betrauern, der zur falschen Zeit auf der Straße auftauchte.";
			link.l1 = "In dieser Prioritätenreihenfolge?";
			link.l1.go = "tonzag_after_hold_2";
		break;
		
		case "tonzag_after_hold_2":
			dialog.text = "Nein, natürlich nicht. Ihre zuerst. Immer.";
			link.l1 = "Wie denken Sie? Sollen wir nach Caracas gehen?";
			link.l1.go = "tonzag_after_hold_3";
		break;
		
		case "tonzag_after_hold_3":
			dialog.text = "Ich persönlich würde das nicht tun, Kapitän. Und ich rate Ihnen auch davon ab. Für die Liga sind Sie kein Feind mehr, und ich bin für sie von keinem Interesse, zumindest vorerst, solange ich in Ihren Diensten stehe. Außerdem habe ich dieses unangenehme Gefühl tief unten\nEs wird schlecht sein, wenn wir dorthin gehen. Sehr schlecht. Diese Geschichte hat kein glückliches Ende. Aber ich werde bis zum Ende bei Ihnen sein, Kapitän.";
			link.l1 = "Ich werde es in Betracht ziehen.";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_hold_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_hold_4":
			dialog.text = "";
			link.l1 = "Übrigens, Sie hatten recht - sie haben es nicht geschafft, die Mine gut genug zu säubern. Schau.";
			link.l1.go = "tonzag_after_hold_5";
		break;
		
		case "tonzag_after_hold_5":
			dialog.text = "Das Tagebuch eines Offiziers... verschlüsselt, aber es ist eine alte Chiffre, ich kenne sie\nNichts Interessantes, scheint es. Es war das Tagebuch unseres Gefangenen. Jetzt ist klar, warum er so bereitwillig reden wollte. Schau hier - Hinweise auf einen versteckten Schatz! Der Schurke hatte offensichtlich vor, sich zur Ruhe zu setzen und war bereit, jeden Moment zu verschwinden!";
			link.l1 = "Und wo ist dieser verborgene Ort?";
			link.l1.go = "tonzag_after_hold_6";
		break;
		
		case "tonzag_after_hold_6":
			dialog.text = "Sie kennen diese Insel, Kapitän. In ihren Gewässern haben Sie Van Berd beendet.";
			link.l1 = "In Ordnung, es ist nicht zu weit, also lass uns nachsehen. Was Caracas betrifft, habe ich mich noch nicht entschieden, aber ich denke, dass wir einen Monat haben.";
			link.l1.go = "tonzag_after_hold_7";
		break;
		
		case "tonzag_after_hold_7":
			dialog.text = "Wie Sie wünschen, Kapitän. Ich bin bis zum Ende bei Ihnen.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_after_drink":
			dialog.text = "It's done, Captain. Austin is currently in Caracas; I think we have a month.";
			link.l1 = "Zuerst einmal. Was hat der Gefangene gesagt? Wer ist dieser Austin? Und warum sollten wir nach Caracas gehen?";
			link.l1.go = "tonzag_after_drink_1";
		break;
		
		case "tonzag_after_drink_1":
			dialog.text = "Austins Bande war dafür berühmt, freie Kapitäne in die Wildnis zu locken, sie aufzuschlitzen und ihre Leichen vollständig von Geld oder Schmuckstücken zu befreien. Gutes Geschäft, und es mangelt nicht an Abenteuersuchenden, also hat niemand etwas dagegen. Aber sie stießen auf ein Problem mit einem Kapitän, und so musste er seine Mannschaft unter den Schutz der Kompanie stellen. Wir hielten ihn an der Leine und ließen ihn nur los, wenn wir Probleme auf schnelle und einfache Weise lösen mussten.";
			link.l1 = "Ich bezweifle, dass ich mit einer solchen Person einen Deal aushandeln kann.";
			link.l1.go = "tonzag_after_drink_2";
		break;
		
		case "tonzag_after_drink_2":
			dialog.text = "Das ist sicher. Wenn er und seine Leute jetzt das Sagen haben, wird die Liga bald nur noch eine weitere Bande sein. Aber ich würde nicht nach Caracas gehen, Kapitän.";
			link.l1 = "Ernsthaft? Hast du Angst?";
			link.l1.go = "tonzag_after_drink_3";
		break;
		
		case "tonzag_after_drink_3":
			dialog.text = "Es ist nicht so, Kapitän. Bevor er seinen Wunden erlag, offenbarte der Gefangene, dass Sie für die Liga kein Feind mehr sind und ich für sie von keinerlei Interesse bin, zumindest solange ich in Ihren Diensten stehe. Die Liga scheint einen neuen einflussreichen Gönner zu haben, der befohlen hat, uns in Ruhe zu lassen\nUnd Caracas... Ich habe dieses üble Gefühl tief unten... Es wird schlecht sein, wenn wir dorthin gehen. Sehr schlecht. Diese Geschichte hat kein glückliches Ende. Aber ich werde bis zum Ende bei Ihnen sein, Kapitän.";
			link.l1 = "Ich werde darüber nachdenken. Natürlich würde ich diese Geschichte gerne ein für alle Mal klären, aber vielleicht haben Sie recht. Ich bezweifle, dass sie es nach den Ereignissen der letzten Woche wagen werden, uns erneut zu nähern.";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_drink_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_drink_4":
			dialog.text = "";
			link.l1 = "Übrigens, du hattest recht - sie haben es nicht geschafft, die Mine gut genug zu säubern. Schau.";
			link.l1.go = "tonzag_after_drink_5";
		break;
		
		case "tonzag_after_drink_5":
			dialog.text = "Das Tagebuch eines Offiziers... verschlüsselt, aber es ist eine alte Chiffre, ich kenne sie\nNichts Interessantes, scheint es. Es war das Tagebuch unseres Gefangenen. Schau hier - Hinweise auf einen versteckten Schatz! Der Schurke hatte offensichtlich vor, in Rente zu gehen und war bereit, jederzeit zu verschwinden!";
			link.l1 = "Und wo ist dieser verborgene Ort?";
			link.l1.go = "tonzag_after_drink_6";
		break;
		
		case "tonzag_after_drink_6":
			dialog.text = "Sie kennen diese Insel, Kapitän. In ihren Gewässern haben Sie Van Berd sein Ende bereitet.";
			link.l1 = "In Ordnung, es ist nicht zu weit, also lasst uns mal nachsehen. Was Caracas betrifft, habe ich mich noch nicht entschieden, aber ich glaube, wir haben einen Monat.";
			link.l1.go = "tonzag_after_drink_7";
		break;
		
		case "tonzag_after_drink_7":
			dialog.text = "Wie Sie wünschen, Kapitän.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_church":
			dialog.text = "Halt ein, Kapitän. Ich gehe alleine dorthin.";
			link.l1 = "And why is that? Feeling heroic now? It's too late; you've made this mess, but we have to clean it together.";
			link.l1.go = "tonzag_church_1";
		break;
		
		case "tonzag_church_1":
			dialog.text = "Es besteht keine Notwendigkeit für Sie, für meine Fehler zu bezahlen, Kapitän. Sie hatten recht - wo immer ich hingehe, sterben Menschen und unschuldiges Blut fließt. Wenn wir zusammen in diese Kirche eintreten, wird es ein weiteres Porto Bello sein, und das möchte ich nicht.";
			link.l1 = "Was ist dort wirklich passiert?";
			link.l1.go = "tonzag_church_2";
		break;
		
		case "tonzag_church_2":
			dialog.text = "Ein Massaker. Ich wollte mich zurückziehen, Kapitän. Ich wollte das Gold nehmen, meine Frau und nach Hause nach Carcassonne gehen. Ich wusste, dass die Liga mehr Leute schicken würde, um meine Arbeit zu beenden und nahm einen großzügigen Vorschuss von meinem neuen Gönner. Dann blieb nur noch, die Stadtwache gegen meine ehemaligen Komplizen und den neuen Arbeitgeber aufzubringen. In all dem Tumult sollte ich mit dem Geld verschwinden und vielleicht, wenn die Zeit es erlaubt, ein paar fette Katzen von Porto Bello berauben.";
			link.l1 = "Guter Plan, obwohl ich es anders gemacht hätte. Zu viele Dinge könnten schief gehen.";
			link.l1.go = "tonzag_church_2a";
			link.l2 = "Ich bin selbst kein Engel, aber dein Vorgehen lässt sogar mich erschauern. Ich bin überrascht, dass du mich noch nicht verraten hast, so wie du es bei der Liga, dem Hidalgo und sogar deiner eigenen Frau getan hast.";
			link.l2.go = "tonzag_church_2a";
		break;
		
		case "tonzag_church_2a":
			dialog.text = "Everything that could go wrong, did go wrong. Shooting a three-pounder towards the governor's palace was a mistake. It barely scratched the governor himself, but his beautiful daughter, as I hear, had to have both her legs amputated below the knees to save her life. The response was horrific - a blood bath; great many people perished, Captain. Now you're looking at the last living witness to those events, and not long ago, you cut down another one yourself.";
			link.l1 = "Erklären Sie.";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_2b":
			dialog.text = "Wenn Madame Tonzag noch am Leben wäre, hätte ich Sie ohne zu zögern verraten, Kapitän. Ich bin ein lebender Toter, der Ihnen folgt, weil ich keinen anderen Platz in dieser Welt habe. Jetzt sehen Sie den letzten lebenden Zeugen dieser Ereignisse, und vor nicht allzu langer Zeit haben Sie selbst einen anderen niedergeschlagen.";
			link.l1 = "Erklären Sie.";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_3":
			dialog.text = "Verzeihen Sie mir, Kapitän, dass ich Ihnen auf dem Weg nicht alles erzählt habe. Als wir uns das erste Mal trafen, dachte ich, Sie wären nur ein weiterer Abschaum wie ich. Und wissen Sie, was ich als Erstes getan habe? Ich habe Sie dazu gebracht, meine Drecksarbeit zu erledigen - diesen spanischen Don zu töten, den ich ursprünglich nicht töten wollte und dann beschlossen habe zu verraten. Dieser Hidalgo, Rodriguez...";
			link.l1 = "Und wofür brauchtest du seinen Finger?";
			link.l1.go = "tonzag_church_4";
		break;
		
		case "tonzag_church_4":
			dialog.text = "Keine Tricks da. Nur ein Test, Kapitän. Wir rekrutieren jedes Jahr Dutzende von jungen Halsabschneidern wie Sie. Nur wenige bestanden die grundlegende Ehrlichkeitsprüfung, und selbst die starben bei den ersten Operationen. Sie sollten die Operation mit Fleetwoods Logbuch nicht überleben. Ich hatte vor, einfach das Haus zu betreten, die Überlebenden zu erledigen und das Logbuch zu nehmen.";
			link.l1 = "Wenn ich mich richtig erinnere, hat sich die Geschichte etwas anders entwickelt.";
			link.l1.go = "tonzag_church_5";
		break;
		
		case "tonzag_church_5":
			dialog.text = "So war es, Kapitän. Ich weiß nicht, was mich dazu bewegt hat, Ihnen zu helfen, aber Sie haben die Füchse mit einer solchen Lebenslust bekämpft, dass Sie mich sogar damit angesteckt haben, wenn auch nur kurz. Am Ende haben Sie mich unwissentlich gerettet. Sie schulden mir nichts, Kapitän. Und ich werde Sie nicht hineinlassen. Das ist meine Angelegenheit, meine Erlösung.";
			link.l1 = "Wie du wünschst, Hercule. Es schmerzt, einen solchen Kämpfer zu verlieren, aber du hast dich vor langer Zeit selbst verloren und bist keinen weiteren vergossenen Blut wert. Du schuldest mir auch nichts und ich hoffe, du findest Erlösung in dieser kleinen Kirche.";
			link.l1.go = "tonzag_church_bad";
			link.l2 = "Schöne Rede, Hercule. Fahr zur Hölle! Falls es dir entgangen ist, sind deine Probleme in letzter Zeit zu meinen geworden. Du bist mein Offizier, und nur ich werde entscheiden, ob du Vergebung verdienst oder nicht. Also wirst du noch ein bisschen bei uns bleiben müssen und deine Erlösung durch Tapferkeit als Teil meiner Crew verdienen!";
			link.l2.go = "tonzag_church_good";
		break;
		
		case "tonzag_church_bad":
			dialog.text = "Danke für alles, Kapitän. Auf Wiedersehen!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchBad");
		break;
		
		case "tonzag_church_good":
			dialog.text = "Aye aye, Kapitän!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchGood");
		break;
		
		case "tonzag_afterchurchfight":
			dialog.text = "Ich habe in meiner Zeit viele Schurken gesehen, Kapitän, aber zum ersten Mal spürte ich einen Dreh des Horrors in mir. Was denken Sie: Wenn ein kleineres Monster ein größeres Monster tötet, zählt das zur Erlösung?";
			link.l1 = "Verdünnen sie Rum mit Wasser? Sag es mir, wenn du es herausfindest. Los geht's, wir sind hier fertig.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ResetTonzag");
		break;

	}
}