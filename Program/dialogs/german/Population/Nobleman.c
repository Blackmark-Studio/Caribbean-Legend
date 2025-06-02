//Jason общий диалог дворян
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iTest;
	string sTemp, sTitle;
	float locx, locy, locz;

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
	
	iTest = FindColony(NPChar.City); // 170712
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> проверка межнациональных отношений
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
				dialog.text = NPCStringReactionRepeat("Hm. Sie segeln unter der Flagge von "+NationNameGenitive(sti(pchar.nation))+", Kumpel. Was zur Hölle machst du hier, in unserer Stadt? Verzieh dich!","Ich möchte nicht als Freund von  verdächtigt werden"+NationNameAblative(sti(pchar.nation))+"! Verschwinde, oder ich melde es der Wache!","Das ist deine letzte Chance zu entkommen. Sonst kannst du nur dich selbst beschuldigen.","Ich habe dich gewarnt. Jetzt wirst du für deine Frechheit bezahlen, Bastard!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Solch ein Patriot, ha!","Gut, gut, beruhige dich. Ich gehe jetzt.","Mach nicht so viel Lärm. Ich gehe jetzt.","Was?!",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> проверка репутации - дворяне гнобят супернегодяев
			if (sti(pchar.reputation.nobility) < 10)
			{
				dialog.text = NPCStringReactionRepeat("Schau dir das an! Und wie lassen unsere Wachen einen solchen Bastard wie dich einfach in der Stadt herumlaufen? Unmöglich...","Verschwinde, ich will nicht mal mit dir reden! Henker...","Das ist deine letzte Chance zu fliehen. Sonst kannst du nur dich selbst beschuldigen.","Ich habe dich gewarnt. Jetzt wirst du für deine Unverschämtheit bezahlen, Bastard!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("He he! Zeigen Sie mir mehr Respekt, Herr!","Schau dich an, Heiliger...","Beruhige dich...","Was?!",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> диалог первой встречи
            if(NPChar.quest.meeting == "0")
			{
				// проверка наличия корабля в порту
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && CheckAttribute(pchar, "questTemp.StatusCity") && pchar.questTemp.StatusCity == npchar.city)//дворянин-пассажир
				{
					dialog.text = "Grüße, "+GetAddress_Form(NPChar)+". Ich sehe, dass Sie Kapitän eines soliden Schiffes sind. Ich möchte Sie um etwas bitten. Sie können es annehmen oder ablehnen.";
					link.l1 = "Ich höre zu, "+GetAddress_FormToNPC(NPChar)+". Was meinst du?";
					link.l1.go = "passenger";
					link.l2 = "Entschuldigen Sie mich, "+GetAddress_FormToNPC(NPChar)+", aber ich habe es eilig.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && or(IsUniversalShipType(pchar), IsMerchantShipType(pchar)))//дворянин-пассажир
				{
					dialog.text = "Grüße, "+GetAddress_Form(NPChar)+". Ich sehe, dass Sie Kapitän eines soliden Schiffes sind. Ich möchte Sie bitten, etwas zu tun. Sie können es annehmen oder ablehnen.";
					link.l1 = "Ich höre zu, "+GetAddress_FormToNPC(NPChar)+". Was meinst du?";
					link.l1.go = "passenger";
					link.l2 = "Entschuldigen Sie mich, "+GetAddress_FormToNPC(NPChar)+", aber ich habe es eilig.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (CheckAttribute(npchar, "quest.donation"))//клянчит деньги
				{
					dialog.text = "Aha, es ist gut, einen Gentleman in unserer kleinen Stadt zu sehen! Ich bin mir sicher, dass Sie gerade aus Europa kommen. Hören Sie, ich möchte Sie bitten, mir zu helfen - von Gentleman zu Gentleman. Ich hoffe, Sie verstehen mich richtig.";
					link.l1 = "Guten Tag, Herr. Ich höre zu.";
					link.l1.go = "donation";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.lombard") && !CheckAttribute(pchar, "GenQuest.Noblelombard"))//семейная реликвия
				{
					dialog.text = "Guten Tag, "+GetAddress_Form(NPChar)+"! Es ist gut, einen Gentleman auf den Straßen unserer Stadt zu treffen! Würden Sie mir ein paar Minuten Ihrer Zeit schenken?";
					link.l1 = "Sicher, Herr. Ich höre zu.";
					link.l1.go = "lombard";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.slaves") && !CheckAttribute(&Colonies[FindColony(npchar.city)], "questslaves"))//привезти рабов
				{
					dialog.text = "Guten Tag an Sie, Kapitän! Ich freue mich, Sie zu sehen, denn Sie sehen aus wie ein Mann, der in der Lage ist, Probleme zu lösen.";
					link.l1 = "Hängt vom Problem ab. Ich bin spezialisiert darauf, sie mit Gewalt zu lösen, ist das was du suchst, "+GetAddress_FormToNPC(NPChar)+"?";
					link.l1.go = "slaves";
					npchar.quest.meeting = "1";
					break;
				}
				dialog.text = RandPhraseSimple("Hallo, "+GetAddress_Form(NPChar)+". Wollen Sie etwas von mir?","Was möchten Sie, Herr?");
				link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". Ich werde nicht viel Ihrer Zeit in Anspruch nehmen, ich möchte nur fragen...";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Ich brauche Informationen über Ihre Kolonie.","Ich brauche Informationen.");
				link.l2.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("Die ganze Stadt ist angespannt - Don Fernando de Alamida, der königliche Inspektor, ist angekommen. Weißt du, ich habe hier viel gesehen, aber das... Es ist nicht die Trauer, die die Menschen verändert, sondern wie sie damit umgehen. Sie sagen, er sei nach dem Tod seines Vaters ein anderer Mensch geworden. Jetzt wirst du keinen unbestechlicheren und... gnadenloseren Diener der Krone im ganzen Archipel finden.","Schau nur auf die 'Heilige Barmherzigkeit'! Sie sagen, der König selbst habe sie nach besonderen Entwürfen bauen lassen. Und beachte - kein einziger Kratzer. Als würde die Jungfrau Maria selbst sie schützen. Obwohl ich Gerüchte gehört habe... vielleicht ist es überhaupt nicht die Jungfrau.","Wissen Sie, wie oft sie versucht haben, Don Fernando zu töten? Zwölf Angriffe auf offener See - und das nur im letzten Jahr! Nun, mit einer so loyalen und ausgebildeten Mannschaft, und unter dem Schutz des Herrn - er wird auch das dreizehnte Mal überleben!"),LinkRandPhrase("Hast du gehört? Don Fernando de Alamida ist in unserer Stadt angekommen, und sie sagen, er sei gerade jetzt irgendwo auf den Straßen. Würde ihn gerne mit meinen eigenen Augen sehen...","Ein komplizierter Mann, dieser Don Fernando. Einige sagen, er sei ein Retter, der das Mutterland vom Dreck reinigt. Andere flüstern, dass nach dem Tod seines Vaters etwas in ihm zerbrochen ist und wir bald alle weinen werden. Aber ich sage Ihnen dies: Fürchten Sie ihn nicht. Fürchten Sie diejenigen, die ihn zu dem gemacht haben, was er ist.","Was für ein hübscher Mann, dieser Don Fernando! Aber wissen Sie, was seltsam ist? Es ist, als würde er niemanden bemerken. Alles Pflicht und Dienst. Ich hörte, es gab ein Mädchen... aber nach einem Treffen mit einem Priester lehnte er weltliche Freuden völlig ab. Als hätte er ein Gelübde abgelegt."),RandPhraseSimple(RandPhraseSimple("Verdammter Inspektor! Solange er hier ist, ist die Stadt wie tot. Kein Handel, kein Spaß. Selbst das Atmen, scheint es, muss leiser sein. Und wissen Sie, was am furchtbarsten ist? Es ist in jedem Hafen genauso. Wie ein Uhrwerk. Seine königliche Majestät könnte diese Folter für uns alle nicht absichtlich erfunden haben!","Don Fernando hat das Waisenhaus wieder besucht. Er spendet großzügig, betet stundenlang. Ein solch würdiger Mann sollte als Beispiel für diese verfluchten Unterschläger gepriesen werden!"),RandPhraseSimple("Ha! 'Heiliger' Fernando hat alle Bordelle wieder geschlossen. Nun, macht nichts, er wird bald absegeln und sie werden sofort wieder öffnen.","Der Insp... Inspektor ist angekommen, das ist es! Don Fernando de Almeyda, oder wie heißt er, Alamida! So wichtig, dass der Gouverneur selbst um ihn herumschleicht. Sie sagen, er schaut dir in die Augen und sieht sofort all deine Sünden. Schrecklich!")));
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== Леди Бет в порту города
			}
			else //--> повторные обращения
			{
				dialog.text = NPCStringReactionRepeat("Was? Schon wieder? Ich habe keine Zeit für dich. Such dir jemand anderen zum Reden. Es laufen viele Gemeine auf den Straßen herum. Und ich muss gehen, es wird heute Abend ein Bankett in der Residenz des Gouverneurs geben und ich muss mein Outfit vorbereiten...","Nein, jetzt ist es wirklich ärgerlich! Verstehst du es nicht? Oder bist du ein langsamer Verstand?","Herr, ich beginne zu vermuten, dass Sie nicht nur ein Idiot, sondern ein Hinterwäldler und ein Tölpel sind. Ich warne Sie, lassen Sie mich in Ruhe oder Sie werden es bereuen, mich belästigt zu haben.","Genug. Ich werde dir eine Lektion erteilen, frecher Kerl!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Ich verstehe. Lebewohl.","Ja-ja, habe gerade vergessen, was ich fragen wollte...","Du hast mich falsch verstanden...","Was?!",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = LinkRandPhrase("Mach weiter.","Was willst du?","Fragen? Gut, Seemann, ich höre zu.");
			link.l1 = LinkRandPhrase("Würden Sie mir nicht die neuesten Klatsch und Tratsch in Ihrer Stadt erzählen?","Ist hier in letzter Zeit etwas Interessantes passiert?","Gibt es Neuigkeiten aus der Karibik, Herr?");
			link.l1.go = "rumours_nobleman";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------дворянин-пассажир---------------------------------------------------
		case "passenger":
			if (hrand(19) > 9) SetPassengerParameter("Noblepassenger", false);
			else SetPassengerParameter("Noblepassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
			{
				dialog.text = ""+GetSexPhrase("Herr","Madame")+", ich muss zur Kolonie gelangen"+XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City+"Akk")+", sobald wie möglich ist es an "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Voc")+", für "+FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty))+". Ihr Schiff sieht im Vergleich zur Mehrheit dieser kleinen Wannen, die hier segeln, robust und schnell aus. Ich kann Ihnen bezahlen "+FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money))+". Was würden Sie sagen?"; // belamour gen
			}
			else
			{
				dialog.text = "Hallo, "+GetSexPhrase("Herr","meine Dame")+"! Ich muss nach "+XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City+"Konto")+"! Das ist dran "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Voc")+", übrigens. Ja, ja, ich weiß - diese Bastarde warten nur darauf, dass wir dort auftauchen. Aber ich habe dort ein sehr dringendes und wichtiges Treffen! Ich bin kein geiziger Mensch - obwohl ich nicht gerne zahle, zahle ich immer. Lass alles stehen und liegen, und sobald wir ankommen, gebe ich dir "+FindRussianDublonString(sti(pchar.GenQuest.Noblepassenger.Money))+".";
			}
			link.l1 = "Hm. Ich gehe auch in diese Richtung, also bin ich bereit, dich unter diesen Bedingungen an Bord zu nehmen.";
			link.l1.go = "passenger_1";
			link.l2 = "Es tut mir leid, "+GetAddress_FormToNPC(NPChar)+", aber ich segle in eine andere Richtung. Ich kann dir nicht helfen.";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "Schade. Nun, ich warte auf ein anderes Schiff. Lebewohl.";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Noblepassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Großartig! Ich habe genug vom Warten. Du bekommst deine Bezahlung, wenn wir dort ankommen.";
			link.l1 = "Geh zu meinem Schiff, "+GetAddress_FormToNPC(NPChar)+". Wir gehen bald.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Noblepassenger.id = npchar.id;
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
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
			AddQuestUserDataForTitle(sTitle, "sType", "nobleman");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Noblepassenger.City+"Gen") + ", at " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Dat")+".";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Noblepassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Noblepassenger.win_condition.l1 = "location";
			pchar.quest.Noblepassenger.win_condition.l1.location = pchar.GenQuest.Noblepassenger.City+"_town";
			pchar.quest.Noblepassenger.function = "Noblepassenger_complete";
			SetFunctionTimerCondition("Noblepassenger_Over", 0, 0, sti(pchar.GenQuest.Noblepassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Noblepassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Hier sind wir, hervorragend! Die Reise auf Ihrem Schiff war durchaus zufriedenstellend. Sie haben eine disziplinierte Besatzung und saubere Decks! Meinen Dank. Nehmen Sie Ihr Geld, Herr.";
			link.l1 = "Viel Glück, "+GetAddress_FormToNPC(NPChar)+"! Auf Wiedersehen.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			chrDisableReloadToLocation = false;//открыть локацию
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
			if (CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Noblepassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Noblepassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Noblepassenger");
		break;
//<-- дворянин-пассажир

//-------------------------------------------------помощь деньгами------------------------------------------------
		case "donation":
			sTemp = DonationText();
			dialog.text = "Ich habe ein ziemlich heikles Geschäft..."+sTemp+" Ich brauche jetzt Geld oder ich bin in großen Schwierigkeiten. Normalerweise würde ich einen anderen Gentleman nie um Geld bitten, aber die Situation ist wirklich schlecht.";
			link.l1 = "Wie viel brauchst du?";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			iTemp = hrand(4)+1;
			pchar.GenQuest.Nobledonation.Money = iTemp*1000+rand(iTemp)*150;
			dialog.text = "Die Summe ist ziemlich klein, es ist "+FindRussianMoneyString(sti(pchar.GenQuest.Nobledonation.Money))+". Also was, kannst du mir helfen?";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Nobledonation.Money))
			{
				link.l1 = "Ja, sicher. Nimm es.";
				link.l1.go = "donation_2";
			}
			link.l2 = "Ich würde gerne helfen, aber auch meine Taschen sind leer - nicht ein einziger übriger Peso.";
			link.l2.go = "donation_exit";
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeOfficersLoyality("bad_all", 1);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
		
		case "donation_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Nobledonation.Money));
			dialog.text = "Mein Dank, "+GetAddress_Form(NPChar)+"! Sie haben mich gerettet! Ich habe Freunde in der Residenz des Gouverneurs und ich werde ihnen von Ihrer Großzügigkeit erzählen. Tausend Dank nochmal!";
			link.l1 = "Sie sind willkommen, Herr. Ich bin sicher, dass Sie das Gleiche für mich tun würden.";
			link.l1.go = "donation_3";
		break;
		
		case "donation_3":
			DialogExit();
			ChangeOfficersLoyality("good_all", rand(2)+1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), rand(1)+2);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
//<-- помощь деньгами

//-------------------------------------------------семейная реликвия---------------------------------------------
		case "lombard":
			LombardText();
			dialog.text = "Ich brauche Ihre Hilfe. Sie sind wohlhabend und ein Gentleman, daher hoffe ich, dass Sie verstehen werden. Vor nicht allzu langer Zeit hatte ich dringend Geld benötigt, also musste ich zum Bankier gehen und verpfänden "+pchar.GenQuest.Noblelombard.Item+"\nEr bot gute Bedingungen an. Zehn Prozent für jeden Monat, insgesamt drei Monate. Aber die Zeit ist um und ich besitze kein Geld, um den Artikel wegen unglücklicher Ereignisse einzulösen\nJetzt sagt er, dass er einen Käufer gefunden hat für "+pchar.GenQuest.Noblelombard.Item+" und er wird es verkaufen, wenn ich meine Schulden und Zinsen nicht sofort zurückzahle. Aber ich habe jetzt nicht viel Geld und der Gegenstand, den ich verpfändet habe, ist sehr teuer...";
			link.l1 = "Und wie kann ich Ihnen dabei helfen, "+GetAddress_FormToNPC(NPChar)+"?";
			link.l1.go = "lombard_1";
		break;
		
		case "lombard_1":
			dialog.text = "Ich bitte Sie, mit unserem Bankier zu sprechen. Bieten Sie ihm Geld an, bürgen Sie für mich... oder tun Sie etwas anderes. Leider habe ich niemanden, den ich bitten könnte, all meine guten Freunde sind plötzlich 'bankrott' gegangen. In drei Monaten "+pchar.GenQuest.Noblelombard.Text+", und ich werde Ihnen alle Ihre Kosten doppelt erstatten! Sie haben mein Wort als Gentleman!";
			link.l1 = "Gut, ich werde versuchen, Ihnen in diesem Fall zu helfen.";
			link.l1.go = "lombard_2";
			link.l2 = "Leider bin ich gerade selbst 'pleite'. Ich kann dir also nicht helfen, es tut mir so leid!";
			link.l2.go = "lombard_exit";
		break;
		
		case "lombard_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Noblelombard");
		break;
		
		case "lombard_2":
			dialog.text = "Danke für Ihr Verständnis. Ich werde auf Sie in der Taverne warten. Kommen Sie so schnell wie möglich dort hin.";
			link.l1 = "...";
			link.l1.go = "lombard_3";
		break;
		
		case "lombard_3":
			DialogExit();
			pchar.GenQuest.Noblelombard = "true"
			pchar.GenQuest.Noblelombard.Name = GetFullName(npchar);
			pchar.GenQuest.Noblelombard.id = npchar.id;
			pchar.GenQuest.Noblelombard.City = npchar.city;
			pchar.GenQuest.Noblelombard.Money = 20000+hrand(60)*500;
			pchar.GenQuest.Noblelombard.Percent = makeint(sti(pchar.GenQuest.Noblelombard.Money)*0.3);
			pchar.GenQuest.Noblelombard.Summ = sti(pchar.GenQuest.Noblelombard.Money)+sti(pchar.GenQuest.Noblelombard.Percent);
			pchar.GenQuest.Noblelombard.Chance = hrand(9);
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома
			FreeSitLocator(pchar.GenQuest.Noblelombard.City + "_tavern", "sit1");
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", pchar.GenQuest.Noblelombard.City+"_tavern", "sit", "sit1", "Nobleman_lombardTavern", 10);
			SetFunctionTimerCondition("Noblelombard_Over", 0, 0, 1, false); //таймер до конца суток
			ReOpenQuestHeader("Noblelombard");
			AddQuestRecord("Noblelombard", "1");
			AddQuestUserData("Noblelombard", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Noblelombard.City));
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
		break;
		
		case "lombard_4":
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Regard"))
			{
				pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
				dialog.text = "Was kannst du sagen, "+GetAddress_Form(NPChar)+"? Waren Sie in der Bank? Haben Sie gute oder schlechte Nachrichten?";
				if (pchar.GenQuest.Noblelombard == "full") link.l1 = "Ich habe es getan. Ich habe all eure Schulden selbst zurückgezahlt. Ihr könnt dorthin gehen und euer Relikt zurückholen.";
				if (pchar.GenQuest.Noblelombard == "maxpercent") link.l1 = "Ich habe. Ich habe alle Zinsen für die letzten drei Monate und auch für die nächsten drei zurückgezahlt. Sie können sicher auf Ihr Geld warten. Vergessen Sie nur nicht, Ihre Hauptschuld in drei Monaten zurückzuzahlen.";
				if (pchar.GenQuest.Noblelombard == "minpercent") link.l1 = "Ich habe. Ich habe alle Zinsen für die letzten drei Monate zurückgezahlt. Der Bankier hat zugestimmt, weitere drei Monate zu warten, bis Sie die gesamte Summe erhalten werden.";
				link.l1.go = "lombard_5";
			break;
			}
			if (pchar.GenQuest.Noblelombard == "fail")
			{
				dialog.text = "Was kannst du sagen, "+GetAddress_Form(NPChar)+"? Waren Sie in der Bank? Haben Sie gute oder schlechte Neuigkeiten?";
				link.l1 = "Ich habe. Dieser Geizhals hat eine unglaubliche Summe verlangt. Er lehnte jegliche Bitten um Zugeständnisse ab und ich habe nicht die benötigte Summe. Also konnte ich dir nicht helfen. Tut mir Leid.";
				link.l1.go = "lombard_fail";
			}
			else
			{
				dialog.text = "Was kannst du sagen, "+GetAddress_Form(NPChar)+"? Waren Sie in der Bank? Haben Sie gute oder schlechte Nachrichten?";
				link.l1 = "Ich bin dran. Warte.";
				link.l1.go = "exit";
				NextDiag.TempNode = "lombard_4";
			}
		break;
		
		case "lombard_fail":
			pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
			dialog.text = "Meh, "+GetAddress_Form(NPChar)+"... Nun sind Sie auch Zeuge der unaufhaltsamen Gier dieser verfluchten blutrünstigen Wucherer. Bei Gott, Herr, sie bringen Juden in Verruf! Denken Sie daran, wenn Sie versuchen, Geld von ihnen zu leihen, wie ich es getan habe. Danke, dass Sie es zumindest versucht haben...";
			link.l1 = "Ich mochte sie nie. Nun, wer mag Wucherer? Es tut mir leid, "+GetAddress_FormToNPC(NPChar)+". Lebewohl.";
			link.l1.go = "lombard_fail_1";
		break;
		
		case "lombard_fail_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Noblelombard", "4");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			sld = characterFromId(pchar.GenQuest.Noblelombard.City+"_usurer");
			DeleteAttribute(sld, "quest.noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
		break;
		
		case "lombard_5":
			dialog.text = "Unglaublich! Du hast mich gerade gerettet, "+GetAddress_Form(NPChar)+"! Ich werde es nie vergessen. Ich versichere Ihnen, dass all Ihre Kosten doppelt erstattet werden. Kommen Sie in drei Monaten zu unserem Bankier. Ich werde ein Depot auf Ihren Namen eröffnen.";
			link.l1 = "Gut, ich werde tun, was du sagst. Auf Wiedersehen!";
			link.l1.go = "lombard_6";
		break;
		
		case "lombard_6":
			dialog.text = "Nochmals danke, Kapitän. Viel Glück!";
			link.l1 = "...";
			link.l1.go = "lombard_7";
		break;
		
		case "lombard_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeOfficersLoyality("good_all", 1);
			AddQuestRecord("Noblelombard", "5");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			SetFunctionTimerCondition("Noblelombard_Regard", 0, 0, 90, false); //таймер
		break;
//<-- семейная реликвия

//------------------------------------------привезти рабов под заказ--------------------------------------------
		case "slaves":
			npchar.quest.slaves.price = 3+hrand(1);//цена на рабов в дублонах
			npchar.quest.slaves.qty = 50+hrand(5)*10;//количество
			npchar.quest.slaves.money = sti(npchar.quest.slaves.qty)*sti(npchar.quest.slaves.price);
			dialog.text = "Ich besitze ein "+LinkRandPhrase("Fabrik","meine","Plantage")+" und ich habe immer Bedarf an frischen Sklaven. Das Klima macht sie wirklich fertig. Gerade jetzt brauche ich "+sti(npchar.quest.slaves.qty)+" Köpfe. Ich bin bereit, eine Partie davon zu bestellen. Ich werde Gold für jeden Kopf bezahlen, "+sti(npchar.quest.slaves.price)+" Dublonen\nKeine Eile, ich werde dir keine Zeit setzen, wenn du mir bringst, was ich brauche. Natürlich in Maßen, zieh es nicht länger als ein halbes Jahr hinaus. Also, was sagst du? Abgemacht?";
			link.l1 = "Abgemacht! Sklaverei ist ein schmutziges Geschäft, aber es ist das Risiko wert.";
			link.l1.go = "slaves_1";
			link.l2 = "Entschuldigung, aber ich bin kein Sklavenhändler. Nicht meine Art von Arbeit.";
			link.l2.go = "exit_slaves";
		break;
		
		case "exit_slaves":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "slaves_1":
			dialog.text = "Sehr gut dann. Ich werde auf dich warten, wenn du die Ladung bringst. Du kannst mich jeden Tag von 11 Uhr bis 13 Uhr in der Kirche finden. Den Rest des Tages bin ich beschäftigt oder bei der Arbeit.";
			link.l1 = "Gut. Ich werde mich daran erinnern. Bis dann, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			DialogExit();
			sGlobalTemp = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			SaveCurrentNpcQuestDateParam(npchar, "slaves_date");//запоминаем дату
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", npchar.city+"_church", "sit", "sit"+(1+rand(5)), "Nobleslaves_Place", 10.0);
			chrDisableReloadToLocation = true;//закрыть локацию
			Colonies[FindColony(npchar.city)].questslaves = true;
			sTitle = npchar.city+"Nobleslaves";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Nobleslaves", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sQty", sti(npchar.quest.slaves.qty));
			AddQuestUserData(sTitle, "sMoney", sti(npchar.quest.slaves.money));
		break;
		
		case "slaves_3":
			if (GetNpcQuestPastDayParam(npchar, "slaves_date") < 180)
			{
				dialog.text = "Haben Sie gebracht "+sti(npchar.quest.slaves.qty)+" Sklaven, wie ich Sie gebeten habe, Kapitän?";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= sti(npchar.quest.slaves.qty))
				{
					link.l1 = "Ja. Die ganze Ladung befindet sich in meinem Laderaum. Ich bin bereit, sie Ihnen zu übergeben.";
					link.l1.go = "slaves_4";
				}
				else
				{
					link.l1 = "Nein, ich bin dabei.";
					link.l1.go = "exit";
					NextDiag.TempNode = "slaves_3";
				}
			}
			else
			{
				dialog.text = "Kapitän, wenn Sie wegen dieser Sklaven hier sind... Ich habe bereits genug gekauft und brauche im Moment keine weiteren. Sie haben zu lange gebraucht, Entschuldigung.";
				link.l1 = "So eine Schande! Aber du hast recht, ich war nicht schnell genug. Lebewohl!";
				link.l1.go = "slaves_8";
			}
		break;
		
		case "slaves_4":
			dialog.text = "Ausgezeichnet. Ich werde sofort ein Beiboot für sie aussenden.";
			link.l1 = "Was ist mit meiner Bezahlung?";
			link.l1.go = "slaves_5";
		break;
		
		case "slaves_5":
			dialog.text = "Mach dir keine Sorgen, ich erinnere mich daran. Hier, nimm die Summe, "+sti(npchar.quest.slaves.price)+" Dublonen pro Kopf. Ein guter Deal für uns beide, ja?";
			link.l1 = "Danke. Geschäft mit Ihnen zu machen war angenehm.";
			link.l1.go = "slaves_6";
		break;
		
		case "slaves_6":
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(npchar.quest.slaves.qty));
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.slaves.money));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.slaves.money))+"");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ich sollte wohl... Verzeihung, ich muss gehen. Wir sehen uns!";
			link.l1 = "Viel Glück, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_7";
		break;
		
		case "slaves_7":
			DialogExit();
			npchar.lifeday = 0;
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			LAi_SetActorType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(npchar, npchar.city+"_church", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "2");
			CloseQuestHeader(sTitle);
		break;

		case "slaves_8":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "3");
			CloseQuestHeader(sTitle);
		break;
//<-- привезти рабов под заказ

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Hör zu, als Bürger dieser Stadt bitte ich dich, dein Schwert zu verstecken.","Hör zu, als Bürger dieser Stadt bitte ich dich, dein Schwert zu scheiden.");
			link.l1 = LinkRandPhrase("Gut.","Wie du wünschst.","Gut.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetHP(NPChar, 400, 400);
			TakeNItems(NPChar, "potion2", 3);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "TempFight");
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterNationReputation(pchar, sti(npchar.nation), -3);
		break;
	}
}

string DonationText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "I've lost all my money in gambling yesterday and I don't have enough sum to wipe away the debt. Can you help me?" break;
		case 1: sText = "I had a nice time yesterday with a... certain lady of the evening, and now she is trying to blackmail me. I need to pay her first and then I will deal with her... Can you help me with some money?" break;
		case 2: sText = "I ran through a local fool with my rapier recently and now the commandant demands a bribe to hush up the event. I am short of money now. Can you help me?" break;
		case 3: sText = "I was unlucky enough to lose a bet and I don't have a trifling sum to repay the debt of honor. Can you help me?" break;
		case 4: sText = "Some bastard knows about my... indiscreet activities concerning a married woman. I don't have enough money to shut his mouth. Just a few gold coins are needed... " break;
		case 5: sText = "Some bastard has stolen important papers from my house and demanding a significant sum for their return. I've almost got it, just a few more coins needed. Can you help me?" break;
	}
	return sText;
}

void LombardText()
{
	switch (hrand(5))
	{
		case 0:
			pchar.GenQuest.Noblelombard.Item = "my mother's diamond pendant made by a jeweler from Madrid";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get my inheritance","my ship will return from Africa loaded with slaves");
		break;
		case 1: pchar.GenQuest.Noblelombard.Item = "an emerald necklace of my sister crafted by a jeweler in Paris";
				pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will inherit a county in Europe","my ship will return from India loaded with spices and silk");
		break;
		case 2:
			pchar.GenQuest.Noblelombard.Item = "family ring with an emblem of our kin";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("my expedition will return from the Spanish Main with gold ingots","I will get my inheritance");
		break;
		case 3:
			pchar.GenQuest.Noblelombard.Item = "a ruby bracelet of my wife, a gift from her mother";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get my investment with the interest from a European bank","I will get the profits from my plantation");
		break;
		case 4:
			pchar.GenQuest.Noblelombard.Item = "a necklace of gold and diamonds, piece work, a pride of my wife";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get profits from my current business","my ship will be back from Africa with the cargo hold stuffed with black ivory");
		break;
		case 5:
			pchar.GenQuest.Noblelombard.Item = "an ivory cane of semiprecious stones, a gift from my grandfather";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("my ship will be back from India with the cargo hold filled with silks and spices","I will receive my interest from a European bank");
		break;
	}
}
