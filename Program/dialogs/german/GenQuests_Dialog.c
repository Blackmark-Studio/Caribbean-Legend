void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ref rItem, rChar, sld, MerPrm;
	aref arTemp1, arTemp2;
	bool bTemp;
	int iBanditsCount, i, iMoney, iNation, iTmp, iGoods, iRank, iScl;
	String sTitle, sGroup, sTemp, sText; // belamour 
	float locx, locy, locz;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Das ist ein Fehler. Kontaktiere die Entwickler und informiere sie, wie und wo du ihn gefunden hast";
					link.l1 = RandSwear()+"Ich werde es ihnen mitteilen!";
					link.l1.go = "exit";
					
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Soldier_")) // Солдеры по квесту "встреча в бухте"
			{
				dialog.text = "Ich bin nicht befugt, mit Ihnen zu verhandeln. Sprechen Sie mit unserem Offizier.";
					link.l1 = LinkRandPhrase("Natürlich...","Ich sehe.","Sicherlich!");
					link.l1.go = "exit";
				break;
			}
			
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Officer_")) // Офицер по квесту "встреча в бухте"
			{
				dialog.text = "Stell dich vor! Ich will wissen, mit wem ich rede!";
					link.l1 = "Mein Name ist "+GetFullName(PChar)+". Was geht hier vor?";
					link.l1.go = "ContraMeetManQuest_Sold_1";
				break;
			}
					
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && PChar.location == PChar.GenQuest.ContraMeetMan.ShoreID) // Квестовый чел по генеру "meeting in the cove" 
			{
				dialog.text = "Käpt'n, dein Name ist "+GetFullName(PChar)+", nicht wahr?";
					link.l1 = "Ja, du hast recht.";
					link.l1.go = "ContraMeetManQuest_1";
					link.l2 = "Nein. Du hast mich mit jemand anderem verwechselt.";
					link.l2.go = "exit";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && CheckAttribute(PChar, "GenQuest.ContraMeetMan.ContraIsDead")) // В комнате таверны после убицства контриков
			{
				LAi_LocationFightDisable(LoadedLocation, false);
				dialog.text = PChar.name+", vielen Dank! Wenn es dich nicht gäbe, wäre mein Schicksal unerträglich... Wie kann ich dir danken?";
					link.l1 = "Ich brauche nichts...";
					link.l1.go = "ContraMeetManQuest_7";
					link.l2 = "Ich würde eine kleine Belohnung nicht ablehnen.";
					link.l2.go = "ContraMeetManQuest_8";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_Contrick_0") // Контрик в комнате по квесту "встреча в бухте"
			{
				iMoney = (rand(3)+2)*500;
				PChar.GenQuest.ContraMeetMan.Money = iMoney;
				if(!CheckAttribute(PChar, "GenQuest.ContraMeetMan.ManIsTraitor")) // Просто платят деньги
				{
					dialog.text = "...Hmm, das ist er tatsächlich... Danke, "+GetSexPhrase("Kamerad","lass")+", ohne deine Hilfe hätten wir es schwer gehabt, es gibt keinen Weg für uns, die Stadt zu verlassen. Hier, nimm "+FindRussianMoneyString(iMoney)+" und du kannst verschwinden. Und wir werden ein 'Gespräch' mit unserem Freund führen...";
						link.l1 = "...";
						link.l1.go = "ContraMeetManQuest_3";
				}
				else
				{
					dialog.text = "...Hmm, das ist er tatsächlich... Danke, "+GetSexPhrase("Kamerad","lass")+", ohne deine Hilfe hätten wir es schwer gehabt, es gibt keinen Weg für uns, die Stadt zu verlassen. Hier, nimm "+FindRussianMoneyString(iMoney)+" und du kannst dich verlaufen. Wir werden diesen schmutzigen Verräter jetzt ausnehmen!";
						link.l1 = "Natürlich. Bis wir uns wiedersehen, Herren...";
						link.l1.go = "ContraMeetManQuest_4";
						link.l2 = "Was?! Nein, ich werde nicht zulassen, dass du einen Mann ermordest, egal wer er ist... Und ich brauche dein verdammtes Geld nicht!";
						link.l2.go = "ContraMeetManQuest_5";
				}
					break;
			}
			
			if(NPChar.id == "ContraDeliverQuest_Soldier_0") // Солдер в комнате
			{
				dialog.text = "So... Was haben wir hier? Piraten?! Ihr müsst mit uns ins Kommandantenbüro zur Untersuchung kommen...";
					link.l1 = "Wir sind überhaupt keine Piraten! Ich kenne diesen Mann nicht einmal! Er hat gerade dieses Zimmer gemietet und eingezogen und ich hatte keine Zeit, meine Sachen zu packen und zu gehen!";
					link.l1.go = "ContraDeliverQuest_Sold1";
					break;
			}
				
			if(CheckAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom") && NPChar.id == "ContraDeliverQuest_Contra_1")
			{
				dialog.text = "Also, was sagten Sie? Sie haben eine Nachricht für mich?! Ich warte!";
					link.l1 = "Hier, bitte...";
					link.l1.go = "ContraDeliverQuest_1";
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom");
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.GoToTavern");
					break;
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "Hallo, du! Ja, du. Ich sehe, dass du ein anständiger und wohlhabender Mann bist.";
					link.l1 = "Kann dasselbe nicht über dich sagen.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_1";
					break;
			}
					
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.WayOfShortVariant") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "Halt an! Hey, "+GetSexPhrase("Kumpel","Lass")+", zeig uns doch, wie schwer dein Beutel ist!";
					link.l1 = "Also, hast du schon all das Kirchengeld verschwendet?";
					link.l1.go = "Church_GenQuest_2_1";
					break;
			}
			
			if(NPChar.id == "ReasonToFast_Hunter")
			{
				if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > sti(pchar.questTemp.ReasonToFast.p2))
				{
					dialog.text = "Hallo, im Boot! Hic... Räum die Fahrrinne - Ich muss mit den Jungs reden...";
					link.l1 = "Bist du nicht ein bisschen benommen, Kumpel? Geh schlafen.";
					link.l1.go = "ReasonToFast_Hunter1";
				}
				else
				{
					dialog.text = "He, Käpt'n! Lass den Anker fallen!";
					link.l1 = "Und warum zum Teufel sollte ich....";
					link.l1.go = "ReasonToFast_Hunter2";
				}
				link.l2 = "Bist du nicht ein bisschen zu unhöflich!?";
				link.l2.go = "ReasonToFast_Hunter3";	
			}
			
			if(NPChar.id == "PirateOnUninhabited_0")
			{
				dialog.text = RandPhraseSimple("Heil dir! Endlich hat der Herr unsere Gebete erhört und einen tapferen Kapitän an dieses verlassene Ufer gesandt!","Dank der Vorsehung! Jetzt werden die örtlichen Aasfresser nicht unsere faulen Knochen fressen!");
				link.l1 = "Hallo, guter Mann, ich bin Kapitän "+GetFullName(PChar)+". Ich sehe, du bist hier ziemlich in Schwierigkeiten.";
				link.l1.go = "PiratesOnUninhabited_3";
				link.l2 = "Guter Mann, ich habe meine eigenen Angelegenheiten zu erledigen und habe keine Zeit, mich mit deinen Schwierigkeiten zu befassen.";
				link.l2.go = "PiratesOnUninhabited_1";
			}
			
			if(NPChar.id == "ShipWreck_0")
			{
				dialog.text = RandPhraseSimple("Oh, Kapitän! Es ist einfach ein gutes Schicksal, dass Gott Ihnen günstigen Wind geschickt und Sie an diesen verlassenen Ort geführt hat!","Kapitän! Dank der Vorsehung, dass Sie beschlossen haben, an diesem verlassenen Ufer Anker zu werfen!");
				link.l1 = "Hallo, guter Mann, ich bin Kapitän "+GetFullName(pchar)+". Ich sehe, du bist hier in ernsten Schwierigkeiten.";	
				link.l1.go = "ShipWreck_2";
				link.l2 = "Guter Mann, ich habe meine eigenen Angelegenheiten zu erledigen und ich habe keine Zeit, mich mit deinen Problemen zu beschäftigen.";
				link.l2.go = "ShipWreck_1";
			}
			
			if(NPChar.id == "Convict_0")
			{
				dialog.text = LinkRandPhrase("Halt ein, "+GetAddress_Form(pchar)+"! Würden Sie uns eine Minute Ihrer kostbaren Zeit schenken?","Wäre ein edler Fehltritt"+GetSexPhrase("ter","s")+" hören Sie auf eine bescheidene Bitte dieser unwürdigen Männer?","Edler Irrtum"+GetSexPhrase("ter","s")+", bitte geben Sie nur ein wenig Ihrer kostbaren Zeit, um mit dem Unglücklichen zu sprechen.");
				link.l1 = LinkRandPhrase("Ich habe keine Zeit für das.","Verschwinde, ich habe viel zu tun ohne dich.","Lass mich in Ruhe, ich habe keine Zeit für dich.");
				link.l1.go = "Convict_0End";
				link.l2 = LinkRandPhrase("Was willst du?","Was brauchst du?","Was ist das Problem?");
				link.l2.go = "Convict_Begin";
			}
			
			// Warship, 15.05.11. Генер "Justice for sale".
			if(HasSubStr(NPChar.id, "JusticeOnSale_Jungle_"))
			{
				dialog.text = "Hallo, Käpt'n! Haben Sie Interesse an indischen Krimskrams und Waren, die man nicht in den gewöhnlichen Läden kaufen kann. Oder vielleicht an Bargeld?";
					link.l1 = "Lumpenpack wie du fordert normalerweise - bietet nichts an. Warum bist du so seltsam zuvorkommend?";
					link.l1.go = "JusticeOnSale_1";
					link.l2 = "Meine Pistole redet normalerweise mit Bastarden wie dir!";
					link.l2.go = "JusticeOnSale_2";
			}
		break;
		
		// Генератор "Situation in the hold - Ransom"
		case "Hold_GenQuest1":
			pchar.quest.Hold_GenQuest_FindCharTimeIsOver.over = "yes";
			dialog.text = "Ich höre Ihnen zu, Kapitän. Sind Sie geschäftlich hier?";
			link.l1 = "Ich suche Herrn "+pchar.GenQuest.Hold_GenQuest.Name+"?";
			link.l1.go = "Hold_GenQuest2";
		break;
		
		case "Hold_GenQuest2":
			dialog.text = RandPhraseSimple("Ich bin Herr "+pchar.GenQuest.Hold_GenQuest.Name+". Wem habe ich die Ehre zu verdanken?","Du hast ihn gefunden. Was kann ich für dich tun?");
			link.l1 = "Ich bin Kapitän "+GetFullName(pchar)+", ich wollte mit dir über etwas sprechen "+pchar.GenQuest.Hold_GenQuest.CapName+".";
			link.l1.go = "Hold_GenQuest3";
		break;
		
		case "Hold_GenQuest3":
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			pchar.GenQuest.Hold_GenQuest.RansomSum = makeint(3 * sti(sld.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(sld, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500); 
						
			switch(hrand(3))
			{
				case 0:
					dialog.text = "Und wer ist es?";
					link.l1 = "Halt ein... Du bist "+pchar.GenQuest.Hold_GenQuest.Name+", und du weißt nichts darüber "+pchar.GenQuest.Hold_GenQuest.CapName+"?";
					link.l1.go = "Hold_GenQuest40";
				break;
				case 1:
					dialog.text = "Wow! Es ist schon eine Weile her, dass ich das letzte Mal von diesem alten Fuchs gehört habe? Was ist ihm diesmal passiert?";
					link.l1 = "Dieses Mal ist er in ernsten Schwierigkeiten... Er wird gefangen gehalten und er braucht deine Hilfe.";
					link.l1.go = "Hold_GenQuest50";
				break;
				case 2:
					dialog.text = "In Ordnung, ich bin ganz Ohr.";
					link.l1 = "Sein Schiff wurde von Piraten angegriffen, und er wird jetzt gefangen gehalten. Er riet mir, dich wegen des Lösegeldes zu sehen.";
					link.l1.go = "Hold_GenQuest60";
				break;
				case 3:
					dialog.text = "Ja, ich freue mich, von einem alten Freund zu hören. Wie geht es ihm?";
					link.l1 = "Seine Situation ist so schlimm, dass man es sich kaum vorstellen kann.";
					link.l1.go = "Hold_GenQuest70";
				break;				
			}	
		break;
		
		case "Hold_GenQuest40":
			// dialog.text = "Ja, das bin ich "+pchar.GenQuest.Hold_GenQuest.Name+"! Aber warum sollte ich etwas darüber wissen "+pchar.GenQuest.Hold_GenQuest.CapName+"Was?!";
			dialog.text = "Das stimmt, ich bin "+pchar.GenQuest.Hold_GenQuest.Name+"! Aber Name "+pchar.GenQuest.Hold_GenQuest.CapName+" sagt mir nichts."; // belamour gen
			link.l1 = "Es tut mir leid. Vielleicht habe ich mich geirrt...";
			link.l1.go = "Hold_GenQuest41";
		break;
		
		case "Hold_GenQuest41":
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest50":
			dialog.text = "Wahnsinn! Und wie soll ich ihm helfen? Indem ich ihn befreie, indem ich all seine Feinde töte oder was? Ha-ha-ha!";
			link.l1 = "Nein-nein, das ist nicht notwendig. Sie müssen nur übergeben "+pchar.GenQuest.Hold_GenQuest.RansomSum+" Pesos als Lösegeld.";
			link.l1.go = "Hold_GenQuest51";
		break;		
		
		case "Hold_GenQuest51":
			dialog.text = "Was für eine Frechheit! Und warum sollte ich Lösegeld für ihn zahlen?! Er ist weder mein Verwandter noch Freund!";
			link.l1 = "Hmm... Er hat mir gesagt, dass du seine einzige Hoffnung bist. Und er hat auch eine Schuld von dir erwähnt...";
			link.l1.go = "Hold_GenQuest52";
		break;		
		
		case "Hold_GenQuest52":
			dialog.text = LinkRandPhrase("Wie ein frecher Kerl! Er ist es, der mir Geld schuldet, nur zur Ihrer Information! Aber das ist kein Grund für mich, ihn zu erpressen in der Hoffnung, dass er beide Schulden bezahlt.","Was für ein Schurke! Er hat mich betrogen, als wir unser Geschäft aufteilten, und jetzt hat er die Frechheit, mich um Lösegeld für ihn zu bitten!","Jetzt ist das eine Überraschung! Warum sollte ich Lösegeld für ihn zahlen?! Wir sind nicht so eng befreundet.");
			link.l1 = "Also, ich kann ihm sagen, dass du dich geweigert hast, sein Lösegeld zu zahlen und deine Schuld nicht anerkannt hast?";	
			link.l1.go = "Hold_GenQuest53";
		break;
		
		case "Hold_GenQuest53":
			dialog.text = "Ach du meine Güte! Von welcher Schuld sprichst du? Ich habe dir bereits alles erklärt! Und wenn du keine weiteren Fragen zu dieser lächerlichen Geschichte hast, dann erlaube mir, mich zu verabschieden.";
			link.l1 = "Ich verstehe. Nun, ich habe keine weiteren Fragen an dich, aber einige an deinen Kumpel.";
			link.l1.go = "Hold_GenQuest54";
		break;
		
		case "Hold_GenQuest54":
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar)); // НПС вешать собрались? )))
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen				
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest60":
			dialog.text = "Hmm... Und Sie, wie ich verstehe, sind derjenige, der ihn festhält... Nun, ich denke, ich werde ihm helfen.";
			link.l1 = "Sehr gut. Das Lösegeld wird sein "+pchar.GenQuest.Hold_GenQuest.RansomSum+" Pesos.";
			link.l1.go = "Hold_GenQuest61";
		break;
		
		case "Hold_GenQuest61":
			dialog.text = "Sie haben mich missverstanden: Ich bin Mitglied des Stadtrats. Wir achten auf die Einhaltung der Charta.\n"+"Wachen!!! Wachen! Verhaftet ihn wegen Verdachts auf Sklavenhandel und Plünderung von Schiffen "+NationNameGenitive(sti(pchar.GenQuest.Hold_GenQuest.Nation))+"!";
			link.l1 = "Nun, 'Kumpel', lass mich nur zu dir kommen...";
			link.l1.go = "Hold_GenQuest62";
		break;
		
		case "Hold_GenQuest62":
			LAi_SetImmortal(NPChar, false);
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen	
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_SetWarriorTypeNoGroup(NPChar);
   	        LAi_warrior_DialogEnable(NPChar, false);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");			
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheckFunction("TmpEnemy", "Hold_GenQuest_AfterBattle");
			chrDisableReloadToLocation = true; 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);  
			AddDialogExitQuest("MainHeroFightModeOn"); 
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
			DialogExit();
		break;
		
		case "Hold_GenQuest70":
			dialog.text = "Was sagst du?! Und wie kann ich ihm helfen?";
			link.l1 = "Er wird gefangen gehalten und er hat mich gebeten, mit dir über sein Lösegeld zu sprechen.";
			link.l1.go = "Hold_GenQuest71";
		break;		
		
		case "Hold_GenQuest71":
			dialog.text = "Natürlich, natürlich. Ich werde alles tun, was ich kann. Wo halten sie sie fest? Und wie hoch ist das Lösegeld?";
			link.l1 = "Die Piraten verlangen "+pchar.GenQuest.Hold_GenQuest.RansomSum+" Pesos. Ich muss das Geld zum Hafen bringen, und dann wird dein Freund frei sein.";
			link.l1.go = "Hold_GenQuest72";
		break;
		
		case "Hold_GenQuest72":
			dialog.text = "Hier ist das Geld. Glücklicherweise hatte ich genug bei mir.";
			link.l1 = "Ja, das ist in der Tat glücklich. Geh dann zum Hafen und bald wirst du deinen Kameraden wiedersehen.";
			link.l1.go = "Hold_GenQuest73";
		break;
		
		case "Hold_GenQuest73":
			addMoneyToCharacter(pchar, sti(pchar.GenQuest.Hold_GenQuest.RansomSum));
			AddQuestRecord("HoldQuest", "11");
			AddQuestUserData("HoldQuest", "sNameChar", GetFullName(NPChar)); // belamour gen 
			AddQuestUserData("HoldQuest", "sName", NPChar.Hold_GenQuest.Name); // belamour gen
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.RansomSum);
			pchar.GenQuest.Hold_GenQuest = "prisoner_ransom";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;				
		// Генератор "Situation in the hold - Ransom"
		
		// Генератор "Situation in the hold - Partner in crime"
		case "Hold_GenQuest80":
			dialog.text = "Hallo, Kapitän, tut mir leid, dass ich nicht die Ehre hatte, vorgestellt zu werden. Sie sagten, Sie suchten nach mir.";
			link.l1 = "Tatsächlich, wenn Sie der Herr sind "+pchar.GenQuest.Hold_GenQuest.Name+". Ich bin Kapitän "+GetFullName(pchar)+", ich wollte mit dir sprechen.";
			link.l1.go = "Hold_GenQuest81";
		break;
		
		case "Hold_GenQuest81":
			dialog.text = "Und um welche Art von Geschäft handelt es sich, Kapitän "+GetFullName(pchar)+"?";
			link.l1 = "Ich habe gehört, dass du etwas besitzt, von dem du dich nicht ungerne trennen würdest.";
			link.l1.go = "Hold_GenQuest82";
		break;
		
		case "Hold_GenQuest82":
			dialog.text = "Was willst du damit andeuten?";
			link.l1 = "Sei nicht so stur, mein guter Mann, ich weiß sehr wohl über deine dunkle Vergangenheit, und über eine behelfsmäßige Karte, auf der der Standort des Schatzes verzeichnet ist"+GetName(NAMETYPE_VIP,pchar.GenQuest.Hold_GenQuest.PirateName,NAME_ACC)+" wird angezeigt.";
			link.l1.go = "Hold_GenQuest83";
		break;
		
		case "Hold_GenQuest83":
			dialog.text = "Verdammt! Ich wusste schon immer, dass dieser Schurke"+pchar.GenQuest.Hold_GenQuest.CapName+" würde das früher oder später ausplaudern! Was habe ich mir dabei gedacht, ihm dieses Angebot zu machen?";
			link.l1 = "Hör schon auf zu jammern. Ich meine es nicht böse... Verkauf mir einfach diese Karte und führe das Leben, an das du gewöhnt bist.";
			link.l1.go = "Hold_GenQuest84";
		break;
		
		case "Hold_GenQuest84":
			dialog.text = "Wenn ich mir nur so sicher sein könnte... Und wie viel bietest du mir dafür an? Du musst doch wissen, dass in der Kiste viel Gold war. Sie wurde von vier Männern getragen, der Herr möge ihre Seelen ruhen lassen...";
			link.l1 = "Aber "+GetName(NAMETYPE_VIP,pchar.GenQuest.Hold_GenQuest.PirateName,NAME_NOM)+" könnte schon seinen Schatz beansprucht haben...";
			link.l1.go = "Hold_GenQuest85";
		break;
		
		case "Hold_GenQuest85":
			dialog.text = "Wahrlich auch... Nun, ich bin bereit, es dir für "+pchar.GenQuest.Hold_GenQuest.Sum+" Pesos. Ich würde es sowieso nicht wagen, die Toten zu stören.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Hold_GenQuest.Sum) && !CheckCharacterItem(pchar,"mapQuest") && !CheckCharacterItem(pchar,"map_full"))
			{
				link.l1 = "Gut. Du hast einen Deal.";
				link.l1.go = "Hold_GenQuest86";
			}	
			link.l2 = "Nein, mein guter Mann, dieses Stück Papier ist dieses Geld nicht wert. Lebewohl...";
			link.l2.go = "Hold_GenQuest87";
			pchar.quest.Hold_GenQuest_GetMapTimeIsOver.over = "yes";
		break;
		
		case "Hold_GenQuest86":		
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Hold_GenQuest.Sum));
			GiveItem2Character(pchar, "mapQuest"); 
			rItem = ItemsFromID("mapQuest");
			Hold_GenQuest_GenerateTreasureMap(rItem);
			AddQuestRecord("HoldQuest", "15");
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);						
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;	
		
		case "Hold_GenQuest87":
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			AddQuestRecord("HoldQuest", "16");
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_GEN)); // belamour gen
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);			
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");				
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		// Генератор "Situation in the hold - Partner in crime"
		
		// Генератор "Shipwrecked"
		case "ShipWreck_1":
			dialog.text = "Wie kann das möglich sein, Kapitän?! Gott wird Ihnen eine solche Sünde niemals vergeben.";
			link.l1 = "Es liegt an Ihm zu entscheiden.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
		
		case "ShipWreck_2":
			pchar.GenQuest.ShipWreck.StartShipType = PiratesOnUninhabited_GenerateShipType(); 		
			pchar.GenQuest.ShipWreck.ShipTypeName = GenerateRandomNameToShip(sti(pchar.GenQuest.ShipWreck.Nation));			
			
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("Hallo, ich bin "+pchar.GenQuest.ShipWreck.Name+", Kapitän des "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Konto"))+" '"+pchar.GenQuest.ShipWreck.ShipTypeName+", mein Schiff ist nicht weit von der Küste an den Riffen gescheitert."+"Nur wenige Matrosen der gesamten Besatzung haben überlebt. Die Flut hat uns an dieses verlassene Ufer gespült. Wir haben gehungert und gedurstet für "+(5+hrand(7))+" Wochen jetzt schon","Hallo, ich bin "+pchar.GenQuest.ShipWreck.Name+", Kapitän des "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Gen"))+" '"+pchar.GenQuest.ShipWreck.ShipTypeName+". Unser Schiff ist nicht weit von hier abgestürzt."+"Wir haben es geschafft, mit den Schiffswracks an dieses Ufer zu gelangen, aber dieser Ort scheint unbewohnt zu sein. Wir waren gezwungen, uns von Muscheln und Palmenfrüchten zu ernähren für "+(5+hrand(7))+" Wochen jetzt schon.");
				link.l1 = RandPhraseSimple("Und wie viele von euch sind übrig?","Und wie viele von euch haben überlebt?");
				link.l1.go = "ShipWreck_3";
			}
			else
			{						
				pchar.GenQuest.ShipWreck.Mutiny = "true"; // belamour gen кавычки
				pchar.GenQuest.ShipWreck.BadName = GenerateRandomName_Generator(sti(pchar.GenQuest.ShipWreck.Nation), "man");
				pchar.GenQuest.ShipWreck.City = GetQuestNationsCity(sti(pchar.GenQuest.ShipWreck.Nation));
				dialog.text = "Oh, Kapitän, unsere Verluste sind wirklich schrecklich... Hallo, ich bin "+pchar.GenQuest.ShipWreck.Name+", Kapitän und Besitzer von "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Gen"))+" '"+pchar.GenQuest.ShipWreck.ShipTypeName+". Oder sollte ich sagen, ehemaliger Kapitän und Besitzer. "+"Dieser Bastard "+pchar.GenQuest.ShipWreck.BadName+" den ich eingestellt habe in "+XI_ConvertString("Colony"+pchar.GenQuest.ShipWreck.City+"Voc")+" hatte meine Crew zur Meuterei provoziert. Am Ende landeten wir an diesem verlorenen Ort. Es geschah "+(5+hrand(7))+" vor einigen Wochen.";
				link.l1 = "Und dann? Hat deine gesamte Mannschaft sich den Meuterern angeschlossen?";
				link.l1.go = "ShipWreck_4";			
			}
		break;
		
		case "ShipWreck_3":
			dialog.text = RandPhraseSimple("Von der gesamten Besatzung, nur "+ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty))+" survived. Other's have perished; several of them died already here of wounds and fever",
				"Only " + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + " were lucky enough. Others have met their end... either in the deep or in the dunes of this coast.");
			link.l1 = LinkRandPhrase("Ja, das ist ein beneidenswertes Schicksal. Aber so ist das Los des Seemanns - jeder könnte an deiner Stelle enden.","Ich sehe... Gott hält jedes Leben, es ist nur so, dass er zu beschäftigt ist, sich an jeden zu erinnern.","Allerdings. Der Mensch denkt, aber Gott lenkt.");
			link.l1.go = "ShipWreck_5";	
		break;
		
		case "ShipWreck_4":
			dialog.text = "Natürlich nicht! Diejenigen, die sich weigerten, sich den Meuterern anzuschließen, waren viele, aber diese Schurken haben das Arsenal erobert, und es ist gut, dass wir keinen Widerstand geleistet haben, sonst wären wir direkt getötet worden. Viele sind hier bereits dem Fieber und dem Gift von giftigen Insekten erlegen, nur "+ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty))+" überlebt. Gott sei Dank, unsere Prüfungen sind endlich vorbei.";
			link.l1 = RandPhraseSimple("Ja, das war sicherlich ein Schlag des Pechs.","Oh, na ja, viele seltsame Dinge können an diesen gottverlassenen Orten passieren.");
			link.l1.go = "ShipWreck_5";			
			link.l2 = "Halt ein, Freund. Und wie soll ich wissen, dass du nicht als Anstifter einer Meuterei an Land gesetzt wurdest?";
			link.l2.go = "ShipWreck_6";			
		break;
		
		case "ShipWreck_5":
			dialog.text = RandPhraseSimple("Kapitän, ich hoffe doch, dass Sie mehrere freie Schließfächer auf Ihrem Schiff haben. Wir alle haben Familien und sie trauern wahrscheinlich um unseren Verlust, während wir sprechen. Wir wären Ihnen sehr dankbar.","Kapitän, wir sind völlig verzweifelt, Sie sind unsere einzige Hoffnung. Bitte, verweigern Sie uns nicht Ihre Hilfe, nehmen Sie uns von diesem gottverlassenen Land.");
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l1 = "Ohh... und wohin möchtest du, dass ich dich bringe?";
				link.l1.go = "ShipWreck_7";			
			}
			link.l2 = RandPhraseSimple(RandPhraseSimple("Es tut mir wirklich leid, aber es gibt nicht mal eine freie Hängematte, geschweige denn Kabinen. Die Seeleute schlafen auf dem Deck, sie können sich nicht mal nach einer Wache gut erholen...","Ich würde Sie wirklich ungern enttäuschen, aber das Schiff ist überladen und die Leute müssen bei schlechtem Wetter schlafen. Sollte eine Krankheit ausbrechen, werde ich die Hälfte der Besatzung verlieren."),RandPhraseSimple("Es tut mir wirklich leid, aber es gibt absolut keinen freien Platz mehr auf meinem Schiff. Ich kann keine weiteren Passagiere an Bord nehmen.","Muss dich enttäuschen, aber mein Schiff ist überladen. Ich fürchte die Epidemie."));
			link.l2.go = "ShipWreck_8";	
			if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "Du bist ein erfahrener Seemann und du solltest wissen, dass die Anwesenheit von jemandem, der einen Schiffbruch erlitten hat, ein sehr schlechtes Zeichen ist. Meine Seeleute werden dich einfach über Bord werfen.";
				link.l3.go = "ShipWreck_9";
			}
		break;
		
		case "ShipWreck_6":
			dialog.text = "Was sagst du, "+GetAddress_Form(npchar)+" "+pchar.lastname+"?! Habt ein Herz! Ich bin ein Händler, bekannt in der Karibik! Nun... Ich schätze, ich war mal einer. Nicht jetzt, ohne ein Schiff oder Geld...";
			link.l1 = "Wie bitte... Ich wette, ihr wart die eigentlichen Anstifter der Meuterei, und jetzt habt ihr bekommen, was ihr verdient habt.";
			link.l1.go = "ShipWreck_18";
			if(GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "Aber was für ein Schurke ist das "+pchar.GenQuest.ShipWreck.BadName+"! Wirst du das wirklich durchgehen lassen und dein Schicksal akzeptieren?";
				link.l2.go = "ShipWreck_19";
			}	
		break;		
		
		case "ShipWreck_7":
			if(rand(1) == 0)
			{
				if(rand(100) < 90)
				{
					pchar.GenQuest.ShipWreck.variant = "1";
					dialog.text = "Zu jeder Siedlung von "+NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation))+".";
					link.l1 = "Nun, ich habe genug freie Schränke und Hängematten. Beladen Sie sich ins Boot.";
					link.l1.go = "ShipWreck_10";
					link.l2 = "Hmm... Wir haben Kämpfe vor uns, und ich weiß nicht, wo du sicherer sein wirst, an Bord meines Schiffes oder in dieser gemütlichen Bucht.";
					link.l2.go = "ShipWreck_11";
				}
				else
				{				
					dialog.text = "Nach Dünkirchen! Meine Mutter lebt dort...";
					link.l1 = "Bist du verrückt oder was?! Ich nehme an, du hast zu viele Schläge auf den Kopf bekommen...";
					link.l1.go = "ShipWreck_12";					
					pchar.GenQuest.ShipWreck.Crazy = true; // получите психа на борт :-)
					
				}				
			}
			else
			{
				pchar.GenQuest.ShipWreck.variant = "2";
				dialog.text = "Wo immer du willst, es ist uns wirklich egal. Wir haben sowieso nichts, um dich zu bezahlen...";
				link.l1 = "Nun, ich habe genug freie Schließfächer und Hängematten. Belade dich selbst auf das Boot.";
				link.l1.go = "ShipWreck_10_1";
				link.l2 = "Hmm... Wir haben Kämpfe vor uns, und ich weiß nicht, wo du sicherer sein wirst, an Bord meines Schiffes oder in dieser gemütlichen Bucht.";
				link.l2.go = "ShipWreck_11";		
			}						
		break;		

		case "ShipWreck_8":
			pchar.GenQuest.ShipWreck.FoodQty = sti(pchar.GenQuest.ShipWreck.Qty) * 10 + rand(10);
			pchar.GenQuest.ShipWreck.MedicamentQty = sti(pchar.GenQuest.ShipWreck.Qty) * 5 + rand(10);
			pchar.GenQuest.ShipWreck.AmunitionQty = sti(pchar.GenQuest.ShipWreck.Qty) * 3 + rand(5);
			pchar.GenQuest.ShipWreck.RumQty = sti(pchar.GenQuest.ShipWreck.Qty) * 7 + rand(10);
			if(GetFreeCrewQuantity(pchar) < sti(pchar.GenQuest.ShipWreck.Qty))
			{
				if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))
				{
					dialog.text = "Aber indem ihr uns ablehnt, verurteilt ihr uns sicherlich zum Tod! Nun, wir werden versuchen, uns den Weg zum Schiff zu bahnen, auch wenn es uns das Leben kostet!";
					link.l1 = "Was? Schaut euch an, ihr könnt kaum auf den Beinen stehen...";
					link.l1.go = "ShipWreck_8_1";
					link.l2 = "Du kannst es versuchen...";
					link.l2.go = "ShipWreck_16";
				}
				else
				{
					dialog.text = "Aber du kannst uns doch nicht einfach hier lassen! Ohne deine Hilfe werden wir alle bald zugrunde gehen!";
					if(GetSquadronGoods(pchar, GOOD_WEAPON) < sti(pchar.GenQuest.ShipWreck.AmunitionQty) || GetSquadronGoods(pchar, GOOD_RUM) < sti(pchar.GenQuest.ShipWreck.RumQty))
					{			
						link.l1 = "Das Einzige, was ich für dich tun kann, ist, dir genug Proviant und Medikamente zu hinterlassen und dir ein Boot zu geben. Zumindest wirst du nicht an Hunger und Durst sterben. Was die Seefahrt betrifft, brauche ich dir das nicht beizubringen.";
						link.l1.go = "ShipWreck_8_2";
					}
					else
					{
						if(rand(1) == 0)
						{
							link.l1 = "Das Einzige, was ich für dich tun kann, ist dir genug Proviant und Medizin zu lassen und dir ein Boot zu geben. Zumindest wirst du nicht an Hunger und Durst sterben. Was die Seefahrt betrifft, brauche ich dir das nicht beizubringen.";
							link.l1.go = "ShipWreck_8_2";
						}
						else
						{
							link.l1 = "Ich kann dir genug Medizin, Munition, Rum und Proviant für einen Monat hinterlassen. Entweder komme ich selbst zurück oder ich schicke jemanden für dich.";
							link.l1.go = "ShipWreck_8_4";
						}
					}
				}
			}
			else
			{
				if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL) // плохиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						dialog.text = "Aber indem ihr uns ablehnt, verurteilt ihr uns sicherlich zum Tode! Nun, wir werden versuchen, uns den Weg zum Schiff zu bahnen, auch wenn es uns das Leben kostet!";
						link.l1 = "Was? Schaut euch doch mal an, ihr könnt kaum auf den Beinen stehen...";
						link.l1.go = "ShipWreck_8_1";
						link.l2 = "Du kannst es versuchen...";
						link.l2.go = "ShipWreck_16";					
					}
					else
					{
						link.l1 = "The only thing I can do for you is leave you enough provisions and medicines and give you a boat. At least you are not going to die of starvation and thirst; as for seafaring, I need not teach you that.";
						link.l1.go = "ShipWreck_8_2";					
					}
				}
				else // кибальчиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						if(rand(1) == 0)
						{
							dialog.text = "Aber indem Sie ablehnen, werden Sie uns sicherlich zum Tode verdammen! Nun, wir werden versuchen, uns den Weg zum Schiff zu bahnen, auch wenn es uns das Leben kostet!";
							link.l1 = "Was? Seht euch doch an, ihr könnt kaum auf euren Füßen stehen...";
							link.l1.go = "ShipWreck_8_1";
							link.l2 = "Du kannst es versuchen...";
							link.l2.go = "ShipWreck_16";						
						}
						else
						{
							dialog.text = "Wie könntest du uns das antun?!.. Du hast nicht nur den Seecodex missachtet, sondern auch deine Ehre besudelt!";
							link.l1 = "Sicherlich bist du nicht derjenige, der über meine Ehre spricht, Krabbe!";
							link.l1.go = "ShipWreck_16";
						}	
					}
					else
					{
						link.l1 = "Das Einzige, was ich für dich tun kann, ist dir genug Proviant und Medizin zu lassen und dir ein Boot zu geben. Zumindest wirst du nicht an Hunger und Durst sterben. Was die Seefahrt betrifft, brauche ich dir das nicht beizubringen.";
						link.l1.go = "ShipWreck_8_2";											
					}						
				}
			}			
		break;				
	
		case "ShipWreck_8_1":
			dialog.text = "Du hast recht, wir haben keine Chance. Nun denn, möge Gott dein Richter sein und jedem das Seine zuteilen.";
			link.l1 = "Nun, ich kann damit umgehen...";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
	
		case "ShipWreck_8_2":
			dialog.text = "Nun... Ihr lasst uns keine Wahl... Wir werden beten, dass die Stürme und der Durst unser Leben nicht nehmen, bevor wir bewohnte Orte erreichen...";
			link.l1 = "Auf Wiedersehen. Möge der Herr über dich wachen...";
			link.l1.go = "ShipWreck_8_3";
		break;
		
		case "ShipWreck_8_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 25);
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.FoodQty + " units of provision.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.MedicamentQty + "units of medicine.");
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_7";
			NextDiag.CurrentNode = NextDiag.TempNode;			
		break;
	
		case "ShipWreck_8_4":	
			dialog.text = "Anscheinend haben wir keine Wahl... Aber ich flehe Sie an, Kapitän, bitte kommen Sie so schnell wie möglich zurück oder schicken Sie uns ein Expeditionsschiff.";
			link.l1 = "Ich werde mir etwas einfallen lassen. Warte einfach ab.";
			link.l1.go = "ShipWreck_8_5";
		break;
	
		case "ShipWreck_8_5":		
			pchar.quest.ShipWreck_LocationExit.over = "yes";
			AddCharacterExpToSkill(pchar, "Leadership", 50); 
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			RemoveCharacterGoods(pchar, GOOD_WEAPON, sti(pchar.GenQuest.ShipWreck.AmunitionQty));
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.GenQuest.ShipWreck.RumQty));			
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.FoodQty + " units of provision.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.MedicamentQty + "units of medicine.");		
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.AmunitionQty + " units of arms.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.RumQty + " units of rum");	
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "11");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);			
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "10");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_6";
			NextDiag.CurrentNode = NextDiag.TempNode;	
			pchar.GenQuest.ShipWreck = "SailorsOnShore";
			SetFunctionTimerCondition("ShipWreck_SaveSailors", 0, 0, 30, false);
			pchar.GenQuest.ShipWreck.Shore = pchar.location;
			SaveCurrentQuestDateParam("GenQuest.ShipWreck");
			SetFunctionLocationCondition("ShipWreck_MeetInShore", pchar.GenQuest.ShipWreck.Shore, true);
		break;
	
		case "ShipWreck_8_6":			
			dialog.text = RandPhraseSimple("Kapitän, bitte vergessen Sie nicht, dass Sie unsere einzige Hoffnung sind...","Warum zögerst du? Jede Minute hier ist unerträglich für uns...");
			link.l1 = "Ich werde alles tun, was ich kann. Leb wohl...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_6";		
		break;

		case "ShipWreck_8_7":			
			dialog.text = RandPhraseSimple("Auf Wiedersehen, Kapitän... Wir müssen uns auf die Reise vorbereiten.","Lebewohl... Und zünde die Kerzen an, um unsere Seelen zu retten...");
			link.l1 = "Auf Wiedersehen. Der Herr möge über dich wachen...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_7";		
		break;
		
		case "ShipWreck_9":
			pchar.GenQuest.ShipWreck = "SailorsOnShoreFight"; // belamour gen
			dialog.text = "Wie konntest du uns das antun?! Du hast nicht nur den Seecode missachtet, du hast auch deine Ehre beschmutzt!";
			link.l1 = "Sicherlich bist du nicht derjenige, der über meine Ehre spricht, Krabbe!";
			link.l1.go = "ShipWreck_16";
		break;					
		
		case "ShipWreck_10":
			dialog.text = "Danke, Kapitän! Das Laden sollte nicht zu viel Zeit in Anspruch nehmen. Gott, wie haben wir für diesen Moment gebetet!";
			link.l1 = "Das ist großartig. Ich hoffe, dass deine Prüfungen bald vorbei sein werden.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Nation_City";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.nation = sti(pchar.GenQuest.ShipWreck.Nation);
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "2");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "1");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
				// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				// <-- belamour
			}
			
		break;							

		case "ShipWreck_10_1":
			dialog.text = "Danke, Kapitän! Das Laden sollte nicht zu viel Zeit in Anspruch nehmen. Gott, wie haben wir für diesen Moment gebetet!";
			link.l1 = "Das ist großartig. Ich hoffe, dass deine Prüfungen bald vorbei sein werden.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "4");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
			}
			else
			{
				AddQuestRecord("ShipWrecked", "3");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				// <-- belamour
			}			
		break;							
				
		case "ShipWreck_11":
			dialog.text = "Los geht's! Wirklich, Kapitän?! Haben wir Angst vor dem Tod?! Wir haben ihn einmal ausgetrickst, wir können es wieder tun. Wir wollen nur nicht so unser Leben verlieren. Hier verrotten, allein\nWir würden uns gerne deiner Mannschaft anschließen und tapfer unter deiner Flagge kämpfen. Lass uns nur nicht hier...";
			link.l1 = "Ich sehe, ihr seid bereit, alles zu tun, nur um hier rauszukommen. Aber schaut euch nur an, was für Seefahrer könnt ihr sein?";
			link.l1.go = "ShipWreck_14";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l2 = "Das ist eine gute Idee. Ich denke, ich könnte dich anheuern.";
				link.l2.go = "ShipWreck_15";
			}	
		break;									
		
		case "ShipWreck_12":
			dialog.text = "Nein-nein, ich mache keine Witze! Bitte, bring mich weg von diesem karibischen Schlachthof ... aus dieser Hölle! Sie wissen, ich bin ein reicher Mann ... ein sehr reicher Mann. Selbst der Papst hat in seiner ganzen Zeit nicht so viel Gold gesehen. Ich werde dich mit Gold überschütten...";
			link.l1 = "Oh je... Also gut, steig ins Boot...";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			ChangeOfficersLoyality("bad_all", 1);
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "5");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
			AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
			// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины
			if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
			{
				AddQuestUserData("ShipWrecked", "sText", "wrecked");
			}
			else
			{
				AddQuestUserData("ShipWrecked", "sText", "wrecked");
			}
			// <-- belamour
		break;							

		case "ShipWreck_13": // берем пассажирами
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			//Achievment_SetStat(29, sti(pchar.GenQuest.ShipWreck.Qty));
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.variant"))
			{
				if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
				if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			}	
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "ShipWreck_13_again";
			}
			DialogExit();
		break;
		
		case "ShipWreck_13_again":
			dialog.text = LinkRandPhrase("Warum zögern Sie, Kapitän? Befehlen Sie den Anker zu lichten.","Es tut uns leid, Kapitän, aber wir müssen uns zum Auslaufen bereitmachen.","Wir haben so ein Glück, dass Sie sich entschieden haben, hierher zu kommen!");
			link.l1 = "Beeil dich. Das Schiff wartet auf niemanden.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_13_again";		
		break;
		
		case "ShipWreck_14":
			dialog.text = "Kapitän, wir haben nichts zu verlieren. Der Tod folgt uns bereits auf Schritt und Tritt... Wir sterben lieber in einem fairen Kampf, als von stinkenden Kojoten gefressen zu werden...";
			link.l1 = "Oh, ist es eine Herausforderung, dann?! Gut, lass uns unsere Streitigkeiten beilegen"+GetSexPhrase(", wie Männer","")+"!";
			link.l1.go = "ShipWreck_16";
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;		
		
		case "ShipWreck_15":
			dialog.text = "Ich schwöre, Kapitän, Sie werden es nicht bereuen. Wir werden die besten Seefahrer im ganzen Archipel sein.";
			link.l1 = "Großartig! Steig in das Boot...";
			link.l1.go = "ShipWreck_17";			
		break;				
		
		case "ShipWreck_16":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetImmortal(rChar, false);
				if(CheckPassengerInCharacter(pchar, "ShipWreck_" + i)) 
				{
					RemovePassenger(pchar, rChar);
				}
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ShipWreckGroup");
			}

			LAi_Group_SetRelation("ShipWreckGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("ShipWreckGroup", LAI_GROUP_PLAYER, true);
			if(pchar.GenQuest.ShipWreck == "fight" || pchar.GenQuest.ShipWreck == "SailorsOnShoreFight") // belamour gen
			{
				LAi_group_SetCheck("ShipWreckGroup", "OpenTheDoors"); 
				LAi_group_SetCheckFunction("ShipWreckGroup", "ShipWreck_AfterBattle");
			}	
			DialogExit();		
		break;
		
		case "ShipWreck_17": // принимаем в команду
			if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
			if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;			
				rChar.Dialog.currentnode = "ShipWreck_17_again";
			}
			AddCharacterCrew(pchar, sti(pchar.GenQuest.ShipWreck.Qty));
			// --> belamour gen по количеству персон
			if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5) sText = "";	
			else sText = "";
			Log_Info("Your team has increased by " + pchar.GenQuest.ShipWreck.Qty + " man" + sText + ".");
			// <-- belamour gen 
			Achievment_SetStat(29, sti(pchar.GenQuest.ShipWreck.Qty));
			pchar.quest.ShipWreck_LocExit.over = "yes"; // Снимаем прерывание на выход из локации			
			DeleteAttribute(pchar, "GenQuest.ShipWreck");			
			AddCharacterExpToSkill(pchar, "Leadership", 50); 			
			DialogExit();
		break;

		case "ShipWreck_17_again":
			dialog.text = LinkRandPhrase("Ich schwöre, Kapitän, Sie werden es nicht bereuen.","Sie haben die richtige Wahl getroffen, Kapitän.","Kapitän, seien Sie versichert, dass Sie ebenso viel Glück hatten wie wir!");
			link.l1 = RandPhraseSimple("Ich hoffe es.","Beeil dich. Das Schiff wird auf niemanden warten.");
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_17_again";
		break;
		
		case "ShipWreck_18":
			dialog.text = "Kapitän, warum würden Sie ehrliche Leute mit solchem Misstrauen beleidigen? Schauen Sie sich doch ihre Gesichter an, glauben Sie wirklich, dass sie Meuterer sein könnten?";
			link.l1 = "Also gut, aber was soll ich jetzt mit dir anfangen?";
			link.l1.go = "ShipWreck_20";
		break;
		
		case "ShipWreck_19":
			dialog.text = "Und was kann ich tun? Zumindest jetzt, bin ich am Leben... und ich danke Gott, dass ich es rausgeschafft habe! Aber wenn du mir hilfst, mein Schiff zurückzuholen und Rache für meine Demütigung zu nehmen, bin ich bereit, dir alles zu geben, was dieser Schurke gestohlen und im Laderaum versteckt hat.";
			link.l1 = "In Ordnung, Sie haben einen Deal.";
			link.l1.go = "ShipWreck_13";
			ShipWreck_SetCapToMap();
			SetFunctionTimerCondition("prosralisrok", 0, 0, 180, false); // таймер лесник тамймер на поиск корабля 																																   
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "16");
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			// --> belamour окончание по количеству персон
			if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
			{
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " his sailors");
			}
			else
			{
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " his sailor");
			}
			// <-- belamour
			AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
		break;
		
		case "ShipWreck_20":
			dialog.text = "Wir sind nicht in der Lage, Befehle zu erteilen. Es liegt an dir, bring uns einfach zu irgendeiner Siedlung oder nimm uns in deine Mannschaft auf.";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l1 = "In Ordnung, ich nehme dich in meine Besatzung auf. Aber kein Unfug! Ich habe strenge Disziplin auf meinem Schiff!";
				link.l1.go = "ShipWreck_17";
			}
			link.l2 = "Ich bringe dich nirgendwo hin. Ich habe schon genug Schläger in meiner Mannschaft.";	
			link.l2.go = "ShipWreck_22";
			link.l3 = "In Ordnung, steig ins Boot, ich bringe dich irgendwohin.";
			link.l3.go = "ShipWreck_10_1";
		break;		
		
		case "ShipWreck_22":
			dialog.text = "Oh, na ja... Sie lassen uns keine Wahl... Wir werden beten, dass die Vorsehung Gnade für uns zeigt und uns aus diesem gefährlichen Ort herauskommen lässt. So Gott will, könnten wir noch das bewohnte Land erreichen...";
			link.l1 = "Auf Wiedersehen. Möge der Herr über dich wachen...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;		
		
		case "ShipWreck_30":
			if(pchar.GenQuest.ShipWreck == "SailorsSaved")
			{
				dialog.text = "Vielen Dank, Kapitän "+GetFullName(pchar)+"! Sie haben so viel für uns getan, dass keine Dankbarkeit ausreichen würde, um Ihnen zurückzuzahlen. Und obwohl all unser Besitz keinen Kupfer wert ist, erlauben Sie mir, Ihnen dieses Amulett zu präsentieren. Es wäre sehr nützlich für einen Kapitän, der häufig an Seeschlachten beteiligt ist.";
				link.l1 = "Danke für dein Geschenk! Dieser Krimskrams ist in der Tat sehr nützlich! Auf Wiedersehen, Kapitän "+pchar.GenQuest.ShipWreck.Name+" und viel Glück auf deinen Reisen.";
				link.l1.go = "ShipWreck_47";
			}
			else
			{
				dialog.text = "Kapitän, vielen Dank. Sie haben viel für uns getan, und jede Belohnung wäre gering im Vergleich zu unserer Dankbarkeit. Bitte, nehmen Sie dieses bescheidene Geschenk als Zeichen unserer Dankbarkeit an.";
				link.l1 = "Wirklich, Sie hätten sich nicht bemühen sollen... Sie brauchen das Geld viel dringender als ich. Dennoch, es ist sehr nett von Ihnen. Danke und auf Wiedersehen.";
				link.l1.go = "ShipWreck_31";
			}	
		break;
		
		case "ShipWreck_31":
			//addMoneyToCharacter(pchar, sti(pchar.rank) * 200 + rand(2000));
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			TakeNItems(pchar, "jewelry2", 15+hrand(10));
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony"+ Locations[FindLocation(PChar.location)].townsack + "Acc"));
			CloseQuestHeader("ShipWrecked");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_32":	
			dialog.text = "Kapitän, wisse, dass es Leute gibt, die von nun an bis ans Ende der Welt für dich gehen würden. Es ist schade, dass ich nichts habe, um dir zu danken. Trotzdem... Bitte, nimm dieses Kleinod an, ich habe es in dieser unglückseligen Bucht gefunden. Ich hoffe, es bringt dir Glück.";
			link.l1 = "Jeder hätte an meiner Stelle dasselbe getan. Lebewohl.";
			link.l1.go = "ShipWreck_33";
		break;
		
		case "ShipWreck_33":
			GiveItem2Character(pchar, pchar.GenQuest.ShipWreck.Prize);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + Locations[FindLocation(PChar.location)].townsack + "Acc")); // belamour gen: просто pchar.location ничего не даст
			CloseQuestHeader("ShipWrecked");		
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_34":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Kapitän, sind wir schon in Dunkirk?","Sind wir wirklich in Dünkirchen, Kapitän?"),RandPhraseSimple("Kapitän, ist es Europa?","Sind wir so schnell nach Europa gesegelt?"));
			bTemp = !GetCharacterItem(pchar, "map_full") && !GetCharacterItem(pchar, "map_part2");
			bTemp = !GetCharacterItem(pchar, "map_part1") || bTemp;
			if(rand(100) > 75 && !isDay() && bTemp)
			{
				link.l1 = "A-ha...";
				link.l1.go = "ShipWreck_40";
			}
			else
			{
				link.l1 = LinkRandPhrase("Noch nicht...","Was Dunkirk? Was Europa? Schau dich um!","Oh mein Gott!");
				link.l1.go = "ShipWreck_35";
			}
		break;
		
		case "ShipWreck_35":
			dialog.text = LinkRandPhrase("Aber, Kapitän, Sie haben ein Versprechen gegeben!","Wie konnten Sie Ihr Wort brechen, Kapitän?","Und wann kommen wir nach Europa?");
			if(rand(100) < 70)
			{
				link.l1 = "In Ordnung. Herr, versammeln Sie Ihre Männer und Ihr Besitztum und gehen Sie, wohin Sie möchten.";
				link.l1.go = "ShipWreck_36";
			}
			link.l2 = RandPhraseSimple(LinkRandPhrase("Bist du sicher, dass wir wirklich nach Dünkirchen müssen?","Weißt du, mein Schiff ist nicht zum Segeln über den Ozean gedacht.","Kapitän, und was ist falsch mit der Karibik?"),LinkRandPhrase("Aber ich hatte andere Pläne...","Warum willst du überhaupt nach Europa gehen...","Stell dir nur all diese verführerischen Mulattinnen vor! Du wirst sie nie in Europa treffen..."));
			link.l2.go = "ShipWreck_37";	
		break;
		
		case "ShipWreck_36":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			pchar.GenQuest.ShipWreck = "fight";
			dialog.text = "Aber wie?.. Wie kannst du es wagen?! Was für ein Verrat ist das?! Ich werde dir beibringen, wie man zu seinem Wort steht!";
			link.l1 = "Nun, du hast danach gefragt...";
			link.l1.go = "ShipWreck_16";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		case "ShipWreck_37":
			dialog.text = LinkRandPhrase(RandPhraseSimple("Nein! Ich muss nach Dünkirchen kommen!","Anstatt mir Geographie beizubringen, solltest du lieber deine Pflicht erfüllen!"),RandPhraseSimple("Ich will nichts davon hören! Du hast mir versprochen, mich nach Europa zu bringen!","Nein, Kapitän, das wird nicht funktionieren. Wir segeln nach Europa."),"Ich werde den Rest meiner Tage nicht in diesem Loch ein elendes Leben führen!");
			link.l1 = "Oh, ich weiß nicht, ob das ein Ende nehmen wird...";
			link.l1.go = "ShipWreck_38";
		break;		
		
		case "ShipWreck_38":
			chrDisableReloadToLocation = false;			
			SetFunctionExitFromLocationCondition("ShipWreck_ExitFromTown", pchar.location, false);				
			if(!CheckAttribute(pchar,"GenQuest.ShipWreck.CrazyRec")) // mitrokosta исправлена блокировка поручения капитана
			{
				pchar.GenQuest.ShipWreck.CrazyRec = true;
				AddQuestRecord("ShipWrecked", "7");
			}
			DialogExit();
		break;
		
		case "ShipWreck_40":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			dialog.text = "Sieh mal! Das ist ein anständiger Mann! Europa! Verdammt altes Europa! Ja-ja-ja!\nOh, ja! Du hast deinen Teil des Abkommens erfüllt und ich werde meinen erfüllen. Hier, nimm diese Hälfte der Karte. Die andere Hälfte hatte mein Partner. Ruhe in Frieden, oder Ruhe im Wasser? Was auch immer. Er war derjenige, der mich überredete, an diesem Abenteuer teilzunehmen.";
			link.l1 = "Halt, also bist du kein Seemann? Dein Kumpel war ein Kapitän?";
			link.l1.go = "ShipWreck_41";
		break;
		
		case "ShipWreck_41":
			dialog.text = "Oh nein!.. Natürlich nicht! Nun, ja, ich bin kein Seemann. Und er wurde von einer riesigen Welle über Bord gewaschen, als er beschloss, weiter von der Küste weg zu segeln. Dann übernahm ich das Kommando und befahl, in die Bucht zu segeln... Und wir haben es gut geschafft, uns durch die Riffe zu kämpfen, bis alles durch einen fatalen Unfall entschieden wurde. Das Schiff traf auf ein Felsfragment und ging unter...";
			link.l1 = "Das ist wirklich eine Demonstration von Inkompetenz...";
			link.l1.go = "ShipWreck_42";
		break;
		
		case "ShipWreck_42":
			dialog.text = "Hör zu, ist das wirklich Dunkirk? Denk mal nach, es sind nur sechs Monate vergangen und der ganze Ort hat sich verändert\nHier, nimm die Karte, oder genauer gesagt, einen Teil davon. Der Schatz befindet sich in einer Höhle! Keine Ahnung, welche Insel, aber du bist ein erfahrener Seemann, du wirst eines Tages den genauen Ort finden... Ich garantiere, dass es unzählige Reichtümer des Piraten namens aaarrrrrhg gibt...";
			link.l1 = "Danke, mein guter Mann. Selbst wenn es überhaupt keinen Schatz gibt, werde ich nicht allzu verärgert sein. Lebewohl, und ich hoffe wirklich, dass wir uns niemals wiedersehen...";
			link.l1.go = "ShipWreck_43";
		break;
		
		case "ShipWreck_43":
			sld = CharacterFromID("ShipWreck_0");
			RemovePassenger(pchar, sld);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddMapPart();
			AddQuestRecord("ShipWrecked", "9");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");	
			AddSimpleRumourCity(LinkRandPhrase(RandPhraseSimple("They say some loony recently showed up on the island. He is telling everyone that he had lost his documents, and no he's attempting to apply for a captain on a ship to Dunkirk.",
				"They say some maniac recently showed up on the island. He stole a spade at the local shop and now is digging a pit past the town gates..."),
				RandPhraseSimple("Just imagine, recently some visiting European in worn and dirty clothes attempted to get an audience with the governor! He claimed that he needed to see the governor of Dunkirk ass soon as possible.",
				"There was a scandal at the town hall recently. Some vagrant was caught, he claimed that he personally knew the governor of Dunkirk."),
				"Some psycho was looking for you recently. He claimed that you owed him money..."), pchar.location, 5, 3,"");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_44":
			dialog.text = RandPhraseSimple("Kapitän, es ist einfach großartig, dass Sie uns nicht vergessen haben! Wir alle haben für Sie gebetet!","Kapitän, ist unser Heil nahe? Wie wir dafür gebetet haben, dass es kommt! Einige Leute begannen bereits, die Hoffnung zu verlieren...");
			link.l1 = "Grüße, "+pchar.GenQuest.ShipWreck.Name+"! Wie könnte ich meine Kollegen in solchem Zustand lassen? Wohin?";
			link.l1.go = "ShipWreck_45";
			link.l2 = "Grüße, "+pchar.GenQuest.ShipWreck.Name+"! Ich fürchte, ich habe schlechte Nachrichten für dich. Es gab eine Änderung der Pläne, und ich kann dich nicht an Bord nehmen.";
			link.l2.go = "ShipWreck_9";
		break;
		
		case "ShipWreck_45":
			dialog.text = "Es ist uns egal, wohin wir gehen, solange es weit genug von diesem verfluchten Ort entfernt ist... Würden Sie uns erlauben, uns selbst zu beladen?";
			link.l1 = "Ja, mach nur weiter. Bald werden deine Prüfungen vorbei sein.";
			link.l1.go = "ShipWreck_46";
		break;

		case "ShipWreck_46":
			ChangeCharacterComplexReputation(pchar,"nobility", 4);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.dialog.currentnode = "ShipWreck_13_again";
			}			
			pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen снять таймер на 30 дней	 
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny")) DeleteAttribute(pchar,"GenQuest.ShipWreck.Mutiny"));
			SetFunctionExitFromLocationCondition("ShipWreck_LocationExit", pchar.location, false);				
			DialogExit();			
		break;

		case "ShipWreck_47":
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			GiveItem2Character(pchar, "indian_10");
			AddQuestRecord("ShipWrecked", "15");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			CloseQuestHeader("ShipWrecked");				
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_48":
			dialog.text = "Danke, Kapitän. Wir haben bereits begonnen zu verzweifeln, aber Sie haben uns buchstäblich wieder zum Leben erweckt.";
			link.l1 = "Es war nichts... Auf Wiedersehen.";
			link.l1.go = "ShipWreck_49";
		break;
		
		case "ShipWreck_49":
			AddQuestRecord("ShipWrecked", "17");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");								
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_50":
			dialog.text = "Was zur Hölle willst du von mir?";
			link.l1 = "Ich bin gekommen"+GetSexPhrase("","")+", um dir Grüße von einer Person namens zu senden"+pchar.GenQuest.ShipWreck.Name+". Kennst du ihn?"; // belamour gen
			link.l1.go = "ShipWreck_51";
		break;
		
		case "ShipWreck_51":
			dialog.text = "Es ist schade, dass ich diesen Schurken nicht vorher erwürgt habe. Nun, dann, ich schätze, die Zeit ist gekommen, für meine Güte zu bezahlen...";
			link.l1 = "Tatsächlich... Und die Zeit ist gerade abgelaufen...";
			link.l1.go = "ShipWreck_52";
		break;
		
		case "ShipWreck_52":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheckFunction(LAI_GROUP_BRDENEMY, "ShipWreck_afterCabinFight");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;

		case "ShipWreck_53":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			pchar.quest.ShipWreck_ShipSink.over = "yes";
			dialog.text = "Gute Arbeit, Kapitän! Alles wie vereinbart, ja? Wir bekommen das Schiff und du bekommst die Fracht?";
			link.l1 = "Sicher. Nimm das Schiff und nutze es gut.";
			link.l1.go = "exit";

			NextDiag.TempNode = "ShipWreck_53_again";		
			AddDialogExitQuestFunction("ShipWreck_SetShipNew");
		break;
		
		case "ShipWreck_53_again":
			dialog.text = "Ich grüße dich, Kapitän "+GetFullName(pchar)+".";
			link.l1 = "Also, wie gefällt Ihnen Ihr Schiff?";
			link.l1.go = "ShipWreck_53_again1";
		break;
		
		case "ShipWreck_53_again1":
			dialog.text = "Heh, es quietscht und knarrt, genau wie ich. Ich glaube, wir beide haben nicht mehr viel Zeit, die hohe See zu befahren...";
			link.l1 = "Viel Glück dann...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_53_again";		
		break;
		// Генератор "Shipwrecked"
		
		// Генератор "State convicts"
		case "Convict_0End":
			DialogExit();
			pchar.GenQuest.Convict = "close";
			chrDisableReloadToLocation = false;
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("Convict_DialogDisable");
		break;
		
		case "Convict_Begin":					
			switch(sti(pchar.GenQuest.Convict.var))
			{
				case 0:
					dialog.text = "Kapitän, bitte helfen Sie uns, ein Schiff oder ein Beiboot, ein Tartan, was auch immer, es ist wirklich egal. Wir sind in solchen Umständen, dass wir diesen unwirtlichen Ort fliehen müssen, aber wir können uns in der Siedlung nicht blicken lassen.";
					link.l1 = "Und welche Art von Umständen sind das?";
					link.l1.go = "Convict_11";
				break;
				case 1:
					dialog.text = "Kapitän, könnten Sie uns bitte ein paar hundert Pesos leihen? Wir würden nicht fragen, aber wir sind wirklich in großer Not.";
					link.l1 = "In schlimmer Not, sagst du? Ich wette, du hast einfach nur keinen Rum mehr und das ist sicherlich eine schlimme Not.";
					link.l1.go = "Convict_12";			
				break;
				case 2:
					pchar.GenQuest.Convict.ToCity = FindColonyWithMayakExceptIsland(GetCharacterCurrentIslandId(pchar));	
					pchar.GenQuest.Convict.Mayak = GetMayakByCityName(pchar.GenQuest.Convict.ToCity);
					dialog.text = "Kapitän, könnten Sie so freundlich sein, unsere bescheidene Gesellschaft zum Leuchtturm zu bringen "+XI_ConvertString("Colony"+pchar.GenQuest.Convict.ToCity+"Gen")+".";
					link.l1 = "Allein durch dein Aussehen würde ich nicht sagen, dass du allzu bescheiden bist.";
					link.l1.go = "Convict_13";								
				break;
			}						
			link.l2 = LinkRandPhrase("Ich gebe freitags keine Almosen.","Ich habe keine Zeit für diesen Unsinn.","Ich helfe keine fremden Leute.");
			link.l2.go = "Convict_14";
			Convict_GetMineType();
			pchar.GenQuest.Convict.ShoreLocation = SelectQuestShoreLocation();
		break;
		
		case "Convict_11":
			dialog.text = "Wir sind Flüchtlinge... aus "+GetStrSmallRegister(XI_ConvertString("Bergwerkstyp"+pchar.GenQuest.Convict.MineType+"Dat"))+". Bald wird der Ex-Meister es bemerken... und dann sind wir sicher tot.";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l1 = "Also weißt du, wie man die Segel bedient?";
				link.l1.go = "Convict_11_1";
			}	
			link.l2 = "Und womit wirst du zahlen?";
			link.l2.go = "Convict_11_2";
		break;
		
		case "Convict_12":
			dialog.text = "Es ist keine gute Zeit für uns, an Rum zu denken. Es ist eine Woche her, seit wir geflohen sind, jetzt verstecken wir uns im Dschungel und verhungern.";
			if(sti(pchar.money) >= 3000)
			{
				link.l1 = "Nun, angenommen, ich könnte dir Geld geben... und dann? Wirst du dich verstecken, bis du schließlich von einer Patrouille entdeckt wirst?";
				link.l1.go = "Convict_12_1";		
				link.l2 = "In Ordnung, wie viel brauchst du?";
				link.l2.go = "Convict_12_2";
			}	
			link.l3 = "Ich habe ein kurzes Gespräch mit solchen wie dir, Köpfe auf dem Henkersblock, und das war's!";
			link.l3.go = "Convict_12_3";
		break;		
		
		case "Convict_12_1":
			if(hrand(1) == 0 && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				dialog.text = "Und was können wir sonst noch tun? Wir würden gerne als Matrosen arbeiten, aber wenn man bedenkt, dass wir Flüchtlinge sind, wer wird uns einstellen?";
				link.l1 = "Ich werde dich einstellen, wenn du weißt, wie man die Segel bedient und keine Anzeichen von Feigheit zeigst.";
				link.l1.go = "Convict_12_1_1";
			}
			else
			{
				dialog.text = "Wir haben bereits eine Vereinbarung mit den örtlichen Seeleuten getroffen. Um hier rauszukommen, fehlen uns nur noch dreitausend.";
				link.l1 = "Nun, hier sind deine dreitausend, wenn das wirklich helfen soll.";
				link.l1.go = "Convict_12_1_2";
			}
			link.l2 = "Nun, ich weiß nicht... Das sind deine eigenen Probleme und ich werde dir nicht helfen, sie zu lösen.";
			link.l2.go = "Convict_12_1_End"; // выход из локи с закрытием квеста
		break;
		
		case "Convict_12_1_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Bitte, Kapitän, stellen Sie uns ein, sicher werden Sie es nicht bereuen! Wir waren Piraten mit "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" in der Adria, bis er schließlich gehängt wurde und wir, "+pchar.GenQuest.Convict.ConvictQty+" Männer, wurden zu diesem Ort verbannt.";
			link.l1 = "In Ordnung. Es gibt einen Ort in der Nähe, bekannt als "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+". Um Mitternacht hole ich dich dort ab. Ich hoffe wirklich, du wirst dich nicht verlaufen.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";		
		break;

		case "Convict_12_1_2":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			iTmp = hrand(3);
			if(iTmp <= 1)
			{
				dialog.text = "Natürlich, das wird uns sehr helfen! Wir werden noch heute in See stechen, wenn der Wind günstig ist und die Fischer uns nicht im Stich lassen. Danke, Kapitän, und möge Gott Ihnen helfen...";
				link.l1 = "Viel Glück auch dir.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			if(iTmp == 2)
			{
				dialog.text = "Das ist aber ein Glücksfall! Wir hätten nicht einmal zu hoffen gewagt, das Geld so schnell zu bekommen. Kapitän, erlauben Sie mir, Ihnen ein Kleinod zu präsentieren, das wir unserem ehemaligen Boss abgenommen haben. Vielleicht bringt es auch Ihnen Glück.";
				link.l1 = "Danke, das ist sicher eine anständige Sache. Viel Glück für dich.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			if(iTmp == 3)
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "Nun, das ist ein großzügiger Mann, der keine Angst hat, das Geld auszugeben, weil er weiß, wie man es verdient!\nLetzte Nacht haben wir gesehen, wie die örtlichen Schmuggler geladen haben "+MerPrm.QuestGoodsIdx+". Es war dunkel, aber wir konnten den Namen des Schiffes an der Seite eines der Boote ausmachen, '"+MerPrm.ShipName+"'... und dieses Schiff segelt unter der Flagge von "+MerPrm.nation+". Vielleicht findest du diese Information nützlich, he-he.";			
				link.l1 = "Hmm... Nun, vielleicht werde ich das tun. Lebewohl, ihr Fährtenleser.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");			
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}
		break;
		
		case "Convict_12_2":
			dialog.text = "Oh, mein Gott, wir sind nicht in der Lage, Forderungen zu stellen. Was auch immer Sie entbehren können, wir werden für alles dankbar sein.";
			link.l1 = "300 Pesos.";
			link.l1.go = "Convict_12_2_1";
			link.l2 = "1000 Pesos.";
			link.l2.go = "Convict_12_2_2";
			link.l3 = "3000 Pesos.";
			link.l3.go = "Convict_12_2_3";
		break;
		
		case "Convict_12_2_1":
			addMoneyToCharacter(pchar, -300);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
			dialog.text = "Danke, Kapitän, und möge Gott über dich wachen...";
			link.l1 = "Viel Glück auch dir.";
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_2":
			addMoneyToCharacter(pchar, -1000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 40);
			if(hrand(1) == 0)
			{
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				dialog.text = "Das ist ja ein Glücksfall! Wir hätten nicht einmal zu hoffen gewagt, das Geld so schnell zu bekommen. Kapitän, erlauben Sie mir, Ihnen einen Talisman zu präsentieren, den wir von unserem früheren Boss genommen haben. Vielleicht bringt er auch Ihnen Glück.";
				link.l1 = "Danke, das ist sicher eine anständige Sache. Viel Glück für dich.";
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 20);
			}
			else
			{
				dialog.text = "Danke, Kapitän, und möge Gott über Sie wachen...";
				link.l1 = "Viel Glück auch Dir.";
			}
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_3":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			if(hrand(1) == 0)
			{
				dialog.text = "Das ist ein Glücksfall! Wir hätten nicht einmal zu hoffen gewagt, das Geld so schnell zu bekommen. Kapitän, erlauben Sie mir, Ihnen ein Kleinod zu präsentieren, das wir unserem ehemaligen Boss abgenommen haben. Vielleicht bringt es Ihnen auch Glück.";
				link.l1 = "Danke, das ist sicher eine anständige Sache. Viel Glück für dich.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			else
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "Nun, da ist ein großzügiger Mann, der keine Angst hat, das Geld auszugeben, weil er weiß, wie man es verdient!\nLetzte Nacht haben wir gesehen, wie die örtlichen Schmuggler geladen haben "+MerPrm.QuestGoodsIdx+". Es war dunkel, aber wir konnten den Namen des Schiffes auf der Seite eines der Boote erkennen '"+MerPrm.ShipName+"'... und dieses Schiff segelt unter der Flagge von "+MerPrm.nation+". Vielleicht findest du diese Information nützlich, he-he.";
				link.l1 = "Hmm... Nun, vielleicht werde ich das tun. Lebewohl, ihr Fährtenleser.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);				
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}			
		break;
		
		case "Convict_12_1_End":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");	
			pchar.GenQuest.Convict = "close";
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_12_3":
			if(hrand(1) == 0)
			{
				dialog.text = "Verfluchen Sie uns nicht, Kapitän! Wir haben ein anständiges Trödel, bitte, akzeptieren Sie es als Lösegeld und lassen Sie uns gehen...";
				link.l1 = "Gib es her, dann, und verzieh dich, solange du noch kannst.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "Nun haben wir keine andere Wahl, ein Mann wird nicht zweimal sterben. Zur letzten Schlacht, Jungs!";
				link.l1 = "Das ist eine andere Geschichte!";
				link.l1.go = "Convict_Fight";
			}			
		break;
		
		case "Convict_13":
			dialog.text = "Nun, wir sind sicherlich keine Heiligen, aber wir suchen keinen Streit aus nichts... Wir sind Flüchtlinge und wir müssen so schnell wie möglich hier raus.";
			link.l1 = "Haben Sie etwas, um für die Passage zu bezahlen?";
			link.l1.go = "Convict_13_1";		
			link.l2 = "Oh, ich verstehe... Nein, ich werde meinen Ruf nicht wegen dir beflecken. Lebewohl.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Sicher! Wir sind an Überfälle und so weiter gewöhnt. Fast zwei Jahre lang waren wir und der Verstorbene "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" terrorisierten die örtlichen Händler, aber ach! Er wurde gehängt, und "+pchar.GenQuest.Convict.ConvictQty+" Männer von uns wurden zu Zwangsarbeit verurteilt.";
			link.l1 = "Wie wäre es, meiner Crew beizutreten? Ich bin großzügig"+GetSexPhrase("","")+", aber ich verspreche Ihnen kein friedliches Leben.";
			link.l1.go = "Convict_11_3";			
		break;
		
		case "Convict_11_2":
			dialog.text = "Ja, wir haben etwas mitgenommen "+GetStrSmallRegister(XI_ConvertString("Bergwerkstyp"+pchar.GenQuest.Convict.MineType+"Gen"))+", also können wir doppelt zahlen. ALSO vertraue ich darauf, dass der Preis vereinbart ist. Und wage es nicht, Wachen mitzubringen. Wir vergeben Verrat nicht..."; // belamour gen
			link.l1 = "Gut, warte auf mich am Strand "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation+"Gen")+". Gegen Mitternacht wird ein Boot für dich da sein ... Und ich will keine Tricks sehen!"; // belamour gen
			link.l1.go = "Convict_11_4";
			link.l2 = "Nein, meine Freunde. Was ist, wenn ich euch das Schiff gebe und ihr mich hinterrücks erstecht? Nein, ich helfe euch nicht in dieser Angelegenheit.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_3":
			dialog.text = "Mit großem Vergnügen, "+GetSexPhrase("Herr","Fräulein")+" Kapitän. Wir sind damit ziemlich vertraut, und wir werden sicherlich nicht mit solchen Empfehlungen in die Marine aufgenommen, he-he.";
			link.l1 = "In Ordnung. Es gibt einen Ort in der Nähe, bekannt als "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+". Nach Mitternacht hole ich dich dort ab. Ich hoffe doch, du wirst dich nicht verlaufen.";
			link.l1.go = "Convict_11_6";
		break;
		
		case "Convict_11_4":
			dialog.text = "Aber, "+GetSexPhrase("Herr","Fräulein")+" Kapitän, gehen wir noch ein größeres Risiko ein? Was ist, wenn Sie sich entscheiden, uns beim Kommandanten zu melden?";
			link.l1 = "Das stimmt... Also gut, wenn ich bis zum Tagesanbruch nicht da bin, dann ist der Handel abgesagt.";
			link.l1.go = "Convict_11_7";			
		break;
		
		case "Convict_11_5":
			if(makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 79) //макс. репутатция 90
			{
				dialog.text = "Oh, Kapitän, wir haben auf dich gezählt...";
				link.l1 = "Kein Problem. Wenn du Geld hast, wirst du eine Passage finden. Lebewohl.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "Du bist ein schlauer, Kapitän, wie ich sehen kann. Du wirst doch gleich zum Kommandanten laufen, oder? Und du denkst, du kommst damit davon?";
				link.l1 = "Und du planst mich aufzuhalten, wie ich sehe?! Dann bekommst du, was du verdienst!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "fight";
			}	
		break;
		
		case "Convict_11_6":
			pchar.GenQuest.Convict = "ToShore";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "1");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen колво прописью
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen"));	// belamour gen	
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);	
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_11_7":
			pchar.GenQuest.Convict = "GetShip";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "2");		
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));					
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();		
			AddDialogExitQuestFunction("Convict_DialogDisable");		
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_13_1":
			pchar.GenQuest.Convict.Sum = (sti(pchar.rank)+10)*100+1000;
			dialog.text = "Da ist etwas. Wir haben in den Truhen unseres Chefs gewühlt, aber dann gab es einen Aufstand darüber, und wir mussten uns mit einem Kampf durchsetzen. Nur "+PChar.GenQuest.Convict.ConvictQty+" Männer haben es geschafft zu überleben.";
			link.l1 = "Unter Berücksichtigung der Umstände werde ich Ihnen die Passage nicht günstiger geben als "+FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum))+" Pesos pro Person.";
			link.l1.go = "Convict_13_2";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "Ich sehe, dass ihr keine Feiglinge seid. Würdet ihr meiner Crew beitreten?";
				link.l2.go = "Convict_13_3";
			}
		break;
		
		case "Convict_13_2":
			dialog.text = "Und haben wir eine Wahl? Na gut, "+FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum))+"...";
			link.l1 = "Dann geh zu "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation+"Dat")+". Ich schick dir ein Boot nach Mitternacht."; // belamour gen 
			link.l1.go = "Convict_13_4";
			pchar.GenQuest.Convict = "ToMayak";
			pchar.GenQuest.Convict.Sum = sti(pchar.GenQuest.Convict.Sum) * sti(pchar.GenQuest.Convict.ConvictQty);
		break;
		
		case "Convict_13_3":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Und warum nicht? Wir kennen das Zeug, wir haben damit Piraten gespielt "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" in "+RandPhraseSimple("Gibraltar","Ärmelkanal")+" bevor wir hier feststeckten.";
			link.l1 = "In Ordnung. Es gibt einen Ort in der Nähe, bekannt als "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+". Um Mitternacht hole ich dich dort ab. Ich hoffe wirklich, du wirst dich nicht verlaufen.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";
		break;
		
		case "Convict_13_4":
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "8");					
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen колво прописью
			AddQuestUserData("Convict", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen"));
			AddQuestUserData("Convict", "sSum", pchar.GenQuest.Convict.Sum);
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Dat"));	// belamour gen	 	
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
				
		case "Convict_14":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Eh, Kapitän, du warst auch einmal arm, du hattest leere Taschen. Und jetzt verachtest du einfache Leute wie uns.","Kapitän, es gehört sich nicht, einfache Leute so zu behandeln. Wir stehen alle unter demselben Gott."),
						RandPhraseSimple("Heh, die Leute werden wirklich zu egoistisch heutzutage. Du lebst, als hättest du noch zwei Jahrhunderte vor dir.","Oh, ich sehe, dass du gerade aus Europa angekommen bist, du hast noch nicht den Gestank unserer tropischen Müllhalde gerochen."));
			link.l1 = LinkRandPhrase("Versuchst du, mich zu blamieren? Ich werde deine Zunge ein paar Zentimeter kürzer machen!","Bist du dabei, mich einzuschüchtern? Halt jetzt deinen Hut fest!","Bist du ein Philosoph oder was? Ich werde dir einen Sinn einprügeln!");
			link.l1.go = "Convict_Fight";	
			pchar.GenQuest.Convict = "fight";
		break;
		
		case "Convict_Fight":
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	 
			LAi_LockFightMode(pchar, false); 
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			iTemp = sti(PChar.GenQuest.Convict.ConvictQty);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID("Convict_" + i);
				DeleteAttribute(rChar, "City");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ConvictGroup");
				LAi_SetImmortal(rChar, false);
			}
			LAi_group_SetRelation("ConvictGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("ConvictGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("ConvictGroup", "OpenTheDoors"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "Convict_15":
			dialog.text = LinkRandPhrase("Also, Kapitän? Haben Sie uns ein Schiff besorgt?","Grüße, Kapitän. Also, was ist mit unserem Deal?","Hallo, Kapitän. Wir haben uns schon Sorgen gemacht. Alles ist gut gelaufen, nehme ich an?");
			if(Convict_CheckShipType(SHIP_TARTANE) || Convict_CheckShipType(SHIP_WAR_TARTANE))
			{
				link.l1 = "Ja, hier ist deine Wanne. Und vergiss nicht die Zahlung. Ich habe bezahlt "+pchar.GenQuest.Convict.ShipPrice+" Münzen dafür, also schuldest du mir "+sti(pchar.GenQuest.Convict.ShipPrice)* 2+", genau wie wir vereinbart haben.";
				link.l1.go = "Convict_15_1";
			}	
			link.l2 = "Nein, ich habe meine Meinung geändert. Such dir einen anderen Helfer. Auf Wiedersehen...";
			link.l2.go = "Convict_15_2";
		break;
		
		case "Convict_15_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "Aber natürlich! Sie haben unsere Freiheit genommen, aber nicht unser Gewissen! Bitte nehmen Sie Ihr Geld zusammen mit unserer grenzenlosen Dankbarkeit. Sie haben uns wirklich geholfen. Macht es Ihnen etwas aus, wenn wir Ihnen in Silberbarren zahlen?";
					link.l1 = "Sicher, das tue ich nicht. Viel Glück auf deiner Reise. Und bete, dass ich dir nicht auf offener See begegne, ich werde kurzen Prozess mit dir machen.";
					link.l1.go = "Convict_15_1_1End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Commerce", 30);
					TakeNItems(pchar, "jewelry6", makeint(sti(pchar.GenQuest.Convict.ShipPrice)/50));
				break;
				case 2:
					dialog.text = "Kapitän, Sie wissen, wir dachten, dass Geld im Leben wirklich nicht so wichtig ist. Und ehrlich gesagt, wir brauchen es momentan viel mehr als Sie. Aber wir haben eine Sache, die wir unserem ehemaligen Boss gestohlen haben. Vielleicht würde es Sie viel mehr als Gold interessieren. Möchten Sie einen Blick darauf werfen?...";
					link.l1 = "Ja, du hast recht. Das ist wirklich eine wunderbare Sache. Also gut, wir haben einen Deal, danke und auf Wiedersehen.";
					link.l1.go = "Convict_15_1_2End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Fortune", 30);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				break;
				case 3:
					pchar.GenQuest.Convict = "FightInShore";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					dialog.text = "Warum zum Teufel brauchst du so viel Geld, Kapitän? Du bist sowieso reich, und wir sind verloren, wenn wir dieses Schiff nicht bekommen. Also... wir werden es einfach von dir nehmen. Nichts für ungut.";
					link.l1 = "Das war dein letzter Fehler. Ohne ein Schiff könntest du noch wegschwimmen, aber jetzt wirst du entweder treiben oder sinken.";
					link.l1.go = "Convict_Fight";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Sneak", 30);
				break;
			}
		break;
	
		case "Convict_15_1_1End":
			AddQuestRecord("Convict", "4");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
	
		case "Convict_15_1_2End":
			AddQuestRecord("Convict", "5");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;	
	
		case "Convict_15_2":
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");
			for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
			{
				sld = CharacterFromID("Convict_" + i);
				sld.LifeDay = 0;
			}	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);	
			LAi_group_Delete("ConvictGroup");
			DeleteAttribute(pchar, "GenQuest.Convict");
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16":
			dialog.text = RandPhraseSimple("Also, Kapitän? Können wir anfangen, uns zu beladen?","Endlich! Wir haben uns schon Sorgen gemacht, wir dachten, dass du deine Meinung geändert hast.");
			link.l1 = "Entschuldigung, ich habe meine Pläne geändert. Sie müssen jetzt einen anderen Kapitän suchen.";
			link.l1.go = "Convict_16_1";
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				link.l2 = "Laden Sie in das Boot, ich habe nicht viel Zeit.";
				link.l2.go = "Convict_16_2";			
			}			
			if(pchar.GenQuest.Convict == "ToShore" && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l2 = "Steig ins Boot, ich habe nicht viel Zeit.";
				link.l2.go = "Convict_16_2";			
			}			
		break;
		
		case "Convict_16_1":
			if(rand(1) == 0)
			{
				dialog.text = "Verdammt seist du! Sicherlich hast du bereits eine Patrouille nach uns geschickt?! Du wirst damit nicht davonkommen!";
				link.l1 = "Wovon redest du?! Willst du sterben oder was?!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "ShoreFight";
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			else
			{
				dialog.text = "Kapitän "+GetSexPhrase(", bist du ein Mann deines Wortes oder was?","?")+"Oder bist du nur ein verfluchter Schwätzer...";
				link.l1 = "Du solltest besser auf deine Zunge aufpassen...";
				link.l1.go = "Convict_16_3";
			}
		break;
		
		case "Convict_16_2":
			if(pchar.GenQuest.Convict == "ToShore")
			{
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterCrew(pchar, sti(pchar.GenQuest.Convict.ConvictQty));
				OfficersReaction("bad");
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "10");
				CloseQuestHeader("Convict");				
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				AddQuestRecord("Convict", "10");
				sld = characterFromId("Convict_0");
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false); 
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				SetFunctionLocationCondition("Convict_OnMayak", pchar.GenQuest.Convict.Mayak, true);
				locations[FindLocation(pchar.GenQuest.Convict.Mayak)].DisableEncounters = true;			
			}
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");
			pchar.GenQuest.Convict = "close";
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");				
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			AddDialogExitQuestFunction("Convict_DialogDisable");			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
						
		case "Convict_17":
			dialog.text = LinkRandPhrase("Oh, danke, "+GetSexPhrase("guter Mann","schönes Mädel")+".","Danke, Kapitän, Sie haben mich wirklich vom Galgen gerettet.","Schätze solch eine feine Reise sehr.");
			link.l1 = LinkRandPhrase("Das ist alles gut und schön, aber ich warte auf das Geld.","Es ist Zeit zu zahlen, du weißt.","Bargeld auf den Nagel, wie wir vereinbart haben.");
			link.l1.go = "Convict_17_1";
		break;
		
		case "Convict_17_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "Natürlich, was für Fragen! Hier ist Ihr Geld in Goldbarren und bitte akzeptieren Sie unseren aufrichtigsten Dank.";
					link.l1 = "Viel Glück auch dir. Lebewohl.";
					link.l1.go = "Convict_17_1_1End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Commerce", 80);
					TakeNItems(pchar, "jewelry5", makeint(sti(pchar.GenQuest.Convict.Sum)/200));
					break;
				case 2:
					dialog.text = "Kapitän, Sie wissen, wir dachten, dass Geld im Leben wirklich nicht so wichtig ist. Und ehrlich gesagt, wir brauchen es im Moment viel dringender als Sie. Aber wir haben eine Sache, die wir von unserem ehemaligen Chef gestohlen haben. Vielleicht würde es Sie viel mehr interessieren als Gold. Möchten Sie mal sehen?...";
					link.l1 = "Ja, du hast recht. Das ist in der Tat eine wunderbare Sache. Also gut, wir haben einen Deal, danke und auf Wiedersehen.";
					link.l1.go = "Convict_17_1_2End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Fortune", 80);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
					break;
				case 3:
					dialog.text = "Warum brauchst du so viel Geld? Du bist sowieso reich. Du hast uns geholfen, wir helfen dir bei einer anderen Gelegenheit.";
					link.l1 = "Es wird nicht so eine Gelegenheit geben. Betet, ihr Schurken, ich dulde keine Schulden.";
					link.l1.go = "Convict_Fight";
					pchar.GenQuest.Convict = "MayakFight";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Sneak", 80);			
					break;
			}
		break;
		
		
		case "Convict_17_1_1End":
			AddQuestRecord("Convict", "11");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));	//belamour gen			
			AddQuestUserData("Convict", "sSum", makeint(pchar.GenQuest.Convict.Sum));
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_17_1_2End":
			AddQuestRecord("Convict", "12");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));	// belamour gen	
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;		
		// <-- Генератор "State convicts"
		
		// Генератор "A reason to hurry" -->
		// Встреча с ОЗГ на берегу
		case "ReasonToFast_Hunter1":
			dialog.text = "Ich wurde hierher geschickt von "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" selbst...";
			link.l1 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" wartet bereits seit ein paar Stunden mit einer Antwort auf dich. Er hat mich sofort nach dir geschickt.";
			link.l1.go = "ReasonToFast_Hunter4";
		break;
		
		case "ReasonToFast_Hunter2":
			dialog.text = "Ich folge dir schon eine ganze Weile in deinem Kielwasser, aber du bist einfach zu schnell.";
			link.l1 = "Und was jetzt?";
			link.l1.go = "ReasonToFast_Hunter6";		
		break;
		
		case "ReasonToFast_Hunter3":
			dialog.text = "Besser sag mir, wie viel zahlt der Gouverneur seinen Untergebenen?";
			link.l1 = "Verdammt!";
			link.l1.go = "ReasonToFast_Fight";		
		break;
		
		case "ReasonToFast_Hunter4":
			dialog.text = "Ich habe nicht getrunken! Ich habe nach dem Bootsmann gesucht...";
			link.l1 = "Geh jetzt... Ich werde erzählen "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+", dass du im Dschungel verloren warst.";
			link.l1.go = "ReasonToFast_Hunter5";		
			AddQuestRecord("ReasonToFast", "5");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
		break;
		
		case "ReasonToFast_Hunter5":
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_HunterGoOut");
		break;
		
		case "ReasonToFast_Hunter6":
			pchar.questTemp.ReasonToFast = "MeetHunterFail";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_PatrolAngry");
		break;
		
		case "ReasonToFast_Fight":
			LAi_SetPlayerType(pchar);
			pchar.questTemp.ReasonToFast = "PatrolAngry";
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY); 
			pchar.GenQuest.HunterScore2Pause = 1; //НЗГ не начисляются
			pchar.GenQuest.ReputationNotChange = 1; //репутацию не менять
			sTemp = "Patrol" + pchar.questTemp.ReasonToFast.LocIdx + "_";
			sGroup = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
			iTemp = sti(pchar.questTemp.ReasonToFast.PatrolNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("ReasonToFast_Hunter");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		// бой с кэпом пиратского корабля
		case "ReasonToFast_FightCap": 
			dialog.text = "Und du bist ein schlauer. Betet zu Gott, dass eure Tricks nicht bekannt werden "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+".";
			link.l1 = "Er wird es nicht wissen, wenn du es ihm nicht sagst... Und du wirst es nicht tun, oder?";
			link.l1.go = "ReasonToFast_FightCap_1";
		break;
		
		case "ReasonToFast_FightCap_1":
			dialog.text = "Warum? Sicherlich werde ich das tun, und das mit großem Vergnügen!";
			link.l1 = "Er wird dich sowieso für diese Torheit hängen. Also verschwenden wir keine Zeit, und ich werde dir helfen, dem Galgen zu entkommen.";
			link.l1.go = "ReasonToFast_FightCap_2";
		break;
		
		case "ReasonToFast_FightCap_2":
			dialog.text = "Hmm... Und wie gedenkst du das zu tun?";
			link.l1 = "Ich werde dich selbst töten...";
			link.l1.go = "ReasonToFast_FightCap_Last";
		break;
		
		case "ReasonToFast_FightCap_Last":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;		
		
		// встреча с лакеем в резиденции
		case "ReasonToFast_Lakey":
			dialog.text = "Hast du hier Geschäfte zu erledigen, "+GetSexPhrase("Herr","Fräulein")+"?";
			link.l1 = "Nein-nein, ich bin hier auf Einladung der charmanten Gouverneursfrau, um mir diese wirklich luxuriöse Residenz anzuschauen.";
			link.l1.go = "ReasonToFast_Lakey1";
			link.l2 = "Ich habe eine Nachricht von Leuten, die du kennst.";
			link.l2.go = "ReasonToFast_Lakey2";
			link.l3 = "Ja. Ich will dich der Gerechtigkeit zuführen!";
			link.l3.go = "ReasonToFast_Lakey3";
			pchar.questTemp.ReasonToFast = "MeetLakey";
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_Lakey1":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "Oh ja, ich hatte wirklich Glück, in einem so schönen Haus dienen zu dürfen.";
			link.l1 = "Kein Wunder...";
			link.l1.go = "ReasonToFast_Lakey11";
		break;

		case "ReasonToFast_Lakey11":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "Vergiss nicht, unseren Garten zu besichtigen!";
			link.l1 = "Danke, guter Mann!";
			link.l1.go = "exit";			
			bDisableFastReload = false;
		break;
		
		case "ReasonToFast_Lakey2":
			dialog.text = "Ehh... "+pchar.questTemp.ReasonToFast.password+"?";
			link.l1.edit = 1;			
			link.l1 = ""; 
			link.l1.go = "ReasonToFast_Lakey21";
		break;

		case "ReasonToFast_Lakey3":
			dialog.text = "Du wirst damit nicht davonkommen, Verräter!";
			link.l1 = "Halt still, Schurke!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;			
		break;

		case "ReasonToFast_Lakey21":
			if(GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipName) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Schnell jetzt! Nimm alles Wertvolle und lauf!";
				link.l1 = "Ich denke, du solltest auch laufen.";
				link.l1.go = "ReasonToFast_Lakey_exit";
				TakeNItems(pchar,"icollection", sti(pchar.questTemp.ReasonToFast.p8));
				TakeNItems(pchar,"Chest", sti(pchar.questTemp.ReasonToFast.p7));
				pchar.questTemp.ReasonToFast = "LakeyExitSuccess";					
				bDisableFastReload = true;		
				//chrDisableReloadToLocation = true;			
			}
			else
			{
				dialog.text = "Mmm, entschuldigen Sie, ich muss gehen.";
				link.l1 = "Halt still, Schurke!";
				link.l1.go = "ReasonToFast_Lakey_exit";
				pchar.questTemp.ReasonToFast = "LakeyExitFail";
				bDisableFastReload = false;
			}			 
		break;

		case "ReasonToFast_Lakey_exit":
			DialogExit();	
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.ReasonToFast_ClearLakey.over = "yes"; //снимаем таймер
			ReasonToFast_SetHunterCoastal();
			AddDialogExitQuest("ReasonToFast_LakeyGoOut");
		break;		
		
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Du bist "+GetSexPhrase("ein Dieb, wie ich sehe! Wachen, schnappt ihn","ein Dieb, sehe ich! Wachen, ergreift sie")+"!","Ich kann es nicht glauben! Ich habe mich für eine Sekunde abgewendet und du tauchst in meine Truhe ein! Stoppt den Dieb!","Wachen! Raub! Haltet den Dieb!");
			link.l1 = "Aaaah, Teufel!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;
		break; 
		// Генератор "A reason to hurry" <--
		
		// ситуации с капитаном захваченного корабля
		// взрыв на корабле
		case "ShipSituation11": // пираты или ДУ
			dialog.text = RandPhraseSimple("Hallo, "+GetSexPhrase("Kumpel","lass")+"! Ich habe eine Überraschung für dich vorbereitet, ich habe die Zündschnur zur Pulverkammer entzündet. Es wird in alle Himmelsrichtungen fliegen!","Warum stehst du da? Es brennt im Pulverkammer! Es wird explodieren, und das Feuerwerk wird man in Europa sehen!");
			link.l1 = RandPhraseSimple("Du Schuft, du wirst mich nicht überlisten! Kämpfe, du Feigling!","Ich sehe die Ratten das Schiff verlassen, und du bist einer der Ersten?");
			link.l1.go = "ShipSituation12";
		break;
		
		case "ShipSituation12":
			dialog.text = RandPhraseSimple("Du solltest auch laufen, wenn dir dein Leben lieb ist... Nun, ich habe keine Zeit, ein Boot wartet auf mich. Viel Spaß beim Angeln!","Ich habe keine Zeit, den Helden zu spielen, die Jungs im Boot warten auf mich. Viel Spaß beim Angeln, Gewinner!");
			link.l1 = RandPhraseSimple("Verdammt! Schneidet die Fender ab! Los!","Oh, Gott, wie konnten wir in so ein Durcheinander geraten! Öffnet die Seeschleusen! Macht los!");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation21": // военный корабль (не флагман)
			dialog.text = "So?! Du denkst, du hast den Kampf gewonnen?! Auf keinen Fall. Ich habe die Pulverkammer in Brand gesetzt, du wirst dieses Schiff nicht lebend verlassen.";
			link.l1 = RandPhraseSimple("Du Schurke, du wirst mich nicht täuschen! Kämpfe, du Feigling!","Ich sehe die Ratten das Schiff verlassen, und du bist einer der Ersten?");
			link.l1.go = "ShipSituation22";
		break;
		
		case "ShipSituation22":
			dialog.text = RandPhraseSimple("Ich bin durch einen Eid gebunden, aber das bedeutet nicht, dass ich für nichts Gutes sterben muss. Entschuldigung, dass ich Ihnen keinen Platz im Boot anbiete, die Seeleute werden es nicht verstehen.","Die Schiffe sind beim Entern miteinander verbunden, also ist dein Schicksal besiegelt. Entschuldigung, aber mein Boot wartet...");
			link.l1 = RandPhraseSimple("Verdammt! Schneidet die Fender ab! Geht von Bord!","Oh, Gott, wie konnten wir nur in so ein Durcheinander geraten! Öffnet die Seeeinlässe! Zieht ab!");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation31": // ОЗГ
			dialog.text = RandPhraseSimple("Du bist siegreich! Willkommen in der Hölle! Ich habe einen Pulverraum in Brand gesetzt.","Hier bist du, mein guter Mann! Und du bist erledigt, ich habe einen Pulverraum in Brand gesetzt.");
			link.l1 = RandPhraseSimple("Du Schuft, du wirst mich nicht täuschen! Kämpfe, du Feigling!","Ich sehe die Ratten das Schiff verlassen, und du bist unter den Ersten?");
			link.l1.go = "ShipSituation32";
		break;
		
		case "ShipSituation32":
			dialog.text = RandPhraseSimple("Ich habe dich schon eine ganze Weile verfolgt. Schade, dass ich mein Schiff opfern musste, aber dein Kopf ist sowieso zwei neue wert. Viel Spaß beim Angeln!","Seht ihr, wie ihr gehen werdet? Mit Feuerwerken, wie ein indischer Prinz"+GetSexPhrase("ce","Dreck")+". Aber ich werde nicht als Verlierer dastehen, dein Kopf ist viel mehr wert als mein Schiff. Leb wohl, mein Boot wird nicht zu lange warten...");
			link.l1 = RandPhraseSimple("Verdammt! Schneidet die Fender ab! Fahrt los!","Oh, Gott, wie konnten wir in solch ein Durcheinander geraten! Öffnet die Seeeinlässe! Legt ab!");
			link.l1.go = "ShipSituation_End";			
		break;
		
		case "ShipSituation_End":
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			NPChar.LifeDay = 0;
			LAi_LockFightMode(pchar, false);	
			Log_Info(XI_ConvertString("Ship can explode"));
			pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4;	
			pchar.GenQuest.ShipSituation.Explosion.CapId = NPChar.CaptanId;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		// эпидемия
		case "ShipEpidemy1":
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = RandPhraseSimple("Halt ein, Kapitän! Für ein paar Worte.","Halt ein, Kapitän! Ich denke, das könnte für dich interessant sein.");
			link.l1 = LinkRandPhrase("Warum reden während eines Kampfes?!","Und worüber sollte ich mit einem toten Mann sprechen?","Was ist los? Willst du ein Testament in meinem Namen machen?");
			link.l1.go = "ShipEpidemy2";
		break;
		
		case "ShipEpidemy2":
			dialog.text = "Es gibt einen Krankheitsausbruch an Bord. Ich habe während der Reise ein Viertel meiner Besatzung verloren. Ihr seid alle verdammt...";
			link.l1 = RandPhraseSimple("Du verdammtes Gesindel! Warum hast du kein Signal gezeigt, dass es eine Katastrophe auf deinem Schiff gibt?!","Hast du den Seecode vergessen? Du hättest ein Signal am Mast anzeigen müssen, dass es eine Katastrophe auf deinem Schiff gibt!");
			link.l1.go = "ShipEpidemy3";
		break;
		
		case "ShipEpidemy3":
			dialog.text = "Wir standen sowieso kurz vor dem Tod. Deshalb haben wir nicht aufgegeben, wir wollten dich und deine Teufel mit uns in die nächste Welt mitnehmen! Jetzt bin ich völlig zufrieden. Du kannst deine abscheuliche Tat vollenden.";
			link.l1 = RandPhraseSimple("Du wirst dafür büßen!..","Mir gefällt die Idee, dass du zuerst stirbst. Und ich werde zusehen.");
			link.l1.go = "ShipEpidemy31";
			link.l2 = RandPhraseSimple("Ich werde meine Klinge nicht mit deinem schmutzigen Blut beflecken, du darfst leben, obwohl... wofür? Ich nehme meine Mannschaft von diesem verrotteten alten Kahn weg.","Du solltest dafür zum Galgen geschickt werden, aber das ist jetzt nicht nötig. Ich nehme meine Männer mit... Du darfst leben, obwohl deine Zeit kurz sein sollte...");
			link.l2.go = "ShipEpidemy32";
			pchar.GenQuest.ShipSituation.Epidemy.CapId = NPChar.CaptanId;
			pchar.GenQuest.ShipSituation.Epidemy = ShipSituation_4;
		break;
		
		case "ShipEpidemy31":
			pchar.GenQuest.QuestAboardCabinDialogIdx = NPChar.index;
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Died"; // вражеский кэп на волосок от смерти от переизбытка стали и свинца в организме
			LAi_LockFightMode(pchar, false);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "ShipEpidemy32":
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			LAi_LockFightMode(pchar, false);	
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Live"; // вражеский кэп остался в живых
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		// ситуации с капитаном захваченного корабля
		
		// Генератор "A damsel in the jungle"
		case "EncGirl_Lover":
			dialog.text = "Hallo, Kapitän, mir wurde gesagt, dass Sie nach mir gesucht haben.";
			link.l1 = "Ich bin - wenn du bist "+pchar.GenQuest.EncGirl.sLoverId+".";
			link.l1.go = "EncGirl_Lover1";
		break;
		
		case "EncGirl_Lover1":
			dialog.text = "Das bin ich. Irgendwas wichtiges?";
			link.l1 = "Ich weiß nicht, ob das für Sie wichtig ist, aber ich habe gebracht "+pchar.GenQuest.EncGirl.name+". Sie ist von zu Hause weggelaufen und wartet jetzt nicht weit von der Taverne auf dich.";
			link.l1.go = "EncGirl_Lover2";
		break;
		
		case "EncGirl_Lover2":
			dialog.text = "Oh mein Gott... Ich wusste, dass es so enden würde... Und warum ist sie weggelaufen? Hat sie dir das gesagt?";
			link.l1 = "Ihr Vater will sie an den Sohn des Wucherers verheiraten.";
			link.l1.go = "EncGirl_Lover3";
		break;
		
		case "EncGirl_Lover3":
			pchar.GenQuest.EncGirl.LoverCity = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			pchar.GenQuest.EncGirl.LoverIsland = GetIslandByCityName(pchar.GenQuest.EncGirl.LoverCity);
			dialog.text = "Oh nein, das können wir nicht zulassen! Kapitän, Sie wissen, ich bin in so einer dummen Situation... Ich wollte Sie bitten, uns zu "+XI_ConvertString(pchar.GenQuest.EncGirl.LoverIsland+"Konto")+" zu Stadt namens "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.LoverCity)+", aber momentan habe ich kein Geld und habe immer noch keinen Job gefunden. Ich habe eine wohlhabende Familie und eine vielversprechende Karriere in "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.LoverCity)+"...\nIch versichere Ihnen, meine Eltern werden sich freuen, mich mit einer jungen Verlobten zu sehen und sie werden Sie gut belohnen. Also, bist du dabei?";
			link.l1 = "...Hör jetzt zu, ich habe ganz andere Pläne. Ich kann dir einen Rat geben, einen Job als Seemann zu bekommen und für deinen Lohn eine Kabine für deine Braut zu mieten. Auf diese Weise kommen Menschen nach Europa, und diese Siedlung von dir ist in einer Vogelnachtflug.";
			link.l1.go = "EncGirl_Lover4";
			link.l2 = "Oh, die Jugend... Begreifst du, was du mich bittest zu tun? Ein Mädchen ohne den Segen ihrer Eltern wegnehmen? ... Und welcher Mann würde so etwas ablehnen, natürlich bin ich dabei!";
			link.l2.go = "EncGirl_Lover5";
		break;
		
		case "EncGirl_Lover4":
			npchar.lifeDay = 0;
			AddDialogExitQuestFunction("EncGirl_LoverExit");	
			DialogExit();
		break;
		
		case "EncGirl_Lover5":
			AddDialogExitQuestFunction("EncGirl_ToLoverParents");	
			DialogExit();
		break;
		
		case "EncGirl_Lover6":
			AddSimpleRumourCityTip(RandPhraseSimple("Have you heard, " + pchar.GenQuest.EncGirl.name + " ran off with her lover. She decided not to bind her life to an invalid. That's surely the mistake of her parents, they should not have become tempted with the money of her fiance and try to give such a beauty in marriage to a fright.",  
				"Have you heard?" + pchar.GenQuest.EncGirl.name + " tricked both her dad and her would-be fiance. They say one noble captain helped her and her lover to get to another island, where her lover's parents lived... Imagine that, there still are people, who had not yet forgotten the taste of passion!"), pchar.GenQuest.EncGirl.LoverCity, 3, 2, "citizen,habitue", "");
			dialog.text = "Danke, Kapitän. Wir werden uns den Rest unseres Lebens an Ihre Hilfe erinnern.";
			link.l1 = "Es war nichts. Ich hoffe, alles wird gut für dich laufen.";
			link.l1.go = "EncGirl_Lover7";
		break;
		
		case "EncGirl_Lover7":
			switch (rand(4))
			{
				case 0:
					sTemp = "the shop";
					pchar.GenQuest.EncGirl.LoverFather = "store_keeper";
				break;
				case 1:
					sTemp = "the shipyard";					
					pchar.GenQuest.EncGirl.LoverFather = "shipyard_keeper";
				break;
				case 2:
					sTemp = "the port office";					
					pchar.GenQuest.EncGirl.LoverFather = "portman_keeper";
				break;
				case 3:
					sTemp = "the tavern";					
					pchar.GenQuest.EncGirl.LoverFather = "tavern_keeper";
				break;
				case 4:
					sTemp = "the bank";					
					pchar.GenQuest.EncGirl.LoverFather = "usurer_keeper";
				break;
			}	
			pchar.GenQuest.EncGirl.FatherLoc = sTemp;
			dialog.text = "Ich habe versprochen, dich meinen Eltern vorzustellen. Wenn du zufällig eine freie Minute hast, komm bitte zu "+sTemp+", mein Vater arbeitet dort, und ich werde ihm erzählen, was du für uns getan hast. Ich bin sicher, er wird sich freuen, dich zu sehen.";
			link.l1 = "In Ordnung, ich schau vorbei, sobald ich einen Moment Zeit habe. Seid glücklich und passt aufeinander auf, ihr beide...";
			link.l1.go = "EncGirl_Lover8";
		break;
		
		case "EncGirl_Lover8":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			npchar.lifeday = 0;
			AddQuestRecord("JungleGirl", "16");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sText", pchar.GenQuest.EncGirl.FatherLoc);
			if((GetSummonSkillFromName(pchar, SKILL_FORTUNE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)) < 175)
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 0; // папочка жениха счастлив за сына :)
			}
			else
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 1; // папочка жениха разъярен за то что сын притащил в дом шалаву :)
			}
			chrDisableReloadToLocation = false; 
			pchar.GenQuest.EncGirl = "toLoverFather";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.function = "EncGirl_GenQuest_GetLoverFather";
			DialogExit();	
		break;
		// Генератор "A damsel in the jungle"
		
		// Генератор "Captain's request"
		case "CaptainComission_1":
			dialog.text = RandPhraseSimple("Halt an! Halt an, Kapitän! Bitte.","Kapitän, bitte, warten Sie, ich flehe Sie an...");
			link.l1 = LinkRandPhrase("Was? Den Atem verloren?","Erhebe deine Klinge, du Feigling!","Was ist los? Hast du vergessen, ein Testament zu machen?");
			link.l1.go = "CaptainComission_2";
		break;
		
		case "CaptainComission_2":
			dialog.text = "Warte... Ich bin verletzt und zu schwach um weiter zu kämpfen... Ich bitte nicht um Gnade, aber ich habe eine unvollendete Angelegenheit. Bitte, versprich mir, dass du den letzten Willen eines sterbenden Mannes erfüllen wirst.";
			link.l1 = RandPhraseSimple("Sei kein Weichei, Kapitän, akzeptiere den Tod wie ein Mann es tun sollte!","Kapitän, was für eine Sentimentalität? Eine Schlacht tobt ringsum, also lasst uns beenden, was wir begonnen haben.");
			link.l1.go = "CaptainComission_21";
			link.l2 = "Sprechen Sie jetzt und machen Sie es schnell.";
			link.l2.go = "CaptainComission_22";
		break;
		
		case "CaptainComission_21":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_22":		
			if(rand(1) == 0) // "Ransom"
			{
				CaptainComission_Init(NPChar);
				dialog.text = "Sag "+pchar.GenQuest.CaptainComission.Name+" aus der Siedlung von "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City)+", dass ich es versäumt habe, seine Bitte zu erfüllen... bevor ich Zeit hatte... Möge er mir vergeben...";
				link.l1 = RandPhraseSimple("Und das ist alles?! Gut, ich kann es tun. Hey, Freund...","In Ordnung, ich werde es ihm sagen, wenn ich Zeit habe. Hey, Freund...");
				link.l1.go = "CaptainComission_22_1";
				link.l2 = "Ich glaube nicht. Ich habe keine Zeit für solchen Unsinn. Lassen wir beenden, was wir begonnen haben.";
				link.l2.go = "CaptainComission_22_2";
			}
			else // "Operation 'Galleon'"
			{			
				CaptainComission_GaleonInit(NPChar);
				dialog.text = "Bitte, informieren Sie den Kapitän einer Patrouille "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Gen"))+" '"+pchar.GenQuest.CaptainComission.ShipTypeName+"' "+pchar.GenQuest.CaptainComission.Name+", dass er sein Gesicht nicht zeigen sollte in "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Stimme")+"..."+"Die Behörden sind sich der wahren Umstände seines Todes bewusst "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Gen"))+" '"+pchar.GenQuest.CaptainComission.VictimShipName+"... die Zeit ist knapp, er wird verhaftet werden... segelt nach "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Akk")+" von "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City1+"Gen")+", die Reise wird fast fünfzehn Tage dauern... ahh ... wir sollten uns beeilen..."; // belamour gen
				link.l1 = RandPhraseSimple("Ich verspreche nichts, aber ich werde bei Gelegenheit versuchen. Hey, Freund...","Gut, ich werde es ihm sagen, wenn ich Zeit habe. Hey, Freund...");
				link.l1.go = "CaptainComission_300";
			}					
		break;
		
		case "CaptainComission_22_1":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));	
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();	
		break;
		
		case "CaptainComission_22_2":
			dialog.text = "So eine Grausamkeit! Ich hoffe, du wirst dafür bezahlen.";
			link.l1 = "Und für viel mehr ...";
			link.l1.go = "CaptainComission_22_3";
		break;
		
		case "CaptainComission_22_3":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			pchar.GenQuest.CaptainComission = "Begin_2";
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_3":
			dialog.text = LinkRandPhrase("Ich höre Ihnen zu, "+GetAddress_Form(pchar)+".","Was wolltest du?","Wie kann ich Ihnen helfen?");
			if (pchar.GenQuest.CaptainComission == "Begin_1" || pchar.GenQuest.CaptainComission == "Begin_2") // лесник - доп.проверка если есть квест. для перехода .
			{	
			link.l1 = "Bist du "+pchar.GenQuest.CaptainComission.Name+"? Ich habe Geschäfte mit Ihnen. Kapitän "+pchar.GenQuest.CaptainComission.CapName+" bat mich, Ihnen eine wichtige Information zu übermitteln.";
			link.l1.go = "CaptainComission_4";
			break;
			}
			link.l2 = "Nein, nichts...";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_3"; // лесник - переход чтобы не вызывал баг при повтороном обращении
		break;
		
		case "CaptainComission_4":
			dialog.text = "Hat er? In Ordnung. Also, was ist es, dass Kapitän "+pchar.GenQuest.CaptainComission.CapName+"wollte, dass ich es weiß?";
			link.l1 = "Er bat mich, Ihnen zu sagen, dass er Ihre Anfrage nicht erfüllen kann.";
			link.l1.go = "CaptainComission_5";
		break;
		
		case "CaptainComission_5":
			dialog.text = "Wovon sprichst du?! Ich kenne ihn schon seit Ewigkeiten, er ist ein sehr ehrlicher Mann. Er konnte dir das einfach nicht gesagt haben!";
			link.l1 = "Sagen wir mal, es war aus Gründen, die er nicht kontrollieren konnte. Mit anderen Worten - das war sein letzter Wunsch.";
			link.l1.go = "CaptainComission_6";
		break;
		
		case "CaptainComission_6":
			CaptainComission_GetPirateIsland();
			CaptainComission_GetFamilyType();
			if(pchar.GenQuest.CaptainComission == "Begin_1")
			{
				dialog.text = "Ach, das ist völlig fehl am Platz! So viel verschwendete Zeit\n"+"Kapitän, in diesem Fall muss ich Sie bitten, mir zu helfen. Piraten von  "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Gen")+" haben meinen Verwandten gefangen genommen "+pchar.GenQuest.CaptainComission.SlaveName+" und verlangen ein Lösegeld für ihn. Könnten Sie diese Mission übernehmen? Die Belohnung sollte ziemlich großzügig sein.";
				link.l1 = "Leider habe ich andere Pläne.";
				link.l1.go = "CaptainComission_6_1";
				link.l2 = "Ich werde versuchen, Ihnen zu helfen, wenn Sie es genauer erklären.";
				link.l2.go = "CaptainComission_6_2";
			}
			
			if(pchar.GenQuest.CaptainComission == "Begin_2")
			{
				dialog.text = "Ach, das ist völlig fehl am Platz! So viel Zeit verschwendet\nUnd was ist mit den Truhen?";
				link.l1 = "Ähm... welche Truhen?";
				link.l1.go = "CaptainComission_6_3";
				pchar.GenQuest.CaptainComission.CanFindChest = true;
			}	
		break;
		
		case "CaptainComission_6_1":
			dialog.text = "Schade, Kapitän... Es ist schade, dass Sie nicht bereit sind, mir zu helfen.";
			link.l1 = "Das ist keine Frage meines Willens, mein Freund. Du musst verstehen. Auf Wiedersehen.";
			link.l1.go = "CaptainComission_6_1End";
		break;
		
		case "CaptainComission_6_2":
			dialog.text = "Gestern habe ich einen Brief von "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_ACC)+", in dem er mir mitteilte, dass das Lösegeld höher sein wird und er droht auch, ihn in die Sklaverei zu verkaufen. Der verstorbene Kapitän hätte benachrichtigen sollen "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_ACC)+", dass ich den früheren Bedingungen zustimme und eine Anzahlung leiste. Aber jetzt sehe ich, warum die Piraten die Einsätze erhöht haben.";
			link.l1 = "Und was schlägst du vor?";
			link.l1.go = "CaptainComission_6_21";
		break;
		
		case "CaptainComission_6_3":
			dialog.text = "Oh, "+GetSexPhrase("Kamerad","lass")+", Ich spüre üble Spielchen hier. Ich warne Sie, dass dies sehr gefährlich ist und schlimme Folgen haben kann. Kapitän "+pchar.GenQuest.CaptainComission.CapName+" hatte drei Kisten voller Gold, das er hätte übergeben sollen "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_DAT)+" auf "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Konto")+" als Lösegeld für einen Mann -  "+pchar.GenQuest.CaptainComission.SlaveName+". Und wenn er wollte, dass du zu uns kommst, könnte er nicht vergessen haben, dir von den Truhen zu erzählen.";
			link.l1 = "Während er sein letztes sprach, schien es nicht, als hätte er seinen Satz beendet. Ich hoffte, du würdest mir mehr erzählen.";
			link.l1.go = "CaptainComission_6_31";
		break;
		
		case "CaptainComission_6_1End":
			AddQuestRecord("CaptainComission1", "3");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCharType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			CloseQuestHeader("CaptainComission1");
			sld = CharacterFromID("CapComission_1"); // удаление если послал нахуй. лесник.
			sld.LifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DialogExit();	
		break;
		
		case "CaptainComission_6_21":
			dialog.text = "Ich habe keine andere Wahl... Ich habe bereits die benötigte Summe gesammelt, 150 000 Pesos. Ich bitte Sie, es zu liefern an "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Konto")+" und bring meinen Verwandten hierher. Ich werde dir 40 000 bezahlen, sobald es erledigt ist.";
			link.l1 = "Gut, ich bin bereit.";
			link.l1.go = "CaptainComission_6_22";
			link.l2 = "Leider habe ich andere Pläne.";
			link.l2.go = "CaptainComission_6_1";			
		break;
		
		case "CaptainComission_6_22":
			dialog.text = "Dann nimm das Geld und möge unser Herr dich segnen. Aber bitte, beeil dich. Ich fürchte, dass "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_NOM)+" wird nicht warten und die arme Seele in die Sklaverei verkaufen.";
			link.l1 = "Warte hier auf mich. Ich glaube, es wird nicht allzu lange dauern.";
			link.l1.go = "CaptainComission_6_22End";
		break;
		
		case "CaptainComission_6_22End":
			AddQuestRecord("CaptainComission1", "4");
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sFamilyType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			addMoneyToCharacter(pchar, 150000);
			pchar.GenQuest.CaptainComission = "Begin_11";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "goodSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_6_31":
			dialog.text = "Es ist egal\nDie Leute, die das Lösegeld gesammelt haben, kümmern sich nicht. Sie brauchen nur das Ergebnis, atmen und in einem Stück - "+pchar.GenQuest.CaptainComission.SlaveName+". Also verschwende keine Zeit.";
			link.l1 = "Und was, wenn ich ablehne?";
			link.l1.go = "CaptainComission_6_32";
		break;
						
		case "CaptainComission_6_32":
			dialog.text = "Eigentlich brauche ich Ihre Zustimmung nicht. Ich teile Ihnen nur mit, dass Sie liefern müssen "+pchar.GenQuest.CaptainComission.SlaveName+" lebendig und trittend zur Taverne, ich werde Kopfgeldjäger hinter dir hersenden...";
			link.l1 = "Hmm... Das ist ernst. Und wenn ich es mache?";
			link.l1.go = "CaptainComission_6_33";
		break;
		
		case "CaptainComission_6_33":
			dialog.text = "Dann werden wir es weiter besprechen.";
			link.l1 = "Also gut... Mal sehen, wie es läuft.";
			link.l1.go = "CaptainComission_6_33End";
		break;
		
		case "CaptainComission_6_33End":
			AddQuestRecord("CaptainComission1", "5");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCapName",pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			pchar.GenQuest.CaptainComission = "Begin_22";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "badSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_7":
			if(pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Hallo, Kapitän "+GetFullName(pchar)+". Irgendwelche Neuigkeiten?","Also, Kapitän, haben Sie das Lösegeld bereits geliefert?","Hallo, ich hoffe, Sie kommen mit guten Nachrichten?");
					if(makeint(pchar.money)>=150000)
					{
						link.l1 = "Leider haben sich meine Pläne geändert, daher muss ich unseren Deal abbrechen.";
						link.l1.go = "CaptainComission_7_1";
					}
					link.l2 = "Noch nicht. Ich bin immer noch damit beschäftigt.";
					link.l2.go = "CaptainComission_7_2";
				}
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
				{
					dialog.text = LinkRandPhrase("Oh, freut mich, dich zu begrüßen, Kapitän "+GetFullName(pchar)+". Gibt es gute Neuigkeiten?","So, Kapitän, haben Sie unseren leidenden Freund gerettet?","Froh, Sie lebendig und aktiv zu sehen, Kapitän. Wie steht es um unsere gemeinsame Angelegenheit?");
					link.l1 = "Bisher keine Neuigkeiten, aber ich bin dran.";
					link.l1.go = "CaptainComission_7_3";
					link.l2 = "Hör zu, Freund, und warum versuchst du, mich für diesen Handel verantwortlich zu machen?";
					link.l2.go = "CaptainComission_7_4";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "GetSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Hallo, Kapitän "+GetFullName(pchar)+". Irgendwelche Neuigkeiten?","Also, Kapitän, haben Sie das Lösegeld schon übergeben?","Hallo, ich hoffe, Sie kommen mit guten Nachrichten?");
					link.l1 = "Ja. Ihr Antrag wurde erfüllt, "+pchar.GenQuest.CaptainComission.SlaveName+" ist an Bord meines Schiffes und bereitet sich darauf vor, an Land zu gehen.";
					link.l1.go = "CaptainComission_30";
				}
				else
				{
					dialog.text = LinkRandPhrase("Oh, freut mich, dich zu begrüßen, Kapitän "+GetFullName(pchar)+". Gibt es gute Nachrichten?","Also, Kapitän, haben Sie unseren leidenden Freund gerettet?","Schön dich lebendig und munter zu sehen, Kapitän. Wie steht es um unsere gemeinsame Angelegenheit?");	
					link.l1 = "Ich habe den Mann gebracht, über den wir gesprochen haben. Er ist an Bord meines Schiffes.";
					link.l1.go = "CaptainComission_32";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "SlaveDied")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Hallo, Kapitän "+GetFullName(pchar)+". Gibt es Neuigkeiten?","Also, Kapitän, haben Sie das Lösegeld bereits geliefert?","Hallo, ich hoffe, du bist mit guten Nachrichten gekommen?");
					link.l1 = "Grüße, "+pchar.GenQuest.CaptainComission.Name+", Ich muss dich enttäuschen.";
					link.l1.go = "CaptainComission_50";
				}
				else
				{
					dialog.text = LinkRandPhrase("Oh, freut mich, dich zu begrüßen, Kapitän "+GetFullName(pchar)+". Gute Nachrichten?","So, Kapitän, hast du unseren leidenden Freund gerettet?","Schön dich lebendig und munter zu sehen, Kapitän. Wie steht es um unsere gemeinsame Angelegenheit?");
					link.l1 = "Der Mann, für den du eingetreten bist, ist tot.";
					link.l1.go = "CaptainComission_60";
				}
			}
		break;
		
		case "CaptainComission_30":
			dialog.text = "Danke, Kapitän, Sie haben unserer Familie einen großen Gefallen getan. Hier ist Ihre Belohnung... Es sind drei Kisten - das entspricht genau 40 000 Pesos. Bitte entschuldigen Sie mich, ich muss ihn jetzt sehen.";
			link.l1 = "Natürlich, habt ein herzliches Treffen und viel Glück euch beiden.";
			link.l1.go = "CaptainComission_30_1";
			if(CheckAttribute(pchar, "GenQuest.CaptainComission.SlaveAddMoney"))
			{
				link.l2 = "Ich verstehe Ihre Ungeduld vollkommen, aber es gab unvorhergesehene Umstände, die mich zwangen, zusätzliche Kosten zu tragen.";
				link.l2.go = "CaptainComission_31";
			}	
		break;
		
		case "CaptainComission_30_1":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 3);
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("CaptainComission1", "14");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_31":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 2);
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ich verstehe nicht... Wir haben uns doch bereits auf die Summe Ihrer Zahlung geeinigt, oder nicht?";
			link.l1 = "Wir haben, aber anstatt 150000 Pesos musste ich 200000 zahlen, ganz zu schweigen von der Reise nach Barbados.";
			link.l1.go = "CaptainComission_31_1";
		break;
		
		case "CaptainComission_31_1":
			dialog.text = "Kapitän, dies ist nur das Ergebnis Ihrer eigenen Trägheit. Piraten haben bei mir keine zusätzlichen Forderungen gestellt. Was für ein merkwürdiger Kerl, der versucht, auf Kosten der Mühen anderer etwas zu gewinnen?";
			link.l1 = "Also gut, ich sehe, dass es zwecklos ist, dir etwas zu erklären...";
			link.l1.go = "CaptainComission_31_1End";
		break;
		
		case "CaptainComission_31_1End":
			AddQuestRecord("CaptainComission1", "15");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;

		case "CaptainComission_32":
			dialog.text = "Ausgezeichnet! Und du hattest deine Zweifel, dass wir gut zusammenarbeiten würden.";
			link.l1 = "Aber ich musste viel für diese Angelegenheit ausgeben.";
			link.l1.go = "CaptainComission_32_1";
		break;
		
		case "CaptainComission_32_1":
			GetSlaveSpeciality();
			dialog.text = "Ich weiß, ich weiß... Aber daran bist auch du schuld. Wie konntest du drei Kisten mit Gold versenken, die wir buchstäblich aus der Schatzkammer schütteln mussten, so dass "+NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation))+" könnte so einen Spezialisten haben "+pchar.GenQuest.CaptainComission.SlaveSpeciality+"?";
			link.l1 = "Wissen Sie, dass ich ihn Ihnen nicht ohne angemessene Entschädigung geben werde.";
			link.l1.go = "CaptainComission_32_2";
		break;
		
		case "CaptainComission_32_2":
			dialog.text = "Nun, du bist ein kluger Mann, sicherlich verstehst du, dass es zu spät zum Handeln ist. Wir hätten dein Schiff mit seiner Ladung festnehmen können.\nAber die Entschädigung wurde bereits zuvor geleistet. Daher, die Regierung von "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+" gratuliert Ihnen zu einer erfolgreichen Operation und überreicht Ihnen dieses wertvolle Geschenk und eine bescheidene Belohnung.";
			link.l1 = "Hmm... Nun, immer noch besser als nichts. Nimm deinen wertvollen Spezialisten.";
			link.l1.go = "CaptainComission_32_2End";
		break;
		
		case "CaptainComission_32_2End":
			AddQuestRecord("CaptainComission1", "16");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSpeciality", pchar.GenQuest.CaptainComission.SlaveSpeciality);
			AddQuestUserData("CaptainComission1", "sNation", NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)));
			CloseQuestHeader("CaptainComission1");			
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 15);			
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Item); 
			TakeNItems(pchar, "jewelry5", 100);
			PlaySound("interface\important_item.wav");
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_1":
			dialog.text = "Oh, was für ein Pech! Ich habe schon zu viel Zeit verloren. Du hast mich wirklich runtergezogen, Kapitän!";
			link.l1 = "Ich verstehe, aber die Umstände konnten nicht überwunden werden. Hier ist Ihr Geld.";
			link.l1.go = "CaptainComission_7_1End";
		break;
		
		case "CaptainComission_7_1End":
			AddQuestRecord("CaptainComission1", "8");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			rChar = characterFromId("CapComission_1");
			rChar.lifeDay = 0; 
			pchar.quest.CaptainComission1_30DaysIsLeft.over = "yes";
			addMoneyToCharacter(pchar, -150000);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_2":
			dialog.text = "Könnten Sie bitte sich beeilen? Ich befürchte, dass die Piraten die Bedingungen des Geschäfts erneut ändern werden.";
			link.l1 = "Mach dir keine Sorgen, wir werden es schaffen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_3":
			dialog.text = "Ich hoffe, du weißt, dass du gegen die Uhr arbeitest?";
			link.l1 = "Noch einmal! Ich bin dran. Hab Geduld.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_4":
			dialog.text = "Gott bewahre uns! Kein Druck, einfach eine Hilfe vom bescheidenen Puritaner\nEs ist deine eigene Schuld. Du hast den Kapitän getötet "+pchar.GenQuest.CaptainComission.CapName+", verloren unser Gold und scheiterten bei der Lösegeldzahlung für einen sehr wertvollen Mann. Es ist jetzt ein Schmerz im Hintern und deine Verantwortung. Denk nicht einmal daran, dass du vergeben bist... Du wirst für alles bezahlen.";
			link.l1 = "Verpiss dich!";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		// диалоги с управляющим на плантации
		case "CaptainComission_10":
			dialog.text = "Hallo, wolltest du etwas?";
			link.l1 = "Darf ich den Besitzer dieser Plantage sehen?";
			link.l1.go = "CaptainComission_10_1";
		break;
		
		case "CaptainComission_10_1":
			dialog.text = "Er ist nicht hier, er sucht nach einem entlaufenen Sklaven, Klinge, oder Blut, ich erinnere mich nicht... Und ich bin der örtliche Verwalter "+npchar.name+" und ich bin befugt, alle Angelegenheiten zu regeln, während der Chef im Urlaub ist.";
			link.l1 = "Bist du das? Das ist gut... Und sind Sklavenverkäufe auch deine Angelegenheiten?";
			link.l1.go = "CaptainComission_10_2";
		break;
		
		case "CaptainComission_10_2":
			dialog.text = "Natürlich. Wie viele wollen Sie kaufen?";
			link.l1 = "Nur einer.";
			link.l1.go = "CaptainComission_10_3";
		break;
		
		case "CaptainComission_10_3":
			dialog.text = "Ehh... Bist du sicher, dass du nur einen Sklaven brauchst?";
			link.l1 = "Natürlich bin ich das. Sein Name ist "+pchar.GenQuest.CaptainComission.SlaveName+".";
			link.l1.go = "CaptainComission_10_4";
		break;
		
		case "CaptainComission_10_4":
			if(rand(1) == 0)
			{
				dialog.text = "Aber sicherlich ist Ihnen bewusst, dass der Preis für einen Sklaven höher sein wird im Vergleich zum Preis eines Sklaven in einer größeren Menge?";
				link.l1 = "Natürlich tue ich das. Kannst du den Preis nennen?";
				link.l1.go = "CaptainComission_11";
			}
			else
			{
				if(rand(100) < makeint(sti(pchar.rank) + 0.75 * GetSummonSkillFromName(pchar, SKILL_FORTUNE)))
				{
					dialog.text = "Hmm... Ich hoffe, du weißt, für wen du eintrittst?";
					link.l1 = "Was meinst du?";
					link.l1.go = "CaptainComission_12";
				}
				else
				{
					dialog.text = "Oh, dieser Nichtstuer. Ich würde keinen Kupferpfennig für ihn geben. Seit der Zeit, als er hierher gebracht wurde, hat er nie wirklich gearbeitet. Ich habe keine Ahnung, warum der Oberst Geld für diese Staatsverbrecher verschwenden würde. Jetzt sind die schwarzen Kerle eine andere Geschichte. Sie sind großartige Arbeiter, es liegt in ihrem Blut, stark und gefügig zu sein. Und glaub mir, sie können absolut jede Arbeit erledigen. Zuckerrohrernte oder als Steward dienen - sie werden es auf bestmögliche Weise tun, gib ihnen nur ein bisschen 'Überzeugung'...";
					link.l1 = "Mein Freund, deine schwarzen Kerle interessieren mich nicht. Ich interessiere mich nur für diesen Taugenichts, von dem du gesprochen hast, er wird sowieso nicht lange leben, ich brauche ihn als Kanonenfutter und ich werde mehr für ihn bezahlen.";
					link.l1.go = "CaptainComission_13";
				}
			}
		break;
		
		case "CaptainComission_11":
			dialog.text = "Sicher, sicher. Lass mich die Preise sehen\nOh!!! 150000 Pesos.";
			link.l1 = "Wahnsinn...";
			link.l1.go = "CaptainComission_11_1";
		break;
		
		case "CaptainComission_11_1":
			dialog.text = "Der Preis sollte in der Preisliste stehen. Hier. Weißt du, ich verstehe es nicht ganz. Andere Sklaven werden zu angemessenen Preisen verkauft, aber dieser wird für ein Vermögen verkauft...";
			if(sti(pchar.money) >= 150000)
			{
				link.l1 = "Ich glaube, ich verstehe, was hier los ist... Also gut, hier ist das Geld, und ich nehme ihn mit mir.";
				link.l1.go = "CaptainComission_14";
			}	
			link.l2 = "Hmm... Aber ich will keine Geisel auslösen, ich will einen gewöhnlichen Sklaven kaufen. Glaubst du nicht, dass man für eine solche Summe ein ordentlich ausgerüstetes Schiff kaufen könnte?";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_12":
			dialog.text = "Das ist kein gewöhnlicher Sklave. Colonel Bishop hat sogar befohlen, ihn zu bewachen.";
			link.l1 = "Also kann ich ihn nicht einmal kaufen?";
			link.l1.go = "CaptainComission_12_1";
		break;
		
		case "CaptainComission_12_1":
			dialog.text = "Warum, Sie können sicherlich. Der Oberst hat einen Preis für ihn festgelegt - 200000 Pesos, laut Preisliste.";
			if(sti(pchar.money) >= 200000)
			{
				link.l1 = "Wow! Nun, sicherlich muss dieser Oberst wissen, welche Art von Person dieser Sklave ist...";
				link.l1.go = "CaptainComission_16";
			}	
			link.l2 = "Hmm... Aber ich erpresse kein Lösegeld für eine Geisel, ich möchte einen gewöhnlichen Sklaven kaufen. Glaubst du nicht, dass man für eine solche Summe ein anständiges, voll ausgerüstetes Schiff kaufen könnte?";
			link.l2.go = "CaptainComission_15";	
		break;
		
		case "CaptainComission_13":
			dialog.text = "Ach, ja. Entschuldigen Sie mich. Lassen Sie mich die Preise sehen, die Bischof hinterlassen hat.\nAha, hier ist es. Nun. Oh!.. 150 000 Pesos!..";
			if(sti(pchar.money) >= 15000)
			{
				link.l1 = "Anscheinend handelt es sich um einen Fehler. Sie wissen sicherlich, dass kein Sklave so viel kosten kann. Ich nehme an, es gibt eine zusätzliche Null, und die Summe sollte 15000 Pesos betragen. Und das ist immer noch zu viel, wenn man bedenkt, dass er ein Faulenzer und ein Idiot ist.";
				link.l1.go = "CaptainComission_17";
			}	
			link.l2 = "Hmm... Aber ich löse kein Lösegeld für eine Geisel ein, ich möchte einen gewöhnlichen Sklaven kaufen. Glaubst du nicht, dass man für diese Summe ein voll ausgerüstetes Schiff kaufen könnte?";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_14":
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 150000;
			dialog.text = "Großartig! Das ist großartig! Sie werden ihn sofort hierher bringen... Ähh... Tee, vielleicht?";
			link.l1 = "Nein, danke... Grüße Oberst Bishop...";
			link.l1.go = "CaptainComission_14_1";
		break;
		
		case "CaptainComission_14_1":
			dialog.text = "Und von wem, darf ich wissen?";
			link.l1 = "Mmm... Vergiss es, mach dir keine Mühe. Auf Wiedersehen.";
			link.l1.go = "CaptainComission_14_1End";
		break;
		
		case "CaptainComission_14_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_15":
			dialog.text = "Es tut mir leid, aber ich kann nichts tun. Hier ist die Preisliste.";
			link.l1 = "Oh hör schon auf, 'Preisliste, Preisliste...' Ihr könnt ohne Bischof nicht mal das Einfachste entscheiden. Sag ihm... Ach, sag ihm gar nichts.";
			link.l1.go = "CaptainComission_15_1";
		break;
		
		case "CaptainComission_15_1":
			dialog.text = "Also, du wirst diesen Sklaven nicht kaufen.";
			link.l1 = "Nein. Auf Wiedersehen.";
			link.l1.go = "CaptainComission_15_1End";
		break;
		
		case "CaptainComission_15_1End":
			OfficersReaction("bad");
			AddQuestRecord("CaptainComission1", "30");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			NextDiag.TempNode = "CaptainComission_19";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_16":
			dialog.text = "Ich weiß nichts darüber. Ich habe nur spezifische Anweisungen zum Verkauf dieses besonderen Sklaven.";
			link.l1 = "Unsinn... Na gut, egal. Hier ist das Geld. Bring den Sklaven.";
			link.l1.go = "CaptainComission_16_1"; 
		break;
		
		case "CaptainComission_16_1":
			addMoneyToCharacter(pchar, -200000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 200000;
			dialog.text = "Natürlich. Er wird hier in einem Augenblick geliefert.";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "CaptainComission_16_1End";
		break;
		
		case "CaptainComission_16_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_17":
			dialog.text = "Hmm... Ja, vielleicht hast du recht. Muss ein Fehler sein.";
			link.l1 = "Nun, wenn wir uns über den Preis einig sind, kann ich ihn jetzt mitnehmen?";
			link.l1.go = "CaptainComission_17_1";
		break;
		
		case "CaptainComission_17_1":
			dialog.text = "Ja, natürlich. Er wird in einem Moment hierher gebracht.";
			link.l1 = "Sehr gut. Hier ist dein Geld... Auf Wiedersehen.";
			link.l1.go = "CaptainComission_17_1End";
		break;
		
		case "CaptainComission_17_1End":
			addMoneyToCharacter(pchar, -15000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 15000;
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_18":
			dialog.text = "Möchten Sie etwas Tee, Kapitän?";
			link.l1 = "Nein, danke.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_19":
			dialog.text = "Haben Sie sich entschieden, ihn zu kaufen.";
			link.l1 = "Nein. Auf Wiedersehen.";
			link.l1.go = "exit";
		break;
		
		// диалоги с рабом
		case "CaptainComission_20":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "Hallo, Kapitän. Wie kann ich Ihnen helfen? Ich kann nicht glauben, dass diese Qual endlich vorbei ist.";
				link.l1 = "Du solltest nicht mir danken, sondern deinem Verwandten "+pchar.GenQuest.CaptainComission.Name+" von "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+". Er hat das Lösegeld gesammelt.";
				link.l1.go = "CaptainComission_201";
			}
			else
			{
				dialog.text = "Hallo, Kapitän. Mir wurde gesagt, dass Sie das Lösegeld für mich bezahlt haben. Ich muss Ihnen dafür danken, obwohl ich weiß, dass Sie nur ein Kurier waren.";
				link.l1 = "Sie sehen nicht so glücklich mit Ihrer neu gewonnenen Freiheit aus. Macht Ihnen etwas Sorgen?";
				link.l1.go = "CaptainComission_202";
			}
		break;
		
		case "CaptainComission_201":
			dialog.text = "Bitte, wenn es Ihre Pläne nicht zu sehr stört, bringen Sie mich zu ihm. Ich möchte ihm persönlich danken.";
			link.l1 = "Natürlich werde ich das tun. Komm, ich bringe dich zum Schiff.";
			link.l1.go = "CaptainComission_201_1";
		break;
		
		case "CaptainComission_201_1":
			AddQuestRecord("CaptainComission1", "11");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			DialogExit();
		break;
		
		case "CaptainComission_202":
			dialog.text = "Sicherheitshalber muss ich die Namen derjenigen kennen, die dafür bezahlt haben.";
			link.l1 = "Nun, ich war derjenige, der bezahlt hat, obwohl es nicht aus freiem Willen war.";
			link.l1.go = "CaptainComission_202_1";
		break;
		
		case "CaptainComission_202_1":
			dialog.text = "Also, meine Vermutungen wurden bestätigt. Du wurdest dazu gezwungen von "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation))+"?";
			link.l1 = "Ja, das ist es "+pchar.GenQuest.CaptainComission.Name+" von "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+".";
			link.l1.go = "CaptainComission_202_2";
		break;
		
		case "CaptainComission_202_2":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta 
			if(iNation == -1) iNation = rand(NON_PIRATES);
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar, true);// лесник . откатил .  и защиту  чтоб умники не убили.
			dialog.text = "Ich verstehe. Ich habe keine Ahnung, was sie dir versprochen haben, aber hier ist der Deal: Bring mich zur Kneipe von "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.SlaveCity+"Gen")+", Ich werde dort wirklich sicher sein. Im Gegenzug werde ich einige Informationen, die ich besitze, mit Ihnen teilen.";
			link.l1 = "Das ist in Ordnung, umso mehr, als sie bisher nichts versprochen haben. Komm mit mir, ich bringe dich zu meinem Schiff.";
			link.l1.go = "CaptainComission_202_3";
			link.l2 = "Ich riskiere nicht, mir wegen einiger fragwürdigen Informationen Ärger einzuhandeln.";
			link.l2.go = "CaptainComission_203";
		break;
		
		
		
		case "CaptainComission_202_3":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			rChar = characterFromId("CapComission_1");
			ChangeCharacterAddress(rChar, "none", "");			
			rChar.lifeDay = 0; 
			AddQuestRecord("CaptainComission1", "12");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.quest.CapComission_DeliveSlave.win_condition.l1 = "location";
			pchar.quest.CapComission_DeliveSlave.win_condition.l1.location = pchar.GenQuest.CaptainComission.SlaveCity + "_tavern";
			pchar.quest.CapComission_DeliveSlave.function = "CaptainComission_DeliveSlave";
			LAi_SetActorType(NPChar);
			LAi_ActorFollow(NPChar, PChar, "OpenTheDoors", -1.0); //лесник  идем за ГГ
			DialogExit();
		break;
		
		case "CaptainComission_203":
			dialog.text = "Leider kann ich es Ihnen jetzt nicht offenbaren. Das kann Ärger für uns beide bedeuten.";
			link.l1 = "All desto mehr... Folgen Sie mir und bitte keine dummen Dinge. Betrachten Sie sich erneut unter Arrest.";
			link.l1.go = "CaptainComission_203_1";
		break;
		
		case "CaptainComission_203_1":
			AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0); //лесник - провожаем на корабль типа..
			DialogExit();
		break;
		
		case "CaptainComission_50":
			dialog.text = "Was?! Die Piraten haben das Geschäft schon wieder geändert? Aber ich kann kein weiteres Geld aus dem Geschäft nehmen! So werde ich bald bankrott sein!";
			link.l1 = "Nein... Dein Verwandter ist auf den Plantagen von Barbados bei einem missglückten Fluchtversuch ums Leben gekommen.";
			link.l1.go = "CaptainComission_51";
		break;
		
		case "CaptainComission_51":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			dialog.text = "Oh... Ich bin total am Boden zerstört... Wie ist das passiert?";
			link.l1 = "Die Piraten hatten nicht auf das Lösegeld gewartet und ihn in die Sklaverei verkauft. Ich ging für ihn nach Barbados, aber es gelang mir nicht, ihn zu retten...";
			link.l1.go = "CaptainComission_52";
		break;
		
		case "CaptainComission_52":
			dialog.text = "Verdammt! Was ist hier los?\nGut, Kapitän, danke für Ihre Teilnahme. Und bitte, geben Sie das Geld zurück, das ich Ihnen gegeben habe.";
			link.l1 = "Meine Ausgaben überstiegen alle Erwartungen, also werde ich dein Geld behalten... Lebewohl.";
			link.l1.go = "CaptainComission_53";
			if(sti(pchar.money) >= 150000)
			{
				link.l2 = "Sicher, nimm es... Entschuldigung, dass ich dir nicht helfen konnte... Lebewohl.";
				link.l2.go = "CaptainComission_54";
			}
		break;
		
		case "CaptainComission_53":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			OfficersReaction("bad");			
			AddQuestRecord("CaptainComission1", "22");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_54":
			OfficersReaction("good");
			addMoneyToCharacter(pchar, -150000);
			AddQuestRecord("CaptainComission1", "23");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_60":
			dialog.text = "Das ist zu schade. Sie haben keine Ahnung, wie schlimm es wirklich ist...";
			link.l1 = "Es gibt nichts, was ich dagegen tun kann. Ich bin sogar froh, dass alles so passiert ist. Lebewohl.";
			link.l1.go = "CaptainComission_61";
		break;
		
		case "CaptainComission_61":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -15);
			AddQuestRecord("CaptainComission1", "32");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");			
			DialogExit();
		break;
		
		// диалог с рабом в колодках
		case "CaptainComission_70":
			dialog.text = "Trinken... Kapitän, bringt etwas Wasser...";
			link.l1 = "He, Kumpel, bist du nicht "+pchar.GenQuest.CaptainComission.SlaveName+"?";
			link.l1.go = "CaptainComission_71";
		break;
		
		case "CaptainComission_71":
			dialog.text = "Ja... Das bin ich...";
			link.l1 = "Hör zu! Wenn du nicht hier krepiert werden willst, wie ein Plattfisch auf einem Sandbank, sammle dich und hör mir zu. Weißt du, wo der Leuchtturm von Barbados liegt?";
			link.l1.go = "CaptainComission_72";
		break;
		
		case "CaptainComission_72":
			dialog.text = "Ich tue...";
			link.l1 = "Sobald du die Chance hast, renne dorthin. Ich werde versuchen, eine solche Chance für dich zu arrangieren.";
			link.l1.go = "CaptainComission_73";			
		break;
		
		case "CaptainComission_73":	
			LAi_SetPlayerType(pchar); 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);			
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			for(i = 0; i < 3; i++)
			{
				if (GetCharacterIndex("SlaveGuard_" + i) == -1) continue;
				sld = CharacterFromID("SlaveGuard_" + i);			
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SlaveGuards");
			}
						
			LAi_group_SetRelation("SlaveGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetRelation("SlaveGuards", sTemp, LAI_GROUP_NEITRAL);			
			LAi_group_SetAlarmReaction("SlaveGuards", sTemp, LAI_GROUP_NEITRAL, LAI_GROUP_FRIEND);
			LAi_group_FightGroups("SlaveGuards", LAI_GROUP_PLAYER, true);
			LAi_group_SetAlarm("SlaveGuards", LAI_GROUP_PLAYER, 0);
			LAi_group_SetCheck("SlaveGuards", "OpenTheDoors");
			LAi_group_SetCheckFunction("SlaveGuards", "CaptainComission_GuardsAfter");
			
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		// диалог охранников раба
		case "CaptainComission_80":
			dialog.text = RandPhraseSimple("Gehen Sie voran und fragen Sie, Kapitän, aber seien Sie schnell, ich bin im Dienst.","Sprechen Sie, aber machen Sie es schnell und belästigen Sie mich nicht mit Kleinigkeiten.");
			link.l1 = RandPhraseSimple("Können Sie mir sagen, wie ich einen bestimmten Sklaven finden kann? Sein Name ist "+pchar.GenQuest.CaptainComission.SlaveName+".","Irgendwo auf dieser Plantage sollte es einen Sklaven namens geben "+pchar.GenQuest.CaptainComission.SlaveName+". Könntest du mir sagen, wie ich mit ihm reden könnte?");
			link.l1.go = "CaptainComission_81";			
		break;
		
		case "CaptainComission_81":
			dialog.text = "Heute wird er bestraft und ist unter Bewachung.";
			link.l1 = "Danke.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_80";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_85":
			dialog.text = "Danke... Kapitän, Sie haben mein Leben gerettet...";
			link.l1 = "Lauf zum Leuchtturm von Barbados und warte dort auf mich.";
			link.l1.go = "CaptainComission_86";
		break;
		
		case "CaptainComission_86":
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			LAi_group_AttackGroup(sTemp, LAI_GROUP_PLAYER);
			DialogExit();
		break;
		
		case "CaptainComission_90":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "Kapitän, wie kann ich Ihnen danken? Ich kann immer noch nicht glauben, dass diese Qual endlich vorbei ist.";
				link.l1 = "Ich wurde bereits von deinem Verwandten gedankt "+pchar.GenQuest.CaptainComission.Name+" von "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+". Ich handle nach seinen Anweisungen.";
				link.l1.go = "CaptainComission_91";
			}
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
			{
				dialog.text = "Danke, Kapitän. Ich weiß nicht, in wessen Auftrag Sie handeln, aber selbst eine schlechte Freiheit ist besser als eine gute Sklaverei.";
				link.l1 = "Was meinst du?";
				link.l1.go = "CaptainComission_92";
			}
		break;
		
		case "CaptainComission_91":
			dialog.text = "Wenn es Ihre Pläne nicht zu sehr stört, bringen Sie mich bitte zu ihm. Ich bin einfach zu müde von alldem.";
			link.l1 = "Natürlich werde ich... wenn wir es schaffen, hier lebend rauszukommen.";
			link.l1.go = "CaptainComission_91End";
		break;
		
		case "CaptainComission_91End":
			pchar.GenQuest.CaptainComission = "toOurTavern";
			rChar = CharacterFromID("CapComission_Slave");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_92":
			dialog.text = "Und darf ich die Namen der Leute erfahren, die für meine Freiheit bezahlt haben?";
			link.l1 = "Nun, tatsächlich wurde ich nicht bezahlt. Sie haben mir keine Wahl gelassen.";
			link.l1.go = "CaptainComission_93";
		break;
		
		case "CaptainComission_93":
			dialog.text = "Also, meine Vermutungen wurden bestätigt. Du wurdest dazu gezwungen von "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation))+"?";
			link.l1 = "Ja, es ist "+pchar.GenQuest.CaptainComission.Name+" von "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+".";
			link.l1.go = "CaptainComission_94";
		break;		
		
		case "CaptainComission_94":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta
			if(iNation == -1) iNation = rand(NON_PIRATES);
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar, true);// лесник . откатил .  и защиту  чтоб умники не убили.
			dialog.text = "Ich habe keine Ahnung, was sie dir versprochen haben, aber hier ist der Deal: Bring mich zur Taverne von "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.SlaveCity+"Gen")+", Ich werde dort wirklich sicher sein. Im Gegenzug teile ich einige Informationen, die ich besitze, mit dir.";
			link.l1 = "Das ist gut, umso mehr, da sie bisher nichts versprochen haben. Komm mit mir, ich bringe dich zu meinem Schiff.";
			link.l1.go = "CaptainComission_95";
			link.l2 = "Ich riskiere nicht, mir wegen einiger fragwürdiger Informationen Ärger einzuhandeln.";
			link.l2.go = "CaptainComission_96";
		break;	
		
		case "CaptainComission_95":
		AddQuestRecord("CaptainComission1", "12"); // поставил запись в СЖ лесник
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.GenQuest.CaptainComission = "toEnemyTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_96":
			dialog.text = "Leider kann ich es Ihnen momentan nicht offenbaren. Dies könnte für uns beide Ärger bedeuten.";
			link.l1 = "All das mehr so... Folge mir und bitte keine dummen Dinge. Betrachte dich erneut als verhaftet.";
			link.l1.go = "CaptainComission_97";
		break;
		
		case "CaptainComission_97":	
            AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);		
			pchar.GenQuest.CaptainComission = "toTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_100":		
			dialog.text = "Danke, Kapitän. Jetzt bin ich endlich sicher. Ich biete Ihnen kein Geld an, denn ich bin sicher, dass Wissen und seine geschickte Anwendung viel mehr wert sind als vergängliches Metall.";
			link.l1 = "Ich warte auf die Information";
			link.l1.go = "CaptainComission_101";
		break;
		
		case "CaptainComission_101":
			GetSlaveSpeciality();
			dialog.text = "Die Sache ist, dass ich Wissenschaftler bin, Spezialist für "+pchar.GenQuest.CaptainComission.SlaveSpeciality+" und "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.EnemyNation))+" bot mir schon seit geraumer Zeit seine Zusammenarbeit an,"+"aber ich bin ein Militäringenieur und ich halte meine Eidespflichten ein. Sie haben versucht, mich zu stehlen, obwohl die wirklichen Probleme begannen, als Piraten meine wahre Identität und Bedeutung erkannten\n"+"Am Ende haben sie es geschafft, mich zu fangen, doch das Gold war das Einzige, was sie wollten, sie brauchten mein Wissen nicht. Meine Freunde und Feinde haben es nicht geschafft, mich rechtzeitig auszulösen und ich wurde an Plantagen verkauft. Den Rest kennst du.";
			link.l1 = "Ja, Wehe dem Verstand, wie man so sagt, in der Tat.";	
			link.l1.go = "CaptainComission_102";
		break;
		
		case "CaptainComission_102":
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					sTemp = "protecting your ship and its crew during combat.";
				break;	
				case 1:
					sTemp = "quickly reloading your cannons and firing aimed shot under conditions of dusting. ";
				break;					
				case 2:
					sTemp = "quickly managing the sails and maneuvering in combat.";
				break;					
			}
			dialog.text = "Nun, das könnte man sagen. Also, wenn du darauf achtest, was ich dir erzählen kann, wirst du viel geschickter in der Fähigkeit von "+sTemp;
			link.l1 = "Danke, diese Information ist wirklich sehr nützlich.";
			link.l1.go = "CaptainComission_103";
		break;
		
		case "CaptainComission_103":
			dialog.text = "Nun, Lebewohl und danke für alles.";
			link.l1 = "Danke auch dir. Lebewohl, und versuche beim nächsten Mal nicht erwischt zu werden.";
			link.l1.go = "CaptainComission_104";
		break;
		
		case "CaptainComission_104":
			AddQuestRecord("CaptainComission1", "21");
			CloseQuestHeader("CaptainComission1");
			// а теперь раздача слонов !!!!!!!
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					if(hrand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_DEFENCE, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_REPAIR, 10);
					}					
				break;
				case 1:
					if(hrand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_CANNONS, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_ACCURACY, 10);
					}	
				break;
				case 2:
					AddCharacterSkill(pchar, SKILL_SAILING, 10);
				break;
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "","OpenTheDoors", -1.0);
			NPChar.lifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		// Генератор "Captain's request"
		
		// Генератор "Operation 'Galleon'"
		case "CaptainComission_300":
			ReOpenQuestHeader("CaptainComission2");
			AddQuestRecord("CaptainComission2", "1");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //ПРАВКА
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCapName",  pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Voc")); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipTypeNom", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))));
			AddQuestUserData("CaptainComission2", "sCity2", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen"));
			AddQuestUserData("CaptainComission2", "sCity11", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));			
			SetFunctionLocationCondition("CaptainComission_GenerateQuestContinuation", GetArealByCityName(pchar.GenQuest.CaptainComission.City), false);
			SetFunctionTimerCondition("CaptainComission_TimeIsOver", 0, 0, 15, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission");
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();			
		break;
		
		// диалог с кэпом на палубе 
		case "CaptainComission_301":
		    if (!CheckAttribute(pchar,"GenQuest.pizdezh_uze_bil")) // проверка если разговор уже состоялся . чтобы не повторяться. лесник
			{
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			dialog.text = RandPhraseSimple("Ahoi, ich bin Kapitän "+GetFullName(NPChar)+", was hat dich auf das Deck meines Schiffes gebracht '"+pchar.GenQuest.CaptainComission.ShipTypeName+"'?","Ahoy, ich freue mich immer, Gäste auf meinem Schiff zu haben. Kapitän "+GetFullName(NPChar)+" zu Ihren Diensten.");
			link.l1 = "Hallo, ich bin Kapitän "+GetFullName(pchar)+", im Auftrag eines gewissen Kapitäns "+pchar.GenQuest.CaptainComission.CapName+". Er hat mich gebeten, Ihnen zu sagen, dass Sie verhaftet werden würden in "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+". Die Behörden wissen über "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Gen"))+"."; // ПРАВКА + belamour gen
			link.l1.go = "CaptainComission_302";
			break;
			}
			dialog.text = "Was zum Teufel machst du hier? Wir haben alles geregelt! Geh zurück zu deinem Schiff!";
			link.l2 = "Uhh..Ja, genau!";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_301"; // чтобы не было перехода на баг  - и т.д.  лесник 
			
		break;
		
		case "CaptainComission_302":
			dialog.text = "Ach, was für eine Schande! Lass mich nachdenken\nUnd wo ist der Kapitän "+pchar.GenQuest.CaptainComission.CapName+"?";
			link.l1 = "Er ist gestorben.";
			link.l1.go = "CaptainComission_303";
		break;
		
		case "CaptainComission_303":
			dialog.text = "Verdammt! Es wird nur noch schlimmer... Hör zu, "+GetFullName(pchar)+", Ich bin nicht bereit, solch eine Wendung der Ereignisse zu begegnen. Kapitän "+pchar.GenQuest.CaptainComission.CapName+" und wir haben uns darauf geeinigt, uns zu treffen bei "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+". Der Plan war, etwas Fracht in sein Schiff zu laden. Jetzt, wo der Kapitän tot ist, kann ich nicht in der Siedlung auftauchen\nEs scheint, dass mir nichts anderes übrig bleibt, als Sie um einen Gefallen zu bitten.";
			link.l1 = "Meine Zustimmung hängt von der Art der Hilfe ab, die du brauchst.";
			link.l1.go = "CaptainComission_304";
		break;
		
		case "CaptainComission_304":
			pchar.GenQuest.CaptainComission.ShoreLocation = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "Hilf mir mit Männern und Langbooten. Ich brauche die Fracht, um weggenommen zu werden von "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+". Du kannst den Anteil des verstorbenen Kapitäns an der Fracht behalten.";
			link.l1 = "Hmm... Anscheinend hast du mehr zugebissen, als du kauen könntest. Ich brauche mehr Informationen.";
			link.l1.go = "CaptainComission_305";
			link.l2 = "Leider bin ich nicht in der Lage, Zeit dafür zu verschwenden.";
			link.l2.go = "CaptainComission_306";
		break;
		
		case "CaptainComission_305":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "Gut, ich werde dir Details geben\n"+"Während einer meiner regelmäßigen Patrouillen traf ich auf ein Schiff unter der Flagge von "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+". Sie haben meine Befehle zur Kapitulation ignoriert."+"Als wir nach einer kurzen Verfolgungsjagd aufgeholt hatten "+sTemp+"'"+pchar.GenQuest.CaptainComission.VictimShipName+"' und so hissten sie die schwarze Flagge. Das Fort war ziemlich weit weg, also mussten wir alleine kämpfen. Sie zerstörten unsere Fockspriet, deshalb konnten wir das Entern nicht vermeiden.\n"+"Es war knapp, aber wir haben es geschafft, sie alle zu töten, dank der heiligen Maria und einer Musketiereinheit. Stell dir unsere Freude vor, als wir herausfanden, dass "+sTemp+" war gefüllt mit. "+"Wir haben entschieden, dass dies eine anständige Belohnung für unsere Wunden und den Tod unserer Kameraden ist\nEs war bereits dunkel, wir haben "+sTemp+" zum nächsten Hafen und verstecken die Ladung an Land. Dann hatten wir gesprengt "+sTemp+" und ich berichtete von dem gesunkenen Piratenschiff. Natürlich habe ich die Ladung nicht erwähnt.";
			link.l1 = "Anscheinend hat es doch jemand ausgeplaudert...";	
			link.l1.go = "CaptainComission_307";
		break;
		
		case "CaptainComission_306":
			dialog.text = "Es ist schade, Kapitän... Es ist schade, dass Sie mir nicht helfen wollen.";
			link.l1 = "Das ist nicht eine Frage meines Willens, meine Liebe. Du musst verstehen. Lebewohl.";
			link.l1.go = "CaptainComission_306End";			
		break;
		
		case "CaptainComission_306End":
			AddQuestRecord("CaptainComission2", "3");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", 1.5);			
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
		break;
		
		case "CaptainComission_307":
			dialog.text = "Ich glaube nicht, dass es meine Männer waren. Wahrscheinlich ist der Besitzer der Ladung begierig darauf, den Schmerz des Verlustes zu lindern\nSo? Kann ich auf Ihre Hilfe zählen?";
			link.l1 = "Ja, klingt gut.";
			link.l1.go = "CaptainComission_308";
			link.l2 = "Nein, mein Freund. Erstens: Ich weiß nicht, wie viel Ladung in meinen Laderaum gehen wird. Und zweitens: Es gibt keine Garantie, dass die Behörden es noch nicht gefunden und weggenommen haben, während sie eine Hinterhaltpartei an der Cache zurückgelassen haben.";
			link.l2.go = "CaptainComission_309";
		break;
		
		case "CaptainComission_308":
			dialog.text = "Lass uns treffen bei "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+" dann, gleich nach Mitternacht. Meine derzeitige Position erfordert Diskretion. Wir müssen Patrouillen vermeiden."; // belamour gen
			link.l1 = "In Ordnung, warte dort auf mich.";
			link.l1.go = "CaptainComission_313";
//			bQuestDisableMapEnter = true;
		break;
		
		case "CaptainComission_309":
			dialog.text = "Schade, aber du lässt mir keine Wahl. Ein Schiff reicht nicht aus, um die gesamte Ladung zu nehmen. Ich habe dafür mein Leben und meine Karriere riskiert. Sicherlich wird deine Crew mir gerne helfen, im Austausch für einen anständigen Anteil.";
			link.l1 = "Und was schlägst du vor?";
			link.l1.go = "CaptainComission_310";
		break;
		
		case "CaptainComission_310":
			dialog.text = "Ich werde dein Schiff nehmen und dich zurücklassen bei "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+"."; // belamour gen
			link.l1 = "Dein Erfolg scheint mir unwahrscheinlich. Ich werde zu meinem Schiff zurückkehren, selbst wenn ich deine gesamte Crew niedermetzeln muss.";
			link.l1.go = "CaptainComission_311";
			link.l2 = "Es scheint, dass ich keine Wahl habe. Nun, ich werde mich der Gewalt beugen...";
			link.l2.go = "CaptainComission_312";
		break;
		
		case "CaptainComission_311":
			pchar.GenQuest.CaptainComission.FightAfterDeck = true; //после резни на палубе - драка в море		
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "CaptainComission_FightInDeck", 3.5);
			DialogExit();
		break;
		
		case "CaptainComission_312":
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_toShore");
		break;
		
		case "CaptainComission_313": 		
			NextDiag.TempNode = "CaptainComission_314";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("CaptainComission2", "7");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreNameDat", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Dat"));
			SetFunctionTimerCondition("CaptainComission_SailToShore", 0, 0, 1, false);
		    pchar.GenQuest.pizdezh_uze_bil = "true"; // лесник временная запоминалка для диалога 
			DialogExit();			
		break;
		
		case "CaptainComission_314":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = "Kapitän, wir müssen uns beeilen. Ich fürchte, eine Patrouille könnte uns entdecken.";
			link.l1 = "In Ordnung, lass uns uns beeilen.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_315":
			dialog.text = "Kapitän, befiehl das Aussetzen aller Rettungsboote. Wir müssen mehrmals fahren, und ich fürchte, dass eine Patrouille zur Bucht kommen könnte. ";
			link.l1 = "Mach dir keine Sorgen, alles sollte in Ordnung sein. Die Boote kommen bereits an die Küste.";
			link.l1.go = "CaptainComission_316";
		break;
		
		case "CaptainComission_316":
			dialog.text = "Oh, verdammt. Jetzt haben wir Gesellschaft...";
			link.l1 = "Wahrlich, wenn du einen Dummkopf erwähnst, wird er sofort auftauchen...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.pizdezh_uze_bil"); // удаление проверки на повтор диалога лесник
			AddDialogExitQuestFunction("CaptainComission_GenerateShorePatrol");
		break;
		
		// диалог с патрулем на берегу
		case "CaptainComission_317":
			dialog.text = "Kapitän, wir suchen nach einem Kriegsverbrecher "+pchar.GenQuest.CaptainComission.Name+", der eine wertvolle Ladung vor den Behörden versteckt hat. Ihre Papiere, bitte.";
			link.l1 = "Welche Dokumente, Offizier? Wir sind an Land gegangen, um unsere Vorräte an frischem Wasser aufzufüllen.";
			link.l1.go = "CaptainComission_318";
		break;
		
		case "CaptainComission_318":
			dialog.snd = "Voice\COGU\COGU004"; 
			dialog.text = "Und hier ist er, "+pchar.GenQuest.CaptainComission.Name+" sich selbst . Übergebt eure Waffen und folgt mir, ihr beide!";
			link.l1 = "Das war wirklich schlecht getimt, Offizier...";
			link.l1.go = "CaptainComission_319";
		break;
		
		case "CaptainComission_319":
			DialogExit();
			for (i = 1; i <= sti(pchar.GenQuest.CaptainComission.SoldierQty); i++)
			{
    			sTemp = "SoldierIDX" + i;
				sld = GetCharacter(sti(pchar.GenQuest.CaptainComission.(sTemp)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			
			LAi_group_SetHearRadius("CoastalGuards", 100.0);			
		    sld = characterFromId("CapComission_1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);		
			LAi_group_SetRelation("CoastalGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("CoastalGuards", LAI_GROUP_PLAYER, true);
            LAi_SetFightMode(Pchar, true);
				
		break;
		
		case "CaptainComission_320":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие если жив.
			pchar.GenQuest.CaptainComission.GoodsQty = makeint((sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) - sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Capacity")) + rand(250)) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));	
			pchar.GenQuest.CaptainComission.GoodsQtyNorm = sti(pchar.GenQuest.CaptainComission.GoodsQty);
			dialog.text = "Wir müssen uns beeilen, bevor Verstärkungen hier eintreffen. Das Laden ist fast abgeschlossen, und dein Anteil ist "+pchar.GenQuest.CaptainComission.GoodsQty+" Einheiten von "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+".";
			link.l1 = "Ausgezeichnet. Zeit zu gehen. Schön, Geschäfte mit Ihnen zu machen.";
			link.l1.go = "CaptainComission_321";
		break;
		
		case "CaptainComission_321":		
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;
			dialog.text = "Und noch eine Bitte. Die Behörden werden uns sicherlich verfolgen, könnten Sie bitte mein Schiff eskortieren nach "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+", welches sich auf "+XI_ConvertString(GetIslandByCityName(sTemp)+"Hallo, Freund.")+"?"; // belamour gen
			link.l1 = "Nein, mein Freund, ab jetzt ist jeder Mann für sich selbst. Lebewohl...";
			link.l1.go = "CaptainComission_322";
			if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l2 = "Natürlich könnte ich das für eine gute Belohnung tun.";
				link.l2.go = "CaptainComission_323";
			}				
		break;
		
		case "CaptainComission_322":
			Group_DeleteGroup("Sea_CapComission_1"); 
			sld = characterFromId("CapComission_1");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			sld.lifeDay = 0; 	
			CaptainComission_GenerateCoastalPatrol();
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			AddQuestRecord("CaptainComission2", "10");
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;
		
		case "CaptainComission_323":
			sld = characterFromId("CapComission_1");
			Fantom_SetCharacterGoods(sld, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoFreeSpace(sld), 1);
			pchar.GenQuest.CaptainComission.ConvoyMoney = makeint((sti(pchar.rank)*100 + sti(NPChar.rank)*170 + hRand(30)*20) * 2.5);
			pchar.GenQuest.CaptainComission.iDay  = 15 + hRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "Natürlich. Für die Eskorte bin ich bereit zu zahlen  "+pchar.GenQuest.CaptainComission.ConvoyMoney+" Pesos. Aber es gibt noch eine Bedingung, es darf nicht länger als "+pchar.GenQuest.CaptainComission.iDay+" Tage. Es ist wichtig.";	
			link.l1 = "Abgemacht. Lass uns sofort aufbrechen.";
			link.l1.go = "CaptainComission_324";
			NextDiag.TempNode = "CaptainComission_325";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_324":
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха 
			sld = characterFromId("CapComission_1");
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(sld);
			LAi_ActorSetStayMode(sld);
			CharacterIntoCompanionAndGoOut(pchar, sld, "reload", sTemp, 5, false);
			SetShipRemovable(sld, false);
			SetCharacterRemovable(sld, false);
			Group_ChangeCharacter(PLAYER_GROUP, "CapComission_1");
			AddQuestRecord("CaptainComission2", "11");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));		
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.CaptainComission.ConvoyCity) + "Voc")); // belamour gen
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.ConvoyMoney);
			CaptainComission_GenerateCoastalPatrol();
			pchar.quest.CaptainComission_MapEnter.win_condition.l1 = "MapEnter";
			pchar.quest.CaptainComission_MapEnter.function = "CaptainComission_MapEnter"; 
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1 = "Character_sink";
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_CapShip_Sink.function = "CaptainComission_CapShip_Sink";
			DialogExit();
		break;
		
		case "CaptainComission_325":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = LinkRandPhrase("Kapitän, wir verschwenden Zeit. Sie könnten uns jeden Moment finden.","Kapitän, wir stehen unter Zeitdruck. Vergessen Sie nicht, dass sie mich suchen.","Kapitän, wir dürfen nicht verweilen. Mein Schiff ist zu groß, um die Aufmerksamkeit der Patrouille zu vermeiden.");
			link.l1 = LinkRandPhrase("Ja, du hast recht. Wir müssen uns beeilen.","Dann ladet euch ohne weitere Verzögerung in die Boote.","Das ist es... Sammle deine Männer. Wir gehen.");
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_326_0":
			dialog.text = "Kapitän, ich muss mit meinen Männern sprechen.";
			link.l1 = "Geh voran.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_326":
			sld = characterFromId("Blaze");
			dialog.text = "Ich grüße Sie, Kapitän "+pchar.CaptainComission.Name+". Also, hast du die gesamte Ladung gebracht? Und wo ist der Kapitän "+pchar.CaptainComission.CapName+"?";
			link.l1 = pchar.CaptainComission.CapName+" starb. Ich musste fragen "+NPCharSexPhrase(sld,"dieser Herr","diese Dame")+" um Hilfe. Ich stelle vor, das ist Kapitän "+pchar.CaptainComission.FullName+".";
			link.l1.go = "CaptainComission_327";
		break;
		
		case "CaptainComission_327":
			sld = characterFromId("Blaze");
			dialog.text = "Und "+NPCharSexPhrase(sld,"wer ist er? Ist er","wer ist sie? Ist sie")+" bewusst unserer Angelegenheiten?";
			link.l1 = "Allgemein ja. Aber es gibt ein Problem -"+NPCharSexPhrase(sld,"er ist sicher","sie ist sicher")+", dass die Hälfte der Ladung gehört zu "+NPCharSexPhrase(sld,"ihn","sie")+". Wir müssen überzeugen "+NPCharSexPhrase(sld,"ihn","sie")+", dass dies nicht genau der Fall ist.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialog");
		break;
		
		case "CaptainComission_328":
			dialog.text = "Mein Freund "+GetFullName(pchar)+", Sie haben bereits gehört, was Sie wissen mussten. Wir müssen auf Ihren Laderaum zugreifen.";
			link.l1 = "Und ihr denkt, dass meine Jungs einfach dastehen und zusehen werden, wie irgendwelche Taugenichtse ihren Laderaum leerräumen?";
			link.l1.go = "CaptainComission_329";
		break;
		
		case "CaptainComission_329":
			pchar.GenQuest.CaptainComission.GoodsSum = 2 * sti(pchar.GenQuest.CaptainComission.GoodsQtyNorm) * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost);
			dialog.text = "Du hast recht. Geld in Höhe von, sagen wir, "+pchar.GenQuest.CaptainComission.GoodsSum+" Pesos werden uns von der Notwendigkeit befreien, mit deiner Crew aneinanderzugeraten. Bedenke, dass dies die Hälfte unserer Ladung abdeckt, also ist alles fair. Wenn du damit einverstanden bist, wird niemand verletzt.";
			link.l1 = "Und was, wenn ich ablehne?";
			link.l1.go = "CaptainComission_330";
		break;
		
		case "CaptainComission_330":
			dialog.text = "In diesem Fall ist Gewalt unvermeidlich. Du wirst das erste Opfer sein und du wirst Frieden in dieser gemütlichen Bucht finden, und deine Mannschaft wird einfach nicht in der Lage sein, dir zur Hilfe zu kommen... Wie würde dir das gefallen?";
			link.l1 = "Du lässt mir keine Wahl. Nun, ich werde euch alle töten.";
			link.l1.go = "CaptainComission_331";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsSum))
			{
				link.l2 = "Ich glaube, ich habe keine Wahl. Also gut, hier ist dein Geld.";
				link.l2.go = "CaptainComission_332";
			}	
		break;
		
		case "CaptainComission_331":
			dialog.text = "Nun, das ist eine passende Entscheidung für "+GetSexPhrase("ein edler Herr","eine tapfere Dame")+".";
			link.l1 = "Hör auf zu philosophieren! Lass uns zur Sache kommen!";
			link.l1.go = "CaptainComission_334";
			CaptainComission_ChangeCaptain();
		break;
		
		case "CaptainComission_332":
			dialog.text = "Eine weise Entscheidung. Viel Glück für Sie.";
			link.l1 = "Mögest du daran ersticken...";
			link.l1.go = "CaptainComission_333";
		break;
		
		case "CaptainComission_333":
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);// лесник - разрешить снова драться после сдачи денег. но после драки кулаками не машут ..как говориться))
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsSum));
			AddQuestRecord("CaptainComission2", "17");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", UpperFirst(XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsSum);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GangExit");
		break;

		case "CaptainComission_334":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheckFunction(sGroup, "CaptainComission_GangDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;

		case "CaptainComission_340":
			dialog.text = "Kapitän "+GetFullName(pchar)+", wir sind zu spät. Ich hoffe, du verstehst, dass du jetzt nicht mehr für eine Belohnung in Frage kommst.";
			link.l1 = "Sicher mache ich das. Ich habe bereits eine gute Münze gemacht, dank dir. Lebewohl...";
			link.l1.go = "CaptainComission_341";
		break;
		
		case "CaptainComission_341":
			Group_DeleteGroup("Sea_CapComission_1");			
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			AddQuestRecord("CaptainComission2", "15");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");					
			DialogExit();
		break;
		
		case "CaptainComission_Canoneer":
			dialog.text = "Möchten Sie etwas Rum für einen alten Soldaten kaufen, der in den Schlachten für die Ehre der Krone sehr gelitten hat?";
			link.l1 = "Wirt! Schenk uns etwas Rum ein!";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_Canoneer1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("CaptainComission_TalkCanoneer");
		break;
		
		case "CaptainComission_Canoneer1":
			dialog.text = "Oh, danke dir, "+GetAddress_Form(pchar)+", sehr nett von Ihnen, einen Behinderten zu behandeln, der sein Gedächtnis völlig verloren hat...";
			link.l1 = "Vollständig, sagst du?";
			link.l1.go = "CaptainComission_Canoneer2";
		break;
		
		case "CaptainComission_Canoneer2":
			dialog.text = "Absolut, Fräulein"+GetSexPhrase("ter","s")+"Kapitän... vollständig. Ich erinnere mich an nichts außer einem Knüppel, der mir direkt auf den Kopf flog. Schau dir nur das Loch an, das er darin gemacht hat, ich vermute, all meine Erinnerungen müssen durch es hindurch gesickert sein.";
			link.l1 = "Kumpel, behalte deine jämmerlichen Geschichten für Hausfrauen. Ich habe Menschen gesehen, die einen direkten Schuss von Traubenschüssen erlitten haben, ihre Erinnerung wurde komplett weggewischt... mit ihren Köpfen... Und hier redest du über eine imaginäre Kettenschuss. Lassen Sie uns besser über den Kapitän sprechen "+pchar.GenQuest.CaptainComission.Name+". ";
			link.l1.go = "CaptainComission_Canoneer3";
		break;
		
		case "CaptainComission_Canoneer3":
			dialog.text = "Oh, nun, du weißt schon. Ich muss irgendwie meinen Lebensunterhalt verdienen. Was den Kapitän angeht "+pchar.GenQuest.CaptainComission.Name+", es bringt mir keinen Gewinn, zu schwatzen... Wenn ich für jede Frage über ihn hundert Münzen verlangen würde, hätte ich jetzt mehr Gold als der Gouverneur in einem Jahr von seinen Untertanen einnimmt... ";
			link.l1 = "Und hast du versucht, die Ladung zu verkaufen, die von diesem Kapitän versteckt wurde?";
			link.l1.go = "CaptainComission_Canoneer4";
		break;
		
		case "CaptainComission_Canoneer4":
			dialog.text = "Was? Noch ein Schnüffler? Ich sage es dir noch einmal, ich erinnere mich an keinen Kapitän "+pchar.GenQuest.CaptainComission.Name+"! Ich bin verwundet, und ich habe das Arztzeugnis, das das bestätigt! Was brauchst du noch?!";
			link.l1 = "Woah, werde nicht so aufgeregt. Du weißt... Er war zu spät. Kapitän "+pchar.GenQuest.CaptainComission.CapName+" hat mich gebeten zu sagen, dass "+pchar.GenQuest.CaptainComission.Name+" sollte sein Gesicht nicht in dieser Siedlung zeigen, die Behörden wissen über die Umstände der Zerstörung von "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Konto"))+" '"+pchar.GenQuest.CaptainComission.VictimShipName+", und er wird verhaftet werden.";
			link.l1.go = "CaptainComission_Canoneer5";
		break;
		
		case "CaptainComission_Canoneer5":
			dialog.text = "Puh. Das hättest du gleich sagen sollen und nicht um den heißen Brei herumreden. Ich war es, der den Kapitän gefragt hat "+pchar.GenQuest.CaptainComission.CapName+" um unser Schiff bei seiner Rückkehr abzufangen. "+"Es wurde direkt nach dem blutigen Kampf an den Docks verschoben. Was machte dieser verfluchte Pirat dort mit seinen Waren?! So viele Kameraden sind wegen ihm gestorben.";
			link.l1 = "Und wie hast du es geschafft zu überleben?";
			link.l1.go = "CaptainComission_Canoneer6";	
		break;
		
		case "CaptainComission_Canoneer6":
			dialog.text = "Durch einen Fehler. Um ehrlich zu sein, durch meinen eigenen verfluchten Fehler. Ich war nicht schnell genug, also hat unser Beiboot es nicht aus der Gefahrenzone geschafft. Ich war der Einzige, der gelitten hat. Wurde von einem Wrack getroffen und ins Wasser geworfen. Ich erinnere mich nicht einmal daran, wie ich das Ufer erreicht habe.";
			link.l1 = "Und wie haben Sie es geschafft, sich aus der Untersuchung herauszuwinden?";
			link.l1.go = "CaptainComission_Canoneer7";
		break;
		
		case "CaptainComission_Canoneer7":
			dialog.text = "Ich habe ihnen gesagt, dass ich während des Einsteigens kontus wurde und nichts von irgendeiner Ladung wusste. Ich tat auch so, als ob ich schwach im Kopf wäre, du weißt, ich bin gerade erst auf die Beine gekommen, kurz vor der Ankunft von "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+". Konnte mich nicht richtig bewegen, meine Koordination war im Eimer.";
			link.l1 = "He, aber wer hat das Geheimnis über die Ladung ausgeplaudert?";
			link.l1.go = "CaptainComission_Canoneer8";
		break;
		
		case "CaptainComission_Canoneer8":
			dialog.text = "Die Piraten haben dem Gouverneur einen Brief geschickt, angeblich im Namen des verletzten Kaufmanns. Sie haben beschlossen, sich für seine Hartnäckigkeit am Kapitän zu rächen. Es war seine Schuld, seine dumme Sturheit, uns in dieses Durcheinander zu führen.";
			link.l1 = "Aber wie sind Sie überhaupt auf diesen Piraten gestoßen?";
			link.l1.go = "CaptainComission_Canoneer9";
		break;
		
		case "CaptainComission_Canoneer9":
			dialog.text = "Ich weiß es nicht. Es war eine normale Patrouille und da war ein normales Schiff, das unter der Flagge von "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+". Ich habe keine Ahnung, warum der Kapitän beschlossen hat, es zu inspizieren, aber sie schenkten einem Warnschuss keine Beachtung, und als wir sie einholten, hissten sie eine 'Jolly Roger'. "+"Wir hatten keine Unterstützung von der Festung, daher war der Kampf nicht einfach. Dann der Enterpart. Ich weiß immer noch nicht, wie wir sie besiegen konnten.\n"+"Nun, und wir sahen all diese kostbare Fracht. Der Teufel selbst muss sie uns gegeben haben. Wir mussten die Ladung an Land verstecken und das eroberte Schiff in die Luft jagen. Sie war zu beschädigt.";
			link.l1 = "Hast du keine Angst, dass all deine Anstrengungen und Opfer umsonst sein könnten, wenn die Männer des Gouverneurs das Versteck entdecken?";	
			link.l1.go = "CaptainComission_Canoneer10";
		break;
		
		case "CaptainComission_Canoneer10":
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			pchar.GenQuest.CaptainComission.CanoneerCity = Colonies[iTmp].id;			
			pchar.GenQuest.CaptainComission.Sum = 20000 + 2000 * sti(pchar.rank);
			dialog.text = "Sie werden es nicht finden. Ich habe den Eingang der Höhle gut gesprengt, schließlich war ich der beste Sprengstoffexperte in der ganzen Staffel. Nur Schmuggler können meine Beute finden, sie kennen jeden Zentimeter dieses Ortes.\n"+"Schau, ich habe selbst keine Ahnung, was ich mit der Beute anfangen soll. Ich kann sie weder verkaufen noch alleine wegschaffen. Außerdem wird niemand Geschäfte mit einem gespaltenen Schädel machen. Ich will nicht an den Toden meiner Crewkameraden verdienen, aber ich kann dir den Standort des Verstecks für "+pchar.GenQuest.CaptainComission.Sum+"  Pesos, wenn du mich zu "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.CanoneerCity)+".";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				link.l1 = "Ich stimme zu. Hier ist dein Geld. Jetzt sprich.";	
				link.l1.go = "CaptainComission_Canoneer11";
			}
			else
			{
				link.l1 = "Verdammt! Gut, warte hier, ich hole das Geld.";
				link.l1.go = "CaptainComission_Canoneer12";				
			}	
			link.l2 = "Das ist zu viel, Kamerad. Außerdem habe ich kein passendes Schiff. Nun, viel Glück und auf Wiedersehen...";
			link.l2.go = "CaptainComission_Canoneer13";
		break;
		
		case "CaptainComission_Canoneer11":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.Sum));
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "Nun, gut. Treffen wir uns heute Nacht nach Mitternacht um "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+". Und stellen Sie sicher, dass Sie Platz in Ihrem Laderaum haben für "+pchar.GenQuest.CaptainComission.GoodsQty+" Stk. "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+". Es wäre schade, etwas davon wegzuwerfen..."; // belamour gen
			link.l1 = "Ich kümmere mich darum. Wir sehen uns in der Bucht...";
			link.l1.go = "CaptainComission_Canoneer14";
		break;
		
		case "CaptainComission_Canoneer12":
			AddQuestRecord("CaptainComission2", "41");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //Gen лесник
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.Sum);
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			SetFunctionTimerCondition("CaptainComission_CanoneerWaitMoney", 0, 0, 1, false);
			NextDiag.TempNode = "CaptainComission_Canoneer15";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer13":
			AddQuestRecord("CaptainComission2", "40");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(NPChar);
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer14":
			AddQuestRecord("CaptainComission2", "43");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat"));	// belamour gen
			LAi_CharacterDisableDialog(NPChar);
			SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			SetFunctionTimerCondition("CaptainComission_MeetCanoneerInShoreTimer", 0, 0, 1, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer15":
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				dialog.text = "Und da bist du endlich. Ich fing schon an, mir Sorgen zu machen. Ich dachte, du würdest mich einfach den Behörden übergeben.";
				link.l1 = "Ich bin noch nicht verrückt geworden. Hier ist dein Geld. Jetzt bist du dran.";
				pchar.quest.CaptainComission_CanoneerWaitMoney.over = "yes";// лесник . снят таймер ожилания бабла
				link.l1.go = "CaptainComission_Canoneer11";
			}	
			else
			{
				dialog.text = "Also, wo ist das Geld?";	
				link.l1 = "Verdammt! Gut, warte hier, ich hole es.";
				link.l1.go = "exit";
				NextDiag.TempNode = "CaptainComission_Canoneer15";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
		break;
		
		case "CaptainComission_350":
			dialog.text = "Kapitän, anscheinend sind wir zu spät. Die Schmuggler haben das Versteck gefunden.";
			link.l1 = "Ich werde meine Beute nicht aufgeben, selbst der Teufel wird sie mir nicht nehmen.";
			link.l1.go = "CaptainComission_351";
			link.l2 = "Ich kündige, kümmere dich selbst um deine Konkurrenten.";	
			link.l2.go = "CaptainComission_352";
		break;
		
		case "CaptainComission_351":
			DialogExit();
			AddDialogExitQuest("CaptainComission_GangDialog_1");
		break;
		
		case "CaptainComission_352":
			DialogExit();
			//SetFunctionExitFromLocationCondition("CaptainComission_NoGangDialog", pchar.location, false);
			 AddDialogExitQuestFunction("CaptainComission_NoGangDialog");   // лесник - исправлено . предыдцщий код не работал
		break;
		
		case "CaptainComission_360":
			dialog.text = "Kapitän, wir haben hier eine ernste Angelegenheit. Ich rate Ihnen, Ihr Geschwader wegzubringen, bevor unsere Schiffe ankommen.";
			link.l1 = "Meine Herren, es scheint, als würdet ihr versuchen, das zu nehmen, was euch nicht gehört.";
			link.l1.go = "CaptainComission_361";
		break;
		
		case "CaptainComission_361":
			dialog.text = "Oh, wirklich?! Hast du eine Ahnung, mit wem du sprichst?";
			link.l1 = "Ich spreche mit dir, Freund. Diese Ladung, sie hat einen rechtmäßigen Besitzer, und ich vertrete ihn.";
			link.l1.go = "CaptainComission_362";
		break;
		
		case "CaptainComission_362":
			dialog.text = "Wir werden nicht zulassen, dass du dich in unsere Angelegenheiten einmischst, selbst wenn du der Messias unseres Gottes wärst! Räum die Fahrrinne, wenn dir dein Leben lieb ist?";
			link.l1 = "Habe ich mich nicht klar ausgedrückt? Diese Fracht gehört mir und ich gehe nicht ohne sie!";
			link.l1.go = "CaptainComission_363";
		break;
		
		case "CaptainComission_363":
			dialog.text = "Zum Teufel mit dir! Wenn du es so sehr willst, dann wirst du hier darauf warten, für immer!";
			link.l1 = "Das Schicksal wird entscheiden, wer für immer hier bleiben wird.";
			link.l1.go = "CaptainComission_364";
		break;
				
		case "CaptainComission_364":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				rChar = CharacterFromID("CapComission_1");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);						
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				rChar = CharacterFromID("CapComission_Canoneer");
				//LAi_SetWarriorType(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);			
			}	
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckCaptainAfterBattle");
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckGangAfterBattle");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_365":
			dialog.text = "Kapitän, befehlen Sie Ihren Männern, sich zu beeilen, eine Patrouille kann jederzeit eintreffen. Außerdem haben die Schmuggler offensichtlich auf ihre Transporte gewartet.";
			link.l1 = "Ja, wir müssen uns beeilen... Ladet die Ladung in die Laderäume, und lasst uns hier verschwinden.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_365";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_366":
			dialog.text = "Danke, Kapitän "+GetFullName(pchar)+". Wenn es dich nicht gäbe, hätten die Schmuggler unsere Fracht bekommen, und die Leute, die dabei ihr Leben gelassen haben, wären umsonst gestorben...";
			link.l1 = "Und danke, dass du mir vertraust.";
			link.l1.go = "CaptainComission_367";
		break;
		
		case "CaptainComission_367":
			dialog.text = "Ich habe einen Talisman, hier, ich verdanke ihm mein Leben. Bitte, nimm ihn, vielleicht bringt er dir Glück. Und danke noch einmal, Freund. Mögen die Winde immer auf deiner Seite sein.";
			link.l1 = "Danke für das Geschenk, ich habe es nicht erwartet. Und du solltest besser auf deine Gesundheit achten, solange du noch Münzen in deinen Taschen hast.";
			link.l1.go = "CaptainComission_368";
		break;
		
		case "CaptainComission_368":
			LAi_SetActorType(NPChar);
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.LifeDay = 0;
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "48");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity + "Gen"));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_370":
			if(pchar.GenQuest.CaptainComission == "MayorTalkBad")
			{
				pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			}	
			dialog.text = "Scheinbar ist heute mein Besuchstag. Brauchen Sie mich?";
			link.l1 = "Wenn du Kapitän bist "+pchar.GenQuest.CaptainComission.Name+", dann ja.";
			link.l1.go = "CaptainComission_371";
		break;
		
		case "CaptainComission_371":
			dialog.text = "...ehemaliger Kapitän"+pchar.GenQuest.CaptainComission.Name+"...";
			link.l1 = "Ich bin "+GetFullName(pchar)+", und ich habe ein paar Fragen an dich.";
			link.l1.go = "CaptainComission_372";
		break;
		
		case "CaptainComission_372":
			dialog.text = "Und warum denken Sie, dass ich sie beantworten würde?";
			link.l1 = "Kapitän "+pchar.GenQuest.CaptainComission.CapName+" bat mich, Sie zu warnen, dass die Umstände der Zerstörung von "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Konto"))+" '"+pchar.GenQuest.CaptainComission.VictimShipName+" wurde den Behörden bekannt, "+"aber ich habe dein Schiff auf der Reise von "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City1+"Gen")+".";
			link.l1.go = "CaptainComission_373";	
		break;
		
		case "CaptainComission_373":
			dialog.text = "Und wo ist der Kapitän "+pchar.GenQuest.CaptainComission.CapName+"?";
			link.l1 = "Er ist gestorben.";
			link.l1.go = "CaptainComission_374";
		break;
		
		case "CaptainComission_374":
			dialog.text = "Ich sehe... Also so ist das, ja? Viele Dinge sind jetzt an ihrem Platz. Also, jemand hat ausgeplaudert, dass wir geplündert haben "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Gen"))+". "+"Früher oder später werden sie die Ladung finden und mich aufhängen. Kapitän "+pchar.GenQuest.CaptainComission.CapName+" ist tot, das bedeutet, niemand kann mir helfen\nAußer dir\n "+GetFullName(pchar)+", hol mich hier raus und es wird sich für dich lohnen.";
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "Der Gouverneur hat eine Nachricht vom Eigentümer der Ladung erhalten. Und die Zahlen darin sind ziemlich beeindruckend, wissen Sie.";
					link.l1.go = "CaptainComission_375";
				}
				else
				{
					link.l1 = "Aber sicherlich glaubst du nicht, dass ich dir mit verbundenen Augen helfen werde?";
					link.l1.go = "CaptainComission_375";
				}
			}			
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "Der Gouverneur hat eine Nachricht vom Eigentümer der Ladung erhalten. Und die Zahlen darin sind ziemlich beeindruckend, wissen Sie.";
					link.l1.go = "CaptainComission_375";				
				}
				else
				{
					link.l1 = "Es gibt Gerüchte in der Kolonie, dass du mit den Schmugglern zu tun hast...";
					link.l1.go = "CaptainComission_375";				
				}
			}
		break;
		
		case "CaptainComission_375":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "Sieht so aus, als müsste ich Ihnen die ganze Geschichte erzählen.\n"+"Während einer meiner regulären Patrouillen traf ich auf ein Schiff unter der Flagge von "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+". Sie hatten meine Befehle zur Kapitulation ignoriert. "+"Wir hatten erreicht "+sTemp+" '"+pchar.GenQuest.CaptainComission.VictimShipName+"' nach einer kurzen Verfolgungsjagd hissten sie die schwarze Flagge. Die Festung war ziemlich weit entfernt, also mussten wir alleine kämpfen. Sie zerstörten unseren Klüverbaum, deshalb konnten wir das Entern nicht vermeiden.\n"+"Es war knapp, aber wir haben es geschafft, sie alle zu töten, dank Heiliger Maria und einer Musketiereinheit. Stell dir unsere Freude vor, als wir herausfanden, dass "+sTemp+" war gefüllt mit Wertsachen. "+"Wir haben entschieden, dass dies eine anständige Belohnung für unsere Wunden und den Tod unserer Männer ist\nEs war bereits dunkel, wir haben es geschafft zu nehmen "+sTemp+" zum nächsten Hafen und verstecken die Ladung an Land. Dann haben wir verbrannt "+sTemp+" und ich berichtete von einem gesunkenen Piratenschiff. Natürlich habe ich die Fracht nicht erwähnt.";		
			link.l1 = "Ich denke, es bringt dir nichts, mich zu täuschen. Deshalb schlage ich einen Handel vor, du zeigst mir das Versteck, und ich bringe dich an jeden Ort im Archipel, den du willst.";
			link.l1.go = "CaptainComission_376";
		break;
		
		case "CaptainComission_376":
			dialog.text = "Ha-ha-ha... Nein, Kapitän, ich verlasse die Siedlung nicht ohne meinen Anteil, selbst wenn ich am Galgen hängen muss.";
			link.l1 = "In Ordnung. Du bekommst deine Hälfte.";
			link.l1.go = "CaptainComission_377";
			link.l2 = "Hmm... Weißt du, ich bin nicht bereit, meinen Kopf für dein Wohlergehen zu riskieren. Lebewohl...";
			link.l2.go = "CaptainComission_378";
		break;
		
		case "CaptainComission_377":
			dialog.text = "Jetzt redest du. Ich bin bereit\nZuerst solltest du mich an Bord deines Schiffes verstecken. Ich werde dir die Bucht zeigen, in der die Beute versteckt ist.";
			link.l1 = "Dann handeln wir schnell und koordiniert. Ich werde deine Zelle öffnen, und du folgst mir. Bleib nicht zurück und keine Fragen, bis wir aus der Festung draußen sind.";
			link.l1.go = "CaptainComission_379";
		break;
		
		case "CaptainComission_378":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			sld = CharacterFromID("CapComission_1");
			sld.LifeDay = 0;
			ChangeCharacterComplexReputation(pchar,"nobility", -5);			
			AddQuestRecord("CaptainComission2", "8");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(npchar);// лесник - запрет диалога
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_379":
			AddQuestRecord("CaptainComission2", "21");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition = "CaptainComission_PrisonFree_Death";
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_group_Register("CapComission_Prison");
			LAi_group_SetRelation("CapComission_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "CapComission_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "CapComission_Prison");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CaptainComission.PrisonFree = true;
			if(pchar.GenQuest.CaptainComission == "MayorTalkGood") 
			{
				chrDisableReloadToLocation = true;	
				sld = CharacterFromId(pchar.GenQuest.CaptainComission.City + "JailOff");	
				sld.dialog.currentnode = "CapComission_PrisonFree1";
			}	
			pchar.quest.CapComission_ExitFromPrison.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_ExitFromPrison.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_ExitFromPrison.win_condition = "CaptainComission_ExitFromPrison"; 
			DialogExit();
		break;		
		
		case "CaptainComission_380":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			pchar.quest.CaptainComission_PrisonFree_Death.over = "yes";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakCaptain");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PrisonFree");
			pchar.GenQuest.CaptainComission = "CanGetGoods";
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "Danke für die Rettung. Lass uns weitergehen zu "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Dat")+", Ich werde den Ort des Verstecks zeigen. Wir sollten uns beeilen, bevor die Wilden den Platz finden.";	// belamour gen	
			link.l1 = "Sind Sie sicher, dass wir die gesamte Ladung aufnehmen können?";
			link.l1.go = "CaptainComission_381";
		break;
		
		case "CaptainComission_381":
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "Du hast recht, stelle sicher, dass du genug Platz für "+pchar.GenQuest.CaptainComission.GoodsQty+" Stücke von "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+". Es wäre schade, solch wertvolle Beute mit so viel Blut darauf zu verlieren. Sie werden uns keine zweite Chance geben.";
			link.l1 = "Ich werde mich darum kümmern.";
			link.l1.go = "CaptainComission_382";
		break;
		
		case "CaptainComission_382":
			AddQuestRecord("CaptainComission2", "24");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			SetFunctionLocationCondition("CaptainComission_MeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false); 
			SetFunctionTimerConditionParam("CaptainComission_CapEscapeTimer", 0, 0, 1, MakeInt(24 - GetHour()), false);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false; // Откроем выход
			DeleteAttribute(pchar,"TownEscape");
			QuestOpenSeaExit();
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "CaptainComission_383":
			dialog.text = "Kapitän, wir brauchen keine Zeugen. Bitte versuchen Sie, diese Leute zu überreden, die Bucht zu verlassen.";
			link.l1 = "Gut, lass uns das tun.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialogGetGoods");
		break;
		
		case "CaptainComission_384":
			dialog.text = "Kapitän, es tut mir leid, aber dies ist nicht der beste Ort für Ihre Übungen. Dieser Dock ist bereits belegt.";
			link.l1 = "Meine Herren, ich bin nicht zum Sightseeing hier. Ich habe hier Geschäfte zu erledigen.";
			link.l1.go = "CaptainComission_385";
		break;
		
		case "CaptainComission_385":
			dialog.text = "Nun, wir fangen hier auch keine Quallen, dreht eure Schiffe um und verschwindet verdammt noch mal von hier.";
			link.l1 = "Ich will meine Zeit nicht damit verschwenden, dich zum Gehen zu überreden. Entweder du tust es freiwillig und lebst, oder du bleibst für immer hier.";
			link.l1.go = "CaptainComission_386";
		break;
		
		case "CaptainComission_386":
			dialog.text = "Ich sehe, dass du Probleme hast, meine Worte zu verstehen. Na gut, wenn's dein Begräbnis ist...";
			link.l1 = "Das ist besser!";
			link.l1.go = "CaptainComission_364";
		break;
		
		case "CaptainComission_387":
			LAi_LocationDisableOfficersGen(pchar.GenQuest.CaptainComission.ConvoyShore, false);
			pchar.GenQuest.CaptainComission.MaxGoodsQty = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods));
			if(sti(pchar.GenQuest.CaptainComission.MaxGoodsQty) > sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.MaxGoodsQty = pchar.GenQuest.CaptainComission.GoodsQty;
			dialog.text = "Wir sind hier. Der Versteck ist in einer Nische in jenem Felsen. Der Eingang ist mit Steinen blockiert. Im Versteck gibt es "+pchar.GenQuest.CaptainComission.GoodsQty+" Einheiten von "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+". Denk dran, die Hälfte gehört mir?";
			link.l1 = "Ich sicherlich. Wir haben etwas Zeit, während meine Männer Waren laden. Lassen Sie uns besprechen, wo Sie und Ihre Ladung hin müssen.";
			link.l1.go = "CaptainComission_388";
			if (!CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{	
			link.l2 = "Sehr gut. Jetzt sag mir, gibt es einen Grund für mich zu teilen?";
			link.l2.go = "CaptainComission_389";
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				link.l3 = "Kapitän "+pchar.GenQuest.CaptainComission.Name+", ich muss Ihnen etwas Unangenehmes mitteilen. Ich arbeite für den Gouverneur. Und ich beabsichtige, ihm die gesamte Fracht zu liefern, die Sie versteckt haben. Sie sollten in ein Gefängnis zurückkehren und dort auf Ihr Schicksal warten.";
				link.l3.go = "CaptainComission_389";
				link.l2 = "Sehr gut. Aber hier ist die Sache... Zuerst wollte ich dich den Behörden ausliefern, aber warum sollte ich das jetzt tun? Und warum sollte ich mit dir teilen?";
			    link.l2.go = "CaptainComission_3899"; // // лесник . отдельный диалог в случае обмана всех.
			}	
		break;
		
		case "CaptainComission_388":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;			
			pchar.GenQuest.CaptainComission.iDay  = 20 + hRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "Ich muss nach "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+", um "+XI_ConvertString(GetIslandByCityName(sTemp)+"Stimme")+" für "+pchar.GenQuest.CaptainComission.iDay+" Tage. Meine Leute dort müssen die Fracht zum Verkauf vorbereitet haben."; // belamour gen
			link.l1 = "In Ordnung. Dann ist es Zeit zu gehen.";
			link.l1.go = "CaptainComission_391";
		break;
		case "CaptainComission_3899": // лесник . отдельный диалог в случае обмана всех.
		    DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = "Richtig. Man sollte immer dem Verstand und nicht dem Herzen vertrauen. Leben und lernen. Auch wenn ich das nicht erwartet habe, bin ich immer bereit für einen Kampf. Du wirst für deinen Verrat bezahlen.";
			link.l1 = "Nun, wenn du Glück hast...";
			link.l1.go = "CaptainComission_390";
			SetFunctionTimerConditionParam("CaptainComission_NaebalGubera", 0, 0, 1, MakeInt(24 - GetHour()), false);
		break;
		
		case "CaptainComission_389":
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = "Richtig. Man sollte immer dem Verstand und nicht dem Herzen vertrauen. Leben und lernen. Obwohl ich das nicht erwartet habe, bin ich immer bereit für einen Kampf. Du wirst für deinen Verrat bezahlen.";
			link.l1 = "Ich stehe zu Eurem Dienst...";
			link.l1.go = "CaptainComission_390";
		break;
		
		
		case "CaptainComission_390":
			LAi_SetPlayerType(pchar);
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_SetImmortal(rChar, false);// лесник.  
			LAi_group_MoveCharacter(rChar, "EnemyFight");		
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors"); 			
			if(pchar.GenQuest.CaptainComission == "CapDuel")
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CaptainDiedDuel");
			}
			else
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CheckCaptainDied");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_391":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			GetCharacterPos(NPChar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			pchar.GenQuest.CaptainComission.CapGoodsQty = sti(pchar.GenQuest.CaptainComission.GoodsQty)/2;
			if(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) > sti(pchar.GenQuest.CaptainComission.MaxGoodsQty)) pchar.GenQuest.CaptainComission.CapGoodsQty = pchar.GenQuest.CaptainComission.MaxGoodsQty;
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))AddQuestRecord("CaptainComission2", "53");// лесник. выбор записи в СЖ
			else AddQuestRecord("CaptainComission2", "26");// смотря по какому пути пошел 
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.MaxGoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum1", pchar.GenQuest.CaptainComission.CapGoodsQty);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sDays", pchar.GenQuest.CaptainComission.iDay);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyIsland + "Gen")); // belamour gen
			OfficersReaction("bad");
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				ChangeCharacterComplexReputation(pchar,"nobility", -5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
			}
			CaptainComission_GenerateCoastalPatrol();
			pchar.GenQuest.CaptainComission = "GetGoodsEscape";
			SetFunctionLocationCondition("CaptainComission_CapMeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission.DeleiveCapShore");	
			DialogExit();
		break;
		
		case "CaptainComission_392":
			dialog.text = "Anscheinend waren wir zu spät... Die Kunden haben nicht gewartet, und ich habe keine Möglichkeit, die Lagerung und den Verkauf der Fracht selbst zu organisieren...";
			link.l1 = "Haben Sie diesbezüglich irgendwelche besonderen Vorschläge?";
			link.l1.go = "CaptainComission_393";
		break;
		
		case "CaptainComission_393":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Kapitän "+GetFullName(pchar)+", Ich weiß, es ist ein bisschen merkwürdig, aber... könnten Sie mir einen Geldwert für meinen Anteil geben? Ich vermute, "+pchar.GenQuest.CaptainComission.GoodsPrice+" Pesos könnten ein guter Kompromiss sein.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				link.l1 = "Ja, das ist ein fairer Preis. Es macht mir nichts aus. Hier ist dein Geld, und lebe wohl.";
				link.l1.go = "CaptainComission_394";
			}
			link.l2 = "Oh, nein, mein Freund, das wird nicht funktionieren. Ich kann nicht ewig dein Babysitter sein. Wenn du deine Ladung nicht abholen willst, behalte ich sie einfach. Sei versichert, ich finde Wege, sie zu lagern und schließlich zu verkaufen.";
			link.l2.go = "CaptainComission_3951";
		break;
		
		case "CaptainComission_394":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			dialog.text = "Halt an, Kapitän. Ich möchte dir für meine Rettung danken. Weißt du, ich hatte fast die Hoffnung verloren... Hier, ich bin sicher, du wirst diesen Krimskrams in vielen schwierigen Situationen ziemlich nützlich finden... Lebe wohl jetzt.";
			link.l1 = "Danke. Ich habe nicht erwartet. Es war ein Vergnügen, mit Ihnen Geschäfte zu machen.";
			link.l1.go = "CaptainComission_395";
		break;
		
		case "CaptainComission_3951": // лесник . верное назначение диалога
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes";
			dialog.text = "Ich hätte das nicht von dir erwartet... Anscheinend habe ich keine andere Wahl, als dich zu einem Duell herauszufordern.";
			link.l1 = "Ich stehe zu Euren Diensten...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
		break;
		
		case "CaptainComission_395":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "32");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");	
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_396_0":
			dialog.text = "Kapitän, ich muss mit meinen Männern sprechen.";
			link.l1 = "Geh voran.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_396":
			sld = characterFromId("Blaze");
			dialog.text = "Ich grüße Sie, Kapitän "+GetFullName(pchar)+". Also, hast du die gesamte Ladung gebracht? Und wo ist der Kapitän "+pchar.CaptainComission.CapName+"?";
			link.l1 = pchar.CaptainComission.CapName+" starb, und ich wurde aufgrund einer Denunziation verhaftet. Und wenn Kapitän "+pchar.CaptainComission.FullName+" hättest du mir nicht geholfen, hättest du weder mich noch die Fracht gesehen.";
			link.l1.go = "CaptainComission_397";
		break;
		
		case "CaptainComission_397":
			sld = characterFromId("Blaze");
			dialog.text = "Und "+NPCharSexPhrase(sld,"wer ist er? Ist er","wer ist sie? Ist sie")+" sind Sie sich unserer Angelegenheiten bewusst?";
			link.l1 = "Natürlich. "+NPCharSexPhrase(sld,"Er hat extrahiert","Sie hat extrahiert")+" me from the jail and undertook to deliver half of the cargo here; the other half I promised "+ NPCharSexPhrase(sld, "him","her") +" as a compensation.";
			link.l1.go = "CaptainComission_398";
		break;
		
		case "CaptainComission_398":
			sld = characterFromId("Blaze");
			dialog.text = "Eh, Kapitän, auf keinen Fall. Das sind deine Probleme! Ich schlug vor, dass wir das Schiff wegnehmen, aber du hast dich zu sehr um deine verfluchte Karriere gekümmert. Und hier bist du, dein geliebter Gouverneur hat dich im Gefängnis."+" Dein Anteil war viel kleiner als die Hälfte! Wir haben unsere Köpfe nicht unter Traubenkugeln gesetzt, damit du die ganze Hälfte für dich selbst stiehlst!";
			link.l1 = "Hör zu, Bootsmann, erinnerst du dich nicht daran, dass das Schiff völlig kaputt war? Dass es fast unter Wasser war? Verstehst du nicht, dass du, wenn ich diesem Mann nicht die Hälfte gegeben hätte, nie wieder auch nur ein kleines Stück der Ladung gesehen hättest?";	
			link.l1.go = "CaptainComission_399";
		break;
		
		case "CaptainComission_399":
			dialog.text = "Du wirst mich nicht täuschen! Wie könnten wir wissen, dass du nicht unter einer Decke steckst? Was, wenn es gar keine Verhaftung gab? Was, wenn du einfach zu gierig warst und beschlossen hast, unsere Habseligkeiten zu stehlen? Oder denkst du, wir haben vergessen, wie man eine Klinge führt?!";
			link.l1 = "Ich sehe, du bist verrückt geworden. Du hörst nichts anderes als das Klimpern von Münzen in deinen Ohren.";
			link.l1.go = "CaptainComission_400";
		break;
		
		case "CaptainComission_400":
			sld = characterFromId("Blaze");
			dialog.text = "Jungs! Schaut mal, wie unser Kapitän jetzt redet! Tatsächlich, die Gier hat ihn völlig verschlungen! Er hat unseren Anteil verkauft an "+NPCharSexPhrase(sld,"ein Schurke","eine Abenteurerin")+"!!";
			link.l1 = "Halt jetzt dein verdammtes Maul, oder ich bringe dich zum Schweigen!";
			link.l1.go = "exit";
			AddDialogExitQuest("CaptainComission_ShoreGangDialog");
		break;
		
		case "CaptainComission_401":
			dialog.text = "Es tut mir leid, Kapitän, dass Sie Zeuge dieser lächerlichen Szene werden mussten und sogar daran teilnehmen mussten. Es ist schwer zu glauben, dass wir vor nur einem Monat eine vereinte Crew waren und jeder von uns gerne sein Leben opfern würde, um einen Freund zu retten.";
			link.l1 = "Ich muss zugeben, ich kann mir das nicht vorstellen, nicht böse gemeint.";
			link.l1.go = "CaptainComission_402";
		break;
		
		case "CaptainComission_402":
			dialog.text = "Leider habe ich keine Möglichkeit, die Lagerung und den Verkauf der Fracht selbst zu organisieren...";
			link.l1 = "Haben Sie diesbezüglich bestimmte Vorschläge?";
			link.l1.go = "CaptainComission_403";
		break;
		
		case "CaptainComission_403":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Kapitän "+GetFullName(pchar)+", Ich weiß, es ist ein bisschen unangenehm, aber... könnten Sie mir einen Geldwert für meinen Anteil geben? Ich vermute, "+pchar.GenQuest.CaptainComission.GoodsPrice+" Pesos könnten ein guter Kompromiss sein.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				pchar.quest.CaptainComission_Capitan_Cdox.over = "yes"; // на всякий случай .лесник
				pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник
				link.l1 = "In Ordnung, es macht mir nichts aus. Hier ist dein Geld und auf Wiedersehen.";
				link.l1.go = "CaptainComission_404";
			}	
			link.l2 = "Nein, das wird nicht funktionieren. Du kannst deine Ladung nehmen oder im Laderaum lassen, aber ich werde dir keinen einzigen Taler geben.";
			link.l2.go = "CaptainComission_405";
		break;
		
		case "CaptainComission_404":
			bTemp = false;
			if(hrand(1) == 0)
			{
			    NPChar.reputation = 60 + rand(20); 
				NPChar.alignment = "good"; 
			}	
			else
			{
			    NPChar.reputation = 10 + rand(20); 
				NPChar.alignment = "bad"; 			
			}
			if (NPChar.alignment == "good" && sti(pchar.reputation.nobility) > 50) bTemp = true; 
			if (NPChar.alignment == "bad" && sti(pchar.reputation.nobility) <= 50) bTemp = true;
			
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			
			if(!bTemp || FindFreeRandomOfficer() < 0)
			{
				dialog.text = "Halt ein, Kapitän. Ich möchte dir für meine Rettung danken. Weißt du, ich hatte fast die Hoffnung verloren... Hier, ich bin sicher, du wirst dieses Kleinod in vielen schwierigen Situationen ganz nützlich finden... Lebe wohl jetzt.";
				link.l1 = "Danke. Ich habe es nicht erwartet. Es war ein Vergnügen, Geschäfte mit Ihnen zu machen.";
				link.l1.go = "CaptainComission_406";
			}
			else
			{
				dialog.text = "Warte... Ich habe gerade gedacht... Weisst du, meine Karriere ist jetzt vorbei, ich habe keine Crew und ich bin im Exil in meiner Heimat. Sicherlich brauchst du vertrauenswürdige Männer mit einer ruhigen Hand, die ihren Mund halten können. Bitte nimm mich in deine Crew auf, ich verspreche dir, dass du es nicht bereuen wirst.";
				if(!CaptainComission_CheckAllPassengersHired())
				{
					link.l1 = "Um ehrlich zu sein, habe ich schon eine Weile auf Ihre Zustimmung gewartet. Sicher. Sieh mich an Bord.";
					link.l1.go = "CaptainComission_407";
				}	
				link.l2 = "Hmm... weißt du, es scheint mir, dass du einfach zu klug bist, um unter jemandem zu dienen. Lebewohl...";
				link.l2.go = "CaptainComission_408";
			}
		break;
		
		case "CaptainComission_405":
			dialog.text = "Nun, anscheinend ist heute eindeutig nicht mein Glückstag... Also, Kapitän, ziehen wir unsere Klingen und machen wir es sofort...";
			link.l1 = "Ich stehe zu Ihren Diensten...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
			pchar.GenQuest.CaptainComission.Duel = true;
		break;
		
		case "CaptainComission_406":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "34");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
	
		
		case "CaptainComission_407":	
			AddQuestRecord("CaptainComission2", "36");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");		
			npchar.CaptainComission = true;
			SetCharacterRemovable(Npchar, true);
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
			NPChar.Dialog.CurrentNode = "hired";
            NPChar.greeting = "Gr_Officer"; 			
			NPChar.quest.OfficerPrice = sti(pchar.rank)*500;	
			NPChar.loyality = MAX_LOYALITY;
			DeleteAttribute(NPChar, "LifeDay");
			NPChar.id = "GenChar_" + NPChar.index;// лесник . смена ИД при взятии в оффы. 
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(NPChar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired"); 
			NPChar.quest.meeting = true; 
			DialogExit();
		break;		
		
		case "CaptainComission_408":
			AddQuestRecord("CaptainComission2", "35");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);						
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;		
		// Генератор "Operation 'Galleon'"
		
		// Квест "meeting in the cove" -->
		// Офицер
		case "ContraMeetManQuest_Sold_1":
			dialog.text = "Geht dich nichts an. Jetzt sag mir, was du hier schnüffelst? Suchst du nicht nach einem Mann, der gerade festgenommen wurde?!";
				link.l1 = "Ein Mann?! Nein...";
				link.l1.go = "ContraMeetManQuest_Sold_2";
			break;
			
		case "ContraMeetManQuest_Sold_2":
			dialog.text = "Gut für dich. Sonst würdest du auch ins Gefängnis kommen, zusammen mit ihm. Also mach hier keinen Ärger, Matrose. Verschwinde!";
				link.l1 = "Ja, ich sollte besser gehen...";
				link.l1.go = "ContraMeetManQuest_Sold_3";
			break;
			
		case "ContraMeetManQuest_Sold_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteQuestCondition("ContraMeetManQuest_TimeIsLeft"); // Время больше не роляет
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "8");
			PChar.GenQuest.ContraMeetMan.ToTavernPatrolInShore = true;
			LAi_CharacterDisableDialog(NPChar);
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			ContraMeetManQuest_DeletePatrolFromShore(); // По выходу потрем всех из локации
			break;
			
		// Сам чел
		case "ContraMeetManQuest_1":
			dialog.text = "Großartig! Wir sollten jetzt zur Taverne zu diesem Schmuggler gehen. Ich würde nicht gerne hier verweilen!";
				link.l1 = "Kein Problem damit. Lass uns gehen...";
				link.l1.go = "ContraMeetManQuest_2";
			break;
			
		case "ContraMeetManQuest_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(NPChar);
			LAi_ActorFollowEverywhere(NPChar, "", -1);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "3");
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			PChar.GenQuest.ContraMeetMan.ToTavernWithMan = true;
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			break;
		
		// Контрики в комнате таверны	
		case "ContraMeetManQuest_3":
			ContraMeetManQuest_ContersGoQut();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "4");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ChangeContrabandRelation(PChar, 5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_4":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "5");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContraBeatMan();
			ChangeContrabandRelation(PChar, 5);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_5":
			dialog.text = "He-he... Es scheint, "+GetSexPhrase("Kamerad","lass")+", du wirst sehr bald mit ihm zur Hölle fahren... Hey, Kumpel - lass uns beide ausnehmen!";
				link.l1 = "Du dreckiges Schwein! Verteidige dich!";
				link.l1.go = "ContraMeetManQuest_6";
			break;
			
		case "ContraMeetManQuest_6":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraMeetManQuest_PlayerBeatContra();
			break;
			
		case "ContraMeetManQuest_7":
			dialog.text = "Vielen Dank noch einmal, "+PChar.name+". Lebewohl...";
				link.l1 = "...";
				link.l1.go = "ContraMeetManQuest_9";
			break;
			
		case "ContraMeetManQuest_8":
			iMoney = (rand(3)+2)*500;
			PChar.GenQuest.ContraMeetMan.Money = iMoney;
			dialog.text = "Eine Belohnung?! Oh, sicher. Hier - nimm "+FindRussianMoneyString(iMoney)+" und Lebewohl...";
				link.l1 = "Auf Wiedersehen...";
				link.l1.go = "ContraMeetManQuest_10";
			break;
			
		case "ContraMeetManQuest_9":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "6");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoney));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_10":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "7");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
		// <-- Квест "meeting in the cove"
			
		// Квест на доставку письма контрику -->
		case "ContraDeliverQuest_Sold1":
			dialog.text = "Heh! Ihr erwartet, dass wir diesen Bullshit glauben?! Jungs, schnappt euch diese beiden Galgen-Vögel!";
			//if(80 > rand(100) || sti(PChar.skill.Fortune) > rand(100)) // Попытка отмазаться
			//{
				link.l1 = "Offizier, Sie machen einen schweren Fehler, indem Sie versuchen, zwei unschuldige Menschen festzuhalten. Glauben Sie mir, ich kenne diesen Mann nicht und er könnte mir nicht gleichgültiger sein."+" Ich bin sicher, dass Ihr Kommandant sehr unzufrieden mit Ihnen sein wird, wenn Sie zwei gesetzestreue Bürger festhalten...";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty";
			//}
			/*else // Тюрьма
			{
				link.l1 = "";
				link.l1.go = "ContraDeliverQuest_Sold2_Prison";
			}*/
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty":
			dialog.text = "Hmm... Ja, vielleicht hast du Recht. Der Kommandant wird sicherlich darüber verärgert sein. Weißt du was - lass uns einfach diesen kleinen Vorfall vergessen.";
				link.l1 = "Danke, Offizier, Sie haben uns Zeit gespart. Ich möchte Sie bitten, das nächste Mal vorsichtiger zu sein, Sie möchten sicherlich nicht degradiert werden, oder?";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty1";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty1":
			dialog.text = "Nein, auf keinen Fall. In diesem Fall bitte ich Sie, sich zu zerstreuen. Auf Wiedersehen...";
				link.l1 = "Das ist besser!";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty2";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraDeliverQuest_SoldiersGoOut();
			break;
		
		case "ContraDeliverQuest_1":
			iMoney = (rand(3)+2)*500;
			if(rand(1) == 0) // Денег не даёт
			{
				dialog.text = "Ausgezeichnet! Und jetzt kannst du verloren gehen!";
					link.l1 = "Was?! Und was ist mit dem Geld? Wir hatten einen Deal...";
					link.l1.go = "ContraDeliverQuest_NoMon";
			}
			else // Деньги или патруль
			{
				if(rand(2) == 1) // Патруль
				{
					dialog.text = "Danke für die Lieferung. Jetzt kannst du los... warte, da kommt jemand...";
						link.l1 = "Was?!";
						link.l1.go = "ContraDeliverQuest_Patrol";
				}
				else // Просто отдает деньги
				{
					dialog.text = "Großartig. Danke für die Lieferung. Hier, nimm "+FindRussianMoneyString(iMoney)". Und behalte im Kopf, dass Schmuggler immer gute Leute in Erinnerung behalten...";
					link.l1 = "Ich hoffe es doch. Lebewohl.";
					link.l1.go = "ContraDeliverQuest_GoWithMoney";
					PChar.GenQuest.ContraDeliver.Money = iMoney;
				}
			}
			
			ChangeContrabandRelation(PChar, 5); // Письмо доставили - повышаем отношение у контриков
			ChangeCharacterComplexReputation(pchar,"nobility", -5); // Помогли контрикам - репу понижаем
			RemoveItems(PChar, "letter_1", 1);
			BackItemDescribe("letter_1");
			DeleteAttribute(&Items[FindItem("letter_1")], "City");
			rChar = &Characters[GetCharacterIndex(Locations[FindLocation(PChar.location)].townsack + "_Smuggler")];
			SaveCurrentNpcQuestDateParam(rChar, "work_date");
			break;
			
		case "ContraDeliverQuest_Patrol":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_LocationFightDisable(LoadedLocation, true); // Чтоб не поубивали кого-нить
			ContraDeliverQuest_GeneratePatrolToRoom();
			break;
			
		case "ContraDeliverQuest_NoMon":
			dialog.text = "Hör zu... du und ich hatten überhaupt keinen Deal. Fordere dein Geld von demjenigen ein, der diese Vereinbarung mit dir getroffen hat.";
				link.l1 = "Nun, das ist sicherlich nicht mein Glückstag, was soll ich sonst sagen?! Also gut, wir sehen uns...";
				link.l1.go = "ContraDeliverQuest_GoWithoutMoney";
				link.l2 = RandSwear()+"Du wirst dafür bezahlen! Bereite dich auf den Tod vor!";
				link.l2.go = "ContraDeliverQuest_PrepareToFight";
			break;
			
		case "ContraDeliverQuest_GoWithoutMoney": // Уходим без денег
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			PChar.GenQuest.ContraDeliver.Complete.WithoutMoney = true;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "4");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ContraDeliver.QuestTown));
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
			
		case "ContraDeliverQuest_PrepareToFight":
			dialog.text = "Du hast es gewagt, mich herauszufordern, "+GetSexPhrase("Welp","Dreck")+"? Nun, du hast sicher keine Ahnung, was gut für dich ist. Ich werde dich ausnehmen!";
				link.l1 = "..., Freund.";
				link.l1.go = "ContraDeliverQuest_Fight";
			break;
			
		case "ContraDeliverQuest_Fight": // Бой
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetImmortal(NPChar, false);
			LAi_ActorAttack(NPChar, PChar, "");
			LAi_SetFightMode(PChar, true);
			SetFunctionNPCDeathCondition("ContraDeliverQuest_ContraIsDead", NPChar.ID, false);
			break;
			
		case "ContraDeliverQuest_GoWithMoney": // Уходим с деньгами
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraDeliver.Money));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "3");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraDeliver.Money)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ContraDeliver"); // Квест пройден - атрибуды потрем
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
		// <-- Квест на доставку письма контрику
			
		// Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем -->
		case "ChurchGenQuest_1_DeckDialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern")) // Если ждёт в таверне
				{
					dialog.text = RandPhraseSimple("Ein halbes Tausend Männer! Und eine Totenkiste! Hic!","Trink! Hicks! Und der Teufel hat für den - Hicks! - Rest gesorgt!");
						link.l1 = "Ohh... Nun. Hallo, Herr "+GetFullname(NPChar)+".";
						link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_2";
						PChar.Quest.Church_GenQuest1_Timer.over = "yes";
				}
				else // на палубе своего шипа
				{
					if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
					{
						dialog.text = "Also gut, mal sehen... Drei Stücke Segeltuch, Planken für den Schiffsrumpf, Ersetzung der Betings und Seile an den Streben...";
							link.l1 = "Hallo, Herr "+GetFullName(NPChar)+". Ich bin Kapitän "+PChar.name+".";
							link.l1.go = "ChurchGenQuest1_DialogShip_1";
					}
					else
					{
						dialog.text = LinkRandPhrase("Verlass mein Schiff sofort, ich habe viel zu tun ohne dich!","Sie haben Ihre Bücher erhalten, was wollen Sie sonst noch?!","Ich habe alles getan, was du wolltest, was willst du noch von mir?!");
							link.l1 = "Mach nicht so einen Aufstand, oder du bekommst noch einen Herzinfarkt!";
							link.l1.go = "exit";
					}					
				}
			}
			else
			{
				dialog.text = RandPhraseSimple("Rum, Rum! Gib mir Rum... Hic!","Es ist eine Weile her... hic... als ich das letzte Mal so betrunken war...");
					link.l1 = "Ja, dein Laderaum ist voll... vielleicht ist es Zeit, eine Bucht anzusteuern?";
					link.l1.go = "exit";
			}			
			NextDiag.TempNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_2":
			dialog.text = RandPhraseSimple("Bitte nehmen Sie Platz, Ka-hicks-tän! Was ist Ihr Gift?","Setz dich, Kapitän! Was möchtest du trinken? Hicks...");
					link.l1 = "Danke, aber ich würde lieber ein nettes Gespräch mit einem anständigen Mann führen.";
					link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_3";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_3":
			dialog.text = "Versuchst du - hicks! - mich zu beleidigen?.. In dieser Taverne gibt es keinen einzigen anständigen Mann! Hicks! Nur Banditen und Kehlenschneider! Alle sind sie Erpresser, und der da... der schlimmste von allen! Ihr Anführer, eine Muräne soll ihm in den Hals kriechen!";
				link.l1 = "Ich meinte dich. Du bist derjenige, mit dem ich reden möchte. Und wer ist der Banditenführer und warum würde er...";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_4";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_4":
			dialog.text = "Fehl"+GetSexPhrase("ter","s")+"! Meine Liebe! Wie war noch mal Ihr Name? Ich respektiere Sie! Niemand hat bisher einen alten Seebären einen anständigen Mann genannt! Ich würde alles für Sie tun! Ich würde Ihnen all mein Geld geben, bis zum letzten Peso!.. Ach, habe gerade vergessen. Ich habe kein Geld mehr. Ich habe nicht mal mehr Roolies. Dieser Bastard, dieser Erpresser hat mir gerade das letzte Schriftstück genommen, mögen die Kobolde in der Hölle ihre Kanonen mit seinen Eingeweiden laden!";
				link.l1 = "Herr Kapitän? Geht es Ihnen gut? Ist Ihnen bewusst, dass Sie delirieren? Welche Schriftrollen?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_5";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_5":
			dialog.text = "Nein, nein! Dieser alte Käppi mag betrunken sein, aber er behält immer noch seinen Verstand bei sich. Die Bücher und die Schriftrollen wurden mir vom Vater gegeben "+PChar.GenQuest.ChurchQuest_1.ToName+", ich brachte sie zu "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+". Und am Morgen bin ich zur örtlichen Kirche gegangen und habe dem dortigen Padre von diesen Büchern erzählt. Natürlich wollte er sie sehen, ihr wisst wie sie sind, sie sind einfach verrückt nach dem Leben ihrer Heiligen und all dem Zeug. Also schickte ich einen Kabinenjungen, um die Truhe mit ihnen zu holen. Und während ich wartete, beschloss ich ein bisschen zu zocken... und irgendwie habe ich all mein Geld verloren. Alles! Nichts, um den Schnaps zu bezahlen! Also, der Tavernenbesitzer nahm die Bücher als Pfand, und dann gab ich ihm auch noch die Schriftrollen...";
				link.l1 = "Also, du hast Bücher verkauft, die heiligen Bücher, die dir vom Priester anvertraut wurden  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Gen")+"?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_6";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_6":
			dialog.text = "Ich weiß, ich weiß... Ich werde in der Hölle für alle Ewigkeit brennen. Ich kann jetzt mein Gesicht weder dem Vater zeigen, der mir diesen Auftrag gab, noch dem, der die Papiere lieferte, noch dem Einheimischen... Wer wird jetzt für meine Seele beten? Und was ist, wenn sie mich exkommunizieren? Oh, wehe mir... Ich brauche einen Schluck... ";
				link.l1 = "Woah entspann dich, es ist nicht so schlimm. Deine Taten waren mies und gotteslästerlich, und doch bin ich bereit, dir zu helfen. Ich werde deine Schulden begleichen und diese Manuskripte kaufen. Außerdem werde ich, da ich beide genannten Priester bereits kenne, direkt zu "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+" um die Papiere dort abzuliefern. Abgemacht?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_7";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_7":
			dialog.text = "Retter! Gottes Engel... Natürlich, ich stimme zu! Ich würde dir alles geben... alles! Wenn ich nur noch einen Schluck trinken könnte...";
				link.l1 = "Ich nehme an, du hast schon genug gehabt... Ach, was auch immer. Ich kaufe dir noch etwas Rum vom Barkeeper.";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_8";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_8":
			DialogExit();
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap");
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithBarmen = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7_2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			NextDiag.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogShip_1":
			dialog.text = "...und die Segel! Wir müssen auch die Segel ersetzen!.. Oh, hallo. Bitte seien Sie nicht beleidigt, meine Dame"+GetSexPhrase("ter","s")+" was-auch-immer-dein-Name-ist, aber gerade jetzt, wie du sehen kannst, bin ich ziemlich beschäftigt, also wenn du Geschäfte mit mir hast, bitte mach schnell damit.";
				link.l1 = "Soweit ich weiß, Vater "+PChar.GenQuest.ChurchQuest_1.ToName+" hat dir einige heilige Papiere in "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Voc")+". Du hast versprochen, sie zu liefern "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+" weil du sowieso in diese Richtung gesegelt bist."; // belamour gen
				link.l1.go = "ChurchGenQuest1_DialogShip_2";
			break;
			
		case "ChurchGenQuest1_DialogShip_2":
			dialog.text = "Ich war in diese Richtung unterwegs, bis dieser verfluchte Sturm meine alte Kiste beinahe zerstört hat, und ich weiß der Teufel wie lange hier feststecke! Diese Betrüger an den Docks versuchen mir ständig morsche Planken zu unterjubeln, die die Flut angeschwemmt hat, für den Schiffsrumpf, und für die Segel, irgendeinen alten Sackstoff, auf dem ihre Großmütter geschlafen haben, als sie noch jung waren.";
				link.l1 = "Herr, das nächste Mal werde ich gerne Ihre großartigen Geschichten hören, aber jetzt würde ich gerne mehr über das Schicksal der Bücher und Manuskripte erfahren, die Sie erhalten haben bei "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Dat")+".";
				link.l1.go = "ChurchGenQuest1_DialogShip_3";
			break;
			
		case "ChurchGenQuest1_DialogShip_3":
			dialog.text = "Niemand, hörst du mich? Niemand wagt es, mich für die Verspätung bei der Lieferung dieser verfluchten Papiere zu beschuldigen!";
				link.l1 = "Oh, nein, das habe ich sicherlich nicht gemeint. Ich wollte nur deine Last erleichtern. Die Sache ist, dass "+PChar.GenQuest.ChurchQuest_1.ToName+" ist ziemlich besorgt um Bücher und Papiere, die geliefert werden sollen an "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+". Tatsächlich werde ich jetzt gleich dorthin segeln.";
				link.l1.go = "ChurchGenQuest1_DialogShip_4";
			break;
			
		case "ChurchGenQuest1_DialogShip_4":
		if(rand(3) != 1)
		{
			dialog.text = "Mir scheint, Fräulein"+GetSexPhrase("ter","s")+", dass du in jedem Hafen einen geistlichen Ratgeber hast. Obwohl das nicht meine Angelegenheit ist. Wenn dir dieser Unsinn wichtig ist, dann schnapp dir deine Bücher und verschwinde! Gott sei Dank!";
				link.l1 = "Danke, Herr Kapitän. Viel Glück bei Ihren Reparaturen.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_1";
		}
		else // Свитки не отдает
		{
			dialog.text = "Mach dir darüber keine Sorgen, Fräulein"+GetSexPhrase("ter","s")+", und reise nach "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+" leichtfertig, denn ich war es, der sich verpflichtet hat, diese Papiere zu liefern, und ich werde es sein, der dies um jeden Preis tut, damit niemand an jeder Ecke schreit, dass Kapitän "+NPChar.name+" hielt nicht sein Wort!";
				link.l1 = "Aber Herr Kapitän, der Punkt ist eigentlich...";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2";
		}
			break;
			
		case "ChurchGenQuest1_DialogShip_5_1":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2":
			dialog.text = "Eigentlich ist der Punkt, dass ich überhaupt keine Geschäfte mit dir habe. Der Heilige Vater hat mir eine Aufgabe gegeben, die Bücher zu liefern an "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+" und übergib sie dem örtlichen Priester. Und ich sehe dich dort nicht. Überhaupt nicht! Viel Glück.";
//				link.l1 = "Gut, dann. Du bist ein sehr verantwortungsbewusster Mann, obwohl es dein einziges Verdienst ist. Viel Glück, mein unhöflicher Freund";
//				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_1"; // Сваливаем, поверили ему
				link.l2 = "Ich habe genug von deinem frechen Verhalten. Dein dummer Mund könnte selbst einen Engel zur Gewalt zwingen. Ich muss den Willen meines heiligen Vaters erfüllen und ich werde meine Waffe benutzen, wenn ich muss!";
				link.l2.go = "ChurchGenQuest1_DialogShip_5_2_2"; // 
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_1":
			DialogExit();
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "11");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete.NoManuscripts = true; // Квест выполнен без манускриптов
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_2":
			dialog.text = "Ruhe, Ruhe, Kapitän "+PChar.name+"! Was ist los mit dir? Oh, gut, ich sehe, dass wenn du diese Papiere nicht bringst, all diese Heiligen Väter ziemlich wütend auf dich sein würden, ganz zu schweigen von unserem Vater im Himmel. Also, nimm deine theologischen Wertsachen und geh mit Gottes Segen.";
				link.l1 = "Froh, dass du nicht nur meine Position verstanden hast, sondern auch meinen Namen behalten hast. Ich schlage vor, du erinnerst dich daran jedes Mal, wenn du etwas Dummes tun willst.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_3"; // Сваливаем, поверили ему
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_3":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		// <-- Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем
			
		case "Left_Time_Case":
			dialog.text = RandPhraseSimple("Verschwinde...","Stör mich nicht!");
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Left_Time_Case";
			break;
			
		case "Church_GenQuest_2_1":
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 1)
			{
				dialog.text = RandSwear()+"Du hättest das nicht sagen sollen! Jetzt muss ich dich zum Herrn schicken, um für die Vergebung meiner Sünden zu beten!";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 2)
			{
				dialog.text = RandSwear()+"Du hättest das nicht sagen sollen! Jetzt muss ich dich zum Herrn schicken, um für die Vergebung unserer Sünden zu beten!";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) > 2)
			{
				dialog.text = RandSwear()+"Du hättest das nicht sagen sollen! Jetzt muss ich dich zum Herrn schicken, um für die Vergebung all unserer Sünden zu beten!";
			}
			
				link.l1 = "Kaum, Kumpel. Jeder wird vor Gott für sich selbst antworten!";
				link.l1.go = "exit";
				NPChar.money = sti(PChar.GenQuest.ChurchQuest_2.MoneyCount);
				LAi_LocationFightDisable(LoadedLocation, false);
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_1":
			dialog.text = "He, warum fluchen? Was ist, wenn ich Geschäfte mit dir habe.";
				link.l1 = "Das sind Neuigkeiten! Wissen Sie, ich führe kurze Gespräche mit Leuten wie Ihnen!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_2";
				LAi_LocationFightDisable(LoadedLocation, false);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_2":
			dialog.text = "Nun, ich werde auch keine langen Gespräche mit dir führen. Aber vielleicht wärst du daran interessiert, ein paar Krimskrams zu einem guten Preis zu kaufen?";
				link.l1 = "Sehe ich aus wie ein verdammter Hehler?!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_3":
			if(rand(1) == 0)
			{
				dialog.text = "Ruhig, ruhig, bei uns gibt es keine Diebe! Diese Vase wurde uns für ehrliche Arbeit gegeben! Schau nur... pure Gold, verziert mit Perlen. Aber der Punkt ist, dass wir sie nicht brauchen. Also wollen wir sie nur verkaufen und das Geld teilen.";
					link.l1 = "Lass mich mal genauer hinsehen... Oh mein Gott! Das ist der Abendmahlskelch!!! Also, ihr seid diese Gotteslästerer, die die Kirche geplündert haben von "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+"?! Da bist du ja!";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_4";
					break;
			}
		
			dialog.text = "Ruhe, Miss"+GetSexPhrase("ter","s")+"Heuchler! Du weißt, wir sind ein bisschen knapp bei Kasse, also haben wir beschlossen, etwas zu verkaufen. Schau dir diese Vase an... reines Gold, verziert mit Perlen. Spezialpreis für dich, sagen wir, tausend Münzen.";
				link.l1 = "Lass mich mal genauer hinsehen... Oh mein Gott! Das ist der Abendmahlskelch!!! Also, ihr seid die Gotteslästerer, die die Kirche geplündert haben von "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+"?! Da bist du ja!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_1";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_4":
			dialog.text = "Haltet eure Pferde, Fräulein"+GetSexPhrase("ter","s")+"!.. Verdammt, ich habe diesem Dummkopf gesagt, er soll keinen Ärger machen, bis die Zeit gekommen ist...";
				link.l1 = "Was faselst du da? Gut, triff deine Wahl: Entweder du gibst mir deine gestohlene Beute freiwillig, oder ich rufe die Wachen.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_5";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_5":
			dialog.text = "Hör zu, "+GetSexPhrase("guter Mann","junge Dame")+", wir brauchen keine Streitigkeiten, also lassen wir diese Angelegenheit friedlich klären. Sie müssen uns glauben, wir haben diese Kirche tatsächlich nicht geplündert, noch haben wir Geld. Ja, wir haben einige Pesos und dieses goldene Trinket für die Nachahmung des Raubüberfalls erhalten. Und dieser goldene Pokal war das einzige, was wir nach der Bezahlung der Schmuggler noch übrig hatten...";
				link.l1 = "Also, du versuchst zu sagen, dass...";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_6";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_6":
			dialog.text = "Dieser verfluchte Priester hat uns eingestellt, das sage ich! Aber warum musste er dich zu uns schicken?.. Nun, wir sind quitt. Nimm diese Vase und zeige sie diesem Heuchler, du wirst sehen, dass er sich wie ein Tintenfisch im Watt winden wird!";
				link.l1 = "Gib mir den Becher und verschwinde, bevor ich meine Meinung ändere.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_7";
				link.l2 = "Du redest geschickt, aber ich bin nicht so leicht zu täuschen. Wenn du mich überzeugen willst, dann überzeuge zuerst mein Schwert.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_8";
				// Тут давать чашу, если будет
				ChurchGenQuest2_GiveCup();
				PChar.GenQuest.ChurchQuest_2.Complete.PriestIsThief = true;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_7":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
				LAi_ActorRunToLocation(rChar, "reload", "reload1_back", "none", "", "", "", -1);
			}
			
			// Разрешим генерацию энкаунтеров, откроем выходы
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_1");
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_8":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_2");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_1":
			if(PChar.GenQuest.ChurchQuest_2.BanditsCount == 1)
			{
				dialog.text = RandSwear()+"Habe ich diesen Lumpen nicht gesagt: Haltet eure gierigen Pfoten still und nehmt vom Priester nichts außer Geld!";
			}
			else
			{
				dialog.text = RandSwear()+"Habe ich diesen unersättlichen Schakalen nicht gesagt: haltet eure gierigen Pfoten zurück und nehmt vom Priester nichts außer Geld!";
			}
			
					link.l1 = "Was faselst du da? Gut, triff deine Wahl: Entweder du gibst mir deine gestohlene Beute freiwillig, oder ich rufe die Wachen.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2":
			dialog.text = "Ich treffe eine andere Wahl, du hältst dein schwatzendes Maul und gibst mir deine Geldbörse, und ich verschone dein Leben.";
				link.l1 = "Ich werde Ihnen helfen, jetzt eine Audienz bei unserem Herrn zu bekommen!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_1";
				link.l2 = "Gut, ich gebe dir etwas Geld, aber nur aus freien Stücken, damit du und deine Freunde ein ehrliches Leben führen könnt und euch nicht durch Raub erniedrigen müsst.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_2";
				link.l3 = "Ehh... Also gut, lassen wir unsere Meinungsverschiedenheiten beiseite und gehen zurück zum Anfang unseres Gesprächs. Also, wie viel wolltest du für das Ding?";
				link.l3.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_1":
			// Не забыть чашу!
			ChurchGenQuest2_GiveCup();
			PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
			NPChar.money = ((rand(3) + 6) * 1000);
			PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_2":
			AddMoneyToCharacter(PChar, -sti(PChar.money)/2); // Забираем половину денег
			PChar.GenQuest.ChurchQuest_2.Complete.Without_All = true; // Полностью проигрышный вариант. Остаемся ни с чем
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "First time";
			}
			
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "11_2");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3":
			iMoney = makeint(makeint(Pchar.money)/20)*10;
			dialog.text = "Ich brauche auch keine Probleme, "+GetAddress_Form(pchar)+", aber nun ist der Preis gestiegen. Für diesen kostbaren Becher werde ich alles verlangen, was du bei dir hast.";
			if(iMoney >= makeint(Pchar.rank)*300)
			{
				link.l1 = "Du gieriger Abschaum! Ich habe nur "+FindRussianMoneyString(iMoney)+" mit mir. Nimm es und verschwinde!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1";
			}
			else
			{
				link.l1 = "Falsche Wahl, gierige Ratte. Du wirst auf meine Kosten nichts Gutes tun!"+GetSexPhrase(" Ich bin frei wie der Wind - jetzt hier, am nächsten Tag dort, heute bin ich arm - morgen werde ich reich...","")+"";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2";
			}
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_GiveCup();	// Даем чашу
			AddMoneyToCharacter(PChar, -(makeint(makeint(Pchar.money)/20)*10));
			PChar.GenQuest.ChurchQuest_2.Complete.Only_With_Cup = true;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "Left_Time_Case"; // Диалог не забыть поменять.
			}
			
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_3");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2":
			dialog.text = "Bist du nicht gerade dabei zu sagen, dass besonders heute "+GetSexPhrase("du bist arm","du hast kein Geld")+"Was?!";
				link.l1 = "Genau, mein gieriger Freund, zu deiner großen Enttäuschung. Und nun muss ich mich entschuldigen, ich habe viel zu tun.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3";	
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3":
			dialog.text = "Halt! Wir werden das überprüfen, und wenn du nicht die Wahrheit gesprochen hast, werde ich deine lügende Zunge in eine Ameisenkolonie stecken!";
				link.l1 = "Nachdem du das gesagt hast, bist du erledigt!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4";
			break;
			
		// Можно этот кэйс - Church_GenQuest_2_ShoreBandit_Real_Band_2_1
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4":
				// ГГ как-бы может обыскать трупики и забрать все барахло...
				PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
				NPChar.money = ((rand(3) + 6) * 1000);
				PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
				sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
				AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_4");
				AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("As a real gentleman, I am honest","I am honest"));
			break;
			
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// ГЕНЕР "PIRATES ON AN UNINHABITED ISLAND"
		///////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "PiratesOnUninhabited_1":
			dialog.text = "Oh, es gibt nichts zu entscheiden. Wir können alles selbst entscheiden. Aber wir nehmen Ihr Schiff und hauen hier ab.";
			link.l1 = "Es gibt eine Bedingung, zuerst musst du mir mein Schwert abnehmen...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_2":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				LAi_SetImmortal(CharacterFromID("PirateOnUninhabited_" + i), false);
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_3":
			PChar.GenQuest.PiratesOnUninhabited.MainPirateName = GetRandName(NAMETYPE_NICK, NAME_GEN);
			PChar.GenQuest.PiratesOnUninhabited.BadPirateName = GetRandName(NAMETYPE_ORIG, NAME_NOM);
			
				i = PiratesOnUninhabited_GenerateShipType();
				PChar.GenQuest.PiratesOnUninhabited.StartShipType = i;
			
			if(hrand(1) == 0)
			{
				PChar.GenQuest.PiratesOnUninhabited.Shipwrecked = true;
				
				dialog.text = "Hallo, Kapitän! Anscheinend hat die Vorsehung selbst dich geschickt, um zu retten "+PChar.GenQuest.PiratesOnUninhabited.MainPirateName+" und seine Jungs. Wir sind hier dringend in Not."+"Unsere "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[i].Name))+" ist im Sturm an den örtlichen Riffen gestrandet, und die Wellen spülten die Überlebenden der Besatzung an Land."+"Für "+(5+hrand(7))+" Wochenlang starrten wir am Horizont, in der Hoffnung, das Segel eines Schiffes zu sehen, das uns retten würde.";
				link.l1 = RandPhraseSimple(RandPhraseSimple("Ja, das ist ein beneidenswertes Schicksal. Aber so ist das Los des Seemannslebens, jeder könnte an deiner Stelle enden.","Ich verstehe... Gott hält jedes Leben, es ist nur so, dass er zu beschäftigt ist, sich an jeden zu erinnern."),RandPhraseSimple("Gewiss. Der Mensch schlägt vor, aber Gott verfügt.","Ja, das war sicherlich ein Schlag des Pechs."));
				link.l1.go = "PiratesOnUninhabited_4";
			}
			else
			{
				dialog.text = "Es war sehr ernst! Dieser Schurke "+PChar.GenQuest.PiratesOnUninhabited.BadPirateName+" konnte mir keine andere Strafe vorstellen als zu gehen "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_ACC)+" auf einer unbewohnten Insel, wie ein räudiger Köter! "+"Er hoffte, dass Sonne und Durst uns ausdörren würden wie einen getrockneten Makrele auf einem Fischerstand! Aber er hat sich geirrt, denn die Vorsehung selbst war auf unserer Seite, als Sie uns hierher geschickt hat, um uns zu retten...";
				link.l1 = RandPhraseSimple("Nicht so schnell, Freund. Soweit ich sagen kann, seid ihr Männer eines freien Berufes, und ihr seid nicht zufällig hier gelandet.","Redest du schon von Erlösung? Soweit ich verstehe, bist du wegen besonderer Leistungen hier.");
				link.l1.go = "PiratesOnUninhabited_41";
			}
		break;
		
		case "PiratesOnUninhabited_4":
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = 5 + hrand(5);
			
			dialog.text = RandPhraseSimple("Kapitän, seien Sie so gut und helfen Sie  "+PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))+" mittellose Männer. Du bist unsere einzige Hoffnung, abgesehen von unserem gnädigsten Herrn.","Kapitän, hätten Sie freie Schließfächer auf Ihrem Schiff für "+PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))+" mittellose Männer?");
			
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l1 = "Ohh... und wohin möchtest du, dass ich dich bringe?";
				link.l1.go = "PiratesOnUninhabited_5";
			}
			
			link.l2 = RandPhraseSimple(RandPhraseSimple("Es tut mir wirklich leid, aber es gibt nicht einmal eine freie Hängematte, ganz zu schweigen von den Kabinen. Die Matrosen schlafen auf dem Deck, sie können sich nicht einmal nach einer Wache gut ausruhen...","Ich würde es wirklich hassen, dich zu enttäuschen, aber das Schiff ist überladen, und die Leute müssen bei schlechtem Wetter schlafen. Sollte eine Krankheitsausbruch geben, werde ich die Hälfte der Mannschaft verlieren."),RandPhraseSimple("Es tut mir wirklich leid, aber auf meinem Schiff ist absolut kein Platz mehr für zusätzliche Besatzungsmitglieder. Ich kann keine weiteren Passagiere aufnehmen.","Ich muss dich enttäuschen, aber mein Schiff ist überladen mit Besatzungsmitgliedern. Ich fürchte die Epidemie..."));
			link.l2.go = "PiratesOnUninhabited_21";
			
			if(stf(PChar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "Du bist ein erfahrener Seemann und solltest wissen, dass die Anwesenheit von jemandem, der einen Schiffbruch erlitten hat, ein sehr schlechtes Zeichen ist. Meine Seeleute werden euch einfach alle über Bord werfen.";
				link.l3.go = "PiratesOnUninhabited_7";
			}
		break;
		
		case "PiratesOnUninhabited_5":
			dialog.text = "Hmm... Sie wissen, aus mehreren Gründen möchten wir so weit wie möglich von den Behörden entfernt bleiben... Bitte bringen Sie uns zu irgendeiner Bucht auf einer bewohnten Insel oder im Main, und dann könnten wir für uns selbst sorgen.";
			link.l1 = "Nun, ich habe genug freie Schließfächer und Hängematten. Belade dich selbst ins Boot.";
			link.l1.go = "PiratesOnUninhabited_10";
			link.l2 = "Hmm... Unglück... Wir haben Kämpfe vor uns, und ich weiß nicht, wo du sicherer sein wirst, an Bord meines Schiffes oder in dieser gemütlichen Bucht.";
			link.l2.go = "PiratesOnUninhabited_6";
		break;
		
		case "PiratesOnUninhabited_6":
			dialog.text = "Oh, Kapitän! Das sind Zeiten, in denen man sich nicht einmal in einem Bett mit seiner Frau sicher fühlen kann, ha-ha, geschweige denn auf See... Schau dir diese Schurken an, jeder von ihnen ist bereit, mit bloßen Händen gegen Kanonen zu kämpfen. Sie sehnen sich überhaupt nicht nach Sicherheit und Komfort, das kannst du in ihren Gesichtern lesen!";
			link.l1 = "Auf ihren Gesichtern kann ich nur den Willen ablesen, ihren törichten Wohltäter in den Rücken zu stechen.";
			link.l1.go = "PiratesOnUninhabited_7";
			link.l2 = "Hmm... Das ist tatsächlich eine gute Idee. Sag mir, Freund, sind deine Schurken bereit, in meiner Mannschaft zu dienen?";
			link.l2.go = "PiratesOnUninhabited_8";
		break;
		
		case "PiratesOnUninhabited_7":
			dialog.text = "Ein Jammer, Kapitän... Ich sehe, dass wir es nicht auf freundliche Weise klären können. Ich glaube, ich muss Sie an den Seemannscode erinnern. Und denken Sie daran, wenn es ums Entern geht, sind wir unübertroffen...";
			link.l1 = "Nun, jetzt kann ich endlich sehen, wer du wirklich bist...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", -3.0);
		break;
		
		// Берем их в команду
		case "PiratesOnUninhabited_8":
			dialog.text = "Aber natürlich! Sie würden sich freuen, Teil Ihrer Entertruppe zu werden! Niemand wird sie im Kampf besiegen, außer vielleicht Davy Jones selbst! Ha-ha-ha!";
			link.l1 = "Gut, dann. Ladet euch in die Boote...";
			link.l1.go = "PiratesOnUninhabited_9";
		break;
		
		case "PiratesOnUninhabited_9":
			bTemp = CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked");
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;
				
				if(bTemp)
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				}
				else
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_43_again";
				}
			}
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount));
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			OfficersReaction("bad");
			
			//PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			//DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_10":
			dialog.text = "Danke, Kapitän! Das Beladen sollte nicht zu viel Zeit in Anspruch nehmen. Gott, wie wir für diesen Moment gebetet haben!";
			link.l1 = "Sehr gut, dann.";
			link.l1.go = "PiratesOnUninhabited_11";
		break;
		
		// Берем их в пассажирами - держать курс на населенный остров
		case "PiratesOnUninhabited_11":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
			}
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			OfficersReaction("good");
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			
			sTemp = XI_ConvertString(PChar.location + "Gen"); // belamour gen
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			
			if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.TreasureMap"))
			{
				if(CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked"))
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "1");
					AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
					// --> belamour gen: нужно разделить, иначе получается с потерпевшего крушение бригантины 
					if(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
					{
						AddQuestUserData(sTitle, "sText", "wrecked pirate");
					}
					else
					{
						AddQuestUserData(sTitle, "sText", "wrecked pirate");
					}
					// <-- belamour gen
				}
				else
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "11");
					AddQuestUserData(sTitle, "pirateName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
				}
			}
			else
			{
				AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "5");
				AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
				// --> belamour gen: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData(sTitle, "sText", "wrecked pirate");
				}
				else
				{
					AddQuestUserData(sTitle, "sText", "wrecked pirate");
				}
				// <-- belamour gen
			}
			
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailors"); // belamour gen
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1.location = PChar.location;
			PChar.Quest.PiratesOnUninhabited_LocExitGood.function = "PiratesOnUninhabited_LocationExit_Good";
			
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1.location_type = "seashore";
			PChar.Quest.PiratesOnUninhabited_OnShore.again = true;
			PChar.Quest.PiratesOnUninhabited_OnShore.function = "PiratesOnUninhabited_OnShore";
			
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1.location_type = "mayak";
			PChar.Quest.PiratesOnUninhabited_OnMayak.again = true;
			PChar.Quest.PiratesOnUninhabited_OnMayak.function = "PiratesOnUninhabited_OnShore";
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_11_Again":
			dialog.text = LinkRandPhrase("Warum zögerst du, Kapitän? Befehle den Anker zu lichten.","Es tut uns leid, Kapitän, aber wir müssen uns zum Auslaufen fertig machen.","Wir sind so glücklich, dass du dich entschieden hast, hierher zu kommen!");
			link.l1 = "Beeil dich. Das Schiff wird auf niemanden warten.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_11_Again";
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове
		case "PiratesOnUninhabited_12":
			if(hrand(1) == 0)
			{
				// Успешное завершение квеста - даст награду
				dialog.text = "Danke, Kapitän. Tatsächlich hatten wir recht, an unser Glück zu glauben... Bitte, nimm diesen Edelstein, ich habe ihn in dieser verhängnisvollen Bucht gefunden. Ich hoffe, er bringt dir Glück.";
				link.l1 = "Ich habe so ein Geschenk nicht erwartet.";
				link.l1.go = "PiratesOnUninhabited_13";
			}
			else
			{
				// Требуют денег
				dialog.text = "Kapitän, bitte, denken Sie nicht, dass wir zu unverschämt sind, aber uns fehlt wirklich das Geld. Sie wissen, wir haben alles verloren, was wir hatten. Könnten Sie uns bitte ein paar Hände voll Pesos leihen? Wir werden Ihnen sicher zurückzahlen... wenn sich die Gelegenheit ergibt...";
				link.l1 = "Wahnsinn! Tatsächlich, die Unverschämtheit kennt keine Grenzen. Nun, das Einzige, was ich jetzt für dich tun könnte, nach allem, was ich bereits getan habe, wäre, den Behörden nichts von dir zu erzählen.";
				link.l1.go = "PiratesOnUninhabited_15";
				link.l2 = "Das sagst du nicht... Und wie viel willst du?";
				link.l2.go = "PiratesOnUninhabited_17";
			}
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_13":
			AddItems(PChar, "jewelry4", 1);
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				
				rChar.Dialog.currentnode = "PiratesOnUninhabited_14";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "2");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_14":
			dialog.text = LinkRandPhrase("Danke, Kapitän.","Kapitän, wir sind Ihnen so dankbar.","Wir werden für Sie beten, Kapitän "+PChar.name+"!");
			link.l1 = "Viel Glück für dich. Auf Wiedersehen...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_14";
		break;
		
		case "PiratesOnUninhabited_15":
			dialog.text = "Heh, Kapitän... Du weißt, wir haben uns gut verstanden... Es wäre wirklich schade, dich zu töten...";
			link.l1 = "Du kannst es versuchen!";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
		break;
		
		case "PiratesOnUninhabited_16":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "3");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_17":
			iMoney = sti(PChar.rank) * 500;
			PChar.GenQuest.PiratesOnUninhabited.Money = iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			
			dialog.text = "Nun, sag, "+iMoney+" Pesos für jeden von uns wären recht nett... Natürlich, wenn du nicht denkst, dass diese Entschädigung für all unseren Schmerz und unser Leiden zu klein ist, he-he...";
			link.l1 = RandPhraseSimple("Ganz im Gegenteil, ich bin mir sicher, dass es viel zu viel ist... Ein Galgenstrick um den Hals für jeden von euch wäre das Beste.","Ich werde euch wie Affen an Palmen für solches Geld selbst aufhängen!");
			link.l1.go = "PiratesOnUninhabited_18";
			
			if(sti(PChar.money) >= iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				link.l2 = "In Ordnung, nimm es. Ich hoffe wirklich, ich schulde dir nichts weiter?";
				link.l2.go = "PiratesOnUninhabited_19";
			}
		break;
		
		case "PiratesOnUninhabited_18":
			dialog.text = "Welche Großzügigkeit! Ehrlich gesagt, dachte ich, dass Sie bereits die Gelegenheit hatten zu sehen, dass wir immer das bekommen, was wir wollen. Und dieses Mal werden wir auch nicht zurückweichen...";
			link.l1 = "Du kannst es versuchen!";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_19":
			dialog.text = "Oh nein, Kapitän, was sagst du?! Wir werden definitiv eine Kerze in deinem Namen anzünden, wenn wir jemals eine Kirche betreten... hah!";
			link.l1 = "Ich hoffe es...";
			link.l1.go = "PiratesOnUninhabited_20";
			
			iMoney = sti(PChar.GenQuest.PiratesOnUninhabited.Money);
			
			AddMoneyToCharacter(PChar, -iMoney);
			AddMoneyToCharacter(NPChar, iMoney);
		break;
		
		case "PiratesOnUninhabited_20":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_CharacterDisableDialog(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
			OfficersReaction("good");
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Acc")));
			CloseQuestHeader(sTitle);
			
			NPChar.SaveItemsForDead = true; // сохранять на трупе вещи
			NPChar.DontClearDead = true;  // не убирать труп через 200с
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_21":
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				// Игрок врет - свободное место есть
				dialog.text = "Oh nein, Kapitän, was sagst du da?! Wir werden sicherlich eine Kerze in deinem Namen anzünden, wenn wir jemals eine Kirche betreten...hah!";
				link.l1 = "Ich hoffe es...";
				link.l1.go = "PiratesOnUninhabited_23";
			}
			else
			{
				dialog.text = "Heh, Kapitän, Sie wissen, das ist nicht viel von einem Problem. Ich und meine Jungs sind bereit, ein Dutzend Hängematten auf Ihrem Schiff von denen zu befreien, die sie derzeit besetzen...";
				link.l1 = "Hmm... das klingt wie eine Drohung...";
				link.l1.go = "PiratesOnUninhabited_22";
			}
		break;
		
		case "PiratesOnUninhabited_22":
			dialog.text = "Nun, tatsächlich ist es eine Bedrohung. Ich brauche dein Schiff, und ich werde diesen Ort verlassen, mit oder ohne deine Zustimmung!";
			link.l1 = "Nun, jetzt kann ich endlich sehen, wer du wirklich bist...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_23":
			dialog.text = "Ich verstehe Sie, Kapitän. Ich verstehe Sie vollkommen... Wer würde schon arme Piraten pflegen wollen, die nach einer Schlinge gefragt haben?.. Aber... was wäre, wenn ich Ihnen einen Tausch anbiete? Sie liefern uns zu irgendeiner Bucht auf einer bewohnten Insel oder im Main, und ich gebe Ihnen dafür eine Schatzkarte. Haben wir einen Deal?";
			link.l1 = "Hmm... Und wie können Sie garantieren, dass diese Karte keine Fälschung ist?";
			link.l1.go = "PiratesOnUninhabited_25";
			link.l2 = "Ha, ich bin sicher, dass deine Karte so viel kostet wie das Stück Papier, auf dem sie gezeichnet wurde...";
			link.l2.go = "PiratesOnUninhabited_24";
		break;
		
		case "PiratesOnUninhabited_24":
			dialog.text = "Nun... Du lässt uns keine Wahl... Trotzdem werden wir diesen Ort verlassen, ob du willst oder nicht!";
			link.l1 = "Nun, jetzt kann ich endlich sehen, wer du wirklich bist...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_25":
			dialog.text = "Und wie kannst du garantieren, dass du uns nicht bei den Behörden im nächsten Hafen verrätst? Wir spielen beide, ohne die Karten des anderen zu sehen...";
			link.l1 = "In Ordnung, wir haben einen Deal.";
			link.l1.go = "PiratesOnUninhabited_11";
			PChar.GenQuest.PiratesOnUninhabited.TreasureMap = true;
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове. Вариант, когда нам обещали карту сокровищ
		case "PiratesOnUninhabited_26":
			// PChar.GenQuest.PiratesOnUninhabited.MainPirateName - имя в родительном падеже
			
			dialog.text = "Danke, Kapitän "+PChar.name+". Du hast erfüllt"+GetSexPhrase("","")+" deine Versprechen, es ist Zeit "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_DAT)+" um meine zu erfüllen. Ich habe die Karte nicht bei mir, aber ich werde dir sagen, wo der Schatz ist. Geh zur Bucht...";
			link.l1 = "Oh, so drückst du es jetzt aus! Ich sehe, du wolltest mich von Anfang an hereinlegen...";
			link.l1.go = "PiratesOnUninhabited_27";
			link.l2 = "Ich wusste sofort, dass man dir nicht trauen konnte...";
			link.l2.go = "PiratesOnUninhabited_30";
			link.l3 = "Das passiert, wenn man einem Piraten vertraut. Was seid ihr für Leute? Euch ist nichts heilig!";
			link.l3.go = "PiratesOnUninhabited_33";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_27":
			dialog.text = "Mach keine Szene... Ich bin kein Heiliger, aber ich halte mein Wort!";
			link.l1 = "Und du erwartest, dass ich dir wieder glaube? Damit mich morgen der gesamte Archipel auslacht?";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		case "PiratesOnUninhabited_28":
			dialog.text = "Hmm... Anscheinend wird es keine friedliche Lösung geben. Aber, Gott weiß, ich wollte es nicht...";
			link.l1 = "Zieh dein Schwert, oder ich zermalme dich wie die Ratte, die du bist!";
			link.l1.go = "PiratesOnUninhabited_29";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_29":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "6");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_30":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "Und was hätte ich sonst tun sollen? In dieser stinkenden Pfütze mit meinen Jungs bleiben und zu Tode verrotten? Du hörst mir besser zu..."+XI_ConvertString(sTitle+"Gen")+" Kapitän "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" es gibt ein Versteck, wo er seine Beute aufbewahrt. Aber sei vorsichtig"+GetSexPhrase("","")+", er besucht oft dort. Das Versteck zu finden wird nicht schwer sein, wenn du deinen Verstand bei dir behältst..."; // belamour gen
			link.l1 = "Und du erwartest, dass ich dir noch einmal glaube? Damit morgen der gesamte Archipel über mich lacht?";
			link.l1.go = "PiratesOnUninhabited_28";
			link.l2 = "In Ordnung. Aber wenn du mich noch einmal anlügst, werde ich dich finden.";
			link.l2.go = "PiratesOnUninhabited_31";
		break;
		
		case "PiratesOnUninhabited_31":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				rChar.Dialog.currentnode = "PiratesOnUninhabited_32";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "7");
			AddQuestUserData(sTitle, "capName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_NOM));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.TreasureShore + "Gen"))); // belamour gen
			
			// Таймер для клада. По прошествии 10 дней в кладе будут всякие бакланы и т.д.
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1 = "Timer";
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.function = "PiratesOnUninhabited_TreasureLose"; // belamour gen
			
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1 = "Location";
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1.Location = PChar.GenQuest.PiratesOnUninhabited.TreasureShore;
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.function = "PiratesOnUninhabited_InTreasureLoc";
			
			DialogExit();
			
			// Курс в бухту, которую назвал пират. У нас сроку 10 дней, котом клад пропадёт
		break;
		
		case "PiratesOnUninhabited_32":
			sTemp = ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC);
			
			dialog.text = LinkRandPhrase("Hör zu "+sTemp+", er spricht Sinn.","Sei nicht böse auf "+sTemp+", er hatte einfach keine andere Wahl.","Danke, Kapitän.");
			link.l1 = "Viel Glück für dich...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_32";
		break;
		
		case "PiratesOnUninhabited_33":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "Und was hätte ich sonst tun sollen? In dieser stinkenden Pfütze mit meinen Jungs bleiben und zu Tode verrotten? Du hörst mir besser zu..."+XI_ConvertString(sTitle+"Gen")+" Kapitän "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" es gibt ein Versteck, wo er seine Beute aufbewahrt. Aber sei vorsichtig, er besucht es oft. Das Versteck zu finden wird nicht schwer sein, wenn du deinen Verstand beisammen hältst..."; // belamour gen
			link.l1 = "Und du erwartest, dass ich dir wieder glaube? Damit morgen der ganze Archipel über mich lacht?";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		// Пираты в бухте с сокровищем
		case "PiratesOnUninhabited_34":
			dialog.text = "Wer bist du,"+GetSexPhrase(" Kamerad"," Lass")+"? Und was hat dich an diesen verlassenen Ort gebracht?";
			link.l1 = "Ich habe angehalten, um meine Vorräte an frischem Wasser aufzufüllen.";
			link.l1.go = "PiratesOnUninhabited_35";
			link.l2 = "Ich bin hier im Auftrag von "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_GEN)+".";
			link.l2.go = "PiratesOnUninhabited_38";
			NextDiag.TempNode = "PiratesOnUninhabited_34";
		break;
		
		case "PiratesOnUninhabited_35":
			dialog.text = "Du hast einen schlechten Ort dafür ausgewählt... Na gut, nimm dir Zeit.";
			link.l1 = "A-ha...";
			link.l1.go = "exit";
			link.l2 = "Und wer bist du, mir zu sagen, was ich tun soll?";
			link.l2.go = "PiratesOnUninhabited_36";
		break;
		
		case "PiratesOnUninhabited_36":
			dialog.text = "Ich sage allen, was sie zu tun haben. Und diejenigen, die sich für zu schlau halten, werden am Palmenbaum hängen.";
			link.l1 = "Ich schneide deine Zunge ab, du Hund.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_37":
			DialogExit();
			LAi_Group_SetRelation("PiratesOnUninhabited_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;
		
		case "PiratesOnUninhabited_38":
			dialog.text = "Und warum ist er nicht selbst gekommen?";
			link.l1 = "Er wollte nicht, blieb bei "+LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen"))+" und warten auf mich."; // belamour gen
			link.l1.go = "PiratesOnUninhabited_39";
		break;
		
		case "PiratesOnUninhabited_39":
			dialog.text = "Dieser alte Schurke! Er versucht uns wieder hereinzulegen, oder? Das wird nicht funktionieren. Sag ihm, dass er das Geld nur gemeinsam mit uns einsammeln kann!";
			link.l1 = "Er hat mir gesagt, nicht ohne Geld zurückzukommen und niemanden an Bord zu nehmen...";
			link.l1.go = "PiratesOnUninhabited_40";
		break;
		
		case "PiratesOnUninhabited_40":
			dialog.text = "Nun, wenn du ihm so sehr vertraust, kannst du hier bleiben. Aber wir werden dein Schiff, dein Geld nehmen und nach "+LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen"))+". Wir sterben vor Neugier, das Gesicht von "+PChar.GenQuest.PiratesOnUninhabited.MainPirateName+"."; // belamour gen
			link.l1 = "Wenn du ihn so sehr vermisst, kannst du dorthin schwimmen... oder du kannst hier sterben.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.GenQuest.PiratesOnUninhabited.UseMainPiratename = true;
		break;
		
		// Ветка из PiratesOnUninhabited_3
		case "PiratesOnUninhabited_41":
			iBanditsCount = 5 + hrand(5);
			iMoney = GetFreeCrewQuantity(PChar);
			
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = iBanditsCount;
			
			dialog.text = "Du bist eine gerissene Person. Aber lass mich dir versichern, dass unser Konflikt mit dem Kapitän "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_ABL)+" ist rein ideologischer Natur. Ich habe ihn gewarnt, dass seine schmutzigen Operationen eines Tages bestraft werden würden und jetzt ich und mein  "+iBanditsCount+" Kumpels leiden wegen unserer Liebe zu Gott und Gerechtigkeit.";
			link.l1 = "Wie bitte... Ich wette, ihr seid die eigentlichen Anstifter der Meuterei gewesen, und ihr habt bekommen, was ihr verdient habt.";
			link.l1.go = "PiratesOnUninhabited_42";
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l2 = "Natürlich... Es wäre jedoch schön, die Meinung des Kapitäns zu hören "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" selbst hinsichtlich eurer Meinungsverschiedenheiten.";
				link.l2.go = "PiratesOnUninhabited_44";
			}
		break;
		
		case "PiratesOnUninhabited_42":
			dialog.text = "Kapitän, warum beleidigen Sie ehrliche Leute mit Ihrem Misstrauen? Schauen Sie sich nur ihre Gesichter an... Glauben Sie wirklich, sie sind Meuterer? Sie sind so bescheiden, wie Männer nur sein können... Aber sie sind unübertroffen im Kampf für eine gerechte Sache unter gutem Kommando! Ich kann persönlich für jeden einzelnen von ihnen bürgen.";
			link.l1 = "Also gut, aber was soll ich jetzt mit dir machen?";
			link.l1.go = "PiratesOnUninhabited_43";
		break;
		
		case "PiratesOnUninhabited_43":
			iBanditsCount = sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			iMoney = GetFreeCrewQuantity(PChar);
			
			dialog.text = "Was auch immer du wünschst. Es liegt an dir, bring uns zu einer Siedlung oder nimm uns in deine Crew auf, du scheinst mir ein guter Kapitän zu sein.";
			
			if(iMoney >= iBanditsCount)
			{
				link.l1 = "In Ordnung, ich nehme dich in meine Mannschaft auf. Aber kein Unsinn! Auf meinem Schiff herrscht strenge Disziplin!";
				link.l1.go = "PiratesOnUninhabited_9"; // Берем в команду
			}
			
			link.l2 = "Ich bringe dich nirgendwohin. Ich habe schon genug Schläger in meiner Mannschaft.";
			link.l2.go = "PiratesOnUninhabited_24"; // Рубилово и конец квеста
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l3 = "In Ordnung, steig ins Boot, ich bringe dich irgendwohin.";
				link.l3.go = "PiratesOnUninhabited_11"; // В пассажиры и на остров
			}
		break;
		
		case "PiratesOnUninhabited_43_again":
			dialog.text = LinkRandPhrase("Ich schwöre, Kapitän, Sie werden es nicht bereuen.","Sie haben die richtige Wahl getroffen, Kapitän.","Kapitän, seien Sie versichert, dass Sie genauso viel Glück hatten wie wir!");
			link.l1 = RandPhraseSimple("Ich hoffe es.","Beeil dich. Das Schiff wartet auf niemanden.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_43_again";
		break;
		
		case "PiratesOnUninhabited_44":
			sTitle = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.PiratesOnUninhabited.StartShipName = sTitle;
			
			dialog.text = "Das kann leicht arrangiert werden. Er segelt auf  "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Name+"Voc"))+" '"+sTitle+" und handelt mit Sklaverei... Lass uns das so machen: Wenn wir ihn finden, bekommst du die Ladung und wir das Schiff. Oh, und du kannst ihn auch fragen, ob er etwas über "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_ACC)+". Ich hoffe, er kackt nicht in die Hose, wenn er diesen Namen hört, denn das ist mein Schiff..."; // belamour gen
			link.l1 = "Also gut, wir haben einen Deal.";
			link.l1.go = "PiratesOnUninhabited_45";
		break;
		
		case "PiratesOnUninhabited_45":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				rChar.location = "none"; // Убираем из локации при выходе   исправлено с NPChar на rChar - лесник
				rChar.location.locator = ""; // лесник  - так же исправлено .  тогда бага не будет.
			}
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1)
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			//NPChar.FaceId = 101; // лесник потом подобрать аву бандиту.   
			
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			sTemp = XI_ConvertString(PChar.location + "Gen"); // belamour gen
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "13");
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			// --> belamour окончание по количеству персон
			if(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) >= 5)
			{
				AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailors");
			}
			else
			{
				AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailor");
			}
			// <-- belamour
			AddQuestUserData(sTitle, "badCapName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Voc")) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'"); // belamour gen
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PiratesOnUninhabited_SetCapToMap(); // Ставим корабль на карту
			
			DialogExit();
		break;
		
		// Диалог с кэпом в каюте
		case "PiratesOnUninhabited_46":
			dialog.text = "Was zum Teufel willst du von mir?";
			link.l1 = "Ich bin gekommen, um im Namen von "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_GEN)+". Ich nehme an, du kennst ihn?";
			link.l1.go = "PiratesOnUninhabited_47";
			
			PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
			PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
			Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
		break;
		
		case "PiratesOnUninhabited_47":
			dialog.text = "Es ist schade, dass ich diesen Schurken nicht früher erwürgt habe. Nun, dann ist es wohl an der Zeit, für meine Güte zu bezahlen...";
			link.l1 = "Tatsächlich... Und die Zeit ist gerade abgelaufen...";
			link.l1.go = "PiratesOnUninhabited_48";
		break;
		
		case "PiratesOnUninhabited_48":
			LAi_CharacterDisableDialog(NPChar);
			LAi_Group_Attack(NPChar, Pchar);
			
			LAi_SetCurHPMax(NPChar);
			QuestAboardCabinDialogFree(); // важный метод
			
			LAi_Group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_Group_SetCheckFunction(LAI_GROUP_BRDENEMY, "PiratesOnUninhabited_CapDeath");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_49":
			dialog.text = "Großartige Arbeit, Kapitän! Alles wie abgemacht, oder? Wir bekommen das Schiff und du die Ladung?";
			link.l1 = "Sicher. Nimm das Schiff und nutze es gut.";
			link.l1.go = "PiratesOnUninhabited_50";
		break;
		
		case "PiratesOnUninhabited_50":
			NPChar.LifeDay = 0;
			NPChar.location = "none"; // Убираем из каюты
			NPChar.location.locator = "";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "14");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			ChangeAttributesFromCharacter(CharacterFromID("PiratesOnUninhabited_BadPirate"), NPChar, true);
			DialogExit();
			
		break;
		
		// На палубе, когда корабль с нашим пиратом отпустили
		case "PiratesOnUninhabited_50_Deck1":
			dialog.text = "Ich grüße Sie, Kapitän "+PChar.name+".";
			link.l1 = "Also, wie gefällt Ihnen Ihr Schiff?";
			link.l1.go = "PiratesOnUninhabited_50_Deck2";
		break;
		
		case "PiratesOnUninhabited_50_Deck2":
			dialog.text = "Heh... es quietscht und knarrt, genau wie ich. Ich glaube, wir haben beide nicht mehr viel Zeit, die hohen Meere zu befahren...";
			link.l1 = "Viel Glück, dann...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_50_Deck1";
		break;
		
		// В бухте, вариант, когда корабль, который нужно было захватить, утопили
		case "PiratesOnUninhabited_51":
			dialog.text = "Warum hast du mein Schiff versenkt?! Erinnerst du dich überhaupt an unseren Deal?";
			link.l1 = "Was, ich wollte nicht, dass er mich stattdessen versenkt. Siehst du nicht, dass ich es kaum geschafft habe?";
			link.l1.go = "PiratesOnUninhabited_52";
		break;
		
		case "PiratesOnUninhabited_52":
			if(hrand(1) == 1)
			{
				dialog.text = "Wer kämpft denn so? Du hast ein solches Schiff verloren! Was zum Teufel! Was macht ein Kind wie du überhaupt hier?";
				link.l1 = "Ich schneide deine Zunge ab, du Tölpel.";
				link.l1.go = "PiratesOnUninhabited_53";
			}
			else
			{
				iMoney = sti(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Price);
				iMoney = MakeInt((iMoney / 1.2 + hrand(iMoney - (iMoney / 1.2))) * 1.2);
				dialog.text = "Wer kämpft denn so? Du hast solch ein Schiff verloren! Hast du eine Ahnung, wie viel das mich gekostet hat? "+FindRussianMoneyString(iMoney)+"! Du schuldest mir jetzt...";
				link.l1 = "Wäre es nicht zu viel für dich? Vergiss nicht, dass ich dir schon einen Gefallen getan habe.";
				link.l1.go = "PiratesOnUninhabited_54";
				
				if(sti(PChar.money) >= iMoney)
				{
					link.l2 = "Verflucht seist du mit diesem verfluchten Schiff! Nimm dein Geld und falle nicht mehr unter mein Auge!";
					link.l2.go = "PiratesOnUninhabited_55";
				}
			}
		break;
		
		case "PiratesOnUninhabited_53":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "15");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_54":
			dialog.text = "Und was nützt mir dieser Gefallen jetzt?! Wenn Kapitän "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_NOM)+" liegt jetzt mit meinem Schiff auf dem Meeresgrund! Jetzt bekomme ich weder meinen Anteil, noch mein Schiff zurück! Welch ein Schicksal, im Rinnstein zu sterben, wie ein Landstreicher!!!";
			link.l1 = "Aber warum? Ich kann Ihnen ein spektakuläres Begräbnis arrangieren. Gleich hier, wenn das für Sie in Ordnung ist...";
			link.l1.go = "PiratesOnUninhabited_53";
		break;
		
		case "PiratesOnUninhabited_55":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "16");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// КОНЕЦ
		
		// Warship, 15.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "Ich dachte wir könnten... vielleicht zu einer Vereinbarung kommen? Wenn Sie uns einen Gefallen tun, werden wir ihn erwidern, he-he.";
			link.l1 = "Einen Gefallen? Und was ist der Deal und was bietest du im Gegenzug an?";
			link.l1.go = "JusticeOnSale_3";
		break;
		
		case "JusticeOnSale_2":
			LAi_Group_SetRelation("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, true);
			
			DialogExit();
			LAi_SetFightMode(PChar, true);
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "Unser Kapitän "+PChar.GenQuest.JusticeOnSale.SmugglerName+" wurde von der örtlichen Patrouille erwischt "+XI_ConvertString("Colony"+PChar.GenQuest.JusticeOnSale.CityId+"Gen")+". Sie haben ihn eingesperrt, aber sie haben nicht genug Beweise, um ihn zu hängen. Wir können ihn nicht selbst rausschleppen\n"+"Sie sind ein angesehener Mann. Die Leute kennen Sie. Vielleicht könnten Sie verhandeln, auslösen oder ihn einfach kaufen? Vertrauen Sie uns, wir werden die Insel verlassen, sobald wir unseren Mann haben, also wird Ihr Ansehen nicht leiden!"; // belamour gen
			link.l1 = "Lassen Sie uns sagen, dass ich Ihnen helfen kann. Aber was ist mit meiner Bezahlung?";
			link.l1.go = "JusticeOnSale_4";
			link.l2 = "Zum Teufel, teuflischer Spross! Ich will nichts mit dir zu tun haben!";
			link.l2.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Möchten Sie einige indische Trinkets und Talismane? Sie sind ziemlich selten... Oder bevorzugen Sie Bares auf den Nagel? Mehrere tausend Pesos, sage ich?";
			link.l1 = "Zum Teufel, teuflischer Sprössling! Ich werde keine Geschäfte mit dir machen!";
			link.l1.go = "JusticeOnSale_5";
			link.l2 = "Ich bin an indischen Krimskrams interessiert. Ich denke, ich werde zustimmen.";
			link.l2.go = "JusticeOnSale_6";
			link.l3 = "Bargeld ist der beste Freund eines Seemanns. Geld hat keinen Geruch, wie wir alle wissen. Ich stimme zu.";
			link.l3.go = "JusticeOnSale_7";
		break;
		
		case "JusticeOnSale_5":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			DialogExit();
		break;
		
		case "JusticeOnSale_6":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 0; // Подрякушки.
			dialog.text = "Danke, Käpt'n. Wir werden Ihnen die Summe der Kaution zusätzlich zu Ihrer Belohnung auszahlen. Ich denke, Sie sollten mit dem Kommandanten über unseren Kapitän sprechen. Vielleicht können Sie ihn überzeugen. Sobald Sie ihn rausbekommen, kommen Sie zu "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+", das ist, wo unser Schiff den Anker gelassen hat - "+LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name))+" '"+PChar.GenQuest.JusticeOnSale.ShipName+"'. Wir werden auf dich am Ufer warten."; // belamour gen
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_7":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 1; // Монеты.
			
			dialog.text = "Danke, Kapitän. Wir werden Ihnen die Kaution zusätzlich zu Ihrer Belohnung erstatten. Ich denke, Sie sollten mit dem Kommandanten über unseren Kapitän sprechen. Vielleicht können Sie ihn überzeugen. Wenn Sie ihn rausbekommen, kommen Sie zu "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+", das ist, wo unser Schiff den Anker geworfen hat - "+LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name))+" '"+PChar.GenQuest.JusticeOnSale.ShipName+". Wir werden auf dich am Ufer warten."; // belamour gen
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			ReOpenQuestHeader("JusticeOnSale");
			AddQuestRecord("JusticeOnSale", "1");
			AddQuestUserData("JusticeOnSale", "cityName", XI_ConvertString("Colony" + PChar.GenQuest.JusticeOnSale.CityId + "Gen")); // belamour gen
			PChar.GenQuest.JusticeOnSale.MayorWait = true;
			PChar.GenQuest.JusticeOnSale.PrisonWait = true;
			
			DialogExit();
		break;
		
		case "JusticeOnSale_9":
			if(hrand(1) == 0)
			{
				if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
				{
					// Награда побрякушками.
					dialog.text = "Wir sind hier, Kapitän! Sie haben einen großartigen Job gemacht, diese bauchigen Bürokraten zu täuschen! Hier ist Ihre Belohnung. Jungs, holt die Schnickschnack!";
				}
				else
				{
					// Награда золотом.
					dialog.text = "Wir sind hier, Kapitän! Sie haben hervorragende Arbeit geleistet, diese bauchigen Bürokraten zu täuschen! Hier ist Ihre Belohnung. Jungs, holt die Kiste!";
				}
				
				link.l1 = "Gib mir meinen Anteil und verschwinde!";
				link.l1.go = "JusticeOnSale_10";
			}
			else
			{
				// Массакра.
				dialog.text = "Wir sind da, Kapitän! Ich sehe, dass Sie alles schön arrangiert haben. Aber Sie sehen... wir brauchen keine Zeugen, also... Lasst uns dem Kapitän danken, Jungs!";
				link.l1 = RandSwear()+"Ich hätte dich erschießen sollen, als ich dich getroffen habe!";
				link.l1.go = "JusticeOnSale_11";
			}
			chrDisableReloadToLocation = false;
		break;
		
		case "JusticeOnSale_10":
			DialogExit();
			if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddItems(PChar, "indian_"+(1+hrand(10)), 1);
				}
				else
				{
					AddItems(PChar, "obereg_"+(1+hrand(10)), 1);
				}
			}
			else
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 700 + hrand(2000));
				}
				else
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 500 + hrand(1000));
				}
			}
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_ActorGoToLocation(rChar, "reload", LAi_FindNearestFreeLocator2Pchar("reload"), "none", "", "", "", 3.0);
			}
			AddQuestRecord("JusticeOnSale", "3");
			CloseQuestHeader("JusticeOnSale");
		break;
		
		case "JusticeOnSale_11":
			AddQuestRecord("JusticeOnSale", "4");
			CloseQuestHeader("JusticeOnSale");
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_Group_MoveCharacter(rChar, "JusticeOnSale_ShoreGroup");
			}
			
			LAi_Group_SetRelation("JusticeOnSale_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;
		
		// belamour постоялец-->
		case "Unwantedpostor_room":
			dialog.text = ""+GetSexPhrase("Wer bist du? Und warum dringst du in mein Zimmer ein?","Wow. Wer bist du? Das ist natürlich mein Zimmer, aber solche Gesellschaft stört mich nicht. Ist das eine Liebeslieferung?")+"";
			link.l1 = ""+GetSexPhrase("Nicht mehr deins. Der Wirt hat mir das Zimmer vermietet, und da du nicht dafür bezahlst, wirst du hier rausgeschmissen. Jetzt können wir das auf die leichte oder die harte Tour machen. Die Entscheidung liegt bei dir.","Du träumst. In unserem Fall geht es ums Saubermachen. Also räum dich selbst hier weg. Dies ist jetzt mein Zimmer, denn im Gegensatz zu dir zahle ich immer die Wirtsleute.")+"";
			link.l1.go = "Unwantedpostor_room_1";
		break;
		
		case "Unwantedpostor_room_1":
			If(sti(pchar.reputation.fame) > 60)
			{
				dialog.text = ""+GetSexPhrase("Ich glaube, ich habe von dir gehört. Gut, du hast gewonnen, ich gehe, ich will noch leben...","Hmm, ich habe viel von dir gehört. Ich nehme an, es ist nicht nur deine Zunge, die scharf ist. Okay, sei nicht böse, das Zimmer gehört dir.")+"";
				link.l1 = ""+GetSexPhrase("Du hast eine gute Entscheidung getroffen.","Guter Junge.")+"";
				link.l1.go = "Unwantedpostor_peace";
				break;
			}
			dialog.text = ""+GetSexPhrase("So ist es also, hm? Nun, ich wähle den schwierigen Weg.","Du Schlampe! Ich wollte freundlich mit dir umgehen...")+"";
			link.l1 = ""+GetSexPhrase("Wie du wünschst...","Und du nennst das 'nett'? Ich bemitleide dich. Obwohl, vielleicht doch nicht.")+"";
			link.l1.go = "Unwantedpostor_fight";
		break;
		
		case "Unwantedpostor_peace":
			DialogExit();
			sld = CharacterFromID("Berglar_Unwantedpostor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			DeleteAttribute(PChar, "GenQuest.Unwantedpostor");
			SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 180, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sTemp = 40*MOD_SKILL_ENEMY_RATE/2;
			AddCharacterExpToSkill(pchar, "Fortune", sti(sTemp));
			AddCharacterExpToSkill(pchar, "Sneak", sti(sTemp));
			AddCharacterExpToSkill(pchar, "Leadership", sti(sTemp));
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "Unwantedpostor_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetFightMode(pchar, true);
			sld = characterFromId("Berglar_Unwantedpostor"); 
			LAi_SetWarriorType(sld);
			LAi_Group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_SetCheckMinHP(sld, 10, true, "Unwantedpostor_Win");
			LAi_SetCheckMinHP(pchar, 10, true, "Unwantedpostor_Lose");	
		break;
		
		case "Unwantedpostor_Win":
			dialog.text = ""+GetSexPhrase("Gut, in Ordnung, halt! Töte mich nicht. Ich gehe.","Halt! Was sollen wir jetzt machen, uns wegen dieses Raumes umbringen?! Würg daran, es gehört ganz dir. Stinktier...")+"";
			link.l1 = ""+GetSexPhrase("Richtige Entscheidung. Ein andermal, denk mit deinem Kopf: nicht jeder ist so freundlich wie ich, sie können unabsichtlich töten.","Männer.")+"";
			link.l1.go = "Unwantedpostor_Win_1";
		break;
		
		case "Unwantedpostor_Win_1":
			DialogExit();
			sld = CharacterFromID("Berglar_Unwantedpostor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			if(CheckAttribute(pchar,"GenQuest.Unwantedpostor")) DeleteAttribute(PChar, "GenQuest.Unwantedpostor"); // полуночная драка
			SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 170+rand(20), false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sTemp = 40*MOD_SKILL_ENEMY_RATE/2;
			AddCharacterExpToSkill(pchar, "FencingL", sti(sTemp));
			AddCharacterExpToSkill(pchar, "FencingS", sti(sTemp));
			AddCharacterExpToSkill(pchar, "FencingH", sti(sTemp));
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "Unwantedpostor_Lose":
			dialog.text = ""+GetSexPhrase("Nun, hast du mich vertrieben? Verzieh dich, bevor ich dich aufschlitze.","So alles, was du kannst, ist einfach nur zu schwatzen. Sei froh, dass ich noch gut gelaunt bin, sonst hätte ich dir etwas noch Schlimmeres angetan. Verzieh dich!")+"";
			link.l1 = ""+GetSexPhrase("Verdammt...","Verdammt, ich habe dich unterschätzt... Okay, okay, ich gehe jetzt.")+"";
			link.l1.go = "Unwantedpostor_Lose_1";
		break;
		
		case "Unwantedpostor_Lose_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sld = CharacterFromID("Berglar_Unwantedpostor");
			sld.lifeday = 0;
			if(CheckAttribute(pchar,"GenQuest.Unwantedpostor")) pchar.GenQuest.Unwantedpostor = "Lose"; // если драка за полночь перевалит
			DoQuestReloadToLocation(Locations[FindLocation(pchar.location)].fastreload+"_tavern", "reload", "reload2_back", "");	
		break;
		// <-- belamour постоялец
		
		// belamour пьяный матрос -->
		case "GuiltySailor":
			dialog.text = "Ah?.. Raus, Grünschnabel, ich trinke.... hic!.. mit niemandem.";
			link.l1 = "Ich schlage dich jetzt so hart, dass du eine Woche lang nicht trinken wirst.";
			link.l1.go = "GuiltySailor_1";
		break;
		
		case "GuiltySailor_1":
			dialog.text = "Was?! Weißt du, mit wem du sprichst? Ich bin ein Seemann vom Schiff '"+pchar.ship.name+"'! Ich muss es nur dem Kapitän sagen, und Sie werden nicht einmal Zeit haben, die Stadt zu verlassen! Hau ab, solange du noch in einem Stück bist."; 
			link.l1 = "..., Freund.";
			link.l1.go = "GuiltySailor_2";
		break;
		
		case "GuiltySailor_2":
			dialog.text = "..., Freund.";
			link.l1 = "...";
			link.l1.go = "GuiltySailor_3";
		break;
		
		case "GuiltySailor_3":
			dialog.text = "Kapitän?..";
			link.l1 = "Du wirst einen Monat lang das Deck schrubben.";
			link.l1.go = "GuiltySailor_4";
		break;
		
		case "GuiltySailor_4":
			NPChar.Dialog.currentnode = "GuiltySailor_Again";
			SetFunctionTimerCondition("GuiltySailor_NextQ", 0, 0, 45+rand(45), false);
			DialogExit();
		break;
		
		case "GuiltySailor_Again":
			dialog.text = "Tut mir leid, Kapitän!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "GuiltySailor_Again";
		break;
		// <-- пьяный матрос
		
		// belamour хороший специалист -->
		case "ExpertSailor":
			int ExpertSailorVar = 1 + hrand(2);
			dialog.text = "Grüße Kapitän! Ich weiß, du bist der Kapitän, ja.";
			link.l1 = "Grüße. Wie wissen Sie, dass ich der Kapitän bin?";
			link.l1.go = "ExpertSailor_"+ExpertSailorVar;
		break;
		
		case "ExpertSailor_1": // матрос
			dialog.text = "Ha, ich bin ein erfahrener Seewolf, ich segel seit mehr als einem Jahrzehnt auf dem Meer. Ich war hauptsächlich mit Segeln beschäftigt: segelte in der Ruhe, im Sturm, auf einem Kutter und sogar auf einem Schlachtschiff. Wahrlich, letzten Monat wurde ich nach einem harten Kampf verletzt, es gab einen starken Sturm und niemand wagte es, das Segel zu erklimmen, also tat ich es, aber ich zahlte einen Preis dafür, zum Glück verdrehte ich nur meinen Knöchel und konnte ein paar Wochen nicht laufen. Also haben sie mich an Land geschrieben. Jetzt geht es mir besser und ich sitze hier, warte auf eine Gelegenheit.";
			link.l1 = "Interessant. Ich würde mir nicht einen Spezialisten in dieser Angelegenheit wünschen. Möchtest du dich meiner Mannschaft anschließen?";
			link.l1.go = "ExpertSailor_1_1";
		break;
		
		case "ExpertSailor_1_1":
			dialog.text = "Warum nicht? Ich vermisse bereits das Schiffsdeck und das Geräusch der Segel, die mit frischem Wind gefüllt sind. Ich könnte auch dein Team trainieren, wenn nötig. Aber ich werde dich sofort um tausend Pesos bitten, sonst sind meine Taschen bereits leer. Dann wieder, wie der Rest des Teams. Ich bin eine ehrliche Person.";
			link.l1 = "Nein, ich werde wahrscheinlich ablehnen. Wenn alle Matrosen tausend Pesos für die Einstellung bezahlt bekommen, werde ich pleite gehen. Mach mir keine Vorwürfe.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "Abgemacht. Ich habe nichts gegen tausend Pesos für einen guten Spezialisten. Warte mal... hier. Und ich warte auf dich auf dem Schiff.";
				link.l2.go = "ExpertSailor_payS";
			}
		break;
		
		case "ExpertSailor_nomoney":
			DialogExit();
			NPChar.Dialog.currentnode = "ExpertSailor_Again";
		break;
		
		case "ExpertSailor_payS":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Sailors", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_2": // канонир
			dialog.text = "Ha, ich bin ein erfahrener Seewolf, ich segel schon seit mehr als einem Jahrzehnt auf dem Meer. Meistens stand ich in der Nähe der Kanonen: Schoss aus Falkonetten, aus Karren, Kartaunen, Sakers... diente auf einem Lugger und sogar auf einem Schlachtschiff. Wahrhaftig, letzten Monat wurde ich nach einem harten Kampf verwundet, ein Querschläger aus der Traubenschuss bekam mich, nichts Ernstes nur eine Schramme an meinem Bein, also schrieben sie mich an das Ufer. Jetzt geht es mir besser und ich sitze hier, warte auf eine Gelegenheit.";
			link.l1 = "Interessant. Ich könnte einen Spezialisten in dieser Angelegenheit gebrauchen. Möchtest du meinem Team beitreten?";
			link.l1.go = "ExpertSailor_2_1";
		break;
		
		case "ExpertSailor_2_1":
			dialog.text = "Warum nicht? Ich vermisse bereits das Geschützdeck, den Geruch von brennendem Schießpulver und das Donnern der Kanonensalven. Ich könnte auch dein Team coachen, wenn nötig. Aber ich werde dich sofort um tausend Pesos bitten, sonst sind meine Taschen bereits leer. Dann, wie der Rest des Teams bin ich ein ehrlicher Mann.";
			link.l1 = "Nein, ich werde wahrscheinlich ablehnen. Wenn alle Matrosen tausend Pesos für die Einstellung bezahlt bekommen, werde ich pleite gehen. Gib mir nicht die Schuld.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "Abgemacht. Ich habe nichts gegen tausend Pesos für einen guten Spezialisten. Warte mal... hier. Und ich warte auf dich auf dem Schiff.";
				link.l2.go = "ExpertSailor_payС";
			}
		break;
		
		case "ExpertSailor_payС":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Cannoners", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_3": // солдат
			dialog.text = "Ha, ich bin ein erfahrener Seewolf, ich segle schon seit mehr als einem Jahrzehnt auf dem Meer. Ich habe hauptsächlich in Entermanövern gekämpft: Ich habe gegen Piraten und reguläre Armeen gekämpft, ich weiß mit allen Arten von Waffen umzugehen, war auf einer Jolle und sogar auf einem Kriegsschiff. Zugegeben, letzten Monat wurde ich nach einem harten Kampf verwundet, es war nur ein kleiner Säbelkratzer auf meinem Rücken, der Feigling konnte mir nicht ins Gesicht sehen, aber ich habe ihn im Gegenzug getötet, oh, ihr hättet ihr Gesichter sehen sollen, als sie den Kratzer sahen ha-ha. Also, sie haben mich an Land geschrieben. Jetzt geht es mir besser und ich sitze hier und warte auf eine Gelegenheit.";
			link.l1 = "Interessant. Ich würde nicht gegen einen Spezialisten in dieser Angelegenheit einzuwenden haben. Möchtest du meiner Mannschaft beitreten?";
			link.l1.go = "ExpertSailor_3_1";
		break;
		
		case "ExpertSailor_3_1":
			dialog.text = "Warum nicht? Ich vermisse bereits das Geräusch der Säbel, das Knistern der Schiffe, die an den Seiten zusammenlaufen, und den Adrenalinschub der Schlacht. Ich könnte auch dein Team trainieren, wenn nötig. Aber ich werde dich sofort um tausend Pesos bitten, sonst sind meine Taschen schon leer. Dann, wie der Rest des Teams bin ich ein ehrlicher Mann.";
			link.l1 = "Nein, ich werde wahrscheinlich ablehnen. Wenn alle Seeleute tausend Pesos für die Einstellung bezahlt werden, werde ich pleite gehen. Mach mir keine Vorwürfe.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "Abgemacht. Ich habe nichts gegen tausend Pesos für einen guten Spezialisten. Warte mal... hier. Und ich warte auf dich auf dem Schiff.";
				link.l2.go = "ExpertSailor_payA";
			}
		break;
		
		case "ExpertSailor_payA":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Soldiers", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_Again":
			dialog.text = "Viel Glück auf See, Kapitän!";
			link.l1 = "Du auch.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ExpertSailor_Again";
		break;
		// <-- хороший специалист
		
		//belamour ночной приключенец -->
		// матрос -->
		case "NightAdventure_Sailor":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "W-wer bist du?";
			link.l1 = "Ich bin Kapitän "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Entschuldigung, Kumpel, ich habe es eilig.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_SailorTavern":          link.l1.go = "NightAdventure_Sailor_1_1"; break; // до таверны
				case "NightAdventure_SailorShuler0":         link.l1.go = "NightAdventure_Sailor_2_1"; break; // шулер
				case "NightAdventure_SailorShulerGiveMoney": link.l1.go = "NightAdventure_Sailor_2_1"; break;
				case "NightAdventure_SailorShulerGiveOk":    link.l1.go = "NightAdventure_Sailor_2_1"; break; 
				case "NightAdventure_SailorShulerFight":     link.l1.go = "NightAdventure_Sailor_2_1"; break; 
				case "NightAdventure_SailorBoat":      		 link.l1.go = "NightAdventure_Sailor_3_1"; break; // до пирса
				case "NightAdventure_SailorShip":            link.l1.go = "NightAdventure_Sailor_3_1"; break;
				case "NightAdventure_Bull":                  link.l1.go = "NightAdventure_Bull";       break; // наезд
			}
		break;
		// до таверны 
		case "NightAdventure_Sailor_1_1":
			dialog.text = "Kapitän?.. hic! K-Kapitän... bring mich zur T-Taverne... hic!.. huh? Bitte. Es scheint... ich habe mich in dieser K-Kolonie verlaufen, ja... hic! ..";
			link.l1 = "Verschwinde von mir, ich habe keine Zeit!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Gut, lass uns gehen. Sieht so aus, als könntest du nicht alleine dorthin kommen.";
			link.l2.go = "NightAdventure_Sailor_1_2";
		break;
		
		case "NightAdventure_Sailor_1_2":
			dialog.text = "Nur... hicks!.. langsam, b-bitte. Ich kann... hicks!.. nicht... stehen...";
			link.l1 = "Gut, lass uns gehen, langsam.";
			link.l1.go = "NightAdventure_Sailor_tavern";
		break;
		
		case "NightAdventure_Sailor_tavern":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = "NA_SailorTavern"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		// шулер
		case "NightAdventure_Sailor_2_1":
			dialog.text = "Kapitän?.. hic!.. K-kapitän... hilf mir!";
			link.l1 = "Komm von mir runter, ich habe keine Zeit!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Was ist los mit dir?";
			link.l2.go = "NightAdventure_Sailor_2_2";
		break;
		
		case "NightAdventure_Sailor_2_2":
			dialog.text = "Dort... in der Taverne... hic!.. der Kartenhai!";
			link.l1 = "Nun, was ist daran falsch? In jeder Taverne jeder Kolonie gibt es Kartenspieler, wie Dreck.";
			link.l1.go = "NightAdventure_Sailor_2_3";
		break;
		
		case "NightAdventure_Sailor_2_3":
			dialog.text = "C-Kapitän, Sie... verstehen nicht... hic!... Er hat m-mich... ohne einen einzigen Peso verlassen! Hic!.. Und dann... hat er mich vertrieben... hic!..";
			link.l1 = "Also, was willst du jetzt von mir?";
			link.l1.go = "NightAdventure_Sailor_2_4";
		break;
		
		case "NightAdventure_Sailor_2_4":
			dialog.text = "Komm m-mit mir... hic!... Mach mit ihm fertig! M-mach... hic!.. dass er mir mein Geld zurückgibt! hic!..";
			link.l1 = "Sie müssen kein Kartenhai sein, um eine betrunkene Person am Brett zu schlagen. Trinken Sie das nächste Mal weniger.";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Nun, wofür brauche ich das, hm? .. Na gut, gehen wir, schauen wir uns deinen Kartenhai an.";
			link.l2.go = "NightAdventure_Sailor_2_5";
		break;
		
		case "NightAdventure_Sailor_2_5":
			dialog.text = "Nur... hic!.. langsam, b-bitte. Ich kann... hic!.. nicht... stehen...";
			link.l1 = "Gut, gehen wir langsam.";
			link.l1.go = "NightAdventure_Sailor_gambler";
		break;
		
		case "NightAdventure_Sailor_gambler":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = "NA_SailorGambler"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		// диалог в таверне с матросом
		case "NA_SailorTavern":
			dialog.text = "C-Kapitän... hicks!.. vielen Dank... hast mir geholfen! Ich... hier, nimm... hicks!.. Es ist für dich.";
			link.l1 = "Komm schon, ist doch egal... Trink nicht mehr so. Oder such zumindest keine Abenteuer mehr.";
			link.l1.go = "NA_SailorTavern_1";
		break;
		
		case "NA_SailorTavern_1":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			chrDisableReloadToLocation = false;
			if(GetDataDay() < 7) AddMoneyToCharacter(pchar, 10);
			if(GetDataDay() >= 7  && GetDataDay() < 13) {GiveItem2Character(pchar, "slave_01");  Log_Info("You've received Harpoon");}
			if(GetDataDay() >= 13 && GetDataDay() < 19) {GiveItem2Character(pchar, "potion5");   Log_Info("You've received Ginger root");}
			if(GetDataDay() >= 19 && GetDataDay() < 25) {GiveItem2Character(pchar, "cartridge"); Log_Info("You've received Paper cartridge");}
			if(GetDataDay() >= 25) 
			{
				if(GetDataDay() == 25) {GiveItem2Character(pchar, "amulet_8");  Log_Info("You've received amulet 'Anchor'");}
				if(GetDataDay() == 26) {GiveItem2Character(pchar, "amulet_9");  Log_Info("You've received amulet 'Encolpion'");}
				if(GetDataDay() == 27) {GiveItem2Character(pchar, "obereg_7");  Log_Info("You've received amulet 'Fisher'");}
				if(GetDataDay() >  27) {GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			}
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// разговор про  шулера
		case "NA_SailorGambler":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShuler0")
			{
				dialog.text = "C-Kapitän!.. Der... Hic!.. Kartenhai!..";
				link.l1 = "Wer, ich? Kartenspieler?";
				link.l1.go = "NA_SailorGamblerBelka";
			}
			else	
			{
				dialog.text = "Da ist er, Kapitän! Hicks!.. S-sitzt am Tisch...";
				link.l1 = "Mach schon...";
				link.l1.go = "NA_SailorGamblerCards"; 
			}
					
		break;
		// шулер сбежал
		case "NA_SailorGamblerBelka": 
			dialog.text = "Nein... hic!... Schärfer!... Er ist verschwunden!...";
			link.l1 = "Nun, er ist gegangen, also hat er nicht auf dich gewartet.";
			link.l1.go = "NA_SailorGamblerBelka_1";
		break;
		
		case "NA_SailorGamblerBelka_1":
			dialog.text = "Und was... w-weiter? Hic!..";
			link.l1 = "Nun, es gibt nichts, was du jetzt tun könntest. Ich werde definitiv nicht nachts in der Kolonie nach ihm suchen. Trink nicht mehr so. Oder zumindest nicht spielen, während du betrunken bist.";
			link.l1.go = "NA_SailorGamblerBelka_2";
		break;
		
		case "NA_SailorGamblerBelka_2":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		// шулер остался таверне
		case "NA_SailorGamblerCards":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			iNation = npchar.nation
			iRank = MOD_SKILL_ENEMY_RATE+sti(pchar.rank);
			iScl = 15 + 2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("NightAdventure_CardProf", "citiz_"+(rand(9)+11), "man", "man", iRank, iNation, 1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_04", "pistol1", "bullet", iScl*2);
			sld.dialog.filename    = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "NightAdventure_CardProf";
			sld.greeting = "player";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			AddMoneyToCharacter(sld, sti(pchar.GenQuest.NightAdventure_money));
			GiveItem2Character(sld, "totem_13");
			FreeSitLocator(pchar.location, "sit_front4");
			ChangeCharacterAddressGroup(sld, pchar.location, "sit", "sit_front4");
			LAi_SetSitType(sld);
			chrDisableReloadToLocation = false;
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// разговор с самим шулером
		case "NightAdventure_CardProf":
			dialog.text = "Ich schlage ein Würfelspiel vor. Bist du dabei?";
			link.l1 = "Auf keinen Fall. Ich bin der Kapitän des Schiffes und ich spiele nicht mit Falschspielern. Aber ich kann dir leicht die Seiten zerquetschen, wenn du dem guten Mann dort drüben nicht das Geld zurückgibst.";
			link.l1.go = "NightAdventure_CardProf_1";
		break;
		
		case "NightAdventure_CardProf_1":
			dialog.text = "Mit Kartenhaien?! Bin ich ein Kartenhai? Wem soll ich das Geld zurückgeben, diesem Trunkenbold?! Sie beleidigen mich, Kapitän...";
			link.l1 = "Ich kann noch mehr beleidigen. Gib das Geld zurück.";
			link.l1.go = "NightAdventure_CardProf_2";
		break;
		
		case "NightAdventure_CardProf_2":
			dialog.text = "Ja, ich bin kein Kartenhai! Ich bin ein fairer Spieler. Glück gewinnt, und dein Freund hatte einfach nur Pech, das ist alles.";
			link.l1 = "Glück, hm? Gib mir deine Würfel, und ich werde sehen, wie glücklich es ausfällt.";
			link.l1.go = "NightAdventure_CardProf_3";
		break;
		
		case "NightAdventure_CardProf_3":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerGiveMoney") // отдал деньги
			{
				AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money));
				dialog.text = "In Ordnung, in Ordnung, beruhige dich, Kapitän. Nun, ich habe den Betrunkenen geschlagen und ein wenig betrogen, und das macht jeder zweite Spieler. Hier ist sein Geld.";
				link.l1 = "Das ist besser. Und, ich hoffe, Sie verstehen, dass wenn mein Freund jetzt sagt, dass dies nicht der ganze Betrag ist, dann werde ich zu Ihnen zurückkehren?";
				link.l1.go = "NightAdventure_CardProf_GiveMoney";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerGiveOk") // играл честно
			{
				dialog.text = "Ja bitte, hier sind meine Würfel. Beide Sätze. Überprüfen. Ich habe nichts zu verbergen.";
				link.l1 = "So... Paar... Nichts... Paar... Voll... Nichts... Nichts... Zwei Paare... Set... Nichts... Paar...";
				link.l1.go = "NightAdventure_CardProf_Ok";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerFight") // драка
			{
				dialog.text = "Ja bitte, hier sind meine Würfel. Beide Sets. Überprüfen Sie. Ich habe nichts zu verbergen.";
				link.l1 = "So... Vier Gleiche... Vier Gleiche... Full... Full... Vier Gleiche... Poker... Full... Poker... Vier Gleiche... Full... Hmm, und wie wirst du mir das erklären?";
				link.l1.go = "NightAdventure_CardProf_Fight";
			}
		break;
		// разошлись миром
		case "NightAdventure_CardProf_GiveMoney":
			dialog.text = "Ich verstehe alles, hier ist die ganze Summe. Viel Glück für dich und deinen Freund.";
			link.l1 = "Du auch.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_1";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_CharacterDisableDialog(npchar);
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_CardProf_GiveMoney_2";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		// матрос забирает свои деньги
		case "NightAdventure_CardProf_GiveMoney_2":
			AddMoneyToCharacter(pchar, - makeint(pchar.GenQuest.NightAdventure_money));
			dialog.text = "Aber... er wollte es nicht zugeben! Hic!..";
			link.l1 = "Ja, er hat versucht, es zu umgehen. Hier, behalte dein Geld.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_3";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_3":
			AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money)/2);
			dialog.text = "C-Kapitän... hicks!.. vielen Dank... hat mir geholfen! Ich...'kotzt an die Seite'... hier hast du... hicks!.. Es ist für dich.";
			link.l1 = "Komm schon, ugh... vergiss es... Trink nicht mehr so. Oder zumindest nicht, wenn du betrunken bist.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_4";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// играл честно
		case "NightAdventure_CardProf_Ok":
			dialog.text = "Nun? Überzeugt?";
			link.l1 = "Hmm, es scheinen wirklich gewöhnliche Würfel zu sein ...";
			link.l1.go = "NightAdventure_CardProf_Ok_1";
		break;
		
		case "NightAdventure_CardProf_Ok_1":
			dialog.text = "Ich habe es dir gesagt. Und dein Freund ist einfach betrunken. Er hat auch seine Niederlage nicht zugegeben, deshalb hat er dich hierher gebracht.";
			link.l1 = "Gut, es tut mir leid wegen des Vorfalls. Viel Glück.";
			link.l1.go = "NightAdventure_CardProf_Ok_2";
		break;
		
		case "NightAdventure_CardProf_Ok_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_CharacterDisableDialog(npchar);
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_CardProf_Ok_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		// подходит матрос
		case "NightAdventure_CardProf_Ok_3":
			dialog.text = "So... hic!.. was ist es?.. Er... hic!.. ist kein S-Schwindler?..";
			link.l1 = "Nun, es scheint, dass er fair gespielt hat.";
			link.l1.go = "NightAdventure_CardProf_Ok_4";
		break;
		
		case "NightAdventure_CardProf_Ok_4":
			dialog.text = "Und was... w-weiter? Hic!..";
			link.l1 = "Nun, es gibt nichts, was du jetzt tun kannst. Er hat dich ehrlich geschlagen. Trink nicht mehr so. Oder zumindest nicht, wenn du betrunken bist.";
			link.l1.go = "NightAdventure_CardProf_Ok_5";
		break;
		
		case "NightAdventure_CardProf_Ok_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// драка 
		case "NightAdventure_CardProf_Fight":
			dialog.text = "Glück. Du hattest einfach nur Glück, das ist alles. Glück ist eine launische Dame.";
			link.l1 = "Hmm, wirklich. Nun, dann lass uns spielen, aber denk dran, ich spiele mit diesen Würfeln!";
			link.l1.go = "NightAdventure_CardProf_Fight_1";
		break;
		
		case "NightAdventure_CardProf_Fight_1":
			dialog.text = "Diese?.. Das ist... Nein, ich möchte nicht mit dir spielen! Du hast mich beleidigt. Und überhaupt, ich bin pleite...";
			link.l1 = "Vielleicht möchtest du, dass ich jedem in dieser Taverne von deinen Würfeln erzähle? Oder zeige sie vielleicht? Und dann erzählst du ihnen von Glück. Was denkst du?";
			link.l1.go = "NightAdventure_CardProf_Fight_2";
		break;
		
		case "NightAdventure_CardProf_Fight_2":
			dialog.text = "Was?! Wer glaubst du, dass du bist?! Versuchst du, mich zu erpressen?! Ich werde dir jetzt ein paar Löcher verpassen, wenn du nicht abhaust!";
			link.l1 = "Ich würde lieber hier bleiben und jedem deine Würfel zeigen.";
			link.l1.go = "NightAdventure_CardProf_Fight_3";
		break;
		
		case "NightAdventure_CardProf_Fight_3":
			dialog.text = "Nun, komm her, Aas!";
			link.l1 = "Verliere deine Hosen nicht.";
			link.l1.go = "NightAdventure_CardProf_Fight_4";
		break;
		
		case "NightAdventure_CardProf_Fight_4":
			LAi_LocationDisableOfficersGen(pchar.location, true); // офицеров не  пускать
			SetFunctionLocationCondition("NightAdventure_Duel", Locations[FindLocation(pchar.location)].fastreload+"_town", false);
			pchar.quest.NightAdventure_KillPhant.over = "yes";
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			DialogExit();
		break;
		// матрос на выходе
		case "NightAdventure_CardProf_Fight_5":
			dialog.text = "C-Kapitän?.. Sie... hicks!.. haben sich geprügelt?.. Und dieser... hicks!.. s-schärfer?";
			link.l1 = "Er hat sich selbst geschlagen. Er wird mit niemand anderem spielen.";
			link.l1.go = "NightAdventure_CardProf_Fight_6";
		break;
		
		case "NightAdventure_CardProf_Fight_6":
			dialog.text = "Aber... er w-wollte es nicht zugeben! Hic!..";
			link.l1 = "Ja, er hat versucht, es zu vermeiden. Er hatte einfach dein Geld nicht. Wahrscheinlich ausgegeben.";
			link.l1.go = "NightAdventure_CardProf_Fight_7NM";
			link.l2 = "Ja, er hat versucht, es zu vermeiden. Hier, dein Geld.";
			link.l2.go = "NightAdventure_CardProf_Fight_7";
		break;
		
		case "NightAdventure_CardProf_Fight_7NM": // скажем, что нет денег
			ChangeCharacterComplexReputation(pchar,"nobility", -5); 
			ChangeOfficersLoyality("bad", 2); 
			dialog.text = "Und was... w-weiter? Hic!..";
			link.l1 = "Nun, es gibt nichts, was du jetzt tun kannst. Er hat dich ehrlich geschlagen. Trink nicht mehr so. Oder zumindest nicht spielen, wenn du betrunken bist.";
			link.l1.go = "NightAdventure_CardProf_Fight_End";
		break;
		
		case "NightAdventure_CardProf_Fight_7": // деньги есть
			AddMoneyToCharacter(pchar, - makeint(pchar.GenQuest.NightAdventure_money));
			ChangeCharacterComplexReputation(pchar,"nobility", 3); 
			ChangeOfficersLoyality("good", 1); 
			dialog.text = "C-Kapitän... hicks!.. vielen Dank... du hast mir geholfen! Ich...'kotzt über die Seite'... hier, nimm... hicks!.. Es ist für dich.";
			link.l1 = "Komm schon, ugh... vergiss es... Trink nicht mehr so. Oder zumindest nicht, wenn du betrunken bist.";
			link.l1.go = "NightAdventure_CardProf_Fight_End";
			AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money)/2);
		break;
		
		case "NightAdventure_CardProf_Fight_End": 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DialogExit();
			
		break;
		// проводить до пирса
		case "NightAdventure_Sailor_3_1":
			dialog.text = "Kapitän?.. hic!.. K-kapitän... begleite mich zum K-k-kai... hic!.. huh? Bitte. Ich... hic!.. m-muss zum ... Schiff... Bootsmann... wird f-fluchen... hic!.. wenn ich spät bin...";
			link.l1 = "Verpiss dich, ich habe keine Zeit!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Gut, lass uns gehen. Du scheinst nicht in der Lage zu sein, alleine dorthin zu kommen";
			link.l2.go = "NightAdventure_Sailor_3_2";
		break;
		
		case "NightAdventure_Sailor_3_2":
			dialog.text = "Nur... hic!.. langsam, b-bitte. Ich kann... hic!.. nicht... stehen...";
			link.l1 = "Gut, gehen wir langsam.";
			link.l1.go = "NightAdventure_Sailor_3_3";
		break;
		
		case "NightAdventure_Sailor_3_3":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorBoat")
			{
				pchar.GenQuest.NightAdventureNode = "NA_SailorBoat"; 
			}
			else
			{
				pchar.GenQuest.NightAdventureNode = "NA_SailorShip"; 
			}
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocatorCondition("NightAdventure_ToBoat",  npchar.City+"_town", "quest", "quest1", false)
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		// вариант просто проводить
		case "NA_SailorBoat":
			dialog.text = "C-Kapitän... hicks!.. vielen Dank... hat mir geholfen! Ich...'übergibt sich auf die Seite'... hier gehen Sie... hicks!.. Es ist für dich.";
			link.l1 = "Komm schon, ugh... vergiss es... Trink nicht mehr so. Oder zumindest such nicht mehr nach Abenteuern.";
			link.l1.go = "NA_SailorBoat_1";
		break;
		
		case "NA_SailorBoat_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			if(GetDataDay() < 7) AddMoneyToCharacter(pchar, 10);
			if(GetDataDay() >= 7  && GetDataDay() < 13)  {GiveItem2Character(pchar, "slave_01");  Log_Info("You've received Harpoon");}
			if(GetDataDay() >= 13 && GetDataDay() < 19)  {GiveItem2Character(pchar, "potion5");   Log_Info("You've received Ginger root");}
			if(GetDataDay() >= 19 && GetDataDay() < 25)  {GiveItem2Character(pchar, "cartridge"); Log_Info("You've received Paper cartridge");}
			if(GetDataDay() >= 25) 
			{
				if(GetDataDay() == 25) {GiveItem2Character(pchar, "amulet_8");  Log_Info("You've received amulet 'Anchor'");}
				if(GetDataDay() == 26) {GiveItem2Character(pchar, "amulet_9");  Log_Info("You've received amulet 'Encolpion'");}
				if(GetDataDay() == 27) {GiveItem2Character(pchar, "obereg_7");  Log_Info("You've received amulet 'Fisher'");}
				if(GetDataDay() >  27) {GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "NightAdventure_OpenLoc", -1); 
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// просится на корабль
		case "NA_SailorShip":
			dialog.text = "H-hauptmann!.. Schiff!";
			link.l1 = "Welches 'Schiff'?";
			link.l1.go = "NA_SailorShip_1";
		break;
		
		case "NA_SailorShip_1":
			dialog.text = "S-Schiff!.. Wo ist es?.. hic!..";
			link.l1 = "Offensichtlich ist er gegangen. Du musst weniger in Tavernen trinken. Das ganze Schiff wird nicht auf einen betrunkenen Seemann warten.";
			link.l1.go = "NA_SailorShip_2";
		break;
		
		case "NA_SailorShip_2":
			dialog.text = "Aber ich bin... hicks!... nicht betrunken... fast...vielleicht...";
			link.l1 = "Ach ja, in der Tat. Feines Glück.";
			link.l1.go = "NA_SailorShip_3";
		break;
		
		case "NA_SailorShip_3":
			dialog.text = "Warte, K-Kapitän! N-nimm mich... hic!.. zu deinem S-Schiff! Ich werde nicht... hic!.. m-mehr trinken...";
			if(GetFreeCrewQuantity(pchar) > 0)
			{
				link.l1 = "Gut, was kannst du dagegen tun. Aber sofort zum Schiff gehen. Und Gott bewahre, ich sehe dich irgendwo betrunken, du wirst das Deck schrubben, bis zum nächsten Hafenstopp.";
				link.l1.go = "NA_SailorShip_4";
			}
			link.l2 = "Damit du dich auf meinen Gehalt betrinkst und ich dich dann in allen Tavernen und Eingängen der Kolonie suchen muss? Nein, solches Glück brauche ich nicht.";
			link.l2.go = "NA_SailorShip_6";
			
		break; 
		
		case "NA_SailorShip_4": 
			AddCharacterCrew(pchar, 1);
			dialog.text = "Ja, K-kapitän!.. hic!..";
			link.l1 = "...";
			link.l1.go = "NA_SailorShip_5";
		break;
		
		case "NA_SailorShip_5": 
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "NightAdventure_OpenLoc", 5.0); // побежит вдохновленный 
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NA_SailorShip_6": 
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload4_back");
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "NightAdventure_OpenLoc", -1);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// пьяные наезды
		case "NightAdventure_Bull":
			switch (rand(5))
			{
				case 0:
				dialog.text = "Kapitän?.. hic!.. Du bist... Landratte... hic!.. kein Kapitän!..";
				link.l1 = "Ich habe Hunderte von Leuten wie dich in Entermanövern zerschnitten, also hau ab, Betrunkener.";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 1:
				dialog.text = "Kapitän... hic!.. K-kapitän von diesem T-Trog im Überfall?.. hic!..";
				link.l1 = "Wenn du diesen Trog am Horizont siehst, wenn du auf See bist, ist es besser, sofort ins Wasser zu tauchen: Mit Haien hast du eine bessere Überlebenschance als gegen mein Schiff. Jetzt geh weg!";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 2:
				dialog.text = "Kapitän?.. hic!.. Du bist ein Milchtrinker, kein Kapitän!.. Deine M-mutter war noch ein Mädchen... hic!.. als ich das Meer segelte...";
				link.l1 = "Aber deine Mutter wäre wahrscheinlich froh zu wissen, dass ein kleiner Junge wie ich zum Kapitän wurde, und du bliebst ein betrunkener Seemann, nur geeignet, um die Decks zu schrubben.";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 3:
				dialog.text = "Kapitän?.. Pass auf... hicks!.. Kapitän... Ich schlag dir die Zähne aus... hicks!.. du hast keine Zeit zum Blinzeln!..";
				link.l1 = "Rückstoß wird töten. Raus! Schlage meine Zähne aus, wenn du dich traust...";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 4:
				dialog.text = "Kapitän?.. Sieht aus wie... hic!.. e-eine Art Lump...";
				link.l1 = "Es sieht so aus, als hättest du dich noch nicht im Spiegel betrachtet...";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 5:
				dialog.text = "H-hauptmann?.. Ich würde... hic!.. nicht einmal zustimmen... auf Ihrem Schiff zu d-dienen... hic!..";
				link.l1 = "Und niemand hat dir angeboten, auf mein Schiff zu gehen, damit du zugestimmt hast. Geh mir aus dem Weg.";
				link.l1.go = "NightAdventure_End";
				break;
			}
		break;
		
		case "NightAdventure_End":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			NPChar.Dialog.currentnode = "NightAdventure_Again";
		break;
		
		case "NightAdventure_Again":
			NextDiag.TempNode = "NightAdventure_Again";
			dialog.text = "Hicks!..";
			link.l1 = "Geh schlafen.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_SailorAgain":
			dialog.text = "Hicks!.. Ja... noch weit?..";
			link.l1 = "Wir sind nah dran, hab Geduld.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_SailorAgain";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
		break;
		// <-- матрос
		// горожанин -->
		case "NightAdventure_Citizen":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "W-wer... hicks!.. bist du?..";
			link.l1 = "Ich bin Kapitän "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Entschuldigung, Kumpel, ich habe es eilig.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_CitizenHomie":          link.l1.go = "NightAdventure_Citizen_1_1"; break; // выручить приятеля
				case "NightAdventure_CitizenHomieSolderNM":  link.l1.go = "NightAdventure_Citizen_1_1"; break; 
				case "NightAdventure_CitizenHomieSolderGM":  link.l1.go = "NightAdventure_Citizen_1_1"; break;
				case "NightAdventure_CitizenHomieOfficer":   link.l1.go = "NightAdventure_Citizen_1_1"; break; 
				case "NightAdventure_SailorShuler0":         link.l1.go = "NightAdventure_Sailor_2_1";  break; // шулер
				case "NightAdventure_SailorShulerGiveMoney": link.l1.go = "NightAdventure_Sailor_2_1";  break;
				case "NightAdventure_SailorShulerGiveOk":    link.l1.go = "NightAdventure_Sailor_2_1";  break; 
				case "NightAdventure_SailorShulerFight":     link.l1.go = "NightAdventure_Sailor_2_1";  break; 
				case "NightAdventure_Bull":                  link.l1.go = "NightAdventure_Bull";        break;// наезд
			}
		break;
		
		// дружок
		case "NightAdventure_Citizen_1_1":
			dialog.text = "Kapitän?.. hic!.. K-kapitän... hilf mir! Ich... ich meine... hic!.. mein Freund... braucht wirklich deine H-Hilfe! Bitte.";
			link.l1 = "Ich werde nicht die Probleme jedes Betrunkenen lösen, den ich mitten in der Nacht treffe..";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Gut, erzähl mir, was mit deinem Freund dort passiert ist.";
			link.l2.go = "NightAdventure_Citizen_1_2";
		break;
		
		case "NightAdventure_Citizen_1_2":
			dialog.text = "Mein Freund ... er, im Allgemeinen ... er hat sich betrunken. Einfach so ... hicks! .. hat sich betrunken ...";
			link.l1 = "Natürlich habe ich die Seeleute, die im Dienst getrunken haben, nüchtern gemacht, aber mit ziemlich radikalen Methoden. Ich glaube nicht, dass dein Freund das braucht.";
			link.l1.go = "NightAdventure_Citizen_1_3";
		break;
		
		case "NightAdventure_Citizen_1_3":
			dialog.text = "Nein! Er... er ist mit der W-Wache! Er arrr...stritt sich mit ihnen. Und geriet in eine Schlägerei. Und er... hic!.. wurde ins Gefängnis gebracht... er ist einfach b-betrunken!";
			link.l1 = "Und was willst du jetzt von mir? Er ist selbst schuld: man sollte weniger trinken. Oder zumindest nicht alleine nach Abenteuern suchen...";
			link.l1.go = "NightAdventure_Citizen_1_4";
		break;
		
		case "NightAdventure_Citizen_1_4":
			dialog.text = "Sprechen Sie mit dem Wärter, Kap ... hicks! .. Kapitän! Er wird loslassen... lass ihn gehen! Hmm... hier ist es... hicks!.. wie glücklich du bist... Mein Freund hat gerade... argumentiert... naja... und wollte mich ins Gesicht schlagen... aber... hicks!.. bekam keine Waffe...";
			link.l1 = "Jetzt habe ich nichts anderes zu tun, als nachts Betrunkene aus dem Gefängnis zu ziehen, die sich mit den Wachen gestritten haben. Nein, lass es ein paar Tage sitzen. Vielleicht denkst du das nächste Mal darüber nach.";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Ja, zur Hölle mit dir. Gut, ich werde mit dem Wärter sprechen.";
			link.l2.go = "NightAdventure_Citizen_1_5";
			if(GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && !CheckNationLicence(HOLLAND))
			{
				link.l2 = "Ich bin mir nicht sicher, ob dem Wärter mein Akzent gefallen würde. Er wird es später dem Gouverneur melden. Also mach ohne mich weiter.";
				link.l2.go = "NightAdventure_Citizen_RE";
			}
			if(ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
			{
				link.l2 = "Ich fürchte, Freund, der Weg zu den örtlichen Kasematten ist für mich versperrt. Der Wärter hält mein Porträt wie eine Ikone, und ich habe nicht vor, mich in diesen gastfreundlichen Apartments niederzulassen. Also tut es mir leid, aber ich kann dir nicht helfen.";
				link.l2.go = "NightAdventure_Citizen_NR";
			}
		break;
		
		case "NightAdventure_Citizen_1_5":
			DialogExit();
			pchar.GenQuest.NightAdventureToJail = true;
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			chrDisableReloadToLocation = true; //закрыть локацию пока бежит
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0); 
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_CitizenHomiePresent":
			dialog.text = "D-danke... Kapitän. Und für meinen F-freund auch. H-hier... das ist für Sie.";
			link.l1 = "Nächstes Mal, behalte deinen Freund im Auge, wenn er betrunken wird und beschließt, gegen die Wachen zu kämpfen. Es ist nicht jede Nacht, dass Kapitäne die Straßen entlanglaufen, bereit, mit dem Wärter für einige Betrunkene zu verhandeln. Viel Glück.";
			link.l1.go = "NightAdventure_CitizenHomiePresent_1";
		break;
		
		case "NightAdventure_CitizenHomiePresent_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5.0);
			sld = characterFromId("NightAdventure_Homie");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			if(GetDataDay() < 7) 						{GiveItem2Character(pchar, "indian_2");  Log_Info("You've received amulet 'Gunpowder tester'");}
			if(GetDataDay() >= 7  && GetDataDay() < 13) {GiveItem2Character(pchar, "obereg_5");  Log_Info("You've received amulet 'Jade turtle'");}
			if(GetDataDay() >= 13 && GetDataDay() < 19) {GiveItem2Character(pchar, "obereg_6");  Log_Info("You've received amulet 'Monkey's fist'");}
			if(GetDataDay() >= 19 && GetDataDay() < 25) {GiveItem2Character(pchar, "obereg_8");  Log_Info("You've received amulet 'Merchant's beads'");}
			if(GetDataDay() == 25) 		    			{GiveItem2Character(pchar, "indian_9");  Log_Info("You've received amulet 'Baldo'");}
			if(GetDataDay() == 26) 	    				{GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			if(GetDataDay() >= 27 && GetDataDay() < 31) {GiveItem2Character(pchar, "obereg_4");  Log_Info("You've received amulet 'Gypsy's fan'");}
			if(GetDataDay() == 31) 	    				{GiveItem2Character(pchar, "amulet_11"); Log_Info("You've received amulet 'Cimaruta'");}
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_Citizen_RE":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)  < (rand(100)+rand(100)))
			{
				dialog.text = "Oh!.. Also ich weiß wie... hic!.. meinen... f-freund... hic!.. befreien kann!.. Wachen! Ein s-spion in der Stadt!.. hic!..";
				link.l1 = "Du hast eine sehr schlechte Option gewählt, um deinen Freund zu befreien.";
				link.l1.go = "NightAdventure_Fight";
			}
			else
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
				dialog.text = "Ach, a-ausländischer ... hicks! .. Du... du wirst Probleme haben ... hicks! .. In Ordnung... Ich habe hier ... hicks! .. alles ist unter Kontrolle.";
				link.l1 = "Natürlich. Wenn etwas passiert, komme ich sofort zu Ihnen.";
				link.l1.go = "NightAdventure_End";
			}
		break;
		
		case "NightAdventure_Citizen_NR":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetSummonSkillFromName(pchar, SKILL_FORTUNE) < (rand(100)+rand(100)))
			{
				dialog.text = "Ah ... also du ... hic! .. Du bist ein Verbrecher! Wachen!";
				link.l1 = "Ach, so redest du jetzt also!";
				link.l1.go = "NightAdventure_Fight";
			}
			else
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
				dialog.text = "Oh, wie ... hicks! .. Entschuldigung. Und was wenn... du lässt mich... für dich mit... hicks!.. dem Wärter verhandeln und du... hicks!.. für m-meinen Freund?..";
				link.l1 = "Nein, du musst nicht für mich verhandeln, danke. Viel Glück.";
				link.l1.go = "NightAdventure_End";
			}
		break;
		
		case "NightAdventure_Fight":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			LAi_group_Attack(NPChar, Pchar);
		break;
		// контрабандист 
		case "NightAdventure_Pirate": 
			LAi_RemoveLoginTime(npchar);
			dialog.text = "W-wer... hic!.. bist du?...";
			link.l1 = "Ich bin Kapitän "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Entschuldigung, Kumpel, ich habe es eilig.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_Bull":          		 link.l1.go = "NightAdventure_Bull";       break; // пьяные наезды
				case "NightAdventure_PiratePeace":           link.l1.go = "NightAdventure_PirateCave"; break; // до пещеры
				case "NightAdventure_PirateBad":             link.l1.go = "NightAdventure_PirateCave"; break;
			}
		break;
		
		case "NightAdventure_PirateCave":
			dialog.text = "Kapitän?.. hicks!.. K-kapitän... hör zu, begleite mich zur Höhle in der Nähe der Stadt... hicks!.. huh? B-bitte.";
			link.l1 = "Zur Höhle? Ich verstehe nicht. Warum gehst du zur Höhle? Und warum brauchst du mich?";
			link.l1.go = "NightAdventure_PirateCave_1";
		break;
		
		case "NightAdventure_PirateCave_1":
			dialog.text = "Sie sehen... K-Kapitän... hic!.. Ich habe kein G-Geld mehr für Getränke... Und in... hic!.. in einer Höhle habe ich... einen Vorrat, also... hic! .. Aber ich... es ist... ich habe Angst, nachts allein durch den D... D... Dschungel zu gehen... hic!.. also...";
			link.l1 = "Verpiss dich, ich habe keine Zeit!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Gut, lass uns gehen. Du scheinst nicht alleine dorthin kommen zu können";
			link.l2.go = "NightAdventure_PirateCave_2";
		break;
		
		case "NightAdventure_PirateCave_2":
			dialog.text = "Einfach... hicks!.. langsam, b-bitte. Ich kann... hicks!.. nicht... stehen...";
			link.l1 = "Gut, lass uns langsam gehen.";
			link.l1.go = "NightAdventure_PirateCave_3";
		break;
		
		case "NightAdventure_PirateCave_3":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = true; // что взяли квест
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			string NAIsland = GetIslandByCityName(npchar.city);
			string NACave = "absent. Tell belamour that you are";
			// найти пещеру на острове
			i = Findlocation(NAIsland+"_Grot");
			if(i != -1) NACave = NAIsland+"_Grot";
			i = Findlocation(NAIsland+"_Cave");
			if(i != -1) NACave = NAIsland+"_Cave";
			// для мейна и капстервиля
			i = Findlocation(npchar.city+"_Cave");
			if(i != -1) NACave = npchar.city+"_Cave";
			i = Findlocation(npchar.city+"_Grot");
			if(i != -1) NACave = npchar.city+"_Grot";
			
			log_testinfo("Cave "+NACave+" on the island " +NAIsland);
			SetFunctionLocationCondition("NightAdventure_InCave", NACave, false);
			SetFunctionLocationCondition("NightAdventure_InFort", npchar.city+"_ammo", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_PirateCave_4": // диалог в пищере
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PiratePeace")
			{
				AddMoneyToCharacter(pchar, 1000);
				TakeNItems(pchar, "potionrum", 1);   
				TakeNItems(pchar, "potionwine", 1);
				PlaySound("interface\important_item.wav");
				Log_Info("You've received an alcohol")
				dialog.text = "C-Kapitän... hicks!.. vielen Dank... haben mir geholfen! Ich... hier... hicks!.. Das ist für dich.";
				link.l1 = "Komm schon, ugh... vergiss es... Trink nicht mehr so.";
				link.l1.go = "NightAdventure_PirateCave_4_1";
				break;
			} 
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PirateBad")
			{
				dialog.text = "Ausgezeichnet, Kapitän! Ich freue mich, dass Sie zugestimmt haben.";
				link.l1 = "Nun, wo ist dein Versteck? Warte mal, es scheint, dass du nicht betrunken bist.";
				link.l1.go = "NightAdventure_PirateCave_5";
				break;
			} 
		break;
		
		case "NightAdventure_PirateCave_4_1": // мирный исход
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0); 
			SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
		break;
		
		case "NightAdventure_PirateCave_5": // драка
			dialog.text = "Ja, ich habe nicht viel getrunken, mach dir keine Sorgen um mich. Und über den Versteck ... Leute!";
			link.l1 = "...";
			link.l1.go = "NightAdventure_PirateCave_6";
		break;
		
		case "NightAdventure_PirateCave_6": 
			DialogExit();
			AddDialogExitQuestFunction("NightAdventure_PiratesInCave");
		break;
		
		case "NightAdventure_PirateCave_7": 
			dialog.text = "Leute, ich habe hier einen Vorrat gebracht. Ihr müsst ihn öffnen. Es sei denn, natürlich, dieser Vorrat öffnet sich von selbst, auf eine gute Weise. Kapitän, was denken Sie?";
			link.l1 = LinkRandPhrase("Ich denke, es wäre besser, wenn du dich bis zum Gedächtnisverlust betrinken würdest. Zumindest würdest du am Leben bleiben. Und jetzt gibt es nur noch einen Weg ... "," Ich denke, du bist überhaupt nicht gut mit deinem Kopf, da du dich entschieden hast, den Kapitän eines Kriegsschiffes auszurauben ... "," Ich denke, dass du wahrscheinlich müde vom Leben bist, da du dich entschieden hast, dies zu versuchen...");
			link.l1.go = "NightAdventure_PirateCave_8F";
			link.l2 = "Gut, ich nehme an, es ist am besten, auf gute Weise zu gehen. Und wie viel brauchst du?";
			link.l2.go = "NightAdventure_PirateCave_8A";
		break;
		
		case "NightAdventure_PirateCave_8F": 
			dialog.text = "Also, auf gute Weise werden wir das Versteck nicht öffnen?";
			link.l1 = "Ich fürchte, das war der letzte Vorrat deines Lebens.";
			link.l1.go = "NightAdventure_PirateCave_9F";
		break;
		
		case "NightAdventure_PirateCave_9F": 
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
			sld = CharacterFromID(pchar.GenQuest.NightAdventureId);
			sld.SaveItemsForDead   = true; // сохранять на трупе вещи
			sld.DontClearDead = true;  // не убирать труп через 200с
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=0 ; i < 3; i++)
			{
				sld = CharacterFromID("NAPirat_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			LAi_SetFightMode(pchar, true);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_PirateCave_8A": // испугался
			iMoney = sti(pchar.money)/3;
			dialog.text = "Ach, wir sind nicht gierig. Nur "+FindRussianMoneyString(iMoney)+"."; 
			link.l1 = "Ich fürchte, das war der letzte Vorrat deines Lebens.";
			link.l1.go = "NightAdventure_PirateCave_9F";
			link.l2 = "Gut, mach es auf deine Weise. Ich werde nie wieder einem betrunkenen Menschen helfen...";
			link.l2.go = "NightAdventure_PirateCave_9A";
		break;
		
		case "NightAdventure_PirateCave_9A": 
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_PirateCaveAgain";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false); 
			iMoney = sti(pchar.money)/3;
			AddMoneyToCharacter(pchar, -iMoney);
			AddMoneyToCharacter(npchar, iMoney);
			npchar.SaveItemsForDead   = true; // сохранять на трупе вещи
			npchar.DontClearDead = true;  // не убирать труп через 200с
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for(i=0 ; i < 3; i++)
			{
				sld = CharacterFromID("NAPirat_" + i);
				sld.dialog.currentnode = "NightAdventure_PirateCaveAgain";
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_Group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "NightAdventure_PirateCaveAgain": 
			dialog.text = "Kapitän, Sie überraschen mich mit Ihrer Großzügigkeit. Wollen Sie mehr mit uns teilen?";
			link.l1 = "Ich habe dir bereits alles gegeben. Ich gehe...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_PirateCaveAgain";
		break;
		
		// дворянин -->
		case "NightAdventure_Noble":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "W-wer... hic!.. bist du?...";
			link.l1 = "Ich bin Kapitän "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Entschuldigung, Kumpel, ich habe es eilig.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_NobleGame":             link.l1.go = "NightAdventure_NobleGame";  break; // карты
				case "NightAdventure_NobleGameDuel":         link.l1.go = "NightAdventure_NobleGame";  break; 
				case "NightAdventure_NobleWhore": 			 link.l1.go = "NightAdventure_NobleWhore"; break; // жрица
			}
		break;
		// карты
		case "NightAdventure_NobleGame": 
			dialog.text = "Kapitän?.. hic!.. oh, "+GetAddress_Form(NPChar)+" ... Es tut m-mir so leid... hicks!.. für meinen... Z-Zustand. Möchten Sie sich m-mir anschließen? hicks!.. B-bitte."; 
			link.l1 = "Entschuldigung, "+GetAddress_Form(NPChar)+", aber ich bin beschäftigt."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Beitreten? Es tut mir leid, aber ich trinke heute nicht.."; 
			link.l2.go = "NightAdventure_NobleGame_1";
		break;
		
		case "NightAdventure_NobleGame_1":
			dialog.text = "Oh, du brauchst nicht ... hic! .. zu tr-trinken! Hier ist eine Sache ... Also ... Ich habe mit meinem Freund getrunken ... Also ... Ich bin schon angetrunken ... siehst du?";
			link.l1 = "In Ordnung. Also, brauchst du Hilfe beim Ausnüchtern?";
			link.l1.go = "NightAdventure_NobleGame_2";
		break;
		
		case "NightAdventure_NobleGame_2": 
			dialog.text = "Nicht wirklich! Mir geht's gut. Jetzt will ich K-karten spielen... im Allgemeinen will ich spielen... hic!.. A-aber nicht um miserable... P-pesos... mit diesen Lumpen in... hic!.. t-Taverne... Aber mit einem echten Edelmann! hic!.. Für echte Wetten!.."; 
			link.l1 = "Entschuldigung, "+GetAddress_Form(NPChar)+", was soll ich sagen... Ich bin kein Fan von Glücksspielen. Es ist notwendig, den Seeleuten Gehälter zu zahlen, das Schiff zu warten, wissen Sie..."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Hmm, gut, lass uns spielen. Sollen wir zur Taverne gehen?"; 
			link.l2.go = "NightAdventure_NobleGame_3";
		break;
		
		case "NightAdventure_NobleGame_3": 
			dialog.text = "Fein! Nur... hic!.. langsam, b-bitte. Ich kann... hic!.. nicht... stehen..."; 
			link.l1 = "Gut, lass uns langsam gehen."; 
			link.l1.go = "NightAdventure_NobleGame_4";
		break;
		
		case "NightAdventure_NobleGame_4":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_NobleTownAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode =  "NightAdventure_NobleGame_5"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_NobleGame_5": 
			pchar.quest.NightAdventure_Intavern.over = "yes";
			FreeSitLocator(pchar.location, "sit_front4");
			FreeSitLocator(pchar.location, "sit_base4");
			dialog.text = "F-für diesen Tisch... hic!.. lass uns gehen!"; 
			link.l1 = "Gut, lass uns gehen."; 
			link.l1.go = "NightAdventure_NobleGame_6";
		break;
		
		case "NightAdventure_NobleGame_6": 
			DialogExit();
			//if(CheckAttribute(pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LAi_Fade("NightAdventure_NobleGameDialogPrep", "NightAdventure_NobleGameDialog");
		break;
		
		case "NightAdventure_NobleGame_7": 
			dialog.text = "Sie haben keine Ahnung, K-Kapitän, wie... hic!.. wie ich froh bin, einen echten Edelmann zu treffen! hic!.. In dieser Wildnis... normalerweise nur... hic!.. A-Abschaum..."; 
			link.l1 = "Ja, es ist ein Dutzend in lokalen Kolonien. Nun, sollen wir spielen?"; 
			link.l1.go = "NightAdventure_NobleGame_8";
		break;
		
		case "NightAdventure_NobleGame_8": 
			dialog.text = "Ja, lass uns spielen! Hicks!.. Welche Wetten?.."; 
			if(sti(pchar.money) > 10000)
			{
				link.l1 = "Wir spielen um 1000 Pesos."; 
				link.l1.go = "NightAdventure_NobleGame_9_1";
			}
			if(sti(pchar.money) > 20000)
			{
				link.l2 = "Wir spielen um 2000 Pesos."; 
				link.l2.go = "NightAdventure_NobleGame_9_2";
			}
			link.l3 = "Hmm, es tut mir leid, es scheint, meine Tasche ist im Moment leer..."; 
			link.l3.go = "NightAdventure_NobleGame_Голодранец";
		break;
		
		case "NightAdventure_NobleGame_Голодранец": 
			dialog.text = "W-was?.. Du hast... hic!.. kein Geld um mit... mit mir zu spielen?.."; 
			link.l1 = "Nun, es passiert. Wir werden das nächste Mal spielen, mach dir keine Sorgen."; 
			link.l1.go = "NightAdventure_NobleGame_Голодранец_1";
		break;
		
		case "NightAdventure_NobleGame_Голодранец_1": 
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			chrDisableReloadToLocation = false; // открыть локацию
			LAI_SetPlayerType(pchar);           
			DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;
		
		case "NightAdventure_NobleGame_9_1": 
			DialogExit();
			npchar.money = 15000;
			pchar.questTemp.NA.Cards = true; 
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = 1000; 
			LaunchCardsGame();
		break;
		
		case "NightAdventure_NobleGame_9_2": 
			DialogExit();
			npchar.money = 30000;
			pchar.questTemp.NA.Cards = true; 
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = 2000; 
			LaunchCardsGame();
		break;
		
		case "NightAdventure_NobleGame_Win": 
			DeleteAttribute(pchar, "questTemp.NA.Cards.Win");
			dialog.text = "Hicks!.. Hatte eine großartige Zeit, K-Kapitän! hicks!.."; 
			link.l1 = "Ich stimme Ihnen zu. Machen Sie zumindest eine Pause vom Geschäft."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd";
		break;
		
		case "NightAdventure_NobleGame_Lose": 
			DeleteAttribute(pchar, "questTemp.NA.Cards.Fail");
			dialog.text = "Hicks!.. Hatte eine tolle Zeit, K-kapitän! hicks!.."; 
			link.l1 = "Ich stimme dir zu. Machen Sie zumindest eine Pause vom Geschäft."; 
			link.l1.go = "NightAdventure_NobleGame_Lose_1";
		break;
		
		case "NightAdventure_NobleGame_Lose_1": 
			dialog.text = "Manchmal muss man einfach... hic!.. Zeit mit einer netten... hic!.. Gesellschaft verbringen. Vielen Dank... hic!.. für deine Gesellschaft!"; 
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleGameDuel")
			{		
				link.l1 = "Ja, ich habe gerade in Scherben verloren. Und wie ist es passiert, dass du sogar in den Fällen gewonnen hast, in denen ich jede Chance hatte zu gewinnen?"; 
				link.l1.go = "NightAdventure_NobleGame_Duel";
				break;
			}	
			link.l1 = "Gegenseitig, danke für das Spiel und für das Gespräch."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
		break;
		
		case "NightAdventure_NobleGame_HappyEnd": 
			dialog.text = "Manchmal muss man einfach... hic!.. Z-Zeit mit netter... hic!.. Gesellschaft verbringen. Vielen Dank... hic!.. für deine Gesellschaft!"; 
			link.l1 = "Gegenseitig, danke für das Spiel und für das Gespräch."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
		break;
		
		case "NightAdventure_NobleGame_HappyEnd_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.NA.Cards");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			chrDisableReloadToLocation = false; // открыть локацию
			LAI_SetPlayerType(pchar);           
			DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;
		
		case "NightAdventure_NobleGame_Duel": 
			dialog.text = "Nur Glück, K-Kapitän... Schluckauf!.."; 
			link.l1 = "Es sieht nicht nur nach Glück aus...."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_1";
		break;
		
		case "NightAdventure_NobleGame_Duel_1": 
			dialog.text = "Was willst du damit andeuten? Willst du etwa sagen, dass ich unehrlich gespielt habe? Du hast selbst alles gesehen, wir haben Karten aus demselben Stapel genommen!"; 
			link.l1 = "Ja, ich habe gesehen. Und ich habe auch gesehen, dass deine Zunge vor einer Minute kaum bewegt hat, und jetzt sprichst du, als ob du nicht betrunken bist."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_2";
		break;
		
		case "NightAdventure_NobleGame_Duel_2": 
			dialog.text = "Ach, verdammt! Und du hast mich gut erwischt! Gut, ich gebe zu, ich werde mich nicht verstecken. Ich war nicht betrunken. Aber weißt du, wie gut die Leute auf diese angeblich reichen und betrunkenen Leute hereinfallen, die Karten spielen wollen? Jeder, der etwas zu setzen hat, läuft fast zuerst zur Taverne, um schnell einen zweifellos großen Gewinn von einem zweifellos reichen, aber betrunkenen Adligen zu erzielen. Lass mich sagen, dass du der Erste bist, der mich durchschaut hat."; 
			link.l1 = "Also, was jetzt? Gibst du mir mein Geld auf eine gute Weise zurück?"; 
			link.l1.go = "NightAdventure_NobleGame_Duel_3";
		break;
		
		case "NightAdventure_NobleGame_Duel_3": 
			dialog.text = "Ha ha ha, bring mich nicht zum Lachen, Kapitän. Natürlich werde ich dir nichts zurückerstatten! Und denk nicht, dass du mich dazu bringen kannst. Ich kann leicht einen respektierten Adligen darstellen, der von irgendeinem herumstreunenden Kapitän angepflaumt wird. Also mein Rat an dich ist: Akzeptiere deine Niederlage und geh einfach weg."; 
			link.l1 = "Nun, ich wünsche Ihnen aufrichtig, dass Sie nicht unter weniger glücklichen Umständen von mir erwischt werden, denn dann werden Sie nicht mehr so lachen. Auf Wiedersehen."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
			link.l2 = "Und mein Rat an dich, versuche die Zeit zu finden, um ein Schwert zu bekommen."; 
			link.l2.go = "NightAdventure_NobleGame_Duel_4";
		break;
		
		case "NightAdventure_NobleGame_Duel_4": 
			dialog.text = "Du würdest nicht wagen... Es ist eine Taverne, voller Menschen..."; 
			link.l1 = "Also ich bin nur ein streunender Kapitän, was kümmern mich die Regeln der Anständigkeit. Und in der Hafentaverne in der Nacht, was kann passieren ... Ich führe in jeder Hinsicht besser ein Schwert als du."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_5";
		break;
		
		case "NightAdventure_NobleGame_Duel_5": 
			dialog.text = "Ach so ist das?! Nun, jetzt werden wir überprüfen, wer es besser besitzt!"; 
			link.l1 = "Zu Euren Diensten..."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_6";
		break;
		
		case "NightAdventure_NobleGame_Duel_6": 
			DeleteAttribute(pchar, "questTemp.NA.Cards");
			SetFunctionLocationCondition("NightAdventure_KillPhant", NPChar.City+"_town", false);
			npchar.money = 0;
			AddMoneyToCharacter(npchar, makeint(pchar.GenQuest.NightAdventure_money));
			GiveItem2Character(npchar, "totem_13");
			npchar.SaveItemsForDead   = true; // сохранять на трупе вещи
			npchar.DontClearDead = true;  // не убирать труп через 200с
			chrDisableReloadToLocation = false; // открыть локацию
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			DialogExit();
		break;
		// жрица
		case "NightAdventure_NobleWhore": 
			dialog.text = "Kapitän?.. hic!.. oh, "+GetAddress_Form(NPChar)+" ... i-ich bin so s-sorry... hic!.. für meinen... Zustand. K-können Sie mir helfen? hic!.. B-bitte."; 
			link.l1 = "Entschuldigung, "+GetAddress_Form(NPChar)+", aber ich bin beschäftigt."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Ach... ich höre zu."; 
			link.l2.go = "NightAdventure_NobleWhore_1";
		break;
		
		case "NightAdventure_NobleWhore_1": 
			dialog.text = "Es ist so eine Sache... Im Allgemeinen... Ich bin... schon angetrunken... Du kannst sehen... hic!.. ja?"; 
			link.l1 = "Um ehrlich zu sein, ja. Brauchst du Hilfe beim Nüchternwerden?"; 
			link.l1.go = "NightAdventure_NobleWhore_2";
		break;
		
		case "NightAdventure_NobleWhore_2": 
			dialog.text = "Nicht wirklich! Ich bin g-gut. Ich möchte eine Dame. Aber ich bin so b-betrunken... hic!.. Die M-madam wird mich rauswerfen, also. Könntest du... hic!... für mich v-verhandeln? Ich werde Geld geben."; 
			link.l1 = "Es tut mir leid, "+GetAddress_Form(NPChar)+", aber wie kann ich dir sagen... Ich gehe nicht zu Bordellen. Ehre, Ruf... du verstehst ..."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Oh, gut, ich helfe dir."; 
			link.l2.go = "NightAdventure_NobleWhore_3";
		break;
		
		case "NightAdventure_NobleWhore_3": 
			dialog.text = "Nur... hic!.. langsam, b-bitte. Ich kann... hic!.. nicht... stehen..."; 
			link.l1 = "Gut, lass uns langsam gehen."; 
			link.l1.go = "NightAdventure_NobleWhore_4";
		break;
		
		case "NightAdventure_NobleWhore_4":
			DialogExit();
			if(npchar.city != "Charles" || npchar.city != "Tortuga") // вход только с парадного
			{
				LocatorReloadEnterDisable(npchar.city+"_town", "reload91", true);
			}
			NPChar.Dialog.currentnode = "NightAdventure_NobleTownAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventure_money = 3000+(rand(4)*500);
			pchar.GenQuest.NightAdventureNode =  "NightAdventure_NobleWhore_5"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_InBrothel", npchar.City+"_Brothel", false);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_NobleWhore_5": 
			pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleWhoreMoney";
			AddMoneyToCharacter(pchar, 5000);
			dialog.text = "Hier ist das Geld... hic!... Ich werde auf dich h-hier warten."; 
			link.l1 = "Gut, ich komme bald zurück."; 
			link.l1.go = "NightAdventure_NobleWhore_6";
		break;
		
		case "NightAdventure_NobleWhore_6": 
			LAi_SetCitizenType(npchar);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload1_back", true); 
			LocatorReloadEnterDisable(npchar.city + "_SecBrRoom", "reload2", true); 
			NPChar.Dialog.currentnode = "NightAdventure_NobleBrothelAgain";
			dialog.text = "N-nur... bring mir... hic!.. das... beste!.. Ja..."; 
			link.l1 = "Gut, in Ordnung, ich habe es verstanden."; 
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleWhore_7": // заказ исполнен
			dialog.text = "Hicks!.. Wie lange noch?"; 
			link.l1 = "Das beste Mädchen dieser Kolonie wartet oben auf dich."; 
			link.l1.go = "NightAdventure_NobleWhore_8";
		break;
		
		case "NightAdventure_NobleWhore_8": 
			dialog.text = "Ja!.. Dieser Abend... ist großartig... D-danke dir, "+GetAddress_Form(NPChar)+". Der Rest des Geldes... hic!... nimm es. Und ich versinke ... in... meiner..... schööönen... Geliebten...";
			link.l1 = "Nun, hab eine gute Zeit."; 
			link.l1.go = "NightAdventure_NobleWhore_9";
		break;
		
		case "NightAdventure_NobleWhore_9": 
			DialogExit();
			chrDisableReloadToLocation = true; // закрыть пока бежит
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "", "", "", "NightAdventure_OpenBrothel", -1);
		break;
		
		case "NightAdventure_NobleBrothelAgain":
			NextDiag.TempNode = "NightAdventure_NobleBrothelAgain";
			dialog.text = "Hicks!.. Wie lange noch?";
			link.l1 = "Ich werde bald verhandeln, hab Geduld.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleEnd":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			NPChar.Dialog.currentnode = "NightAdventure_NobleEndAgain";
		break;
		
		case "NightAdventure_NobleEndAgain":
			NextDiag.TempNode = "NightAdventure_NobleEndAgain";
			dialog.text = "Hicks!..";
			link.l1 = "Du musst schlafen.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleTownAgain":
			dialog.text = "Hicks!.. Ja... ist es noch weit?..";
			link.l1 = "Wir sind fast da, sei geduldig.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_SailorAgain";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
		break;
		// <-- ночной приключенец
		
		// belamour квест на получение фонаря Xenon -->
		case "CemeteryMan":
			dialog.text = "Hä? Wer bist du? Was machst du hier?";
			link.l1 = "Ich könnte Ihnen dasselbe fragen.";
			link.l1.go = "CemeteryMan_1";
		break;
		
		case "CemeteryMan_1":
			dialog.text = "Wir? Oh, wir... äh... Wir sammeln hier Blumen...";
			link.l1 = "Grabblumen? Nun, wie sieht das Herbarium aus?";
			link.l1.go = "CemeteryMan_2";
		break;
		
		case "CemeteryMan_2":
			dialog.text = "Ihr... Hat es etwas mit Kräutern zu tun?";
			link.l1 = "Also... Ich glaube, ich verstehe, was hier vor sich geht.";
			link.l1.go = "CemeteryMan_3";
		break;
		
		case "CemeteryMan_3":
			dialog.text = "Wir sind keine Plünderer! Redet nicht so über uns! Wir sind nur...";
			link.l1 = "Nur was?";
			link.l1.go = "CemeteryMan_4";
		break;
		
		case "CemeteryMan_4":
			dialog.text = "Nun, wir... Mein Vater verbietet uns, uns zu sehen! Und ihr Vater auch! Also haben wir... wir haben nach einem Ort ohne Zeugen gesucht. Um alleine zu sein. Das Schloss an der Tür ist sowieso kaputt, also ist es einfach, hier reinzukommen...";
			link.l1 = "Ich sehe jetzt, was diese gruseligen Stöhnen der unruhigen Seele waren...";
			link.l1.go = "CemeteryMan_5";
		break;
		
		case "CemeteryMan_5":
			DialogExit();
			sld = characterFromId("CemeteryCouple_2");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "CemeteryMan_6":
			dialog.text = "Nun, wenn du alles herausgefunden hast, vielleicht lässt du uns dann in Ruhe?";
			link.l1 = "Hast du keine Angst, deine Verabredungen in einer Gruft zu arrangieren? Nicht der beste Ort...";
			link.l1.go = "CemeteryMan_7";
		break;
		
		case "CemeteryMan_7":
			dialog.text = "Wir sind nicht abergläubisch! Und selbst wenn es gruselig wäre - welche Wahl haben wir? In der Stadt hätten die Eltern sofort davon erfahren. Aber hier wird uns niemand verpetzen. Also ist es vorerst die beste Option.";
			link.l1 = "Es tut mir wirklich leid, aber könnten Sie einen anderen Ort suchen? Verstehen Sie mich nicht falsch, ich verstehe alles - die Jugend und all das - aber Ihre Verabredungen haben den Friedhofswächter zu Tode erschreckt, wegen all dem Lärm und den Stöhnen, die jede Nacht aus der Gruft kommen.";
			link.l1.go = "CemeteryMan_8";
		break;
		
		case "CemeteryMan_8":
			dialog.text = "Nun... Den Wächter zu erschrecken war nicht Teil unseres Plans. Aber wo sonst könnten wir uns treffen? Oder schlägst du vor, wir verabreden uns unter freiem Himmel?";
			link.l1 = "Liebe kennt keine Grenzen. Finden Sie einen anderen Ort, an dem Sie definitiv niemanden stören werden. Dann wird dich auch niemand stören. Wahrscheinlich. Und es ist besser, die Dinge mit deinen Eltern zu klären - du planst doch nicht, dich für immer zu verstecken, oder?";
			link.l1.go = "CemeteryMan_9";
		break;
		
		case "CemeteryMan_9":
			dialog.text = "Fine, we'll think of something... We won't be scaring the guard anymore; you have my word.";
			link.l1 = "Wunderbar. Viel Glück dir!";
			link.l1.go = "CemeteryMan_10";
		break;
		
		case "CemeteryMan_10":
			sld = characterFromId("CemeteryCouple_1");
			sld.lifeDay = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("CemeteryCouple_2");
			sld.lifeDay = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			pchar.questTemp.Lantern = "ToKeeper";
			DeleteAttribute(pchar,"questTemp.Lantern.nation");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddQuestRecord("NoiseCemetery", "2");
			DialogExit();
		break;
		
		case "CemeteryGirl":
			dialog.text = "Was?!";
			link.l1 = "Ach, nichts...";
			link.l1.go = "CemeteryGirl_1";
		break;
		
		case "CemeteryGirl_1":
			DialogExit();
			sld = characterFromId("CemeteryCouple_1");
			sld.dialog.currentnode = "CemeteryMan_6";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		// <-- квест на получение фонаря 

		//замечание по обнажённому оружию от персонажей типа citizen // лесник вставил в ген.квесты чтобы не было пустого диалога .
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin ein Bürger dieser Stadt und ich bitte dich, dein Schwert niederzuhalten.","Hör zu, ich bin Bürger dieser Stadt und ich bitte dich, dein Schwert niederzuhalten.");
			link.l1 = LinkRandPhrase("Gut.","Wie du wünschst...","Wie du sagst...");
			link.l1.go = "exit";
		break;																																																				  
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;
	}
}

void ChurchGenQuest2_GiveCup()
{
	AddItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	rItem.Name = "itmname_ChurchGenQuest2Cup"; // rItem.Name = "itmname_bible";
	rItem.City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen");
	rItem.Weight = 15.0; // rItem.Weight = 2;
	rItem.picIndex = 13; // itm.picIndex = 6;
	rItem.picTexture = "ITEMS_31"; // itm.picTexture = "ITEMS_9";
	ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest2Cup");
}

// Для генера "Пираты на необитаемом острове"
String PiratesOnUninhabited_GetStringNum(int _num)
{
	String retValue = "";
	
	switch(_num)
	{
		case 5: retValue = "five"; break;
		case 6: retValue = "six"; break;
		case 7: retValue = "seven"; break;
		case 8: retValue = "eight"; break;
		case 9: retValue = "nine"; break;
		case 10: retValue = "ten"; break;
	}
	
	return retValue;
}

int PiratesOnUninhabited_GenerateShipType()
{
	int rank = sti(PChar.rank);
	int retShipType;
	
	if(rank < 5)
	{
		switch(hrand(1))
		{
			case 0: retShipType = SHIP_LUGGER; break;
			case 1: retShipType = SHIP_SLOOP; break;
		}
	}
	
	if(rank >= 5 && rank < 20)
	{
		switch(hrand(3))
		{
			case 0: retShipType = SHIP_SLOOP; break;
			case 1: retShipType = SHIP_BRIGANTINE; break;
			case 2: retShipType = SHIP_SCHOONER_W; break;
			case 3: retShipType = SHIP_BRIG; break;
		}
	}
	
	if(rank >= 20)
	{
		switch(hrand(2))
		{
			case 0: retShipType = SHIP_CORVETTE; break;
			case 1: retShipType = SHIP_GALEON_H; break;
			case 2: retShipType = SHIP_FRIGATE; break;
		}
	}
	
	return retShipType;
}

String PiratesOnUninhabited_GenerateTreasureShore(ref _boxId)
{
	String retShoreId;
	
	switch(hrand(4))
	{
		case 0:
			retShoreId = "Shore9";
			_boxId = "box1";
		break;
		
		case 1:
			retShoreId = "Shore55";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	
		case 2:
			retShoreId = "Shore_ship1";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 3:
			retShoreId = "Shore_ship2";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 4:
			retShoreId = "Shore_ship3";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	}
	
	return retShoreId;
}

void PiratesOnUninhabited_SetCapToMap()
{
	int temp;
	String group = "PiratesOnUninhabited_SeaGroup";
	ref character = GetCharacter(NPC_GenerateCharacter("PiratesOnUninhabited_BadPirate", "", "man", "man", sti(pchar.rank) + 5, PIRATE, -1, true, "soldier"));		
	character.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType), true, character);
	character.Ship.Name = PChar.GenQuest.PiratesOnUninhabited.StartShipName;
    SetBaseShipData(character);
    SetCrewQuantityFull(character);
    Fantom_SetCannons(character, "pirate");
    Fantom_SetBalls(character, "pirate");
	Fantom_SetUpgrade(character, "pirate");
	
	character.Ship.Mode = "pirate";	
	SetCaptanModelByEncType(character, "pirate");

	DeleteAttribute(character, "SinkTenPercent");
	DeleteAttribute(character, "SaveItemsForDead");
	DeleteAttribute(character, "DontClearDead");
	DeleteAttribute(character, "AboardToFinalDeck");
	DeleteAttribute(character, "SinkTenPercent");
	
	character.AlwaysSandbankManeuver = true;
	character.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	character.DontRansackCaptain = true; //не сдаваться
	
	SetAllPerksToChar(character, false);
	
	Group_FindOrCreateGroup(group);
	Group_SetTaskAttackInMap(group, PLAYER_GROUP);
	Group_LockTask(group);
	Group_AddCharacter(group, character.id);
	Group_SetGroupCommander(group, character.id);
	SetRandGeraldSail(character, PIRATE);
	
	character.fromCity = SelectAnyColony(""); // Колония, из бухты которой выйдет
	character.fromShore = GetIslandRandomShoreId(GetArealByCityName(character.fromCity));
	character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придёт
	character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
	
	character.mapEnc.type = "trade";
	character.mapEnc.worldMapShip = "quest_ship";
	character.mapEnc.Name = LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'";
	
	Map_CreateTrader(character.fromShore, character.toShore, "PiratesOnUninhabited_BadPirate", GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)) + 3);
	
	temp = GetCharacterFreeSpace(character, GOOD_SLAVES); // Сколько влезет рабов
	AddCharacterGoodsSimple(character, GOOD_SLAVES, makeint(temp / 2 + hrand(temp / 2)) - 1);
	
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1 = "Character_sink";
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1.character = "PiratesOnUninhabited_BadPirate";
	PChar.Quest.PiratesOnUninhabited_ShipSink.function = "PiratesOnUninhabited_ShipSink";
	
	Log_TestInfo("Pirates on an uninhabited island: cap left " + character.fromCity + " and went to: " + character.toShore);
}
// belamour gen количество каторжан прописью -->
String Convict_GetStringNum(int iCQTY)
{
	String ConvictStr = "";
	
	switch(iCQTY)
	{
		case 2: ConvictStr = "two"; break;
		case 3: ConvictStr = "three"; break;
		case 4: ConvictStr = "four"; break;
		case 5: ConvictStr = "five"; break;
		case 6: ConvictStr = "six"; break;
		case 7: ConvictStr = "seven"; break;
	}
	
	return ConvictStr;
}
// <-- gen
