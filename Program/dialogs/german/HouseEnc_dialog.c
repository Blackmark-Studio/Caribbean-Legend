void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;
	ref rColony;
	
	int iTest;
	
	bool  ok; // лесник . спецпеременная.

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	iTest = FindColony(NPChar.City);
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	if (Dialog.CurrentNode == "SkladMan1") Dialog.CurrentNode = "SkladMan";

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(int(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_GoOut":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			DoQuestFunctionDelay("HouseEnc_TimerGoUot", 10.0);
			pchar.questTemp.HouseEncTimer = pchar.location;
			pchar.questTemp.HouseEncTimer.Id = npchar.id;
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_close":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------------- мужик ---------------------------------
		case "HouseMan":
			NextDiag.TempNode = "HouseMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("Alarm wird in der Stadt ausgelöst. Anscheinend ist es an der Zeit, dass ich auch zu den Waffen greife...","Die Stadtwachen sind nicht zufällig hinter dir her, oder? ","Du wirst hier keinen Unterschlupf finden, aber du könntest sehr wohl mehrere Zentimeter kalten Stahls zwischen deinen Rippen finden!"),LinkRandPhrase("Was willst du hier, du "+GetSexPhrase("Schurke","Schurkin")+"?! Die Stadtwachen haben bereits deine Fährte aufgenommen, du wirst nicht weit kommen, "+GetSexPhrase("du schmutziger Pirat","du Piratenhure")+"!","Dreckiger Mörder! Wachen!!!","Ich fürchte dich nicht, du "+GetSexPhrase("Widerling","Hure")+"! Bald wirst du in unserem Fort gehängt werden, du wirst nicht weit kommen..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Ich sehe, du bist Lebensmüde...","So scheint es, es gibt tatsächlich kein friedliches Leben für die Bürger von "+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("Geh zur Hölle!","Heh, das werden die letzten Sekunden deines Lebens sein..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "Ich habe dich gewarnt. Jetzt kannst du selbst entscheiden, ob du Ärger haben willst.";
					link.l1 = "Heh!";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Was brauchst du in meinem Haus, Schuft?! Du hast zehn Sekunden, um hier raus zu kommen!";
					link.l1 = LinkRandPhrase("Heh, sieht so aus, als würden sie mich auch hier kennen!","Mein Ruhm ist mir wohl vorausgegangen...","Hmm, ich verstehe.");
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("Ich freue mich, Sie in meinem Zuhause willkommen zu heißen. Haben Sie Geschäfte mit mir?","Was kann ich für dich tun?","Hmm... Was kann ich für dich tun?","Es tut mir leid, aber wenn Sie kein Geschäft mit mir haben, stören Sie mich bitte nicht...","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Nein, ich schaue mich nur um, treffe neue Leute...","Nein, nichts Besonderes...","Nichts...","Gut, wie du sagst.",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseMan_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("Es tut mir leid, aber die Nacht ist nicht die beste Zeit für Besuche, und daher bitte ich Sie, mein Haus sofort zu verlassen!","Ich habe dir schon gesagt, es ist spät. Bitte, geh weg.","Ich möchte nicht unhöflich erscheinen, aber ich bestehe darauf, dass Sie mein Haus sofort verlassen!","Verdammt, was geht hier vor?! Wachen! Diebe!","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("In Ordnung, ich verstehe...","Ja, nur einen Moment...","In Ordnung, reg dich nur nicht so auf.","Welche Diebe?! Halt den Mund!",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "fight", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseMan_1":
			dialog.text = "Oh, erlaube mir, mich vorzustellen - "+GetFullName(npchar)+". Wir freuen uns sehr, Sie als unseren Gast zu haben. In dieser Stadt werden die Gesetze der Gastfreundschaft geehrt.";
			link.l1 = GetFullName(pchar)+", wenn es Ihnen recht ist...";
			link.l1.go = "exit_setOwner";
		break;
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Du bist "+GetSexPhrase("ein Dieb, wie ich sehe! Wachen, ergreift ihn","eine Diebin, wie ich sehe! Wachen, ergreift sie")+"!!!","Ich kann es nicht fassen! Ich habe mich für eine Sekunde abgewendet - und du tauchst einfach in meinen Besitztümern ein! Haltet den Dieb!!!","Wachen! Raub! Stoppt einen Dieb!!!");
			link.l1 = "Aaaah, Teufel!!!";
			link.l1.go = "fight";
		break;
		// --------------------------------- баба ---------------------------------
		case "HouseWoman":
			NextDiag.TempNode = "HouseWoman";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("Ich warne Sie, mein Mann wird bald zurückkehren! Sie sollten jetzt besser mein Haus verlassen!","Ich glaube nicht, dass du es schaffst zu entkommen! Und sei dir bewusst, dass mein Mann bald nach Hause kommt!","Mein Mann wird bald nach Hause kommen! Sie müssen sofort gehen!"),LinkRandPhrase("Schade, dass mein Mann nicht zu Hause ist... Raus! Jetzt!!!","Dreckiger Mörder, verlasse sofort mein Haus! Wachen!",""+GetSexPhrase("Was für ein Schuft","Was für eine Drecksau")+"... Bald wird mein Mann zurückkehren, und er wird sehen, welche Farbe dein Blut hat!"));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Oh, dein Ehemann... oooooh...Ich zittere...","Heh... Weißt du, Mädel, dein Mann ist auch nur ein Mann... du würdest ihn doch nicht tot vor deinen Füßen haben wollen, oder?"),RandPhraseSimple("Halt den Mund, Weib, bevor ich dich aufschlitze...","Ich bleibe hier so lange ich will. Und du hältst besser den Mund, wenn du weißt, was gut für dich ist..."));
				link.l1.go = "exit_setOwner";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "Ich habe dich gewarnt. Verschwinde oder du wirst es bereuen!";
					link.l1 = "Was für eine dumme Dirne...";
					link.l1.go = "exit";
				}
				else
				{					
					dialog.text = "Was machst du in meinem Haus, "+GetSexPhrase("du Schurke","du Schurkin")+"?! Wenn du nicht in zehn Sekunden verschwunden bist, rufe ich die Wachen!";
					link.l1 = "Welch eine dumme Dirne...";
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("Ich freue mich, Sie in unserem Haus zu sehen. Mein Name ist "+GetFullName(npchar)+". Was kann ich für Sie tun?","Bist du noch hier?","Hm, entschuldigen Sie, aber denken Sie nicht, dass es Zeit für Sie ist zu gehen?","Ich würde Euch bitten, unsere Gastfreundschaft nicht zu missbrauchen.","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat(GetFullName(pchar)+" zu Ihren Diensten. Ich kam hierher ohne besonderen Grund, nur um Bekanntschaft zu machen.","Immer noch hier.","Nun, ich weiß nicht...","Gut.",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseWoman_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("Oh mein Gott, warum brechen Sie zu solch einer Zeit in mein Haus ein! Sie haben mich wirklich erschreckt... Bitte, kommen Sie morgen zu Besuch!","Bitte, verlassen Sie unser Haus!"+GetSexPhrase("","Ich bin eine verheiratete Frau!")+"","Ich bitte Sie zum letzten Mal, unser Zuhause zu verlassen!","Aber was geht hier vor?!","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Hab keine Angst, ich werde dir nicht wehtun.","In Ordnung, reg dich nur nicht so auf.","Ich gehe weg.","Was ist los?",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "HouseWoman_2", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseWoman_1":
			dialog.text = "Wir haben immer gerne Gäste. Bleiben Sie nur nicht zu lange hier,"+GetSexPhrase(", da ich eine verheiratete Frau bin..."," da ich viel zu tun habe...")+"";
			link.l1 = "Oh, ja, sicher...";
			link.l1.go = "exit_setOwner";
		break;
		case "Woman_FackYou":
			dialog.text = "So ist das also? Ich habe dich als meinen Gast begrüßt, und du durchwühlst unsere Truhen?! Wachen!";
			link.l1 = "Halt die Klappe, Schlampe!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(int(npchar.nation), RELATION_ENEMY);
		break;
		case "HouseWoman_2":
			dialog.text = "Ich habe Sie auf freundliche Weise gebeten, unser Haus zu verlassen, aber Sie wollten einfach nicht zuhören! Genug! Hilfe! Wachen!";
			link.l1 = "Halt den Mund, du törichte Frau! Bist du verrückt?!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(int(npchar.nation), RELATION_ENEMY);
		break; 
		//--------------------------------- завсклад ---------------------------------		
		case "SkladMan":
			NextDiag.TempNode = "SkladMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Alarm wird in der Stadt ausgelöst. Anscheinend ist es an der Zeit, dass auch ich zu den Waffen greife...","Verfolgen dich zufällig nicht die Stadtwachen?","Du wirst hier keinen Schutz finden, aber du könntest durchaus einige Zentimeter kalten Stahls zwischen deinen Rippen finden!"),LinkRandPhrase("Was willst du hier, du "+GetSexPhrase("Schurke","Schurkin")+"?! Die Stadtwachen haben bereits deine Fährte aufgenommen, du wirst nicht weit kommen, "+GetSexPhrase("schmutziger Pirat","du Piratenhure")+"!","Dreckiger Mörder! Wachen!!!","Ich fürchte dich nicht, du "+GetSexPhrase("Widerling","Hure")+"! Bald wirst du in unserer Festung gehängt werden, du wirst nicht weit kommen..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Ich sehe, du bist Lebensmüde...","So scheint es, es gibt tatsächlich kein friedliches Leben für die Bürger von "+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("Geh zur Hölle!","Heh, das werden die letzten Sekunden deines Lebens sein..."));
				link.l1.go = NPCharRepPhrase(pchar, "exit_setOwner", "fight");
				break;
			}
			//открывание двери верфи по квесту промышленного шпионажа
			if (CheckAttribute(pchar, "questTemp.different.ShipyardsMap") && pchar.questTemp.different.ShipyardsMap == "toTarget" && npchar.city == pchar.questTemp.different.ShipyardsMap.city && locations[reload_cur_location_index].type == "shipyard")
			{
				link.l2 = "Hör zu, Kamerad, ich möchte offen mit dir reden.";
				link.l2.go = "ShipyardsMap_1";
				pchar.questTemp.different.ShipyardsMap = "toResult";					
			}
			// ugeen --> склад товаров для ГГ				
			if(CheckAttribute(NPChar,"Storage"))
			{
				if(!CheckAttribute(NPChar, "Storage.Speak"))
				{
					link.l7 = DLG_Convert("storageRent", "Dialogs.txt");
					link.l7.go = "storage_rent";
				}
				else
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "Bring mich zum Lagerhaus. Ich möchte sehen, in welchem Zustand es ist.";
						link.l7.go = "storage_0";
						link.l8 = "Ich habe beschlossen, das Lagerhaus zu räumen. Ich brauche es nicht mehr.";
						link.l8.go = "storage_04";
					}
					else
					{
						link.l7 = "Sie haben ein Lagerhaus erwähnt. Ist es noch frei?";
						link.l7.go = "storage_01";
					}
				}		
			// <-- ugeen
			}		
			dialog.text = NPCStringReactionRepeat("Willkommen! Mein Name ist "+GetFullName(npchar)+". Hier bin ich der Boss, also denk nicht einmal daran, etwas mitzunehmen...","Benehmen Sie sich anständig und behalten Sie im Kopf, dass ich ein Auge auf Sie habe.","Solange du nicht in die Truhen schaust, darfst du hier bleiben. Ich bin sowieso alleine gelangweilt...",RandPhraseSimple("Oh je, mir ist so langweilig!","Verdammt, was soll ich tun? Hier zu sein ist so langweilig!"),"block",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("In Ordnung, mach dir keine Sorgen.","Sicher!","Ich sehe...","Ja, das klingt nach einem Problem.",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
		break;
		
		//--------------------------------- Аренда склада ---------------------------------
		case "storage_rent":
			NPChar.Storage.Speak = true;
			dialog.text = "Wir haben ein Gebiet, das als Lager geeignet ist. Möchten Sie es für einen vernünftigen Preis mieten? Stellen Sie sich vor, Sie hätten Ihr eigenes Lager, um wertvolle Fracht zu lagern...";
			link.l1 = "Ein Lagerhaus, sagst du? Ja, in der Tat verlockend... Ist es groß genug? Und wie viel verlangst du für die Miete?";
			link.l1.go = "storage_rent1";
		break;
		
		case "storage_rent1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Es ist ziemlich geräumig, selbst für ein Hafenlager, es kann, lassen Sie uns sehen... 50000 Zentner Ladung halten. Für "+FindRussianMoneyString(int(NPChar.MoneyForStorage))+"  pro Monat kann ich die sichere Aufbewahrung Ihrer Waren gewährleisten. "+"Das beinhaltet den Schutz mit meinen Männern, Schutz vor Wasserschäden und den Kampf gegen die Ratten. Was sagen Sie dazu? Oh, und Vertraulichkeit gillt ja ohnehin, ohne mehr darauf einzugehen.";
			link.l1 = "Wird gemacht. Kann ich mal einen Blick darauf werfen?";	
			link.l1.go = "storage_rent2";
			link.l2 = "Das ist zu viel. Und ich wette, es ist überschwemmt und von Ratten befallen.";
			link.l2.go = "storage_rent3";		
		break;
		
		case "storage_rent2":
			dialog.text = "Sicher, sicher. Aber... Ich brauche eine Monatszahlung im Voraus. ";
			if(int(pchar.money) >= int(NPChar.MoneyForStorage))
			{
				link.l1 = "Du bist... ziemlich merkantil, muss ich sagen. Hier ist dein Geld ... Ich werde diesen Schuppen mieten.";
				link.l1.go = "storage_11";
			}
			else
			{	
				link.l1 = "Du bist... ziemlich geschäftstüchtig, muss ich sagen. Gut, ich hole das Geld.";
				link.l1.go = "exit";
			}	
		break;
		
		case "storage_rent3":
			dialog.text = "Wie du wünschst. Wenn du deine Meinung änderst, lass es mich einfach wissen. Und denk daran, dass so ein schönes Lagerhaus unwahrscheinlich lange leer bleibt...";
			link.l1 = "Kein Problem. Ich werde dich wissen lassen, wenn ich es brauche.";
			link.l1.go = "exit";
		break;
		
		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * int(NPChar.Storage.MoneyForStorage);
			if(int(NPChar.MoneyForStorage) > 0)
			{
				dialog.text = "Und für die Miete, schuldest du mir immer noch  "+FindRussianMoneyString(int(NPChar.MoneyForStorage))+".";
				if(int(pchar.money) >= int(NPChar.MoneyForStorage))
				{
					link.l1 = "In Ordnung, ich werde jetzt die Miete bezahlen.";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "Ich komme später wieder.";
					link.l1.go = "exit";
				}
			}		
			else
			{ // лесник . если забыл с собой корабль то никак.
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		        if (int(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{	
				dialog.text = "Geh voran.";
				link.l1 = "Danke.";
				link.l1.go = "storage_2";
				}
				else
				{
                dialog.text = RandPhraseSimple("Kapitän, wo ist Ihr Schiff? Wie planen Sie, die Ladung zu bewegen?","Ich sehe Ihr Schiff nicht im Hafen liegen. Wie genau wollen Sie es beladen?");
                link.l1 = RandPhraseSimple("Ach.. Das habe ich völlig vergessen!","Verdammt, das stimmt!");
			    link.l1.go = "exit";
				break;
                }			
			}
			link.l2 = "Nein, ich habe meine Meinung geändert.";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			dialog.text = "Nein, "+GetSexPhrase("Herr","meine Dame")+", immer noch frei und wartet auf Sie. Ich wusste, dass Sie mein Angebot am Ende nicht ablehnen würden.";
			link.l1 = "Sehr gut. Ich werde es mieten.";
			link.l1.go = "storage_1";
			link.l2 = "Nein, es kam mir nur gerade in den Sinn...";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Wie du dich erinnern solltest, brauche ich eine Monatszahlung im Voraus.";
			if(int(pchar.money) >= int(NPChar.MoneyForStorage))
			{
				link.l1 = "Natürlich erinnere ich mich. Hier, bitte.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "Verdammt. Gut, ich werde das Geld holen.";
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -int(NPChar.MoneyForStorage));
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			Achievment_Set("ach_67"); // ugeen 2016
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(int(rColony.StoreNum));
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(int(rColony.StoreNum));
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -int(NPChar.MoneyForStorage));
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(int(rColony.StoreNum));
		break;		

		case "storage_04":
			dialog.text = "Sie gehen schon? Was für eine Schande, das ist wirklich ein ausgezeichneter Ort zu großartigen Bedingungen. Ich versichere Ihnen, dass Sie nirgendwo in der Karibik ein solches Angebot bekommen werden.";
			link.l1 = "Ich habe gesagt, ich räume es. Oder schlägst du mir vor, für die Lagerung von Luft zu bezahlen? Du kannst nach einem anderen Halter suchen.";
			link.l1.go = "storage_4";
			link.l2 = "Nirgendwo in der Karibik, sagst du? In Ordnung, ich behalte es für eine Weile, dann. Aber die Mietkosten, muss ich sagen, sind ein bisschen zu hoch.";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * int(NPChar.Storage.MoneyForStorage);
			if(int(NPChar.MoneyForStorage) > 0)
			{
				dialog.text = "Und für die Miete, du schuldest mir immer noch "+FindRussianMoneyString(int(NPChar.MoneyForStorage))+".";
				if(int(pchar.money) >= int(NPChar.MoneyForStorage))
				{
					link.l1 = "Gut.";
					link.l1.go = "storage_5";
				}
			}
			else
			{ // лесник . если нет корабля то и товар не забрать
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		        if (int(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{	
				dialog.text = "Sammle deine Waren und ich werde das Lagerhaus schließen.";
				link.l1 = "Gut.";
				link.l1.go = "storage_6";
				}
				else
				{
                dialog.text = RandPhraseSimple("Kapitän, wo ist Ihr Schiff? Wie planen Sie, die Ladung zu bewegen?","Ich sehe nicht, dass Ihr Schiff im Hafen liegt. Wie genau gedenken Sie es zu beladen?");
                link.l1 = RandPhraseSimple("Oh.. Ich habe das total vergessen!","Verdammt, das stimmt!");
			    link.l1.go = "exit";
				break;
                }				
			}
		break;
		
		case "storage_5":
			LeaveStorage(NPChar, rColony, int(NPChar.MoneyForStorage));
			DialogExit();
		break;
		
		case "storage_6":
			LeaveStorage(NPChar, rColony);
			DialogExit();
		break;

		//--------------------------------- Аренда склада ---------------------------------
		
		case "ShipyardsMap_1":
			dialog.text = "Heh! Also gut, lass uns reden.";
			link.l1 = "Ich muss nachts zur Werft, wenn niemand da ist.";
			link.l1.go = "ShipyardsMap_2";
		break;
		case "ShipyardsMap_2":
			if (int(pchar.questTemp.different.ShipyardsMap.skladFight))
			{
				dialog.text = "Schau dir das an! Hey, Wachen, wir haben hier einen Dieb!!!";
				link.l1 = "Welcher Dieb? Ich wollte nur reden!";
				link.l1.go = "fight";
				AddCharacterExpToSkill(pchar, "FencingL", 5);
				AddCharacterExpToSkill(pchar, "FencingS", 5);
				AddCharacterExpToSkill(pchar, "FencingH", 5);
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
				dialog.text = "Wahnsinn! Schau dich mal an, "+GetSexPhrase("Kumpel","Fräulein")+". Mit einer solchen Bitte ins Schiffswerftlager zu kommen!";
				link.l1 = "Ich muss zum Schiffswerft selbst. Dein Lagerhaus ist mir völlig egal.";
				link.l1.go = "ShipyardsMap_3";
				AddCharacterExpToSkill(pchar, "Fortune", 10);
			}
		break;
		case "ShipyardsMap_3":
			dialog.text = "Aber warum brauchst du es?";
			link.l1 = "Es gibt einen Bedarf. Und ich bin bereit dafür zu zahlen...";
			link.l1.go = "ShipyardsMap_4";
		break;
		case "ShipyardsMap_4":
			dialog.text = "Hmm, das ist besser... Gut! Gib mir "+FindRussianMoneyString(int(pchar.questTemp.different.ShipyardsMap.sklad)*1000)+", und ich werde die Tür zur Werft während des folgenden Tages offen lassen.";
			link.l1 = "Das ist zu teuer. Dann muss ich wohl darauf verzichten...";
			link.l1.go = "exit";
			if (int(pchar.money) >= (int(pchar.questTemp.different.ShipyardsMap.sklad)*1000))
			{
				link.l2 = "In Ordnung, ich stimme zu. Nimm dein Geld und tue es, wie wir es vereinbart haben.";
				link.l2.go = "ShipyardsMap_5";
			}
		break;
		case "ShipyardsMap_5":
			dialog.text = "Mach dir keine Sorgen, es wird erledigt werden.";
			link.l1 = "Ich hoffe es...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -int(pchar.questTemp.different.ShipyardsMap.sklad)*1000);
			AddQuestRecord("ShipyardsMap", "5");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			//снимаем close_for_night
			string  sName;
			int location_index = FindLocation(npchar.city + "_town");
    		makearef(arRld, Locations[location_index].reload);
    		Qty = GetAttributesNum(arRld);
    		for (int a=0; a<Qty; a++)
    		{
    			arDis = GetAttributeN(arRld, a);
				sName = arDis.go;
    			if (findsubstr(sName, "_shipyard" , 0) != -1)
    			{
					DeleteAttribute(arDis, "close_for_night");
					break;
    			}
    		}
			LocatorReloadEnterDisable(npchar.city + "_shipyard", "reload2", true);
			//ставим таймер на возврат close_for_night
			SetTimerFunction("ShipyardsMap_returnCFN", 0, 0, 2);
		break;

	}
}
