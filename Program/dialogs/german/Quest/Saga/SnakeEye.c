// шаман команчей Змеиный Глаз
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "calendar")
			{
				dialog.text = "Grüße, mein blasser Freund.";
				link.l2 = "Ich bin auch froh, dich zu sehen, Rothaut-Bruder. Ich habe wieder wichtige Geschäfte für dich.";
				link.l2.go = "calendar";
				break;
			}
			dialog.text = "Grüße, mein blasser Freund.";
			link.l1 = "Ich freue mich auch, dich zu sehen, Snake Eye.";
			link.l1.go = "exit";
			if (CheckAttribute(npchar, "quest.amulet") && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Indian) && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Amulet) && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Obereg))
			{
				link.l2 = "Ich habe dir die Amulette gebracht, nach denen du gefragt hast. Lassen uns handeln.";
				link.l2.go = "SnakeEye_potion";
			}
			if (CheckAttribute(pchar, "questTemp.LSC")) // был в LSC
			{
				if (CheckAttribute(npchar, "quest.LSC_hello") && CheckCharacterItem(pchar, "buben"))
				{
					link.l2 = "Ich habe deine Tamburin gefunden, Snake Eye. Schau es dir an.";
					link.l2.go = "LSC_buben";
				}
				if (CheckAttribute(npchar, "quest.LSC_tube") && CheckCharacterItem(pchar, "smoking_tube"))
				{
					link.l2 = "Ich habe eine interessante Indianerpfeife gefunden, Snake Eye. Schau mal.";
					link.l2.go = "LSC_tube";
				}
				if (!CheckAttribute(npchar, "quest.LSC_hello"))
				{
					link.l2 = "Hallo, Schamane. Ich habe die Statue benutzt und eine unglaubliche Reise erlebt. Du hattest vollkommen recht. Ich habe den Schiffsfriedhof, den weißen Kapitän und sogar den Laderaum mit den Vorräten gefunden!";
					link.l2.go = "LSC_hello";
				}
				if (CheckAttribute(npchar, "quest.LSC_hello") && pchar.questTemp.Saga.BaronReturn == "shamane")
				{
					link.l3 = "Snake Eye, ich brauche deine Hilfe.";
					link.l3.go = "Saga_nathaniel";
				}
			}		
			NextDiag.TempNode = "First time";
		break;
		
	//---------------------------------------- первая встреча------------------------------------------------
		case "SnakeEye":
			dialog.text = "Grüße, mein blasser Freund.";
			link.l1 = "Hallo, Schamane. Warum nimmst du an, dass ich dein Freund bin?";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "Ich weiß viel, aber ich weiß nicht immer genau was. Du bist mit einem Zweck hierher gekommen. Das Schicksal hat dich hierher geführt und ich helfe dir.";
			link.l1 = "Gut zu wissen! Ich bin tatsächlich hier um deine Hilfe zu bitten, mein Rothaut-Freund. Ich komme gleich zur Sache: Was meintest du, als du die Frau von Hawk über Kukulcan erzählt hast?";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "Sogar tote Fische treiben ab. Und der lebende Mensch wird vom Schicksal von Ziel zu Ziel geführt. Das Ziel des gefesselten Kapitäns, der von bösen Menschen in der Selva gejagt wurde, war die Kukulcan-Statue. Wenn er sich selbst opfert, kann er weit weg von hier sein.";
			link.l1 = "Ich habe kein Wort verstanden. Worum geht es bei der Statue deines Gottes und wie konnte Hawk so weit zu Fuß gehen, dass ihn jetzt niemand finden kann?";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "Wenn Kukulcan den Hawk gefressen hat, könnte er ihn überall ausspucken. Vielleicht sogar in einer anderen Welt. Kukulcan hat mich dreimal gefressen. Und jedes Mal war ich an verschiedenen Orten. Vor langer Zeit bin ich hierher gekommen und habe beschlossen, kein Risiko mehr einzugehen. Ich bin nicht in Kukulcans Mund gegangen und ich weiß nicht, wo er seine Opfer ausspuckt.";
			link.l1 = "Jesus, das geht über mein Verständnis hinaus! Sagst du mir, dass die Steinidole Menschen weit weg teleportieren können?";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "Nicht nur das. Kukulcan beherrscht nicht nur den Raum, sondern auch die Zeit. Oder sogar mehr. Ich erzählte dem gefesselten Kapitän von der goldenen Statue, die Menschen frisst. Vielleicht hat er sich entschieden zu riskieren, als er sah, dass die Verfolger nahe waren...";
			link.l1 = "Warte, die Statue ist aus Stein. Und du sprichst von einer goldenen...";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "Um Mitternacht beginnt das Idol zu leben und wird zu Gold. In diesem Moment lebt der Geist von Kukulcan in ihm. Fürchte dich, ihm nahe zu kommen, sonst könntest du den Sonnenaufgang an einem anderen Ort sehen. Sogar die Sterne können ihre Plätze am Himmel wechseln. Du triffst diejenigen, die noch nicht geboren wurden, oder siehst die Geburt von denen, die schon lange gestorben sind oder überhaupt nicht geboren wurden.";
			link.l1 = "Was zum... Rätsel und nochmals Rätsel... Du faszinierst mich, Snake Eye. Du hast gesagt, dass du drei Begegnungen mit Kukulcan, dem Gott an den du glaubst, überlebt hast. Warum versuche ich nicht mein Glück mit dem Idol des Gottes, an den ich nicht glaube?";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "Schade. Schade, dass du nicht glaubst. Vielleicht hat Kukulcan dich selbst gerufen und dich veranlasst, das Land deiner Vorfahren zu verlassen. Aber du hörst ihn noch nicht. Alles geschieht aus gutem Grund. Wenn du dich entscheidest zu riskieren, dann musst du wissen, dass ich jedes Mal nur überlebt habe, weil ich wunderbare Comanche-Tränke hatte.";
			link.l1 = "Comanche? Ist das ein anderer Stamm?";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "So nennen Feinde mein Volk, das ich nie wieder sehen werde. Der Trank stellt Kraft und Ausdauer wieder her, heilt auch und schützt dich vor starken Giften. Du brauchst mehrere Flaschen, aber ich habe nur noch drei übrig.\nEs gab vier Flaschen, aber ich habe eine an einem seltsamen Ort verloren, es sieht aus wie ein Friedhof der Schiffe der Weißen. Dort begann meine Reise in dieser Welt. Vielleicht hat Kukulcan den Kapitän dort ausgespuckt. Wenn das so ist, beneide ich ihn nicht.";
			link.l1 = "Was ist das für ein Ort? Der Schiffsfriedhof?";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "Seltsamer Ort... Er sollte nicht existieren, aber er existiert. Menschen, die wegen der Hautfarbe töten, leben dort. Sie bewahren ihre Vorräte in einem großen Schiff auf, wo Kukulcan mich ausgespuckt hat. Ich bin nicht in seinen Frachtraum gegangen, den sie vor Dieben schützen, sie sind keine vertrauenswürdigen Nachbarn. Wenn du dorthin gelangst - finde einen anderen Ausgang, geh nicht in den Frachtraum oder es gibt Ärger.\nWeißer Junge hilft dir eine weitere Statue zu finden, wenn er noch lebt. Gib ihm diese weiße Perle. Er mag sie.";
			link.l1 = "Hm. Mein Kopf dreht sich schon und das wird immer interessanter. Mach weiter, Rothaut Bruder.";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			Log_Info("Du hast eine weiße Perle erhalten");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "jewelry52");
			dialog.text = "Wenn du den Kapitän lebend findest, könnte er sehr krank sein. Ich hatte keine Zeit, ihm den Trank zu geben. Such dort nach meiner Tamburin. Ich habe sie von meinem Großvater bekommen. Es gibt viele Dinge in der Tasche, die ich verloren habe, aber ich brauche nur die Tamburin. Es ist schwierig, ohne sie mit den Geistern zu sprechen.";
			link.l1 = "Nun, dieser Ort klingt sehr interessant! Hoffen wir, dass Hawk dorthin teleportiert wurde... Gibst du mir deinen Trank?";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "Ich werde es dir geben. Aber du gibst mir im Austausch drei lokale Amulette: "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Indian)+", "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Amulet)+" und "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Obereg)+". Eine Flasche für jedes Amulett. So ist es fair. Komm zurück, wenn du alle Amulette hast. Dann tauschen wir sie aus. Denk nicht, dass ich gierig bin. Oder, vielleicht überdenkst du es, während du nach Amuletten suchst.";
			link.l1 = "Ich werde nicht so denken. Warte auf mich, Snake Eye, ich komme bald zurück.";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			npchar.quest.amulet = "true";
			AddQuestRecord("BaronReturn", "3");
			AddQuestUserData("BaronReturn", "sItem1", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Indian));
			AddQuestUserData("BaronReturn", "sItem2", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Amulet));
			AddQuestUserData("BaronReturn", "sItem3", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Obereg));
			sld = characterFromId("Danielle");
			sld.quest.talk = "SnakeEye";
			pchar.quest.BaronReturn_out.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BaronReturn_out.win_condition.l1.location = pchar.location;
			pchar.quest.BaronReturn_out.function = "Saga_DannyTalk";
			pchar.questTemp.HelenDrinking.GiveAmulets = true;
			
			//if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap4_Start"))
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway"))	// Временно так
			{
				// Квест "Путеводная звезда", начало 4 этапа
				PChar.quest.PZ_Etap4_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap4_Start.win_condition.l1.location = "Shore9";
				PChar.quest.PZ_Etap4_Start.win_condition = "PZ_Etap4_Start";
				locations[FindLocation("Shore9")].DisableEncounters = true;
			}
		break;
		
		// даёт зелья - идем на телепортацию
		case "SnakeEye_potion":
			dialog.text = "Gut, mein Freund. Hast du mir Amulette gebracht, damit du zu Kukulcan gehen kannst?";
			link.l1 = "Ja. Ich bin bereit, dieselbe Reise zu unternehmen, die Nathaniel, der gefesselte Kapitän, getan hat.";
			link.l1.go = "SnakeEye_potion_1";
		break;
		
		case "SnakeEye_potion_1":
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Indian, 1);
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Amulet, 1);
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Obereg, 1);
			TakeNItems(pchar, "Ultimate_potion", 3);
			Log_Info("Du hast die Amulette gegeben");
			Log_Info("Du hast drei vielseitige Tränke erhalten");
			PlaySound("interface\important_item.wav");
			dialog.text = "Nimm diese Tränke. Denke daran, dass du einen sofort nach dem Ausspucken durch Kukulcan trinken musst, sonst stirbst du oder bleibst sehr, sehr krank. Denke auch daran, nicht in den Laderaum zu gehen, wo die Bleichgesichter ihre Vorräte lagern. Es gibt einen anderen Weg, das Schiff zu verlassen. Tatsächlich gibt es zwei Wege. Finde die rote Frau in der ersten Nacht, das ist sehr wichtig. Das ist alles, was ich dir sagen kann.";
			link.l1 = "Ich werde das im Kopf behalten, Rothaut-Bruder.";
			link.l1.go = "SnakeEye_potion_2";
		break;
		
		case "SnakeEye_potion_2":
			dialog.text = "Dann geh. Berühre Kukulcan um Mitternacht und es wird dich fressen. Ich werde Geister rufen, um dich zu führen.";
			link.l1 = "Danke dir, Snake Eye. Mach dir keine Sorgen um mich, alles wird gut gehen. Wir werden uns wiedersehen!";
			link.l1.go = "SnakeEye_potion_3";
		break;
		
		case "SnakeEye_potion_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			pchar.questTemp.Saga.BaronReturn = "first_teleport";
			pchar.questTemp.Dolly = true; // телепорты работают!
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", true); // не пускать офицеров в локу телепорта
			DeleteAttribute(npchar, "quest.amulet");
			AddQuestRecord("BaronReturn", "4");
			sld = characterFromId("Danielle");
			sld.quest.talk = "teleport";
			pchar.quest.BaronReturn_out1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BaronReturn_out1.win_condition.l1.location = pchar.location;
			pchar.quest.BaronReturn_out1.function = "Saga_DannyTalk";
			QuestPointerToLoc("Pearl_Jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("Pearl_Jungle_03", "camera", "dolly");
		break;
		
		// пришёл из LSC
		case "LSC_hello":
			dialog.text = "Ich freue mich, dich zu sehen, mein Freund. Wie bist du vom Schiffsfriedhof zurückgekehrt?";
			link.l1 = "Ich habe die Statue von Kukulcan dort gefunden, genau wie du es mir gesagt hast. Der Weiße Junge hat mir geholfen - Ole Christiansen. Die Statue war im Meer versunken, aber ich konnte sie erreichen. Sie hat mich in ein indisches Dorf auf Dominica teleportiert.";
			link.l1.go = "LSC_hello_1";
			npchar.quest.LSC_hello = "true";
		break;
		
		case "LSC_hello_1":
			dialog.text = "Hat Monkitekuvri dich dort getroffen?";
			link.l1 = "Hm. Monkitekuvri? Wer ist das?";
			link.l1.go = "LSC_hello_2";
		break;
		
		case "LSC_hello_2":
			dialog.text = "Er ist der Dorfhäuptling.";
			link.l1 = "Ich habe nicht nach seinem Namen gefragt. Vielleicht war er Monkitekuvri, vielleicht nicht.";
			link.l1.go = "LSC_hello_3";
		break;
		
		case "LSC_hello_3":
			dialog.text = "Hatte er einen prächtigen Kopfschmuck aus Vogelfedern auf dem Kopf?";
			link.l1 = "Sicher, hatte er. Eine Menge Federn... Es scheint, dass er alle Papageien im Dschungel gerupft hat.";
			link.l1.go = "LSC_hello_4";
		break;
		
		case "LSC_hello_4":
			dialog.text = "Er heißt Monkitekuvri. Es sind keine Papageienfedern, sondern Adlerfedern. Dieser Kopfschmuck ist mein Kopfschmuck. Ich habe ihn Monkitekuvri präsentiert, als Kukulcan mich wieder ausspuckte. Dann brachten sie mich zu einer anderen Statue...";
			link.l1 = "Ist das nicht etwas! Sie haben mich auch 'Kukulcan geopfert'! Und ich habe mich hier gefunden, in der Nähe der ersten Statue.";
			link.l1.go = "LSC_hello_5";
		break;
		
		case "LSC_hello_5":
			dialog.text = "Ja, mein bleicher Freund. Meine Reise endete auch hier.";
			link.l1 = "Die Idole teleportieren im Kreis... Aber was ist der Sinn davon? Hast du irgendwelche Ideen, Snake Eye?";
			link.l1.go = "LSC_hello_6";
		break;
		
		case "LSC_hello_6":
			dialog.text = "Ich vermute, dass die Statuen nicht richtig funktionieren. Momentan bewegen sie Leute herum, aber sie sollten sie an einen Ort bringen. Etwas an ihnen ist kaputt.";
			link.l1 = "Was lässt dich so denken?";
			link.l1.go = "LSC_hello_7";
		break;
		
		case "LSC_hello_7":
			dialog.text = "Weil Teleportation im Kreis keinen Sinn hat. Kukulcan muss alle Opfer an einen Ort bringen und sie nicht herumbewegen.";
			link.l1 = "Und wo könnte dieser eine Ort sein?";
			link.l1.go = "LSC_hello_8";
		break;
		
		case "LSC_hello_8":
			dialog.text = "Das ist ein großes Geheimnis, weißer Bruder, selbst für mich.";
			link.l1 = "Ich verstehe. Gut, zum Teufel mit den Idolen. Ich werde ihnen nie wieder nahe kommen. Ich habe den angeketteten Kapitän gefunden, es besteht keine Notwendigkeit mehr, durch die Portale zu reisen.";
			link.l1.go = "LSC_hello_9";
			AddQuestRecord("BaronReturn", "12");
		break;
		
		case "LSC_hello_9":
			dialog.text = "Wenn du auf dem Schiffsfriedhof warst. Hast du dort mein Tamburin gefunden?";
			if (CheckCharacterItem(pchar, "buben"))
			{
				link.l1 = "Ich denke schon. Schau mal.";
				link.l1.go = "LSC_buben";
			}
			else
			{
				link.l1 = "Nein. Leider habe ich es nicht gefunden. Aber ich weiß, wo die Insel ist und ich kann sie erreichen. Ich werde nach deiner Tamburin suchen.";
				link.l1.go = "LSC_hello_10";
			}
		break;
		
		case "LSC_hello_10":
			dialog.text = "Such danach, mein blasser Freund. Ich bitte dich inständig. Ohne mein Tamburin höre ich die Geister nicht gut.";
			link.l1 = "In Ordnung, Snake Eye. Wir sehen uns!";
			link.l1.go = "exit";
		break;
		
		case "LSC_buben":
			RemoveItems(pchar, "buben", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Das ist mein Tamburin. Danke, mein blasser Freund. Ich kann dich belohnen. Ich überreiche dir diese Waffe, welche dein Volk noch lange nicht haben wird. Diese Waffe ist die Waffe der Bleichgesichter meiner Zeit.";
			link.l1 = "Interessant! Zeig es mir, Rothaut Freund...";
			link.l1.go = "LSC_buben_1";
		break;
		
		case "LSC_buben_1":
			GiveItem2Character(pchar, "pistol7");
			Log_Info("Du hast einen Colt-Revolver erhalten");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 3);
			dialog.text = "Nimm es. Es sind nur noch drei Ladungen darin, den Rest habe ich benutzt. Aber vielleicht lernst du, Ladungen dafür zu machen. Ich habe einige Dutzend Teile für Ladungen auf dem Schiffsfriedhof verloren, du kannst sie dort finden.";
			link.l1 = "Ohoho! Das ist eine Pistole! Ich habe noch nie so etwas gesehen... was für eine seltsame Maschine? Ein Drehmechanismus... fünf Ladungen! Schön!";
			link.l1.go = "LSC_buben_2";
		break;
		
		case "LSC_buben_2":
			dialog.text = "Es heißt Colt Revolver. Keine andere Pistole wie diese zu deiner Zeit. Einfach zu bedienen, den Hahn heben und den Abzug ziehen. Es schießt gut.";
			link.l1 = "Danke! Danke, Snake Eye! Es wird eine nette Überraschung für meine Feinde sein... Schade, dass es nur drei Ladungen gibt...";
			link.l1.go = "LSC_buben_3";
		break;
		
		case "LSC_buben_3":
			dialog.text = "Versuche dir selbst beizubringen, wie man Ladungen für den Colt-Revolver herstellt. Dann wirst du ein großer Krieger deiner Zeit sein. Ach, mein blasser Bruder, ich vergaß dich zu bitten, meine Pfeife auf dem Schiffsfriedhof zu finden. Es war eine sehr hübsche Pfeife.";
			if (CheckCharacterItem(pchar, "smoking_tube"))
			{
				link.l1 = "Ha! Und ich habe mich gefragt, wem diese bemalte Pfeife gehören könnte? Schau mal.";
				link.l1.go = "LSC_tube";
			}
			else
			{
				link.l1 = "Gut. Ich werde auch nach deiner Pfeife suchen. Bis dann!";
				link.l1.go = "exit";
			}
			npchar.quest.LSC_tube = "true";
		break;
		
		case "LSC_tube":
			RemoveItems(pchar, "smoking_tube", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Das ist meine Pfeife, mein Bruder. Ich bin froh, dass du sie gefunden hast. Und ich kann dir ein weiteres Geschenk dafür geben. Das ist ein kluges Buch der Bleichgesichter aus meiner Zeit. Ich kann es nicht verstehen. Versuche, einen klugen Mann zu finden, der dieses Buch lesen und verstehen kann.";
			link.l1 = "Danke dir, Snake Eye. Ich glaube, ich kenne jemanden, der sich dafür interessieren wird.";
			link.l1.go = "LSC_tube_1";
		break;
		
		case "LSC_tube_1":
			GiveItem2Character(pchar, "chemistry");
			Log_Info("Du hast ein Lehrbuch der Chemie von Lavoisier erhalten");
			PlaySound("interface\important_item.wav");
			dialog.text = "Gib es ihm, weißer Bruder. Dieses Buch birgt große Geheimnisse der Bleichgesichts-Weisheit.";
			link.l1 = "Gut. Auf Wiedersehen, Snake Eye!";
			link.l1.go = "exit";
		break;
		
		// лечение Натаниэля
		case "Saga_nathaniel":
			dialog.text = "Ich höre dir zu, bleichgesichtiger Bruder.";
			link.l1 = "Ich habe den gefesselten Kapitän, den ich auf dem Schiffsfriedhof gesucht habe, mitgebracht. Er ist sehr krank. Ich weiß, dass nur du ihn heilen kannst...";
			link.l1.go = "Saga_nathaniel_1";
		break;
		
		case "Saga_nathaniel_1":
			dialog.text = "Kukulcan hat seine Gesundheit verschlungen. Ich denke, ich kann ihm helfen, sich zu erholen. Aber es dauert nicht weniger als einen vollen Mond. Kukulcan hat den Kapitän vor langer Zeit gefressen und die Krankheit hat sich tief in ihm ausgebreitet.";
			link.l1 = "Bitte heile ihn, Schamane! Ich bringe dir, was auch immer du brauchst!";
			link.l1.go = "Saga_nathaniel_2";
		break;
		
		case "Saga_nathaniel_2":
			dialog.text = "Ich werde es versuchen, weißer Bruder. Du musst mir nichts bringen. Ich habe alles. Die Zeit macht die Krankheit stärker, aber der gefesselte Kapitän wird in einem Mond wieder gesund sein.";
			link.l1 = "Danke dir, rothäutiger Bruder. Du bist wieder einmal mein Lebensretter.";
			link.l1.go = "Saga_nathaniel_3";
		break;
		
		case "Saga_nathaniel_3":
			dialog.text = "Hinterlasse den gefesselten Kapitän in meiner Hütte, weißer Bruder, und gehe ohne Sorge. Nimm auch seine Frau mit, niemand darf meine Riten sehen.";
			link.l1 = "Gut, Snake Eye. Ich nehme Danielle mit mir. Bis dann!";
			link.l1.go = "Saga_nathaniel_4";
		break;
		
		case "Saga_nathaniel_4":
			DialogExit();
			pchar.questTemp.Saga.BaronReturn = "treatment";
			sld = characterFromId("Nathaniel");
			RemovePassenger(Pchar, sld);
			LAi_SetStayType(sld);
			sld.location = "none";
			pchar.quest.Saga_NatanTreatment1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Saga_NatanTreatment1.win_condition.l1.location = pchar.location;
			pchar.quest.Saga_NatanTreatment1.function = "Saga_NatanTreatment";
		break;
		
		case "calendar":
			dialog.text = "Ich höre zu, mein Freund.";
			link.l1 = "Erinnerst du dich an unser Gespräch über die Kukulcan-Statuen? Du hast gesagt 'sie sollten Menschen an einen besonderen Ort bewegen'.";
			link.l1.go = "calendar_1";
		break;
		
		case "calendar_1":
			dialog.text = "Ich erinnere mich, weißer Kapitän.";
			link.l1 = "Ich weiß, wohin diese Statuen die Menschen gebracht haben müssen, die von Kukulcan gefressen wurden.";
			link.l1.go = "calendar_2";
		break;
		
		case "calendar_2":
			dialog.text = "Wo?";
			link.l1 = "Zur alten Maya-Stadt Tayasal. Sie befindet sich tief im Dschungel von Main.";
			link.l1.go = "calendar_3";
		break;
		
		case "calendar_3":
			dialog.text = "Sehr interessant. Wie wissen Sie das?";
			link.l1 = "Es ist eine lange Geschichte, Snake Eye. Ich verstehe auch, wie du hierher gekommen bist. Du bist noch nicht einmal geboren, oder?";
			link.l1.go = "calendar_4";
		break;
		
		case "calendar_4":
			dialog.text = "Sogar mein Vater ist nicht in Eurer Zeit geboren. Aber ich lebe in Eurer Zeit und das ist ein großes Geheimnis.";
			link.l1 = "Es ist tatsächlich erklärbar. Ein Itza-Priester namens Kanek, der in Tayasal lebt, rief Kukulcan dazu auf, als Sterblicher in dieser Welt geboren zu werden und die Weisheit der weißen Rasse aufzunehmen. Er erschuf auch ein Zeitloch, das einige Männer aus der Zukunft in unsere Zeit teleportierte...";
			link.l1.go = "calendar_5";
		break;
		
		case "calendar_5":
			dialog.text = "Um Kukulcan die Weisheit der zukünftigen Menschen aufnehmen zu lassen?";
			link.l1 = "Ja. Und Kukulcan plant, in die Vergangenheit zu reisen, um das Wissen den Maya-Leuten zu überbringen, die vor langer Zeit gestorben sind. Die Geschichte wird sich ändern und die Maya werden über Amerika und vielleicht sogar mehr herrschen...";
			link.l1.go = "calendar_6";
		break;
		
		case "calendar_6":
			dialog.text = "";
			link.l1 = "Aber etwas ist mit den Portalen passiert und sie haben angefangen, Menschen im Kreis anstatt nach Tayasal zu teleportieren. Und deshalb bin ich hier, ich brauche deinen Rat, Snake Eye.";
			link.l1.go = "calendar_7";
		break;
		
		case "calendar_7":
			dialog.text = "Warum ich, weißer Kapitän?";
			link.l1 = "Weil du von Kukulcan gefressen wurdest. Und weil die Kukulcan-Statue in der Nähe deines Dorfes eine seltsame Markierung auf dieser Karte hat, die stark mit Kaneks Ritualen verbunden ist.";
			link.l1.go = "calendar_8";
		break;
		
		case "calendar_8":
			dialog.text = "Zeig mir diese Karte?";
			link.l1 = "Hier, schau mal...";
			link.l1.go = "calendar_9";
		break;
		
		case "calendar_9":
			RemoveItems(pchar, "skinmap", 1);
			dialog.text = "(blickend) Dieses runde Zeichen, ja? Und was bedeutet es?";
			link.l1 = "Ich weiß es nicht, Schamane. Ich weiß nur, dass nur eine der drei Kukulcan-Statuen dieses Zeichen hat. Und dass die Statue mit dem Zeichen die deine ist. Ich schließe daraus, dass deine Statue eine besondere ist. Hast du irgendwelche Ideen?";
			link.l1.go = "calendar_10";
		break;
		
		case "calendar_10":
			dialog.text = "Gib mir Zeit bis morgen früh, weißer Bruder. Lass mir diese Lederkarte. Ich muss die Geister fragen. Komm morgen zurück.";
			link.l1 = "Gut, Rothaut Bruder. Ich werde morgen hier sein. Danke für deine Hilfe.";
			link.l1.go = "calendar_11";
		break;
		
		case "calendar_11":
			DialogExit();
			SetFunctionTimerCondition("Tieyasal_CalendarThink", 0, 0, 1, false);
			pchar.questTemp.Tieyasal = "calendar_think";
			NextDiag.CurrentNode = "calendar_wait";
		break;
		
		case "calendar_wait":
			dialog.text = "Komm später, weißer Bruder. Belästige mich jetzt nicht.";
			link.l1 = "Sicher, Schamane...";
			link.l1.go = "exit";
			NextDiag.TempNode = "calendar_wait";
		break;
		
		case "calendar_12":
			dialog.text = "Ich muss dir etwas sagen, weißer Bruder.";
			link.l1 = "Hast du etwas gefunden? Oder hast du eine Vermutung?";
			link.l1.go = "calendar_13";
		break;
		
		case "calendar_13":
			dialog.text = "Ahnengeister gaben mir Vision und ich ging mit Karte zu Kukulcan. Ich suchte und fand. Es muss sein, wonach du suchst, weißer Bruder.";
			link.l1 = "Was hast du gefunden?";
			link.l1.go = "calendar_14";
		break;
		
		case "calendar_14":
			dialog.text = "Die Kukulcan-Statue hat zwei Eisenklammern und eine Vertiefung. Die Vertiefung hat eine runde, glatte Form. Sie ist auf das runde und flache Objekt von Ihrer Ledertkarte ausgerichtet.";
			link.l1 = "Was ist es?";
			link.l1.go = "calendar_15";
		break;
		
		case "calendar_15":
			dialog.text = "Ich weiß es nicht. Ich weiß nur, dass es rund, flach ist, ungefähr so groß wie ein kleiner Kürbis und vielleicht so dick wie ein Finger. Du kannst selbst nach der Aussparung und den Klemmen schauen. Die Klemme muss es halten können.";
			link.l1 = "Hast du eine Ahnung? Oder eine Vermutung, was es sein könnte?";
			link.l1.go = "calendar_16";
		break;
		
		case "calendar_16":
			dialog.text = "Stein hat eine Spur von Feuer. Ich weiß, was damit passiert ist. Himmelsflamme hat ihn getroffen.";
			link.l1 = "Blitz? Hat der Blitz es getroffen?";
			link.l1.go = "calendar_17";
		break;
		
		case "calendar_17":
			dialog.text = "Ich bin mir sicher. Ich habe Miskito nach diesem Idol gefragt. Ein Krieger sagte, dass vor langer Zeit einige hübsch bemalte Dinge an der Statue zu sehen waren. Sehr ähnlich zu Steinen. Er erzählte mir, dass es sehr hübsche rote Steine waren. Ein weißer Mann aus dem weißen Dorf hat sie gekauft.";
			link.l1 = "Hm. Soweit ich verstehe, scheint es, dass der Blitz dieses runde 'Etwas' getroffen hat, es in Stücke zerbrach und dann wurden diese Stücke an irgendeinen weißen Kerl verkauft?";
			link.l1.go = "calendar_18";
		break;
		
		case "calendar_18":
			dialog.text = "Es scheint so.";
			link.l1 = "Und wer war dieser weiße Mann? Hat dir dein Krieger davon erzählt?";
			link.l1.go = "calendar_19";
		break;
		
		case "calendar_19":
			dialog.text = "Er hat es mir gesagt. Er war ein großer Freund von Miskito und er lebt im Dorf Blueweld. Sein Name ist Forest Devil. Ich kenne ihn, du musst ihn auch kennen.";
			link.l1 = "Jan Svenson? Warte mal... rot bemalte Steine, sagst du? Es sieht so aus, als ob ich gerade sehr viel Glück hatte. Schau mal, Schamane, schau dir diese roten Steine an, die ich habe! Der Forest Devil hat sie mir geschenkt.";
			link.l1.go = "calendar_20";
		break;
		
		case "calendar_20":
			Log_Info("Du hast die ornamentale Musterfragmente gegeben");
			RemoveItems(pchar, "splinter_js", 1);
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			dialog.text = "Das müssen sie sein. Fünf Steine. Schau mal, weißer Bruder. Wenn du sie so anordnest... (zusammenfügt)";
			link.l1 = "...";
			link.l1.go = "calendar_21";
		break;
		
		case "calendar_21":
			dialog.text = "... dann haben wir Rundgegenstand. Schau! Sie passen zusammen. Es war früher ein Gegenstand.";
			link.l1 = "Verdammt! Und diese Dinge waren so lange in meiner Tasche... Hör zu, Schamane, wenn ich die Scherben in die Vertiefung lege...";
			link.l1.go = "calendar_22";
		break;
		
		case "calendar_22":
			dialog.text = "Kukulcan wird das Opfer in der alten Indianerstadt ausspucken, wie du gesagt hast.";
			link.l1 = "Das wäre großartig! Ich muss dorthin gelangen! Glaubst du, das Schmuckstück wird funktionieren, wenn es in Scherben zerbrochen ist?";
			link.l1.go = "calendar_23";
		break;
		
		case "calendar_23":
			dialog.text = "Ich denke, wir müssen sie zusammenbringen und dann den Schmuck in die Vertiefung legen.";
			link.l1 = "Sie zusammenbringen? Aber wie können wir sie wieder zusammenbringen?";
			link.l1.go = "calendar_24";
		break;
		
		case "calendar_24":
			dialog.text = "Überlass es mir und den Ahnengeistern, weißer Bruder. Es sind nicht nur einfache Steine. Es ist ein Wundergegenstand. Komm in drei Nächten wieder, weißer Bruder. Ich rufe die Geister, Weisheit und Fähigkeiten des Lebens und versuche, die Scherben zu vereinen.";
			link.l1 = "Unglaublich... Wie kann ich dir jemals danken, Snake Eye?";
			link.l1.go = "calendar_25";
		break;
		
		case "calendar_25":
			dialog.text = "Dank mir später, weißer Bruder. Geh jetzt. Komm in drei Nächten zurück.";
			link.l1 = "Gut. Ich hoffe, dass du Erfolg haben wirst...";
			link.l1.go = "calendar_26";
		break;
		
		case "calendar_26":
			DialogExit();
			SetFunctionTimerCondition("Tieyasal_CalendarDone", 0, 0, 3, false);
			NextDiag.CurrentNode = "calendar_wait";
		break;
		
		case "calendar_28":
			dialog.text = "Ich kann dich glücklich machen, weißer Bruder.";
			link.l1 = "Konnten Sie die Splitter vereinen?";
			link.l1.go = "calendar_29";
		break;
		
		case "calendar_29":
			dialog.text = "Ja. Es war nicht einfach und es sind Narben auf dem Kalender geblieben, aber jetzt ist es vollendet.";
			link.l1 = "Kalender? Warum hast du es so genannt?";
			link.l1.go = "calendar_30";
		break;
		
		case "calendar_30":
			dialog.text = "Weil dieses runde Ding ein Kalender ist. Ich habe es sorgfältig studiert. Es hat eine Zeitrechnung darauf. Die Indianer aus der antiken Stadt zählen Nächte, Monde, Jahre und Zeitalter.";
			link.l1 = "Unglaublich... Aber wenn man darüber nachdenkt, was die Maya-Priester zu tun in der Lage sind - scheint die Erstellung dieses Kalenders nichts Besonderes zu sein.";
			link.l1.go = "calendar_31";
		break;
		
		case "calendar_31":
			GiveItem2Character(pchar, "calendar_maya");
			sld = ItemsFromID("calendar_maya");
			sld.shown = "0";
			Log_Info("Du hast einen Maya-Kalender erhalten");
			dialog.text = "Nimm es, weißer Kapitän. Leg es in die Vertiefung der Statue. Dann spuckt es dich vielleicht in der indischen Stadt aus.";
			link.l1 = "Wie kann ich dir danken, Snake Eye?";
			link.l1.go = "calendar_32";
		break;
		
		case "calendar_32":
			dialog.text = "Sag 'Danke'. Die Götter leiten dich auf deinem Weg, auch wenn du es nicht siehst. Die Weißen sagen - Schicksal. Kukulcan hat dich gerufen, die Götter leiten dich. Geh jetzt. Tu deine Arbeit und lass gute Geister dich leiten.";
			link.l1 = "Danke dir, Snake Eye! Ich werde dich nie vergessen.";
			link.l1.go = "calendar_33";
		break;
		
		case "calendar_33":
			TakeNItems(pchar, "Ultimate_potion", 4);
			Log_Info("Du hast vier vielseitige Tränke erhalten");
			PlaySound("interface\important_item.wav");
			dialog.text = "Warte. Wir haben fast das Wichtigste vergessen. Kukulcan frisst den Menschen und verzehrt sein Leben. Ich habe dir Tränke gemacht. Comanche-Tränke. Ich gebe sie dir. Ich habe vier Flaschen gemacht, damit du drei treue und mutige Gefährten mitnehmen kannst.";
			link.l1 = "Du hast so viel für mich getan, rothäutiger Bruder...";
			link.l1.go = "calendar_34";
		break;
		
		case "calendar_34":
			dialog.text = "Bruder ist nicht nur ein Wort für die Indianer des Comanche-Stamms. Wenn du aus der Stadt Kukulcan zurück bist, besuche unser Dorf. Wir kochen viel, viel Saraiaka. Ich würde mich freuen, dich zu sehen.";
			link.l1 = "Sicher, Rothaut Bruder! Ich werde dich sicherlich besuchen!";
			link.l1.go = "calendar_35";
		break;
		
		case "calendar_35":
			DialogExit();
			pchar.questTemp.Tieyasal = "calendar_place";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Tieyasal", "17");
			sld = ItemsFromID("skinmap");
			sld.price = 100; // кожаную карту можно выкладывать 270912 
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
