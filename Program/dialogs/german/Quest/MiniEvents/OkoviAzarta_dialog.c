void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
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
		
		case "OZ_Kuznets_1":
			//PlaySound("VOICE\Russian\Master_05.wav");
			dialog.text = "Was möchten Sie, "+GetAddress_Form(NPChar)+"? Verzeihen Sie, aber ich nehme keine neuen Aufträge an. Ich habe einfach... zu viel Arbeit...";
			link.l1 = "Ach ja? Man sagt, Sie hätten neulich beim Kartenspiel etwas sehr Wertvolles verloren, stimmt das?";
			link.l1.go = "OZ_Kuznets_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Kuznets_2":
			dialog.text = "Nun, wenn Sie gekommen sind, um sich an meinem Unglück zu ergötzen, stellen Sie sich hinten an – es gibt auch ohne Sie genug Freiwillige. Nur hat mir keiner davon Hilfe angeboten. Mein Schicksal hängt am seidenen Faden, und es liegt ganz in den Händen von Javier Castillo, während die Leute sich nur über mein Pech amüsieren wollen.";
			link.l1 = "Ich gehöre nicht zu denen, die über das Unglück anderer lachen. Erzählen Sie mir, wie es dazu kam. Vielleicht kann ich Ihnen helfen.";
			link.l1.go = "OZ_Kuznets_3";
			link.l2 = "Hilfe? Und warum sollte Ihnen überhaupt jemand helfen? Ich werde es jedenfalls nicht tun. Sie sind selbst der Schmied Ihres Glücks... und auch Ihres Unglücks. Also hören Sie auf, sich als Opfer darzustellen – akzeptieren Sie einfach die Folgen Ihrer Taten, sie sind mehr als verdient.";
			link.l2.go = "OZ_Kuznets_NoAgree";
		break;
		
		case "OZ_Kuznets_NoAgree":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Kuznets_NoAgree");
		break;
		
		case "OZ_Kuznets_3":
			dialog.text = "Dieser Abend hätte nicht mein Verhängnis werden sollen. Ich ging nur in die Taverne, um nach einem großen Auftrag vom Admiral Eugenio de la Torre ein Glas Rum zu trinken. Doch, bereits gut angeheitert, setzte ich mich an den Kartentisch. Da nahm sich Javier meiner an\nAnfangs war das Glück auf meiner Seite – ich gewann sogar eine ansehnliche Summe. Aber sobald ich an mein Glück glaubte, wendete sich das Blatt schlagartig. Javier goss immer weiter Rum in meinen Becher, und ich verlor Spiel um Spiel: zuerst mein Bargeld, dann das Geld für Materialien und schließlich all meine Ersparnisse\nAls mir klar wurde, wie viel ich bereits verloren hatte, war es zu spät, um aufzuhören. Ich war nur noch von einem Gedanken besessen – mich um jeden Preis zurückzuholen. Also setzte ich mein Buch aufs Spiel. Dieser Schurke Javier bewertete es auf nur fünftausend Pesos\nNatürlich ist es viel mehr wert, aber ich war so vom Spielrausch geblendet, dass ich zustimmte. Und dann... Nun, ich denke, Sie wissen schon, wie es weiterging. Ich verlor. So etwas ist mir noch nie passiert. Ich glaube, dieser Schuft hat mich irgendwie betäubt.";
			link.l1 = "Und womit, darf ich fragen, könnte ich Ihnen helfen? Sie haben sich doch selbst an den Tisch gesetzt, selbst Ihr Eigentum aufs Spiel gesetzt und alles verloren. Jetzt wollen Sie nur die Folgen nicht akzeptieren? Und was ist so wertvoll an diesem Buch, dass Sie so darüber verzweifeln?";
			link.l1.go = "OZ_Kuznets_4";
		break;
		
		case "OZ_Kuznets_4":
			dialog.text = "Dieses Buch ist das Wertvollste, was ich besaß. Es enthält Geheimnisse, die über Jahrhunderte von Meister zu Schüler weitergegeben wurden. Es ist das Herz meiner Schmiede, die Seele meines Handwerks. Mit der Niederlage habe ich mich bereits abgefunden, "+GetAddress_Form(NPChar)+", aber wie soll ich mich mit dem Verlust dieses Buches abfinden? Ich bot Javier an, es für fünftausend Pesos zurückzukaufen\nIch wäre sogar bereit gewesen, Schulden zu machen, nur um es zurückzubekommen. Aber wissen Sie, was er sagte? Er wolle hunderttausend dafür! Hundert, "+GetAddress_Form(NPChar)+"! So viel Geld habe ich nicht. Und er ist nicht bereit, den Preis zu senken oder Ratenzahlungen zu akzeptieren. Ich flehte ihn an... aber er lachte mich nur aus. Ich sehe, Sie sind "+GetSexPhrase("ein mutiger Mann, ein Seemann... vielleicht sogar ein Kapitän. Und Ihre Waffe tragen Sie sicher nicht nur zur Zierde","keine gewöhnliche Frau, und Sie können sicherlich jeden Mann um den Finger wickeln")+"\nIch bitte Sie, sprechen Sie mit Javier. Vielleicht hört er auf Sie und stimmt einer Zahlungsfrist zu. Ohne dieses Buch... hat mein Leben keinen Sinn mehr. Im Gegenzug werde ich Ihnen, sobald ich wieder auf die Beine komme, stets hochwertige Materialien zu einem guten Preis verkaufen – vielleicht kann ich sogar etwas Besonderes für Sie anfertigen, Kapitän.";
			link.l1 = "Nun, reden ist keine große Sache. Mal sehen, was sich daraus ergibt. Aber zunächst darf ich mich vorstellen: Mein Name ist "+GetFullName(pchar)+", ich bin Kapitän meines eigenen Schiffes.";
			link.l1.go = "OZ_Kuznets_5";
		break;
		
		case "OZ_Kuznets_5":
			dialog.text = ""+GetSexPhrase("Und ich bin Sebastián Cordoba...","Eine Frau – Kapitän ihres eigenen Schiffes? Davon habe ich gehört, aber noch nie persönlich eine getroffen und gesprochen.")+" Freut mich, Sie kennenzulernen, Kapitän "+pchar.lastname+". Und ich danke Ihnen. In unserer Zeit findet man leichter jene, die sich über das Unglück anderer lustig machen, als solche, die bereit sind zu helfen. Wissen Sie, wenn mein Buch jemals zu mir zurückkehrt, schwöre ich: Ich werde nie wieder Glücksspiele spielen.";
			link.l1 = "Noch haben Sie keinen Grund, mir zu danken. Erst werde ich meine Angelegenheiten regeln, und wenn dann noch Zeit bleibt, spreche ich mit Javier.";
			link.l1.go = "OZ_Kuznets_6";
		break;
		
		case "OZ_Kuznets_6":
			dialog.text = "Ich fürchte, Sie könnten zu spät kommen. Javier erwies sich als weit geschickter, als ich dachte\nEr hat bereits einen Käufer für das Buch gefunden – es ist Étienne Renoir, ein französischer Waffenmeister. Wenn der Admiral erfährt, dass wegen mir solch ein Schatz in die Hände der Franzosen gelangt... werde ich meinen Kopf verlieren. Das Gefängnis wäre da noch eine milde Strafe.";
			link.l1 = "Hm... Nun gut. Ich werde mich sofort um Ihr Problem kümmern.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			AddDialogExitQuestFunction("OZ_Kuznets_Agree");
		break;
		
		case "OZ_Kuznets_repeat":
			dialog.text = "Kapitän "+ pchar.lastname +"! Haben Sie mit Javier gesprochen? Gibt es Neuigkeiten?";
			link.l1 = "Noch nicht, aber ich bin gerade auf dem Weg in die Taverne.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			if (CheckCharacterItem(PChar, "OZ_book"))
			{
				link.l1 = "Ja, ich habe mit ihm gesprochen. Und zwar sehr erfolgreich. Javier hat sich eilends ins Jenseits verabschiedet, aber vorher noch Ihr Buch zurückgegeben. Hier, bitte.";
				link.l1.go = "OZ_Kuznets_11";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "OZ_Kuznets_11":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", Sie können sich gar nicht vorstellen, was das für mich bedeutet! Dank Ihnen kann ich alle Aufträge ausführen, sogar den für den Admiral selbst! Geld habe ich leider keines, aber ich habe dennoch eine Belohnung für Sie vorbereitet\nHier, nehmen Sie diesen Kürass – ich habe ihn für einen Don angefertigt, aber ich bin sicher, er kann noch etwas warten. Außerdem habe ich einige Materialien, die Ihnen nützlich sein werden, falls Sie selbst etwas herstellen möchten.";
			link.l1 = "Danke, "+npchar.name+", Sie sind sehr großzügig!";
			link.l1.go = "OZ_Kuznets_12";
			TakeItemFromCharacter(pchar, "OZ_book");
		break;
		
		case "OZ_Kuznets_12":
			dialog.text = "Und noch etwas – schauen Sie bei mir vorbei, wenn Sie Materialien benötigen. Ich bekomme Lieferungen einmal im Monat, also wird für Sie immer etwas Nützliches dabei sein – und das zu einem guten Preis. Ich halte meine Versprechen.";
			link.l1 = "Ich werde sicher vorbeischauen! Nun, "+npchar.name+", bleiben Sie gesund. Ich muss jetzt gehen, die Arbeit ruft.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Nagrada");
			GiveItem2Character(PChar, "cirass3");
			AddItems(PChar, "jewelry13", 10);
			AddItems(PChar, "jewelry12", 5);
			AddItems(PChar, "jewelry10", 5);
			AddItems(PChar, "jewelry11", 2);
			AddQuestRecordInfo("Useful_Acquaintances", "7");
		break;
		
		case "OZ_Kuznets_Fail":
			dialog.text = "Kapitän "+ pchar.lastname +"! Haben Sie mit Javier gesprochen? Gibt es Neuigkeiten?";
			link.l1 = "Sehen Sie... das Buch war in meinen Händen. Aber... die Umstände waren so, dass es verkauft wurde.";
			link.l1.go = "OZ_Kuznets_Fail_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Kuznets_Fail_2":
			dialog.text = "Was?! Sie... Sie haben es verkauft?! Mein Buch?!";
			link.l1 = "Das Buch, das Sie beim Kartenspiel verloren haben. Es wurde an den Franzosen verkauft, dem es Javier versprochen hatte.";
			link.l1.go = "OZ_Kuznets_Fail_3";
		break;
		
		case "OZ_Kuznets_Fail_3":
			dialog.text = "Aber... das ist mein Ende. Das Buch ist bei den Franzosen, der Auftrag des Admirals wird nicht erfüllt... mein Leben ist ruiniert... Ich... ich bin verloren!";
			link.l1 = "Sie haben sich selbst in diese Lage gebracht. Ich denke, das wird Ihnen eine gute Lehre sein. Lebewohl.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Fail");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "OZ_Shuler_1":
			PlaySound("Voice\english\tavern\Igroki v Tavernah-01.wav"); 
			dialog.text = "He, "+GetSexPhrase("Seemann","Süße")+", willst du dein Glück beim Kartenspiel versuchen? Setz dich, die Einsätze sind hier moderat... zumindest für Anfänger.";
			link.l1 = "Ich habe das Gefühl, du bist genau der, den ich suche. So hast du auch Sebastián ins Spiel gelockt, bevor du ihn bis aufs Hemd ausgezogen hast? Ich bin hier, um ihm sein Buch zurückzubringen.";
			link.l1.go = "OZ_Shuler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Shuler_2":
			dialog.text = "Na schön, perfekt. Gib mir hunderttausend, und du kannst es mitnehmen. Für mich hat dieses Buch keinen Wert, ich könnte nicht einmal eine Zange von einem Hammer unterscheiden.";
			link.l1 = "Ich gebe dir fünftausend – genau den Preis, den du selbst festgelegt hast, als du dem Schmied das Buch abgeluchst hast.";
			link.l1.go = "OZ_Shuler_3";
		break;
		
		case "OZ_Shuler_3":
			dialog.text = "Ha! Hältst du mich für einen Idioten? Ich kenne den wahren Wert dieses Buches sehr gut. Hunderttausend, keinen Peso weniger. Oder es geht an die Franzosen – die haben bekanntlich kein Geldproblem.";
			link.l1 = "Glaubst du wirklich, die Behörden werden einfach zusehen, wie du französischen Händen spanische Baupläne übergibst? Der Admiral wird toben, wenn er davon erfährt.";
			link.l1.go = "OZ_Shuler_4";
		break;
		
		case "OZ_Shuler_4":
			dialog.text = "Ach komm schon. Den Behörden ist so ein läppisches Buch völlig egal, die haben genug andere Sorgen. Und der Admiral? Ja, er hasst die Franzosen von ganzem Herzen, aber auf ihn werde ich nicht warten – mit so viel Geld werde ich in jeder Kolonie der Neuen Welt ein gern gesehener Gast sein.";
			link.l1 = "Dann lass uns einen Deal machen. Du bekommst dein Geld, aber nicht sofort. Der Schmied zahlt die Schuld in Raten zurück, und das Buch geht heute noch an ihn zurück – als Pfand auf meine Kapitänsehre. Für dich ändert sich nichts – er wird sowieso zahlen, und du verlierst keinen Peso.";
			link.l1.go = "OZ_Shuler_5";
		break;
		
		case "OZ_Shuler_5":
			dialog.text = "Ich glaube, du hörst mir nicht zu. Ich habe doch klar gesagt – ich brauche das Geld sofort. Nicht in einer Woche, nicht in einem Monat oder wann auch immer der Schmied es zusammenkratzt, sondern jetzt gleich. Ich will so schnell wie möglich von dieser elenden Insel verschwinden. Also: Entweder die gesamte Summe jetzt auf die Hand, oder das Buch geht an die Franzosen, und deine Kapitänsehre kannst du dann dem Admiralsschergen verpfänden.";
			if (sti(pchar.Money) >= 100000 && GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
				link.l1 = "Wie wär’s so: Wir spielen. Meine hunderttausend gegen das Buch. Wenn du gewinnst, verlässt du die Insel als reicher Mann. Wenn du verlierst – nehme ich das Buch mit. Oder spielst du nur gegen Leute, die zum ersten Mal Karten in der Hand haben?";
				link.l1.go = "OZ_Shuler_6";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "OZ_Shuler_6_No_Money";
				AddDialogExitQuestFunction("OZ_GameCards_Fail");
			}
		break;
		
		case "OZ_Shuler_6_No_Money":
			DialogExit();
			Notification_Money(false, 100000, "peso");
			LAi_CharacterDisableDialog(npchar);
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
			Notification_Skill(true, 30, SKILL_SNEAK);
			}
			else
			{
			Notification_Skill(false, 30, SKILL_SNEAK);
			}
		break;
		
		case "OZ_Shuler_6":
			dialog.text = "Ha! Ich muss nicht reich werden – ich bin es schon! Warum sollte ich riskieren, was mir eine Menge Geld einbringt?";
			link.l1 = "Na sowas, der große Javier Castillo hat Angst zu spielen? Und ich dachte, du wärst ein abgebrühter Spieler und kein gewöhnlicher Gauner, der nur von betrunkenen Tölpeln lebt.";
			link.l1.go = "OZ_Shuler_7";
			Notification_Money(true, 100000, "peso");
			Notification_Skill(true, 30, SKILL_SNEAK);
		break;
		
		case "OZ_Shuler_7":
			dialog.text = "Ich habe keine Angst, ich sehe nur keinen Sinn darin, mich an den Tisch zu setzen, wenn ich schon alles habe, was ich brauche.";
			link.l1 = "Ach komm, ich sehe doch, wie es dich in den Fingern juckt, gegen jemanden zu spielen, der nicht zum ersten Mal Karten in der Hand hält. Lass mich raten – du willst so schnell abhauen, weil dir peinlich ist, dass alle schon gemerkt haben, dass du keinen stärkeren Gegner als einen betrunkenen Trottel schlagen kannst?";
			link.l1.go = "OZ_Shuler_8";
		break;
		
		case "OZ_Shuler_8":
			dialog.text = "Wie kannst du es wagen?! Ich habe Leute geschlagen, die sich nie mit dir an einen Tisch setzen würden! Wir hatten schon Pötte, für die man jedem am Tisch ein Schiff und einen unverschämten Kapitän dazu kaufen konnte! Wir spielen. Fünftausend pro Karte, jeder hat hunderttausend, und wer kein Geld mehr hat, verliert. Mal sehen, wer hier wen besiegt.";
			link.l1 = "Weniger reden, mehr Karten austeilen.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards");
		break;
		
		case "OZ_Shuler_Win_1":
			dialog.text = "Verdammt! Das kann nicht sein...";
			link.l1 = "Na, macht es nicht so viel Spaß, wenn mal jemand anderes gewinnt?";
			link.l1.go = "OZ_Shuler_Win_2";
		break;
		
		case "OZ_Shuler_Win_2":
			dialog.text = "Du bist ein Betrüger! Denkst du, ich habe nichts gesehen? Von wegen, dass ich mich von dir übers Ohr hauen lasse! Eher hacke ich dich in Stücke.";
			link.l1 = "Betrüger? Ha-ha! Sieht so aus, als könntest du einfach nicht verlieren, Freundchen. Aber wenn du es so eilig hast, ins Jenseits zu gehen – ich helfe dir gern dabei. Zu den Waffen!";
			link.l1.go = "exit";
			pchar.questTemp.OZ_Draka = true;
			AddDialogExitQuestFunction("OZ_GameCards_Duel");
		break;
		
		case "OZ_Shuler_Lose_1":
			dialog.text = "Ha! Na, "+GetSexPhrase("Kumpel","Süße")+", wie fühlt es sich an, völlig abgezockt zu werden? Man sagt, Frechheit siegt – aber nicht in deinem Fall.";
			link.l1 = "Freu dich nicht zu früh. Du hattest einfach nur Glück.";
			link.l1.go = "OZ_Shuler_Lose_2";
		break;
		
		case "OZ_Shuler_Lose_2":
			dialog.text = "Verlierer sagen das immer. Nun ja, gespielt"+GetSexPhrase("","")+", verloren"+GetSexPhrase("","")+", also nimm’s nicht persönlich. Falls du jemals wieder hunderttausend auftreibst, kannst du dein Glück erneut versuchen... Aber das Ergebnis wird sich wohl kaum ändern...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards_Lose");
			AddLandQuestMark(characterFromId("PortSpein_Tavern"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_1":
			dialog.text = "Guten Tag, "+GetAddress_Form(NPChar)+". Womit verdanke ich Ihren Besuch?";
			link.l1 = "Sei gegrüßt. Ich bin Kapitän "+GetFullName(pchar)+", und ich möchte mit Ihnen über Javier Castillo sprechen.";
			link.l1.go = "OZ_Felip_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_2":
			dialog.text = "Hm... Wenn dieser Gauner auch Ihnen Geld schuldet, dann fürchte ich, müssen Sie sich hinten anstellen. Javier hat sich noch nie mit der Rückzahlung seiner Schulden beeilt. Und selbst wenn er zu Geld kommt, wird er zuerst mich bezahlen – ich habe bereits dafür gesorgt, dass er keine andere Wahl hat.";
			link.l1 = "Zum Glück bin ich nicht sein Gläubiger. Wie viel schuldet er Ihnen denn? Und welche Maßnahmen haben Sie ergriffen?";
			link.l1.go = "OZ_Felip_3";
		break;
		
		case "OZ_Felip_3":
			dialog.text = "Seine gesamte Schuld beträgt hundertfünfzigtausend Pesos. Er hat nur zehntausend zurückgezahlt – offenbar in dem Glauben, es dabei belassen zu können. Doch ich habe ihm schnell klargemacht, dass er sich irrt. Meine Leute haben ihm weitere zwanzigtausend abgepresst. Den Rest muss er innerhalb einer Woche zahlen, und die Frist läuft bald ab. Zum Glück habe ich gehört, dass er bald eine ordentliche Summe für den Verkauf eines Buches erhalten wird.";
			link.l1 = "Glauben Sie wirklich, dass er vorhat, Ihnen das Geld zurückzugeben? Ich denke nicht, dass Sie ernsthaft darauf bauen sollten. Javier macht kein Geheimnis daraus, dass er, sobald er das Geld hat, sofort verschwinden will.";
			link.l1.go = "OZ_Felip_4";
		break;
		
		case "OZ_Felip_4":
			dialog.text = "Das ist mir bekannt, Kapitän. Seien Sie versichert, ich habe bereits dafür gesorgt, dass er nicht fliehen kann, ohne mich zu bezahlen.";
			link.l1 = "Ich sehe, Sie haben die Lage im Griff. Dennoch zeigt die Erfahrung, dass zusätzliche Absicherung nie schadet. Sehen Sie, ich bin sozusagen ein Spezialist"+GetSexPhrase("","in")+" für die Eintreibung von Schulden. Wenn Sie mir erlauben, in Ihrem Namen zu handeln, kann ich Ihnen Ihr Geld zurückholen.";
			link.l1.go = "OZ_Felip_5";
		break;
		
		case "OZ_Felip_5":
			dialog.text = "Leider, Kapitän, hat mich die Rückforderung dieser Schuld schon zu viel gekostet, und ich kann es mir nicht leisten, auch noch Ihre Dienste zu bezahlen...";
			link.l1 = ""+UpperFirst(GetAddress_Form(NPChar))+", darum müssen Sie sich keine Sorgen machen. In dieser Angelegenheit habe ich mein eigenes Interesse, und deshalb werde ich Ihnen unentgeltlich helfen.";
			link.l1.go = "OZ_Felip_6";
		break;
		
		case "OZ_Felip_6":
			dialog.text = "Darf ich erfahren, worin genau Ihr Interesse besteht?";
			link.l1 = "Sagen wir es so: Manche seiner Tricks am Kartentisch kann ich nicht ungestraft lassen.";
			link.l1.go = "OZ_Felip_7";
		break;
		
		case "OZ_Felip_7":
			dialog.text = "Nun, wenn es mich nichts kostet, sehe ich keinen Grund, abzulehnen. Nur eines, Kapitän – bitte gehen Sie nicht zu weit. Wenn dieser Schurke ins Jenseits geht, bevor er die Schuld beglichen hat, habe ich nichts davon.";
			link.l1 = "Keine Sorge, Felipe, ich werde vorsichtig vorgehen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
			AddDialogExitQuestFunction("OZ_Felip_2");
			pchar.questTemp.OZ_Dolg = true;
		break;
		
		case "OZ_Felip_again":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"! Haben Sie es etwa schon so schnell geschafft?";
			link.l1 = "Leider noch nicht. Aber ich arbeite daran.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
		break;
		
		case "OZ_Shuler_11":
			if (CheckAttribute(npchar, "quest.OZ_Shuler_Lose"))
			{
				dialog.text = "Ah, "+GetSexPhrase("Kapitän","Süße")+"-Emporkömmling! Schon wieder du? Willst du noch ein paar tausend verlieren?";
			}
			else
			{
				dialog.text = "Schon wieder du? Ich habe doch klar gesagt: Geld auf den Tisch – oder verschwinde.";
			}
			link.l1 = "Nimm den Ton runter, Javier. Und hol den Geldbeutel raus – ich bin nicht umsonst hier. Du hast doch nicht etwa deine Schuld bei Felipe Alarcón vergessen? Ab jetzt vertrete ich seine Interessen. Also wähl: Entweder du zahlst die Schuld sofort zurück, oder ich suche das Geld in deinen Taschen, nachdem du zu den Ahnen geschickt wurdest.";
			link.l1.go = "OZ_Shuler_12";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Shuler_12":
			dialog.text = "Zum Teufel mit dir! Ich habe gerade ein Geschäft, siehst du das nicht? Komm in ein paar Stunden wieder – dann reden wir.";
			link.l1 = "Scheint, als hättest du mich nicht gehört. Ich habe doch klar"+GetSexPhrase("","") +" gemacht – ich will das Geld jetzt. Nicht in einer Woche, nicht in einem Monat oder wann auch immer du es zusammenscharst, sondern sofort. Hundertzwanzigtausend Pesos, keinen weniger. Das Buch akzeptiere ich als fünftausend.";
			link.l1.go = "OZ_Shuler_13";
		break;
		
		case "OZ_Shuler_13":
			dialog.text = ""+GetSexPhrase("Dreckiger Bastard","Du Miststück")+"! Wenn du glaubst, dass du mich so leicht loswirst – das ist der größte Fehler deines jämmerlichen Lebens.";
			link.l1 = "Das werden wir sehen.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Shuler_Bitva");
		break;
		
		case "OZ_Frantsuz_1":
			//PlaySound("VOICE\Russian\tra_quest_1.wav");
			if (CheckAttribute(pchar, "questTemp.OZ_Draka"))
			{
				dialog.text = "Was für ein Schauspiel... Ich muss gestehen, "+GetAddress_Form(NPChar)+", Sie haben mir Vergnügen bereitet. Sie beherrschen die Klinge meisterhaft. Erlauben Sie, dass ich mich vorstelle – "+GetFullName(npchar)+". Und dieser Unglückliche ist, wie ich vermute, Javier Castillo?";
				link.l1 = "Ganz genau, das ist er. Und ich bin Kapitän "+GetFullName(pchar)+".";
				link.l1.go = "OZ_Frantsuz_1_1";
			}
			else
			{
				dialog.text = "Was für ein Schauspiel... Ich muss gestehen, "+GetAddress_Form(NPChar)+", Sie haben mir Vergnügen bereitet. Sie beherrschen die Klinge meisterhaft. Amüsant, wie sich die Umstände manchmal fügen – das Buch, für das ich eine so lange Reise auf mich genommen habe, hat den Besitzer auf die unerwartetste Weise gewechselt. Aber ich hoffe, ich fahre nicht mit leeren Händen von hier weg.";
				link.l1 = "Hm... Und auf wie viel schätzen Sie dieses Buch?";
				link.l1.go = "OZ_Frantsuz_2";
			}
		break;
		
		case "OZ_Frantsuz_1_1":
			dialog.text = "Sehen Sie, Kapitän, ich habe eine beträchtliche Strecke zurückgelegt wegen eines einzigen Buches... Und anscheinend befindet es sich nun in Ihren Händen. Ich hoffe aufrichtig, dass wir zu einer Einigung kommen – ich möchte diesen Ort nur ungern mit leeren Händen verlassen.";
			link.l1 = "Hm... Und auf wie viel schätzen Sie dieses Buch?";
			link.l1.go = "OZ_Frantsuz_2";
		break;
		
		case "OZ_Frantsuz_2":
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+", ich kenne den Wert wahrhaft seltener Dinge. Achtzigtausend Peso. Eine mehr als großzügige Summe, und glauben Sie mir, Sie werden ein solches Angebot kaum ein zweites Mal bekommen.";
			link.l1 = "Nun, das Buch ist wirklich wertvoll, und ich gebe zu, ich habe nur aus reiner Neugier gefragt. Ich habe nicht vor, mit dem Schicksal eines Menschen zu handeln. Leider, Monsieur, wird es kein Geschäft geben – dieses Buch muss zu seinem Besitzer zurückkehren.";
			link.l1.go = "OZ_Frantsuz_3";
			link.l2 = "Ein lächerlicher Betrag. In diesem Buch sind die Geheimnisse der besten Schmiedemeister gesammelt. Hundertfünfzigtausend Peso – entweder Sie stimmen zu, oder es geht zurück zu seinem Besitzer. Kein Feilschen.";
			link.l2.go = "OZ_Frantsuz_4";
		break;
		
		case "OZ_Frantsuz_3":
			dialog.text = "Bitte, lehnen Sie nicht vorschnell ab. Ich habe einen weiten Weg dafür zurückgelegt. Ich bin bereit, Ihnen hunderttausend zu bieten, ausschließlich als Zeichen des Respekts für die Geschicklichkeit, mit der Sie diesen Mann besiegt haben.";
			link.l1 = "Ich habe alles gesagt. Verzeihen Sie mich, ich muss gehen.";
			link.l1.go = "OZ_Frantsuz_4_1";
		break;
		
		case "OZ_Frantsuz_4_1":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "OZ_Frantsuz_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", ich schätze Ihr Selbstvertrauen, aber hundertfünfzigtausend – das ist kein Preis mehr, das ist absurd. Lassen Sie uns das Geschäft nicht ins Lächerliche ziehen. Hunderttausend Peso ist ein fairer Betrag, stimmen Sie zu, mehr wird Ihnen niemand für dieses Buch geben.";
			link.l1 = "Anscheinend finden wir keine gemeinsame Basis. Nun, ich sehe keinen Sinn, dieses Gespräch fortzusetzen. Auf Wiedersehen, Monsieur.";
			link.l1.go = "OZ_Frantsuz_5";
		break;
		
		case "OZ_Frantsuz_5":
			dialog.text = "Warten Sie! Gut, Sie haben gewonnen. Hundertfünfzigtausend. Einverstanden?";
			link.l1 = "Ich freue mich, dass Sie die richtige Wahl getroffen haben. Das Buch gehört Ihnen. Ich denke, damit werden Sie der beste Meister in der Karibik.";
			link.l1.go = "OZ_Frantsuz_6";
			TakeItemFromCharacter(pchar, "OZ_book");
			AddMoneyToCharacter(pchar, 150000);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterNationReputation(pchar, SPAIN, -10);
			ChangeCharacterReputation(pchar, -5);
		break;
		
		case "OZ_Frantsuz_6":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", selbst ohne dieses Buch war mir niemand ebenbürtig. Aber ich gestehe, es ist angenehm, solch eine seltene Trophäe zu erlangen. Und nun entschuldigen Sie mich bitte – ich kann es kaum erwarten, zu prüfen, ob es wirklich all die Lobpreisungen wert ist, die ich darüber gehört habe.";
			link.l1 = "Nun, dann will ich Sie nicht länger aufhalten. Alles Gute.";
			link.l1.go = "OZ_Frantsuz_7";
		break;
		
		case "OZ_Frantsuz_7":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_2");
		break;
		
		case "OZ_Bandit_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Na, was haben wir denn hier für Gesindel? Dachtet du etwa, du könntest unsere Truhe plündern und dann abhauen? Falsch gedacht, Freundchen. Gleich stopfen wir dich selbst in diese Truhe und nageln den Deckel zu!";
			}
			else
			{
				dialog.text = "Na, na... Wen haben wir denn hier? Hast du dich verlaufen, Kleine? Dachtet du etwa, du könntest die Truhe plündern und leise verschwinden? Falsch gedacht, Liebling. Jetzt durchsuchen wir dich gründlich – mal sehen, was du da in den Taschen hast... und nicht nur dort.";
			}
			link.l1 = "Zu viele Worte für erbärmliche Würmer wie euch. Zieht eure Eisen, und wir werden sehen, was ihr wirklich draufhabt.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Grot_4");
		break;
		
		case "OZ_Felip_11":
			dialog.text = "Kapitän! Man hat mir bereits berichtet, dass Javier durch Ihre Hand ins Jenseits befördert wurde. Und ich habe doch gebeten, ihn nicht vorzeitig zu töten! Ich hoffe, Sie sind hier, um mir mein Geld zurückzugeben?";
			if (sti(pchar.Money) >= 100000)
			{
				link.l1 = "Ganz genau. Ich konnte sein Versteck finden, in dem sich hunderttausend Peso befanden. Das ist alles, was er hatte.";
				link.l1.go = "OZ_Felip_12";
			}
			link.l2 = "Ja, ich musste ihn töten. Aber er hat zuerst angegriffen, und ich musste mich verteidigen. In seinen Taschen war gähnende Leere – kein einziger Maravedí. Leider konnte die Schuld nicht beglichen werden.";
			link.l2.go = "OZ_Felip_14";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.OZ_Dolg");
		break;
		
		case "OZ_Felip_12":
			dialog.text = "Hunderttausend... Sicher, das ist nicht der gesamte Betrag, aber bei Javier bezweifle ich, dass jemand mehr aus ihm hätte herauspressen können. Nun gut, ich danke Ihnen, Kapitän. Offenbar habe ich die falschen Leute angeheuert. Sie sind wirklich ein Meister Ihres Fachs.";
			link.l1 = "Das war nicht schwer. Damit muss ich mich nun leider verabschieden – die Geschäfte warten.";
			link.l1.go = "OZ_Felip_13";
			AddMoneyToCharacter(pchar, -100000);
		break;
		
		case "OZ_Felip_13":
			dialog.text = "Auf Wiedersehen, Kapitän.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_good");
		break;
		
		case "OZ_Felip_14":
			dialog.text = "Du elender Schuft"+GetSexPhrase("","in")+"! Du lügst mir doch direkt ins Gesicht?! Das wirst du mir büßen!";
			link.l1 = "Argh...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_bad");
		break;
		
		case "OZ_Kuznets_Tovar":
			//PlaySound("VOICE\Russian\Master_02.wav");
			//PlaySound("VOICE\Spanish\Master_02.wav");
			dialog.text = "Guten Tag, "+pchar.name+"! Möchten Sie Materialien oder Waren erwerben?";
			link.l1 = ""+TimeGreeting()+". Lassen Sie uns sehen, was Sie im Angebot haben.";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "Guten Tag auch Ihnen, "+npchar.name+"! Danke für das Angebot, aber ich wollte nur kurz grüßen.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
			SetFunctionTimerCondition("OZ_Kuznets_Reset", 0, 0, 1, false);
			if (!CheckAttribute(npchar, "quest.OZ_Kuznets_tovar")) 
			{
				SetFunctionTimerCondition("OZ_Kuznets_Reset_2", 0, 0, 30, false);
				npchar.quest.OZ_Kuznets_tovar = true;
			}
		break;
		
		case "OZ_Kuznets_Tovar_repeat":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", haben Sie sich nun doch entschieden, etwas zu kaufen?";
			link.l1 = "Genau. Zeigen Sie mir, was Sie heute im Angebot haben.";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "Leider muss ich schon wieder gehen.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
		case "OZ_Kuznets_Tovar_2":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
	}
}