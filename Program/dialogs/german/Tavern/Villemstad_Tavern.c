// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Alle Gerüchte von "+GetCityName(npchar.city)+" zu Ihren Diensten. Was möchten Sie herausfinden?","Wir haben gerade darüber gesprochen. Du musst es vergessen haben...","Das ist das dritte Mal heute, dass du von irgendeiner Frage sprichst...","Du plapperst immer das Gleiche wie ein Papagei...","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Weißt du, "+NPChar.name+", vielleicht nächstes Mal.","Richtig, ich habe aus irgendeinem Grund vergessen...","Ja, es ist wirklich das dritte Mal...","Ja...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//работорговец
			if (pchar.questTemp.Slavetrader == "EscapeSlave_Villemstad")
            {
                link.l1 = "Ich habe gehört, dass es auf der Insel ein heilloses Durcheinander gab... Sklaven?";
                link.l1.go = "EscapeSlaveVillemstad_T1";
            }
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "SeekPortVillemstad")
            {
                link.l1 = "Ich habe gehört, dass dieser verfluchte Schurke Bart der Portugiese endlich Gerechtigkeit getroffen hat! Ist er im Gefängnis? Wann wird seine Hinrichtung sein, weißt du das? Ich möchte zuschauen, ich habe eine Rechnung mit diesem Abschaum zu begleichen...";
                link.l1.go = "Portugal";
            }
			//--> Тайна Бетси Прайс
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern"))
			{
				link.l1 = "Sag mal, "+npchar.name+", ich habe gehört"+GetSexPhrase("","e")+", du hattest kürzlich eine neue hübsche Kellnerin... und sie ist schon verschwunden?";
				link.l1.go = "TBP_Tavern_1";
			}
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern2"))
			{
				link.l1 = "Sag mal, "+npchar.name+", hast du am Abend von Betsys Verschwinden jemanden Verdächtiges in ihrer Nähe gesehen? Vielleicht hat sie mit jemandem gesprochen?";
				link.l1.go = "TBP_Tavern2_11";
			}
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern3"))
			{
				link.l1 = "Na, "+npchar.name+", gute Neuigkeiten – deine wertvolle Kellnerin ist am Leben und wohlauf. Du solltest deinen Rumvorrat wieder auffüllen, die Leute werden bald zurückkehren.";
				link.l1.go = "TBP_Tavern3_21";
			}
			//<-- Тайна Бетси Прайс
 		break;

		//работорговец
		case "EscapeSlaveVillemstad_T1":
			dialog.text = "Ja, so ein Durcheinander gab es noch nie... Mehr als tausend Neger haben sich aufgelehnt. Zwei Plantagen wurden bis auf den Grund niedergebrannt und jeder ihrer Herren wurde ermordet. Der Kommandant befürchtet, dass die Sklaven die Stadt angreifen könnten, also hat er das Kriegsrecht durchgesetzt. Und das alles begann wegen zwei Negern, einem Bock namens Tamango und einer Hirschkuh namens Isauri...";
			link.l1 = "Klingt ziemlich dramatisch. Erzähl mir die ganze Geschichte, wer sind diese Schwarzen?";
			link.l1.go = "EscapeSlaveVillemstad_T2";
		break;
		
		case "EscapeSlaveVillemstad_T2":
				dialog.text = "Tamango und Izaura - Sklaven auf der Blenheim-Plantage, der ersten niedergebrannten Plantage. Diese beiden Neger liebten sich. Aber der Sohn des Pflanzers, Leonsio, kam aus Europa und verliebte sich in die Hirschkuh. Er wollte Izaura zu seiner persönlichen Konkubine machen. Der schwarze Hirsch Tamango mochte die Idee nicht und Izaura auch nicht, sie liebte wirklich den schwarzen Teufel\nDieser Tamango war eine Art Häuptling oder so in Afrika... Ein riesiger Hirsch - schwärzer als die Sünde und tödlich mit einer Axt, die anderen Neger fürchteten und respektierten ihn. Also führte dieser Neger die anderen Sklaven zu einem Aufstand. Sie griffen die Wachen in der Nacht an, töteten jeden Weißen außerhalb des großen Hauses, auch die Mulatten\nDann öffnete Izaura die Türen der Plantage und die wilden Affen mordeten jeden im Inneren. Blenburg wurde niedergebrannt. Dann flohen die Sklaven in die Dschungel und verschwanden...";
			link.l1 = "Nun, wie ist das für eine Geschichte, klingt wie die Handlung für einen Roman! Ein ordentlicher Sklavenaufstand, genau wie im alten Rom. Wie hast du das übrigens herausgefunden?";
			link.l1.go = "EscapeSlaveVillemstad_T3";
		break;
		
		case "EscapeSlaveVillemstad_T3":
			dialog.text = "Gerüchte, mein Herr, die Erde ist voll von ihnen. Rum löst die Zungen, Sie müssen nur zuhören...";
			link.l1 = "Und wie ist das alles ausgegangen? Haben sie diese Neger gefunden?";
			link.l1.go = "EscapeSlaveVillemstad_T4";
		break;
		
		case "EscapeSlaveVillemstad_T4":
				dialog.text = "Ha, keine Chance! Bis die Verstärkungen endlich eintrafen, hat niemand einen Schritt in den Dschungel gewagt. Dann kam ein Kriegsschiff der Kompanie mit einer Einheit Soldaten und sie durchsuchten die Insel. Sie fanden weder schwarze Haut noch lockiges Haar von einem einzigen entlaufenen Neger.";
			link.l1 = "Nun, wie wäre es damit! Tausend Neger sind einfach in Luft aufgelöst?";
			link.l1.go = "EscapeSlaveVillemstad_T5";
		break;
		
		case "EscapeSlaveVillemstad_T5":
			dialog.text = "Eigentlich ins Wasser.";
			link.l1 = "Wovon redest du, "+npchar.name+"? Sie wissen genauso gut wie ich, dass Negros nicht schwimmen können.";
			link.l1.go = "EscapeSlaveVillemstad_T6";
		break;
		
		case "EscapeSlaveVillemstad_T6":
			dialog.text = "He-he... oh nein, diese Schwarzen sind nicht so schnell Haifutter. Die Sache ist die, am nächsten Abend nach der Meuterei verschwand eine Bark von den Docks. Du kannst mich schwarz anmalen und ich spiele das Banjo und tanze für dich, wenn das nicht auf das Konto von diesem Burschen Tamango und seinen Negern geht! Deswegen sind sie nicht mehr auf der Insel.";
			link.l1 = "Ha, jetzt habe ich alles gehört, "+npchar.name+". Ihr erwartet von mir, dass ich glaube, dass eine Gruppe halbwilder Neger Segel handhaben und navigieren kann? Ich würde eher erwarten, dass ein Schiff voller Affen aus Guinea hereinstürzt.";
			link.l1.go = "EscapeSlaveVillemstad_T7";
		break;
		
		case "EscapeSlaveVillemstad_T7":
			dialog.text = "Ich habe es auch nicht geglaubt, Herr, aber der Beweis liegt im verschwundenen Schiff. Vielleicht hat einer dieser Neger als Steward auf einem Schiff gedient und einige Segeltechniken erlernt. Vielleicht haben sie schwarze Magie benutzt, wer weiß! Besuchen Sie mich wieder, "+pchar.name+", Ich werde das nächste Mal mehr Geschichten für dich haben.";
			link.l1 = "Danke! Nun, es ist Zeit für mich zu gehen.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "22_2");
			pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_P";
		break;						

		case "Portugal":
			dialog.text = "Ja, das ist korrekt. Sie haben diesen Piraten gefangen. Und kannst du glauben, wie? Er wurde allein auf einem Beiboot mitten auf dem Meer aufgegriffen. Er hat keinen Mucks gemacht, bevor er in den Laderaum für die Ratten geschickt wurde. Es ist wirklich amüsant, weißt du, so ein gefährlicher Pirat wurde wie ein solcher Tölpel gefangen!";
			link.l1 = "Und warum war er ganz allein auf dem Meer?";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Er hat sich wahrscheinlich dazu entschieden, sich von seinen Schergen zu trennen, ohne Zweifel... Sie konnten die Beute nicht fair teilen. Jetzt ist er in den Händen der Kompanie selbst und diese Kerle verstehen keinen Spaß. Sie sagen, er habe sich eines der Boote der Kompanie bemächtigt, mit etwas Wertvollem darauf. Anscheinend hängt er nur deshalb noch nicht am Galgen, weil sie noch einige Informationen aus ihm herauspressen wollen.";
			link.l1 = "Also, wann wird seine Hinrichtung sein, weißt du das?";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Niemand weiß es. Ich denke, sobald die Kompanie herausfindet, was sie will, werden sie ihm eine Hanfkrawatte um den Hals legen. Der Portugiese sitzt gerade im Gefängnis unter zuverlässiger Bewachung\nKürzlich haben sie auch seinen Bootsmann hierher gebracht. Seine Geschichte war noch überraschender, er hat sich den Holländern in Philipsburg ergeben. Also, sie haben ihn in eine Zelle direkt neben seinem Ex-Kapitän gesteckt, sie sind jetzt also Nachbarn, he-he...";
			link.l1 = "Wunder geschehen doch! Na gut, ich werde nach den Neuigkeiten Ausschau halten. Ich will diese Hängung nicht verpassen. Tschüss, "+npchar.name+"!";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			DialogExit();
			pchar.questTemp.Portugal = "PortugalInPrison";
			AddQuestRecord("Portugal", "32");
		break;
		
		//--> Тайна Бетси Прайс
		case "TBP_Tavern_1":
			dialog.text = "Oh, wenn Ihr sie nur gesehen hättet, Kapitän! Betsy... solche Anmut, solch ein Lächeln! Männer kamen in Scharen hierher, nur um sie anzusehen. Und wie viel Silber sie in meinem Wirtshaus ließen... Aber vor drei Tagen erschien sie nicht zur Arbeit. Natürlich schickte ich Leute zu ihrem Haus, aber sie war nicht da. Das Haus war in Unordnung, ihre persönlichen Sachen waren verschwunden\nIch weiß nicht mehr, was ich denken soll. Die Wachen haben es wie üblich einfach abgetan. Sie sagen, sie hätten Wichtigeres zu tun, als nach vermissten Mädchen zu suchen, dass sie wahrscheinlich ausgelassen feiert und bald zurückkehren wird. Kapitän, vielleicht könntet Ihr sie finden? Wenn Ihr sie hierher bringt, zahle ich Euch hundert Dublonen. Ich kann sie einfach nicht verlieren, versteht Ihr? Sie ist ein wahrer Schatz! Ich muss sie zurückbekommen, koste es, was es wolle!";
			link.l1 = "Mal sehen, was sich tun lässt. Hat sie sich vor dem Verschwinden merkwürdig verhalten oder schlechte Nachrichten erhalten?";
			link.l1.go = "TBP_Tavern_2";
			link.l2 = "Eine verschwundene Kellnerin suchen? Ich habe Wichtigeres zu tun. Kümmere dich selbst darum.";
			link.l2.go = "TBP_Tavern_End";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern_End":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.TBP_Tavern");
			CloseQuestHeader("TBP");
		break;

		case "TBP_Tavern_2":
			dialog.text = "Am Tag ihres Verschwindens wirkte sie zufrieden, sogar glücklich! Kein Zeichen von Unruhe, kein Wort darüber, dass sie verschwinden wollte. Sie ging einfach – und war weg!";
			link.l1 = "Interessant... Wo kann ich ihr Haus finden?";
			link.l1.go = "TBP_Tavern_3";
		break;

		case "TBP_Tavern_3":
			dialog.text = "Sie lebte weiter die Straße hinauf, in einer Hütte direkt hinter dem Haus gegenüber der Villa mit dem blauen Balkon. Es ist nicht weit von hier.";
			link.l1 = "Ich werde keine Zeit verlieren. Wenn ich etwas herausfinde, sage ich dir Bescheid.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_Poorman");
		break;

		case "TBP_Tavern2_11":
			dialog.text = "Verdächtig? Um sie herum schwirrten Horden von Verehrern, jeder auf seine Weise verdächtig! Eine wahre Kokette, sie wusste, wie man Aufmerksamkeit erregt.";
			link.l1 = "Das habe ich schon bemerkt"+GetSexPhrase("","e")+". Hat sich jemand besonders hervorgetan?";
			link.l1.go = "TBP_Tavern2_12";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern2_12":
			dialog.text = "Hmm... Ja, da war einer. An dem Abend schenkte er ihr ein Kamee-Amulett. Er saß hier, ließ sie keinen Moment aus den Augen und schlich den ganzen Abend um sie herum.";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon"))
			{
				link.l1 = "Ist das zufällig dieses Amulett? (Zeige das Kamee, das vom Bettler gekauft wurde)";
				link.l1.go = "TBP_Tavern2_13";
			}
			else
			{
				link.l1 = "Ein Kamee-Amulett, sagst du...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("TBP_SearchHouseWithFonar");
			}
		break;

		case "TBP_Tavern2_13":
			dialog.text = "Das ist es! Ganz sicher! Kapitän, habt Ihr schon etwas herausgefunden?";
			link.l1 = "Die Details später, "+npchar.name+", jetzt dürfen wir keine Zeit verlieren.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_SearchHouseWithFonar");
			RemoveItems(pchar, "jewelry24", 1); 
			notification("Übergeben: Kamee-Anhänger", "None");
		break;

		case "TBP_Tavern3_21":
			dialog.text = "Das ist großartig, Kapitän! Ich hatte schon gedacht, ich würde sie nie wiedersehen. Was ist also passiert? Wollte sie wirklich einfach abhauen?";
			link.l1 = "Sagen wir, sie musste sich mit einigen Problemen aus der Vergangenheit auseinandersetzen. Aber es sieht so aus, als sei das nun überstanden, und sie kann bald zur Arbeit zurückkehren.";
			link.l1.go = "TBP_Tavern3_22_leadership";
			link.l2 = "Sagen wir, sie brauchte eine kleine Pause von deinem langweiligen Gesicht. Haha! Nimm’s nicht übel, ich scherze nur. Jede Dame braucht ihre kleinen Geheimnisse...";
			link.l2.go = "TBP_Tavern3_22_fortune";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern3_22_leadership":
			dialog.text = "Nun, die Hauptsache ist, dass sie zur Arbeit zurückkehren wird. Ihr habt Eure Belohnung verdient, Kapitän. Hier, nehmt – hundert Dublonen, wie vereinbart. Und außerdem, nehmt diese Karte. Einer der Besucher hat sie hier gelassen und ist nie zurückgekehrt. Allen Anzeichen nach führt sie zu einem Schatz.";
			link.l1 = "Nun, das werde ich überprüfen. Danke.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddItems(pchar, "gold_dublon", 100);
			GiveItem2Character(PChar, "map_full");
		break;
		
		case "TBP_Tavern3_22_fortune":
			dialog.text = "Nun, die Hauptsache ist, dass sie zur Arbeit zurückkehren wird. Ihr habt Eure Belohnung verdient, Kapitän. Hier, nehmt – hundert Dublonen, wie vereinbart. Und außerdem, nehmt diese Karte. Einer der Besucher hat sie hier gelassen und ist nie zurückgekehrt. Allen Anzeichen nach führt sie zu einem Schatz.";
			link.l1 = "Nun, das werde ich überprüfen. Danke.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddItems(pchar, "gold_dublon", 100);
			GiveItem2Character(PChar, "map_full");
		break;
		//<-- Тайна Бетси Прайс
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
