// Акула: Стивен Додсон
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			// Jason НСО
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, was zur Hölle!";
				link.l1 = "Steven, es gab eine Überschneidung. Ich konnte weder kommen noch dich über meine Abwesenheit informieren...";
				link.l1.go = "patria_33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Froh dich zu sehen, Kumpel! Wie kann ich dir helfen? ";
				link.l1 = "Freut mich auch dich zu sehen. Ich wollte dir für das perfekt durchgeführte Spektakel danken!";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Freut mich, dich zu sehen, Kumpel! Wie kann ich dir helfen?";
				link.l1 = "Ich habe einen Vorschlag für dich. Einen piratischen, weißt du!";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "Das ist unser Kunde! Die Arbeit ist erledigt, euer Baron sitzt in einem gut bewachten Kerker. Vielleicht möchtet ihr mal einen Blick werfen, he-he?!";
				link.l1 = "Ich werde genug Zeit dafür haben, ha-ha. Wird er gut behandelt?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = "Freut mich, dich zu sehen, Kumpel! Wie kann ich dir helfen?";
				link.l1 = "Ich bin wieder gekommen, um deine Hilfe zu bitten.";
				link.l1.go = "tieyasal";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesoro")
			{
				dialog.text = "Froh dich zu sehen, Kumpel! Wie kann ich dir helfen?";
				link.l1 = "Steven, ich habe etwas für dich.";
				link.l1.go = "guardoftruth";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro")
			{
				dialog.text = "Schön dich zu sehen, Kumpel! Wie kann ich dir helfen?";
				link.l1 = "Steven, ich muss dich etwas fragen. Es könnte dir nicht gefallen, aber ich brauche deine Hilfe.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro")
			{
				dialog.text = "Ha, da bist du ja, "+pchar.name+". Ich habe deine Ankunft erwartet. Waldteufel hat mir von deinen Schwierigkeiten mit Tortuga erzählt...";
				link.l1 = "Er hat mir auch gesagt, dass du bereits eine Lösung gefunden hast. Ist das wahr?";
				link.l1.go = "terrapin";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina") && pchar.questTemp.Terrapin == "tortuga")
			{
				dialog.text = "Wie geht es uns, "+pchar.name+"?";
				link.l1 = "Überall Geheimnisse... Ich brauche deinen Rat, Steven.";
				link.l1.go = "terrapin_8";
				break;
			}
			// belamour legendary edition хвастовство "Фортуной"
			if(CheckShipTypeInSquadron(SHIP_FRIGATE_L) > 0 && !CheckAttribute(pchar,"questTemp.SharkFrigate"))
			{
				link.l2 = "Ja, ich möchte dir etwas zeigen... Möchtest du mit mir zum Pier gehen?";
				link.l2.go = "check_out_my_frigate";
			}
			
			// belamour legendary edition на пару с Акулой
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "toDodson")
			{
				dialog.text = "Ach, mein Freund "+GetFullName(pchar)+"! Komm rein, es ist gut dich zu sehen! Warum bist du gekommen?";
				link.l1 = "Hallo, Steven! Nun, ich bin wie versprochen aufgetaucht. Ist dein Schiff bereit?";
				link.l1.go = "SharkGoldFleet";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "RUinDeal")
			{
				link.l2 = "Was ist mit deinem Geschäft los? Hast du dieses Unterfangen bezüglich der 'Goldenen Flotte' nicht aufgegeben?";
				link.l2.go = "SharkGoldFleet_10";
			}
			dialog.text = "Ach, mein Freund "+GetFullName(pchar)+"! Komm rein, es ist gut dich zu sehen! Warum bist du gekommen?";
			link.l1 = "Ja, ich besuchte Isla Tesoro geschäftlich und beschloss, für eine Minute vorbeizuschauen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// --------------------------------------вариант R-----------------------------------------------
		case "Chad_die":
			dialog.text = "Ha! Du bist also unser nächtlicher Besucher? Mir wurde zu spät von diesem Unfall berichtet. Ich habe deine Sachen durchsucht und einen Brief vom Waldteufel gefunden. Verdammt, es roch fast nach den Dschungeln von Main\nDein Name ist "+GetFullName(pchar)+"? Sei nicht überrascht, ich habe es aus dem Brief gelesen. Mein Name ist Steven Dodson. Oder einfach Hai. Der Hai. Ich denke, du hast schon von mir gehört. Ich bekleide derzeit eine Position als Admiral in dieser Stadt oder Insel, was auch immer\nIch entschuldige mich für das Verhalten meiner Männer letzte Nacht. Es war mein Befehl, jeden zu fangen, der sich ins Frachtraum schleicht. Zu viele Diebe unter den Narwalen und Rivados\nChad hat dich gehen lassen, nehme ich an? Seltsam. Ich wollte ihm gerade den Befehl senden, dich freizulassen. Wo ist dein Schiff? Ich hoffe, es geht ihr gut?";
			link.l1 = "Chad? Soweit ich verstehe, hätte dein Bootsmann mich nie lebend aus dem Gefängnis lassen. Ich habe es selbst getan und habe auch einen schwarzen Kerl von diesen... Rivados befreit.";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "Du erzählst mir interessante Dinge, Kumpel. Und wie hast du es aus dem 'Tartarus' geschafft? Es sieht so aus, als würde ich ein nettes Gespräch mit Chad und seinen Gefängniswärtern führen...";
			link.l1 = "Du wirst mit ihnen keinen Plausch halten. Sie werden leider nie wieder sprechen. Chad drohte mir, mich für immer im Käfig zu behalten. Er beschuldigte mich, ein Rivados zu sein und verlangte, dass ich das Gegenteil beweise, indem ich den schwarzen Zauberer Chimiset töte...";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "Was zur Hölle?! So eine törichte Eigenwilligkeit! Wir brauchen Chimiset lebendig, und Chad wusste das ganz genau! Und warum sollte er annehmen, dass du ein Rivados bist, wenn alle von ihnen schwarz sind? Was hat er vor, verdammt noch mal?";
			link.l1 = "Er ist zu etwas aufgelegt, das dir sicherlich nicht gefallen wird, Steven. Chad hat mir ein Machete gegeben und mich nach unten geschickt, um Chimiset zu töten. Aber der alte Schwarze hat mir etwas Wichtiges erzählt, und ich habe erkannt, dass, wenn ich Chimiset töte, ich der Nächste sein werde...";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "";
			link.l1 = "Anstatt den alten Mann zu töten, habe ich eine Kiste mit Munition geöffnet und mit Chad und seinen Kumpels gekämpft. Siehst du jetzt, warum du nicht mehr mit ihnen reden kannst? Sie sind alle tot.";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = "Verdammt! Die Nachrichten werden immer erschreckender! Und was soll ich mit diesem ganzen Durcheinander anfangen?";
			link.l1 = "Hör mir zu, Steve. Chimiset hat mir erzählt, dass Chad einen Deal mit einigen Narwalen hatte - das ist der andere Clan, soweit ich verstehe. Chad wollte dich töten und deine Position einnehmen. Die Narwale sind darauf aus, dich tot zu sehen, weil sie sicher sind, dass du ihren Anführer Allen... oder Alan, ich erinnere mich nicht, getötet hast.";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "Unsinn! Ich habe Alan nicht getötet! Jemand anderes hat das getan, vielleicht sogar Narwale. Ich denke, dass ihr aktueller Anführer - Donald Greenspen - Alan getötet hat!";
			link.l1 = "Nein. Chad hat ihn ermordet. Chimiset war Zeuge des Verbrechens - deshalb wollten sie ihn auch töten. Aus irgendeinem Grund wollte Chad das nicht selbst tun - es sieht so aus, als hätte er Angst vor einem Fluch gehabt. Deshalb wollte er, dass ich den Job erledige.";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			dialog.text = "Ich kann es nicht glauben... Chad hat Alan getötet? Aber warum?";
			link.l1 = "Um dir die Schuld zu geben und dich zum Feind der Narwale zu machen. Ich vermute, dass er derjenige war, der Gerüchte verbreitet hat, denn warum sollten die Narwale nur dich beschuldigen? Steven, sie planen, dich zu töten. Und der Rivados-Clan würde dafür verantwortlich gemacht werden - ich weiß allerdings nicht, wie sie das anstellen wollen. Chimiset hat mir davon erzählt.";
			link.l1.go = "Chad_die_7";
		break;
		
		case "Chad_die_7":
			dialog.text = "";
			link.l1 = "Außerdem habe ich diesen Brief in Chads Truhe gefunden. Lies ihn. Es scheint ein stichfester Beweis zu sein, wenn auch indirekt.";
			link.l1.go = "Chad_die_8";
		break;
		
		case "Chad_die_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "...(liest)... heh! Ich bin nicht überrascht von Chads Verrat. Der Hurensohn wollte schon immer die Macht auf dieser Insel. Aber Narwale! Ernsthaft zu glauben, dass ich es war, der Alan getötet hat! Das wird ihnen einen doppelten Preis für Proviant kosten\nIch hatte sowieso vor, Chimiset freizulassen, es ist höchste Zeit, Frieden mit ihnen zu schließen. Du hast mich geschockt, Kumpel, um ehrlich zu sein...";
			link.l1 = "Ich verstehe, Steven. Mir gefällt es auch nicht, ich bin in ein politisches Durcheinander geraten, seit ich die Insel erreicht habe. Ich kam nur her, um dich und Nathaniel Hawk zu finden...";
			link.l1.go = "Chad_die_9";
		break;
		
		// ноды пересечения
		case "Chad_die_9":
			dialog.text = "Was? Falke? Ist er nicht auf Jamaika? Er ist ein Baron von Maroon Town, warum sollte er hier sein?";
			link.l1 = "Nein. Jackman hat dort jetzt das Kommando. Ich konnte herausfinden, dass Hawk auf die gleiche Weise dorthin gekommen war wie ich - durch das Portal von Kukulcan.";
			link.l1.go = "Chad_die_10";
		break;
		
		case "Chad_die_10":
			dialog.text = "Was ist das für ein Unsinn? Welches Portal? Und du hast immer noch nicht geantwortet - wo ist dein Schiff?";
			link.l1 = "Es gibt kein Schiff. Ich verstehe, Steve, dass es schwer zu glauben ist, aber ich bin wirklich durch das indische Idol aus dem Main hierher gekommen... schau mich nicht so an - ich bin nicht verrückt! Ich selbst verstehe nicht, wie das möglich ist, aber es ist so!";
			link.l1.go = "Chad_die_11";
		break;
		
		case "Chad_die_11":
			dialog.text = "";
			link.l1 = "Der Schamane im Miskito-Dorf hat gesehen, wie Nathaniel Hawk, der vor den Verfolgern floh, zum indischen Idol, das als Statue von Kukulcan bekannt ist, lief und plötzlich verschwand. Dieser Schamane erzählte mir, dass er selbst auf dieser Insel gewesen war und dass er auf die gleiche Weise durch die Statue dorthin gelangt war...";
			link.l1.go = "Chad_die_12";
		break;
		
		case "Chad_die_12":
			dialog.text = "";
			link.l1 = "Ich suche nach Nathan, deshalb musste ich in seinen Fußstapfen wandern. Ich kam um Mitternacht zur Statue, genau wie der Schamane es mir gesagt hat. Du wirst es nicht glauben, aber die Spitze der Steinstatue war in dieser Nacht golden und ein mysteriöses Licht leuchtete darüber!";
			link.l1.go = "Chad_die_13";
		break;
		
		case "Chad_die_13":
			dialog.text = "";
			link.l1 = "Sobald ich die Statue berührt hatte, bildete sich ein Kreis aus Licht um das Idol, Feuer flammte auf, und dann wurde ich in die Statue hineingezogen. Ich wurde hier herausgeworfen, im Laderaum deines Schiffes, unten in der Nähe des Bugs, an der Bruchstelle...";
			link.l1.go = "Chad_die_14";
		break;
		
		case "Chad_die_14":
			dialog.text = "";
			link.l1 = "Ich habe das nur knapp überlebt, dank des Schamanen, der mir einen speziellen Trank gegeben hat. Am Ende wurde ich von einem Monster angegriffen - einer riesigen Krabbe. Ich hoffe, jetzt vertraust du mir?";
			link.l1.go = "Chad_die_15";
		break;
		
		case "Chad_die_15":
			dialog.text = "Du meinst den Teil mit der Krabbe? Daran glaube ich dir. Es gibt viele dieser Monster auf der Insel. Wir ködern sie mit totem Fisch, so bewachen sie oft unsere Hintertür. Macht Diebe starr vor Angst. Und was du über das Idol erzählt hast - ich bin noch nicht verrückt\nAber ich werde deine Geschichte auch nicht ablehnen, die Einheimischen haben seit mehreren Dutzend Jahren über solche Dinge getratscht, außerdem habe ich vor langer Zeit selbst seltsame Dinge auf den Schiffen von Rivados gesehen... egal.";
			link.l1 = "Ich schwöre, dass es die ganze Wahrheit ist.";
			link.l1.go = "Chad_die_16";
		break;
		
		case "Chad_die_16":
			dialog.text = "Gut. So sei es. Sag mir, warum hast du mich und Nathan gesucht? Laut Jans Brief wolltest du, dass ich der Anführer der Bruderschaft der Küste werde?";
			link.l1 = "Genau. Viele Dinge haben sich verändert nach deinem und Hawk's Verschwinden. Jackman versucht, die zentrale Rolle unter den Piraten zu spielen. Er plant, ihr Anführer zu werden, und er wird Erfolg haben, wenn Jan und ich ihn nicht stoppen.";
			link.l1.go = "Chad_die_17";
		break;
		
		case "Chad_die_17":
			dialog.text = "";
			link.l1 = "Jackman ist bereit für ein ernstes und blutiges Spiel. Ich bin sicher, dass er es war, der den Hinterhalt und die Jagd auf Nathaniel organisiert hat. Ich glaube auch, dass er Blaze getötet hat. Dich zum Anführer der Bruderschaft der Küste zu machen, ist der einzige Weg, ihn zu stoppen.";
			link.l1.go = "Chad_die_18";
		break;
		
		case "Chad_die_18":
			dialog.text = "Schau, ich wäre froh, aber wir müssen zuerst diese Insel verlassen. Ich habe genug davon. Umso mehr, dass ich Dexter hier lassen kann, er kann Geschäfte in meiner Abwesenheit führen. Ich hatte nicht vor, so lange hier zu bleiben, aber mein Schiff wurde in einem Kampf gegen die Clans niedergebrannt. Ich werde nicht durch diese Portale reisen, versuche nicht einmal, mich zu überreden, ich brauche ein Schiff.";
			link.l1 = "Ich werde nicht... Steven, der Miskito-Schamane hat mir gesagt, dass hier auf der Insel eine Statue von Kukulcan steht. Sie sieht aus wie ein gewöhnliches Steingötzenbild. Weißt du, wo ich sie finden kann?";
			link.l1.go = "Chad_die_19";
		break;
		
		case "Chad_die_19":
			dialog.text = "Ich weiß es nicht. Ich habe noch nie solche Statuen gesehen. Frag jemand anderen.";
			link.l1 = "Siehst du, wenn ich diese Statue finde, kann ich ohne Schiff von dieser Insel fliehen. Die Reise macht mir keine Angst mehr. Und dann würde ich auf normale Weise zurückkehren und dich von hier mitnehmen.";
			if (pchar.questTemp.LSC == "entrance" || pchar.questTemp.LSC == "mary") link.l1.go = "entrance_4";
			else link.l1.go = "Chad_die_20";
		break;
		// ноды пересечения
		
		case "Chad_die_20":
			dialog.text = "Ich verstehe, aber ich kann dir nicht helfen. Außerdem ist diese Angelegenheit mit dem Attentat ziemlich beunruhigend. Chad ist tot, aber ich bezweifle, dass die Narwale ihren Plan aufgeben werden. Ich will nicht jeden Tag damit rechnen müssen, von hinten erschossen zu werden. Da du mich lebendig brauchst und du bereits in dieses Chaos verwickelt bist, biete ich dir an, diese Verschwörung zu untersuchen. Du bist ein Neuling, das ist ein Vorteil. Finde Chads Partner und bring sie zu mir oder töte sie, wo sie stehen, es ist mir egal. Sprich mit Chimiset, der alte Schwarze weiß mehr, als er uns bereits erzählt hat. Sei vorsichtig mit den Narwalen, überschreite ihre Grenzen nicht, es sei denn, du hast ein Passwort. Sie ändern die Passwörter jede Woche. Sobald die Bedrohung beseitigt ist, werde ich dir alle erforderlichen Segelanweisungen und Informationen geben. Geh und finde die Verantwortlichen. Stelle die Ordnung wieder her. Ich werde dafür sorgen, dass sie das Gefängnis nach dir säubern. Und wir brauchen einen neuen Gefängniswärter. Und ich brauche etwas Rum, mir geht es nicht gut.";
			link.l1 = "Gut, Steven. Lass uns das tun...";
			link.l1.go = "Chad_die_21";
		break;
		
		case "Chad_die_21":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.questTemp.LSC.rvd_friend = "true"; //флаг на проход по кораблям ривадос
			pchar.rvd_friend = true; // ривадосы не будут останавливать где просят пароль
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "Friend"; //ноду Чимисету
			pchar.quest.LSC_Eddy.win_condition.l1 = "location";
			pchar.quest.LSC_Eddy.win_condition.l1.location = "ProtectorFisher";
			pchar.quest.LSC_Eddy.function = "LSC_EddyTalk"; //на разговор с Эдди
			AddQuestRecord("SharkHunt", "10");
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			for (i=7; i<=12; i++)
			{
				sld = CharacterFromID("RivadosSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=4; i<=8; i++)
			{
				sld = CharacterFromID("RivadosProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("Just imagine: someone has killed the admiral's jailer, Chad Kapper. Impossible! No doubt, that was the Rivados wizard's job...", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("I heard that Chad Kapper is dead. There was no official statement; his body was never found, either. Perhaps, the admiral had simply given him a secret mission?", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("I don't see our jailer Chad Kapper. Some people say that he was killed and some disagree. Anyway, no one has seen him dead.", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that the admiral has doubled provision prices for Narwhals! That pirate is truly reckless!", "LostShipsCity", 7, 3, "LSC", "");
		break;
		
			case "Mary_Die":
			dialog.text = "Nun, was hast du, "+pchar.name+"? Neuigkeiten über die Narwale?";
			link.l1 = "Ja. Du wirst froh sein zu wissen, Steve, dass die Verschwörung aufgedeckt wurde und die Verschwörer tot sind. Ich habe alle Beweise.";
			link.l1.go = "Mary_Die_1";
		break;
		
		case "Mary_Die_1":
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) dialog.text = "Ich dachte es mir schon, als ich den Schusswechsel hörte... Erzähl mir mehr, ich höre zu.";
			else dialog.text = "Ist das so? Das freut mich wirklich zu hören! Erzähl mir mehr, ich höre zu.";
			link.l1 = "Es war alles von deinem Bootsmann, Chad Kapper, geplant. Er hat Alan Milrow im 'Tartarus' Gefängnis getötet, und er hat Gerüchte über deine Beteiligung verbreitet. Ich denke, dass die Narwale wirklich wütend waren, und es war ein harter Schlag für Alans Freundin, Rote Mary...";
			link.l1.go = "Mary_Die_2";
		break;
		
		case "Mary_Die_2":
			dialog.text = "";
			link.l1 = "Mary war begierig, Rache zu nehmen und Chad Kapper nutzte es für seine eigenen Zwecke. Sie schmiedeten einen raffinierten Plan, um ein Attentat auf dein Leben zu verüben. Jeder hier weiß über deine Gewohnheit, jeden Abend auf dem Heck der 'San Augustine' herumzulaufen.";
			link.l1.go = "Mary_Die_3";
		break;
		
		case "Mary_Die_3":
			dialog.text = "Heh! Ich werde meine Gewohnheiten überdenken... Mach weiter.";
			link.l1 = "Sie brauchten ein langes und genaues Gewehr, um ihren Plan auszuführen, und so lieferte es ihnen ein gewisser Adolf Barbier. Aber sein Stutzen wurde an Giuseppe Fazio verpfändet, also gaben Mary und Chad ihm genug Geld, um es zurückzukaufen. Adolf hat es aus der Pfandleihe herausgeholt...";
			link.l1.go = "Mary_Die_4";
		break;
		
		case "Mary_Die_4":
			dialog.text = "";
			link.l1 = "Sie haben den Zyklopen Marcello, einen ehemaligen königlichen Jäger, angeheuert, um dich zu töten. Er sollte das Gewehr erhalten und dich totschießen. Danach hätte Mary ihn getötet und seine Leiche und das Gewehr als Beweis dafür verwendet, dass die Rivados für den Angriff verantwortlich waren. Zyklop Marcello ist ein Mulatte, weißt du...";
			link.l1.go = "Mary_Die_5";
		break;
		
		case "Mary_Die_5":
			dialog.text = "So ein schlauer Bastard!";
			link.l1 = "Danach würden Narwale und Piraten Rivados angreifen und sie zerstören. Chad würde ein Admiral werden und Mary wäre seine Geliebte. Vielleicht hätte er ihr jedoch die Kehle durchgeschnitten, da sie zu viel wusste. Sehr wahrscheinlich...";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) link.l1.go = "Mary_Die_6a";
			else link.l1.go = "Mary_Die_6";
		break;
		
		case "Mary_Die_6":
			dialog.text = "";
			link.l1 = "So oder so, es ist jetzt vorbei. Adolf war nicht gesprächig genug, und ich musste ihn direkt in seiner Kabine töten. Ich musste auch mit Mary und Zyklop umgehen, die gekommen waren, um den Stutzen von Adolf zu holen. Sie erkannten sofort, wer ich war, und griffen mich sofort an.";
			link.l1.go = "Mary_Die_7";
		break;
		
		case "Mary_Die_7":
			dialog.text = "Also liegen sie in der 'Santa Florentina', richtig?";
			link.l1 = "Ja. Alle drei von ihnen.";
			link.l1.go = "Mary_Die_8";
		break;
		
		case "Mary_Die_8":
			dialog.text = "Das ist gut, dass keine Zeugen in dieses Durcheinander verwickelt waren. Ich werde mich um die Leichen kümmern. Du hast gute Arbeit geleistet, "+pchar.name+"! Wärst du in meiner Mannschaft gewesen, hätte ich dich definitiv zu meinem ersten Maat gemacht.";
			link.l1 = "Danke für so eine hohe Antwort! Und schließlich, schau dir diese Briefe an. Ich habe sie von den Körpern von Zyklop und der armen Mary genommen...";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("Have you heard that? Our squabbler and madcap Red Mary has disappeared. I won't be surprised if she is dead...", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that Red Mary has disappeared. Have you heard about it?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Mary Casper has vanished. Some people say that she is still inside her cabin but I don't believe it. It's been too long since there last was light in it.", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that Red Mary was murdered. Poor girl! Yes, she had tough character, but everybody loved her. Who could have done such a terrible thing?", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		case "Mary_Die_6a":
			dialog.text = "";
			link.l1 = "So oder so, es ist jetzt vorbei. Adolf war nicht gesprächig genug, und ich musste ihn direkt in seiner Kabine töten. Ich musste auch mit Mary und Zyklop umgehen, die gekommen waren, um den Stutzen von Adolf zu holen. Sie erkannten sofort, wer ich war, und griffen mich sofort an.";
			link.l1.go = "Mary_Die_7a";
		break;
		
		case "Mary_Die_7a":
			dialog.text = "Schade, dass du einen Kampf auf 'Eva' angefangen hast. Jetzt wissen die Narwale, dass du für den Tod ihrer Männer verantwortlich bist, solche Aktionen werden deinen Ruf nicht verbessern. Dasselbe gilt für meinen. Besuche sie nicht, bis du diesen Konflikt gelöst hast\nIm Allgemeinen hast du gut gemacht, "+pchar.name+"! Wärest du in meiner Mannschaft, hätte ich dich definitiv zu meinem Ersten Maat gemacht.";
			link.l1 = "Danke für so eine hohe Antwort! Und schau dir endlich diese Briefe an. Ich habe sie von den Leichen des Zyklopen und der armen Mary genommen...";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("Such a massacre you have performed here! Narwhals won't forget about it!", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I understand killing Cyclops and two Narwhal bandits... But the girl, why have you killed the girl? Poor Mary...", "LostShipsCity", 7, 5, "LSC", "");
		break;
		
		case "Mary_Die_9":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Arme Mary? Hast du Mitleid mit dieser Hure?";
			link.l1 = "Ich bin es wirklich. Siehst du, Chad hat sie getäuscht und ausgenutzt. Sie konnte ihren Gefühlen und ihrer natürlichen Hitzköpfigkeit nicht widerstehen... und das hat sie dazu gebracht.";
			link.l1.go = "Mary_Die_10";
		break;
		
		case "Mary_Die_10":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			dialog.text = "Nun, geh und besuche Bruder Julian und zünde eine Kerze an... Das werde ich allerdings nicht selbst tun. Also, lassen wir das Thema. Ich bin dir dankbar, "+pchar.name+", für Ihre Hilfe. Sie können jetzt auf meine Unterstützung zählen. Ich möchte Sie für Ihre hervorragende Arbeit bezahlen. Hier, nehmen Sie fünfhundert Dublonen.";
			link.l1 = "Schön, danke!";
			link.l1.go = "LSC_navy";
			AddSimpleRumourCityTip("They say that the admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------вариант N---------------------------------------------------
		case "entrance":
			dialog.text = "Was willst du? Ich erinnere mich nicht an dich...";
			link.l1 = "Natürlich kennst du mich nicht - wir haben uns noch nie getroffen, und ich bin erst kürzlich hierher gekommen. Hallo, Steven. Was für ein seltener Glücksfall! Ich habe dich schließlich gefunden, ich habe nach dir gesucht, obwohl ich nicht erwartet habe, dich hier zu finden!";
			link.l1.go = "entrance_1";
		break;
		
		case "entrance_1":
			dialog.text = "Warte, Kumpel, beruhige dich. Suchst du mich? Das mag ich nicht. Warum zum Teufel hast du mich gesucht?";
			link.l1 = "Ich verstehe. Lassen wir es dann noch einmal versuchen. Hier, nimm den Brief. Er wurde von Jan Svenson für dich geschrieben. Ich vermute, dass all deine Verdächtigungen nach dem Lesen verschwinden werden.";
			link.l1.go = "entrance_2";
		break;
		
		case "entrance_2":
			RemoveItems(pchar, "letter_svenson", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "(liest)... Hm. Das erklärt vieles. Und ich dachte, du würdest mir einen schwarzen Fleck für Blazes Tod geben. Du weißt, in letzter Zeit waren viele Kerle darauf aus, das zu tun. Hast du dein Schiff im äußeren Ring gelassen? Und wie wusstest du, dass ich hier war?";
			link.l1 = "Ich habe nicht. Das war ein glücklicher Zufall. Und über Blaze ... Jan und ich denken, dass du nicht für seinen Tod verantwortlich bist.";
			link.l1.go = "entrance_3";
		break;
		
		case "entrance_3":
			dialog.text = "Und du hast recht. Ich bin es nicht. Jemand versucht, mich zu beschuldigen, das ist wahr. Aber ich habe ihn nicht getötet.";
			link.l1 = "Das ist gut. Interessant, ich kam hierher, um Nathaniel Hawk zu finden, aber stattdessen habe ich dich gefunden, ha-ha!";
			link.l1.go = "Chad_die_9";
		break;
		
		case "entrance_4":
			dialog.text = "Ich verstehe, aber ich kann dir nicht helfen. Du musst mit den Alteingesessenen dieser Insel darüber reden. Sprich mit dem Rivados-Zauberer Chimiset. Der alte Schwarze weiß viel mehr, als er sagt.";
			link.l1 = "Und wo kann ich diesen Zauberer finden?";
			if (pchar.questTemp.LSC == "mary") link.l1.go = "mary";
			else link.l1.go = "entrance_5";
		break;
		
		case "entrance_5":
			dialog.text = "In meinem Gefängnis, auf 'Tartarus'. Ich hatte sowieso vor, ihn freizulassen, es ist Zeit, unsere Beziehungen zu Rivados zu verbessern. Richtig! Geh zum Gefängnis, sag Chad Kapper, er ist ein Gefängniswärter, dass ich befohlen habe, Chimiset freizulassen\nSag dem schwarzen Mann, warum ich dich geschickt habe, sag ihm, dass ich ihn freilassen werde, wenn er gesprächig genug ist. Ich bin sicher, das wird ihn zum Reden bringen.";
			link.l1 = "Hm... Ich bin neu hier. Wo ist das Gefängnis?";
			link.l1.go = "entrance_6";
		break;
		
		case "entrance_6":
			dialog.text = "Behalte folgendes im Kopf. Verlasse meine Residenz, überquere die Brücke, biege links ab, gehe durch die Fregatte Carolina zum Galeon Gloria und du wirst zur Esmeralda gelangen. Such nach einem Ladenschild und betrete die Türen darunter. Geh durch die Tür im Bugteil des Schiffs und du wirst Tartarus erreichen\nSei vorsichtig bei der Esmeralda, sie gehört dem Narwale Clan, auch wenn andere sie besuchen können. Ärgere ihre Kämpfer nicht und vermeide Ärger.";
			link.l1 = "Wer sind diese Rivados und Narwale?";
			link.l1.go = "entrance_7";
		break;
		
		case "entrance_7":
			dialog.text = "Die Clans leben schon seit sehr langer Zeit hier. Sie repräsentieren die Nachkommen der ersten Siedler. Narwale sind hauptsächlich Engländer, Niederländer und Franzosen, Rivados sind alle Neger. Jeder Clan hat einen Anführer, sie besitzen mehrere Schiffe und lassen andere nicht in ihr Territorium\nDu musst die Passwörter kennen, um sie zu besuchen. Sie ändern die Passwörter jede Woche.";
			link.l1 = "Gut. Ich werde mich darum kümmern. Lassen sie mich ins Gefängnis rein?";
			link.l1.go = "entrance_8";
		break;
		
		case "entrance_8":
			dialog.text = "Sie werden es tun. Hier ist der Schlüssel, damit Chad weiß, dass ich dich dorthin geschickt habe. Nimm ihn.";
			link.l1 = "Gut. Dann werde ich mit diesem... Chimiset sprechen und dann komme ich mit den Ergebnissen zurück.";
			link.l1.go = "entrance_9";
		break;
		
		case "entrance_9":
			DialogExit();
			GiveItem2Character(pchar, "key_capper");
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "prisoner"; //даем ноду Чимисету
			sld.quest.chimiset_die = "true";
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "quest", "prison2"); // в закрытую клетку
			LAi_SetGroundSitTypeNoGroup(sld);
			sld = characterFromId("Capper");
			sld.dialog.currentnode = "prisoner"; //даем ноду Капперу
			LAi_LocationFightDisable(&Locations[FindLocation("Tartarusprison")], true);//запретить драться
			// прерывания на локаторы тартаруса
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator = "reload51";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance1.function = "LSC_TartarusEntrance1_Open";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator = "reload52";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance2.function = "LSC_TartarusEntrance2_Open";
			AddQuestRecord("SharkHunt", "19");
		break;
		
		case "entrance_10":
			dialog.text = "Also, waren Sie schon auf 'Tartarus'?";
			link.l1 = "Ja. Ich habe Chad deine Befehle gegeben und ich habe mit dem schwarzen Mann gesprochen.";
			link.l1.go = "entrance_11";
		break;
		
		case "entrance_11":
			dialog.text = "Hat der Zauberer dir etwas Interessantes erzählt?";
			link.l1 = "Oh, ja. Er hat mir gesagt, wo ich das Teleportationsidol von Kukulcan finden kann. Es war auf dem Schiff 'San Geronimo', das in der Nähe des Narwal-Territoriums auf einer Sandbank gesunken ist.";
			link.l1.go = "entrance_12";
		break;
		
		case "entrance_12":
			dialog.text = "Ha-ha-ha, großartig! Also ist dein 'Portal' jetzt am Boden? Nun, Kumpel, ich fürchte, du bist auf dieser Insel eingesperrt. Also schließe dich mir und meinen Männern an...";
			link.l1 = " Ich werde einen Weg finden, um zur Idole zu gelangen. Ich werde den Weg finden. Jetzt. Chimiset hat mir gesagt, dass du Kapper nicht vertrauen solltest, weil er gesehen hat, wie Chad einige Alan Milrow, den Kopf der Narwale, mit eigenen Augen tötet.";
			link.l1.go = "entrance_13";
		break;
		
		case "entrance_13":
			dialog.text = "Was?! Chad hat Alan getötet? Dieser Zauberer ist verrückt! Das kann einfach nicht wahr sein!";
			link.l1 = "Weißt du, Steve, Chimiset hat wirklich Angst. Ich glaube nicht, dass er mich angelogen hat.";
			link.l1.go = "entrance_14";
		break;
		
		case "entrance_14":
			dialog.text = "Verdammt, das sind wirklich schlechte Nachrichten! Alans Mord hat meinen Ruf unter den Narwals bereits ruiniert - einige von ihnen haben entschieden, dass ich dafür verantwortlich war, und jetzt stellt sich heraus, dass einer meiner Offiziere das getan haben könnte!";
			link.l1 = "Es scheint, dass die Leute dir gerne die Sünden anlasten, die nicht deine sind...";
			link.l1.go = "entrance_15";
		break;
		
		case "entrance_15":
			dialog.text = "Ja, das ist beunruhigend...";
			link.l1 = "Und jetzt die 'schönste' Nachricht für dich - der alte Mann hat mir erzählt, dass er einige Gespräche belauscht und herausgefunden hat, dass einige deiner Männer vorhatten, dich zu töten. Er wird dir mehr erzählen, aber nur, wenn du ihn freilässt, und unter vier Augen.";
			link.l1.go = "entrance_16";
		break;
		
		case "entrance_16":
			dialog.text = "Großartig! Und das alles nur wegen dir! Nichts für ungut, ich mache nur Spaß. Mir dreht sich der Kopf: Chad hat Alan getötet, meine Männer planen einen Mordanschlag auf mein Leben... Hat dir der alte Schwarze irgendwelche Details erzählt?";
			link.l1 = "Nein. Er fürchtet Chad zu sehr, soweit ich verstanden habe.";
			link.l1.go = "entrance_17";
		break;
		
		case "entrance_17":
			dialog.text = "Gut. Ich werde Rivados sagen, dass ich mich mit Chimiset treffen möchte. Mal sehen, was er mir sagt. Und was den Versuch angeht... gut, ich werde vorsichtig sein. Also, was wirst du jetzt tun, "+pchar.name+"?";
			link.l1 = "Noch nichts Besonderes. Ich werde mich auf der Insel umsehen und die Einheimischen kennenlernen - vielleicht fällt mir eine Idee ein, wie ich von hier wegkomme. Und ich muss zuerst Nathan Hawk finden, er ist der Grund, warum ich hier bin.";
			link.l1.go = "entrance_18";
		break;
		
		case "entrance_18":
			dialog.text = "Ich verstehe. Vergiss nicht, mich zu besuchen, wenn du einen Weg von dieser Insel findest - Ich gebe dir die Segelanweisungen, ohne die du nicht hierher zurückkehren kannst. Ich werde dir auch einige wichtige Details erzählen.";
			link.l1 = "Gut. Ich werde dich sicher besuchen, Steve!";
			link.l1.go = "entrance_19";
		break;
		
		case "entrance_19":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			// прерывание на вызов к Акуле
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			pchar.quest.LSC_GotoShark.win_condition.l1.date.hour  = 9.00;
			pchar.quest.LSC_GotoShark.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l2 = "location";
			pchar.quest.LSC_GotoShark.win_condition.l2.location = "LostShipsCity_town";
			pchar.quest.LSC_GotoShark.function = "LSC_GotoShark";
			AddQuestRecord("SharkHunt", "21");
		break;
		
		case "entrance_20":
			dialog.text = "Es ist gut, dass du gekommen bist, "+pchar.name+". Ich habe auf dich gewartet. Schlechte Nachrichten. Chimiset ist tot, Chad Kapper ist spurlos verschwunden.";
			link.l1 = "Verdammt... Ich bin sicher, dass Chad Chimiset getötet hat! Der alte schwarze Mann hatte nicht ohne Grund solche Angst.";
			link.l1.go = "entrance_21";
		break;
		
		case "entrance_21":
			dialog.text = "Ich habe daran keinen Zweifel. Verdammt, die Situation verschlechtert sich stündlich. Ich hatte fast feste und direkte Kontakte zu Black Eddie arrangiert und jetzt das. Nun, wir können die Freundschaft mit den Rivados vergessen\nSie wissen, dass du mit Chimiset gesprochen hast, bevor er gestorben ist, und sie betrachten dich als einen meiner Männer, also vermeide es, sie zu kontaktieren.";
			link.l1 = "Ja, was für ein Jammer...";
			link.l1.go = "entrance_22";
		break;
		
		case "entrance_22":
			dialog.text = "Ich habe dich nicht nur gebeten zu kommen, um Neuigkeiten zu erzählen. Ich habe einen Brief von unserem Vermittler und Diplomaten, Giuseppe Fazio, erhalten, er lädt mich ein, seine Hütte in Carolina um Mitternacht zu besuchen. Er erwähnt auch, dass ich alleine kommen muss, weil mein Leben auf dem Spiel steht und niemandem vertraut werden kann\nDas macht Sinn, Chimiset hat uns vor einem Verräter in meiner Nähe gewarnt. Dennoch riecht es zu verdächtig... alleine, um Mitternacht... Normalerweise kommt der dicke Mann selbst zu mir. Trotzdem werde ich um deine Hilfe bitten\nTechnisch gesehen bist du nicht einer meiner Männer und du bist neu hier. Jan hat dich als findigen und mutigen Mann mit guten Fechtkünsten beschrieben. Ich möchte, dass du mich um Mitternacht zum Treffen begleitest...";
			link.l1 = "Du musst mich nicht fragen, Steven. Ich bin dabei. Mir gefällt diese Einladung auch nicht - sie riecht nach einer Falle.";
			link.l1.go = "entrance_23";
		break;
		
		case "entrance_23":
			dialog.text = "Vielleicht irre ich mich und es ist keine Falle, aber ich sollte besser vorbereitet sein. Ich bin froh, dass du zugestimmt hast. Komm um Mitternacht an Deck der 'San Augustine', und wir werden Fazio sehen, seine alte Badewanne ist nicht weit von hier.";
			link.l1 = "Abgemacht. Ich werde um Mitternacht und gut bewaffnet an Deck der 'San Augustine' sein.";
			link.l1.go = "entrance_24";
		break;
		
		case "entrance_24":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			SetFunctionTimerCondition("LSC_MeetingSharkAugustine", 0, 0, 1, false); // таймер
			AddQuestRecord("SharkHunt", "22");
		break;
		
		case "caroline":
			dialog.text = "Schön dich zu sehen, "+pchar.name+". Lass uns keine Zeit verschwenden und sehen, was dieser dicke Mann Fazio zu sagen hat. Folge mir!";
			link.l1 = "Lass uns gehen, Steve. Halt deine Waffe bereit...";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload25", "CarolineBank", "barmen", "bar2", "LSC_CarolineOpen", -1);
		break;
		
		case "caroline_2":
			dialog.text = "Und wo ist dieser verdammte Dicke? Wo ist er hin? Wir sind seine Gäste und er begrüßt uns nicht. Siehst du ihn, "+pchar.name+"? Vielleicht sollten wir seine Truhen überprüfen, er könnte in ihnen sein...";
			link.l1 = "Er wird sowieso nicht in der Lage sein, irgendeine Truhe auf der Welt zu öffnen. Ruhe! Steven! Draußen ist Lärm...";
			link.l1.go = "caroline_3";
		break;
		
		case "caroline_3":
			dialog.text = "Verdammt! Du hast recht. Es scheint, dass wir in Schwierigkeiten sind."+pchar.name+".";
			link.l1 = "..., Freund.";
			link.l1.go = "caroline_4";
		break;
		
		case "caroline_4":
			DialogExit();
			LAi_SetPlayerType(pchar);
			// запускаем Мэри, Чада и нарвалов - будет лютое рубилово
			sld = characterFromId("Capper");
			sld.cirassId = Items_FindItemIdx("cirass1");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload3");
			sld = characterFromId("Mary");
			sld.greeting = "mary_4";
			int iScl = MOD_SKILL_ENEMY_RATE*10 + 2*sti(pchar.rank);
			LAi_SetHP(sld, 250+iScl, 250+iScl); // усилим
			sld.dialog.currentnode = "caroline";
			ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload2");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "caroline_5":
			dialog.text = "Argh! Wir haben es geschafft... Um ehrlich zu sein, ich dachte, wir wären sicher tot.";
			link.l1 = "Ich war schon in schlimmeren Schwierigkeiten. Aber ich gebe zu, diese Bastarde waren hart. Chimiset hatte recht, uns zu warnen - Chad ist ein Verräter. Wer war das Mädchen, das sie befehligt hat?";
			link.l1.go = "caroline_6";
		break;
		
		case "caroline_6":
			dialog.text = "Ihr Name ist Mary Casper, auch bekannt als Rote Mary, die Ex-Freundin des verstorbenen Alan Milrow. Ich verstehe, warum Chad hierher gekommen ist, er wollte meine Position einnehmen, aber was hat sie hier gemacht?";
			link.l1 = "Es ist klar genug. Du hast gesagt, dass sie seine Geliebte war, ihre Absichten sind klar - Rache. Das arme Mädchen wusste nicht, dass sie auf derselben Seite mit dem Mörder ihres Freundes kämpfte.";
			link.l1.go = "caroline_7";
		break;
		
		case "caroline_7":
			dialog.text = "Macht Sinn. Nun, jetzt werden sie für alles bezahlen! Ich werde aufhören, ihnen Vorräte und Proviant zu verkaufen - lass sie verhungern. Meine Männer können jede Belagerung aushalten, falls die Narwale versuchen, den San Augustine zu stürmen, werden wir sie wie Hunde erschießen\nSie werden es bereuen, mich auf so niedrige Weise hintergangen zu haben. Ich werde Fazios fetten Arsch an die Wand hinter meinem Stuhl nageln!";
			link.l1 = "Warte, Steve. Es scheint, dass es nicht so klar ist. Gib mir einen Tag und ich werde versuchen, dieses Durcheinander zu untersuchen. Ich bin sicher, dass Chad der einzige verantwortliche Mann ist. Er hat Milrow getötet, das Gerücht verbreitet, dass du es warst, hat Alans Freundin benutzt...";
			link.l1.go = "caroline_8";
		break;
		
		case "caroline_8":
			dialog.text = "Gut. Untersuche. Vielleicht haben wir noch nicht alle Verschwörer gefunden. Und ich werde etwas Rum trinken gehen. Und, "+pchar.name+": Ich schulde dir. Du kannst auf mich in allem zählen. Du hättest den Posten des Bootsmanns bekommen, wenn du in meiner Mannschaft gewesen wärst.";
			link.l1 = "Danke für diese hohe Resonanz! Wir werden sowieso zusammenarbeiten, wenn du Oberhaupt der Bruderschaft der Küste wirst. Geh und ruh dich aus und ich werde diese Kabine überprüfen, vielleicht finde ich etwas Nützliches.";
			link.l1.go = "caroline_9";
		break;
		
		case "caroline_9":
			dialog.text = "Gut. Ich schicke meine Männer hierher, um vor dem Morgen aufzuräumen - wir wollen die Leute nicht mit Leichen erschrecken. Nun, die Krabben werden heute Abend ein feines Mahl haben! Bis dann!";
			link.l1 = "Bis dann...";
			link.l1.go = "caroline_10";
		break;
		
		case "caroline_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SanAugustineResidence", "sit", "sit1", "LSC_SharkReturnSit", 10.0);
			AddQuestRecord("SharkHunt", "24");
		break;
		
		case "narval":
			dialog.text = "Nun, "+pchar.name+", Ich nehme an, deine Untersuchung war fruchtbar?";
			link.l1 = "Das kann man wohl sagen. Narwale waren nicht an dem Mordversuch auf dein Leben beteiligt. Außer Mary und den Kerlen, die uns auf der 'Carolina' begegnet sind. Ich denke, sie hat sie dazu angestiftet, uns anzugreifen. Fazio wurde gezwungen, dir die Einladung zu schicken. Ich habe den Brief in seiner Kabine gefunden, der vieles erklärt. Lies ihn.";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "(liest)... Hm. Das sieht aus wie ein Fazio-Typ. Klar, was könnte er gegen Chad ausrichten... er hat seine fette Haut gerettet. Es scheint, dass es alles wegen meines Bootsmanns war...";
			link.l1 = "Du siehst es jetzt selbst. Die Motive sind klar, und wir wissen, warum Chad Chimiset und Alan getötet hat. Kapper wollte Admiral der Insel werden. Ich habe den Anführer der Narwale - Donald Greenspen - besucht. Er schwor, dass weder er noch einer seiner Männer gegen dich verschworen waren.";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "Vertraust du ihm?";
			link.l1 = "Ich tue es. Donald wird deinen Namen von den Anschuldigungen des Todes von Alan klären. Er ist bereit, dich persönlich zu besuchen und dir offizielle Entschuldigungen zu bringen. Du wurdest auch ohne Grund beschuldigt, erinnerst du dich?";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "Gut, einen Krieg zu erklären wäre ein bisschen zu viel. Wir sind nicht in der Lage, ein Blutvergießen zu beginnen. Außerdem sieht es so aus, als wären nur ein paar Abschaum dafür verantwortlich, nicht der ganze Clan\nDu sagst, dass Donald bereit ist sich zu entschuldigen? Gut, lass uns das nutzen, um positive Beziehungen zu den Narwals aufzubauen, die Rivados sind uns sowieso verloren.";
			link.l1 = "Das ist ein guter Punkt, Steven. Jetzt ist die perfekte Zeit dafür.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "Gut. Sag Donald, dass ich bereit bin, ihn zu sehen und Frieden zu schließen.";
			link.l1 = "Ich bin auf dem Weg.";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "Warte, "+pchar.name+". Du hast gut gearbeitet und ich möchte dich mit feinem Gold bezahlen. Hier, nimm diese fünfhundert Dublonen.";
			link.l1 = "Danke dir!";
			link.l1.go = "LSC_navy";
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("SharkHunt", "27");
			pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "shark_16"; // ноду Дональду Гринспи
			SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
			AddSimpleRumourCityTip("They say that admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------вариант M----------------------------------------------------
		case "mary":
			dialog.text = "In meinem Gefängnis 'Tartarus'. Du kannst dorthin gehen und ihn sehen. Ich gebe dir den Schlüssel und Chad Kapper wird dir nicht im Weg stehen...";
			link.l1 = "Warte, Steven. Ich glaube, ich sollte noch nicht zu Chad Kapper gehen...";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "Und warum solltest du nicht? Was, magst du ihn nicht?";
			link.l1 = "Eigentlich mag er dich nicht. Ich habe schlechte Nachrichten für dich. Chad Kapper plant, einen Mordanschlag auf dich zu verüben.";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "Was?! Erklär dich. Wer hat das gesagt?";
			link.l1 = "Lass mich dir die ganze Geschichte erzählen. Das wäre besser.";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "Nun, erzähl mir dann...";
			link.l1 = "Nachdem ich mich im überfluteten Laderaum gefunden hatte, kam ich durch das Loch heraus und schwamm zwischen den Schiffswracks, um einen sicheren Ort zu finden. Schließlich kletterte ich auf die alte Flöte und gelangte ins Schiff. Dort war ein Kampf zwischen einem Mädchen in einer roten Jacke und zwei großen Kerlen...";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1.go = "mary_4"; // Мэри жива
			else link.l1.go = "mary_15";
		break;
		
		case "mary_4":
			dialog.text = "Heh, es scheint, dass die Rote Mary endlich jemanden verärgert hat.";
			link.l1 = "Ich habe ihr geholfen und wir haben diese Bastarde erledigt. Danach hatten wir ein interessantes Gespräch... Sag mir, Steve, wer sind diese Narwale und Rivados, sie hat diese Worte so oft benutzt, dass ich zu schüchtern war, sie zu fragen, was sie eigentlich bedeuten.";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "Die Gruppen von Einheimischen, die schon lange hier leben. Sie sind die Nachkommen der allerersten Siedler der Insel. Narwale sind meistens Engländer, Holländer und Franzosen, Rivados sind alle schwarz. Diese Clans haben ihre eigenen Anführer, ihre eigenen Schiffe und sie lassen andere nicht auf ihre Territorien. Du musst ihre Passwörter kennen, falls du die Schiffe der Clans besuchen möchtest. Sie ändern sie jede Woche.";
			link.l1 = "Ich verstehe jetzt. Ich nehme an, dass Mary bei den Narwalen ist?";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "Ja, dieses ausdrucksstarke Mädchen ist aus ihrem Clan. Also, was hat sie dir erzählt?";
			link.l1 = "Chad Kapper hat Alan Milrow, ihren Geliebten, getötet, den du gefangen genommen hast. Danach verbreitete er Gerüchte über deine Beteiligung daran. Chad hat Mary getäuscht und versucht, ihren Rachedurst zu nutzen.";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "Verdammt! Er hat Alan getötet? Aber warum? Um mir die Schuld zu geben?";
			link.l1 = "Um die Narwale gegen dich aufzubringen und ihr Vertrauen zu gewinnen. Kappers endgültiges Ziel ist es, dich zu beseitigen und deine Position einzunehmen. Mary hat sich geweigert, an seinem Plan teilzunehmen und seine Geliebte zu werden - deshalb hat er die Narwale beauftragt, sie zu töten.";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "Hat sie dir das erzählt?";
			link.l1 = "Ja. Und es sah nicht so aus, als würde sie lügen. Außerdem gab sie mir einen Brief von Chad Kapper. Ich habe ihn bereits gelesen, also solltest du das Gleiche tun.";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Hm. Ja, das sind Chads Schriften. Ich kenne seine bauerliche Handschrift sehr gut (liest) Argh! Unglaublich! Bastard! Verräter! Nun, ich werde ihn mit seinen eigenen Eingeweiden aufhängen! Layton! Sammle fünf Männer! Andererseits, Layton, warte, entlassen!\nWir werden es auf kluge Weise tun. Ich hatte vor, unsere Beziehungen zu Rivados zu verbessern, das ist eine Chance. Ihr Zauberer Chimiset wird in Tartarus festgehalten. Ein Gefängnis. Wir werden Rivados ihren Mann selbst befreien lassen und dabei werden sie den Verräter töten\nLayton! Geh nach Tartarus und nimm alle unsere Wachen von ihrem Oberdeck! "+pchar.name+", du wirst auch daran teilnehmen und ich bin dabei, dir eine sehr wichtige Rolle zuzuweisen. Finde den Anführer der Rivados, Black Eddie, und verhandle mit ihm...";
			link.l1 = "Ich? Hm. Aber ich kenne hier niemanden!";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "So you will get to know some people soon - actually you will get to know the very first man of the entire Rivados clan. You are the most suitable candidate to perform the diplomatic part of my plan. My pirates won't be able to come through Rivados territories easily; also I don't have men with decent oratory skills.";
			link.l1 = "Nun gut. Ich kümmere mich darum. Was soll ich tun?";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			GiveItem2Character(pchar, "key_capper");
			Log_Info("You have received 50 doubloons");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 50);
			dialog.text = "Nimm diesen Schlüssel. Er öffnet jede Tür auf dem 'Tartarus'. Nimm auch diese fünfzig Dublonen. Zuerst solltest du zur 'Carolina' gehen, kaufe ein Passwort, um Zugang zum Rivados-Territorium zu erhalten. Rede mit Fazio, er ist unser Vermittler, ein Passwort wird dich fünfzig Dublonen kosten. Dann solltest du zum 'Beschützer'\nDas ist die Residenz von Black Eddie. Sag ihm, dass Chad Kapper auf der Seite der Narwale ist, hat aufgehört, meinen Befehlen zu folgen und wird Chimiset ermorden. Gib ihm den Schlüssel, sag ihm, er soll eine anständige Anzahl seiner Kämpfer mitnehmen und den 'Tartarus' angreifen\nWir werden zwei Fliegen mit einer Klappe schlagen: Rivados wird uns als ihre Verbündeten ansehen und Kapper wird durch die Hände der Negros sterben. Kann nicht sagen, dass ich den Mann beneide. Verstanden?";
			if (pchar.questTemp.LSC.Mary == "alive")// Мэри жива
			{
				link.l1 = "Ich verstehe - aber wo finde ich 'Protector' und 'Carolina'?";
				link.l1.go = "mary_12";
			}
			else
			{
				link.l1 = "Hör zu, Steve, sag mir, wer sind diese Rivados und Narwale. Du redest die ganze Zeit über sie, aber ich habe immer noch keine Ahnung, wer sie sind.";
				link.l1.go = "mary_12_1";
			}
		break;
		
		case "mary_12_1":
			dialog.text = "Narvals und Rivados sind die lokalen Clans. Die Clans leben hier schon seit sehr langer Zeit. Sie repräsentieren die Nachkommen der ersten Siedler. Narvals sind hauptsächlich Engländer, Niederländer und Franzosen, Rivados sind alle Neger. Jeder Clan hat einen Anführer, sie halten mehrere Schiffe und lassen andere nicht in ihr Gebiet\nDu musst die Passwörter kennen, um sie zu besuchen. Sie ändern die Passwörter jede Woche.";
			link.l1 = "Nun sehe ich. Sag mir - wo finde ich 'Protector' und 'Carolina'?";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "So einfach wie Kuchen. Verlasse meine Residenz, überquere eine Brücke und biege links ab. Das wird Carolina sein. Den Protector zu finden ist ein bisschen kniffliger: Nachdem du eine Brücke überquert hast, biege rechts ab und gehe über Bretter nach Santa Florentina\nFinde dort die Rivados Soldaten. Sie werden nach einem Passwort fragen. Sag es laut und deutlich. Dann geh ins Innere der Fury und betrete den Protector durch das Heck.";
			link.l1 = "Nun, ich sehe jetzt. Ich glaube, dass sie mir nicht fehlen werden.";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "Sehr gut, dann. Mach weiter, Freund!";
			link.l1 = "Bis dann!";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			DialogExit();
			NextDiag.CurrentNode = "dodson_warwait";
			AddQuestRecord("SharkHunt", "32");
			sld = characterFromId("Eddy");
			sld.dialog.currentnode = "capper"; // ноду Эдди
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			pchar.questTemp.LSC = "mary_go"; //меняем флаг
		break;
		
		case "dodson_warwait":
			dialog.text = "Bist du immer noch hier? Geh jetzt nach Rivados!";
			link.l1 = "Ich bin auf dem Weg!";
			link.l1.go = "exit";
			NextDiag.TempNode = "dodson_warwait";
		break;
		
		case "mary_15":
			dialog.text = "Heh, es scheint, dass Rote Mary endlich jemanden verärgert hat.";
			link.l1 = "Ja. Sie hat Chad Kapper verärgert. Ich hatte mich dem Kampf angeschlossen, aber leider konnte ich das Mädchen nicht retten, einer der Angreifer hat sie mit seinem Säbel geschnitten.";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "Es tut mir sicherlich leid um sie, aber es war zweifellos ihr Fehler. Mary hat immer nach Ärger gesucht. Und was ist mit Chad Kapper? Das ist tatsächlich mein Bootsmann.";
			link.l1 = "Dein Bootsmann? He-he... Hier, lies diesen Brief. Ich habe ihn auf dem Körper des Mädchens gefunden. Du wirst jetzt sehen, wer sie töten lassen hat und warum. Kapper plant einen Anschlag auf dein Leben.";
			link.l1.go = "mary_9";
		break;
		
		// Каппер сбежал
		case "Chad_escape":
			dialog.text = "Wo bist du so lange gewesen? Mir wurde gesagt, dass Rivados ihren Zauberer freigelassen hat...";
			link.l1 = "Ich wurde als Geisel auf dem 'Protector' gehalten, um ihre Sicherheit vor einem Hinterhalt zu gewährleisten. Sie haben Chimiset befreit, ja, aber Chad hat es geschafft zu entkommen.";
			link.l1.go = "Chad_escape_1";
		break;
		
		case "Chad_escape_1":
			dialog.text = "Scheiße! Niemals mit Schwarz handeln, sagen sie... Sie konnten nicht mal eine so einfache Aufgabe erledigen! Verdammt noch mal, diese Rivados!";
			link.l1 = "Chad hat sich unter den Narwalen versteckt...";
			link.l1.go = "Chad_escape_2";
		break;
		
		case "Chad_escape_2":
			dialog.text = "Sicher, hat er! Er ist kein Narr und hat erkannt, dass Rivados ohne meine Hilfe nicht in den Tartarus hätte gelangen können. Jetzt wird er sich verstecken und aus dem Schatten heraus angreifen. Layton! Verstärke die Posten! Haltet die Augen jederzeit offen! Ich werde ein Vermögen dem Mann zahlen, der mit Kapper fertig wird!";
			link.l1 = "Gut, Steven. Ich muss darüber nachdenken. Vielleicht kann ich Chad aufspüren. Bis dann.";
			link.l1.go = "Chad_escape_3";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Chad_escape_3":
			DialogExit();
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				pchar.questTemp.Saga.SharkHunt = "mary_whiskey"; // к Мэри
				AddQuestRecord("SharkHunt", "34");
			}
			else
			{ // не уберег Мэри - допетривай сам, куда идти
				pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			}
			NextDiag.CurrentNode = "Total_wait";
			// добавим немного атмосферы - уберем Акселя до утра
			sld = characterFromId("Axel");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "goto", "goto5");
			sld = GetCharacter(NPC_GenerateCharacter("AxelHelper", "citiz_52", "man", "man", 35, PIRATE, 1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_21", "pistol4", "bullet", 200);
			sld.dialog.Filename = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "AxelHelper";
			LAi_SetOwnerType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "LSC_NARVAL");
			SetFunctionTimerCondition("LSC_AxelReturnStore", 0, 0, 1, false); // таймер на возврат Акселя
		break;
		
		case "whiskey":
			dialog.text = "Was ist passiert, "+pchar.name+"? Du siehst aus, als würdest du von Luzifer selbst gejagt.";
			link.l1 = "Haben sie dir ein Fass Whiskey gebracht?";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "Welches Fass?";
			link.l1 = "HABEN SIE DIR EIN FASS WHISKEY GEBRACHT?!";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Warum schreist du so, Kumpel? Nein, das haben sie nicht. Was ist los?";
			link.l1 = "Gott sei Dank bin ich rechtzeitig gekommen... Chad Kapper hat ein Fass Bushmills von Axel Yost gekauft...";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Bushmills? Das ist mein Lieblingsgetränk! Ich habe es seit Ewigkeiten nicht mehr getrunken!";
			link.l1 = "Ja-Ja. Und Kapper weiß das auch. Er bat auch seinen Kumpel Marcello Zyklop, etwas Arsen von Sancho Carpentero zu kaufen. Siehst du, warum?";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "Glaubst du, er wird mich vergiften?";
			link.l1 = "Kein Zweifel! Deshalb hatte ich es so eilig. Wenn sie dir ein Fass Whiskey bringen - trink es nicht. Es ist vergiftet.";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = "Heh, danke für die Warnung! Ich werde vorsichtig sein. Warte, wohin gehst du jetzt?";
			link.l1 = "Ich muss Kapper und Zyklop finden. Ich habe eine Idee, wo ich sie finden kann. Wir sehen uns!";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			DialogExit();
			pchar.questTemp.LSC.Dodson_warning = "true"; // Акула предупрежден
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "45");
		break;
		
		case "whiskey_7":
			dialog.text = "Ha! Ich bin froh, dich zu sehen, Kumpel! Sieht so aus, als ob ich dir mein Leben schulde.";
			link.l1 = "Haben sie Whisky mitgebracht?";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "Sie haben! Bushmills, genau wie du gesagt hast. Unser lieber Fazio war so nett... Ich habe ihn verhaftet, um zu ermitteln...";
			link.l1 = "Hat er gestanden?";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			dialog.text = "Ja. Er sagt, dass Kapper ihn dazu gezwungen hat. Er hatte Angst und... brachte mir das Fass als Geschenk von den Narwals.";
			link.l1 = "Kapper ist tot. Ich habe ihn und seine Narwal-Freunde ausgelöscht. Jetzt bleibt nur noch ein Bastard übrig - Zyklop Marcello... Ich bin sicher, dass dieses fette Schwein seinen Aufenthaltsort kennt. Lass mich ihn ein bisschen drängen!";
			link.l1.go = "whiskey_10";
		break;
		
		case "whiskey_10":
			dialog.text = "Sicher. Versuche nur, ihn nicht zu töten, unser armer Fazio ist eher in schlechter Gesundheit.";
			link.l1 = "Ich werde sanft sein... sehr sanft, verdammt nochmal!";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			chrDisableReloadToLocation = true;//закрыть локацию
			sld = CharacterFromID("Facio");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "poison":
			pchar.questTemp.LSC.Dodson_poison = "true"; // разговор состоялся
			dialog.text = "Argh... "+pchar.name+", Freund, mit mir stimmt etwas ganz und gar nicht..";
			link.l1 = "Steven! Hast du den Whiskey getrunken? Verdammt, hast du ihn wirklich getrunken?!";
			link.l1.go = "poison_1";
		break;
		
		case "poison_1":
			dialog.text = "Ja... Das ist der beste irische Whiskey... Giuseppe Fazio hat ihn mir heute gebracht. Er sagte, es sei ein Geschenk vom Narwal-Anführer... ein Friedenszeichen... oh, das tut weh... Sieht aus, als wäre es das Ende von mir.";
			link.l1 = "Verdammt! Der Whisky war mit Arsen vergiftet! Chad Kapper und Marcello Cyclops haben das getan!";
			link.l1.go = "poison_2";
		break;
		
		case "poison_2":
			dialog.text = "Verdammt... der Bootsmann hat mich endlich erwischt... Scheiße!";
			if (CheckCharacterItem(pchar, "ultimate_potion"))
			{
				link.l1 = "Du wirst nicht sterben! Hörst du mich? Du wirst nicht sterben! Schnell, nimm diese Flasche. Das ist das mächtigste Heiltrank der Welt, es heilt alles. Trink es... jetzt!";
				link.l1.go = "poison_3";
			}
			else
			{
				link.l1 = "Steven!";
				link.l1.go = "dodson_poison";
			}
		break;
		
		case "dodson_poison": // Акула умирает
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			SetFunctionTimerCondition("LSC_SetDexterAdmiral", 0, 0, 1, false); // через день Декстера в адмиралы
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				AddQuestRecord("SharkHunt", "41");
				sld = CharacterFromID("Facio");
				sld.dialog.currentnode = "whiskey";
				sld.greeting = "facio_2";
				sld.quest.poisonnode = 1;
			}
			else AddQuestRecord("SharkHunt", "42");
			pchar.questTemp.Saga.DodsonDie = "true"; // атрибут Саге что Акула погиб
		break;
		
		case "poison_3":
			RemoveItems(pchar, "ultimate_potion", 1);
			Log_Info("Comanche potion was used");
			Log_Info("Poison was cured!");
			PlaySound("interface\notebook.wav");
			dialog.text = "Oh... "+pchar.name+", es hat wirklich geholfen. Fühle mich immer noch ein bisschen krank, aber der Schmerz ist fast weg...";
			link.l1 = "Dieser Trank neutralisiert selbst die tödlichsten Gifte. Trink alles! Ja...";
			link.l1.go = "poison_4";
		break;
		
		case "poison_4":
			LAi_SetStayType(npchar);
			dialog.text = "Ein Wunder... Mir geht's jetzt gut. Danke, Freund, das werde ich nie vergessen...";
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				link.l1 = "Du solltest dich jetzt besser ausruhen. Du siehst aus wie ein toter Mann. Dieser Bastard Kapper wird uns nicht mehr bedrohen können - ich habe mich um ihn und um ein paar Narwale gekümmert. Nur Marcello Zyklop bleibt übrig. Du hast gesagt, dass Fazio dir den Whisky gebracht hat, richtig?";
				link.l1.go = "poison_5";
			}
			else
			{
				link.l1 = "Du solltest dich jetzt besser ausruhen. Du siehst aus wie ein toter Mann. Du hast gesagt, dass Fazio dir den Whisky gebracht hat, oder?";
				link.l1.go = "poison_7";
			}
		break;
		
		case "poison_5":
			dialog.text = "Ja. Ich hätte wirklich auf sein blasses Gesicht und seine zitternden Hände achten müssen...";
			link.l1 = "Es scheint, dass er dazu gezwungen wurde. Gut, ich werde diesen fetten Schwein besuchen und die Informationen von ihm holen. Ich bin sicher, dass er weiß, was ich brauche. Erhole dich gut!";
			link.l1.go = "poison_6";
		break;
		
		case "poison_6":
			DialogExit();
			sld = CharacterFromID("Facio");
			sld.dialog.currentnode = "whiskey";
			sld.greeting = "facio_2";
			sld.quest.poisonnode = 1;
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "40");
		break;
		
		case "poison_7":
			dialog.text = "Ja. Ich hätte wirklich auf sein blasses Gesicht und zitternde Hände achten müssen...";
			link.l1 = "Es scheint, dass er dazu gezwungen wurde. Gut, ich werde dieses fette Schwein schließlich kriegen, aber jetzt muss ich mich um Kapper und Zyklop kümmern. Ich weiß, wo sie sich verstecken. Erhol dich gut!";
			link.l1.go = "poison_8";
		break;
		
		case "poison_8":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "43");
		break;
		
		case "clear":
			dialog.text = "Was sagst du, "+pchar.name+"? Ich weiß schon, dass du dich mit Kapper auf 'Eva' befasst hast. Und da hast du nicht mal aufgeräumt, ha-ha! Um ehrlich zu sein, ich bewundere dich! Chad und seine Männer zu töten, ist das nicht etwas! Ja, Jan hatte recht, dich zu loben.";
			link.l1 = "Nicht nur habe ich mich mit Kapper auseinandergesetzt, sondern ich habe auch ein Attentat auf dein Leben verhindert. Du solltest vergiftet werden, Steven, aber ich habe die Bastarde daran gehindert, das zu tun.";
			link.l1.go = "clear_1";
		break;
		
		case "clear_1":
			dialog.text = "Mich vergiften? Aber wie?";
			link.l1 = "Chad hat ein Fass irischen Bushmills Whiskey von Axel gekauft...";
			link.l1.go = "clear_2";
		break;
		
		case "clear_2":
			dialog.text = "Bushmills? Das ist mein Lieblingsgetränk! Ich habe es seit Ewigkeiten nicht mehr getrunken!";
			link.l1 = "Ja-ja. Und Kapper weiß das auch. Er hat auch seinen Kumpel, Marcello Cyclops, gebeten, bei Sancho Carpentero Arsenik zu kaufen. Dann haben er und seine Kumpel Fazio genommen und sind in den Laderaum der 'Eva' hinuntergegangen. Er wollte den Whiskey vergiften und Fazio zwingen, ihn Ihnen als Geschenk von den Narwals zu bringen.";
			link.l1.go = "clear_3";
		break;
		
		case "clear_3":
			dialog.text = "Ha! Natürlich hätte ich sofort einen Pint Whiskey getrunken...";
			if (CheckCharacterItem(pchar, "cask_whisky"))
			{
				link.l1 = "Chad hatte darauf gehofft. Aber er hat versagt - er hatte nicht einmal Zeit, Arsen hineinzutun. Ja, und ich habe das Fass mitgenommen. Du kannst es als Geschenk haben.";
				link.l1.go = "clear_4";
			}
			else
			{
				link.l1 = "Chad hat darauf gezählt. Aber er hat versagt - er hatte nicht einmal Zeit, Arsen hinein zu stecken.";
				link.l1.go = "clear_7";
			}
		break;
	
		case "clear_4":
			RemoveItems(pchar, "cask_whisky", 1);
			PlaySound("interface\notebook.wav");
			dialog.text = "Zeig mir... "+pchar.name+", das ist ein echter Bushmills! Der beste irische Whiskey! Argh, ich habe jahrelang davon geträumt! Du, du.. Verdammt! Du hast Chad ausgeschaltet und so einen herrlichen Whiskey gefunden!\nIch werde dir einen meiner besten Talismane geben. Das ist Thors Hammer, er ist unvergänglich. Dein Kanonier wird ihn lieben!";
			link.l1 = "Danke! Ich bin auch sehr froh.";
			link.l1.go = "clear_5";
		break;
		
		case "clear_5":
			GiveItem2Character(pchar, "talisman3"); 
			PlaySound("interface\notebook.wav");
			Log_Info("You have received a 'Thor's hammer' amulet");
			dialog.text = "Ich freue mich darauf, ein Pint von diesem herrlichen Whiskey zu trinken... "+pchar.name+", wir werden heute Abend eine Party haben! Und du kommst morgen zu mir. In der Zwischenzeit werde ich über deine Worte und Chads Handlungen nachdenken...";
			link.l1 = "Gut, Steven, ich werde dich nicht beim... Entspannen stören, ha-ha!";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "53");
		break;
		
		case "clear_6":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			if (CheckAttribute(pchar, "questTemp.LSC.CyclopDie"))
			{
				SetFunctionTimerCondition("LSC_WhiskeyStoryFinal_1", 0, 0, 1, false); // адмирал зовет
				DeleteAttribute(pchar, "questTemp.LSC.CyclopDie");
			}
		break;
		
		case "clear_7":
			dialog.text = "Du hast mir etwas sehr Wichtiges erzählt. Ich werde über deine Worte und Chads Handlungen nachdenken... und dann werde ich dich rufen.";
			link.l1 = "Gut, Steven. Ich werde warten!";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "54");
		break;
		
		case "whyskey_final":
			dialog.text = "Ha, da bist du ja, "+pchar.name+". Jetzt sind alle hier und wir können anfangen. Ich habe dich und Layton herbeigerufen, um die Situation zu besprechen und zu entscheiden, was wir mit den Narwahlen machen sollen.";
			link.l1 = "Was meinst du - was soll man mit Narwalen machen?";
			link.l1.go = "whyskey_final_1";
		break;
		
		case "whyskey_final_1":
			dialog.text = "Ein Anschlag auf mein Leben wurde von Chad organisiert, der direkte Unterstützung von Narwhals hatte. Ich erkenne dies als offenen Akt der Aggression. Angesichts der Tatsache, dass wir eine kurzfristige Allianz mit Rivados haben, schlage ich folgendes vor\nWir bilden eine Allianz mit Rivados, bereiten eine Operation vor und vernichten den Narwhal-Clan ein für alle Mal. Ich habe genug von ihrer Banditenhaltung. Du, "+pchar.name+", wirst erneut die Rolle des Diplomaten spielen\nSprich mit Black Eddie und Chimiset, überzeuge sie, sich uns im Kampf gegen unseren gemeinsamen Feind anzuschließen. Ich denke, sie werden dir zuhören, sie halten dich für ihren Verbündeten\nDexter wird einen Angriffsplan ausarbeiten, er kennt die Geographie der Insel in- und auswendig. Layton, hast du schon irgendwelche Gedanken?";
			link.l1 = "";
			link.l1.go = "whyskey_final_2";
		break;
		
		case "whyskey_final_2": // перекидываем ноду Декстеру
			DialogExit();
			sld = characterFromId("Dexter");
			sld.greeting = "";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "whyskey_final_3":
			dialog.text = "Eine weise Idee. Gezwungen sich auf die San Gabriel zurückzuziehen, werden die Narwale vielleicht nicht so schnell unseren Truppen weichen - aber ohne Versorgung werden sie schnell sterben oder gezwungen sein, einen verzweifelten Angriff zu starten. Was sagst du, "+pchar.name+"?";
			link.l1 = "Was soll ich sagen... Ich sage, dass eine Kriegserklärung gegen Narwale ein politisch falscher Schritt ist.";
			link.l1.go = "whyskey_final_4";
		break;
		
		case "whyskey_final_4":
			dialog.text = "Und du sagst das, nachdem du alle Männer von Chad getötet hast? Vergiss nicht, dass sie alle Narwale waren!";
			link.l1 = "Nicht alle von ihnen. Einer der ersten dieser Bastarde, Marcello Zyklop, war kein Narwal. Tatsächlich war er Rivados treu und hatte vielleicht vor, sich ihnen anzuschließen. Er ist immerhin ein Mulatte. Ich denke, dass die Narwale nicht für ein Attentat auf dein Leben verantwortlich sind - nur ein paar Bastarde, die von Kapper angeworben wurden.";
			link.l1.go = "whyskey_final_5";
		break;
		
		case "whyskey_final_5":
			dialog.text = "Und was schlägst du vor? Ignorieren wir das alles?";
			link.l1 = "Ich schlage vor, mich in meiner Rolle als Diplomat zu belassen - aber diesmal werde ich mit dem Anführer der Narwale, Donald, verhandeln. Außerdem erlaube mir, dir meine Sichtweise bezüglich des möglichen Ausgangs eines Angriffs auf die Narwale zu erläutern.";
			link.l1.go = "whyskey_final_6";
		break;
		
		case "whyskey_final_6":
			dialog.text = "Mach weiter.";
			link.l1 = "Soweit ich sehe, ist der Frieden auf der Insel nur aufgrund der Rivalität zwischen zwei Clans möglich, die in ihren Stärken fast gleich sind. Deine Kämpfer sind die dritte Macht, und sie können einem von ihnen helfen, den Sieg zu erringen. Aber sowohl Rivados als auch Narwale sind stark und ein Sieg wird den Gewinner in jedem Fall zu sehr kosten.";
			link.l1.go = "whyskey_final_7";
		break;
		
		case "whyskey_final_7":
			dialog.text = "";
			link.l1 = "Der Preis für die Zerstörung der Narwale wird viele Leben deiner und der Rivados-Männer kosten. Außerdem sagte Layton, dass die Belagerung von San Gabriel lange dauern wird, und wir könnten auch möglicherweise Aggressionen von den Rivados gegenüberstehen, falls wir zu viele Männer verlieren...";
			link.l1.go = "whyskey_final_8";
		break;
		
		case "whyskey_final_8":
			dialog.text = "";
			link.l1 = "Vergiss nicht, dass beide Clans darauf erpicht sind, auf der Insel zu dominieren, und bis vor kurzem waren sie deine Feinde. Also, meiner Meinung nach, wäre das Gemetzel eine wahre Plage für die gewöhnlichen Einwohner.";
			link.l1.go = "whyskey_final_9";
		break;
		
		case "whyskey_final_9":
			dialog.text = "Hm. Deine Worte klingen weise, aber du hast mich noch nicht überzeugt.";
			link.l1 = "Ich muss auch irgendwie die Insel verlassen, also muss ich die Statue von Kukulcan auf dem Meeresgrund erreichen. Die Rivados können mir nicht helfen - vielleicht die Narwale? Sie zu bekämpfen wird mir auch nicht helfen.";
			link.l1.go = "whyskey_final_10";
		break;
		
		case "whyskey_final_10":
			if (pchar.questTemp.LSC.Mary != "die") sTemp = "Ha! And I guess that there is one more reason why you don't want to make Narwhals our enemies. That red-haired girl of Ceres Smithy, right, friend? Am I right? Don't worry about her, "+pchar.name+", since you care about her this much - we will take her in the safe place before fighting starts.\n";
			else sTemp = "";
			dialog.text = ""+sTemp+"Aber ich stimme zu, wenn du so entschlossen bist. Geh und besuche Donald Greenspen, den Kopf der Narwale. Seine Residenz befindet sich im Hintergrund von Esmeralda. Mal sehen, was dieser Schurke uns erzählen wird.";
			link.l1 = "Gut. Ich bin auf dem Weg.";
			link.l1.go = "whyskey_final_11";
		break;
		
		case "whyskey_final_11":
			DialogExit();
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations"; // ноду Гринспи
			sld = characterFromId("Dexter");
			LAi_SetHuberType(sld);
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "negotiations_wait";
			pchar.questTemp.LSC.Donald_enter = "true";
			AddQuestRecord("SharkHunt", "55");
		break;
		
		case "negotiations_wait":
			dialog.text = "Geh zu Donald, Kumpel, und lass ihn deine Stiefel lecken, ha-ha! Ich werde auf dich warten.";
			link.l1 = "Ich bin auf dem Weg.";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_wait";
		break;
		
		case "peace":
			dialog.text = "Na und, hast du mit Donald gesprochen? Ich sehe, dass du es hast...";
			link.l1 = "Ja. Er hat seinen Männern nicht befohlen, dir zu schaden. Alle Narwale, die an dem Versuch teilgenommen haben, wurden von Chad Kapper angeworben. Er ist sehr verärgert und versichert uns, dass die Narwale keine bösen Absichten gegen dich haben. Er ist bereit, dir seine persönlichen Entschuldigungen für diesen Mordversuch an deinem Leben und für den Verdacht auf Alans Mord zu bringen.";
			link.l1.go = "peace_1";
		break;
		
		case "peace_1":
			dialog.text = "Ist er bereit, hierher zu kommen und all diese Dinge zu sagen?";
			link.l1 = "Er schwor auf der Bibel.";
			link.l1.go = "peace_2";
		break;
		
		case "peace_2":
			dialog.text = "Heh, vielleicht wird das reichen. Es scheint, dass der einzige Schurke, dem die Schuld zuzuschreiben ist, mein ehemaliger Bootsmann ist.";
			link.l1 = "Ich bin mir völlig sicher, Steven. Wir brauchen diesen Krieg nicht. Niemand braucht ihn.";
			link.l1.go = "peace_3";
		break;
		
		case "peace_3":
			dialog.text = "Gut! Abgemacht. Ich bin bereit, Donald mit seinen Entschuldigungen zu akzeptieren, aber er sollte sich besser beeilen. Geh und sag ihm das.";
			link.l1 = "Sofort, Steven.";
			link.l1.go = "peace_4";
		break;
		
		case "peace_4":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "Take your Mary there and live your lives together, there is plenty of free space.";
			else sTemp = "";
			dialog.text = "Warte! "+pchar.name+", Ich bin sehr froh, dass du hier auf der Insel aufgetaucht bist. Jan hält sehr viel von dir, aber du hast alle Erwartungen übertroffen. Wenn du in meiner Mannschaft wärst... eigentlich biete ich dir Kappers Position an, solange du hier bist. Du wirst meine Garnison auf 'Tartarus' befehligen. "+sTemp+".";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1 = "Nein, Steven, vielen Dank, aber ich werde hier nicht lange bleiben. Such dir jemand anderen dafür. Und was Mary betrifft - wir kommen auf der 'Ceres Schmiede' gut zurecht.";
			else link.l1 = "Nein, Steven, vielen Dank, aber ich werde nicht lange hier bleiben. Finde jemand anderen dafür.";
			link.l1.go = "peace_5";
		break;
		
		case "peace_5":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Egal, Freund. So sei es. Bitte akzeptiere dieses Geschenk von mir. Ich denke, du wirst diese fünfhundert Dublonen nützlich finden.";
			link.l1 = "Danke!";
			link.l1.go = "LSC_navy";
			AddQuestRecord("SharkHunt", "57");
			pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations_17"; // ноду Дональду Гринспи
			AddSimpleRumourCityTip("They say that admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		case "LSC_navy":
			dialog.text = "Lass uns über unser Geschäft reden... Nimm diese Seekarten. Benutze sie, um hier mit dem Schiff und in einem Stück zurückzukehren\nOhne sie wirst du entweder keinen Weg hierher finden wegen der Riffe und Stürme rund um die Insel, also wird dein Schiff wahrscheinlich ihren Schwestern hier beitreten. Denk daran, dass du ein relativ kleines Schiff benutzen musst, um die Riffe zu passieren. Luggers, Schoner, Brigantine, Brig... Vierte Klasse, nicht größer\nDein Ziel ist es, diesen Ort mit diesen Seekarten in der Tasche zu verlassen und dann auf einem Schiff für mich zurückzukehren. Sobald ich zurück bin, werde ich mich dir und Svenson in eurem Spiel anschließen. Ich habe keine Ahnung, wie du die Insel verlassen kannst, allerdings. Nur du kannst dir in dieser Angelegenheit helfen, und vielleicht dieser Kukulcan von dir...";
			link.l1 = "Lustig, aber ich zähle tatsächlich auf seine Hilfe. Danke für die Segelanweisungen, Steven. Ich werde noch den Weg von dieser Insel finden.";
			link.l1.go = "LSC_navy_1";
		break;
		
		case "LSC_navy_1":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = "Ich wünsche Ihnen dann viel Glück. Beeil dich, wenn du kannst, meine Lagerhäuser leeren sich ziemlich schnell und bald gibt es überhaupt keine Vorräte mehr. Du weißt, wozu hungrige und bewaffnete Männer fähig sind, oder?";
			link.l1 = "Ich muss jetzt los. Bis dann!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
			AddQuestRecord("LSC", "5");
			// убираем квестовые предметы
			sld = ItemsFromID("key_capper");
			sld.price = 10;
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
		break;
		
		case "Dodson_wait":
			dialog.text = "Hast du den Weg von der Insel gefunden, "+pchar.name+"?";
			link.l1 = "Noch nicht, Steven. Ich bin noch dran.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
		break;
		
		// --> информационный блок
		case "Total_wait":
			dialog.text = "Nun, was hast du, "+pchar.name+"? Hast du interessante Neuigkeiten?";
			
			if (!CheckAttribute(npchar, "quest.items") && CheckAttribute(npchar, "quest.takeitems"))
			{
				link.l1 = "Steven, ich möchte dich bitten, mir meine beschlagnahmten Sachen zurückzugeben.";
				link.l1.go = "Items";
			}
			if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l2 = "Steven, erzähl mir mehr über diese Insel.";
				link.l2.go = "Story_island";
			}
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l3 = "Bist du sicher, dass Hawk nicht auf der Insel ist? Er kam durch das Portal, also muss er hier sein.";
				link.l3.go = "Natan";
			}
			if (!CheckAttribute(npchar, "quest.whiteboy"))
			{
				link.l4 = "Kennen Sie einen Mann mit dem Spitznamen Weißer Junge?";
				link.l4.go = "Whiteboy";
			}
			if (!CheckAttribute(npchar, "quest.ships"))
			{
				link.l5 = "Welche Territorien gehören hier den Narwalen und Rivados?";
				link.l5.go = "ships";
			}
			if (!CheckAttribute(npchar, "quest.parol"))
			{
				link.l6 = "Wie kann ich die Passwörter lernen, um an Bord der Clan-Schiffe zu kommen?";
				link.l6.go = "parol";
			}
			if (!CheckAttribute(npchar, "quest.map"))
			{
				link.l7 = "Hör zu, gibt es eine Karte von der Insel?";
				link.l7.go = "map";
			}
			if (!CheckAttribute(npchar, "quest.blade"))
			{
				link.l8 = "Du hast ein so interessantes Breitschwert. Ich habe noch nie so etwas gesehen...";
				link.l8.go = "blade";
			}
			link.l9 = "Keine Fragen bisher. Aber ich könnte bald einige haben...";
			link.l9.go = "exit";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Items":
			dialog.text = "Ach, ja, sicher! Ich habe es völlig vergessen... Deine Sachen sind oben in der Truhe. Du kannst sie nehmen. Layton wird dich nicht aufhalten.";
			link.l1 = "Danke!";
			link.l1.go = "exit";
			npchar.quest.items = "true";
			NextDiag.TempNode = "Total_wait";
			ref location = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(location, "private1.key");
			for (i=1; i<=10; i++) // можно лезть в сундук
			{
				sld = characterFromId("SharkSoldInside_"+i);
				DeleteAttribute(sld, "watchBoxes");
			}
		break;
		
		case "Story_island":
			dialog.text = "Diese Insel muss sehr alt sein. Ich habe alte Karavellen im äußeren Ring gesehen, sie sind mehr als hundert Jahre alt. Ihre Existenz ist möglich wegen eines großen Flachwassers und einer starken Strömung, die Schiffrahmen hierher bringt. Die Menschen leben hier schon lange. Es gibt diejenigen, die hier geboren wurden und nie gegangen sind.\nKlans wurden direkt nach der Expedition von de Betancourt gebildet, die hier endete. Übrigens waren die San Augustine und die Tartarus Teil dieser Expedition. Die Tartarus hatte viele schwarze Sklaven in ihren Laderäumen. Sie gründeten den Rivados-Klan zu Ehren von Pedro Rivados, ihrem Anführer. Er hatte einen Aufstand begonnen und versucht, die Tartarus zu erobern, aber sie scheiterten. Der Mann wurde zu einem langsamen Tod verurteilt.\nSklaven erlangten hier ihre Freiheit und stellten sich sofort gegen den Rest der Einheimischen. Ihr Streben nach Dominanz und afrikanische Traditionen brachten die meisten Christen dazu, sich zu vereinen und einen Narwal-Klan zu bilden.\nDer Narwal-Klan hatte viele Söldner, Soldaten, Offiziere und Abenteurer in seinen Reihen, sie sammelten Vorräte und bauten eine kleine, professionelle Armee auf, bereit, gegen Rivados mit ihrem zahlenmäßigen Vorteil zu kämpfen. Seitdem sind die Narwale bei der Aufnahme neuer Rekruten sehr wählerisch geworden und Rivados hat ihre Ambitionen begrenzt. Du kannst die Ergebnisse jetzt sehen.";
			link.l1 = "Gab es irgendwelche Verbindungen zwischen der Insel und der Außenwelt?";
			link.l1.go = "Story_island_1";
		break;
		
		case "Story_island_1":
			dialog.text = "Es gab in den letzten zehn Jahren keine Verbindungen. Die Einheimischen haben einmal mit Kuba gehandelt, Gold und wertvolle Waren gegen Lebensmittel getauscht. Aber sie tun es nicht mehr.";
			link.l1 = "Hm. Also scheint es, dass Svenson und Schwarzer Pastor beide recht hatten... Und warum haben die Leute die Insel nicht verlassen, als sie noch die Möglichkeit dazu hatten?";
			link.l1.go = "Story_island_2";
		break;
		
		case "Story_island_2":
			dialog.text = "Einige Leute taten es, aber die Mehrheit beschloss zu bleiben. Viele von ihnen haben hier ein Zuhause gefunden, viele andere wurden hier geboren. Sie wollen nicht zurückkehren. Dieser Ort scheint für sie viel besser zu sein... Einige Leute haben zu viel Angst, mit alten Booten durch die Sturmzone zu reisen. Was die Rivados betrifft - sie haben keine andere Wahl, als hier zu bleiben.";
			link.l1 = "Und warum bist du hierher gekommen? Du hast deine ausgezeichnete Fregatte verlassen und stattdessen eine Brigg gewählt...";
			link.l1.go = "Story_island_3";
		break;
		
		case "Story_island_3":
			dialog.text = "Ich wurde des Mordes an Blaze Sharp beschuldigt. Ich habe keine Ahnung, warum. Offensichtlich spielt jemand schmutzige Spielchen. Die Zahl meiner Feinde begann rapide zu steigen, also musste ich Isla Tesoro verlassen und hier warten. Ich kenne diesen Ort schon seit sehr langer Zeit. Ich habe meine Fregatte verlassen, weil sie zu groß war, um die örtlichen Riffe zu umschiffen\nKaum war ich hier, wurde ich von Narwhals und Rivados angegriffen. Sie schätzten meine Ankunft nicht. Sie kamen nachts mit Langbooten nahe an mein Schiff heran und setzten es in Brand. Wir haben ihre Kähne mit unseren Kanonen und Musketen zerschmettert. Aber das Feuer hat seine Arbeit getan - meine Brigantine wurde niedergebrannt\nWir wurden wütend wie die Hölle, stürmten die Insel, stürmten San Augustine und zeigten ihnen, wie Korsaren kämpfen. Sie konnten unserem Druck nicht standhalten und zeigten bald wie Feiglinge ihren Rücken. Wir eroberten San Augustine, stellte sich heraus, dass diese Idioten sie als Proviantlager benutzten. Jetzt müssen sie es von mir zu einem Preis kaufen, den ich festlege\nWir haben auch die lokalen Anführer gefangen genommen: den Leiter der Narwhals Alan Milrow und den spirituellen Anführer der Rivados Chimiset. Layton verbrachte die nächsten Tage mit der Aufklärung der Gegend und wir griffen Tartarus an - eine Schwachstelle in ihrer Verteidigung\nJetzt haben wir zwei dieser Schiffe und die Clans müssen sich an unsere Anwesenheit gewöhnen. Heutzutage haben wir hier so etwas wie Frieden. Was die anderen Einheimischen betrifft, so scheinen sie die Idee einer dritten Kraft zu mögen.";
			link.l1 = "Jetzt verstehe ich. Danke für die Geschichte!";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Natan":
			dialog.text = "Ich kann es nicht sicher sagen, aber ich habe ihn hier jedenfalls nicht gesehen. Nicht auf den Straßen, weder in der Taverne noch auf den Clan-Schiffen. Du bist der erste Mann, der mir sagt, dass Hawk irgendwo hier sein sollte. Aber wie ich schon gesagt habe - ich bezweifle es.";
			link.l1 = "Ich sehe...";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Whiteboy":
			dialog.text = "Weißer Junge? Hm... Nein, von ihm habe ich noch nie gehört. Aber das bedeutet nicht, dass er nicht hier ist. Ich muss nicht jeden lokalen Abschaum kennen, stimmst du zu?";
			link.l1 = "Ich mache. Gut, ich würde jemand anderen fragen.";
			link.l1.go = "exit";
			npchar.quest.whiteboy = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "ships":
			dialog.text = "Die Insel ist von Narwalen, Rivados und meinen Männern geteilt. Es gibt auch einen neutralen Bereich. Ich kontrolliere San Augustine und Tartarus\nRivados halten Protector, das ist ihr Wohnsitz, Fury - Kasernen, Velasco - Lagerhaus. Fremden ist es verboten durchzugehen, du musst ein spezielles Passwort sagen, um dorthin zu gelangen\nNarwale haben viele Schiffe in ihrem Besitz. Esmeralda ist der Wohnsitz ihres Anführers und ein Laden. So genanntes 'Wissenschaftszentrum San Gabriel' und eine Phoenix-Plattform. Nicht zuletzt, Ceres Schmiede - ihre Werkstatt. Jedes Schiff außer Esmeralda ist ein eingeschränktes Gebiet, du musst ein Passwort sagen, bevor sie dich reinlassen\nDie restlichen Schiffe gelten als neutral, lokale Bürger leben in ihnen. Sancho's Taverne befindet sich in der Karavelle Fleron und Bruder Julian ist der Leiter der örtlichen Kirche in der Galeone Gloria.";
			link.l1 = "Danke für die Information!";
			link.l1.go = "exit";
			npchar.quest.ships = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "2");
		break;
		
		case "parol":
			dialog.text = "Eigentlich geben sie diese Passwörter an Leute, an denen sie selbst Interesse haben. Leider gehörst du nicht dazu. Aber das ist kaum ein Problem. Geh zu einer alten Fregatte namens Carolinea. Dort lebt ein fetter, schlauer Hund namens Giuseppe Fazio. Er ist hier so etwas wie ein Diplomat. Ich weiß nicht, was er gemacht hat, bevor er hierher kam, aber der Mann hat Können. Er macht Geschäfte mit jedem. Die Clans benutzen ihn als Vermittler. Gierig. Bereit, sich selbst für einen einzigen Dublonen zu essen, aber er zeigt es nie. Frag ihn nach dem aktuellen Passwort, obwohl es dich etwas kosten wird.";
			link.l1 = "Danke! Ich werde das in Erinnerung behalten.";
			link.l1.go = "exit";
			npchar.quest.parol = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "3");
		break;
		
		case "map":
			dialog.text = "Dexter besitzt eine. Er ist mein Stellvertreter. Er hat gleich nach unserer Ankunft eine detaillierte Karte erstellt. Geh nach oben und sprich mit ihm, falls du sie brauchst.";
			link.l1 = "Verstanden. Danke!";
			link.l1.go = "exit";
			npchar.quest.map = "true";
			NextDiag.TempNode = "Total_wait";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "blade":
			dialog.text = "Ha! Ein feines Breitschwert. Eine Art einzigartige Klinge.. Eine Trophäe von Alan Milrow, dem Anführer des Narwal-Clans. So habe ich es benannt. Jurgen, ein Narwal-Schmied, hat es aus einem erstaunlichen Metall gefertigt, das sie auf dem Meeresgrund gefunden haben\nEs rostet nicht, wird nie stumpf und schneidet alles und jeden auf einmal. Ich bin sehr zufrieden mit dieser Waffe und habe nicht vor, sie zurückzulassen.";
			link.l1 = "Ich bin neugierig, ob Jurgen in der Lage ist, ein weiteres Breitschwert wie dieses herzustellen? Für gutes Geld, natürlich...";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "Nun, er könnte sicherlich noch einen machen. Aber das wird er nicht tun. Jurgen ist ein Narwal, er ist loyal zu seinem Clan und er wird nie etwas für Außenstehende herstellen. Außerdem würdest du ein sehr spezielles Eisen brauchen, um das zweite Schwert herzustellen. Dieses Eisen kann nur am Grund gefunden werden - und wie soll man da hin kommen? Also vergiss es.";
			link.l1 = "Ich verstehe. Schade.";
			link.l1.go = "exit";
			npchar.quest.blade = "true";
			NextDiag.TempNode = "Total_wait";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				sld = characterFromId("Schmidt");
				sld.quest.narval_blade = "begin"; // возможность сделать 'Нарвал' для Мэри
			}
		break;
		// <-- информационный блок
		
		case "return":
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = "Ha, ich habe deine Segel am Horizont gesehen, "+pchar.name+". Schön dich zu sehen, Freund! Wie war die Reise?";
			link.l1 = "Es war in Ordnung.";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Gut. Nun, ich bin bereit, auf dein Schiff zu steigen und zu Jan Svenson zu segeln. Layton wird hier als Admiral bleiben, er hat bereits den Stuhl eingenommen, ha-ha! Es scheint, als würde er die Insel nicht verlassen, er mag diesen Ort.";
			link.l1 = "Du hast einmal gesagt, dass es ihm wirklich gut geht.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "Ja, das ist er sicherlich. Nun, ich bin bereit. Lass uns gehen?";
			link.l1 = "Komm auf mein Schiff, Steven. Wir werden ablegen, sobald ich hier meine Geschäfte erledigt habe.";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "Abgemacht! Eh, es ist zu lange her, dass ich das Deck eines ordentlichen Schiffes unter meinen Füßen gespürt habe!";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_SetDodsonPassenger", -1);
		break;
		
		case "return_5":
			dialog.text = "Hier sind wir, Freund. Nun, ich werde gehen und Svenson sehen. Du solltest ihn auch sehen und unsere zukünftigen Pläne besprechen. Ha-ha! Heiße Tage erwarten uns, hm?";
			link.l1 = "Kein Zweifel. Wir sehen uns, Steven!";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS1", "none", "", "", "OpenTheDoors", -1);
			sld = ItemsFromID("LSC_navigation_map");
			sld.price = 1000; // лоцию можно выкладывать 270912
			sld = ItemsFromID("keys_skel");
			sld.price = 3000; // отмычки можно выкладывать 270912 
			pchar.questTemp.LSC.Dios = "true"; // можно отдать лоцию Диосу
			CloseQuestHeader("LSC"); // 280313
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "Sicher, ich werde tun, was ich kann! Mach weiter.";
			link.l1 = "Steve, schau mal... Ein Haifischzahn. Sag mir nicht, dass er dir unbekannt ist!";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "Ha! Du bist schlau! Ja, das ist mein Zahn. Nun, es ist der Zahn eines Hais, den ich getötet habe, um eine Schönheit zu beeindrucken. Seitdem nennen sie mich Hai. Nur wenige konnten das unter Wasser mit einem einfachen Säbel tun, aber ich war jung und dumm, und Beatrice Sharp war das schönste Mädchen in der Karibik... Wie bist du darauf gekommen?";
			link.l1 = "Der ehemalige Henker von St. John's hat es mir gegeben. Ein Mann wurde damit abgeschlachtet. Sein Name war... Joshua Leadbeater.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "Ja, ich habe es getan. Ich habe ihm mit diesem Zahn die Kehle durchgeschnitten. Ich war entsetzt über den Tod von Beatrice und glaubte, dass Leadbeater der einzige Überlebende war, der dafür verantwortlich war. Ich habe später die Papiere gelesen, die ich bei ihm gefunden habe. Nun, er hatte jedes Recht zur Rache\nBlazes Schwester war einfach zur falschen Zeit am falschen Ort. Man kann der Maske nicht die Schuld für ihren Tod geben, er wollte es nicht, nur der Schlächter war sein Ziel. Ich bedaure, ihn ermordet zu haben. Die Wahrheit ist, diese Hündin Jessica hat das Ganze eingefädelt.";
			link.l1 = "Hast du diese Papiere gerettet?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "Warum sollte ich? Natürlich habe ich nicht. Ich brauchte sie nicht. Aber ich kann dir sagen, warum Maske Butcher gejagt hat, wenn du Zeit hast.";
			link.l1 = "Ich habe. Wisse, dass es nicht nur eine Neugier ist, ich bin wirklich interessiert. Ich bin sogar bereit, deine Geschichte niederzuschreiben.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "Ich weiß, du verschwendest nie deine Zeit. Höre dann zu. Joshua Leadbeater war ein gewöhnlicher Kapitän der britischen Marine und er kommandierte die Fregatte 'Neptune', die später zur Legende wurde...";
			link.l1 = "..., Freund.";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("One hour later...", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "... Allerdings überlebte Leadbeater und er wurde von einem vorbeifahrenden Schiff gerettet. Seine Wunden entstellten sein Gesicht, und seitdem trug er eine Maske. Den Schuldigen all seiner Missgeschicke zu finden und zu bestrafen, war zu seinem Lebenssinn geworden.";
			link.l1 = "Ich sehe... Ich habe es aufgeschrieben. Ich denke, ich sollte es lesen, um zu sehen, was ich habe. Es ist eine sehr traurige Geschichte. Hast du das gesehen, Jessica?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "Sicher! Sie begleitete Metzger auf all seinen Reisen, bis er sie für Beatrice verließ. Jess konnte ihm das nicht vergeben. Sie nannten sie das Talisman des Metzgers, weil er immer Glück hatte, während sie bei ihm war\nGlaub es oder nicht, aber sobald er sie auf Barbados loswurde, lief sein Geschäft schlecht, die Beute wurde schlecht und die 'Neptune' wurde ein häufiger Gast auf der Werft von Isla Tesoro. Obwohl es dadurch erklärt werden kann, dass Metzger die meiste Zeit mit Beatrice in der Kabine verbrachte, anstatt auf dem Achterdeck\nBeatrice war nicht wie Jessica, sie war nicht süchtig nach Abenteuern und Krieg, obwohl Nicolas ihr das Fechten und die Seemannschaft beibrachte. Ja, sie liebte die Seeromantik, aber sie hatte nicht genug Härte im Charakter. Metzgers 'Neptune' war nicht der richtige Ort für sie. Am Ende hat sie ihn getötet.";
			link.l1 = "Und was ist mit Jessica?";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "Oh, sie war etwas Besonderes. Jeder Seemann der 'Neptune' gehorchte ihren Befehlen und nicht nur, weil sie die Freundin des Kapitäns war. Jess beherrschte das Fechten und die Seemannschaft, die Bemühungen des Metzgers waren nicht umsonst. Sie war hart und rücksichtslos, und zudem mit gutem Aussehen gesegnet.\nViele Männer wollten mit ihr schlafen, aber sie wollte nur den Metzger, sie zu belästigen war wirklich riskant - viele haben die Ergebnisse buchstäblich auf ihren eigenen Rücken getestet, und für die Hartnäckigsten wurden ihre Fechtstunden zu den letzten in ihrem Leben.\nJess besaß ein ganz besonderes Schwert, das einzige seiner Art in der Karibik, ich habe keine Ahnung, wo sie es her hat. Flammenklingenschwert. Niemand kann seine Klinge greifen und schon die kleinste Berührung hinterlässt eine schreckliche Wunde.\nJess war nicht von Geburt an eine Abenteurerin, sondern von Berufung. Übrigens, wenn Sie mehr über sie erfahren möchten, können Sie mit einem Bekannten von Ihnen sprechen. Er kann Ihnen viel mehr über sie erzählen als ich.";
			link.l1 = "Wirklich? Und wer ist dieser Mann?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "Jan Svenson. Der Waldteufel wird es nie zugeben, aber er hatte Pläne mit Jessica. Das war die Zeit, als er bereits das Western Main für sich genommen hatte und sein Ruhm war etwas, vor dem man neidisch sein konnte, also war die Tigerin genauso gut wie er\nNachdem der Metzger Jess losgeworden war, begann Jan verdächtig oft Barbados zu besuchen und brachte die englische Garnison durcheinander. Wie du weißt, war Jessica die Tochter eines Plantagenbesitzers aus Bridgetown\nAlles in allem waren seine Pläne in privaten Kreisen gut bekannt, doch niemand wagte es, seine Meinung dazu zu äußern. Jan mag heutzutage in Blueweld auf seinem Hintern sitzen, aber damals konnte jedes falsche Wort in seiner Adresse schlecht enden\nAm Ende hat es für sie nicht geklappt. Jess konnte nicht mit der Art und Weise leben, wie der Metzger sie behandelte, und sie rächte sich ein Jahr später mit Hilfe der Maske. Diese Rache endete schrecklich für alle: für den Metzger, für Beatrice, für die Maske und für sie selbst. Sie alle starben.";
			link.l1 = "Nicht alle von ihnen. Der Metzger lebt noch.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "Was? Habe ich dich missverstanden? Er lebt?!";
			link.l1 = "Ja. Kapitän Schlächter wurde nicht hingerichtet. Nun, er hätte es sein sollen, aber er überlebte dank Jacob Jackman und Heinrich dem Henker, die den Scharfrichter eingeschüchtert hatten. Die Hinrichtung war ein Schwindel. Ich habe Beweise.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "Unmöglich! Und wo ist er jetzt?";
			link.l1 = "Er ist bekannt als Lawrence Beltrope und er lebt in Port Royal. Er ist jedoch immer noch gefährlich. Jackman, der so viele Probleme unter den Brüdern der Küste verursacht hat, handelte unter seinem Befehl.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "Verdammt! Der Quartiermeister hat seinen Kapitän nach so langer Zeit gefunden! Beltrope, sagst du... warte! Jetzt verstehe ich, warum es einen seltsamen Verhörbericht unter Blazes Papieren gab... Es scheint, als hätte Blaze auch von Metzger-Beltrope erfahren...";
			link.l1 = "Wovon redest du?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "Nachdem ich diesen Wohnsitz übernommen hatte, durchwühlte ich die alten Papiere von Blaze. Ich habe ein Verhörprotokoll von einem gewissen Samuel Brooks gefunden. Es ging viel um die Abenteuer von Thomas Beltrope und dass er als Pirat und enger Freund von Nicolas Sharp bekannt ist. Es scheint, dass er der Vater von Butcher war.";
			link.l1 = "Interessant. Es sieht so aus, als ob die Kinder von Sharp und Beltrope die Arbeit ihrer Eltern fortgesetzt haben...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "Es scheint so... Aber sag mir, Freund, warum bist du so interessiert an den Taten verstorbener Menschen? Was geht dich das an?";
			link.l1 = "Ich brauche Papiere, die bestätigen, dass Helen McArthur die Tochter von Beatrice Sharp ist und dass sie alle Rechte an diesem Nachnamen hat. Es ist mir egal, dass sie auch Beltrope ist.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "Es gibt nichts über Helen McArthur, weder in Leadbeaters Papieren noch in Blazes Archiven. Es ist seltsam, dass Beatrice Blaze nicht von der Geburt seiner Nichte erzählte. Das sieht ihr nicht ähnlich.";
			link.l1 = "Hör zu, vielleicht gibt es noch etwas in Sharps Papieren? Ich brauche jedes Detail!";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "Hm, ich schätze. Laut Blazes Notizen hat er versucht, die Insel zu finden, auf der seine Schwester gestorben ist. Es gibt Papiere über Leadbeaters Strafexpedition. Nichts Interessantes, außer ein paar Breitengradnummern\nDiese Parallele durchquert das Karibische Meer im Norden. Aber es gibt keine Anzeichen von Längengrad. Offensichtlich sind Blazes Suchen gescheitert, du kannst dir nicht vorstellen, wie viele kleine Inseln auf dieser Breite liegen.";
			link.l1 = "Und was ist das?";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "Lass uns sehen... hier: Breitengrad 21 Grad 32' Nord. Ich weiß nicht, wie das dir helfen kann.";
			link.l1 = "Es wird. Gut, Steven, vielen Dank für deine ehrliche Geschichte. Bis dann!";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "First time";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// рифы доступны для посещения
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// для любителей самостоятельно добавлять локаторы
			LAi_LocationDisableOfficersGen("Shore67", true);//офицеров не пускать
			// и сразу прерывание
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// активируем квест хронометра Алекса
			pchar.questTemp.AlexClock = "dodson"; // 280912
		break;
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "Man könnte es so sagen. Nun, über Tortuga\nDie Insel wurde so genannt, weil sie fast wie eine Schildkröte aussieht. Levasseur hat zwölf Jahre lang den Schildkrötenpanzer verdickt - Fort La Roche. Ein Frontalangriff ist selbstmörderisch, die schweren Kanonen des Forts lassen keine Chance. Also, eine Suppe aus dieser Schönheit zu kochen, wird nicht leicht sein. Die Spanier haben es sehr lange versucht und sind nie erfolgreich gewesen.";
			link.l1 = "Deswegen bin ich zu Svenson gegangen. Also, was ist dein Plan? Los, Steven!";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "Meine Männer haben in den letzten Wochen anständige Arbeit auf Tortuga geleistet und eine Menge interessanter Informationen gesammelt. Also habe ich gute Nachrichten für dich, Kumpel! Es scheint, dass du dich nicht mit den Kanonen von La Roche auseinandersetzen musst, da wir nicht die einzigen sind, die von Levasseur die Nase voll haben. Es gibt Leute unter seinen Freunden, die ihn auch tot sehen wollen.";
			link.l1 = "Mach weiter...";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "Es ist bekannt, dass Levasseur junge Kolonistinnen mag. Sie verschwinden, nachdem er mit ihnen fertig ist. Der Hauptsklavenlieferant von Tortuga heißt Robert Marten vom Galleon Voltigeur\nSein Kumpel, Levasseurs Neffe Henri Thibaut, wählt die hübschesten weißen Mädchen direkt im Hafen für seinen Gönner aus. Also, vor nicht allzu langer Zeit, bekam Marten ein sehr schönes Mädchen von einem englischen Brig. Ihr Name ist Molly Jones. Er lieferte sie nicht an Levasseur aus, sondern an seinen Neffen, nachts zu einer geheimen Grotte auf Tortuga\nDie Crew wurde informiert, dass das Mädchen an einem Herzinfarkt gestorben ist und ihr 'Körper' wurde an Bord geworfen. Es sieht so aus, als hätten unsere Kumpels beschlossen, ein hübsches Ding für sich zu behalten. Wenn Levasseur von Molly erfährt, werden diese beiden Probleme bekommen.";
			link.l1 = "Und wie können wir dieser Information vertrauen? Es ist offensichtlich, dass beide verstehen, dass sie mit dem Feuer spielen...";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			dialog.text = "Wahr. Aber jede Kette hat eine Schwachstelle. Und ich habe solche für dich gefunden. Vor drei Tagen hat ein ehemaliger Seemann der 'Voltigeur' namens Fernand Lucas zu viel getrunken und in der Taverne von Basse-Terre viele interessante Dinge erzählt\nEs stellte sich heraus, dass Molly Jones ihn gebeten hatte, ihren Bruder in St John's um Hilfe zu bitten. Aber Lucas hat das Ziel nie erreicht, er ist vor seinem Kapitän geflohen und sitzt jetzt auf Guadeloupe und ertränkt seine Feigheit im Rum\nAntigua ist kein sicherer Ort für französische Piraten. Merk dir das! Oberst Fox ist bereit, sie an jeder Palme der Insel aufzuhängen, nachdem seine Frau durch die Hand eines französischen Korsaren gestorben ist. Und seine furchterregenden Marines werden alles tun, was ihr Kommandant befiehlt.";
			link.l1 = "Ich verstehe noch nicht, wie das mit unserem Geschäft zusammenhängt... Sprechen wir über unsere Jungs, Marten und Thibaut. Was ist der Sinn eines solchen Risikos? War der Charme der Frau so stark oder haben diese Sklavenhändler Gnade gezeigt?";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "Ich kenne diesen Abschaum Marten sehr gut. Wenn er Risiken eingeht, bedeutet das, dass entweder Gold im Spiel ist oder Angst um seine Haut. Ich weiß nicht, was unsere Gefangene damit zu tun hat\nVielleicht erwartet Robert ein hohes Lösegeld für sie, was unwahrscheinlich ist, das Mädchen sah aus wie eine Dienerin. Oder vielleicht... Ha! Ich frage mich, wer für Marten furchterregender sein könnte als Levasseur!";
			link.l1 = "Und warum denken Sie, dass Miss Jones immer noch vor dem Gouverneur versteckt wird? Vielleicht haben sie bekommen, was sie von ihr wollten und haben sie an Levasseur ausgeliefert? Ja, haben Sie etwas Spezifisches über diesen Thibaut zu berichten?";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "Weiß nicht viel über den Mann. Ich weiß nur, dass der Onkel diesem Welpen genug vertraut, um ihn zu seinem Erben zu machen. Er hat noch ein Mädchen, sonst bräuchten sie all diese Verschwörung nicht.\nEs ist unklar, wo das Mädchen festgehalten wird und warum Thibaut Marten die Führung überlässt. Es gibt ein Geheimnis, das uns helfen kann, dieses Spiel zu gewinnen, ohne Tortuga stürmen zu müssen. Du bist Franzose, also nehme ich an, du würdest es so bevorzugen\nAber du solltest dich beeilen, Lucas' betrunkene Gespräche könnten von Martens und Levasseurs Agenten gehört werden, du kannst dir die Konsequenzen vorstellen!";
			link.l1 = "Ich verstehe. Also, Thibaut ist ein Erbe von Levasseur? Und er versteckt ein Sklavenmädchen vor seinem Onkel? Verdammt, ich nehme an, der junge Mann kann es kaum erwarten, dass sein Onkel so schnell wie möglich stirbt!";
			link.l1.go = "terrapin_6";
		break;
		
		case "terrapin_6":
			dialog.text = "Wahrlich. Nach Lucas' Worten, ist diese Molly eine seltene Schönheit, unser tapferer Thibaut könnte sich in sie verlieben. Du weißt, was Menschen aus Liebe tun können. Geh nach Basse-Terre\nFinde diesen betrunkenen Idioten und bring ihn zum Reden. Außerdem solltest du alles über Molly und ihren Bruder herausfinden. Vielleicht solltest du zuerst nach Antigua gehen, Molly hat Lucas dort aus einem bestimmten Grund hingeschickt. Aber welcher ist dieser Grund?";
			link.l1 = "Ich verstehe. Lass uns keine Zeit verschwenden. Danke, Steven.";
			link.l1.go = "terrapin_7";
		break;
		
		case "terrapin_7":
			DialogExit();
			AddMapQuestMarkCity("SentJons", true);
			AddMapQuestMarkCity("BasTer", true);
			AddQuestRecord("Terrapin", "1");
			pchar.questTemp.Terrapin = "baster";
			pchar.questTemp.Terrapin.SJ_count = 0;
			// прячем Фокса
			sld = characterFromId("Fox");	
			ChangeCharacterAddressGroup(sld, "none", "", "");
			// садим в таверну Робера Мартэна
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Rober", "Marten", "man", "man", 30, FRANCE, -1, true, "quest"));
			FantomMakeCoolSailor(sld, SHIP_GALEON_L, "Voltigeur", CANNON_TYPE_CANNON_LBS20, 90, 90, 90);
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_19", "pistol5", "bullet", 150);
			sld.name = "Rober";
			sld.lastname = "Marten";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "Rober";
			sld.greeting = "pirat_common";
			TakeNItems(sld, "potion2", 1);
			TakeNItems(sld, "potion3", 2);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "LongRangeGrappling");
			SetCharacterPerk(sld, "GrapplingProfessional");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "BasicBattleState");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "Doctor2");
			sld.MultiFighter = 1.0+fMft; // мультифайтер
			LAi_SetSitType(sld);
			UpgradeShipParameter(sld, "SpeedRate");//апгрейдить скорость
			UpgradeShipParameter(sld, "TurnRate");//манёвренность
			FreeSitLocator("Baster_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, "Baster_tavern", "sit", "sit1");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 20, false); // таймер
			}
			else SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 10, false); // таймер
			
			// Квест "Погасшая Звезда" провалена, всё удаляем
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway"))
			{
				CloseQuestHeader("PZ");
				DeleteAttribute(pchar, "questTemp.PZ_Etap5_Start");
				DeleteAttribute(pchar, "questTemp.PZ_Etap4_Start");
				DeleteQuestCondition("PZ_Etap5_Start");
				DeleteQuestCondition("PZ_LongwayCapstervilleDialog");
				DeleteQuestCondition("PZ_OhotaNaZvezdu_Kapstervil");
				DeleteQuestCondition("PZ_OhotaNaZvezdu_Yamaika");
				DeleteQuestCondition("PZ_Beliz_PoterpKrushenie");
				pchar.questTemp.PZ_ProvalFinal = true;
			}
		break;
		
		case "terrapin_8":
			dialog.text = "Mach weiter!";
			link.l1 = "Ich habe Mollys Bruder in St. John's gefunden. Es ist Fox's Batman. Aber es gibt etwas Seltsames. Seine Schwester Molly ist eine bekannte hässliche Hexe, ungefähr so groß wie du. Sie ist die Magd von Fox's Tochter, Catherine, und sie war bis vor kurzem mit ihr in England...";
			link.l1.go = "terrapin_9";
		break;
		
		case "terrapin_9":
			dialog.text = "";
			link.l1 = "Was Catherine betrifft, sie ist tatsächlich für ihre Schönheit bekannt und sie wollte ihren Vater an seinem Geburtstag besuchen, aber sie war spät wegen der Verspätung des Geschwaders in London...";
			link.l1.go = "terrapin_10";
		break;
		
		case "terrapin_10":
			dialog.text = "";
			link.l1 = "Ihr Vater, der den Tod seiner Frau durch den Angriff des französischen Korsaren schwer nahm, hat ihr strengstens verboten, England auf einem einsamen Schiff zu verlassen. Also kann Molly Jones nicht Thibauts Gefangene sein. Aber wer ist sie dann?";
			link.l1.go = "terrapin_11";
		break;
		
		case "terrapin_11":
			dialog.text = "Hm... Verdammt, wenn ich es weiß. Vielleicht ist sie eine andere Molly Jones, nicht die, nach der du gefragt hast. Obwohl... es gibt zu viele Zufälle. Ich glaube nicht, dass alles nur ein Zufall ist! Ich habe einige unklare Verdächtigungen, aber... obwohl viele seltsame Dinge passieren können!";
			link.l1 = "Was meinst du? Erzähl mir!";
			link.l1.go = "terrapin_12";
		break;
		
		case "terrapin_12":
			dialog.text = "Und was, wenn die Tochter den Befehlen des Vaters nicht gehorcht und ohne Eskorte in See gestochen ist? Der letzte Monat war ziemlich stürmisch, der Albatross könnte beschädigt worden sein und wurde eine leichte Beute für den Marder. Ich vermute, dass Catherine ihren wahren Namen nicht genannt hat, du solltest verstehen warum, und sie wird unter dem Namen Molly in Tortuga festgehalten\nDu weißt, was ihr droht, wenn ihr wahrer Name auffliegt. Das fängt an Sinn zu machen!";
			link.l1 = "Verdammt nochmal! Ich hätte nie daran gedacht! Molly... Catherine... Aber es fällt alles zusammen!";
			link.l1.go = "terrapin_13";
		break;
		
		case "terrapin_13":
			dialog.text = "Das ist es, wovon ich rede, Kumpel. Nicht sicher, dass wir recht haben, aber...";
			link.l1 = "Aber es ändert alles! Vielleicht sollten wir die Engländer um Unterstützung bitten? Damit die Bajonette der Marines den Weg für uns freimachen!";
			link.l1.go = "terrapin_14";
		break;
		
		case "terrapin_14":
			dialog.text = "Beruhige dich, "+pchar.name+"! Wir brauchen mehr stichhaltige Beweise. Wir können nicht sicher sein. Die echte Catherine könnte in London sein und auf eine Staffel warten, um in See zu stechen. Die Briten haben ihre eigenen Probleme, sie werden das Risiko nicht eingehen, La Roche anzugreifen. Aber wenn unsere Verdächtigungen wahr sind und Oberst Fox herausfindet, was mit seiner Tochter passiert ist ...\n Er wird eine Blockade um die Insel errichten und auf die Ankunft des Geschwaders warten. Dann wird er die Stadt angreifen. Seefüchse sind eine furchterregende Kraft im Nahkampf. Ich bin sicher, dass er die englische Flagge über den Ruinen von Tortuga in drei Tagen hissen wird. Willst du das wirklich?";
			link.l1 = "Nein, das ist nicht unsere Art. Jetzt sehe ich, welches Lösegeld Marten meint.";
			link.l1.go = "terrapin_15";
		break;
		
		case "terrapin_15":
			dialog.text = "Wir müssen vorsichtig handeln. Wir sind uns nicht einmal sicher, ob Marten von Mollys wahrer Identität weiß. Oberst Fox zu erpressen, wäre eine selbstmörderische Idee. Vor allem, wenn Cromwells Geschwader bald ankommt\nWenn Catherine stirbt, verlieren auch wir. Unsere Bruderschaft hat kein Interesse daran, Oberst Fox wütender zu machen als üblich. Dieser Mann kann eine Menge Ärger verursachen. Wenn Catherine nach allem sterben muss, müssen wir sicherstellen, dass sie nicht durch unsere Hände stirbt und nachdem sie ihre Rolle in unserem Spiel gespielt hat\nAber es wäre viel besser, das arme Mädchen ihrem Vater zu übergeben. Ihr Retter wird belohnt. Wenn nicht in dieser Welt, dann in der anderen.";
			link.l1 = "Um Gottes willen... Steven, du bist ein Genie! Ich gehe sofort nach Tortuga! Ich werde herausfinden, wer diese Molly Jones ist! Ich bin verdammt sicher, dass sie Catie Fox ist!";
			link.l1.go = "terrapin_16";
		break;
		
		case "terrapin_16":
			dialog.text = "Vielleicht... Verschwende keine Zeit, "+pchar.name+". Und wenn ich recht habe - sorge dafür, dass sie am Leben bleibt.";
			link.l1 = "Ich werde tun, was ich kann. Wir sehen uns!";
			link.l1.go = "terrapin_17";
		break;
		
		case "terrapin_17":
			DialogExit();
			AddQuestRecord("Terrapin", "7");
			pchar.questTemp.Terrapin = "tortuga1";
			pchar.questTemp.Terrapin.Room_close = "true": // не пускать в комнату таверны
		break;
		
		case "guardoftruth":
			dialog.text = "Ho-Ho! Spuck es aus, Freund! Wir werden jedes verdammte Problem sicher lösen!";
			link.l1 = "Ich komme gleich zur Sache. Kennst du Miguel Dichoso?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Ich kenne ihn. Dieser spanische Don hat mir ein großartiges Schiff verkauft - eine Fregatte. Eh, was für ein Schiff sie war, stell dir nur vor...";
			link.l1 = "Lass mich raten, ein einzigartiger Rumpf, maximal sechzehn Knoten Geschwindigkeit? 'Santa Quiteria'?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Du hast recht mit ihrem Rumpf und ihrer Geschwindigkeit, aber der Name war anders - 'San Martin'. Ich habe ihm eine riesige Menge Gold bezahlt, es war alles, was ich hatte. Alle meine Ersparnisse gingen direkt in die Taschen dieses Schurken.";
			link.l1 = "Bist du sicher, dass ihr Name San Martin und nicht Santa Quiteria war? Und wann hast du es gekauft? Und warum nennst du ihn einen Schurken?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "So viele Fragen! Ich werde sie alle in der Reihenfolge beantworten: Ich bin sicher, dass es San Martin war. Ich habe persönlich den Arbeitern von Alexus geholfen, ein Brett mit diesem päpstlichen Namen von dem Heck zu entfernen. Ich habe sie 'Fortune' genannt - ein viel passenderer Name für eine solche Prinzessin\nIch habe sie kurz vor der Ermordung von Blaze Sharp im Winter 1654 gekauft. Warum habe ich Miguel so genannt? Weil dieser Hurensohn es geschafft hat, das Schiff von der spanischen Militärbasis von Providence zu stehlen. Wir haben ihnen eine ziemliche Show geliefert, direkt vor dem Fort von San Juan. Ich habe zwei halbtote Luggers geopfert, um den Kampf glaubwürdiger zu machen. Wir haben die Schiffe verbrannt und geflutet, um den Kampf mit der Fregatte zu simulieren. Und als die Dunkelheit hereingebrochen ist - haben wir die San Martin zur Isla Tesoro gefahren.. Ich habe das Schiff bekommen und Dichoso hat Geld bekommen. Er hat seinem Oberkommando erzählt, dass die Fregatte in einem Kampf mit Piraten gesunken ist, der Kommandant von San Juan hat das bestätigt.";
			link.l1 = "So das ist also, wie spanische Dons ihre Taschen füllen! Was für ein Schurke! Sag mir, ist das wirklich im Winter 1654 passiert? Vielleicht im Frühling? Und wurde die Fregatte durch Stürme beschädigt?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Im Winter... Verdammt, ich bin mir nicht ganz sicher - könnte auch im Frühling gewesen sein. Ich erinnere mich wirklich nicht. Die Fregatte war nicht beschädigt, sie war ganz neu. Sie sah aus wie frisch gebaut. Wenn ich an sie denke, möchte ich vor Ärger einfach weinen...";
			link.l1 = "Warum? Ja, und wo ist jetzt deine schöne Fregatte?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Weil sie von mir gegangen ist. Sie haben mich reingelegt, meinen Talisman auf Blazes Leiche gelegt und verbreitet, dass ich der Mörder sei. Dann hörte ich, dass Marcus Tyrex - unser Codehalter - mir eine schwarze Marke überreichen will. Also beschloss ich, für eine Weile aus diesem Chaos auf die Insel der Gerechtigkeit zu fliehen, wo du mich gefunden hast\nIch konnte nicht mit einer Fregatte dorthin gelangen, also verpfändete ich sie an den Schwarzen Pastor im Austausch für eine Brigg voller Proviant, ich hatte nach meinem Geschäft mit diesem schlauen Dichoso nicht viel Münze. Ich hoffte, den Proviant verkaufen und in ein oder zwei Monaten nach Isla Tesoro zurückkehren zu können... Nun, du kennst den Rest.";
			link.l1 = "Und der Schwarze Pastor hat nicht auf dich gewartet, also hat er sie verkauft";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Genau. Sie wurde von einem Engländer gekauft, oder genauer gesagt, von einem Schotten, William Paterson. Ich könnte versuchen, das Mädchen zurückzubekommen, sicher, aber dieser Highlander ist ein ernsthaftes Vögelchen, ein Kapitän der Royal Navy, ein guter Freund von Oberst Fox. Außerdem hat er mit Jackman Geschäfte gemacht, genauso wie du mit Svenson\nDer Schotte hat eine Staffel... verdammt, ich werde mein Schiff nie wieder sehen.";
			link.l1 = "Ich verstehe. Weißt du nicht, wo dieser Dichoso jetzt ist?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Ich habe keine Ahnung. Ich habe ihn nie gesehen, nachdem ich mein Glück gekauft habe.";
			link.l1 = "Und warum hat Miguel es nicht jemand anderem angeboten? Wie wäre es mit Tyrex, Barbazon, Sharp? Oder Paterson?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Ich habe keine Ahnung. Paterson war zu dieser Zeit, so weit ich mich erinnere, nicht hier. Zachariah, Jacques und Marcus hätten niemals zugestimmt und ich... Ich mochte die Fregatte wirklich!";
			link.l1 = "Ich verstehe, dass... Ich verstehe gar nichts. Rätsel überall...";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Eintauchen in die Vergangenheit wieder? Welche Insel willst du diesmal nehmen? Ha-ha-ha!";
			link.l1 = "Es gibt eine Insel... Aber ich finde noch keinen Weg dorthin. Gut, Steven, danke für deine Informationen! Lebewohl!";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Viel Glück, "+pchar.name+"!";
			link.l1 = "..., Freund.";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			DialogExit();
			AddQuestRecord("Guardoftruth", "60");
			pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
			// маленькая развлекуха
			pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
			pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;
		
		case "tieyasal":
			dialog.text = "Und ich helfe Ihnen wie immer gerne. Was wollen Sie diesmal, "+pchar.name+"?";
			link.l1 = "Es geht wieder um deinen alten Freund Miguel Dichoso. Mir ist bekannt, dass er wieder auf Isla Tesoro gesehen wurde. Kannst du mir nicht helfen, ihn zu finden?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Ho, Freund, das wusste ich eigentlich nicht. Ich habe ihn hier nicht gesehen. Ich habe ihn nicht gesehen, seit ich 'Fortune' von ihm gekauft habe. Und warum brauchst du diesen spanischen Don?";
			link.l1 = "Ich brauche ihn. Miguel kennt den Weg zu einer alten indischen Stadt. Ich bin wirklich begierig darauf, dorthin zu gelangen.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Genau wie immer, mein Freund, wirst du dich wieder in das Durcheinander hineinziehen. Leider kann ich dir nicht helfen. Ich rate dir, durch die Siedlung zu laufen und die Leute zu fragen, vielleicht hat jemand ihn gesehen. Er ist hier ein bekannter Mann, weißt du.";
			link.l1 = "Hallo, Steven, kannst du mir wenigstens sagen, wie er aussieht?";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Nun, er ist fünfundzwanzig - achtundzwanzig Jahre alt, ungefähr so groß wie du, dunkle Augen, keine Perücke. Auf seiner rechten Wange ist eine Säbelnarbe.";
			link.l1 = "Hm. Du weißt, es gibt viele Leute, die auf diese Beschreibung passen könnten.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "Es gibt keine weiteren einzigartigen Details über ihn. Er ist selbstbewusst, frech und sehr gefährlich. Es gab Gerüchte über ihn...";
			link.l1 = "Ich verstehe. Gut, ich werde mich nach ihm erkundigen. Viel Glück, Steven!";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			DialogExit();
			AddQuestRecord("Tieyasal", "2");
			npchar.quest.tieyasal = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "Ho-ho! Du bist am richtigen Ort! Spuck es aus!";
			link.l1 = "Es gibt einen Kerl, der keine Angst vor Piraten hat. Er nimmt sie nicht ernst. Er muss eine Lektion in Respekt lernen. Denk daran, töte ihn nicht.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Huh! Das ist niemand anders als der alte Mann Charles! Ich wette, du hast dich wieder in irgendeine Affäre verwickelt! Lassen wir uns ins Detail gehen, wer ist diesmal das Ziel und was sollen wir ihm beibringen";
			link.l1 = "Ein Gast aus Europa, ein Inspektor des französischen Finanzministeriums - Baron Noel Forget. Er möchte hier eine französische Handelsgesellschaft gründen, aber ich und ein enger Freund von mir sind dagegen. Wir versuchten, den Baron davon zu überzeugen, dass der Handel hier wegen der Niederländer, Engländer und vor allem Piraten nach Levasseurs Niederlage sehr riskant wäre, aber er hörte nicht zu. Wir müssen ihm Angst einjagen, damit er es auf seiner eigenen Haut spürt.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "Ja-Ja... Ein echter Baron!.. Werden wir sein Schiff angreifen?";
			link.l1 = "Hier ist der Plan: Sein Schiff wird bald von Port-au-Prince nach Capsterville aufbrechen. Du musst den Baron nach seiner Abfahrt abfangen und ihn als Geisel nehmen. Es wäre besser, wenn du das Schiff nicht versenkst und die Besatzung nicht tötest. Die Franzosen sind schließlich unsere Freunde. Wirst du damit zurechtkommen?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "Nun, ich kann nichts versprechen. Aber ich werde es versuchen. Welches Schiff ist es?";
			link.l1 = "Eine Brigg namens 'Favory'.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Eine Brigantine ist kein Gegner für meine Fregatte. Wir werden leicht mit ihnen fertig. Wenn sie sich ergeben, lasse ich jeden leben.";
			link.l1 = "Perfekt. Jagt ihnen Angst ein und bietet ihnen an, sich zu ergeben. Danach schickt den Baron in den rattenverseuchten Laderaum. Versucht, den schmutzigsten Platz zu finden, den ihr könnt, aber behaltet ihn dort nicht länger als einen Tag, sonst könnte er krank werden und sterben. Dann bringt ihn in die Kajüte, geht zur Isla Tesoro und sperrt ihn an einem abgelegenen Ort ein. Verkleidet einige eurer Männer als gefangene französische Händler und lasst sie sich so verhalten. Drei Tage lang sollten sie ihm alles darüber erzählen, wie die skrupellosen Piraten sie jagen, ausrauben, Lösegeld fordern, foltern... mit allen erforderlichen Details.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Ha-ha-ha! Das muss der lustigste Job sein, den ich seit sehr langer Zeit angenommen habe! Nun, ich werde solche Schauspieler finden, Kumpel. Zweifel nicht daran, nach ihren Geschichten wird dein Baron sich in die Hosen scheißen! Sie werden ihm Narben von Säbeln und erhitzten Ladestöcken zeigen...";
			link.l1 = "Genau. Dann wirst du ihn zwingen, einen Brief an Poincy zu schreiben, um Lösegeld zu verlangen. Dreieinhalb Millionen für so einen hohen Tiers sind nicht viel.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "Gut. Was machen wir als nächstes?";
			link.l1 = "Und dann bringst du den Baron zu den Turks. Dort nimmst du das Lösegeld entgegen und gibst mir den Baron. Und zusätzlich solltest du erwähnen, dass alle Franzosen für Tortuga und Levasseur büßen werden.";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "Ha-ha-ha! Das ist ein verdammt guter Trick! Wir persönlich, nun, du weißt, was wir mit Levasseur gemacht haben, und jetzt... ha-ha-ha!.. Gut, Kumpel. Es wird erledigt! Sagst du, dass das Schiff bald ankommen wird?";
			link.l1 = "Bald. Wir müssen auf der Hut sein.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "Mach dir keine Sorgen, ich werde dich nicht enttäuschen. Ich werde das persönlich regeln. Wenn du Gerüchte hörst, dass dieser Baron gefangen genommen wurde, komm zu mir.";
			link.l1 = "Gut. Meinen Dank, Steven.";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "70");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
		break;
		
		case "patria_10":
			dialog.text = "Natürlich, Kumpel. Wie vereinbart. Gruselige Geschichten über böse Piraten, die unschuldige französische Händler abschlachten. Das Geräusch einer Peitsche, Stöhnen und Schreien. Ein Kohlebecken und verbrannte Handschellen. Genau wie es sein sollte.";
			link.l1 = "Nun, halt mal die Pferde. Ich brauche ihn lebendig.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Mach dir keine Sorgen, er wird am Leben bleiben. Er hat diesen Brief mit zitternder Hand geschrieben. Hier ist er.";
			link.l1 = "Was steht da geschrieben? Fleht er Poincy an, ihn hier rauszuholen?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Genau richtig, Kumpel! Er bettelt!";
			link.l1 = "Werf diesen Brief weg, oder besser - verbrenne ihn. Wir treffen uns in einer Woche auf den Turks. Es muss so aussehen, als bräuchten wir Zeit, um das Lösegeld zu sammeln.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "Hab's verstanden. In einer Woche, Nördlicher Golf. Vergiss nicht, das Geld mitzunehmen: Das muss hübsch aussehen. Danach komm zu mir, wir werden das klären.";
			link.l1 = "Natürlich, ich wette, sogar der Seeigel hätte das herausgefunden. Bis später! ";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //снять таймер
			dialog.text = "He, Froschfresser! Halt!";
			link.l1 = "Ich bewege mich nicht.";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "Hier ist euer Baron. Ein bisschen abgenutzt, aber in einem Stück. Ist er es?";
			link.l1 = "Ja.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Perfekt. Jetzt gib das Geld her oder er ist erledigt! Und versuch nicht uns zu täuschen, wir haben dich im Visier!";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "Hier.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "Verdammt! Ich habe es auf dem Schiff vergessen...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "Ha-ha-ha! Du bist ein schlauer Bursche, Franzose. Nimm deine Heiligkeit. Und sag Poincy, er soll das Geld vorbereiten: alle französischen Bastarde werden für das bezahlen müssen, was du Levasseur und Tortuga angetan hast. Und eure Händler werden uns mit ihren, Gütern und Schiffen bezahlen. Ha-ha-ha! Vergiss nicht, uns noch mehr Barone ins Archipel zu bringen, sie bringen uns viel Profit! Ha-ha-ha!";
			link.l1 = "Bitte gehen Sie zu meinem Boot, Baron.";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "Und denk nicht mal daran, uns zu verfolgen, Kapitän. Du weißt, wer ich bin. Ich habe mehr Froschfresser als Gefangene, und wenn ich nicht rechtzeitig nach Hause komme, werden sie alle von meinen Männern getötet. Kapiert?";
			link.l1 = "Die Zeit wird kommen und wir werden mit euch, verfluchten Blasphemikern, fertig werden!";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Ha-ha-ha-ha!";
			link.l1 = "..., Freund.";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "Spielst du mit mir?";
			link.l1 = "Einen Moment, ich bringe es...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "Argh, Steven, was hat dein Dummkopf gemacht!";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			dialog.text = "Charles, was hast du getan? Wo ist das Geld? Ich habe meinen Jungs nicht gesagt, dass das nicht echt war... und so hat dieser Idiot entschieden, dass du sie überlisten wolltest...";
			link.l1 = "Wie schade! Der Baron ist tot... Was wird Poincy jetzt tun?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_26":
			dialog.text = "Nun, Kumpel, es ist deine Schuld, ich hoffe du verstehst das. Vielleicht wird es dir dadurch nur besser gehen.";
			link.l1 = "Was für ein Idiot ich bin! Alles vermasselt. Gut, ich gehe nach Poincy... Verzeih mir, dass ich ein Narr bin, Steven, wir sehen uns.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Du musst dich ausruhen, du verlierst deine Fähigkeiten. Komm mal zu mir, ich besorge dir etwas Rum und feine Maiden.";
			link.l1 = "Danke, ich werde dich besuchen, wenn ich kann.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "Du bist willkommen, Kumpel. Für mich war das der meiste Spaß, den ich dieses Jahr hatte! Wir haben so viel gelacht, ich und meine Jungs!.. Also möchte ich dir dafür danken. Hier ist dein Geld.";
			link.l1 = "Du solltest dir einen Anteil behalten.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Vergiss es. Ich habe das um unserer Freundschaft willen getan. Die Bruderschaft der Küste schuldet dir viel mehr, und doch hast du keinen einzigen Dublon gefordert.";
			link.l1 = "Dennoch, nimm mindestens fünfzigtausend für die Dienste und Entschädigung. Danke, Steven! Ich bin froh, dass ich dich einmal auf dieser seltsamen Insel der verlorenen Schiffe getroffen habe.";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "Und ich auch. Charles, besuch mich, wann immer du etwas Zeit hast!";
			link.l1 = "Mit Vergnügen!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "Du bist eine Woche zu spät! Ich habe meinen Jungs nicht gesagt, dass das nicht echt war...! Sie wollten nicht länger warten und beschlossen, deinen Baron zu beenden!";
			link.l1 = "Wie ein Idiot bin ich! Alles vermasselt! Was soll ich Poincy erzählen?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "Nun, Kumpel, es ist deine Schuld, ich hoffe, du verstehst das. Vielleicht wird es für dich umso besser sein.";
			link.l1 = "Gut, ich gehe nach Poincy... Vergib mir, dass ich ein Narr bin, Steven, wir sehen uns...";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			dialog.text = "Du musst dich ausruhen, du verlierst deine Fähigkeiten. Komm mal zu mir, ich besorge dir etwas Rum und feine Mägde";
			link.l1 = "Danke, ich werde dich besuchen, wenn ich kann.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
		// belamour legendary edition хвастаемся Фортуной
		case "check_out_my_frigate":
			dialog.text = "Interessant, fasziniert. Na gut, lass uns einen Spaziergang machen.";
			link.l1 = "...";
			link.l1.go = "check_out_my_frigate_01";
		break;
		
		case "check_out_my_frigate_01":
			DialogExit();
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			DoQuestReloadToLocation("pirates_town", "reload", "reload3_back", "SharkFrigateToTown");
			pchar.questTemp.SharkFrigate = true;
		break;
		
		case "check_out_my_frigate_02":
			dialog.text = "Zum Teufel! Ich kann meinen Augen nicht trauen! Ist sie es wirklich? Sag mir, ist sie es? Ist das die 'Fortune'?!";
			link.l1 = "Ja, mein Freund, deine Augen täuschen dich nicht. Das ist sie. Hast du sie vermisst?";
			link.l1.go = "check_out_my_frigate_03";
		break;
		
		case "check_out_my_frigate_03":
			dialog.text = "Ha ha ha, ich kann es nicht glauben! Tausend Teufel! Aber wo hast du es her?";
			link.l1 = "Von einem gewissen Schotten namens William Paterson. Ja, ja, von dem, der es vom Schwarzen Pastor gekauft hat.";
			link.l1.go = "check_out_my_frigate_04";
		break;
		
		case "check_out_my_frigate_04":
			dialog.text = "Verflucht... Und was, er hat dir 'Fortune' verkauft? So ein wunderschönes Schiff? Nachdem du es gekauft hast?";
			link.l1 = "Hehe, nun, fast. Sagen wir es so: wir kamen überhaupt nicht miteinander aus, und ich nahm das Schiff als Ausgleich für die Kosten, die mir durch unseren Konflikt entstanden sind. Er braucht sowieso kein Schiff.";
			link.l1.go = "check_out_my_frigate_05";
		break;
		
		case "check_out_my_frigate_05":
			dialog.text = "Du überraschst mich immer mehr ... Er ist ein Militärkapitän im Dienst von England. Sein Geschwader der Kolonie kann nach Belieben ausrauben. Selbst ich habe es nicht gewagt, mir die Zähne an ihm auszubeißen. Und wie hast du es geprüft? Ist es dir gelungen, die 'Fortune' vom Geschwader zu reißen?";
			link.l1 = "Nein, das Geschwader sank. Tatsächlich war es nicht einfach. Die Schlacht war ernst, aber sie fand weit entfernt von bewohnten Orten statt, und nur meine Matrosen und Offiziere waren unter den Zeugen. Im Allgemeinen fürchte ich keine Verfolgung durch die britischen Behörden. William Paterson verschwand einfach während irgendeines regelmäßigen Abenteuers ...";
			link.l1.go = "check_out_my_frigate_06";
		break;
		
		case "check_out_my_frigate_06":
			dialog.text = "Wahnsinn... Ich habe schon lange die Hoffnung verloren, meine Schwalbe wiederzusehen. Nun, ich hoffe, dieses Schiff wird dir treu dienen. Wirklich froh für dich, Freund!";
			link.l1 = "Was? Brauchst du ihn nicht? Ich wollte ihn seinem rechtmäßigen Besitzer zurückgeben...";
			link.l1.go = "check_out_my_frigate_07";
		break;
		
		case "check_out_my_frigate_07":
			if(CheckAttribute(pchar, "questTemp.SharkGoldFleet"))
			{
				dialog.text = "Ha-ha-ha, mein Freund, behalte 'Fortune' für dich. Erstens, du bist ihr rechtmäßiger Besitzer. Du hast sie ehrlich im Kampf erworben. Es ist nicht gut, das Schiff nach all dem zu verlassen. Und zweitens, ich habe bereits ein neues Schiff. Natürlich, als ich 'Fortune' gekauft habe, dachte ich nicht, dass ich sie jemals für etwas anderes eintauschen würde. Aber, da ich nicht erwartet habe, sie wieder zu sehen, habe ich bei Alexus einen neuen Fregatten bestellt. Und weißt du... Er ist verdammt gut. Ich habe gehört, und in diesem Fall war es nicht ohne deine Beteiligung, ha ha!";
			}
			else
			{
				dialog.text = "Ha-ha-ha, mein Freund, behalte die 'Fortune' für dich. Erstens, du bist ihr rechtmäßiger Besitzer. Du hast sie ehrlich im Kampf bekommen. Es ist nicht gut, das Schiff nach so etwas zu verlassen. Und zweitens, für mich wird bereits ein neues Schiff gebaut. Natürlich, als ich die 'Fortune' gekauft habe, dachte ich nicht, dass ich sie jemals für etwas anderes wechseln würde. Aber, da ich schon nicht erwartet hatte, sie wieder zu sehen, habe ich bei Alexus einen neuen Fregatten bestellt. Und ich freue mich darauf, wann ich seinen Deck betreten kann.";
			}
			link.l1 = "Nun, dann habe ich keine andere Wahl, als dieses schöne Schiff für mich selbst zu behalten, Steven!";
			link.l1.go = "check_out_my_frigate_08";
		break;
		
		case "check_out_my_frigate_08":
			dialog.text = "Genau. Das Einzige, was ich von dir verlange, ist, dass du dich um 'Fortune' kümmerst. Glaub mir, du wirst nirgendwo ein solches Schiff finden. Es ist einzigartig. Und ich liebe es als Erinnerung. Und es würde mich freuen zu wissen, dass mein Freund dieses Schiff besitzt, und nicht irgendein Halunke.";
			link.l1 = "Gut Steven. Ich verspreche, dass ich 'Fortune' schützen werde.";
			link.l1.go = "check_out_my_frigate_09";
		break;
		
		case "check_out_my_frigate_09":
			dialog.text = "Ja, und noch eine Sache...";
			link.l1 = "Hör zu.";
			link.l1.go = "check_out_my_frigate_10";
		break;
		
		case "check_out_my_frigate_10":
			dialog.text = "Da du jetzt 'Fortune' hast, möchte ich dir ein Geschäft anbieten.";
			link.l1 = "Ich höre dir SEHR aufmerksam zu.";
			link.l1.go = "check_out_my_frigate_11";
		break;
		
		case "check_out_my_frigate_11":
			if(!CheckAttribute(pchar, "questTemp.SharkGoldFleet.KGBB"))
			{
				dialog.text = "Wie ich bereits sagte, baut Alexus derzeit eine neue Fregatte für mich. Er wird natürlich die 'Fortune' in Sachen Geschwindigkeit kaum übertreffen, aber er wird auch nicht viel nachgeben. Und genau für eine Sache brauche ich ein paar leistungsstarke, aber schnelle Schiffe. Ich könnte es alleine schaffen, aber zwei sind viel besser.";
				link.l1 = "Großartig. Und um welche Art von Geschäft handelt es sich hier?";
				link.l1.go = "check_out_my_frigate_12";
			}
			else
			{
				dialog.text = "Wie ich bereits sagte, hat Alexus kürzlich eine neue Fregatte für mich gebaut. Er wird natürlich die 'Fortune' wahrscheinlich nicht in Geschwindigkeit übertreffen, aber er wird auch nicht viel nachgeben. Und nur für eine Sache brauche ich ein paar mächtige, aber schnelle Schiffe. Ich könnte es alleine schaffen, aber zwei sind viel besser.";
				link.l1 = "Gut. Und was für ein Geschäft ist das?";
				link.l1.go = "check_out_my_frigate_13";
			}
		break;
		// Фрегат Акулы не построен
		case "check_out_my_frigate_12":
			dialog.text = "Es ist zu früh, darüber zu sprechen, denn ich weiß noch nicht, wann mein neues Schiff die Werft verlässt. Alexus scheint einige Schwierigkeiten bei der Materialbeschaffung zu haben. Übrigens, wenn du die Möglichkeit hast, könntest du ihm helfen. Ich bin sicher, dass er anständig bezahlen wird: Ich habe ihm einen sehr ernsthaften Vorschuss gegeben. Nachdem er alle Materialien gefunden hat, denke ich, wird mein Schiff in einem Monat fertig sein. Dann warte ich auf dich. Aber komm unbedingt auf der 'Fortune' und rüste sie im Voraus aus, dann wird wenig Zeit sein! Ja, und sorge dafür, dass die Spanier deinen Kopf nicht auf einer Silberplatte sehen wollen. Die Einzelheiten erzähle ich dir später.";
			link.l1 = "Nun, ich werde unseren Schiffbauer fragen, welche Hilfe er vielleicht braucht. Und wir werden unsere Unterhaltung dann einen Monat nachdem ich Alexus geholfen habe fortsetzen, wenn du wieder segeln wirst.";
			link.l1.go = "check_out_my_frigate_14";
		break;
		
		// Фрегат Акулы построен
		case "check_out_my_frigate_13":
			dialog.text = "Es ist noch zu früh, darüber zu sprechen, denn mein Schiff hat noch nicht einmal die Werft verlassen. Ich muss es noch ausrüsten. Also erwarte ich dich nicht früher als in einem Monat. Aber komm unbedingt auf der 'Fortune' und rüste sie im Voraus aus, dann bleibt wenig Zeit! Ja, und achte darauf, dass die Spanier deinen Kopf nicht auf einem Silbertablett sehen wollen. Die Details erzähle ich dir später.";
			link.l1 = "Gut, dann kommen wir später zu unserem Gespräch zurück, wenn ihr wieder unter Segel seid.";
			link.l1.go = "check_out_my_frigate_14";
		break;
		
		case "check_out_my_frigate_14":
			dialog.text = "Nun, gut. Jetzt gehe ich zur Residenz, wenn es dir nichts ausmacht. Dinge, wie man so schön sagt, warten nicht.";
			link.l1 = "Bis bald, Hai! Ich sag nicht auf Wiedersehen.";
			link.l1.go = "check_out_my_frigate_15";
		break;
		
		case "check_out_my_frigate_15":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload3_back","SharkFrigateEnd", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// belamour legendary edition на пару с Акулой
		case "SharkGoldFleet":
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = "Meins ist bereit, wie sieht's mit deinem aus? Ich habe dir gesagt, du sollst auf die 'Fortune' kommen. Ich weiß nicht, wo du es gelassen hast, aber es ist zu riskant, sich auf so ein Glücksspiel auf irgendeinem anderen Schiff einzulassen. Also warte ich auf dich auf dem Schiff, auf das wir uns geeinigt haben. Und zieh nicht zu fest an.";
				link.l1 = "Verdammt, ich habe komplett vergessen, du Mistkerl! Warte: Ich werde zurück auf dem richtigen Schiff sein.";
				link.l1.go = "exit";
				break;
			}
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Charles, ich habe dir gesagt, du sollst ohne Geschwader kommen. Bei dem Geschäft, das ich mit dir machen möchte, werden definitiv keine zusätzlichen Schiffe benötigt. Verlagere deine Flotte irgendwohin und komm zurück.";
				link.l1 = "Ja, ich habe es komplett vergessen. Warte: Ich komme bald ohne Geschwader zurück.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Ach, da bist du ja, Freund! Endlich! Und dann habe ich angefangen, mir Sorgen zu machen. Mein Schiff ist fast fertig. Jetzt habe ich ihn zu Tirax geschickt: er muss ihn mit dem Zweiunddreißigsten Kaliber ausrüsten, das er letzten Monat vom Prisenschweren Galeon genommen hat. Ich bin schon zu den Türken und zurück geritten, und ich muss sagen, dass Alexus einen tollen Job gemacht hat. Übrigens habe ich noch keinen passenden Namen dafür ausgewählt, obwohl es mehrere Optionen gibt. Kannst du mir helfen, zu wählen?";
			link.l1 = "Natürlich helfe ich! Wie auch immer du ein Schiff nennst, so wird es fliegen, nicht wahr? Was sind deine Optionen?";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "Ich habe mich bisher auf drei Optionen festgelegt.";
			link.l1 = "..., Freund.";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "Die erste Option ist 'Phantom'. Die Fregatte ist schnell und mächtig, und bei diesem Namen werden alle Geizhälse von Havanna bis Cumana beim bloßen Erwähnen zittern!";
			link.l1 = "Ja, und du musst auch im Nebel erscheinen und verschwinden, damit die Seeleute definitiv anfangen, getauft zu werden, ha ha! Guter Name, ich mag es.";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "Mir gefällt es auch. Die zweite Option ist 'Hai'. Und was? Warum gebe ich meinem Schiff nicht seinen eigenen Spitznamen? Lassen Sie uns Namensvettern mit ihm sein, ha!";
			link.l1 = "Es gibt einen Hai auf dem 'Hai'... Ironisch. Aber jeder wird genau wissen, wer das Schiff besitzt.";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "Hier bin ich ungefähr gleich. Und die dritte Option ist 'Sturm'. Um jeden Angst zu machen, sich auch nur in die Nähe meines Schiffes zu wagen, ha ha ha!";
			link.l1 = "Weil du von der Seite in einen Schwall von Bällen geraten kannst? Und was, nicht schlecht.";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "Genau! Aber jetzt kann ich mich nicht zwischen diesen drei Namen entscheiden. Also los, hilf. Wie du willst.";
			link.l1 = "Ich schlage vor, es 'Phantom' zu nennen. Dann werden alle Händler die weiße Flagge hissen, sobald sie dich am Horizont sehen!";
			link.l1.go = "SharkGoldFleet_05f";
			link.l2 = "Ich mag den Namen 'Hai'. Jeder sollte wissen, dass das Schiff kein Neuling ist, sondern der Anführer der Bruderschaft der Küste selbst!";
			link.l2.go = "SharkGoldFleet_05a";
			link.l3 = "Ich denke, 'Flurry' ist ein guter Name. Jeder Krieger, Freibeuter oder Händler sollte wissen, was passieren wird, wenn er sich entscheidet, gegen dieses Schiff zu kämpfen.";
			link.l3.go = "SharkGoldFleet_05s";
		break;
		
		case "SharkGoldFleet_05f":
			pchar.questTemp.SharkGoldFleet.KGBB = "Phantom";
			dialog.text = "Du siehst aus - sogar das Militär wird das Gleiche tun, ha! Also, es ist beschlossen. Halte den Krug, Freund. Lass uns auf mein neues Schiff trinken. Für 'Phantom!'";
			link.l1 = "Für 'Phantom!'";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_05a":
			pchar.questTemp.SharkGoldFleet.KGBB = "Shark";
			dialog.text = "Und lass sie dreimal nachdenken, bevor sie meinen Weg kreuzen! Also, es ist entschieden. Halt den Krug, Freund. Lasst uns auf mein neues Schiff trinken. Für 'Hai'!";
			link.l1 = "Für 'Hai'!";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_05s":
			pchar.questTemp.SharkGoldFleet.KGBB = "Flurry";
			dialog.text = "Und wenn er sich immer noch entscheidet, wird ihn so ein Schneesturm bedecken, dass tropische Stürme wie eine leichte Brise erscheinen! Also, es ist entschieden. Halte den Krug, Freund. Lassen wir auf mein neues Schiff trinken. Für 'Sturm!'";
			link.l1 = "Für 'Sturm!'";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "Und möge dieses Schiff treu dienen und die Bitterkeit der Niederlage nicht kennen! Nun, jetzt zum Punkt.";
			link.l1 = "Ich höre dir genau zu.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Sag mal, Charles, weißt du was die 'Goldene Flotte' ist?";
			link.l1 = "Kha-kha! .. Ich habe schon am Rum erstickt. Steven, sag mir nicht, dass du mit zwei Fregatten den am stärksten bewaffneten Konvoi in der Karibik ausrauben willst.";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			dialog.text = "Nun, nein, natürlich bin ich nicht selbstmörderisch. Wir werden definitiv nicht den ganzen Konvoi ausrauben. Aber hier können wir etwas davon schnappen.";
			link.l1 = "Steven, es tut mir leid, natürlich, aber ich bin nicht bereit für das. Ja, die Spanier werden uns lebendig verbrennen, wenn wir uns in ihre Flotte einmischen! Geh ohne mich.";
			link.l1.go = "SharkGoldFleet_09";
			link.l2 = "Gut, wo wir nicht verschwunden sind... Ich bin bereit teilzunehmen!";
			link.l2.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_09":
			pchar.questTemp.SharkGoldFleet = "RUinDeal";
			dialog.text = "Argh! Es ist eine Schande. Ohne dich bin ich zu riskant. Gut, jetzt werde ich nicht überreden, aber denk darüber nach, ja? Wenn du dich jemals dazu entscheidest, lass es mich wissen.";
			link.l1 = "Wenn ich es tue, dann sicher. Entschuldigung Steven.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "Solche Unternehmungen gibt man nicht auf! Nun, was ist mit dir? Vielleicht hast du deine Meinung geändert?";
			link.l1 = "Nein, Freund, es tut mir leid, aber ich passe immer noch.";
			link.l1.go = "exit";
			link.l2 = "Gut, wo wir nicht verschwunden sind ... Ich bin bereit teilzunehmen!";
			link.l2.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = "Du bist vielleicht bereit, aber dein Schiff ist es nicht. Ich habe dir gesagt, du sollst auf 'Fortune' kommen. Ich weiß nicht, wo du es gelassen hast, aber es ist zu riskant, ein solches Glücksspiel auf einem anderen Schiff zu wagen. Also warte ich auf dich auf dem Schiff, auf dem wir uns geeinigt haben. Und zieh nicht zu fest an.";
				link.l1 = "Verdammt, ich habe es vollkommen vergessen, Tölpel! Warte: Ich werde auf dem richtigen Schiff zurück sein.";
				link.l1.go = "exit";
				break;
			}
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Aber nein: du bist noch nicht bereit, Charles. Ich habe dir gesagt, du sollst ohne Geschwader kommen. Bei dem Fall, den ich mit dir vorhabe, sind zusätzliche Schiffe definitiv nicht nötig. Verlege deine Flotte irgendwohin und komm zurück.";
				link.l1 = "Ja, ich habe es völlig vergessen. Warte: Ich werde bald ohne Geschwader zurück sein.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Tausende von Teufeln, das ist genau das, was ich hören wollte! Also, schlage ich vor, dass du und ich ein Stück aus dem Konvoi schnappen. Viel Beute...";
			link.l1 = "Meinst du schnappen, ohne von den Wachschiffen erwischt zu werden?";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			dialog.text = "Genau. Sieh mal, wie du wahrscheinlich weißt, sammelt sich die 'Goldene Flotte' in Porto Bello und geht von dort nach Havanna. Nach Havanna ist es schon nutzlos, ihn abzufangen: Er überquert den Atlantik nach Spanien mit solchen Wachen, dass nur ein völliger Idiot seinen Kopf zu ihm aufstecken würde. Zur Zeit des Übergangs von Porto Bello nach Havanna ist die Situation kaum besser. Natürlich kannst du es versuchen, aber dafür musst du eine Staffel zusammenstellen, die sogar in der Lage ist, Festungen wie Nüsse zu knacken. Aber in Porto Bello treffen Schiffe aus ganz Maine zusammen, und dort sind sie nicht mehr besonders geschützt.";
			link.l1 = "Nur jetzt ist die Zeit des Übergangs und die Namen solcher Schiffe streng geheim. Wir werden nicht in Porto Bello herumlungern und ein halbes Jahr lang alle spanischen Schiffe abfangen, die den Hafen anlaufen.";
			link.l1.go = "SharkGoldFleet_13";
		break;
		
		case "SharkGoldFleet_13":
			dialog.text = "Natürlich werden wir das nicht tun. Von Cartagena aus gehen die Schiffe beispielsweise von selbst, und, wie Sie richtig bemerkt haben, weiß nur Gott, um welche Art von Schiffen es sich handelt und wann sie gehen werden. Aber von Caracas, neben dem eine spanische Mine liegt und das ziemlich weit von Porto Bello entfernt ist, sind die Schiffe nicht völlig allein.";
			link.l1 = "Wie ist es nicht völlig allein?";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			dialog.text = "Ich konnte herausfinden, dass ein mit Waren beladenes Schiff alleine oder mit einer kleinen Wache aus Caracas ausläuft, aber irgendwo auf der Länge des Golfs von Maracaibo treffen spanische Kriegsschiffe auf es, um seine weitere Sicherheit zu gewährleisten. Wie denken Sie, wissen sie, wann und wen sie dort treffen müssen?";
			link.l1 = "Sie müssen etwas gesagt bekommen haben...";
			link.l1.go = "SharkGoldFleet_15";
		break;
		
		case "SharkGoldFleet_15":
			dialog.text = "Richtig. Bevor das Hauptschiff ablegt, geht ein Kurierschiff von Caracas nach Porto Bello, es meldet den Ort und das Datum des Treffens, sowie den Namen des spanischen Schiffes. Dann kehrt es zurück und bringt die Bestätigung, dass das Schiff zur richtigen Zeit und am richtigen Ort getroffen wird. Erst danach wird unser gemeinsames Ziel von Caracas aus in Angriff genommen.";
			link.l1 = "Aber wenn wir den Kurier abfangen, wird das Schiff in Caracas keine Bestätigung erhalten und den Hafen nicht verlassen. Hast du dazu eine Idee? Außerdem, wie sollen wir den Kurier selbst fangen? Wir wissen auch nicht, wann er abfahren wird.";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_16":
			dialog.text = "Und hier gibt es eine kleine Hürde. Die Spanier verwenden natürlich Kurierkutter für diese Zwecke, aber das ist riskant: die Chance ist zu groß, dass sie vom ersten Konterpiraten abgefangen werden. Also kann man lange warten, bevor man das Schiff schickt. Deshalb übermitteln sie, wenn möglich, Anweisungen zusammen mit guten, starken, aber schnellen Schiffen - Kaufleuten zum Beispiel oder Kaperfahrern, die die richtige Route nehmen. \nGenauso wie eine versiegelte Post. Außerdem ist es viel billiger als das Senden eines separaten Kurierschiffs, sogar eines Kutters. Und gierige spanische Beamte sparen gerne Geld, während sie etwas in ihre Tasche stecken, hehe.";
			link.l1 = "Ich glaube, ich verstehe! Muss ich so ein Kaufmann werden?";
			link.l1.go = "SharkGoldFleet_17";
		break;
		
		case "SharkGoldFleet_17":
			dialog.text = "Genau! Und wir hatten Glück: Ich habe es geschafft, von einer zuverlässigen Quelle herauszufinden, dass sie in Caracas jetzt nach einem solchen Kurier suchen, um ihn in den nächsten drei Wochen mit einem Brief zu schicken. Und du hast gerade ein mächtiges und schnelles Schiff, und sogar von den Spaniern gebaut! Besorge dir eine GVIK-Lizenz, für mehr Glaubwürdigkeit - gleich für sechs Monate, kaufe genug Waren in Caracas für einen profitablen Weiterverkauf in Porto Bello, und dann geh zum örtlichen Hafenmeister und frag, ob du unterwegs etwas mitnehmen musst. \nWenn die Hafenbehörde fragt, stelle dich als Spanier vor. Und ja - denke nicht einmal daran, eine Geschwader mit dir zu schleppen. Wir brauchen nicht zu viel Aufmerksamkeit auf uns zu ziehen, sonst könnte das ganze Unternehmen bedeckt sein.";
			link.l1 = "Und aus den Dokumenten, die sie mir geben werden, werde ich das Datum und den Ort des Treffens des Schiffes und des Konvois herausfinden?";
			link.l1.go = "SharkGoldFleet_18";
		break;
		
		case "SharkGoldFleet_18":
			dialog.text = "Nicht so einfach. Ich sage dir: die Dokumente sind versiegelt. Und du kannst sie nicht selbst öffnen. Sie werden sie bei der Hafenbehörde von Porto Bello öffnen, und dann werden sie eine Antwort schreiben und, wenn du so freundlich wärst zu sagen, dass du nach Caracas zurückkehrst, werden sie dich bitten, ihn dorthin zu bringen. Die Antwort wird natürlich auch versiegelt sein.";
			link.l1 = "Und wie kann ich dann den Ort und das Datum des Treffens herausfinden?";
			link.l1.go = "SharkGoldFleet_19";
		break;
		
		case "SharkGoldFleet_19":
			dialog.text = "Sie müssen schlau sein und es irgendwie ausspionieren... Zum Beispiel in dem Moment, wenn in Porto Bello Dokumente geöffnet werden und sie die Antwort schreiben. Oder stehlen Sie sie einfach, wenn sie Ihnen eine Bestätigung geben, die nach Caracas gebracht werden muss. Aber das ist keine gute Option: danach kann alles schief gehen.";
			link.l1 = "Es ist natürlich schwierig ... Aber ich denke, ich kann damit umgehen.";
			link.l1.go = "SharkGoldFleet_20";
		break;
		
		case "SharkGoldFleet_20":
			dialog.text = "Ich meinerseits werde mein Schiff von Marcus nehmen und vor Kap Santa Maria in Curacao auf dich warten. Wenn du fertig bist, komm einfach zu mir. Wir fangen das Schiff an den angegebenen Koordinaten ab und verschwinden dann sofort zur Hölle. Jetzt verstehst du, warum Schiffe mächtig, aber schnell sein müssen? Ich möchte überhaupt nicht gegen die spanische Militäreskorte kämpfen. Du wirst vor ihnen fliehen müssen.";
			link.l1 = "Verstanden. Nun, dann ziehe ich los. Triff mich am Kap Santa Maria!";
			link.l1.go = "SharkGoldFleet_21";
		break;
		
		case "SharkGoldFleet_21":
			dialog.text = "Das ist richtig, wir treffen uns dort. Nun, viel Glück Freund! Hoffe, unser Geschäft klappt.";
			link.l1 = "Ich hoffe es auch. Wie auch immer, ich gehe jetzt.";
			link.l1.go = "SharkGoldFleet_22";
		break;
		
		case "SharkGoldFleet_22":
			DialogExit();
			AddQuestRecord("SharkGoldFleet", "1");
			pchar.questTemp.SharkGoldFleet = "start";
			SetFunctionExitFromLocationCondition("SharkGoldFleetStart", pchar.location, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleet21", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleet30", 0, 0, 30, false);
			else NewGameTip("Exploration mode: timer is disabled.");
		break;
		// провал
		case "SharkGoldFleet_23":
			dialog.text = "Verdammt Charles! Ich dachte, ich würde dich nie wiedersehen! Wo warst du? Ich habe auf dich an dem vereinbarten Ort gewartet, aber du bist nie gekommen. Und von dir gab es keine Neuigkeiten.";
			link.l1 = "Entschuldigung Steven. Ich konnte meine Aufgabe nicht erfüllen.";
			link.l1.go = "SharkGoldFleet_24";
		break;
		
		case "SharkGoldFleet_24":
			NextDiag.CurrentNode = "First time";
			dialog.text = "Eh, sie haben so einen Fisch verpasst ... Na gut, sei nicht traurig. Nächstes Mal hast du mehr Glück.";
			link.l1 = "Hoffentlich.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_25":
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = pchar.name+", was zum Teufel? Ich habe dir gesagt, dass du ohne Geschwader sein sollst! Versteh: wir brauchen keinen Ballast, sonst könnte die ganze Operation scheitern! Ich weiß nicht, was dich geritten hat, aber so wird das nicht funktionieren. Schicke deinen Karawanen dringend irgendwohin und kehre auf einem Schiff zurück. Ich warte hier auf dich.";
				link.l1 = "Ja, ich dachte nur, dass dies wahrscheinlicher ist ... Gut, ich verstehe dich. Warte hier: Ich komme gleich wieder!";
				link.l1.go = "exit";
				NextDiag.TempNode = "SharkGoldFleet_25";
				break;
			}
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = pchar.name+", was zum Teufel? Ich habe dir gesagt, du sollst auf der 'Fortune' sein! Versteh: wir brauchen zwei schnelle und mächtige Schiffe, sonst könnte die ganze Operation scheitern! Ich weiß nicht, was dich geritten hat, aber so wird das nicht funktionieren. Wechsle dringend deine Pritsche zur 'Fortune' und komm zurück. Ich warte hier auf dich.";
				link.l1 = "Ja, ich dachte nur, dass dieses Schiff besser ist ... Gut, ich verstehe dich. Warte hier: Ich komme gleich zurück!";
				link.l1.go = "exit";
				NextDiag.TempNode = "SharkGoldFleet_25";
				break;
			} 
			dialog.text = "Und hier bist du, mein Freund! Nun, wie gefällt dir mein Hübscher?";
			link.l1 = "Wunderschöne Fregatte, Steven! Ich würde das nicht ablehnen...";
			link.l1.go = "SharkGoldFleet_26";
		break;
		
		case "SharkGoldFleet_26":
			dialog.text = "Nein, jetzt hast du 'Glück', haha! Na, erzähl mir, wie es gelaufen ist.";
			if(pchar.questTemp.SharkGoldFleet == "LightVarToShark")
			{
				link.l1 = "Alles lief einwandfrei: Ich schaffte es, einen ehrlichen und zuverlässigen Händler zu imitieren. Ich brachte die Dokumente nach Porto Bello, wo es mir gelang, den örtlichen Hafenmeister fünf Minuten lang abzulenken und das Datum und die Koordinaten des Treffens der Schiffe mit der Fracht und der Militäreskorte für mich umzuschreiben.";
				link.l1.go = "SharkGoldFleet_27";
			}
			else
			{
				link.l1 = "Es gab einige kleinere Komplikationen. Der Brief wurde per Kurier nach Porto Bello geschickt. Ich habe ihn abgefangen, an den Empfänger geliefert und sogar eine Antwort erhalten, aber der Leiter der Hafenbehörde vermutete, dass ich nicht die Person war, die die Dokumente bringen sollte. Ich musste mich mit einem Kampf daraus befreien. Aber ich habe das Datum und die Koordinaten des Treffens des Schiffes mit der Fracht und der Militäreskorte herausgefunden und die Antwort nach Caracas geliefert, also wartet die Produktion auf uns!";
				link.l1.go = "SharkGoldFleet_30";
			}
		break;
		
		case "SharkGoldFleet_27":
			dialog.text = "Warte mal. Hast du 'Schiffe' gesagt?";
			link.l1 = "Ja, Hai! Es werden zwei von ihnen sein!";
			link.l1.go = "SharkGoldFleet_28";
		break;
		
		case "SharkGoldFleet_28":
			dialog.text = "Ha-ha-ha, ja, wir werden den Jackpot knacken! Nun, meine Bestie ist bereit, ein Feuertaufe zu durchlaufen. Aber er hat noch nicht an den Kämpfen teilgenommen, also lass uns die Schlacht führen. Und vorerst werde ich mich deinem Geschwader anschließen.";
			link.l1 = "Bin ich etwa befehlen Steven Dodson selbst, dem Anführer der Bruderschaft der Küste? Im Geschäft!";
			link.l1.go = "SharkGoldFleet_29";
		break;
		
		case "SharkGoldFleet_29":
			NextDiag.TempNode = "SharkGoldFleet_33";
			pchar.questTemp.SharkGoldFleet.talk = true;
			AddQuestRecord("SharkGoldFleet", "22");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			SGF_SharkCompanion();
			pchar.quest.SGF_SharkDelGroup1.win_condition.l1 = "ExitFromSea";
			pchar.quest.SGF_SharkDelGroup1.function = "SGF_SharkDelGroup";
			if(bImCasual)
			{
				pchar.GenQuest.SeaHunter2Pause = true;
				SeaHunter_Delete();
			}
			dialog.text = "Nun, sei nicht zu arrogant: es ist nur, weil ich das erste Mal auf meinem Schiff kämpfen werde. Und sorge für freie Offiziere für Prisenschiffe. Denn deren Laderäume werden vollgepackt sein, und keiner meiner Mannschaft wird in der Lage sein, das Schiff alleine zu managen... Gut, genug mit dem Geplapper. Die Beute wartet auf uns!";
			link.l1 = "Genau! Ich gehe zu meinem Schiff.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_30":
			dialog.text = "Ja, du hast geerbt ... Dann müssen wir uns darauf vorbereiten, dass die Staffel dort vor dem vereinbarten Termin ankommt und wir mit allen gleichzeitig kämpfen müssen.";
			link.l1 = "Warum sagst du das?";
			link.l1.go = "SharkGoldFleet_31";
		break;
		
		case "SharkGoldFleet_31":
			dialog.text = "Und du grübelst. In Porto Bello wissen sie, dass das Schiff mit der Fracht definitiv Caracas verlassen wird, weil du den Rückbrief dorthin gebracht hast. Aber da du dich verraten hast, werden sie ihr Bestes geben, um zu verhindern, dass wir dieses Schiff abfangen. Ich denke, dass die Geschwader dort früher ankommen werden. Das würde ich tun. Also, bereiten wir uns auf einen harten Kampf vor. Spätes Rückzug.";
			link.l1 = "Mach dir keine Sorgen. Du und ich sind zwei Seewölfe, wir haben das nicht durchgemacht!";
			link.l1.go = "SharkGoldFleet_32";
		break;
		
		case "SharkGoldFleet_32":
			dialog.text = "Deine Wahrheit. Nun, mein Biest ist bereit, ein Feuertaufe zu durchlaufen. Aber er hat noch nicht an den Schlachten teilgenommen, also lass uns die Schlacht führen. In der Zwischenzeit werde ich mich deinem Geschwader anschließen.";
			link.l1 = "Bin ich etwa der Befehlshaber von Stephen Dodson selbst, dem Oberhaupt der Bruderschaft der Küste? Im Geschäft!";
			link.l1.go = "SharkGoldFleet_29";
		break;
		
		case "SharkGoldFleet_33":
			NextDiag.TempNode = "SharkGoldFleet_33";
			dialog.text = "Keine Zeit zum Plaudern, "+pchar.name+"! Auf zur Beute!";
			link.l1 = "Und möge das Glück mit uns sein!";
			link.l1.go = "exit";
		break;
		// делим добычу на берегу
		case "SharkGoldFleet_34":
			if(makeint(pchar.questTemp.SharkGoldFleet) > 74)
			{
				dialog.text = "Tausend Teufel! Großartige Arbeit, Charles! Die Beute stellte sich als viel reicher heraus als ich ursprünglich dachte! Ich glaube, diese ganze Reise hat sich definitiv gelohnt.";
				link.l1 = "Ich stimme dir vollkommen zu, Steven! Heute ist definitiv unser Tag!";
				link.l1.go = "SharkGoldFleet_35";
			}
			else
			{
				if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
				{
					dialog.text = "Gute Arbeit, Freund. Obwohl, wir müssen zugeben, dass wir viel Beute verloren haben.";
					link.l1 = "Ich stimme zu, Steven, wir könnten es besser machen. Aber was da ist, ist auch gut!";
					link.l1.go = "SharkGoldFleet_35";
				}
				else
				{
					dialog.text = "Verdammt! Es war solch eine gute Idee ... Und als Ergebnis sind die Ausgaben aus dieser Kampagne mehr als Gewinne. Charles, ich habe dir tatsächlich das Kommando gegeben, und du hast es geschafft, alles zu verlieren!";
					link.l1 = "Sag nichts... Ich bin verdammt wütend auf mich selbst. Wie viel Beute ist uns durch die Finger gerutscht!..";
					link.l1.go = "SharkGoldFleet_37";
				}
			}
		break;
		
		case "SharkGoldFleet_35":
			dialog.text = "Nun, wir haben beide gute Arbeit geleistet. Ich habe den Plan erstellt und Informationen über den Kurier beschafft, und du hast diesen Plan brillant umgesetzt. Und wir haben beide gleichberechtigt um unsere Beute gekämpft. Daher schlage ich vor, sie nach den Gesetzen der Bruderschaft der Küste zu teilen: gleichmäßig!";
			link.l1 = "Wir machen es!";
			link.l1.go = "SharkGoldFleet_36";
		break;
		
		case "SharkGoldFleet_36":
			dialog.text = "Nun, jetzt gehe ich zur Isla Tesoro. Ich muss das Schiff reparieren und die erste erfolgreiche Reise auf meinem neuen Schiff ordentlich waschen. Viel Glück, Freund! Immer froh, dich in meiner Residenz zu sehen!";
			link.l1 = "Ich bin froh, dass unser Geschäft so profitabel geworden ist. Ich werde dich definitiv irgendwann besuchen. Viel Glück!";
			link.l1.go = "SharkGoldFleet_39";
		break;
		
		case "SharkGoldFleet_37":
			dialog.text = "Gut, behalte alles für dich. Wenn überhaupt noch etwas übrig ist. Diese Kleinen interessieren mich nicht. Schließlich habe ich dich in die ganze Sache hineingezogen.";
			link.l1 = "Ja, mein Fehler auch... Entschuldigung, Steven.";
			link.l1.go = "SharkGoldFleet_38";
		break;
		
		case "SharkGoldFleet_38":
			dialog.text = "Entschuldige dich nicht, ich schulde dir immer noch mein Leben und das werde ich nicht vergessen. Und jetzt bin ich auf dem Weg zur Isla Tesoro. Wir müssen das Schiff reparieren und es waschen ... Obwohl, was gibt es zu waschen ... Viel Glück, Kumpel! Immer froh, dich in meiner Residenz zu sehen!";
			link.l1 = "Na gut, alles kann passieren, Niederlagen passieren. Hauptsache wir sind am Leben. Ich werde dich bestimmt mal besuchen, Freund! Viel Glück!";
			link.l1.go = "SharkGoldFleet_39";
		break;
		
		case "SharkGoldFleet_39":
			if(makeint(pchar.questTemp.SharkGoldFleet) > 74)
			{
				AddQuestRecord("SharkGoldFleet", "34");	
				ChangeCharacterComplexReputation(pchar, "fame", 10);
				ChangeCharacterComplexReputation(pchar, "authority", 5);
				ChangeOfficersLoyality("good_all", 2);
				AddComplexSeaExpToScill(150, 150, 150, 150, 150, 150, 0);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
				AddCharacterExpToSkill(PChar, "Fortune", 300);
				AddCharacterExpToSkill(PChar, "Sneak", 300);
			}
			else
			{
				if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
				{
					AddQuestRecord("SharkGoldFleet", "35");
					ChangeCharacterComplexReputation(pchar, "fame", 1);
					ChangeCharacterComplexReputation(pchar, "authority", 1);
					AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
					AddCharacterExpToSkill(pchar, "Leadership", 200);
					AddCharacterExpToSkill(PChar, "Fortune", 200);
					AddCharacterExpToSkill(PChar, "Sneak", 200);
				}
				else
				{
					AddQuestRecord("SharkGoldFleet", "36");
					AddCharacterExpToSkill(pchar, "Leadership", 100);
					AddCharacterExpToSkill(PChar, "Fortune", 100);
					AddCharacterExpToSkill(PChar, "Sneak", 100);
				}
			}
			if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
			{
				if(GetSquadronGoods(pchar, GOOD_GOLD)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_GOLD, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SILVER)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SILVER, sti(makeint(pchar.questTemp.SharkGoldFleet.Silver)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SANDAL)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(makeint(pchar.questTemp.SharkGoldFleet.Sandal)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SHIPSILK)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SHIPSILK, sti(makeint(pchar.questTemp.SharkGoldFleet.Silk)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_ROPES)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_ROPES, sti(makeint(pchar.questTemp.SharkGoldFleet.Ropes)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_OIL)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_OIL, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold)/2));
				}
			}
			SGF_GoodSwimReturn();
			SGF_DelAllSubAttributes(); // убираем все лишнее, чтобы не болталось
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "SGF_SharkToIT", -1);
			CloseQuestHeader("SharkGoldFleet");
			DialogExit();
		break;
	}
}
