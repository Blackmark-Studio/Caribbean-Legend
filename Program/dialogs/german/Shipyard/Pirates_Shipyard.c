// диалог по городам
// Это мастер тюнинга
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    string 	sTemp;
	int 	amount, iSan, iOil, iSil, iRop;
	int iTemp, iSum; // 280912
	ref 	shTo;
	string 	s1;
	
	int     Matherial1;
	int     Matherial2;
	int     Matherial3;
	int     Matherial4;
	int		HPPrice; 
	
	if ( sti(pchar.Ship.Type) != SHIP_NOTUSED)
	{
		int   	shipCurHP   = sti(RealShips[sti(pchar.Ship.Type)].HP);
		int   	shipBaseHP	= sti(RealShips[sti(pchar.Ship.Type)].BaseHP);
		int   	shipClass   = sti(RealShips[sti(pchar.Ship.Type)].Class);
	}	
 
	switch (Dialog.CurrentNode)
	{		
		// -----------------------------------Диалог первый - первая встреча
		case "First time":  // перехват основного диалога, только один раз
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "Puh... Was für ein schreckliches Klima... Mein Name ist "+GetFullName(npchar)+", und möge Gott mich verdammen, wenn ich nicht der beste Schiffsbauer auf diesen gottverlassenen Inseln bin. Aber diese Feuchtigkeit schlägt mich einfach nieder...";
				Link.l1 = pcharrepphrase("Tausend Haie, mir fehlte gerade noch das Gemurmel eines alten Mannes. Mein Name ist "+GetFullName(pchar)+", ich glaube, du hast von mir gehört.","Es ist nicht die Feuchtigkeit, es ist das Alter, Herr. Mein Name ist "+GetFullName(pchar)+", ich glaube, Sie haben von mir gehört.");
				Link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else // нужно, если по квестам будет сброс на  "First time"
			{
				dialog.text = "Oh, du schon wieder, immer redest du von deinen Problemen... (hustet).";
				link.l1 = pcharrepphrase("Du hast recht, ich bin es wieder. Aber lass uns über Geschäftliches reden, während du deine Seele noch nicht an Gott abgegeben hast.","Ihre Erinnerung dient Ihnen gut, und jetzt, wenn Sie erlauben, lassen Sie uns zu einigen spezifischeren Fragen kommen.");
				link.l1.go = "node_3";
				link.l2 = pcharrepphrase("Ich habe genug von deinem Gemurmel. Lebewohl.","Es ist Zeit für mich zu gehen. Entschuldigung für die Störung");
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "Master_Ship";
			Dialog.CurrentNode = "Master_Ship";
		break;
		
		case "Master_Ship":
		//Jason ----------------------------------- Хронометр Алекса ------------------------------------------
			if (CheckAttribute(npchar, "quest.sextant") && CheckAttribute(pchar, "questTemp.AlexClock") && pchar.location == "Pirates_shipyard" && !CheckAttribute(npchar, "quest.clock"))
			{
				dialog.text = "Aha, Kapitän "+GetFullName(pchar)+"! Wie schön, dass du vorbeigekommen bist!";
				Link.l1 = "Es sieht so aus, als ob du mich für etwas brauchst, nicht wahr? Normalerweise bist du nicht ganz so höflich.";
				Link.l1.go = "clock_begin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "clock" && pchar.location == "Pirates_shipyard")
			{
				dialog.text = "Ich sehe, Sie sind mit leeren Händen zu mir zurückgekehrt, Kapitän! Was ist mit den...Gästen passiert?";
				Link.l1 = "Sie sind weggegangen. Ich habe sie gefragt und sie sind weggegangen.";
				Link.l1.go = "clock_complete";
				break;
			}
		//<-- хронометр Алекса
			dialog.text = "Oh, du schon wieder, immer redend über deine Probleme... (hustend)";
			link.l1 = pcharrepphrase("Du hast recht, ich bin es wieder. Aber lass uns über Geschäfte reden, solange du deine Seele noch nicht Gott gegeben hast.","Ihr Gedächtnis dient Ihnen gut, und jetzt, wenn Sie erlauben, lassen Sie uns zu einigen spezifischeren Fragen übergehen.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("Ich habe genug von deinem Gemurmel. Lebewohl.","Es ist Zeit für mich zu gehen. Entschuldigung für die Störung.");
			link.l2.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;

		case "node_1":
			dialog.text = "Die jungen Leute heutzutage... Ihr habt nie Respekt. Heiße Köpfe, harte Hände, was braucht ihr?";
			link.l1 = pcharrepphrase("Das ist richtig. Aber früher oder später kommt alles zu einem Ende und es sieht so aus, als ob deine Zeit nahe wäre...","Etwas sagt mir, dass du in deinen jungen Jahren nicht unbedingt viel Respekt vor den Älteren hattest. Liege ich richtig?");
			link.l1.go = "node_2";
		break;

		case "node_2":
			dialog.text = "Streite nicht mit deinen Ältesten, Welpe.";
			link.l1 = pcharrepphrase("Ruhig, jetzt. Beruhige dich. Überanstrenge dich nicht, sonst kannst du einen Herzinfarkt bekommen. Ich möchte nicht beschuldigt werden für den Tod des besten Schiffsbauers in der Karibik. Lass uns zur Sache kommen.","Ich vergebe Ihnen Ihre Unhöflichkeit, nur aus Respekt vor Ihrem Alter. Und nun, wenn Sie fertig sind, lassen Sie uns zur Sache kommen.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("Also gut, das reicht mit dem Belehren! Lebewohl!","Ich sehe, wir werden uns nicht einig. Lebewohl.");
			link.l2.go = "exit";
		break;

		case "node_3":
			dialog.text = "(hustend)... Die Leute lassen einen Alten nicht in Ruhe. Was brauchst du diesmal von mir, "+GetAddress_Form(NPChar)+"? ";
			link.l1 = pcharrepphrase("Ich muss die Dienste der Werft in Anspruch nehmen.","Ich möchte die Dienste der Werft in Anspruch nehmen.");
			link.l1.go = "shipyard_dlg";
            Link.l2 = "Ich habe eine Frage.";
			Link.l2.go = "quests"; //(пересылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l3 = "Ich möchte über Finanzen sprechen.";
				link.l3.go = "LoanForAll";//(перессылка в файл города)
			}
			link.l9 = pcharrepphrase("Scheiße, ich habe ein paar dringende Angelegenheiten zu erledigen, auf Wiedersehen.","Es ist Zeit für mich zu gehen. Entschuldigung.");
			link.l9.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;
		
		case "shipyard_dlg":			
			if((shipBaseHP - shipCurHP > 0) && (shipClass < 7))
			{
				dialog.Text = "Ich kann Ihnen eine Hauptreparatur Ihres Rumpfrahmens vorschlagen. Die Leute hier haben keine Ahnung, wie man anständige Schiffe baut, sie zerfallen alle bei einem Schuss...";						
				Link.l1 = "Großartig! Es stellt sich heraus, dass ich ein Schiff habe, das repariert werden muss. Vielleicht schaust du dir an, was du tun kannst?";
				Link.l1.go = "ship_repair_start";		
			}
			else
			{
				dialog.Text = "Na los, was willst du? Belästige einen alten Mann nicht...";
			}	
			link.l2 = "Ich möchte nur die Dienste der Werft nutzen.";
			link.l2.go = "shipyard";
			link.l3 = "Ich brauche Waffen für das Schiff.";
			link.l3.go = "Cannons";
			if(RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
			{
					link.l4 = "Ich möchte das Aussehen meiner Segel ändern.";
					link.l4.go = "SailsGerald";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_hull"))
			{
					link.l50 = "Mein Schiff ist ziemlich... speziell. Ich möchte ein paar Änderungen vornehmen.";
					link.l50.go = "FDM";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_full") && npchar.quest.FDM_full == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
			{
					link.l50 = "Ich habe mehr Kisten für den Kabinenumbau.";
					link.l50.go = "FDM_cabin_pay";
			}
			// Xenon -->
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmoney")
			{
					link.l50 = "Ich bin hier wegen des Umbaus des Schiffes.";
					link.l50.go = "FDM_hull_givemoney";
			}

			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmaterials")
			{
					link.l50 = "Ich bin hier wegen des Umbaus des Schiffes.";
					link.l50.go = "FDM_hull_checkmaterials";
			}
			// <-- Xenon
			link.l9 = pcharrepphrase("Scheiße, ich habe ein paar dringende Angelegenheiten zu erledigen, auf Wiedersehen.","Es ist Zeit für mich zu gehen. Tut mir Leid.");
			Link.l9.go = "ship_tunning_not_now";
		break;
		
		case "ship_repair_again":
			if((shipBaseHP - shipCurHP > 0) && (shipClass < 7))
			{
				dialog.Text = RandPhraseSimple("Ach... du schon wieder. Willst du dein Schiff wieder reparieren lassen?",RandPhraseSimple("Grüße, zu einem berühmten Kapitän. Was, brauchst du eine weitere Hauptreparatur?","Mensch... Nicht eine Minute Ruhe und Frieden. Ihr lasst einen alten Mann nicht konzentrieren.. Noch eine Reparatur?"));
				Link.l1 = "Ja. Du hast recht. Werden wir mal sehen, was wir machen können?";
				Link.l1.go = "ship_repair_start";						   
			}
			else
			{
				dialog.Text = "Was ist diesmal passiert? Du willst mich einfach nicht in Ruhe lassen...";
			}				
			link.l2 = "Ich möchte nur die Dienste der Werft in Anspruch nehmen.";
			link.l2.go = "shipyard";
			link.l3 = "Ich brauche Waffen für das Schiff.";
			link.l3.go = "Cannons";
			if(RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
			{
					link.l31 = "Ich möchte das Aussehen meiner Segel ändern.";
					link.l31.go = "SailsGerald";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_hull"))
			{
					link.l50 = "Mein Schiff ist ziemlich... speziell. Ich möchte ein paar Änderungen vornehmen.";
					link.l50.go = "FDM";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_full") && npchar.quest.FDM_full == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
			{
					link.l50 = "Ich habe mehr Truhen für den Kabinenumbau.";
					link.l50.go = "FDM_cabin_pay";
			}
            Link.l4 = "Ich habe eine Frage.";
			Link.l4.go = "quests"; //(пересылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = "Ich möchte über Finanzen sprechen.";
				link.l5.go = "LoanForAll";//(пересылка в файл города)
			}
			Link.l9 = "Nein. Ich bin zufrieden mit dem, was ich habe.";
			Link.l9.go = "ship_tunning_not_now_2";
		break;
		
		case "ship_tunning_not_now_2":
			dialog.Text = "Oh, ich sehe, du denkst noch! Du wirst weit kommen! Komm zurück, wenn du entschieden hast, was du willst und belästige mich nicht mit lächerlichem Unsinn.";
			Link.l1 = RandPhraseSimple("Danke! Alles Gute.","Auf Wiedersehen, Meister. Und weniger Sarkasmus.");
			Link.l1.go = "ship_tunning_not_now";
		break;
		
		case "ship_repair_start":
            if ( sti(Pchar.Ship.Type) == SHIP_NOTUSED || Pchar.location.from_sea != "Pirates_town")
            {
                dialog.Text = "Wo ist das Schiff? Was ist das alles für Hokuspokus?!";
			    Link.l1 = "Ja, du hast recht... Ich bin... Ich entschuldige mich.";
			    Link.l1.go = "ship_tunning_not_now";
            }
            else
            {
			    if (GetHour() == 13)
			    {
					dialog.Text = "Ich bin vielleicht ein Arbeitstier, aber ich habe auch eine Mittagszeit. Komm später wieder!";
			        Link.l1 = "Gut...";
			        Link.l1.go = "ship_tunning_not_now";
			    }
			    else
			    {
                    if( makefloat(shipCurHP)/makefloat(shipBaseHP) < 0.10)
                    {
						dialog.Text = "Mensch... Dein Schiff ist völlig zerstört. Ich werde keine Hauptreparatur durchführen, frag mich nicht mal danach... Wenn du etwas früher gekommen wärst...";
    			        Link.l1 = "Schon gut... Das ist schade...";
    			        Link.l1.go = "ship_tunning_not_now";
    			        break;
                    }
					if( makefloat(shipCurHP)/makefloat(shipBaseHP) > 0.95)
                    {
						dialog.Text = "Was ist das für ein Hokuspokus... Dein Schiff sieht aus wie neu... Der Rahmen strahlt praktisch hell. Hier gibt es nichts zu reparieren.";
						Link.l1 = "Gut... Nun, ich komme später...";
    			        Link.l1.go = "ship_tunning_not_now";
    			        break;
					}
                    s1 = "Fine, alright... What do we have here... Aha, " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ".";
    			    if (sti(RealShips[sti(Pchar.Ship.Type)].Stolen) == true && !CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning"))
    			    {
    			        s1 = s1 + " Bah! This ship's been in too many hands. Yeah and there are a lot of scuffs. Do you have a corsair patent? Just joking... anyway, back to the matter.";
    			    }
                    dialog.Text = s1;
					Link.l1 = "Lassen wir uns mal anschauen, was wir hier machen können.";
    			    Link.l1.go = "ship_repair_HP";		    			    
    			    Link.l2 = "Halt! Ich habe meine Meinung geändert.";
    			    Link.l2.go = "ship_tunning_not_now_2";
			    }
			}
		break;
		
		case "ship_repair_HP":
			HPPrice 	= GetMaterialQtyRepair( pchar, 0 ); 
			Matherial1	= GetMaterialQtyRepair( pchar, 1 );
			Matherial2	= GetMaterialQtyRepair( pchar, 2 );
			Matherial3	= GetMaterialQtyRepair( pchar, 3 );
			Matherial4	= GetMaterialQtyRepair( pchar, 4 );
			
			s1 = "Let's have a look here at what we can do. At the moment, the ship's frame is " + shipCurHP + ". . The highest possible value is " + shipBaseHP;			
			s1 = s1 + ". In order to make a full repair, I need: ironwood - "+ Matherial1 + ", resin - " + Matherial2 + ", ship silk - " + Matherial3 + " ropes - " + Matherial4 + ".";
			s1 = s1 + " For this work I will charge: "+ HPPrice + " doubloons for the labor... My grandchildren have been calling me back to Europe for a long time. I don't want to come back empty-handed you know... So, that'll be all. And oh yes - the money up front.";
            dialog.Text = s1;
			Link.l1 = "Klingt gut. Ich akzeptiere die Bedingungen. Alles wird wie vereinbart geliefert.";
			if(CheckItemMyCabin("gold_dublon") >= HPPrice)
			{
				Link.l1.go = "ship_repair_HP_start_0";
			}
			else
			{
				Link.l1.go = "ship_repair_HP_start";
			}			
			Link.l2 = "Nein. Damit bin ich nicht zufrieden.";
			Link.l2.go = "ship_tunning_not_now";
		break;
		
		case "ship_repair_HP_start_0":
			dialog.Text = "Ja... Die Zahlung... Sie können jetzt gleich bezahlen oder Sie können einen Boten zum Schiff schicken, um den notwendigen Betrag zu holen... Was möchten Sie tun?";
			link.l1 = "Ich werde jetzt sofort bezahlen.";
			link.l1.go = "ship_repair_HP_start";
			link.l2 = "Ich werde einen Botenjungen schicken. Ich glaube, ich hatte ein bisschen Gold in meinen Truhen liegen...";
			link.l2.go = "ship_repair_HP_start_1";
		break;
		
		case "ship_repair_HP_start":
			HPPrice 	= GetMaterialQtyRepair( pchar, 0 ); 
			Matherial1	= GetMaterialQtyRepair( pchar, 1 );
			Matherial2	= GetMaterialQtyRepair( pchar, 2 );
			Matherial3	= GetMaterialQtyRepair( pchar, 3 );
			Matherial4	= GetMaterialQtyRepair( pchar, 4 );
		    amount = HPPrice;
		    if(GetCharacterItem(pchar,"gold_dublon") >= amount)
			{
				TakeNItems(pchar,"gold_dublon", -amount);				
			    NPChar.Repair.Money  		= amount;
			    NPChar.Repair.Matherial1 	= Matherial1; 
			    NPChar.Repair.Matherial2    = Matherial2;
				NPChar.Repair.Matherial3 	= Matherial3; 
			    NPChar.Repair.Matherial4    = Matherial4; 				 				
			    NPChar.Repair.ShipType      = Pchar.Ship.Type;
			    NPChar.Repair.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NPChar.Repair.Delta         = shipBaseHP - shipCurHP;
			    			
				NextDiag.TempNode = "ship_repair_HP_again";
                dialog.text = "Hervorragend. Ich werde auf die Materialien warten.";
			    link.l1 = "Werd' sie sammeln...";
			    link.l1.go = "Exit";
			    
			    ReOpenQuestHeader("ShipRepair");
			    AddQuestRecord("ShipRepair", "t1");
				AddQuestUserData("ShipRepair", "sText",  "For capital repairing measures of  " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
    " the shipmaster requires: ironwood - " + NPChar.Repair.Matherial1 + ", resin - "+ NPChar.Repair.Matherial2 + ", ship silk - " + NPChar.Repair.Matherial3 + " ropes - " + NPChar.Repair.Matherial4 + 
				". As a deposit we handed in " + NPChar.Repair.Money + " doubloons... He says he's about to take off to Europe. I think that old devil's lying.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = RandPhraseSimple("Ich sehe die Anzahlung nicht...","Was ist das für ein Hokuspokus...");
				link.l1 = "Ich komme später wieder.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_repair_HP_start_1":
			HPPrice 	= GetMaterialQtyRepair( pchar, 0 ); 
			Matherial1	= GetMaterialQtyRepair( pchar, 1 );
			Matherial2	= GetMaterialQtyRepair( pchar, 2 );
			Matherial3	= GetMaterialQtyRepair( pchar, 3 );
			Matherial4	= GetMaterialQtyRepair( pchar, 4 );
			AddTimeToCurrent(0, 30);
		    amount = HPPrice;
			GetItemMyCabin("gold_dublon", amount);
		    
			NPChar.Repair.Money  		= amount;
			NPChar.Repair.Matherial1 	= Matherial1; 
			NPChar.Repair.Matherial2    = Matherial2; 
			NPChar.Repair.Matherial3 	= Matherial3; 
			NPChar.Repair.Matherial4    = Matherial4; 				 							
			NPChar.Repair.ShipType      = Pchar.Ship.Type;
			NPChar.Repair.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
			NPChar.Repair.Delta         = shipBaseHP - shipCurHP;
			    			
			NextDiag.TempNode = "ship_repair_HP_again";
			dialog.text = "Prächtig. Ich werde auf die Materialien warten.";
			link.l1 = "Da geh ich hin...";
			link.l1.go = "Exit";
			
			ReOpenQuestHeader("ShipRepair");
			AddQuestRecord("ShipRepair", "t1");
			AddQuestUserData("ShipRepair", "sText",  "For capital repairing measures of  " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
    " the shipmaster requires: ironwood - " + NPChar.Repair.Matherial1 + ", resin - "+ NPChar.Repair.Matherial2 + ", ship silk - " + NPChar.Repair.Matherial3 + " ropes - " + NPChar.Repair.Matherial4 + 
				". As a deposit we handed in " + NPChar.Repair.Money + " doubloons... He says he's about to take off to Europe. I think that old devil's lying.");
			
		break;
		
		case "ship_repair_HP_again":
		    if (sti(NPChar.Repair.ShipType) == sti(Pchar.Ship.Type) && NPChar.Repair.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_repair_HP_again";
				dialog.Text = "Die Uhr tickt. Hast du, was ich gefragt habe?";
			    Link.l1 = "Ja. Ich habe etwas bekommen.";
			    Link.l1.go = "ship_repair_HP_again_2";
			    Link.l2 = "Nein. Ich bin immer noch auf der Suche.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Repair");
                NextDiag.TempNode = "ship_repair_again";
			    dialog.Text = "Es scheint mir, Herr, dass Sie seit unserer letzten Vereinbarung Ihr Schiff gewechselt haben. Wir müssen alles noch mal neu zählen...";
			    Link.l1 = "Ja, das stimmt. Was für ein Pity, dass die Kaution weg ist...";
			    Link.l1.go = "Exit";		    
			    AddQuestRecord("ShipRepait", "Lose");
			    CloseQuestHeader("ShipRepair");
			}
		break;
		
		case "ship_repair_HP_again_2":
			checkMatherial_repair(Pchar, NPChar, GOOD_SANDAL, 	1);
			checkMatherial_repair(Pchar, NPChar, GOOD_OIL, 		2);
			checkMatherial_repair(Pchar, NPChar, GOOD_SHIPSILK, 3);
			checkMatherial_repair(Pchar, NPChar, GOOD_ROPES, 	4);
		    if(sti(NPChar.Repair.Matherial1) < 1 && 
			   sti(NPChar.Repair.Matherial2) < 1 &&
			   sti(NPChar.Repair.Matherial3) < 1 &&
			   sti(NPChar.Repair.Matherial4) < 1)
			{
                NextDiag.TempNode = "ship_repair_again";
                dialog.text = "Alles, was ich brauchte. Gut! Zeit zu arbeiten...";
			    link.l1 = "In Ordnung, ich warte.";
			    link.l1.go = "ship_repair_HP_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_repair_HP_again";
				dialog.Text = "Jetzt was du mir noch bringen musst ist: "+sti(NPChar.Repair.Matherial1)+" aus Eisenholz, "+sti(NPChar.Repair.Matherial2)+" Harz, "+NPChar.Repair.Matherial3+" aus Schiffsseide, "+NPChar.Repair.Matherial4+"Seile.";
				link.l1 = "In Ordnung.";
				link.l1.go = "Exit";

                AddQuestRecord("ShipRepair", "t1");
				AddQuestUserData("ShipRepair", "sText", "Materials left: ironwood - "+ NPChar.Repair.Matherial1 + ", resin - "+ NPChar.Repair.Matherial2 + ", ship silk - " + NPChar.Repair.Matherial3 + " ropes - " + NPChar.Repair.Matherial4 + ".");
			}
		break;
		
		case "ship_repair_HP_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.HP = sti(shTo.HP) + sti(NPChar.Repair.Delta);
		    DeleteAttribute(NPChar, "Repair");
			
			pchar.ship.hp = GetCharacterShipBaseHP(pchar);
			DeleteAttribute(pchar, "ship.hulls");
			DeleteAttribute(pchar, "ship.blots");		
			
            NextDiag.TempNode = "node_3";
			dialog.Text = "... Nun, das ist alles... Ich garantiere Ihnen, es wird ziemlich schwierig sein, dieses Schiff jetzt zu zerstören!";
			Link.l1 = "Danke! Ich würde lieber nicht experimentieren, aber ich werde dir vertrauen.";
			Link.l1.go = "Exit";
			AddQuestRecord("ShipRepair", "End");
			CloseQuestHeader("ShipRepair");
		break;		
		
		///////////////////////////////  квестовые ветки
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Fragen haben Sie?","Wie kann ich Ihnen helfen?"),"Du hast versucht, mir vor einer Weile eine Frage zu stellen...","Ich habe noch nie Menschen mit solcher Neugier in meiner Werft oder sonst wo in dieser Stadt getroffen.","Was ist mit all den Fragen? Meine Aufgabe ist es, Schiffe zu bauen. Kümmern wir uns darum.","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert...","Ich habe im Moment nichts zu besprechen."),"Umph, wo ist mein Gedächtnis hin...","Hm, nun...","Gut, lass uns...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "Step_Door"))
			{
				link.l2 = "Hör zu, ich möchte durchgehen und diese Tür ist verschlossen...";
				link.l2.go = "Step_Door_1";
			}

			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAlexus"))
			{
				link.l1 = "Ich möchte einen Handel vorschlagen.";
				link.l1.go = "Al_ShipLetters_1";// генератор  "Найденные документы"
				pchar.questTemp.different.GiveShipLetters.speakAlexus = true;
			}
			if(CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "go") // 280912
			{
				link.l1 = "Ich bin hier wegen den Materialien für die Fregatte.";
				link.l1.go = "clock";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Hör zu, "+npchar.name+", haben Sie kürzlich Miguel Dichoso auf Isla Tesoro gesehen?";
				link.l1.go = "tieyasal";
			}
		break;
//*************************** Генератор - "Найденные судовые документы" **************
		
		case "Al_ShipLetters_1":
			dialog.text = "Nennen Sie Ihre Bedingungen.";
			s1 = "I lucked into finding an absolutely legal ship's documents packet that hasn't been called for search yet.";
			s1 = s1 + "The ship is afloat and it hasn't been excluded from the registry, don't worry. Just a blind fool-owner had the misfortune of losing these papers...";
			link.l1 = s1;
			link.l1.go = "Al_ShipLetters_2";			
		break;
		case "Al_ShipLetters_2":
			s1 = "Let me take a look! It really looks to be freshly filled out. Well, luck is in your favor, sir! ";
			s1 = s1 + "I actually needed a packet just like this. I, in turn, will offer you " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pesos. What do you say?";
			dialog.text = s1;
			link.l1 = "Wahre königliche Großzügigkeit! Natürlich stimme ich zu!";
			link.l1.go = "Al_ShipLetters_3";
			link.l2 = "Nein, ich glaube nicht.";
			link.l2.go = "exit";
		break;
		case "Al_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5)); 
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			OfficersReaction("bad"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "9");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		

//*************************** Открывание двери ***************************
 		case "Step_Door_1":
			dialog.text = "Das ist richtig. Wenn du durch diese Tür gehen willst, musst du mir 20000 Pesos zahlen. Wenn du nicht zahlst, öffne ich nicht. Das hier ist keine Suppenküche. Und ich rate dir auch nicht, dort hinzugehen. Es wäre besser für dich, wenn du nicht gehst...";
			if(sti(pchar.money) >= 20000)
			{
    			link.l1 = "Hier ist dein Geld. Mach auf.";
    			link.l1.go = "Step_Door_2";
            }
            else
            {
    			link.l1 = "Ich habe nicht so viel Geld.";
    			link.l1.go = "Step_Door_3";
            }
            link.l2 = "Keine Chance! Ich würde niemals für eine Tür bezahlen.";
    		link.l2.go = "exit";
		break;
		
 		case "Step_Door_2":
			npchar.Step_Door = true; // fix
			dialog.text = "Geh rein. Die Tür ist offen. Mach dir keine Sorgen, mir zu danken!";
			link.l1 = "Nein, warum nicht. Danke, "+npchar.name+"...";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
            AddMoneyToCharacter(pchar, -20000);
			pchar.quest.CloseBermudesDungeonDoor.win_condition.l1 = "MapEnter";
            pchar.quest.CloseBermudesDungeonDoor.win_condition = "CloseBermudesDungeonDoor";
		break;
		
 		case "Step_Door_3":
			dialog.text = "Nun, wenn du es hast, komm zurück. Ansonsten versuch gar nicht erst, mich zu überzeugen. Es ist nutzlos...";
			link.l1 = "Argh, ich bin völlig sprachlos!";
			link.l1.go = "exit";
		break;
		
	// ------------------------------------------- хронометр Ђлекса ----------------------------------------------// Addon-2016 Jason замена дублонов на песо везде
		case "clock_begin":
			dialog.text = "Komm schon, sei nicht so streng mit einem alten Mann... Ich brauche wirklich deine Hilfe, Kapitän.";
			link.l1 = "Sag mir, Meister. Was ist Ihnen passiert?";
			link.l1.go = "clock_begin_1";
		break;
		
		case "clock_begin_1":
			sTotalTemp = "Steven Dodson";
			if (pchar.questTemp.Alex.Clock == "terrax") sTotalTemp = "Marcus Tyrex";
			dialog.text = "Unser neuer Anführer der Bruderschaft der Küste, "+sTotalTemp+", hat ein neues Schiff bestellt, eine Fregatte. Er hat auch ziemlich schwierige Aufgaben gestellt: geschützter Rumpf, hohe Geschwindigkeit und gute Manövrierfähigkeit plus Kanonen des größtmöglichen Kalibers\nIch verstehe, dass das Schiff eines Admirals, entschuldigen Sie, des Anführers der Brüder, etwas Besonderes sein muss, aber das bedeutet, dass ich spezielle Materialien brauche, um es zu bauen. Du musst von ihnen gehört haben. Eisenholz, Harz, Schiffsseide und Seile...";
			link.l1 = "So erzähle dies dem Anführer der Brüder. Oder hast du Angst, dass "+sTotalTemp+"werde ich dir den Kopf dafür abschneiden?";
			link.l1.go = "clock_begin_2";
		break;
		
		case "clock_begin_2":
			dialog.text = "Ich habe es ihm gesagt... Die Sache ist, dass unser neuer Anführer weder die Zeit noch die Möglichkeit hat, diese Materialien zu finden und zu bringen. Du musst wissen, was für eine Seltenheit das ist. Und ohne sie werde ich auf keinen Fall in der Lage sein, eine Fregatte mit den genannten Eigenschaften zu bauen.";
			link.l1 = "Und Sie schlagen wahrscheinlich vor, dass ich Materialien für das Schiff finden muss?";
			link.l1.go = "clock_begin_3";
		break;
		
		case "clock_begin_3":
			dialog.text = "Nun, ja. Sie sind ein guter Freund unseres Anführers. "+sTotalTemp+" sagt selbst, dass er dir viel schuldet und dass er allerlei Respekt für dich verlangt... Also dachte ich: Da du sein Freund bist, wärst du vielleicht nicht dagegen, ihm zu helfen? Und gleichzeitig: Du verstehst doch, in was für einer peinlichen Position ich mich befinde? Alle Materialien werden bezahlt, "+sTotalTemp+" ist nicht knauserig mit seinem Gold.";
			link.l1 = "Es tut mir leid, Meister, aber ich bin nicht weniger beschäftigt als "+sTotalTemp+". Ich fürchte, das Sammeln von Materialien könnte eine ganze Ewigkeit dauern. Also, fragen Sie besser jemand anderen.";
			link.l1.go = "clock_exit";
			link.l2 = "Nun, wenn "+sTotalTemp+" bestellte ein Schiff bei Ihnen - dann werde ich natürlich versuchen zu helfen. Wir sind wirklich Freunde, und Freunde müssen einander helfen. Wie viele Materialien brauchst du?";
			link.l2.go = "clock_begin_4";
		break;
		
		case "clock_exit":
			dialog.text = "Das ist schade. Das ist wirklich schade. Ich habe auf dich gezählt. Nun, wie man so sagt, nein heißt nein...";
			link.l1 = "...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.AlexClock");
		break;
		
		case "clock_begin_4":
			dialog.text = "Mir fehlen 100 Einheiten Eisenholz, 150 Behälter Harz, 110 Rollen Schiffsseide und 90 Spulen Hanfseile. Was denkst du? Könntest du mir all das in vier Monaten besorgen? Ich glaube, ich habe nicht mehr Zeit.";
			link.l1 = "Ich kann es zumindest versuchen. Und was ist mit der Bezahlung?";
			link.l1.go = "clock_begin_5";
		break;
		
		case "clock_begin_5":
			dialog.text = "Hier sind meine Preise: Eisenholz für 4000 Pesos pro Stück, Harze für 1400 Pesos pro Behälter, Seide für 2500 Pesos pro Rolle und Seile für 1500 Pesos pro Spule. Und wenn Sie mir all das bringen, erhalten Sie ein sehr schönes Geschenk von mir.";
			link.l1 = "Was mag das sein, frage ich mich?";
			link.l1.go = "clock_begin_6";
		break;
		
		case "clock_begin_6":
			dialog.text = "Bring mir zuerst die Materialien. Aber ich versichere dir: es wird dir sehr nützlich sein, und das Ding ist einzigartig. Es gibt kein anderes in der Karibik, oder in der ganzen Welt bisher. Ich hoffe, dieser kleine Funke der Neugier hat dein Interesse geweckt, die Materialien für mich zu sammeln.";
			link.l1 = "Nun, du bist schlau wie ein Kobold, Meister! Gut, wir haben einen Deal.";
			link.l1.go = "clock_begin_7";
		break;
		
		case "clock_begin_7":
			dialog.text = "Ich bin sehr glücklich. Ich freue mich auf Ihre Rückkehr.";
			link.l1 = "Ich hoffe, es dauert nicht zu lange...";
			link.l1.go = "clock_begin_8";
		break;
		
		case "clock_begin_8":
			DialogExit();
			pchar.questTemp.AlexClock = "go";
			npchar.quest.clock = "true";
			SetFunctionTimerCondition("AlexClock_Over", 0, 0, 122, false); // таймер
			AddQuestRecord("alex_clock", "1");
			// запоминаем переменные
			pchar.questTemp.AlexClock.Sandal = 100;
			pchar.questTemp.AlexClock.Oil = 150;
			pchar.questTemp.AlexClock.Shipsilk = 110;
			pchar.questTemp.AlexClock.Ropes = 90;
		break;
		
		case "clock":
			dialog.text = "Ausgezeichnet! Was hast du mir heute mitgebracht?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && !CheckAttribute(npchar, "quest.sandal"))
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "Eisenholz, in der Menge von "+FindRussianQtyString(iSan)+".";
				link.l1.go = "sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && !CheckAttribute(npchar, "quest.oil"))
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "Harze, in der Menge von "+FindRussianQtyString(iOil)+".";
				link.l2.go = "oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && !CheckAttribute(npchar, "quest.shipsilk"))
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "Seidenschiff, in der Menge von "+FindRussianQtyString(iSil)+".";
				link.l3.go = "shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && !CheckAttribute(npchar, "quest.ropes"))
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "Hanfseile, in der Menge von "+FindRussianQtyString(iRop)+".";
				link.l4.go = "ropes";
			}
			link.l5 = "Nichts im Moment. Ich wollte nur sicherstellen, dass wir noch eine Vereinbarung haben.";
			link.l5.go = "exit";
		break;
		
		case "clock_1":
			if (CheckAttribute(npchar, "quest.sandal") && CheckAttribute(npchar, "quest.oil") && CheckAttribute(npchar, "quest.shipsilk") && CheckAttribute(npchar, "quest.ropes")) // все привез
			{
				dialog.text = "Wunderbar! Ich habe alle Materialien in der benötigten Menge. Vielen Dank für Ihre Hilfe, Kapitän. Sie haben mir sehr geholfen.";
				link.l1 = "Ja, jederzeit, Meister. Ich bin auch ziemlich zufrieden: Ich habe einem Freund geholfen und gutes Geld verdient. Und nun lass uns zu unserem Gespräch über deinen mysteriösen Gegenstand zurückkehren, den du mir versprochen hast.";
				link.l1.go = "clock_2";
			}
			else
			{
				dialog.text = "Gibt es noch mehr Überraschungen für mich, Kapitän?";
				link.l1 = "Ach, das ist alles für jetzt. Warte einfach weiter.";
				link.l1.go = "exit";
				link.l2 = "Ja, ich habe noch eine Sache...";
				link.l2.go = "clock";
			}
		break;
		
		case "sandal": // бакаут
			amount = sti(pchar.questTemp.AlexClock.Sandal);
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			iTemp = amount-iSan;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 4000*iSan;
				dialog.text = "Gut, in Ordnung. Ich werde auch brauchen "+FindRussianQtyString(amount)+" aus Eisenholz. Du hast mir gebracht "+FindRussianQtyString(iSan)+". . Also, was bleibt dir noch zu bringen ist "+FindRussianQtyString(iTemp)+". In Ordnung, mit einem Preis von 4000 Pesos pro Stück beläuft sich Ihre Belohnung auf "+FindRussianMoneyString(iSum)+". Bitte, nimm es.";
				link.l1 = "Danke! Der Rest kommt bald.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				pchar.questTemp.AlexClock.Sandal = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 4000*amount;
				dialog.text = "Gut, in Ordnung. Ich werde auch noch brauchen "+FindRussianQtyString(amount)+"  aus Eisenholz. Du hast mir gebracht "+FindRussianQtyString(iSan)+". Also, wir haben uns jetzt um das Eisenholz gekümmert! Gut, zum Preis von 4000 Pesos pro Stück beläuft sich Ihre Belohnung auf "+FindRussianMoneyString(iSum)+". Bitte, nimm es.";
				link.l1 = "Danke dir!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.sandal = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "oil": // смолы
			amount = sti(pchar.questTemp.AlexClock.Oil);
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			iTemp = amount-iOil;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 1400*iOil;
				dialog.text = "Gut, in Ordnung. Ich werde auch brauchen "+FindRussianQtyString(amount)+" Harze. Du hast mir gebracht "+FindRussianQtyString(iOil)+". Also, was bleibt für dich, mir zu bringen ist "+FindRussianQtyString(iTemp)+". In Ordnung, zum Preis von 1400 Pesos pro Container beläuft sich Ihre Belohnung auf "+FindRussianMoneyString(iSum)+". Bitte, nimm es.";
				link.l1 = "Danke! Sie werden den Rest bald haben.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				pchar.questTemp.AlexClock.Oil = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "resins");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1400*amount;
				dialog.text = "Gut, gut. Ich werde auch noch brauchen "+FindRussianQtyString(amount)+" Harze. Du hast mir gebracht "+FindRussianQtyString(iOil)+". Also, wir haben uns jetzt um die Harze gekümmert! Gut, zum Preis von 1400 Pesos pro Container beläuft sich Ihre Belohnung auf "+FindRussianMoneyString(iSum)+". Bitte, nimm es.";
				link.l1 = "Danke dir!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.oil = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "resins");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "shipsilk": // шёлк
			amount = sti(pchar.questTemp.AlexClock.Shipsilk);
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			iTemp = amount-iSil;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 2600*iSil;
				dialog.text = "Gut, in Ordnung. Ich werde auch noch brauchen "+FindRussianQtyString(amount)+" Seide. Du hast mir gebracht "+FindRussianQtyString(iSil)+". Also, was bleibt Ihnen noch, mir zu bringen ist "+FindRussianQtyString(iTemp)+". Also gut, zum Preis von 2600 Pesos pro Stück beläuft sich Ihre Belohnung auf "+FindRussianMoneyString(iSum)+". Bitte, nimm es.";
				link.l1 = "Danke! Den Rest bekommst du bald.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				pchar.questTemp.AlexClock.Shipsilk = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "silk");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 2600*amount;
				dialog.text = "Gut, in Ordnung. Ich werde auch brauchen "+FindRussianQtyString(amount)+" Seide. Du hast mir gebracht "+FindRussianQtyString(iSil)+". Also, wir haben uns jetzt um die Seide gekümmert! Also, zum Preis von 2600 Pesos pro Stück beträgt Ihre Belohnung insgesamt "+FindRussianMoneyString(iSum)+". Bitte, nimm es.";
				link.l1 = "Danke dir!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.shipsilk = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "silk");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "ropes": // канаты
			amount = sti(pchar.questTemp.AlexClock.Ropes);
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			iTemp = amount-iRop;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 1500*iRop;
				dialog.text = "Gut, in Ordnung. Ich werde auch brauchen "+FindRussianQtyString(amount)+" Seile. Du hast mir gebracht "+FindRussianQtyString(iRop)+". Also, was bleibt Ihnen noch zu bringen ist "+FindRussianQtyString(iTemp)+". Also, mit einer Rate von 1500 Pesos pro Stück, beläuft sich Ihre Belohnung auf "+FindRussianMoneyString(iSum)+". Bitte, nimm es.";
				link.l1 = "Danke! Sie bekommen den Rest bald.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				pchar.questTemp.AlexClock.Ropes = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ropes");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1500*amount;
				dialog.text = "Gut, in Ordnung. Ich werde auch brauchen "+FindRussianQtyString(amount)+" Seile. Du hast mir gebracht "+FindRussianQtyString(iRop)+". Also, wir haben uns bereits um die Seile gekümmert. Gut, zum Preis von 1500 Pesos pro Stück beläuft sich Ihre Belohnung auf "+FindRussianMoneyString(iSum)+". Bitte, nimm es.";
				link.l1 = "Danke dir!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.ropes = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ropes");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "clock_2":
			dialog.text = "Ja, ja... über meine Sache, natürlich. M-m-mmm...Hmmm... wo habe ich... ahhh...";
			link.l1 = "Was ist los, Meister? Sie sehen ziemlich besorgt aus. Ist etwas nicht in Ordnung? Irgendwelche Probleme?";
			link.l1.go = "clock_3";
		break;
		
		case "clock_3":
			dialog.text = "Genau. Probleme. Aktuelle. Verdammt noch mal, diese Schatzjäger...";
			link.l1 = "Beruhige dich, beruhige dich. In deinem Alter ist es nicht gut, sich so Sorgen zu machen. Gott bewahre, du könntest nur einen Schlag entfernt sein. Wer würde dann die Fregatte für den Kopf der Bruderschaft bauen? Beruhige dich und erkläre mir, wer sind diese Schatzsucher?";
			link.l1.go = "clock_4";
		break;
		
		case "clock_4":
			dialog.text = "Dort drüben bei meinem Tisch ist eine Tür. Sie führt direkt in einen alten Tresorraum. In diesem Tresorraum, in einer der Schatzkisten, bewahre ich meine Metallkiste mit Gegenständen auf, die bei mir waren, als ich vor zwanzig Jahren durch diesen verdammten Trichter gezogen wurde und hier gelandet bin...";
			link.l1 = "Welcher Trichter? Wovon redest du?";
			link.l1.go = "clock_5";
		break;
		
		case "clock_5":
			dialog.text = "Ach, entschuldige meine Phantasien. Alt zu sein ist nicht einfach, junger Mann. Verzeih mir. Aber das ist irrelevant. Was relevant ist, ist, dass eine Kiste mit einem Geschenk für dich in der Truhe liegt, die derzeit in einem Kerker liegt, der von einigen Abschaum besetzt ist. Sie sind nicht unsere Leute, noch von Isla Tesoro\nSchatzjäger, jemand muss ihnen erzählt haben, dass dieser Ort voller Schätze ist. Sie würden es nicht wagen, sich hier zu zeigen, aber ich habe zu viel Angst, sie zu besuchen, verstehst du? Ihre Gesichter sind...";
			link.l1 = "Ich verstehe. Öffne deine Tür. Ich werde deine ungebetenen Gäste vertreiben.";
			link.l1.go = "clock_6";
		break;
		
		case "clock_6":
			dialog.text = "Einfach so? Du wirst sie vertreiben? Alleine? Hast du keine Angst? Wir haben eine ganze Siedlung, die für dich kämpfen wird, wenn du nur fragst...";
			link.l1 = "Weniger Gerede, mehr Aktion, Meister. Öffnen Sie diese Tür und überlassen Sie den Rest mir. In welcher Truhe bewahren Sie Ihre Sachen auf?";
			link.l1.go = "clock_7";
		break;
		
		case "clock_7":
			dialog.text = "Gerade den Gang hinunter ist eine ganze Sammlung leerer Holzfässer. Hinter ihnen auf dem Boden an einem abgelegenen Ort befindet sich eine kleine Truhe. Ich habe ein Schloss darauf gehämmert, also bezweifle ich, dass diese Eindringlinge es schaffen würden, ihre schmutzigen Hände hinein zu bekommen, selbst wenn sie es finden würden. Hier, nimm den Schlüssel.";
			link.l1 = "Es freut mich, dass du vorausdenkst. Warte hier und geh nirgendwohin.";
			link.l1.go = "clock_8";
		break;
		
		case "clock_8":
			DialogExit();
			GiveItem2Character(pchar, "key3"); 
			bDisableFastReload = true;//закрыть переход
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", true);//офицеров не пускать
			pchar.quest.Alex_Chest.win_condition.l1 = "location";
			pchar.quest.Alex_Chest.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.Alex_Chest.function = "AlexClock_Chest";
			pchar.quest.AlexClock_Over.over = "yes"; //снять прерывание
			pchar.questTemp.AlexClock = "chest";
			AddQuestRecord("alex_clock", "3");
		break;
		
		case "clock_complete":
			dialog.text = "Sie haben Ihnen einfach zugehört und sind dann gegangen?";
			link.l1 = "Das stimmt. Sie stellten sich als höfliche nette Kerle heraus. Ich habe ihnen erklärt, dass ihre Anwesenheit den alten berühmten Schiffsbauer erschreckt und aus Respekt vor deinem Alter haben sie das Gelände verlassen. Du kannst dort unten ohne Sorge hinuntergehen.";
			link.l1.go = "clock_complete_1";
		break;
		
		case "clock_complete_1":
			dialog.text = "Ach, du machst dich über einen alten Mann lustig! Schon gut. Gib mir meine Kiste und ich öffne sie und gebe dir das Gerät, das du fair und quadratisch verdient hast.";
			link.l1 = "Bitte, nimm es...";
			link.l1.go = "clock_complete_2";
		break;
		
		case "clock_complete_2":
			RemoveItems(pchar, "alexs_chest", 1);
			dialog.text = "Dankbarkeit! Lass uns es öffnen. Hier, nimm das. Automatischer mechanischer Timer, niemand macht solche Geräte hier und niemand wird es für die nächsten dreihundert Jahre tun... huh, Entschuldigungen, bitte verzeih dem alten Mann. Alles, was ich sage, ist, dass dieses Ding einzigartig ist\nEs erledigt die ganze Arbeit selbst, du brauchst keine dummen Sanduhren und so weiter. Keine Fehler! Bewahre es nur vor direkten Schlägen und Wasser, sonst verlierst du es. Selbst ein Affe kann diesen Timer verwenden.";
			link.l1 = "Hol das mal! Ich habe noch nie etwas so Wunderbares in meinem Leben gesehen! Danke, Meister.";
			link.l1.go = "clock_complete_3";
		break;
		
		case "clock_complete_3":
			GiveItem2Character(pchar, "clock3");
			Log_Info("You've received an automatic mechanical timer");
			SetAlchemyRecipeKnown("sextant2");
			PlaySound("interface\important_item.wav");
			dialog.text = "Bitte sehr. Jetzt wirst du immer genau wissen, wie spät es ist. Frag mich nicht, wo ich es her habe. Ich werde es dir nicht sagen.";
			link.l1 = "Jeder hat seine Geheimnisse, nicht wahr, Meister? Gut... behalte deine Geheimnisse und ich werde mich nicht in deine Angelegenheiten einmischen. Danke für das Geschenk!";
			link.l1.go = "clock_complete_4";
		break;
		
		case "clock_complete_4":
			dialog.text = "Und danke für Ihre Hilfe, Kapitän. Besuchen Sie mich manchmal. Vergessen Sie einen alten Schiffbauer nicht.";
			link.l1 = "Wie könnte ich dich vergessen... Wie auch immer, das werde ich auf jeden Fall tun, Alexus der Meister. Auf Wiedersehen!";
			link.l1.go = "clock_complete_5";
		break;
		
		case "clock_complete_5":
			DialogExit();
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", false);
			LocatorReloadEnterDisable("Bermudes_Dungeon", "reload2_back", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", false);
			AddQuestRecord("alex_clock", "5");
			CloseQuestHeader("alex_clock");
			DeleteAttribute(pchar, "questTemp.AlexClock");
			// belamour legendary edition на пару с Акулой
			pchar.questTemp.SharkGoldFleet.KGBB = true;
			if(CheckAttribute(pchar,"questTemp.SharkFrigate")) SetTimerCondition("SharkGoldFleet", 0, 0, 30, false);
		break;
	// <-- хронометр Алекса
		
		// город майя
		case "tieyasal":
			dialog.text = "Aha, Miguel! Mein alter Bekannter. Ich erinnere mich an ihn. Er hat mich immer wieder nach jedem kleinen Detail gefragt. Aber wie sollte ich ihm erklären, wie ein Radio innen konstruiert war, wenn er noch nicht einmal ein einfaches Telegraf gesehen hatte?";
			link.l1 = "Was?.. Wovon redest du, Meister?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Oh, Entschuldigung, junger Mann. Beachten Sie mein Gerede nicht allzu sehr... Unser neugieriger Michel hat seine Neugier befriedigt und ist verschwunden. Erst vor drei Tagen haben wir uns unterhalten.";
			link.l1 = "Wo ist Miguel gerade jetzt, wenn es Ihnen nichts ausmacht, dass ich frage?";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Wer weiß. Vielleicht macht er seine Geschäfte in Scharftown oder er ist bereits von Isla Tesoro abgereist.";
			link.l1 = "Ich verstehe. Danke, Meister!";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Калеуче
		case "FDM":
			if(CheckAttribute(npchar, "quest.FDM_secondtime"))
				dialog.text = "Wieder mit deinem 'Geisterschiff'... Wisse das - Ich arbeite nur daran in der Hoffnung, dass es etwas Anständiges wird. Sonst würde ich es nicht einmal berühren. Ich denke, jeder auf See teilt eine ähnliche Meinung. Was willst du diesmal damit machen?";
			else	
				dialog.text = "Ach, das 'Geisterschiff'! Mütter benutzen deine Galeone, um unartige Kinder zu erschrecken. Und du hast dich entschieden, dieses verdammte Schiff zu behalten, anstatt es zu versenken! Seeleute zittern, wenn sie dein Schiff am Horizont sehen... Also, was willst du damit machen?";
			if (!CheckAttribute(npchar, "quest.FDM_cabin"))
			{
				link.l1 = "Ich mag die Idee von kleinen Feiglingen, die sich zu Tode erschrecken. Aber das Innere macht mich traurig. Haben Sie die Kabine gesehen? Es fühlt sich an wie ein Sarg. All dieser Schimmel und Staub. Ich möchte es reparieren. Können Sie das machen, Meister?";
				link.l1.go = "FDM_cabin";
			}
			if (!CheckAttribute(npchar, "quest.FDM_sails"))
			{
				link.l2 = "Ich habe genug von diesen zerrissenen schwarzen Lumpen. Ich gebe zu, sie fangen den Wind genauso gut wie normale Segel, aber die Aussicht... Ekelhaft. Ich will gewöhnliche schneeweiße Segel. Bist du dabei, Meister?";
				link.l2.go = "FDM_sails";
			}
			
			if (!CheckAttribute(npchar, "quest.FDM_hull"))
			{
				link.l3 = "Nun, ich denke, es ist an der Zeit, daraus etwas Anständiges zu machen. Das Schiff ist gut, die Mannschaft ist daran gewöhnt, aber es ist einfach nicht würdig für einen respektablen Kapitän, auf einem Schiff zu segeln, das Erwachsenen die Scheiße aus dem Leib schrecken kann, geschweige denn Kindern. Ich möchte es komplett umbauen, damit andere Kapitäne es beneiden, wenn sie mein Schiff sehen, anstatt sich zu bekreuzigen. Und an wen sollte ich mich mit diesem Anliegen wenden, wenn nicht an den besten Schiffsbauer im Archipel?";
				link.l3.go = "FDM_hull";
			}
		break;
		
		case "FDM_cabin":
			dialog.text = "Warum nicht? Meine Hände sind immer noch gerade. Ihre Galeone ist riesig, also kann ich sogar eine königliche Kabine bauen, wie sie in Schlachtschiffen und Kriegsschiffen bauen. Oder wir können eine Standardkabine behalten. Die Wahl liegt bei Ihnen?";
			link.l1 = "Bau die Kajüte des Linienschiffes! Sie werden alle vor Neid sterben...";
			link.l1.go = "FDM_cabin_m";
			link.l2 = "Kein Sinn in übermäßigem Luxus. Halten Sie sich an den Standard.";
			link.l2.go = "FDM_cabin_s";
		break;
		
		case "FDM_cabin_m":
			dialog.text = "Gut. Zehn Kisten mit Dublonen und es wird in fünf Tagen erledigt sein.";
			link.l1 = "Abgemacht!";
			link.l1.go = "FDM_cabin_m1";
			link.l2 = "Zehn Kisten? Tausendfünfhundert Dublonen? Hm, ich brauche Zeit, um solche Ausgaben zu überlegen...";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_s":
			dialog.text = "Gut. Sieben Kisten mit Dublonen und es wird in fünf Tagen erledigt sein.";
			link.l1 = "Abgemacht!";
			link.l1.go = "FDM_cabin_s1";
			link.l2 = "Sieben Kisten? Mehr als tausend Dublonen? Hm, ich brauche Zeit, um solche Ausgaben zu überlegen...";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_m1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin = 10;
			npchar.quest.FDM_cabin.type = "Cabin_Huge";
			dialog.text = "Gut, ich werde auf eine Zahlung warten.";
			if (iTemp > 0)
			{
				link.l1 = "Ich habe Kisten bei mir. Lass uns sehen. Hier, "+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "Ich muss gehen und Münzen in die Truhen legen.";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_s1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin = 7;
			npchar.quest.FDM_cabin.type = "Cabin";
			dialog.text = "Gut, ich werde auf eine Zahlung warten.";
			if (iTemp > 0)
			{
				link.l1 = "Ich habe Kisten bei mir. Mal sehen. Hier, "+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "Ich muss gehen und Münzen in die Truhen legen.";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_wait":
			DialogExit();
			npchar.quest.FDM_full = "cabin";
		break;
		
		case "FDM_cabin_pay":
			iTemp = GetCharacterItem(pchar, "Chest");
			amount = sti(npchar.quest.FDM_cabin)-iTemp;
			Log_Info("You have given chests to Master Alexus");
			PlaySound("interface\important_item.wav");
			if (amount <= 0) // всё принес
			{
				RemoveItems(pchar, "chest", sti(npchar.quest.FDM_cabin));
				dialog.text = "Also, du musstest mich bringen "+FindRussianQtyString(sti(npchar.quest.FDM_cabin))+" Kisten, die du gebracht hast "+FindRussianQtyString(iTemp)+". Ich habe die Bezahlung. Jetzt bin ich dran. Geh und schlendere herum. Mach dir keine Sorgen, ich werde mein Bestes geben.";
				link.l1 = "Gut...";
				link.l1.go = "FDM_cabin_do";
			}
			else
			{
				RemoveItems(pchar, "chest", iTemp);
				dialog.text = "Also, du musstest mich bringen "+FindRussianQtyString(sti(npchar.quest.FDM_cabin))+" Kisten, die du gebracht hast "+FindRussianQtyString(iTemp)+". "+FindRussianQtyString(amount)+" Kisten übrig.";
				link.l1 = "Sehr gut, Meister.";
				link.l1.go = "FDM_cabin_wait";
				npchar.quest.FDM_cabin = amount;
			}
		break;
		
		case "FDM_cabin_do":
			DialogExit();
			SetLaunchFrameFormParam("Five days later..."+ NewStr() +"Master Alexus has done his job", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.CabinType = npchar.quest.FDM_cabin.type;
			if (CheckAttribute(npchar, "quest.FDM_sails")) npchar.quest.FDM_full = "done";
			else DeleteAttribute(npchar, "quest.FDM_full");
		break;
		
		case "FDM_sails":
			dialog.text = "Sicher, ich kann das machen! Nun... Das bedeutet, dass wir jeden schmutzigen alten Lappen wegwerfen und neue und klare Segel aus Baumwolle setzen müssen. Hier gibt es viel zu tun. Hunderttausend Pesos für Arbeit und Materialien. Abgemacht?";
			if (sti(Pchar.money) >= 100000)
			{
				link.l1 = "Sicher, das passt mir. Abgemacht!";
				link.l1.go = "FDM_sails_do";
			}
			link.l2 = "Hm. Ich denke, ich muss darüber nachdenken...";
			link.l2.go = "exit";
		break;
		
		case "FDM_sails_do":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "Gut. Ich habe die Münzen, Zeit meine Arbeit zu machen. Lauf herum, bis es erledigt ist und mach dir keine Sorgen.";
			link.l1 = "Gut...";
			link.l1.go = "FDM_sails_done";
		break;
		
		case "FDM_sails_done":
			DialogExit();
			SetLaunchFrameFormParam("Two days later..."+ NewStr() +"Master Alexus has done his job", "", 0, 5);
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//белый хлопковый парус
			npchar.quest.FDM_sails = "true";
			if (CheckAttribute(npchar, "quest.FDM_cabin")) npchar.quest.FDM_full = "done";
		break;
		//--> Xenon
		case "FDM_hull":
			dialog.text = "Nun, ich bin froh, das endlich zu hören. Und wahrhaftig - du scheinst ein feiner Kerl zu sein, segelst aber auf Gott weiß was. Aber lass mich dich vorwarnen, dieser Job ist nicht nur für ein paar Stunden, und es wird dich ein hübsches Sümmchen kosten. ";
			link.l1 = "Ok, könnten Sie etwas genauer sein?";
			link.l1.go = "FDM_hull_01";
		break;

		case "FDM_hull_01":
			dialog.text = "Gut, lass uns rechnen... Für eine komplette Überholung des Schiffsrumpfs benötige ich 150 Einheiten Eisenholz, 130 Rollen Seile, 170 Rollen Schiffsseide und 200 Fässer Harz. Für all das nehme ich 250 Tausend Pesos. Und schau mich nicht so an - das meiste von dem Geld geht sowieso in die Arbeit! Schließlich bauen wir keine Tartane um.";
			link.l1 = "Ich denke nicht. Ich habe keine Lust, eine solch riesige Menge an Materialien zu transportieren und dazu noch eine Viertelmillion für den Job zu bezahlen. Ich denke, ich werde so weitersegeln, wie es ist.";
			link.l1.go = "FDM_hull_thinking";
			link.l2 = "Eh, was werden wir nicht alles für unser Schiff tun...Na gut, es ist ein Deal.";
			link.l2.go = "FDM_hull_02";
		break;

		case "FDM_hull_02":
			dialog.text = "Gut, weniger Gespräch, mehr Aktion. Ich werde auf das Geld von dir warten, damit ich anfangen kann, alles zu kaufen, was ich brauche. Sobald ich das Geld habe, kannst du anfangen, mir die Materialien zu bringen. Und ich werde an deinem Schiff arbeiten.";
			if(sti(pchar.money) >= 250000)
			{
    			link.l1 = "Nun, Geld ist kein Problem. Ich habe es bei mir. Hier haben Sie es, Meister.";
    			link.l1.go = "FDM_hull_waitmaterials";
            }
            else
            {
    			link.l1 = "Im Moment habe ich nicht so viel Geld. Warte ein wenig, ich bringe es für dich.";
    			link.l1.go = "FDM_hull_waitmoney";
            }
		break;

		case "FDM_hull_waitmaterials":
			addMoneyToCharacter(pchar, -250000);
			npchar.quest.FDMsandal = 0;
			npchar.quest.FDMoil = 0;
			npchar.quest.FDMshipsilk = 0;
			npchar.quest.FDMropes = 0;
			AddQuestRecord("renovate_fdm", "1");

			npchar.quest.FDM_hull = "hull_waitmaterials";
			dialog.text = "Nicht ängstlich, mit so einer ordentlichen Summe durch eine Piratensiedlung zu laufen, hehe? Gut, ich mache Witze, das sind alles ehrliche Leute, auf ihre Weise. Jetzt warte ich auf die Materialien. Zur Erinnerung, du musst insgesamt 150 Eisenholz, 130 Rollen Seile, 170 Rollen Schiffsseide und 200 Fässer Harz mitbringen.";
			link.l1 = "Halte durch, ich bringe dir deine Materialien.";
			link.l1.go = "exit";
		break;

		case "FDM_hull_checkmaterials":
			dialog.text = "Sehr gut! Was hast du heute für mich mitgebracht?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && sti(npchar.quest.FDMsandal) < 150)
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "Eisenholz in der Menge von "+FindRussianQtyString(iSan)+".";
				link.l1.go = "FDM_sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && sti(npchar.quest.FDMoil) < 200)
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "Harz in der Menge von "+FindRussianQtyString(iOil)+".";
				link.l2.go = "FDM_oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && sti(npchar.quest.FDMshipsilk) < 170)
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "Schiffsseide in der Menge von "+FindRussianQtyString(iSil)+".";
				link.l3.go = "FDM_shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && sti(npchar.quest.FDMropes) < 130)
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "Seile in der Menge von "+FindRussianQtyString(iRop)+".";
				link.l4.go = "FDM_ropes";
			} 
			link.l5 = "Noch nichts. Wollte nur sicherstellen, dass das Geschäft noch läuft.";
			link.l5.go = "exit";
		break;

		case "FDM_hull_checkmaterials_1":
			if (sti(npchar.quest.FDMsandal) > 149 && sti(npchar.quest.FDMoil) > 199 && sti(npchar.quest.FDMshipsilk) > 169 && sti(npchar.quest.FDMropes) > 129)
			{
				dialog.text = "Wunderbar! Alle Materialien sind vorhanden. Jetzt lasst mich dieses Monster von Euch nehmen. Endlich wird es ein angemessenes Aussehen erhalten.";
				link.l1 = "In Ordnung, genug gemurrt, Meister. Ich erwarte das Ergebnis voller Ungeduld.";
				link.l1.go = "FDM_hull_building";
			}
			else
			{
				dialog.text = "Haben Sie noch etwas, um meinen Tag zu erhellen, Kapitän?";
				link.l1 = "Ach, das ist alles für jetzt.";
				link.l1.go = "exit";
				link.l2 = "Ja, ich habe noch etwas für dich...";
				link.l2.go = "FDM_hull_checkmaterials";
			}
		break;

		case "FDM_sandal": // бакаут
			amount = 150 - sti(npchar.quest.FDMsandal);
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			iTemp = amount-iSan;
			if (iTemp > 0) 
			{
				dialog.text = "Lass sehen... Ich benötige "+FindRussianQtyString(amount)+" aus Eisenholz. Du hast gebracht "+FindRussianQtyString(iSan)+". aus Eisenholz. Daher musst du mir immer noch bringen "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Danke! Ich werde Ihnen den Rest bald besorgen.";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + iSan;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ironwood");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Lass sehen... Ich brauche immer noch "+FindRussianQtyString(amount)+" aus Eisenholz. Du hast mir gebracht  "+FindRussianQtyString(iSan)+". Daher sind wir mit Eisenholz fertig!";
				link.l1 = "Danke!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ironwood"); 
			}
		break;

		case "FDM_oil": // смолы
			amount = 200 - sti(npchar.quest.FDMoil);
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			iTemp = amount-iOil;
			if (iTemp > 0) 
			{
				dialog.text = "Lass mal sehen... Ich brauche "+FindRussianQtyString(amount)+" aus Harz. Du hast gebracht "+FindRussianQtyString(iOil)+". Daher musst du mir immer noch bringen "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Danke! Ich werde Ihnen den Rest bald bringen.";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				npchar.quest.FDMoil = sti(npchar.quest.FDMoil) + iOil;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "resin");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Lass uns sehen... Ich brauche immer noch "+FindRussianQtyString(amount)+" von Harz. Du hast mir gebracht "+FindRussianQtyString(iOil)+". Daher sind wir mit Harz fertig!";
				link.l1 = "Danke!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.FDMoil = makeint(npchar.quest.FDMoil) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "resin");
			}
		break;

		case "FDM_shipsilk": // шёлк
			amount = 170 - sti(npchar.quest.FDMshipsilk);
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			iTemp = amount-iSil;
			if (iTemp > 0) 
			{
				dialog.text = "Lass uns sehen... Ich benötige "+FindRussianQtyString(amount)+" der Schiffsseide. Du hast gebracht "+FindRussianQtyString(iSil)+". Daher musst du mir immer noch bringen "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Danke! Ich werde dir den Rest bald bringen";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + iSil;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ship silk");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Lass sehen... Ich brauche immer noch "+FindRussianQtyString(amount)+" von Schiffsseide. Daher musst du mir noch bringen "+FindRussianQtyString(iSil)+". Daher sind wir fertig mit Schiffsseide";
				link.l1 = "Danke!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ship silk"); 
			}
		break;

		case "FDM_ropes": // канаты
			amount = 170 - sti(npchar.quest.FDMropes);
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			iTemp = amount-iRop;
			if (iTemp > 0) 
			{
				dialog.text = "Lass uns sehen... Ich benötige "+FindRussianQtyString(amount)+" der Seile. Du hast gebracht "+FindRussianQtyString(iRop)+". Daher musst du mir immer noch bringen "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Danke! Ich werde Ihnen bald den Rest bringen";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + iRop;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ropes");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Lass sehen... Ich benötige  "+FindRussianQtyString(amount)+" der Seile. Du hast gebracht "+FindRussianQtyString(iRop)+". Daher sind wir mit Seilen fertig!";
				link.l1 = "Danke!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ropes");
			}
		break;

		case "FDM_hull_thinking":
			DialogExit();
			npchar.quest.FDM_secondtime = true;
		break;

		case "FDM_hull_waitmoney":
			DialogExit();
			npchar.quest.FDM_hull = "hull_waitmoney";
		break;

		case "FDM_hull_givemoney":
			dialog.text = "Nun, hast du das Geld mitgebracht";
			if(sti(pchar.money) >= 250000)
			{
    			link.l2 = "Ja, das habe ich. 250 000 Pesos, wie vereinbart.";
    			link.l2.go = "FDM_hull_waitmaterials";
            }
            else
            {
    			link.l1 = "Noch nicht, warte mal, Meister.";
    			link.l1.go = "exit";
            }
		break;

		case "FDM_hull_building":
			DialogExit();
			SetLaunchFrameFormParam("Five days passed..."+ NewStr() +"Master Alexus completed the job", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //Pass time
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			RealShips[sti(Pchar.Ship.Type)].BaseType = SHIP_RENOVATED_FDM;
			RealShips[sti(Pchar.Ship.Type)].Name = "NewFlyingdutchman1";
			RealShips[sti(Pchar.Ship.Type)].BaseName = "NewFlyingdutchman";
			/* RealShips[sti(Pchar.Ship.Type)].CannonsQuantity = 58;
			RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMax = 58;
			RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMin = 58;
			RealShips[sti(Pchar.Ship.Type)].rcannon = 24;
			RealShips[sti(Pchar.Ship.Type)].lcannon = 24;
			RealShips[sti(Pchar.Ship.Type)].fcannon = 6;
			RealShips[sti(Pchar.Ship.Type)].bcannon = 4; */
			if(Get_My_Cabin() == "My_Cabin") RealShips[sti(Pchar.Ship.Type)].CabinType = "Cabin";	
			else RealShips[sti(Pchar.Ship.Type)].CabinType = "Cabin_Huge";
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//White cotton sail
			RealShips[sti(Pchar.Ship.Type)].HP = GetCharacterShipBaseHP(pchar);
			pchar.ship.hp = GetCharacterShipBaseHP(pchar);
			DeleteAttribute(pchar, "ship.hulls");
			DeleteAttribute(pchar, "ship.blots");	
			CloseQuestHeader("renovate_fdm");
		break;
		//<-- Xenon
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

void checkMatherial_repair(ref Pchar, ref NPChar, int good, int goodType)
{
	int amount;
	string Matherial = "Matherial" + goodType;
	amount = GetSquadronGoods(Pchar, good) - sti(NPChar.Repair.(Matherial));
	
	if (amount < 0)
    {
		amount = amount + sti(NPChar.Repair.(Matherial));
    }
    else
    {
		amount = sti(NPChar.Repair.(Matherial));
    }
    RemoveCharacterGoods(Pchar, good, amount);
    NPChar.Repair.(Matherial) = sti(NPChar.Repair.(Matherial)) - amount;
}

int GetMaterialQtyRepair( ref _chr, int MaterialNum )
{
	if ( sti(_chr.Ship.Type) == SHIP_NOTUSED) return 0;
	
	int   	shipCurHP   = sti(RealShips[sti(_chr.Ship.Type)].HP);
	int   	shipBaseHP	= sti(RealShips[sti(_chr.Ship.Type)].BaseHP);	
	int   	shipClass   = sti(RealShips[sti(_chr.Ship.Type)].Class);
	int     shipWeight  = CWT2Tonnes(sti(RealShips[sti(_chr.Ship.Type)].Weight));
	int     HPPrice     = shipWeight * (1.2 - makefloat(shipCurHP)/makefloat(shipBaseHP));
	int     modifier    = (2 * MOD_SKILL_ENEMY_RATE) + sti(RealShips[sti(_chr.Ship.Type)].MinCrew)/2 + 1;	

	float   fQuest 	= 1.0;
	if(CheckAttribute(&RealShips[sti(_chr.Ship.Type)], "QuestShip")) 
	{
		fQuest  = 1.3;
		HPPrice = HPPrice * 2;
	}					
	
	int     Matherial1 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
	int     Matherial2 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
	int     Matherial3 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
	int     Matherial4 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
		
	if(MaterialNum == 0) return HPPrice;	
	if(MaterialNum == 1) return Matherial1;
	if(MaterialNum == 2) return Matherial2;
	if(MaterialNum == 3) return Matherial3;
	if(MaterialNum == 4) return Matherial4;
	
	return 0;
}
