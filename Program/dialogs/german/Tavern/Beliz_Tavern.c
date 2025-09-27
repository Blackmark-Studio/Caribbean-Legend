// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Alle Gerüchte von "+GetCityName(npchar.city)+" zu Ihren Diensten. Was möchten Sie herausfinden?","Wir haben gerade darüber gesprochen. Du musst es vergessen haben...","Das ist das dritte Mal heute, dass du mich fragst...","Du wiederholst alles wie ein Papagei...","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Weißt du, "+NPChar.name+", vielleicht nächstes Mal.","Stimmt, ich habe aus irgendeinem Grund vergessen...","Ja, es ist wirklich das dritte Mal...","Jawohl...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Hör mal, ist hier in dieser Stadt ein Alchemist angekommen, ein Arzt? Er ist Italiener, ungefähr dreißig Jahre alt, sein Name ist Gino Gvineili?";
				link.l1.go = "guardoftruth";
			}
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.Caleuche"))
			{
				link.l1 = "Hör zu, ich brauche einen Jäger namens Fergus Hooper. Mir wurde gesagt, dass er hier lebt. Wo kann ich ihn finden?";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
			//--> Дикая Роза
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz"))
			{
				link.l1 = "Vor etwa anderthalb Monaten kam ein gewisser Jérôme Sauvergne in eure Stadt. Können Sie sich an ihn erinnern?";
				link.l1.go = "WildRose_Tavern_1";
			}
			//<-- Дикая Роза 
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Nein, haben wir nicht. Wir haben Kräuterkundige und Ärzte, aber keiner von ihnen trägt diesen Namen.","Das ist das erste Mal, dass ich einen so seltsamen Namen höre. Nein, wir hatten nie Besuch von dem Mann, von dem du sprichst.","Wir haben überhaupt keine Art von Alchemisten. Wir haben Ärzte, aber keinen mit einem solchen Namen.");
			link.l1 = "Ich verstehe. Das ist schade. Ich werde weiter suchen!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
		
		// Калеуче
		case "caleuche":
			dialog.text = "Fergus? Er besucht oft mein Platz. Aber er ist seit gestern im Dschungel. Mach dir keine Sorgen, er wird in einer Woche zurück sein, Rum trinken und mit seinen Seefahrten prahlen. Obwohl, ich gebe zu, er ist ein verdammter guter Jäger. Ich kenne niemanden, der so gut Schlangen fangen kann wie er.";
			link.l1 = "Schlangen? Hm. Wann sollte ich hierher zurückkommen, um ihn zu finden?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Drei Tage mindestens. Sei dir bewusst, dass er immer erst nach sechs Uhr abends hierher kommt und nicht später als zehn geht.";
			link.l1 = "Wie sieht er aus? Habe ihn noch nie gesehen.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Bärtig, mittleren Alters, trägt braunen Mantel, Hut und lange Stiefel.";
			link.l1 = "Danke! Du hast mir sehr geholfen, Kumpel. Wir sehen uns!";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "8");
			int iTerms = sti(pchar.questTemp.Caleuche.Belizterms);
			SetFunctionTimerCondition("Caleuche_FergusCome", 0, 0, iTerms, false);
			npchar.quest.Caleuche = "true";
		break;
		
		//--> Дикая Роза
		case "WildRose_Tavern_1":
			dialog.text = "Ähm, ja… ich glaube schon. Ja, ich erinnere mich an diesen Herrn. Nicht gerade wie aus dem Ei gepellt, aber mit Geld.";
			link.l1 = "Er wurde in einer Schlägerei in eurer Taverne verletzt.";
			link.l1.go = "WildRose_Tavern_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tavern_2":
			dialog.text = "Na und? Hier gibt’s alle paar Tage Prügeleien. Die Matrosen saufen sich voll, ein Wort gibt das andere – und schon fliegen die Fäuste. Sie sehen mir nicht wie ein Neuling aus – wundert Sie das wirklich?";
			link.l1 = "Ganz und gar nicht. Die Sache ist die: dieser Mann ist ein alter Bekannter von mir. Wir hatten hier eine Verabredung, aber ich habe mich etwas verspätet. Können Sie mir sagen, wo ich ihn finde?";
			link.l1.go = "WildRose_Tavern_3";
		break;

		case "WildRose_Tavern_3":
			dialog.text = "Warum auch nicht, mein Herr? Wie ich sagte – Geld hatte er genug, also hat er sich ein kleines Haus beim Hafenamt gemietet. Auffällig, mit einem roten Dach. Sitzt meist drin und kuriert sein Bein aus. Ab und zu schaut er hier vorbei, um ein Gläschen zu trinken. Aber nicht jeden Tag – manchmal kommt er, manchmal nicht.";
			link.l1 = "Dann statte ich ihm wohl besser zu Hause einen Besuch ab. Danke für die Auskunft. Einen schönen Tag noch.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_3_tavern");
		break;
		//<-- Дикая Роза

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
