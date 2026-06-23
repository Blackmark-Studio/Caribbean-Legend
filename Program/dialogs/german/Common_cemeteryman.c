// Jason общий диалог смотрителей кладбищ
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Cemetery\" + NPChar.City + "_cemetery.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
    int iTemp;
	string sTemp;
	bool ok;
    
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("Die Stadt ist in Alarmbereitschaft. Scheint, als wäre es Zeit für mich, auch zu den Waffen zu greifen...","Bist du nicht von der gesamten Stadtwache verfolgt? Zu mir, Soldaten!!!","Du wirst hier keinen Schutz finden. Aber ein paar Zentimeter kalten Stahls unter einer Rippe!"),LinkRandPhrase("Was willst du, Schurke?! Ein Stadtwächter hat bereits deine Spur aufgenommen, du wirst nicht weit fliehen, "+GetSexPhrase("schmutziger Pirat!","Schurke")+"!","Halt! "+GetSexPhrase("Dreckiger Mörder! Wache!!!","Ich habe keine Angst vor dir! Bald wirst du in unserer Festung aufgehängt werden, es gibt keinen Ort zum Verstecken...")));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Scheint, als wärst du des Lebens müde...","Und warum wollt ihr nicht ruhig leben, Bürger..."+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("Geh zur Hölle!","Es bleiben dir nur noch ein paar Sekunden in dieser Welt..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Lantern"))
			{
				dialog.text = "A-a-ah! Ah, es bist du... Wer bist du? Was hast du auf dem Friedhof verloren?";
				link.l1 = "Mein Name ist "+GetFullName(pchar)+". Und wer bist du und was machst du hier? Und warum hast du solche Angst?";
				link.l1.go = "Lantern_01";
				npchar.quest.meeting = "1";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToCrypt")
			{
				dialog.text = "Also, wie war es? Hast du nachgesehen? Glaubst du mir jetzt?";
				link.l1 = "Nein, ich bin noch nicht in die Gruft hinuntergegangen. Warte noch ein bisschen, ich werde alles überprüfen.";
				link.l1.go = "exit";
				break;
			}
			
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToKeeper")
			{
				dialog.text = "So? Hast du einen Blick geworfen? Hast du es gesehen?";
				link.l1 = "Ja, sicher! Du hattest recht!";
				link.l1.go = "Lantern_10";
				link.l2 = "Es war nicht ganz das, was du dachtest.";
				link.l2.go = "Lantern_14";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("Hallo, Seemann! Mein Name ist "+GetFullName(npchar)+", und ich bin die einzige lebende Seele hier. Eigentlich werden wir alle sowieso sterben, ha-ha-ha! Warum bist du gekommen?","Hallo! Ich habe schon lange keinen lebenden Mann mehr gesehen... Darf ich mich vorstellen - "+GetFullName(npchar)+", und dieser Friedhof ist meine letzte Zuflucht. Anscheinend werde ich hier begraben. Wie kann ich Ihnen helfen?");
				link.l1 = "Hallo, "+npchar.name+"! Mein Name ist "+GetFullName(pchar)+", und ich bin ein Kapitän. Ich ging durch den Dschungel und kam hierher. Dachte, ich schaue mal in diesem gemütlichen Haus vorbei, um zu sehen, wer hier nicht Angst hat zu leben...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, mein alter Freund, Kapitän "+GetFullName(pchar)+"! Komm rein, komm rein!";
				link.l1 = "Willkommen, Freund! Sehr froh, dich zu sehen. Siehst du nachts keine tanzenden Skelette und tote Menschen mit Kupfermünzen auf den Augen in deinen Träumen?";
				link.l1.go = "talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Und warum sollte ich Angst haben, Kapitän? Man muss vor lebenden Menschen Angst haben, die Toten beißen nicht. Eh! Einmal hatte ich ein ganz anderes Leben, und jetzt bin ich Wächter dieses Friedhofs. Ich kümmere mich um Gräber. Und manchmal handele ich auch mit einigen seltsamen Dingen...";
			link.l1 = "Und welche Waren handelst du, sag mir bitte?";
			link.l1.go = "trade_info";
		break;
		
		case "talk":
			dialog.text = "Was hat dich dieses Mal zu mir geführt?";
			link.l1 = "Zeig mir, was du heute zum Verkauf hast.";
			link.l1.go = "trade";
			link.l2 = "Ich möchte dir eine Frage stellen...";
			link.l2.go = "quests";
			link.l3 = "Nichts Ernstes. Ich bin einfach gekommen, um dich zu begrüßen.";
			link.l3.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "Ich habe viel freie Zeit, daher gehe ich gerne im Dschungel spazieren, um nützliche Pflanzen und schicke Steine zu sammeln. Dann verkaufe ich sie in der Stadt. Sie kosten nicht viel, aber - es ist besser als nichts. Und ich bekomme eine Vielzahl von Dingen von meinen Freunden...";
			link.l1 = "Freunde? Sie meinen, Sie verkaufen weiter, was andere Ihnen bringen?";
			link.l1.go = "trade_info_1";
		break;
		
		case "trade_info_1":
			dialog.text = "O-ho-ho... Nein, sie geben mir alles kostenlos. Wer kann ein Freund eines Friedhofswächters sein, wenn nicht Tote?";
			link.l1 = "Wa... Plünderst du etwa Leichen?";
			link.l1.go = "trade_info_2";
		break;
		
		case "trade_info_2":
			dialog.text = "I don't rob; I just take things off those who don't need them anymore. Many different people are buried here-some unknown and not from our lands. The commandant brings a dead body from the town and says: 'This is for you, "+npchar.name+", send him on his final journey.' Homeless, hanged pirates, bandits killed by guardians-all are buried here. And old "+npchar.name+" buries their bodies on a Christian custom.";
			link.l1 = "Ich verstehe. Nun, Geld ist Geld, zeig mir, was du hast.";
			link.l1.go = "trade";
			link.l2 = "Habe es verstanden. Ich muss gehen. Es hat mich gefreut, dich kennenzulernen.";
			link.l2.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
			NextDiag.TempNode = "First time";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(int(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("Und du, "+GetFullName(pchar)+", bist ein Dieb! Wachen!!!","Was zum Teufel! Ich habe nur einen Moment weggeschaut und du versuchst schon, das zu stehlen, was mir gehört! Haltet den Dieb!!!","Wache! Raub!!! Schnappt den Dieb!!!");
			link.l1 = "Ach Scheiße!!!";
			link.l1.go = "fight";
		break;
		//belamour квест на получение фонаря -->
		case "Lantern_01":
			dialog.text = "Puh, also bist du nur ein Reisender ... Mein Name ist "+GetFullName(npchar)+", Ich bin der Hüter dieses gottverlassenen Ortes.";
			link.l1 = "Warum fühlen Sie sich so über den Friedhof? Im Gegenteil, von hier aus nimmt unser Herr die Gerechten nach der Beerdigung.";
			link.l1.go = "Lantern_02";
		break;
		
		case "Lantern_02":
			dialog.text = "Aber die Ungerechten, anscheinend, bleiben hier nach der Beerdigung! In den letzten paar Nächten gab es Geräusche aus der Gruft. Und die Seufzer sind so erschreckend, dass es mir Schauer über den Rücken jagt... Es scheint, dass eine verlorene Seele keine Ruhe finden kann! Jetzt schlafe ich nur noch tagsüber - nachts kann ich meinen Posten nicht verlassen oder ein Auge zu machen...";
			link.l1 = "Geräusche? Stöhnen? Aber da ist niemand außer den Verstorbenen.";
			link.l1.go = "Lantern_03";
		break;
		
		case "Lantern_03":
			dialog.text = "Das ist es, was ich sage, verstehst du? Du solltest besser hier rauskommen, bevor der Geist dich bemerkt... Sonst wirst du nicht schlafen können, genau wie ich.";
			link.l1 = "Hm, ja, ich denke, ich sollte diesen Ort besser verlassen.";
			link.l1.go = "Lantern_04";
			link.l2 = "Vielleicht kann ich Ihnen helfen? Lassen Sie mich heute Abend in diese seltsamen Geräusche hineinhören.";
			link.l2.go = "Lantern_05";
		break;
		
		case "Lantern_04":
			pchar.questTemp.Lantern = "NoLantern";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_05":
			dialog.text = "Bist du von Sinnen?! Ich sehe, du hast eine Waffe, aber wie planst du damit gegen die Untoten zu kämpfen? Und wenn du dort den Löffel abgibst, was dann? Der Geist wird frei herumwandern und dich vielleicht sogar als seinen Diener erwecken!";
			link.l1 = "Nun, das ist nur Aberglaube...";
			link.l1.go = "Lantern_06";
		break;
		
		case "Lantern_06":
			dialog.text = "Welcher Aberglaube? Dies ist nicht das fromme Land Europa, verdammt ... Die Eingeborenen, diese rotgesichtigen Leute, sie können alles heraufbeschwören - und jetzt müssen wir hier leben!";
			link.l1 = "Dennoch, lass mich es versuchen. Ich werde bis zur Nacht warten und dann zur Gruft hinuntergehen.";
			link.l1.go = "Lantern_07";
		break;
		
		case "Lantern_07":
			dialog.text = "Gut, mach, was du willst. Aber wenn du nicht bis zum Sonnenaufgang zurückkommst, werde ich alles abschließen, verbarrikadieren und auf eigene Faust hier rauskommen! Egal ob als Matrose das Deck schrubben oder als Hafenarbeiter Kisten schleppen - ich werde sowieso nicht hierher zurückkommen!";
			link.l1 = "Beruhige dich einfach... Alles wird gut werden.";
			link.l1.go = "Lantern_08";
		break;
		
		case "Lantern_08":
			dialog.text = "Warte... Nimm diese Laterne. Ich habe eine Ersatzlaterne. Du wirst sie dort brauchen. Es ist stockdunkel!";
			link.l1 = "Danke, eine Laterne wird tatsächlich nützlich sein an einem solchen Ort.";
			link.l1.go = "Lantern_09";
		break;
		
		case "Lantern_09":
			GiveItem2Character(pchar, "lantern_belt");
			Log_Info("'Lantern' received");
			PlaySound("interface\important_item.wav");
			if(npchar.city == "Charles") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Charles_CryptBig2", true);
			if(npchar.city == "Havana") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Havana_CryptBig2", true);
			if(npchar.city == "Villemstad" || npchar.city == "PortRoyal") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Common_CryptBig2", true);
			pchar.quest.NoiseCemetery_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NoiseCemetery_SeaExit.function = "NoiseCemetery_SeaExit";
			pchar.questTemp.Lantern = "ToCrypt";
			pchar.questTemp.Lantern.nation = npchar.nation;
			AddQuestRecord("NoiseCemetery", "1");
			AddQuestUserData("NoiseCemetery", "sCity", XI_ConvertString(loadedlocation.islandId)); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_10":
			dialog.text = "Stimmt's? Was war da? Erzähl mir!";
			link.l1 = "Da war der unruhige Geist einer Frau! Glücklicherweise hatte ich den örtlichen Priester meine Klinge segnen lassen, um die Bösen zu zerschmettern, also hat alles geklappt. Dieser Geist wird dich nicht mehr belästigen.";
			link.l1.go = "Lantern_11";
		break;
		
		case "Lantern_11":
			dialog.text = "Oh Herr, rette unsere sündigen Seelen! Ich habe euch gewarnt! Und ihr habt mir nicht geglaubt!";
			link.l1 = "Ja, und das bedaure ich aufrichtig. Aber jetzt ist alles in Ordnung - ich habe diesen Ort mit Weihwasser bespritzt, und kein Geist wird es wagen, aus dem Grab zu steigen. Du kannst ruhig schlafen.";
			link.l1.go = "Lantern_12";
		break;
		
		case "Lantern_12":
			dialog.text = "Vielen Dank! Sie haben keine Ahnung, was das für mich bedeutet! Hier, bitte nehmen Sie das. Es ist nicht viel, aber ich kann Sie nicht ohne Belohnung gehen lassen.";
			link.l1 = "Danke, ich kann nicht ablehnen. Viel Glück für dich!";
			link.l1.go = "Lantern_13";
		break;
		
		case "Lantern_13":
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "3");
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_14":
			dialog.text = "Nein? Also was zum Teufel... Ich meine, was zum Himmel, ist dort passiert?";
			link.l1 = "Es gab überhaupt keinen Geist. Ein junges Paar wählte diese Gruft als Ort für ihre Verabredungen. Ihre Eltern sind gegen diese Verbindung, also suchten sie einen Ort, um alleine zu sein.";
			link.l1.go = "Lantern_15";
		break;
		
		case "Lantern_15":
			dialog.text = "Allein?.. Warum diese jungen Leute! Lassen sie es nur wagen, hierher zurückzukommen! Entweder jage ich beide mit einer Peitsche weg oder schließe sie in der Gruft ein, damit sie dort bleiben!!!";
			link.l1 = "Sie werden hier nicht mehr zurückkommen. Ich habe ihnen gesagt, dass ihre kleinen Eskapaden die örtliche Wache wirklich erschreckt haben. Sie beabsichtigen, das zu tun. Und übrigens, das Schloss an der Tür ist sowieso kaputt.";
			link.l1.go = "Lantern_16";
		break;
		
		case "Lantern_16":
			dialog.text = "Kein Problem, ich werde es ersetzen. Aber wenn ich sie jemals erwische...";
			link.l1 = "Sei nicht so wütend. Wir waren alle mal in dem Alter. Sie sind nicht hierher gekommen, weil dies der beste Ort zum Daten war.";
			link.l1.go = "Lantern_17";
		break;
		
		case "Lantern_17":
			dialog.text = "Gut genug... Nun, Gott sei mit ihnen. Danke, dass Sie einen alten Mann nicht in Schwierigkeiten lassen. Hier, bitte nehmen Sie das. Es ist nicht viel, aber ich kann Sie nicht ohne Belohnung gehen lassen.";
			link.l1 = "Danke, ich kann nicht ablehnen. Viel Glück für dich!";
			link.l1.go = "Lantern_18";
		break;
		
		case "Lantern_18":
			DialogExit();
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "4");
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		// <-- квест на получение фонаря 
	}
}
