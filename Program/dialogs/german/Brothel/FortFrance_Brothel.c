// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;   
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Was für Fragen, "+GetSexPhrase("junger Mann","junge Dame")+"?","Was brauchen Sie, "+GetSexPhrase("schöner","hübsche")+"? Fragen Sie nur."),"Wieder Fragen?","Tee-hee, wenn es Ihnen recht ist - fragen Sie...",""+GetSexPhrase("Hm, warum suchen Sie sich nicht eine Schönheit aus? Ich fange an, Sie zu verdächtigen, dass Sie etwas im Schilde führen...","Hm, warum wählen Sie nicht eine Schönheit aus? Jungs haben wir hier leider nicht, hihi...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe es mir anders überlegt, entschuldigen Sie mich.","Eigentlich, ach vergessen Sie es..."),"Ich... Entschuldigung, ich habe im Moment keine Fragen.","Sie haben recht, es ist bereits das dritte Mal. Verzeihen Sie mir.","Vielleicht nächstes Mal, Madame.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start")
			{
				DelLandQuestMark(npchar);
				link.l1 = "Hören Sie, Aurora, ich brauche ein Mädchen für die Nacht. Und ich möchte sie mit nach Hause nehmen. Können Sie das arrangieren?";
                link.l1.go = "Gigolo";
			}	
			//<-- Бремя гасконца */
		break;
		
		//--> Бремя гасконца
		case "Gigolo":
			dialog.text = "Natürlich, Liebling. Hast du bereits eine passende Schönheit gefunden oder soll ich eine auswählen?";
			link.l1 = "Tatsächlich habe ich das. Ich habe ein Auge auf ein Mädchen namens Lucille geworfen.";
			link.l1.go = "Gigolo_1";
		break;
		
		case "Gigolo_1":
			dialog.text = "Meinen Sie Lucille Montaigne?";
			link.l1 = "Ehrlich gesagt, ich habe nicht nach ihrem Nachnamen gefragt. Alles was ich weiß, ist, dass sie ein junges, schönes und blondes Mädchen namens Lucille ist.";
			link.l1.go = "Gigolo_2";
		break;
		
		case "Gigolo_2":
			dialog.text = "Ja, das beschreibt sie sehr gut. Also gut. Aber sagen Sie mir, warum sie? Sind die anderen Mädchen nicht nach Ihrem Geschmack?";
			link.l1 = "Nun, sehen Sie... sie hat gerade erst angefangen hier zu arbeiten, also glaube ich, dass sie noch nicht erfahren genug im 'Gewerbe' ist, um meiner Börse zu stark zur Last zu fallen.";
			link.l1.go = "Gigolo_2_1";
			link.l2 = "Sehen Sie, ich verehre Blondinen mit heller Haut. Lucille ist in dieser Hinsicht perfekt.";
			link.l2.go = "Gigolo_2_2";
		break;
		
		case "Gigolo_2_1":
			if (int(pchar.questTemp.Sharlie.Gigolo.Rand1) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 5000;
				dialog.text = "Nun, Monsieur, das ist nicht wahr! Sie ist jung, hübsch und erfahren, alle meine Kunden bewundern sie geradezu. Sie wird Sie viel kosten. Fünftausend Pesos für eine Nacht mit ihr, und nicht einen einzigen Peso weniger.";
				if (int(pchar.money) >= 5000)
				{
					link.l1 = "Teuer, aber gut. Hier haben Sie Ihr Geld.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Das ist aber teuer! So viel habe ich nicht dabei. Wir sprechen später nochmal.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 2500;
				dialog.text = "Seufz, Sie haben recht, Monsieur, sie ist hübsch und jung, aber es fehlt ihr an Erfahrung. Meine Kunden bemerken das normalerweise nicht, deshalb habe ich gefragt. Aber wenn Sie wirklich bescheidene Mädchen mögen, kann ich Ihnen sagen, dass sie eine gute Wahl ist. Sie wird Sie zweitausendfünfhundert Pesos kosten.";
				if (int(pchar.money) >= 2500)
				{
					link.l1 = "Ach, sie wird es gut machen. Hier haben Sie Ihr Geld.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Das ist aber teuer! Ich habe nicht so viel dabei. Ich werde später nochmal mit Ihnen reden.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_2_2":
			if (int(pchar.questTemp.Sharlie.Gigolo.Rand2) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 4500;
				dialog.text = "Sie wären nicht der Erste, Schöner. Manchmal stehen meine Kunden Schlange für ihre Aufmerksamkeit, da sie sich sehr von den dunkelhäutigen Töchtern unserer Inseln unterscheidet. Sie wird Sie viertausendfünfhundert Pesos kosten.";
				if (int(pchar.money) >= 4500)
				{
					link.l1 = "Teuer, aber gut. Hier haben Sie Ihr Geld.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Das ist aber teuer! Ich habe nicht so viel dabei. Ich werde später nochmal mit Ihnen reden.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 3000;
				dialog.text = "Wirklich, Monsieur? Schon Heimweh? Meine Kreolen und insbesondere meine Mulatten sind leidenschaftlicher als diese entspannte Pariser Gassenkatze. Aber ach, es ist Ihre Wahl. Sie wird Sie dreitausend Pesos kosten.";
				if (int(pchar.money) >= 3000)
				{
					link.l1 = "Teuer, aber gut. Hier haben Sie Ihr Geld.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Das ist aber teuer! So viel habe ich nicht dabei. Ich werde später nochmal mit Ihnen reden.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_3":
			AddMoneyToCharacter(pchar, -int(pchar.questTemp.Sharlie.Gigolo.Money));
			dialog.text = "Wie Sie wünschen, Liebster. Lucille wird Sie um elf Uhr am Abend sehnsüchtig erwarten. Sie darf nicht später als um sieben Uhr morgens zurückkehren. Wenn Sie nicht vor Mitternacht ankommen, wird sie sich einem anderen Kunden widmen, und dann müssen Sie bis zum nächsten Abend warten, um sie zu nehmen. \nUnd denken Sie nicht daran... ihr in irgendeiner Weise weh zu tun, es sei denn, Sie wollen es bereuen. Eine faire Warnung, Liebster.";
			link.l1 = "Machen Sie sich keine Sorgen, ich werde sie wie eine Geliebte behandeln, nicht wie ein Unmensch. Ich werde sie um elf Uhr abholen. Was soll ich bis dahin tun?";
			link.l1.go = "Gigolo_4a";
		break;
		
		case "Gigolo_4a":
			dialog.text = "Nun, ich weiß es nicht, Liebling. Schauen Sie in der Taverne vorbei, plaudern Sie mit dem Wirt...";
			link.l1 = "Nicht die schlechteste Idee. Genau das werde ich tun. Haben Sie einen schönen Tag!";
			link.l1.go = "Gigolo_4";
		break;
		
		case "Gigolo_4":
			//DeleteAttribute(pchar, "GenQuest.CannotWait");
			DialogExit();
			AddQuestRecord("SharlieC", "2");
			pchar.questTemp.Sharlie.Gigolo = "girl";
			Sharlie_CreateGigoloGirl();
			QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
			QuestPointerDelLoc("fortfrance_brothel", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			SetCurrentTime(17, 30);
			//NewGameTip("Доступна функция перемотки времени! Она доступна через опцию 'мысли вслух' в меню действий (ENTER).");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
