void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Was wollen Sie?";
			link.l1 = "Nichts.";
			link.l1.go = "exit";
		break;

		case "Naemnik":
			dialog.text = "Du bist gut"+GetSexPhrase("","e")+"... verdammt gut"+GetSexPhrase("","e")+". Aber bevor du den Auftrag abschließt, hör mich an. Ich bin sicher, was ich dir sage, wird dich interessieren.";
			link.l1 = "Na gut, du darfst vor deinem Tod sprechen. Aber mach dir keine Hoffnungen – aus dieser Höhle kommst du nicht lebend raus.";
			link.l1.go = "Naemnik_2";
		break;

		case "Naemnik_2":
			dialog.text = "Der Hafenmeister, ja? Er hat dich auf meinen Kopf angesetzt?";
			link.l1 = "Schlau wie eh und je.";
			link.l1.go = "Naemnik_3";
		break;

		case "Naemnik_3":
			dialog.text = "Er hat dich geschickt, um mich zu töten, nicht wahr? Nicht um mich zu fangen, nicht um mich festzunehmen – sondern um mich zu töten?";
			link.l1 = "Ganz genau. Na und?";
			link.l1.go = "Naemnik_4";
		break;

		case "Naemnik_4":
			dialog.text = "Oh... du bist so ein"+GetSexPhrase("Trottel","Dummchen")+". Hast du jemals darüber nachgedacht, warum es ihm so wichtig ist, mich zu töten und nicht einfach ins Gefängnis zu stecken? Nein? Du hast keine Ahnung, wen du da eigentlich rettest. Diese Spinne im Hafen hat alles in ein Netz aus Lügen gehüllt, und du, "+GetSexPhrase("Junge","Kleines")+", steckst mittendrin.\nDu denkst, er ist ein ehrlicher Verwalter? Ha, Ehrlichkeit kennt er nur im Traum! Er verkauft Hinweise an Piraten und Holländer. Verrät diejenigen, die ihm vertrauen. So ein Abschaum gehört unter die Erde!";
			link.l1 = "Wer durch den Dreck watet, ist auch nicht sauber! Du bist selbst kein Heiliger.";
			link.l1.go = "Naemnik_5";
		break;

		case "Naemnik_5":
			dialog.text = "Ich bin keiner, und ich tu auch nicht so. Meine Klinge lügt nie. Ein Blick, und der Mensch weiß – der Tod ist da. Ich lächle meinem Opfer nicht zu, schüttle ihm nicht die Hand, wenn ich weiß, es ist verloren. Nein. Meine Absichten sind klar. Aber dieser Bürokrat...\nEr verrät jeden, der ihm vertraut, und tut dabei so, als würde er helfen. Er ist schlimmer als jeder Bastard, den ich je ins Grab gebracht habe.";
			link.l1 = "Angenommen, du sagst die Wahrheit. Wer hat dich angeheuert?";
			link.l1.go = "Naemnik_6";
		break;

		case "Naemnik_6":
			dialog.text = "Den Namen sage ich dir nicht – ich kenne ihn selbst nicht. Aber es ist jemand, der unter diesem Dreckskerl gelitten hat. Jemand, der Gerechtigkeit oder Rache will. Nenn es, wie du willst, es macht keinen Unterschied. Fünfhundert Dublonen für den Kopf dieses faulen Beamten! Hilf mir, und wir teilen das Geld.";
			link.l1 = "Genug geschwätzt! Du würdest alles erzählen, um deine jämmerliche Haut zu retten. Ich habe dich ausreden lassen"+GetSexPhrase("","")," jetzt ist Schluss.";
			link.l1.go = "Naemnik_7";
			link.l2 = "Eine schöne Geschichte. Aber ich glaube dir nicht aufs Wort. Hast du Beweise, Zeugen? Oder ist das nur ein weiterer Trick, um dem Tod zu entgehen?";
			link.l2.go = "Naemnik_8";
		break;
		
		case "Naemnik_7":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_UbivaemNaemnika");
		break;
		
		case "Naemnik_8":
			dialog.text = "Diese Papiere wurden in der Kabine eines Piraten gefunden, den mein Auftraggeber im Kampf besiegte. Er bekam Hinweise vom Hafenmeister. In den Notizen sind deutlich die Routen der Schiffe, ihre Abfahrtszeiten und die transportierten Waren angegeben.\nUnd das Wichtigste: Die Handschrift stimmt exakt mit der in den offiziellen Frachtpapieren überein. Diese Dokumente sind der Schlüssel, ihn zu entlarven. Mein Auftraggeber will, dass sie auf der Leiche gefunden werden. Ein gewöhnliches Gerichtsverfahren reicht nicht aus.\nDieser Schuft ist zu einflussreich und hat viele korrupte Freunde. Wäre es vor Gericht gegangen, hätte er sich herausgewunden. Solche wie er verdienen keinen Platz unter den Lebenden. Der Tod mit Schande – das ist alles, was er verdient.";
			link.l1 = "Elender Bastard! Die Leute vertrauen ihm ihr Leben an, und er verkauft sie an Piraten! Ich bin dabei. Für solche Menschen ist auf dieser Welt kein Platz.";
			link.l1.go = "Naemnik_9";
			GiveItem2Character(PChar, "GS_letters");
			AddQuestRecordInfo("GS_Letters", "1");
		break;

		case "Naemnik_9":
			dialog.text = "Ich habe einen Schlüssel zu seinem Haus – über einen Tischler bekommen, der seine Möbel reparierte. Alles lief glatt, bis ich merkte, dass er nicht allein dort wohnt. Als ich kam, um die Sache zu beenden, war seine Frau im Haus.\nIhre Anwesenheit überraschte mich. Niemand hätte extra für ihren Kopf bezahlt, und die Behörden hätten sich noch intensiver auf die Suche nach dem Mörder gemacht. Also änderte ich den Plan und lauerte ihm beim Verwaltungshaus auf.";
			link.l1 = "Verdammt. Die ganze Stadt ist in Aufruhr, einfach reinmarschieren und ihn umlegen funktioniert nicht. Was also tun?";
			link.l1.go = "Naemnik_10";
		break;

		case "Naemnik_10":
			dialog.text = "Ich habe die Stadt beobachtet und gewartet, bis sich alles beruhigt. Nach meinem Besuch schickte der feige Ratte seine Frau fort. Ich habe mit eigenen Augen gesehen, wie sie ein Schiff bestieg und den Hafen verließ.\nJetzt ist er allein – die perfekte Gelegenheit, das zu beenden. In der Nacht kannst du in seine Höhle schleichen und dem Spuk ein Ende setzen. Dann leg die Papiere so hin, dass jeder sieht, was für ein verrottetes Wesen er war.\nAber ich kann die Stadt im Moment nicht betreten. Du aber... du kannst das. Niemand erwartet dich. Du wirst leicht hineinschlüpfen. Sein Haus steht in der Nähe des Stadtgefängnisses. Fünfhundert Dublonen! Die Hälfte gehört dir, wenn du es zu Ende bringst.";
			link.l1 = "Gut. Ich persönlich werde diesen Mistkerl ins Jenseits befördern. Die Papiere bleiben in seinem Haus – die Wahrheit muss ans Licht. Warte hier. Ich komme zurück, sobald es erledigt ist.";
			link.l1.go = "Naemnik_11";
		break;

		case "Naemnik_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
			AddQuestRecord("GS", "5");
			AddQuestUserData("GS", "sSex", GetSexPhrase("","а"));
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetWarriorType(sld);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			NextDiag.CurrentNode = "Naemnik_12";
			
			sld = &Locations[FindLocation("Beliz_town")];
			sld.reload.l11.open_for_night = 1;
			sld = &Locations[FindLocation("Beliz_houseS5_room2")];
			sld.locators_radius.item.button01 = 1.0;
			
			pchar.quest.GS_SoldatyDoma.win_condition.l1 = "Hour";
			pchar.quest.GS_SoldatyDoma.win_condition.l1.start.hour = 0.00;
			pchar.quest.GS_SoldatyDoma.win_condition.l1.finish.hour = 5.00;
			PChar.quest.GS_SoldatyDoma.win_condition.l2 = "location";
			PChar.quest.GS_SoldatyDoma.win_condition.l2.location = "Beliz_houseS5";
			PChar.quest.GS_SoldatyDoma.function = "GS_SoldatyDoma";
		break;
		
		case "Naemnik_12":
			dialog.text = "Warum stehst du da wie angewurzelt"+GetSexPhrase("","e")+"?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Naemnik_12";
		break;

		case "Portman_1":
			dialog.text = "Sie? Was zum Teufel? Wie sind Sie hier hereingekommen?";
			link.l1 = "Wie ich hierher gekommen"+GetSexPhrase("","e")+" bin, spielt keine Rolle. Und ich glaube, tief in Ihrem Inneren wissen Sie genau, warum ich gekomm"+GetSexPhrase("en","en")+" bin.";
			link.l1.go = "Portman_2";
			DelLandQuestMark(npchar);
		break;

		case "Portman_2":
			dialog.text = "Nein, ich verstehe nicht! Wenn Sie wegen der Belohnung hier sind, kommen Sie morgen zur Verwaltung, ich werde alles übergeben.";
			link.l1 = "Hören Sie auf, unschuldig zu tun! Ich weiß alles. Sie haben Piraten Hinweise über die Schiffe Ihrer Kunden verkauft. Ein so abscheulicher Mensch verdient es nicht, solche Ämter zu bekleiden. Mehr noch – Sie verdienen es nicht, unter ehrlichen Leuten zu leben. Ihr Platz ist bei Ihresgleichen – in der Hölle.";
			link.l1.go = "Portman_3";
		break;

		case "Portman_3":
			dialog.text = "Oh, nein-nein-nein! Nein! Sie haben alles falsch verstanden! S-sie haben mich gezwungen... Sie kamen zu mir und drohten, meine Familie zu töten, wenn ich ihnen nicht helfe... Sie verstehen das nicht...";
			link.l1 = "Ich habe genug von Ihren jämmerlichen Ausreden! Ich habe Ihre Notizen in der Hand, in denen Sie Ihren Anteil für die Tipps fordern! Ihre Heuchelei ist abscheulich, und ich werde das nicht länger dulden. Ziehen Sie Ihre Waffe und verteidigen Sie sich, wenn Sie den Mut dazu haben!";
			link.l1.go = "Portman_4";
		break;
		
		case "Portman_4":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Beliz_portman_clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_PortmanDead");
		break;
		
		case "Naemnik_21":
			dialog.text = "Nun, was gibt es Neues? Ist die Sache erledigt?";
			link.l1 = "Hast du etwa gezweifelt? Er hat sich alle Mühe gegeben, eine armselige Ausrede zu finden, aber es hat ihm nichts gebracht. Ich habe die Notizen gut sichtbar hinterlassen, wie wir es vereinbart hatten.";
			link.l1.go = "Naemnik_22";
		break;

		case "Naemnik_22":
			dialog.text = "Solche erbärmlichen Würmer wie er denken immer, dass sie sich mit billigen Lügen und etwas Geld vom Schwert der Gerechtigkeit freikaufen können.";
			link.l1 = "Nun, jetzt denkt er überhaupt nicht mehr. Gib mir mein Geld, und ich gehe.";
			link.l1.go = "Naemnik_23";
		break;

		case "Naemnik_23":
			dialog.text = "Hier sind deine Dublonen. Ausgezeichnete Arbeit, das muss ich zugeben. Aber weißt du, wenn ich damals etwas Solideres in der Hand gehabt hätte, hätte das Ganze vielleicht anders ausgehen können... für dich. In den engen Wänden des Hauses kann man kaum ausholen, also habe ich dieses armselige Zahnstocher genommen, um die Sache schnell zu erledigen.\nHätte ich gewusst, wie es läuft, hätte ich etwas Solideres mitgenommen.";
			link.l1 = "Ha-ha. Und unser armer Mann sagte, du wärst bewaffnet wie Roland vor dem Pass von Roncesvalles!";
			link.l1.go = "Naemnik_24";
			AddItems(pchar, "gold_dublon", 250);
		break;

		case "Naemnik_24":
			dialog.text = "Heh. Nun, Angst hat große Augen. Du hast selbst gesehen, mit welcher Gabel ich fast dein Herz durchbohrt hätte.";
			link.l1 = "Willst du damit sagen, dass du mit einem schwereren Eisen mir hättest Paroli bieten können?";
			link.l1.go = "Naemnik_25";
		break;

		case "Naemnik_25":
			dialog.text = "Im Umgang mit mittelgroßen Waffen bin ich ein Meister, das ist Fakt. Glaubst du mir nicht? Na gut, ich teile mit dir ein paar Tricks, die mir schon oft das Leben gerettet haben. Hör gut zu – das sind keine bloßen Worte, sondern etwas, das dir eines Tages das Leben retten könnte. Solche Geheimnisse teilt man nicht mit jedem.";
			link.l1 = "...";
			link.l1.go = "Naemnik_26";
		break;
		
		case "Naemnik_26":
			DialogExit();

			SetLaunchFrameFormParam("Eine Stunde ist vergangen...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("GS_Spravedlivost_2", 0.0);
			LaunchFrameForm();
		break;

		case "Naemnik_27":
			dialog.text = "...";
			link.l1 = "Ich sehe, du verstehst wirklich dein Handwerk. Danke für die Lektion. Aber wenn das alles ist, muss ich gehen.";
			link.l1.go = "Naemnik_28";
			AddComplexSelfExpToScill(0, 500, 0, 0);
		break;

		case "Naemnik_28":
			dialog.text = "Leb wohl, "+GetSexPhrase("Käpt'n","Süße")+". Hoffen wir, dass wir uns nicht im Kampf wiedersehen. Es wäre schade, dich zu töten. Ha-ha.";
			link.l1 = "Du hättest nicht den Hauch einer Chance, selbst wenn ich betrunken und auf einem Bein stünde, heh! Also, leb wohl, Söldner.";
			link.l1.go = "Naemnik_29";
		break;

		case "Naemnik_29":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
			LAi_SetPlayerType(pchar);

			LAi_SetWarriorType(npchar);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PEACE);

			AddQuestRecord("GS", "7");
			CloseQuestHeader("GS");

			AddSimpleRumourCity("Man sagt, der Hafenmeister wurde tot in seinem eigenen Haus gefunden. Bei ihm fand man Notizen, die seine Beteiligung am Verschwinden von Schiffen beweisen. Welch eine Schande für unsere Stadt...", "Beliz", 30, 1, "");
			AddSimpleRumourCity("Hast du schon gehört? Jemand ist ins Haus des Hafenmeisters eingebrochen, hat die Wachen getötet und ihn umgebracht. Auf der Leiche fand man Routenpläne verschwundener Schiffe – von ihm selbst geschrieben! Ein Diener der Krone, aber in Wahrheit ein Verräter! Er bekam, was er verdiente! Und wo hat der Gouverneur all die Jahre hingeschaut?", "Beliz", 30, 1, "");
			AddSimpleRumourCity("Der Hafenmeister wurde getötet! Direkt in seinem eigenen Haus! Die Wachen wurden niedergemetzelt, und unter seinen Sachen waren Notizen mit Routen verschwundener Schiffe. Kein Zweifel, er war verantwortlich! Der Schurke hat seine gerechte Strafe erhalten.", "Beliz", 30, 1, "");
		break;
	}
}