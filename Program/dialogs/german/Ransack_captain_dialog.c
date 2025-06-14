// BOAL диалог пленников - в трюме
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref offref;
    int i, cn;
    int qty;
    string attrLoc, sTmp;
    
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "First time":
		//--> Jason, Ложный след
		if (CheckAttribute(pchar, "questTemp.FalseTrace.Prisoner") && GetFullName(npchar) == pchar.questTemp.FalseTrace.CapName)
		{
			dialog.text = "Was wollen Sie, Kapitän? Über mein Lösegeld diskutieren? Ich möchte, dass Sie wissen, dass mir das Schicksal des Mädchens am Herzen liegt...";
			link.l1 = "Du sprichst von Katerine Rayner? Ich bin schon darüber informiert, "+pchar.questTemp.FalseTrace.CapName+". Sie bat mich, mit Ihnen zu sprechen.";
			link.l1.go = "FalseTrace_Prisoner";
			break;	
		}
		//<-- Ложный след
		
		// Addon-2016 Jason ФМК-Гваделупа
		if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && CheckAttribute(pchar, "questTemp.FMQG.Prisoner") && GetFullName(npchar) == pchar.questTemp.FMQG.Prisoner)
		{
			dialog.text = "";
			link.l1 = "Sieh mal, Don Juan, Verrat ist schlecht...";
			link.l1.go = "FMQG";
			break;	
		}
			if (sti(NPChar.nation) == PIRATE)
			{
				dialog.text = RandSwear()+"Ich bin dein Gefangener, "+GetAddress_Form(NPChar)+". Aber ich möchte, dass du weißt, dass "+NationNameNominative(sti(NPChar.nation))+" bezahlt nie für ihre Leute. Wir sind alle für uns selbst.";
				link.l1 = "Nun... Ich sehe, dass ich mit dir keinen Gewinn machen werde. Zumindest kann ich dich als Verbrecher in irgendeiner Kolonie auslösen.";
				link.l1.go = "offender";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l2 = "Schau, du bist ein geschickter Kämpfer und ich brauche Leute wie dich. Möchtest du unter meinem Kommando dienen?";
					link.l2.go = "free_to_officer";
				}	
			}
			else
			{
				dialog.text = RandSwear()+"Ich bin dein Gefangener, "+GetAddress_Form(NPChar)+". "+NationNameNominative(sti(NPChar.nation))+" wird einen guten Preis für meine Freiheit zahlen.";
				if(NPChar.EncType == "trade" && FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
				{
					link.l1 = "Schau, du bist ein geschickter Seemann und ich brauche Leute wie dich. Möchtest du unter meinem Kommando dienen?";
					link.l1.go = "free_to_officer_trader";
				}
			}
			attrLoc = Sea_FindNearColony();
			if (attrLoc != "none") 
			{
                link.l3 = "Wir sind nicht weit von "+GetConvertStr(attrLoc+" Stadt","LocLables.txt")+". Und ich könnte dich hier gehen lassen.";
			    link.l3.go = "free_withoutFee";
			}
			else
			{
                link.l3 = "Geh zum Bootsmann, sag ihm, er soll dir ein Schließfach geben. Du kannst im nächsten Hafen an Land gehen.";
			    link.l3.go = "free_withoutFee_2";
			}			
			link.l4 = "Ich vermute, ich werde einen großartigen Sklaven aus dir machen - stark und pflichtbewusst.";
			link.l4.go = "Slave_1";
			link.l5 = "Sie haben einen Befehl zum Einholen Ihrer Segel ignoriert und mit Gewalt Widerstand geleistet. Dafür werden Sie gehängt. Der Bootsmann hat bereits meine Befehle erhalten.";
			link.l5.go = "PunishmentAction";
			link.l99 = "Ich weiß.";
			link.l99.go = "exit";
			NextDiag.TempNode = "second time"; 
		break;
		
		case "second time":
			if(CheckAttribute(NPChar,"Hold_GenQuest") && !CheckAttribute(pchar,"GenQuest.Hold_GenQuest"))
			{
				switch(sti(NPChar.Hold_GenQuest.variant))
				{				
					case 0: // "tip-off"
						dialog.text = RandPhraseSimple("Kapitän, möchten Sie meinen Vorschlag über eine profitablere Variante meines Lösegeldes hören?","Ich verstehe, dass in meiner Lage kein Raum für Handel ist, aber möchten Sie meinen Vorschlag hören?");
						link.l1 = "Ich höre zu.";	
						link.l1.go = "free_tip_off";
					break;
					
					case 1:
						dialog.text = "Kapitän, warum lässt du mich nicht einfach frei? Ich bin für dich von keinem Wert. Wenn du mich an Sklavenhändler verkaufst, bekommst du nur ein paar Münzen und einen schlechten Ruf.";
						link.l1 = "Und wenn ich dich einfach so freilasse, bekomme ich gar nichts...";
						link.l1.go = "free_by_hoard";
						attrLoc = Sea_FindNearColony();
						if (attrLoc != "none") 
						{
							link.l2 = "Sie haben einen Befehl zum Senken Ihrer Segel ignoriert und mit Gewalt Widerstand geleistet. Sie werden dafür gehängt werden. Der Bootsmann hat bereits meine Befehle erhalten.";
							link.l2.go = "PunishmentAction";							
						}
						else
						{
							link.l2 = "Du bist wirklich hartnäckig, also denke ich, dass ich dir geben kann, was du willst. Du bist jetzt ein freier Mann. Verlasse mein Schiff.";
							link.l2.go = "free_in_sea";
						}
						link.l3 = LinkRandPhrase("Teste meine Geduld nicht. Du bist bereits ein glücklicher Mann, am Leben zu bleiben.","Ich habe meine eigenen Pläne für dich.","Ich vermute, dass du mir in der Zukunft noch nützlich sein kannst.");
						link.l3.go = "exit";	
					break;
					
					case 2: // "ransom"
						dialog.text = "Kapitän, diese Ungewissheit bringt mich um. Darf ich wissen, was Sie mit mir vorhaben?";
						link.l1 = "Haben Sie mir etwas anzubieten?";
						link.l1.go = "free_buyout";
						link.l2 = RandPhraseSimple("Ich habe noch keine Vorstellungen von dir.",RandPhraseSimple("Pläne? Kanonenkugel an deinem Hals? Ich mache nur Spaß, ha!","Du bist mein Gefangener und ich habe alle Rechte, mit dir zu tun, was ich will. Deine eigene Meinung hat hier keinen Wert."));
						link.l2.go = "exit";
					break;										
				}
				NextDiag.TempNode = "second time"; 
			}
			else
			{
				if (sti(NPChar.nation) == PIRATE)
				{
					dialog.text = "Kapitän, warum lässt du mich nicht einfach gehen? Du brauchst mich nicht. Pirat zu werden war die einzige Option für mich, weil ich keine wertvollen Fähigkeiten oder Bildung habe. Mein Wunsch war es, etwas Geld zu verdienen und dann in den Ruhestand zu gehen.";
					if (FindFreeRandomOfficer() > 0)
					{
						link.l2 = "Schau, du bist ein geschickter Kämpfer und ich brauche Halsabschneider wie dich. Möchtest du mein Offizier sein?";
						link.l2.go = "free_to_officer";
					}				
					link.l3 = LinkRandPhrase("Keine Gnade für dich. Es gibt viele Schläger auf See. Zumindest wird jetzt einer weniger dort segeln."," Irgendwelche Probleme, 'Seewolf'? Bleib hier und halt die Klappe.","Galgen warten auf alle deinesgleichen. Ich werde dich an die Behörden verkaufen und das wird eine große Lektion für jeden Piraten sein.");	
					link.l3.go = "exit";
				}
				else
				{
					if(NPChar.EncType == "trade")
					{
						dialog.text = "Kapitän, ich flehe Sie an... Lassen Sie mich frei. Ich habe Familie und Kinder und sie werden es ohne mich nicht schaffen.";
						if (FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
						{
							link.l2 = "Schau, du bist ein geschickter Seemann und ich brauche Leute wie dich. Möchtest du unter meinem Kommando dienen?";
							link.l2.go = "free_to_officer_trader";
						}
						link.l3 = LinkRandPhrase("Ich habe meine eigenen Pläne mit dir.","Ich vermute, dass du mir in Zukunft immer noch nützlich sein kannst.","Du bist mein Gefangener und ich habe alle Rechte, mit dir zu tun, was immer ich will.");
						link.l3.go = "exit";
					}
					if(NPChar.EncType == "war")
					{
						dialog.text = RandPhraseSimple("Kapitän, ich habe einen Kampf verloren und flehe Sie um Ihre Gnade an. ","Kapitän, ich bitte um Ihre Großzügigkeit. Ich verstehe, dass es keinen Grund gibt, mich wie einen Kriegsgefangenen zu behandeln, daher bitte ich Sie, mich zu verschonen. Ich gebe Ihnen mein Wort, dass ich es vermeiden werde, Sie auf See zu treffen.");
						link.l2 = LinkRandPhrase("Teste meine Geduld nicht. Du bist bereits ein glücklicher Mann, am Leben zu bleiben.",RandPhraseSimple("Ich habe meine eigenen Pläne für dich.","Ich vermute, dass du mir in Zukunft noch nützlich sein könntest."),RandPhraseSimple("Du bist mein Gefangener und ich habe alle Rechte, mit dir zu tun, was immer ich will. Deine eigene Meinung hat hier keinen Wert.","Du warst... nun, du warst Kapitän eines Kriegsschiffes und dir waren die Risiken bewusst. Versuche hier nicht, dich als Heiligen darzustellen."));
						link.l2.go = "exit";	
						if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 1)
						{
							if(sti(Items[sti(pchar.EquipedPatentId)].Nation) == sti(NPChar.nation) && FindFreeRandomOfficer() > 0)
							{
								link.l3 = "Schau, du bist ein geschickter Kämpfer und ich brauche Halsabschneider wie dich. Möchtest du mein Offizier sein?";
								link.l3.go = "free_to_officer";
							}
						}
					}
				}
				attrLoc = Sea_FindNearColony();
				if (attrLoc != "none") 
				{
					link.l4 = "Wir sind nicht weit von "+GetConvertStr(attrLoc+" Stadt","LocLables.txt")+". Und ich könnte dich hier gehen lassen.";
					link.l4.go = "free_withoutFee";
				}
				else
				{
					if(NPChar.EncType == "trade" || NPChar.EncType == "pirate")
					{
						link.l4 = "Geh zum Bootsmann, sag ihm, er soll dir ein Schließfach geben. Du kannst im nächsten Hafen an Land gehen.";
						link.l4.go = "free_withoutFee_4";			
					}	
					else
					{
						link.l4 = "Verdammt mit dir! Geh zum Bootsmann, sag ihm, er soll dir ein Schließfach geben. Du kannst im nächsten Hafen an Land gehen. Und denk daran, dass unser nächstes Treffen das letzte sein wird.";
						link.l4.go = "free_withoutFee_4";
					}
				}				
				link.l5 = "Sie haben einen Befehl ignoriert, Ihre Segel zu senken und haben mit Gewalt Widerstand geleistet. Dafür werden Sie gehängt werden. Der Bootsmann hat bereits meine Befehle erhalten.";
				link.l5.go = "PunishmentAction";
				NextDiag.TempNode = "second time"; 
			}	
		break;
		
		case "offender":
			dialog.text = "Verbrecher? Machst du Witze,"+GetAddress_Form(NPChar)+"!";
			link.l1 = "Kein Scherz. Du bist ein Pirat.";
			link.l1.go = "exit";
		break;
		
		case "free_to_officer":
			if ((GetSummonSkillFromName(pchar, "Leadership") + 20) <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = "Unter Ihrem Kommando dienen? Ich würde lieber die Haie füttern!";
				link.l1 = "Halte deine Zunge im Zaum oder du wirst sie füttern.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Um dein Offizier zu sein, "+GetAddress_Form(NPChar)+"? Ich stimme zu. Ich kenne meinen Job und ich habe nichts zu verlieren.";
				link.l1 = "Abgemacht! Geh und mach deine Arbeit.";
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "Warte ein bisschen, ich habe meine Meinung geändert.";
				link.l2.go = "exit";
			}
		break;

		case "free_to_officer_trader":
			if (GetSummonSkillFromName(pchar, "Leadership") <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = LinkRandPhrase("Es ist ein verlockendes Angebot... aber ich muss es ablehnen. Aus Prinzip.","Es tut mir leid, aber nach dem, was du mit meinen Freunden gemacht hast... Es ist unmöglich.","Nein, Kapitän. Nach all diesem Schrecken kann ich diesen Job nicht mehr machen. Ich habe ein Gelübde abgelegt, dass, wenn die Heilige Jungfrau meine Gebete erhören und mir die Freiheit schenken würde, ich nicht mehr segeln werde.");
				link.l1 = "Es ist deine Wahl. Ich werde nicht hartnäckig sein.";	
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Warum nicht? Ich bin ein schlechter Kapitän, habe mein Schiff verloren und an Land ist nichts mehr für mich übrig. Außer Rechnungen und Schulden...";
				link.l1 = "Abgemacht! Geh zum Bootsmann und hol dir deine Zuteilungen. Ich werde dir später eine Position auf meinem Schiff geben.";	
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "Warte mal, ich habe meine Meinung geändert.";
				link.l2.go = "exit";
			}
		break;
		
		case "free_to_officer_Hire":
            NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
            NPChar.greeting = "Gr_Officer";
            NPChar.loyality = 5 + rand(10);
		    if (sti(NPChar.reputation) > 41)
		    {
		        NPChar.alignment = "good";
		    }
		    else
		    {
		        NPChar.alignment = "bad";
		    }
            ReleasePrisoner(NPChar); // освободили пленника
            DeleteAttribute(NPChar, "LifeDay") // постоянный
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			// тут трем накопивщиеся сабли и корабли 290704 BOAL -->
			DeleteAttribute(Npchar, "Ship");
			Npchar.Ship.Type = SHIP_NOTUSED;
            DeleteAttribute(Npchar, "Fellows"); // его офицеры
            Npchar.Fellows.Passengers.id0 = Npchar.index; // свой пассажир

			Npchar.Fellows.Passengers.boatswain = "-1";
			Npchar.Fellows.Passengers.navigator = "-1";
			Npchar.Fellows.Passengers.doctor = "-1";
			Npchar.Fellows.Passengers.cannoner = "-1";
			Npchar.Fellows.Passengers.treasurer = "-1";
			Npchar.Fellows.Passengers.carpenter = "-1";
            
			if(CheckAttribute(NPChar,"Hold_GenQuest")) DeleteAttribute(NPChar, "Hold_GenQuest");
			
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			DialogExit();
        break;
				
		case "Slave_1":
			dialog.text = "Aber "+GetAddress_Form(NPChar)+", das kannst du nicht tun! Ich habe mich ergeben.";
            link.l1 = "Halt den Mund! ... Fessel ihn.";
			link.l1.go = "Slave_2";
			link.l99 = "In Ordnung. Bleib hier, bis ich entscheide...";
			link.l99.go = "exit";
		break;
		
		case "Slave_2":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
            if (rand(5) == 1)
            {
    			dialog.text = "Nie im Leben! Ich würde mich lieber umbringen, als ein Sklave zu werden!";
                link.l1 = "Hör auf damit! Das ist ein Befehl!... Bootsmann! Räum die Ladung auf...";
    			link.l1.go = "free_in_sea_4";
			}			
			else
			{
                if (rand(1) == 1)
                {
                    if (GetPrisonerQty() > 1)
                    {
                        dialog.text = "Metzger! Jungs, schließt euch mir an, wir haben nichts zu verlieren!";
                        link.l1 = "Falsche Wahl, Damen. Ich kümmere mich selbst und sehr schnell um Meutereien...";
            			link.l1.go = "free_in_sea_battle_all";
                    }
					else
					{
						dialog.text = "Auf keinen Fall! Ich sterbe lieber im Kampf!";
						link.l1 = "Wie du wünschst...";
						link.l1.go = "free_in_sea_battle_1";
					}	
    			}
    			else
    			{
					dialog.text = "Oh, ich stimme zu. Ich habe keine Wahl.";
                    link.l1 = "Prächtig. Es ist besser, ein atmender Sklave zu sein, als ein toter Held.";
        			link.l1.go = "Slave_3";				
    			}			
			}
		break;

		case "Slave_3":
            ReleasePrisoner(NPChar); //  пленника в рабы
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", -6);
        	DialogExit();
        	AddCharacterGoodsSimple(pchar, GOOD_SLAVES, 1);
        break;

		case "free_withoutFee":
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+", bist du wirklich so nett und lässt mich ohne Lösegeld frei?";
            link.l1 = "Ja, das bin ich. Du bist jetzt frei,"+GetFullName(NPChar);
			link.l1.go = "free_withoutFee_2";
			link.l99 = "Hm... Du hast einen Punkt! Ich brauche mehr Zeit zum Entscheiden.";
			link.l99.go = "exit";
		break;

		case "free_withoutFee_2":
			dialog.text = "Danke, "+GetFullName(PChar)+"! Ich werde für dich beten.";
            link.l1 = "Geh jetzt, und versuche am Leben zu bleiben, sonst wird meine Großzügigkeit umsonst sein.";
			link.l1.go = "free_withoutFee_3";
			OfficersReaction("good");
		break;
		
		case "free_withoutFee_3":
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", 2);
        	DialogExit();
        break;	

		case "free_withoutFee_4":	
			switch(NPChar.EncType)
			{
				case "pirate":
					dialog.text = RandPhraseSimple("Danke, Kapitän. Ich werde Ihre Freundlichkeit nie vergessen. Ich werde diesen Job verlassen und kleine Boote in friedlichen Häfen reparieren. Das kann ich tun.","Danke, Kapitän! Ich schwöre, ich werde diesen undankbaren Beruf aufgeben und Fischer werden.");
					link.l1 = "Wenn du ehrlich bist, dann wünsche ich dir Glück, und wenn nicht, dann bete, mich nie wieder zu treffen...";	
				break;
				case "trade":
					dialog.text = "Weiß gar nicht, wie ich Ihnen danken soll, Kapitän. Ich hatte meine Hoffnung schon verloren. Ich werde jedem von Ihrer Güte erzählen. Ich gebe Ihnen mein Wort, dass ich eine Kerze für Sie anzünden werde! Lassen Sie mich nur zu einer Kirche kommen.";
					link.l1 = "Auf Wiedersehen. Und versuch das nächste Mal gar nicht erst zu widerstehen. Schieß auf mich und das wird ein Todesurteil für dich und deine Mannschaft sein.";
				break;
				case "war":
					dialog.text = "Mein Dank, Kapitän. Ich werde für dich beten.";
					link.l1 = "Viel Glück, und vergiss nicht, wenn du beschließt, mich zu jagen, wird es dein Ende sein.";
				break;
			}
			link.l1.go = "free_withoutFee_3";
		break;
		
		case "free_in_sea_battle_1":
            ReleasePrisoner(NPChar); // освободили пленника        	
        	LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
            LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, LAI_GROUP_TmpEnemy);
            LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, "Prisoner", LAI_GROUP_NEITRAL);
        	DialogExit();
        break;		

		case "free_in_sea_battle_all":
			//ugeen --> привет Сиварду !!! после релиза пленников кол-во пассажиров уменьшается и цикл нихрена дальше не срабатывал
			for(int j = GetPassengersQuantity(pchar) - 1; j > -1; j--)
            {
                cn = GetPassenger(pchar, j);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if (CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                        	ReleasePrisoner(offref); // освободили пленника
							LAi_SetWarriorType(offref);
							LAi_warrior_DialogEnable(offref, false);
                            LAi_group_MoveCharacter(offref, LAI_GROUP_TmpEnemy);
                        }
                    }
                }
            }
            LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
			LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
        	DialogExit();
        break;
		
		case "free_in_sea_4":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";
	        LAi_KillCharacter(NPChar);
        	DialogExit();
        break;

		case "PunishmentAction":
			dialog.text = "Aber "+GetAddress_Form(NPChar)+", das kannst du nicht tun! Ich habe mich ergeben.";
			link.l1 = "Nur nachdem deine Männer weg waren. Du hast sie verraten... Bootsmann! Nehmt ihn.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "Nun... Ich brauche Zeit, um darüber nachzudenken. Bleib hier.";
			link.l2.go = "exit";
        break;

		case "PunishmentAction1":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			AddCharacterExpToSkill(Pchar, "Leadership", -150);
			if (rand(1) == 1)
            {
                if (GetPrisonerQty() > 1)
                {
                    dialog.text = "Metzger! Jungs, wir haben nichts zu verlieren!";
                    link.l1 = "Falsche Wahl, Damen. Meutereien handhabe ich selbst und auf sehr schnelle Weise...";
					link.l1.go = "free_in_sea_battle_all";
                }
				else
				{
					dialog.text = "Keine Chance! Ich sterbe lieber im Kampf!";
					link.l1 = "Wie du wünschst...";
					link.l1.go = "free_in_sea_battle_1";
				}	
    		}
			else
    		{
				dialog.text = "Gib mir zumindest etwas Zeit zum Beten...";
                link.l1 = "Bete, wenn du willst.";
        		link.l1.go = "PunishmentAction2";				
    		}						
		break;
		
		case "PunishmentAction2":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";		
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
		break;
		
		case "free_tip_off":
			dialog.text = "Ich habe interessante Informationen, die für einen Mann wie Sie nützlich sein könnten. Aber ich brauche Ihre Garantie, dass ich im Austausch meine Freiheit bekomme.";
			link.l1 = "Wie kann ich Ihnen meine Garantien geben, wenn ich Ihren Vorschlag nicht einmal kenne? Ich bezweifle, dass Ihre Informationen mir überhaupt etwas bringen werden.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Ich kann Ihnen nur mein Wort geben.";
			link.l2.go = "free_tip_off_1";
		break;
		
		case "free_tip_off_0":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			DeleteAttribute(NPChar, "Hold_GenQuest");
			DialogExit();
		break;
		
		case "free_tip_off_1":
			switch(NPChar.EncType)
			{
				case "trade":
					sTmp = "He proposed me a freight but this guy was too greedy and I rejected the offer.";  
				break;
				case "war":
					sTmp = "I have escorted him a few times as a commander of a convoy.";
				break;
				case "pirate":
					sTmp = "I had an idea to rob him once but I have never had a single chance to do that.";
				break;
			}
			dialog.text = "Gut. Das reicht mir. Jetzt direkt zum Geschäft, in "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.City+"Hallo, Freund.")+" lebt ein reicher Kaufmann "+NPChar.Hold_GenQuest.Name+". "+"Er hat sein Vermögen auf seinem Schiff gemacht '"+NPChar.Hold_GenQuest.ShipName+" verkaufen "+GetStrSmallRegister(XI_ConvertString(Goods[sti(NPChar.Hold_GenQuest.Goods)].Name+"Akk"))+" mit Route : "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.FromCity)+" - "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.ToCity)+". "+"Wenn er zu viel Fracht hat, bezahlt er für eine Eskorte."+sTmp+" Ich bin sicher, dass diese Informationen für dich wertvoller sind als das Leben eines einzelnen Mannes.";
			link.l1 = "Bezweifle, dass diese Informationen für mich nützlich sein können. Ich werde friedliche Händler nicht jagen.";	
			link.l1.go = "free_tip_off_0";
			link.l2 = "Nicht sicher, ob diese Information für mich von Nutzen sein wird, aber ich habe Ihnen mein Wort gegeben. Der Bootsmann wird Sie bei meiner Mannschaft unterbringen und Sie im nächsten Hafen rauslassen.";
			link.l2.go = "free_tip_off_2";			
		break;
		
		case "free_tip_off_2":
			dialog.text = "Mein Dank, Kapitän! Ich hatte keinen Zweifel an Ihrer Ehrlichkeit!";
			link.l1 = RandPhraseSimple(RandPhraseSimple("Ich wünschte, ich könnte dasselbe über dich sagen","Es tut mir leid, aber ich kann das Gleiche über dich nicht sagen."),RandPhraseSimple("Geh und denk daran, dass ich das nächste Mal nicht so großzügig sein werde.","Geh und bleib mir aus dem Weg. Das nächste Mal werde ich dir nicht so leicht glauben."));
			link.l1.go = "free_tip_off_3";
		break;
		
		case "free_tip_off_3":
			pchar.GenQuest.Hold_GenQuest.Goods 			= NPChar.Hold_GenQuest.Goods;			
			pchar.GenQuest.Hold_GenQuest.Nation 		= NPChar.Hold_GenQuest.Nation; 
			pchar.GenQuest.Hold_GenQuest.Name 			= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.ToCity 		= NPChar.Hold_GenQuest.ToCity;
			pchar.GenQuest.Hold_GenQuest.FromCity 		= NPChar.Hold_GenQuest.FromCity; 
			pchar.GenQuest.Hold_GenQuest.ShipName 		= NPChar.Hold_GenQuest.ShipName;				
			pchar.GenQuest.Hold_GenQuest.City 			= NPChar.Hold_GenQuest.City;
			pchar.GenQuest.Hold_GenQuest.CapName		= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.Island			= GetArealByCityName(pchar.GenQuest.Hold_GenQuest.City); 
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern 	= true;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "1");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Acc"))); 
			AddQuestUserData("HoldQuest", "sCityFrom", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.FromCity));
			AddQuestUserData("HoldQuest", "sCityTo", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.ToCity));
			AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);
			
			SetFunctionTimerCondition("Hold_GenQuest_SetMerchant_pre", 0, 0, 1+rand(2), false);
			SetFunctionTimerCondition("Hold_GenQuest_MerchantOver", 0, 0, 30, false);
			
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();			
		break;
	
		case "free_buyout":
			dialog.text = "Und ich habe einen Vorschlag für dich. In "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.City+"Stimme")+" lebt mein Freund, "+NPChar.Hold_GenQuest.Name+" ist sein Name. Wir hatten einmal ein Geschäft zusammen."+"Finden Sie ihn dort. Ich bin sicher, dass er Ihnen eine große Summe zahlen wird. Er schuldet mir und ich werde selbst mit ihm fertig werden.";
			link.l1 = "Dein Freund, hm? Lass ihn uns sehen.";	
			link.l1.go = "free_buyout1";
			link.l2 = "Warum sollte ich nach deinem Freund suchen, wenn ich im allerersten Hafen Lösegeld bekommen kann?";
			link.l2.go = "free_tip_off_0";
		break;
	
		case "free_buyout1":
			LAi_CharacterDisableDialog(NPChar);
			
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.CapId		= NPChar.Id;
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "6");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc")); 
			AddQuestUserData("HoldQuest", "sNameChar", NPChar.Hold_GenQuest.Name);
			DialogExit();
		break;

		case "free_by_hoard":
			dialog.text = "Eigentlich kenne ich einen Mann, der einen feinen Schatz hat, aber er hat nicht den Mut, ihn zu nutzen.";
			link.l1 = "Was meinst du?";
			link.l1.go = "free_by_hoard1";
			link.l2 = "Verschone mich mit deinen Geschichten. Du solltest dir lieber Sorgen um deine Seele machen.";
			link.l2.go = "free_tip_off_0";
		break;
		
		case "free_by_hoard1":
			dialog.text = "Ich erzähle Ihnen die Geschichte, die zu großen Schätzen führt. Ich brauche Ihr Wort dafür, dass Sie mich im nächsten Hafen gehen lassen.";
			link.l1 = "Ich werde selbst entscheiden, wann und was ich mit dir anfange. Deine 'Geschichten' werden keinen Unterschied machen.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Ich höre zu. Sie haben mein Wort.";
			link.l2.go = "free_by_hoard2";
		break;
		
		case "free_by_hoard2":
			dialog.text = "Ich vertraue so einem ehrenhaften "+GetSexPhrase("Mann","Frau")+". Leute wie Sie halten immer ihr Wort! Es spielt keine Rolle, ob die ganze Welt brennt, Sie werden Ihr Wort halten! Habe ich recht, Kapitän?";
			link.l1 = "Erzähl mir deine Geschichte oder ich lasse dich sofort gehen... über Bord und kopflos.";
			link.l1.go = "free_by_hoard4";
		break;
		
		case "free_by_hoard4":
			dialog.text = "Ha-ha, netter Witz... Jetzt hör zu. Es gibt einen Kumpel in "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.City+"Voc")+" genannt "+NPChar.Hold_GenQuest.Name+", er war in seiner Jugend ein wirklich rücksichtsloser Kerl. Er hatte in jenen Tagen viele 'Geschäfte'..."+"Also erzählte er mir einmal in der Taverne, dass er Mitglied war von "+GetName(NAMETYPE_VIP,NPChar.Hold_GenQuest.PirateName,NAME_ACC)+" Bande und er sah, wie diese Piraten einen Schatz vergruben."+"Er ließ fünf seiner Kameraden wegen dieses Schatzes töten... Es gab Gerüchte, dass er gefasst und gehängt wurde, aber die Wahrheit ist, dass er sich aus dem Geschäft zurückgezogen hat und eine Familie gegründet hat. Er erinnerte sich an den Ort des Schatzes, hatte sogar eine Karte gezeichnet. Er bot mir an, ihn bei der Suche nach dem Schatz zu begleiten. Ein abergläubischer Mann ist er, der Schatz war in Blut getaucht, also fürchtet er sich, dort alleine hinzugehen. Ich gebe zu, auch ich habe mich aus dem gleichen Grund nicht gewagt."+"Er war bereit, die Karte zu verkaufen, aber warum sollte ich sie brauchen, wenn ich sowieso nie dorthin gehen werde...\nDas ist meine Geschichte... Ich denke, dass ein so mutiger Mann wie du sie nützlich finden wird, und die Karte ist übrigens ziemlich billig.";
			link.l1 = "Und schlagen Sie wirklich vor, dass ich das kaufen soll? Ihre Geschichte ist nicht real, also breche ich unseren Deal.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Interessante Geschichte, obwohl ich nicht wirklich daran glaube. Aber du hast mein Wort, geh und sag dem Bootsmann, er soll dir ein Schließfach geben. Du bist frei.";
			link.l2.go = "free_by_hoard5";
		break;
		
		case "free_by_hoard5":
			dialog.text = "Mein Dank, Kapitän! Jetzt sehe ich den Preis für das Wort eines "+GetSexPhrase("Herr!","Frau!");
			link.l1 = "Geh und halt dich aus meinem Weg. Das nächste Mal lasse ich dich nicht so leicht davonkommen.");
			link.l1.go = "free_by_hoard6";
		break;
		
		case "free_by_hoard6":
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.PirateName	= NPChar.Hold_GenQuest.PirateName;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1) + 2;
			pchar.GenQuest.Hold_GenQuest.Sum		= 10000 + rand(10000);
			pchar.GenQuest.Hold_GenQuest.Treasure	= rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "12");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc")); 
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();					
		break;
		
		case "free_in_sea":
			dialog.text = "Aber, "+GetAddress_Form(NPChar)+", wir sind auf hoher See! Es ist, als würdest du mich hinrichten!";
			link.l1 = "Das ist was du wolltest. Lebewohl. Der Bootsmann wird meinen Befehl ausführen.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "In Ordnung, ich habe mich noch nicht entschieden.";
			link.l2.go = "exit";
		break;		
		
		//--> Jason, Ложный след
		case "FalseTrace_Prisoner":
			dialog.text = "Katerine! Hat sie dich wirklich gebeten, hierher zu kommen? So ein wunderbares Mädchen...";
			link.l1 = "Lassen wir die Poesie beiseite, Kapitän, und reden wir über ernstere Dinge. Ich werde Ihnen von der aktuellen Situation erzählen und erwarte eine Antwort von Ihnen. Ihre Antwort wird Ihr Schicksal und das von Katerine bestimmen.";
			link.l1.go = "FalseTrace_Prisoner_1";
		break;
		
		case "FalseTrace_Prisoner_1":
			dialog.text = "Ich höre zu, Kapitän.";
			link.l1 = "Ich habe Eure Flöte geentert, weil Adam Rayner, der Ehemann von Katerin, mir erzählt hat, dass es viel Silber auf eurem Schiff gibt. Dieser Trick ermöglichte es ihm, eine Frau, die ihm einst gehörte und von ihm zu Euch floh, zurückzuholen.";
			link.l1.go = "FalseTrace_Prisoner_2";
		break;
		
		case "FalseTrace_Prisoner_2":
			dialog.text = "Adam? Dieser Bastard? Es war alles sein Plan! Jetzt sehe ich... Ja, ich habe Katrine vor drei Monaten geholfen zu fliehen. Solch ein armes Mädchen, du hast keine Vorstellung wie er sie behandelt hat...";
			link.l1 = "Sie war seine Frau und es war mir egal, was passiert ist, es geht mich nichts an. Ich habe einen Fehler gemacht, als ich Ihre Galeone betreten habe, aber es ist zu spät, darüber zu sprechen. Adam hat mir versprochen, für meine Hilfe zu bezahlen.";
			link.l1.go = "FalseTrace_Prisoner_3";
		break;
		
		case "FalseTrace_Prisoner_3":
			dialog.text = "Adam hat ein Versprechen gemacht? Ha-ha! Und Sie haben ihm vertraut? Kapitän, wissen Sie überhaupt, was für eine Person er ist? Er...";
			link.l1 = "Katerine hat mir schon viel über ihn erzählt und sich dabei große Mühe gegeben. Aber sein Vorschlag macht Sinn und obwohl ich keinen Grund habe, diesem Bastard zu vertrauen, erzählt er vielleicht diesmal die Wahrheit. Also kommen wir gleich zur Sache...";
			link.l1.go = "FalseTrace_Prisoner_4";
		break;
		
		case "FalseTrace_Prisoner_4":
			dialog.text = "";
			link.l1 = "Ich wollte dich den Behörden ausliefern und Adam zusammen mit Katerine übergeben "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Akz")+", dann hole dir von Adam die Informationen über das Gold von Schieläugigem Solly und segel dorthin. Aber Katerine hat mich überredet, zuerst mit dir zu sprechen, sie sagte, du könntest mir etwas Besseres und Zuverlässigeres anbieten als Adam, im Austausch für euer Leben und Freiheit.";
			link.l1.go = "FalseTrace_Prisoner_5";
		break;
		
		case "FalseTrace_Prisoner_5":
			dialog.text = "";
			link.l1 = "Deswegen stehe ich hier und rede mit dir. Ich habe fertig. Jetzt bist du dran. Denke über meine Worte und die Worte von Katerine nach und gib mir deine Ideen. Du hast nicht viel Zeit.";
			link.l1.go = "FalseTrace_Prisoner_6";
		break;
		
		case "FalseTrace_Prisoner_6":
			dialog.text = "Kapitän! Obwohl ich nicht denke, dass Sie ein guter Mann sind, haben Sie doch auf das Flehen eines armen Mädchens gehört und sind hierher gekommen. Es zeigt mir, dass Sie ehrenhaft sein können und Mitleid empfinden. Ich brauche keine Zeit, ich bin bereit, Ihnen meinen Vorschlag zu unterbreiten.";
			link.l1 = "Wirklich? Ausgezeichnet! Nun, ich höre zu.";
			link.l1.go = "FalseTrace_Prisoner_7";
		break;
		
		case "FalseTrace_Prisoner_7":
			dialog.text = "Du wirst Adam Rayner verhaften und ihn in Ketten legen. Dann bringst du mich und Katerine zu "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". Lande nicht in der Stadt, schließlich warst du es, der meine Galeone versenkt hat, setze uns alle drei ab bei "+XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen")+"\nIch würde dich auch um eine Waffe bitten. Wir werden durch den Dschungel in die Stadt gehen und ich werde dafür sorgen, dass dieser Abschaum nicht nur für seine Verbrechen, sondern auch für deine bezahlt. Er hat es verdient\nDu hast mein Wort, dass dein Name nicht auftauchen wird. Im Gegenzug gebe ich dir wahre Informationen über ein Schiff mit Gold des Feindstaates\nEs wird für dich keine große Herausforderung sein, aber es hat Zähne, du wirst eine feine Beute erlangen. Viel besser als mein Lösegeld und die 'sogenannten' Schätze des Squint-Eyed Solly. Haben wir einen Deal?";
			link.l1 = "Ich mag deinen Plan nicht. Ich denke, dass die örtlichen Behörden sofort eine Jagd auf mich organisieren werden, sobald ich die Küsten verlasse "+XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen")+". Nein, Kapitän, ich werde meinen Kopf nicht riskieren. Unser Gespräch ist vorbei.";
			link.l1.go = "FalseTrace_Prisoner_8";
			link.l2 = "Nun, es sieht so aus, als ob Katerine recht hatte. Dein Vorschlag gefällt mir. Adam Rayner wird verhaftet werden. Ich werde es sofort erledigen. Du wirst freigelassen, nachdem wir Adam verhaftet haben. Auf Wiedersehen, Kapitän!";
			link.l2.go = "FalseTrace_Prisoner_9";
		break;
		
		case "FalseTrace_Prisoner_8":
			DialogExit();
			AddQuestRecord("FalseTrace", "9");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			bQuestDisableMapEnter = false;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_Prisoner_9":
			DialogExit();
			AddQuestRecord("FalseTrace", "10");
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			AddDialogExitQuestFunction("SetCheckForGoldShip");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FalseTrace.PrisonerID = npchar.id;
			Pchar.questTemp.FalseTrace.PrisonerIDX = GetCharacterIndex(npchar.id);
		break;
		//<-- Ложный след
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "Bist du hier um zu predigen oder um Geschäfte zu machen?";
			link.l1 = "Um Geschäfte zu machen. Ich brauche deinen Partner in Verbrechen - Bertrand Pinette. Ich stecke tief in der Scheiße wegen ihm. Wo kann ich ihn finden, huh?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Warum denkst du, dass ich dir das erzählen werde?";
			link.l1 = "Dein Arsch steht auf dem Spiel. Ich werde dich nach Basse-Terre bringen, dich dem Gouverneur übergeben und eine Belohnung für die Festnahme eines Deserteurs erhalten, der die Flucht von Carlos de Milyar organisiert hat. Es ist deine Entscheidung. Entweder du verrätst mir den Aufenthaltsort von Pinette oder wir beide fahren nach Guadeloupe.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = "Also weißt du alles... Gut, ich werde dir alles erzählen, was ich über Bertrand Pinette weiß, aber du wirst mich dafür freilassen.";
			link.l1 = "Geh und erzähl mir dann. Ich werde dich in der Moskito-Bucht absetzen, genau wie das letzte Mal. Aber lüge mich an und ich werde zurückkehren und diese Plantage, die dir von Don Carlos geschenkt wurde, in Brand setzen, ich werde auch Basse-Terre von deinem Aufenthaltsort informieren, also werde ich nicht der Einzige sein, der dich jagt.";
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = "Zuerst, lande mich dort. Das wird mich sicherer fühlen lassen und ich schwöre, ich werde dir alles erzählen.";
			link.l1 = "Gut. Es ist nicht so, als würdest du irgendwohin gehen.";
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "16");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FMQG.PrisonerID = npchar.id;
			Pchar.questTemp.FMQG.PrisonerIDX = GetCharacterIndex(npchar.id);
			pchar.quest.FMQG_SailMoskitos.win_condition.l1 = "location";
			pchar.quest.FMQG_SailMoskitos.win_condition.l1.location = "Shore47";
			pchar.quest.FMQG_SailMoskitos.function = "FMQG_ArriveMoskitos";
			pchar.questTemp.FMQG = "to_moskitos";
			AddMapQuestMarkShore("Shore47", true);
			bDisableMapEnter = false; // Rebbebion, теперь можно
		break;
		
		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
	}
}
