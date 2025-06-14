void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
			dialog.text = "Was brauchen Sie?";
			link.l1 = "Nichts.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "AlonsoNaPalube":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube"))
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube2 = true;
				dialog.text = "Ihre Entscheidung, Kapitän? Vielleicht sollten wir es lassen?";
				link.l1 = "Hast du es geschafft, mehr Freiwillige für die Sache zu sammeln?";
				link.l1.go = "AlonsoNaPalube_StrongGroup";
			}
			else
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube = true;
				dialog.text = "Kapitän, ein Wort unter vier Augen.";
				link.l1 = "Bericht erstatten, Alonso.";
				link.l1.go = "AlonsoNaPalube_2";
			}
			locCameraFromToPos(-10.33, 9.69, -22.16, true, -5.22, 7.19, -21.06);
		break;
		
		case "AlonsoNaPalube_2":
			dialog.text = "Die Mannschaft fragt sich, was Sie auf den Kaiman-Insel vorhaben. Die Leute sind beunruhigt.";
			link.l1 = "Ich habe noch nicht entschieden. Und warum sind die Leute beunruhigt, Alonso?";
			link.l1.go = "AlonsoNaPalube_3";
		break;
		
		case "AlonsoNaPalube_3":
			dialog.text = "Diese Insel ist das Revier von Kapitän Blackwood. Die Seeleute sagen, er gräbt dort wie besessen. Dass er Dutzende Männer bei seinen Ausgrabungen zugrunde gerichtet hat... Und die, die ihn verlassen, erzählen seltsame Dinge.";
			link.l1 = "Was für Dinge?";
			link.l1.go = "AlonsoNaPalube_4";
		break;
		
		case "AlonsoNaPalube_4":
			dialog.text = "Dass Blackwood nicht mehr derselbe Mensch ist wie früher. Dass er besessen ist von der Suche nach einem Schatz der Konquistadoren. Dass er bereit ist, alles und jeden dafür zu opfern. Wir wissen, wie gern Sie sich in schöne Geschichten verwickeln, allein an Land gehen und in Fallen geraten... Diesmal aber kommen Sie da nicht heraus.";
			link.l1 = "Danke für den Bericht und die Warnung. Wenn ich mich dennoch zur Landung entschließe, werde ich die Vorhut und eine Truppe unserer besten Männer mitnehmen.";
			link.l1.go = "AlonsoNaPalube_5";
		break;
		
		case "AlonsoNaPalube_5":
			dialog.text = "Das könnte schwierig werden, Kapitän. Entern ist das eine, aber sich an Land den Kugeln der Marineinfanterie und den Klingen des Gesindels zu stellen, das Blackwood angeblich in jeder Ecke der Kleinen Antillen angeworben hat, ist etwas ganz anderes. Und die Gerüchte über die Kaimaninseln sind nicht gut... Nein, für so einen Auftrag werden Sie nicht viele Freiwillige finden.";
			link.l1 = "Dann müssen wir eben mit dem auskommen, was wir haben. Deine Teilnahme ist unerlässlich, Alonso.";
			link.l1.go = "AlonsoNaPalube_LiteGroup";
			link.l2 = "Meiner Meinung nach habe ich bereits alles bewiesen, was es zu beweisen gab. Alle guten Kämpfer und Schützen kommen mit. Das ist ein Befehl.";
			link.l2.go = "AlonsoNaPalube_StrongGroup";
			link.l3 = "Hm... Ich muss darüber nachdenken. Möglicherweise kommen wir später auf diese Frage zurück.";
			link.l3.go = "AlonsoNaPalube_Exit";
		break;
		
		case "AlonsoNaPalube_Exit":
			SetFunctionLocationCondition("LadyBeth_CaimanSea", "Caiman", false);
			EndQuestMovie();
			bQuestDisableMapEnter = false;
			chrDisableReloadToLocation = false;
			if(UnloadLocation(loadedLocation) == true)
			{
				pchar.Ship.Pos.x = 0;
				pchar.Ship.Pos.z = 0;
				pchar.Ship.Ang.y = 0;
				Land_MapLoad();
				pchar.location = "";
			}
		break;
		
		case "AlonsoNaPalube_LiteGroup":
			dialog.text = "Wird gemacht, Käpt’n!";
			link.l1 = "Und was ist mit Blackwoods Schiff? Wird es uns keine Schwierigkeiten bereiten?";
			link.l1.go = "AlonsoNaPalube_Vpered";
			pchar.questTemp.LadyBeth_LiteGroup = true;
		break;
		
		case "AlonsoNaPalube_StrongGroup":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50 || sti(pchar.rank) >= 17)
			{
				dialog.text = "Wird gemacht, Käpt’n!";
				link.l1 = "Und was ist mit Blackwoods Schiff? Wird es uns keine Schwierigkeiten bereiten?";
				link.l1.go = "AlonsoNaPalube_Vpered";
				pchar.questTemp.LadyBeth_StrongGroup = true;
				if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50) notification("Überprüfung bestanden", SKILL_Leadership);
				if (sti(pchar.rank) >= 17) notification("Levelprüfung bestanden", "None");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube2"))
				{
					dialog.text = "Ich fürchte, nein, Kapitän.";
				}
				else
				{
					dialog.text = "Ihnen ist weder mir noch Ihren Offizieren etwas zu beweisen, und wir werden dem Befehl dorthin folgen, wohin Sie es sagen, aber ein gewöhnlicher Matrose denkt anders. Ich fürchte, es wird Probleme geben, Kapitän.";
				}
				link.l1 = "Dann müssen wir eben mit dem auskommen, was wir haben. Deine Teilnahme ist unerlässlich, Alonso.";
				link.l1.go = "AlonsoNaPalube_LiteGroup";
				link.l2 = "Hm... Ich muss darüber nachdenken. Möglicherweise kommen wir später auf diese Frage zurück.";
				link.l2.go = "AlonsoNaPalube_Exit";
				if (GetSummonSkillFromName(pchar, SKILL_Leadership) < 50) notification("Fähigkeit unzureichend entwickelt (50)", SKILL_Leadership);
				if (sti(pchar.rank) < 17) notification("Stufe 17 erforderlich", "None");
			}
		break;
		
		case "AlonsoNaPalube_Vpered":
			dialog.text = "Eine Schnau. Man sagt, sie sei eine wahre Schönheit mit einem grimmigen Wesen. Ich würde mir ihretwegen keine Sorgen machen. Wahrscheinlich schuftet die ganze Mannschaft an Land wie verrückt, während das Schiff sicher in den Falten der Küstenlinie versteckt ist. Wenn und falls wir gewinnen, können wir sie als Preis nehmen.";
			link.l1 = "Sammle die Männer. Heute ist ein guter Tag - das Glück wird auf unserer Seite sein.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_AlonsoNaPalube_Vpered");
		break;
		
		// Диалог в таверне с Блеквудом
		case "LadyBeth_DialogInCity": // главное меню
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Fourth"))
			{
				dialog.text = "Schön, Sie zu sehen, Kapitän. Ich glaube, wir haben bereits alles besprochen.";
				link.l1 = "In der Tat. Lebewohl.";
				link.l1.go = "exit";
				NextDiag.TempNode = "LadyBeth_DialogInCity_again";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Third"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", Albert.";
				link.l1.go = "LadyBeth_DialogInCity_Third_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", Kapitän Blackwood.";
				link.l1.go = "LadyBeth_DialogInCity_Second_1";
				break;
			}
			if (startHeroType == 4)
			{
				dialog.text = "...";
				link.l1 = "Guten Tag. Sind Sie Kapitän Blackwood?";
				link.l1.go = "LadyBeth_DialogInCity_First_Helena_1";
			}
			else
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+". Sie sind Kapitän Albert Blackwood, richtig?";
				link.l1.go = "LadyBeth_DialogInCity_First_1";
			}
		break;
		
		case "LadyBeth_DialogInCity_again": // повтор
			dialog.text = "Schön, Sie zu sehen, Kapitän. Ich glaube, wir haben bereits alles besprochen.";
			link.l1 = "In der Tat. Lebewohl.";
			link.l1.go = "exit";
			NextDiag.TempNode = "LadyBeth_DialogInCity_again";
		break;
		
		case "LadyBeth_DialogInCity_First_1": // первый диалог
			dialog.text = "Ja, genau der. Und Sie?";
			link.l1 = "Kapitän "+GetFullName(pchar)+". Ich führe das Schiff '" + PChar.Ship.Name + "'.";
			link.l1.go = "LadyBeth_DialogInCity_First_2";
		break;
		
		case "LadyBeth_DialogInCity_First_2":
			dialog.text = "Kapitän... Waren Sie schon einmal auf der Kaiman-Insel?";
			link.l1 = "Ich bin nur vorbeigekommen.";
			link.l1.go = "LadyBeth_DialogInCity_First_3";
		break;
		
		case "LadyBeth_DialogInCity_First_3":
			dialog.text = "Haben Sie dort von irgendwelchen Schätzen gehört?";
			link.l1 = "Nein, nichts Konkretes.";
			link.l1.go = "LadyBeth_DialogInCity_First_4";
		break;
		
		case "LadyBeth_DialogInCity_First_4":
			dialog.text = "Spuren der Spanier? Alte Waffen? Münzen aus der Zeit der Konquistadoren?";
			link.l1 = "Ich habe nichts dergleichen gefunden.";
			link.l1.go = "LadyBeth_DialogInCity_First_5";
		break;
		
		case "LadyBeth_DialogInCity_First_5":
			dialog.text = "Lokale Legenden? Geschichten über Cortés? Irgendwelche Begräbnisstätten?";
			link.l1 = "Verzeihung, Kapitän, aber ich verfüge nicht über solche Informationen. Und das hier erinnert langsam an ein Verhör.";
			link.l1.go = "LadyBeth_DialogInCity_First_6";
		break;
		
		case "LadyBeth_DialogInCity_First_6":
			dialog.text = "Entschuldigen Sie bitte... Schlechte Angewohnheit eines ehemaligen Offiziers. Es ist nur so... es ist mir äußerst wichtig.";
			link.l1 = "Warum interessiert Sie gerade Kaiman so sehr?";
			link.l1.go = "LadyBeth_DialogInCity_First_7";
		break;
		
		case "LadyBeth_DialogInCity_First_7":
			dialog.text = "Das spielt keine Rolle. Nochmals, entschuldigen Sie mich bitte.";
			link.l1 = "Ich verstehe. Viel Glück bei Ihrer Suche.";
			link.l1.go = "LadyBeth_DialogInCity_First_8";
		break;
		
		case "LadyBeth_DialogInCity_First_8":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Gute Nacht";
			else sStr = "Einen guten Tag Ihnen";
			dialog.text = "Schauen Sie bei mir vorbei, falls sich etwas Interessantes ergibt. Es wäre mir eine Freude, mit einem anderen Kapitän zu sprechen... mit jemandem, der das Meer versteht. Einen schönen Tag noch. " + sStr + ".";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_First_9";
		break;
		
		case "LadyBeth_DialogInCity_First_9":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_1": // первый диалог с Элен
			dialog.text = "In eigener Person. Und Sie... Kapitän Helen MacArthur? Protegé von Jan Swenson, richtig? Ich habe von Ihnen gehört.";
			link.l1 = "Sie sind gut informiert, Kapitän Blackwood. Aber es überrascht mich nicht, dass ein englischer Offizier über mich Bescheid weiß.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_2":
			dialog.text = "Ehemaliger Offizier. Und alle Rotröcke kennen Ihre... einzigartigen Vorrechte von der Krone. Gewinn stinkt bekanntlich nicht. Und die Geschichte, wie Ihr Vater Sean MacArthur Sie von klein auf mit zur See nahm und zum Kapitän machte, ist in der Flotte fast schon legendär.";
			link.l1 = "Und wie fühlt es sich an, dieser Legende zu begegnen?";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_3";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_3":
			dialog.text = "Ich persönlich bin beeindruckt. Obwohl, zugegeben, viele meiner ehemaligen Kollegen das ziemlich ärgert. Aber um Kapitän zu werden, braucht es mehr als nur edle Herkunft oder ein königliches Patent, nicht wahr?";
			link.l1 = "Richtig. Man braucht Wissen, Erfahrung und ständige Bereitschaft, seine Kompetenz zu beweisen. Besonders in meinem Fall.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_4";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_4":
			dialog.text = "Genau! Auf See, wie im Leben, zählen nicht die Titel, sondern die Ergebnisse. Freut mich, Sie kennenzulernen, Kapitän MacArthur. Ich hoffe, wir sehen uns wieder. Vielleicht schauen Sie auf ein Glas Wein vorbei, wenn ich von meiner Expedition zurückkomme?";
			link.l1 = "Vielleicht. Viel Glück bei Ihrer Suche, Kapitän.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_5_harizma";
			link.l2 = "Interessiert mich nicht. Aber viel Glück bei Ihrer Suche, Kapitän.";
			link.l2.go = "LadyBeth_DialogInCity_First_Helena_5_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_harizma":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_oruzhie":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_1": // второй диалог
			dialog.text = "Ah, Kapitän "+pchar.lastname+"! Schön, Sie zu sehen. Setzen Sie sich?";
			link.l1 = "Mit Vergnügen.";
			link.l1.go = "LadyBeth_DialogInCity_Second_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_2":
			dialog.text = "Kapitän... sagen Sie, was bedeuten für Sie wahre Schätze?";
			link.l1 = "Der wahre Schatz ist die Liebe. Die richtige Person ist in Ihrer Nähe. Es gibt nichts Schlimmeres, als allein zu sein.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love";
			link.l2 = "Geld, natürlich. Was sonst könnte ein Schatz sein?";
			link.l2.go = "LadyBeth_DialogInCity_Second_3_sokrovisha";
			link.l3 = "Wertvolle und einzigartige Ausrüstung. Ein guter Degen oder eine Pistole sind mehr wert als Gold.";
			link.l3.go = "LadyBeth_DialogInCity_Second_3_oruzhie";
			link.l4 = "Wissen. Der wertvollste Schatz ist das, was man im Kopf hat.";
			link.l4.go = "LadyBeth_DialogInCity_Second_3_znania";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love":
			if (startHeroType == 4)
			{
				dialog.text = "Liebe? Hm... So eine Antwort hätte ich nicht von der Tochter eines Piraten erwartet. Ich war... ich war mit Elizabeth verlobt. Der Tochter eines Plantagenbesitzers aus Barbados. Aber ihr Vater... er hielt mich für nicht wohlhabend genug. Was konnte ich seiner Tochter bieten außer meiner Liebe? Sie hatten Glück, Kapitänin MacArthur. Ihr Vater schätzte Ihre Fähigkeiten mehr als Ihre Mitgift.";
				link.l1 = "Vielleicht liegt es nicht am Glück, sondern daran, dass wahre Liebe sich nicht in Gold messen lässt. Mein Vater hat das verstanden. Und Ihre Verlobte? Teilt sie die Ansichten ihres Vaters?";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_1";
			}
			else
			{
				dialog.text = "Liebe? Ja... Vielleicht haben Sie recht. Ich... ich war verlobt. Auf Barbados. Wir haben uns geliebt, aber... ihr Vater hielt mich für eine schlechte Partie. Ha! Nicht reich genug. Deshalb bin ich hier - auf Schatzsuche, um es allen zu beweisen. Vielleicht vergebens?";
				link.l1 = "Vielleicht sollten Sie einfach mit ihr reden? Zum Teufel mit diesem Plantagenbesitzer.";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_2";
			}
			AddComplexLandExpToScill(100, 100, 0);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_2":
			dialog.text = "Reden... Ja, das ist möglich. Aber was soll ich sagen? 'Tut mir leid, ich konnte dir kein anständiges Leben bieten'? NEIN. Ich muss siegreich zurückkehren. Oder überhaupt nicht.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_1":
			dialog.text = "Elizabeth? Nein... sie liebt mich. Aber ich... ich konnte ihr kein Leben in Armut zumuten. Sie verdient Besseres. Und ich muss beweisen, dass ich ihrer würdig bin.";
			link.l1 = "Manchmal steht der Stolz dem Glück mehr im Weg als die Armut, Kapitän.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_2":
			dialog.text = "Ich kann nicht mit leeren Händen zurückkehren. Einfach nicht. Entschuldigen Sie mich, ich habe viel Arbeit. Es war mir eine Freude, mit Ihnen zu sprechen, Kapitänin MacArthur.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha":
			dialog.text = "Was für eine banale Antwort. Aber schwer zu widerlegen. Wirklich, wenn man in den Slums von Bristol aufgewachsen ist, wenn man um Essensreste kämpfen musste... dann beginnt man, den wahren Wert des Geldes zu verstehen. Es ist kein Luxus. Es ist Freiheit. Die Möglichkeit, nicht dorthin zurückkehren zu müssen, woher man sich so mühsam herausgearbeitet hat.";
			link.l1 = "Da stimme ich zu. Geld löst die meisten Probleme. Und wenn nicht - dann war es einfach nicht genug.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_sokrovisha_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha_2":
			dialog.text = "Genau! Sie verstehen. Geld macht nicht glücklich, aber sein Fehlen macht mit Sicherheit unglücklich. Das weiß ich nur zu gut...";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie":
			dialog.text = "Interessant. Praktisch. Ich habe eine Arkebuse... echt, aus der Zeit der Konquistadoren. Ein Geschenk eines Priesters. Manchmal denke ich, sie ist mehr wert als all das Gold, das ich gefunden habe. Aber... das wird meine Probleme nicht lösen.";
			link.l1 = "Eine gute Waffe kann viele Probleme lösen. Und sie wird dich nie verraten.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie_2":
			dialog.text = "Da ist etwas Wahres dran. Aber manche Kämpfe kann man nicht mit Waffengewalt gewinnen.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_znania":
			dialog.text = "Wissen... Ja, ich verstehe. Ich habe alles studiert, was ich über Konquistadoren und Schätze finden konnte. Ich habe ein komplettes Schatzsuch-Regelwerk geschrieben. Ich habe ein System aus regelmäßigen Übungen und materiellen Anreizen für die Schützenabteilung des Schiffs entwickelt\nJeder Kapitän wäre froh, mein Regelwerk zu haben. Aber all dieses Wissen... ist nutzlos, wenn es nicht zu einem Ergebnis führt. Zu einem echten Ergebnis.";
			link.l1 = "Aber gerade Wissen hilft, ein Ergebnis zu erreichen. Ohne es ist jede Suche nur ein Umherirren im Dunkeln.";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "LadyBeth_DialogInCity_Second_4":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Nun, es ist schon spät und ich habe viel Arbeit";
			else sStr = "Nun, ich habe viel Arbeit";
			dialog.text = "" + sStr + ". Danke für das Gespräch, Kapitän. Es war wirklich interessant.";
			link.l1 = "Auch Ihnen vielen Dank. "+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_5":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Third = true;
		break;
		
		case "LadyBeth_DialogInCity_Third_2": // третий диалог
			dialog.text = "Ah, "+pchar.name+"! Schön, Sie zu sehen. Ich habe großartige Neuigkeiten – ich habe endlich eine Lösung für meine Probleme gefunden. Bald geht es auf Expedition, und diesmal komme ich mit einem echten Schatz zurück! Ein freundlicher Rat – halten Sie sich von Cayman fern. Das ist jetzt mein Gebiet.";
			link.l1 = "Cayman gehört Ihnen nicht, Albert. Sie haben keine Krone-Rechte darauf. Das ist Piraterie.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma";
			link.l2 = "Drohen Sie mir, Blackwood?";
			link.l2.go = "LadyBeth_DialogInCity_Third_3_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma":
			dialog.text = "Kronrechte? Sie hätten mal in den Slums von Bristol leben sollen, "+pchar.name+", dann wüssten Sie, was diese Papiere wert sind. Wenn man hungert, ist das Gesetz bedeutungslos. Aber... Sie haben recht. Formal habe ich keine Rechte auf die Insel\nAber ich habe dort gefunden, wonach ich jahrelang gesucht habe. Und ich werde niemandem erlauben, es mir zu nehmen.";
			link.l1 = "Ich hoffe, Sie wissen, dass Sie einen gefährlichen Weg eingeschlagen haben.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma_2":
			dialog.text = "Ich wusste immer, dass mein Weg nicht leicht sein würde. Lebewohl, "+pchar.name+". Vielleicht sehen wir uns wieder.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie":
			dialog.text = "Ich drohe? Nein, ganz und gar nicht. Nur ein freundschaftlicher Rat von einem Kapitän zum anderen. Es ist gefährlich auf den Kaimaninseln... besonders für diejenigen, die sich in meine Angelegenheiten einmischen.";
			link.l1 = "Ich werde mich an Ihren 'Rat' erinnern. Viel Glück auf Cayman.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie_2":
			dialog.text = "Auch Ihnen viel Glück, Kapitän. Ich hoffe, Sie werden es nicht brauchen. Lebewohl.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_4":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Fourth = true;
		break;
		
		// Ловушка, абордаж в каюте
		case "LadyBeth_abordage":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "Sie?!! Glauben Sie, ich werde mich ergeben? Glauben Sie, ich kehre ins Elend zurück? Lieber sterbe ich, als noch einmal in den Elendsvierteln zu hungern! Keine Gnade, keine Belohnung, kein Sieg! Unter der Koje steht ein Pulverfass... Wir gehen alle gemeinsam unter!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
			else
			{
				dialog.text = "Wer sind Sie, dass Sie mich angreifen?! Glauben Sie, ich werde mich ergeben? Nein! Lieber sterbe ich, als noch einmal in den Elendsvierteln zu hungern! Keine Gnade, keine Belohnung, kein Sieg! Unter der Koje steht ein Pulverfass... Wir gehen alle gemeinsam unter!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
		break;
		
// Блеквуд разговаривает с ГГ перед битвой на Каймане
		case "LadyBeth_BlackWood_Boss":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "Kapitän! Ich habe Sie doch gewarnt. Jetzt werden Sie für Ihre Neugier bezahlen.";
			}
			else
			{
				dialog.text = "Wer sind Sie und wie wagen Sie es, in mein Gebiet einzudringen?! Diese Insel gehört mir!";
			}
			link.l1 = "Wir werden sehen, Blackwood. Heute wird es einen Besessenen weniger auf dieser Welt geben.";
			link.l1.go = "LadyBeth_BlackWood_Boss_oruzhie_1";
			link.l2 = "Lassen Sie uns das friedlich klären, Blackwood. Ich kann gehen.";
			link.l2.go = "LadyBeth_BlackWood_Boss_torgovlya_1";
			link.l3 = "Blackwood, Sie sind doch ein vernünftiger Mensch! Sie sind Offizier! Über Ihrem Lager weht die königliche Flagge, verdammt noch mal! Können wir uns denn wirklich nicht einigen?";
			link.l3.go = "LadyBeth_BlackWood_Boss_harizma_1";
		break;
		
		case "LadyBeth_BlackWood_Boss_oruzhie_1":
			dialog.text = "Besessen? Ha! Ich bin nur ein Mann, der weiß, was er will!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_1":
			dialog.text = "Gehen? Nach dem, was Sie gesehen haben? Nein, nein, nein! Niemand darf wissen, was ich hier gefunden habe. Niemand!";
			link.l1 = "Ich gebe Ihnen mein Wort, dass ich es niemandem erzählen werde. Ich schwöre bei der Ehre eines Kapitäns.";
			link.l1.go = "LadyBeth_BlackWood_Boss_torgovlya_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_2":
			dialog.text = "Es gibt keine Ehre in dieser Welt, Kapitän. Nur Dreck, Elend und Verachtung. Es tut mir leid, aber Sie müssen hier sterben.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
		break;
		
		case "LadyBeth_BlackWood_Boss_harizma_1":
			dialog.text = "Ich habe nachgedacht. Viel nachgedacht. Und ich habe erkannt – das ist meine einzige Chance. Entweder finde ich das Gold von Cortés, oder... nichts. Verstehen Sie? Nichts! Ich kehre nicht in mein altes Leben zurück! Ich kehre nicht in Dreck und Elend zurück! Lieber sterbe ich hier!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_2":
			dialog.text = "Zum Kampf! Bullock, Fraser - schießt mit Kartätsche, wenn sie sich nähern! Hopkins, Angriff!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_CaimanKino_11");
		break;
		
		// Диалоги с офицерами
		case "LadyBeth_Helena_1": // Элен
			dialog.text = "Geht es dir gut?";
			link.l1 = "Ja, alles gut. Und du?";
			link.l1.go = "LadyBeth_Helena_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Helena_2":
			dialog.text = "Am Leben. Aber diese Landschlachten sind nichts für mich. Gib mir ein Deck unter den Füßen, und ich zerlege jedes Schiff, aber hier... ein seltsamer Ort. Hundert Seewölfe an Land bringen, mit Spitzhacken arbeiten lassen, Befestigungen bauen... Ich hätte das nicht geschafft.";
			link.l1 = "Blackwood wusste, wie man seine Mannschaft inspiriert.";
			link.l1.go = "LadyBeth_Helena_3";
		break;
		
		case "LadyBeth_Helena_3":
			dialog.text = "Ich habe in Blueveldt von ihm gehört. Viele englische Seeleute sprachen mit Respekt über ihn. Der beste Offizier in der Flotte, eine glänzende Karriere... und plötzlich hat er alles aufgegeben, um nach Schätzen zu suchen.";
			link.l1 = "Was hältst du von ihm?";
			link.l1.go = "LadyBeth_Helena_4";
		break;
		
		case "LadyBeth_Helena_4":
			dialog.text = "Ich denke, das Beispiel von Blackwood zeigt gut die Last der Verantwortung, die wir... also du, gegenüber deiner Mannschaft trägst. Bitte werde nicht zu einem Kapitän wie er.";
			link.l1 = "Ich werde mein Bestes tun, Helen.";
			link.l1.go = "LadyBeth_Helena_5";
		break;
		
		case "LadyBeth_Helena_5":
			dialog.text = "Danke, mein Kapitän. Ich weiß, dass du es schaffen wirst.";
			link.l1 = "Wir.";
			link.l1.go = "LadyBeth_Helena_6";
		break;
		
		case "LadyBeth_Helena_6":
			dialog.text = "Wir.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Helena_7";
		break;
		
		case "LadyBeth_Helena_7":
			DialogExit();
			Return_HelenaOfficer();
		break;
		
		case "LadyBeth_Mary_1": // Мэри
			dialog.text = "Charles... es ist so unheimlich hier.";
			link.l1 = "Geht es dir gut, Mary? Du hast dich wie ein echter Soldat gehalten.";
			link.l1.go = "LadyBeth_Mary_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Mary_2":
			dialog.text = "Nein, es geht mir nicht gut, ja, gell. Schau dir diese Leute an! Sie haben bis zur Erschöpfung gearbeitet, halb verhungert gelebt, sind an Krankheiten gestorben... Und wofür? Für Gold, das vielleicht gar nicht existiert.";
			link.l1 = "Blackwood glaubte, es sei hier.";
			link.l1.go = "LadyBeth_Mary_3";
		break;
		
		case "LadyBeth_Mary_3":
			dialog.text = "Diese rote Uniform... genau wie meine. Ein englischer Offizier... Weißt du, ich habe plötzlich an meine Eltern gedacht, ja, gell. An meine Wurzeln... an das, was ich nie gekannt habe. Vielleicht bin ich auch so jemand?";
			link.l1 = "Was meinst du?";
			link.l1.go = "LadyBeth_Mary_4";
		break;
		
		case "LadyBeth_Mary_4":
			dialog.text = "Von denen, die etwas suchen, das es vielleicht gar nicht gibt. Und sich in dieser Suche verlieren. Ich... ich möchte später darüber sprechen, ja, gell. Wenn wir diesen schrecklichen Ort verlassen haben.";
			link.l1 = "Natürlich, Mary.";
			link.l1.go = "LadyBeth_Mary_5";
		break;
		
		case "LadyBeth_Mary_5":
			dialog.text = "Lass uns ihn zuerst beerdigen, bitte? Auch wenn er es vielleicht nicht verdient hat. Für den Menschen, der er einmal war.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Mary_6";
		break;
		
		case "LadyBeth_Mary_6":
			DialogExit();
			Return_MaryOfficer();
		break;
		
		case "LadyBeth_Tichingitu_1": // Тичингиту
			dialog.text = "Kapitän... Tichingitu sieht. Ort ist schlecht. Sehr schlecht.";
			link.l1 = "Was meinst du?";
			link.l1.go = "LadyBeth_Tichingitu_2";
			DelLandQuestMark(npchar);
		break;

		case "LadyBeth_Tichingitu_2":
			dialog.text = "Insel hat jetzt Fluch. Erde trank viel Blut... viele Tränen. Wer gräbt hier – atmet Fluch.";
			link.l1 = "Denkst du, Blackwood war besessen?";
			link.l1.go = "LadyBeth_Tichingitu_3";
		break;

		case "LadyBeth_Tichingitu_3":
			dialog.text = "Nicht nur besessen. Er war... wie sagt man... leerer Topf. Etwas ging hinein, Seele ging fort. Tichingitu sah so was. Schamane vom Stamm – er opferte Menschen. Hatte selben Blick.";
			link.l1 = "Aber was konnte eine solche Besessenheit auslösen?";
			link.l1.go = "LadyBeth_Tichingitu_4";
		break;

		case "LadyBeth_Tichingitu_4":
			dialog.text = "Mensch mit Leere – leicht zu füllen. Jemand fand Schwäche. Benutzte sie. Tichingitu... hat fast Mitleid.";
			link.l1 = "Fast?";
			link.l1.go = "LadyBeth_Tichingitu_5";
		break;

		case "LadyBeth_Tichingitu_5":
			dialog.text = "Ja. Fast. Krieger wählt selbst. Auch wenn Dämon flüstert.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Tichingitu_6";
		break;

		case "LadyBeth_Tichingitu_6":
			DialogExit();
			Return_TichingituOfficer();
		break;
		
		case "LadyBeth_Irons_1": // Томми
			dialog.text = "Verdammt, Kapitän! Sieh dir das an! Wie in den guten alten Zeiten!";
			link.l1 = "Du weißt genau, wie Krieg an Land aussieht.";
			link.l1.go = "LadyBeth_Irons_2";
			DelLandQuestMark(npchar);
		break;

		case "LadyBeth_Irons_2":
			dialog.text = "Hat mich an Naseby erinnert. Unsere Kavallerie traf auf Ruperts Reiter. Die Kerle haben für ihren König gekämpft wie Besessene.";
			link.l1 = "Was hältst du von Blackwood?";
			link.l1.go = "LadyBeth_Irons_3";
		break;

		case "LadyBeth_Irons_3":
			dialog.text = "Dieser Blackwood war entweder ein verdammtes Genie oder komplett irre. Wahrscheinlich beides. Weißt du, was mich wundert? Seine Leute. Viele waren ehemalige Soldaten. Kein Abschaum, sondern echte Profis.\nUnd trotzdem sind sie ihm in diesen Wahnsinn gefolgt. Sogar Fox’ Marineinfanterie. Ha! Der Kerl wird sich über das heutige Gemetzel freuen – er hat ihnen die Desertion nie verziehen.";
			link.l1 = "Vielleicht ging es ums Geld?";
			link.l1.go = "LadyBeth_Irons_4";
		break;

		case "LadyBeth_Irons_4":
			dialog.text = "Nein, da war mehr. Der Bursche hatte Macht über sie. Richtige Macht. Und ich hab gehört, er war mit ’ner reichen Lady aus Barbados verlobt. Komisch, dass er sie nie geheiratet hat, nicht mal nach all den Schätzen, die er fand.\nTypisch Soldat – wusste nicht, wann Schluss ist.";
			link.l1 = "Danke, Tommy. Du bist ein echter Denker.";
			link.l1.go = "LadyBeth_Irons_5";
		break;

		case "LadyBeth_Irons_5":
			dialog.text = "Hä?";
			link.l1 = "Nichts.";
			link.l1.go = "LadyBeth_Irons_6";
		break;
		
		case "LadyBeth_Irons_6":
			DialogExit();
			Return_IronsOfficer();
		break;
		
		case "LadyBeth_Knippel_1": // Книппель
			dialog.text = "Es ist bitter, das zu sehen, Käpt’n. Wie tief sind wir nur gesunken?!";
			link.l1 = "Wir?";
			link.l1.go = "LadyBeth_Knippel_2";
			DelLandQuestMark(npchar);
		break;

		case "LadyBeth_Knippel_2":
			dialog.text = "Die englische Flotte! Sehen Sie nur – kleine rote Punkte, verstreut zwischen diesem toten Gesindel!";
			link.l1 = "Einige dieser 'Gesindel' sind unsere Leute, Charlie. Ich verstehe deine Wut, aber...";
			link.l1.go = "LadyBeth_Knippel_3";
		break;

		case "LadyBeth_Knippel_3":
			dialog.text = "Zum Teufel damit, Sir.";
			link.l1 = "Ich verstehe dich, aber dein Zorn sollte Blackwood gelten. Er war es, der aus deiner geliebten englischen Flotte desertiert ist – und sie ins Verderben führte.";
			link.l1.go = "LadyBeth_Knippel_4";
			link.l2 = "In der Tat. Gehen wir, der Tag ist noch nicht vorbei.";
			link.l2.go = "LadyBeth_Knippel_6";
		break;

		case "LadyBeth_Knippel_4":
			dialog.text = "Sie haben nur ihrem Kommandanten gehorcht!";
			link.l1 = "So wie du Fleetwood gehorcht hast?";
			link.l1.go = "LadyBeth_Knippel_5";
			link.l2 = "In der Tat. Gehen wir, der Tag ist noch nicht vorbei.";
			link.l2.go = "LadyBeth_Knippel_6";
		break;

		case "LadyBeth_Knippel_5":
			dialog.text = "So wie ich Ihnen folge!";
			link.l1 = "Ich hoffe, ich bin ein besserer Kapitän als Blackwood oder Fleetwood. Gehen wir, der Tag ist noch nicht vorbei.";
			link.l1.go = "LadyBeth_Knippel_6";
		break;

		case "LadyBeth_Knippel_6":
			dialog.text = "Jawohl, Käpt’n. Und wenn er vorbei ist – trinke ich, bis der nächste anfängt.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Knippel_7";
		break;
				
		case "LadyBeth_Knippel_7":
			DialogExit();
			Return_KnippelOfficer();
		break;
		
		case "LadyBeth_Alonso_1": // Алонсо
			dialog.text = "Madre de Dios, Kapitän! Geht es Ihnen gut?";
			link.l1 = "Das wird sich zeigen. Wie viele Männer haben wir verloren?";
			link.l1.go = "LadyBeth_Alonso_2";
			DelLandQuestMark(npchar);
		break;

		case "LadyBeth_Alonso_2":
			dialog.text = "Getötet? In diesem Abenteuer haben wir "+sti(pchar.SailorDiedInBattleInfo)+" Mann verloren. Ich will nicht aufdringlich wirken, Kapitän, aber... ich habe Sie gewarnt!";
			link.l1 = "Ich werde diesen Kommentar überhören – heute hast du dich bewährt, Alonso. Woher hast du all diese Talente?";
			link.l1.go = "LadyBeth_Alonso_3";
		break;

		case "LadyBeth_Alonso_3":
			dialog.text = "Eines Tages erzähle ich Ihnen diese Geschichte, Kapitän... falls wir lange genug leben, natürlich.";
			link.l1 = "Hast du noch weitere Ratschläge für mich?";
			link.l1.go = "LadyBeth_Alonso_4";
		break;

		case "LadyBeth_Alonso_4":
			dialog.text = "Wenn es hier wirklich einen Schatz gäbe, hätten sie ihn längst gefunden. Trotzdem sollten wir die Insel durchsuchen und nach Überlebenden Ausschau halten – und dann entscheiden, was mit ihnen geschieht. Und vergessen wir nicht Blackwoods Schiff: Ich habe nur Gutes über diese schöne Schnau gehört. Es wäre schade, so einen Fang zu verpassen, Kapitän. Natürlich bringe ich hier nur die Meinung der Mannschaft zum Ausdruck.";
			link.l1 = "Natürlich. Gehen wir. Die Beute wartet!";
			link.l1.go = "LadyBeth_Alonso_5";
		break;
		
		case "LadyBeth_Alonso_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		// Диалог с матросом в гроте Каймана
		case "LadyBeth_MatrosyInGrot":
			dialog.text = "Nicht schießen! Wir ergeben uns!";
			link.l1 = "Wer seid ihr?";
			link.l1.go = "LadyBeth_MatrosyInGrot_2";
		break;

		case "LadyBeth_MatrosyInGrot_2":
			dialog.text = "Wir... wir gehören zur 'Lady Beth'. Kapitän Blackwoods Mannschaft. Lebt er noch?";
			link.l1 = "Nein. Euer Kapitän ist tot.";
			link.l1.go = "LadyBeth_MatrosyInGrot_3";
		break;

		case "LadyBeth_MatrosyInGrot_3":
			dialog.text = "Dann ist es vorbei... Gott sei Dank.";
			link.l1 = "Ihr wirkt nicht gerade traurig über seinen Tod.";
			link.l1.go = "LadyBeth_MatrosyInGrot_4";
		break;

		case "LadyBeth_MatrosyInGrot_4":
			dialog.text = "Sie verstehen nicht. Blackwood war ein großer Mann. Der beste Kapitän, den ich je hatte. Aber in den letzten Monaten... hat er sich verändert. Er war besessen, grausam. Er trieb uns Tag und Nacht an, etwas zu finden, das es vielleicht gar nicht gibt.";
			link.l1 = "Ich nehme euch in meine Mannschaft auf. Wir brauchen erfahrene Seeleute.";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda";
			link.l2 = "Pech für die Verlierer, Jungs. Jetzt gehört ihr mir. Wenn ihr Glück habt, überlebt ihr lange genug für eine Plantage auf Barbados.";
			link.l2.go = "LadyBeth_MatrosyInGrot_PlusRaby";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda":
			dialog.text = "Wirklich? Sie... Sie haben keine Angst, dass mit uns... dass mit uns nach all dem etwas nicht stimmt?";
			link.l1 = "Jeder verdient eine zweite Chance.";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda_1";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda_1":
			dialog.text = "Danke, Kapitän. Ich schwöre, Sie werden es nicht bereuen. Wir sind gute Seeleute. Und... vielleicht hören die Albträume jetzt auf.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 30;
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusRaby":
			dialog.text = "Danke, danke! Wenigstens bleiben wir am Leben. Bringen Sie uns bitte hier weg. Diese Insel... sie scheint verflucht zu sein.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+30);
		break;
		
		case "LadyBeth_MatrosyInGrot_exit":
			DialogExit();
			for (i=1; i<=8; i++)
			{
				sld = CharacterFromID("LadyBeth_MatrosyPryachutsya_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		break;
		
		// Диалог с матросом на Леди Бет
		case "LadyBeth_EnemyMatros_1":
			dialog.text = "Was zum Teufel?! Wie konntet ihr es wagen, die 'Lady' anzugreifen und Jeremy zu töten? Ihr werdet hier nicht lebend rauskommen, Mistkerle, der Kapitän kehrt zurück und...";
			link.l1 = "Euer Kapitän ist tot. Jeremy hat zuerst geschossen, und ich nehme eure 'Lady' als rechtmäßige, mit Blut bezahlte Prise.";
			link.l1.go = "LadyBeth_EnemyMatros_2";
		break;

		case "LadyBeth_EnemyMatros_2":
			dialog.text = "Der Kapitän... tot? Lügner, du Hund! Du bist nicht mal einen Knopf an seiner Uniform wert!";
			link.l1 = "Wenn diese Uniform etwas bedeutete, dann für den Blackwood, der längst nicht mehr existiert. Entscheidet selbst – kämpft für einen Toten oder rettet euer Leben.";
			link.l1.go = "LadyBeth_EnemyMatros_3";
		break;
		
		case "LadyBeth_EnemyMatros_3":
			if (CharacterIsHere("Helena"))
			{
				StartInstantDialog("Helena", "LadyBeth_EnemyMatros_Helena_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Knippel"))
			{
				StartInstantDialog("Knippel", "LadyBeth_EnemyMatros_Knippel_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Irons"))
			{
				StartInstantDialog("Irons", "LadyBeth_EnemyMatros_Irons_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			dialog.text = "Wir werden euch das Schiff nicht kampflos überlassen!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		case "LadyBeth_EnemyMatros_Helena_1":
			dialog.text = "Hört zu, Jungs. Ich weiß, ihr wart eurem Kapitän treu ergeben. Das verdient Respekt. Aber er ist tot – und ihr lebt noch. Jetzt müsst ihr entscheiden, wie es weitergeht. Wir bieten euch die Chance auf einen Neuanfang.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;

		case "LadyBeth_EnemyMatros_Knippel_1":
			dialog.text = "Kapitän, diese Männer sind keine Feinde. Sie haben nur Befehle befolgt. Viele von ihnen sind ehemalige königliche Seeleute – gut ausgebildet, diszipliniert. Es wäre eine Verschwendung, ihre Fähigkeiten nicht zu nutzen.\nJungs, ich war mehr als einmal an eurer Stelle während meines langen Dienstes in der Marine. Und ich habe die richtige Entscheidung getroffen. Trefft sie auch.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
		break;

		case "LadyBeth_EnemyMatros_Irons_1":
			dialog.text = "Na, Seemänner! Die Wahl ist einfach: Entweder ihr lebt – als Gefangene im Laderaum oder als Mitglieder unserer Crew mit gutem Proviant und regelmäßiger Bezahlung – oder... (fährt sich mit dem Finger über die Kehle) An eurer Stelle würde ich das Erste nehmen!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_10";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;
		
		case "LadyBeth_EnemyMatros_5":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_6", "Quest\ShipsPack\LadyBeth_dialog.c");
		break;
		
		case "LadyBeth_EnemyMatros_6":
			dialog.text = "...";
			link.l1 = "Ihr werdet Teil meiner Mannschaft.";
			link.l1.go = "LadyBeth_EnemyMatros_7";
			link.l2 = "Wehe den Besiegten, Jungs. Jetzt seid ihr in meiner Gewalt. Ihr habt Glück. Wenn ihr durchhaltet – landet ihr auf irgendeiner Plantage auf Barbados.";
			link.l2.go = "LadyBeth_EnemyMatros_9";
		break;

		case "LadyBeth_EnemyMatros_7":
			dialog.text = "Sie nehmen uns in Ihre Mannschaft? Nach allem, was passiert ist?";
			link.l1 = "Gute Seeleute sind immer gefragt. Und Blackwood wusste, wie man Leute auswählt.";
			link.l1.go = "LadyBeth_EnemyMatros_8";
		break;
		
		case "LadyBeth_EnemyMatros_8":
			dialog.text = "Danke, Käpt’n. Wir werden Sie nicht enttäuschen.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 12;
		break;

		case "LadyBeth_EnemyMatros_9":
			dialog.text = "Nun ja... dieses Abenteuer konnte wohl kaum anders enden. Vergib uns, Kapitän Blackwood. Wir konnten dich nicht retten.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+12);
		break;
		
		case "LadyBeth_EnemyMatros_10":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_11", "Quest\ShipsPack\LadyBeth_dialog.c");
		break;
		
		case "LadyBeth_EnemyMatros_11":
			dialog.text = "Wir werden euch das Schiff nicht kampflos überlassen!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		// Диалог с Элизабет Бишоп
		case "LadyBeth_Elizabeth_1":
			dialog.text = "...";
			link.l1 = "Entschuldigen Sie. Sind Sie Elizabeth?";
			if (pchar.sex == "man") link.l1.go = "LadyBeth_Elizabeth_2";
			if (pchar.sex == "woman") link.l1.go = "LadyBeth_Elizabeth_Woman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Elizabeth_2":
			dialog.text = "Ja, die bin ich. Und Sie sind?";
			link.l1 = "Kapitän "+GetFullName(pchar)+". Ich kannte... Albert Blackwood.";
			link.l1.go = "LadyBeth_Elizabeth_3";
		break;
		
		case "LadyBeth_Elizabeth_3":
			dialog.text = "Mein Albert? Mein Gott... Geht es ihm gut?";
			link.l1 = "Leider nicht. Er ist im Kampf gefallen. Er kämpfte bis zum Schluss.";
			link.l1.go = "LadyBeth_Elizabeth_4";
		break;
		
		case "LadyBeth_Elizabeth_4":
			dialog.text = "Ich... ich habe es geahnt. So viele Jahre ohne ein Lebenszeichen... Wissen Sie, ich habe auf ihn gewartet. Lange gewartet. Mein Vater sagte, Albert müsse nur auf seine Beförderung warten. Der Gouverneur hatte schon alles beschlossen, es war nur eine Frage von Monaten\nAber Albert... er sah das ganz anders. Er sagte, er würde reich zurückkehren, meiner Hand würdig. Und dann ging er. Einfach... ging.";
			link.l1 = "Er hat bis zu seinem letzten Tag an Sie gedacht.";
			link.l1.go = "LadyBeth_Elizabeth_5";
		break;
		
		case "LadyBeth_Elizabeth_5":
			dialog.text = "Wie töricht das war. Ich brauchte seine Schätze nicht. Ich liebte ihn, nicht sein Geld. Ich war bereit, mit ihm durchzubrennen... aber er war so stolz. Ich wartete auf einen Brief, ein Lebenszeichen... Und dann kam nur dieses seltsame Statut\nEin kaltes, berechnendes Dokument... ganz anders als der Albert, den ich kannte. Da wusste ich, dass ich ihn verloren hatte.";
			link.l1 = "Ich habe das hier unter seinen Sachen gefunden.";
			link.l1.go = "LadyBeth_Elizabeth_6";
		break;
		
		case "LadyBeth_Elizabeth_6":
			dialog.text = "Eine Karte zu meinem Haus? Ich war also sein größter Schatz? Wie ironisch. Er hat überall in der Karibik nach Reichtümern gesucht, dabei war das Einzige, was ihm wirklich wichtig war, immer hier... Warten Sie. Ich habe etwas für Sie\nDas ist Alberts Statut. Er hat es mir vor einem Jahr geschickt. Er sagte, es würde ihm helfen, einen Schatz zu finden und zu mir zurückzukehren. Jetzt wird es Ihnen mehr nützen.";
			link.l1 = "Danke, Elizabeth. Es tut mir leid, dass alles so gekommen ist.";
			link.l1.go = "LadyBeth_Elizabeth_7";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_7":
			dialog.text = "Und ich habe geheiratet, Kapitän. Einen gewissen Herrn Bishop. Mein Vater hat darauf bestanden. Sie kennen diesen Mann nicht... und das ist auch gut so. Jeden Tag denke ich daran, wie mein Leben verlaufen wäre, wenn Albert nur... zurückgekehrt wäre.";
			link.l1 = "Jetzt werde ich auch darüber nachdenken.";
			link.l1.go = "LadyBeth_Elizabeth_8";
		break;
		
		case "LadyBeth_Elizabeth_8":
			dialog.text = "Lebt wohl, Kapitän. Und... passen Sie auf sich auf. Jagen Sie keinen Geistern hinterher.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
		
		case "LadyBeth_Elizabeth_Woman_2":
			dialog.text = "Ja, die bin ich.";
			link.l1 = "Kapitänin Helen MacArthur. Ich kannte... Albert Blackwood.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_3";
		break;
		
		case "LadyBeth_Elizabeth_Woman_3":
			dialog.text = "Mein Albert? Mein Gott... Er... Und Sie sind?";
			link.l1 = "Kapitänin Helen MacArthur, wie ich sagte. Ich kommandiere mein eigenes Schiff.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_4";
		break;
		
		case "LadyBeth_Elizabeth_Woman_4":
			dialog.text = "Kapitänin? Eine Frau als Kapitän? Sie... Sie waren mit Albert? In welchem Sinne... kannten Sie ihn?";
			link.l1 = "Nur als Kapitän. Es tut mir leid, aber Albert ist gefallen. Ich war Zeugin seines letzten Gefechts.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_5";
		break;
		
		case "LadyBeth_Elizabeth_Woman_5":
			dialog.text = "Ich verstehe. Verzeihen Sie meinen Verdacht. Es ist nur so... Kapitän Blackwood hat immer die Aufmerksamkeit der Frauen auf sich gezogen. Selbst hier auf Barbados. Besonders hier.";
			link.l1 = "Sie haben ihn geliebt.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_6";
		break;
		
		case "LadyBeth_Elizabeth_Woman_6":
			dialog.text = "Mit ganzem Herzen. Mein Vater sagte, Albert müsse nur auf seine Beförderung warten. Es war eine Frage von wenigen Monaten. Aber Albert verstand seine Worte als eine Ablehnung wegen seiner Armut. Er sagte, er würde mit einem Schatz zurückkehren. Und er ging.";
			link.l1 = "Männer und ihr Stolz!";
			link.l1.go = "LadyBeth_Elizabeth_Woman_7";
		break;
		
		case "LadyBeth_Elizabeth_Woman_7":
			dialog.text = "Sie haben Glück, Kapitänin MacArthur. Sie sind frei. Sie segeln, wohin Sie wollen. Keine Plantagenbesitzer, keine Väter, die über Ihr Schicksal bestimmen. Keine Ehemänner, die Sie als ihr Eigentum betrachten.";
			link.l1 = "Freiheit hat ihren Preis. Und man muss sie jeden Tag verteidigen.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_8";
		break;
		
		case "LadyBeth_Elizabeth_Woman_8":
			dialog.text = "Ich habe vielleicht etwas, das Ihnen helfen kann. Hier, nehmen Sie. Das ist sein Schatzsuch-Statut. Albert hat es mir vor etwa einem Jahr geschickt. Er sagte, es sei das Beste, was er je geschaffen habe\nDass es ihm helfen würde, reich zu werden und zu mir zurückzukehren. Doch mit jeder Seite erkannte ich ihn weniger wieder.";
			link.l1 = "Danke. Ich werde es aufbewahren.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_9";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_Woman_9":
			dialog.text = "Bitte, Kapitänin... schätzen Sie Ihre Freiheit. Ich habe Oberst Bishop geheiratet. Einen Mann, vor dem selbst mein Vater Angst hat. Wenn ich so frei gewesen wäre wie Sie... Wäre alles anders gekommen.";
			link.l1 = "Ich weiß.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_10";
		break;
		
		case "LadyBeth_Elizabeth_Woman_10":
			dialog.text = "Lebt wohl, Kapitänin. Und mögen Ihnen gute Winde folgen.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
	}
} 