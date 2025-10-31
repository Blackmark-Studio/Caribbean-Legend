// Addon-2016 Jason, французские миниквесты (ФМК) Последний урок
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ein offensichtlicher Fehler. Informiere die Entwickler darüber.";
			link.l1 = "Oh, das werde ich.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "greguar":
			PlaySound("Voice\English\LE\Greguar\Greguar_04.wav");
			pchar.quest.FMQL_delete_guide.over = "yes";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
			if (CheckAttribute(pchar, "questTemp.HWIC") || pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! Du siehst anders aus, mein Freund und du hast Erfolg! Sie beginnen über dich zu sprechen, weißt du? Du lernst schnell, Monsieur, ich bin wirklich stolz auf dich. Ich wünsche dir weitere Glück und Erfolg in der Zukunft! Es freut mich, dich wieder zu sehen!";
				link.l1 = "Monseniour Gregoire Valinnie, was für ein Treffen! Ich schulde Ihnen viel für meine bescheidenen Erfolge. Freut mich auch, Sie zu treffen! Viel Glück!";
				link.l1.go = "greguar_exit_1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! Du siehst anders aus, mein Freund, und du bist erfolgreich! Sie fangen an, über dich zu reden, weißt du? Du lernst schnell, Monsieur, ich muss sagen, du hast mich stolz gemacht.";
				link.l1 = "Herr Gregoire Valinnie, was für eine Begegnung! Ich verdanke Ihnen viel für meine bescheidenen Erfolge. Es freut mich, Sie zu treffen! Lassen Sie mich raten, Sie haben einen Geschäftsvorschlag für mich?";
				link.l1.go = "greguar_1";
			}
		break;
		
		case "greguar_1":
			dialog.text = "Aye! Das tue ich. Ich werde kurz sein, Zeit ist Geld. Also, ein holländisches Kronensquadron segelte von Brasilien nach Curacao mit einer Ladung strategisch wertvoller Güter und wurde von den Engländern zwischen Trinidad und dem Festland überfallen. Eine Flöte der Kompanie konnte fliehen und an der Küste von Boca de la Serpienta anlegen. Sie retteten einen Teil der Ladung, doch nicht für lange - sie wurden von einem lokalen Indianerstamm angegriffen. \nNach meinen Informationen haben sie jeden Holländer an dieser Küste ausgelöscht und die Ladung in ihr Dorf gebracht. Die Indianer haben auch die holländischen Feuerwaffen ergriffen, aber schwere Verluste erlitten. Das ist unsere Chance! Die Briten und die Holländer kämpfen noch in dieser Region und sie sind zu beschäftigt, um sich um die verlorene Flöte zu kümmern. Zum jetzigen Zeitpunkt... Du hast ein Schiff und eine Mannschaft. Wir können dorthin segeln, landen und die Indianer erledigen. Die Ladung ist äußerst wertvoll und es gibt eine Menge davon dort.\nIch habe bereits eine kleine Expedition zur Aufklärung geschickt - das war alles, was ich mir leisten konnte, erinnere dich an die Geldprobleme? Ich habe einen vertrauenswürdigen Käufer, du kannst auf mein Schwert und meine Söldner zählen. Fünfzig-fünfzig Aufteilung, wir haben eine Woche, um dorthin zu gelangen. Also mein Freund, bist du dabei?";
			link.l1 = "Verzeihen Sie mir, Monsieur, aber ich lehne ab. Ich komme gerade von einer harten Reise, wir haben nicht genug Zeit für Reparaturen und Rekrutierungen. Selbst an diesem von Gott vergessenen Ort kann ein Mann nicht alles haben.";
			link.l1.go = "greguar_exit";
			link.l2 = "Es klingt wie ein gefährliches Geschäft mit einem Hauch von anständigem Profit und Abenteuern darin. Natürlich bin ich dabei! Lassen wir keine Zeit verschwenden!";
			link.l2.go = "greguar_2";
		break;
		
		case "greguar_exit":
			dialog.text = "Schade. Es ist Ihre Entscheidung. Gott sei mit Ihnen, Monsieur, ich werde trotzdem dorthin gehen. Ein Mann muss es versuchen, nicht wahr?";
			link.l1 = "Gute Fahrt, Monsieur Valinnie!";
			link.l1.go = "greguar_exit_1";
		break;
		
		case "greguar_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 20.0);
		break;
		
		case "greguar_2":
			dialog.text = "Richtige Wahl, mein Freund! Du kannst zusätzliches Geld gebrauchen, richtig? Wie geht es übrigens deinem Bruder?";
			link.l1 = "Ich kann immer zusätzliches Geld gebrauchen. Michel? Mein Bruder ist gesund und ihm ist langweilig. Manchmal beneide ich ihn... Zeit, die Segel zu setzen!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_Begin");
		break;
		
		case "greguar_3":
			PlaySound("Voice\English\QuestMan02.wav");
			dialog.text = "So einfach wie Kuchen! Das waren die Neulinge, die den Scharmützel mit den Holländern überlebt haben. Wir sollten tiefer ins Festland vordringen, meine Expedition muss dort sein!";
			link.l1 = "Es schien zu einfach... aber es ist zu früh zum Feiern, Monsieur Valinnie. Schau mal dort drüben...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_SecondCoastBattle");
		break;
		
		case "greguar_4":
			PlaySound("Voice\English\LE\Greguar\Greguar_05.wav");
			dialog.text = "Verdammt, diese Rothäute! Sie hatten uns fast! Nun bin ich sicher, dass nur noch Frauen und Kinder im Dorf übrig sind. Auf geht's!";
			link.l1 = "Ich bin mir nicht sicher, dass du Musketen erwähnt hast, ich habe sie nicht gesehen... Ach was auch immer. Los geht's!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_GoToJungle");
		break;
		
		case "greguar_5":
			PlaySound("Voice\English\LE\Greguar\Greguar_06.wav");
			dialog.text = "Bedeutung? Die Holländer und wir müssen sie alle getötet haben!";
			link.l1 = "";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_7":
			dialog.text = "Fliehen? Bist du verrückt? Wir sind fast da! Hast du Angst vor einer Horde bemalter Wilder?";
			link.l1 = "";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_9":
			dialog.text = "Das Allerletzte, Kapitän. Ich kehre nach Europa zurück. Ich bin enttäuscht! In dir, in diesen Feiglingen und in dieser verdammten Region!";
			link.l1 = "...";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			DialogExit();
			DoQuestReloadToLocation("shore18", "goto", "goto8", "FMQL_JungleExit");
		break;
		
		case "greguar_11":
			dialog.text = "Puh! Wir haben es geschafft!";
			link.l1 = "Aber um welchen Preis! Schau! Fast jeder in unserer Truppe ist tot. Wir sollten uns zurückziehen, Gregoire, es gibt keine Garantien, dass mehr Krieger auf uns warten. Außerdem fehlen uns einfach die Zahlen, um die Beute zu tragen.";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "Verdammt! Es ist traurig, aber du hast recht, "+pchar.name+": selbst wenn die Wilden alle tot sind, werden wir die Ladung nicht wegtragen können, bevor die Holländer oder die Engländer hier landen. Wir müssen jetzt gehen! Verdammt sei diese Küste!";
			link.l1 = "...";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_13":
			dialog.text = "Puh! Wir haben es geschafft! Gut gemacht, "+pchar.name+"! Jetzt gehen wir zum Höhlen der Wilden für unseren Preis! Nichts kann uns jetzt stoppen!";
			link.l1 = "Wir sollten uns beeilen, während die Briten und die Niederländer noch miteinander beschäftigt sind. Los geht's!";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			DialogExit();
			DoQuestCheckDelay("FMQL_RunToGrabbing", 1.0);
		break;
		
		case "greguar_15":
			dialog.text = "Wir haben gut gearbeitet, "+pchar.name+". Nun müssen wir nur noch die Ladung verkaufen, ohne Verdacht zu erregen. Ich habe einen soliden Käufer, er wird uns um Mitternacht in der Bucht von Lamentin erwarten. Nehmt keine Offiziere mit und meidet den Ort vor dem Treffen, der Kunde ist ein sehr nervöser Geselle.";
			link.l1 = "Geschäft ist Geschäft. Die Ladung muss verkauft werden und das muss sicher geschehen, sonst wird meine Schuld bei Poincy noch höher steigen. Gut, ich werde bis Mitternacht da sein.";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.quest.FMQL_goods_timer.win_condition.l1 = "Timer";
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQL_goods_timer.function = "FMQL_MeetingOnLamanten";
			AddQuestRecord("FMQ_Lesson", "7");
			LAi_LocationDisableOfficersGen("Shore38", true); // may-16
			LAi_LocationFightDisable(&Locations[FindLocation("Shore38")], true);
			locations[FindLocation("Shore38")].DisableEncounters = true;
			Pchar.GenQuest.Hunter2Pause = true;
		break;
		
		case "greguar_17":
			PlaySound("Voice\English\Master_01.wav");
			pchar.quest.FMQL_goods_over.over = "yes";// лесник снято прерывание на встречу.
			dialog.text = "Es ist getan. Die Ladung ist entladen, der Kunde ist hier. Lassen Sie uns das Gespräch führen.";
			link.l1 = "...";
			link.l1.go = "greguar_18";
		break;
		
		case "greguar_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("FMQL_contra_"+i);
				if (i == 2) 
				{
					LAi_CharacterEnableDialog(sld);
					AddLandQuestMark(sld, "questmarkmain");
				}
			}
		break;
		
		case "greguar_19":
			dialog.text = "Überraschung, ihr Bastarde!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_LookOnGuards");
		break;
		
		case "greguar_20":
			PlaySound("Voice\English\OliverTrast01.wav");
			dialog.text = "Ach, Johnny, was für ein Kerl! Großartig! Hast du etwas zu sagen, "+pchar.name+"?";
			link.l1 = "Nein. Eigentlich ja! Was zur Hölle?!";
			link.l1.go = "greguar_21";
		break;
		
		case "greguar_21":
			dialog.text = "Ärgern Sie den toten Mann nicht, Monsieur. Wo sind Ihre Manieren?.. Das Geld ist hier, die Fracht wird von mir und meinen Freunden betreut. Ich habe sie nicht an die Küste geschickt, das wäre eine Verschwendung gewesen. Besonders Johnny dorthin zu schicken. Siehst du diesen Rothäutigen dort mit einer Kulewin in den Händen? Weißt du, Johnny mochte seinen eigenen Stamm nie wirklich.";
			link.l1 = "Ich verstehe... Was jetzt? Wirst du mich auch töten?";
			link.l1.go = "greguar_22";
		break;
		
		case "greguar_22":
			dialog.text = "Nun, ich sollte es tun. Aber ich bin sentimental. Geh und nimm ein Viertel des Geldes. Die Ladung und der Rest des Geldes bleiben hier bei mir. Versuche nicht, den Helden zu spielen, das sind nicht die Dschungel des Festlandes. Du hast keine Chance.";
			link.l1 = "Und wo sind deine Adel und Manieren, Gregoire? Das habe ich von dir nicht erwartet. Ich gehe, aber das werde ich nicht vergessen.";
			link.l1.go = "greguar_23";
			link.l2 = "Ich spiele keinen Helden, habe ich nie getan. Ich werde euch einfach alle töten! Zuerst diese Damen, dann den Affen mit dem Granatwerfer und dann dich!";
			link.l2.go = "greguar_25";
		break;
		
		case "greguar_23":
			dialog.text = "Es gibt weder Adlige noch Schläger an diesem Strand, Monsieur. Es gibt nur fünf Männer, eine große Kanone und ein Opfer. Dies geschieht hier ständig, aber Sie haben die einzig richtige Wahl getroffen. Gut gemacht. Wissen Sie, dass an Ihrer Stelle hier und jetzt zwei andere stehen könnten? Sie sind fast genau wie Sie. Aber Sie sind hier und sie sind es nicht, und ich denke, sie werden deswegen umkommen.";
			link.l1 = "Ich verstehe nicht...";
			link.l1.go = "greguar_24";
		break;
		
		case "greguar_24":
			dialog.text = "Eines Tages wirst du. Sie haben ihre letzte Lektion nicht erhalten. Du hast. Du bist willkommen. Lebewohl, Monsieur. Willkommen in der Karibik!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_PeaceFinal");
		break;
		
		case "greguar_25":
			dialog.text = "Ahh... Du bist nicht der hellste Schüler, den ich hatte. Nun gut... jedem das Seine!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_BattleOnBeach");
		break;
		
		case "mercen":
			PlaySound("Voice\English\pirat_guard_4.wav");
			dialog.text = "Perfektes Timing! Wir sind gerade noch so vor der Horde der Kariben geflohen, sie waren auf dem Weg in deine Richtung und, nach deinem Aussehen zu urteilen, hast du sie bereits getroffen. Ihr Dorf ist in der Nähe, aber unsere Probleme fangen gerade erst an.";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper":
			dialog.text = ""+GetFullName(pchar)+"! Du bist hier! Und warum bin ich nicht überrascht! Perfektes Timing, mein Freund. Wir sind gerade noch so der Horde der Kariben entkommen, sie waren in deine Richtung unterwegs und, nach deinem Aussehen zu urteilen, hast du sie bereits getroffen.";
			link.l1 = "Prosper! Und ich bin überrascht! Wieder Löcher in die Indianer gemacht? Hoffentlich geht es Selina gut?";
			link.l1.go = "prosper_1";
		break;
		
		case "prosper_1":
			dialog.text = "Es war töricht von mir, mich dieser Expedition anzuschließen, ich frage mich, ob meine Tochter mich jemals wiedersehen wird. Selina? Nun, sie sitzt zu Hause und träumt von dir! Die Jugendlichen von Martinique haben mittlerweile jede Hoffnung verloren... Weißt du, ich bereue es nicht mehr, dieses Musket gekauft zu haben. Eine solide Feuerwaffe. Zuverlässig. Auch ein zusätzlicher Grund, an einem weiteren Selbstmordversuch teilzunehmen, obwohl es jetzt ein bisschen weniger selbstmörderisch ist, seit du aufgetaucht bist. Ihr Dorf ist in der Nähe, aber unsere Probleme fangen gerade erst an.";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper_2":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_3":
			dialog.text = "Nicht alle von ihnen. Unser Späher wurde erschossen, hat es aber trotzdem in ihr Versteck geschafft. Ein Häuptling selbst kommt hierher mit seinen Wächtern. Und sie haben holländische Musketen. Sie haben einen Vorteil in Zahlen und sie sind wütend wie die Hölle. Der Häuptling ist der beste Krieger ihres Stammes, seine Männer sind Teufel in Fleisch und Blut. Wir sollten schnell entscheiden, hier und jetzt. Entweder wir kämpfen gegen sie oder wir fliehen. Ehrlich gesagt, ziehe ich das Letztere vor...";
			link.l1 = "";
			link.l1.go = "prosper_4";
		break;
		
		case "prosper_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_5":
			dialog.text = "Sie haben sie nicht gesehen, mein guter Mann! Diese 'Wilden' haben Musketen und sie sind überraschend gut damit. Jemand hat ihnen Unterricht gegeben, daran besteht kein Zweifel! Also nennen Sie mich nicht noch einmal einen Feigling!";
			link.l1 = "Lassen wir uns beruhigen und entscheiden, was zu tun ist. Es ist noch Zeit.";
			link.l1.go = "prosper_6";
		break;
		
		case "prosper_6":
			int n = 0;
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("FMQL_sailor_"+i) != -1) n++;
			}
			dialog.text = "Ich höre zu, "+pchar.name+".";
			if (n > 2 && GetSummonSkillFromName(pchar, SKILL_SNEAK) > 30)
			{
				Notification_Skill(true, 31, SKILL_SNEAK);
				link.l1 = "Wir werden ihnen einen Kampf liefern, Jungs! Es gibt Waren und Geld gleich hinter diesem Hügel! Wir sind hier für sie und wir gehen nicht weg. Keine Chance, dass irgendein Haufen Rothäute, selbst mit Muskete, uns stoppen kann! Lasst uns die verdammten Kerle begraben und die Arbeit beenden! Wir haben genug Männer, es besteht die Chance, sie zu überfallen. Vier Männer werden sie mit Feuer von den Flanken begrüßen und der Rest von uns wird hier Stellung nehmen. Dezimiert ihre Zahl und macht sie fertig!";
				link.l1.go = "prosper_8";
			}
			else
			{
				if (GetCharacterSkill(pchar, SKILL_SNEAK) < 31) Notification_Skill(false, 31, SKILL_SNEAK);
				if (n < 3) notification("Not enough people", "X");
				if (n > 0)
				{
					link.l1 = "Wir werden ihnen einen Kampf liefern, Jungs! Es gibt Waren und Geld gleich hinter diesem Hügel! Wir sind hier für sie und wir gehen nicht. Keine Chance, dass uns irgendein Haufen Rothäute, auch mit Musketen, aufhalten kann! Lasst uns die Mistkerle begraben und die Arbeit erledigen!";
					link.l1.go = "prosper_7";
				}
				else
				{
					link.l1 = "Die Chancen stehen in jeder möglichen Weise gegen uns. Vergessen Sie nicht die Holländer direkt hinter uns.";
					link.l1.go = "prosper_9";
				}
			}
		break;
		
		case "prosper_9":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_7":
			DialogExit();
			pchar.questTemp.FMQL = "battle";
			AddDialogExitQuestFunction("FMQL_PrepareAttack");
		break;
		
		case "prosper_8":
			DialogExit();
			pchar.questTemp.FMQL = "sneak";
			AddDialogExitQuestFunction("FMQL_PrepareSneakAttack");
		break;
		
		case "prosper_9x":
			dialog.text = "Wir leben und wir sind zu Hause! Ich schwöre, ich hatte genug von Abenteuern... für die nächsten paar Monate, ha-ha! Ich sollte zu meiner Tochter gehen, bitte besuchen Sie uns, "+pchar.name+". Und bitte, sei vorsichtig.";
			link.l1 = "Keine Versprechungen, Prosper. Viel Glück!";
			link.l1.go = "prosper_10";
		break;
		
		case "prosper_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
		break;
		
		case "prosper_11":
			pchar.quest.FMQL_prosper_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			PlaySound("Voice\English\pirat_guard_4.wav");
			dialog.text = "Ich habe Sie gewarnt, Kapitän, seien Sie vorsichtig! Ich hatte Verdacht gegen diesen Bastard.";
			link.l1 = "Prosper! Danke dir! Aber wie?";
			link.l1.go = "prosper_12";
		break;
		
		case "prosper_12":
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.FMQL.PirateDead")) sTemp = "Poor lad, even though he was a pirate.";
			dialog.text = "Johnny wurde zu gesprächig. Der Rothaut-Typ auf dem Sand. Er ging in ein Bordell und versuchte, ein Mädchen aufzureißen. Sie weigerten sich, ihn zu bedienen, Johnny wurde wütend, fing an zu schreien, dass er bald reich sein würde, sobald er und seine Kumpels irgendeinen Kapitän in den Dschungeln töten würden. Ich sah, was kommen würde und rannte zu eurem Offizier, der es auch geschafft hat, in der Stadt etwas Unruhe zu stiften. "+sTemp+" Ich schulde dir viel, "+pchar.name+", also besteht kein Grund, mir allzu sehr zu danken.";
			link.l1 = "Und dennoch, vielen Dank, Prosper! Es war hart hier ... zu hart. Möchtest du meiner Crew beitreten? Ich brauche einen Offizier wie dich. Es ist heutzutage schwer, loyale Männer zu finden, insbesondere Scharfschützen.";
			link.l1.go = "prosper_13";
		break;
		
		case "prosper_13":
			dialog.text = "Nein, mein Freund. Ich habe Verpflichtungen gegenüber meiner Tochter. Sie hat mich schwören lassen, meine Abenteuer hinter mir zu lassen. Es war mein letztes. Verdammt, was für ein Pech, aber ich liebe meine Tochter mehr als alles andere auf der Welt. Lebewohl, "+pchar.name+". Und.. Selina spricht die ganze Zeit über dich. Vielleicht könntest du uns eines Tages besuchen?";
			link.l1 = "Wer weiß, vielleicht werde ich das... Lebewohl, Prosper! Ich wünsche, dass deine Tochter einen guten Ehemann findet... (zu sich selbst) Lektion gelernt, Monsieur Gregoire, Lektion gelernt... jeder nach seiner Fasson, sagte er... Ich werde das in Erinnerung behalten.";
			link.l1.go = "prosper_14";
		break;
		
		case "prosper_14":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "15");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "contra":
			DelLandQuestMark(npchar);
			dialog.text = "Wer zum Teufel bist du?";
			link.l1 = "Wir haben die Ladung. Interessiert?";
			link.l1.go = "contra_1";
		break;
		
		case "contra_1":
			dialog.text = "Ha. Sehr interessiert. Vor allem mein Klient. Was ist der Gewinn?";
			link.l1 = ""+FindRussianQtyString(sti(pchar.questTemp.FMQL.Sanl))+" aus Eisenholz, "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Silk))+" von Schiffsseide, "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Rope))+" aus Seil und "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Oil))+" aus Harz.";
			link.l1.go = "contra_2";
		break;
		
		case "contra_2":// Addon 2016-1 Jason пиратская линейка
			iTotalTemp = 2200*sti(pchar.questTemp.FMQL.Sanl)+1600*sti(pchar.questTemp.FMQL.Silk)+1000*sti(pchar.questTemp.FMQL.Rope)+900*sti(pchar.questTemp.FMQL.Oil);
			dialog.text = "Sehr gut. 2200 Pesos für jedes Stück Eisenholz, 900 Pesos für Harz, 1600 Pesos für Schiffsseide und 1000 Pesos für Seile. Was haben wir hier... Na-na. "+iTotalTemp+" Pesos. Abgemacht?";
			link.l1 = "Abgemacht!";
			link.l1.go = "contra_3";
		break;
		
		case "contra_3":
			LAi_Fade("", "");
			FMQL_CreateGuidesWarriors();
			dialog.text = "Prächtig! Bring mehr. Die Holländer hören nie auf, großzügig zu den Rothäuten zu sein... Und wer sind diese Gäste? Was zum Teufel?!";
			link.l1 = "";
			link.l1.go = "contra_4";
		break;
		
		case "contra_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_19";
			AddMoneyToCharacter(sld, iTotalTemp);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FMQL_beach":
			pchar.quest.FMQL_pirate_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			dialog.text = "Ja, Kapitän. Ich habe aus einem Grund zu viel vom Segeln getrunken.";
			link.l1 = "Du? Wie?!";
			link.l1.go = "FMQL_beach_1";
		break;
		
		case "FMQL_beach_1":
			dialog.text = "Es tut mir leid, Kapitän. Nach dem Durcheinander mit den Indianern musste ich ein oder zwei Becher trinken. Da war ein Mädchen, ich habe ein Zimmer für hundert Pesos genommen und sie... sie...";
			link.l1 = "Was? Dich ausgeraubt?";
			link.l1.go = "FMQL_beach_2";
		break;
		
		case "FMQL_beach_2":
			sld = CharacterFromID("FMQL_Prosper");
			dialog.text = "Nein! Sie hat sich verliebt! Verdammt, ich hätte von dort weglaufen sollen! Aber dann taucht dein Freund auf, schreit mich wegen diesem Abschaum an, deinem ehemaligen Gefährten, der dich übers Ohr hauen und dich töten will.";
			if (LAi_GetCharacterHP(sld) > 0)
			{
				link.l1 = "Gut gemacht, Prosper...";
				link.l1.go = "FMQL_beach_3";
			}
			else
			{
				link.l1 = "Prosper... Es tut mir so leid. Ich werde mich um deine Tochter kümmern. Lektion gelernt, Monsieur Gregoire... Was hast du gesagt? Jedem das Seine? Ich sollte mich daran erinnern.";
				link.l1.go = "FMQL_beach_3";
			}
		break;
		
		case "FMQL_beach_3":
			dialog.text = "Sollen wir gehen, Kapitän?";
			link.l1 = "Ja. Danke für Ihren Dienst. Halten Sie sich von einem Becher fern und wir werden Sie vor dieser Schönheit retten. Los geht's.";
			if (CheckAttribute(pchar, "questTemp.FMQL.ProsperDead")) link.l1.go = "FMQL_beach_5";
			else link.l1.go = "FMQL_beach_4";
		break;
		
		case "FMQL_beach_4": // Проспер жив
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload_sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			sld = CharacterFromID("FMQL_Prosper");
			sld.Dialog.currentnode = "prosper_11";
			sld.MusketerDistance = 20;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0); 
		break;
		
		case "FMQL_beach_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			if (sti(pchar.money) >= 20000) DoQuestFunctionDelay("FMQL_MoneyForSelina", 0.5);
			else
			{
				pchar.quest.FMQL_money_20k.win_condition.l1 = "Money";
				pchar.quest.FMQL_money_20k.win_condition.l1.value = 20000;
				pchar.quest.FMQL_money_20k.win_condition.l1.operation = ">=";
				pchar.quest.FMQL_money_20k.function = "FMQL_MoneyForSelina";
			}
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "10");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
