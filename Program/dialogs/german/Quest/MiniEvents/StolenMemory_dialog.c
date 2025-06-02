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
			dialog.text = "Was wollt Ihr?";
			link.l1 = "Nichts.";
			link.l1.go = "exit";
		break;

		case "Juli":
			dialog.text = "...";
			if (pchar.sex == "woman")
			{
				link.l1 = "Mademoiselle, man sagt, Port-au-Prince verliert seinen Charme, wenn Ihr nicht lächelt. Heute scheint einer dieser Tage zu sein. Verzeiht meine Offenheit, aber bedrückt Euch etwas?";
			}
			else
			{
				link.l1 = "Mademoiselle, ich habe viel über Eure Schönheit und Anmut gehört – und ich muss sagen, die Gerüchte waren keineswegs übertrieben. Man sagt auch, Port-au-Prince verliert seinen Zauber, wenn Ihr nicht lächelt. Heute scheint, leider, genau so ein Tag zu sein. Nennt mir den Namen des Halunken, der es wagte, Euch den Tag zu verderben, und ich fordere ihn zum Duell, um Euch Euer Lächeln zurückzubringen.";
			}
			link.l1.go = "Juli_2";
			DelLandQuestMark(npchar);
		break;

		case "Juli_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "Ach, Mademoiselle, Ihr seid zu aufmerksam... Ich gestehe, Eure Fürsorge rührt mich. Doch leider ist der Grund meiner Sorge nicht einer, den man mit ein paar Worten zerstreuen könnte. Es ist nicht die Schuld einer Person, sondern Umstände, die selbst der entschlossensten Seele entgleiten.";
				link.l1 = "Umstände? Ich versichere Euch, Mademoiselle, für "+GetFullName(pchar)+" gibt es keine unüberwindbaren Hindernisse. Erzählt mir, was geschehen ist – vielleicht kann ich helfen.";
			}
			else
			{
				dialog.text = "Oh, Monsieur, Ihr seid wahrlich ein Meister schöner Worte. Ich gestehe, Ihr habt mir beinahe ein Lächeln entlockt. Aber leider kann ein Duell mein Problem nicht lösen. Derjenige, der meinen Tag verdunkelte, ist kein Bösewicht, sondern eher ein Umstand, den selbst ein so ehrenwerter Herr wie Ihr nicht ändern kann.";
				link.l1 = "Umstände? Ich versichere Euch, Mademoiselle, Kapitän "+GetFullName(pchar)+" meistert jede Situation! Und sollte ich scheitern, so schwöre ich, den Hut des ersten Passanten zu verspeisen, der mir begegnet!";
			}
			link.l1.go = "Juli_3";
		break;

		case "Juli_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "Wenn Ihr wirklich darauf besteht, werde ich Euch erzählen, was geschehen ist. Doch gebt mir zuerst Euer Wort, dass dieses Gespräch nur zwischen uns bleibt.";
				link.l1 = "Ich gebe Euch mein Ehrenwort, Mademoiselle. Alles, was Ihr mir anvertraut, bleibt unter uns – selbst wenn ich dieses Geheimnis mit auf den Meeresgrund nehmen müsste.";
			}
			else
			{
				dialog.text = "Monsieur "+pchar.lastname+", Ihr versteht es wahrlich, selbst eine tief betrübte Dame aufzuheitern. Doch bitte, verschont die Hüte unschuldiger Passanten. Wenn Ihr wirklich darauf besteht, werde ich Euch erzählen, was geschehen ist. Gebt mir nur Euer Wort, dass meine Worte ein Geheimnis zwischen uns bleiben.";
				link.l1 = "Ich gebe Euch mein Wort, Mademoiselle, dass alles, was Ihr mir sagt, selbst unter Androhung des Todes mein Geheimnis bleibt.";
			}
			link.l1.go = "Juli_4";
		break;
		
		case "Juli_4":
			dialog.text = "Also gut. Vor Kurzem verschwand eine Halskette aus meinem Zimmer... es ist nicht einfach nur ein Schmuckstück. Es war ein Geschenk von jemandem, der einen besonderen Platz in meinem Herzen einnimmt. Jetzt fühlt es sich an, als hätte ich etwas weit Wichtigeres verloren als nur einen Gegenstand\nIch habe lange nachgedacht, wer es gewesen sein könnte, und bin zu einem einzigen Schluss gekommen. Ich fürchte, es war jemand aus meinem Dienstpersonal. Nur sie haben Zugang zu meinem Zimmer – und ein mögliches Interesse an solch einem Diebstahl. Aber ich kann diesen Verdacht nicht offen aussprechen...";
			link.l1 = "Eine heikle Angelegenheit, wenn Ihr keine öffentliche Aufmerksamkeit wollt. Doch wenn ich Euch helfen soll, muss ich wissen, was genau Euch dazu bringt, das Ganze geheim zu halten. Es ist notwendig, damit ich Euch nicht versehentlich verrate. Ich muss wissen, wen – oder was – ich meiden soll.";
			link.l1.go = "Juli_5";
			if (pchar.sex == "woman")
			{
				link.l2 = "Ihr könnt es nicht sagen? Nun, Mademoiselle, dann bleibt mir nur, Euch viel Glück zu wünschen. Heimlichtuerei liegt mir nicht. Euer Problem scheint mir durchaus lösbar – mit Hilfe der Stadtwache. Doch Ihr scheint die Dinge lieber zu verkomplizieren.";
				link.l2.go = "Juli_end";
			}
			else
			{
				link.l2 = "Ihr könnt es nicht sagen? Nun denn, verzeiht mir, Mademoiselle, aber dann bin ich machtlos. Geheimniskrämerei liegt mir nicht. Euer Problem scheint mir erschreckend einfach – ein Fall für die Wache. Aber offenbar zieht Ihr es vor, es zu einem höfischen Drama zu machen.";
				link.l2.go = "Juli_end";
			}
		break;

		case "Juli_end":
			dialog.text = "So geht Ihr also mit schwierigen Umständen um, "+GetFullName(pchar)+"? Man vertraut Euch etwas an – und Ihr wendet Euch ab? Ich hoffe, Ihr findet Aufgaben, die Eurer außerordentlichen Begabung würdiger sind – vielleicht das Zählen von Rumfässern oder das Diskutieren mit Hafenhändlern. Doch behaltet unser Gespräch für Euch, falls noch ein Funken Ehre in Euch ist. Lebt wohl.";
			link.l1 = "...";
			link.l1.go = "Juli_end_2";
		break;

		case "Juli_end_2":
			DialogExit();
			CloseQuestHeader("UV");
			ChangeCharacterComplexReputation(pchar, "nobility", -5);

			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;

		case "Juli_5":
			dialog.text = "Ihr habt recht, "+GetAddress_Form(NPChar)+", Ihr solltet die Wahrheit erfahren. Die Halskette war ein Geschenk von jemandem, den mein Onkel, der Gouverneur des französischen Teils dieser Insel, nicht duldet. Er hat mir strengstens verboten, seinen Namen überhaupt zu erwähnen. Wenn er herausfindet, von wem sie stammt, könnten die Folgen verheerend sein – nicht nur für mich, sondern auch...";
			link.l1 = "Sagt nichts weiter, Madame. Ich weiß nun genug. Ich verspreche Euch, ich werde alles tun, um die Kette zurückzubringen – ohne Euer Geheimnis auch nur im Geringsten zu gefährden.";
			link.l1.go = "Juli_6";
		break;

		case "Juli_6":
			dialog.text = "Ich danke Euch, "+GetSexPhrase("Monsieur "+pchar.lastname+"",""+pchar.name+"")+". Eure Entschlossenheit und Euer Taktgefühl haben mich berührt. Ich bin sicher, dass mein Geheimnis bei Euch in besten Händen ist. Möge Euch das Glück bei dieser schwierigen Aufgabe begleiten.";
			if (pchar.sex == "woman")
			{
				link.l1 = "Glück folgt denen, die handeln, Mademoiselle. Ich werde Eure Kette finden, darauf könnt Ihr Euch verlassen.";
			}
			else
			{
				link.l1 = "Das Glück ist mit den Tapferen, Mademoiselle. Sobald ich die Kette finde, wird sie sofort in Eure zarten Hände zurückkehren.";
			}
			link.l1.go = "Juli_7";
		break;
		
		case "Juli_7":
			DialogExit();
			
			NextDiag.CurrentNode = "Juli_7_again";
			AddQuestRecord("UV", "2");
			AddQuestUserData("UV", "sSex", GetSexPhrase("","а"));
			
			pchar.questTemp.UV_Lavochniki = true;
		break;
		
		case "Juli_7_again":
			if (CheckCharacterItem(PChar, "SM_necklace_Julie"))
			{
				dialog.text = "Ah, Kapitän, Ihr seid es... Habt Ihr es gefunden? Bitte sagt mir, dass das Halsband wieder bei Euch ist.";
				link.l1 = "Eure Sorgen haben ein Ende, Julie. Ich habe das Halsband und es ist mir eine große Freude, es dorthin zurückzubringen, wo es hingehört – in Eure zarten Hände.";
				link.l1.go = "Juli_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Ah, Kapitän, Ihr seid es... Habt Ihr es gefunden? Bitte sagt mir, dass das Halsband wieder bei Euch ist.";
				link.l1 = "Leider noch nicht, Julie. Aber macht Euch keine Sorgen – ich werde alles tun, um es zurückzubringen.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Juli_7_again";
				DelLandQuestMark(npchar);
			}
		break;

		case "Starpom_1":
			dialog.text = "Guten Tag, Monsieur. Was führt Euch auf mein Schiff?";
			link.l1 = "Ich suche Tristan Renier. Ich habe ein einträgliches Geschäft mit ihm zu besprechen.";
			link.l1.go = "Starpom_2_sneak";
			link.l2 = "Ich muss mit Tristan Renier sprechen – es ist eine persönliche Angelegenheit.";
			link.l2.go = "Starpom_2_fortune";
			DelLandQuestMark(npchar);
		break;

		case "Starpom_2_sneak":
			dialog.text = "Der Kapitän ist zurzeit nicht an Bord. Ich denke, Ihr könnt ihn irgendwo in der Stadt finden.";
			link.l1 = "Wisst Ihr vielleicht genauer, wohin er gegangen ist?";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "Starpom_2_fortune":
			dialog.text = "Der Kapitän ist zurzeit nicht an Bord. Ich denke, Ihr könnt ihn irgendwo in der Stadt finden.";
			link.l1 = "Wisst Ihr vielleicht genauer, wohin er gegangen ist?";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Starpom_3":
			dialog.text = "Verzeiht, "+GetAddress_Form(NPChar)+", aber der Kapitän teilt seine Pläne nicht mit mir. Ich weiß nur, dass er an Land gegangen ist.";
			link.l1 = "Nun gut, danke trotzdem.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_GoldSeagull_RasprashivaemZhiteley");
		break;
		
		case "Captain_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Wer zum Teufel seid Ihr? Und mit welchem Recht stürmt Ihr in mein Zimmer ohne Einladung?";
				link.l1 = "Mein Name ist "+GetFullName(pchar)+". Und ich habe ein Anliegen.";
			}
			else
			{
				dialog.text = "Wer seid Ihr denn? Ich kann mich nicht erinnern, Gäste eingeladen zu haben. Obwohl... unerwartete Besuche können mitunter unterhaltsam sein. Womit verdiene ich diese Ehre?";
				link.l1 = "Ich bin Kapitänin "+GetFullName(pchar)+". Und ich komme geschäftlich.";
			}
			link.l1.go = "Captain_2";
			DelLandQuestMark(npchar);
		break;

		case "Captain_2":
			if (pchar.sex == "man")
			{
				dialog.text = "Ein Anliegen, sagt Ihr? Was für ein verdammtes Anliegen soll das sein?";
				link.l1 = "Ein sehr einfaches. Ihr habt ein Halsband, das ich suche.";
			}
			else
			{
				dialog.text = "Geschäftlich, sagt Ihr? Interessant... Und was für ein Geschäft bringt eine so reizende Dame direkt in mein Zimmer?";
				link.l1 = "Entspannt Euch, Monsieur Charmeur, ich bin nur wegen eines Halsbandes hier. Und ich weiß, dass Ihr es habt.";
			}
			link.l1.go = "Captain_3";
		break;

		case "Captain_3":
			if (pchar.sex == "man")
			{
				dialog.text = "Ha! Ein Halsband, ja? Ich habe eins – und was soll’s? Denkt Ihr wirklich, ich gebe es einfach so her?";
			}
			else
			{
				dialog.text = "Ein Halsband, sagt Ihr? Hm... Ja, ich habe eines. Und? Wie genau wollt Ihr es bekommen?";
			}
			if (sti(pchar.Money) >= 5000)
			{
				link.l1 = "Ich bin bereit"+GetSexPhrase("","e")+" Euch fünftausend Pesos anzubieten. Davon könnt Ihr Euch ein ebenso edles Schmuckstück leisten. Doch dieses hier gehört jemandem, dem es wirklich am Herzen liegt.";
				link.l1.go = "Captain_4_commerce";
			}
			link.l2 = "Glaubt mir, Ihr habt nicht viele Optionen: Entweder gebt Ihr es mir freiwillig – oder ich hole es mir von Eurem Leichnam. Entscheidet Euch.";
			link.l2.go = "Captain_4_leadership";
		break;

		case "Captain_4_commerce":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 45)
			{
				dialog.text = "Fünftausend, sagt Ihr? Gut, Kapitän. Nehmt es – wenn es Euch so wichtig ist.";
				link.l1 = "Vielen Dank. Ihr habt die richtige Entscheidung getroffen.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie");
				notification("Test bestanden", SKILL_COMMERCE);
				GiveItem2Character(pchar, "SM_necklace_Julie");
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddMoneyToCharacter(pchar, -5000);
			}
			else
			{
				dialog.text = "Ich habe dieses Halsband nicht gekauft, um mit Leuten wie Euch zu feilschen! Es ist ein Geschenk für meine Frau – Ihr habt hier nichts verloren. Verschwindet, bevor ich Euch hinauswerfen lasse!";
				link.l1 = "Wenn Ihr das Halsband nicht freiwillig hergeben wollt, werde ich es mir mit Gewalt holen.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				notification("Fertigkeit zu niedrig (45)", SKILL_COMMERCE);
			}
		break;
		
		case "Captain_4_commerce":
			if (GetSummonSkillFromName(pchar, SKILL_Commerce) >= 45)
			{
				dialog.text = "Fünftausend, sagt Ihr? Nun gut, Kapitän, Ihr treibt einen überzeugenden Handel. Hier, nehmt das Schmuckstück, wenn es so viel bedeutet.";
				link.l1 = "Eure Weisheit entspricht Eurer Großzügigkeit, mein Herr. Diese Entscheidung wird nicht bereut werden.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie");
				notification("Überprüfung bestanden", SKILL_COMMERCE);
				GiveItem2Character(pchar, "SM_necklace_Julie");
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddMoneyToCharacter(pchar, -5000);
			}
			else
			{
				dialog.text = "Ich habe diese Halskette nicht erworben, um sie an den ersten Vagabunden zu verhökern, der mit Münzen raschelt! Sie ist als Geschenk für meine Frau gedacht, und ich werde nichts mehr zu diesem Thema hören. Entfernt Euch aus meiner Gegenwart, bevor ich Männer rufe, um Euch hinauszubegleiten!";
				link.l1 = "Wenn Ihr eine Übereinkunft unter Ehrenmännern ablehnt, dann werde ich das, was ich suche, mit weniger zivilisierten Mitteln beanspruchen.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				notification("Fähigkeit nicht ausreichend (45)", SKILL_COMMERCE);
			}
		break;
		
		case "Captain_4_leadership":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 45)
			{
				dialog.text = "Argh... Frecher Bastard... Glaubst du wirklich, ich fürchte mich vor deinen lächerlichen Drohungen? Ha! Du hast keine Ahnung, mit wem du dich angelegt hast!";
				link.l1 = "Es ist mir egal, wer du bist. Gib mir einfach das Halsband, und ich gehe. Oder bist du wirklich bereit, für ein Schmuckstück zu sterben, das dir nicht mehr bedeutet als irgendein billiger Kram?";
				link.l1.go = "Captain_4_leadership_2";
				notification("Test bestanden", SKILL_Leadership);
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "Ich habe dieses Halsband nicht gekauft, um mit jemandem wie dir zu feilschen! Es ist ein Geschenk für meine Frau – und du hast hier nichts verloren. Verschwinde, bevor wir dich hinauswerfen!";
				link.l1 = "Wenn du das Halsband nicht freiwillig hergeben willst, werde ich es mir mit Gewalt holen.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				notification("Fertigkeit zu niedrig (45)", SKILL_Leadership);
			}
		break;

		case "Captain_4_leadership_2":
			dialog.text = "Zum Teufel mit dir und dieser verfluchten Halskette! Nimm sie. Nimm sie und verschwinde, bevor ich es mir anders überlege.";
			link.l1 = "Eine weise Entscheidung! Lebt wohl.";
			AddDialogExitQuestFunction("UV_Ozherelie");
			GiveItem2Character(pchar, "SM_necklace_Julie");
		break;

		case "Juli_22":
			dialog.text = ""+pchar.name+", ihr habt mir erneut Freude ins Herz gebracht! Ihr habt nicht nur das Collier zurückgebracht, sondern auch ein Stück meiner Seele. Eure Edelmut ist bewundernswert, und ich verspreche, dass jeder, den ich treffe, von eurer Tapferkeit erfahren wird!";
			link.l1 = "Aber bitte, Mademoiselle, ich habe es nicht für Ruhm getan. Euer Lächeln ist die einzige Belohnung, die mir wirklich etwas bedeutet.";
			link.l1.go = "Juli_23";
			TakeItemFromCharacter(pchar, "SM_necklace_Julie");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;

		case "Juli_23":
			dialog.text = "Ihr seid so bescheiden, "+pchar.name+". Aber bitte, nehmt diese Truhe mit Dublonen an. Nur wenn ich weiß, dass ihr mein Geschenk akzeptiert habt, kann ich sicher sein, euch auf angemessene Weise gedankt zu haben.";
			link.l1 = "Ich bitte euch, Mademoiselle, besteht nicht darauf. Euer Wort des Dankes bedeutet mir mehr als jede Truhe voller Dublonen.";
			link.l1.go = "Juli_24_nobility";
			link.l2 = "Wenn es euch beruhigt, Mademoiselle, nehme ich euer Geschenk an. Aber glaubt mir, ich habe das nicht für eine Belohnung getan. "+GetSexPhrase("Eure Anerkennung","Euer Dank")+" bedeutet mir weitaus mehr als diese Dublonen.";
			link.l2.go = "Juli_24_chest";
		break;

		case "Juli_24_nobility":
			dialog.text = "Ich habe ganz vergessen zu fragen: Wisst ihr, wer die Halskette gestohlen hat?";
			link.l1 = "Ich weiß nur eines, Mademoiselle: Offenbar hat eine gewisse Giselle dem Händler das Collier gebracht. Und es scheint nicht das letzte Schmuckstück zu sein, das sie zu verkaufen gedenkt.";
			link.l1.go = "Juli_25";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;

		case "Juli_24_chest":
			dialog.text = "Ich habe ganz vergessen zu fragen: Wisst ihr, wer die Halskette gestohlen hat?";
			link.l1 = "Ich weiß nur eines, Mademoiselle: Offenbar hat eine gewisse Giselle dem Händler das Collier gebracht. Und es scheint nicht das letzte Schmuckstück zu sein, das sie zu verkaufen gedenkt.";
			link.l1.go = "Juli_25";
			GiveItem2Character(PChar, "chest");
		break;

		case "Juli_25":
			dialog.text = "Giselle? Das ist doch meine Zofe! Ich hatte sie im Verdacht... aber ich wollte es nicht glauben. Das Schlimmste ist, dass ich sie kaum bestrafen kann. Sie könnte mein Geheimnis verraten, und das darf ich nicht zulassen.";
			link.l1 = "Und was gedenkt ihr zu tun? Ihr alles durchgehen lassen und sie weiterhin bestehlen lassen?";
			link.l1.go = "Juli_26";
		break;

		case "Juli_26":
			dialog.text = "Oh nein, das bestimmt nicht. Zuerst werde ich dafür sorgen, dass sie nicht länger in meiner Nähe ist. Dann überlege ich mir eine Strafe, die nicht nach mir aussieht.";
			link.l1 = "Weibliche Raffinesse ist eine gefährliche Waffe, besonders in den Händen einer so feinsinnigen und klugen Dame. Ich bin mir sicher"+GetSexPhrase("","e")+", eure Zofe ahnt nicht einmal, dass das Spiel bereits verloren ist – und nicht zu ihren Gunsten.";
			link.l1.go = "Juli_27";
		break;
		
		case "Juli_27":
			dialog.text = "Ach, Kapitän, natürlich möchte ich nicht auf Tricksereien zurückgreifen, aber... manchmal ist List der einzige sichere Weg.";
			link.l1 = "Zweifellos, Julie. Ich würde euch nur ungern verlassen, aber leider ruft die Pflicht. Wer, wenn nicht ich, sollte sich um meine Matrosen kümmern?";
			link.l1.go = "Juli_28";
		break;

		case "Juli_28":
			dialog.text = "Auf Wiedersehen, "+pchar.name+". Bitte besucht unseren Hafen öfter. Unsere Stadt vermisst "+GetSexPhrase("so edle und tapfere Männer wie euch.","junge Frauen mit einem so edlen Herzen und entschlossenen Geist wie euch.")+"";
			link.l1 = "Ihr schmeichelt mir, Mademoiselle. Ich verspreche, keine Gelegenheit zu versäumen, eure wundervolle Stadt erneut zu besuchen. Bis bald.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_Juli_GoodEnd");
		break;

		case "Juli_31":	
			if (CheckAttribute(pchar, "questTemp.UV_ojerelie_Julie"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = ""+pchar.name+"! Welch unerwartete Begegnung! Immer noch auf hoher See unterwegs?";
						link.l1 = "Ich freue mich, euch zu sehen, Mademoiselle. Ich bezwinge die Meere, so gut ich kann, auch wenn sie wie immer unbarmherzig launisch sind. Und ihr, genießt ihr die Ruhe?";
						link.l1.go = "Juli_32";
					break;

					case 1:
						dialog.text = "Ach, Kapitän "+pchar.lastname+", wie sehr ich mich freue, euch zu sehen! Ich hoffe, es geht euch gut?";
						link.l1 = "Ich freue mich ebenfalls, euch zu sehen, Mademoiselle. Die Arbeit verlangt wie immer Zeit und Mühe, aber solche Begegnungen verschönern jeden Tag. Und wie verläuft euer Leben?";
						link.l1.go = "Juli_33";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Kapitän "+pchar.lastname+", schon wieder hier? Gibt es etwa noch jemanden in unserer kleinen Stadt, den ihr nicht für ein paar Goldstücke verraten habt?";
						link.l1 = "Mademoiselle, ich verstehe eure Gefühle, aber ich habe so gehandelt, wie ich es für richtig hielt. Manchmal tun richtige Entscheidungen weh, und es tut mir leid, dass es euch getroffen hat.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;

					case 1:
						dialog.text = "Kapitän "+pchar.lastname+", wieder ihr? Ist eure Gier so groß, dass ihr unsere Stadt nicht in Ruhe lassen könnt und schon nach dem nächsten Opfer sucht?";
						link.l1 = "Mademoiselle, es tut mir leid, dass meine Handlungen euch verletzt haben, aber ich habe so gehandelt, wie ich es für nötig hielt.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;
				}
			}
			SetTimerFunction("UV_Julie_HelloAgain", 0, 0, 1);
		break;
		
		case "Juli_32":	
			dialog.text = "In letzter Zeit ist wirklich alles ruhig und friedlich, nichts stört diese Idylle. Besucht unseren Hafen öfter, Kapitän. Ich bin sicher, dass ihr sowohl in unserem Laden als auch außerhalb alles finden werdet, was ihr euch nur wünschen könnt.";
			link.l1 = "Vielen Dank, Mademoiselle. Ich werde versuchen, öfter vorbeizuschauen. Ich bin mir sicher"+GetSexPhrase("","e")+", eure Stadt wird mich noch oft angenehm überraschen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;

		case "Juli_33":	
			dialog.text = "Dank euch, Kapitän, sind sie viel ruhiger geworden. Ich hoffe, ihr werdet uns noch viele Male mit eurer Anwesenheit erfreuen.";
			link.l1 = "Natürlich, Mademoiselle. Eure Stadt hinterlässt immer nur die angenehmsten Eindrücke. Bis bald.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;

		case "Juli_repeat_residence_1":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Kapitän "+pchar.lastname+", wir begegnen uns wieder. Überraschend, nicht wahr?";
					link.l1 = "Das Schicksal scheint uns heute wohlgesonnen zu sein, Mademoiselle.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;

				case 1:
					dialog.text = "Kapitän "+pchar.lastname+", es scheint, unsere Wege haben sich heute erneut gekreuzt.";
					link.l1 = "Ganz so scheint es, Mademoiselle. Ich freue mich"+GetSexPhrase("","e")+" euch wiederzusehen.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;
			}
		break;

		case "Juli_34_zlaya":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Es scheint, wir treffen uns zu oft, Kapitän. Oder könnt ihr einfach nicht die Finger lassen von denen, die ihr schon verraten habt?";
					link.l1 = "Mademoiselle, unsere Begegnungen sind zufällig, aber ich verstehe euren Groll. Ich hoffe nur, dass ihr eines Tages meine Beweggründe verstehen werdet.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;

				case 1:
					dialog.text = "Was wollt ihr noch? Es ist kaum zu glauben, dass dieses Treffen reiner Zufall ist. Oder wolltet ihr mich doch nur an eure Niederträchtigkeit erinnern?";
					link.l1 = "Mademoiselle, ich habe nicht die Absicht, mich euch aufzudrängen oder euch an die Vergangenheit zu erinnern. Dieses Treffen ist wirklich zufällig.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;
			}
		break;
		
		
		
		
	}
}