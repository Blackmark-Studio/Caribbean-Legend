//Jason общий диалог уличных монахов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iTest;
	string sTemp, sTitle;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	iTest = FindColony(NPChar.City);
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> диалог первой встречи
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(npchar, "quest.donation"))//пожертвования
				{
					dialog.text = "Guten Tag, mein Sohn. Ich bitte dich, etwas Gnade zu zeigen und ein paar Silbermünzen für das Wohl der Armen, deiner Seele und der Heiligen Mutter Kirche zu spenden.";
					link.l1 = "Nun Vater, ich nehme an, dass wir alle einander helfen müssen, wie Christus und seine Kirche es uns lehren. Können Sie mir sagen, wohin das Geld gehen wird?";
					link.l1.go = "donation";
					link.l2 = "Vergib mir, Vater, aber ich bin gerade so arm wie eine Kirchenmaus.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Monkpassenger") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) < 3)//монах-пассажир
				{
					dialog.text = "Guten Tag, mein Sohn. Ich würde dich bitten, mir einen Gefallen zu tun. Ich werde natürlich bezahlen.";
					link.l1 = "Ich höre Ihnen zu, Vater. Was brauchen Sie?";
					link.l1.go = "passenger";
					link.l2 = "Es tut mir so leid, Vater, aber ich muss gehen.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.capellan") && !CheckAttribute(pchar, "questTemp.ShipCapellan"))//корабельный капеллан
				{
					dialog.text = "Grüße, mein Sohn. Ich nehme an, dass du ein Kapitän bist. Also habe ich einen Vorschlag für dich.";
					link.l1 = "Ich höre zu, Vater.";
					link.l1.go = "capellan";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = PCharRepPhrase(LinkRandPhrase("Grüße, mein Sohn. Was bedrückt dich?","Grüße, mein Sohn. Suche den Pastor auf, wenn du beichten möchtest.","Grüße, mein Sohn. 'Gedenke deines Schöpfers in den Tagen deiner Jugend.'"),LinkRandPhrase("Grüße, mein Sohn. Was quält dich?","Guten Tag, mein Sohn, Gott segne dich!","Guten Tag, mein Sohn, möge Gottes Antlitz auf dich scheinen!"));
				link.l1 = LinkRandPhrase("Gleichfalls, Vater. Wie geht es Ihnen?","Guten Tag, Vater. Wie geht es Ihrer Gemeinde?","Wie geht es Ihnen, Vater?");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("Ich habe eine Frage an Sie, Vater.","Ich brauche Informationen.");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10)
				{
					link.l3 = "Vater, ich habe Leute auf meinem Schiff. Sie sind Sklaven, sowohl Christen als auch ungetaufte Heiden. Ich möchte, dass Sie die Heiden taufen und den Christen die Kommunion spenden. Danach werde ich sie alle zur Ehre Gottes und unserer Kirche freilassen.";
					link.l3.go = "slaves";
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "Vater, ich möchte, dass Sie mein Schiff segnen und eine Messe für meine Mannschaft halten. Wie viel würde das kosten?";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("Verzeihung, Vater, aber ich muss gehen.","Entschuldigung für die Störung, Vater.","Ich muss zurück zu meinem Schiff, Vater. Lebewohl!");
				link.l10.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				//--> диалог второй встречи
				dialog.text = LinkRandPhrase("Du schon wieder, mein Sohn? Was willst du?","Hast du mir noch etwas zu erzählen, mein Sohn?","Es ist gut dich wiederzusehen, mein Sohn.");
				link.l1 = LinkRandPhrase("Gleichfalls, Vater. Wie geht es Ihnen?","Guten Tag, Vater. Wie geht es Ihrer Gemeinde?","Wie geht es Ihnen, Vater?");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("Ich habe eine Frage an Sie, Vater.","Ich brauche Informationen.");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10 && !CheckAttribute(npchar, "quest.slaves"))
					{
						link.l3 = "Vater, ich habe Menschen auf meinem Schiff. Sie sind Sklaven, sowohl Christen als auch ungetaufte Heiden. Ich möchte, dass Sie die Heiden taufen und den Christen die Kommunion spenden. Danach werde ich sie alle zur Ehre Gottes und unserer Kirche freilassen.";
						link.l3.go = "slaves";
					}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "Vater, ich möchte, dass Sie mein Schiff segnen und eine Messe für meine Mannschaft abhalten. Wie viel würde das kosten?";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("Verzeihung, Vater, aber ich muss gehen.","Entschuldigen Sie die Störung, Vater.","Ich muss zu meinem Schiff, Vater. Leb wohl!");
				link.l10.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "check":
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) < 3 && !CheckAttribute(npchar, "quest.monkletter") && !CheckAttribute(pchar, "GenQuest.Monkletter") && !CheckAttribute(npchar, "quest.passenger")) //церковная депеша
			{
				pchar.GenQuest.Monkletter.City = FindFriendCityToMC(false);
				pchar.GenQuest.Monkletter.StartCity = npchar.city;//город квестодателя
				dialog.text = "Ich habe eine dringende Angelegenheit für dich, mein Sohn. Ich muss diese Papiere dem Pastor liefern "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Geschlecht")+". Segeln Sie in diese Richtung? Die Dokumente müssen in zwei Wochen geliefert werden...";
				link.l1 = "Leicht genug, Vater. Gib mir diese Papiere und ich werde sie ausliefern "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Geschlecht")+".";
				link.l1.go = "Monkletter";
				link.l2 = "Ich würde es gerne tun, Vater, aber ich segle in eine andere Richtung.";
				link.l2.go = "exit_monkletter";
				npchar.quest.monkletter = "true";
				break;
			}
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) > 5 && sti(pchar.rank < 11) && !CheckAttribute(npchar, "quest.churchbooks") && !CheckAttribute(pchar, "GenQuest.Churchbooks") && !CheckAttribute(npchar, "quest.passenger")) //привезти молитвенники
			{
				pchar.GenQuest.Churchbooks.StartCity = npchar.city;//город квестодателя
				pchar.GenQuest.Churchbooks.Nation = npchar.nation;
				dialog.text = "Mein Sohn, würdest du zustimmen, mir in einer dringenden Angelegenheit zu helfen? Unserer Kirche gehen die Bibeln und Gebetsbücher aus, die wir allen geben, die sie benötigen\nKönntest du zur nächstgelegenen Kolonie segeln "+NationNameGenitive(sti(npchar.nation))+", um ein paar Bibeln und Gebetbücher von der örtlichen Kirche abzuholen und sie hierher zu bringen? Und versuchen Sie, das in einem Monat zu tun, wir haben nicht viele übrig.";
				link.l1 = "Ich helfe Ihrer Kirche gerne. Kann ich diese Bücher von jedem Pfarrer bekommen?";
				link.l1.go = "Churchbooks";
				link.l2 = "Ich würde es gerne tun, Vater, aber ich kann es jetzt nicht.";
				link.l2.go = "exit_churchbooks";
				npchar.quest.churchbooks = "true";
				break;
			}
			
			dialog.text = RandPhraseSimple("Es ist in Ordnung, mein Sohn. Danke für deine freundlichen Worte.","Unsere Pfarrei geht es gut, mein Sohn. Danke für deine Besorgnis.");
			link.l1 = "Ich muss dann gehen, Vater.";
			link.l1.go = "exit";
		break;
		
//-------------------------------------------------пожертвования------------------------------------------------
		case "donation":
			sTemp = DonationType();
			dialog.text = "Sicher, mein Sohn. "+sTemp+"";
			link.l1 = "Welche Spende würde als ausreichend betrachtet?";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			dialog.text = "Alles hängt von deinem Geldbeutel und deinem persönlichen Wunsch ab, mein Sohn. 'Gott liebt einen fröhlichen Geber.' Wir sind für jede Spende zutiefst dankbar.";
			link.l1 = "100 Pesos";
			link.l1.go = "donation_rate_1";
			link.l2 = "1000 Pesos";
			link.l2.go = "donation_rate_2";
			link.l3 = "5000 Pesos";
			link.l3.go = "donation_rate_3";
			link.l4 = "10000 Pesos";
			link.l4.go = "donation_rate_4";
		break;
		
		case "donation_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "Danke dir für die Münzen, mein Sohn! Sie werden für einen guten Zweck verwendet!";
				link.l1 = "Sie sind willkommen, heiliger Vater.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "'Lasst euch nicht täuschen, Gott lässt sich nicht verspotten. Denn was ein Mensch sät, das wird er auch ernten. Denn wer auf sein Fleisch sät, wird vom Fleisch Verderben ernten. Aber wer auf den Geist sät, wird vom Geist ewiges Leben ernten.'";
				link.l1 = "Ha-ha! Spar dir die Predigt, ich mache keine Wohltätigkeit. Verschwinde!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_2":
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "Ich danke Ihnen, mein Sohn. Diese Summe wird unserer Pfarrmission wirklich helfen. Gott segne Sie!";
				link.l1 = "Viel Glück, Vater!";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCrewMorale(pchar, 2);
			}
			else
			{
				dialog.text = "Gottes Rache wartet auf dich, Bursche! Einen Diener der heiligen Kirche Christi zu verspotten, ist eine Blasphemie!";
				link.l1 = "Ha-ha! Ich mache keine Wohltätigkeitsarbeit. Verschwinde!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_3":
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "Ich hätte mir nicht vorstellen können, dass du so großzügig sein würdest, mein Sohn! Ich werde dich in meinem nächsten Brief an unseren Bischof erwähnen und wir werden jeden Tag für dich beten! Ich segne dich und nehme dein Geld dankbar an!";
				link.l1 = "Geld ist nichts, es sei denn, es wird für Gottes Zweck verwendet! Viel Glück, Vater!";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCrewMorale(pchar, 3);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			}
			else
			{
				dialog.text = "Gottes Vergeltung wartet auf dich, Bursche! Ein Diener von Christi heiliger Kirche zu verspotten, ist Blasphemie!";
				link.l1 = "Ha-ha! Ich mache keine Wohltätigkeit. Verpiss dich!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_4":
			if (sti(pchar.money) >= 10000)
			{
				AddMoneyToCharacter(pchar, -10000);
				dialog.text = "Was...Habe ich Sie richtig gehört? Werden Sie wirklich zehntausend Pesos spenden!? Ich segne Sie und nehme Ihr Geld dankbar an. Ich werde Sie in meinem nächsten Brief an unseren Bischof erwähnen und wir werden jeden Tag für Sie beten! Das ist eine riesige Hilfe für die Kirche!";
				link.l1 = "'Wem viel gegeben ist, von dem wird viel verlangt,' richtig? Viel Glück, heiliger Vater.";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 10);
				AddCharacterExpToSkill(pchar, "Leadership", 60);
				AddCrewMorale(pchar, 5);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
				ChangeCrewExp(pchar, "Sailors", 5);
				ChangeCrewExp(pchar, "Cannoners", 5);
				ChangeCrewExp(pchar, "Soldiers", 5);
			}
			else
			{
				dialog.text = "Gottes Vergeltung wartet auf dich, Bursche! Einen Diener von Christi heiliger Kirche zu verspotten ist eine Blasphemie!";
				link.l1 = "Ha-ha! Ich mache keine Wohltätigkeit. Verschwinde!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterHealth(pchar, -5);
			LAi_CharacterDisableDialog(npchar);
		break;
		
//-------------------------------------------отпустить рабов---------------------------------------------------
		case "slaves":
			dialog.text = "Natürlich, mein Sohn. Es ist unsere heilige Pflicht, diesen armen unglücklichen Menschen zu helfen. Ich werde tun, was du verlangst.";
			link.l1 = "Danke, Vater. Ich werde zehn Achtstücke für jeden getauften und verwalteten Gefangenen spenden.";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves_1":
			AddMoneyToCharacter(pchar, -GetSquadronGoods(pchar, GOOD_SLAVES)*10);
			dialog.text = "Während es nicht notwendig ist, nehme ich Ihre gestohlene Gebühr dankbar an. Ihr Geld wird für verschiedene Missionen in unserer Pfarrei verwendet. Könnten Sie mich zu Ihrem Schiff führen?";
			link.l1 = "Ja, Vater. Folge mir.";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			npchar.quest.slaves = "true";
			DialogExit();
			SetLaunchFrameFormParam("Two hours later"+ NewStr() +"Slaves were freed", "Monk_RemoveSlaves", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
//<-- отпустить рабов

//----------------------------------------------освятить корабль------------------------------------------------
		case "shipshine":
			//поиск старшего класса
			iTemp = 7;
			for (i=0; i<COMPANION_MAX; i++)
			{
				int iIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iIdx >= 0)
				{
					sld = GetCharacter(iIdx);
					if (GetCharacterShipClass(sld) < iTemp) iTemp = GetCharacterShipClass(sld);
				}
			}
			switch (GetCompanionQuantity(pchar))
			{
				case 1: 
					sTemp = "I have only one ship in my squadron and it's "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = 5000*(7-iTemp);
				break;
				case 2:
					sTemp = "I have two ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(1.8*(5000*(7-iTemp)));
				break;
				case 3:
					sTemp = "I have three ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(2.6*(5000*(7-iTemp)));
				break;
				case 4:
					sTemp = "I have four ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(3.4*(5000*(7-iTemp)));
				break;
				case 5:
					sTemp = "I have five ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(4.2*(5000*(7-iTemp)));
				break;
			}
			dialog.text = "Es hängt alles von der Gesamtzahl der Schiffe in Ihrem Geschwader und ihrer Größe ab.";
			link.l1 = ""+sTemp+"";
			link.l1.go = "shipshine_1";
		break;
		
		case "shipshine_1":
			dialog.text = "Es wird dich kosten "+FindRussianMoneyString(sti(pchar.GenQuest.Shipshine.Money))+", mein Sohn.";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Shipshine.Money))
			{
				link.l1 = "Ich kann Ihnen diesen Betrag zahlen, Vater. Nehmen Sie das Geld.";
				link.l1.go = "shipshine_2";
			}
			link.l2 = "Leider habe ich nicht so viel Geld bei mir.";
			link.l2.go = "shipshine_exit";
		break;
		
		case "shipshine_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Shipshine.Money));
			dialog.text = "Sehr gut, mein Sohn. Lassen Sie mich die heiligen Gefäße sammeln und wir gehen zum Hafen.";
			link.l1 = "Folge mir, Vater.";
			link.l1.go = "shipshine_3";
		break;
		
		case "shipshine_3":
			DialogExit();
			SetLaunchFrameFormParam("Several hours later"+ NewStr() +"The priest has held mass aboard your ship and blessed it", "Monk_Shipshine", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, GetCompanionQuantity(pchar), 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shipshine_exit":
			DialogExit();
			DeleteAttribute(Pchar, "GenQuest.Shipshine");
		break;
//<-- освятить корабль

//------------------------------------------корабельный капеллан-----------------------------------------------
		case "capellan":
			dialog.text = "Hallo Kapitän, darf ich mich vorstellen. Ich bin ein Priester und habe ziemlich viel Erfahrung als Kaplan an Bord von Kriegsschiffen. Ich habe mein letztes Schiff verlassen, weil der Kapitän und ich einige...moralische Meinungsverschiedenheiten hatten. Möchten Sie mich in Ihrer Besatzung aufnehmen?";
			link.l1 = "Ein Priester an Bord? Sag mir Vater, was macht ein Schiffsgeistlicher?";
			link.l1.go = "capellan_1";
			pchar.questTemp.ShipCapellan = "true";
		break;
		
		case "capellan_1":
			dialog.text = "Wie, es ist ganz offensichtlich. Ich bete zu Gott für dich und deine Mannschaft, halte täglich die Messe ab und segne deine Männer und höre die Beichte vor der Schlacht. Gottes Wort verleiht den Händen und Geistern deiner Mannschaft Stärke. Deine Mannschaft wird regelmäßig die Möglichkeit haben, die Kommunion zu empfangen und die Beichte abzulegen. Glaube mir, ein Seemann in einem Zustand der Gnade wird Situationen durchstehen, in denen ein gottloser erzittern wird\nIch bitte nicht viel für mich: eine einmalige Zahlung von fünfzigtausend Pesos für meine Heimatpfarrei, eine einfache Koje in einer Kabine und ein Brett, wie es deine Offiziere haben. Das wäre alles.";
			if (sti(pchar.money) >= 50000)
			{
				link.l1 = "Interessant... Sie haben recht, ein guter Kapitän muss sich nicht nur um die Körper seiner Mannschaft kümmern, sondern auch um ihre Seelen. Willkommen an Bord, Vater!";
				link.l1.go = "capellan_2";
			}
			link.l2 = "Nein, Vater. Es tut mir leid, aber ich kann mir Ihre Dienste nicht leisten.";
			link.l2.go = "capellan_exit";
		break;
		
		case "capellan_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "capellan_2":
			AddMoneyToCharacter(pchar, -50000);
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = "Danke für dein Vertrauen, mein Sohn. Du hast dein Geld weise ausgegeben. Aber ich warne dich, ich diene nur würdigen Kapitänen, ob Händler oder Freibeuter, spielt keine Rolle. Aber ich werde nie an Bord eines Piratenschiffs predigen! \nAlso, wenn du jemals den Teufels Jolly Roger hisst, werde ich sofort bei der ersten Gelegenheit dein Schiff verlassen.";
			link.l1 = "Ich werde darüber nachdenken, Vater, und ich werde versuchen, dich nicht zu enttäuschen. Bitte geh an Bord und stelle dich der Crew vor!";
			link.l1.go = "capellan_3";
		break;
		
		case "capellan_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "rld", "loc1", "Monk_Capellan", -1);
			pchar.questTemp.ShipCapellan.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.ShipCapellan.Yes = "true";//капеллан в команде
			Achievment_Set("ach_69");
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			npchar.reputation = 60;
		break;
		
		case "capellan_4":
			dialog.text = "Brauchst du etwas, mein Sohn?";
			link.l1 = "Nein, es ist nichts, Vater.";
			link.l1.go = "exit";
			link.l2 = "Padre, ich möchte, dass Sie das Schiff im nächsten Hafen verlassen. Ich werde mich nicht weiter erklären.";
			link.l2.go = "capellan_5";
			NextDiag.TempNode = "capellan_4";
		break;
		
		case "capellan_5":
			dialog.text = "Sehr gut, mein Sohn. Du bist hier der Boss. Ich werde dein Schiff in der nächsten Siedlung verlassen.";
			link.l1 = "Danke für Ihr Verständnis, Vater.";
			link.l1.go = "capellan_6";
		break;
		
		case "capellan_6":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			ShipCapellan_Remove();
		break;
		
		case "capellan_7":
			dialog.text = "Pfui, Kapitän! Ich habe Sie gewarnt, dass ich Sie verlassen werde, wenn Sie die Piratenflagge hissen! Ich verlasse Ihr Schiff im nächsten Hafen. Ich werde für Ihre sofortige Reue und Rückkehr in den Schoß der Heiligen Mutter Kirche beten.";
			link.l1 = "Verdammt noch mal...";
			link.l1.go = "exit";
			NextDiag.TempNode = "capellan_7";
		break;
//<-- капеллан
	
//--------------------------------------------монах-пассажир---------------------------------------------------
		case "passenger":
			if (hrand(19) < 15) SetPassengerParameter("Monkpassenger", false);
			else SetPassengerParameter("Monkpassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
			{
				dialog.text = "Mein "+GetSexPhrase("Sohn","Tochter")+", ich muss zu "+XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+" es ist an "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Dat")+", denn "+FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty))+". Ich werde dich bezahlen "+FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money))+" dafür. Was sagst du?";
			}
			else
			{
				dialog.text = "Mein "+GetSexPhrase("Sohn","Tochter")+", der Herr arbeitet auf geheimnisvolle Weise, und so suche ich einen zuverlässigen Kapitän. Können Sie mir helfen, zu "+XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+", welches sich auf "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Dat")+"? Ich verstehe, dass es wie eine Reise ins feurige Gehenna ist, da unsere Feinde niemals schlafen. Und ich verstehe, dass du nicht Jesus Christus bist, aber ich bin auch kein Apostel, und daher habe ich einige Ersparnisse. Werde "+FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money))+" reicht dir das?";
			}
			link.l1 = "Ich stimme zu, Vater.";
			link.l1.go = "passenger_1";
			link.l2 = "Es tut mir leid, Vater, aber ich segel in eine andere Richtung. Ich kann Ihnen nicht helfen.";
			link.l2.go = "passenger_exit";
			npchar.quest.passenger = true;
		break;
		
		case "passenger_exit":
			dialog.text = "Es ist Gottes Wille für alle, mein Sohn. Ich werde auf ein anderes Schiff warten. Friede sei mit dir!";
			link.l1 = "Auf Wiedersehen, Padre.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Monkpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Gott segne dich! Du wirst deine Bezahlung erhalten, wenn wir an unserem Zielort angekommen sind.";
			link.l1 = "Gehen Sie zu meinem Schiff, Vater. Wir werden bald abfahren.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Monkpassenger.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "monk");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Monkpassenger.City+"Gen") + ", which is on " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Voc")+"."; // belamour gen
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Monkpassenger.win_condition.l1 = "location";
			pchar.quest.Monkpassenger.win_condition.l1.location = pchar.GenQuest.Monkpassenger.City+"_town";
			pchar.quest.Monkpassenger.function = "Monkpassenger_complete";
			SetFunctionTimerCondition("Monkpassenger_Over", 0, 0, sti(pchar.GenQuest.Monkpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Monkpassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Danke, mein "+GetSexPhrase("Sohn","Tochter")+". Du hast dein Versprechen erfüllt und jetzt bin ich an der Reihe. Nimm dein Geld, wie ich versprochen habe.";
			link.l1 = "Danke. Viel Glück, Vater.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Monkpassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Monkpassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Monkpassenger");
		break;
//<-- монах-пассажир
		
//---------------------------------------------церковная депеша-------------------------------------------------
		case "exit_monkletter":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter":
			dialog.text = "Hier. Nimm dieses Paket, mein Sohn. Denke daran, dass du nur zwei Wochen hast, um es zu liefern. Der Pastor wartet darauf. Geh, und möge Gott mit dir sein!";
			link.l1 = "Ich werde dich nicht enttäuschen, Vater. Lebewohl.";
			link.l1.go = "Monkletter_1";
		break;
		
		case "Monkletter_1":
			DialogExit();
			GiveItem2Character(pchar, "letter_church");
			ReOpenQuestHeader("Monkletter");
			AddQuestRecord("Monkletter", "1");
			AddQuestUserData("Monkletter", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("Monkletter", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen"));
			AddQuestUserData("Monkletter", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity));
			SetFunctionTimerCondition("Monkletter_Over", 0, 0, 15, false);
			OfficersReaction("good");
		break;
//<-- Церковная депеша
		
//-------------------------------------------доставить молитвенники---------------------------------------------
		case "exit_churchbooks":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;

		case "Churchbooks":
			dialog.text = "Ja. Sie können sie in jeder Kolonie bekommen "+NationNameGenitive(sti(npchar.nation))+". Bring alle Bücher, die du findest, zu unserem Pastor in der Kirche. Gott segne dich!";
			link.l1 = "Danke! Sie werden Ihre Bücher bald erhalten.";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			DialogExit();
			ReOpenQuestHeader("Churchbooks");
			AddQuestRecord("Churchbooks", "1");
			AddQuestUserData("Churchbooks", "sNation", NationNameGenitive(sti(pchar.GenQuest.Churchbooks.Nation)));
			AddQuestUserData("Churchbooks", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity));
			SetFunctionTimerCondition("Churchbooks_Over", 0, 0, 30, false);
			pchar.GenQuest.Churchbooks = "go";
			switch (rand(4))
			{
				case 0: pchar.GenQuest.Churchbooks.Item = "amulet_2"; break;
				case 1: pchar.GenQuest.Churchbooks.Item = "amulet_3"; break;
				case 2: pchar.GenQuest.Churchbooks.Item = "amulet_6"; break;
				case 3: pchar.GenQuest.Churchbooks.Item = "amulet_7"; break;
				case 4: pchar.GenQuest.Churchbooks.Item = "amulet_10"; break;
			}
			OfficersReaction("good");
		break;
//<-- доставить молитвенники
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string DonationType()
{
	string sText;
	switch (hrand(9))
	{
		case 0: sText = "I am gathering money for building "+LinkRandPhrase("a chapel","an almshouse","a hospital")+". The local citizens give little in alms so I must ask prosperous men like you." break;
		case 1: sText = "I am gathering donations for our church. Sailors don't usually have much time to visit the house of God, but everyone must do his best in saving his own soul." break;
		case 2: sText = "I am gathering money to buy food and medicines for our poorhouse for the sick, widows, orphans, and infirm. Please donate sir, because there but for the grace of God go all of us." break;
		case 3: sText = "I am gathering money for new sacred vessels, the ones which we brought from Europe are battered with continual use. It's a duty for every Christian to take care of our Church." break;
		case 4: sText = "I am gathering money for our church's renovation, the roof is leaking terribly and the pews have to be repaired too. It's a duty for every Christian to take care of our Church." break;
		case 5: sText = "I am gathering money to pay the good artist who is able to paint the walls of our church and draw scenes from the Bible on them for those of our parish who cannot read. It's a duty for every Christian to take care about his Church." break;
		case 6: sText = "I am gathering money for a new high altar for our church. Our parish is poor and we would like a noble seat for the Blessed Sacrament. I do hope for your help." break;
		case 7: sText = "There are a lot of wounded sailors from pirate raids in our hospital. They need medicines and bandages. Pray help them, for you can really understand sufferings of the common sailors." break;
		case 8: sText = "I am trying to get money for clothes and food for our poorest citizens. The only hope they have is our holy church. Please help them." break;
		case 9: sText = "I am going to go deep in our island for missionary work to bring the light of Christ's Gospel to the lost souls of the pagan Indians. I am gathering funds for this expedition. Please help our good deed!" break;
	}
	return sText;
}
