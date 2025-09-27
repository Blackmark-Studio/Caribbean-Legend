// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Beszélj, hallgatlak.";
			link.l1 = "Tévedtem. Viszontlátásra.";
			link.l1.go = "Exit";
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_4")
			{
				link.l1 = "Biztos úr, tudomásomra jutott, hogy a hajó 'Cantavro' egyik tisztjét itt tartják fogva. Így van?";
                link.l1.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_8")
			{
				link.l1 = "Azért jöttem vissza, hogy ismét don Lope után érdeklôdjek, tiszt úr. Megkapta már a szabadon bocsátási parancsát?";
                link.l1.go = "Mtraxx_5";
			}
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "Mtraxx":
            dialog.text = "A 'Cantavro'? Don Lope Montoro tisztje? Igen, itt van ôrizetben. Mi a haszna?";
			link.l1 = "Engedélyt kérek, hogy meglátogathassam.";
			link.l1.go = "Mtraxx_1";
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Lope"), "questmarkmain");
		break;
		
		case "Mtraxx_1":
            dialog.text = "Elnézést, de milyen alapon?";
			link.l1 = "Ez csak egy személyes ügy. Ismertem ôt még Európában, és megdöbbentett a bebörtönzésének híre, és az a pletyka, ami az egész városban elterjedt. Szeretnék beszélni vele.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
            dialog.text = "Hm...";
			link.l1 = "Biztos úr, talán én... 'köszönöm' , hogy meglátogathatom?";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            dialog.text = "Erre nincs szükség. Engedélyezem, hogy találkozzon don Montoróval. Az ôrök átengedik.";
			link.l1 = "Köszönöm!";
			link.l1.go = "Mtraxx_4";
		break;
		
		case "Mtraxx_4":
			DialogExit();
            pchar.questTemp.jailCanMove = true;
			pchar.questTemp.Mtraxx = "jewelry_5";
		break;
		
		case "Mtraxx_5":
            dialog.text = "A parancsom az, hogy don Lope Montoro-t közvetlenül a parancsnoknak adjam át. De úgy vélem, még néhány hétig nem hagyja el a cellát. De azért elmehetsz hozzá, amíg még itt van.";
			link.l1 = "Köszönöm, tiszt úr, ezért vagyok itt.";
			link.l1.go = "Mtraxx_6";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtraxx_6":
            DialogExit();
            pchar.questTemp.jailCanMove = true;
			pchar.questTemp.Mtraxx = "jewelry_9";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
