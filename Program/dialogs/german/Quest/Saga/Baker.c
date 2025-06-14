// Раймонд Бейкер - палач Сент-Джонса и возможный офицер
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
			dialog.text = "Willst du etwas?";
			link.l1 = "Nein, nichts.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "baker":
			dialog.text = "Danke, Kapitän! Ich kann mir gar nicht vorstellen, was ich ohne Sie gemacht hätte...";
			link.l1 = "Kann ich mir vorstellen. Du hättest vor Hunger sterben können oder wärst im Magen eines Wilden aus Dominica gelandet. Aber du hast die Chance, dich bei mir zu revanchieren.";
			link.l1.go = "baker_1";
		break;
		
		case "baker_1":
			dialog.text = "Wie kann ich Ihnen helfen, Kapitän?";
			link.l1 = "Ich möchte mehr über einen Mann wissen. Er ist sozusagen unser gemeinsamer Freund. Tatsächlich ein sehr enger Freund von Ihnen. Ich meine Kapitän Butcher. Ja, der, den Sie vor zwanzig Jahren gehängt haben. Herr, warum sind Sie so blass? Möchten Sie einen Schluck Rum?";
			link.l1.go = "baker_2";
		break;
		
		case "baker_2":
			dialog.text = "Hat... hat er Sie gesandt?";
			link.l1 = "Unsinn! Wie kann ich 'von ihm gesandt' sein, wenn er tot ist! Ich interessiere mich mehr für die Dinge, die er hinterlassen hat, als für Butcher selbst. Briefe, Dokumente, solche Sachen. Vielleicht hast du etwas in seinen Taschen gefunden... Warte! Ich verstehe es nicht. Glaubst du wirklich, dass Butcher noch lebt? Du hast ihn doch selbst hingerichtet!";
			link.l1.go = "baker_3";
		break;
		
		case "baker_3":
			dialog.text = "Verdammt! Du hast keine Ahnung. Das bedeutet, du wurdest nicht von Butcher geschickt, wie ich dachte...";
			link.l1 = "Nun, nun. Das wird immer interessanter. Es scheint, dass Henry allen Grund hatte, vor Butcher Angst zu haben und deshalb starb er an einem Herzinfarkt... Lebt Butcher noch?";
			link.l1.go = "baker_4";
		break;
		
		case "baker_4":
			dialog.text = "Er tut es, Kapitän... Und sie suchen nach mir.";
			link.l1 = "Raymond, man hat mir gesagt, dass du kein dummer Mann bist. Versuche nicht, mit mir zu spielen. Hier bist du vor jeder Bedrohung sicher. Erzähl mir alles, was du weißt, und ich werde etwas finden, um dir zu helfen. Vielleicht haben wir gemeinsame Feinde. Lass uns mit Butcher anfangen.";
			link.l1.go = "baker_5";
		break;
		
		case "baker_5":
			dialog.text = "Er lebt noch, aber er hat jetzt einen anderen Namen! Seine Männer haben mich in der Nacht der Hinrichtung besucht. Jackman und ein anderer Mann mit einem seltsamen Spitznamen. Soweit ich mich erinnere, war es der 'Ertrunkene Mann'.";
			link.l1 = "Hangman. Henry Hangman.";
			link.l1.go = "baker_6";
		break;
		
		case "baker_6":
			dialog.text = "Richtig! Sie boten mir ein einfaches Geschäft an - auf die schmerzhafteste Weise zu sterben oder ihren Kapitän zu retten. Also musste ich die Hinrichtung mit speziellen Geräten, die ich in meiner Freizeit gebaut hatte, vortäuschen. Sie sehen, eine solche Konstruktion aus Gurten und Klammern kann das Körpergewicht verteilen.\nAlles, was ich tun musste, war es mit einem geheimen Haken in der Schlaufe zu verbinden. Die 'Leiche' musste ihre Rolle allerdings gut spielen. Ich muss sagen, dass Lawrences Schauspiel ziemlich überzeugend war, er hat alles richtig gemacht, außer dass er sich weigerte, sich in die Hose zu pissen, wegen...";
			link.l1 = "Hast du Butcher gerade 'Lawrence' genannt?";
			link.l1.go = "baker_7";
		break;
		
		case "baker_7":
			dialog.text = "Das ist sein wahrer Name. Ich habe dir gesagt, dass er Lawrence Beltrope genannt wird. Seit er vor einem Jahr in die Karibik zurückkehrte, bin ich unruhig. Und als ich herausfand, dass einige üble Leute nach mir suchen...\nIch habe sogar ein Geständnis für die Behörden geschrieben, nur für den Fall. Ich habe es ständig bei mir, da ich zu ängstlich bin es wegzugeben. Da sie ansonsten denken könnten, dass ich ein williger Gehilfe war. Bitte, lassen Sie mich bei Ihrer Crew bleiben. Ich schwöre, ich bin ein ausgezeichneter Arzt und kann Ihnen sehr helfen.";
			link.l1 = "Gut. Und was ist mit den persönlichen Gegenständen von Butcher... äh, Beltrope? Ist er mit Thomas Beltrope verwandt?";
			link.l1.go = "baker_8";
		break;
		
		case "baker_8":
			dialog.text = "Keine Ahnung. Ich habe nichts Besonderes mehr von Beltrope selbst. Aber ich werde dir alles geben was ich habe, du kannst damit machen was du willst. Alle Papiere zum Thema sind in meiner Tasche. Ich habe alles für den Fall der Fälle aufbewahrt und halte es nahe bei mir. \nHier, schau mal ... das ist die Legende von Kapitän Butcher, das ist mein Geständnis... Das sind Dinge, die Joshua Leadbeater gehörten...";
			link.l1 = "Halt! Leadbeater? Wer ist das?";
			link.l1.go = "baker_9";
		break;
		
		case "baker_9":
			dialog.text = "Oh! Er war ein ganz besonderer Mann. Er war derjenige, der Butcher selbst gejagt hat. Die Leute erinnerten sich an ihn als den 'maskierten Mann'. Kurz nach der Hinrichtung von Butcher wurde er ermordet. Jemand schlitzte ihm mit einem Haifischzahn die Kehle auf! Ein Schnitt und er war erledigt. Als er noch lebte, muss er sehr gelitten haben.\nHättest du sein Gesicht unter der Maske gesehen, es war nichts als Fleisch! Als er starb, hatte er diese Tagebuchseite in seiner Tasche. Es muss aus den Schriften von Jessica Rose stammen. Gruselige Geschichte! Lies sie, sie wird vieles verständlicher machen.\nUnd das ist der Zahn selbst. Kannst du die Buchstaben sehen? S.D.... Was auch immer das bedeutet. Es sind auch noch einige Blutflecken übrig.";
			link.l1 = "Genug! Ich muss alles sorgfältig lesen und darüber nachdenken. Und du wirst mein Passagier oder Schiffsarzt sein, bis ich damit fertig bin. Du kannst frei atmen, Raymond, du bist sicher auf meinem Schiff.";
			link.l1.go = "baker_10";
		break;
		
		case "baker_10":
			DialogExit();
			sld = characterFromId("Baker_Cap");
			LAi_SetImmortal(sld, false);
			sld.lifeday = 0;
			//sld.ship.hp = 0;
			//sld.SinkTenPercent = true;
			bQuestDisableMapEnter = false;
			GiveItem2Character(pchar, "shark_teeth");
			GiveItem2Character(pchar, "letter_jess");
			GiveItem2Character(pchar, "letter_baker"); // показания бейкера
			ChangeItemDescribe("letter_baker", "itmdescr_letter_baker"); // Addon-2016 Jason
			AddQuestRecordInfo("Legend_CapBucher", "1");
			AddQuestRecordInfo("Letter_jess", "1");
			AddQuestRecord("Shadows", "5");
			pchar.questTemp.Saga.Shadows = "islatesoro";
			// в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.CompanionDisable = true; //нельзя в компаньоны
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Baker_officer";
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddCharacterExpToSkill(pchar, "Sailing", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Baker_officer":
			dialog.text = "Ja, Kapitän?";
			Link.l1 = "Höre auf meinen Befehl!";
            Link.l1.go = "stay_follow";
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Raymond, gib mir einen vollständigen Schiffsbericht.";
			    Link.l11.go = "QMASTER_1";

			    // Warship. Автозакупка товара
				Link.l12 = "Ich möchte dass du bestimmte Waren kaufst, jedes Mal wenn wir angedockt sind.";
				Link.l12.go = "QMASTER_2";
			}
			
			link.l2 = "Es ist nichts. Wegtreten!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Baker_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
        case "QMASTER_1":
			dialog.Text = "Komm schon, Kapitän, ich bin ein Arzt, kein Zahlmeister. Auch wenn ich in der Vergangenheit in anderen Bereichen gearbeitet habe... egal. Ich mache wirklich keine Buchhaltung, Entschuldigung.";
			Link.l1 = "Gut, so sei es. Du bist mein Arzt - wie wir vereinbart haben, nachdem du meiner Mannschaft beigetreten bist.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Kapitän, um ganz ehrlich zu sein, habe ich nie viel Erfahrung im Handel gesammelt. Nie gehandelt, nie Preisschilder verfolgt. Außerdem... Ich würde lieber auf dem Schiff bleiben, wenn es Ihnen recht ist. Einige dieser Händler könnten mich erkennen und bevor Sie es wissen - kommen kurz darauf maskierte Männer.";
			link.l1 = "Also, du wirst weiterhin in Angst vor deiner Vergangenheit leben... Gut, atme aus, ich werde es selbst machen.";
			Link.l1.go = "exit";
        break;
		
		case "stay_follow":
            dialog.Text = "Befehle?";
            Link.l1 = "Steh hier!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Folge mir und halt Schritt!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Ändere die Munitionsart für deine Feuerwaffe.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Wähle die Art der Munition:";
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
            dialog.Text = "Es gibt eine Änderung der Disposition!";
            Link.l1 = "Weggetreten.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Es gibt eine Änderung der Disposition!";
            Link.l1 = "Weggetreten.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
