// Фадей Московит
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie"))
			{
				if (pchar.questTemp.Sharlie == "fadey")
				{
					dialog.text = "Was kann ich für Sie tun, Monsieur? Ich spreche nicht mit Leuten, die ich nicht kenne. Wenn Sie vorbeigekommen sind, um zu plaudern oder zu fragen, zu welcher Zeit des Monats der spanische Silberzug 1640 in Maricaibo ankommt, dann muss ich Sie enttäuschen. Ich verschwende meine Zeit nicht mit leerem Gerede.";
					link.l1 = "Guten Nachmittag, Monsieur Fadey. Sie kennen mich vielleicht noch nicht, aber Sie kennen meinen Bruder. Darf ich mich vorstellen - Charles de Maure, der Bruder von Michel de Monper.";
					link.l1.go = "Sharlie";
					break;
				}
				if (pchar.questTemp.Sharlie == "takeknife" && !CheckAttribute(pchar, "questTemp.Persian"))
				{
					dialog.text = "Ach, du schon wieder Charles! Kak dela? Was ist diesmal los?";
					link.l1 = "Du hast gesagt, dass man dich ausgeraubt hat... Hast du die Schuldigen gefunden?";
					link.l1.go = "Sharlie_8";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "fadey")
				{
					dialog.text = "So Charles, hast du mit diesem Wilden gesprochen?";
					link.l1 = "Ich habe... Deshalb bin ich zu dir zurückgekommen.";
					link.l1.go = "Tichingitu";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "dublon")
				{
					dialog.text = "Ach, du bist es wieder, mein lieber Freund! Nun, hast du das Lösegeld in Dublonen für den Indianer gebracht?";
					if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu80"))
					{
						if (PCharDublonsTotal() >= 80) // belamour legendary edition
						{
							link.l1 = "Ja. Hier sind deine 80 Dublonen.";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "Nein, ich habe noch nicht genug gesammelt.";
							link.l1.go = "exit";
						}
					}
					else
					{
						if (PCharDublonsTotal() >= 100) // belamour legendary edition
						{
							link.l1 = "Ja. Hier sind deine hundert Dublonen.";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "Nein, ich habe noch nicht genug gesammelt.";
							link.l1.go = "exit";
						}
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "begin")
				{
					dialog.text = "Ha, nun, es ist Monsieur de Maure selbst! Ich sagte komm rein, steh nicht da! Was hat dich zu meinem Dom gebracht?";
					link.l1 = TimeGreeting()+", Fadey, mein Bruder hat mir gesagt, ich solle dich sehen. Er sagte, du würdest mir helfen, Arbeit zu finden.";
					link.l1.go = "trial";
					// опоздал
					if (CheckAttribute(pchar, "questTemp.Trial.late")) {
						link.l1.go = "trial_late";
					}
					break;
				}
				if (pchar.questTemp.Sharlie == "trial" && !CheckAttribute(npchar, "quest.vodka"))
				{
					dialog.text = "Ha, du bist es! Was bringt Sie hierher, Monsieur de Maure?";
					link.l1 = TimeGreeting()+", Fadey. Mein Bruder bestand darauf, dass ich nicht mit dir darüber sprechen sollte, aber ich konnte mich nicht fernhalten... ";
					link.l1.go = "vodka";
					break;
				}
				// belamour legendary edition пиратская линейка -->
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "Baster")
				{
					dialog.text = "Ach, alter Freund! Komm rein, komm rein, "+pchar.name+"! Wie geht es dir?";
					link.l1 = TimeGreeting()+", Fadey. Schön, dich zu sehen. Eigentlich habe ich wichtige Geschäfte zu besprechen. Schwarzes Gold.";
					link.l1.go = "Slaves";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "FindGold")
				{
					dialog.text = "Ach, du bist es wieder, mein lieber Freund! Hast du die Beute bekommen? Hast du genug Dublonen gefunden?";
					if(PCharDublonsTotal() >= 150)
					{
						link.l1 = "Da, Monsieur Fadey! Hier ist Ihr Gold.";
						link.l1.go = "Slaves_2";
					}
					else
					{
						link.l1 = "Nein, ich bin nur vorbeigekommen. Ich suche immer noch nach der richtigen Menge.";
						link.l1.go = "exit";
					}
					
					link.l2 = "Fadey, mir ist gerade eine Idee gekommen. Ich brauche die Sklaven nicht mehr. Du musst mir verzeihen, wir sehen uns später!";
					link.l2.go = "Slaves_3";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Baster")
				{
					dialog.text = "Ach, mein alter Freund! Komm rein, komm rein, "+pchar.name+"! Wie geht es dir?";
					if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
					{
						if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
						{
							link.l1 = TimeGreeting()+", Ich brauche wieder deine Hilfe.";
						}
					}
					else
					{
						link.l1 = TimeGreeting()+", Fadey. Schön dich zu sehen. Ich habe Geschäfte mit dir.";
					}
					link.l1.go = "pistols";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "Ach, du bist es wieder, mein lieber Freund! Nun, hast du das Geld gefunden?";
					if(PCharDublonsTotal() >= 300)
					{
						link.l1 = "Ich habe, Monsieur Fadey! Hier sind Ihre 300 Dublonen.";
						link.l1.go = "pistols_4D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "Ich habe, Herr Fadey! Hier sind Ihre 40.000 Pesos.";
						link.l2.go = "pistols_4P";
					}
					if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) 
					{
						link.l3 = "Nein, nur zu Besuch. Ich suche immer noch nach der richtigen Menge.";
						link.l3.go = "exit";
					}
					link.l4 = "Entschuldigung, Fadey, aber ich kann es mir nicht leisten. Ich werde versuchen, alleine klarzukommen. Bis dann!";
					link.l4.go = "pistols_x";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Today")
				{
					dialog.text = "Komm rein, komm rein, "+pchar.name+"! Ich kann in deinen Augen sehen, dass du von meinem Erfolg hören möchtest.";
					link.l1 = "Genau, Fadey. Ich vertraue darauf, dass du hast, was ich will.";
					link.l1.go = "pistols_5";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "Ach, du bist es wieder, mein lieber Freund! Also, hast du das Geld gefunden?";
					if(PCharDublonsTotal() >= 300)
					{
						link.l1 = "Nimm 300 Dublonen. Ich werde die Matrosen bitten, diese Kiste zu meinem Schiff zu bringen. Oh, was würde ich ohne dich, Fadey, tun?! Du hast keine Ahnung, wie sehr du mir geholfen hast!";
						link.l1.go = "pistols_5D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "Nimm 40.000 Pesos. Ich werde die Matrosen bitten, diese Kiste auf mein Schiff zu bringen. Oh, was würde ich ohne dich Fadey machen?! Du hast keine Ahnung, wie sehr du mir geholfen hast!";
						link.l2.go = "pistols_5P";
					}
					if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) // возможность найти без отказа
					{
						link.l3 = "Nein, bin nur vorbeigekommen. Ich versuche immer noch genug zu sammeln.";
						link.l3.go = "exit";
					}
					link.l4 = "Entschuldige, Fadey, ich bin pleite. Behalte die Anzahlung, ich hoffe, sie wird ausreichen, um deine Ausgaben für diesen Deal zu decken, und ich werde versuchen, alleine klarzukommen. Auf Wiedersehen!";
					link.l4.go = "pistols_x";
					break;
				}
				// <-- legendary edition
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "seek")
				{
					dialog.text = "Ach, Markierter - ich meine "+pchar.name+"! Los, erzähl mir, was du für mich hast!";
					link.l1 = TimeGreeting()+", Fadey. Freut mich, dich zu sehen. Ich bin gekommen, um mit dir über Geschäfte zu sprechen.";
					link.l1.go = "guardoftruth";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "find" && !CheckAttribute(npchar, "quest.utensil"))
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". Ich wette, du bist begierig darauf, die Ergebnisse meines herzzerreißenden Gesprächs mit dem Priester zu entdecken.";
					link.l1 = "Natürlich bin ich das! Wie ist es gelaufen?";
					link.l1.go = "guardoftruth_9";
					break;
				}
				if (CheckAttribute(npchar, "quest.utensil") && PCharDublonsTotal() >= 250)
				{
					dialog.text = "Ach verzeih mir, ich bin so abgelenkt vom Klimpern in deinen Taschen!";
					link.l1 = "Solche Habgier, Fadey! Hier ist dein Gold.";
					link.l1.go = "guardoftruth_11";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "guadeloupe")
				{
					dialog.text = "Aha, mein alter Freund! Komm rein, komm rein, "+pchar.name+"! Also, hast du etwas Neues?";
					link.l1 = "Hallo, Fadey. Ich bitte dich erneut um deine Unterstützung.";
					link.l1.go = "guardoftruth_14";
					break;
				}
				dialog.text = "Was bist du? Eine Statue? Wenn du etwas hast, dann spuck' die Bohnen aus, wenn nicht, mach' dich vom Acker, "+pchar.name+"!";
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "start" && CheckNCountPersian() > 0)
				{// персидские клинки
					link.l2 = "Werf einen Blick darauf, Fadey. Ich vermute, das ist ein persischer Shamshir, möglicherweise einer von denen, die aus deiner Sammlung gestohlen wurden?";
					link.l2.go = "persian";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "one" && CheckNCountPersian() > 0)
				{
					link.l2 = "Ich habe gute Nachrichten für dich. Ich habe hier noch ein persisches Shamshir für dich.";
					link.l2.go = "persian_6";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "two" && CheckNCountPersian() > 0)
				{
					link.l2 = "Ich habe ein drittes persisches Shamshir. Genau wie du es verlangt hast, habe ich es so schnell wie möglich zurückgebracht.";
					link.l2.go = "persian_9";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "cirass")
				{
					link.l2 = "Ich bin hier wegen der leichten Rüstung, die wir besprochen haben.";
					link.l2.go = "persian_13";
				}
				if(CheckAttribute(npchar, "quest.ropes") && GetDataDay() == 20) // торговля канатами
				{
					link.l3 = "Fadey, ich möchte etwas von deinem berühmten Seil kaufen.";
					link.l3.go = "ropes";
				}
				link.l1 = "Fadey, ich brauche deine Hilfe.";
				link.l1.go = "help";
 				link.l9 = "Nein, im Moment nichts.";
				link.l9.go = "exit";
			}
			else
			{
				dialog.text = "Was kann ich für Sie tun, Monsieur? Ich spreche nicht mit Leuten, die ich nicht kenne.";
				link.l1 = "Oh, ich bin nur vorbeigekommen, um zu sehen, wer hier wohnt.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
			dialog.text = "Ach, also bist du der kleine Bruder vom guten alten Michel! Das ändert die Situation! Komm rein, komm rein, Monsieur, nimm Platz. Möchtest du auf unser Treffen einen Wodka erheben? Ich habe noch ein paar Flaschen übrig und es wäre mir eine Freude, eine davon mit dem Bruder eines guten Freundes zu teilen, da!";
			link.l1 = "Verzeihen Sie mir, Monsieur Fadey, aber Trinken steht heute Abend nicht auf dem Programm. Ich würde es vorziehen, direkt zum Geschäft zu kommen.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Was redet ihr da! Dieser lokale Rum ist im Vergleich zum russischen Wodka schwach wie Pisse! Ihr wisst nicht, was ihr verpasst, möge mich das Meer nehmen, wenn ich lüge! Gut, dann zum Geschäft. Ich bin ganz Ohr, Charles.";
			link.l1 = "Herr, ich befürchte, dass das, was ich Ihnen gleich sagen werde, ziemlich unangenehm sein wird, aber leider bin ich aus Pflicht dazu gezwungen! Michel hat mir erzählt, dass Sie ihm durch das Glücksspiel mit ihm einiges an Geld schulden. Er hat auch darauf bestanden, dass Sie das Geld mir übergeben, da mein Bruder momentan... nicht in der Lage ist, Sie persönlich zu besuchen.";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Oh, junger Mann! Natürlich erinnere ich mich an alles und ich gebe zu, dass ich deinem Bruder etwas schulde. Eine Spielschuld ist heilig, diese Pflicht zu ehren ist das einzige, was uns vor tödlicher Anarchie und gefährlichen Banditen bewahrt! Aber ich flehe dich an, bitte verstehe meine Situation! Mir ist kürzlich eine unangenehme Geschichte passiert - ich wurde auf die unverschämteste Weise ausgeraubt!\nVerdammte Diebe haben alles mitgenommen, was sie konnten, alles, was ich in Jahren der Arbeit verdient hatte, mein Geld und meine unbezahlbare Sammlung! Ich kann die Schuld einfach nicht begleichen, nein\nAber, Monsieur de Maure, ich gebe meine Verpflichtungen nicht auf! Ich bitte dich nur, mir entgegenzukommen. Da ich sowieso kein Geld habe, biete ich dir diesen ausgezeichneten, seltenen Dolch an. Schau mal!\nDas ist ein echtes Meisterwerk aus Stahl, der Stolz meiner gestohlenen Sammlung. Außerdem wurde es von indischen Schamanen verzaubert und hat starke verborgene Kräfte! Die Indianer nannten es die Klaue des Häuptlings\nIch hätte nie zugestimmt, es wegzugeben, weil ich eine große Summe für den Dolch bezahlt habe, viel mehr als meine Schuld, aber angesichts der Umstände und meiner Beziehung zu deinem großen Bruder, bin ich bereit, es dir zu geben. Nimm, es ist ein sehr guter Deal!";
			link.l1 = "Ich würde das Geld wirklich einem Messer vorziehen...";
			link.l1.go = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			dialog.text = "Aber ich habe das Geld nicht und ich habe dieses seltene verzauberte Artefakt! Glaubst du wirklich, mein Freund, dass ich dir unter anderen Umständen dieses großartige magische Dolch anbieten würde anstelle von einigen wertlosen Silbermünzen? Pesos kann man überall finden, sogar auf der Straße liegend! Du musst zugeben, ich stecke hier in einer Zwickmühle. Mein Herz blutet, wenn ich nur daran denke, mich von diesem unglaublichen Kunstwerk zu trennen, aber eine Spielschuld ist eine Ehrenschuld, also bin ich bereit, es nur dir zu geben, obwohl es mir sehr lieb ist, weil du ein wahrer Ehrenmann und ein wahrer Freund bist.";
			link.l1 = "Gut, da du schwörst, dass du kein Geld hast, nehme ich diesen magischen Dolch von dir. Hoffentlich kann ich ihn zu einem guten Preis verkaufen...";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "'Verkaufen'!? Verzieh dich stal-ich meine Charles! Nein, ich kann meinen Ohren kaum trauen! Ich gebe meinen wertvollsten Besitz weg, für den ich in Europa mindestens zehn Mal mehr bekommen würde, und du stehst da unverschämt und sagst, du würdest ihn einfach versetzen!? Dieser Dolch, junger Mann, hat einem Mann das Leben gerettet! Lass mich dir erzählen-";
			link.l1 = "Und welche verborgene Kraft meinten Sie?";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "Oh, ho ho! Nun Charles, ich bin ein guter Christ, du weißt, nicht irgendein indischer Schamane. Ich habe keine Möglichkeit, alle verborgenen Eigenschaften dieser Klinge zu kennen. Aber sie existieren, oh ja! Halte diesen Dolch in deiner Hand und du wirst die Kraft darin selbst spüren! Nimm es, nimm es! Wie wäre es damit! Fühlst du etwas?";
			link.l1 = "Hm... Ich fühle nichts. Obwohl es gut in meiner Hand liegt.";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "Aha! Da haben Sie es! Aber das ist nur die kleinste seiner Eigenschaften. Wenn Sie diesen Dolch im Kampf führen, bin ich sicher, wird er seine Macht auf viele dramatische Weisen zeigen! Nun, nehmen Sie es?";
			link.l1 = "Nun, habe ich eine Wahl? Ich nehme es, da du kein Geld hast...";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			GiveItem2Character(pchar, "knife_01");
			PlaySound("interface\important_item.wav");
			//Log_Info("You've received the Chief's Claw'");
			sld = ItemsFromID("knife_01");
			sld.Weight = 1.5;
			sld.price = 0;
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddMapQuestMarkCity("FortFrance", false);
			dialog.text = "Danke, Charles. Du wirst es nicht bereuen, oh das wirst du ganz sicher nicht! Hier, nimm das. Und grüße Michel von mir! Sag ihm, er soll vorbeikommen, sobald er die Chance bekommt.";
			link.l1 = "Oh, ich werde es ihm sagen...";
			link.l1.go = "exit";
			link.l2 = "Du hast gesagt, dass du ausgeraubt wurdest... Hast du die Täter gefunden?";
			link.l2.go = "Sharlie_8";
			pchar.questTemp.Sharlie = "takeknife";
			AddQuestRecord("Sharlie", "18-1");
			sld = characterFromId("Mishelle");	
			sld.greeting = "mishelle_2";
			
			// Sinistra - Старт квеста "Деньги на деревьях"
			PChar.quest.MOT_BarbieSpawn.win_condition.l1 = "location";
			PChar.quest.MOT_BarbieSpawn.win_condition.l1.location = "BasTer_town";
			PChar.quest.MOT_BarbieSpawn.win_condition = "MOT_BarbieSpawn";
			//убрать запрет боёвок на Мартинике
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_townhall")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_prison")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_fort")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ammo")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload2", false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload3", false);
			sld = &Locations[FindLocation("FortFrance_prison")];
			sld.locators_radius.item.detector1 = 0.5;
		break;
		
		case "Sharlie_8":
			dialog.text = "Das Problem ist, ich habe nicht. Diese Rüpel haben das ganze Haus leer geräumt, sind mit allem Silber, Gold, meinen Ersparnissen von Jahren harter Arbeit davongelaufen. Das stört mich normalerweise nicht, denn ein echter Gentleman, auch wenn er alles verliert, was er besitzt, darf keine Emotionen zeigen! Geld muss einem Gentleman so weit unterlegen sein, dass es kaum der Mühe wert ist, sich darüber zu ärgern. Aber das Schlimmste ist, sie haben meine prächtige Sammlung persischer Shamshirs aufgeschnappt! Es gibt keine solche Sammlung in der Neuen oder Alten Welt. Wirklich bemerkenswerte persische Kavallerieschwerter...";
			link.l1 = "Persische Schwerter, sagst du? Klingt ziemlich interessant. Also, du bist ein Sammler, dann?";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "Nun, ich sammle gerne seltene Dinge... Hör zu, Charles, vielleicht könntest du mir in dieser Angelegenheit helfen...";
			link.l1 = "Hilfe? Aber wie? Du meinst, indem ich die Diebe fange?";
			link.l1.go = "Sharlie_10";
		break;
		
		case "Sharlie_10":
			dialog.text = "Nein. Die Diebe interessieren mich nicht besonders. Ich möchte meine persischen Kavallerieschwerter zurück. Wenn du sie findest, werde ich es dir definitiv wert machen, das verspreche ich.";
			link.l1 = "Hm. Aber wo soll ich sie überhaupt suchen? Rund um die Karibik? Oder vielleicht auf der ganzen Welt?";
			link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "Nun, vielleicht wirst du sie auf den Inseln bei einigen Straßenhändlern erblicken, diese Schurken können den Wert dieser Kavallerieschwerter nicht einmal begreifen und sie werden sie sicherlich für Schrott verkaufen. Also, wenn du die persischen Schwerter irgendwo siehst, bring sie zu mir. Wirst du sie erkennen können?";
			link.l1 = "Ich glaube, das werde ich tun. Also gut, ich werde die Augen offen halten und wenn ich ungewöhnliche Klingen sehe, die der Beschreibung entsprechen, werde ich sie definitiv zu dir bringen.";
			link.l1.go = "Sharlie_12";
			link.l2 = "Weißt du, ich bin kein Experte für feine Waffen. Ich fürchte, ich kann dir nicht helfen. Es wäre unehrlich von mir, dir falsche Hoffnungen zu machen.";
			link.l2.go = "Sharlie_13";
		break;
		
		case "Sharlie_12":
			dialog.text = "Gut! Ich hoffe, Sie haben Glück und finden diese Artefakte, und ich werde es Ihnen danken. Gute Jagd, Stalker - ich meine, Kapitän! Ja, Charles, können Sie sich vorstellen, ich hatte vor kurzem einen weiteren Raubversuch!\nEin Dieb versuchte vor ein paar Tagen in mein Haus einzubrechen.\nDas war einfach zu viel für mich! Dieses Mal konnte er mir jedoch nicht entkommen, ich schaffte es, ihn zu fangen, verpasste ihm eine ordentliche Tracht Prügel und übergab ihn den Wachen im Gefängnis der Stadt. Ich hoffe, sie hängen ihn bald auf!";
			link.l1 = "Glaubst du, er gehört zu den Dieben, die deine Shamshirs geklaut haben?";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "start";
			// --> скимитар 021012
			pchar.questTemp.Persian.skimitar = "true";
			pchar.quest.Persian.win_condition.l1 = "item";
			pchar.quest.Persian.win_condition.l1.item = "blade_23";
			pchar.quest.Persian.function = "Persian_FindSkimitar";
		break;
		
		case "Sharlie_13":
			dialog.text = "Schade, aber es hat keinen Sinn, nach dem Mond zu weinen. Da, Charles, kannst du dir vorstellen, ich hatte erst kürzlich einen weiteren Raubversuch!\nEin Dieb versuchte vor ein paar Tagen, in mein Haus zu kommen\nDas war einfach zu viel für mich! Er entkam mir jedoch nicht: Ich schaffte es, ihn zu fangen, gab ihm eine gute Tracht Prügel und schickte ihn ins örtliche Gefängnis. Man kann nicht auf Kosten der Unglücklichkeit eines anderen glücklich sein. Ich hoffe, sie hängen ihn bald!";
			link.l1 = "Glaubst du, er gehört zu den Dieben, die deine Shamshirs geklaut haben?";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "end";
		break;
		
		case "Sharlie_14":
			dialog.text = "Nein, das glaube ich nicht. Er war hinter Geld her. Erwischt ihn in meinem Zimmer, wie er meine Truhen durchwühlt\nEin Indianer aus irgendeinem tiefen Dschungel auf der Spanischen Hauptstraße. Er sieht lächerlich aus, anders als die Einheimischen hier. Ganz bemalt mit Kriegsfarben und gekleidet in ein farbenfrohes Kostüm... Du solltest den Kerker besuchen und dir diesen Narren selbst ansehen, wenn du magst, solange er noch lebt.";
			link.l1 = "Hm... Vielleicht schaue ich mal bei ihm vorbei.";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "Geh vor, schau dir die Freakshow an... Horosho, Charles, das war ein nettes Gespräch. Gute Reise zurück nach Martinique, Poputniy Veter!";
			link.l1 = "Alles Gute, Fadey.";
			link.l1.go = "exit";
			SetQuestHeader("Tichingitu");
			AddQuestRecord("Tichingitu", "1");
			pchar.questTemp.Sharlie.Tichingitu = "true";
			AddDialogExitQuestFunction("SetTichingituJail");
			SetFunctionTimerCondition("FreeTichingituOver", 0, 0, 10, false);
			pchar.questTemp.Sharlie = "takeknife";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "Wie interessant! Ich höre zu.";
			link.l1 = "Fadey, ich habe mit diesem Indianer gesprochen. Und ich komme zu dir, um um Hilfe zu bitten, ihn rauszuholen. Der arme Teufel wollte nur etwas zu essen...";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Hahaha, und du hast dieser Geschichte geglaubt? Junge Männer sind heutzutage so leichtgläubig...";
			link.l1 = "Fadey, ich mag jünger sein als du, aber selbst ich kann erkennen, wann mir die Wahrheit gesagt wird und wann man mich belügt. Außerdem, denkst du wirklich, eine Hinrichtung sei eine angemessene Strafe für diese Art von Verbrechen? Es scheint übertrieben. Zuhause würde man für einen Wiederholungstäter nur ein paar Peitschenhiebe oder eine Brandmarkung bekommen.";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "Übertrieben!? Er ist in mein Haus eingebrochen! Dieser Wilde hätte nie hierher kommen sollen! Was würdest du tun, wenn du in meiner Situation wärst? Du würdest sicherlich seine Innereien zu Äußereien machen und ihn zu Wurmfutter verarbeiten, ja?!";
			link.l1 = "Nein, das würde ich nicht, Fadey, Du bist immer noch wütend wegen deiner gestohlenen Shamshir-Sammlung. Wenn das nicht passiert wäre, wärst du eher geneigt, diesem lächerlichen Rothaut eine ordentliche Tracht Prügel und einen Tritt in den Hintern zu geben, liege ich falsch?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "Ahhhh, Charles... Du bist genau wie dein Bruder... Gut. Wir werden dies wie ehrliche Geschäftsleute klären. Da du diesen Inder so sehr willst, entschädige mich für den moralischen Schaden und den Sachschaden, den er verursacht hat und ich werde im Gegenzug dem Kommandanten sagen, dass ich keine Anklage erheben möchte. Wie klingt das?";
			link.l1 = "Wie viel?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Ha, du beginnst bereits, die Wege der Karibik zu lernen, Charles. Hundertfünfzig Gold-Dublonen, nicht einen Kopeken weniger.";
			link.l1 = "Fadey, Gott hab Erbarmen...";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Gut, gut. Hundert Gold-Dukaten. Aber das ist mein letztes Angebot. Und wir reden über Dukaten, nicht Pesos. Unser Bankier wird sicherlich in der Lage sein, diesen Betrag zum Tausch bereitzustellen.";
			if(PCharDublonsTotal() >= 100) // belamour legendary edition
			{
				link.l1 = "Ich habe gerade den Betrag, den Sie brauchen. Hier sind sie, hier sind Ihre hundert Dublonen.";
				link.l1.go = "Tichingitu_7";
			}
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l2 = "(Vertrauenswürdig) Fadey, hör zu... Ich verstehe deinen Ärger, aber ich bin der Einzige, der bereit ist, dich für diese Unannehmlichkeit mit echtem Geld zu entschädigen.";
				link.l2.go = "Tichingitu_7_TW";
			}
			else notification("Perk Check Failed", "Trustworthy");
			link.l3 = "In Ordnung, ich werde holen, was du brauchst.";
			link.l3.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_7_TW":
			dialog.text = "Du hast hier eine Zukunft, mein Freund, das kann ich dir sagen. Gut! Achtzig Gold - und kein Münzchen weniger!";
			link.l1 = "";
			link.l1.go = "Tichingitu_6";
			pchar.questTemp.Sharlie.Tichingitu80 = true;
		break;
		
		case "Tichingitu_6":
			dialog.text = "Und beeile dich, Charles! Du hast nur noch zehn Tage, bis er hingerichtet wird.";
			link.l1 = "Ich werde das im Kopf behalten. Auf Wiedersehen!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "dublon";
		break;
		
		case "Tichingitu_7":
			if(CheckAttribute(pchar,"questTemp.Sharlie.Tichingitu80"))
			{
				RemoveDublonsFromPCharTotal(80);
				DeleteAttribute(pchar,"questTemp.Sharlie.Tichingitu80");
			}
			else RemoveDublonsFromPCharTotal(100); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Sehr gut. Ich schreibe jetzt eine Notiz und setze mein Siegel darauf, warte einen Moment... hier bitte. Gib das dem Kommandanten und du kannst deinen Indianer mitnehmen. Ich bin mir nicht sicher, warum du dir so sehr um ihn Sorgen machst, aber das ist dein Problem. Was wirst du tun, stellst du ihn auf einer Maskerade zur Schau? Haha, was für ein Gedanke!";
			link.l1 = "Gott sieht alles, Fadey. Einem Mann das Leben zu retten, ist eine edle Tat.";
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1_Fadey");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ich stimme deiner ersten Aussage zu, aber deine zweite ist diskutabel, Charles. Was ist, wenn du einen Mörder oder Vergewaltiger vor der Gerechtigkeit rettest, die ihn am Ende eines Seils erwartet? Bah, was auch immer, nicht mehr mein Problem. Gott sei mit dir. Geh zum Kommandanten, bevor dein rothäutiger Freund blass wird von einem Strick um seinen Hals...";
			link.l1 = "Ich bin auf dem Weg. Bis später, Fadey.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "pay";
			SetFunctionLocationCondition("Tichingitu_AddQuestMark", "baster_prison", false);
			QuestPointerToLoc("BasTer_town", "reload", "reload_jail");
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
		break;
		
		case "vodka":
			dialog.text = "Du siehst grimmig aus, mein Freund! Ich nehme an, du bist dabei, mir schlechte Nachrichten zu überbringen?";
			link.l1 = "Das ist das lange und kurze davon, ja. Ich werde ehrlich zu dir sein, Fadey: Michel sagte, dass du mich mit diesem 'Häuptlingskralle' Stück Scheiße reingelegt hast. Er sagte, dies sei kein Artefakt, und ich könnte es von jedem Straßenhändler für ein paar hundert Pesos kaufen. Ich habe mich bei den Straßenverkäufern erkundigt, die mit Metallwaren handeln. Sie gaben mir genau diesen Preis.";
			link.l1.go = "vodka_1";
			npchar.quest.vodka = "true";
		break;
		
		case "vodka_1":
			dialog.text = "Ach, Monsieur de Maure ... Ich bin verletzt! Ich bin überrascht von Ihrem Bruder. Diese halbgebildeten Händler auf der Straße können sagen, was sie wollen, aber er! Sag mir, Charles, wenn dir jemand ein altes zweihändiges Ritterschwert aus den Tagen Karls des Großen brächte und anböte, es dir zu verkaufen, was würdest du dafür geben?";
			link.l1 = "Eine Zweihänder? Verarschst du mich gerade, Fadey? Was würde ich mit irgendeiner alten, rostigen Henkersklinge anfangen? Das ist das siebzehnte Jahrhundert im Namen des Herrn Jesus Christus! Ich würde keinen einzigen Peso dafür geben!";
			link.l1.go = "vodka_2";
		break;
		
		case "vodka_2":
			dialog.text = "Ach, nun sieh deine Kurzsichtigkeit, mein Freund! Mit dieser Einstellung wirst du es nie schaffen. Und wenn du mir ein solches Artefakt bringen würdest, würde ich dafür dreihundert Dublonen bezahlen. Fragst du warum? Weil es ein Antiquität ist, ein historischer Schatz, den man in dieser Zeit kaum findet! Du verstehst es nicht, und doch urteilst du! \nMit Gott und seiner gesegneten Mutter als meine Zeugen, die Klaue des Häuptlings ist ein Meisterwerk eines Dolches, meine Quellen sagen mir, dass Cortez selbst es besaß. DER Hernan Cortez! Der legendäre Konquistador, der Tenochtitlan plünderte und den Kaiser der Azteken gefangen nahm! Und du spottest und sagst, es sei gewöhnlicher Müll!\nAußerdem habe ich dir schon gesagt, dass es nicht irgendein Dolch ist, es ist ein verzauberter Dolch! Bist du immer noch so grün, dass du nicht alle Wunder der Karibik gesehen hast? Zauber und Magie, Rituale und Flüche? Charles, das ist die Neue Welt, die Heimat der Mayas und Azteken, deren Kenntnisse solcher teuflischen Künste Höhen erreichten, die uns Christen unvorstellbar sind!\nDieser Dolch hat verborgene Kräfte. Leider weiß noch niemand, welche Art von Kräften. Du hast eine einzigartige, unglaubliche Chance, selbst herauszufinden, wozu er fähig ist, und doch behauptest du immer noch, es sei ein 'Stück Scheiße' und dein lieber armer alter Freund Fadey hätte versucht, dich zu betrügen!\nWenn ich nur genug Geld hätte, um meine Schulden bei deinem Bruder zu begleichen, würde ich es sofort für deine verächtliche Münze zurücktauschen... Dies ist ein sehr wertvoller Gegenstand und sein Wert wird in mehr als nur Geld bemessen, ja!";
			link.l1 = "In Ordnung, in Ordnung, beruhige dich Fadey. Ich glaube dir. Deine Argumente sind ziemlich überzeugend und die feurige Leidenschaft, die du zeigst, ist entweder ein Zeugnis deiner Aufrichtigkeit oder deiner beispiellosen Schwindelei.";
			link.l1.go = "vodka_3";
		break;
		
		case "vodka_3":
			dialog.text = "Dankeschön! Du hast gut gemacht, Charles, dass du dich nicht beleidigt hast und direkt zu mir gekommen bist, um eine Erklärung zu bekommen. Ich vertraue darauf, dass das Problem jetzt vom Tisch ist?";
			link.l1 = "Ja, Monsieur Fadey. Völlig. Jetzt bitte, lassen Sie mich gehen...";
			link.l1.go = "vodka_4";
		break;
		
		case "vodka_4":
			PlaySound("Voice\English\sharlie\Fadey Moskovit-04.wav");
			dialog.text = "Halt, Charles! Ich werde ehrlich sein, ich mag deinen Stil. Vielleicht könnten du und ich eines Tages beste Freunde werden. Und warum nicht den ersten Schritt in Richtung dieser Freundschaft gleich jetzt machen? Ich habe zwei Flaschen ausgezeichneten russischen Wodkas in eiskaltem Quellwasser im Keller gekühlt. Was sagst du, sollen du und ich eine Flasche auf die Gesundheit deines Bruders öffnen?";
			link.l1 = "Hm. Es tut mir leid, Monsieur Fadey, aber es ist bereits Zeit für mich, in See zu stechen. Ich habe ein bisschen Eile.";
			link.l1.go = "vodka_no";
			link.l2 = "Du hattest es das letzte Mal angeboten und ich habe abgelehnt... Es wäre unhöflich, zweimal abzulehnen. Gut, Fadey. Ich bin dabei!";
			link.l2.go = "vodka_5";
		break;
		
		case "vodka_no":
			dialog.text = "Das ist zu schade. Im Vergleich zu Wodka ist Rum nur Wasser, billiger Wischiwaschi. Aber da du es eilig hast, will ich dich nicht länger aufhalten. Gute Jagd, Charles!";
			link.l1 = "Gleiches gilt für Sie, Monsieur Fadey...";
			link.l1.go = "exit";
		break;
		
		case "vodka_5":
			dialog.text = "Das höre ich gerne! Prächtig! Setzen Sie sich und legen Sie die Füße hoch! Bitte, Monsieur, fühlen Sie sich wie zu Hause während ich den Wodka hole. Oh, ich habe solche Nachmittagstreffen mit Freunden vermisst! Ah, der Wodka ist schön und kalt, Sie werden ihn sicherlich genießen, nazdoroviya! Lassen Sie mich ein paar Gurken und geräucherten Schinken herauslegen.";
			link.l1 = "...";
			link.l1.go = "vodka_6";
		break;
		
		case "vodka_6":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "bottle";
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "sit2";
			DoQuestReloadToLocation("BasTer_houseSp1", "sit", "sit2", "Sharlie_DrinkWithFadey");
			NextDiag.CurrentNode = "vodka_7";
		break;
		
		case "vodka_7":
			dialog.text = "";
			link.l1 = "Woah... Also, sag m-mir, Fadey, w-wie funktioniert d-das? Hic! Wir haben... z-zwei Flaschen W-Wodka getrunken... übrigens! - du siehst v-verdammt n-nüchtern aus und ich bin... betrunken wie ein Stinktier. Wie geht d-das, huh?";
			link.l1.go = "vodka_8";
		break;
		
		case "vodka_8":
			dialog.text = "Charles, mein Freund, entspann dich. Was hat ein Stinktier mit all dem zu tun? Wir haben gerade hervorragenden Wodka getrunken. Schlaf ein bisschen und du wirst beim Aufwachen hellwach und putzmunter sein. Selbst dein Kopf wird ohne Kater wieder klar. Du wirst sehen.";
			link.l1 = "J-ja, Wodka... es ist... es ist absolut großartig, dieser Wodka. Ich habe noch nie so etwas getrunken.";
			link.l1.go = "vodka_9";
		break;
		
		case "vodka_9":
			dialog.text = "Ha! Das hast du richtig erkannt! Diese Art von Wodka wurde nach geheimen Rezepten hergestellt und aus meiner Heimat Russiya verschifft, und selbst dort weiß nicht jeder, wie man ihn richtig herstellt. Ich kaufe nur das Beste! Wie diesen Stoff hier, den du und ich nippen durften.";
			link.l1 = "A-aber sag mir, Fadey: w-wie k-kannst du s-so viel trinken und nicht betrunken werden? W-wie machst du das, huh? T-teile das Geheimnis mit mir. V-vielleicht wird es später nützlich sein... Hic!";
			link.l1.go = "vodka_10";
		break;
		
		case "vodka_10":
			dialog.text = "Ha! Nun, du kannst dich und mich nicht vergleichen, junger Charles! Sieh dich nur an, dünn wie eine Peitsche. Dazu bist du nicht an ernstes Trinken gewöhnt, ja! Aber weil wir wahre Freunde sind, werde ich ein paar Geheimnisse mit dir teilen, wie man trinkt und sich davor bewahrt, sich anzupissen.";
			link.l1 = "B-bitte t-tun...hicks!";
			link.l1.go = "vodka_11";
		break;
		
		case "vodka_11":
			dialog.text = "Nun, wenn du trinken willst und nicht sofort knallvoll sein willst, musst du ein paar wichtige Regeln befolgen. Am wichtigsten ist, niemals zu trinken, wenn dein Magen leer ist. Iss etwas Herzhaftes, bevor die Trinksession beginnt\nZweitens, vergiss nicht, nach jedem Glas etwas zu essen. Fleisch oder Fisch wären am besten, etwas Schönes und Salziges. Drittens, spüle nicht den Mund mit dem Wodka aus, schlucke ihn auf einmal\nAußerdem, ein kleiner - nicht mehr als ein halber Pint - Schluck vor dem Hauptgang bereitet deinen Körper auf ernsthafte Alkoholdosen vor. Übertreibe diesen Appetizer nicht, sonst wird der Effekt ganz das Gegenteil sein und du wirst dich ruinieren, bevor du in See stichst\nSchließlich ist diszipliniertes Training der Schlüssel, regelmäßiges Trinken moderater Mengen Rum oder anderer Alkoholarten macht dich widerstandsfähiger gegen sie.";
			link.l1 = "Hm-mm... S-so ist es also! Ich werde definitiv...hic!.. all deine Anweisungen, Fadey, behalten. D-danke dir. Und j-jetzt glaube ich, wäre es eine g-gute Idee, ein wenig zu schlafen, denn ich fühle mich gerade nicht so gut.";
			link.l1.go = "vodka_12";
		break;
		
		case "vodka_12":
			dialog.text = "Gönn dir etwas Ruhe, Charles. Wir hatten einen schönen Abend, du und ich! Waidmannsheil!";
			link.l1 = "D-d-do Wiedersehen, Fadey! Ich gehe zu - hic! - dem Wunscherfüller!";
			link.l1.go = "vodka_13";
		break;
		
		case "vodka_13":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = false;
			sld = ItemsFromID("lcheer");
			sld.shown = false;
			pchar.questTemp.CanDrink = true; // Шарль теперь знает секреты выпивки, это ему потом пригодится
			LAi_SetSitType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Sharlie_TrialOver.over = "yes"; //снять таймер
			dialog.text = "Was, hat er tatsächlich gesagt, dass ich dir helfen würde?";
			link.l1 = "Nun, ziemlich viel. Wirst du dem Bruder deines langjährigen Freundes helfen? Es ist nicht so, als würde ich um Almosen wie ein Bettler bitten. Ich bitte dich, mir die Möglichkeit zu geben, etwas Geld zu verdienen.";
			link.l1.go = "trial_1";
		break;
		
		case "trial_late":
			dialog.text = "Ach Charles! Du bist spät dran. Wärst du früher gekommen, hätte ich das Richtige für dich gefunden, aber jetzt - prosti. Mach dir keine Sorgen, schlendere durch die Städte, plaudere mit Leuten. In der Karibik gibt es viel zu tun";
			link.l1 = "Ich sehe, das ist bedauerlich. Auf Wiedersehen!";
			link.l1.go = "trial_late_1";
		break;
		
		case "trial_late_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Trial");
		break;

		case "trial_1":
			dialog.text = "Hm. Nein, ich werde dich natürlich nicht abweisen. Wenn du einen Mann ernähren willst, gib ihm keinen Fisch, sondern eine Angel. Nicht wahr, Monsieur de Maure? Also brauchst du einen Job... Einfach genug. Ich werde mit einem Mann reden, den ich kenne, und ich werde dich ihm empfehlen. Und alles andere hängt davon ab, wie gut du die Arbeit machst.";
			link.l1 = "Wunderbar. Mit wem muss ich sprechen?";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "Komm morgen in den Laden. Ein Mann namens Gerard LeCroix wird dort auf dich warten. Er wird dir etwas Arbeit geben. Er wird nur bis morgen Abend in dieser Kolonie herumsitzen. Sieh ihn bald und erledige die Arbeit ordentlich. Bring mich nicht in eine peinliche Position.";
			link.l1 = "Abgemacht. Danke dir, Fadey!";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			SetFunctionTimerCondition("Trial_StartLine", 0, 0, 1, false); // таймер
			pchar.questTemp.Trial = "start";
			AddQuestRecord("Trial", "1");
		break;
		// belamour legendary edition пиратская линейка -->
		case "Slaves":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Ach, wie kann ich dir helfen, mein Freund?";
			link.l1 = "Fadey, hör zu, ich muss wirklich fünfzig Sklaven von Schmugglern kaufen. Das Problem ist, sie kennen mich nicht und ich brauche deine Vorstellung für mich. Ohne dich werden sie mir nicht einmal zuhören, und dies ist eine Frage von Leben und Tod für eine sehr wichtige Person.";
			link.l1.go = "Slaves_1";
		break;
		
		case "Slaves_1":
			dialog.text = "Oh ho! Du erweiterst also dein Geschäft, wie ich sehe! Wie profitabel! Ich werde dir helfen, lieber Freund. Aber wie du weißt, arbeite ich nicht umsonst. Es wird 150 Gold-Dublonen kosten, um den Verkäufer von deinen guten Absichten zu überzeugen, die Neger zu kaufen und natürlich ein kleines Extra für meine fleißigen Bemühungen...";
			if(PCharDublonsTotal() >= 150)
			{
				link.l1 = "Ich habe nichts weniger erwartet, Monsieur Fadey! Hier ist dein Gold.";
				link.l1.go = "Slaves_2";
			}
			else
			{
				link.l1 = "Ich gehe sofort zum Wucherer! Warte, Monsieur Fadey, ich komme gleich wieder!";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.GiveMeSlaves = "FindGold"; 
			}
			
			link.l2 = "Fadey, es scheint, dass ich etwas gefunden habe und die Neger nicht mehr brauche. Es tut mir leid. Bis dann!";
			link.l2.go = "Slaves_3";
		break;
		
		case "Slaves_2":
			RemoveDublonsFromPCharTotal(150);
			pchar.questTemp.Mtraxx.GiveMeSlaves = "kapster";
			locations[FindLocation("Shore29")].DisableEncounters = true; //энкаутеры закрыть
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1 = "Hour";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.start.hour = 22.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.finish.hour = 23.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3 = "location";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3.location = "Shore29";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.function = "MtraxxGiveMeSlavesKapsterInShore"; // прибыли
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.hour  = 23.0; // не пришли, значит гудбай
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.function = "MtraxxGiveMeSlavesKapsterInShoreLate"; // опоздание
			AddQuestRecord("Roger_3", "23");
			dialog.text = "Ausgezeichnet, Freund. Aber wenn du mich mit dem Bedarf deines Kaufs täuschen willst und es für wertlose Zwecke ist, wirst du mich sehr wütend machen. Du willst das nicht. Morgen um zehn Uhr bei Sonnenuntergang am Capster Strand werde ich ein Treffen für dich arrangieren, versetz mich nicht.";
			link.l1 = "Du musst dir keine Sorgen machen, ich komme zurück für die Waren.";
			link.l1.go = "exit";
		break;
		
		case "Slaves_3":
			DialogExit();
			AddQuestRecord("Roger_3", "22");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
		break;
		
		case "pistols":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Hallo hallo! Sag mir, guter Kerl, was bringt dich zu meinem bescheidenen Haus?";
			link.l1 = "Ich brauche Waffen. Die örtlichen Händler können die Menge, die ich brauche, nicht finden, aber ich denke, du kannst mir helfen.";
			link.l1.go = "pistols_1";
		break;
		
		case "pistols_1":
			dialog.text = "Zuerst einmal, erzähle mir, lieber Freund, was genau Du benötigst. Dann werde ich Dir genau sagen, ob ich Dir helfen kann.";
			link.l1 = "Ich brauche 30 Soldatenpistolen, zwei Luntenmusketen, 70 Patronen dafür und 90 Heiltränke.";
			link.l1.go = "pistols_2";
		break;
		
		case "pistols_2":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
			{
				if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
				{
					dialog.text = pchar.name+", du machst mir Angst. Erst fünfzig Neger, dann Waffen. Versuchst du einen Sklavenaufstand zu starten, mein Freund?";
					link.l1 = "Sehr scharfsinnig, Fadey. Wie ich schon früher sagte, ist all dies notwendig für die Rettung einer wichtigen Person. Mach dir keine Sorgen, er wird aus den Klauen der Spanier gezogen, so wird dein Ruf hier nicht leiden.";
					link.l1.go = "pistols_3";
					break;
				}
			}
			dialog.text = "Das ist gut zu hören. Ich kann helfen.";
			link.l1 = "Es freut mich, das zu hören. Wie viel?";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_3":
			dialog.text = "Ich bin froh, dass du dich erklärt hast. Und wenn das wirklich etwas mit den Spaniern zu tun hat, dann werde ich dir helfen. Aber wenn sich herausstellt, dass du mich getäuscht hast, werde ich sehr wütend sein.";
			link.l1 = "Habe etwas Vertrauen in mich, Fadey. Wie viel?";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_4":
			dialog.text = "Gut, also ... Pistolen und ein paar Musketen, mit Pulver und Kugel für jede... Daher ... Ich kann nicht versprechen, dass ich absolut alles bekomme, was du gefragt hast, aber ich werde alles in meiner Macht stehende tun. In der Zwischenzeit brauche ich eine Anzahlung von 40.000 Pesos oder 300 Dublonen, wenn du das bevorzugst.";
			if(PCharDublonsTotal() >= 300)
			{
				link.l1 = "Nimm Dublonen, Fadey. Ich habe zufällig gerade einige bei mir.";
				link.l1.go = "pistols_4D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "Alle meine Dublonen sind ausgegangen, nimm Pesos, Fadey.";
				link.l2.go = "pistols_4P";
			}
			if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "Ich muss mit meinem Bankier sprechen. Ich bin gleich zurück!";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "Entschuldigung, Fadey, aber ich kann es mir nicht leisten. Ich werde versuchen, alleine zurechtzukommen. Bis später!";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_4D":
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "Komm morgen, "+pchar.name+", und ich werde das Material haben, das du brauchst.";
			link.l1 = "Dann werde ich nicht im Weg stehen. Bis morgen!";
			link.l1.go = "exit";
		break;
		
		case "pistols_4P":
			AddMoneyToCharacter(pchar, -40000);
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
            pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "Komm morgen, "+pchar.name+", und ich werde das Material haben, das du brauchst.";
			link.l1 = "Dann werde ich nicht im Weg sein. Bis morgen!";
			link.l1.go = "exit";
		break;
		
		case "pistols_X":
			DialogExit();
			DeleteAttribute(pchar,"questTemp.Mtraxx.MagicBox");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
		break;
		
		case "pistols_5":
			dialog.text = "Nun, mein Junge, ich hatte Glück, alles zu finden, was du unter solchen Zeitdruck gefragt hast. Du solltest dankbar sein! Jetzt, die endgültige Zahlung. Gib mir genau so viel mehr, wie als Anzahlung gegeben wurde, und nimm deine Waffen.";
			if(PCharDublonsTotal() >= 300)
			{
				link.l1 = "Nimm 300 Dublonen. Meine Männer werden die Waffen auf mein Schiff bringen. Was würde ich ohne dich tun, Fadey? Du hast keine Ahnung, wie sehr du mir geholfen hast!";
				link.l1.go = "pistols_5D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "Nimm 40 000 Pesos. Meine Männer werden die Waffen zu meinem Schiff bringen. Was würde ich ohne dich machen, Fadey? Du hast keine Ahnung, wie sehr du mir geholfen hast!";
				link.l2.go = "pistols_5P";
			}
			if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "Nun verdammt, wie konnte ich das Geld vergessen? Ich komme bald zurück.";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "Entschuldigung, Fadey, ich bin pleite. Behalte die Anzahlung, ich hoffe, es wird genug sein, um deine Ausgaben mit diesem Geschäft zu decken, und ich werde versuchen, alleine klarzukommen. Auf Wiedersehen!";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_5D":
			Log_Info("Fadey's weapons are loaded on the ship");
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "Helfen Sie denen in Not ist eine Ehre. Helfen Sie denen, die zahlen, ist ein Vergnügen. Wenn Sie das nächste Mal in Basse-Terre sind, besuchen Sie mich, um Hallo zu sagen.";
			link.l1 = "Das ist absurd - in Basse-Terre zu sein und meinen Freund Fadey nicht zu sehen! Bis zum nächsten Mal!";
			link.l1.go = "exit";
		break;
		
		case "pistols_5P":
			Log_Info("Fadey's weapons are loaded on the ship");
			AddMoneyToCharacter(pchar, -40000);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "Helfen Sie denen in Not ist eine Ehre. Helfen Sie denen, die bezahlen, ist ein Vergnügen. Wenn Sie das nächste Mal in Basse-Terre sind, besuchen Sie mich, um Hallo zu sagen.";
			link.l1 = "Das ist absurd - in Basse-Terre zu sein und meinen Freund Fadey nicht zu sehen! Bis zum nächsten Mal!";
			link.l1.go = "exit";
		break;
		// <-- legendary edition

		case "guardoftruth":
			dialog.text = "Nun, wer würde daran zweifeln, dass du geschäftlich hier bist, mein Freund! Leider kann ich dir im Moment keinen Wodka anbieten, ich habe alles getrunken. Erzähl mir, in was für Ärger du jetzt wieder geraten bist.";
			link.l1 = "Einer örtlichen Pfarrei wurde von einem gewissen Freibeuter ein goldenes Brustkreuz mit Lazurit für die Vergebung seiner Sünden angeboten. Es ist ein einzigartiger und wertvoller Gegenstand. Das Problem ist, dass dieses Kreuz aus einer anderen Pfarrei gestohlen wurde. Nicht nur das, sondern ein Priester wurde während des Raubüberfalls ermordet.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "O makellose Theotokos! Sag bloß!";
			link.l1 = "Ja. Ich vertrete die beraubten Pfarrkinder und versuche, das Kreuz seinen ursprünglichen Besitzern zurückzugeben.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Eine edle Tat und sehr fromm. Versuchst du, Punkte bei dem Allmächtigen zu sammeln?";
			link.l1 = "Aber der örtliche Priester weigert sich, es mir zurückzugeben, trotz allem, was ich ihm erzählt habe. Ich verstehe es nicht. Wie kann man ruhig ein gestohlenes Kreuz mit dem Blut eines unschuldigen Mannes darauf im Haus Gottes aufstellen? Das ist Blasphemie!";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Nun, technisch gesehen trägt jeder geweihte Kelch das Blut des unschuldigen Christus...aber ich schweife ab. Du möchtest also, dass ich dir helfe?";
			link.l1 = "Ich tue es! Sie haben einen großen Einfluss in Basse-Terre. Sie werden respektiert, also wird der Priester vielleicht auf Ihre Ermahnungen hören.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = ""+pchar.name+", hast du unserem Priester die genaue Geschichte dieses gestohlenen Kreuzes erzählt?";
			link.l1 = "Natürlich! Ich habe an seine religiösen Gefühle, an christliche Solidarität, an sein verdammt Gewissen um Gottes willen appelliert, aber er hat seine Ohren verschlossen.";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Hm... Haben Sie schon versucht, ihn auf andere Weise zu überzeugen?";
			link.l1 = "Du meinst ihn bestechen? Ich bestechen keinen Priester. Wäre er ein Bankier, oder ein Händler, oder sogar ein Gouverneur, würde ich versuchen das Problem auf diese Weise zu lösen, aber keinen Priester!";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Mein lieber naiver Freund, wenn die Ohren des Priesters wirklich gegen Gewissensbekenntnisse taub sind, dann werden sicherlich seine Hände für Gold offen sein... Oder andersherum. Ich werde dir helfen, ich denke, dass es größere Probleme verursachen wird, wenn wir einen solch befleckten Schatz hier behalten. Es wird jedoch bestimmte Ausgaben erfordern."link.l1 ="Warum bin ich nicht überrascht? Wie viel diesmal?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Komm morgen vorbei, "+pchar.name+", Ich kann den Preis noch nicht nennen. Aber du wirst dieses gestohlene Kreuz haben, sei versichert.";
			link.l1 = "Sehr gut Fadey, ich werde dich dann nicht weiter belästigen. Bis morgen!";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			pchar.questTemp.Guardoftruth.Baster_church = "wait";
			SetFunctionTimerCondition("GuardOT_FadeyTimer", 0, 0, 1, false);
			AddQuestRecord("Guardoftruth", "29");
		break;
		
		case "guardoftruth_9":
			dialog.text = "Genau wie versprochen, habe ich das Kreuz. Was die Details angeht... ach vergiss sie... alles Unsinn, vergeben durch das vergossene Blut unseres kostbaren Erlösers";
			link.l1 = "Wie viel schulde ich Ihnen?";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Zweihundertfünfzig Dublonen. Als Deckung meiner Ausgaben, und natürlich würde ich ein kleines Extra für meine rechtschaffene Hilfe schätzen...";
			if(PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "Jawohl, Monsieur Fadey. Hier ist Ihr Gold.";
				link.l1.go = "guardoftruth_11";
			}
			else
			{
				link.l1 = "Ich muss das Gold aus meiner Kabine holen. Bin gleich zurück.";
				link.l1.go = "exit";
				npchar.quest.utensil = "true";
			}
		break;
		
		case "guardoftruth_11":
			DeleteAttribute(npchar, "quest.utensil");
			dialog.text = "Gut. Hier ist das gestohlene Kreuz.";
			link.l1 = "Danke dir, Fadey. Du kannst dir gar nicht vorstellen, wie viel du für mich getan hast!";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			RemoveDublonsFromPCharTotal(250); // belamour legendary edition
			GiveItem2Character(pchar, "jewelry34");
			//Log_Info("You've received a golden cross with lazurite");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ich helfe immer gerne einem freundlichen - und vor allem - großzügigen Freund. Schauen Sie öfter vorbei. Vielleicht trinken wir Wodka, wenn er mir aus der Heimat geliefert wird.";
			link.l1 = "Gerne!";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Baster_church");
			AddQuestRecord("Guardoftruth", "30");
		break;
		
		case "guardoftruth_14":
			dialog.text = "Nun, nun, das Meer hat dich noch nicht gefordert! Erzähl mir. Welche Unglücke haben dich dieses Mal zu meiner Tür gebracht?";
			link.l1 = "Ich weiß nicht, ob ich sie Unglücke nennen soll oder nicht, aber trotzdem bin ich hier. Fadey, am ersten Tag, an dem wir uns trafen, hast du mir einen seltenen Dolch gegeben, die Klaue des Häuptlings. Jetzt weiß ich, dass er zuvor einem Mann namens Archibald Calhoun gehörte. Bitte, erzähle mir, was du über diesen Mann weißt.";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Vor dir kann nichts verborgen bleiben, "+pchar.name+". Du siehst durch alles durch, genau wie dein Bruder. Ja, ich habe diesen Dolch in einem Würfelspiel von Calhoun gewonnen. Wer ist er? Ich habe selbst keine Ahnung. Wir trafen uns zufällig in der Taverne, wir kamen ins Gespräch, tranken ein wenig, und er begann mir von einigen Sünden seiner Vergangenheit zu erzählen, die ihn belasteten...";
			link.l1 = "Was bist du, sein Beichtvater? Welche Sünden?";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "Archibald wurde von der Erinnerung an einen Mann verzehrt, der wegen ihm und über anderen unschuldigen Seelen, die er getötet hatte, von der Inquisition gefoltert und getötet wurde. Er nannte sich selbst Judas. Sagte, dass Gott ihn für seine Sünden bestrafte und die Inquisition jagte ihn\nEr erwähnte, dass der spanische Inquisitor Vincento selbst ihn tot sehen wollte und Söldner schickte, um ihn durch die Karibik zu jagen. Dann gewann der Alkohol über sein besseres Urteil und wir spielten um diesen alten Dolch.";
			link.l1 = "Ist das alles? Hast du ihn nie wieder gesehen?";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Natürlich nicht, er ist jetzt tot. Eine Bande elender Piraten hat seine Fluyt in Davy Jones' Spind geschickt und die ganze Besatzung zu Mictlantecuhtli. Ehrlich gesagt, es gab Gerüchte, dass sie von Profis angegriffen wurden, die sich als Piraten verkleidet hatten... Agenten der Inquisition. Man sagt, Vater Vincento kriegt immer seinen Mann.";
			link.l1 = "Archibald Calhoun lebt. Ich habe ihn vor nicht allzu langer Zeit zusammen mit einem gewissen William Paterson gesehen. Er dient ihm als erster Maat.";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Oh ho, was für eine Überraschung! Archibald kann zumindest unter Kapitän Patersons Flügel Atem holen. Er ist in guter Gesellschaft. Die Spanier fürchten Patterson wie die Pest. Sie würden es nicht wagen, gegen Archibald zu intrigieren, solange er unter Patterons Schutz steht.";
			link.l1 = "Kennen Sie Paterson?";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "Wer kennt William Paterson nicht!? Er ist ein Neuling in der Karibik, genau wie du. Und genau wie du hat er sich bereits einen gewaltigen Ruf erarbeitet. Herr Patterson ist der engste Freund von Colonel Fox und steht in gutem Verhältnis zu Lord Windsor selbst, dem Generalgouverneur aller englischen Kolonien in der Karibik. Er besucht oft den Gouverneurspalast in Port Royal, auf Jamaika.";
			link.l1 = "Hab's kapiert. Danke für die Information, Fadey!";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "Ach, erwähne es nicht, Freund. Besuch mich mal! Gute Jagd!";
			link.l1 = "Sicherlich!";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			DialogExit();
			pchar.questTemp.Guardoftruth.Archy = "portroyal";
			AddQuestRecord("Guardoftruth", "62");
			// эскадру Патерсона - в Порт-Рояль
			Group_SetAddress("Willy_group", "Jamaica", "quest_ships", "quest_ship_1");
			pchar.quest.GuardOT_jamaica.win_condition.l1 = "location";
			pchar.quest.GuardOT_jamaica.win_condition.l1.location = "Jamaica";
			pchar.quest.GuardOT_jamaica.function = "GuardOT_PortRoyalArrive";
		break;
		
		// персидские клинки
		case "persian":
			dialog.text = "Lass uns mal schauen, "+pchar.name+"... Da! Das ist einer von ihnen! Das ist mein Junge, du hast meinen Tag gemacht! Wo hast du es gefunden?";
			link.l1 = "Es spielt keine Rolle. Das Wichtige ist, dass es seinen Weg zurück zu dir gefunden hat.";
			link.l1.go = "persian_1";
		break;
		
		case "persian_1":
			dialog.text = "Ich werde gut für Ihre gründliche Untersuchung bezahlen. Drei hundert goldene Dublonen sollten als Belohnung für Ihre Mühen ausreichen...";
			link.l1 = "Bist du dabei, mich mit einigen der Dublonen zu bezahlen, die du mir vorher aus der Tasche gezogen hast? Obwohl ich sie natürlich nicht ablehnen werde. Hier ist dein Shamshir.";
			link.l1.go = "persian_2";
		break;
		
		case "persian_2":
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "one";
			dialog.text = "Spasiba, mein Freund! Danke für das Schwert und deine sarkastischen Worte. Du bist weise über deine Jahre hinaus, "+pchar.name+", aber menschliche Freundschaftsbande übersteigen den Wert von Gold. Apropos Gold, - Ich werde dir vollständig bezahlen. Hier, nimm deine Dublonen.";
			link.l1 = "Danke.";
			link.l1.go = "persian_3";
		break;
		
		case "persian_3":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("You've received 300 doubloons");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "Und wenn wir schon über die Bande der Freundschaft sprechen, insbesondere über unsere, "+pchar.name+". Ich habe etwas, das dich sehr interessieren wird.";
			link.l1 = "Lass mich raten, mehr Wodka?";
			link.l1.go = "persian_4";
		break;
		
		case "persian_4":
			dialog.text = "Ha! Wodka ist gut, aber das ist nicht das Einzige, wofür mein Land bekannt ist. Es gibt ein besonderes Material, das nur Russland produziert. Ich lasse dieses Material von meinen Kontakten aus der Heimat hierher liefern, um zu handeln. Jeder Kapitän will es haben, denn es verbessert jedes Schiff. Ich spreche von Hanfseilen\nSeilen, die gegen Feuchtigkeit und Meersalz gleichermaßen immun sind. Man sagt, dass es das beste Material für Takelage ist\nJeden Monat bekomme ich eine bestimmte Menge aus Reval geliefert. Normalerweise hat mein Lagerhaus Mitte des Monats ein paar hundert Spulen. Also, "+pchar.name+", I am offering to sell you a batch of fifty coils. Ten doubloons a coil\nI have only two terms: first, I will keep your ropes until the 20th of every month; second, you can buy only the whole batch. Fifty coils for five hundred doubloons. Confidentially speaking, "+pchar.name+", they say that there are certain places where you can resell those ropes for a much greater price, but what do I know!\I am completely satisfied with the current state of my operation and don't need to find resellers myself. If you find a good merchant, you can turn a fine profit.";
			link.l1 = "Verstanden. Das ist ein großartiges Angebot, Fadey! Ich glaube, ich werde die Gelegenheit nutzen, die du mir geboten hast. Also, jeden zwanzigsten Tag eines Monats, fünfhundert Dublonen für fünfzig Stücke?";
			link.l1.go = "persian_5";
		break;
		
		case "persian_5":
			AddQuestRecordInfo("Unique_Goods", "2");
			dialog.text = "Da. Holen Sie Ihren Kauf ab. Aber warten Sie, warten Sie, lieber Kerl! Neben diesem Shamshir, das Sie mir aus wahrer Wohlwollen zurückgegeben haben, gab es noch zwei andere. Ich bitte Sie, bitte, wenn Sie sie finden, bringen Sie sie mir zurück und ich werde Ihnen mehr als einen fairen Preis für ihre Rückkehr zahlen.";
			link.l1 = "Sicherlich, Fadey. Wenn ich sie finde, bringe ich sie zurück.";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "Gute Nachrichten für dich. Ich habe ein weiteres persisches Shamshir.";
				link.l2.go = "persian_6";
			}
			npchar.quest.ropes = "true";
		break;
		
		case "persian_6":
			dialog.text = "Oh, mein guter Freund! Du hast gerade meine Tränen getrocknet! Lass mich mal sehen... Da! Das ist es, mein wertvolles Shamshir! Hier, genau wie ich dir versprochen habe, dreihundert Dublonen Belohnung dafür.";
			link.l1 = "Danke!";
			link.l1.go = "persian_7";
		break;
		
		case "persian_7":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("You've received 300 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "two";
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "Bitte akzeptieren Sie meine Dankbarkeit und ein bescheidenes, aber sehr nützliches Geschenk. Ich brauche es nicht, aber Sie oder Ihr Schiffszimmermann werden es sehr hilfreich finden\nHier, schauen Sie sich diesen feinen Ring an! Er gehört jetzt Ihnen. Aber es ist nicht irgendein gewöhnlicher Ring, es ist ein verzauberter Ring. Er hilft beim Teppichlegen und bei der Schiffreparatur. Viele Handwerker würden ihn gerne haben, aber ich habe ihn für einen besonderen Anlass aufbewahrt. Nehmen Sie ihn, mein Freund, ich hoffe, er wird Ihre Last erleichtern!";
			link.l1 = "Sie tragen sicherlich viele interessante Artefakte bei sich. Danke, Fadey!";
			link.l1.go = "persian_8";
		break;
		
		case "persian_8":
			GiveItem2Character(pchar, "talisman7");
			//Log_Info("You've received the Scarab amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Es bleibt nur noch ein Shamshir meiner verlorenen Sammlung zu finden. Ich zähle auf dich, "+pchar.name+", und auf dein Glück. Wenn du es findest, zögere nicht, schnell zu mir zurückzukehren.";
			link.l1 = "Auf jeden Fall! Bis bald...";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "Warum sollte ich mich beeilen? Das Schwert ist bei mir.";
				link.l2.go = "persian_9";
			}
		break;
		
		case "persian_9":
			dialog.text = "Oh, Gott sei Dank, dass ich gerade dich um Hilfe gebeten habe, "+pchar.name+". Du bist ein Wundermann, mein Freund! Zeig es mir... Ohooo! Sie ist es, sie ist es. Meine Liebling! Krasavitsa! Ich danke dir, feiner Kerl, ich verneige mich vor dir! Hier, hier ist dein Geld. Vierhundert Dublonen und kein Kopeke weniger! Ich werde nicht geizig sein.";
			link.l1 = "Danke dir, Fadey. Es ist ein Vergnügen zu helfen.";
			link.l1.go = "persian_10";
		break;
		
		case "persian_10":
			TakeNItems(pchar, "gold_dublon", 400);
			//Log_Info("You've received 400 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 3);
			Achievment_Set("ach_65");
			dialog.text = "Meine Sammlung von Shamshirs ist wieder vereint! Niemand wird es wagen, sie mir wieder zu stehlen, das werde ich sicherstellen! Ich habe eine ganz besondere Belohnung für dich, guter Mann. In zwei Wochen wird ein Kaufmann mir eine Reihe von hervorragender Fecht-Rüstung aus Europa bringen. Auf Bestellung von einem Adligen, es ist ein ziemlich einzigartiges Rüstungsstück\nAlso, wenn du willst, kannst du es für nur siebenhundert goldene Dublonen kaufen. Ich werde dem Adligen sagen, dass es auf dem Weg verloren gegangen ist.";
			link.l1 = "Was ist so gut an dieser Rüstung?";
			link.l1.go = "persian_11";
		break;
		
		case "persian_11":
			dialog.text = "Es ist sehr bequem und haltbar, dennoch leistet es so gut wie der Eisenharnisch. Plus, es sieht toll aus! Du solltest in ein paar Wochen wiederkommen und es dir ansehen. Aber nimm dir nicht länger als einen Monat oder ich verkaufe es an den ursprünglichen Kunden.";
			link.l1 = "Abgemacht. Ich schaue in zwei Wochen bei dir vorbei.";
			link.l1.go = "persian_12";
		break;
		
		case "persian_12":
			DialogExit();
			pchar.questTemp.Persian = "time";
			SetFunctionTimerCondition("Persian_CirassLamport", 0, 0, 14, false); // таймер
		break;
		
		case "persian_13":
			dialog.text = "Ja, es wurde bereits geliefert und wartet auf Sie. Hast du das Geld mitgebracht?";
			if(PCharDublonsTotal() >= 700) // belamour legendary edition
			{
				link.l1 = "Ja. Hier sind siebenhundert Dublonen.";
				link.l1.go = "persian_14";
			}
			else
			{
				link.l1 = "Verdammt. Ich habe das Geld auf dem Schiff vergessen. Ich bringe es in einer Sekunde!";
				link.l1.go = "exit";
			}
		break;
		
		case "persian_14":
			RemoveDublonsFromPCharTotal(700); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "cirass8"); 
			//Log_Info("You've received wicker armour");
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			dialog.text = "Ja, mein guter Mann! Hier, nimm das. Diese Rüstung aus Weide wird dir gut dienen, das versichere ich dir. Es gibt nichts Vergleichbares, nicht in der gesamten Karibik!";
			link.l1 = "Ja, das kann ich sehen. Danke! Kann es kaum erwarten, es anzuprobieren...";
			link.l1.go = "persian_15";
		break;
		
		case "persian_15":
			dialog.text = "Warum musst du warten? Mach weiter. Mal sehen, wie es passt.";
			link.l1 = "Mach ich. Bis später, Monsieur Fadey!";
			link.l1.go = "persian_16";
		break;
		
		case "persian_16":
			DialogExit();
			pchar.questTemp.Persian = "end";
			pchar.quest.Persian_CirassLamportOver.over = "yes"; //снять прерывание
		break;
		
		// торговля канатами
		case "ropes":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes"))
			{
				dialog.text = "Kommen Sie herein, mein lieber Freund. Die Ware ist bereit für Ihren Kauf. 2125 Dublonen für zweihundertfünfzig Stücke.";
				if (PCharDublonsTotal() >= 2125)
				{
					link.l1 = "Alles ist wie vereinbart. Nimm das Geld.";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "Lass mich nur die Münzen aus meiner Kabine holen.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Komm herein, mein lieber Freund. Die Ware ist bereit für deinen Kauf. Fünfhundert Dublonen für fünfzig Stücke.";
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = "Alles ist wie vereinbart. Nimm das Geld.";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "Lass mich nur die Münzen aus meiner Kabine holen.";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && !CheckAttribute(pchar, "questTemp.FadeyRopesBlock")) // увеличить объём поставок канатами
			{
				link.l4 = "Fadey, könnten wir das Volumen unserer Geschäfte erhöhen? Ich bin bereit, fünfmal mehr Waren von dir zu kaufen! Ich denke, das würde uns beiden zugute kommen. Was sagst du dazu?";
				link.l4.go = "UpgradeRopes";
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && CheckAttribute(pchar, "questTemp.FadeyRopesPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок канатами, если в первый раз не принесли
			{
				link.l4 = "Fadey, ich habe das Geld mitgebracht! Drei tausend Gold-Dukaten, wie vereinbart.";
				link.l4.go = "UpgradeRopes_Agreed";
			}
		break;
		
		case "ropes_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) RemoveDublonsFromPCharTotal(2125);
			else RemoveDublonsFromPCharTotal(500); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Schön, Geschäfte mit Ihnen zu machen, "+pchar.name+". Ich werde meinen Männern befehlen, die Seile auf Ihr Schiff zu tragen.";
			link.l1 = "Danke dir!";
			link.l1.go = "ropes_2";
		break;
		
		case "ropes_2":
			dialog.text = "Wenn du noch mehr Seile brauchst, komm in einem Monat wieder.";
			link.l1 = "Sehr gut, Fadey. Bis später!";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) AddCharacterGoods(pchar, GOOD_ROPES, 250);
			else AddCharacterGoods(pchar, GOOD_ROPES, 50);
			DeleteAttribute(npchar, "quest.ropes");
			SetFunctionTimerCondition("Ropes_FadeyAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.FadeyRopes = sti(pchar.questTemp.FadeyRopes) + 1; // счётчик покупок
		break;
		
		// уменьшение НЗГ
		case "help":
			if (!CheckAttribute(npchar, "quest.relation_info"))
			{
				dialog.text = "Was kann ich für Sie tun, mein lieber Freund?";
				link.l1 = "Sie sind ein einflussreicher Mann, Fadey. Ein Freund des Gouverneurs und, wie Gerüchte sagen, haben Sie Verbindungen zum Hof. Könnten Sie bei den Behörden intervenieren, falls ich Ärger mit dem Gesetz bekomme?";
				link.l1.go = "relation_info";
				break;
			}
			dialog.text = "Wie kann ich Ihnen helfen, mein Freund?";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "Ich habe ein Problem mit den englischen Behörden.";
				link.l1.go = "relation";
				pchar.GenQuest.FadeyNation = ENGLAND;
			}
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "Ich habe Ärger mit den französischen Behörden bekommen.";
				link.l2.go = "relation";
				pchar.GenQuest.FadeyNation = FRANCE;
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Ich habe ein riesiges Problem mit den Schmugglern.";
				Link.l5.go = "contraband";
            }
			link.l9 = "Entschuldigung, ich denke, ich kann es selbst schaffen.";
			link.l9.go = "exit";
		break;
		
		case "relation_info":
			dialog.text = "Oh ho ho, mein guter Mann, wer hat dir das gesagt? Jeder lügt. Aber da du Michel's Bruder und ein guter Freund von mir bist, kann ich versuchen, die Dinge für dich zu regeln. Ich kann nur bei den englischen und französischen Behörden für dich eintreten, obwohl meine Verbindungen Grenzen haben. Ich mache keine Geschäfte mit den Spaniern und den Niederländern.\nIch warne dich auch, dass mein Einfluss nur ausreicht, um dich vor geringfügigen Vergehen zu retten. Ich kann sie dazu bringen, ihre Haltung dir gegenüber im Falle eines leichten Fehlverhaltens zu überdenken oder etwas milden Zorn zu lindern. Also fang keinen Krieg an und erwarte, dass ich deine Kastanien aus dem Feuer hole!\nDarüber hinaus kann ich nur eine Nation auf einmal beruhigen: Frankreich oder England. Ich kann mich nicht in zwei Hälften reißen, um zwei Aufgaben gleichzeitig zu erledigen. Natürlich wird auch Münze benötigt, um Bestechungsgelder zu machen. Zögere nicht, mich um Hilfe zu bitten, wenn du meine Bedingungen akzeptierst.";
			link.l1 = "Danke, Fadey. Das werde ich im Kopf behalten.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "relation":
			rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.FadeyNation), 0));
			if (rate <= 10)
			{
				dialog.text = "Natürlich. Ich habe sicherlich von Ihren Abenteuern - oder Missgeschicken - gehört. Ich kann mich um Ihr kleines Problem kümmern, nichts, was nicht die richtige Menge an Gold in den richtigen Händen lösen könnte. Drei hundert Gold-Dublonen und ich ziehe Sie aus der Patsche.";
				if (PCharDublonsTotal() >= 300) // belamour legendary edition
				{
					link.l1 = "Großartig! Hier ist das Gold.";
					link.l1.go = "agree";
					iTotalTemp = 300;
				}
				link.l2 = "Dann ist es gerade die richtige Zeit für mich, die Münzen zu holen.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate <= 20)
				{
					dialog.text = "Natürlich. Ich habe sicherlich von deinen Abenteuern - oder Missgeschicken gehört. Ich kann mich um dein kleines Problem kümmern, nichts, was die richtige Menge Gold in den richtigen Händen nicht beheben könnte. Sechshundert goldene Dublonen und ich ziehe dich aus der Patsche.";
					if (PCharDublonsTotal() >= 600) // belamour legendary edition
					{
						link.l1 = "Großartig! Hier ist das Gold.";
						link.l1.go = "agree";
						iTotalTemp = 600;
					}
					link.l2 = "Dann ist es gerade die richtige Zeit für mich, die Münzen zu holen.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Ja, du steckst wirklich in der Klemme! Ich kann diese Situation nicht vollständig klären. Allerdings kann ich den Schlag des Donners, der gleich auf deinen sündigen Kopf herabfallen wird, abmildern. Und später, zu jedem beliebigen Zeitpunkt, können wir erneut ein Bestechungsgeld präsentieren, wenn du das Geld und den Wunsch hast. Siebenhundert Gold-Dublonen und ich kann anfangen, deine Probleme zu glätten.";
					if (PCharDublonsTotal() >= 700) // belamour legendary edition
					{
						link.l1 = "Ich habe es satt, von den Piratenjägern gejagt zu werden. Hier ist das Gold.";
						link.l1.go = "agree";
						iTotalTemp = 700;
					}
					link.l2 = "Dann ist es genau der richtige Zeitpunkt für mich, die Münzen zu holen.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iTotalTemp); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Gut, gib mir etwa zehn bis fünfzehn Tage. In der Zwischenzeit mache ich einen Termin und kümmere mich um dies und das. Alles wird in etwa zwei Wochen erledigt sein. ";
			link.l1 = "Danke dir, Fadey! Ich werde warten...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
			SetFunctionTimerCondition("ChangeNationRelationFromFadeyComplete", 0, 0, 10+rand(5), false);
			pchar.GenQuest.FadeyNation.Rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.FadeyNation), 0));
			npchar.quest.relation = "true";
		break;
		
		case "contraband":
			dialog.Text = "Warum hast du sie verärgert, mein guter Mann? Die Schmuggler sind nicht die schlechtesten Leute in dieser Gegend der Welt und sie können dir einen guten Gewinn bringen. Gut, ich werde dir helfen, ich weiß, wie man sie beschwichtigt... Das macht siebenhundert Dublonen, kein Feilschen.";
			if (PCharDublonsTotal() >= 700) // belamour legendary edition
			{
				Link.l1 = "Sehr gut, Fadey, ich stimme zu. Nimm dein Gold.";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "Ich habe jetzt nicht so viel Gold bei mir. Ich komme später wieder!";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Gut, ich werde den Streit beilegen, mach dir keine Sorgen. Sie werden wieder Geschäfte mit dir machen, genau wie in alten Zeiten.";
			Link.l1 = "Danke dir!";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			RemoveDublonsFromPCharTotal(700); // belamour legendary edition
			PlaySound("interface\important_item.wav");
		break;
		
		case "UpgradeRopes":
			dialog.text = "Ho-ho, ich sehe, dass Ihr Geschäft blüht und die Gelüste wachsen! Ihr habt recht, unsere Waren sind fein und die Preise nicht zu hoch. Bedenkt aber, dass Investitionen notwendig sind! Solch ein Geschäft erfordert einen ernsten Ansatz, um alles perfekt zu machen.";
			link.l1 = "Hätte ich Ihnen ein solches Angebot gemacht, ohne ein paar hundert Dublonen in Reserve zu haben?";
			link.l1.go = "UpgradeRopes_1";
		break;
		
		case "UpgradeRopes_1":
			dialog.text = "Ich weiß, dass du Münzen in deiner Truhe hast, und nicht nur ein paar, sicherlich würden fünfzig passen! Aber unser Geschäft ist nicht gewöhnlich - es geht nicht nur darum, Waren zu bewegen, sondern einen Weg zu finden... sagen wir mal, diskret. Für solch ein Ausmaß musst du schwer investieren, nicht nur zahlen, um es profitabel zu machen! Und um sicherzustellen, dass dein Geld nicht in Luft aufgeht. Wenn du bereit bist, dich von dreitausend Gold-Dublonen zu trennen, dann nimm mein Wort, dass alles richtig für dich gemacht wird, als ein guter Freund, und wir werden dich beim Preis nicht über's Ohr hauen.";
			if (PCharDublonsTotal() >= 3000)
			{
				Link.l1 = "Dreitausend Dublonen! Nun, ich muss zugeben, dass man ein solch großzügiges Angebot selbst bei den wohlhabendsten Kaufleuten, selbst in den fantastischsten Geschichten, selten hört! Wenige sind bereit, so großzügig in ein solches Unternehmen zu investieren. Aber ich, glücklicherweise, gehöre zu ihrer Zahl. Hier ist dein Geld, Monsieur Fadey.";
				Link.l1.go = "UpgradeRopes_Agreed";
			}
			Link.l2 = "Dreitausend Gold-Dukaten! Ich bin nicht bereit für eine solche Summe, Fadey. Leider. Ich komme später zurück.";
			Link.l2.go = "UpgradeRopes_Potom";
			link.l3 = "Dreitausend, sagst du? Nun... Um die Wahrheit zu sagen, eine solche Summe gebietet Respekt vor deinem Ehrgeiz. Aber ich muss zugeben - das ist nichts für mich.";
			link.l3.go = "UpgradeRopes_2";
		break;
		
		case "UpgradeRopes_2":
			dialog.text = "Welch eine Wendung! Du kommst mit einem Angebot, dann ziehst du sofort zurück! Ich gebe zu, ich bin enttäuscht, aber werde unsere Freundschaft nicht fallen lassen. Lassen wir es wie zuvor: unser früherer Vertrag besteht weiterhin - fünfzig Spulen zu je zehn Dublonen, jeden Monat, am 20.";
			link.l1 = "Gut, dass du mich verstehst, Fadey. Ich würde meine Meinung gerne ändern, aber solche Ausgaben übersteigen meine Möglichkeiten. Ach, meine Mittel sind in dieser Angelegenheit begrenzt.";
			link.l1.go = "UpgradeRopes_3";
		break;
		
		case "UpgradeRopes_3":
			dialog.text = "Nun, wenn das deine Entscheidung ist, gibt es nichts mehr zu besprechen. Diese Wendung wird unsere Freundschaft nicht beeinflussen. Besuche uns, "+GetSexPhrase("guter Herr","schöne Dame")+".";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "exit";
			pchar.questTemp.FadeyRopesBlock = true;
		break;
		
		case "UpgradeRopes_Potom":
			DialogExit();
			pchar.questTemp.FadeyRopesBlock = true;
			pchar.questTemp.FadeyRopesPotom = true;
		break;
		
		case "UpgradeRopes_Agreed":
			dialog.text = "Jetzt ist das vernünftig! Du bist nicht einer für leeres Gerede, sondern weißt, wie man handelt. Für Geschäftsleute wie dich gibt es immer einen Rabatt zu finden! Fünfzehn Prozent Rabatt auf alle zukünftigen Sendungen! Hier ist unser Deal: 250 Rollen Hanfseil werde ich jeden Monat für dich bereithalten. Du kannst sie, wie zuvor, am 20. abholen, zahlst 2125 Dublonen für alles, ohne Rest.";
			link.l1 = "Perfekt, Fadey! Du bist bemerkenswert einfach zu handeln. Ich bin sicher, der Erfolg erwartet uns. Bis zum nächsten Mal!";
			link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "2_1");
			pchar.questTemp.UpgradeRopes = true;
			pchar.questTemp.FadeyRopesBlock = true;
			DeleteAttribute(pchar, "questTemp.FadeyRopesPotom");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}