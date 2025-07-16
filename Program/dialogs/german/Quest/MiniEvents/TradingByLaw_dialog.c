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

		case "Kristian":
			dialog.text = "Willkommen in meinem Haus! Mein Name ist Christian. Christian Delouche. Wie kann ich Ihnen helfen?";
			link.l1 = "Ich bin Kapitän "+GetFullName(pchar)+". Ich möchte eine Lieferung Alkohol kaufen. Sie wissen, wovon ich spreche?";
			link.l1.go = "Kristian_2";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_2":
			dialog.text = "Was??? Wer hat Ihnen das gesagt? Das muss ein Missverständnis sein, ich versichere Ihnen, ich handle nicht mit Alkohol!";
			link.l1 = "Aha. Ich sehe, ich bin hier richtig.";
			link.l1.go = "Kristian_3";
		break;

		case "Kristian_3":
			dialog.text = "Oh-oh-oh, nein-nein, was denken Sie! Kein Alkoholhandel, wirklich nicht, ich... ich bin einfach, äh... nun... Ja, ich habe Waren, aber das ist... alles legal! Ich kaufe nur für Privatpersonen, äh... für Feiern, für kleine Treffen!";
			link.l1 = "Warum sind Sie so nervös? Ich bin nicht gekommen, um Sie zu verhaften, sondern um Ihrem Geschäft zum Erfolg zu verhelfen. Und hoffentlich füllt sich dabei auch meine Tasche mit ein paar Goldstücken.";
			link.l1.go = "Kristian_4";
		break;

		case "Kristian_4":
			dialog.text = "Ich... ich bin überhaupt nicht nervös! Warum sollte ich nervös sein? Ich bin ein ehrlicher Bürger, mein Haus ist direkt neben der Residenz des Gouverneurs. Ich verstoße gegen nichts, ich versichere Ihnen!";
			link.l1 = "Also handeln Sie nicht mit Alkohol? Schade, wirklich schade. Sehen Sie, ich habe ein sehr lukratives Angebot. Ich bin sicher, ein kleiner Schwarzmarkthändler wie Sie hat von so vielen Dublonen noch nie geträumt. Nun, wenn Sie nicht derjenige sind, den ich suche, dann gehe ich wohl besser. Ja?";
			link.l1.go = "Kristian_5";
		break;

		case "Kristian_5":
			dialog.text = "Äh... warten Sie... "+GetAddress_Form(NPChar)+"... entschuldigen Sie, ich war einfach so aufgeregt, dass ich vergessen habe, wie Sie heißen.";
			link.l1 = "Kapitän "+GetFullName(pchar)+".";
			link.l1.go = "Kristian_6";
		break;

		case "Kristian_6":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" "+pchar.lastname+", die Sache ist die, äh... nun... ich weiß, wo man denjenigen finden kann, den Sie suchen. Ich kann ihm... Ihr Angebot übermitteln.";
			link.l1 = "Übermitteln? Glauben Sie wirklich, dass man in solchen Angelegenheiten etwas durch Dritte übermitteln sollte?";
			link.l1.go = "Kristian_7";
		break;
		
		case "Kristian_7":
			dialog.text = "Sie haben recht. Aber... ach... sei's drum... ja, ich bin derjenige, den Sie suchen.";
			link.l1 = "Na also, so ist's besser, Christian. Sehen Sie, die Taverne hat derzeit große Probleme mit der Versorgung mit Alkohol, und ich hoffe, wir können gemeinsam daraus Kapital schlagen.";
			link.l1.go = "Kristian_8";
		break;

		case "Kristian_8":
			dialog.text = "Kapitän, mir sind die Schwierigkeiten des Wirts wohlbekannt, denn die Leute strömten zu mir, und ich begann bereits, mich beim Handel zu fürchten – das zieht zu viel Aufmerksamkeit auf sich. Da dachte ich, dass Sie... nun, Sie verstehen schon...";
			link.l1 = "Warum haben Sie ihm Ihre Dienste nicht angeboten?";
			link.l1.go = "Kristian_9";
		break;

		case "Kristian_9":
			dialog.text = "Er... er würde niemals mit mir zusammenarbeiten. Dieser Mann verachtet kleine Geschäftsleute wie mich.";
			link.l1 = "Ja, davon habe ich gehört. Mit Ihnen vielleicht nicht. Aber mit mir – das wird er.";
			link.l1.go = "Kristian_10";
		break;

		case "Kristian_10":
			dialog.text = "Sie wollen Vermittler werden? Nun gut, ich habe nichts dagegen... Wir haben kürzlich eine Lieferung hereingebracht – ein wahrer Rekord! Sie hätte mir wohl für ein halbes Jahr gereicht. Aber Gott ist mein Zeuge – nur ein Wunder hat uns vor der Entdeckung bewahrt.\nIch verstehe bis heute nicht, wie wir entkommen konnten. So etwas ein zweites Mal zu versuchen, wäre Selbstmord.";
			link.l1 = "Dann sollten Sie aus dem Schatten treten. Zumindest teilweise.";
			link.l1.go = "Kristian_11";
		break;

		case "Kristian_11":
			dialog.text = "Aus dem Schatten treten? Aber... dafür braucht man Kontakte! Und Geld! Und wozu das Ganze? Werden Sie, ein Schiffskapitän, sich in einer Stadt niederlassen und für die örtliche Taverne liefern?";
			link.l1 = "Was die Kontakte angeht – ich denke, da kann ich helfen. Was das Geld betrifft... ich glaube nicht, dass viel nötig sein wird. Und das Letzte brauchen Sie nicht zu tun. Sie werden in meinem Namen handeln. Ich helfe Ihnen – und Sie helfen mir. Und zwar regelmäßig. Sie bekommen einen stabilen Absatzmarkt, und ich einen zuverlässigen Lieferanten. Was halten Sie davon?";
			link.l1.go = "Kristian_12";
		break;

		case "Kristian_12":
			dialog.text = "Ich dachte schon, das sei eine Falle. Aber ehrlich gesagt, Ihr Vorschlag klingt... äußerst verlockend. Stabilität, Zuverlässigkeit... Wer hätte gedacht, dass ich eine solche Chance bekomme. "+GetSexPhrase("Monsieur","Mademoiselle")+", ich bin dabei! Wie viel möchten Sie kaufen?";
			link.l1 = "Zuerst legalisieren wir Ihr Geschäft, dann besprechen wir die Einzelheiten. Wie viel Rum und Wein haben Sie gerade jetzt auf Lager?";
			link.l1.go = "Kristian_13";
		break;

		case "Kristian_13":
			dialog.text = "Gerade jetzt? Äh... Gehen wir in den Keller, dort kann ich Ihnen die genaue Menge nennen.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_GoToPogreb");	// спускаемся в погреб
		break;
		
		// погреб
		case "Kristian_15":
			dialog.text = "Na, na... Was haben wir denn hier? Aha\nDerzeit habe ich genau hundert Flaschen Rum und hundert Flaschen Wein auf Lager.";
			link.l1 = "Nun, ich denke, das reicht fürs Erste. Wenn sich das Einfuhrproblem lösen lässt – könnten Sie solche Lieferungen monatlich und zuverlässig bereitstellen?";
			link.l1.go = "Kristian_16";
		break;

		case "Kristian_16":
			dialog.text = "Natürlich, Kapitän! Und sogar das Dreifache, nein – das Vierfache wäre möglich! Es wird keine Ausfälle geben. Ich werde stets genug auf Lager halten, um etwaige Engpässe problemlos auszugleichen.";
			link.l1 = "Wie viel möchten Sie für diese Lieferung erhalten?";
			link.l1.go = "Kristian_17";
		break;

		case "Kristian_17":
			dialog.text = "Ich wäre zufrieden mit: zehn Dublonen für je zehn Flaschen Wein und drei Dublonen für je zehn Flaschen Rum. Das macht insgesamt einhundertdreißig Dublonen für die gesamte Lieferung.";
			link.l1 = "Einverstanden. Ich werde mit dem Wirt sprechen und bald zurückkehren.";
			link.l1.go = "Kristian_18";
		break;
		
		case "Kristian_18":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_18_1";
			pchar.questTemp.TPZ_Tavern_2 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			AddQuestRecord("TPZ", "4");
		break;
		
		case "Kristian_18_1":
			dialog.text = "Kapitän, gibt es Neuigkeiten? Was hat der Wirt gesagt?";
			link.l1 = "Ich bin gerade auf dem Weg zu ihm.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_18_1";
		break;

		case "Kristian_21":
			dialog.text = "Wie ist es gelaufen, Kapitän? Konnten Sie sich mit dem Wirt einigen?";
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				link.l1 = "Ich habe ganze Arbeit geleistet, Christian. Er wird dieses und alle künftigen Lieferungen für zweihundertvierzig Dublonen abnehmen. Für die erste Lieferung zahle ich Ihnen die vereinbarten einhundertdreißig Dublonen. Den Rest behalte ich als Lohn für meine Mühen. Künftige Gewinne gehören ganz Ihnen.";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				link.l1 = "Ich habe gute Arbeit geleistet, Christian. Er wird diese und alle weiteren Lieferungen für zweihundert Dublonen abnehmen. Für die erste Lieferung zahle ich Ihnen einhundertdreißig Dublonen, wie besprochen. Den Rest behalte ich als Belohnung für meinen Einsatz. Der zukünftige Gewinn gehört ganz Ihnen.";
			}
			link.l1.go = "Kristian_22";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_22":
			dialog.text = "Das sind großartige Neuigkeiten, Kapitän! Ich hätte nie von einem solchen Geschäft geträumt – danke Ihnen! Aber... haben Sie sich nicht vielleicht etwas zu sehr beeilt? Der Gouverneur... ich meine...";
			link.l1 = "Mit dem Gouverneur ist alles geregelt. Ab jetzt zahlen Sie jeden Monat eine Steuer von hundert Dublonen und legen ordnungsgemäße Handelsberichte vor.";
			link.l1.go = "Kristian_23";
		break;

		case "Kristian_23":
			dialog.text = "Unglaublich! Wie haben Sie das geschafft, Kapitän? Der Gouverneur ist doch ein strenger Mann, und zudem ein erklärter Feind des Schwarzhandels...";
			link.l1 = "Gerade deshalb, Christian – er ist ein Feind des Schwarzhandels, aber nicht des ehrlichen. Er hat mir aufmerksam zugehört und die Bedingungen für den Alkoholhandel auf der Insel dargelegt. Sie arbeiten künftig in meinem Namen, und ich hafte für all Ihre Vergehen genauso wie Sie selbst. Also enttäuschen Sie mich nicht – ich finde Sie, selbst wenn Sie sich im Jenseits verkriechen.";
			link.l1.go = "Kristian_24";
		break;

		case "Kristian_24":
			dialog.text = "Ich schwöre, Kapitän, Sie werden es nicht bereuen!";
			link.l1 = "Jetzt müssen wir nur noch das Geschäft mit dem Wirt abschließen, und dann besprechen wir die Details unserer Zusammenarbeit.";
			link.l1.go = "Kristian_25";
		break;
		
		case "Kristian_25":
			dialog.text = "Natürlich, Kapitän. Sind Sie bereit, die Lieferung sofort mitzunehmen? Der Preis beträgt einhundertdreißig Dublonen.";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "Ja, hier sind Ihre Dublonen.";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "Im Moment habe ich nicht genug Geld. Warten Sie hier, ich werde das Geld besorgen und zurückkommen.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;

		case "Kristian_25_1":
			dialog.text = "Kapitän! Sie sind zurück, um die Ware abzuholen? Das kostet einhundertdreißig Dublonen.";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "Ganz genau! Hier sind Ihre Dublonen.";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "Leider habe ich derzeit nicht genug Geld. Ich komme später wieder.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;

		case "Kristian_26":
			dialog.text = "Vielen Dank! Nehmen Sie es mit – einhundert Flaschen Wein und einhundert Flaschen Rum, wie vereinbart.";
			link.l1 = "Meine Matrosen werden die Ware abholen. Ich spreche inzwischen mit dem Wirt.";
			link.l1.go = "Kristian_27";
			RemoveDublonsFromPCharTotal(130);
		break;
		
		case "Kristian_27":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.TPZ_Tavern_4 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
		break;
		
		case "Kristian_31":
			dialog.text = ""+pchar.name+"! Sie sind schon zurück! Nun, wie ist es gelaufen?";
			link.l1 = "Alles in Ordnung, Christian. Der Wirt wird solche Lieferungen zweimal im Monat abnehmen. Sorgen Sie für einen stabilen Nachschub – und Sie werden Armut bald vergessen.";
			link.l1.go = "Kristian_32";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_32":
			dialog.text = "Kapitän... Sie... als hätte das Schicksal selbst Sie zu mir geführt! Es ist wie ein Wunder, ich kann es kaum glauben! Womit habe ich so viel Güte verdient? Ich weiß gar nicht, wie ich Ihnen danken soll!";
			link.l1 = "Ich weiß es dafür, Christian. Jeden Monat soll ein Teil der Ware ausschließlich für mich reserviert sein. Ich kaufe sie zum von Ihnen genannten Preis – zehn Dublonen für zehn Flaschen Wein und drei Dublonen für zehn Flaschen Rum.";
			link.l1.go = "Kristian_33";
		break;

		case "Kristian_33":
			dialog.text = "Ich wäre glücklich, "+pchar.name+", die Ware für Sie bereitzuhalten! Seien Sie sicher, ich werde Sie nicht enttäuschen! Wie viel möchten Sie jeweils abnehmen? Fünfzig? Hundert Flaschen? Sagen Sie einfach Bescheid!";
			link.l1 = "So viel brauche ich derzeit nicht. Zwanzig Flaschen reichen mir vorerst. Wenn ich mehr benötige, lasse ich es Sie wissen.";
			link.l1.go = "Kristian_34";
		break;

		case "Kristian_34":
			dialog.text = "Natürlich, natürlich! Also, zwanzig Flaschen Wein und zwanzig Rum für 26 Dublonen. Am fünfzehnten jeden Monats wird die Ware für Sie bereitstehen. Ich freue mich, Sie jederzeit begrüßen zu dürfen – selbst wenn Sie nur auf einen Plausch vorbeikommen!";
			link.l1 = "Ausgezeichnet! Und noch etwas, Christian. Ich habe mit meinem Namen für Sie gebürgt. Enttäuschen Sie mich nicht.";
			link.l1.go = "Kristian_35";
		break;

		case "Kristian_35":
			dialog.text = "Ich... was sagen Sie da, Kapitän... nein, nein – ich werde Sie nicht enttäuschen! Alles wird erstklassig sein, das schwöre ich!";
			link.l1 = "Dann bis bald!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_SpawnShip");
		break;
		
		case "Pirate_1":
			dialog.text = "Mistkerl"+GetSexPhrase("","in")+"! Hat man dir nie beigebracht, dass es Ärger gibt, wenn man sich in fremde Angelegenheiten einmischt?";
			link.l1 = "Du hast mich selbst angegriffen und wagst es jetzt zu sagen, ich würde mich einmischen? Bist du völlig verrückt geworden?";
			link.l1.go = "Pirate_2";
		break;

		case "Pirate_2":
			dialog.text = "Beim Klabautermann! Du "+GetSexPhrase("elender Hund","dreckiges Weib")+" hast also wirklich keine Ahnung, worin du da hineingeraten"+GetSexPhrase(""," bist")+"? Glaubst du etwa, die Lieferungen für die Taverne seien einfach so versandet?";
			link.l1 = "Willst du damit sagen, dass du die Brennerei in Brand gesteckt hast?";
			link.l1.go = "Pirate_3";
		break;

		case "Pirate_3":
			dialog.text = "Ha-ha, endlich dämmert’s dir, Kanonenkugel noch mal! Ganz genau – ich war’s! Der Kerl hatte sich zu sehr festgesetzt. Aber wie du siehst, weiß ich immer, wie ich meine Feinde ausschalte. Und du wirst da keine Ausnahme sein, Kettenkugel mir in den Großmast!";
			link.l1 = "Wie amüsant. Na, dann wollen wir doch sehen, wie gut du wirklich bist – Möwen sollen deine Überreste finden! Ha-ha!";
			link.l1.go = "Pirate_4";
		break;
		
		case "Pirate_4":
			DialogExit();
			
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Kristian_41":
			dialog.text = "Guten Tag, "+pchar.name+"! Was führt Sie zu mir?";
			if(CheckAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom")) // Handel mit Wein und Rum
			{
				if (GetDataDay() == 15)
				{
					link.l1 = "Guten Tag, Christian. Ist meine Ware bereit?";
					link.l1.go = "Kristian_42";
				}
			}
			link.l2 = "Guten Tag, Christian. Ich wollte nur sehen, wie es Ihnen geht. Ich bin schon wieder weg.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Kristian_41";
		break;

		case "Kristian_42":
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				dialog.text = "Natürlich, Kapitän! Hatten Sie etwa Zweifel an meiner Zuverlässigkeit?";
				if (PCharDublonsTotal() >= 130)
				{
					link.l1 = "Natürlich nicht, Christian. Hier ist Ihr Geld, ich nehme den Alkohol mit.";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "Keineswegs. Aber ich habe leider meine Dublonen vergessen. Ich komme später wieder.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			else
			{
				dialog.text = "Natürlich, Kapitän! Hatten Sie etwa Zweifel an meiner Zuverlässigkeit?";
				if (PCharDublonsTotal() >= 26)
				{
					link.l1 = "Natürlich nicht, Christian. Hier ist Ihr Geld, ich nehme den Alkohol mit.";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "Keineswegs. Aber ich habe leider meine Dublonen vergessen. Ich komme später wieder.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoBlock")) // Erweiterung des Lieferumfangs
			{
				link.l4 = "Christian, ich möchte mehr kaufen. Sagen wir, hundert Flaschen Rum und Wein monatlich.";
				link.l4.go = "UpgradeVino";
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom") && sti(pchar.Money) >= 50000)
			{
				link.l4 = "Christian, ich möchte über eine Erweiterung der Liefermenge sprechen.";
				link.l4.go = "UpgradeVino_Agreed";
			}
		break;
		
		case "Kristian_43":
			dialog.text = "Ausgezeichnet. Am fünfzehnten Tag des Monats wird Ihre neue Lieferung wie immer bereitstehen. Schauen Sie vorbei.";
			link.l1 = "Ich werde auf jeden Fall vorbeischauen. Bis bald.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";

			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				RemoveDublonsFromPCharTotal(130);
				AddItems(pchar, "potionrum", 100);
				AddItems(pchar, "potionwine", 100);
			}
			else
			{
				RemoveDublonsFromPCharTotal(26);
				AddItems(pchar, "potionrum", 20);
				AddItems(pchar, "potionwine", 20);
			}

			DeleteAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom");
			SetFunctionTimerCondition("TPZ_KristianReturn", 0, 0, 1, false); // Timer
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			pchar.questTemp.TPZ_KritstianVinoAndRom = sti(pchar.questTemp.TPZ_KritstianVinoAndRom) + 1; // Kaufzähler
		break;

		case "UpgradeVino":
			dialog.text = "Kapitän, eine Ausweitung des Volumens ist natürlich erfreulich, aber auch kostspielig! Mehr Ware bedeutet mehr Arbeitskräfte, größere Lagerräume, ein geräumigeres Schiff... Ohne Investitionen kann ich diese Mengen nicht pünktlich liefern.";
			link.l1 = "Und um welche Summe geht es? Wie viel wird benötigt, um alles reibungslos umzusetzen?";
			link.l1.go = "UpgradeVino_2";
		break;

		case "UpgradeVino_2":
			dialog.text = "Fünfzigtausend Pesos. Alle weiteren Kosten übernehme ich.";
			link.l1 = "Fünfzigtausend? Hm... das ist eine stolze Summe. Gibt es keine Möglichkeit, die Kosten zu senken?";
			link.l1.go = "UpgradeVino_3";
		break;

		case "UpgradeVino_3":
			dialog.text = "Leider nicht, Kapitän. Wenn man spart, läuft alles womöglich schief... und Probleme wollen weder Sie noch ich.";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "Hier ist Ihr Geld. Enttäuschen Sie mich nicht, Christian.";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "Vielleicht ist das Ganze doch keine so gute Idee. Wir sprechen später nochmal darüber.";
			link.l2.go = "UpgradeVino_4";
		break;

		case "UpgradeVino_4":
			dialog.text = "Wie Sie wünschen, Kapitän. Wenn Sie Ihre Meinung ändern, lassen Sie es mich wissen.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			pchar.questTemp.TPZ_KritstianVinoPotom = true;
		break;

		case "UpgradeVino_Agreed":
			dialog.text = "Kapitän, das sind hervorragende Nachrichten! Sind Sie bereit, die fünfzigtausend Silberstücke sofort zu zahlen?";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "Hier ist Ihr Geld. Enttäuschen Sie mich nicht, Christian.";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "Im Moment habe ich nicht genug. Ich komme zurück, wenn ich die Summe beisammen habe.";
			link.l2.go = "UpgradeVino_4";
		break;

		case "UpgradeVino_5":
			dialog.text = "Ich verspreche Ihnen, "+pchar.name+", Sie werden es nicht bereuen! Ich beginne sofort mit den Vorbereitungen. Ab der nächsten Lieferung erhalten Sie jeweils hundert Flaschen Rum und ebenso viele exzellente Weine, für insgesamt 130 Dublonen.";
			link.l1 = "Hervorragend. Und vergessen Sie die Vorsicht nicht. Ihre Arbeit steht auch für meinen Ruf.";
			link.l1.go = "UpgradeVino_6";
			AddMoneyToCharacter(pchar, -50000);
		break;
		
		case "UpgradeVino_6":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_41";
			pchar.questTemp.TPZ_UpgradeVino = true;
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			DeleteAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom");
			AddQuestRecordInfo("Useful_Acquaintances", "4_1");
		break;
		
		
	}
}