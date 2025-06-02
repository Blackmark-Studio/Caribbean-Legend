// диалог прочих и малозначимых НПС
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp;
	string attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Gibt es etwas, das du brauchst?";
			link.l1 = "Nein, jetzt gerade nicht.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> матрос на корабле, прибытие в Сен-Пьер
		case "Startsailor":
			dialog.text = "Verdammt meine Augen, endlich Land! Wach auf, Monsieur... wie auch immer dein Name ist... Wir sind angekommen!";
			link.l1 = "A-ah! Ist es schon Morgen? Was ist das für eine verdammte Hitze und Feuchtigkeit?";
			link.l1.go = "Startsailor_1";
			link.l2 = "Ich sage! Charles de Maure! Ein Adliger, wissen Sie. Wie können Sie bei dieser Hitze trinken? Ich hätte lieber etwas Wasser, um Himmels willen.";
			link.l2.go = "Startsailor_1a";
		break;
		
		case "Startsailor_1":
			dialog.text = "Gewöhnen Sie sich daran, Monsieur. Das ist das einzige Wetter, das wir hier haben... es könnte immer schlimmer sein.";
			link.l1 = "Wie könnte es noch schlimmer werden!? Ich trage nur ein Leinenhemd und mir läuft der Schweiß den Rücken runter!";
			link.l1.go = "Startsailor_2";			
		break;
		
		case "Startsailor_2":
			dialog.text = "Sie werden sehen, haha! Es könnte Hurrikansaison sein! Beeilen Sie sich, Monsieur. Das Beiboot wird nicht auf Sie warten. Sie wollen doch nicht nach Martinique schwimmen, oder?";
			link.l1 = "Geben Sie mir einen Moment, ja? Wo ist mein Schwert? Ah, hier ist es...";
			link.l1.go = "Startsailor_3";			
		break;
		
		case "Startsailor_3":
			dialog.text = "Sie sind nicht mehr in Europa... Seien Sie vorsichtig, Monsieur. Dies sind unruhige Zeiten. Gerüchten zufolge hat die Gesellschaft der amerikanischen Inseln die Insel Martinique an einige religiöse Fanatiker, Kreuzritter oder so einen Unsinn verkauft. Ich habe zumindest vom Deck aus noch nichts Ungewöhnliches bemerkt. Aber da wir eine Weile weg waren, könnte sich in meiner Abwesenheit viel verändert haben.";
			link.l1 = "Kreuzritter? Unsinn!";
			link.l1.go = "Startsailor_4";			
		break;
		
		case "Startsailor_4":
			dialog.text = "Ob es Unsinn ist oder nicht, Gerüchte sind weit verbreitet. Wir haben schon genug Ärger wie es ist. Kannibalen im Dschungel, tropisches Fieber, Piraten, Banditen in den Gassen, ganz zu schweigen von den Spaniern und Engländern...";
			link.l1 = "Oh, da gehen wir wieder... Im Moment sehe ich nur die drückende Hitze und Moskitos als Ärger... Gut, ich bin bereit. Sollen wir gehen?";
			link.l1.go = "Startsailor_5";			
		break;
		
		case "Startsailor_5":
			dialog.text = "Geht an Deck und steigt in das Beiboot, Monsieur. Willkommen in der Karibik!";
			link.l1 = "";
			link.l1.go = "Startsailor_6";			
		break;
		
		case "Startsailor_1a":
			dialog.text = "Es gibt hier kein anderes Wetter, 'Eure Lordschaft'. Wenn überhaupt, wird es nur schlimmer.";
			link.l1 = "Das Wetter ist unerträglich, ebenso wie meine Gesellschaft in den letzten Monaten. Ich hoffe, auf dem Archipel gibt es ein paar anständige Leute.";
			link.l1.go = "Startsailor_2a";
			AddCharacterExpToSkill(pchar, "Leadership", 10);
		break;
		
		case "Startsailor_2a":
			dialog.text = "Nun, dann denke ich, werden wir alle froh sein, Sie endlich verabschieden zu können, Monsieur. Das Boot wartet. Springen Sie vor Freude nicht aus Ihrer Hose. Und vergessen Sie nicht Ihre Habseligkeiten - das Schiff fährt weiter, und Sie könnten sie genauso gut vergessen, wenn Sie es nicht tun.";
			link.l1 = "Als ob ich sie zu deinem Vergnügen lassen würde. Pesos, Schwert - es scheint, ich bin nicht ausgeraubt worden.";
			link.l1.go = "Startsailor_3a";			
		break;
		
		case "Startsailor_3a":
			dialog.text = "Wir sind natürlich ehrliche Leute, aber du denkst richtig - behalte immer ein Auge auf deine Sachen, oder jemand könnte deine Taschen leeren. Genau wie im alten Europa. Oder überall, wirklich. Aber dieser Ort ist nicht wie zu Hause. Einige Fanatiker haben hier eine Basis eingerichtet. Man sagt, sie hätten heimlich die ganze Insel gekauft. Also, bleib wachsam und ziehe keine Aufmerksamkeit auf dich.";
			link.l1 = "Welcher Unsinn!";
			link.l1.go = "Startsailor_4a";			
		break;
		
		case "Startsailor_4a":
			dialog.text = "Das ist das Gerücht. Sei dankbar, dass ich mich überhaupt bemüht habe, es zu teilen und mich um deinen Aufenthalt hier zu kümmern. Andernfalls könnte deine zarte Gascogne-Rose unter unserer brennenden Sonne welken. Unsinn oder nicht, behalte deinen Verstand bei dir - wir haben genug Ärger ohne die Fanatiker. Banditen in den Gassen und im Dschungel, Piraten auf See und rot-häutige Kannibalen...";
			link.l1 = "Jetzt, jetzt! Ich werde es schon schaffen. Es mag für mich jetzt ein bisschen heiß sein, aber ich bin zu Hause sonnenverhärtet, im Gegensatz zu, sagen wir, diesen Normannen. Und wenn irgendetwas mit einem Schwert gelöst werden kann, kannst du auf mich zählen. Aber die Mücken - das ist reine Qual! Nun, all meine Sachen sind vorhanden. Das Boot ist bereit, sagst du?";
			link.l1.go = "Startsailor_5a";			
		break;
		
		case "Startsailor_5a":
			dialog.text = "Warten Sie gespannt. Hoffen Sie, dass Sie es selbst schaffen können, Monsieur? Kopf hoch, und hoffentlich verirren Sie sich von dort nicht. Oh, und willkommen im Archipel, heh-heh.";
			link.l1 = "Ja, danke. Der einzige Trost ist, dass ich nicht lange hier sein werde.";
			link.l1.go = "Startsailor_6";			
		break;
		
		case "Startsailor_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		// <-- матрос на корабле, прибытие в Сен-Пьер
		
		// горожанин знает Мишеля
		case "Benuatalker":
			DelLandQuestMark(npchar);
			link.l1 = "Entschuldigen Sie, "+GetAddress_FormToNPC(NPChar)+", könnten Sie mir sagen, wo ich Michel de Monper finden kann? Er muss irgendwo in Ihrer Stadt sein.";
            link.l1.go = "Benuatalker_1";
		break;
		
		case "Benuatalker_1":
			dialog.text = "Hmm... Ich sehe, dass du erst kürzlich hierher gekommen bist, da du so furchtlos solche Fragen stellst... Ich rate dir, damit aufzuhören, sonst bekommst du Ärger. Und zu deiner Frage... Sprich mit dem Abt. Du kannst ihn in der Kirche finden.";
			link.l1 = "Danke dir!";
            link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddDialogExitQuest("Sharlie_SetBenua");
			QuestPointerToLoc("FortFrance_town", "reload", "reload7_back");
		break;
		
		// --> арест в резиденции
		case "Sharlie_arest":
			dialog.text = "Halt! Übergeben Sie sofort Ihre Waffen, Monsieur, und folgen Sie uns!";
			link.l1 = "Was zum Teufel ist das?";
			link.l1.go = "Sharlie_arest_1";
			if (CheckCharacterItem(PChar, "knife_03")) pchar.Sharlie.KnifeMonpe = true;
		break;
		
		case "Sharlie_arest_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("FortFrance_prison", "goto", "goto9", "Puancie_InJail");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveAllCharacterItems(PChar, true);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "Puancie_Jail"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "FortFrance_prison", "goto", "goto13");
		break;
		// арест в резиденции
		
		// --> офицер базы
		case "Maltie_officer":
			ref location = &Locations[FindLocation(pchar.location)];
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "begin")
			{
				dialog.text = "Gut Sie zu sehen, Monsieur de Maure. Was ist der Anlass?";
				link.l1 = TimeGreeting()+", Offizier. Ich möchte mit meinem Bruder, Michel de Monper, sprechen. Natürlich offiziell. Ich versuche, etwas über seinen Dienst hier in der Karibik herauszufinden.";
				link.l1.go = "spanish";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
			{
				dialog.text = "Wie lief das Verhör? Haben Sie etwas Wertvolles gefunden?";
				link.l1 = "Oh ja. So sehr, dass ich diesen Spanier mit auf mein Schiff nehme. Er ist ein wichtiger Zeuge und muss zur weiteren Befragung nach St. Christopher gebracht werden.";
				link.l1.go = "spanish_10";
				break;
			}
			if (!CheckAttribute(location, "first_meeting"))
			{
				dialog.text = "Was haben Sie hier zu schaffen, Monsieur?";
				link.l1 = "Ich bin gekommen, um meinen Bruder, Michel de Monper, zu sehen.";
				link.l1.go = "Maltie_officer_1";
				location.first_meeting = true;
			}
			else
			{
				dialog.text = "Herr, ich muss Sie sanft daran erinnern, dass Sie sich in einem Militärlager befinden. Verhalten Sie sich entsprechend.";
				link.l1 = "Ja, Herr. Natürlich.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
			
			if (SandBoxMode)
			{
				dialog.text = "Herr, ich muss Sie sanft daran erinnern, dass Sie sich in einem Militärlager befinden. Verhalten Sie sich entsprechend.";
				link.l1 = "Ja, Herr. Natürlich.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
		break;
		
		case "Maltie_officer_1":
			DelLandQuestMark(npchar);
			dialog.text = "Michel de Monper wird derzeit in einer unserer Kasematten unter Bewachung gehalten, auf persönlichen Befehl des Ritters Philippe de Poincy. Geht nach unten zur unteren Ebene. Dort findet ihr die Kasematten, die wir für Lagerung und Zellen verwenden. Ich denke, ihr könnt euren Weg finden.";
			link.l1 = "Danke!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_officer";
			QuestPointerToLoc("FortFrance_Dungeon", "quest", "quest1");
		break;
		// офицер базы
		
		// --> солдаты базы
		case "Maltie_soldier":
			dialog.text = "Hallo, Monsieur. Kann ich Ihnen bei etwas helfen?";
			link.l1 = "Danke, Soldat, aber nein, mir geht es ganz gut. Mach weiter.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_soldier";
		break;
		// --> солдаты базы
		
		// --> мальтиец-проводник
		case "Sharlie_maltie":
			dialog.text = "Danke für das Warten, Monsieur. Suchen Sie also nach Michel de Monper? Sie sind sein Bruder?";
			link.l1 = "Ja, das ist korrekt. Ich bin sein Bruder Charles. Ich muss ihn sofort sehen. Ist Michel in Schwierigkeiten?";
			link.l1.go = "Sharlie_maltie_1";			
		break;
		
		case "Sharlie_maltie_1":
			dialog.text = "Leider ist er das, Monsieur. Michel ist in einer der Kasematten unten eingesperrt. Chevalier de Poincy, der Generalgouverneur der französischen Kolonien in der Neuen Welt, hat den Befehl zu seiner Verhaftung persönlich unterschrieben. Wir alle waren schockiert. Ihr Bruder ist ein Vorbild für männliche Tugend, Disziplin und Mut, der Stolz unseres Ordens! Das Schlimmste ist, dass wir, seine Freunde, ihn hinter Gitter bringen und ihn wie einen gewöhnlichen Verbrecher bewachen müssen! Wir tun alles in unserer Macht Stehende, um ihm den Aufenthalt so angenehm wie möglich zu gestalten, aber... Gefängnis bleibt Gefängnis.";
			link.l1 = "Wovon wird er beschuldigt? Hat er ein Verbrechen begangen?";
			link.l1.go = "Sharlie_maltie_1_1";			
		break;
		
		case "Sharlie_maltie_1_1":
			dialog.text = "Das Büro des Generalgouverneurs hat Michel des Unterschlagung beschuldigt! Wie lächerlich! Wir alle hier sind überzeugt, dass es politisch motiviert ist. Ich werde Ihnen etwas im Vertrauen erzählen. Michel hat sich an bestimmten verdeckten Aktionen im Auftrag des Ordens beteiligt. Vielleicht hat er mehr herausgefunden, als er hätte sollen. Oder schlimmer, einige mächtige Männer verärgert. Aber Geld stehlen? Das glaubt niemand. Es ist ein Vorwand, kein echter Grund, ein feiger und unedler Vorwand! Aber genug der Worte. Ihr Bruder freut sich darauf, Sie zu sehen, ich bin sicher, er wird Ihnen alles selbst erzählen.";
			link.l1 = "Gut. Wo befindet sich euer Gefängnis?";
			link.l1.go = "Sharlie_maltie_1_2";
		break;
		
		case "Sharlie_maltie_1_2":
			dialog.text = "In unserer unterirdischen Waffenkammer, direkt hier in der Stadt. Folge mir. Ich zeige dir den Weg.";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2";
		break;
		
		case "Sharlie_maltie_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "FortFrance_town", "officers", "reload7_1", "Maltie_GoTown", -1);
		break;
		
		case "Sharlie_maltie_3":
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Maltie_officer"), "questmarkmain");
			dialog.text = "Hier sind wir. Dies ist unser Operationsbasis - die Karibische Abteilung des Hospitaliterordens von Sankt Johannes von Jerusalem, von Rhodos und von Malta. Die Kasematten sind unter uns. Geh den Flur entlang, vorbei am Speisesaal und der Kapelle. Die Treppe dort führt dich zur unteren Ebene. Such nach einem Korridor mit Zellen gesäumt. Du wirst deinen Bruder in einer nahe dem Ende finden.\nGeh, Charles, und Gott sei mit dir. Bitte hilf Michel! Er ist unschuldig, das kann hier jeder schwören.";
			link.l1 = "Der ganze Grund, warum ich zu diesem Drecksloch gekommen bin, ist, meinen Bruder zu sehen. Ich hoffe, ich kann ihn zumindest aus dieser Klemme herausbekommen.";
			link.l1.go = "Sharlie_maltie_4";
		break;
		
		case "Sharlie_maltie_4":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "none", -1);
		break;
		
		//belamour cle -->
		case "Sharlie_maltieA":
			dialog.text = "Also haben Sie nach Michel de Monper gesucht? Und Sie sind sein Bruder?";
			link.l1 = "Ja, das ist richtig. Ich bin sein Bruder Charles. Ich muss ihn sofort sehen. Er hat Ärger bekommen, nicht wahr?";
			link.l1.go = "Sharlie_maltie_1a";			
		break;
		
		case "Sharlie_maltie_1a":
			dialog.text = "Leider hat er, Monsieur. Michel ist verhaftet und in unserem Gefängnis eingesperrt. Chevalier de Poincy, der Generalgouverneur der französischen Kolonien, hat die Befehle selbst gegeben und unterschrieben. Wir waren alle schockiert.\nIhr Bruder ist ein Beispiel für Männlichkeit, Festigkeit und Mut, ein Stolz unseres Ordens! Das Schlimmste ist, dass wir, seine Freunde, seine Zelle abschließen und ihn wie einen Verbrecher bewachen müssen! Wir tun alles, um seinen Zustand zu erleichtern, aber... ein Gefängnis ist ein Gefängnis.";
			link.l1 = "Also, was wird ihm vorgeworfen? Hat er ein Verbrechen begangen?";
			link.l1.go = "Sharlie_maltie_1_1a";			
		break;
		
		case "Sharlie_maltie_1_1a":
			dialog.text = "Unsinn! Reiner Unsinn! Sie haben Michel der Unterschlagung und des Staatsgeldesdiebstahls beschuldigt. Lächerlich! Wir sind alle sicher, dass es nur ein politisches Spiel ist. Michel hat an geheimen Operationen des Ordens teilgenommen, vielleicht hat er mehr erfahren, als er hätte sollen.\nOder etwas anderes. Aber Geld stehlen! Niemand glaubt das. Es ist nur eine Ausrede, kein Grund, so eine grobe und dämliche Ausrede! Aber genug der Worte. Dein Bruder freut sich darauf, dich zu sehen, ich bin sicher, er wird dir alles selbst erzählen.";
			link.l1 = "Gut. Wo befindet sich das Gefängnis?";
			link.l1.go = "Sharlie_maltie_1_2a";
		break;
		
		case "Sharlie_maltie_1_2a":
			dialog.text = "Es befindet sich in unserer Untergrundbasis, hier in der Stadt. Folge mir. Ich zeige dir den Weg.";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2a";
		break;
		
		case "Sharlie_maltie_2a":
			DialogExit();
			//LAi_ActorGoToLocation(npchar, "reload", "reloadPr1", "FortFrance_Dungeon", "reload", "reload1", "", -1);
			Pchar.quest.Sharlie_Maltie.win_condition.l1 = "location";
			Pchar.quest.Sharlie_Maltie.win_condition.l1.location = "FortFrance_town";
			Pchar.quest.Sharlie_Maltie.win_condition = "Maltie_GoBasement";
			QuestPointerDelLoc("FortFrance_prison", "reload", "reload1");
		break;
		//<-- cle
		// мальтиец-проводник
		
		// --> найм матросов
		case "Sharlie_sailor":
			DelLandQuestMark(npchar);
			dialog.text = "Und dann beugte er sich über die Reling und hat so viel von sich gegeben, dass selbst die Karibik grün wurde! Ha-ha-ha!";
			link.l1 = "Alonso?";
			link.l1.go = "Sharlie_sailor_1";
		break;
		
		case "Sharlie_sailor_1":
			dialog.text = "Oh! Charles, ich erzähle den Jungs gerade von unseren Abenteuern!";
			link.l1 = "Ist mir aufgefallen. Hör zu, Alonso. Ich bin jetzt... Kapitän.";
			link.l1.go = "Sharlie_sailor_2";
		break;
		
		case "Sharlie_sailor_2":
			dialog.text = "Schon? Ich dachte, Sie bräuchten mindestens einen Monat, ha-ha!";
			link.l1 = "Ich meine es ernst!";
			link.l1.go = "Sharlie_sailor_3";
		break;
		
		case "Sharlie_sailor_3":
			dialog.text = "Wäre es nur um mich gegangen, hätte ich sofort zugesagt. Aber mit mir sind noch vierzig Männer von der Ulysse. Sie haben mir ihr Schicksal anvertraut, ich muss sicher sein, dass Sie sie nicht enttäuschen\n"+
			"Was für ein Schiff haben Sie?";
			link.l1 = "Ein Schiff wie jedes andere, "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype), "Name")))+". Ist das so wichtig?";
			link.l1.go = "Sharlie_sailor_4";
		break;
		
		case "Sharlie_sailor_4":
			dialog.text = "Wissen Sie, nach der Ulysse wollen wir nicht auf irgendeiner Barke oder Tartane dienen. Wir haben Ihr Schiff schon gesehen, und die Jungs sind zufrieden\n"+
			"Jetzt zum Geld. Wir nehmen 4.800 Pesos im Voraus. Danach – wie üblich, Anteile. Keine Sorge, wir verlangen nicht zu viel. Schaffen Sie das?";
			if (sti(Pchar.money) >= 4800)
			{
				link.l1 = "Abgemacht! Hier ist Ihr Geld.";
				link.l1.go = "Sharlie_sailor_5";
			}
			link.l2 = "Leider habe ich gerade nicht so viel Geld bei mir.";
			link.l2.go = "Sharlie_sailor_nomoney";
		break;
		
		case "Sharlie_sailor_5":
			if (GetSquadronGoods(pchar, GOOD_FOOD) < 20 || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < 30)
			{
				dialog.text = "Haben Sie Proviant im Laderaum, Kapitän? Und Medizin? Nein? Nun, das ist nicht gut. Geh raus und hol das Minimum für unsere Reise und dann komm zurück und wir werden reden. Geh zum Laden und hol was du brauchst.";
				link.l1 = "Hm. Du hast recht. Also gut, ich werde das tun.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				AddMoneyToCharacter(pchar, -4800);
				dialog.text = "Na sowas! Glückwunsch... Kapitän! Ich hole sofort die Jungs, und wir gehen an Bord.";
				link.l1 = "Freue mich, unser Abenteuer fortzusetzen, Alonso. Mach das Schiff klar zum Auslaufen!";
				link.l1.go = "Sharlie_sailor_6";
			}
		break;
		
		case "Sharlie_sailor_6":
			DialogExit();
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "Fortfrance_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
			SetCrewQuantityOverMax(PChar, 40);
			pchar.Ship.Crew.Morale = 50;
			pchar.Ship.Crew.Exp.Sailors = 50;
			pchar.Ship.Crew.Exp.Cannoners = 50;
			pchar.Ship.Crew.Exp.Soldiers = 50;
			AddQuestRecord("Sharlie", "7");
			pchar.questTemp.Sharlie = "skiper";
			DeleteAttribute(pchar, "GenQuest.CannotWait");//снимаем запрет, если не был снят раньше
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		case "Sharlie_sailor_nomoney":
			dialog.text = "Nun, sobald du genug Geld gefunden hast, komm zurück. Du wirst uns hier in der Taverne finden. Es sind sowieso keine anderen Schiffe in der Nähe. Wir werden einfach weiter unser Geld mit Trinken und Huren verschwenden, harhar!";
			link.l1 = "Ich werde versuchen, so schnell wie möglich zurück zu sein.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Sharlie_sailor_again";
		break;
		
		case "Sharlie_sailor_again":
			dialog.text = "Sie sind zurück, Kapitän? Bereit, mich und meine Kameraden zu engagieren? Unsere Geldbeutel beginnen sich zu leeren, wir brauchen die Meeresbrise wieder auf unseren Gesichtern!";
			if (sti(Pchar.money) < 4800)
			{
				link.l1 = "Noch nicht, ich bereite immer noch alles vor.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				link.l1 = "Ja. Nimm deine Vorauszahlung. Jetzt stehst du in meinem Dienst.";
				link.l1.go = "Sharlie_sailor_5";
			}
		break;
		// найм матросов
		
		// наводчик на штурмана
		case "skipertalker":
			DelLandQuestMark(npchar);
			dialog.text = LinkRandPhrase("Ahoi Käpt'n! Was brauchst du?","Hallo Monsieur. Was kann ich für Sie tun?","Guten Tag. Was wünschen Sie?");
			link.l1 = RandPhraseSimple("Ich habe eine Frage an dich.","Ich brauche Informationen über diese Kolonie.");
			link.l1.go = "skipertalker_1";
			link.l2 = "Nur ein Hallo. Auf Wiedersehen!";
			link.l2.go = "exit";
			NextDiag.TempNode = "skipertalker";
		break;
		
		case "skipertalker_1":
			dialog.text = RandPhraseSimple("Was ist los?","Was brauchst du?");
			link.l1 = "Hör zu, "+GetAddress_FormToNPC(NPChar)+", hier ist die Sache... Ich suche einen Navigator. Vielleicht kennst du hier in der Stadt jemanden, der für den Job geeignet ist?";
			link.l1.go = "skipertalker_2";
		break;
		
		case "skipertalker_2":
			dialog.text = "Ein Navigator? Hm. Nun, ich kenne einen... Es gibt nur ein Problem - er ist im Gefängnis, Schuldnergefängnis. Der arme Teufel ist jetzt seit fast einem Monat in den Kerkern eingesperrt, bis er oder jemand anderes bezahlt, was er schuldet.";
			link.l1 = "Ein Schuldner? Hm... Wie heißt er?";
			link.l1.go = "skipertalker_3";
		break;
		
		case "skipertalker_3":
			dialog.text = "Sein Name ist Folke Deluc. Frag den Gefängniskommandanten, wenn du ihn sehen willst. Aber ich glaube nicht, dass sie ihn rauslassen werden, es sei denn, du bezahlst seine Schulden, denn das wird er sicher nicht tun, hahaha!";
			link.l1 = "Vielleicht werde ich das tun. Danke für die Information, Freund.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie = "jailskiper";
			AddQuestRecord("Sharlie", "8");
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", false);
			SetFunctionLocationCondition("FortfranceJailOff_AddQuestMark", "fortfrance_prison", false);
		break;
		
		// --> штурман
		case "Folke":
			dialog.text = "Wodurch habe ich solche Ehre verdient, Monsieur?";
			link.l1 = "Hallo, Folke. Es ist einfach, ich habe ein Schiff, aber keinen Navigator. Und ich brauche einen. Also habe ich deine Schulden abgelöst...";
			link.l1.go = "Folke_1";
		break;
		
		case "Folke_1":
			dialog.text = "Du willst mir also sagen, dass du mich hier rausgeschleppt hast, um mich in deine Mannschaft aufzunehmen?";
			link.l1 = "Genau. Ich denke, du wirst schnell das Geld ausgleichen, das ich für dich ausgegeben habe. Nun... wir werden sehen, wie es läuft.";
			link.l1.go = "Folke_2";
		break;
		
		case "Folke_2":
			dialog.text = "Mein Dank, Monsieur. Ich habe genug von dieser faulen, feuchten Zelle. Es würde mir große Freude bereiten, wieder an Bord zu gehen. Ah, das Meer...";
			link.l1 = "Ich bin froh, dass wir uns verständigt haben, Folke. Noch eine Sache, hast du noch andere Fähigkeiten außer ein Schiff zu steuern?";
			link.l1.go = "Folke_3";
		break;
		
		case "Folke_3":
			dialog.text = "Ein bisschen von allem, Kapitän. Ich habe früher auf einem Kaperfahrer für die Niederländische Westindien-Kompanie gedient. Dort habe ich gelernt, wie man Kanonen bedient, also kann ich als Artillerieoffizier dienen, wenn Sie mich brauchen. Handel und Entern sind meine schwächsten Punkte.";
			link.l1 = "Danke fürs Teilen, nun folge mir zum Schiff. Ich möchte, dass du die Mannschaft mit deinem erfahrenen Auge beobachtest, während sie alles für die Abfahrt vorbereiten. Dann möchte ich so schnell wie möglich nach Guadeloupe aufbrechen.";
			link.l1.go = "Folke_4";
		break;
		
		case "Folke_4":
			dialog.text = "Aye aye, Kapitän! Ich werde in deiner Kabine auf dich warten. *Benutze das Aktionsmenü auf See, um auf die Kabine und andere Bereiche des Schiffes zuzugreifen*";
			link.l1 = "Danke dir, Folke. Wir sehen uns an Bord.";
			link.l1.go = "Folke_5";
			Log_Info("You have received amulet 'Merchant's Rosary'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_8");
			if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
			{
				DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
			}
		break;
		
		case "Folke_5":
			DialogExit();
			EndQuestMovie();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			AddQuestRecord("Sharlie", "10");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_skiper.win_condition.l1 = "location";
			pchar.quest.Sharlie_skiper.win_condition.l1.location = "My_Cabin_Small";
			pchar.quest.Sharlie_skiper.function = "Sharlie_SkiperTalk";
			//прерывание на засаду пиратов - принудительный квест
			pchar.quest.Sharlie_seabattle.win_condition.l1 = "location";
			pchar.quest.Sharlie_seabattle.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_seabattle.function = "SharlieSeabattle_agent";
			
			pchar.quest.NewGameTip2.win_condition.l1 = "location";
			pchar.quest.NewGameTip2.win_condition.l1.location = "Martinique";
			pchar.quest.NewGameTip2.function = "ShowNewGameTip";
			pchar.quest.NewGameTip2.text = "Your first officer is waiting for you. Use the action menu (ENTER) to go to the cabin.";
		break;
		
		case "Folke_6":
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин 250912
			dialog.text = "Eine feine Lugger, Kapitän! Ein recht anständiges kleines Schiff mit feiner Takelage und soliden Balken. Mit einem Schiff wie diesem werden wir nicht nur sicher Guadeloupe erreichen, sondern können sogar die ganze Karibik durchkreuzen, wenn wir wollen.";
			link.l1 = "Ausgezeichnet. Wenigstens habe ich mein Geld nicht für ein leckes Boot ausgegeben... Hast du irgendeinen Rat, bevor wir in See stechen, Folke?";
			link.l1.go = "Folke_8";
		break;
		
		case "Folke_7":
			dialog.text = "Verdammt, diese Schaluppe leckt wie ein Sieb, Kapitän. Es wird knapp für uns, nach Guadeloupe überzusetzen. Wenn Sie in einem Stück in Basse-Terre ankommen wollen, muss sie sofort zur Reparatur in die Werft.";
			link.l1 = "Ich hatte keine Wahl, das war das einzige Schiff zum Verkauf! Und sie haben mich ein hübsches Sümmchen dafür berechnet. Wie du weißt, haben wir im Moment keine Zeit, sie zu reparieren... Hast du irgendwelche Ratschläge, bevor wir in See stechen?";
			link.l1.go = "Folke_8";
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_BALLS) >= 80) && (GetSquadronGoods(pchar, GOOD_GRAPES) >= 80) && (GetSquadronGoods(pchar, GOOD_KNIPPELS) >= 80) && (GetSquadronGoods(pchar, GOOD_BOMBS) >= 80) && (GetSquadronGoods(pchar, GOOD_POWDER) >= 180);
		case "Folke_8":
			if (bOk)
			{
				dialog.text = "Nun, wir sind gut mit Pulver und Kugeln versorgt, Kapitän. Das reicht fürs Erste; denken Sie nur daran, rechtzeitig nachzufüllen.";
				link.l1 = "Nun, das versteht sich von selbst. Irgendwelche anderen Kommentare?";
				link.l1.go = "Folke_10";
				if (CheckCharacterItem(PChar, "BoxOfBalls"))
				{
					link.l2 = "Ah! Danke für die Erinnerung. Ich habe zufällig eine ganze Kiste Kugeln dabei!";
					link.l2.go = "Folke_8_1";
				}
			}
			else
			{
				dialog.text = "Wir haben nicht genug Munition im Magazin, Kapitän. Wir brauchen mindestens hundert Kanonenkugeln, Kettenkugeln und Bomben, sowie hundert Säcke Traubenschrot und zweihundert Fässer Schießpulver. Kaufen Sie das notwendige Material, Kapitän. Es wird nicht viel kosten, aber es wird unser Leben retten, wenn wir von Piraten oder den Spaniern angegriffen werden.";
				link.l1 = "Ein lohnendes Investment. Ich gehe zum Händler.";
				link.l1.go = "Folke_9";
			}
		break;
		
		case "Folke_8_1":
			dialog.text = "...Und wie lange schleppen Sie die schon mit sich herum?";
			link.l1 = "Fast zwei Wochen.";
			link.l1.go = "Folke_8_2";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
			//AddCharacterGoodsSimple(sld, GOOD_BALLS, 10);
		break;
		
		case "Folke_8_2":
			dialog.text = "Aber warum, Käpt’n?!";
			link.l1 = "Ich sammle gern allerlei Kram. Man weiß nie, was nützlich sein könnte.";
			link.l1.go = "Folke_8_3";
		break;
		
		case "Folke_8_3":
			dialog.text = "Tja, Pech gehabt. Diese Kugeln passen nie in unsere Kanönchen. So große Kugeln habe ich noch nie gesehen. Eine davon schickt die Adeline auf den Grund.";
			link.l1 = "...";
			link.l1.go = "Folke_10";
		break;
		
		case "Folke_9":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_1";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "12");
		break;
		
		case "Folke_goods_1":
			dialog.text = "Haben Sie schon Munition eingekauft, Kapitän?";
			if (bOk)
			{
				link.l1 = "Ja, das habe ich. Noch weitere Anmerkungen?";
				link.l1.go = "Folke_10";
			}
			else
			{
				link.l1 = "Nicht jetzt, ich arbeite noch daran.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_1";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_WEAPON) >= 50);
		case "Folke_10":
			if (bOk)
			{
				dialog.text = "Gut gemacht, du hast genug Waffen für deine Mannschaft gekauft. Wenn wir nicht genug Waffen haben, werden wir bei Enteraktionen weit mehr Männer verlieren. Gott bewahre uns davor. Vergiss nicht, regelmäßig die Menge im Laderaum zu überprüfen\nEs ist klug, ein paar mehr Waffen zu behalten, als wir brauchen. Die verdammten Ratten lieben es, an den hölzernen Griffen und Schäften zu nagen.";
				link.l1 = "Verstanden. Ich sehe, es gibt noch etwas, was Sie hinzufügen möchten?";
				link.l1.go = "Folke_11";
			}
			else
			{
				dialog.text = "Wir haben nicht genug Waffen an Bord für die Besatzung. Wenn wir nicht genug Waffen haben, werden wir bei Enteraktionen weit mehr Männer verlieren. Gott beschütze uns davor. Soweit ich verstehe, haben Sie vierzig Männer in der Besatzung\nKaufen Sie genug Waffen für jeden, oder sogar ein paar extra, fünfzig Sets sollten ausreichen. Es ist klug, ein paar mehr Waffen zu haben, als wir brauchen. Die verdammten Ratten mögen es, an den hölzernen Griffen und Schaften zu nagen.";
				link.l1 = "Das werde ich tun. Ich komme bald zurück.";
				link.l1.go = "Folke_10_1";
			}
		break;
		
		case "Folke_10_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_2";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "13");
		break;
		
		case "Folke_goods_2":
			dialog.text = "Haben Sie den Waffenkauf abgeschlossen, Kapitän?";
			if (bOk)
			{
				link.l1 = "Die Waffen sind im Laderaum. Ich sehe, es gibt noch etwas, das du hinzufügen möchtest?";
				link.l1.go = "Folke_11";
			}
			else
			{
				link.l1 = "Nicht gerade jetzt, ich arbeite noch daran.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_2";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_FOOD) >= 100) && (GetSquadronGoods(pchar, GOOD_RUM) >= 10);
		case "Folke_11":
			if (bOk)
			{
				dialog.text = "Nein, ich denke, das ist alles. Wir haben genug Essen, du hast auch für Rum für die Crew gesorgt. Das ist klug, denn es gibt kein besseres Heilmittel für alle Beschwerden als ein schöner kühler Schluck Rum nach deiner Schicht. Seeleute lieben und respektieren Kapitäne, die ihnen ihre tägliche Rumration geben. Du willst nie hören, wie deine Männer fragen: 'Warum ist der Rum weg?'";
				link.l1 = "Können wir jetzt in See stechen?";
				link.l1.go = "Folke_12";
			}
			else
			{
				dialog.text = "Ja. Essen und Rum. Es ist katastrophal, wenn du nicht genug Essen an Bord hast. Hab immer mehr Proviant, als du denkst, dass du brauchen wirst. Du weißt nie, wie lange eine Reise dauern wird - eine Flaute oder ein starker Sturm können jeden Plan ruinieren. Die Männer werden meutern oder vor Hunger sterben, wenn der Proviant weg ist\nDer Rumvorrat ist nicht so kritisch, aber ich empfehle dringend, immer etwas an Bord zu haben, es gibt kein besseres Heilmittel für alle Beschwerden als einen schönen kühlen Schluck Rum nach deiner Schicht. Seeleute lieben und respektieren Kapitäne, die ihnen ihre tägliche Rumration geben\nAlso geh und kaufe die Vorräte, die wir brauchen - mindestens hundert Kisten Essen und zehn Fässer Rum. Du willst nie hören, wie deine Männer fragen: 'Warum ist der Rum alle?'";
				link.l1 = "Ich denke, du hast Recht. Ich werde den Händler noch einmal besuchen.";
				link.l1.go = "Folke_11_1";
			}
		break;
		
		case "Folke_11_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_3";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "14");
		break;
		
		case "Folke_goods_3":
			dialog.text = "Haben Sie schon unser Essen und Rum gekauft, Kapitän?";
			if (bOk)
			{
				link.l1 = "Ja. Können wir jetzt in See stechen?";
				link.l1.go = "Folke_12";
			}
			else
			{
				link.l1 = "Nein, ich arbeite noch daran.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_3";
			}
		break;
		
		case "Folke_12":
			dialog.text = "Ja, Käpt'n. Wir können den Anker lichten und nach Norden in Richtung Guadeloupe segeln, wie Sie wollten.";
			// belamour legendary edition -->
			link.l1 = "Große Arbeit, Folke. Ohne dich hätte ich es nicht geschafft.";
			link.l1.go = "Folke_13";
			link.l2 = "In Ordnung, wir machen uns an die Arbeit, mal sehen, ob du das Geld wert bist.";
			link.l2.go = "Folke_13a";
		break;
		
		case "Folke_13a":
			Npchar.loyality = makeint(Npchar.loyality) - 5;
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			dialog.text = "Dann setze mich als Navigator ein und ich werde an meinen Platz an Deck gehen.";
			link.l1 = "..., Freund.";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_13":
			Npchar.loyality = makeint(Npchar.loyality) + 5;
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			// <-- legendary edition
			dialog.text = "Dann setze mich als Navigator ein und ich werde an meinen Platz an Deck gehen.";
			link.l1 = "...";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_14":
			DialogExit();
			LAi_SetStayType(npchar);
			LAi_SetImmortal(npchar, false);
			AddQuestRecord("Sharlie", "15");
			pchar.questTemp.Sharlie = "seabattle";//в Ле Франсуа
			DeleteAttribute(pchar, "NoNavyPenalty"); // штрафуем за нехватку навигации
			
			npchar.quest.OfficerPrice = 20;
			npchar.loyality = 30;
			
			// --> копипаста LandEnc_OfficerHired
			AddPassenger(pchar, npchar, false);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			// <--
			
			pchar.questTemp.HelenDrinking.TakeFolke = true;
			
			DoQuestFunctionDelay("Tutorial_Navigator2", 1.0);
			//DoQuestFunctionDelay("Ngt_FolkeEng", 3.0);
			//NewGameTip("Welcome aboard your new officer! Press F4 to assign him as your Navigator.");
			pchar.questTemp.Sharlie.FolkeWait = true;
			LocatorReloadEnterDisable("My_Cabin_Small", "reload1", true);
			NextDiag.CurrentNode = "Folke_wait";
		break;
		
		case "Folke_wait":
			dialog.text = "Bereit zum Ablegen, Kapitän!";
			link.l1 = "...";
			
			if (!CheckAttribute(npchar, "navigator")) {
				dialog.text = "Kapitän, setze mich als Navigator ein, sonst laufen wir in Eile auf Grund.";
				link.l1 = "Verstanden, ich mache es jetzt.";
			}
			
			link.l1.go = "exit";
			NextDiag.TempNode = "Folke_wait";
		break;
	
		// штурман

	// --> пират-обманщик
		case "Seabattle_pirate":
			dialog.text = "Meine Entschuldigung. "+GetFullName(pchar)+"?";
			link.l1 = "Richtig. Was schulde ich für diesen Anlass, Herr?";
			link.l1.go = "Seabattle_pirate_1";
		break;
		
		case "Seabattle_pirate_1":
			dialog.text = "Erlauben Sie mir, mich vorzustellen - "+GetFullName(npchar)+". Ich wurde hierher geschickt von Cesar Craig. Sie müssen ihn kennen. Er ist der Besitzer der Taverne in Le Francois. Soweit er informiert ist, sind Sie kurz davor, nach Guadeloupe abzureisen. Er möchte Ihnen etwas leicht verdientes Geld anbieten.";
			link.l1 = "Hm... Interessant! Und wie ist Cesar Craig so gut informiert geworden?";
			link.l1.go = "Seabattle_pirate_2";
		break;
		
		case "Seabattle_pirate_2":
			dialog.text = "Es ist einfach, Kapitän. Ihr Schiff ist das einzige Schiff in St. Pierre im Moment, jeder mit zwei Ohren und einem Auge weiß alles über Sie und wohin Sie gehen. Hier in den Kolonien fliegen Gerüchte schneller herum als Möwen. Sind Sie also interessiert, unser Angebot zu hören?";
			link.l1 = "Sicher. Ich bin nie gegen das Verdienen von etwas Geld.";
			link.l1.go = "Seabattle_pirate_3";
		break;
		
		case "Seabattle_pirate_3":
			dialog.text = "Jetzt reden wir, Kumpel! Ich sehe, du hast einen scharfen Sinn für Geschäfte. Hier ist der Deal. Cesar braucht dringend eine Lieferung Wein nach Guadeloupe. Zweihundert Fässer, das kann dein Schiff locker aufnehmen. Die Bezahlung beträgt zehntausend Pesos für eine leichte Aufgabe - Cesar hat es eilig, und dein Schiff ist gerade das einzige im Hafen. Du musst zustimmen, solch lukrative Angebote sind selten.";
			link.l1 = "Verdammt, zehntausend Pesos? Nun, wir haben einen Deal!";
			link.l1.go = "Seabattle_pirate_4";
		break;
		
		case "Seabattle_pirate_4":
			dialog.text = "Fahre nach Le Francois und sprich mit Cesar. Er kümmert sich um alles. Du musst nur in der Bucht vor Le Francois ankern. Lass mich nicht im Stich Kumpel, Cesar hat mir tausend Pesos versprochen, wenn ich dich überzeugt habe...";
			link.l1 = "Mach dir keine Sorgen, betrachte mich als überzeugt. Sobald ich bereit bin abzufahren, werde ich direkt nach Le Francois segeln.";
			link.l1.go = "Seabattle_pirate_5";
		break;
		
		case "Seabattle_pirate_5":
			dialog.text = "Hurra! Ich gehe, um meine tausend zu holen. Danke, Kumpel!";
			link.l1 = "Bitte schön...";
			link.l1.go = "Seabattle_pirate_6";
		break;
		
		case "Seabattle_pirate_6":
			DialogExit();
			AddLandQuestMark(characterFromId("LeFransua_tavernkeeper"), "questmarkmain");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "", -1);
			AddQuestRecord("Sharlie", "11");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.location = "None";
		break;
	// пират-обманщик

	// офицер Гриффондора
		case "griffondor_officer":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;

	// командир абордажной роты по защите Сен-Пьера
		case "rosetti":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Kapitän, die Entertruppe ist formiert und bereit! Warten auf Ihre Befehle!";
			link.l1 = "";
			link.l1.go = "rosetti_1";
		break;
		
		case "rosetti_1":
			DialogExit();
			bDisableCharacterMenu = true;//лоченые интерфейсы
			ChangeShowIntarface();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("DefendSP_soldier_0"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Blaze");
			sld.dialog.filename = "MainHero_dialog.c";
			sld.dialog.currentnode = "SP_defend";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rosetti_2":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "Aye aye, Kapitän! Macht euch bereit Jungs, folgt dem Kapitän! Hütte, eins-zwei-drei!";
			link.l1 = "";
			link.l1.go = "rosetti_3";
		break;
		
		case "rosetti_3":
			DialogExit();
			PlaySound("interface\abordage_wining.wav");
			bDisableCharacterMenu = false;//лоченые интерфейсы
			ChangeShowIntarface();
			for (i=0; i<=12; i++)
			{
				sld = CharacterFromID("DefendSP_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// прерывание на джунгли перед выходом из города
			pchar.quest.DefendSP_jungle1.win_condition.l1 = "location";
			pchar.quest.DefendSP_jungle1.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.DefendSP_jungle1.function = "DefendSP_SpainPatrol";
		break;
		
		case "spain_patrol":
			dialog.text = "Scheiße, französische Verstärkungen! Bildet Reihen! Lorenzo, geh ins Lager und schlage Alarm! Sterbt, ihr Scheißkerle!";
			link.l1 = "...";
			link.l1.go = "spain_patrol_1";
		break;
		
		case "spain_patrol_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DefendSP_spapatrol_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "DefendSP_SpaPatrolDie");
				AddDialogExitQuest("MainHeroFightModeOn");
			}
			sld = CharacterFromID("DefendSP_spapatrol_5");
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "DefendSP_GateAlarm", -1);
		break;

	// страж истины
		case "spanish":
			dialog.text = "Verstehen Sie, dass ich nicht befugt bin, solche Informationen zu verbreiten?";
			link.l1 = "Verstehst du, dass es nur dank meiner rechtzeitigen Unterbrechung war, dass St. Pierre nicht von den Spaniern verwüstet wurde? Mein Bruder ist verschwunden, hat den Orden verlassen! Er muss das aus einem Grund getan haben. Ich, als Vertreter von Sir Philippe de Poincy, bin berechtigt zu ermitteln!";
			link.l1.go = "spanish_1";
		break;
		
		case "spanish_1":
			dialog.text = "In Ordnung, in Ordnung, Monsieur de Maure. Ich werde Ihre Fragen beantworten. Beruhigen Sie sich zuerst. Nun fragen Sie los.";
			link.l1 = "Was passierte, bevor Michel unter Bewachung eingesperrt wurde?";
			link.l1.go = "spanish_2";
		break;
		
		case "spanish_2":
			dialog.text = "Michel de Monper verhandelte mit einigen Piratenbaronen, um einen Regimewechsel auf Tortuga zu arrangieren.";
			link.l1 = "Das weiß ich schon. Was noch?";
			link.l1.go = "spanish_3";
		break;
		
		case "spanish_3":
			dialog.text = "Er plante auch eine andere Operation gegen die Spanier. Um genau zu sein - die Eroberung eines spanischen Schiffes mit wertvoller Ladung an Bord. Michel sollte das Ziel unter die Kanonen der leichten Fregatte 'Gryffondor' locken. Wir haben ihn eine ganze Weile nicht gesehen, während er das plante.\nAber der Plan ging schief. Der spanische Transporter kam nicht an und Michel selbst wurde von örtlichen Fischern halbtot an den Ufern der Bucht von Le Marin angespült. Es scheint, dass die Operation ein Fehlschlag war.\nKrieg ist Krieg, und Dinge gehen schief. Es war ein Wunder, dass Michel überhaupt überlebte, aber Chevalier de Poincy geriet in Wut. Er beschuldigte Michel, Geld des Ordens veruntreut zu haben, und ließ ihn einsperren. Natürlich glaubten wir kein Wort von diesen Anschuldigungen. Michel ist ein ehrlicher Mann, ein wahrer Ritter des Ordens. Nur Gott weiß, was den Generalgouverneur aufgebracht hat. Vielleicht wird Ihnen Chevalier de Poincy selbst davon erzählen?";
			link.l1 = "Möglicherweise. Ist das alles, was du weißt?";
			link.l1.go = "spanish_4";
		break;
		
		case "spanish_4":
			dialog.text = "Leider gibt es nichts weiter zu sagen. Die Einzelheiten der Operationen Ihres Bruders waren nur ihm selbst und Chevalier de Poincy bekannt. Wir sind Ritter des Malteserordens. Wir führen unsere Befehle aus.";
			link.l1 = "Wenn der Chevalier Michel so sehr vertraut, muss er zuvor erfolgreich seine geheimen Pläne ausgeführt haben. Kennen Sie erfolgreiche Aktionen, die Michel durchgeführt hat?";
			link.l1.go = "spanish_5";
		break;
		
		case "spanish_5":
			dialog.text = "Ganz bestimmt. Dieses jüngste Versagen von Michel de Monper war auch sein erstes Versagen, weshalb wir über die Reaktion des Ritters schockiert waren. Vor nicht allzu langer Zeit hat 'Gryffindor' dank Michels sorgfältiger Planung eine spanische Schatzgaleere voller Silber erbeutet. Das allein hätte für Dutzende von zukünftigen Misserfolgen entschädigen sollen. Und doch wurde dein Bruder verhaftet.";
			link.l1 = "Ich verstehe. Haben Sie eine Ahnung, warum Michel aus St. Pierre geflohen ist?";
			link.l1.go = "spanish_6";
		break;
		
		case "spanish_6":
			dialog.text = "Ich vermute, dass ein zwischenmenschlicher Konflikt zwischen Michel und de Poincy der Grund für seine Verhaftung war. Offensichtlich fürchtet dein Bruder, dass der Ritter ihn auch nach seiner Freilassung weiter verfolgen wird, daher hat er Vorsichtsmaßnahmen getroffen. Und wissen Sie was, Monsieur de Maure - niemand hier macht ihm Vorwürfe für seine Entscheidung!\nDer Mann hatte tapfer für das Wohl des Ordens gearbeitet und doch warfen sie ihn bei seinem allerersten Fehltritt, während er schwer verletzt war, in eine stinkende Zelle! Ein Fehltritt, der nicht einmal so schlimm war, niemand starb und kein Schiff sank!\nÜbrigens, dieses Gespräch ist streng vertraulich und ich werde nicht wiederholen, was ich gerade gesagt habe, auch nicht unter Eid, ist das klar, Monsieur de Maure?";
			link.l1 = "Ja, Herr. Ich habe bereits vergessen, dass wir dieses Gespräch geführt haben. Sagen Sie mir, könnte der spanische Angriff auf St. Pierre durch den Überfall des Ordens auf spanische Schiffe provoziert worden sein? Vielleicht dasselbe spanische Galeon mit Silber, das Sie erwähnt haben? Die Kastilier waren äußerst eifrig bei der Suche nach Ihrer Basis...";
			link.l1.go = "spanish_7";
		break;
		
		case "spanish_7":
			dialog.text = "Bezweifle ich. Nur wenige Menschen wissen über die Präsenz des Ordens in der Karibik und all unsere Vorstöße gegen die Spanier waren sorgfältig geplant. Frag den spanischen Offizier, den wir gefangen genommen haben, er kühlt gerade sein feuriges kastilisches Temperament in unseren Kasematten ab. Wir haben ihn bereits verhört. Der Angriff auf St. Pierre war ein gewöhnlicher Überfall, organisiert von einem spanischen Großbaron namens Ramon de Mendoza y Riba zum Zweck seines eigenen Gewinns und um die französischen Kolonien einzuschüchtern. Er wollte auch die Gunst des Escorial gewinnen.";
			link.l1 = "Ich werde mit diesem Spanier sprechen. Wo kann ich ihn finden?";
			link.l1.go = "spanish_8";
		break;
		
		case "spanish_8":
			dialog.text = "Unten, in derselben Zelle, in der dein Bruder festgehalten wurde.";
			link.l1 = "Ich kenne den Weg. Ich komme zurück, nachdem ich den Spanier verhört habe. Ich könnte noch einige Fragen haben.";
			link.l1.go = "spanish_9";
		break;
		
		case "spanish_9":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "2");
			pchar.questTemp.Guardoftruth = "prisoner";
			sld = characterFromId("spa_baseprisoner");
			LAi_CharacterEnableDialog(sld);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "spanish_10":
			dialog.text = "Nun, ist das nicht etwas! Du verstehst, dass ich diesen Gefangenen nicht freilassen kann, oder? Dieser Schurke hat den Angriff auf St. Pierre mit angeführt!";
			link.l1 = "Offizier, das ist ein wichtiger Zeuge. Der Angriff auf St. Pierre war kein einfacher Raubzug auf der Suche nach Beute. Don Ramon Mendosa suchte nach etwas anderem. Wir müssen ein definitives Motiv finden. Also, werden Sie diesen Spanier an mich übergeben oder muss ich die Erlaubnis von de Poincy einfordern?";
			link.l1.go = "spanish_11";
		break;
		
		case "spanish_11":
			dialog.text = "Beim Allmächtigen Gott... Gut, nimm ihn. Ich wollte diesen Bastard sowieso auf dem Platz von St. Pierre wie den gewöhnlichen Piraten, der er ist, aufhängen... Jetzt ist er dein Problem. Sorge dafür, dass er der Gerechtigkeit nicht entkommt!";
			link.l1 = "Zweifellos. Ich werde für diesen Spanier vor de Poincy antworten. Lassen Sie diesen Gefangenen fesseln und zu meinem Langboot am Stadtdock liefern.";
			link.l1.go = "spanish_12";
		break;
		
		case "spanish_12":
			dialog.text = "Sehr gut, Kapitän.";
			link.l1 = "Noch eine Sache, Offizier. Sagt Ihnen der Name Miguel Dichoso etwas?";
			link.l1.go = "spanish_13";
		break;
		
		case "spanish_13":
			dialog.text = "Nein. Ich habe es noch nie gehört. Warum fragst du?";
			link.l1 = "Bist du sicher? Also hast du niemanden mit diesem Namen getroffen, weder hier in deinem Lager, noch im Gouverneurspalast, noch irgendwo in St. Pierre?";
			link.l1.go = "spanish_14";
		break;
		
		case "spanish_14":
			dialog.text = "Nein, habe ich nicht. Wir denken nicht allzu gut über Spanier, wo ich herkomme.";
			link.l1 = "Also gut. Wie auch immer, das war zu erwarten. Es wäre zu einfach gewesen... Danke, Offizier! Sie waren sehr hilfreich.";
			link.l1.go = "spanish_15";
		break;
		
		case "spanish_15":
			dialog.text = "Sie sind willkommen... Was denken Sie, Monsieur de Maure, wo ist Ihr Bruder jetzt?";
			link.l1 = "Ich würde selbst gerne die Antwort auf diese Frage wissen. Und ich werde es herausfinden ... früher oder später. Au revoir!";
			link.l1.go = "spanish_16";
		break;
		
		case "spanish_16":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "3");
			pchar.questTemp.Guardoftruth = "toship";
			sld = characterFromId("spa_baseprisoner");
			sld.dialog.currentnode = "spa_prisoner_28";
			LAi_CharacterEnableDialog(sld);
		break;
		
	// монах-посланник от Винсенто
		case "monk_vinsento":
			dialog.text = TimeGreeting()+"! Bist du Kapitän "+GetFullName(pchar)+"?";
			link.l1 = "Ja, ich bin es. Was kann ich für dich tun?";
			link.l1.go = "monk_vinsento_1";
		break;
		
		case "monk_vinsento_1":
			dialog.text = "Grüße, Kapitän. Ich wurde von Vater Vincento zu Ihnen geschickt. Ich habe etwas für Sie...";
			link.l1 = "Vater Vincento? Ich arbeite nicht mehr für Seine Gnaden. Nicht nachdem er Alonso de Maldonado, den eingeschworenen Mann von Diego de Montoya, geschickt hat, um mich zu töten. Sie können diese Nachricht an den ehrwürdigen Vater weitergeben: er hat versagt.";
			link.l1.go = "monk_vinsento_2";
		break;
		
		case "monk_vinsento_2":
			dialog.text = "Warten Sie, Kapitän. Vater Vincento hat eine solche Reaktion von Ihnen erwartet und mich davor gewarnt. Ich versichere Ihnen, dass Seine Gnaden Ihnen nichts Böses wünscht. Bitte, lesen Sie diesen Brief. Es ist sehr, sehr wichtig.";
			link.l1 = "Vater Vincento wünscht mir nichts Schlechtes? Hm. Vielleicht hat er Ihnen auch nichts über mich und Don de Maldonado erzählt? Ich sehe, warum ich Ihnen glauben sollte.";
			link.l1.go = "monk_vinsento_3";
		break;
		
		case "monk_vinsento_3":
			dialog.text = "Nehmen Sie diesen Brief, Kapitän. Lesen Sie ihn und treffen Sie Ihre eigene Entscheidung. Wissen Sie nur, dass das Schicksal des gesamten Christentums in Ihren Händen liegt. Nehmen Sie das nicht auf die leichte Schulter. Möge Gott Sie segnen und Ihre Füße auf einen gerechten Weg stellen!";
			link.l1 = "In Ordnung, gib mir den Brief.";
			link.l1.go = "monk_vinsento_4";
		break;
		
		case "monk_vinsento_4":
			GiveItem2Character(pchar, "specialletter"); 
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_last";
			dialog.text = "Hier hast du es. Ich bete, dass du die richtige Entscheidung triffst. Pax vobiscum.";
			link.l1 = "...";
			link.l1.go = "monk_vinsento_5";
		break;
		
		case "monk_vinsento_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			ReOpenQuestHeader("Sharlie"); // patch-8
			AddQuestRecord("Sharlie", "40");
			CloseQuestHeader("Ksochitam");
		break;
		
	// падре Адриан
		case "adrian":
			dialog.text = "Grüße, mein Sohn. Der Herr sei mit dir.";
			link.l1 = "Und auch mit Ihnen, Vater Adrian. Seine Gnade sagte, dass Sie mir Amulette und Medizin zur Verfügung stellen können.";
			link.l1.go = "adrian_1";
		break;
		
		case "adrian_1":
			dialog.text = "Ja, natürlich. Ich habe eine spezielle Lieferung aus Santiago nur für dich erhalten. Hier sind gesegnete Amulette und Heiltränke. Und um das Ganze abzurunden, ein seltener, einzigartiger Ometochtli-Trank, der dich im Kampf unbesiegbar macht. Das ist alles für dich, mein Sohn. Nimm und sieh, dass der Herr gut ist.";
			link.l1 = "Danke dir!";
			link.l1.go = "adrian_2";
		break;
		
		case "adrian_2":
			for(i=2; i<=10; i++)
			{
				if (i == 4 || i == 5 || i == 8 || i == 9) continue;
				TakeNItems(pchar, "amulet_"+i, 2);
			}
			TakeNItems(pchar, "potion2", 20);
			TakeNItems(pchar, "potion4", 10);
			TakeNItems(pchar, "potion7", 3);
			TakeNItems(pchar, "berserker_potion", 3);
			dialog.text = "Sollten Sie weitere Heilkräuter benötigen, kann ich Ihnen jeden Tag ein Fläschchen von jedem zur Verfügung stellen. Ich werde so viel davon vorbereiten, wie Sie brauchen.";
			link.l1 = "Sie haben meinen Dank, Vater Adrian. Ich werde das im Hinterkopf behalten.";
			link.l1.go = "exit";
			link.l2 = "Großartig. Ich brauche jetzt sofort etwas.";
			link.l2.go = "potion";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "adrian_3":
			dialog.text = "Gott segne und behüte dich, mein Sohn. Was möchtest du?";
			link.l1 = "Ich möchte einige Heiltränke kaufen.";
			link.l1.go = "potion";
			link.l2 = "Nichts im Moment, ich bereite mich auf eine Reise vor. Bin nur vorbeigekommen, um Hallo zu sagen und zu sehen, wie es dir geht.";
			link.l2.go = "exit";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "potion":
			dialog.text = "Natürlich, mein Sohn. Welche Medizin brauchst du?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "Nur ein einfaches Heilmittel.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "Ein gesundheitsförderndes Elixier.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "Ein Gegengift.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "Ein Kräutergemisch.";
				link.l4.go = "potion4";
			}
			link.l5 = "Es tut mir leid, dich zu belästigen, Vater. Ich habe meine Meinung geändert.";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "Eine heilende Essenz? Das sind 90 Pesos, mein Sohn. Für Materialien natürlich.";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "Danke, Vater.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Leider habe ich das Geld nicht... Ich komme später zurück.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "Eine gesundheitsfördernde Elixiere? 500 Pesos, mein Sohn.";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "Danke, Vater.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Leider habe ich das Geld nicht... Ich komme später zurück.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "Ein Gegengift? 200 Pesos, mein Sohn.";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "Danke, Vater.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Leider habe ich das Geld nicht... Ich komme später wieder.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "Eine Kräutermischung? 900 Pesos, mein Sohn.";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "Danke, Vater.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Leider habe ich das Geld nicht... Ich komme später zurück.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "'Denn ich will dir Gesundheit wiederbringen und deine Wunden heilen, spricht der Herr.' Hier ist deine Medizin. Dominus vobiscum!";
			link.l1 = "Danke, Vater Adrian.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
			NextDiag.TempNode = "adrian_3";
		break;
		
	// посланец Дичозо
		case "Dichoso_agent":
			dialog.text = "Kapitän "+GetFullName(pchar)+"?";
			link.l1 = "Ja, das bin ich. Was willst du?";
			link.l1.go = "Dichoso_agent_1";
		break;
		
		case "Dichoso_agent_1":
			dialog.text = "Ich habe eine Nachricht für Sie vom Kapitän Miguel Dichoso. Er sagt, Sie kennen ihn.";
			link.l1 = "Ja, ich habe von ihm gehört. Hatte aber nie die Ehre, ihn persönlich zu treffen.";
			link.l1.go = "Dichoso_agent_2";
		break;
		
		case "Dichoso_agent_2":
			dialog.text = "Kapitän Dichoso möchte das ändern. Er will sich von Angesicht zu Angesicht mit dir treffen. Er hat ein Angebot für dich bezüglich einer Expedition in die Tiefen der Spanischen Hauptstraße zur verlorenen Indianerstadt Tayasal. Er sagte mir, dass deine Erfahrung in Kombination mit seinem Wissen befriedigende Ergebnisse liefern wird.";
			link.l1 = "Das waren genau seine Worte?";
			link.l1.go = "Dichoso_agent_3";
		break;
		
		case "Dichoso_agent_3":
			dialog.text = "Richtig. Kapitän Dichoso wird auf dich auf St. Christopher warten. Er wird dich in der großen Krypta des Capsterville-Friedhofs erwarten, um neugierige Augen und Ohren zu vermeiden.";
			link.l1 = "Hm...";
			link.l1.go = "Dichoso_agent_4";
		break;
		
		case "Dichoso_agent_4":
			dialog.text = "Dichoso warnte mich, dass du zögern würdest. Er sagte mir, ich solle dir Garantien anbieten, dass dir während der Verhandlungen nichts geschehen wird, egal wie deine Entscheidung ausfällt. Er fügt hinzu, dass das, was du auf einer bestimmten Insel gefunden hast, nur ein winziger Vorgeschmack darauf ist, was du in Tayasal finden würdest.";
			link.l1 = "Ist das so... das ist sehr interessant. Aber warum hat Kapitän Dichoso mich nicht selbst besucht? Warum hat er einen Dritten geschickt?";
			link.l1.go = "Dichoso_agent_5";
		break;
		
		case "Dichoso_agent_5":
			dialog.text = "Don Dichoso hat zuerst auf der Isla Tesoro nach dir gesucht, dann hier, und ist nun auf dem Weg nach St. Christopher in der Hoffnung, dich dort zu finden. Du bist doch ein Offizier von Philippe de Poincy selbst, oder? Ich sollte hier auf dich warten, falls du in Blueweld ankommst.";
			link.l1 = "Dann ist alles klar. Na gut. Ich werde keine Zeit verschwenden, ich sollte nach Capsterville gehen.";
			link.l1.go = "Dichoso_agent_6";
		break;
		
		case "Dichoso_agent_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "Tieyasal_PrepareDichosoTrap", -1);
		break;
		
	// агент Дичозо
		case "Dichoso_crypt_agent":
			dialog.text = "Nun, endlich treffen wir uns, Kapitän "+GetFullName(pchar)+"...";
			if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) 
			{
				link.l1 = "Wo ist Miguel Dichoso? Und versuche nicht, dich aus dieser Sache herauszuwinden. Ich weiß, wer er wirklich ist und ich denke, du weißt es auch.";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "Ich nehme an, das ist Miguel Dichoso höchstpersönlich direkt vor mir?";
				link.l1.go = "Dichoso_crypt_agent_1";
			}
		break;
		
		case "Dichoso_crypt_agent_1":
			dialog.text = "Sie vermuten richtig, Kapitän. Wir sind uns schon lange auf den Fersen, nicht wahr?";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l1 = "Ich kann sehen, dass du lügst, nur indem ich dich anschaue, Kumpel. Du bist nicht Dichoso. Ich habe die Logbucheinträge des Kapitäns der 'Santa Quiteria' gelesen und mich nach seinem Aussehen erkundigt. Du siehst ihm nicht ähnlich. Du hast nicht einmal eine Narbe im Gesicht von einem Kavallerieschwert. Komm schon, selbst ein Pantomime hätte zumindest versucht, es aufzuzeichnen!";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "Genau. Wenn ich es richtig verstehe, sind wir hier, um über die verlorene Stadt Tayasal zu sprechen?";
				link.l1.go = "Dichoso_crypt_agent_7";
			}
		break;
		
		case "Dichoso_crypt_agent_2":
			dialog.text = "Ha! Keinen Sinn, diese Farce fortzusetzen. Miguel hat mich gewarnt, dass du ein schlauer Schelm bist...";
			link.l1 = "Wo ist Miguel Dichoso?";
			link.l1.go = "Dichoso_crypt_agent_3";
		break;
		
		case "Dichoso_crypt_agent_3":
			dialog.text = "Er ist nicht hier. Ich bin befugt, Sie zu treffen und in seinem Namen mit Ihnen zu sprechen.";
			link.l1 = "Ich werde nicht mit einer Spielfigur sprechen. Ich bin hier für den König. Wo ist er?!";
			link.l1.go = "Dichoso_crypt_agent_4";
		break;
		
		case "Dichoso_crypt_agent_4":
			dialog.text = "Nicht gerade ein angenehmer Gesprächspartner, Kapitän. Sie haben Ihre Fassung verloren.";
			link.l1 = "Genug Spiele, ich verstehe es. Es ist wieder ein Hinterhalt. Ihr Jungs müsst euch einige neue Tricks einfallen lassen.";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
		case "Dichoso_crypt_agent_5":
			dialog.text = "Haha, wieder richtig, Kamerad! Meine Männer warten gleich hinter der Tür zu den Katakomben auf dich. Dazu habe ich Musketiere, die hinter jedem Grabstein versteckt sind und bereit zum Schießen. Es gibt kein Entkommen. So repetitiv dieser Trick auch sein mag, du bist direkt hineingeklettert! Dein Wunsch, Tayasal zu sehen, hat deinen gesunden Menschenverstand überwogen!";
			link.l1 = "Du hast einen großartigen Ort für einen Kampf ausgesucht, Abschaum. Ich werde nicht weit gehen müssen, um dich und deine Banditenfreunde zu begraben.";
			link.l1.go = "Dichoso_crypt_agent_6";
		break;
		
		case "Dichoso_crypt_agent_6":
			dialog.text = "Haha! Ich mag deinen Witz! Genau wie Miguel! Sag, was du willst, ihr seid beide vom selben Schlag... Ich werde tun, was er befohlen hat - Ich schicke dich so schnell und schmerzlos wie möglich zur Hölle. Zu den Waffen, Jungs!";
			link.l1 = "Bessere Männer als du haben es versucht. Grüß den Teufel von mir, Schurke!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_StartCryptBattle");
		break;
		
		case "Dichoso_crypt_agent_7":
			dialog.text = "Sie wollen wirklich in die Stadt? Ich verstehe, Kapitän, aber ich denke, das ist keine gute Idee.";
			link.l1 = "Dann worüber sind wir hier zu sprechen?";
			link.l1.go = "Dichoso_crypt_agent_8";
		break;
		
		case "Dichoso_crypt_agent_8":
			dialog.text = "Ich suche kein langes, romantisches Gespräch mit dir. Du bist hier und das ist für mich genug.";
			link.l1 = "Genug der Spielchen, ich verstehe. Es ist wieder ein Hinterhalt. Ihr Burschen müsst euch neue Tricks einfallen lassen.";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
	// командир абордажников
		case "newcastle_officer":
			dialog.text = "Auf Ihre Befehle warten, Kapitän!";
			link.l1 = "Wir gehen durch den Dschungel zum Friedhof von Capsterville. Wenn wir dort ankommen, betretet nicht den Friedhof selbst. Nehmt Schusspositionen direkt vor dem Tor ein und hört genau zu, wenn ich hineingehe. Wenn ihr einen Kampf hört, stürmt sofort hinein.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_0":
			dialog.text = "Ich warte auf Ihre Befehle, Kapitän!";
			link.l1 = "Wir gehen durch den Dschungel zum Friedhof von Capsterville. Sobald wir dort sind, betretet nicht den Friedhof selbst. Nehmt entlang des Pfades Feuerpositionen ein, umzingelt den Friedhof und hört genau zu, wenn ich hineingehe. Dieser ganze Plan stinkt nach einem Hinterhalt. Sobald ihr den Feind seht, greift sofort an.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_1":
			dialog.text = "Aye aye, Kapitän!";
			link.l1 = "In Ordnung. Vorwärts!";
			link.l1.go = "newcastle_officer_2";
		break;
		
		case "newcastle_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Charles_exittown")].DisableEncounters = true; //энкаутеры закрыть
			locations[FindLocation("Charles_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			for(i=2; i<=4; i++)
			{
				locations[FindLocation("Charles_Jungle_0"+i)].DisableEncounters = true; //энкаутеры закрыть
			}
			LocatorReloadEnterDisable("Shore42", "boat", true);
			for(i=1; i<=iTotalTemp; i++)
			{
				sld = characterFromID("Tieyasal_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// на локацию перед кладбищем
			pchar.quest.Tieyasal_newcastle.win_condition.l1 = "location";
			pchar.quest.Tieyasal_newcastle.win_condition.l1.location = "Charles_exittown";
			pchar.quest.Tieyasal_newcastle.function = "Tieyasal_NewcastleGoJungle";
			// на крипту
			pchar.quest.Tieyasal_graveyard.win_condition.l1 = "location";
			pchar.quest.Tieyasal_graveyard.win_condition.l1.location = "Charles_CryptBig2";
			pchar.quest.Tieyasal_graveyard.function = "Tieyasal_InGraveyardCrypt";
		break;

case "Europe":
			PlaySound("Voice\English\military01.wav");
			dialog.text = "Kapitän Hobart! Laut den Informationen unseres Spions verstecken sich Rebellen auf diesem Anwesen. Fünf Dragoner stehen Ihnen zur Verfügung. Durchsuchen Sie das Gebäude und verhaften Sie jeden, der sich dort aufhält! Packen Sie diesen Abschaum nicht mit Samthandschuhen an. Sie handeln im Namen des Königs!";
			link.l1 = "Ja, Herr!";
			link.l1.go = "Europe_1";
		break;
		
		case "Europe_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Europe_SharlieFinal_1", 5);
		break;
		
		//Индеец по квесту "Знакомство с индейцами"
		case "ZsI_ListKakao":
			dialog.text = "Tsk! Sohn des Meeres!";
			link.l1 = "Eh... was? Sprechen Sie mich an?";
			link.l1.go = "ZsI_ListKakao_1";
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "ZsI_ListKakao_1":
			dialog.text = "Richtig. Ich bin Kakaoblatt. Ich habe Geschäfte mit dir, Sohn des Meeres.";
			link.l1 = "Ich weiß nicht, wie Kakao aussieht, oder warum du danach benannt bist. Aber gut, sag mir schnell, was du brauchst.";
			link.l1.go = "ZsI_ListKakao_2";
		break;
		
		case "ZsI_ListKakao_2":
			dialog.text = "Tsk! Du gehst in die Stadt. Kaufe zwei Pistolen und zwei zehn Pulver und Kugeln. Gib sie mir. Es gibt eine Belohnung. Der Sohn des Meeres wird erfreut sein.";
			link.l1 = "Zwei Pistolen und zwanzig Schüsse? Das ist alles? Warum kaufst du sie dann nicht selbst?";
			link.l1.go = "ZsI_ListKakao_3";
		break;
		
		case "ZsI_ListKakao_3":
			dialog.text = "Verstehst du es nicht, Bleichgesicht? Wer würde mir eine Feuerwaffe verkaufen?!";
			if (CheckAttribute(pchar, "questTemp.ZsI_Cannibals"))		//Sinistra Только если проходил квест "Каннибалы"
			{
				link.l1 = "Weißt du, ich bin deinesgleichen schon einmal auf Martinique begegnet... Kannibalen. Sie entführten ein Mädchen und zwei Männer. Sie brieten und aßen einen der Männer. Wenn auch nur einer von ihnen eine Pistole gehabt hätte, hätten wir dieses Gespräch nicht.";
				link.l1.go = "ZsI_ListKakao_3_1";
			}
			else
			{
				link.l1 = "Und warum brauchst du eine Feuerwaffe, Kakaoblatt? Willst du jemanden töten?";
				link.l1.go = "ZsI_ListKakao_3_2";
			}
		break;
		
		case "ZsI_ListKakao_3_1":
			dialog.text = "Goo-oo! Kakaoblatt ist kein Bandit, mein Kampf ist nur für Krieger deines Stammes. Bleichgesichter kommen in unser Land, machen uns zu Sklaven. Kakaoblatt selbst kämpft. Nimm einen Sklaven. Nicht gut, nicht schlecht. So läuft das. Indianer, weiß, kein Unterschied. Feuerwaffen machen einen Unterschied.";
			link.l1 = "Und warum brauchst du eine Feuerwaffe, Koka Blatt? Willst du jemanden töten?";
			link.l1.go = "ZsI_ListKakao_3_2";
		break;
		
		case "ZsI_ListKakao_3_2":
			dialog.text = "Zu kämpfen. Aber zu gleichen Bedingungen. Bleichgesichter haben Feuerwaffen, Indianer nicht. Das ist unfair. Und für einen Indianer eine Feuerwaffe zu haben - es ist ein Schutz gegen ungerechte Behandlung, Demütigung oder Beleidigung durch Bleichgesichter.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_4";
		break;
		
		case "ZsI_ListKakao_4":
			StartInstantDialog("Tichingitu", "ZsI_ListKakao_5", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_5":
			dialog.text = "Richtig, Kapitän. Die Bleichgesichter sehen auf uns herab.";
			link.l1 = "Ich habe es bemerkt. Zurück in Europa predigen sie über die Belehrung der Indianer im wahren Glauben und wie wir alle friedlich auf Plantagen zusammenarbeiten...";
			link.l1.go = "ZsI_ListKakao_7";
		break;
		
		case "ZsI_ListKakao_7":
			dialog.text = "Tichingitu versteht den Kapitän vielleicht nicht, aber er versteht Kakaoblatt. Er sucht Rache.";
			link.l1 = "Scheint so... Willst du nicht auch Rache, gegen unsere kürzlichen Entführer?";
			link.l1.go = "ZsI_ListKakao_8";
		break;
		
		case "ZsI_ListKakao_8":
			dialog.text = "Vielleicht. Aber Tichingitu wird dazu nicht greifen. Tichingitu ist jetzt bei dir. Und Tichingitu benutzt seinen eigenen Kopf. Es wird zu viel Blutvergießen geben. Weißes Blut. Indianer Blut. Zu viel Leiden. Das ist nicht richtig.";
			link.l1 = "Ja, es ist bereits schlimm, und es wird nur noch schlimmer, wenn wir Kakaoblatt dabei helfen, an Waffen zu kommen... Aber er hat einen Punkt. Und ich muss meine Mannschaft bald bezahlen.";
			link.l1.go = "ZsI_ListKakao_9";
		break;
		
		case "ZsI_ListKakao_9":
			dialog.text = "Benutze deinen eigenen Kopf, Kapitän.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_10";
		break;
		
		case "ZsI_ListKakao_10":
			StartInstantDialog("ListKakao", "ZsI_ListKakao_11", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_11":
			dialog.text = "Der Sohn des Meeres redet viel. Sieht aus wie eine Squaw mit einem Schnurrbart.";
			link.l1 = "Wer? Erklär mir das, Kakaoblatt. Ich bin auch ein Bleichgesicht und du fragst mich nach Waffen, um gegen Bleichgesichter zu kämpfen. Ist das nicht widersprüchlich? Warum kommst du auf mich zu?";
			link.l1.go = "ZsI_ListKakao_12";
		break;
		
		case "ZsI_ListKakao_12":
			dialog.text = "Ich habe euer Gespräch mit diesem seltsam gekleideten Indianer belauscht. Ihr seid nicht wie die anderen Bleichgesichter. Ihr versteht Tichingitu. Und ihr versteht sicher auch Kakaoblatt, da bin ich sicher.";
			link.l1 = "Oh... Was bieten Sie für Waffen, Kakaoblatt?";
			link.l1.go = "ZsI_ListKakao_13";
		break;
		
		case "ZsI_ListKakao_13":
			dialog.text = "Die Tränen der Götter. Ihr nennt sie Perlen. Viele Perlen.";
			link.l1 = "Ich habe meine Entscheidung getroffen, Kakaoblatt. Warte hier, ich gehe zum Waffenhändler. Ich werde kaufen, was ich brauche und zurückkommen.";
			link.l1.go = "ZsI_ListKakao_Soglasen_5";
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				link.l2 = "Ich habe meine Entscheidung getroffen, Kakaoblatt. Es stellt sich heraus, dass ich bereits habe, was du brauchst. Hier, bitte.";
				link.l2.go = "ZsI_ListKakao_Soglasen_2";
			}
			link.l3 = "Ich habe meine Entscheidung getroffen, Kakaoblatt. Ich will keinen unnötigen Ärger einladen. Du bekommst keine Feuerwaffen von mir. Zieh weiter.";
			link.l3.go = "ZsI_ListKakao_Otkaz";
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		
		case "ZsI_ListKakao_Otkaz":
			dialog.text = "Tsk!";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Otkaz_2";
		break;
		
		case "ZsI_ListKakao_Otkaz_2":
			DialogExit();
			
			ChangeIndianRelation(-3.0);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "ZsI_Mir", -1);
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 1.0, 1.0);
			npchar.lifeday = 0;
			PChar.quest.ZsI_Draka.win_condition.l1 = "NPC_Death";
			PChar.quest.ZsI_Draka.win_condition.l1.character = "ListKakao";
			PChar.quest.ZsI_Draka.win_condition = "ZsI_Draka";
			PChar.quest.ZsI_Mir.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ZsI_Mir.win_condition.l1.location = PChar.location;
			PChar.quest.ZsI_Mir.win_condition = "ZsI_Mir";
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			sld = characterFromId("Tichingitu");
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.Dialog.CurrentNode = "Tichingitu_officer";
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_2":
			dialog.text = "Uh-oh! Hat der Sohn des Meeres ein Musket? Zahlen Sie einen hohen Preis für ein Musket!";
			link.l1 = "Nein, aber wird eine Kanone von meinem Schiff ausreichen? Verlasse uns jetzt, Kakaoblatt, bevor wir entdeckt und verhaftet werden.";
			link.l1.go = "ZsI_ListKakao_Soglasen_3";
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			ChangeIndianRelation(3.0);
			AddItems(pchar, "jewelry53", 180);
			Log_Info("You have received 180 small pearls");
			PlaySound("Interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
				RemoveItems(PChar, "pistol1", 2);
				RemoveItems(PChar, "GunPowder", 20);
				RemoveItems(PChar, "bullet", 20);
			}
		break;
		
		case "ZsI_ListKakao_Soglasen_3":
			dialog.text = "Guter Handel! Sohn des Meeres, wenn du in den Dschungel gehst, nimm eine Feuerwaffe. Triffst du einen Indianer, sei ein Schnäppchen.";
			link.l1 = "Ich werde das nicht vergessen. Auf Wiedersehen, Kakaoblatt.";
			link.l1.go = "ZsI_ListKakao_Soglasen_4";
		break;
		
		case "ZsI_ListKakao_Soglasen_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			Return_TichingituOfficer();
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_5":
			dialog.text = "Kakaoblatt wird warten.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Soglasen_6";
		break;
		
		case "ZsI_ListKakao_Soglasen_6":
			DoQuestReloadToLocation("BasTer_town", "reload", "gate_back", "ZsI_TPvGorod");
		break;

		case "ZsI_officer":
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				dialog.text = "Ach, es sieht so aus, als hätten wir hier eine Versammlung von Einheimischen!\nWillst du zurück ins Gefängnis, Hund?\nWas machst du hier, Monsieur?";
			}
			else
			{
				dialog.text = "Halt! Was machen Sie hier, Monsieur?";
			}
			link.l1 = "";
			link.l1.go = "ZsI_officer_2";
			sld = CharacterFromID("ListKakao");
			LAi_CharacterEnableDialog(sld);
			EndBattleLandInterface();
		break;
		
		case "ZsI_officer_2":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "He, Abschaum, hast du auf diesen ehrbaren Bürger gewartet?";
			link.l1 = "";
			link.l1.go = "ZsI_officer_3";
		break;
		
		case "ZsI_officer_3":
			DialogExit();
			StartInstantDialog("ListKakao", "ZsI_officer_4", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_4":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ZsI_Patrul_off"));
			dialog.text = "Alle Bleichgesichter sehen für mich gleich aus. Aber diesen hier habe ich noch nie gesehen. Du, Krieger, tu mit mir, was du musst. Es wird mühsam. Kakaublatt ist bereit, den Geistern des Waldes zu begegnen.";
			link.l1 = "";
			link.l1.go = "ZsI_officer_5";
		break;
		
		case "ZsI_officer_5":
			DialogExit();
			StartInstantDialog("ZsI_Patrul_off", "ZsI_officer_6", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_6":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "Hölle erwartet dich, nicht die Geister des Waldes.";
			link.l1 = "";
			link.l1.go = "ZsI_officer_7";
		break;
		
		case "ZsI_officer_7":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			dialog.text = "Kapitän, Sie sind entlassen. Halten Sie sich aus meinem Weg. Die Stadt zu schützen ist ernste Angelegenheit.";
			link.l1 = "Ich verstehe... Aber was ist mit diesem Inder?";
			link.l1.go = "ZsI_officer_8";
		break;
		
		case "ZsI_officer_8":
			dialog.text = "Was ist Ihr Interesse an Indianern, Monsieur? Obwohl... nun, ja, Sie sind frisch aus Europa\nWie geht's in Paris? Quetschen sie immer noch Stadtratten, oder haben sie angefangen, sie zur Kommunion einzuladen? Sie sehen, wir haben Eingeborene statt Ratten. Sie machen Geschäfte mit Freibeutern, greifen Holzfäller an, sie essen Menschen, verdammt noch mal\nVor drei Tagen hat irgendein heller Kopf bereits ein Musketengewehr an so einen verkauft. Und raten Sie mal? Diese Bastarde haben alle Soldaten in der Patrouille getötet, geführt übrigens von meinem Freund und Kameraden. Wir haben den Verräter-Kolonisten gefunden und ihn in der Sonne aufgehängt, um ein Beispiel zu setzen. Feuerwaffen an Indianer zu geben! Das ist Verrat! Verrat an Frankreich! Wir haben diesen farbigen Affen schon eine Weile verfolgt, da er bereits ein vertrautes Gesicht bei verschiedenen Veranstaltungen geworden ist\nNun, jetzt wird er sein schnelles und verdientes Ende finden. Sie können weitermachen, Kapitän. Mischen Sie sich nicht in Angelegenheiten ein, die Sie nichts angehen. Sie sind nicht Teil dieses Krieges... Noch nicht... Oder doch?!";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l1 = "(Vertrauenswürdig) Sehen Sie, Offizier... Ich bin Kapitän Charles de Maure, ein Gast von Fadey Muscovite. Wir haben ein gewisses Interesse an diesem Inder... also lassen Sie uns nicht in die Pflichten des anderen eingreifen. Einverstanden, Leutnant?";
				link.l1.go = "ZsI_officer_Mir";
			}
			link.l2 = "Einstellungen gegenüber Neulingen, Einstellungen gegenüber Einheimischen... Kolonisten, Einheimische... Ich verstehe das Ganze noch nicht so recht, aber in diesem Moment, Leutnant, ist der Vergleich nicht zu Ihren Gunsten... Zum Kampf!";
			link.l2.go = "ZsI_officer_Draka";
			link.l3 = "Sie haben recht, Leutnant, das bin ich nicht. Auf Wiedersehen.";
			link.l3.go = "ZsI_officerKIll";
			StartBattleLandInterface();
		break;
		
		case "ZsI_officer_Mir":
			dialog.text = "Ähem! Verstanden, Kapitän. Bitte richten Sie meinen Gruß an Monsieur Fadey aus. Trupp, setzt die Patrouille fort!";
			link.l1 = "";
			link.l1.go = "ZsI_officer_Mir_2";
		break;
		
		case "ZsI_officer_Mir_2":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_SetImmortal(sld, true);
			LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetActorType(sld);
				sld.lifeday = 0;
				LAi_SetImmortal(sld, true);
				LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			}
			sld = CharacterFromID("ListKakao");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "ZsI_MirFinal";
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Fortune", 30);
		break;
		
		case "ZsI_MirFinal":
			dialog.text = "Oh-oh!";
			link.l1 = "Ja, nun, sogar ich bin überrascht, dass das geklappt hat. Hier sind deine Waren, Kakaoblatt.";
			link.l1.go = "ZsI_MirFinal_2";
		break;
		
		case "ZsI_MirFinal_2":
			dialog.text = "Der Sohn des Meeres spricht gut. Einen Indianer zu retten ist eine große Sache! Große Belohnung!";
			link.l1 = "Wow, das ist eine ziemliche Beute... Und ein Stein mit einem Loch darin, und irgendeine Art von Amulett.";
			link.l1.go = "ZsI_MirFinal_3";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("You have received 180 small pearls");
			Log_info("You have received Amulet 'Cascavella'}");
			Log_info("You have received Ward 'Adder stone'");
			Log_info("You have received 3 Datura herbs");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_MirFinal_3":
			dialog.text = "Hat der Sohn des Meeres ein Musket? Zahle einen hohen Preis für ein Musket!";
			link.l1 = "Nein, aber wird eine Kanone von meinem Schiff es tun? Geh jetzt, Kakaoblatt, bevor wir entdeckt und verhaftet werden.";
			link.l1.go = "ZsI_MirFinal_4";
		break;
		
		case "ZsI_MirFinal_4":
			dialog.text = "Guter Handel! Sohn des Meeres, wenn du in den Dschungel gehst, nimm eine Feuerwaffe. Triffst du einen Indianer, sei ein Handel.";
			link.l1 = "Ich werde mich daran erinnern. Auf Wiedersehen, Kakaoblatt.";
			link.l1.go = "ZsI_MirFinal_5";
		break;
		
		case "ZsI_MirFinal_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetPlayerType(pchar);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "ZsI_officer_Draka":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeCharacterComplexReputation(pchar, "authority", -2);	
			ChangeIndianRelation(5.0);
			ChangeCharacterNationReputation(pchar, FRANCE, -10);
			sld = CharacterFromID("ListKakao");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetImmortal(sld, false);
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "ZsI_officer_Draka_3");
		break;
		
		case "ZsI_Final":
			ChangeIndianRelation(5.0);
			dialog.text = "Uh-oh! Schlechte Entscheidung, Sohn des Meeres. Warum würdest du das tun?";
			link.l1 = "Ugh... Vor fünf Minuten schien es noch richtig... Jetzt bin ich mir nicht mehr so sicher.... Ich habe schließlich meinen eigenen getötet. Was soll ich jetzt tun? Was ist, wenn sie es herausfinden? Scheiße! Scheiße!";
			link.l1.go = "ZsI_Final_2";
		break;
		
		case "ZsI_Final_2":
			dialog.text = "Jetzt wird es einen Überfall geben. Soldaten töten jeden. Zwei Patrouillen nicht zu vergeben. Kakaoblatt rennt. Und du, Sohn des Meeres... warum. Kakaoblatt stirbt sowieso. Die Geister wollen es so.";
			link.l1 = "Oh... Ist unser Geschäft noch auf dem Tisch?";
			link.l1.go = "ZsI_Final_3";
		break;
		
		case "ZsI_Final_3":
			dialog.text = "Schlechte Entscheidung, Sohn des Meeres. Aber danke. Große Belohnung.";
			link.l1 = "Nicht so groß, wenn man alles in Betracht zieht...";
			link.l1.go = "ZsI_Final_4";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("You have received 180 small pearls");
			Log_info("You have received Amulet 'Cascavella'}");
			Log_info("You have received Ward 'Adder stone'");
			Log_info("You have received 3 Datura herbs");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_Final_4":
			dialog.text = "Sohn des Meeres, wenn du überlebst und dann in den Dschungel gehst, nimm eine Feuerwaffe. Triff einen Indianer, sei ein Handel.";
			link.l1 = "Ich werde das für die Zukunft im Hinterkopf behalten. Auf Wiedersehen, Kakaoblatt.";
			link.l1.go = "ZsI_Final_5";
		break;
		
		case "ZsI_Final_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
		break;
		
		case "ZsI_officerKIll":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("ListKakao"));
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("ZsI_officerKIll_1", 0.1);
			DoQuestCheckDelay("ZsI_officerKIll_2", 1.3);
			AddItems(pchar, "pistol1", 2);
			AddItems(pchar, "GunPowder", 20);
			AddItems(pchar, "bullet", 20);
		break;
		
		//Торговец Барбье по квесту "Деньги на деревьях"
		case "MOT_Barbie":
			dialog.text = "Grüße, Kapitän Charles de Maure. Mein Name ist Charles Barbier. Könnte ich einen Moment Ihrer Zeit haben?";
			link.l1 = "Kapitän de Maure... Tatsächlich, das bin ich! Bitte fahren Sie fort, Monsieur Barbier.";
			link.l1.go = "MOT_Barbie_2";
		break;
		
		case "MOT_Barbie_2":
			dialog.text = "Es ist immer ein Vergnügen, einen Kollegen zu treffen, besonders einen, mit dem ich einen Namen teile! Ich habe einen Vorschlag für Sie, Kapitän. Sie sehen, ich benötige eine Eskorte nach St. Pierre, und...";
			link.l1 = "Ich kenne St. Pierre! Aber das ist nur eine zweitägige Reise! Und ich muss gestehen, ich bin noch ziemlich grün für die Rolle eines Begleiters. Ich habe erst vor einer Woche das Kommando über dieses Schiff übernommen.";
			link.l1.go = "MOT_Barbie_3";
		break;
		
		case "MOT_Barbie_3":
			dialog.text = "Ihre Ehrlichkeit wird geschätzt, Kapitän. Charles, verzeihen Sie meine Umgangssprache, aber Sie sind genau die Person, die ich brauche.";
			link.l1 = "Hmm... Ich erinnere mich an einen ähnlichen Vorschlag vor nicht allzu langer Zeit. Er führte zu einem Piratenüberfall in der Nähe von Le Francois.";
			link.l1.go = "MOT_Barbie_4";
		break;
		
		case "MOT_Barbie_4":
			dialog.text = "Ich habe von diesem Vorfall gehört, deshalb habe ich dich gesucht\nErstens, ich transportiere eine ziemlich wertvolle Ladung, und es lauern immer Räuber. Dein jüngster Triumph über die Piraten in der Nähe von Le Francois wird jedoch den Schurken dort eine Pause geben\nZweitens, deine Verbindung mit Fadey Muscovite ist eine starke Empfehlung.";
			link.l1 = "Eine überzeugende Argumentation, Monsieur. Und welche Entschädigung schlagen Sie für diesen Gefallen vor?";
			link.l1.go = "MOT_Barbie_5";
		break;
		
		case "MOT_Barbie_5":
			dialog.text = "Es ist kein Gefallen, Kapitän, sondern ein gegenseitig vorteilhaftes Unterfangen! Ich zahle Ihnen vierzig Goldstücke, um mich rechtzeitig nach St. Pierre zu begleiten.";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l1 = "(Vertrauenswürdig) Da ich in die entgegengesetzte Richtung unterwegs bin, Monsieur, verlange ich Vorauszahlung.";
				link.l1.go = "MOT_Barbie_Torg";
			}
			link.l2 = "Nicht schlecht - Ich bin sowieso in diese Richtung unterwegs. Abgemacht!";
			link.l2.go = "MOT_Barbie_Soglasen";
			link.l3 = "Wertvolle Ladung, sagst du? Bedauerlicherweise, Monsieur, ich habe genug von Abenteuern für den Moment.";
			link.l3.go = "MOT_Barbie_Otkaz";
		break;
		
		case "MOT_Barbie_Torg":
			dialog.text = "Es ist schwer, einem so ernsthaften jungen Mann abzulehnen, Kapitän. Hier sind Ihre vierzig Dublonen. Sollen wir ohne Verzögerung in See stechen? Zeit ist Geld.";
			link.l1 = "Wir werden nicht lange verweilen, Monsieur. Wir werden in Kürze in See stechen.";
			link.l1.go = "MOT_Barbie_Escadra";
			
			AddItems(pchar, "gold_dublon", 40);
			Log_info("You've received 40 doubloons");
			PlaySound("Interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
		break;
		
		case "MOT_Barbie_Soglasen":
			dialog.text = "Ausgezeichnet! Ich werde mich sofort auf die Abreise vorbereiten!";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Escadra";
		break;
		
		case "MOT_Barbie_Otkaz":
			dialog.text = "Ich verstehe, Kapitän. Ich werde mich nicht aufdrängen. Lebewohl und einen guten Tag.";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Otkaz_2";
		break;
		
		case "MOT_Barbie_Otkaz_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload6_back", "none", "", "", "", -1);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_Escadra":
			DialogExit();
			
			SetQuestHeader("MoneyOnTrees");
			AddQuestRecord("MoneyOnTrees", "1");
			
			FantomMakeCoolSailor(npchar, SHIP_BARKENTINE, "Charles", CANNON_TYPE_CANNON_LBS3, 40, 33, 20);
			npchar.Ship.Mode = "trade";
			SetCharacterRemovable(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.CompanionEnemyEnable = true;
			SetCrewQuantity(npchar, 35);
			SetCharacterGoods(npchar, GOOD_ROPES, 30);
			LAi_SetImmortal(npchar, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			SetTimerCondition("MOT_ZadanieProvaleno", 0, 0, 14, false);
			PChar.quest.MOT_Zahvatili.win_condition.l1 = "NPC_Death";
			PChar.quest.MOT_Zahvatili.win_condition.l1.character = "SharlieBarbie";
			PChar.quest.MOT_Zahvatili.win_condition = "MOT_Zahvatili";
			PChar.quest.MOT_Dostavili.win_condition.l1 = "location";
			PChar.quest.MOT_Dostavili.win_condition.l1.location = "FortFrance_town";
			PChar.quest.MOT_Dostavili.win_condition = "MOT_Dostavili";
		break;
		
		case "MOT_Barbie_101":
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				dialog.text = "Danke für Ihre vorbildliche Eskorte, Kapitän. Ich bin froh, dass wir keine Zwischenfälle hatten.";
				link.l1 = "Es war mir ein Vergnügen, Geschäfte mit Ihnen zu machen, Monsieur. Wenn Sie mich nun entschuldigen würden, ich habe viel zu erledigen.";
			}
			else
			{	
				dialog.text = "Vielen Dank für Ihre vorbildliche Eskorte, Kapitän. Ich bin froh, dass wir keine Zwischenfälle hatten. Hier ist Ihre Bezahlung - vierzig Dublonen in voller Höhe.";
				link.l1 = "Es war mir ein Vergnügen, Geschäfte mit Ihnen zu machen, Monsieur. Jetzt, wenn Sie mich entschuldigen, habe ich viel zu erledigen.";
				AddItems(pchar, "gold_dublon", 40);
				Log_info("You've received 40 doubloons");
				PlaySound("Interface\important_item.wav");
			}
			link.l1.go = "MOT_Barbie_102";
		break;
		
		case "MOT_Barbie_102":
			dialog.text = "Charles...";
			link.l1 = "Ja, Charles? Du scheinst beunruhigt. Ist etwas nicht in Ordnung?";
			link.l1.go = "MOT_Barbie_103";
			RemoveCharacterCompanion(pchar, npchar);
			npchar.lifeday = 0;
		break;
		
		case "MOT_Barbie_103":
			dialog.text = "Nun, da du eine zuverlässige Person bist und Fadey kennst... Schau, Handel ist ein riskantes Geschäft, nicht wahr?";
			link.l1 = "Wenn du meinst.";
			link.l1.go = "MOT_Barbie_104";
		break;
		
		case "MOT_Barbie_104":
			dialog.text = "Ich habe es geschafft, eine Ladung Seile auf Guadeloupe zu einem Schnäppchenpreis von... du weißt schon. Ich hatte vor, sie schnell in St. Pierre zu verkaufen und den Erlös für den Kauf von Kaffee zum Weiterverkauf in Willemstad zu verwenden. Es schien ein solider Plan zu sein.";
			link.l1 = "Ich bezweifle nicht Ihre Integrität, Monsieur, aber das klingt alles ziemlich zweifelhaft. Sie sprechen von Ihrer Ladung, als wäre sie aus Gold. Unterdessen ist mein Schiff mit diesen Seilen beladen und sie sind spottbillig.";
			link.l1.go = "MOT_Barbie_106";
		break;
		
		case "MOT_Barbie_106":
			dialog.text = "Charles, diese Seile sind von feinster Qualität, gefertigt aus überlegenem Hanf und gewebt in den Fabriken des Moskauer Zaren. Sie dienen strategischen Zwecken und werden in der Takelage von Kriegsschiffen verwendet. Die Engländer monopolisieren Handelsrouten mit Moskau, was den freien Handel solcher Seile verbietet. Andere Nationen bemühen sich intensiv, die gesamte verfügbare Menge für ihre Werften in Europa zu sichern.";
			link.l1 = "Also, das ist Schmuggel?";
			link.l1.go = "MOT_Barbie_107";
		break;
		
		case "MOT_Barbie_107":
			dialog.text = "Yes. Unfortunately, I had a falling out with Santiago smugglers last year. I had nearly forgotten about it, but these individuals maintain close connections and long memories. Here's a piece of advice: avoid incensing them and reneging on deals; it's a situation you won't rectify later.";
			link.l1 = "Danke, aber Schmuggel interessiert mich nicht.";
			link.l1.go = "MOT_Barbie_108";
		break;
		
		case "MOT_Barbie_108":
			dialog.text = "Schade! Ehrlicher Handel kann Ihnen einen hübschen Gewinn bringen, aber Sie werden nie ein beträchtliches Vermögen anhäufen. Trotzdem habe ich dieses eher heikle Gespräch mit Ihnen nicht ohne Grund begonnen. Ich schlage vor, Sie kaufen eine Ladung Seile von mir. Lokale Schmuggler besuchen häufig die Taverne, und sie werden eifrige Käufer für diese Fracht sein. Stellen Sie sich das vor! Sie werden heute einen beträchtlichen Gewinn erzielen, ohne sich auf die offene See zu wagen.";
			link.l1 = "Wie viel verlangen Sie für die Ladung?";
			link.l1.go = "MOT_Barbie_109";
		break;
		
		case "MOT_Barbie_109":
			dialog.text = "Zehntausend Pesos. Es ist eine bescheidene Summe, und der Weiterverkauf der Seile an Schmuggler wird beträchtliche Gewinne bringen.";
			if (sti(pchar.Money) >= 10000)
			{
				link.l1 = "Ich könnte es mir nie verzeihen, wenn ich eine solche Gelegenheit verpassen würde. Nehmt das Silber und sorgt dafür, dass die Ware prompt an mein Schiff geliefert wird.";
				link.l1.go = "MOT_Barbie_ContraSoglasen";
			}
			if (sti(pchar.Money) >= 7000)
			{
				link.l2 = "Das ist ein heikles Unterfangen, mein Freund. Lassen wir uns auf halbem Weg treffen, ja? Ich nehme deine Seile für siebentausend.";
				link.l2.go = "MOT_Barbie_ContraTorg";
			}
			link.l3 = "Das ist eine beträchtliche Summe, Monsieur. Ich sympathisiere mit Ihrer misslichen Lage, aber ich kann ein solches Risiko nicht eingehen.";
			link.l3.go = "MOT_Barbie_ContraOtkaz";
		break;
		
		case "MOT_Barbie_ContraSoglasen":
			dialog.text = "Mein Dank, Charles! Du hast mich vor dem finanziellen Ruin bewahrt! Die Waren werden schnell und mit größter Vorsicht versandt\nErlaube mir, dir einen Ratschlag als Kollege Kaufmann zu geben: sobald du einen anständigen Zahlmeister eingestellt hast, beschaffe Kaffee in Saint-Pierre und verkaufe ihn mit Gewinn in Willemstad. Lokale Kapitale zahlen großzügig für Kolonialwaren, um sie mit erheblichem Gewinn nach Europa zu exportieren. Viel Glück bei deinen Unternehmungen, Freund!";
			link.l1 = "Auf Wiedersehen, Monsieur.";
			link.l1.go = "MOT_Barbie_ContraSoglasen_2";
			AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
			AddMoneyToCharacter(pchar, -10000);
			Log_info("You've received 30 ropes");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "MOT_Barbie_ContraSoglasen_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "5");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_ContraTorg":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 30)
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				dialog.text = "Mein Dank, Charles! Du hast mich vor dem finanziellen Ruin bewahrt! Die Waren werden schnell und mit größter Vorsicht versandt\nErlaube mir, dir einen Rat als Mitkaufmann zu geben: Sobald du einen anständigen Zahlmeister angestellt hast, beschaffe Kaffee in Saint-Pierre und verkaufe ihn mit Gewinn in Willemstad. Die lokalen Kapitalisten zahlen für Kolonialwaren gutes Geld und exportieren sie mit erheblichem Gewinn nach Europa. Viel Erfolg bei deinen Unternehmungen, Freund!";
				link.l1 = "Auf Wiedersehen, Monsieur.";
				link.l1.go = "MOT_Barbie_ContraSoglasen_2";
				AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
				AddMoneyToCharacter(pchar, -7000);
				Log_info("You've received 30 ropes");
				PlaySound("Interface\important_item.wav");
			}
			else
			{
				notification("Skill Check Failed (31)", SKILL_COMMERCE); 
				dialog.text = "Ich kann nicht, Kapitän. Meine Ware ist ernst und erfordert ernsthafte Behandlung. Die meisten freien Kapitäne wagen es nicht, mit strategischen Gütern zu handeln. Leider ist hier kein Handeln gerechtfertigt.";
				if (sti(pchar.Money) >= 10000)
				{
					link.l1 = "Ich würde es mir nie verzeihen, wenn ich eine solche Gelegenheit verpassen würde. Nimm das Silber und stelle sicher, dass die Waren prompt an mein Schiff geliefert werden.";
					link.l1.go = "MOT_Barbie_ContraSoglasen";
				}
				link.l2 = "Das ist eine beträchtliche Summe, Monsieur. Ich sympathisiere mit Ihrer misslichen Lage, aber ich kann ein solches Risiko nicht eingehen.";
				link.l2.go = "MOT_Barbie_ContraOtkaz";
			}
		break;
		
		case "MOT_Barbie_ContraOtkaz":
			dialog.text = "Schade! Auf Wiedersehen, Kapitän.";
			link.l1 = "";
			link.l1.go = "MOT_Barbie_ContraOtkaz_2";
		break;
		
		case "MOT_Barbie_ContraOtkaz_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "4");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		//Миниквест "Делюк"
		//Матрос Алонсо
		case "Del_Alonso":
			dialog.text = "Ärger, Käpt’n.";
			link.l1 = "Nun?";
			link.l1.go = "Del_Alonso_2";
		break;
		
		case "Del_Alonso_2":
			dialog.text = "Unser Navigator wurde verhaftet und in die örtlichen Verliese gebracht. Sie sagen, es sei eine Schuldenangelegenheit.";
			link.l1 = "Was, schon wieder?!";
			link.l1.go = "Del_Alonso_3";
		break;
		
		case "Del_Alonso_3":
			dialog.text = "Er ist ein Schelm, Kapitän.";
			link.l1 = "Was für ein schrecklicher Zeitpunkt! Ohne einen Navigator sind wir hier gestrandet. Ich muss ihn schon wieder raushauen! Ich werde mit dem Kommandanten sprechen...";
			link.l1.go = "Del_Alonso_4";
		break;
		
		case "Del_Alonso_4":
			dialog.text = "Erlaubnis zu sprechen, Kapitän?";
			link.l1 = "Mach weiter.";
			link.l1.go = "Del_Alonso_5";
		break;
		
		case "Del_Alonso_5":
			dialog.text = "Warum all diese Mühe? Ein Mann wie er wird nur Ärger auf das Schiff bringen.";
			link.l1 = "Habe ich eine Wahl? Es sind kaum andere Navigatoren verfügbar, also sind meine Optionen eher begrenzt.";
			link.l1.go = "Del_Alonso_6";
		break;
		
		case "Del_Alonso_6":
			dialog.text = "Wahrlich, ein erstklassiger Navigator ist schwer zu finden, aber du brauchst noch keinen Meister, nur einen kompetenten. Deine Situation hat sich in der vergangenen Woche geändert, das weißt du, oder? Du musst nicht mehr das Fass bis zum Boden ausschaben, um Männer für deine Crew zu finden. Die Leute reden jetzt darüber, wie du diesen Piraten besiegt hast und über die Verbindungen, die du hast. Die Crew steht auch hinter dir, Kapitän, wir mögen dich.";
			link.l1 = "Das beruhigt, Alonso. Und was denkt die Mannschaft über Deluc?";
			link.l1.go = "Del_Alonso_7";
		break;
		
		case "Del_Alonso_7":
			dialog.text = "Sie lernen schnell, Käpt’n. Die Mannschaft meint, er ist zwar ein fähiger Offizier und behandelt uns gut, aber der Aufwand lohnt nicht. Ein großer Händler hat gerade Offiziere entlassen – vielleicht schauen Sie in der Taverne? Da findet sich sicher jemand. Und Deluc vergessen Sie besser – so denken die Leute.";
			link.l1 = "Danke für den Rat, Alonso. Ich wusste, ich kann mich auf dich verlassen. Geh zurück aufs Schiff und übernimm die Wache, während ich das kläre.";
			link.l1.go = "Del_Alonso_8";
		break;
		
		case "Del_Alonso_8":
			dialog.text = "Jawohl!";
			link.l1 = "...";
			link.l1.go = "Del_Alonso_9";
		break;
		
		case "Del_Alonso_9":
			DialogExit();
			SetQuestHeader("FolkeDeluc");
			AddQuestRecord("FolkeDeluc", "1");
			
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			SetFunctionLocationCondition("FortfranceJailOff_AddQuestMark", "fortfrance_prison", false);
			QuestCloseSeaExit();
			sld = CharacterFromID("Folke");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_Folke_1";
			RemovePassenger(pchar, sld);
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "FortFrance_prison", "goto", "goto9");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.questTemp.Del_Deluck = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("Del_shturman", "mercen_4", "man", "man", 5, FRANCE, 3, false, "quest"));
			GiveItem2Character(sld, "blade_03");
			EquipCharacterByItem(sld, "blade_03");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_shturman";
			LAi_SetSitType(sld);
			sld.greeting = "officer_hire";
			SetSelfSkill(sld, 21, 23, 18, 33, 25);
			SetShipSkill(sld, 25, 10, 8, 6, 35, 11, 13, 25, 14);
			SetSPECIAL(sld, 7, 10, 6, 8, 7, 8, 4);
			sld.rank = 5;
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "BasicDefense");
			//sld.quest.officertype = "navigator";
			FreeSitLocator("FortFrance_tavern", "sit4");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit4");
			AddLandQuestMark(characterFromId("Del_shturman"), "questmarkmain");
		break;
		
		//Делюк
		case "Del_Folke_1":
			DelLandQuestMark(npchar);
			dialog.text = "Kap...";
			link.l1 = "Ich habe eine Million Fragen, aber ich werde nur diese stellen: Wie hast du es geschafft, neue Schulden anzuhäufen, während du die ganze Zeit bei mir warst und mir die Seemannschaft beigebracht hast!";
			link.l1.go = "Del_Folke_2";
		break;
		
		case "Del_Folke_2":
			dialog.text = "Es ist mir peinlich, es zuzugeben, Kapitän, aber ich habe schon lange vor meinem Eintritt in Ihre Mannschaft von verschiedenen Geldgebern geliehen. Mein Plan war, mich zu verstecken und auf Ihrem Schiff zu arbeiten, bis ich genug verdient hatte, um all meine Schulden zu begleichen. Aber ich habe den Fehler gemacht, das Schiff hier zu verlassen, um mich mit einer bestimmten Frau hier in St. Pierre einzulassen, und die Soldaten haben mich direkt unter ihr festgenommen. Ich habe keine neuen Schulden in Martinique gemacht, seit Sie meine letzte bezahlt haben, das schwöre ich!";
			link.l1 = "Du bist ein Idiot, Deluc, und du hast mich zum Gespött von St. Pierre gemacht!";
			link.l1.go = "Del_Folke_3a";
			link.l2 = "Beeindruckend, Folke. Danke für die Anekdote.";
			link.l2.go = "Del_Folke_3b";
		break;
		
		case "Del_Folke_3a":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "Was werden Sie tun, Kapitän? Können Sie mich wieder raushauen? Einen neuen Navigator zu finden wird nicht einfach sein, wissen Sie...";
			link.l1 = "Bleib vorerst stehen. Ich werde eine Entscheidung treffen. Ich könnte den Bankier wieder besuchen.";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_3b":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "Was werden Sie tun, Kapitän? Können Sie mich wieder raushauen? Einen neuen Navigator zu finden wird nicht einfach sein, wissen Sie...";
			link.l1 = "Bleib vorerst wo du bist. Ich werde eine Entscheidung treffen. Ich könnte den Bankier noch einmal besuchen.";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_4":
			dialog.text = "Es ist nicht so, als hätte ich einen Ort, an den ich gehen könnte...";
			link.l1 = "...";
			link.l1.go = "Del_Folke_5";
		break;
		
		case "Del_Folke_5":
			DialogExit();
			
			pchar.questTemp.Del_Rostovshik = true;
			LAi_CharacterDisableDialog(npchar);
			AddLandQuestMark(characterFromId("FortFrance_usurer"), "questmarkmain");
		break;
		
		case "Del_Folke_10":
			dialog.text = "Kapitän, danke. Sie haben meine Schulden beglichen, aber jetzt schulde ich Ihnen eine noch größere Schuld - mein Leben. Und dafür bin ich wirklich dankbar! Ich versichere Ihnen, Sie werden nirgendwo auf dieser Welt einen treueren Mann finden!";
			link.l1 = "Ich vermute, einige Schulden können nur durch das Aufnehmen anderer Schulden beglichen werden. Lass uns weiterarbeiten, Folke. Auf See gibt es noch viel zu tun.";
			link.l1.go = "Del_Folke_11a";
			link.l2 = "Vergiss das nicht, Deluc. Das nächste Mal schieße ich einfach auf dich.";
			link.l2.go = "Del_Folke_11b";
			
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			QuestOpenSeaExit()
			sld = CharacterFromID("Del_shturman");
			sld.lifeday = 0;
			
			sld = CharacterFromID("Del_Ohranik");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", -1);
		break;
		
		case "Del_Folke_11a":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "Aye aye, Kapitän!";
			link.l1 = "...";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_11b":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "Aye aye, Kapitän!";
			link.l1 = "...";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_12":
			DialogExit();
			EndQuestMovie();
			AddQuestRecord("FolkeDeluc", "3");
			CloseQuestHeader("FolkeDeluc");
			
			ChangeCharacterComplexReputation(pchar, "authority", -2);
			AddCrewMorale(Pchar, -30);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.location = "None";
			npchar.Dialog.CurrentNode = "hired";
			npchar.Payment = true;
			SetCharacterPerk(npchar, "ByWorker");
			DeleteAttribute(npchar, "CompanionDisable");
		break;
		
		//Штурман из таверны. Стандартный диалог, но с некоторыми изменениями (обучение найма для новичков)
		case "Del_shturman":
			dialog.text = "Brauchen Sie einen Offizier, Kapitän?";
    		Link.l1 = "Ein Offizier? Und was können Sie gut?";
    		Link.l1.go = "Del_Node_2";
			Link.l2 = "Nein, ich habe das volle Set.";
			Link.l2.go = "Exit";
			NextDiag.TempNode = "Del_OnceAgain";
		break;		
		case "Del_Node_2":
			dialog.text = "Ich bin der beste Navigator in diesen Gewässern. Ich kenne mich noch ein wenig mit Medizin aus. Und ich bin bereit, Ihnen einen Gefallen zu tun und unter Ihnen zu dienen.";
			Link.l1 = "Und wie viel wollen Sie?";
			Link.l1.go = "Del_price";
			Link.l2 = "Und was für ein Spezialist sind Sie?";
			Link.l2.go = "Del_ShowParam_exit";
			Link.l3 = "Ach, ich habe bereits einen Navigator.";
			Link.l3.go = "Exit";
		break;		
		case "Del_price":
			dialog.text = "Ich denke, wir können uns auf 4000 Pesos einigen.";
			Link.l1 = "Ist das nicht ein bisschen zu viel?";
			Link.l1.go = "Del_trade";
			Link.l2 = "Ich stimme zu. Betrachten Sie sich als Teil der Besatzung.";
			Link.l2.go = "Del_hire";
			Link.l3 = "Du bist dieses Geld nicht wert.";
			Link.l3.go = "exit";
		break;	
		case "Del_ShowParam_exit":
			NextDiag.TempNode = "Del_OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;		
		case "Del_OnceAgain":
			NextDiag.TempNode = "Del_OnceAgain";
			dialog.text = "Haben Sie Ihre Meinung geändert, Kapitän? Beschlossen, dass ein neuer Navigator nicht schaden würde?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "So etwas. Wie viel möchtest du?";
                Link.l1.go = "Del_price";
			}
			Link.l2 = "Und was kannst du?";
			Link.l2.go = "Del_ShowParam_exit";
			// boal <--
			Link.l3 = "Ich habe ein volles Set. Wir sehen uns.";
			Link.l3.go = "exit";
		break;		
		case "Del_trade":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 25)
			{
				dialog.text = "Also gut... Ich denke, ich könnte sogar mit 2500 Pesos einverstanden sein. Was sagst du dazu?";
				Link.l1 = "So ist es besser. Du bist drin.";
				Link.l1.go = "Del_hire";
				pchar.questTemp.Del_SniziliTsenu = true;
			}
			else
			{
				dialog.text = "Es tut mir leid, Kapitän, aber ich bin genau so viel wert, wie ich verlangt habe. Wenn es Ihnen zu viel ist, dann suchen Sie jemand anderen.";
				Link.l1 = "Also gut, ich stimme zu. Ich nehme dich mit.";
				Link.l1.go = "Del_hire";				
				Link.l2 = "Das ist es, was ich vorhabe zu tun. Lebewohl.";
				Link.l2.go = "exit";
			}
		break;		
		case "Del_hire":
			if (CheckAttribute(pchar, "questTemp.Del_SniziliTsenu"))
			{
				if (sti(pchar.Money) >= 2500)
				{
					AddMoneyToCharacter(pchar, -2500);
					NextDiag.TempNode = "OnboardSoon";
					dialog.text = "Danke, Kapitän. Sie werden Ihre Wahl nicht bereuen.";
					Link.l1 = "Ich hoffe es.";
					Link.l1.go = "Del_Exit_hire";
					DeleteAttribute(pchar, "questTemp.Del_SniziliTsenu");
				}
				else
				{
					dialog.text = "Ich sehe, Ihnen fehlt das Geld, Kapitän! Es tut mir leid, aber ich arbeite nicht auf Kredit.";
					Link.l1 = "Ach, Teufel!";
					Link.l1.go = "Exit";								
				}
			}
			else
			{
				if (sti(pchar.Money) >= 4000)
				{
					AddMoneyToCharacter(pchar, -4000);
					NextDiag.TempNode = "Del_OnboardSoon";
					dialog.text = "Danke, Kapitän. Sie werden Ihre Wahl nicht bereuen.";
					Link.l1 = "Ich hoffe es.";
					Link.l1.go = "Del_Exit_hire";
				}
				else
				{
					dialog.text = "Ich sehe, Ihnen fehlt es an Geld, Kapitän! Es tut mir leid, aber ich arbeite nicht auf Kredit.";
					Link.l1 = "Oh, Teufel!";
					Link.l1.go = "Exit";								
				}
			}
		break;
		case "Del_OnboardSoon":			
			NextDiag.TempNode = "Del_OnboardSoon";
			dialog.text = "Ich trinke nur noch meinen Drink aus, Kapitän, und dann gehe ich zum Schiff. Mach dir keine Sorgen, ich werde rechtzeitig da sein.";
			Link.l1 = "Also gut. Wenn du zu spät kommst, lasse ich dich das Deck schrubben!";
			Link.l1.go = "Exit";											
		break;
		case "Del_exit_hire":
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.Dialog.CurrentNode = "hired";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NPChar.quest.meeting = true;
			npchar.loyality = 18;
			
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			AddCrewMorale(Pchar, 30);
			QuestOpenSeaExit();
			DelLandQuestMark(npchar);
			pchar.quest.FortfranceJailOff_AddQuestMark.over = "yes";
			if (GetCharacterIndex("FortFranceJailOff") != -1)
			{
				DelLandQuestMark(characterFromId("FortFranceJailOff"));
			}
			sld = CharacterFromID("Folke");
			LAi_CharacterDisableDialog(sld);
			DeleteAttribute(pchar, "questTemp.Del_Deluck");
			DeleteAttribute(pchar, "questTemp.Del_DeluckSvoboda");
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik");
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik_repeat");
			pchar.questTemp.Del_DeluckSiditTurma = true;
			AddQuestRecord("FolkeDeluc", "4");
			CloseQuestHeader("FolkeDeluc");
			DialogExit();
		break;
		
		//Квест "Травля крысы"
		//Капитан корабля Хейтер
		case "TK_Kapitan":
			dialog.text = "Also gut, also gut! Ich gebe auf, verdammt noch mal!";
			link.l1 = "Du bist jetzt mein Gefangener, aber du wirst dich bald in St. Pierre vor dem Galgen wiederfinden.";
			link.l1.go = "TK_Kapitan_1";
			PChar.quest.TK_Potopil.over = "yes";
		break;
		
		case "TK_Kapitan_1":
			dialog.text = "Also ist es das... Wie wusstest du, wo du mich finden kannst?";
			link.l1 = "Der Gouverneur hat mich persönlich über die Situation informiert.";
			link.l1.go = "TK_Kapitan_2";
		break;
		
		case "TK_Kapitan_2":
			dialog.text = "Was für ein Trottel! Er muss von meinen Plänen erfahren haben und hat sich entschieden, mich ganz offen direkt vor seiner Höhle zu ficken, um ein Beispiel für andere Crews zu setzen!";
			link.l1 = "Noch eine Beleidigung gegen Seine Exzellenz, und Ihre Reise nach St. Pierre wird schnell und unvergesslich sein.";
			link.l1.go = "TK_Kapitan_3";
		break;
		
		case "TK_Kapitan_3":
			dialog.text = "Eh? Ich rede nicht von Eurer Exzellenz, Kumpel. Ich rede von Jacques dem Goodman\nVerdammt, die Gerüchte waren wahr! Barbazon hat erkannt, dass ich eine Bedrohung wurde, also hat er mich dem Gouverneur übergeben, um mich aus dem Weg zu räumen. Deshalb hattest du meinen genauen Standort - und hast mich mit heruntergelassenen Hosen erwischt, ha ha!";
			link.l1 = "Du bist verrückt. Der Gouverneur von Martinique würde sich nicht herablassen, mit einem Piratenführer zu verhandeln!";
			link.l1.go = "TK_Kapitan_4";
		break;
		
		case "TK_Kapitan_4":
			dialog.text = "Ja, genau. Vielleicht nicht direkt, aber ich denke, er hat einen Deal mit Barbazon gemacht. Es ist praktisch für ihn: Ein gefährlicher Pirat wird gehängt, Berichte sehen gut aus und die 'Ausgaben für die militärische Operation' sind gerechtfertigt. Ich habe gedient, weißt du? Also weiß ich, wie es dort läuft. Und du? Dienst du in der Garnison?";
			link.l1 = "Ich diene meinem Land, und dieses Gespräch ist beendet. Willkommen im Gefängnis.";
			link.l1.go = "TK_Kapitan_5";
		break;
		
		case "TK_Kapitan_5":
			dialog.text = "Halt ein, Kumpel. Ich bin kein Kastilier und ich war heute nicht auf See, um französische Händler zu plündern. Ich habe Prinzipien, verdammt noch mal! Lassen wir einen Deal machen, sollen wir?";
			link.l1 = "Du verschwendest deinen Atem, Pirat. Ab in den Kerker mit dir.";
			link.l1.go = "TK_Kapitan_7_1";
			link.l2 = "Versuchst du, dem Galgen zu entkommen?";
			link.l2.go = "TK_Kapitan_6";
		break;
		
		case "TK_Kapitan_6":
			dialog.text = "Ich hatte hier einen festen Vorsprung, und ich werde dich einbeziehen, wenn du mich gehen lässt. Mein Leben ist nur ein paar tausend Silberstücke wert, aber ich kann dir viel mehr machen - und steuerfrei.";
			if (CheckAttribute(pchar, "questTemp.MOT_SharlyBad"))
			{
				link.l1 = "Das ist ein verlockendes Angebot... Obwohl Piraterie nicht gerade meine Stärke ist.";
				link.l1.go = "TK_Kapitan_7";
			}
			else
			{
				link.l1 = "Ich bin kein Pirat!";
				link.l1.go = "TK_Kapitan_7";
			}
		break;
		
		case "TK_Kapitan_7":
			dialog.text = "Es liegt an dir, Kumpel. Ob du ein Mann des Glücks oder ein mittelloser Kapitän mit Prinzipien sein willst. Wenn du echtes Geld und Freiheit willst, musst du dich ein bisschen mit allem beschäftigen. Nutze jede Gelegenheit.";
			link.l1 = "Du hast sicherlich eine Art mit Worten umzugehen...";
			link.l1.go = "TK_Kapitan_8";
			link.l2 = "Ähem... Ich nehme an, ich bringe dich nach St. Pierre. Das scheint das Richtige zu tun.";
			link.l2.go = "TK_Kapitan_7_1";
		break;
		
		case "TK_Kapitan_7_1":
			dialog.text = "Dann fick dich!";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Plen";
		break;
		
		case "TK_Kapitan_8":
			dialog.text = "Also, haben wir einen Deal?";
			link.l1 = "Ja. Sag mir, wer deine Führung ist, und du bist frei zu gehen.";
			link.l1.go = "TK_Kapitan_9";
		break;
		
		case "TK_Kapitan_9":
			dialog.text = "Es gibt einen schlauen Engländer von der Henry, einer Bark. Er steht kurz davor, seine kleine Handelsreise zu beenden, indem er Waren von französischen Plantagen nach Willemstad für einen stattlichen Gewinn bringt. Er verlässt Martinique bald Richtung Curacao. Es ist eine leichte Aufgabe - keine Eskorte, und die Bark ist voller Wertsachen auf Kosten ihrer Verteidigung. Er braucht zu lange, also verbreiten sich Gerüchte. Mein Rat, Kumpel? Sei nicht schüchtern in der Taverne. Ein paar Drinks für die Einheimischen, und sie werden einige Geheimnisse preisgeben.";
			link.l1 = "Warum keine Eskorte?";
			link.l1.go = "TK_Kapitan_10";
		break;
		
		case "TK_Kapitan_10":
			dialog.text = "Wie sonst sollte ein Engländer seine Geschäfte ruhig in Curacao führen? Es ist ein offener Krieg zwischen England und den Niederlanden, und eine Handelslizenz zu bekommen ist mühsam und teuer.";
			link.l1 = "Aber es gibt keinen Krieg zwischen Frankreich und England. Was sind die Konsequenzen, wenn ich ein neutrales Schiff angreife?";
			link.l1.go = "TK_Kapitan_11";
		break;
		
		case "TK_Kapitan_11":
			dialog.text = "Keines, wenn du diskret bist. Die Crew wird definitiv in dem nächsten Hafen über deine Heldentaten prahlen, aber solange du nicht regelmäßig englische oder holländische Schiffe überfällst, solltest du in Ordnung sein. Nähert euch der Henry unter französischer Flagge. Ladet eure Kanonen mit Traubenhagel, verringert die Distanz, setzt die Schwarze ein, feuert ein paar Salven ab und entert die Schlampe. Es ist einfach, Kumpel.";
			link.l1 = "Wir werden sehen. Ich werde mein Wort halten und dich freilassen. Gib mir keinen Grund, es zu bereuen.";
			link.l1.go = "TK_Kapitan_12";
		break;
		
		case "TK_Kapitan_12":
			dialog.text = "Ich werde nicht. Gute Jagd, Kumpel.";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Otpustil";
		break;
		
		case "TK_Kapitan_Plen":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.DontRansackCaptain = true;
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter2", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, false, "pirate"));
			sld.name = "Daniel";
			sld.lastname = "Montbars";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto7");
			LAi_SetGroundSitType(sld);
			LAi_CharacterDisableDialog(sld);
			DoQuestCheckDelay("TK_KapitanSidit_1", 0.8);
		break;
		
		case "TK_Kapitan_Otpustil":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetCitizenType(sld);
			sld.lifeday = 0;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			pchar.questTemp.TK_Otpustil = true;
			AddQuestRecord("TravlyaKrys", "4");
			
			SetTimerCondition("TK_GenrihSpawn", 0, 0, 1, false);	
		break;
		
		//Диего и Гийом за столиком по квесту "Встреча с Диего"
		case "VsD_DiegoAndErnat":
			dialog.text = "... Ich werde mich um deine Glücksspielprobleme kümmern. Hey! Reiß dich zusammen, Mann! Entweder du reißt dich zusammen oder ich schüttele selbst etwas Vernunft in dich hinein.";
			link.l1 = "";
			link.l1.go = "VsD_DiegoAndErnat_2";
			sld = CharacterFromID("GiumDyubua");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "VsD_DiegoAndErnat_2":
			DialogExit();
			StartInstantDialogNoType("GiumDyubua", "VsD_DiegoAndErnat_3", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "VsD_DiegoAndErnat_3":
			dialog.text = "Herr, entschuldigen Sie, aber Sie sind ein bisschen lästig.";
			link.l1 = "Ja, natürlich. Habt einen angenehmen Tag, meine Herren.";
			link.l1.go = "VsD_DiegoAndErnat_4";
		break;
		
		case "VsD_DiegoAndErnat_4":
			DialogExit();
			sld = CharacterFromID("Diego");
			LAi_CharacterDisableDialog(sld);
			sld = CharacterFromID("GiumDyubua");
			LAi_CharacterDisableDialog(sld);
		break;
		
		//Гийом Дюбуа по квесту "Встреча с Диего"
		case "VsD_GiumDyubua":
			dialog.text = "Kapitän de Maure! Warte!";
			link.l1 = "Ja, Leutnant?";
			link.l1.go = "VsD_GiumDyubua_2";
			DelLandQuestMark(npchar);
		break;
		
		case "VsD_GiumDyubua_2":
			dialog.text = "Ich konnte kaum mit dir mithalten. Es gab... ein kleines Problem, Kapitän. Was für ein Durcheinander!";
			link.l1 = "Atme tief ein und beruhige dich bitte.";
			link.l1.go = "VsD_GiumDyubua_3";
		break;
		
		case "VsD_GiumDyubua_3":
			dialog.text = "Stimmt, stimmt. Hör zu, nachdem wir die Kanonen geladen haben, ist noch Platz im Laderaum?";
			link.l1 = "Ich bin noch neu dabei, also nicht ganz sicher, aber ich gehe davon aus, dass es so sein sollte.";
			link.l1.go = "VsD_GiumDyubua_4";
		break;
		
		case "VsD_GiumDyubua_4":
			dialog.text = "Ausgezeichnet! Das Kommando möchte die Operation in Porto Bello auf jede mögliche Weise unterstützen, daher haben sie die Lieferung von zusätzlichen zweihundert Maß Schießpulver an die Kriegsähnliche angeordnet. Es mag nicht viel erscheinen, aber ein paar zusätzliche Salven könnten das Blatt der Schlacht wenden!";
			link.l1 = "Sehr gut, Leutnant. Ich bin bereit, meinen Teil zu tun. Ladet das Pulver - es macht mir überhaupt nichts aus.";
			link.l1.go = "VsD_GiumDyubua_5";
		break;
		
		case "VsD_GiumDyubua_5":
			dialog.text = "Danke, Kapitän. Ich werde unsere Ladebesatzung sofort informieren. Glücklicherweise haben sie noch nicht mit der '"+PChar.Ship.Name+"' noch nicht. Viel Glück bei deiner Mission!";
			link.l1 = "Danke, obwohl es bisher ziemlich chaotisch war. Auf Wiedersehen, Leutnant.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("VsD_GoToCity");
		break;
		
		//Фульк или Алонсо по квесту "Встреча с Диего"
		case "VsD_FolkeAlonso":
			dialog.text = "Jesus, Kapitän! Dank dem Himmel, du bist unversehrt!";
			link.l1 = "Was zum Teufel ist passiert?! Was ist mit meinem Schiff passiert?!";
			link.l1.go = "VsD_FolkeAlonso_2";
		break;
		
		case "VsD_FolkeAlonso_2":
			dialog.text = "Ich weiß nicht, Kapitän! Ich habe mich gerade von einer lokalen Frau verabschiedet, die ich kürzlich getroffen habe... Oh Scheiße! Eugenie!";
			link.l1 = "Sie ist tot, "+npchar.name+". Es tut mir leid, aber wir müssen uns konzentrieren und sehen, ob jemand aus unserer Besatzung verletzt ist.";
			link.l1.go = "VsD_FolkeAlonso_3";
		break;
		
		case "VsD_FolkeAlonso_3":
			dialog.text = "Wir kannten uns kaum... Aaah! Verdammt! Meldung, Kapitän: Die meisten der Crew waren an Land, als die Explosion passierte - zum Glück. Die Jungs haben sich etwas Landgang gegönnt, bevor unsere nächste große Reise losgeht. Aber die Schiffsbesatzung... Ich fürchte, es gibt keine Überlebenden. Sieh dich nur um! Die Trümmer haben sogar hier, auf diesem Pier, Menschen verletzt oder getötet! Es ist ein Wunder, dass wir beide unversehrt sind.";
			link.l1 = "Was ist mit dem Schiff? Ist sie in Ordnung?!";
			link.l1.go = "VsD_FolkeAlonso_4";
		break;
		
		case "VsD_FolkeAlonso_4":
			dialog.text = "Ist sie das?! Meine Entschuldigung, Kapitän. Es ist schwer zu sagen, aber es scheint, dass die Explosion auf dem Oberdeck stattgefunden hat, nicht darunter. Ich sehe keine aktiven Brände, und es sieht so aus, als ob wir größeren Schäden entkommen sind.";
			link.l1 = "...";
			link.l1.go = "VsD_FolkeAlonso_5";
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("PortPaxAmmoOff"), 0));
			sld.id = "PortPaxAmmoOff_clone";
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, "PortPax_town", "quest", "quest1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "VsD_FolkeAlonso_5":
			DialogExit();
			LAi_SetStayType(pchar);
			sld = CharacterFromID("PortPaxAmmoOff_clone");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "VsD_Komendant";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 3, 0);
		break;
		
		case "VsD_Komendant":
			dialog.text = "Was zum Teufel, Kapitän?!";
			link.l1 = "Ich frage dasselbe, Oberst!";
			link.l1.go = "VsD_Komendant_1";
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				LAi_SetActorType(sld);
				LAi_ActorGoToLocator(sld, "reload", "reload1", "", -1);
			}
		break;
		
		case "VsD_Komendant_1":
			dialog.text = "Hüte dich, de Maure! Du hast diesen Auftrag von der Marine angenommen, du hast schwere Kanonen übernommen - Eigentum der Krone, von strategischer Bedeutung! Verstehst du die Bedeutung dieser Kanonen für die gesamte Operation?! Deine Nachlässigkeit hat fast vierhundert Männer und ein französisches Kriegsschiff in Gefahr gebracht! Du stehst hier vor einem Prozess wegen Hochverrats!";
			link.l1 = "Beruhigen Sie sich, Oberst! Wie durch ein Wunder scheint mein Schiff überlebt zu haben, und Ihre kostbare Ladung ist größtenteils intakt... größtenteils.";
			link.l1.go = "VsD_Komendant_2";
		break;
		
		case "VsD_Komendant_2":
			dialog.text = "Was meinst du mit 'hauptsächlich'?!";
			link.l1 = "Ich kann nicht garantieren, dass die zweihundert Fässer Schießpulver, die in letzter Minute von einem Ihrer Leutnants geladen wurden, nicht beschädigt wurden. Sie sollten zuletzt geladen werden, und sie waren wahrscheinlich diejenigen, die explodierten.";
			link.l1.go = "VsD_Komendant_3";
		break;
		
		case "VsD_Komendant_3":
			dialog.text = "Was ist das für ein Unsinn, Charles? Welcher Leutnant? Welches Schießpulver? Ich habe einen solchen Befehl nicht erteilt!";
			link.l1 = "Dieser Leutnant muss aus Ihrer Garnison stammen. Ich habe nicht nach seinem Namen gefragt, aber er schien über die Operation Bescheid zu wissen.";
			link.l1.go = "VsD_Komendant_4";
		break;
		
		case "VsD_Komendant_4":
			dialog.text = "Ach, Scheiße! Scheint, dass die Kastilier auch dazu neigen, schmutzige Spielchen zu spielen... Ich werde mich um diese unglückliche Situation kümmern, Kapitän. Du hast jedoch immer noch einen Job zu erledigen: Bist du sicher, dass dein Schiff seetüchtig ist?";
			link.l1 = "Sie schwimmt, aber sie braucht definitiv erhebliche Reparaturen.";
			link.l1.go = "VsD_Komendant_5";
			SetMusic("classic_fra_music_day");
		break;
		
		case "VsD_Komendant_5":
			dialog.text = "Keine Zeit dafür, Kapitän. Setzen Sie sofort Segel und erfüllen Sie die Mission. Die Einsätze sind zu hoch, um zu verzögern.";
			link.l1 = "Können wir nicht wenigstens einen Tag haben, um Himmels willen? Die örtliche Werft könnte die notwendigen Reparaturen durchführen! Und was ist mit meiner Mannschaft?! Es gibt sicherlich Verletzte!";
			link.l1.go = "VsD_Komendant_6";
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (GetCharacterIndex("Folke") != -1 && CheckPassengerInCharacter(pchar, "Folke"))
			{
				sld = CharacterFromID("Folke");
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.Dialog.Filename = "Enc_Officer_dialog.c";
				sld.Dialog.CurrentNode = "hired";
			}
			else
			{
				sld = CharacterFromID("Alonso");
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
		break;
		
		case "VsD_Komendant_6":
			dialog.text = "Falls Sie es noch nicht bemerkt haben, die Werft steht in Flammen. Wir versuchen immer noch festzustellen, ob es absichtlich passiert ist oder eine Nebenwirkung der Explosion. Ich kann Ihnen nur versprechen, dass Ihre Verwundeten medizinische Versorgung erhalten werden, und die Krone wird die Kosten für die Beerdigung der Toten tragen.";
			link.l1 = "Bist du ernst? Das ist das Beste, was du anbieten kannst?";
			link.l1.go = "VsD_Komendant_7";
			sld = CharacterFromID("VsD_Tsyganka");
			ChangeCharacterAddressGroup(sld, "PortPax_town", "reload", "reload5_back");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "VsD_Komendant_7":
			dialog.text = "Kapitän, Frankreich benötigt dringend Ihre Hilfe. Ich werde Ihnen Planken zur Verfügung stellen, und wenn Sie Ihre Karten klug spielen, wird Ihr Schiff fast vollständig repariert sein, wenn Sie Jamaika erreichen.";
			link.l1 = "Verzeihung, aber welche Planken? Und warum Jamaika?";
			link.l1.go = "VsD_Komendant_8";
			pchar.ship.HP = sti(pchar.ship.HP) / 2;
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) - sti(pchar.ship.Crew.Quantity) / 7;
			AddCharacterGoodsSimple(pchar, GOOD_PLANKS, 100);
		break;
		
		case "VsD_Komendant_8":
			dialog.text = "Deine Mannschaft kann mit den Planken - einem primären Reparaturmaterial - Notfallreparaturen auf See durchführen. Und Jamaika liegt ziemlich nah an einer der Routen, die du nach Porto Bello nehmen kannst. Wenn du keine Zeit verschwendest, kannst du die Reparaturen abschließen und dort eine vollständige Mannschaft rekrutieren.";
			link.l1 = "Sehr gut, dann. Ich werde sofort Segel setzen, Oberst.";
			link.l1.go = "VsD_Komendant_9";
			
			sld = CharacterFromID("PortRoyal_shipyarder");
			sld.TrialDelQuestMark = true;
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("PortRoyal", false);
		break;
		
		case "VsD_Komendant_9":
			DialogExit();
			LAi_SetStayType(pchar);
			
			sld = CharacterFromID("VsD_Tsyganka");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "VsD_Tsyganka";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 3, 0);
			
			sld = CharacterFromID("PortPaxAmmoOff_clone");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "gate_back", "none", "", "", "", -1);
		break;
		
		case "VsD_Tsyganka":
			dialog.text = "Warum die Eile, Lieber?";
			link.l1 = "Liebling, ich habe jetzt keine Zeit dafür. Siehst du nicht, was passiert?";
			link.l1.go = "VsD_Tsyganka_1";
		break;
		
		case "VsD_Tsyganka_1":
			dialog.text = "Oh, die aktuellen Probleme sind schlimm, aber ich kann an deiner Hand ablesen, dass am Horizont noch mehr auftauchen.";
			link.l1 = "Jeder kann das sehen, auch ohne auf meine Hand zu schauen, die, wie ich hinzufügen möchte, in einem Handschuh ist. Gut, ich spiele mit: Was ist heute der Preis, um eine Katastrophe abzuwenden?";
			link.l1.go = "VsD_Tsyganka_2";
		break;
		
		case "VsD_Tsyganka_2":
			dialog.text = "Ich habe diese Macht nicht, hübscher Mann. Und selbst wenn ich sie hätte, könnte ich sie mir nicht leisten. Aber ich kann Ihnen immer noch helfen... mit Ihrem Schiff. Die Dame ist in einem bedauernswerten Zustand, mein Lieber.";
			link.l1 = "Ich habe noch nie gehört, dass euer Zigeunervolk Ambitionen im Zimmermannshandwerk hat.";
			link.l1.go = "VsD_Tsyganka_3";
			
			for (i=3; i<=8; i++)
			{				
				sld = CharacterFromID("VsD_MirnyeMan_"+i);
				LAi_SetCitizenType(sld);
			}
			for (i=3; i<=6; i++)
			{				
				sld = CharacterFromID("VsD_MirnyeWoman_"+i);
				LAi_SetCitizenType(sld);
			}
			for (i=1; i<=6; i++)
			{				
				sld = CharacterFromID("VsD_Sold_"+i);
				LAi_SetCitizenType(sld);
			}
			//Возвращаем всё обратно
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			bDisableCharacterMenu = false;
			SetLocationCapturedState("PortPax_town", false);
			Locations[FindLocation("PortPax_town")].locators_radius.quest.quest1 = 1.0;
			Locations[FindLocation("PortPax_town")].locators_radius.patrol.patrol14 = 0.5;
			LocatorReloadEnterDisable("PortPax_ExitTown", "reload2_back", false);
			LocatorReloadEnterDisable("PortPax_ExitTown", "reload1_back", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_Fort")], false);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("VsD_Guard_"+i);
				sld.lifeday = 0;
			}
			//Диего исчезает
			sld = CharacterFromID("Diego");
			LAi_CharacterEnableDialog(sld);
			sld.location = "None";
			//Верфь закрывается
			LocatorReloadEnterDisable("PortPax_Town", "reload5_back", true);
			SetTimerCondition("VsD_VerfOtkryt", 0, 0, 7, false);
			//Труп предателя в джунглях
			PChar.quest.VsD_TrupPredatelya.win_condition.l1 = "location";
			PChar.quest.VsD_TrupPredatelya.win_condition.l1.location = "PortPax_ExitTown";
			PChar.quest.VsD_TrupPredatelya.win_condition = "VsD_TrupPredatelya";
			SetTimerCondition("VsD_TrupPredatelya_3", 0, 0, 60, false);
		break;
		
		case "VsD_Tsyganka_3":
			dialog.text = "Du, Liebling, bist kaum ein Zimmermann. Glaubst du, Bretter allein werden das Schiff reparieren? Sie werden dich nur belasten, wenn du keinen Meisterzimmermann hast...";
			link.l1 = "Oder?";
			link.l1.go = "VsD_Tsyganka_4";
		break;
		
		case "VsD_Tsyganka_4":
			dialog.text = "Es gibt ein mächtiges Amulett, das von den Einheimischen verehrt wird. Holz beugt sich seinem Willen, und sogar diejenigen, die mit der Tischlerei nicht vertraut sind, finden sich geschickt, sobald sie es tragen. Es ist Ihres für nur tausend Pesos, Lieber.";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Sehr gut, wir haben einen Deal. Ich brauche jede Hilfe, die ich kriegen kann.";
				link.l1.go = "VsD_Tsyganka_Da";
			}
			link.l2 = "Ich habe keine Zeit für deine Hexerei. Geh in Frieden, Hexe, und mische dich nicht ein.";
			link.l2.go = "VsD_Tsyganka_Net";
			npchar.lifeday = 0;
		break;
		
		case "VsD_Tsyganka_Net":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Trial", "7_1");
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "VsD_Tsyganka_Da":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Trial", "7_1");
			AddCharacterExpToSkill(pchar, "Repair", 20);
			AddMoneyToCharacter(pchar, -1000);
			GiveItem2Character(PChar, "obereg_1");
			Log_info("You have received Amulet 'Teredo'");
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin ein gesetzestreuer Bürger dieser Stadt. Ich muss dich bitten, nicht mit gezogenem Schwert herumzulaufen wie ein Räuber.","Herr bitte, das Gesetz ist klar, dass Männer innerhalb der Stadtmauern nicht mit gezogenen Waffen umhergehen dürfen.");
			link.l1 = LinkRandPhrase("In Ordnung.","Gut.","Wie du wünschst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
