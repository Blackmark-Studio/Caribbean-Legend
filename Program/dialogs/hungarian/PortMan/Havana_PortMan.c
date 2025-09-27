// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdések?", "Mit akarsz, " + GetAddress_Form(NPChar) + "?"), "Már próbáltál kérdezni " + GetAddress_Form(NPChar) + "...", "Ma már harmadszor beszélsz valamilyen kérdésrôl...",
                          "Nézze, ha nincs mondanivalója a kikötô ügyeirôl, akkor ne zavarjon a kérdéseivel.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam.", "Nincs mirôl beszélnem."), "Nevermind.", "Valóban, már harmadszor...", "Sajnálom, de egyelôre nem érdekelnek a kikötô ügyei.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "Jó napot kívánok. Szeretnék megismerkedni a '" + pchar.questTemp.Slavetrader.ShipName + "' nevû korvettel, amely Francois Gontier parancsnoksága alatt állt.";
                link.l1.go = "Havana_ratP_1";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Elnézést, egy Joachim Merriman nevû férfi érkezett a kikötôjébe? Egy portugál, középkorú szenior, bajusszal, császári szakállal és szúrós szemekkel?";
				link.l1.go = "caleuche";
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && !CheckAttribute(npchar, "quest.Mtraxx"))
			{
				link.l1 = "Érdekel egy 'Cantavro'. nevû hajó, melynek kapitányát - Esberdo Cabanas - keresem, magánügyben. Tudna nekem segíteni?";
				link.l1.go = "mtraxx";
			}
		break;
		
		case "Havana_ratP_1":
			dialog.text = NPCStringReactionRepeat("Igen, itt volt. De már elment. Kérdezd meg róla a kocsmárosunkat, ô bérelt egy szobát az emeleten.", "Errôl már kérdezett, és én válaszoltam.", "Mondom neked, hogy már kérdeztél errôl a Gontierrôl...", "Kérem, hogy ne zavarjon!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Köszönöm. Megteszem.", "Hm, nos ...", "Igen, tényleg megkérdeztem ...", "Pardon, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Nem tudok róla semmit mondani. Még ha meg is érkezett, nem jelentkezett sehova.";
			link.l1 = "Értem. Milyen kár... Rendben, folytatom a keresést...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
			dialog.text = "Lássuk csak... a schooner 'Cantavro' két napja vitorlát bontott egy ôrjáratra... a helyszín azonban nincs feltüntetve. Ez egy katonai hajó, így a célállomást csak a kapitánya és az erôd parancsnoka ismeri. Javaslom, hogy beszéljetek közvetlenül a parancsnokkal, ôt az erôdben találjátok meg, ha többet szeretnétek tudni. Sajnos, ez minden, amit tehetek önért.";
			link.l1 = "Értem. Nos, köszönöm az idejét...";
			link.l1.go = "exit";
			npchar.quest.Mtraxx = "true";
			AddQuestRecord("Roger_1", "5");
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Havana_tavernkeeper"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
